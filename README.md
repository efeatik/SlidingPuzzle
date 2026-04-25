# 8-Puzzle Game (C & ncurses)

Terminal tabanlı klasik **8-Puzzle (Sliding Puzzle)** oyunu.
C dili ve `ncurses` kütüphanesi kullanılarak geliştirilmiştir.

---

## Oyun Hakkında

8-Puzzle, 3x3’lük bir tahtada 1’den 8’e kadar numaralı taşları doğru sıraya dizmeye çalıştığınız klasik bir bulmaca oyunudur.

Boş kare (`0`) kullanılarak taşlar hareket ettirilir. Amaç:

```
[1][2][3]
[4][5][6]
[7][8][ ]
```

düzenine ulaşmaktır.

---

## Özellikler

* Rastgele ama **çözülebilir** tahta oluşturma
* Kazanma durumu kontrolü
* Klavye ile kontrol (WASD veya yön tuşları)
* Hamle sayacı
* Terminal tabanlı arayüz (`ncurses`)

---

## Gereksinimler

* C derleyicisi (gcc önerilir)
* `ncurses` kütüphanesi

---

## Derleme ve Çalıştırma

```bash
gcc Puzzle.c -o Puzzle -lncurses
./Puzzle
```

---

## Kontroller

| Tuş   | Açıklama    |
| ----- | ----------- |
| ↑ / W | Yukarı      |
| ↓ / S | Aşağı       |
| ← / A | Sol         |
| → / D | Sağ         |
| Q     | Oyundan çık |

---

## Nasıl Çalışır?

* Tahta **Fisher-Yates shuffle** algoritması ile karıştırılır
* `is_solvable()` fonksiyonu ile çözülüp çözülemeyeceği kontrol edilir
* Sadece **çözülebilir ve başlangıçta çözülmüş olmayan** durumlar kabul edilir
* Oyuncu hamle yaptıkça boş kare yer değiştirir

---

## Oyun Sonu

Tüm taşlar doğru sıraya geldiğinde:

```
KAZANDINIZ!
```

mesajı gösterilir.

---

## NOT:

Proje **Unix-Based işletim sistemleri** için `ncurses` kullanılarak geliştirilmiştir.
Windows işletim sistemleri üzerinde çalışmayacaktır.
Derlerken `-lncurses` eklemeyi unutmayınız.

---
