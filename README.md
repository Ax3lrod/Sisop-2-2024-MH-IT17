# LAPRES SOAL SHIFT MODUL 2

## Anggota Kelompok

1. Aryasatya Alaauddin 5027231082 (Mengerjakan soal 1 dan 2)
2. Diandra Naufal Abror 5027231004 (Mengerjakan soal 4)
3. Muhamad Rizq Taufan 5027231021 (Mengerjakan soal 3)

## NOMOR 1

Gavriel adalah seorang cyber security enthusiast. Suatu hari, ia dikontrak oleh sebuah perusahaan ternama untuk membuat sebuah program yang cukup rumit dengan bayaran jutaan rupiah. Karena tergoda dengan nominal bayaran tersebut, Gavriel langsung menerima tawaran tersebut. Setelah mencoba membuat dan mengembangkan program tersebut selama seminggu, laptop yang digunakan Gavriel mengalami overheat dan mati total sehingga harus dilarikan ke tukang servis terdekat. Karena keterbatasan waktu dalam pembuatan program dan tidak ingin mengecewakan perusahaan, Gavriel meminta bantuan kalian untuk membuat program tersebut dengan ketentuan sebagai berikut:
Program dapat menerima input path berupa ‘argv’ untuk mengatur folder dimana file akan dieksekusi
Program tersebut berfungsi untuk mereplace string dengan ketentuan sebagai berikut:
a. String m4LwAr3 direplace dengan string [MALWARE]
b. String 5pYw4R3 direplace dengan string [SPYWARE]
c. String R4nS0mWaR3 direplace dengan string [RANSOMWARE]
d. Program harus berjalan secara daemon, dan tidak diperbolehkan menggunakan command system() dalam pembuatan program
e. Program akan secara terus menerus berjalan di background dengan jeda 15 detik
f. Catat setiap penghapusan string yang dilakukan oleh program pada sebuah file bernama virus.log dengan format: [dd-mm-YYYY][HH:MM:SS] Suspicious string at <file_name> successfully replaced!

**Solusi**
**Oleh Aryasatya Alaauddin (5027231082)**

```
#include <stdio.h> // Library standar untuk fungsi input-output
#include <stdlib.h> // Library standar untuk fungsi-fungsi umum
#include <string.h> // Library standar untuk manipulasi string
#include <dirent.h> // Library untuk manipulasi direktori
#include <unistd.h> // Library untuk fungsi-fungsi POSIX
#include <sys/types.h> // Tipe data khusus untuk sistem POSIX
#include <sys/stat.h> // Struktur dan fungsi untuk mendapatkan informasi status file
#include <fcntl.h> // Fungsi untuk mengontrol file descriptor
#include <errno.h> // Variabel global untuk menyimpan kode kesalahan
#include <time.h> // Fungsi-fungsi untuk operasi waktu

#define MAX_PATH_LENGTH 1024 // Definisi konstanta untuk panjang maksimum path
#define MAX_STRING_LENGTH 256 // Definisi konstanta untuk panjang maksimum string

// Fungsi untuk mengganti string dalam sebuah file
void replace_strings(const char *file_path) {
    FILE *file = fopen(file_path, "r+"); // Membuka file untuk dibaca dan ditulis
    if (file == NULL) { // Memeriksa apakah file berhasil dibuka
        perror("Error opening file"); // Mencetak pesan kesalahan jika gagal membuka file
        return; // Keluar dari fungsi jika gagal membuka file
    }

    char *line = NULL; // Pointer untuk menampung baris yang dibaca
    size_t len = 0; // Variabel untuk menampung panjang baris yang dibaca
    ssize_t read; // Variabel untuk menampung jumlah karakter yang dibaca

    while ((read = getline(&line, &len, file)) != -1) { // Loop untuk membaca file per baris
        char *ptr; // Pointer untuk melakukan pencarian string dalam baris
        while ((ptr = strstr(line, "m4LwAr3")) != NULL) { // Loop untuk mencari string "m4LwAr3" dalam baris
            strncpy(ptr, "[MALWARE]", 9); // Menggantikan string "m4LwAr3" dengan "[MALWARE]"
        }
        while ((ptr = strstr(line, "5pYw4R3")) != NULL) { // Loop untuk mencari string "5pYw4R3" dalam baris
            strncpy(ptr, "[SPYWARE]", 9); // Menggantikan string "5pYw4R3" dengan "[SPYWARE]"
        }
        while ((ptr = strstr(line, "R4nS0mWaR3")) != NULL) { // Loop untuk mencari string "R4nS0mWaR3" dalam baris
            strncpy(ptr, "[RANSOMWARE]", 12); // Menggantikan string "R4nS0mWaR3" dengan "[RANSOMWARE]"
        }

        fseek(file, -read, SEEK_CUR); // Menggeser posisi file ke belakang sebelumnya
        fwrite(line, 1, strlen(line), file); // Menulis kembali baris yang telah dimodifikasi ke file
    }

    fclose(file); // Menutup file yang sudah selesai dibaca dan ditulis
    if (line) // Memeriksa apakah `line` tidak NULL
        free(line); // Membebaskan memori yang dialokasikan untuk `line`

    FILE *log_file = fopen("virus.log", "a"); // Membuka file log "virus.log" untuk ditambahkan data
    if (log_file == NULL) { // Memeriksa apakah file log berhasil dibuka
        perror("Error opening log file"); // Mencetak pesan kesalahan jika gagal membuka file log
        return; // Keluar dari fungsi jika gagal membuka file log
    }
    time_t now; // Variabel untuk menampung waktu saat ini
    time(&now); // Mendapatkan waktu saat ini
    struct tm *local = localtime(&now); // Konversi waktu lokal
    fprintf(log_file, "[%02d-%02d-%d][%02d:%02d:%02d] Suspicious string at %s successfully replaced!\n",
            local->tm_mday, local->tm_mon + 1, local->tm_year + 1900, // Menulis tanggal
            local->tm_hour, local->tm_min, local->tm_sec, // Menulis waktu
            file_path); // Menulis path file yang telah dimodifikasi
    fclose(log_file); // Menutup file log
}
```
**replace_strings(const char *file_path)***

Fungsi ini bertujuan untuk membuka sebuah file yang diberikan, membaca setiap baris di dalamnya, dan menggantikan string-string tertentu dengan string-string baru.

* Input: file_path adalah path dari file yang akan diproses.
* Output: Tidak ada (void).

Langkah-langkahnya adalah sebagai berikut:

* Membuka file dengan mode "r+" yang memungkinkan pembacaan dan penulisan.
* Membaca file per baris menggunakan getline.
* Melakukan penggantian string-string tertentu (seperti "m4LwAr3", "5pYw4R3", dan "R4nS0mWaR3") dengan string-string baru (masing-masing "[MALWARE]", "[SPYWARE]", dan "[RANSOMWARE]").
* Menulis kembali baris yang sudah diganti ke dalam file.
* Setelah selesai, file akan ditutup.

Fungsi ini juga mencatat setiap penggantian yang berhasil ke dalam file log virus.log bersama dengan timestamp.

```

// Fungsi untuk memantau direktori secara rekursif
void monitor_folder(const char *folder_path) {
    struct dirent *dp; // Pointer untuk entri direktori
    DIR *dir = opendir(folder_path); // Membuka direktori yang diberikan
    if (dir == NULL) { // Memeriksa apakah direktori berhasil dibuka
        perror("Error opening directory"); // Mencetak pesan kesalahan jika gagal membuka direktori
        return; // Keluar dari fungsi jika gagal membuka direktori
    }

    while ((dp = readdir(dir)) != NULL) { // Loop untuk membaca setiap entri dalam direktori
        char path[MAX_PATH_LENGTH]; // Array untuk menyimpan path lengkap dari entri
        snprintf(path, sizeof(path), "%s/%s", folder_path, dp->d_name); // Menggabungkan `folder_path` dan nama entri menjadi path lengkap

        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) // Memeriksa apakah entri adalah "." atau ".."
            continue; // Melewati "." dan ".."

        struct stat statbuf; // Struktur untuk menyimpan informasi status file
        if (stat(path, &statbuf) == -1) { // Mendapatkan informasi status file
            perror("Error getting file status"); // Mencetak pesan kesalahan jika gagal mendapatkan status file
            continue; // Melanjutkan ke entri berikutnya jika gagal mendapatkan status file
        }

        if (S_ISDIR(statbuf.st_mode)) { // Memeriksa apakah entri adalah direktori
            monitor_folder(path); // Memanggil fungsi secara rekursif jika entri adalah direktori
        } else {
            replace_strings(path); // Memanggil fungsi untuk mengganti string jika entri adalah file
        }
    }

    closedir(dir); // Menutup direktori setelah selesai digunakan
}
```
**monitor_folder(const char *folder_path)***

Fungsi ini digunakan untuk memonitor folder secara rekursif, yaitu mencari file-file dalam folder tersebut dan subfolder-subfoldernya, kemudian melakukan pemrosesan pada file-file tersebut.

* Input: folder_path adalah path dari folder yang akan dimonitor.
* Output: Tidak ada (void).

Langkah-langkahnya adalah sebagai berikut:

* Membuka folder yang diberikan menggunakan opendir.
* Membaca setiap entri (file atau folder) dalam folder menggunakan readdir.
* Jika entri tersebut adalah sebuah folder, fungsi akan dipanggil secara rekursif untuk memonitor folder tersebut.
* Jika entri tersebut adalah sebuah file, fungsi replace_strings akan dipanggil untuk melakukan penggantian string dalam file tersebut.
* Setelah selesai memproses semua entri dalam folder, folder akan ditutup.
```
int main(int argc, char *argv[]) { // Fungsi utama program
    if (argc != 2) { // Memeriksa jumlah argumen yang diberikan
        printf("Usage: %s folder_path\n", argv[0]); // Mencetak cara penggunaan program jika jumlah argumen salah
        return 1; // Keluar dari program dengan status error
    }

    char folder_path[MAX_PATH_LENGTH]; // Array untuk menyimpan path folder
    strncpy(folder_path, argv[1], sizeof(folder_path)); // Menyalin argumen folder_path ke array folder_path

    DIR *dir = opendir(folder_path); // Membuka folder yang diberikan
    if (dir == NULL) { // Memeriksa apakah folder berhasil dibuka
        perror("Invalid folder path"); // Mencetak pesan kesalahan jika folder tidak valid
        return 1; // Keluar dari program dengan status error
    }
    closedir(dir); // Menutup folder setelah selesai digunakan

    pid_t pid = fork(); // Membuat proses baru menggunakan fork
    if (pid < 0) { // Memeriksa apakah fork berhasil
        perror("Error forking"); // Mencetak pesan kesalahan jika gagal fork
        return 1; // Keluar dari program dengan status error
    }

    if (pid > 0) { // Jika proses adalah proses induk
        printf("Daemon process started with PID %d\n", pid); // Mencetak PID dari proses daemon
        return 0; // Keluar dari program dengan status sukses
    }

    if (setsid() == -1) { // Membuat sesi baru untuk proses anak
        perror("Error creating new session"); // Mencetak pesan kesalahan jika gagal membuat sesi baru
        return 1; // Keluar dari program dengan status error
    }

    close(STDIN_FILENO); // Menutup file descriptor untuk stdin
    close(STDOUT_FILENO); // Menutup file descriptor untuk stdout
    close(STDERR_FILENO); // Menutup file descriptor untuk stderr

    while (1) { // Loop utama untuk memantau folder secara terus menerus
        monitor_folder(folder_path); // Memanggil fungsi untuk memantau folder
        sleep(15); // Menunda eksekusi selama 15 detik
    }

    return 0; // Mengembalikan nilai 0 sebagai status sukses
}

```
**main(int argc, char *argv[])***

Fungsi utama program. Ini bertanggung jawab untuk memeriksa argumen yang diberikan, memastikan validitas folder path yang diberikan, menciptakan proses daemon, dan menjalankan loop utama untuk memonitor folder secara terus menerus.

* Input: argc adalah jumlah argumen yang diberikan saat menjalankan program, dan argv adalah array dari argumen-argumen tersebut.
* Output: Mengembalikan status exit.

Langkah-langkahnya adalah sebagai berikut:

* Memeriksa apakah jumlah argumen yang diberikan sesuai.
* Membuka folder yang diberikan untuk memeriksa kevalidannya.
* Menciptakan proses daemon menggunakan fork.
* Jika proses adalah proses induk, mencetak PID proses daemon dan keluar.
* Jika proses adalah proses anak, menjadi proses daemon dengan melakukan sesi baru menggunakan setsid, menutup file descriptor standar, dan memanggil fungsi monitor_folder dalam loop utama dengan interval 15 detik menggunakan sleep.

**Sample Output**

Saya akan membuat folder baru bernama test dan saya akan membuat 2 file txt bernamaa test1.txt dan test2.txt dengan isi berikut.

**test1.txt**
pU=-JWQ$5$)D-[??%AVh]$cB6bm4LwAr3jEQC2p3R{HV]=-AUaxj:Qe+h


**test2.txt**
!aNX,i:!z3W=2;.tHc3&S+}6F)CFf%tfZLP1*w5m1PAzZJUux(
Pd&f8$F5=E?@#[6jd{TJKj]5pYw4R3{KK1?hz384$ge@iba5GAj$gqB41
#C&&a}M9C#f64Eb.?%c)dGbCvJXtU[?SE4h]BY4e1PR4nS0mWaR3{]S/{w?*

Kemudian saya meng compile virus.c dan menjalankan codenya dengan command

./virus /home/ax3lrod//sisop/modul2/praktikum/soal_1/test

![Screenshot from 2024-04-23 17-06-07](https://github.com/Ax3lrod/Sisop-2-2024-MH-IT17/assets/150204139/d9bb624c-f3be-4dbe-8cc5-cdb2129b7db2)

Setelah program dijalankan, dapat dilihat bahwa isi semua file .txt di dalam folder test telah berubah dan file virus.log terbentuk dan terisi.

![Screenshot from 2024-04-23 17-06-26](https://github.com/Ax3lrod/Sisop-2-2024-MH-IT17/assets/150204139/1281f260-ad40-49f2-bfb3-4056a700a1f3)

![Screenshot from 2024-04-23 17-06-46](https://github.com/Ax3lrod/Sisop-2-2024-MH-IT17/assets/150204139/330a3a34-cfe0-41e1-b8e6-5027c54c1367)

![Screenshot from 2024-04-23 17-06-56](https://github.com/Ax3lrod/Sisop-2-2024-MH-IT17/assets/150204139/9b2c3a6e-20e7-4a18-b8a6-c7a943cc34e1)

## NOMOR 2

## NOMOR 3

## NOMOR 4
Salomo memiliki passion yang sangat dalam di bidang sistem operasi. Saat ini, dia ingin mengotomasi kegiatan-kegiatan yang ia lakukan agar dapat bekerja secara efisien. Bantulah Salomo untuk membuat program yang dapat mengotomasi kegiatan dia!
- Salomo ingin dapat membuka berbagai macam aplikasi dengan banyak jendela aplikasi dalam satu command. Namai file program tersebut **setup.c**.
- Program dapat membuka berbagai macam aplikasi dan banyak jendela aplikasi sekaligus (bisa membuka 1 atau lebih aplikasi dengan 1 atau lebih window (kecuali aplikasi yang tidak bisa dibuka dengan banyak window seperti discord)) dengan menjalankan: `./setup -o <app1> <num1> <app2> <num2>.....<appN> <numN>`. Contoh penggunaannya adalah sebagai berikut:**./setup -o firefox 2 wireshark 2**. Program akan membuka 2 jendela aplikasi firefox dan 2 jendela aplikasi wireshark.
- Program juga dapat membuka aplikasi dengan menggunakan file konfigurasi dengan menggunakan `./setup -f file.conf`. Format file konfigurasi dibebaskan, namun pastikan dapat menjalankan fitur dari poin 2.
Contoh isi file.conf:**Firefox 2 Wireshark 3**. Ketika menjalankan command contoh, program akan membuka 2 jendela aplikasi firefox dan 3 jendela aplikasi wireshark.
- Program dapat mematikan semua aplikasi yg dijalankan oleh program tersebut dengan `./setup -k`.
- Program juga dapat mematikan aplikasi yang dijalankan sesuai dengan file konfigurasi. Contohnya: `./setup -k file.conf`. Command ini hanya mematikan aplikasi yang dijalankan dengan `./setup -f file.conf`.

## Solusi
### setup.c

## REVISI
