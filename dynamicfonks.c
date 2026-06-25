#define _CRT_SECURE_NO_WARNINGS 
#include "dynamicfonks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dosyadan okuma
int dosyadanOku(struct Kisi kisiler[], int limit) {
    FILE* dosya = fopen("fihrist.txt", "r");
    if (!dosya) return 0;

    int sayac = 0;
    while (sayac < limit &&
        fscanf(dosya, "%s %s %u", kisiler[sayac].ad, kisiler[sayac].soyad, &kisiler[sayac].numara) == 3) {
        sayac++;
    }
    fclose(dosya);
    return sayac;
}

// Kayýt ekleme
int kaydet(struct Kisi kisiler[], int kisiSayisi, struct Kisi yeni) {
    if (kisiSayisi >= LIMIT) {
        printf("Fihrist dolu!\n");
        return kisiSayisi;
    }

    kisiler[kisiSayisi] = yeni;

    FILE* dosya = fopen("fihrist.txt", "a");
    if (!dosya) {
        printf("Dosya açýlmadý!\n");
        return kisiSayisi;
    }
    fprintf(dosya, "%s %s %u\n", yeni.ad, yeni.soyad, yeni.numara);
    fclose(dosya);

    printf("Kaydedildi!\n");
    return kisiSayisi + 1;
}

// Karþýlaþtýrma fonksiyonlarý (qsort ve bsearch için)
int karsilastirIsim(const void* a, const void* b) {
    const struct Kisi* ka = (const struct Kisi*)a;
    const struct Kisi* kb = (const struct Kisi*)b;
    return strcmp(ka->ad, kb->ad);
}

int karsilastirSoyad(const void* a, const void* b) {
    const struct Kisi* ka = (const struct Kisi*)a;
    const struct Kisi* kb = (const struct Kisi*)b;
    return strcmp(ka->soyad, kb->soyad);
}

int karsilastirNumara(const void* a, const void* b) {
    const struct Kisi* ka = (const struct Kisi*)a;
    const struct Kisi* kb = (const struct Kisi*)b;
    if (ka->numara < kb->numara) return -1;
    else if (ka->numara > kb->numara) return 1;
    else return 0;
}

// Bul ve yaz fonksiyonlarý
void bulVeYazIsim(struct Kisi kisiler[], int n, char* aranan) {
    struct Kisi arananKisi = { 0 };
    strcpy(arananKisi.ad, aranan);

    qsort(kisiler, n, sizeof(struct Kisi), karsilastirIsim);

    struct Kisi* bulunan = (struct Kisi*)bsearch(&arananKisi, kisiler, n, sizeof(struct Kisi), karsilastirIsim);

    if (!bulunan) {
        printf("Kayýt bulunamadý.\n");
        return;
    }

    int index = (int)(bulunan - kisiler);

    int i = index;
    while (i >= 0 && strcmp(kisiler[i].ad, aranan) == 0) i--;
    i++;
    while (i < n && strcmp(kisiler[i].ad, aranan) == 0) {
        printf("%s %s %u\n", kisiler[i].ad, kisiler[i].soyad, kisiler[i].numara);
        i++;
    }
}

void bulVeYazSoyad(struct Kisi kisiler[], int n, char* aranan) {
    struct Kisi arananKisi = { 0 };
    strcpy(arananKisi.soyad, aranan);

    qsort(kisiler, n, sizeof(struct Kisi), karsilastirSoyad);

    struct Kisi* bulunan = (struct Kisi*)bsearch(&arananKisi, kisiler, n, sizeof(struct Kisi), karsilastirSoyad);

    if (!bulunan) {
        printf("Kayýt bulunamadý.\n");
        return;
    }

    int index = (int)(bulunan - kisiler);

    int i = index;
    while (i >= 0 && strcmp(kisiler[i].soyad, aranan) == 0) i--;
    i++;
    while (i < n && strcmp(kisiler[i].soyad, aranan) == 0) {
        printf("%s %s %u\n", kisiler[i].ad, kisiler[i].soyad, kisiler[i].numara);
        i++;
    }
}

void bulVeYazNumara(struct Kisi kisiler[], int n, unsigned int aranan) {
    struct Kisi arananKisi = { 0 };
    arananKisi.numara = aranan;

    qsort(kisiler, n, sizeof(struct Kisi), karsilastirNumara);

    struct Kisi* bulunan = (struct Kisi*)bsearch(&arananKisi, kisiler, n, sizeof(struct Kisi), karsilastirNumara);

    if (!bulunan) {
        printf("Kayýt bulunamadý.\n");
        return;
    }

    int index = (int)(bulunan - kisiler);

    int i = index;
    while (i >= 0 && kisiler[i].numara == aranan) i--;
    i++;
    while (i < n && kisiler[i].numara == aranan) {
        printf("%s %s %u\n", kisiler[i].ad, kisiler[i].soyad, kisiler[i].numara);
        i++;
    }
}

// Tüm kayýtlarý dosyaya yeniden yazma fonksiyonu
void dosyayaYaz(struct Kisi kisiler[], int n) {
    FILE* dosya = fopen("fihrist.txt", "w");
    if (!dosya) {
        printf("Dosya yazma hatasý!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(dosya, "%s %s %u\n", kisiler[i].ad, kisiler[i].soyad, kisiler[i].numara);
    }

    fclose(dosya);
    printf("Tüm kayýtlar dosyaya yazýldý.\n");
}