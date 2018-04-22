
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Verbose.hh"
#include "Randomize.hh"

#include "$MyPrimaryGeneratorAction$.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$MyPrimaryGeneratorAction$::$MyPrimaryGeneratorAction$()
    : G4VUserPrimaryGeneratorAction() 
{
  if (verbose)
    G4cout << "====>$MyPrimaryGeneratorAction$::$MyPrimaryGeneratorAction$()" << G4endl;

$gunSrcIni$

  //create a messenger for this class
  fGunMessenger = new MyPrimaryGeneratorMessenger(this);

  fRootFileName = G4String("./root/tmp.root");
  fTxtFileName  = G4String("./gif/tmp.txt");
  fProgFileName = G4String("./gif/progress.txt");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$MyPrimaryGeneratorAction$::~$MyPrimaryGeneratorAction$()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyPrimaryGeneratorAction$::GeneratePrimaries(G4Event *anEvent)
{
  if (verbose)
    G4cout << "====>$MyPrimaryGeneratorAction$::GeneratePrimaries()" << G4endl;

$gunSrcAct$
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......