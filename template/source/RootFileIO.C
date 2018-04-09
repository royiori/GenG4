#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include "TKey.h"
#include "iostream"
//*****************************************************************************
// To run this macro in root:
//
// gSystem->Load("/Users/liuqian/Work/work/geant4/Geant4 Framework/v2/debug/libSimEventDict.so");
// .L RootFileIO.C++
// RootFileIO();
//
//*****************************************************************************

#include "SimEvent.h"

void WriteRoot();
void ReadRoot();

TString fFileName("tmp.root");

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
  
  SimEvent* fEvent = 0;
  TTree   * fTree1  = (TTree *)fRootFp->Get("sim");
  fTree1->SetBranchAddress("SimEvent", &fEvent);

  fTree1->GetEntry(0);
  G4cout<<fEvent->GetTime(2)<<G4endl;  

  fRootFp->Close();
}


