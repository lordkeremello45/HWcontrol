// src/ai/ai_core.c

#include <stdio.h>

// Sabit Güvenlik Limitleri
#define CRITICAL_TEMP 95
#define WARNING_TEMP 80

// Bu fonksiyon Python'dan çağrıldığında sisteme anında tepki verir
// 0: Normal, 1: Uyarı, 2: Acil Kapatma
int get_thermal_action(int current_temp) {
    
    // 1. En kritik kontrol (En hızlı çalışan)
    if (current_temp >= CRITICAL_TEMP) {
        return 2; // Acil durum: Fanı %100 yap ve korumaya al
    }
    
    // 2. Uyarı kontrolü
    if (current_temp >= WARNING_TEMP) {
        return 1; // Performans moduna geç
    }
    
    // 3. Normal durum
    return 0; // Dengeli mod
}

// Donanım register'ına yazacakmış gibi davranan bir simülasyon
void set_fan_speed_raw(int speed) {
    // Burada ileride gerçek sürücü (kernel) iletişimini kuracağız
    printf("Hardware Action: Fan speed set to %d%%\n", speed);
}
