
#ifndef $SDClass$_hh
#define $SDClass$_hh 1

#include "G4VSensitiveDetector.hh"
#include "$HitClass$.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class $SDClass$ : public G4VSensitiveDetector
{
  public:
    $SDClass$(G4String);
    virtual ~$SDClass$();

      virtual void Initialize(G4HCofThisEvent* HCE);
      virtual G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist);
      virtual void EndOfEvent(G4HCofThisEvent* HCE);
      virtual void clear();
      virtual void DrawAll();
      virtual void PrintAll();
      
  private:
    $HitClass$Collection*     fHitsCollection;
};

#endif