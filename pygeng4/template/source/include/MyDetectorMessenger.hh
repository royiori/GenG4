#ifndef $MyDetectorMessenger$_h
#define $MyDetectorMessenger$_h

#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADouble;
class $MyDetectorConstruction$;

//-------------------------------
// $MyDetectorMessenger$ class that defines commands for $MyDetectorConstruction$.
class $MyDetectorMessenger$ : public G4UImessenger
{
public:
  $MyDetectorMessenger$($MyDetectorConstruction$ *);
  virtual ~$MyDetectorMessenger$();

  virtual void SetNewValue(G4UIcommand *, G4String);

private:
  $MyDetectorConstruction$ *fDetectorConstruction;

  G4UIdirectory *fMyDirectory;
  G4UIdirectory *fDetDirectory;

$detMesIniDef$

  G4UIcmdWithoutParameter *fUpdateCmd;
};

#endif
