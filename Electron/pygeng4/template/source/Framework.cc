
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4VModularPhysicsList.hh"
#include "G4StepLimiterPhysics.hh"
#include "Randomize.hh"

#include "$MyActionInitialization$.hh"
#include "$MyDetectorConstruction$.hh"
#include "$MyPhysics$.hh"

int verbose = $Verbose$;

int main(int argc, char **argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive *ui = 0;
  if (argc == 1)
  {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::$RandomEng$);

  // Construct the default run manager
  G4RunManager *runManager = new G4RunManager;

  // Set mandatory initialization classes
  //
  // Detector construction
  $MyDetectorConstruction$ *detector = new $MyDetectorConstruction$;
  runManager->SetUserInitialization(detector);

  // Physics list
  G4VModularPhysicsList *physicsList = new $MyPhysics$;
  physicsList->SetVerboseLevel(1);
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());

  runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserInitialization(new MyActionInitialization());

  // Initialize visualization
  //
  G4VisManager *visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if (!ui)
  {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }
  else
  {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  delete visManager;
  delete runManager;
}