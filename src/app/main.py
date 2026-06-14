import customtkinter as ctk
from bridge import HWControlBridge

# Kurumsal Lacivert & Siyah Tema Ayarları
COLORS = {
    "bg": "#0A0C10",        # Arka plan - Derin Siyah
    "card": "#0F1318",      # Kart/Panel rengi - Lacivert-Gri
    "accent": "#002D72",    # Kurumsal Lacivert - Vurgu
    "text": "#E8EDF5"       # Metin rengi - Açık Gri
}

class HWControlApp(ctk.CTk):
    def __init__(self):
        super().__init__()

        # Köprü (Driver Connection)
        self.bridge = HWControlBridge()

        # Pencere Ayarları
        self.title("HWControl - Kernel Manager")
        self.geometry("450x350")
        self.configure(fg_color=COLORS["bg"])

        # Ana Panel
        self.main_frame = ctk.CTkFrame(self, fg_color=COLORS["card"], corner_radius=10)
        self.main_frame.pack(fill="both", expand=True, padx=20, pady=20)

        # Başlık
        self.title_label = ctk.CTkLabel(
            self.main_frame, text="SİSTEM FAN KONTROLÜ", 
            font=("Consolas", 18, "bold"), text_color=COLORS["text"]
        )
        self.title_label.pack(pady=25)

        # Fan Hızı Slider
        self.slider = ctk.CTkSlider(
            self.main_frame, from_=0, to=100, 
            progress_color=COLORS["accent"], fg_color=COLORS["bg"]
        )
        self.slider.pack(pady=20, padx=40, fill="x")
        self.slider.set(50) # Başlangıç hızı %50

        # Uygula Butonu
        self.apply_btn = ctk.CTkButton(
            self.main_frame, text="UYGULA", 
            fg_color=COLORS["accent"], hover_color="#003E9C",
            command=self.on_apply
        )
        self.apply_btn.pack(pady=20)

    def on_apply(self):
        speed = int(self.slider.get())
        # bridge üzerinden sürücüye gönderim yapıyoruz
        if self.bridge.send_fan_command(speed):
            print(f"Başarılı: Fan hızı %{speed} olarak ayarlandı.")
        else:
            print("Hata: Sürücüye ulaşılamadı. Uygulamayı Yönetici olarak çalıştırdınız mı?")

if __name__ == "__main__":
    app = HWControlApp()
    app.mainloop()
