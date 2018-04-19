
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

  fStepLimit = 0;
  for(int i=0;i<SIZE;i++) fDetPar[i] = new MyDetectorParameters();
  for(int i=0;i<SIZE;i++) fSolid[i]  = 0;
  for(int i=0;i<SIZE;i++) fLogic[i]  = 0;
  for(int i=0;i<SIZE;i++) fPhysc[i]  = 0;
  
  fDetectorMessenger = new MyDetectorMessenger(this);

$detSrcIni$ 

  //DefineMaterials();

}

$MyDetectorConstruction$::~$MyDetectorConstruction$()
{
  delete fDetectorMessenger;
  delete fStepLimit;
}

G4VPhysicalVolume *$MyDetectorConstruction$::Construct()
{
  if (verbose)
    G4cout << "====>$MyDetectorConstruction$::Construct()" << G4endl;

  return DefineVolumes();
}

G4VPhysicalVolume *$MyDetectorConstruction$::DefineVolumes()
{
  if(verbose) G4cout<<"====>G4VPhysicalVolume* MyDetectorConstruction::DefineVolumes()"<<G4endl;

  for(int i=0; i<100; i++)
  {
     if(fPhysc[i]!=NULL) delete fPhysc[i];
     if(fLogic[i]!=NULL) delete fLogic[i];
     if(fSolid[i]!=NULL) delete fSolid[i];
  }

  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // Define volume

$detSrcVol$ 

$detSrcVis$

  return physWorld;
}