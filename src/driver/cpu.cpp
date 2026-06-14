#include <ntddk.h>
#include <intrin.h>
#include "../include/hwcontrol.h"

extern "C" {

// CPU Üreticisini (Vendor) tespit eden fonksiyon
// 0: Unknown, 1: Intel, 2: AMD
int DetectCpuVendor() {
    int cpuInfo[4];
    __cpuid(cpuInfo, 0); // Vendor ID sorgusu
    
    // "GenuineIntel" -> 0x756E6547
    // "AuthenticAMD" -> 0x68747541
    if (cpuInfo[1] == 0x756E6547) return 1; 
    if (cpuInfo[1] == 0x68747541) return 2;
    return 0;
}

// İşlemciyi optimize eden ana fonksiyon
void ApplyCpuBoost() {
    int vendor = DetectCpuVendor();

    // AVX2 desteği yoksa (i3/Ryzen 3 altı) işlemi durdur (Güvenlik Kalkanı)
    int cpuInfo[4];
    __cpuid(cpuInfo, 0x7);
    if (!(cpuInfo[1] & (1 << 5))) {
        DbgPrint("CPU: Modern mimari algılanamadı, optimizasyon pas geçildi.\n");
        return;
    }

    if (vendor == 1) { // INTEL
        // Intel için Turbo Boost Control (IA32_PERF_CTL)
        __writemsr(0x199, 0x0000000000000800);
        DbgPrint("CPU: Intel Turbo Boost moduna optimize edildi.\n");
    } 
    else if (vendor == 2) { // AMD (RYZEN)
        // AMD Zen için CPB (Core Performance Boost) kontrolü
        __writemsr(0xC0010015, 0x0000000000000001);
        DbgPrint("CPU: Ryzen Core Performance Boost aktif edildi.\n");
    }
}
}
