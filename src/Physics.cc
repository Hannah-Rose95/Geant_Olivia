// $Id$

#include "Physics.h"
#include "G4ParticleTypes.hh"
#include "globals.hh"
#include "G4ProcessManager.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4LivermorePhotoElectricModel.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4EmStandardPhysics_option4.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"


Physics::Physics()
{
defaultCutValue = 1*um;
RegisterPhysics( new G4EmStandardPhysics_option4(0) );
RegisterPhysics( new G4DecayPhysics(0) );
RegisterPhysics( new G4RadioactiveDecayPhysics(0) );
}

Physics::~Physics()
{
}

/*
void Physics::ConstructParticle()
{
 G4Gamma::GammaDefinition();
 G4Electron::ElectronDefinition();
 G4Positron::PositronDefinition();
}

void Physics::ConstructProcess()
{
  AddTransportation();

   auto theParticleIterator = GetParticleIterator();
   theParticleIterator->reset();
   while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if (particleName == "gamma") {
      // set processes for gamma particles
      // Discrete processes only happen at post step positions
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      pmanager->AddDiscreteProcess(new G4ComptonScattering);
    //  pmanager->AddDiscreteProcess(new G4GammaConversion);

    } else if (particleName == "e-") {
      //electron processes
      //continuous processes ordered (RHS) for at rest, along step and post step; ordered by probability of occurring
      pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4eIonisation,         -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung,     -1, 3, 3);

    } else if (particleName == "e+") {
      //positron
      pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4eIonisation,         -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung,     -1, 3, 3);
      pmanager->AddProcess(new G4eplusAnnihilation,    0,-1, 4);

    }
  }
} */

void Physics::SetCuts()
{
  SetCutsWithDefault();
}
