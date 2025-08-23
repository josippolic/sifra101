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

