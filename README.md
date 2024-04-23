# LAPRES SOAL SHIFT MODUL 2

## Anggota Kelompok

1. Aryasatya Alaauddin 5027231082 (Mengerjakan soal 1 dan 2)
2. Diandra Naufal Abror 5027231004 (Mengerjakan soal 4)
3. Muhamad Rizq Taufan 5027231021 (Mengerjakan soal 3)

## NOMOR 1

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
