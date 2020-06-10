// $Id$

#include "Primaries.h"
#include "Randomize.hh"

#include "G4Event.hh"
//#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"
//#include "SystemOfUnits.h"

Primaries::Primaries()
{


  G4int n_particle = 1;
  /*particleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("gamma");

  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleTime(0.0*ns);
  particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,7.85*cm));
//  particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,-1.0));
  particleGun->SetParticleEnergy(141*keV);
*/
 particleSource = new G4GeneralParticleSource();
}

Primaries::~Primaries()
{
  //delete particleGun;
  delete particleSource;
}

void Primaries::GeneratePrimaries(G4Event* anEvent)
{

/*  G4double max_angle = 5.0*deg;
  G4double max_vector = 1*tan(max_angle);
  G4double nx = CLHEP::RandFlat::shoot(-1.0*max_vector,max_vector);
  G4double ny = CLHEP::RandFlat::shoot(-1.0*max_vector,max_vector);
  particleGun-> SetParticleMomentumDirection(G4ThreeVector(nx,ny,-1.0));
*/
//  particleGun->GeneratePrimaryVertex(anEvent);

  particleSource-> GeneratePrimaryVertex(anEvent);
}
