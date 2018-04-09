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

const int NX = 31;
const int NY = 31;
const double XStep = 0.08;
const double YStep = 0.08;

class MyAnalysisManager
{
   public:
     static MyAnalysisManager* GetInstance(){
       if(MyAnalysisManager::fInstance == NULL) MyAnalysisManager::fInstance = new MyAnalysisManager();
       return MyAnalysisManager::fInstance;
     }

      MyAnalysisManager();
      ~MyAnalysisManager();
      //void Book();
      //void Fill(G4int EID,G4int PID,G4int TID,G4double prex,G4double prey,G4double prez,
      //                 G4double postx,G4double posty,G4double postz,G4double Edep,
      //                 G4double Ek);

      void BeginOfEventAction(const G4Event* evt);
      void EndOfEventAction(const G4Event* evt);

      void BeginOfRunAction();
      void EndOfRunAction();

      SimEvent* GetSimEvent() { return fEvent; }

   private:
      G4bool fFactoryOn;
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
