// src/bridger.c
#include "ntddk.h"
#include "hwcontrol.h"
#include "ai_optimizer.h" // AI mantığı için
#include "ai_ram.h"       // Bellek yönetimi için

// GUI'ye gönderilecek birleştirilmiş veri paketi
typedef struct {
    float temp;
    int fan_speed;
    int layout_mode; // 0: Compact, 1: Wide
    int ram_status;  // 0: Normal, 1: Warning
} GUI_PACKET;

// Ekran çözünürlüğüne göre layout belirleyen AI mantığı
int Bridger_DetermineLayout(int width, int height) {
    if (width >= 2560) return 1; // 4K/Wide
    return 0; // Compact
}

// Tüm verileri toparlayan ve GUI'ye iten ana fonksiyon
void Bridger_ProcessAndPush(int screen_width, int screen_height) {
    GUI_PACKET output;
    
    // 1. Donanım ve AI'dan verileri çek (Data Fusion)
    output.temp = Read_Thermal_Sensor();
    output.fan_speed = Get_Optimal_Fan_Speed();
    
    // 2. Ekran çözünürlüğüne göre ayar yap (Orchestration)
    output.layout_mode = Bridger_DetermineLayout(screen_width, screen_height);
    
    // 3. Bellek kontrolü (Self-Throttling)
    if (Get_RAM_Usage() > 3000) { // 3GB+ sınırı
        output.ram_status = 1;
    } else {
        output.ram_status = 0;
    }
    
    // 4. Veriyi GUI'ye gönder (Ping yapmadan, doğrudan push)
    // Bu fonksiyon arayüz katmanına veri gönderen kancadır
    Push_To_GUI(output);
}

// Kernel katmanından gelen IOCTL isteklerini işleyen ana dispatch
NTSTATUS Bridger_Dispatch(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
    ULONG code = stack->Parameters.DeviceIoControl.IoControlCode;

    switch (code) {
        case IOCTL_AI_SYNC:
            // Python tarafından gönderilen çözünürlük verisini al
            int* res = (int*)Irp->AssociatedIrp.SystemBuffer;
            Bridger_ProcessAndPush(res[0], res[1]);
            break;
            
        default:
            Irp->IoStatus.Status = STATUS_INVALID_DEVICE_REQUEST;
    }

    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return Irp->IoStatus.Status;
}
