
#include "$SDClass$.hh"
#include "$HitClass$.hh"
#include "SimEvent.h"
#include "SimTrack.h"
#include "$MyAnalysisManager$.hh"

#include "G4TouchableHistory.hh"
#include "G4HCofThisEvent.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "G4LossTableManager.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "Verbose.hh"
#include "g4root.hh"

$SDClass$::$SDClass$(G4String name) : G4VSensitiveDetector(name)
{
  if (verbose)
    G4cout << "====>$SDClass$::$SDClass$(G4String name)" << G4endl;

  collectionName.insert("$SDClass$Collection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$SDClass$::~$SDClass$()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $SDClass$::Initialize(G4HCofThisEvent *)
{
  if (verbose)
    G4cout << "====>$SDClass$::Initialize(G4HCofThisEvent *)" << G4endl;

  fHitsCollection = new $HitClass$Collection(SensitiveDetectorName, collectionName[0]);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4bool $SDClass$::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
  if (verbose)
    G4cout << "====>$SDClass$::ProcessHits(G4Step *aStep, G4TouchableHistory *)" << G4endl;

  G4double dE       = aStep->GetTotalEnergyDeposit();
  G4double stepl    = aStep->GetStepLength();
  G4bool isFirstDep = aStep->IsFirstStepInVolume();
  //G4double edelta = aStep->GetDeltaEnergy();
  //G4double eNonIoniz = aStep->GetNonIonizingEnergyDeposit();

  G4StepPoint *preStepPoint  = aStep->GetPreStepPoint();
  G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
  G4ThreeVector prePos  = preStepPoint->GetPosition();
  G4ThreeVector postPos = postStepPoint->GetPosition();

  G4Track *aTrack = aStep->GetTrack();
  G4int trackID   = aTrack->GetTrackID();
  G4int prodID    = aTrack->GetParentID();
  G4int pdgID     = aTrack->GetDefinition()->GetPDGEncoding();
  G4int StepNo    = aTrack->GetCurrentStepNumber();
  G4ParticleDefinition *particleType = aTrack->GetDefinition();

  if ((dE == 0.) || (stepl == 0.))
    return false;

  if (particleType == G4Gamma::Gamma() && dE > 0)
  {
    // usually dE is 0 for gammas, for the last step of a gamma track,
    // if dE > 0., it is the last step of the gamma track (no new particle is generated),
    // then treat this dE as a 'virtual' electron
    G4LossTableManager *manager = G4LossTableManager::Instance();
    stepl = manager->GetRange(G4Electron::Electron(), dE, aTrack->GetMaterialCutsCouple());
  }

  //------------------------------
  // save hits to the collection
  // so we can save the hits later
  $HitClass$ *SDHit = new $HitClass$(aStep);
  fHitsCollection->insert(SDHit);

  //------------------------------
  // save tracks to the collection
  // if the step is the first step of a track
  if (StepNo == 1)
  {
    aStep->SetFirstStepFlag();

    G4ThreeVector momDir = preStepPoint->GetMomentumDirection();
    G4double Ek = preStepPoint->GetKineticEnergy();

    SimTrack *aSimTrack = $MyAnalysisManager$::GetInstance()->GetSimEvent()->Get$SDClass$Track(trackID);
    aSimTrack->SetPDGID(pdgID);
    aSimTrack->SetInitPx(momDir.x());
    aSimTrack->SetInitPy(momDir.y());
    aSimTrack->SetInitPz(momDir.z());
    aSimTrack->SetInitEk(Ek);
    aSimTrack->SetInitX(prePos.x());
    aSimTrack->SetInitY(prePos.y());
    aSimTrack->SetInitZ(prePos.z());
  }

  //------------------------------
  // Last step of the track
  if (postStepPoint->GetKineticEnergy() == 0.)
  {
    G4ThreeVector momDir = postStepPoint->GetMomentumDirection();

    SimTrack *aSimTrack = $MyAnalysisManager$::GetInstance()->GetSimEvent()->Get$SDClass$Track(trackID);
    aSimTrack->SetExitX(postPos.x());
    aSimTrack->SetExitY(postPos.y());
    aSimTrack->SetExitZ(postPos.z());
    aSimTrack->SetExitPx(momDir.x());
    aSimTrack->SetExitPy(momDir.y());
    aSimTrack->SetExitPz(momDir.z());
  }

  //------------------------------
  // Save the hit to the deposit
  SimDeposit* aDep = new SimDeposit();
  aDep->SetPreX(prePos.x());
  aDep->SetPreY(prePos.y());
  aDep->SetPreZ(prePos.z());
  aDep->SetPostX(postPos.x());
  aDep->SetPostY(postPos.y());
  aDep->SetPostZ(postPos.z());
  aDep->SetStepLength(stepl);
  aDep->SetEdep(dE);
  aDep->SetTrackID(trackID);
  aDep->SetPDGID(pdgID);
  aDep->SetProducerID(prodID);
  aDep->SetFirstDeposit( isFirstDep );

  // add the MC deposit into the SimEvent
  $MyAnalysisManager$::GetInstance()->GetSimEvent()->Add$SDClass$Deposit( trackID, aDep );
  

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void $SDClass$::EndOfEvent(G4HCofThisEvent *HCE)
{
  if (verbose)
    G4cout << "====>$SDClass$::EndOfEvent(G4HCofThisEvent *HCE)" << G4endl;

  static G4int HCID = -1;
  if (HCID < 0)
    HCID = GetCollectionID(0);
  HCE->AddHitsCollection(HCID, fHitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $SDClass$::clear()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $SDClass$::DrawAll()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $SDClass$::PrintAll()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
