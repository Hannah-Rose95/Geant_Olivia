// $Id: SiSD.cc,v 1.1 2013/10/03 19:07:26 mjt Exp $

#include "SiSD.h"
#include "SiHit.h"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"         
#include "G4ThreeVector.hh"  
#include "G4SDManager.hh"    
#include "G4ios.hh"          
#include "G4UnitsTable.hh"

#include <fstream>
#include <iostream>
#include <sstream> 

using namespace std;

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
  if(aStep->GetTrack()->GetTrackID() > 0) {
  G4double edep = aStep->GetTotalEnergyDeposit();

  if(edep==0) return false;

  SiHit* aHit = new SiHit();
  aHit->SetEdep(edep);
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
