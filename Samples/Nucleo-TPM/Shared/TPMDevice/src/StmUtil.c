#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "stm32l4xx_hal.h"
#include "usb_device.h"
#include "StmUtil.h"

// RTC initialized by MX_RTC_Init
extern RTC_HandleTypeDef hrtc;

typedef unsigned char DEVICE_UNIQUE_ID_T[12];
#define DEVICE_UNIQUE_ID (*(DEVICE_UNIQUE_ID_T*)(UID_BASE))
#define DEVICE_FLASH_SIZE (*(uint16_t *)(FLASHSIZE_BASE))
#define DEVICE_TYPE (*(uint16_t *) (DBGMCU->IDCODE & 0x00000fff))
#define DEVICE_REV (*(uint16_t *) (DBGMCU->IDCODE >> 16))
char __attribute__((section (".ram2"))) logStampStr[40] = {0};
void* __attribute__((section (".ram2"))) g_itm[ITMCHANNELS] = {0};

GPIO_PinState BlueButtonLast = GPIO_PIN_SET;
int BlueButtonTransitionDetected(void)
{
    GPIO_PinState PPButton = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
    if((PPButton == GPIO_PIN_RESET) && (BlueButtonLast == GPIO_PIN_SET))
    {
        // Now pressed
        BlueButtonLast = PPButton;
        return 1;
    }
    else if((PPButton == GPIO_PIN_SET) && (BlueButtonLast == GPIO_PIN_RESET))
    {
        // Now released
        BlueButtonLast = PPButton;
        return -1;
    }
    // No change
    return 0;
}

#ifndef NDEBUG
#define ITM_PORT_BITS (0xffffffff)
void InitializeITM()
{
//    CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk; /* enable trace in core debug */
//    ITM->TCR = ITM_TCR_TraceBusID_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_SYNCENA_Msk | ITM_TCR_ITMENA_Msk; /* ITM Trace Control Register */
//    ITM->TPR = ITM_TPR_PRIVMASK_Msk; /* ITM Trace Privilege Register */
//    ITM->TER = ITM_PORT_BITS; /* ITM Trace Enable Register. Enabled tracing on stimulus ports. One bit per stimulus port. */
//    *((volatile unsigned *)(ITM_BASE + 0x01000)) = 0x400003FE; /* DWT_CTRL */
//    *((volatile unsigned *)(ITM_BASE + 0x40304)) = 0x00000100; /* Formatter and Flush Control Register */

    for(uint32_t n = 0; n < ITMCHANNELS; n++)
    {
        char fileName[10];
        sprintf(fileName, "ITM[%02u]", (unsigned int)n);
        g_itm[n] = (void*)fopen(fileName, "wb");
    }
}

void ITM_Out(uint32_t port, uint8_t ch)
{
    while(ITM->PORT[port].u32 == 0);
    ITM->PORT[port].u8 = ch;
}
#endif

void SetDutyCycleIndicator(bool on)
{
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

char* GetLogStamp(void)
{
    RTC_TimeTypeDef time = {0};
    RTC_DateTypeDef date = {0};
    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);

    sprintf(logStampStr, "%04d.%02d.%02d-%02d:%02d:%02d.%03dGMT",
                date.Year + 2000,
                date.Month,
                date.Date,
                time.Hours,
                time.Minutes,
                time.Seconds,
                (int)((1000 / time.SecondFraction) * (time.SecondFraction - time.SubSeconds)));
    return logStampStr;
}

void KillUSBLink(void)
{
    dbgPrint("USB de-initialization...\r\n");
    MX_USB_DEVICE_DeInit();
}

void SetRealTimeClock(time_t tm)
{
    struct tm* local = localtime((time_t*)&tm);
    RTC_TimeTypeDef time = {0};
    RTC_DateTypeDef date = {0};
    date.Year = local->tm_year - 100;
    date.Month = local->tm_mon + 1;
    date.Date = local->tm_mday;
    date.WeekDay = local->tm_wday  + 1;
    time.Hours = local->tm_hour;
    time.Minutes = local->tm_min;
    time.Seconds = local->tm_sec;
    HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN);
}

void ReadMcuInfo(unsigned char* serial, uint16_t *flashSize, uint16_t *mcuType, uint16_t *mcuRev)
{
    if(serial)
    {
        memcpy(serial, DEVICE_UNIQUE_ID, sizeof(DEVICE_UNIQUE_ID));
    }
    if(flashSize)
    {
        *flashSize = DEVICE_FLASH_SIZE;
    }
    if(mcuType)
    {
        *mcuType = DEVICE_TYPE;
    }
    if(mcuRev)
    {
        *mcuRev = DEVICE_REV;
    }
}

void PerformSystemReset(void)
{
    dbgPrint("Executing NVIC_SystemReset()...\r\n");
    HAL_Delay(1);
    NVIC_SystemReset();
}
