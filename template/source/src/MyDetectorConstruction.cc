
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "Verbose.hh"

#include "$MyDetectorConstruction$.hh"

$MyDetectorConstruction$::$MyDetectorConstruction$()
    : G4VUserDetectorConstruction()
{
  if (verbose)
    G4cout << "====>$MyDetectorConstruction$::$MyDetectorConstruction$()" << G4endl;
}

$MyDetectorConstruction$::~$MyDetectorConstruction$()
{
}

G4VPhysicalVolume *$MyDetectorConstruction$::Construct()
{
  if (verbose)
    G4cout << "====>$MyDetectorConstruction$::Construct()" << G4endl;

  // Get nist material manager
  G4NistManager *nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  // World
  G4double world_size = 200 * cm;
  G4Material *world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box *solidWorld =
      new G4Box("World",                                               //its name
                0.5 * world_size, 0.5 * world_size, 0.5 * world_size); //its size

  G4LogicalVolume *logicWorld =
      new G4LogicalVolume(solidWorld, //its solid
                          world_mat,  //its material
                          "World");   //its name

  G4VPhysicalVolume *physWorld =
      new G4PVPlacement(0,               //no rotation
                        G4ThreeVector(), //at (0,0,0)
                        logicWorld,      //its logical volume
                        "World",         //its name
                        0,               //its mother  volume
                        false,           //no boolean operation
                        0,               //copy number
                        checkOverlaps);  //overlaps checking

  //box
  G4Material *box_mat = nist->FindOrBuildMaterial("G4_Fe");
#define DZ 50. * cm
#define DY 60. * cm
#define DX 22. * cm
  G4ThreeVector posBox(DX, DY, DZ); //its position
  G4double box_x = 20. * cm;
  G4double box_y = 20. * cm;
  G4double box_z = 20. * cm;
  G4Box *solidShapeBox =                     //its name
      new G4Box("Box", box_x, box_y, box_z); //its size
  G4LogicalVolume *logicShapeBox =
      new G4LogicalVolume(solidShapeBox, //its solid
                          box_mat,       //its material
                          "Box");        //its name
  using std::string;
  G4String name("Box");
  new G4PVPlacement(0,              //no rotation
                    posBox,         //at position
                    logicShapeBox,  //its logical volume
                    name,           //its name
                    logicWorld,     //its mother  volume
                    false,          //no boolean operation
                    0,              //copy number
                    checkOverlaps); //overlaps checking
  return physWorld;
}