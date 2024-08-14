//TP 2022/2023: LV 9, Zadatak 4
#include <iostream>
#include <cmath>
#include <iomanip>

class Sat {
    //int sati, minute, sekunde;
    int ukupno_sekundi = 0;
public:
    int DajSekunde() const { return ukupno_sekundi % 60; }
    int DajMinute() const { return (ukupno_sekundi / 60) % 60; }
    int DajSate() const { return ((ukupno_sekundi / 3600) % 24); }
    void Ispisi() const {std::cout << std::setfill('0') << std::setw(2) << DajSate() << ":" << std::setw(2) << DajMinute() << ":" << std::setw(2) << DajSekunde();}
    static bool DaLiJeIspravno(const int h, const int m, const int s) { return (h >= 0 && h < 24 && m >= 0 && m < 60 && s >=0 && s < 60); }
    void Postavi(int h, int m, int s);
    void PostaviNormalizirano(int h, int m, int s);
    Sat &Sljedeci() { PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde() + 1); return *this; }
    Sat &Prethodni() { PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde() - 1); return *this; }
    Sat &PomjeriZa(int broj) { PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde() + broj); return *this; }
    static int Razmak(Sat, Sat);
    friend int BrojSekundiIzmedju(Sat, Sat);
};

void ProvjeraDatumaTePostavljanje(Sat &s1) {
    if(!Sat::DaLiJeIspravno(s1.DajSate(), s1.DajMinute(), s1.DajSekunde())) {
        s1.PostaviNormalizirano(s1.DajSate(), s1.DajMinute(), s1.DajSekunde());
    }
}

int PretvoriUSekunde(Sat s1) {
    return s1.DajSekunde() + s1.DajMinute() * 60 + s1.DajSate() * 3600;
}

int Sat::Razmak(Sat s1, Sat s2) {
    ProvjeraDatumaTePostavljanje(s1);
    ProvjeraDatumaTePostavljanje(s2);
    return PretvoriUSekunde(s1) - PretvoriUSekunde(s2);
}

int BrojSekundiIzmedju(Sat s1, Sat s2) {
    return Sat::Razmak(s1, s2);
}

void Sat::Postavi(int h, int m, int s) {
    if(!DaLiJeIspravno(h, m, s)) {
        throw std::domain_error("Neispravno vrijeme");
    }
    ukupno_sekundi = s + m * 60 + h * 3600; 
}

void Sat::PostaviNormalizirano(int h, int m, int s) {
    try {
        Postavi(h, m, s);
    }
    catch(std::domain_error) {
        int sekunde, minute, sati;
        sekunde = (s >= 0 ? s % 60 : 60 + (s % 60));
        m += s / 60;
        if(s < 0 && (s / 60) >= 0) m--;
        minute = (m >= 0 ? m % 60 : 60 + (m % 60));
        h += m / 60;
        if(m < 0 && (m / 60) >= 0) h--;
        sati = (h >= 0 ? h % 24 : 24 + (h % 24));
        Postavi(sati, minute, sekunde);
        //Sat s;
        //s.Postavi(sati, minute, sekunde);
        //ukupno_sekundi = PretvoriUSekunde(s);
    }
}

void Unesi(int i, Sat &s1) {
    std::cout << "Unesite vrijeme s" << i << ": ";
    int h, m, s;
    std::cin >> h >> m >> s;
    s1.Postavi(h,m,s);
}

int main () {
    Sat s1, s2;
    Unesi(1, s1);
    Unesi(2, s2);
    std::cout << "Ovo vrijeme je ispravno(true/false): "<< std::boolalpha << Sat::DaLiJeIspravno(s1.DajSate(), s1.DajMinute(), s1.DajSekunde()) << std::noboolalpha;
    std::cout << "\nPrvo uneseno vrijeme je: ";
    s1.Ispisi();
    std::cout << "\nDrugo uneseno vrijeme je: ";
    s2.Ispisi();
    std::cout << "\nUnesite broj veci od 0: ";
    int br;
    std::cin >> br;
    Sat s3;
    s3.Postavi(0,0,0);
    while(br > 0) {
        s3.Sljedeci();  
        br--;
    }
    std::cout << "\nProslo je ";
    s3.Ispisi();
    std::cout << " ciklusa da se izvrsi petlja.";
	return 0;
}