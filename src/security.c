// HWcontrol/src/security.c
#include <windows.h>
#include <bcrypt.h>
#include "integrity.h"

// SHA-256 ile dosya bütünlüğü denetimi
BOOL VerifyFileIntegrity(LPCWSTR filePath, PBYTE expectedHash) {
    BCRYPT_ALG_HANDLE hAlg = NULL;
    BCRYPT_HASH_HANDLE hHash = NULL;
    BYTE pbHash[32]; // SHA-256 sonuç uzunluğu

    if (BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_SHA256_ALGORITHM, NULL, 0) != 0) return FALSE;
    BCryptCreateHash(hAlg, &hHash, NULL, 0, NULL, 0, 0);

    // Dosyayı aç ve oku (Basitleştirilmiş blok)
    HANDLE hFile = CreateFileW(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        BYTE buffer[1024];
        DWORD bytesRead;
        while (ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
            BCryptHashData(hHash, buffer, bytesRead, 0);
        }
        CloseHandle(hFile);
    }

    BCryptFinishHash(hHash, pbHash, sizeof(pbHash), 0);
    BCryptDestroyHash(hHash);
    BCryptCloseAlgorithmProvider(hAlg, 0);

    // Orijinal imza ile karşılaştır
    return (memcmp(pbHash, expectedHash, 32) == 0);
}
