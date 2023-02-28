// TrieStablo.cpp: implementation of the TrieStablo class.
//
//////////////////////////////////////////////////////////////////////

#include "TrieStablo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TrieStablo::TrieCvor::TrieCvor(TrieStablo::TrieCvor *roditelj)
: m_roditelj(roditelj),
  m_info(0),
  m_brojPodstabala(0)
{
      for(int i = 0; i < 255; i++)
            m_niz_pokazivaca[i] = 0;
}

TrieStablo::TrieCvor::~TrieCvor()
{
      if( m_info )
            delete []m_info;

      for(int i = 0; i < 255; i++)
            if( m_niz_pokazivaca[i] )
                  delete m_niz_pokazivaca[i];
}


TrieStablo::TrieCvor *TrieStablo::TrieCvor::pronadjiPodstablo(char deoKljuca)
{
      return m_niz_pokazivaca[deoKljuca];
}

void TrieStablo::TrieCvor::dodajPodstablo(char deoKljuca, TrieStablo::TrieCvor *cvor)
{
      if( ! m_niz_pokazivaca[deoKljuca] )
      {
            m_niz_pokazivaca[deoKljuca] = cvor;
            m_brojPodstabala++;
      }
}

void TrieStablo::TrieCvor::ukloniPodstablo(char deoKljuca)
{
      if( m_niz_pokazivaca[deoKljuca] )
      {
            m_niz_pokazivaca[deoKljuca] = 0;
            m_brojPodstabala--;
      }
}

void TrieStablo::TrieCvor::postaviInfo(const char *tekst)
{
      if( m_info )
      {
            delete []m_info;
            m_info = 0;
      }

      if( tekst )
      {
            m_info = new char[ strlen(tekst) + 1 ];
            strcpy(m_info, tekst);
      }
}

char *TrieStablo::TrieCvor::dohvatiInfo()
{
      return m_info;
}


void TrieStablo::TrieCvor::poseti(ostream &it)
{
      if( m_info )
            it << m_info << endl;

      for(int i = 0; i < 255; i++)
            if( m_niz_pokazivaca[i] )
                  m_niz_pokazivaca[i]->poseti(it);
}



//---------------------------------------------------------------


TrieStablo::TrieCvor *TrieStablo::pronadjiCvor(const char *kljuc)
{
      if( ! m_koren )
            return 0;

      TrieCvor *tek = m_koren;

      for( int i = 0; i < strlen(kljuc) && tek; i++ )
            tek = tek->pronadjiPodstablo( kljuc[i] );

      return tek;
}

TrieStablo::TrieStablo()
: m_koren(0)
{
}

TrieStablo::~TrieStablo()
{
      if( m_koren )
            delete m_koren;
}


bool TrieStablo::umetni(const char *kljuc, const char *podaci)
{
      if( ! m_koren )
      {
            m_koren = new TrieCvor(0);
            m_brCvorova++;
      }

      TrieCvor *tek = m_koren;
      TrieCvor *sledeci = 0;

      for( int i = 0; i < strlen(kljuc); i++ )
      {
      
            sledeci = tek->pronadjiPodstablo( kljuc[i] );

            if( ! sledeci )
            {
                  sledeci = new TrieCvor(tek);
                  tek->dodajPodstablo( kljuc[i], sledeci );
                  m_brCvorova++;
            }

            tek = sledeci;
      }

      bool rezultat = true;  // ako je kljuc prvi put umetnut, onda true
      if( sledeci->dohvatiInfo() )
            rezultat = false;
      else
            m_brKljuceva++;

      sledeci->postaviInfo(podaci);      

      return rezultat;
}

bool TrieStablo::obrisi(const char *kljuc)
{
      if( ! m_koren )
            return false;

      TrieCvor *tek = pronadjiCvor(kljuc);
      if( ! tek )
            return false;

      tek->postaviInfo(0);
      int i = strlen(kljuc)-1;
      
      while( i >= 0 && tek && tek->brojPodstabala() == 0 && !tek->dohvatiInfo() )
      {
      TrieCvor *roditelj = tek->roditelj();

            delete tek;
            m_brCvorova--;

            if( roditelj )
                  roditelj->ukloniPodstablo( kljuc[i--] );
            else
                  m_koren = 0;
            tek = roditelj;
      }

      m_brKljuceva--;
      return true;
}

void TrieStablo::obidji(ostream &it)
{
      if( m_koren )
            m_koren->poseti(it);
      else
            it << "Stablo je prazno." << endl;
}


char *TrieStablo::dohvatiInfo(const char *kljuc)
{
/*
      if( ! m_koren )
            return 0;

      TrieCvor *cvor = m_koren;
      int i = 0, maxi = strlen(kljuc);

      while( cvor && i < maxi )
            cvor = cvor->pronadjiPodstablo( kljuc[i++] );
*/
      TrieCvor *cvor = pronadjiCvor(kljuc);

      if( cvor )
            return cvor->dohvatiInfo();

      return 0;
}