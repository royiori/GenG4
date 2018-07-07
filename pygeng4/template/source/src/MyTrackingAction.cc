
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "Verbose.hh"

#include "$MyTrackingAction$.hh"
#include "$MyAnalysisManager$.hh"

$MyTrackingAction$::$MyTrackingAction$()
    : G4UserTrackingAction()
{
  if (verbose)
    G4cout << "====>$MyTrackingAction$::$MyTrackingAction$()" << G4endl;
}

$MyTrackingAction$::~$MyTrackingAction$()
{
}