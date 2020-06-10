// $Id: EventAction.cc,v 1.1 2013/10/03 19:07:26 mjt Exp $

#include "EventAction.h"
#include "SiHit.h"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"

#include "G4VisManager.hh"

using namespace std;

extern ofstream outfile;

EventAction::EventAction()
: G4UserEventAction()
{
  SiDetCollID = -1;
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{  
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  
  if (SiDetCollID==-1) {
    SiDetCollID = SDman->GetCollectionID("SiHCollection");
  }
}

void EventAction::EndOfEventAction(const G4Event* event)
{
  G4int i;
  G4int NumOfHits = 0;
  G4double energy = 0;
 
  G4int eventID = event->GetEventID();
 
  SiHitsCollection *SiHits = 0;
  G4HCofThisEvent* HCE = event->GetHCofThisEvent();

  if(HCE){
    SiHits = (SiHitsCollection*)(HCE->GetHC(SiDetCollID));
    if(SiHits) {
    
      NumOfHits = SiHits->GetSize();
    
    if(NumOfHits > 0) {
      for(i=0;i<NumOfHits;i++) {
	energy += (*SiHits)[i]->GetEdep();
      }
      G4cout << eventID << "\t" << energy/MeV << " MeV" << G4endl;     
    }
   }
  }
}  
