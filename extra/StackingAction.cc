// $Id: StackingAction.cc,v 1.1 2013/10/03 19:56:58 mjt Exp $

#include "StackingAction.h"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"

StackingAction::StackingAction()
{
  gammaCounter = 0;
}

StackingAction::~StackingAction()
{}

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track *aTrack)
{
  if(aTrack->GetDefinition() == G4Gamma::GammaDefinition())
  {
    if(aTrack->GetParentID()>0)
    { 
      gammaCounter++;
    }
  }
  return fUrgent;
}

void StackingAction::NewStage()
{
  G4cout << "Number of gammas in this event : "
         << gammaCounter << G4endl;
}

void StackingAction::PrepareNewEvent()
{ 
  gammaCounter = 0; 
}
