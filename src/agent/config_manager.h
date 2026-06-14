#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace ConfigManager {
    inline std::string GetApiKey() {
        std::string filePath = "src/config.json"; // src klasörü içindeki yol
        
        if (!std::filesystem::exists(filePath)) {
            std::cerr << "[Hata] Config dosyası src/ klasöründe bulunamadı!" << std::endl;
            return "";
        }

        std::ifstream inFile(filePath);
        std::string line;
        while (std::getline(inFile, line)) {
            // Basit bir arama: "api_key": "DEGER"
            if (line.find("api_key") != std::string::npos) {
                size_t start = line.find("\"") + 4; // "api_key": " kısmını atla
                size_t end = line.find_last_of("\"");
                return line.substr(start, end - start);
            }
        }
        return "";
    }
}
