// $Id: StackingAction.cc,v 1.1 2013/10/03 19:56:58 mjt Exp $

#include "StackingAction.h"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"

using namespace std;
extern ofstream outfile;

StackingAction::StackingAction()
{
}

StackingAction::~StackingAction()
{}

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track *aTrack)
{
  //if the particle is a gamma and if it is a secondary, count it
  if(aTrack->GetDefinition() == G4Gamma::GammaDefinition())
  {
    //ParentID = 0 for prims and =1 for secondaries
    if(aTrack->GetParentID()>0)
    {
    }

  }
  return fUrgent;
}

void StackingAction::NewStage()
{
  //G4cout << "Number of gammas in this event : "
  //       << gammaCounter << G4endl;
}

void StackingAction::PrepareNewEvent()
{
  gammaCounter = 0;
}
