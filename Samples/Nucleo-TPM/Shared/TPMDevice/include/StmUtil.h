#include <stdbool.h>

#ifndef NDEBUG
#define ITMSTDERR   (0)
#define ITMSIGNAL   (1)
#define ITMCMDRSP   (2)
#define ITMCHANNELS (3)
#define dbgPrint(fmt, ...) fprintf(stderr, "%s: " fmt, GetLogStamp(), ##__VA_ARGS__);
#define dbgPrintAppend(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__);
#define itmPrint(__channel, fmt, ...) fprintf(g_itm[__channel], "%s: " fmt, GetLogStamp(), ##__VA_ARGS__);
#define itmPrintAppend(__channel, fmt, ...) fprintf(g_itm[__channel], fmt, ##__VA_ARGS__);
#else
#define dbgPrint(fmt, ...) ((void)0)
#define dbgPrintAppend(fmt, ...) ((void)0)
#endif
#define logError(fmt, ...) dbgPrint("[ERROR] %s (%s@%u) - " fmt, __func__, __FILE__, __LINE__, ##__VA_ARGS__);
#define logWarning(fmt, ...) dbgPrint("[WARNING] %s (%s@%u) - " fmt, __func__, __FILE__, __LINE__, ##__VA_ARGS__);
#define logInfo(fmt, ...) dbgPrint("[Info] %s (%s@%u) - " fmt, __func__, __FILE__, __LINE__, ##__VA_ARGS__);
extern char logStampStr[40];
extern void* g_itm[ITMCHANNELS];

#define ITMFILENO (4)
#define ITMCHANNELNO (32)
void ITM_Out(uint32_t port, uint8_t ch);

char* GetLogStamp(void);
int BlueButtonTransitionDetected(void);
void SetDutyCycleIndicator(bool on);
void KillUSBLink(void);
void SetRealTimeClock(time_t tm);
void ReadMcuInfo(unsigned char* serial, uint16_t *flashSize, uint16_t *mcuType, uint16_t *mcuRev);
void PerformSystemReset(void);
void InitializeITM();
