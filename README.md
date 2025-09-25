Ovaj C++ program je **aplikacija za generiranje lozinki** s dodatnim sigurnosnim značajkama. Evo sažetka što radi:

* 📂 **Wordliste (blacklist)**: koristi `john.lst`, `wifite.txt`, `rockyou.txt` ili sve zajedno da bi izbjegao generiranje lozinki koje se nalaze u poznatim wordlistama.
* 🔐 **Generiranje lozinki**:

  * ručno (korisnik odredi dužinu),
  * automatski (uz provjeru da nije na wordlisti),
  * potpuno unikatna (lozinka koja nikad prije nije generirana i nije na wordlisti).
* 🎲 **Slučajni generator**: koristi **sigurniji generator slučajnih brojeva** (`std::random_device` + `mt19937`).
* 📊 **Entropija**: računa se količina sigurnosti lozinke u bitima (`length * log2(broj_znakova)`).
* 📑 **Logiranje**: svaka lozinka se sprema u `passwords5.txt` s datumom, entropijom, brojem generiranja i statusom blacklist provjere.
* 🔁 **Brojanje**: u `password_counts.txt` vodi se evidencija koliko je puta neka lozinka već generirana.
* 🛡 **Sigurni unos**: program koristi funkciju za sigurno čitanje cijelih brojeva (da spriječi krive unose).

➡️ Ukratko:
Program generira sigurne lozinke koje izbjegavaju poznate wordliste, računa im entropiju, pamti broj ponovnog generiranja i sve zapisuje u log fajlove.

____________________________________________________________________________________________________________________________________________________________
radi samo na kali linuxu

Ovaj C++ program je **generator lozinki** s podrškom za izbjegavanje poznatih lozinki iz wordlista (`john.lst`, `wifite.txt`, `rockyou.txt`) i vođenjem evidencije o broju puta kada je svaka lozinka generirana. Evo detaljan opis njegovih funkcionalnosti:

---

### 🧠 **Funkcionalnosti:**

1. **Učitavanje prethodnih lozinki:**

   * Čita datoteku `passwords5.txt` i sprema lozinke i broj njihovih generiranja u `unordered_map`.

2. **Wordlist Blacklisting:**

   * Učitava jedan ili više wordlista (`john.lst`, `wifite.txt`, `rockyou.txt`) te ih koristi za **izbjegavanje poznatih lozinki**.
   * Sve lozinke iz wordlista sprema u `unordered_set` (blacklist).

3. **Generiranje lozinki:**

   * **Ručni unos duljine lozinke** (8-15 znakova).
   * Koristi predefinirani set znakova `CHARACTERS`.
   * Provjerava je li lozinka već korištena i koliko puta.

4. **Tri moda rada:**

   * `Opcija 1:` Ručno generiranje lozinke.
   * `Opcija 2:` Automatsko generiranje, uz provjeru protiv wordlista.
   * `Opcija 3:` Potpuno jedinstvena lozinka (nije generirana ranije i nije u wordlistama).

5. **Evidencija lozinki:**

   * Nakon svake lozinke ažurira i zapisuje stanje u `passwords5.txt`.

---

### 📁 **Datoteke i putanje:**

* `passwords5.txt`: Sprema generirane lozinke i broj njihovih ponavljanja.
* Wordlist datoteke:

  * `~/usr/share/wordlists/john.lst`
  * `~/usr/share/wordlists/wifite.txt`
  * `~/usr/share/wordlists/rockyou.txt`

> ⚠ Napomena: Putanja `~` se neće automatski proširiti. Preporučuje se koristiti punu putanju (`/home/korisnik/...`).

---

### 🔐 **Set znakova za generiranje:**

```cpp
abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ@Ł!&#$/<>*ł?£&{}[]€;:-_÷^
```

> Uključuje velika/mala slova, brojeve i razne specijalne znakove (uključujući i Unicode znakove kao `Ł`, `€`, `ł`...).

---

### ✅ **Prednosti:**

* Povećana sigurnost izbjegavanjem poznatih lozinki.
* Jedinstveni mod koji osigurava potpunu originalnost lozinke.
* Dugoročno praćenje broja generiranja svake lozinke.

---

### 📌 **Moguće nadogradnje:**

* GUI verzija s Qt, GTK ili C++/CLI.
* Više opcija filtriranja (npr. isključi određene znakove).
* Šifriranje lozinki u datoteci.
* Bolja podrška za putanje (`~` expand).

---




