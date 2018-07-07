#ifndef $MyPrimaryGeneratorAction$_h
#define $MyPrimaryGeneratorAction$_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

#include "$MyPrimaryGeneratorMessenger$.hh"

class $MyPrimaryGeneratorAction$ : public G4VUserPrimaryGeneratorAction
{
public:
  $MyPrimaryGeneratorAction$();
  virtual ~$MyPrimaryGeneratorAction$();

  virtual void GeneratePrimaries(G4Event *);

  $MyPrimaryGeneratorMessenger$ *fGunMessenger;

$gunIncFunc$

  G4String fRootFile;
  G4String fTxtFile;
  G4String fProgFile;

};

#endif