#ifndef $MyPrimaryGeneratorAction$_h
#define $MyPrimaryGeneratorAction$_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class $MyPrimaryGeneratorAction$ : public G4VUserPrimaryGeneratorAction
{
public:
  $MyPrimaryGeneratorAction$();
  virtual ~$MyPrimaryGeneratorAction$();

  virtual void GeneratePrimaries(G4Event *);

$gunIncFunc$

};

#endif