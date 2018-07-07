
#include "$MyActionInitialization$.hh"
#include "$MyPrimaryGeneratorAction$.hh"
#include "$MyRunAction$.hh"
#include "$MyEventAction$.hh"
#include "$MySteppingAction$.hh"
#include "$MyStackingAction$.hh"
#include "$MyTrackingAction$.hh"
#include "Verbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$MyActionInitialization$::$MyActionInitialization$()
    : G4VUserActionInitialization()
{
  if (verbose)
    G4cout << "====>$MyActionInitialization$::$MyActionInitialization$()" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$MyActionInitialization$::~$MyActionInitialization$()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyActionInitialization$::BuildForMaster() const
{
  if (verbose)
    G4cout << "====>$MyActionInitialization$::BuildForMaster()" << G4endl;

  SetUserAction(new $MyRunAction$());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyActionInitialization$::Build() const
{
  if (verbose)
    G4cout << "====>$MyActionInitialization$::Build()" << G4endl;

  SetUserAction(new $MyPrimaryGeneratorAction$());

  SetUserAction(new $MyEventAction$());

  SetUserAction(new $MyRunAction$());

  SetUserAction(new $MySteppingAction$());

  SetUserAction(new $MyStackingAction$());

  SetUserAction(new $MyTrackingAction$());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
