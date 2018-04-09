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

int main(int argc,char** argv)
{
  fFileName = TString("tmp.root");

  // initialize ROOT
  TSystem ts;
  gSystem->Load("libSimEventDict");
  if(argc<2) G4cout << "Missing name of the file to read! Read " << fFileName << " instead."<< G4endl;
  else fFileName = TString(argv[1]);

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





void RootFileIO()
{

//   WriteRoot();

   ReadRoot();

}


void WriteRoot()
{
  G4cout<<"---> Write to "<<fFileName<<" root file."<<G4endl;

  TFile * fRootFp = new TFile(fFileName, "recreate");

  SimEvent* fEvent = new SimEvent();
  TTree   * fTree1 = new TTree("sim", "Tree of GasTPC events");


  fTree1->Branch("SimEvent", "SimEvent", &fEvent, 32000, 99);
  for(int i=0; i<9; i++) fEvent->SetTime(i, 10*i);

  fTree1->Fill();
  fEvent->Clear();

  fRootFp->Write();
  fRootFp->Close();
}

void ReadRoot()
{
  G4cout<<"---> Read from "<<fFileName<<" root file."<<G4endl;

  TFile * fRootFp = new TFile(fFileName);    
  if(!fRootFp->IsOpen()) {G4cout<<"---> Can't open "<<fFileName<<"."<<G4endl; return;} 

  SimEvent* fEvent = 0;
  TTree   * fTree1  = (TTree *)fRootFp->Get("sim");
  fTree1->SetBranchAddress("SimEvent", &fEvent);

  fTree1->GetEntry(0);
  G4cout<<fEvent->GetTime(2)<<G4endl;  

  fRootFp->Close();
}


