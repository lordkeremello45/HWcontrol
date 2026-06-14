#include <ntddk.h>

// Sürücü durdurulduğunda yapılacak işlem
VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("HWControl: Sürücü durduruldu.\n");
}

// Sürücünün giriş noktası (DriverEntry)
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    // Unload fonksiyonunu belirtiyoruz
    DriverObject->DriverUnload = DriverUnload;

    DbgPrint("HWControl: Sürücü başarıyla yüklendi.\n");

    return STATUS_SUCCESS;
}
