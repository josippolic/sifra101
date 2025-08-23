//moduli
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <random>
#include <ctime>
#include <cmath>
#include <limits>

using namespace std;

// Konstante
const string LOG_FILE = "passwords5.txt";
const string COUNT_FILE = "password_counts.txt";
const string JOHN_LIST_PATH = "/home/korisnik/usr/share/wordlists/john.lst";
const string WIFITE_LIST_PATH = "/home/korisnik/usr/share/wordlists/wifite.txt";
const string ROCKYOU_LIST_PATH = "/home/korisnik/usr/share/wordlists/rockyou.txt";
const string CHARACTERS = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ@Ł!&#$/<>*ł?£&{}[]€;:-_÷^";

// Sigurniji generator slučajnih brojeva
string generatePassword(int length) {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, CHARACTERS.length() - 1);

    string password;
    for (int i = 0; i < length; ++i) {
        password += CHARACTERS[dis(gen)];
    }
    return password;
}

unordered_map<string, int> readPasswords() {
    unordered_map<string, int> passwords;
    ifstream file(COUNT_FILE);
    string password;
    int count;
    while (file >> password >> count) {
        passwords[password] = count;
    }
    return passwords;
}

void writePasswords(const unordered_map<string, int>& passwords) {
    ofstream file(COUNT_FILE);
    for (const auto& entry : passwords) {
        file << entry.first << " " << entry.second << "\n";
    }
}

unordered_set<string> readWordlist(const string& path) {
    unordered_set<string> blacklist;
    ifstream file(path);
    string word;
    while (getline(file, word)) {
        if (!word.empty()) blacklist.insert(word);
    }
    return blacklist;
}

double calculateEntropy(int length, int charsetSize) {
    return length * log2(charsetSize);
}

string getCurrentTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M", ltm);
    return string(buffer);
}

// Sigurno čitanje cijelog broja iz inputa
int safeInputInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Neispravan unos. Pokušaj ponovno.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

void passwordGenerator() {
    unordered_map<string, int> passwords = readPasswords();
    unordered_set<string> blacklist;

    cout << "\n================== Password Generator App ==================\n\n";
    cout << "Odaberi wordlist:\n";
    cout << "1. john.lst\n";
    cout << "2. wifite.txt\n";
    cout << "3. rockyou.txt\n";
    cout << "4. svi (john + wifite + rockyou)\n";
    int choice = safeInputInt("Tvoj izbor (1/2/3/4): ", 1, 4);

    if (choice == 1) {
        blacklist = readWordlist(JOHN_LIST_PATH);
    } else if (choice == 2) {
        blacklist = readWordlist(WIFITE_LIST_PATH);
    } else if (choice == 3) {
        blacklist = readWordlist(ROCKYOU_LIST_PATH);
    } else if (choice == 4) {
        blacklist = readWordlist(JOHN_LIST_PATH);
        unordered_set<string> wifite = readWordlist(WIFITE_LIST_PATH);
        unordered_set<string> rockyou = readWordlist(ROCKYOU_LIST_PATH);
        blacklist.insert(wifite.begin(), wifite.end());
        blacklist.insert(rockyou.begin(), rockyou.end());
    }

    cout << "\nOdaberi opciju:\n";
    cout << "1. Ručno generiraj lozinku\n";
    cout << "2. Automatski generiraj (izbjegni wordlistu)\n";
    cout << "3. Potpuno unikatna lozinka\n";
    int option = safeInputInt("Unesi broj: ", 1, 3);

    if (option == 1 || option == 2) {
        int passlen = safeInputInt("Unesi dužinu lozinke (8-15): ", 8, 15);

        string password;
        do {
            password = generatePassword(passlen);
        } while (blacklist.find(password) != blacklist.end());

        double entropy = calculateEntropy(passlen, CHARACTERS.length());
        string timestamp = getCurrentTimestamp();

        passwords[password]++;
        cout << "\n🔐 Lozinka: " << password;
        cout << "\n📊 Entropija: " << entropy << " bita";
        cout << "\n🔁 Generirana " << passwords[password] << " puta.";
        cout << "\n⚠️  Blacklist status: NE\n";

        ofstream log(LOG_FILE, ios::app);
        if (log.is_open()) {
            log << "---------------------------\n";
            log << "Datum: " << timestamp << "\n";
            log << "Lozinka: " << password << "\n";
            log << "Entropija: " << entropy << " bita\n";
            log << "Broj generiranja: " << passwords[password] << "\n";
            log << "Blacklist status: NE\n";
            log << "---------------------------\n";
            log.close();
        }
    } else if (option == 3) {
        string password;
        int passlen;
        do {
            passlen = 8 + (rand() % 8);
            password = generatePassword(passlen);
        } while (passwords.find(password) != passwords.end() || blacklist.find(password) != blacklist.end());

        double entropy = calculateEntropy(passlen, CHARACTERS.length());
        string timestamp = getCurrentTimestamp();

        passwords[password] = 1;

        cout << "\n🔐 Unikatna lozinka: " << password;
        cout << "\n📊 Entropija: " << entropy << " bita";
        cout << "\n⚠️  Blacklist status: NE\n";

        ofstream log(LOG_FILE, ios::app);
        if (log.is_open()) {
            log << "---------------------------\n";
            log << "Datum: " << timestamp << "\n";
            log << "Lozinka: " << password << "\n";
            log << "Entropija: " << entropy << " bita\n";
            log << "Broj generiranja: 1\n";
            log << "Blacklist status: NE\n";
            log << "---------------------------\n";
            log.close();
        }
    }

    writePasswords(passwords);
}

int main() {
    passwordGenerator();
    return 0;
}
