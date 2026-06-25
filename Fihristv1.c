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
//const generic türün sabit olduðunu belirtiyor belirsiz türdeler 
//Bildiðimiz türe çevirerek gerçek veriye ulaþýrýz dizimin elemanlarý struct türünde
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

void bulVeYazIsim(struct Kisi kisiler[], int n, char* aranan) {
    struct Kisi arananKisi = { 0 };
    strcpy(arananKisi.ad, aranan);

    //aranan stringindeki ismi, arananKisi.ad alanýna kopyala

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

int main() {
    struct Kisi kisiler[LIMIT];
    int kisiSayisi = dosyadanOku(kisiler, LIMIT);
    char secim[20];

    while (1) {
        printf("\nFIHRIST\n");
        printf("kaydet\n");
        printf("listele\n");
        printf("bul\n");
        printf("cikmak icin q\n");
        printf("Isleminizi girin: ");
        scanf("%19s", secim);

        if (strcmp(secim, "q") == 0) {
            printf("Programdan cikiliyor.\n");
            break;
        }
        else if (strcmp(secim, "kaydet") == 0) {
            struct Kisi yeni;
            while (1) {
                printf("Isim girin (q ile cik): ");
                scanf("%99s", yeni.ad);
                if (strcmp(yeni.ad, "q") == 0) break;

                printf("Soyisim girin: ");
                scanf("%99s", yeni.soyad);

                char numaraStr[100];
                printf("Numara girin: ");
                scanf(" "); // önceki tamponu temizle
                fgets(numaraStr, sizeof(numaraStr), stdin);// entera kadar olan kýsmý okur her zaman string okur
                //stdin verildi kullanýcýdan okur
                sscanf(numaraStr, "%u", &yeni.numara);//metini unsigned int brkliyoruz 


                kisiSayisi = kaydet(kisiler, kisiSayisi, yeni);
            }
        }
        else if (strcmp(secim, "listele") == 0) {
            printf("\nFIHRIST:\n");
            for (int i = 0; i < kisiSayisi; i++) {
                printf("%s %s %u\n", kisiler[i].ad, kisiler[i].soyad, kisiler[i].numara);
            }
        }
        else if (strcmp(secim, "bul") == 0) {
            char aramaSecimi;
            char arananStr[MAX];
            unsigned int arananNumara;

            printf("\nNe aramak istiyorsun?\n");
            printf("a. Isim\n");
            printf("b. Soyisim\n");
            printf("c. Numara\n");
            printf("Seciminizi girin: ");
            scanf(" %c", &aramaSecimi);

            if (aramaSecimi == 'a') {
                printf("Aranacak ismi girin: ");
                scanf("%99s", arananStr);
                bulVeYazIsim(kisiler, kisiSayisi, arananStr);
            }
            else if (aramaSecimi == 'b') {
                printf("Aranacak soyismi girin: ");
                scanf("%99s", arananStr);
                bulVeYazSoyad(kisiler, kisiSayisi, arananStr);
            }
            else if (aramaSecimi == 'c') {
                printf("Aranacak numarayi girin: ");
                scanf("%u", &arananNumara);
                bulVeYazNumara(kisiler, kisiSayisi, arananNumara);
            }
            else {
                printf("Gecersiz secim yaptiniz.\n");
            }
        }
        else {
            printf("Gecersiz secim yaptiniz.\n");
        }
    }

    return 0;
}