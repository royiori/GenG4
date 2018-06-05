
#include "$MyAnalysisManager$.hh"
#include "SimEvent.h"
#include "SimTrack.h"
#include "Verbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$MyAnalysisManager$ *$MyAnalysisManager$::fInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$MyAnalysisManager$::$MyAnalysisManager$()
{
  if (verbose)
    G4cout << "====>$MyAnalysisManager$::$MyAnalysisManager$()" << G4endl;

  fFileName = TString("tmp.root");
  fRootFp = NULL;
  fTree = NULL;
  fEvent = NULL;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyAnalysisManager$::BeginOfRunAction()
{
  if (verbose)
    G4cout << "====>$MyAnalysisManager$::BeginOfRunAction()" << G4endl;

  fRootFp = new TFile(fFileName, "recreate");
  if (!fRootFp)
  {
    G4cout << "\n====>$MyAnalysisManager$::BeginOfRunAction(): "
           << "cannot open " << fFileName << G4endl;
    return;
  }

  fEvent = new SimEvent();
  fTree = new TTree("sim", "Tree of data events");
  fTree->Branch("SimEvent", "SimEvent", &fEvent, 32000, 100);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyAnalysisManager$::EndOfRunAction()
{
  if (verbose)
    G4cout << "====>$MyAnalysisManager$::EndOfRunAction()" << G4endl;
  
  if (!fRootFp)
  {
    G4cout << "\n====>$MyAnalysisManager$::EndOfRunAction(): "
           << "cannot open " << fFileName << G4endl;
    return;
  }

  fRootFp->Write();
  fRootFp->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyAnalysisManager$::BeginOfEventAction(const G4Event *)
{
  if (verbose)
    G4cout << "====>$MyAnalysisManager$::BeginOfEventAction()" << G4endl;
  
  fEvent->MyClear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyAnalysisManager$::EndOfEventAction(const G4Event *)
{
  if (verbose)
    G4cout << "====>$MyAnalysisManager$::EndOfEventAction()" << G4endl;

  // Fill tree
  fTree->Fill();
  fEvent->MyClear();
}
