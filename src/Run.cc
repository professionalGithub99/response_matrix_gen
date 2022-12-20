/// \file Run.cc
/// \brief Implementation of the Run class

#include "Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Run::Run()
: G4Run()
{
  ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Run::~Run()
{}

void Run::RecordEvent(const G4Event* evt)
{
  //G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  //if(HCE)
  //{
    // This part of the code could be replaced to any kind of access
    // to hits collections and scores

  //}
  G4Run::RecordEvent(evt);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Run::Merge(const G4Run* run)
{

}
