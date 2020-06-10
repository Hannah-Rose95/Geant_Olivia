// $Id: EventAction.cc,v 1.1 2013/10/03 19:07:26 mjt Exp $

#include "EventAction.h"
#include "SiHit.h"
#include <math.h>

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
//#include "G4VProcess.hh"

using namespace std;
using namespace CLHEP;

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
  //Create variables and arrays to store data: ints set to zero and array[x] defines empty array of size x
  G4int i;
  //G4int j=0;
  //G4int jmin=0;
 // ints if we only get one value for each event (e.g. total energy deposited in event); array if get multiple values for the event (i.e. each interaction position)
  G4int NumOfHits = 0;             //variable to store the number of interactions in an event : an int because only get one value for each event
  G4int NumOfGammas = 0;           //variable to store the number of gamma interactions in an event
  G4int NumOfIGammas = 0;           //variable to store the number of gamma interactions in an event

  G4int NumofElecs = 0;            //variable to store the number of electron interactions in an event
  G4double energy = 0;             //variable to store the total energy deposited in an event
  G4double totalenergy = 0;
  //G4double distance = 0;           //variable to store the distance between gamma interactions in an event
  G4double distancesquared[10000][10000];           //variable to store the distance squared between gamma interactions in an event
  G4double distance[10000][10000];           //variable to store the distance squared between gamma interactions in an event
  G4double maxdistance = 0;           //variable to store the maximum distance between gamma interactions in an event
  G4ThreeVector mypos(0);          //three vector variable to store the final interaction position of an event (x,y,z)
  //G4ThreeVector processes(0);

  G4int eventID = event->GetEventID();

  SiHitsCollection *SiHits = 0;
  G4HCofThisEvent* HCE = event->GetHCofThisEvent(); //get hit collection for this event

  if(HCE){
    SiHits = (SiHitsCollection*)(HCE->GetHC(SiDetCollID)); //get hit collection just for the chosen detector
    if(SiHits) {
      NumOfHits = SiHits->GetSize(); //how many interactions are there per event?
  //arrays to store things when there are properties for multiple interactions in a single event
  G4ThreeVector myposarray[10000];   //variable to store the interaction positions within an event
  G4ThreeVector Gammapos[10000];   //variable to store the interaction positions of just gammas within an event
  G4ThreeVector Gammapos1[10000];   //variable to store the first gamma interaction position for comparison
  G4ThreeVector Gammapos2[10000];   //variable to store the second gamma interaction position for comparison

  G4String type[10000];              //variable to store the type of particle (gamma or electron)
  G4double Type[10000];              //variable to store the type of particle in numerical form (gamma=1, electron=2)
  G4String process[10000];           //variable to store the physical process name through which the particle interacts (phot, compt, mcs, eIoni)- process across step
  G4double Process[10000];           // variable to store the physical process through which the particle interacts as an integer (phot=1, compt=2, mcs=3, eIoni=4)
  G4String c_process[10000];           //variable to store the physical process name  which created the particle  (phot, compt, mcs, eIoni)
  G4double c_Process[10000];           // variable to store the physical process which created the particle as an integer (phot=1, compt=2, mcs=3, eIoni=4)
  G4double energy_gamma[10000];      //variable to store the energy deposited by each interaction in an event
  //UNUSED
  G4int parent_ID[10000];         //variabe to store the track ID of the parent
  G4int track_ID[10000];
  G4double Ek_i[10000];
  G4double Ek_f[10000];
  //G4double delta_Energy[1000];

  //change this number later mofo

    if(NumOfHits > 0) {
  //call methods here using the name I gave them
      for(i=0;i<NumOfHits;i++) {
	energy += (*SiHits)[i]->GetEdep();        //total energy deposited across a step for each event
  energy_gamma[i]= (*SiHits)[i]->GetEdep(); //energy deposited across a step for each interaction
  Ek_i[i]=(*SiHits)[i]->GetIKineticEnergy();
  parent_ID[i]=(*SiHits)[i]->GetParentID();
  track_ID[i]=(*SiHits)[i]->GetTrackID();
  Ek_f[i]=(*SiHits)[i]->GetFKineticEnergy();
  myposarray[i]=(*SiHits)[i]->GetPos();

  //convert type of particles to an integer for easy read out
  if ((*SiHits)[i]->GetType()=="gamma") {
    Type[i]=1;
    Gammapos[i]=(*SiHits)[i]->GetPos();
    //count number of gamma interactions per event
    NumOfGammas ++;
    if ((track_ID[i]==1)) {
      NumOfIGammas ++;
    //want to add a line in here to calc dist between gammas
  }
}
  if ((*SiHits)[i]->GetType()=="e-") {
    Type[i]=2;
    //count number of electron interactions per event
    NumofElecs ++;
  }

/*
if(NumOfGammas > 1) {
  for(i=0;i<NumOfGammas;i++){
    Gammapos1[i]=Gammapos[i];
    jmin = i+1;
    for(j=jmin;j<NumOfGammas;j++){
    Gammapos2[j]=Gammapos[j];
    distancesquared[i][j]= (pow((Gammapos2[j][0]-Gammapos1[i][0]),2))+(pow((Gammapos2[j][1]-Gammapos1[i][1]),2))+(pow((Gammapos2[j][2]-Gammapos1[i][2]),2));
    distance[i][j]= pow(distancesquared[i][j],0.5);
    if(distance[i][j]>maxdistance){
      maxdistance = distance[i][j];
    }
    //maxdistance = max_element(begin (distance), end (distance));
  }}
}
*/

  type[i]=(*SiHits)[i]->GetType();

  //get the process across the step of the particle
  process[i]=(*SiHits)[i]->GetCreatProcess();
  //convert the processes into int values so they can be histogrammed later in python 
  if ((*SiHits)[i]->GetCreatProcess()=="phot") {
    Process[i]=1;
  } else if ((*SiHits)[i]->GetCreatProcess()=="compt") {
    Process[i]=2;
  } else if ((*SiHits)[i]->GetCreatProcess()=="msc") {
    Process[i]=3;
  } else if ((*SiHits)[i]->GetCreatProcess()=="eIoni") {
    Process[i]=4;
  } else {
    Process[i]=0;
  }

  //get the process which created the particle
  if (track_ID[i] != 1) {
    c_process[i]=(*SiHits)[i]->GetCProcess();
  //convert the processes into int values so they can be histogrammed
    if ((*SiHits)[i]->GetCProcess()=="phot") {
      c_Process[i]=1;
    } else if ((*SiHits)[i]->GetCProcess()=="compt") {
      c_Process[i]=2;
    } else if ((*SiHits)[i]->GetCProcess()=="msc") {
      c_Process[i]=3;
    } else if ((*SiHits)[i]->GetCProcess()=="eIoni") {
      c_Process[i]=4;
    } else {
      c_Process[i]=0;
    }  }
   if (track_ID[i] == 1) {
    c_Process[i] = 0;
  }

//get the last position in the event
      mypos =(*SiHits)[NumOfHits-1]->GetPos();

  }
}
//} //trialling this
//outfile to print one line for each event (i.e. not info about each interaction, just each event) good so don't have to worry about counting same event multiple times in histogram- not good for calculating dist between gammas
  //   outfile << eventID << "\t" << fixed << setprecision(4) << energy/keV << "\t" << NumOfHits << "\t" << NumOfGammas << "\t" << NumofElecs << "\t" << mypos[0]/cm << "\t" << mypos[1]/cm << "\t"<< mypos[2]/cm << G4endl;

  //G4String output_filename = "/media/sf_VirtualBoxShare/G4output.dat";
  //std::ofstream outfile;

  //out_file.open();

  //out_file.open(all_output.c_str(), std::ios_base::app);

  for(i=0;i<NumOfHits;i++) {
     //just print stuff that's going into histograms i.e. no words
    outfile << eventID << "\t" << fixed << setprecision(4) << energy/keV << "\t" << energy_gamma[i]/keV << "\t" << Type[i] << "\t" << Process[i] << "\t" << NumOfHits << "\t" << NumOfGammas << "\t" << NumofElecs << "\t" << mypos[0]/cm << "\t" << mypos[1]/cm << "\t"<< mypos[2]/cm << "\t" << myposarray[i][0]/cm << "\t" << myposarray[i][1]/cm  << "\t" << myposarray[i][2]/cm << "\t" << Ek_i[i]/keV << "\t" << Ek_f[i]/keV << "\t" << parent_ID[i]<< "\t" << track_ID[i] << "\t" << NumOfIGammas<< "\t" << c_Process[i] <<G4endl;
     //print everything for testing
  // outfile << eventID << "\t" << fixed << setprecision(4) << energy/keV << "\t" << energy_gamma[i]/keV << "\t" << maxdistance << "\t" << Type[i] << "\t" << type[i] << "\t" << process[i] << "\t" << Process[i] << "\t" << NumOfHits << "\t" << NumOfGammas << "\t" << NumofElecs << "\t" <<  mypos[0]/cm << "\t" << mypos[1]/cm << "\t"<< mypos[2]/cm << "\t" << myposarray[i][0]/cm << "\t" << myposarray[i][1]/cm  << "\t" << myposarray[i][2]/cm << G4endl;
} //one of these has been replaced with on in line (114) 135 eves

   }
 }}

//} }}
