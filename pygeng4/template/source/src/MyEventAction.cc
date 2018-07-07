
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "Verbose.hh"

#include "$MyRunAction$.hh"
#include "$MyEventAction$.hh"
#include "$MyAnalysisManager$.hh"

$MyEventAction$::$MyEventAction$()
    : G4UserEventAction()
{
  if (verbose)
    G4cout << "====>$MyEventAction$::$MyEventAction$()" << G4endl;
}

$MyEventAction$::~$MyEventAction$()
{
}

void $MyEventAction$::BeginOfEventAction(const G4Event *evt)
{
  if (verbose)
    G4cout << "====>$MyEventAction$::BeginOfEventAction()" << G4endl;
  $MyAnalysisManager$::GetInstance()->BeginOfEventAction(evt);
}

void $MyEventAction$::EndOfEventAction(const G4Event *evt)
{
  if (verbose)
    G4cout << "====>$MyEventAction$::EndOfEventAction()" << G4endl;
  $MyAnalysisManager$::GetInstance()->EndOfEventAction(evt);
}
