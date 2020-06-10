// $Id: Run.h,v 1.1 2013/10/03 10:59:34 mjt Exp $

#ifndef Run_h
#define Run_h 1

#include "globals.hh"
#include "G4Run.hh"

#include "G4THitsMap.hh"

class G4Event;

class Run : public G4Run
{
  public:
    Run();
    virtual ~Run();

  public:
    virtual void RecordEvent(const G4Event*);

  private:  
    G4int colID;
};

#endif