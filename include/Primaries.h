// $Id$

#ifndef Primaries_h
#define Primaries_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

//class G4ParticleGun;
class G4GeneralParticleSource;
class G4Event;

class Primaries : public G4VUserPrimaryGeneratorAction
{
  public:
    Primaries();
    virtual ~Primaries();

  public:
    void GeneratePrimaries(G4Event*);

  private:
  //  G4ParticleGun* particleGun;
    G4GeneralParticleSource* particleSource;
};

#endif
