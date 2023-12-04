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
	string dosen;
};

// Struct Transaksi
struct Transaksi {
	string kodeTransaksi;
    string nomorInduk;
    string kodeMataKuliah;
    int nilai = 0;
};

// Global variables
// user
const int MAX_USERS = 100;
User users[MAX_USERS];
int userCount = 3;
// mata kuliah
const int MAX_MATAKULIAH = 100;
MataKuliah mataKuliah[MAX_MATAKULIAH];
int mataKuliahCount = 3;
// transaksi
Transaksi transaksi[];
int transaksiCount = 0;

User currentUser;
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
    users[2].status = "terblokir";
}
void blueprintMataKuliah() {
	mataKuliah[0].kodeMataKuliah = "MK001";
	mataKuliah[0].namaMataKuliah = "Pemrograman Dasar";
	mataKuliah[0].dosen = "1462300002";

	mataKuliah[1].kodeMataKuliah = "MK002";
	mataKuliah[1].namaMataKuliah = "Pemrograman Lanjut";
	mataKuliah[1].dosen = "1462300002";

	mataKuliah[2].kodeMataKuliah = "MK003";
	mataKuliah[2].namaMataKuliah = "Pemrograman Web";
	mataKuliah[2].dosen = "1462300002";
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

        if (password.length() < 8 && hasDigit && hasUppercase) {
            break;
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

//dashboard admin
void detailUser() {
    cout << "\nDetail Pengguna:\n";
    for (int i = 0; i < userCount; ++i) {
        cout << "Pengguna " << i + 1 << ":\n";
        cout << "Nomor Induk    : " << users[i].nomorInduk << "\n";
        //cout << "Password       : " << users[i].password << "\n";
        cout << "Nama           : " << users[i].nama << "\n";
        cout << "Role           : " << users[i].role << "\n";
        cout << "Status         : " << users[i].status << "\n";
        cout << "\n";
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
				cout << "Pengguna " << i + 1 << ":\n";
				cout << "Nomor Induk    : " << users[i].nomorInduk << "\n";
				cout << "Nama           : " << users[i].nama << "\n";
				cout << "Role           : " << users[i].role << "\n";
				cout << "Status         : " << users[i].status << "\n";
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
		cout << "Mata Kuliah " << i + 1 << ":\n";
		cout << "Kode Mata Kuliah    : " << mataKuliah[i].kodeMataKuliah << "\n";
		cout << "Nama Mata Kuliah    : " << mataKuliah[i].namaMataKuliah << "\n";
		cout << "Dosen               : " << mataKuliah[i].dosen << "\n";
		cout << "\n";
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
				cout << "Mata Kuliah " << i + 1 << ":\n";
				cout << "Kode Mata Kuliah    : " << mataKuliah[i].kodeMataKuliah << "\n";
				cout << "Nama Mata Kuliah    : " << mataKuliah[i].namaMataKuliah << "\n";
				cout << "Dosen               : " << mataKuliah[i].dosen << "\n";
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
    string kodeMataKuliah, namaMataKuliah, nomorIndukDosen;
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
        if (mataKuliahCount < MAX_MATAKULIAH) {
			mataKuliah[mataKuliahCount].kodeMataKuliah = kodeMataKuliah;
			mataKuliah[mataKuliahCount].namaMataKuliah = namaMataKuliah;
			mataKuliah[mataKuliahCount].dosen = nomorIndukDosen;
			mataKuliahCount++;
			cout << "Mata Kuliah berhasil ditambahkan!" << endl;
		}
        else {
			cout << "Mata Kuliah mencapai limit. Tidak dapat menambahkan mata kuliah lagi." << endl;
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
			// Meminta input baru dari pengguna
			string newKodeMataKuliah, newNamaMataKuliah, newDosen;

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
			cout << "Masukkan dosen: ";
			cin >> newDosen;

			// Mengganti informasi mata kuliah dengan informasi baru
			mataKuliah[i].kodeMataKuliah = newKodeMataKuliah;
			mataKuliah[i].namaMataKuliah = newNamaMataKuliah;
			mataKuliah[i].dosen = newDosen;

			cout << "Informasi mata kuliah berhasil diubah." << endl;
			return;
		}
	}
}

void adminDashboard(User& currentUser) {
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
        cout << "9. Kembali ke Login" << endl;
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
            cout << "Keluar dari Dashboard Admin." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
        }
    } while (choice != 8);
};

//dashboard Dosen

void detailMahasiswa() {
    cout << "\nDaftar Mahasiswa:" << endl;
    for (int i = 0; i < userCount; ++i) {
        if (users[i].role == "mahasiswa") {
            cout << "Mahasiswa " << i + 1 << ":\n";
            cout << "Nomor Induk    : " << users[i].nomorInduk << "\n";
            cout << "Nama           : " << users[i].nama << "\n";
            cout << "Status         : " << users[i].status << "\n";
            cout << "\n";
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
                    cout << "Pengguna " << i + 1 << ":\n";
                    cout << "Nomor Induk    : " << users[i].nomorInduk << "\n";
                    cout << "Nama           : " << users[i].nama << "\n";
                    cout << "Role           : " << users[i].role << "\n";
                    cout << "Status         : " << users[i].status << "\n";
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

//error
//void inputNilai() {
//    cout << "\nInput Nilai Mahasiswa\n";
//    string nomorInduk, kodeMataKuliah, kodeTransaksi;
//    int nilai;
//
//    cout << "masukkan nomor transaksi: ";
//    cin >> kodeTransaksi;
//    cout << "Masukkan nomor induk mahasiswa: ";
//    cin >> nomorInduk;
//    cout << "Masukkan kode mata kuliah: ";
//    cin >> kodeMataKuliah;
//    cout << "Masukkan nilai: ";
//    cin >> nilai;
//
//    transaksi[transaksiCount].k = kodeMataKuliah;
//    transaksi[transaksiCount].namaMataKuliah = namaMataKuliah;
//    transaksi[transaksiCount].dosen = nomorIndukDosen;
//    transaksiCount++;
//
//}

void dosenDashboard(User& currentUser) {
    int choice;
    do {
        cout << "\n=== DASHBOARD DOSEN ===" << endl;
        cout << "Hai Dosen, " << currentUser.nama << endl;
        cout << "1. Detail Mahasiswa ALL" << endl;
        cout << "2. Cari Mahasiswa" << endl;
        cout << "3. Input Nilai" << endl;
        cout << "4. Kembali ke Login" << endl;
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
            //inputNilai(currentTransaksi);
            break;
        case 4:
            cout << "Keluar dari Dashboard Dosen." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
        }
    } while (choice != 4);
}

//dashboard mahasiswa

void lihatNilai() {

}

void mahasiswaDashboard(User& currentUser) {
	int choice;
    do {
		cout << "\n=== DASHBOARD MAHASISWA ===" << endl;
		cout << "Hai Mahasiswa, " << currentUser.nama << endl;
		cout << "1. Lihat Nilai Mata Kuliah" << endl;
		cout << "2. Kembali ke Login" << endl;
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
	} while (choice != 3);
}

int main() {
    string norek, pin, role, nomorInduk, nama, password;
    char pilihan = 0;

    blueprintUserAndAdmin();
    blueprintMataKuliah();
    
 

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
                adminDashboard(currentUser);
            }
            else if (role == "dosen") {
                cout << "\nBerhasil Login sebagai DOSEN!" << endl;
                //dashboard dosen
                dosenDashboard(currentUser);
            }
            else if (role == "mahasiswa") {
                cout << "\nBerhasil Login! sebagai MAHASISWA!" << endl;
                //dashboard mahasiswa
                //mahasiswaDashboard(currentUser);
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