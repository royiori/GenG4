#ifndef $MyPrimaryGeneratorMessenger$_h
#define $MyPrimaryGeneratorMessenger$_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADouble;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class $MyPrimaryGeneratorAction$;

//-------------------------------
// $MyPrimaryGeneratorMessenger$ class that defines commands for $MyPrimaryGeneratorAction$.
class $MyPrimaryGeneratorMessenger$ : public G4UImessenger
{
  public:
    $MyPrimaryGeneratorMessenger$($MyPrimaryGeneratorAction$ *);
    ~$MyPrimaryGeneratorMessenger$();

    virtual void SetNewValue(G4UIcommand *, G4String);

  private:
    $MyPrimaryGeneratorAction$ *fAction;

    G4UIdirectory *fGunDir;

$gunMesIniDef$

  G4UIcmdWithAString* fRootFileCmd;
  G4UIcmdWithAString* fTxtFileCmd;
  G4UIcmdWithAString* fProgFileCmd; 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
