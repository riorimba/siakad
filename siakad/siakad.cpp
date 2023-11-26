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

// Global variables
const int MAX_USERS = 100;
User users[MAX_USERS];
int userCount = 3;

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

//Validasi
bool isUniqueNomorInduk(const string& nomorInduk) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].nomorInduk == nomorInduk) {
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
                break;
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

void hapusUser(User& currentUser) {
    string nomorInduk, inputPasswordAdmin;
	char pilihan = 0;
    do {
		bool penggunaDitemukan = false;
		cout << "\nHapus Pengguna\n";
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
                cout << "\nMasukkan password admin untuk konfirmasi penghapusan: ";
                hidePassword(inputPasswordAdmin);
                if (inputPasswordAdmin == currentUser.password) {
                    cout << "Apakah Anda yakin ingin menghapus pengguna ini? (y/n): ";
                    cin >> pilihan;

                    if (pilihan == 'y' || pilihan == 'Y') {
                        for (int j = i; j < userCount - 1; ++j) {
                            users[j] = users[j + 1];
                        }
                        userCount--;
                        cout << "Pengguna berhasil dihapus!" << std::endl;
                    }
                    else {
                        cout << "Pengguna tidak jadi dihapus." << std::endl;
                    }
                }
                else {
                    cout << "Password admin tidak cocok. Pengguna tidak dihapus." << std::endl;
                }
			}
		}
        if (!penggunaDitemukan) {
			cout << "Pengguna tidak ditemukan.";
		}
		cout << "\nApakah Anda ingin mencoba lagi? (y/n): ";
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

void adminDashboard(User& currentUser) {
    int choice;
    do {
        cout << "\n=== DASHBOARD ADMIN ===" << endl;
        cout << "Hai Admin, " << currentUser.nama << endl;
        cout << "1. Detail User ALL" << endl;
        cout << "2. Cari User" << endl;
        cout << "3. Tambah User" << endl;
        cout << "4. Hapus User" << endl;
        cout << "5. Edit User" << endl;
        cout << "6. Detail Kelas" << endl;
        cout << "7. Tambah Kelas" << endl;
        cout << "8. Hapus Kelas" << endl;
        cout << "9. Edit Kelas" << endl;
        cout << "10. Detail Mata Kuliah" << endl;
        cout << "11. Tambah Mata Kuliah" << endl;
        cout << "12. Hapus Mata Kuliah" << endl;
        cout << "13. Edit Mata Kuliah" << endl;
        cout << "14. Kembali ke Login" << endl;
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
            hapusUser(currentUser);
            break;
        case 5:
            editUser();
            break;
        case 6:
            cout << "Keluar dari Dashboard Admin." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
        }
    } while (choice != 4);
};

//dashboard user

int main() {
    string norek, pin, role, nomorInduk, nama, password;
    char pilihan{};

    blueprintUserAndAdmin();
    User currentUser;
    const int MAX_LOGIN_ATTEMPTS = 3;
 
    do {
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
                    //dashboard guru
                    //guruDashboard(currentUser);
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
                cout << "Apakah Anda ingin mencoba login kembali? (y/n): ";
                cin >> pilihan;
            }
        } while (pilihan == 'y' || pilihan == 'Y');
        break;
    } while (currentUser.status != "terblokir");

    cout << "\nTerima kasih telah menggunakan SIAKAD!" << endl;


    return 0;
}