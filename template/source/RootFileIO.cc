// ********************************************************************
//
#include "TROOT.h"
#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"
#include "TKey.h"
//
#include "SimEvent.h"
#include "G4ios.hh"

void WriteRoot();
void ReadRoot();

TString fFileName;

int main(int argc, char **argv)
{
  fFileName = TString("tmp.root");

  // initialize ROOT
  TSystem ts;
  gSystem->Load("libSimEventDict");

  if (argc < 2)
    G4cout << "Missing name of the file to read! Read " << fFileName << " instead." << G4endl;
  else
    fFileName = TString(argv[1]);

  ReadRoot();

  return 1;
}
//
//  TFile fo(argv[1]);
//
//  std::vector<ExP01TrackerHit*>* hits;
//  fo.GetListOfKeys()->Print();
//
//  TIter next(fo.GetListOfKeys());
//  TKey *key;
//  //double tot_en;
//  while ((key=(TKey*)next()))
//  {
//    fo.GetObject(key->GetName(), hits);
//
//    //tot_en = 0;
//    G4cout << "Collection: " << key->GetName() << G4endl;
//    G4cout << "Number of hits: " << hits->size() << G4endl;
//    for (size_t i=0;i!=hits->size();i++)
//    {
//      (*hits)[i]->Print();
//    }
//  }

void WriteRoot()
{
  G4cout << "---> Write to " << fFileName << " root file." << G4endl;

  TFile *fRootFp = new TFile(fFileName, "recreate");

  SimEvent *fEvent = new SimEvent();
  TTree *fTree1 = new TTree("sim", "Tree of GasTPC events");

  fTree1->Branch("SimEvent", "SimEvent", &fEvent, 32000, 99);
  //for(int i=0; i<9; i++) fEvent->SetTime(i, 10*i);

  fTree1->Fill();
  fEvent->Clear();

  fRootFp->Write();
  fRootFp->Close();
}

void ReadRoot()
{
  G4cout << "---> Reading from " << fFileName << " root file." << G4endl;

  TFile *fRootFp = new TFile(fFileName);
  if (!fRootFp->IsOpen())
  {
    G4cout << "---> Can't open " << fFileName << "." << G4endl;
    return;
  }

  SimEvent *fEvent = 0;
  TTree *fTree1 = (TTree *)fRootFp->Get("sim");
  fTree1->SetBranchAddress("SimEvent", &fEvent);

  G4cout<<"> There are "<<fTree1->GetEntries()<<" events stored."<<G4endl;
  for(int i=0; i<fTree1->GetEntries(); i++)
  {
    G4cout<<"> No. "<<i<<" event: "<<G4endl;

    fTree1->GetEntry(i);

    // 1. the global information of the fEvent
    G4cout<<">  PdgID : "<<fEvent->GetPDGID()<<G4endl;
    G4cout<<">  Energy: "<<fEvent->GetTrueEnergy()<<G4endl;
    G4cout<<">  Moment: ("<<fEvent->GetMomentumDir().x()<<", "
                          <<fEvent->GetMomentumDir().y()<<", "
                          <<fEvent->GetMomentumDir().z()<<") "<<G4endl;

    TMap *trkMap1 = fEvent->GetGasSDTrackMap();
    TMap *depMap1 = fEvent->GetGasSDDepositMap();

    TMap *trkMap2 = fEvent->GetWindowSDTrackMap();
    TMap *depMap2 = fEvent->GetWindowSDDepositMap();

    // 1. read tracks information
    G4cout<<">-----Tracks in Gas : "<<trkMap1->GetSize()<<" tracks."<<G4endl;

    TObject* tempObj=0;
    TIterator *it = trkMap1->MakeIterator();
    while((tempObj = it->Next()))
    {
      TObjString *obj = dynamic_cast<TObjString *>(tempObj);
      SimTrack* trk = dynamic_cast<SimTrack *>(trkMap1->GetValue(obj));
      G4cout<<": \t-------------------------"<<G4endl;
      G4cout<<": \t-PdgID :"<<trk->GetPDGID()<<G4endl;
      G4cout<<": \t TrkID :"<<trk->GetTrackID()<<G4endl;
      G4cout<<": \t Mass  :"<<trk->GetInitMass()<<G4endl;
      G4cout<<": \t Ek    :"<<trk->GetInitEk()<<G4endl;
      G4cout<<": \t Edep  :"<<trk->GetEdep()<<G4endl;
      G4cout<<": \t IniPx :"<<trk->GetInitPx()<<G4endl;
      G4cout<<": \t IniPy :"<<trk->GetInitPy()<<G4endl;
      G4cout<<": \t IniPz :"<<trk->GetInitPz()<<G4endl;
      G4cout<<": \t IniX  :"<<trk->GetInitX()<<G4endl;
      G4cout<<": \t IniY  :"<<trk->GetInitY()<<G4endl;
      G4cout<<": \t IniZ  :"<<trk->GetInitZ()<<G4endl;
      G4cout<<": \t IniT  :"<<trk->GetInitT()<<G4endl;
      G4cout<<": \t ExtPx :"<<trk->GetExitPx()<<G4endl;
      G4cout<<": \t ExtPy :"<<trk->GetExitPy()<<G4endl;
      G4cout<<": \t ExtPz :"<<trk->GetExitPz()<<G4endl;
      G4cout<<": \t ExtX  :"<<trk->GetExitX()<<G4endl;
      G4cout<<": \t ExtY  :"<<trk->GetExitY()<<G4endl;
      G4cout<<": \t ExtZ  :"<<trk->GetExitZ()<<G4endl;
      G4cout<<": \t ExtT  :"<<trk->GetExitT()<<G4endl;
      G4cout<<": \t Length:"<<trk->GetTrackLength()<<G4endl;

      std::vector<Int_t> stepIdx = trk->GetStepIdx();
      G4cout<<": \t-Deposits in this track : "<<stepIdx.size()<<" hits."<<G4endl;
      for(int j=0; j<(int)stepIdx.size(); j++)
      {
        G4cout<<": \t----hit  : "<<j<<G4endl;
        SimDeposit *dep = dynamic_cast<SimDeposit *>(depMap1->GetValue(Form("%d", stepIdx[j])));
        G4cout<<": \t  PdgID  : "<<dep->GetPDGID()<<G4endl;
        G4cout<<": \t  TrkID  : "<<dep->GetTrackID()<<G4endl;
        G4cout<<": \t  ProdID : "<<dep->GetProducerID()<<G4endl;
        G4cout<<": \t  IniPx  : "<<dep->GetPrePx()<<G4endl;
        G4cout<<": \t  IniPy  : "<<dep->GetPrePy()<<G4endl;
        G4cout<<": \t  IniPz  : "<<dep->GetPrePz()<<G4endl;
        G4cout<<": \t  IniX   : "<<dep->GetPreX()<<G4endl;
        G4cout<<": \t  IniY   : "<<dep->GetPreY()<<G4endl;
        G4cout<<": \t  IniZ   : "<<dep->GetPreZ()<<G4endl;
        G4cout<<": \t  IniT   : "<<dep->GetPreT()<<G4endl;
        G4cout<<": \t  ExtPx  : "<<dep->GetPostPx()<<G4endl;
        G4cout<<": \t  ExtPy  : "<<dep->GetPostPy()<<G4endl;
        G4cout<<": \t  ExtPz  : "<<dep->GetPostPz()<<G4endl;
        G4cout<<": \t  ExtX   : "<<dep->GetPostX()<<G4endl;
        G4cout<<": \t  ExtY   : "<<dep->GetPostY()<<G4endl;
        G4cout<<": \t  ExtZ   : "<<dep->GetPostZ()<<G4endl;
        G4cout<<": \t  ExtT   : "<<dep->GetPostT()<<G4endl;
        G4cout<<": \t  Edep   : "<<dep->GetEdep()<<G4endl;
        G4cout<<": \t  Length : "<<dep->GetStepLength()<<G4endl;
      }
    }    
  }

  fRootFp->Close();
}
