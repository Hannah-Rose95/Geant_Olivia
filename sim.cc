// $Id

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "Primaries.h"
#include "Geometry.h"
#include "Physics.h"
//#include "RunAction.h"
#include "EventAction.h"
#include "StackingAction.h"

#include "G4PhysListFactory.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//#ifdef G4VERBOSE
//G4Exception ("G4Step::GetDeltaEnergy()","Warning", JustWarning,
//  "This method is obsolete and will be removed soon");
//#endif

#include <fstream>
#include <sstream>

using namespace std;
using namespace CLHEP;

ofstream outfile("/dev/fd/3", ios::out|ios::app);

int main(int argc,char** argv)
{
  HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  HepRandom::setTheSeed(1305202004); //change this number for each run for randomness

  G4RunManager* runManager = new G4RunManager;

  //G4VUserPhysicsList* physics = new Physics();
  G4VModularPhysicsList* physicsList = new Physics();
  runManager->SetUserInitialization(physicsList);

  G4VUserDetectorConstruction* detector = new Geometry();
  runManager-> SetUserInitialization(detector);

  G4VUserPrimaryGeneratorAction* primaries = new Primaries();
  runManager->SetUserAction(primaries);

  //G4UserRunAction* runAction = new RunAction();
  //runManager->SetUserAction(runAction);

  G4UserEventAction* eventAction = new EventAction();
  runManager->SetUserAction(eventAction);

  G4UserStackingAction* stackingAction = new StackingAction();
  runManager->SetUserAction(stackingAction);

#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  runManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  //UImanager->ApplyCommand("/control/execute source.mac");
 

// -------------------------------------------------------------------------

 //works with source.mac
  if (argc==1)      // interactive mode: define visualisation and UI terminal
    {
#ifdef G4UI_USE
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
      //UImanager->ApplyCommand("/control/execute source.mac");

#ifdef G4VIS_USE
      UImanager->ApplyCommand("/control/execute vis.mac");
#else
      UImanager->ApplyCommand("/control/execute visinit.mac");
#endif
      ui->SessionStart();
      delete ui;
#endif
    }
  else
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}
