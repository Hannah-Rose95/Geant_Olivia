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

      inline void SetPos(G4ThreeVector pos){ end_pos = pos; };
      inline G4ThreeVector GetPos(){ return end_pos; };

      inline void SetType(G4String type){ par_type = type; };
      inline G4String GetType(){ return par_type; };

      inline void SetCreatProcess(G4String process){ step_process = process; };
      inline G4String GetCreatProcess(){ return step_process; };

      inline void SetParentID(G4int parentID){ parent_ID = parentID; };
      inline G4int GetParentID(){ return parent_ID; };

      inline void SetIKineticEnergy(G4double Ek_i){ E_kin_i = Ek_i; };
      inline G4double GetIKineticEnergy(){ return E_kin_i; };

      inline void SetFKineticEnergy(G4double Ek_f){ E_kin_f = Ek_f; };
      inline G4double GetFKineticEnergy(){ return E_kin_f; };

      inline void SetdeltaEnergy(G4double deltae){ deltaEnergy = deltae; };
      inline G4double GetdeltaEnergy(){return deltaEnergy; };

      inline void SetTrackID(G4int trackID){ track_ID = trackID; };
      inline G4int GetTrackID(){ return track_ID; };

      inline void SetCProcess(G4String creationProcess){ creation_process = creationProcess; };
      inline G4String GetCProcess(){ return creation_process; };

  private:

      G4double edep;
      G4ThreeVector end_pos;
      G4String par_type;
      G4String step_process;
      G4int parent_ID;
      G4double E_kin_i;
      G4double E_kin_f;
      G4double deltaEnergy;
      G4int track_ID;
      G4String creation_process;


};

typedef G4THitsCollection<SiHit> SiHitsCollection;

static G4Allocator<SiHit> SiHitAllocator;

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
