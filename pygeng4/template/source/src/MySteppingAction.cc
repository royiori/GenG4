
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "Verbose.hh"

#include "$MySteppingAction$.hh"
#include "$MyEventAction$.hh"
#include "$MyDetectorConstruction$.hh"
#include "$MyAnalysisManager$.hh"

$MySteppingAction$::$MySteppingAction$()
    : G4UserSteppingAction()
{
  if (verbose)
    G4cout << "====>$MySteppingAction$::$MySteppingAction$()" << G4endl;
}

$MySteppingAction$::~$MySteppingAction$()
{
}

void $MySteppingAction$::UserSteppingAction(const G4Step *)
{
  if (verbose)
    G4cout << "====>$MySteppingAction$::UserSteppingAction()" << G4endl;

  //SimEvent *fEvt = MyAnalysisManager::GetInstance()->GetSimEvent();
}
