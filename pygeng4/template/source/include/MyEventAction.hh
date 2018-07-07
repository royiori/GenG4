#ifndef $MyEventAction$_h
#define $MyEventAction$_h 1

#include "G4UserEventAction.hh"

class $MyEventAction$ : public G4UserEventAction
{
public:
  $MyEventAction$();
  virtual ~$MyEventAction$();

  virtual void BeginOfEventAction(const G4Event *);
  virtual void EndOfEventAction(const G4Event *);

private:
};

#endif
