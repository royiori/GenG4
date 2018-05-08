#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "Verbose.hh"

#include "$MyPrimaryGeneratorMessenger$.hh"
#include "$MyPrimaryGeneratorAction$.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$MyPrimaryGeneratorMessenger$::$MyPrimaryGeneratorMessenger$($MyPrimaryGeneratorAction$ *Gun)
    : G4UImessenger(),
      fAction(Gun)
{
    if (verbose)
        G4cout << "====>$MyPrimaryGeneratorMessenger$::$MyPrimaryGeneratorMessenger$($MyPrimaryGeneratorAction$ *Gun)" << G4endl;

    fGunDir = new G4UIdirectory("/MySimulation/gun/");
    fGunDir->SetGuidance("gun control");

$gunMesSrcDef$ 

    fRootFileCmd = new G4UIcmdWithAString("/MySimulation/gun/setRootName", this);
    fRootFileCmd->SetGuidance("set name for the root file");

    fTxtFileCmd = new G4UIcmdWithAString("/MySimulation/gun/setTxtName", this);
    fTxtFileCmd->SetGuidance("set name for the txt file");

    fProgFileCmd = new G4UIcmdWithAString("/MySimulation/gun/setProgName", this);
    fProgFileCmd->SetGuidance("set name for the progress file");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$MyPrimaryGeneratorMessenger$::~$MyPrimaryGeneratorMessenger$()
{

$gunMesSrcDel$

    delete fRootFileCmd;
    delete fProgFileCmd;
    delete fTxtFileCmd;
    delete fGunDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyPrimaryGeneratorMessenger$::SetNewValue(G4UIcommand *command,
                                              G4String newValue)
{
    if (verbose)
        G4cout << "void $MyPrimaryGeneratorMessenger$::SetNewValue(G4UIcommand* command,G4String newValue)" << G4endl;

$gunMesSrcFunc$

    if (command == fRootFileCmd)
        fAction->SetRootFileName(newValue);
    if (command == fProgFileCmd)
        fAction->SetProgFileName(newValue);
    if (command == fTxtFileCmd)
        fAction->SetTxtFileName(newValue);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
