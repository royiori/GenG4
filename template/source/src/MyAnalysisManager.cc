
#include "$MyAnalysisManager$.hh"
#include "SimEvent.h"
#include "Verbose.hh"

ClassImp(SimEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$MyAnalysisManager$* $MyAnalysisManager$::fInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$MyAnalysisManager$::$MyAnalysisManager$()
{
   fFileName = TString("tmp.root");
   fRootFp = NULL;
   fTree   = NULL;
   fEvent  = NULL;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyAnalysisManager$::BeginOfRunAction()
{
  fRootFp = new TFile(fFileName, "recreate");
  if (!fRootFp) {
    G4cout << "\n--->$MyAnalysisManager$::BeginOfRunAction(): "<< "cannot open " << fFileName << G4endl;
    return;
  }

  fEvent = new SimEvent();
  fTree  = new TTree("sim", "Tree of GasTPC events");
  fTree->Branch("SimEvent", "SimEvent", &fEvent, 32000, 99);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyAnalysisManager$::EndOfRunAction()
{
  if(verbose) {G4cout << "\n--->$MyAnalysisManager$::EndOfRunAction()" << G4endl; }
  if(!fRootFp) {
    G4cout << "\n--->$MyAnalysisManager$::EndOfRunAction(): "<< "cannot open " << fFileName << G4endl;
    return;
  }
  fRootFp->Write();
  fRootFp->Close();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyAnalysisManager$::BeginOfEventAction(const G4Event*)
{
  if(verbose) {G4cout << "\n--->$MyAnalysisManager$::BeginOfEventAction()" << G4endl; }
  fEvent->MyClear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyAnalysisManager$::EndOfEventAction(const G4Event*)
{
  if(verbose) {G4cout << "\n--->$MyAnalysisManager$::EndOfEventAction()" << G4endl; }

//  // create ROOT data objects
//  if(col) {
//    int n_hit = col->entries(); // number of steps
//
//    Float_t totEdep = 0., totTrackL = 0.;
//    Float_t max_dEdx = 0., min_dEdx = 1.e5;
//    Float_t Etrue = 0.;
//
//    for(int i=0; i<n_hit; ++i) {
//      // create new hit in the gas tpc
//      Int_t prodID             = (*col)[i]->GetProducerID();
//      Int_t trackID            = (*col)[i]->GetTrackID();
//      Int_t pdgID              = (*col)[i]->GetPDGID();
//      Double_t Edep            = (*col)[i]->GetEdep();
//      Double_t length          = (*col)[i]->GetStepLength();
//      G4ThreeVector prePos     = (*col)[i]->GetPrePosition();
//      G4ThreeVector postPos    = (*col)[i]->GetPostPosition();
//      G4bool        isFirstDep = (*col)[i]->IsFirstDeposit();
//
//      SimDeposit* aDep = new SimDeposit();
//      aDep->SetPreX(prePos.x());
//      aDep->SetPreY(prePos.y());
//      aDep->SetPreZ(prePos.z());
//      aDep->SetPostX(postPos.x());
//      aDep->SetPostY(postPos.y());
//      aDep->SetPostZ(postPos.z());
//      aDep->SetStepLength(length);
//      aDep->SetEdep(Edep);
//      aDep->SetTrackID(trackID);
//      aDep->SetPDGID(pdgID);
//      aDep->SetProducerID(prodID);
//      aDep->SetFirstDeposit( isFirstDep );
//
//
//      // add the MC deposit into the SimEvent
//      fEvent->addDeposit( trackID, aDep );
//
//      // Summary information: total track length, mean dE/dx,
//      // max dE/dx, min dE/dx, total energy deposit, true energy
//      //if( prodID==0 ) { 
//      //  G4cout << "Edep, length, prePos, postPos: "
//      //         << Edep << ", " << length << ", " << prePos 
//      //         << ", " << postPos << G4endl;
//
//      //  // if this step is the first step
//      //  if( isFirstDep ) {
//      //    G4cout << "first step: Edep, length, prePos, postPos: "
//      //           << Edep << ", " << length << ", " << prePos 
//      //           << ", " << postPos << G4endl;
//      //  }
//      //}
//      totEdep += Edep;
//      totTrackL += length;
//      if( max_dEdx < Edep/length ) max_dEdx = Edep/length;
//      if( min_dEdx > Edep/length ) min_dEdx = Edep/length;
//
//    }
//
//    fEvent->SetMaxStoppingPower(max_dEdx);
//    fEvent->SetMinStoppingPower(min_dEdx);
//    fEvent->SetTotalDepositEnergy(totEdep);
//    fEvent->SetTotalTrackLength(totTrackL);
//  }
//

 
  for(int i=0; i<9; i++) fEvent->SetTime(i, i*10);
  // Fill tree
  fTree->Fill();
  fEvent->MyClear();
}

