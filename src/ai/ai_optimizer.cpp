// src/ai/ai_optimizer.cpp
#include <iostream>
#include <vector>

class AIOptimizer {
private:
    // Öğrenilmiş ağırlıklar (Weights)
    float cooling_efficiency_weight = 0.5f; 

public:
    // Sistemi eğitmek için verileri analiz eden fonksiyon
    void optimize_strategy(float temp, int speed, float result_temp) {
        // Eğer hız artışı sıcaklığı düşürdüyse, ağırlığı artır (Reward)
        if (result_temp < temp) {
            cooling_efficiency_weight += 0.01f;
        } else {
            cooling_efficiency_weight -= 0.01f;
        }
        std::cout << "Model optimize edildi. Yeni verimlilik katsayısı: " << cooling_efficiency_weight << std::endl;
    }

    // Karar verme fonksiyonu
    int suggest_speed(float temp) {
        return (int)(temp * cooling_efficiency_weight);
    }
};
