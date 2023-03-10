/// \file RunAction.cc
/// \brief Implementation of the RunAction class

#include "RunAction.hh"
#include "EventAction.hh"
#include "Analysis.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "TotalHit.hh"
#include "Run.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4AnalysisManager.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <algorithm>
#include <iomanip>
#include <sstream>

#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"

#include <iostream>
#include <string>
#include <sstream>

RunAction::RunAction(std::string fN)
: G4UserRunAction()
{
  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in Analysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Default settings
  analysisManager->SetNtupleMerging(true);
  // Note: merging ntuples is available only with Root output
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName(fN);
  // ***********************
  // Book histograms, ntuple
  // **********************
  int nBins   = 12000;
  double endR = 30;
  // Creating 1D histograms
  analysisManager
    ->CreateH1("Det0_src",";Energy (MeV);Counts",nBins,0,endR); // h1 Id = 0
  analysisManager
    ->CreateH1("Det0_gam_lo",";Energy (MeV);Counts",nBins,0,endR); // h1 Id = 1
  analysisManager
    ->CreateH1("Det0_gam_smear",";Energy (MeV);Counts",nBins,0,endR); //h1 Id = 3
  analysisManager
    ->CreateH1("Det0_gam_scat",";Energy (MeV);Counts",nBins,0,endR); // h1 Id = 4 
  analysisManager
    ->CreateH1("Det0_neu_eDep",";Energy (MeV);Counts",nBins,0,endR);  //h1 Id = 5
  analysisManager
    ->CreateH1("Det0_neu_lo",";Energy (MeV);Counts",nBins,0,endR);  //h1 Id = 6
  analysisManager
    ->CreateH1("Det0_neu_smear",";Energy (MeV);Counts",nBins,0,endR);  //h1 Id = 7
                                                                    
  /*analysisManager
    ->CreateH1("Det0_eDep_neu",";Energy (MeV);Counts",nBins,0,endR); // h1 Id = 3
  analysisManager
    ->CreateH1("Det0_eDep_gam",";Energy (MeV);Counts",nBins,0,endR); // h1 Id = 4
  analysisManager
    ->CreateH1("Det0_eDep_deu",";Energy (MeV);Counts",nBins,0,endR); // h1 Id = 5 sub_eDep_deu_neu
  */
  analysisManager->CreateNtuple("events", "information per event");
  analysisManager->CreateNtupleIColumn("eventID");   // 0
  analysisManager->CreateNtupleDColumn("sourceEn");  // 1 source particle energy
  analysisManager->CreateNtupleDColumn("edep");      // 2
  analysisManager->CreateNtupleDColumn("lo_tot");    // 3
  analysisManager->CreateNtupleDColumn("lo_p");      // 4 LO from proton
  analysisManager->CreateNtupleDColumn("lo_p_smear");// 5 smeared LO from proton
  analysisManager->CreateNtupleDColumn("lo_e");      // 6 LO from electrons
  analysisManager->FinishNtuple();

  analysisManager->CreateNtuple("ptracks", "information per proton track");
  analysisManager->CreateNtupleIColumn("eventID");
  analysisManager->CreateNtupleDColumn("edep");
  analysisManager->CreateNtupleDColumn("lo");
  analysisManager->FinishNtuple();
}

RunAction::~RunAction()
{
  ;
}

G4Run* RunAction::GenerateRun()
{
  return new Run;
}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  // The default file name is set in RunAction::RunAction(),
  // it can be overwritten in a macro
  analysisManager->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  G4cout << "You are going to write the root file" << G4endl;
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

  if (IsMaster()) G4cout << "\n-----------End of Global Run----------------\n";
  else{           G4cout << "\n-----------End of Local Run-----------------\n";}
}
