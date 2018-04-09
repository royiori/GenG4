#ifndef $MyDetectorConstruction$_h
#define $MyDetectorConstruction$_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class $MyDetectorConstruction$ : public G4VUserDetectorConstruction
{
public:
  $MyDetectorConstruction$();
  virtual ~$MyDetectorConstruction$();

  virtual G4VPhysicalVolume *Construct();
};

#endif