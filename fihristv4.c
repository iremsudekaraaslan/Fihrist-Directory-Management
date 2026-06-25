
#include "../libdynamicfihrist/dynamicfonks.h"
#include <stdio.h>



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
                scanf(" "); // Önceki tamponu temizle
                fgets(numaraStr, sizeof(numaraStr), stdin);
                sscanf(numaraStr, "%u", &yeni.numara);

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