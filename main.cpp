#include <IOSTREAM>
using namespace std;

#include "TrieStablo.h"
#include "DigitalnoStablo.h"


void trazi(Stablo &s, const char *kljuc){
    cout << "Trazim kljuc: " << kljuc << endl;
    char *rez = s.dohvatiInfo(kljuc);
    if( rez )
        cout << "<" << kljuc << ">" << " : " << rez << endl << endl;
    else
        cout << "Ne postoji kljuc: " << kljuc << endl << endl;
}

void main(){
Stablo *stablo = 0;
    cout << "(T)rie ili (D)igitalno stablo?";
    char c; cin >> c;
    if( c == 'T' || c == 't' )
        stablo = new TrieStablo;
    else if( c == 'D' || c == 'd' )
        stablo = new DigitalnoStablo;
    if( ! stablo ){
        cout << "Kraj"<<endl;
        exit(0);
    }
    stablo->umetni("Beograd", "Beograd: Glavni grad Srbije");
    stablo->umetni("Pariz", "Pariz: Glavni grad Francuske");
    stablo->umetni("Beocin", "Beocin: Tamo gde ima (privatizovana) cementara");
    stablo->umetni("Bellatrix", "Bellatrix: Jedna od zvezda iz Orionovog sazvezdja");
    stablo->umetni("Zoro", "Zoro: Maskirani osvetnik");

    trazi(*stablo, "Singidunum");
    trazi(*stablo, "Beograd");
    trazi(*stablo, "Pariz");
    trazi(*stablo, "Beocin");
    trazi(*stablo, "Bellatrix");
    trazi(*stablo, "Rigel");

    cout << endl << endl << "Obilazak stabla:" << endl;
    stablo->obidji(cout);
    
    stablo->ispisiStatistiku(cout);

    cout << endl << endl;
    stablo->obrisi("Pariz");

    trazi(*stablo, "Pariz");

    cout << endl << endl << "Obilazak stabla:" << endl;

    stablo->obidji(cout);

    stablo->ispisiStatistiku(cout);

    delete stablo;
}