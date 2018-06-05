
#include "G4RunManager.hh"
#include "G4Electron.hh"
#include "G4Track.hh"

#include "$MyStackingAction$.hh"
#include "$MyEventAction$.hh"
#include "$MyAnalysisManager$.hh"
#include "SimEvent.h"
#include "Verbose.hh"

$MyStackingAction$::$MyStackingAction$()
    : G4UserStackingAction(), fKillSecondary(0)
{
  if (verbose)
    G4cout << "====>$MyStackingAction$::$MyStackingAction$()" << G4endl;
}

$MyStackingAction$::~$MyStackingAction$()
{
}

G4ClassificationOfNewTrack $MyStackingAction$::ClassifyNewTrack(const G4Track *aTrack)
{
  if (verbose)
    G4cout << "====>$MyStackingAction$::ClassifyNewTrack(const G4Track* aTrack)" << G4endl;

  G4int pdgID    = aTrack->GetDefinition()->GetPDGEncoding();
  G4int trackID  = aTrack->GetTrackID();
  G4double energy= aTrack->GetKineticEnergy();
  G4ThreeVector momDir = aTrack->GetMomentumDirection();

  if(trackID == 1)
  {
    SimEvent *fEvent = $MyAnalysisManager$::GetInstance()->GetSimEvent();
    fEvent->SetPDGID(pdgID);
    fEvent->SetTrueEnergy(energy);
    fEvent->SetMomentumX(momDir.x());
    fEvent->SetMomentumY(momDir.y());
    fEvent->SetMomentumZ(momDir.z());
  }

  return fUrgent;
}
