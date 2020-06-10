// $Id: EventAction.h,v 1.1 2013/10/03 19:07:26 mjt Exp $

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"

#include "globals.hh"

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();

    virtual void  BeginOfEventAction(const G4Event* );
    virtual void  EndOfEventAction(const G4Event* );

  private:
    G4int SiDetCollID;
};


#endif