#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    // Durum değişkenleri: Oyuncunun sağlık, enerji, yemek ve sığınak durumunu takip eder
    int saglik = 100;
    int enerji = 100;
    int yemek = 0;
    int siginakVar = 0;

    char komut;
    srand(time(NULL)); // Rastgele sayı üretimi için zaman tabanlı seed ayarı

    printf("=== HAYATTA KALMA SIMULATORU ===\n");
    printf("Komutlar: A(Avlan), S(Siginak Ara), R(Dinlen), E(Envanter), F(Tehlike Dalgasi), P(Sifreli Gecis), X(Cikis)\n");

    // Ana döngü: Kullanıcı 'X' komutunu girene kadar devam eder
    do {
        printf("\nKomut giriniz: ");
        scanf(" %c", &komut);

        switch(komut) {

        // --------------- A: AVLANMA ---------------
        case 'A': {
            printf("\n--- Avlaniyorsun ---\n");

            enerji -= 15; // Enerji azalır 
            if (enerji < 0) enerji = 0; // Enerji alt sınırı kontrolü

            int sans = rand() % 100; // 0-99 arası rastgele sayı

            // Şans değerine göre olay belirlenir 
            if (sans < 40) {
                yemek++; // %40 ihtimalle yemek bulunur
                printf("Yemek buldun! Toplam yemek: %d\n", yemek);
            }
            else if (sans >= 40 && sans < 60) {
                saglik -= 10; // %20 ihtimalle yaralanma
                printf("Yaralandin! Saglik: %d\n", saglik);
            }
            else {
                printf("Hiçbir şey bulamadin.\n"); // %40 ihtimalle boş geçer
            }

            break;
        }

        // --------------- S: SIĞINAK ARAMA ---------------
        case 'S': {
            printf("\n--- Siginak araniyor ---\n");

            // Mantıksal VE (&&) ile enerji ve sağlık kontrolü
            int kosul1 = (enerji > 30);
            int kosul2 = (saglik > 40);

            if (kosul1 && kosul2) { // IF-ELSE ile karar mekanizması
                printf("Siginak buldun!\n");
                siginakVar = 1; // Sığınak bulundu
            } else {
                printf("Siginak bulamadın. Kosullar uygun degil.\n");
            }
            break;
        }

        // --------------- E: ENVANTER GÖRÜNTÜLE ---------------
        case 'E': {
            printf("\n=== Envanter ===\n");
            printf("Saglik: %d\n", saglik);
            printf("Enerji: %d\n", enerji);
            printf("Yemek:  %d\n", yemek);
            printf("Siginak: %s\n", siginakVar ? "Var" : "Yok"); // ? : operatörü ile durum kontrolü
            break;
        }

        // --------------- R: DİNLENME ---------------
        case 'R': {
            printf("\n--- Dinleniyorsun ---\n");

            enerji += 20; // Enerji artışı
            saglik += 10; // Sağlık artışı

            if (enerji > 100) enerji = 100; // Maks sınır kontrolü
            if (saglik > 100) saglik = 100;

            printf("Enerjin yenilendi: %d\n", enerji);
            printf("Sagligin iyilesti: %d\n", saglik);
            break;
        }

        // --------------- F: TEHLİKE DALGASI (FOR DÖNGÜSÜ) ---------------
        case 'F': {
            printf("\n--- Tehlike Dalgasi Basladi ---\n");
            int i;
            for (i = 1; i <= 5; i++) { // For döngüsü ile 5 tur tehlike simülasyonu
                printf("%d. tehlike geliyor...\n", i);

                int olay = rand() % 3; // Rastgele olay seçimi: 0-can kaybı, 1-enerji kaybı, 2-kaçış

                if (olay == 0) {
                    saglik -= 5;
                    if (saglik < 0) saglik = 0;
                    printf("Saldiriya ugradin! Saglik: %d\n", saglik);
                } 
                else if (olay == 1) {
                    enerji -= 5;
                    if (enerji < 0) enerji = 0;
                    printf("Enerjin dustu! Enerji: %d\n", enerji);
                }
                else {
                    printf("Tehlikeden kacmayi basardin!\n");
                }

                if (saglik <= 0) { // Sağlık sıfır olursa oyun biter
                    printf("Oldun! Oyun bitti.\n");
                    return 0;
                }
            }
            break;
        }

        // --------------- P: ŞİFRELİ GEÇİŞ (DO-WHILE DÖNGÜSÜ) ---------------
        case 'P': {
            printf("\n--- Sifreli Kapi ---\n");

            char girilen;
            const char sifre = 'Z';

            do { // En az bir kez çalışır, doğru karakter girilene kadar tekrar eder
                printf("Sifreyi gir (tek karakter): ");
                scanf(" %c", &girilen);

                if (girilen != sifre)
                    printf("Yanlis! Tekrar dene.\n");

            } while (girilen != sifre);

            printf("Kapidan gectin!\n");
            break;
        }

        // --------------- X: ÇIKIŞ ---------------
        case 'X':
            printf("Cikiliyor...\n");
            break;

        // --------------- HATALI KOMUT ---------------
        default:
            printf("Gecersiz komut!\n");
        }

        // Oyuncu öldüyse oyun biter
        if (saglik <= 0) {
            printf("Sagligin tükendi! Oyun bitti.\n");
            break;
        }

    } while (komut != 'X'); // Ana döngü bitiş

    return 0;
}
