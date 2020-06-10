// $Id: SiSD.h,v 1.1 2013/10/03 19:07:26 mjt Exp $

#ifndef SiSD_h
#define SiSD_h 1

#include "G4VSensitiveDetector.hh"
#include "SiHit.h"

class G4Step;
class G4HCofThisEvent;

class SiSD : public G4VSensitiveDetector
{
  public:
      SiSD(G4String);
      virtual ~SiSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

  private:
      SiHitsCollection* SiHCollection;
};

#endif
