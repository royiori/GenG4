#ifndef $MyRunAction$_h
#define $MyRunAction$_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class $MyRunAction$ : public G4UserRunAction
{
public:
  $MyRunAction$();
  virtual ~$MyRunAction$();

  virtual void BeginOfRunAction(const G4Run *run);
  virtual void EndOfRunAction(const G4Run *run);
};

#endif