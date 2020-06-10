// $Id$

#include "Geometry.h"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"


#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4NistManager.hh"

#include "globals.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RunManager.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4SDParticleFilter.hh"
#include "G4SDManager.hh"

//added because of sensitive detector
#include "SiSD.h"

Geometry::Geometry()
{
}

Geometry::~Geometry()
{
}

G4VPhysicalVolume* Geometry::Construct()
{
  //Sizes are half the value of the actual dimensions
  //Set the world and detector dimensions here
  G4double world_size = 2*m;
  G4double detector_x = 22*mm;
  G4double detector_y = 22*mm;
  G4double detector_z = 2.5*mm;


  G4NistManager* man = G4NistManager::Instance();
  //G4Material *Vac = man->FindOrBuildMaterial("G4_Galactic");
  G4Material *Air = man->FindOrBuildMaterial("G4_AIR");
  G4Material *Water = man->FindOrBuildMaterial("G4_WATER");

  //Define detector materials
  //Import pre-defined elements Thallium and Bromine from the NIST database
  G4Element* Tl = man-> FindOrBuildElement("Tl");
  G4Element* Br = man-> FindOrBuildElement("Br");
  //Other way to define elements by defining atomic number and density - will be useful if you need to use materials that aren't in the NIST database
  //G4Element* Tl = new G4Element("Thallium","Tl",81.,127.60*g/mole);
  //G4Element* Br = new G4Element("Bromine","Br",35.,79.904*g/mole);


  //Combine Tl and Br to build TlBr Material
  //May need to change TlBr density and ratios of Tl and Br in compound
  G4Material* TlBr = new G4Material("TlBr", 5.8*g/cm3, 2);
  TlBr->AddElement(Tl, 50*perCent);
  TlBr->AddElement(Br, 50*perCent);


  G4Box* world_box = new G4Box("world_box",world_size,world_size,world_size);

  G4LogicalVolume* world_log = new G4LogicalVolume(world_box,Air,"world_log");

  G4VPhysicalVolume* world_phys = new G4PVPlacement(0,                    //rotation
                        G4ThreeVector(),      //position
                        world_log,            //attach to logical volume
                        "world_phys",         //name of physical volume
                        0,                    //mother volume
                        false,                //unused
                        0,                    //copy number
                        false);               //overlap check

  G4Box* detector_box = new G4Box("detector_box",detector_x,detector_y,detector_z);
  G4LogicalVolume* detector_log = new G4LogicalVolume(detector_box,TlBr,"detector_log");
  G4VPhysicalVolume* detector_phys =  new G4PVPlacement(0,G4ThreeVector(0,0,0*cm),detector_log,"detector_phys",world_log,false,0,false);

  G4Colour col_pink(0.9,0.2,0.8);
  G4VisAttributes* boxVisAtt= new G4VisAttributes(col_pink);
  boxVisAtt->SetVisibility(true);
  detector_log->SetVisAttributes(boxVisAtt);

  G4VisAttributes* worldVisAtt= new G4VisAttributes();
  worldVisAtt->SetVisibility(false);
  world_log->SetVisAttributes(worldVisAtt);


  //Add sensitive detector- Si for silicon for now... go back and change at some stage!..or maybe not this will be v complicated
  G4SDManager* SDman= G4SDManager::GetSDMpointer();
  SiSD*aSiSD= new SiSD("sidet");
  SDman->AddNewDetector(aSiSD);
  detector_log->SetSensitiveDetector(aSiSD);

  //This has to be the last line in the code ALWAYS.
  return world_phys;
}
