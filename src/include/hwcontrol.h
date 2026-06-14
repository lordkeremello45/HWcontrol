#pragma once

// C++ ve C projelerinde uyumlu olması için
#ifdef __cplusplus
extern "C" {
#endif

#include <ntddk.h> // Kernel tanımları için gerekli

// Cihaz isimleri
#define DEVICE_NAME     L"\\Device\\HWControl"
#define SYMLINK_NAME    L"\\DosDevices\\HWControl"

// IOCTL Komut Kodu (Sürücüye ne yapması gerektiğini söyler)
// 0x801, 0x802 gibi özel kodlar veriyoruz
#define IOCTL_SET_FAN_SPEED CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)

// Veri Yapısı (Python'dan gönderilen paket)
#pragma pack(push, 1)
typedef struct _FAN_COMMAND {
    unsigned long speed_percentage; // 0-100 arası değer
} FAN_COMMAND, *PFAN_COMMAND;
#pragma pack(pop)

#ifdef __cplusplus
}
#endif
