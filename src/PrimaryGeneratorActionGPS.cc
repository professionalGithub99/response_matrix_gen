//
#include "PrimaryGeneratorActionGPS.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4AutoLock.hh"
#include "G4RunManager.hh"

namespace { G4Mutex myHEPPrimGenMutex = G4MUTEX_INITIALIZER; }


PrimaryGeneratorActionGPS::PrimaryGeneratorActionGPS()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
  // Use the GPS to generate primary particles,                                   
  // Particle type, energy position, direction are specified in the               
  // the macro file primary.mac  
  fParticleGun = new G4GeneralParticleSource();
}

PrimaryGeneratorActionGPS::~PrimaryGeneratorActionGPS()
{
  delete fParticleGun;
}

void PrimaryGeneratorActionGPS::GeneratePrimaries(G4Event* anEvent)
{
  G4AutoLock lock(&myHEPPrimGenMutex);
  // send energy to Run Action to fill
  RunAction* myRunAction
  = (RunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());

  fParticleGun->GeneratePrimaryVertex(anEvent);
  // send energy value for histogramming
  auto en = fParticleGun->GetParticleEnergy();
  //cout << en << endl;
  myRunAction->SetSourceParticleEnergy(en);
}

