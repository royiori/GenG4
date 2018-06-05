
#include "$HitClass$.hh"

G4ThreadLocal G4Allocator<$HitClass$> *$HitClass$Allocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

$HitClass$::$HitClass$()
{
    this->Init();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

$HitClass$::$HitClass$(const $HitClass$ &right) : G4VHit(right)
{
    this->Init();
    pdgID = right.pdgID;
    prodID = right.prodID;
    trackID = right.trackID;
    Edep = right.Edep;
    stepL = right.stepL;
    prePos = right.prePos;
    postPos = right.postPos;
    isFirstDeposit = right.isFirstDeposit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

$HitClass$::$HitClass$(const G4Step *right)
{
    this->Init();
    pdgID = right->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
    prodID = right->GetTrack()->GetParentID();
    trackID = right->GetTrack()->GetTrackID();
    Edep = right->GetTotalEnergyDeposit();
    stepL = right->GetStepLength();
    prePos = right->GetPostStepPoint()->GetPosition();
    postPos = right->GetPreStepPoint()->GetPosition();
    isFirstDeposit = right->IsFirstStepInVolume();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

$HitClass$::~$HitClass$()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

const $HitClass$ &$HitClass$::operator=(const $HitClass$ &right)
{
    this->Init();
    pdgID = right.pdgID;
    prodID = right.prodID;
    trackID = right.trackID;
    Edep = right.Edep;
    stepL = right.stepL;
    prePos = right.prePos;
    postPos = right.postPos;
    isFirstDeposit = right.isFirstDeposit;
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

int $HitClass$::operator==(const $HitClass$ &) const
{
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void $HitClass$::Init()
{
    pdgID = 0;
    prodID = 0;
    trackID = 0;
    Edep = 0.;
    stepL = 0.;
    prePos = G4ThreeVector(0., 0., 0.);
    postPos = G4ThreeVector(0., 0., 0.);
    isFirstDeposit = false;
}
