#include <iostream>
using namespace std;



//Z0.1
char* AlocirajIKopiraj(const char* tekst)
{
    if (tekst == nullptr)
    {
        return nullptr;
    }
    int vel = strlen(tekst) + 1; //mjeri duzinu proslijedjenog stringa, a +1 stavljamo zbog null terminiracujeg znaka '\0'(oznacava gdje se zavrsava niz)

    char* noviTekst = new char[vel];
    strcpy_s(noviTekst, vel, tekst);
    return noviTekst;
}

struct Datum
{
    int* _dan = nullptr;
    int* _mjesec = nullptr;
    int* _godina = nullptr;
    //Z1.1

    // U unosima uvijek radimo alokaciju

    void Unos(int d, int m, int g)
    {
        _dan = new int;
        _mjesec = new int;
        _godina = new int;

        *_dan = d;
        *_mjesec = m;
        *_godina = g;

    }
    //Z1.2
    void Unos(Datum& datum)
    {
        _dan = new int;
        _mjesec = new int;
        _godina = new int;

        *_dan = *datum._dan;
        *_mjesec = *datum._mjesec;
        *_godina = *datum._godina;
    }
    //Z1.3
    void Unos(Datum* datum)
    {
        _dan = new int;
        _mjesec = new int;
        _godina = new int;

        *_dan = *(*datum)._dan; // da ne bi radili ovako *(*datum)._dan umjesto pointera na datum i . stavljamo -> (shortcut) i izbjegavamo nagomilavanje zagrada
        *_mjesec = *datum->_mjesec;
        *_godina = *datum->_godina;
    }
    //Z1.4
    int GetDan()
    {
        return *_dan;
    }
    int GetMjesec()
    {
        return *_mjesec;
    }
    int GetGodina()
    {
        return *_godina;
    }

    //Z1.5
    void SetDan(int dan) //Funkcija proslijedjeni parametar postavlja za dan 
    {
        if (_dan == nullptr)
        {
            _dan = new int;
        }
        *_dan = dan;

    }
    //Z1.6
    void SetMjesec(int mjesec) //Funkcija proslijedjeni parametar postavlja za mjesec
    {
        if (_mjesec == nullptr)
        {
            _mjesec = new int;
        }
        *_mjesec = mjesec;

    }

    //Z1.7 
    void SetGodina(int godina) //Funkcija proslijedjeni parametar postavlja za godinu
    {
        if (_godina == nullptr)
        {
            _godina = new int;

        }
        *_godina = godina;

    }
    //Z1.8
    void Ispis()
    {
        cout << *_dan << "." << *_mjesec << "." << *_godina << "." << endl;
    }
    //Z1.9
    void Dealokacija()
    {
        delete _dan;
        delete _mjesec;
        delete _godina;

        /*
        Mozemo dealocirati i na kraci nacin:
          delete  _dan, _mjesec, _godina;
        */

        _dan = nullptr;
        _mjesec = nullptr;
        _godina = nullptr;

        /*
        Mozemo setati na null i na kraci nacin:
          _dan = _mjesec = _godina = nullptr;
        */
    }
};
//Z1.10
bool JeLiIsti(Datum& d1, Datum& d2)
{
    return *d1._dan == *d2._dan
        && *d1._mjesec == *d2._mjesec
        && *d1._godina == *d2._godina;

}
//Z1.11
Datum& GetStarijiDatum(Datum& d1, Datum& d2)
{
    if (*d1._godina < *d2._godina)
    {
        return d1;
    }
    else if (*d1._godina == *d2._godina)
    {
        if (*d1._mjesec < *d2._mjesec)
        {
            return d1;
        }
        else if (*d1._mjesec == *d2._mjesec)
        {
            if (*d1._dan <= *d2._dan)
            {
                return d1;
            }
            return d2;

        }
        return d2;
    }
    return d2;
}
//Z1.12
Datum& GetNovijiDatum(Datum& d1, Datum& d2)
{
    if (JeLiIsti(GetStarijiDatum(d1, d2), d1)) // radi olaksanja prosljedjujemo funkciju GetStarijiDatum(d1,d2) i d1 u funkciju JeLiIsti 
    {                                      //gdje nam funkcija provjerava da li je dobijeni datum iz GetStarijiDatum jednak d1 ako jest vracamo d2 
        return d2;                //jer je logicno d2 onda mladji datum, a ako je dobijeni datum iz funkcije GetStarijiDatum razlicit od d1 onda vracamo d1
    }

    return d1;
}

//Z1.13
Datum* GetNajstarijiDatum(Datum datum[], int size)
{
    Datum* najstariji = datum; //Datum* najnoviji = &datum[0]; moze i ovako, ovdje incijaliziramo pointer na prvi element niza datum

    for (int i = 0; i < size; i++)
    {
        najstariji = &GetStarijiDatum(*najstariji, *(datum + i)); // moze i umjesto *(datum+i) datum[i], a & ispred funkcije stavljamo zato sto je objekat i moramo uzeti njegovu adresu 
    }

    return najstariji;
}

/*
ALTERNATIVA ZA PRETHODNU FUNKCIJU:

MOZEMO KORISTITI OBA NACINA SAMO STO SE REFERENCA ODNOSI NA KOMPLETAN OBJEKAT KAO TAKAV, A POKAZIVAC SAMO NA ADRESU TOG OBJEKTA

Datum& GetNajstarijiDatum_1(Datum datum[], int size)
{
    Datum& najstariji = datum[0];

    for (int i = 0; i < size; i++)
    {
      najstariji = &GetStarijiDatum(najstariji, *(datum + i));
    }

    return najstariji;
}

*/
//Z1.14
Datum* GetNajnovijiDatum(Datum datum[], int size)
{
    Datum* najnoviji = &datum[0];

    for (int i = 0; i < size; i++)
    {
        najnoviji = &GetNovijiDatum(*najnoviji, datum[i]); //& ispred funkcije stavljamo zato sto je objekat i moramo uzeti njegovu adresu 
    }

    return najnoviji;
}

struct Glumac
{
    char _jmbg[14] = "";
    char* _ime = nullptr;
    char* _prezime = nullptr;
    Datum* _datumRodjenja = nullptr; // kad god vidimo pokazivac odma treba da znamo da ide dinamicka alokacija
    char* _mjestoRodjenja = nullptr;
    char _drzava[100];
    bool _spol; //1:Muski, 0:Zenski
    //Z2.1
    void Unos(const char* jmbg, const char* ime, const char* prezime, Datum& datumRodjenja,
        const char* mjestoRodjenja, const char* drzava, bool spol) //kada god imamo niz karaktera tj. staticki niz onda nemamo nikakvih alokacija, a ni operator jednako ne mozemo koristiti sa njima osim kad se kreiraju  
    {                                                           // u njih pohranjujemo podatke kopiranjem (stcpy_s) funckijom
        strcpy_s(_jmbg, 14, jmbg);
        _ime = AlocirajIKopiraj(ime);
        _prezime = AlocirajIKopiraj(prezime);
        _datumRodjenja = new Datum;                                 //(*this)ili this-> pristupanje objektima sa kojima trenutno komuniciramo
        _datumRodjenja->Unos(datumRodjenja);
        _mjestoRodjenja = AlocirajIKopiraj(mjestoRodjenja);
        strcpy_s(this->_drzava, 100, drzava);
        _spol = spol;


    }
    //Z2.2
    void Unos(Glumac& glumac)
    {
        strcpy_s(this->_jmbg, 14, glumac._jmbg);
        _ime = AlocirajIKopiraj(glumac._ime);
        _prezime = AlocirajIKopiraj(glumac._prezime);
        _datumRodjenja = new Datum;
        _datumRodjenja->Unos(glumac._datumRodjenja);
        _mjestoRodjenja = AlocirajIKopiraj(glumac._mjestoRodjenja);
        strcpy_s(this->_drzava, 100, glumac._drzava);
        _spol = glumac._spol;
    }
    //Z2.3
    void SetJmbg(const char* jmbg)
    {
        strcpy_s(_jmbg, 14, jmbg);
    }
    //Z2.4
    void SetIme(const char* ime)
    {
        delete[]_ime; //dinamicki nizovi se ne mogu sami od sebe prosiriti, zbog toga ih moramo unistiti (izbrisati) pa prosiriti dinamickim putem
        _ime = AlocirajIKopiraj(ime);
    }
    //Z2.5
    void SetPrezime(const char* prezime)
    {
        delete[]_prezime;
        _prezime = AlocirajIKopiraj(prezime);
    }
    //Z2.6
    void SetDatumRodjenja(Datum& datumRodjenja) //Kad trebamo setovati objekat koji je objekat neke druge klase onda on poziva svoje setere
    {
        if (_datumRodjenja == nullptr)
        {
            _datumRodjenja = new Datum;
        }
        _datumRodjenja->SetDan(*datumRodjenja._dan);
        _datumRodjenja->SetMjesec(*datumRodjenja._mjesec);
        _datumRodjenja->SetGodina(*datumRodjenja._godina);
    }
    //Z2.7
    void SetMjestoRodjenja(const char* mjestoRodjenja)
    {
        delete[]_mjestoRodjenja;
        _mjestoRodjenja = AlocirajIKopiraj(mjestoRodjenja);
    }
    //Z2.8
    void SetDrzava(const char* drzava)
    {
        strcpy_s(_drzava, 100, drzava);
    }
    //Z2.9
    void SetSpol(bool spol)
    {
        _spol = spol; //ovo radimo zato sto je spol varijabla koja nije pokazivac
    }
    //Z2.10
    void Ispis()
    {
        cout << endl;
        cout << "Ime: " << _ime << "\t";
        cout << "Prezime: " << _prezime;
        cout << endl;
        cout << "Datum rodjenja: ";
        _datumRodjenja->Ispis();
        cout << "Mjesto rodjenja: " << _mjestoRodjenja << endl;
        cout << "Drzava rodjenja: " << _drzava << endl;
        //1 za MUSKO, 0 za ZENSKO
        cout << "Spol je: " << ((_spol == true) ? "Musko" : "Zensko") << endl; //upitni ternarni ili operator 
    }
    //Z2.11
    void Dealokacija()
    {
        delete[]_ime, _prezime, _mjestoRodjenja;
        _ime = _prezime = _mjestoRodjenja = nullptr;
        _datumRodjenja->Dealokacija(); //Kada god imamo objekat ili pokazivac na objekat, a dio je neke strukture 
        delete _datumRodjenja;   //prvo se trebamo pobrinuti da su dealocirani njegovi dijelovi pa cemo onda dealocirati njega kao takvog
        _datumRodjenja = nullptr;
    }
};

struct Film {
    char _filmID[50] = ""; //prema ISAN standardu
    char* _naziv = nullptr;
    char _zanr[40];
    int _godinaIzlaska;
    int _trenutnoGlumaca = 0;
    Glumac _glumackaPostava[20]; //kada imamo ovakav slucaj bez pointera tada je samo potrebno da dealociramo njegove atribute koji su dinamicki
    int _trenutnoOcjena = 0; //Kada god imamo prefix trenutno to se odnosi na brojac 
    int* _ocjene = nullptr; //Dinamicki prosirivati ovaj niz svakim novim dodavanjem
    //Z3.1
    void Unos(const char* filmID, const char* naziv, const char* zanr, int godinaIzlaska)
    {
        strcpy_s(_filmID, 50, filmID);
        _naziv = AlocirajIKopiraj(naziv);
        strcpy_s(_zanr, 40, zanr);
        _godinaIzlaska = godinaIzlaska;
    }
    //Z3.2
    void Unos(Film& film)
    {
        strcpy_s(_filmID, 50, film._filmID);
        _naziv = AlocirajIKopiraj(film._naziv);
        strcpy_s(_zanr, 40, film._zanr);
        _godinaIzlaska = film._godinaIzlaska;
        _trenutnoGlumaca = film._trenutnoGlumaca;
        for (int i = 0; i < _trenutnoGlumaca; i++)
        {
            _glumackaPostava[i].Unos(film._glumackaPostava[i]);
        }
        _trenutnoOcjena = film._trenutnoOcjena;

        _ocjene = new int[_trenutnoOcjena];

        for (int i = 0; i < _trenutnoOcjena; i++)
        {
            _ocjene[i] = film._ocjene[i];
        }
    }
    //Z3.3
    bool DodajGlumca(Glumac& g)
    {
        if (_trenutnoGlumaca == 20)
        {
            return false;
        }

        _glumackaPostava[_trenutnoGlumaca].Unos(g); //Koristimo unos obiljezja iz glumca "g"
        _trenutnoGlumaca++;
        return true;
    }
    //Z3.4
    bool DodajOcjenu(int ocjena)
    {
        int* temp = _ocjene;//Pomocni pokazivac na niz ocjene 
        _ocjene = new int[_trenutnoOcjena + 1];//Stari niz ocjena prosirimo za 1
        for (int i = 0; i < _trenutnoOcjena; i++)
        {
            _ocjene[i] = temp[i];
        }
        delete[]temp;

        temp = nullptr;
        _ocjene[_trenutnoOcjena] = ocjena;
        _trenutnoOcjena++;
        return true;
    }
    //Z3.5
    void Ispis()
    {
        cout << "Naziv filma: " << _naziv << endl;
        cout << "Zanr filma: " << _zanr << endl;

        cout << "Godina izlaska: " << _godinaIzlaska << endl;
        cout << "Trenutno ima: " << _trenutnoGlumaca << " glumaca." << endl;
        cout << endl;
        for (int i = 0; i < _trenutnoGlumaca; i++)
        {
            _glumackaPostava[i].Ispis();
        }
        cout << "Ukupno ocjena: " << _trenutnoOcjena << " ocjena." << endl;
        cout << "Prosjecna ocjena: " << GetProsjecnaOcjena() << endl;

    }


    //Z3.6
    float GetProsjecnaOcjena()
    {
        float suma = 0.0;

        for (int i = 0; i < _trenutnoOcjena; i++)
        {
            suma += _ocjene[i];
        }

        return suma / _trenutnoOcjena;
    }

    //Z3.7
    void Dealokacija()
    {
        delete[] _ocjene, _naziv;
        _ocjene = nullptr;
        _naziv = nullptr;

        for (int i = 0; i < _trenutnoGlumaca; i++)
        {
            _glumackaPostava[i].Dealokacija();
        }
    }
};

void Zadatak1() {
    cout << ":Zadatak 1:" << endl;
    Datum prviMart, danNezavisnosti, danDrzavnosti;
    prviMart.Unos(1, 3, 2021);
    danNezavisnosti.Unos(prviMart);
    danDrzavnosti.Unos(&prviMart);
    danDrzavnosti.SetDan(25);
    danDrzavnosti.SetMjesec(11);
    danDrzavnosti.SetGodina(2021);

    cout << "Dan nezavisnosti: " << endl;
    danNezavisnosti.Ispis();
    cout << endl << "Dan drzavnosti: " << endl;
    danDrzavnosti.Ispis();
    prviMart.Dealokacija();
    danNezavisnosti.Dealokacija();
    danDrzavnosti.Dealokacija();

    Datum danD, operacijaBarbarossa, sarajevskiAtentat, apolloSlijetanje, blackThursday;
    danD.Unos(6, 6, 1944);
    operacijaBarbarossa.Unos(22, 6, 1941);
    sarajevskiAtentat.Unos(28, 6, 1914);
    apolloSlijetanje.Unos(24, 7, 1969);
    blackThursday.Unos(24, 10, 1929);

    Datum historijskiDogadjaji[5];
    historijskiDogadjaji[0].Unos(danD);
    historijskiDogadjaji[1].Unos(operacijaBarbarossa);
    historijskiDogadjaji[2].Unos(sarajevskiAtentat);
    historijskiDogadjaji[3].Unos(apolloSlijetanje);
    historijskiDogadjaji[4].Unos(blackThursday);

    cout << endl << "Najstariji datum: " << endl;
    GetNajstarijiDatum(historijskiDogadjaji, 5)->Ispis();
    cout << endl << "Najnoviji datum: " << endl;
    GetNajnovijiDatum(historijskiDogadjaji, 5)->Ispis();

    //DEALOKACIJE
    danD.Dealokacija();
    operacijaBarbarossa.Dealokacija();
    sarajevskiAtentat.Dealokacija();
    apolloSlijetanje.Dealokacija();
    blackThursday.Dealokacija();
    for (size_t i = 0; i < 5; i++)
        historijskiDogadjaji[i].Dealokacija();
    cout << endl << "Dealokacija uspjesna!" << endl;
}

void Zadatak2() {
    cout << ":Zadatak 2:" << endl;

    Glumac alPacino, deNiro;
    Datum temp1, temp2;
    temp1.Unos(25, 4, 1940);
    temp2.Unos(17, 8, 1943);
    alPacino.Unos("1304996055555", "Alfredo", "Pacino", temp1, "Manhattan, NYC", "SAD", 1);
    deNiro.Unos(alPacino);
    deNiro.SetIme("Robert");
    deNiro.SetPrezime("De Niro");
    deNiro.SetDatumRodjenja(temp2);
    deNiro.SetMjestoRodjenja("Greenwich Village");
    deNiro.SetDrzava("SAD");
    deNiro.SetSpol(1);

    Datum datumi[5];
    datumi[0].Unos(7, 6, 1995);
    datumi[1].Unos(7, 11, 1991);
    datumi[2].Unos(3, 6, 1995);
    datumi[3].Unos(5, 6, 1992);
    datumi[4].Unos(1, 6, 1993);
    Glumac glumciNarodnogPozorista[5];
    glumciNarodnogPozorista[0].Unos("0706995088888", "Barb", "Dwyer", datumi[0], "Mostar", "BiH", 1);
    glumciNarodnogPozorista[1].Unos("0711991144488", "Anna", "Graham", datumi[1], "Ostrozac", "BiH", 0);
    glumciNarodnogPozorista[2].Unos("0306995099999", "Benjamin", "Button", datumi[2], "Sarajevo", "BiH", 1);
    glumciNarodnogPozorista[3].Unos("0506992011993", "Jack", "Pott", datumi[3], "Vogosca", "BiH", 1);
    glumciNarodnogPozorista[4].Unos("0106993094444", "Justin", "Case", datumi[4], "Kotor-Varos", "BiH", 1);

    cout << "Ispis svih glumaca:: " << endl;
    for (size_t i = 0; i < 5; i++) {
        cout << "-----------------------------------------------" << endl;
        glumciNarodnogPozorista[i].Ispis();
    }
    cout << "-----------------------------------------------" << endl;
    cout << endl;

    //DEALOKACIJE
    temp1.Dealokacija();
    temp2.Dealokacija();
    alPacino.Dealokacija();
    deNiro.Dealokacija();
    for (size_t i = 0; i < 5; i++) {
        datumi[i].Dealokacija();
        glumciNarodnogPozorista[i].Dealokacija();
    }
    cout << "Dealokacija uspjesna!" << endl;
}
void Zadatak3() {
    Datum temp1, temp2;
    temp1.Unos(25, 4, 1940);
    temp2.Unos(17, 8, 1943);
    Glumac alPacino, deNiro;
    alPacino.Unos("2504940555551", "Alfredo", "Pacino", temp1, "Manhattan, NYC", "SAD", 1);
    deNiro.Unos("1708943055555", "Robert", "De Niro", temp2, "NYC", "SAD", 1);

    Film irishman;
    irishman.Unos("XXXX-AAAA-BBBB-CCCC", "The Irishman", "Biografija, krimi, drama", 2019);
    irishman.DodajGlumca(alPacino);
    irishman.DodajGlumca(deNiro);
    irishman.DodajOcjenu(10);
    irishman.DodajOcjenu(8);
    irishman.DodajOcjenu(9);
    irishman.DodajOcjenu(8);
    irishman.DodajOcjenu(8);
    Film kopija;
    kopija.Unos(irishman);
    kopija.Ispis();
    //DEALOKACIJE
    irishman.Dealokacija();
    kopija.Dealokacija();
    alPacino.Dealokacija();
    deNiro.Dealokacija();
    temp1.Dealokacija();
    temp2.Dealokacija();
}

void main() {
    int nastaviDalje = 1;
    while (nastaviDalje == 1) {
        int izbor = 0;
        do {
            system("cls");
            cout << "::Zadaci::" << endl;
            cout << "(1) Zadatak 1" << endl;
            cout << "(2) Zadatak 2" << endl;
            cout << "(3) Zadatak 3" << endl;
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor < 1 || izbor > 3);
        switch (izbor) {
        case 1: Zadatak1(); cout << "Done." << endl; break;
        case 2: Zadatak2(); cout << "Done." << endl; break;
        case 3: Zadatak3(); cout << "Done." << endl; break;
        default:break;
        }
        do {
            cout << "DA LI ZELITE NASTAVITI DALJE? (1/0): ";
            cin >> nastaviDalje;
        } while (nastaviDalje != 0 && nastaviDalje != 1);
    }
}
