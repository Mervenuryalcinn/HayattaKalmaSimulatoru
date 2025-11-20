# KARAKTER TABANLI HAYATTA KALMA SİMÜLATÖRÜ — TEKNİK RAPOR

## 1. Giriş
Bu proje, C programlama dili kullanılarak geliştirilen karakter tabanlı bir Hayatta Kalma Simülatörü uygulamasıdır.  
Oyuncu tek karakterlik komutlar girerek oyunla etkileşime geçer. Program, `switch–case` yapısı ile komutları işler; sağlık, enerji, yemek ve sığınak gibi durumları aritmetik işlemlerle günceller; rastgele olayları `rand()` fonksiyonu ile üretir.  

---
## 🎮 Nasıl Oynanır?

Komutlar tek karakter ile girilir:

| Komut | Açıklama |
|-------|----------|
| A     | Avlan (Yemek bulma, yaralanma veya boş geçme şansı) |
| S     | Sığınak ara (Enerji ve sağlık yeterliyse sığınak bulunur) |
| R     | Dinlen (Enerji ve sağlık artar) |
| E     | Envanteri görüntüle (Sağlık, enerji, yemek, sığınak durumu) |
| F     | Tehlike dalgası (5 tur süren rastgele tehlikeler) |
| P     | Şifreli geçiş (Doğru karakter girene kadar tekrar) |
| X     | Çıkış |

### Örnek Oynanış Akışı

1. `A` komutunu gir → enerji azalır, rastgele yemek bulunabilir.  
2. `F` komutunu gir → 5 tur tehlike döngüsüne girilir.  
3. `P` komutunu gir → doğru şifre girilene kadar devam eder.  
4. `E` komutunu gir → mevcut durumunu görüntüle.  
5. `X` komutu ile oyundan çık.

---
## 2. Durum Yönetimi
Program, oyun boyunca oyuncunun durumunu takip etmek için aşağıdaki değişkenleri kullanır:

- `saglik (int)` → Oyuncunun sağlık seviyesi. Başlangıç değeri 100. Saldırılarla azalır, dinlenme ile artar.
- `enerji (int)` → Oyuncunun enerji seviyesi. Başlangıç değeri 100. Avlanma ve tehlikelerle azalır, dinlenme ile artar.
- `yemek (int)` → Oyuncunun topladığı yemek miktarı. Başlangıç değeri 0. Avlanma ile artar.
- `siginakVar (int)` → Oyuncunun sığınak bulup bulmadığını gösterir (0: yok, 1: var). Sığınak arama komutu ile güncellenir.

Bu değişkenler, oyun sırasında sürekli olarak güncellenir ve oyuncunun hayatta kalma durumunu kontrol etmek için kullanılır.

---

## 3. Komut Sisteminin Yapısı (Switch–Case)
Program kullanıcıdan bir karakter komutu alır: `A`, `S`, `R`, `E`, `F`, `P`, `X`.  
Bu komutlar `switch(komut)` yapısı ile ayrıştırılır. Bu yapı:  
- Kodun daha düzenli görünmesini sağlar,  
- Her komutun bağımsız işlenmesine imkân tanır,  
- Menü tabanlı uygulamalarda en uygun yöntemdir.  

Her komut kendi `case` bloğunda gerekli işlemleri yapar.

---

## 4. Aritmetik ve Mantıksal İşlemler

### 4.1 Avlanma (A komutu)
- Kullanıcı avlandığında enerji aritmetik olarak azalır:  
  ```c
  enerji -= 15;
  Daha sonra rand() ile 0–99 arası değer üretilir ve if–else yapısı ile değerlendirilir:

%40 ihtimalle yemek kazanılır

%20 ihtimalle yaralanılır

Geri kalan %40 ihtimalle hiçbir şey olmaz

Mantıksal operatör kullanımı:

if (sans < 40)
else if (sans >= 40 && sans < 60)

Bu işlem sayesinde program, farklı şans aralıklarına göre doğru aksiyonu seçer ve karar süreci kontrol altında tutulur.

---
### 4.2 Sığınak Arama (S komutu)

Enerji > 30 ve sağlık > 40 ise oyuncu sığınak bulur:

if ((enerji > 30) && (saglik > 40)) {
    siginakVar = 1;
}
Mantıksal AND (&&) operatörü, iki koşulun aynı anda doğru olmasını gerektirir.

IF–ELSE yapısı ile koşullar sağlanmazsa oyuncuya sığınak bulunamadığı bildirilir.

---
### 4.3 Dinlenme (R komutu)

Dinlenme sırasında enerji ve sağlık artırılır:

enerji += 20;
saglik += 10;

Üst sınır kontrolü IF ile yapılır:

if (enerji > 100) enerji = 100;
if (saglik > 100) saglik = 100;

---

### 5. Döngüler
### .1 For Döngüsü – Tehlike Dalgası (F komutu)

Oyuncu 5 tur süren bir tehlike dalgasına girer. For döngüsü ile yapılır:

for (i = 1; i <= 5; i++) {
    int olay = rand() % 3;
} 
Amaç: Oyuncunun karşılaştığı tehlikeleri simüle etmek.

rand() % 3 → 0, 1 veya 2 değerlerinden rastgele biri seçilir:

0 → Sağlık kaybı (saglik -= 5)

1 → Enerji kaybı (enerji -= 5)

2 → Kaçış başarılı, oyuncu zarar görmez

Her turda sağlık veya enerji azalır, sağlık 0 veya altına düşerse oyun sona erer.

---
### 5.2 Do–While Döngüsü – Şifreli Geçiş (P komutu)

Oyuncu doğru karakteri girene kadar döngü tekrar eder:

do {
    scanf(" %c", &girilen);
} while (girilen != sifre);


Neden do–while? Kullanıcı şifreyi en az bir kez denemek zorundadır.

---
### 6. Programın Çalışma Akışı (Örnek)

Oyuncu A (Avlan) komutunu girer → enerji azalır, rastgele yemek bulunabilir.

Oyuncu F komutunu girer → 5 tur tehlike döngüsüne girilir.

Oyuncu P komutunu girer → doğru şifre girilene kadar döngü devam eder.

Oyuncu E komutu ile mevcut sağlık/enerji/yemek durumu görüntülenir.

X komutu ile program kapanır.



