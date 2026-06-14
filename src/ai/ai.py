# src/ai/ai.py
import ctypes
import os

# C tabanlı refleks sistemini yükle
ai_lib = ctypes.CDLL(os.path.join(os.path.dirname(__file__), "ai_core.dll"))

class AICore:
    def __init__(self):
        self.history = []  # Geçmiş sıcaklıkları tutar (AI'ın hafızası)

    def calculate_smart_speed(self, current_temp, current_load):
        # 1. Refleks Kontrolü (Güvenlik)
        if ai_lib.get_thermal_action(current_temp) == 2:
            return 100
        
        # 2. AI'ın Hafızası (Trend Analizi)
        # Sıcaklık yükselme eğilimindeyse, fanı daha agresif artır
        self.history.append(current_temp)
        if len(self.history) > 10: self.history.pop(0)
        
        trend = 0
        if len(self.history) == 10:
            trend = self.history[-1] - self.history[0] # Trend: pozitifse ısınıyor

        # 3. Kendi "Zeka" Mantığın (Heuristic Algorithm)
        # Sıcaklığa ve Trende göre hız hesabı
        base_speed = (current_temp * 0.8) + (current_load * 0.2)
        final_speed = base_speed + (trend * 2) # Isınma eğilimindeyse bonus hız
        
        return int(max(20, min(final_speed, 100)))
