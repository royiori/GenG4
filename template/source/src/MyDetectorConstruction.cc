
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4UniformMagField.hh"
#include "G4AutoDelete.hh"

#include "G4ProductionCuts.hh"
#include "G4HadronicProcessStore.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Verbose.hh"

#include "$MyDetectorConstruction$.hh"
#include "$MyDetectorMessenger$.hh"

$MyDetectorConstruction$::$MyDetectorConstruction$()
    : G4VUserDetectorConstruction()
{
  if (verbose)
    G4cout << "====>$MyDetectorConstruction$::$MyDetectorConstruction$()" << G4endl;

  fStepLimit = 0;
  for (int i = 0; i < SIZE; i++)
    fDetPar[i] = new MyDetectorParameters();
  for (int i = 0; i < SIZE; i++)
    fSolid[i] = 0;
  for (int i = 0; i < SIZE; i++)
    fLogic[i] = 0;
  for (int i = 0; i < SIZE; i++)
    fPhysc[i] = 0;

  fDetectorMessenger = new $MyDetectorMessenger$(this);

$detSrcIni$

  //DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$MyDetectorConstruction$::~$MyDetectorConstruction$()
{
  delete fDetectorMessenger;
  delete fStepLimit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume *$MyDetectorConstruction$::Construct()
{
  if (verbose)
    G4cout << "====>$MyDetectorConstruction$::Construct()" << G4endl;

  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume *$MyDetectorConstruction$::DefineVolumes()
{
  if (verbose)
    G4cout << "====>G4VPhysicalVolume* MyDetectorConstruction::DefineVolumes()" << G4endl;

  for (int i = 0; i < 100; i++)
  {
    if (fPhysc[i] != NULL)
      delete fPhysc[i];
    if (fLogic[i] != NULL)
      delete fLogic[i];
    if (fSolid[i] != NULL)
      delete fSolid[i];
  }

  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // Define volume

$detSrcVol$

$detSrcVis$

  return fPhysc[WORLD];;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyDetectorConstruction$::Update()
{
  G4RunManager::GetRunManager()->ReinitializeGeometry();
  G4RunManager::GetRunManager()->DefineWorldVolume(DefineVolumes());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyDetectorConstruction$::SetMaterial(int id, G4String materialName)
{
  if (verbose)
    G4cout << "====>void $MyDetectorConstruction$::SetMaterial(int id, G4String materialName)" << G4endl;

  // search the material by its name, or build it from nist data base
  G4Material *pttoMaterial = G4NistManager::Instance()->FindOrBuildMaterial(materialName);

  if (pttoMaterial && fDetPar[id]->Material != pttoMaterial)
  {
    fDetPar[id]->Matt = materialName;
    fDetPar[id]->Material = pttoMaterial;
    if (fLogic[id])
      fLogic[id]->SetMaterial(fDetPar[id]->Material);
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......