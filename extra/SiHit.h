// $Id: SiHit.h,v 1.1 2013/10/03 19:07:26 mjt Exp $

#ifndef SiHit_h
#define SiHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class SiHit : public G4VHit
{
  public:

      SiHit();
      virtual ~SiHit();

      inline void* operator new(size_t);
      inline void  operator delete(void*);

  public:

      inline void SetEdep(G4double de){ edep = de; };
      inline G4double GetEdep(){ return edep; };
      
    
  private:
 
      G4double edep;
      
};

typedef G4THitsCollection<SiHit> SiHitsCollection;

extern G4Allocator<SiHit> SiHitAllocator;

inline void* SiHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) SiHitAllocator.MallocSingle();
  return aHit;
}

inline void SiHit::operator delete(void *aHit)
{
  SiHitAllocator.FreeSingle((SiHit*) aHit);
}

#endif
