
#ifndef $HitClass$_h
#define $HitClass$_h

#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4Step.hh"
#include "G4VHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class $HitClass$ : public G4VHit
{
  public:
    $HitClass$();
    ~$HitClass$();
    $HitClass$(const $HitClass$ &);
    $HitClass$(const G4Step *);

    const $HitClass$ &operator=(const $HitClass$ &);
    int operator==(const $HitClass$ &) const;
    inline void *operator new(size_t);
    inline void operator delete(void *);

    void Init();

    inline G4int GetPDGID() { return pdgID; }
    inline G4int GetProducerID() { return prodID; }
    inline G4int GetTrackID() { return trackID; }
    inline G4double GetEdep() { return Edep; }
    inline G4double GetStepLength() { return stepL; }
    inline G4ThreeVector GetPostPosition() { return postPos; }
    inline G4ThreeVector GetPrePosition() { return prePos; }
    inline G4bool IsFirstDeposit() { return isFirstDeposit; }

    inline void SetPDGID(G4int id) { pdgID = id; }
    inline void SetProducerID(G4int id) { prodID = id; }
    inline void SetTrackID(G4int id) { trackID = id; }
    inline void SetEdep(G4double edep) { Edep = edep; }
    inline void SetStepLength(G4double length) { stepL = length; }
    inline void SetPostPosition(G4ThreeVector pos) { postPos = pos; }
    inline void SetPrePosition(G4ThreeVector pos) { prePos = pos; }
    inline void SetFirstDepositFlag() { isFirstDeposit = true; }

  private:
    G4int pdgID;
    G4int prodID;
    G4int trackID;
    G4double Edep;
    G4double stepL;
    G4ThreeVector prePos;
    G4ThreeVector postPos;
    G4bool isFirstDeposit;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

typedef G4THitsCollection<$HitClass$> $HitClass$Collection;

extern G4ThreadLocal G4Allocator<$HitClass$> *$HitClass$Allocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void *$HitClass$::operator new(size_t)
{
    if (!$HitClass$Allocator)
        $HitClass$Allocator = new G4Allocator<$HitClass$>;
    return (void *)$HitClass$Allocator->MallocSingle();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void $HitClass$::operator delete(void *aHit)
{
    $HitClass$Allocator->FreeSingle(($HitClass$ *)aHit);
}

#endif
