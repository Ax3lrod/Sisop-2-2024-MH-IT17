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

Paul adalah seorang mahasiswa semester 4 yang diterima magang di perusahaan XYZ. Pada hari pertama magang, ia diberi tugas oleh atasannya untuk membuat program manajemen file sederhana. Karena kurang terbiasa dengan bahasa C dan environment Linux, ia meminta bantuan kalian untuk mengembangkan program tersebut.
Atasannya meminta agar program tersebut dapat berjalan secara daemon dan dapat mengunduh serta melakukan unzip terhadap file berikut. Atasannya juga meminta program ini dibuat tanpa menggunakan command system()

Setelah ditelusuri, ternyata hanya 6 file teratas yang nama filenya tidak dienkripsi. Oleh karena itu, bantulah Paul untuk melakukan dekripsi terhadap nama file ke-7 hingga terakhir menggunakan algoritma ROT19

Setelah dekripsi selesai, akan terlihat bahwa setiap file memuat salah satu dari kode berikut: r3N4mE, d3Let3, dan m0V3. Untuk setiap file dengan nama yang memuat kode d3Let3, hapus file tersebut. Sementara itu, untuk setiap file dengan nama yang memuat kode r3N4mE, lakukan hal berikut:
Jika ekstensi file adalah “.ts”, rename filenya menjadi “helper.ts”
Jika ekstensi file adalah “.py”, rename filenya menjadi “calculator.py”
Jika ekstensi file adalah “.go”, rename filenya menjadi “server.go”
Jika file tidak memuat salah satu dari ekstensi diatas, rename filenya menjadi “renamed.file”

Atasan Paul juga meminta agar program ini dapat membackup dan merestore file. Oleh karena itu, bantulah Paul untuk membuat program ini menjadi 3 mode, yaitu:
default: program berjalan seperti biasa untuk me-rename dan menghapus file. Mode ini dieksekusi ketika program dijalankan tanpa argumen tambahan, yaitu dengan command ./management saja
backup: program memindahkan file dengan kode m0V3 ke sebuah folder bernama “backup”
restore: program mengembalikan file dengan kode m0V3 ke folder sebelum file tersebut dipindahkan
Contoh penggunaan: ./management -m backup

Terkadang, Paul perlu mengganti mode dari program ini tanpa menghentikannya terlebih dahulu. Oleh karena itu, bantulan Paul untuk mengintegrasikan kemampuan untuk mengganti mode ini dengan mengirim sinyal ke daemon, dengan ketentuan:
SIGRTMIN untuk mode default
SIGUSR1 untuk mode backup
SIGUSR2 untuk mode restore
Contoh penggunaan: kill -SIGUSR2 <pid_program>

Program yang telah dibuat ini tidak mungkin akan dijalankan secara terus-menerus karena akan membebani sistem. Maka dari itu, bantulah Paul untuk membuat program ini dapat dimatikan dengan aman dan efisien

Terakhir, program ini harus berjalan setiap detik dan mampu mencatat setiap peristiwa yang terjadi ke dalam file .log yang bernama “history.log” dengan ketentuan:
Format: [nama_user][HH:MM:SS] - <nama_file> - <action>
nama_user adalah username yang melakukan action terhadap file
Format action untuk setiap kode:
kode r3N4mE: Successfully renamed.
kode d3Let3: Successfully deleted.
mode backup: Successfully moved to backup.
mode restore: Successfully restored from backup.
Contoh pesan log:
[paul][00:00:00] - r3N4mE.ts - Successfully renamed.
[paul][00:00:00] - m0V3.xk1 - Successfully restored from backup.

Berikut adalah struktur folder untuk pengerjaan nomor 2:
    soal_2/
    ├── history.log
    ├── management.c
    └── library/
        └── backup/

**Solusi**
**Oleh Aryasatya Alaauddin**

```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <ctype.h>

#define LOG_FILE "../history.log" // Change path to outside library folder
#define BACKUP_DIR "../library/backup" // Change path to outside library folder
#define FILE_URL "https://drive.google.com/uc?export=download&id=1rUIZmp10lXLtCIH3LAZJzRPeRks3Crup"
#define FILE_NAME "../library.zip" // Change path to outside library folder

#define MAX_FILENAME_LEN 256
#define MAX_HISTORY_LEN 512 // Increased buffer size for log entries

// Deklarasi fungsi
void downloadAndUnzipFile(); // Function declaration for downloading and unzipping a file
void decryptFileName(char *filename); // Function declaration for decrypting a file name
void manageFiles(); // Function declaration for managing files in the library directory
void backupFiles(); // Function declaration for backing up files
void restoreFiles(); // Function declaration for restoring files from backup
void signalHandler(int signum); // Signal handler function declaration
void logAction(const char *filename, const char *action); // Function declaration for logging actions
void download_and_extract_file(); // Function declaration for downloading and extracting a file
void renameDecryptedFiles(char *filename); // Function declaration for renaming decrypted files
void deleteDecryptedFiles(char *filename); // Function declaration for deleting decrypted files

```
Pertama-tama, kode memuat beberapa pustaka standar yang diperlukan untuk operasi sistem, manipulasi string, manajemen file, dan sebagainya. Selanjutnya, makro konstanta digunakan untuk menentukan path file, URL file, dan ukuran maksimum untuk nama file dan entri log. Setelah itu, fungsi-fungsi deklarasi disediakan untuk mendefinisikan perilaku fungsi-fungsi yang akan digunakan dalam program. Kemudian, variabel global mode dideklarasikan untuk menentukan mode operasi program, dengan nilai 0 sebagai default, 1 untuk operasi backup, dan 2 untuk operasi restore. Ada juga sebuah fungsi yang melakukan enkripsi ROT19 pada karakter yang diberikan, yang nantinya akan digunakan untuk mendekripsi nama file. Fungsi main adalah titik masuk utama program yang melakukan demonisasi, mengatur penangan sinyal, dan menentukan mode operasi program berdasarkan argumen yang diberikan. Ada juga fungsi untuk mendownload dan mengekstrak file, serta fungsi-fungsi untuk mengelola file dalam direktori, seperti mendekripsi nama file, membuat backup file, dan mengembalikan file dari backup. Terakhir, ada sebuah fungsi untuk mencatat tindakan yang dilakukan pada file ke dalam log, yang mencatat nama file, tindakan yang diambil, dan timestamp.

```
// Variabel global
int mode = 0; // 0: default, 1: backup, 2: restore

// Function to perform ROT19 encryption
char rot19(char c) {
    if (isalpha(c)) {
        char base = islower(c) ? 'a' : 'A';
        return (c - base + 7) % 26 + base;
    }
    return c;
}

```
Variabel global mode digunakan untuk menentukan mode operasi program secara keseluruhan, dengan nilai 0 sebagai mode default, 1 sebagai mode backup, dan 2 sebagai mode restore. Ini memungkinkan program untuk beroperasi sesuai dengan tujuan yang diinginkan, seperti membuat cadangan file atau mengembalikan file dari cadangan.

Fungsi rot19 adalah fungsi enkripsi ROT19 yang mengambil satu karakter sebagai input dan mengembalikan karakter yang telah dienkripsi. Saat diberikan karakter alfabet (huruf), fungsi ini akan mengenkripsi karakter tersebut sesuai dengan aturan ROT19, yaitu dengan menggeser karakter sejauh 7 posisi ke kanan dalam alfabet. Fungsi ini memastikan bahwa karakter enkripsi tetap berada dalam rentang alfabet yang benar, baik huruf besar maupun huruf kecil. Jika karakter yang diberikan bukan huruf, fungsi akan mengembalikan karakter tersebut tanpa melakukan enkripsi.

```
// Function to decrypt a file name using ROT19
void decryptFileName(char *filename) {
    char decryptedFilename[MAX_FILENAME_LEN];
    int i = 0;
    while (filename[i] != '\0') {
        decryptedFilename[i] = rot19(filename[i]);
        i++;
    }
    decryptedFilename[i] = '\0';

    // Rename file using the decrypted filename
    if (rename(filename, decryptedFilename) == 0) {
        logAction(filename, "Decrypted");
    } else {
        perror("Error renaming file");
    }
}
```
Fungsi decryptFileName bertanggung jawab untuk mendekripsi nama file menggunakan algoritma ROT19 dan kemudian mengganti nama file dengan nama yang sudah didekripsi. Fungsi ini menerima parameter filename, yang merupakan string yang berisi nama file yang akan dideskripsi. Dalam fungsi, sebuah array karakter decryptedFilename dideklarasikan dengan ukuran MAX_FILENAME_LEN untuk menyimpan nama file yang sudah didekripsi. Selanjutnya, sebuah variabel i digunakan sebagai indeks untuk mengakses karakter dalam filename.

Proses dekripsi dilakukan dengan iterasi melalui setiap karakter dalam filename. Setiap karakter diambil dari filename, dan fungsi rot19 dipanggil untuk mengenkripsi karakter tersebut menggunakan algoritma ROT19. Hasil enkripsi kemudian disimpan dalam array decryptedFilename. Iterasi dilakukan sampai karakter nul (\0) yang menandakan akhir dari string filename.

Setelah proses dekripsi selesai, sebuah karakter nul (\0) ditambahkan ke akhir array decryptedFilename untuk menandakan akhir dari string. Selanjutnya, fungsi rename dipanggil untuk mengganti nama file yang asli (filename) dengan nama yang sudah didekripsi (decryptedFilename). Jika proses penggantian nama berhasil, fungsi logAction dipanggil untuk mencatat tindakan dekripsi yang berhasil ke dalam log. Namun, jika terjadi kesalahan dalam proses penggantian nama, fungsi perror akan digunakan untuk mencetak pesan kesalahan yang sesuai.
```
// Function to rename decrypted files based on certain criteria
void renameDecryptedFiles(char *filename) {
    if (strstr(filename, "r3N4mE") != NULL) { // Check if the filename contains "r3N4mE"
        char *extension = strrchr(filename, '.'); // Find file extension
        if (extension == NULL) {
            // No extension, rename to "renamed.file"
            if (rename(filename, "renamed.file") == 0) {
                logAction(filename, "Renamed to renamed.file");
            } else {
                perror("Error renaming file");
            }
        } else {
            // Process based on file extension
            if (strcmp(extension, ".ts") == 0) {
                if (rename(filename, "helper.ts") == 0) {
                    logAction(filename, "Renamed to helper.ts");
                } else {
                    perror("Error renaming file");
                }
            } else if (strcmp(extension, ".py") == 0) {
                if (rename(filename, "calculator.py") == 0) {
                    logAction(filename, "Renamed to calculator.py");
                } else {
                    perror("Error renaming file");
                }
            } else if (strcmp(extension, ".go") == 0) {
                if (rename(filename, "server.go") == 0) {
                    logAction(filename, "Renamed to server.go");
                } else {
                    perror("Error renaming file");
                }
            } else {
                if (rename(filename, "renamed.file") == 0) {
                    logAction(filename, "Renamed to renamed.file");
                } else {
                    perror("Error renaming file");
                }
            }
        }
    }
}
```
Fungsi renameDecryptedFiles bertujuan untuk menamai ulang file yang sudah didekripsi berdasarkan kriteria tertentu. Pertama, fungsi memeriksa apakah nama file mengandung string "r3N4mE" dengan menggunakan fungsi strstr. Jika nama file memenuhi kriteria tersebut, fungsi akan melanjutkan proses penamaan ulang.

Selanjutnya, fungsi mencari ekstensi file dengan menggunakan fungsi strrchr. Jika file tidak memiliki ekstensi, fungsi akan menamai ulang file tersebut menjadi "renamed.file". Jika file memiliki ekstensi, fungsi akan memproses penamaan ulang berdasarkan ekstensi file tersebut.

Pemrosesan penamaan ulang dilakukan dengan membandingkan ekstensi file dengan beberapa opsi yang telah ditentukan. Jika ekstensi file cocok dengan salah satu opsi yang ditentukan (misalnya, ".ts", ".py", atau ".go"), fungsi akan menamai ulang file tersebut sesuai dengan opsi yang cocok. Jika tidak ada kecocokan dengan opsi yang ditentukan, file akan dinamai ulang menjadi "renamed.file".

Setiap kali penamaan ulang berhasil dilakukan, fungsi logAction dipanggil untuk mencatat tindakan penamaan ulang yang berhasil ke dalam log. Namun, jika terjadi kesalahan dalam proses penamaan ulang, fungsi perror akan digunakan untuk mencetak pesan kesalahan yang sesuai.

```
// Function to delete decrypted files based on certain criteria
void deleteDecryptedFiles(char *filename) {
    if (strstr(filename, "d3Let3") != NULL) { // Check if the filename contains "d3Let3"
        if (remove(filename) == 0) {
            logAction(filename, "Deleted successfully");
        } else {
            perror("Error deleting file");
        }
    }
}
```
Fungsi deleteDecryptedFiles bertujuan untuk menghapus file yang sudah didekripsi berdasarkan kriteria tertentu. Pertama, fungsi memeriksa apakah nama file mengandung string "d3Let3" dengan menggunakan fungsi strstr. Jika nama file memenuhi kriteria tersebut, fungsi akan melanjutkan proses penghapusan.

Selanjutnya, jika nama file memenuhi kriteria, fungsi akan menggunakan fungsi remove untuk menghapus file tersebut. Jika penghapusan berhasil dilakukan, fungsi logAction dipanggil untuk mencatat bahwa file tersebut berhasil dihapus dalam log.

Namun, jika terjadi kesalahan dalam proses penghapusan file, fungsi perror akan digunakan untuk mencetak pesan kesalahan yang sesuai. Pesan kesalahan tersebut dapat membantu dalam menemukan dan memperbaiki masalah yang mungkin terjadi saat menghapus file.
```
// Function to manage files in the library directory
void manageFiles() {
    // Change the working directory to the "library" directory
    if (chdir("library") != 0) {
        perror("Error changing directory to library");
        return;
    }

    // Implement the function to decrypt and process regular files
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    // Iterate through files in the "library" directory
    while ((entry = readdir(dir)) != NULL) {
        char filename[MAX_FILENAME_LEN];
        snprintf(filename, sizeof(filename), "%s", entry->d_name);

        // Skip "." and ".." entries
        if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0)
            continue;

        // Skip files with number 1 to 6 as the first character in their filenames
        if (isdigit(filename[0]) && filename[0] >= '1' && filename[0] <= '6')
            continue;

        // Use lstat() to get information about the file
        if (lstat(filename, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            // Decrypt filename
            decryptFileName(filename);
            
            logAction(filename, "is being processed");
            // Rename and delete decrypted files if necessary
            renameDecryptedFiles(filename);
            deleteDecryptedFiles(filename);
        }
    }

    closedir(dir);

    // Change back to the main directory after processing files in "library"
    if (chdir("..") != 0) {
        perror("Error changing directory back to main directory");
    }
}
```

Fungsi manageFiles bertanggung jawab untuk mengelola file-file dalam direktori "library". Pertama-tama, fungsi mengubah direktori kerja ke direktori "library" menggunakan fungsi chdir. Jika perubahan direktori gagal, fungsi akan mencetak pesan kesalahan menggunakan perror dan kemudian keluar dari fungsi.

Selanjutnya, fungsi membuka direktori "library" menggunakan opendir. Jika pembukaan direktori gagal, fungsi akan mencetak pesan kesalahan dan keluar dari fungsi.

Setelah berhasil membuka direktori, fungsi akan melakukan iterasi melalui setiap entri (file atau subdirektori) dalam direktori "library" menggunakan readdir. Untuk setiap entri, fungsi akan memeriksa apakah nama file adalah "." atau ".." dan melewatkannya jika iya, karena entri tersebut adalah entri direktori yang spesial dan tidak relevan.

Selanjutnya, fungsi akan menggunakan lstat untuk mendapatkan informasi tentang file. Jika file adalah file regular, fungsi akan mendekripsi nama file tersebut menggunakan decryptFileName, mencatat bahwa file sedang diproses dalam log menggunakan logAction, serta memanggil fungsi renameDecryptedFiles dan deleteDecryptedFiles untuk menangani penamaan ulang dan penghapusan file yang sudah didekripsi, jika diperlukan.

Setelah selesai mengelola semua file dalam direktori "library", fungsi akan menutup direktori menggunakan closedir. Kemudian, fungsi akan mengembalikan direktori kerja ke direktori utama setelah selesai memproses file dalam "library". Jika perubahan direktori kembali ke direktori utama gagal, fungsi akan mencetak pesan kesalahan menggunakan perror.

```
// Function to backup files from the library directory
void backupFiles() {
    // Change the working directory to the "library" directory
    if (chdir("library") != 0) {
        perror("Error changing directory to library");
        return;
    }

    // Implement the function to backup files
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char filename[MAX_FILENAME_LEN];
        snprintf(filename, sizeof(filename), "%s", entry->d_name);

        // Use lstat() to get information about the file
        if (lstat(filename, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            decryptFileName(filename); // Decrypt filename

            if (strstr(filename, "m0V3") != NULL) { // Check if the filename contains "m0V3"
                char backupPath[MAX_FILENAME_LEN + sizeof(BACKUP_DIR) + 2]; // Increased buffer size
                snprintf(backupPath, sizeof(backupPath), "%s/%s", BACKUP_DIR, filename);
                rename(filename, backupPath);
                logAction(filename, "Successfully moved to backup.");
            }
        }
    }

    closedir(dir);

    // Change back to the main directory after processing files in "library"
    if (chdir("..") != 0) {
        perror("Error changing directory back to main directory");
    }
}
```
Fungsi backupFiles bertujuan untuk mencadangkan file dari direktori "library". Pertama-tama, fungsi mengubah direktori kerja ke direktori "library" menggunakan fungsi chdir. Jika perubahan direktori gagal, fungsi akan mencetak pesan kesalahan menggunakan perror dan kemudian keluar dari fungsi.

Selanjutnya, fungsi membuka direktori "library" menggunakan opendir. Jika pembukaan direktori gagal, fungsi akan mencetak pesan kesalahan dan keluar dari fungsi.

Setelah berhasil membuka direktori, fungsi akan melakukan iterasi melalui setiap entri (file atau subdirektori) dalam direktori "library" menggunakan readdir. Untuk setiap entri, fungsi akan memeriksa apakah itu adalah file regular menggunakan lstat. Jika iya, fungsi akan mendekripsi nama file tersebut menggunakan decryptFileName.

Kemudian, fungsi akan memeriksa apakah nama file mengandung string "m0V3" menggunakan strstr. Jika iya, fungsi akan menyiapkan jalur cadangan untuk file tersebut dengan menggabungkan nama file dengan direktori cadangan menggunakan snprintf. Setelah itu, file akan dipindahkan ke direktori cadangan dengan menggunakan rename.

Setelah selesai mencadangkan semua file yang memenuhi kriteria, fungsi akan menutup direktori menggunakan closedir. Kemudian, fungsi akan mengembalikan direktori kerja ke direktori utama setelah selesai memproses file dalam "library". Jika perubahan direktori kembali ke direktori utama gagal, fungsi akan mencetak pesan kesalahan menggunakan perror.

```
// Function to restore files from the backup directory
void restoreFiles() {
    // Change the working directory to the backup directory
    if (chdir(BACKUP_DIR) != 0) {
        perror("Error changing directory to backup directory");
        return;
    }

    // Implement the function to restore files
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char filename[MAX_FILENAME_LEN];
        snprintf(filename, sizeof(filename), "%s", entry->d_name);

        // Use lstat() to get information about the file
        if (lstat(filename, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            decryptFileName(filename); // Decrypt filename

            if (strstr(filename, "m0V3") != NULL) { // Check if the filename contains "m0V3"
                char restorePath[MAX_FILENAME_LEN + 3]; // Increased buffer size
                snprintf(restorePath, sizeof(restorePath), "../%s", filename);
                rename(entry->d_name, restorePath);
                logAction(filename, "Successfully restored from backup.");
            }
        }
    }

    closedir(dir);

    // Change back to the main directory after processing files in "backup" directory
    if (chdir("..") != 0) {
        perror("Error changing directory back to main directory");
    }
}
```
Fungsi restoreFiles bertanggung jawab untuk mengembalikan file dari direktori cadangan ke lokasi asalnya. Pertama-tama, fungsi mengubah direktori kerja ke direktori cadangan menggunakan fungsi chdir. Jika perubahan direktori gagal, fungsi akan mencetak pesan kesalahan menggunakan perror dan kemudian keluar dari fungsi.

Selanjutnya, fungsi membuka direktori cadangan menggunakan opendir. Jika pembukaan direktori gagal, fungsi akan mencetak pesan kesalahan dan keluar dari fungsi.

Setelah berhasil membuka direktori, fungsi akan melakukan iterasi melalui setiap entri (file atau subdirektori) dalam direktori cadangan menggunakan readdir. Untuk setiap entri, fungsi akan memeriksa apakah itu adalah file regular menggunakan lstat. Jika iya, fungsi akan mendekripsi nama file tersebut menggunakan decryptFileName.

Kemudian, fungsi akan memeriksa apakah nama file mengandung string "m0V3" menggunakan strstr. Jika iya, fungsi akan menyiapkan jalur pemulihan untuk file tersebut dengan menggabungkan nama file dengan jalur direktori asal menggunakan snprintf. Setelah itu, file akan dipulihkan ke lokasi asalnya dengan menggunakan rename.

Setelah selesai memulihkan semua file yang memenuhi kriteria, fungsi akan menutup direktori menggunakan closedir. Kemudian, fungsi akan mengembalikan direktori kerja ke direktori utama setelah selesai memproses file dalam direktori cadangan. Jika perubahan direktori kembali ke direktori utama gagal, fungsi akan mencetak pesan kesalahan menggunakan perror.

```
// Signal handler function
void signalHandler(int signum) {
    if (signum == SIGRTMIN) {
        mode = 0; // Set mode to default
    } else if (signum == SIGUSR1) {
        mode = 1; // Set mode to backup
    } else if (signum == SIGUSR2) {
        mode = 2; // Set mode to restore
    }
}
```

Fungsi signalHandler adalah fungsi penangan sinyal yang bertujuan untuk menangani sinyal yang diterima oleh proses. Fungsi ini akan dipanggil ketika proses menerima sinyal tertentu yang telah ditentukan sebelumnya.

Pertama, fungsi ini menerima parameter signum, yang merupakan nomor sinyal yang diterima. Fungsi kemudian memeriksa nilai signum untuk menentukan tindakan yang harus diambil sesuai dengan jenis sinyal yang diterima.

* Jika signum sama dengan SIGRTMIN, ini menandakan bahwa proses menerima sinyal real-time minimum. Dalam konteks aplikasi ini, sinyal ini digunakan untuk mengatur mode ke mode default, yang ditandai dengan mode = 0.
* Jika signum sama dengan SIGUSR1, ini menandakan bahwa proses menerima sinyal pengguna 1. Dalam konteks aplikasi ini, sinyal ini digunakan untuk mengatur mode ke mode cadangan, yang ditandai dengan mode = 1.
* Jika signum sama dengan SIGUSR2, ini menandakan bahwa proses menerima sinyal pengguna 2. Dalam konteks aplikasi ini, sinyal ini digunakan untuk mengatur mode ke mode pemulihan, yang ditandai dengan mode = 2.

```
// Function to log actions with filename and action description
void logAction(const char *filename, const char *action) {
    FILE *logFile = fopen(LOG_FILE, "a");
    if (logFile != NULL) {
        time_t rawtime;
        struct tm *timeinfo;
        char timestamp[20];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(timestamp, sizeof(timestamp), "%H:%M:%S", timeinfo);
        char username[64]; // Temporary username as "paul"
        fprintf(logFile, "[paul][%s] - %s - %s\n", timestamp, filename, action);
        fclose(logFile);
    }
}
```
Fungsi logAction bertujuan untuk mencatat tindakan tertentu yang terjadi pada file dalam sebuah log. Fungsi ini menerima dua parameter: filename, yang merupakan nama file yang terlibat dalam tindakan, dan action, yang merupakan deskripsi tindakan yang dilakukan pada file tersebut.

Pertama, fungsi membuka file log untuk ditambahkan ("a") menggunakan fungsi fopen. Jika operasi pembukaan file berhasil, fungsi akan melanjutkan untuk mencatat tindakan dalam file log. Namun, jika pembukaan file gagal, fungsi akan menghentikan proses pencatatan tindakan dan keluar.

Selanjutnya, fungsi mengambil waktu saat ini menggunakan fungsi time, dan kemudian menggunakan fungsi localtime untuk mengonversi waktu tersebut ke dalam format lokal. Informasi waktu ini digunakan untuk membuat timestamp dalam format "HH:MM:SS" menggunakan fungsi strftime, yang kemudian disimpan dalam array timestamp.

Selanjutnya, fungsi mencetak informasi tindakan ke dalam file log menggunakan fungsi fprintf. Informasi ini terdiri dari timestamp, nama pengguna (dalam kasus ini ditetapkan sebagai "paul"), nama file, dan deskripsi tindakan. Setelah pencetakan selesai, file log ditutup menggunakan fclose.
```
// Function to download and extract a file
void download_and_extract_file() {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execlp("wget", "wget", FILE_URL, "-O", FILE_NAME, "-q", NULL);
        perror("exec wget");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // Download successful
            pid_t pid_unzip = fork();
            if (pid_unzip == 0) {
                execlp("unzip", "unzip", FILE_NAME, NULL);
                perror("exec unzip");
                exit(EXIT_FAILURE);
            } else if (pid_unzip > 0) {
                int status_unzip;
                waitpid(pid_unzip, &status_unzip, 0);
                if (WIFEXITED(status_unzip) && WEXITSTATUS(status_unzip) == 0) {
                    // Unzip successful
                } else {
                    printf("Unzip failed.\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                perror("fork unzip");
                exit(EXIT_FAILURE);
            }
        } else {
            printf("Download failed.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        perror("fork wget");
        exit(EXIT_FAILURE);
    }
}
```

Fungsi download_and_extract_file bertujuan untuk mengunduh dan mengekstrak sebuah file dari URL yang telah ditentukan sebelumnya. Fungsi ini menggunakan mekanisme proses fork untuk menjalankan perintah wget dan unzip secara asinkron.

Pertama, fungsi membuat proses anak (pid = fork()) untuk menjalankan perintah wget yang bertanggung jawab untuk mengunduh file dari URL yang telah ditentukan. Dalam proses anak, fungsi menggunakan execlp untuk mengeksekusi perintah wget, dengan argumen berupa URL file yang akan diunduh (FILE_URL) dan nama file tujuan penyimpanan (FILE_NAME). Opsi -q digunakan untuk menonaktifkan output dari wget. Jika pengunduhan berhasil, maka proses anak akan mengeksekusi perintah unzip.

Selanjutnya, dalam proses induk, fungsi menunggu proses anak selesai menggunakan waitpid. Jika pengunduhan berhasil (ditandai dengan status keluaran 0), maka fungsi membuat proses anak baru (pid_unzip = fork()) untuk menjalankan perintah unzip. Proses anak yang baru kemudian mengeksekusi perintah unzip untuk mengekstrak file yang telah diunduh (FILE_NAME).

Setelah proses unzip selesai, proses induk menunggu proses anak selesai menggunakan waitpid. Jika ekstraksi berhasil (ditandai dengan status keluaran 0), maka proses berakhir. Jika ekstraksi gagal, maka proses akan keluar dengan status keluaran EXIT_FAILURE.

Jika proses fork gagal, fungsi akan mencetak pesan kesalahan menggunakan perror dan keluar dengan status keluaran EXIT_FAILURE.

```
int main(int argc, char *argv[]) {
    // Create daemon
    pid_t pid, sid;

    pid = fork(); // Save PID of child process

    /* Exit if fork fails
     * (pid < 0) */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Exit if fork succeeds
     * (pid is PID of child process) */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("./")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Set signal handler
    signal(SIGRTMIN, signalHandler);
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);

    // Create directories if they don't exist
    mkdir("library", 0777);
    mkdir(BACKUP_DIR, 0777);

    // Change mode if argument provided
    if (argc == 3 && strcmp(argv[1], "-m") == 0) {
        if (strcmp(argv[2], "backup") == 0) {
            mode = 1;
        } else if (strcmp(argv[2], "restore") == 0) {
            mode = 2;
        }
    }

    switch (mode) {
        case 0:
            download_and_extract_file();
            manageFiles();
            break;
        case 1:
            backupFiles();
            break;
        case 2:
            restoreFiles();
            break;
    }

    sleep(1);

    exit(EXIT_SUCCESS);
}

```

Fungsi main dalam program ini bertanggung jawab untuk mengatur proses utama dari daemon yang dibuat. Pertama-tama, daemon dibuat dengan melakukan fork. Proses induk akan keluar jika fork berhasil, sedangkan proses anak akan melanjutkan eksekusi.

Setelah fork, daemon menetapkan umask-nya, membuat sesi baru, dan mengubah direktori kerjanya ke direktori saat ini. Kemudian, input/output standar ditutup untuk memisahkan proses dari terminal. Signal handler diatur untuk menangani sinyal SIGRTMIN, SIGUSR1, dan SIGUSR2.

Selanjutnya, program membuat direktori "library" dan "backup" jika belum ada. Jika ada argumen saat menjalankan program dan argumen tersebut adalah "-m" diikuti dengan "backup" atau "restore", mode daemon akan diatur sesuai.

Berdasarkan mode yang telah ditetapkan, daemon akan menjalankan salah satu dari tiga fungsi utama: download_and_extract_file untuk mengunduh dan mengekstrak file, manageFiles untuk mengelola file di direktori "library", backupFiles untuk mencadangkan file, atau restoreFiles untuk memulihkan file dari cadangan.

Setelah menjalankan tugas sesuai mode, daemon akan beristirahat selama satu detik menggunakan fungsi sleep sebelum menutup proses dengan status keluaran EXIT_SUCCESS.

**Sample Output**

Untuk menjalankan program management.c pertama saya mengcompile program dengan command dengan

gcc management.c -o management

dan menjalankannya dengan command

./management

Kemudian program akan berjalan sebagai daemon.

![Screenshot from 2024-04-23 21-56-34](https://github.com/Ax3lrod/Sisop-2-2024-MH-IT17/assets/150204139/cdc5b874-d738-4799-81d9-59ffd2e16c27)

Program akan menginstall file library.zip dan meletakkan isinya ke folder library yang sudah dibuat. Kemudian program mendekripsi nama semua file yang ada
di folder library dan merubah namanya ke nama yang sudsh di dekripsi.

![Screenshot from 2024-04-23 21-55-31](https://github.com/Ax3lrod/Sisop-2-2024-MH-IT17/assets/150204139/937371ac-aa83-4375-b9e4-22dc0fa87c42)

Setelah itu program akan memproses file (memindahkan, menghapus, merename) semua file di dalam folder library sesuai dengan ketentuan yang ada di soal. Keberhasilan 
memproses file ini akan dicatat di history.log.

![Screenshot from 2024-04-23 21-56-04](https://github.com/Ax3lrod/Sisop-2-2024-MH-IT17/assets/150204139/f2bdbc3e-48a9-418a-8af1-485dc489dd15)

Untuk saat ini code saya masih belum bisa berjalan hingga mendekripsi nama filenya tetapi belum berhasil memproses filenya.

## NOMOR 3
Pak Heze adalah seorang admin yang baik. Beliau ingin membuat sebuah program admin yang dapat memantau para pengguna sistemnya. Bantulah Pak Heze untuk membuat program  tersebut!
- Nama program tersebut dengan nama admin.c
- Program tersebut memiliki fitur menampilkan seluruh proses yang dilakukan oleh seorang user dengan menggunakan command:
./admin <user>
- Program dapat memantau proses apa saja yang dilakukan oleh user. Fitur ini membuat program berjalan secara daemon dan berjalan terus menerus. Untuk menjalankan fitur ini menggunakan command: 
./admin -m <user>
- Dan untuk mematikan fitur tersebut menggunakan: 
./admin -s <user>
- Program akan mencatat seluruh proses yang dijalankan oleh user di file <user>.log dengan format:
[dd:mm:yyyy]-[hh:mm:ss]_pid-process_nama-process_GAGAL/JALAN
- Program dapat menggagalkan proses yang dijalankan user setiap detik secara terus menerus dengan menjalankan: 
./admin -c user
- sehingga user tidak bisa menjalankan proses yang dia inginkan dengan baik. Fitur ini dapat dimatikan dengan command:
./admin -a user
- Ketika proses yang dijalankan user digagalkan, program juga akan melog dan menset log tersebut sebagai GAGAL. Dan jika di log menggunakan fitur poin c, log akan ditulis dengan JALAN
## Solusi
Include Libraries: Kode dimulai dengan mengimpor beberapa pustaka yang diperlukan untuk program ini, seperti stdio.h, stdlib.h, unistd.h, dan lainnya. Ini menyediakan fungsi-fungsi yang diperlukan untuk melakukan operasi input/output, alokasi memori, operasi sistem, dan lain-lain.
Deklarasi Fungsi: Beberapa fungsi yang akan digunakan dalam program dideklarasikan. Ini termasuk fungsi-fungsi untuk memantau proses pengguna, memulai mode daemon, menghentikan mode daemon, memblokir proses pengguna, membuka blokir proses pengguna, mencatat log proses, dan melihat log proses.
````
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define MAX_COMMAND_LENGTH 100

void monitor_user_processes(char *user);
void start_daemon_mode(char *user);
void stop_daemon_mode(char *user);
void block_user_processes(char *user);
void unblock_user_processes(char *user);
void log_process(char *user, int pid, char *process_name, int status);
void view_log(char *user);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <option> <user>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *option = argv[1];
    char *user = argv[2];

    if (strcmp(option, "-m") == 0) {
        start_daemon_mode(user);
    } else if (strcmp(option, "-s") == 0) {
        stop_daemon_mode(user);
    } else if (strcmp(option, "-c") == 0) {
        block_user_processes(user);
    } else if (strcmp(option, "-a") == 0) {
        unblock_user_processes(user);
    } else if (strcmp(option, "-l") == 0) {
        view_log(user);
    } else {
        printf("Invalid option!\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
````

Monitor Proses Pengguna (monitor_user_processes): Fungsi ini digunakan untuk memantau proses yang dijalankan oleh pengguna tertentu. Fungsi ini menggunakan perintah ps untuk mendapatkan daftar proses pengguna dan mencatat hasilnya dalam file log.
````
void monitor_user_processes(char *user) {
    // Implementasi fitur untuk memantau proses pengguna
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error forking process");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        // Child process
        int fd = open("/dev/null", O_WRONLY); // Mengarahkan output ke /dev/null untuk menghindari output pada terminal
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);
        execlp("ps", "ps", "-u", user, NULL);
        perror("Error executing ps");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // Proses selesai dengan normal
            // Tidak ada yang gagal
            log_process(user, getpid(), "monitor_user_processes", 1);
        } else {
            // Proses gagal
            log_process(user, getpid(), "monitor_user_processes", 0);
        }
    }
}
````
Start Daemon Mode (start_daemon_mode): Fungsi ini seharusnya menjalankan mode daemon untuk memantau proses pengguna secara berkelanjutan. Namun, pada implementasi ini, fungsi hanya menampilkan pesan bahwa mode daemon dimulai.
````
void start_daemon_mode(char *user) {
    // Mode daemon membutuhkan implementasi yang lebih kompleks.
    // Di sini kita hanya menampilkan pesan bahwa mode daemon dimulai.
    printf("Daemon mode started for user: %s\n", user);
}

````
Stop Daemon Mode (stop_daemon_mode): Fungsi ini seharusnya menghentikan mode daemon yang sedang berjalan. Namun, pada implementasi ini, fungsi hanya menampilkan pesan bahwa mode daemon dihentikan.
````
void stop_daemon_mode(char *user) {
    // Mode daemon membutuhkan implementasi yang lebih kompleks.
    // Di sini kita hanya menampilkan pesan bahwa mode daemon dihentikan.
    printf("Daemon mode stopped for user: %s\n", user);
}
````
![Screenshot 2024-04-25 171647](https://github.com/Ax3lrod/Sisop-2-2024-MH-IT17/assets/151889425/6d64b816-533a-4374-9a34-ba3879c6ded6)

Block User Processes (block_user_processes): Fungsi ini seharusnya memblokir proses yang dijalankan oleh pengguna tertentu. Namun, pada implementasi ini, fungsi hanya menampilkan pesan bahwa proses pengguna diblokir.
````
void block_user_processes(char *user) {
    // Implementasi fitur untuk memblokir proses pengguna.
    // Di sini kita hanya menampilkan pesan bahwa proses pengguna diblokir.
    printf("User processes blocked for user: %s\n", user);
}
````
![Screenshot 2024-04-25 171539](https://github.com/Ax3lrod/Sisop-2-2024-MH-IT17/assets/151889425/bc8d5393-e30b-4810-9c42-cd29d34d2ac5)

Unblock User Processes (unblock_user_processes): Fungsi ini seharusnya membuka blokir proses yang dijalankan oleh pengguna tertentu. Namun, pada implementasi ini, fungsi hanya menampilkan pesan bahwa blokir proses pengguna dibuka.
````
void unblock_user_processes(char *user) {
    // Implementasi fitur untuk membuka blokir proses pengguna.
    // Di sini kita hanya menampilkan pesan bahwa blokir proses pengguna dibuka.
    printf("User processes unblocked for user: %s\n", user);
}
````
![Screenshot 2024-04-25 171608](https://github.com/Ax3lrod/Sisop-2-2024-MH-IT17/assets/151889425/e40e5132-0d62-4857-926e-750622300121)

Log Process (log_process): Fungsi ini digunakan untuk mencatat informasi proses ke dalam file log. Informasi yang dicatat meliputi waktu, PID proses, nama proses, dan status keberhasilan atau kegagalan proses.
````
void log_process(char *user, int pid, char *process_name, int status) {
    // Implementasi fungsi untuk mencatat proses pengguna ke dalam file log
    time_t now;
    struct tm *tm_info;
    time(&now);
    tm_info = localtime(&now);

    char datetime[20];
    strftime(datetime, sizeof(datetime), "%d:%m:%Y-%H:%M:%S", tm_info);

    char *process_status = (status == 0) ? "GAGAL" : "JALAN";

    char filename[50];
    sprintf(filename, "%s.log", user);

    FILE *fp;
    fp = fopen(filename, "a");
    if (fp == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "[%s]-%d-%s-%s\n", datetime, pid, process_name, process_status);

    fclose(fp);
}
````
View Log (view_log): Fungsi ini digunakan untuk menampilkan isi file log proses untuk pengguna tertentu.
````
void view_log(char *user) {
    // Implementasi fungsi untuk melihat log proses
    char filename[50];
    sprintf(filename, "%s.log", user);

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    printf("Log process for user %s:\n", user);
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp);
}
````
### ERROR PADA NO 3
- Log Process gagal dibuat, Sehingga tidak dapat menampilkan log dari user.
![Screenshot 2024-04-25 172322](https://github.com/Ax3lrod/Sisop-2-2024-MH-IT17/assets/151889425/822afeca-44df-4662-8a11-46cb5d7888af)


## NOMOR 4
Salomo memiliki passion yang sangat dalam di bidang sistem operasi. Saat ini, dia ingin mengotomasi kegiatan-kegiatan yang ia lakukan agar dapat bekerja secara efisien. Bantulah Salomo untuk membuat program yang dapat mengotomasi kegiatan dia!
- Salomo ingin dapat membuka berbagai macam aplikasi dengan banyak jendela aplikasi dalam satu command. Namai file program tersebut **setup.c**.
- Program dapat membuka berbagai macam aplikasi dan banyak jendela aplikasi sekaligus (bisa membuka 1 atau lebih aplikasi dengan 1 atau lebih window (kecuali aplikasi yang tidak bisa dibuka dengan banyak window seperti discord)) dengan menjalankan: `./setup -o <app1> <num1> <app2> <num2>.....<appN> <numN>`. Contoh penggunaannya adalah sebagai berikut:**./setup -o firefox 2 wireshark 2**. Program akan membuka 2 jendela aplikasi firefox dan 2 jendela aplikasi wireshark.
- Program juga dapat membuka aplikasi dengan menggunakan file konfigurasi dengan menggunakan `./setup -f file.conf`. Format file konfigurasi dibebaskan, namun pastikan dapat menjalankan fitur dari poin 2.
Contoh isi file.conf:**Firefox 2 Wireshark 3**. Ketika menjalankan command contoh, program akan membuka 2 jendela aplikasi firefox dan 3 jendela aplikasi wireshark.
- Program dapat mematikan semua aplikasi yg dijalankan oleh program tersebut dengan `./setup -k`.
- Program juga dapat mematikan aplikasi yang dijalankan sesuai dengan file konfigurasi. Contohnya: `./setup -k file.conf`. Command ini hanya mematikan aplikasi yang dijalankan dengan `./setup -f file.conf`.

## Solusi
### Definisi Konstanta
```
#define PID_MAX 20
#define ARG_SIZE 50
```
- Konstanta `PID_MAX` dibatasi menjadi 20 proses yang dapat dijalankan program, sedangkan `ARG_SIZE` dibatasi menjadi 50 argumen perintah.
### Deklarasi Variabel Global beserta Fungsi
```
pid_t running[PID_MAX];
int pidcount = 0;

void add_global(pid_t pid);
void kill_procs(int argc, char *argv[]);
void open(int argc, char *argv[]);
void open_file(int argc, char *argv[]);
```
- Array `running` digunakan untuk menyimpan ID akumulasi proses yang dijalankan program, dapat dilacak menggunakan `pidcount`.
### Implementasi Fungsi `add_global`
```
void add_global(pid_t pid) {
    if (pidcount < PID_MAX) {
        running[pidcount] = pid;
        pidcount++;
    }
}
```
- `add_global` berfungsi untuk menambahkan ID proses baru ke dalam array `running`. Jika akumulasi proses dalam array di bawah `PID_MAX`, maka ID proses akan disimpan dalam array dan `pidcount` akan ditingkatkan.
### Implementasi Fungsi `kill_procs`
```
void kill_procs(int argc, char *argv[]) {
    FILE *config = NULL;
    if (argc == 3) {
        config = fopen(argv[2], "r");
        if (!config) {
            printf("Error: Failed to open file");
            exit(1);
        }
    }

    char cmd[ARG_SIZE];
    int num;
    if (config) {
        while (fscanf(config, "%s %d", cmd, &num) != EOF) {
            for (int i = 0; i < num; i++) {
                pid_t pid = fork();
                if (pid < 0) {
                    printf("Error: Fork failed\n");
                    exit(1);
                }
                if (pid == 0) {
                    char *args[] = {"pkill", cmd, NULL};
                    execvp("pkill", args);
                    _exit(1);
                }
                int status;
                waitpid(pid, &status, 0);
            }
        }
        fclose(config);
    } else {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Error: Fork failed\n");
            exit(1);
        }
        if (pid == 0) {
            char *args[] = {"pkill", "firefox", NULL};
            execvp("pkill", args);
            _exit(1);
        }
        waitpid(pid, NULL, 0);

        pid = fork();
        if (pid < 0) {
            printf("Error: Fork failed\n");
            exit(1);
        }
        if (pid == 0) {
            char *args[] = {"pkill", "wireshark", NULL};
            execvp("pkill", args);
            _exit(1);
        }
        waitpid(pid, NULL, 0);
    }
}
```
- `kill_procs` bertujuan untuk mengeliminasi tab aplikasi yang dijalankan program. Jika jumlah argumennya 3, maka fungsi akan membuka file.conf yang diberikan dalam `argv[2]`. Setelah itu, fungsi membaca setiap baris nama aplikasi beserta jumlah tab yang harus dieksekusi. Fungsi akan menginisiasi _child process_ dengan `fork`, setiap _child process_ menjalankan perintah `pkill` dengan argumen _command_ yang didapatkan dari file.conf menggunakan `execvp`. Lain cerita apabila argumennya bukan 3, maka fungsi akan menginisiasi dua _child process_ yang akan menjalankan `pkill firefox` dan `pkill wireshark`.
### Implementasi Fungsi `open`
```
void open(int argc, char *argv[]) {
    for (int i = 2; i < argc; i += 2) {
        if (!isdigit(argv[i + 1][0])) {
            printf("Error: Invalid argument(s)");
            exit(1);
        }
    }

    for (int i = 2; i < argc; i += 2) {
        int num = atoi(argv[i + 1]);
        for (int j = 0; j < num; j++) {
            pid_t pid = fork();
            if (pid < 0) {
                printf("Error: Fork failed\n");
                exit(1);
            }
            if (pid == 0) {
                execlp(argv[i], argv[i], NULL);
                _exit(1);
            } else {
                add_global(pid);
            }
        }
    }
}
```
- Esensinya adalah mengeksekusi aplikasi beserta jumlah tabnya sesuai kebutuhan, ,enjadikan `argc` dan `argv` sebagai parameternya. Argumen setelah `argv[2]` wajib berupa pasangan nama aplikasi dan jumlah tab, lalu fungsi akan memvalidasi apakah argumen untuk kuantitas tab merupakan input digit atau tidak. Jika valid, maka fungsi akan memulai seluruh eksekusinya menggunakan `fork` sesuai dengan input yang kita masukkan. Jika tidak, maka fungsi akan memperingatkan anda "Error" Invalid argument(s)". Setiap _child process_ akan menjalankan aplikasi yang dikehendaki menggunakan `execlp`.
### Implementasi Fungsi `open_file`
```
void open_file(int argc, char *argv[]) {
    FILE *config = fopen(argv[2], "r");
    if (!config) {
        printf("Error: Failed to open file");
        exit(1);
    }

    char cmd[ARG_SIZE];
    int num;
    while (fscanf(config, "%s %d", cmd, &num) != EOF) {
        for (int i = 0; i < num; i++) {
            pid_t pid = fork();
            if (pid < 0) {
                printf("Error: Fork failed\n");
                exit(1);
            }
            if (pid == 0) {
                execlp(cmd, cmd, NULL);
                _exit(1);
            } else {
                add_global(pid);
            }
        }
    }
    fclose(config);
}
```
- Identik dengan fungsi `open`, namun ditujukan untuk file.conf yang diberikan dalam `argv[2]`. Jika file.conf berhasil dibuka, maka fungsi akan membaca setiap baris yang berisikan nama beserta kuantitas tabnya. Untuk setiap baris akan dieksekusi menggunakan `fork`, sementara untuk _child process_ menggunakan `execlp`.
### Implementasi Fungsi `main`
```
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [-o | -f file.conf | -k | -k file.conf]\n", argv[0]);
        return 1;
    }

    switch (argv[1][1]) {
        case 'o':
            open(argc, argv);
            break;
        case 'f':
            open_file(argc, argv);
            break;
        case 'k':
            kill_procs(argc, argv);
            break;
        default:
            printf("Invalid option\n");
            return 1;
    }

    return 0;
}
```
- Fungsi `main` dieksekusi pertama kali ketika program dijalankan. Bertujuan untuk memeriksa jumlah argumen yang diberikan dan mengeksekusi fungsi yang sesuai berdasarkan argumen pertama `argv[1]`. Jika argumen pertamanya `-o`, maka fungsi `open` dijalankan. Jika argumennya `-f`, maka fungsi `open_file` akan dipanggil. Sedangkan untuk argumen pertama `-k`, maka fungsi `kill_procs` akan dieksekusi. Ketiganya dipanggil dengan `argc` dan `argv` sebagai parameternya.
### Penggunaan _Command_ dalam Program
-`./setup -o <app1> <num1> <app2> <num2>...`
Untuk membuka aplikasi beserta jumlah tabnya.
-`./setup -f file.conf`
Untuk menjalankan aplikasi beserta jumlah tabnya yang berada di dalam file.conf.
-`./setup -k`
Untuk mengakhiri seluruh tab aplikasi yang dijalankan _command_.
-`./setup -k file.conf`
Untuk mengakhiri tab aplikasi yang hanya dijalankan file.conf.
## Output
![Ubuntu 64-bit - VMware Workstation 25_04_2024 09_10_25](https://github.com/Ax3lrod/Sisop-2-2024-MH-IT17/assets/151877527/6687faae-a42f-46a1-a743-50819b5d7438)



## REVISI

### Soal_2

Solusi untuk gagal memproses files saya temukan dengan cara memodifikasi dan menambahkan fungsi-fungsi berikut;

```
const char *get_extension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) return "";
    return dot + 1;
}

void renameDecryptedFiles_by_extension(const char *dir_path, const char *filename, const char *extension) {
    char new_name[512];
    if (strcmp(extension, "ts") == 0) {
        strcpy(new_name, "helper.ts");
    } else if (strcmp(extension, "py") == 0) {
        strcpy(new_name, "calculator.py");
    } else if (strcmp(extension, "go") == 0) {
        strcpy(new_name, "server.go");
    } else {
        strcpy(new_name, "renamed.file");
    }
    char old_path[512];
    strcpy(old_path, dir_path);
    strcat(old_path, "/");
    strcat(old_path, filename);
    char new_path[512];
    strcpy(new_path, dir_path);
    strcat(new_path, "/");
    strcat(new_path, new_name);
    if (rename(old_path, new_path) != 0) {
        perror("Rename failed");
    }
}

void renameDecryptedFiles(const char *dir_path, const char *code) {
    DIR *d;
    struct dirent *dir;

    d = opendir(dir_path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, code) != NULL) {
                const char *extension = get_extension(dir->d_name);
                renameDecryptedFiles_by_extension(dir_path, dir->d_name, extension);
            }
        }
        closedir(d);
    } else {
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }
}


void deletedecryptedfiles(const char *dir_path, const char *code) {
    DIR *d;
    struct dirent *dir;

    d = opendir(dir_path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, code) != NULL) {
                char file_path[512];
                strcpy(file_path, dir_path);
                strcat(file_path, "/");
                strcat(file_path, dir->d_name);
                if (remove(file_path) != 0) {
                    perror("Error deleting file");
                }
            }
        }
        closedir(d);
    } else {
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }
}

void manageFiles() {
    // Change the working directory to the "library" directory
    if (chdir("library") != 0) {
        perror("Error changing directory to library");
        return;
    }

    // Implement the function to decrypt and process regular files
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    // Iterate through files in the "library" directory
    while ((entry = readdir(dir)) != NULL) {
        char filename[MAX_FILENAME_LEN];
        snprintf(filename, sizeof(filename), "%s", entry->d_name);

        // Skip "." and ".." entries
        if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0)
            continue;

        // Skip files with number 1 to 6 as the first character in their filenames
        if (isdigit(filename[0]) && filename[0] >= '1' && filename[0] <= '6')
            continue;

        // Menggunakan lstat() untuk mendapatkan informasi tentang file
        if (lstat(filename, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            // Decrypt filename
            decryptFileName(filename);
            
            // Rename and delete decrypted files if necessary
            renameDecryptedFiles("/home/axelrod/sisop/modul2/praktikum/soal_2/library", "r3N4mE");
            deletedecryptedfiles("/home/axelrod/sisop/modul2/praktikum/soal_2/library", "d3Let3");
        }
    }

    closedir(dir);

    // Change back to the main directory after processing files in "library"
    if (chdir("..") != 0) {
        perror("Error changing directory back to main directory");
    }
}
```
Untuk sementara program masih belum bisa backup.
