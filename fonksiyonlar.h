#pragma once
#ifndef FONKSIYONLAR_H
#define FONKSIYONLAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define LIMIT 1000

struct Kisi {
    char ad[MAX];
    char soyad[MAX];
    unsigned int numara;
};

// Fonksiyon prototipleri
int dosyadanOku(struct Kisi kisiler[], int limit);
int kaydet(struct Kisi kisiler[], int kisiSayisi, struct Kisi yeni);

int karsilastirIsim(const void* a, const void* b);
int karsilastirSoyad(const void* a, const void* b);
int karsilastirNumara(const void* a, const void* b);

void bulVeYazIsim(struct Kisi kisiler[], int n, char* aranan);
void bulVeYazSoyad(struct Kisi kisiler[], int n, char* aranan);
void bulVeYazNumara(struct Kisi kisiler[], int n, unsigned int aranan);
void dosyayaYaz(struct Kisi kisiler[], int n);

#endif