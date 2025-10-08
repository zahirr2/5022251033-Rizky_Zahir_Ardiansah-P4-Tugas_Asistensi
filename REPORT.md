# Laporan Perbaikan Program

**Nama:** Zahir  
**Judul:** Program Perhitungan Bunga Bank (`bank_interest.c`)

---

Terdapat beberapa perbaikan penting pada program agar dapat berjalan dengan benar dan sesuai dengan standar penulisan C:

### 1. Perbaikan fungsi error output
Mengganti `printf(stderr, ...)` menjadi `fprintf(stderr, ...)` agar pesan error ditampilkan ke stderr dengan benar.

### 2. Perbaikan penulisan tipe data dan enum
Perbaikan dilakukan dengan mengganti `Rekenin` menjadi `Rekening` pada deklarasi struct dan mengubah `SIMPL` menjadi `SIMPLE` agar sesuai dengan deklarasi pada typedef enum.

### 3. Penambahan library math.h
Menambahkan `#include <math.h>` karena fungsi `pow()` digunakan untuk menghitung bunga majemuk.

### 4. Perbaikan format tampilan
Mengganti format `%ld` menjadi `%d` pada penomoran nasabah agar sesuai dengan tipe data `int`.
