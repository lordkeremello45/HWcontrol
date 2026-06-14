#include <ntddk.h>
#include "../include/hwcontrol.h"

// I/O İsteklerini işleyen merkez fonksiyon
NTSTATUS DriverDispatch(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    UNREFERENCED_PARAMETER(DeviceObject);
    PIO_STACK_LOCATION irpStack = IoGetCurrentIrpStackLocation(Irp);
    
    if (irpStack->MajorFunction == IRP_MJ_DEVICE_CONTROL) {
        if (irpStack->Parameters.DeviceIoControl.IoControlCode == IOCTL_SET_FAN_SPEED) {
            
            PFAN_COMMAND fanCmd = (PFAN_COMMAND)Irp->AssociatedIrp.SystemBuffer;
            if (fanCmd && irpStack->Parameters.DeviceIoControl.InputBufferLength >= sizeof(FAN_COMMAND)) {
                
                // --- BURAYA DONANIM MANTIĞINI EKLEYECEĞİZ ---
                // Örnek: SetFanSpeed(fanCmd->speed_percentage);
                DbgPrint("HWControl: Yeni Fan Hızı: %lu\n", fanCmd->speed_percentage);
                
                Irp->IoStatus.Status = STATUS_SUCCESS;
            } else {
                Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
            }
        }
    } else {
        Irp->IoStatus.Status = STATUS_SUCCESS;
    }

    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return Irp->IoStatus.Status;
}

// Sürücü başlatma noktası
extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    UNICODE_STRING devName = RTL_CONSTANT_STRING(DEVICE_NAME);
    UNICODE_STRING symLink = RTL_CONSTANT_STRING(SYMLINK_NAME);
    PDEVICE_OBJECT deviceObject;

    NTSTATUS status = IoCreateDevice(DriverObject, 0, &devName, FILE_DEVICE_UNKNOWN, 0, FALSE, &deviceObject);
    if (!NT_SUCCESS(status)) return status;

    status = IoCreateSymbolicLink(&symLink, &devName);
    if (!NT_SUCCESS(status)) {
        IoDeleteDevice(deviceObject);
        return status;
    }

    DriverObject->DriverUnload = [](PDRIVER_OBJECT DriverObject) {
        UNICODE_STRING symLink = RTL_CONSTANT_STRING(SYMLINK_NAME);
        IoDeleteSymbolicLink(&symLink);
        IoDeleteDevice(DriverObject->DeviceObject);
    };

    for (int i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
        DriverObject->MajorFunction[i] = DriverDispatch;

    return STATUS_SUCCESS;
}
