#define SIGNALMAGIC (0x326d7054) //Tpm2
#define MAX_TPM_MESSAGE_SIZE (sizeof(unsigned int) + 2048)

typedef enum
{
    SignalNothing = 0,
    SignalShutdown,
    SignalReset,
    SignalSetClock,
        // IN {UINT32 time}
    SignalCancelOn,
    SignalCancelOff,
    SignalCommand,
        // IN {BYTE Locality, UINT32 InBufferSize, BYTE[InBufferSize] InBuffer}
        // OUT {UINT32 OutBufferSize, BYTE[OutBufferSize] OutBuffer}
    SignalResponse,
        // OUT {UINT32 OutBufferSize, BYTE[OutBufferSize] OutBuffer}
} signalCode_t;

typedef struct
{
    unsigned int magic;
    signalCode_t signal;
    unsigned int dataSize;
} signalHdr_t;

typedef union
{
    struct
    {
        unsigned int time;
    } SignalSetClockPayload;
    struct
    {
        unsigned int locality;
        unsigned int cmdSize;
        unsigned char cmd[1];
    } SignalCommandPayload;
} signalPayload_t, *pSignalPayload_t;

typedef union
{
    signalHdr_t s;
    unsigned char b[sizeof(signalHdr_t)];
} signalWrapper_t, *pSignalWrapper_t;

typedef struct tpmOperationsFlags_t
{
    unsigned char resetRequested : 1;
    unsigned char powerOffRequested : 1;
    unsigned char executionRequested : 1;
    unsigned char responseRequested : 1;
} tpmOperationsFlags_t;

typedef struct tpmOperation_t
{
    tpmOperationsFlags_t flags;
    int cmdSize;
    int receivingCmd;
    int rspSize;
    unsigned char msgBuf[MAX_TPM_MESSAGE_SIZE];
} tpmOperation_t;

extern volatile tpmOperation_t tpmOp;

int BlueButtonTransitionDetected(void);
void SetDutyCycleIndicator(bool on);
void KillUSBLink(void);
void SetRealTimeClock(time_t tm);
void ReadMcuInfo(unsigned char* serial, uint16_t *flashSize, uint16_t *mcuType, uint16_t *mcuRev);
void PerformSystemReset(void);
void HAL_Delay(uint32_t Delay);
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);

bool TpmInitializeDevice(void);
bool TpmOperationsLoop(void);
void TpmConnectionReset(void);
bool TpmSignalEvent(uint8_t* Buf, uint32_t *Len);
