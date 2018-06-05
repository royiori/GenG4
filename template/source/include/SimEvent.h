#ifndef SimEvent_h
#define SimEvent_h

#include "TVector3.h"
#include "TObject.h"
#include "TMap.h"
#include "TObjString.h"
#include "Verbose.hh"
#include <map>

#include "SimTrack.h"
#include "SimDeposit.h"

class SimEvent : public TObject
{

public:
  SimEvent() { MyClear(); }
  virtual ~SimEvent() {}

  void SetPDGID(int pdgId) { fPDGID = pdgId; }
  void SetTrueEnergy(double energy) { fEnergy0 = energy; }
  void SetMomentumX(double px) { fPx0 = px; }
  void SetMomentumY(double py) { fPy0 = py; }
  void SetMomentumZ(double pz) { fPz0 = pz; }

  int GetPDGID() { return fPDGID; }
  double GetTrueEnergy() { return fEnergy0; }
  TVector3 GetMomentumDir() { return TVector3(fPx0, fPy0, fPz0); }

public:
  inline void MyClear();

//$DataIncGlobalFunc$

  // SD Functions
$DataIncSDFunc$ 

private:
  // global variables
  int fPDGID;
  double fEnergy0;
  double fPx0;
  double fPy0;
  double fPz0;

//$DataIncGlobalDef$

  // SD variables
$DataIncSDDef$



  ClassDef(SimEvent, 1)
};

inline void SimEvent::MyClear()
{
  fPDGID = -999;
  fEnergy0 = 0.;
  fPx0 = 0.;
  fPy0 = 0.;
  fPz0 = 0.;
$DataIncSDClear$
}
#endif
