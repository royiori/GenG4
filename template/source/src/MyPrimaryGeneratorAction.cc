
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Verbose.hh"
#include "Randomize.hh"

#include "$MyPrimaryGeneratorAction$.hh"

$MyPrimaryGeneratorAction$::$MyPrimaryGeneratorAction$()
    : G4VUserPrimaryGeneratorAction() 
{
  if (verbose)
    G4cout << "====>$MyPrimaryGeneratorAction$::$MyPrimaryGeneratorAction$()" << G4endl;

  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic

  G4ParticleDefinition *particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("proton");

  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  fParticleGun->SetParticleEnergy(3.0 * GeV);
}

$MyPrimaryGeneratorAction$::~$MyPrimaryGeneratorAction$()
{
  delete fParticleGun;
}

void $MyPrimaryGeneratorAction$::GeneratePrimaries(G4Event *anEvent)
{
  if (verbose)
    G4cout << "====>$MyPrimaryGeneratorAction$::GeneratePrimaries()" << G4endl;

  // This function is called at the begining of event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume
  // from G4LogicalVolumeStore.
  /*
  G4double worldZHalfLength = 0;
  G4LogicalVolume* worldLV
    = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
  G4Box* worldBox = NULL;
  if ( worldLV ) worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
  if ( worldBox ) worldZHalfLength = worldBox->GetZHalfLength();
  else  {
    G4cerr << "World volume of box not found." << G4endl;
    G4cerr << "Perhaps you have changed geometry." << G4endl;
    G4cerr << "The gun will be place in the center." << G4endl;
  }

  fParticleGun->SetParticlePosition(G4ThreeVector(0.4, 1.2, 0));//-worldZHalfLength));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));

  fParticleGun->GeneratePrimaryVertex(anEvent);
*/
}