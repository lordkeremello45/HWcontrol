#ifndef HWCONTROL_H
#define HWCONTROL_H

#include <ntddk.h>

// 1. Sürücü Kimliği ve Ayarlar
#define DRIVER_NAME L"HWControl"
#define DEVICE_NAME L"\\Device\\HWControl"
#define SYMLINK_NAME L"\\DosDevices\\HWControl"

// 2. Kontrol Yapıları (Donanım ayarlarını burada tutacağız)
typedef struct _HW_CONTROL_DATA {
    ULONG Voltage;       // Voltaj değeri
    ULONG FanSpeed;      // Fan hızı
    BOOLEAN IsActive;    // Donanım aktif mi?
} HW_CONTROL_DATA, *PHW_CONTROL_DATA;

// 3. Fonksiyon Prototipleri (Sürücünün yapacağı işler)
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath);
VOID DriverUnload(PDRIVER_OBJECT DriverObject);

// Donanımla haberleşme fonksiyonu (İleride içini dolduracağız)
NTSTATUS ReadHardwareRegister(ULONG RegisterAddress, PULONG Value);

#endif // HWCONTROL_H
