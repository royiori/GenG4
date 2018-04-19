#ifndef $MyDetectorConstruction$_h
#define $MyDetectorConstruction$_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4CSGSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class MyDetectorMessenger;

//-------------------------------
// detector parameter variables

$detIncEnum$

//-------------------------------
// detector parameter class
class MyDetectorParameters
{
public:
  MyDetectorParameters()
  {
    Name = "";
    Matt = "";
    Material = 0;
    visAtt = 0;
    for (int i = 0; i < 10; i++)
      Siz[i] = 0;
    for (int i = 0; i < 3; i++)
      Pos[i] = 0;
    for (int i = 0; i < 3; i++)
      Rot[i] = 0;
  }

  virtual ~MyDetectorParameters(){};

  G4String Name;
  G4String Matt;
  G4double Siz[10];
  G4double Pos[3];
  G4double Rot[3];
  G4Material *Material;
  G4VisAttributes *visAtt;
};


//-------------------------------
// detector contructions
class $MyDetectorConstruction$ : public G4VUserDetectorConstruction
{
public:
  $MyDetectorConstruction$();
  virtual ~$MyDetectorConstruction$();

  G4VPhysicalVolume *DefineVolumes();
  virtual G4VPhysicalVolume *Construct();

  void SetMaterial(int, G4String);
  void Update();

public:
$detIncFunc$

private:
  void  DefineMaterials();

  MyDetectorMessenger *fDetectorMessenger;

  G4bool checkOverlaps;
  G4UserLimits *fStepLimit; 

  MyDetectorParameters *fDetPar[SIZE];
  G4CSGSolid *fSolid[SIZE];
  G4LogicalVolume *fLogic[SIZE];
  G4VPhysicalVolume *fPhysc[SIZE];
};

#endif