#ifndef SimEvent_h
#define SimEvent_h

#include "TVector3.h"
#include "TObject.h"
#include "Verbose.hh"
#include <map>

class SimEvent : public TObject {
//    private:
//
//        // Summary of MC truth info
//        Float_t  fTotalEdep;
//        Float_t  fTotalTrackLength;
//        Float_t  fMaxStoppingPower;
//        Float_t  fMinStoppingPower;
//        Int_t    fPDGID; // parent particle ID
//        Float_t  fEnergy; // True Energy
//        Float_t  fPx; // momentum direction
//        Float_t  fPy; // momentum direction
//        Float_t  fPz; // momentum direction
//
//        //... any more information?....
//
//    public:
//
//        SimEvent() {
//          Clear(); 
//        }
//        ~SimEvent() {}
//
//        void Clear() {
//          fTotalEdep = 0.;
//          fTotalTrackLength = 0.;
//          fMaxStoppingPower = 0.;
//          fMinStoppingPower = 0.;
//          fPDGID = -999;
//          fEnergy = 0.;
//          fPx = 0.;
//          fPy = 0.;
//          fPz = 0.;
//        }
//
//        void SetTrueEnergy(Float_t energy) { fEnergy = energy; }
//        void SetPDGID(Int_t pdgId) { fPDGID = pdgId; }
//        void SetMomentumDir(Float_t px, Float_t py, Float_t pz) { fPx = px; fPy = py; fPz = pz;}
//        void SetMaxStoppingPower(Float_t dEdx) { fMaxStoppingPower = dEdx; }
//        void SetMinStoppingPower(Float_t dEdx) { fMinStoppingPower = dEdx; }
//        void SetTotalDepositEnergy(Float_t totDepE) { fTotalEdep = totDepE; }
//        void SetTotalTrackLength(Float_t trackL) { fTotalTrackLength = trackL; }
//
//        Float_t GetTrueEnergy() { return fEnergy; }
//        Int_t   GetPDGID() { return fPDGID; }
//        TVector3 GetMomentumDir() { return TVector3(fPx, fPy, fPz); }
//        Float_t GetMaxStoppingPower() { return fMaxStoppingPower; }
//        Float_t GetMinStoppingPower() { return fMinStoppingPower; }
//        Float_t GetTotalDepositEnergy() { return fTotalEdep; }
//        Float_t GetTotalTrackLength() { return fTotalTrackLength; }

  public:
    SimEvent() {};
    ~SimEvent(){};

    inline void MyClear();

    void SetTime(int n, Float_t t){ fT[n] = t; }
    Float_t GetTime(int n){ return fT[n]; }
    void SetPos(int n, TVector3 pos){ fPos[n] = pos; }
    TVector3 GetPos(int n){ return fPos[n]; }
    void AddTotalEdep(int n, Float_t edep){ fTotalEdep[n] = edep; }

  private:
    Float_t fT[9];
    Float_t fTotalEdep[9];
    TVector3 fPos[9];

    ClassDef(SimEvent, 1);
};

inline void SimEvent::MyClear()
{
  for(int i=0; i!=9; ++i)
  {
    fT[i] = -1;
    fTotalEdep[i] = 0;
    fPos[i] = TVector3(0, 0, 0);
  }
}
#endif
