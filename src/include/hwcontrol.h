#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <ntddk.h> 

// --- CPU ve Donanım Fonksiyon Tanımları ---
void ApplyCpuBoost(); 

// --- Cihaz İsimleri ---
#define DEVICE_NAME     L"\\Device\\HWControl"
#define SYMLINK_NAME    L"\\DosDevices\\HWControl"

// --- IOCTL Komut Kodu ---
#define IOCTL_SET_FAN_SPEED CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)

// --- Veri Yapısı ---
#pragma pack(push, 1)
typedef struct _FAN_COMMAND {
    unsigned long speed_percentage; 
} FAN_COMMAND, *PFAN_COMMAND;
#pragma pack(pop)

#ifdef __cplusplus
}
#endif
