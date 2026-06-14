import ctypes
from ctypes import wintypes

# IOCTL kodu: 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS 
# Bu değer, Windows'un CTL_CODE makrosuyla hesaplanan standart değerdir.
IOCTL_SET_FAN_SPEED = 0x222004

class HWControlBridge:
    def __init__(self):
        # Sürücüye (Symbolic Link) erişim sağlamaya çalışıyoruz
        # "\\\\.\\HWControl" ismi main.cpp'de tanımladığımız isimle aynı olmalı.
        self.handle = ctypes.windll.kernel32.CreateFileW(
            "\\\\.\\HWControl",
            0x40000000,  # GENERIC_WRITE
            0,
            None,
            3,           # OPEN_EXISTING
            0x80,        # FILE_ATTRIBUTE_NORMAL
            None
        )

    def send_fan_command(self, speed):
        """Sürücüye fan hızı verisini gönderir."""
        if self.handle == -1:
            print("Hata: Sürücü handle'ı alınamadı. Sürücü yüklü mü?")
            return False

        # Sürücü tarafındaki _FAN_COMMAND yapısının Python karşılığı
        class FAN_COMMAND(ctypes.Structure):
            _fields_ = [("speed_percentage", ctypes.c_ulong)]

        cmd = FAN_COMMAND(speed_percentage=speed)
        bytes_returned = wintypes.DWORD(0)

        # IOCTL isteğini gönder
        result = ctypes.windll.kernel32.DeviceIoControl(
            self.handle,
            IOCTL_SET_FAN_SPEED,
            ctypes.byref(cmd),
            ctypes.sizeof(cmd),
            None,
            0,
            ctypes.byref(bytes_returned),
            None
        )

        return result != 0

    def close(self):
        """Bağlantıyı güvenli kapat."""
        if self.handle != -1:
            ctypes.windll.kernel32.CloseHandle(self.handle)
