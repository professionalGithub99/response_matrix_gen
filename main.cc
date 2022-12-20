#include <fstream>
#include <math.h>
#include "G4ios.hh"
#include <sys/time.h> 
// package includes
//
#include "G4RunManager.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "ActionInitialization.hh"
// geant4 includes
#include "G4ios.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
// Physics lists
#include "QGSP_BIC_HP.hh"
#include "QGSP_BERT_HP.hh"
#include "QGSP_INCLXX_HP.hh"
#include "QGSP_BIC_HP.hh"
#include "QGSP_BERT_HP.hh"
#include "QGSP_INCLXX_HP.hh"
#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

#include <TROOT.h>
//// ***************************
// This program can take a series of command line arguements.
// (0) executable
// (1) energy of particle (and also an extension for the output file name) 
//     in MeV
// (2) path to macro
void help();
//------------------------------------------------------------------------------
int main(int argc,char** argv)
{
  gROOT->GetInterpreter();
  // ***************************************************************
  // Detect interactive mode (if no arguments) and define UI session
  // ***************************************************************
  //
  double particleEnergy;
  G4UIExecutive* ui = 0;
  if ( argc == 1 )
  {
    ui = new G4UIExecutive(argc, argv);
    particleEnergy = .1;
  }

  if(argc == 3)
  {
    //oFN = argv[1];
    particleEnergy = atof(argv[1]);
    std::cout << "particle energy: " << particleEnergy << std::endl;
  }
  // Choose the Random engine
  //G4Random::setTheEngine(new CLHEP::RanecuEngine);
  // Construct the default run manager
  // for single processor
  //G4RunManager* runManager = new G4RunManager;
  G4int nThreads = 1;
  #ifdef G4MULTITHREADED
    auto runManager = new G4MTRunManager;
    if ( nThreads > 0 )
    {
      runManager->SetNumberOfThreads(nThreads);
    }
  #else
    auto runManager = new G4RunManager;
  #endif
  // Set mandatory initialization classes
  // ********************
  // Detector construction
  runManager->SetUserInitialization(new DetectorConstruction());
  // Physics list
  G4VModularPhysicsList* physicsList = new QGSP_BERT_HP;
  //G4VModularPhysicsList* physicsList = new QBBC;
  physicsList->RegisterPhysics(new G4RadioactiveDecayPhysics());

  physicsList->SetVerboseLevel(1);
  //physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
  //G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  //physicsList->RegisterPhysics(opticalPhysics);
  runManager->SetUserInitialization(physicsList);
  //runManager->SetUserInitialization(new PhysicsList);
  std::cout << "physics set!!!\n";
  // User action initialization
  auto ai = new ActionInitialization();
  std::cout << "action initialized!!!\n";
  ai->SetParticleEnergy(particleEnergy);
  if(argc == 3 ) ai->SetOutFileName(argv[1]);
  runManager->SetUserInitialization(ai);
  std::cout << "user initialized!!!\n";
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  // Process macro or start UI session
  //
  if ( ! ui ){
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[2];
    UImanager->ApplyCommand(command+fileName);
  }
  else{
    // interactive mode
    std::cout << "entering interactive mode\n";
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  std::cout << "ending main program\n";
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !
  delete visManager;
  delete runManager;
}

void help()
{
}
