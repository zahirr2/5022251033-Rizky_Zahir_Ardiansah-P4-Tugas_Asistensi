// bank_interest.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef enum { SIMPLE = 1, COMPOUND = 2 } InterestType;

typedef struct {
    char   nama[64];
    double pokok;        // jumlah awal uang
    double rate;         // suku bunga per tahun 
    int    tahun;        // lama menabung (tahun)
    int    n_per_tahun;  // frekuensi kapitalisasi per tahun (untuk majemuk)
    InterestType tipe;   // SIMPLE atau COMPOUND (sederhana atau majemuk)
} Rekening;

double total_simple(const Rekening *r) {
    return r->pokok + r->pokok * r->rate * r->tahun;
}

double total_compound(const Rekening *r) {
    int n = (r->n_per_tahun > 0) ? r->n_per_tahun : 1;
    return r->pokok * pow(1.0 + r->rate / n, (double)(n * r->tahun));
}

void cetak_ringkasan(const Rekening *r) {
    double total = (r->tipe == SIMPLE) ? total_simple(r) : total_compound(r);
    double bunga = total - r->pokok;

    printf("\n--- Ringkasan Rekening ---\n");
    printf("Nama               : %s\n", r->nama);
    printf("Pokok              : Rp %.2f\n", r->pokok);
    printf("Suku Bunga (%%/thn) : %.2f%%\n", r->rate * 100.0);
    printf("Lama (tahun)       : %d\n", r->tahun);
    if (r->tipe == COMPOUND) {
        printf("Kapitalisasi/thn   : %d x\n", r->n_per_tahun);
        printf("Tipe               : Bunga Majemuk\n");
    } else {
        printf("Tipe               : Bunga Sederhana\n");
    }
    printf("Total Bunga        : Rp %.2f\n", bunga);
    printf("Total Akhir        : Rp %.2f\n", total);
}

int main(void) {
    int n;
    printf("Masukkan jumlah nasabah: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Input jumlah nasabah tidak valid.\n");
        return 1;
    }

    // Alokasi dinamis array Rekening
    Rekening *arr = (Rekening*)malloc(sizeof(Rekening) * n);
    if (!arr) {
        fprintf(stderr, "Gagal alokasi memori.\n");
        return 1;
    }

    // Input data untuk setiap nasabah
    for (Rekening *p = arr; p < arr + n; ++p) {
        int tipe;
        double rate_percent;

        printf("\n=== Data Nasabah %d ===\n", (int)(p - arr + 1));
        printf("Nama lengkap: ");
        // Membaca nama (termasuk spasi)
        scanf(" %63[^\n]", p->nama);

        printf("Jumlah pokok (Rp): ");
        if (scanf("%lf", &p->pokok) != 1 || p->pokok < 0) {
            fprintf(stderr, "Input pokok tidak valid.\n");
            free(arr);
            return 1;
        }

        printf("Suku bunga per tahun (%%), mis. 5 untuk 5%%: ");
        if (scanf("%lf", &rate_percent) != 1 || rate_percent < 0) {
            fprintf(stderr, "Input suku bunga tidak valid.\n");
            free(arr);
            return 1;
        }
        p->rate = rate_percent / 100.0;

        printf("Lama menabung (tahun): ");
        if (scanf("%d", &p->tahun) != 1 || p->tahun < 0) {
            fprintf(stderr, "Input tahun tidak valid.\n");
            free(arr);
            return 1;
        }

        printf("Pilih tipe bunga (1 = sederhana, 2 = majemuk): ");
        if (scanf("%d", &tipe) != 1 || (tipe != 1 && tipe != 2)) {
            fprintf(stderr, "Pilihan tipe tidak valid.\n");
            free(arr);
            return 1;
        }
        p->tipe = (tipe == 1) ? SIMPLE : COMPOUND;

        if (p->tipe == COMPOUND) {
            printf("Frekuensi kapitalisasi per tahun (mis. 12 untuk bulanan): ");
            if (scanf("%d", &p->n_per_tahun) != 1 || p->n_per_tahun <= 0) {
                fprintf(stderr, "Frekuensi kapitalisasi tidak valid.\n");
                free(arr);
                return 1;
            }
        } else {
            p->n_per_tahun = 0; // tidak dipakai
        }
    }

    // Output ringkasan untuk setiap nasabah (pakai pointer)
    for (Rekening *p = arr; p < arr + n; ++p) {
        cetak_ringkasan(p);
    }

    free(arr);
    return 0;
}
