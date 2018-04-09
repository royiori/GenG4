#ifndef $MyActionInitialization$_h
#define $MyActionInitialization$_h 1

#include "G4VUserActionInitialization.hh"

class $MyActionInitialization$ : public G4VUserActionInitialization
{
public:
  $MyActionInitialization$();
  virtual ~$MyActionInitialization$();

  virtual void BuildForMaster() const;
  virtual void Build() const;

private:
};

#endif
