// $Id: Run.cc,v 1.2 2013/10/03 19:07:26 mjt Exp $

#include "Run.h"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
extern ofstream outfile;

Run::Run()
{
  G4String detName = "";
  G4String primName = "";

  G4SDManager* SDMan = G4SDManager::GetSDMpointer();
  G4String fullName;
  
  fullName = detName+"/"+primName;
  colID = SDMan->GetCollectionID(fullName);
}

Run::~Run()
{}

void Run::RecordEvent(const G4Event* evt)
{
  G4int eventID = evt->GetEventID();
  
  G4double ElecEnergy = 0.0;

  
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  if(!HCE) return;
  
  G4THitsMap<G4double>* evtMap;
  std::map<G4int,G4double*>::iterator itr;
  
      evtMap = (G4THitsMap<G4double>*)(HCE->GetHC(colID));
      
      if(!evtMap) return;
      
	itr = evtMap->GetMap()->begin();
	for(; itr != evtMap->GetMap()->end(); itr++) { ElecEnergy += *(itr->second);} 
 
   G4cout << eventID << "\t" << ElecEnergy/MeV << " MeV" << G4endl; 
}



  
