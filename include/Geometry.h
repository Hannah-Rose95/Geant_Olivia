// $Id$

#ifndef Geometry_h
#define Geometry_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

class Geometry : public G4VUserDetectorConstruction
{
  public:
    Geometry();
    virtual ~Geometry();

  public:
    virtual G4VPhysicalVolume* Construct();
};

#endif
