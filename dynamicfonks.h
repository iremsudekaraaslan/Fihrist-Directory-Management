#ifndef DYNAMICFONKS_H
#define DYNAMICFONKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define LIMIT 1000

// DLL içindeysek export, dışarıdaysak import
#ifdef _USRDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

struct Kisi {
    char ad[MAX];
    char soyad[MAX];
    unsigned int numara;
};

// Fonksiyon prototipleri
DLL_EXPORT int dosyadanOku(struct Kisi kisiler[], int limit);
DLL_EXPORT int kaydet(struct Kisi kisiler[], int kisiSayisi, struct Kisi yeni);
DLL_EXPORT int karsilastirIsim(const void* a, const void* b);
DLL_EXPORT int karsilastirSoyad(const void* a, const void* b);
DLL_EXPORT int karsilastirNumara(const void* a, const void* b);
DLL_EXPORT void bulVeYazIsim(struct Kisi kisiler[], int n, char* aranan);
DLL_EXPORT void bulVeYazSoyad(struct Kisi kisiler[], int n, char* aranan);
DLL_EXPORT void bulVeYazNumara(struct Kisi kisiler[], int n, unsigned int aranan);
DLL_EXPORT void dosyayaYaz(struct Kisi kisiler[], int n);

#endif // DYNAMICFONKS_H
