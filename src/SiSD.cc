// $Id: SiSD.cc,v 1.1 2013/10/03 19:07:26 mjt Exp $

#include "SiSD.h"
#include "SiHit.h"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"


#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
//using namespace CLHEP;

extern ofstream outfile;

SiSD::SiSD(G4String name)
:G4VSensitiveDetector(name)
{
  collectionName.insert("SiHCollection");
}

SiSD::~SiSD(){ }

void SiSD::Initialize(G4HCofThisEvent* HCE)
{
  SiHCollection = new SiHitsCollection(SensitiveDetectorName, collectionName[0]);

  static G4int HCID = -1;

  if(HCID<0)
    {
      HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
      }

  HCE->AddHitsCollection(HCID, SiHCollection);
}

G4bool SiSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  //>0 for everything; ==1 for just primary gammas; >1 for just secondaries
  if(aStep->GetTrack()->GetTrackID() > 0 ) { //if the particle is being tracked
  G4double edep = aStep->GetTotalEnergyDeposit();   //get the total energy deposited in the step
  G4ThreeVector pos = aStep->GetPostStepPoint()->GetPosition();   //get the final position of the particle at the end of the step
  G4String type = aStep->GetTrack()->GetDefinition()->GetParticleName(); //get the name of the particle being tracked
  G4String process = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName(); //get ther process name involved in the step
  G4double Ek_i =aStep->GetPreStepPoint()->GetKineticEnergy(); //get the kinetic energy of the particle at the beginning of the step
  G4double Ek_f =aStep->GetPostStepPoint()->GetKineticEnergy(); //get the kinetic energy of the particle at the end of the step
  G4int parentID =aStep->GetTrack()->GetParentID(); //get the parent ID of the particle which created the particle being tracked
  G4double deltaEnergy = aStep->GetDeltaEnergy();
  G4int trackID = aStep->GetTrack()->GetTrackID(); //get the track ID of the particle
  G4String creationProcess;
  if (aStep->GetTrack()->GetCreatorProcess()!=0){
  creationProcess = aStep->GetTrack()->GetCreatorProcess()->GetProcessName(); //get the name of the process of the particle being tracked
  }
  else if (aStep->GetTrack()->GetCreatorProcess()== 0){
  creationProcess = "prim" ;} //get the name of the process of the particle being tracked
  //G4double Ek_f = aStep->GetPostStepPoint()->GetKineticEnergy();

  if(edep==0) return false;

//write the energy etc to Hit objects- can use my names here rather than the proper names
  SiHit* aHit = new SiHit();
  aHit->SetEdep(edep);
  aHit->SetPos(pos);
  aHit->SetType(type);
  aHit->SetCreatProcess(process);
  aHit->SetIKineticEnergy(Ek_i);
  aHit->SetFKineticEnergy(Ek_f);
  aHit->SetParentID(parentID);
  aHit->SetdeltaEnergy(deltaEnergy);
  aHit->SetTrackID(trackID);
  aHit->SetCProcess(creationProcess);



//  aHit->SetKineticEnergy(Ek_f);
//store the hit objects in the hit collection
  SiHCollection->insert(aHit);
  return true;
        } else return false;
}

void SiSD::EndOfEvent(G4HCofThisEvent*)
{
  if (verboseLevel>0) {
     G4int NbHits = SiHCollection->entries();
     G4cout << "\n-------->Hits Collection: in this event there are " << NbHits
            << " hits in the Si detector: " << G4endl;
  }
}
