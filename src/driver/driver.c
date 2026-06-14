// HWcontrol/src/bridger.c

// Donanım verisini sürücüden (IOCTL ile) çeken evrensel fonksiyon
float GetHardwareThermal(VendorType vendor) {
    HAL_DATA_PACKET packet;
    packet.command = GET_THERMAL_CMD;
    packet.vendor = vendor;

    // Sürücüye IOCTL isteği gönder (main.c üzerinden)
    if (CallDriverDevice(&packet)) {
        return packet.value; // Sürücüden dönen işlenmiş ısı verisi
    }
    
    return 0.0f; // Hata durumunda güvenli dönüş
}
