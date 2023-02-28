// TrieStablo.h: interface for the TrieStablo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIESTABLO_H__EA14736F_A30C_4DA9_A044_C865B9328099__INCLUDED_)
#define AFX_TRIESTABLO_H__EA14736F_A30C_4DA9_A044_C865B9328099__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stablo.h"

class TrieStablo : public Stablo  
{
protected:

      class TrieCvor
      {
	      TrieCvor	*m_niz_pokazivaca[255];
            TrieCvor    *m_roditelj;
	      char		*m_info;
            int         m_brojPodstabala;

            TrieCvor(const TrieCvor &) { }
            TrieCvor &operator=(const TrieCvor &) { }

      public:
	      TrieCvor(TrieCvor *roditelj);

	      virtual ~TrieCvor();

            TrieCvor *roditelj() 
            {
                  return m_roditelj;
            }

	      TrieCvor *pronadjiPodstablo(char deoKljuca);
	      void dodajPodstablo(char deoKljuca, TrieCvor *cvor);
            void ukloniPodstablo(char deoKljuca);

            int brojPodstabala() const { return m_brojPodstabala; }

            char *dohvatiInfo();
            void postaviInfo(const char *tekst);

            void poseti(ostream &it);
      };


      TrieCvor    *m_koren;



      TrieStablo(const TrieStablo &) { }
      TrieStablo &operator=(const TrieStablo &) { }

      TrieCvor    *pronadjiCvor(const char *kljuc);   // pronalazi cvor koji sadrzi dati kljuc

public:
	TrieStablo();
	virtual ~TrieStablo();

	virtual bool umetni(const char *kljuc, const char *podaci);
	virtual bool obrisi(const char *kljuc);

      virtual void obidji(ostream &it);

      virtual char *dohvatiInfo(const char *kljuc);
};

#endif // !defined(AFX_TRIESTABLO_H__EA14736F_A30C_4DA9_A044_C865B9328099__INCLUDED_)
