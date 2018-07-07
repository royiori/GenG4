#ifndef MyAnalysisManager_h
#define MyAnalysisManager_h 1

//#include "G4RunManager.hh"
//#include "G4UnitsTable.hh"
//#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
//#include <iomanip>
#include "g4root.hh"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"

class SimEvent;

class MyAnalysisManager
{
   public:
     static MyAnalysisManager* GetInstance(){
       if(MyAnalysisManager::fInstance == NULL) MyAnalysisManager::fInstance = new MyAnalysisManager();
       return MyAnalysisManager::fInstance;
     }

      MyAnalysisManager();
      ~MyAnalysisManager();

      void BeginOfEventAction(const G4Event* evt);
      void EndOfEventAction(const G4Event* evt);

      void BeginOfRunAction();
      void EndOfRunAction();

      SimEvent* GetSimEvent() { return fEvent; }

   private:
      G4String fFileName;

      FILE * outfile;
      TFile* fRootFp;
      TTree* fTree;

      SimEvent* fEvent;

      static MyAnalysisManager* fInstance;

   public:
      inline void SetFileName(G4String name) {fFileName = name;}

};

#endif
