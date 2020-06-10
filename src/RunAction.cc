// $Id: RunAction.cc,v 1.1 2013/10/03 10:59:34 mjt Exp $

#include "RunAction.h"
#include "Run.h"

#include "G4RegionStore.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
extern ofstream outfile;

RunAction::RunAction()
{;}

RunAction::~RunAction()
{;}

G4Run* RunAction::GenerateRun()
{
  return new Run();
}

void RunAction::BeginOfRunAction(const G4Run*)
{
}
void RunAction::EndOfRunAction(const G4Run*)
{
  //out_file.close();
}
