#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <cctype>

using namespace std;

// User struct
struct User {
    string nomorInduk;
    string password;
    string nama;
    string role;
    string status;
};

// Struct Mata kuliah
struct MataKuliah {
	string kodeMataKuliah;
	string namaMataKuliah;
    string namaDosen;
	string nomorIndukDosen;
};

// Struct Transaksi
struct Transaksi {
    string nomorInduk;
    string kodeMataKuliah;
    int nilai = 0;
};

// Global variables
// user
const int MAX_USERS = 100;
User users[MAX_USERS];
int userCount = 5;
// mata kuliah
const int MAX_MATAKULIAH = 100;
MataKuliah mataKuliah[MAX_MATAKULIAH];
int mataKuliahCount = 3;
// transaksi
const int MAX_TRANSAKSI = 100;
Transaksi transaksi[MAX_TRANSAKSI];
int transaksiCount = 3;

User currentUser;
MataKuliah currentMataKuliah;
Transaksi currentTransaksi;

//test akun
void blueprintUserAndAdmin() {
    users[0].nomorInduk = "1462300001";
    users[0].password = "Monhero12";
    users[0].nama = "rio";
    users[0].role = "admin";
    users[0].status = "aktif";

    users[1].nomorInduk = "1462300002";
    users[1].password = "Monhero12";
    users[1].nama = "simbah";
    users[1].role = "dosen";
    users[1].status = "aktif";

    users[2].nomorInduk = "1462300003";
    users[2].password = "Monhero12";
    users[2].nama = "raka";
    users[2].role = "mahasiswa";
    users[2].status = "aktif";

    users[3].nomorInduk = "1462300004";
    users[3].password = "Monhero12";
    users[3].nama = "agil";
    users[3].role = "dosen";
    users[3].status = "aktif";

    users[4].nomorInduk = "1462300005";
    users[4].password = "Monhero12";
    users[4].nama = "ambatukam";
    users[4].role = "mahasiswa";
    users[4].status = "aktif";
}   
void blueprintMataKuliah() {
	mataKuliah[0].kodeMataKuliah = "MK001";
	mataKuliah[0].namaMataKuliah = "Pemrograman Dasar";
    mataKuliah[0].namaDosen = "Pak Simbah";
	mataKuliah[0].nomorIndukDosen = "1462300002";

	mataKuliah[1].kodeMataKuliah = "MK002";
	mataKuliah[1].namaMataKuliah = "Pemrograman Lanjut";
    mataKuliah[1].namaDosen = "Pak Simbah";
    mataKuliah[1].nomorIndukDosen = "1462300002";

	mataKuliah[2].kodeMataKuliah = "MK003";
	mataKuliah[2].namaMataKuliah = "Pemrograman Web";
    mataKuliah[2].namaDosen = "Pak Agil";
    mataKuliah[2].nomorIndukDosen = "1462300004";
}
void blueprintTransaksi() {
    transaksi[0].nomorInduk = "1462300003";
    transaksi[0].kodeMataKuliah = "MK001";
    transaksi[0].nilai = 0;

    transaksi[1].nomorInduk = "1462300003";
    transaksi[1].kodeMataKuliah = "MK002";
    transaksi[1].nilai = 0;

    transaksi[2].nomorInduk = "1462300003";
    transaksi[2].kodeMataKuliah = "MK003";
    transaksi[2].nilai = 0;
}

//Validasi
bool isUniqueNomorInduk(const string& nomorInduk) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].nomorInduk == nomorInduk) {
            return false;
        }
    }
    return true;
}
bool isUniqueKodeMataKuliah(const string& kodeMataKuliah) {
    for (int i = 0; i < mataKuliahCount; ++i) {
        if (mataKuliah[i].kodeMataKuliah == kodeMataKuliah) {
            return false;
        }
    }
    return true;
}
void hidePassword(string& password) {
    char ch;
    password = "";
    bool hasDigit = false;
    bool hasUppercase = false;

    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (password.length() > 0) {
                cout << "\b \b";
                password.pop_back();
            }
            hasDigit = false;
            hasUppercase = false;
        }
        else if (isalnum(ch)) {
            cout << '*';
            password.push_back(ch);

            if (isdigit(ch)) {
                hasDigit = true;
            }
            else if (isupper(ch)) {
                hasUppercase = true;
            }
        }

        if (password.length() > 8 && hasDigit && hasUppercase) {
            continue;
        }
    }
    cout << endl;

    if (password.length() < 8 || !hasDigit || !hasUppercase) {
        cout << "Password minimal harus terdiri dari 8 huruf, angka, dan huruf besar (uppercase)" << endl;
        password = "";
    }
    
}
bool loginUser(const string& nomorInduk, const string& password, string& role, User& currentUser) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].nomorInduk == nomorInduk && users[i].password == password) {
            if (users[i].status == "terblokir") {
                cout << "\nAkun diblokir. Hubungi admin untuk bantuan.\n";
                return false;
            }
            role = users[i].role;
            currentUser = users[i];
            return true;
        }
    }
    return false;
}

void detailUser() {
    cout << "\nDetail Pengguna:\n";
    for (int i = 0; i < userCount; ++i) {
        cout << i + 1 << ". "
            << "Nomor Induk: " << setw(12) << left << users[i].nomorInduk
            << " Nama: " << setw(12) << left << users[i].nama
            << " Role: " << setw(12) << left << users[i].role
            << " Status: " << users[i].status << "\n";
    }
}

void cariUser() {
	string nomorInduk;
    char pilihan = 0;

    do {
        bool penggunaDitemukan = false;
        cout << "\nCari Pengguna Berdasarkan Nomor Induk\n";
        cout << "Masukkan nomor induk: ";
        cin >> nomorInduk;
        for (int i = 0; i < userCount; ++i) {
            if (users[i].nomorInduk == nomorInduk) {
                penggunaDitemukan = true;
                cout << "\nPengguna ditemukan!\n";
				cout << "Nomor Induk: " << users[i].nomorInduk
                    << " Nama: " << setw(12) << left << users[i].nama
                    << " Role: " << setw(12) << left << users[i].role
                    << " Status: " << users[i].status << "\n";
            }
		}
        if (!penggunaDitemukan) {
            cout << "Pengguna tidak ditemukan.";
        }
		cout << "\nApakah Anda ingin mencoba lagi? (y/n): ";
		cin >> pilihan;
    } while (pilihan == 'y' || pilihan == 'Y');
}   

void tambahUser() {
    string nomorInduk, password, konfirmasiPassword, nama, role, status;
	char pilihan = 0;
    do {
		cout << "\nTambah Pengguna\n";
		cout << "Masukkan nomor induk: ";
		cin >> nomorInduk;
        if (!isUniqueNomorInduk(nomorInduk)) {
			cout << "Nomor induk sudah digunakan. Silakan coba lagi." << endl;
			continue;
		}
        cout << "Masukkan Password: ";
        hidePassword(password);
        cout << "Konfirmasi Password: ";
        hidePassword(konfirmasiPassword);
        if (password != konfirmasiPassword) {
			cout << "Password dan konfirmasi password tidak cocok. Silakan coba lagi." << endl;
			continue;
		}
		cout << "Masukkan nama: ";
		cin >> nama;
		cout << "Masukkan role(admin/dosen/mahasiswa): ";
		cin >> role;
        if (userCount < MAX_USERS) {
			users[userCount].nomorInduk = nomorInduk;
            users[userCount].password = password;
			users[userCount].nama = nama;
			users[userCount].role = role;
			users[userCount].status = "aktif";
			userCount++;
			cout << "Pengguna berhasil ditambahkan!" << endl;
		}
        else {
			cout << "Pengguna mencapai limit. Tidak dapat menambahkan pengguna lagi." << endl;
		}
		cout << "\nApakah Anda ingin menambahkan pengguna lagi? (y/n): ";
		cin >> pilihan;
	} while (pilihan == 'y' || pilihan == 'Y');

}

void editUser(){
    string nomorInduk;
    char pilihan = 0;

    cout << "\nEdit Pengguna\n";
    cout << "Masukkan nomor induk: ";
    cin >> nomorInduk;
    

    for (int i = 0; i < userCount; ++i) {
        if (users[i].nomorInduk == nomorInduk) {
            // Meminta input baru dari pengguna
            string newNomorInduk, newPassword, newRole, newStatus;

            cout << "apakah ingin menggunakan nomor induk yang sama(y/n)?";
            cin >> pilihan;
            if (pilihan == 'y' || pilihan == 'Y') {
                newNomorInduk = nomorInduk;
			}
            else {
                cout << "Masukkan nomor induk baru: ";
                cin >> newNomorInduk;
                if (!isUniqueNomorInduk(newNomorInduk)) {
                    cout << "Nomor induk sudah digunakan. Silakan coba lagi." << endl;
                    continue;
                }
            }
            cout << "Masukkan password: ";
            hidePassword(newPassword);
            cout << "Masukkan role(admin/dosen/mahasiswa): ";
            cin >> newRole;
            cout << "Masukkan status(aktif/terblokir): ";
            cin >> newStatus;

            // Mengganti informasi pengguna dengan informasi baru
            users[i].nomorInduk = newNomorInduk;
            users[i].password = newPassword;
            users[i].role = newRole;
            users[i].status = newStatus;

            cout << "Informasi pengguna berhasil diubah." << endl;
            return;
        }
    }
}

void detailMataKuliah() {
	cout << "\nDetail Mata Kuliah:\n";
    for (int i = 0; i < mataKuliahCount; ++i) {
        cout << i+1 << ". "
			<< "Kode Mata Kuliah: " << setw(6) << left << mataKuliah[i].kodeMataKuliah
			<< "Nama Mata Kuliah: " << setw(20) << left << mataKuliah[i].namaMataKuliah
			<< "Nama Dosen: " << setw(12) << left << mataKuliah[i].namaDosen
			<< "Nomor Induk Dosen: " << mataKuliah[i].nomorIndukDosen << "\n";
	}

}

void cariMataKuliah() {
    string kodeMataKuliah;
	char pilihan = 0;
	
    do {
		bool mataKuliahDitemukan = false;
		cout << "\nCari Mata Kuliah Berdasarkan Kode Mata Kuliah\n";
		cout << "Masukkan kode mata kuliah: ";
		cin >> kodeMataKuliah;
        for (int i = 0; i < mataKuliahCount; ++i) {
            if (mataKuliah[i].kodeMataKuliah == kodeMataKuliah) {
				mataKuliahDitemukan = true;
				cout << "\nMata Kuliah ditemukan!\n";
                cout << "Kode Mata Kuliah: " << setw(6) << left << mataKuliah[i].kodeMataKuliah
                    << "Nama Mata Kuliah: " << setw(20) << left << mataKuliah[i].namaMataKuliah
                    << "Nama Dosen: " << setw(12) << left << mataKuliah[i].namaDosen
                    << "Nomor Induk Dosen: " << mataKuliah[i].nomorIndukDosen << "\n";
			}
		}
        if (!mataKuliahDitemukan) {
			cout << "Mata Kuliah tidak ditemukan.";
		}
		cout << "\nApakah Anda ingin mencoba lagi? (y/n): ";
		cin >> pilihan;
	} while (pilihan == 'y' || pilihan == 'Y');

}

void tambahMataKuliah() {
    string kodeMataKuliah, namaMataKuliah, nomorIndukDosen, namaDosen;
	char pilihan = 0;
    do {
		cout << "\nTambah Mata Kuliah\n";
		cout << "Masukkan kode mata kuliah: ";
		cin >> kodeMataKuliah;
        if (!isUniqueKodeMataKuliah(kodeMataKuliah)) {
			cout << "Kode mata kuliah sudah digunakan. Silakan coba lagi." << endl;
			continue;
		}
		cout << "Masukkan nama mata kuliah: ";
		cin >> namaMataKuliah;
		cout << "Masukkan nomor induk dosen: ";
		cin >> nomorIndukDosen;

        for (int i = 0; i < userCount; ++i) {
            if (users[i].nomorInduk == nomorIndukDosen) {
                if (users[i].role == "dosen") {
                    if (mataKuliahCount < MAX_MATAKULIAH) {
                        mataKuliah[mataKuliahCount].kodeMataKuliah = kodeMataKuliah;
                        mataKuliah[mataKuliahCount].namaMataKuliah = namaMataKuliah;
                        mataKuliah[mataKuliahCount].namaDosen = users[i].nama;
                        mataKuliah[mataKuliahCount].nomorIndukDosen = nomorIndukDosen;
                        mataKuliahCount++;
                        cout << "Mata Kuliah berhasil ditambahkan!" << endl;
                    }
                    else {
                        cout << "Mata Kuliah mencapai limit. Tidak dapat menambahkan mata kuliah lagi." << endl;
                    }
				}
                else {
					cout << "Nomor Induk yang Anda masukkan bukan dosen.\n";
				}
				break;
            }
        }

		cout << "\nApakah Anda ingin menambahkan mata kuliah lagi? (y/n): ";
		cin >> pilihan;
	} while (pilihan == 'y' || pilihan == 'Y');
}

void editMataKuliah() {
	string kodeMataKuliah;
	char pilihan = 0;

	cout << "\nEdit Mata Kuliah\n";
	cout << "Masukkan kode mata kuliah: ";
	cin >> kodeMataKuliah;
	

    for (int i = 0; i < mataKuliahCount; ++i) {
        if (mataKuliah[i].kodeMataKuliah == kodeMataKuliah) {
			string newKodeMataKuliah, newNamaMataKuliah, newNomorIndukDosen, newNamaDosen;

			cout << "apakah ingin menggunakan kode mata kuliah yang sama(y/n)?";
			cin >> pilihan;
            if (pilihan == 'y' || pilihan == 'Y') {
				newKodeMataKuliah = kodeMataKuliah;
			}
            else {
				cout << "Masukkan kode mata kuliah baru: ";
				cin >> newKodeMataKuliah;
                if (!isUniqueKodeMataKuliah(newKodeMataKuliah)) {
					cout << "Kode mata kuliah sudah digunakan. Silakan coba lagi." << endl;
					continue;
				}
			}
			cout << "Masukkan nama mata kuliah: ";
			cin >> newNamaMataKuliah;
            cout << "Masukkan nomor induk dosen: ";
            cin >> newNomorIndukDosen;

            for (int j = 0; j < userCount; ++j) {
                if (users[j].nomorInduk == newNomorIndukDosen) {
                    if (users[j].role == "dosen") {
                        // Mengganti informasi mata kuliah dengan informasi baru
                        mataKuliah[i].kodeMataKuliah = newKodeMataKuliah;
                        mataKuliah[i].namaMataKuliah = newNamaMataKuliah;
                        mataKuliah[i].namaDosen = users[j].nama;
                        mataKuliah[i].nomorIndukDosen = newNomorIndukDosen;

                        cout << "Informasi mata kuliah berhasil diubah." << endl;
                        return;
                    }
                    else {
                        cout << "Nomor Induk yang Anda masukkan bukan dosen.\n";
                    }
                    break;
                }
            }
		}
	}
}

void inputMataKuliahMahasiswa() {
    cout << "\nInput Transaksi Mahasiswa\n";
    string nomorInduk, kodeMataKuliah, kodeTransaksi;
    bool penggunaDitemukan = false;
    char pilihan = 0;

    cout << "Masukkan nomor induk mahasiswa: ";
    cin >> nomorInduk;

    for (int i = 0; i < userCount; ++i) {
        if (users[i].nomorInduk == nomorInduk) {
            if (users[i].role == "mahasiswa") {
                penggunaDitemukan = true;
                cout << "Pengguna ditemukan!\n";

                //show nama&kode mata kuliah yang tersedia
                cout << "\nMata Kuliah yang tersedia:\n";
                for (int i = 0; i < mataKuliahCount; ++i) {
                    cout << i + 1 << ". "
                        << setw(20) << left << mataKuliah[i].namaMataKuliah
                        << "  kode: " << mataKuliah[i].kodeMataKuliah << endl;
                }

                do {
                    cout << "Masukkan kode mata kuliah: ";
                    cin >> kodeMataKuliah;

                    bool mataKuliahDitemukan = false;

                    for (int k = 0; k < transaksiCount; ++k) {
                        if (transaksi[k].nomorInduk == nomorInduk && transaksi[k].kodeMataKuliah == kodeMataKuliah) {
                            cout << "Mahasiswa sudah pernah mengambil mata kuliah ini sebelumnya.\n";
                            mataKuliahDitemukan = true;
                            break;
                        }
                    }

                    if (!mataKuliahDitemukan) {
                        transaksi[transaksiCount].nomorInduk = nomorInduk;
                        transaksi[transaksiCount].kodeMataKuliah = kodeMataKuliah;
                        transaksi[transaksiCount].nilai = 0;
                        transaksiCount++;
                        cout << "Transaksi berhasil diinput." << endl;
                    }

                    cout << "Apakah Anda ingin menginput mata kuliah lagi? (y/n): ";
                    cin >> pilihan;
                } while (pilihan == 'y' || pilihan == 'Y');
            }
            else {
                cout << "Nomor Induk yang Anda masukkan bukan mahasiswa.\n";
                break;
            }
        }
    }

    if (!penggunaDitemukan) {
        cout << "Pengguna tidak ditemukan.\n";
    }
}

void detailMahasiswa() {
    int nomorMataKuliah = 1;
    cout << "\nDaftar Mahasiswa:" << endl;
    for (int i = 0,count = 0; i < userCount; ++i) {
        if (users[i].role == "mahasiswa") {
            cout << "Mahasiswa " << ++count << ":\n";
            cout << "Nomor Induk    : " << users[i].nomorInduk << "\n";
            cout << "Nama           : " << users[i].nama << "\n";
            cout << "Status         : " << users[i].status << "\n";

            bool hasMataKuliah = false;
            cout << "\nNilai Matakuliah Mahasiswa\n";
            for (int j = 0; j < transaksiCount; ++j) {
                if (transaksi[j].nomorInduk == users[i].nomorInduk) {
                    for (int k = 0; k < mataKuliahCount; ++k ) {
                        if (mataKuliah[k].kodeMataKuliah == transaksi[j].kodeMataKuliah) {

                            cout << setw(20) << left << mataKuliah[k].namaMataKuliah;
                            hasMataKuliah = true;
                        }
                    }
                    cout << " : " << transaksi[j].nilai << "\n";
                }
            }
            if (!hasMataKuliah) {
                cout << "Mahasiswa Belum Mengambil Mata Kuliah\n";
            }
            cout << "============================\n";
        }
    }
}

void cariMahasiswa() {
    string nomorInduk;
    char pilihan = 0;

    do {
        bool penggunaDitemukan = false;
        cout << "\nCari Mahasiswa Berdasarkan Nomor Induk\n";
        cout << "Masukkan nomor induk: ";
        cin >> nomorInduk;

        for (int i = 0; i < userCount; ++i) {
            if (users[i].nomorInduk == nomorInduk) {
                if (users[i].role == "mahasiswa") {
                    penggunaDitemukan = true;
                    cout << "\nPengguna ditemukan!\n";
                    cout << "Nomor Induk    : " << users[i].nomorInduk << "\n";
                    cout << "Nama           : " << users[i].nama << "\n";
                    cout << "Role           : " << users[i].role << "\n";
                    cout << "Status         : " << users[i].status << "\n";

                    bool hasMataKuliah = false;
                    cout << "\nNilai Matakuliah Mahasiswa\n";
                    for (int j = 0; j < transaksiCount; ++j) {
                        if (transaksi[j].nomorInduk == users[i].nomorInduk) {
                            for (int k = 0; k < mataKuliahCount; ++k) {
                                if (mataKuliah[k].kodeMataKuliah == transaksi[j].kodeMataKuliah) {

                                    cout << j + 1 << ". " << setw(20) << left << mataKuliah[k].namaMataKuliah;
                                    hasMataKuliah = true;
                                }
                            }
                            cout << " : " << transaksi[j].nilai << "\n";
                        }
                    }
                    if (!hasMataKuliah) {
                        cout << "Mahasiswa Belum Mengambil Mata Kuliah\n";
                    }
                }
                else {
                    cout << "Nomor Induk yang Anda masukkan bukan mahasiswa.\n";
                }
                break;
            }
        }

        if (!penggunaDitemukan) {
            cout << "Pengguna tidak ditemukan.";
        }

        cout << "\nApakah Anda ingin mencoba lagi? (y/n): ";
        cin >> pilihan;
    } while (pilihan == 'y' || pilihan == 'Y');
}

void inputNilai() {
    string nim;

    cout << "\nInput Nilai Mahasiswa\n";
    cout << "Masukkan NIM Mahasiswa: ";
    cin >> nim;

    bool mahasiswaDitemukan = false;

    for (int i = 0; i < transaksiCount; ++i) {
        if (transaksi[i].nomorInduk == nim) {
            mahasiswaDitemukan = true;

            // Temukan mata kuliah yang sesuai dengan transaksi
            for (int j = 0; j < mataKuliahCount; ++j) {
                if (mataKuliah[j].kodeMataKuliah == transaksi[i].kodeMataKuliah) {

                    // Periksa apakah dosen yang input nilai adalah dosen yang mengajar mata kuliah ini
                    if (mataKuliah[j].nomorIndukDosen == currentUser.nomorInduk) {
                        cout << "Masukkan nilai untuk mata kuliah " << mataKuliah[j].namaMataKuliah << ": ";
                        cin >> transaksi[i].nilai;
                    }
                }
            }
            
        }
    }

    if (mahasiswaDitemukan) {
        cout << "Nilai berhasil diinput." << endl;
    }
    else {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan atau belum mengambil mata kuliah.\n";
    }
}

void editNilai() {
    string nim;
    string kodeMataKuliah;
    double nilaiBaru;

    cout << "\nEdit Nilai Mahasiswa\n";
    cout << "Masukkan NIM Mahasiswa: ";
    cin >> nim;

    bool mahasiswaDitemukan = false;
    bool mataKuliahDitemukan = false;


    for (int i = 0; i < transaksiCount; ++i) {
        if (transaksi[i].nomorInduk == nim) {
            mahasiswaDitemukan = true;

            cout << "Mata Kuliah yang Diambil oleh Mahasiswa dengan NIM " << nim << ":\n";

            for (int i = 0; i < transaksiCount; ++i) {
                if (transaksi[i].nomorInduk == nim) {
                    mahasiswaDitemukan = true;

                    for (int j = 0; j < mataKuliahCount; ++j) {
                        if (transaksi[i].kodeMataKuliah == mataKuliah[j].kodeMataKuliah) {
                            mataKuliahDitemukan = true;
                            cout << "Kode Mata Kuliah: " << setw(6) << left << mataKuliah[j].kodeMataKuliah
                                << "Nama Mata Kuliah: " << setw(20) << left << mataKuliah[j].namaMataKuliah
                                << "Nilai: " << transaksi[i].nilai << "\n";
                        }
                    }
                }
            }

            cout << "\nMasukkan Kode Mata Kuliah yang akan diubah: ";
            cin >> kodeMataKuliah;

            bool mataKuliahDitemukan = false;

            for (int j = 0; j < mataKuliahCount; ++j) {
                if (transaksi[i].kodeMataKuliah == mataKuliah[j].kodeMataKuliah) {
                    mataKuliahDitemukan = true;

                    // Tampilkan informasi mata kuliah yang akan diubah
                    cout << "Nilai Saat Ini: " << transaksi[i].nilai << "\n";

                    // Masukkan nilai baru
                    cout << "Masukkan Nilai Baru: ";
                    cin >> nilaiBaru;

                    // Simpan nilai baru
                    transaksi[i].nilai = nilaiBaru;
                    cout << "Nilai berhasil diubah.\n";
                    break; // Keluar dari loop setelah nilai diubah
                }
            }

            if (!mataKuliahDitemukan) {
                cout << "Mata kuliah dengan kode " << kodeMataKuliah << " tidak ditemukan.\n";
            }

            break; // Keluar dari loop setelah mahasiswa ditemukan
        }
    }

    if (!mahasiswaDitemukan) {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan atau tidak mengambil mata kuliah.\n";
    }
}



void lihatNilai() {
    cout << "\nNilai Mahasiswa\n";
    cout << "Mahasiswa " << currentUser.nama << " NBI: " << currentUser.nomorInduk << endl;

    int count = 0;

    for (int i = 0; i < transaksiCount; ++i) {
        if (currentUser.nomorInduk == transaksi[i].nomorInduk) {
            for (int j = 0; j < mataKuliahCount; ++j) {
                if (mataKuliah[j].kodeMataKuliah == transaksi[i].kodeMataKuliah) {
                    cout << ++count << ". Nama Mata Kuliah: " << setw(20) << left << mataKuliah[j].namaMataKuliah;
                    cout << "  Nilai: " << transaksi[i].nilai << "\n";
                }
            }
        }
    }

    if (count == 0) {
        cout << "Mahasiswa belum mengambil mata kuliah atau nilai belum diinput.\n";
    }
}


//dashboard
void adminDashboard() {
    int choice;
    do {
        cout << "\n=== DASHBOARD ADMIN ===" << endl;
        cout << "Hai Admin, " << currentUser.nama << endl;
        cout << "1. Detail User ALL" << endl;
        cout << "2. Cari User" << endl;
        cout << "3. Tambah User" << endl;
        cout << "4. Edit User" << endl;
        cout << "5. Detail Mata Kuliah ALL" << endl;
        cout << "6. Cari Mata Kuliah" << endl;
        cout << "7. Tambah Mata Kuliah" << endl;
        cout << "8. Edit Mata Kuliah" << endl;
        cout << "9. Detail Mahasiswa" << endl;
        cout << "10. Input Mata Kuliah Mahasiswa" << endl;
        cout << "11. Kembali ke Login/Keluar" << endl;
        cout << "Pilih opsi : ";
        cin >> choice;

        switch (choice) {
        case 1:
            detailUser();
            break;
        case 2:
            cariUser();
            break;
        case 3:
            tambahUser();
            break;
        case 4:
            editUser();
            break;
        case 5:
            detailMataKuliah();
            break;
        case 6:
            cariMataKuliah();
            break;
        case 7:
            tambahMataKuliah();
            break;
        case 8:
            editMataKuliah();
            break;
        case 9:
            detailMahasiswa();
            break;
        case 10:
            inputMataKuliahMahasiswa();
            break;
        case 11:
            cout << "Keluar dari Dashboard Admin." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
        }
    } while (choice != 11);
};
void dosenDashboard() {
    int choice;
    do {
        cout << "\n=== DASHBOARD DOSEN ===" << endl;
        cout << "Hai Dosen, " << currentUser.nama << endl;
        cout << "1. Detail Mahasiswa ALL" << endl;
        cout << "2. Cari Mahasiswa" << endl;
        cout << "3. Input Nilai" << endl;
        cout << "4. Edit Nilai" << endl;
        cout << "5. Kembali ke Login/Keluar" << endl;
        cout << "Pilih opsi : ";
        cin >> choice;

        switch (choice) {
        case 1:
            detailMahasiswa();
            break;
        case 2:
            cariMahasiswa();
            break;
        case 3:
            inputNilai();
            break;
        case 4:
            editNilai();
			break;
        case 5:
            cout << "Keluar dari Dashboard Dosen." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
        }
    } while (choice != 5);
}
void mahasiswaDashboard() {
	int choice;
    do {
		cout << "\n=== DASHBOARD MAHASISWA ===" << endl;
		cout << "Hai Mahasiswa, " << currentUser.nama << endl;
		cout << "1. Lihat Nilai Mata Kuliah" << endl;
		cout << "2. Kembali ke Login/Keluar" << endl;
		cout << "Pilih opsi : ";
		cin >> choice;

        switch (choice) {
		case 1:
			lihatNilai();
			break;
		case 2:
			cout << "Keluar dari Dashboard Mahasiswa." << endl;
			break;
		default:
			cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
			break;
		}
	} while (choice != 2);
}

int main() {
    string norek, pin, role, nomorInduk, nama, password;
    char pilihan = 0;

    blueprintUserAndAdmin();
    blueprintMataKuliah();
    blueprintTransaksi();
 

    do {
        cout << "\n=== LOGIN SIAKAD ===" << endl;
        cout << "Nomor Induk: ";
        cin >> nomorInduk;
        cout << "Password   : ";
        hidePassword(password);

        if (loginUser(nomorInduk, password, role, currentUser)) {
            if (role == "admin") {
                cout << "\nBerhasil login sebagai ADMIN!" << endl;
                //dashboard admin
                adminDashboard();
            }
            else if (role == "dosen") {
                cout << "\nBerhasil Login sebagai DOSEN!" << endl;
                //dashboard dosen
                dosenDashboard();
            }
            else if (role == "mahasiswa") {
                cout << "\nBerhasil Login! sebagai MAHASISWA!" << endl;
                //dashboard mahasiswa
                mahasiswaDashboard();
            }
            else {
                cout << "\nRole tidak valid. Silakan hubungi admin.\n";
            }
        }
        else {
            cout << "\nNomor Induk atau Password salah. Silakan coba lagi.\n"; 
        }
        cout << "\nApakah Anda ingin login kembali? (y/n): ";
        cin >> pilihan;
    } while (pilihan == 'y' || pilihan == 'Y');

    cout << "\nTerima kasih telah menggunakan SIAKAD!" << endl;

    return 0;
}