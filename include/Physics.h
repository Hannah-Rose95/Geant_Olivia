// $Id$

#ifndef Physics_h
#define Physics_h 1

#include "G4SystemOfUnits.hh"
//#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class Physics: public G4VModularPhysicsList
{
  public:
    Physics();
   ~Physics();

  protected:
    //Don't need these 2 if using modular pre-existing physics list
    //void ConstructParticle();
    //void ConstructProcess();
    void SetCuts();

};

#endif
