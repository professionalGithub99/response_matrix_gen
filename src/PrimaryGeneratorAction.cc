#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomDirection.hh"
#include "G4BosonConstructor.hh"
#include "G4AutoLock.hh"
#include "G4ThreeVector.hh"

#include "Randomize.hh"

namespace { G4Mutex myHEPPrimGenMutex = G4MUTEX_INITIALIZER; }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
PrimaryGeneratorAction::PrimaryGeneratorAction(double partEnergy)
: G4VUserPrimaryGeneratorAction(),
fParticleGun(0)
{
  m_partEnergy = partEnergy;
  G4AutoLock lock(&myHEPPrimGenMutex);
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  auto particleDefinition
  = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
  fParticleGun->SetParticleDefinition(particleDefinition);
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(partEnergy*MeV);
}

//PRIMARY ACTION  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    G4AutoLock lock(&myHEPPrimGenMutex);
    delete fParticleGun;
}

//DEFINE THE PARTICLE, ENERGY, MOMENTUM, AND POSITION - - - - - - - - - - - - - - - - - - - - - - - - -
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4AutoLock lock(&myHEPPrimGenMutex);
  // send energy to Run Action to fill
  RunAction* myRunAction
  = (RunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
  //cout << fParticleGun->GetParticleEnergy() << endl;
  myRunAction->SetSourceParticleEnergy(fParticleGun->GetParticleEnergy());
  
  G4double x, y;
  x = 0, y = 0;
  // *** isotropic
  //auto v = MakeIsotropic();
  //fParticleGun->SetParticleMomentumDirection(v);
  // *** square or circular
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,-1.));
  MakeACircularBeam(x,y);
  // *** General
  fParticleGun->SetParticlePosition(G4ThreeVector(x*cm,y*cm,100*cm));
  // define energy
  //G4double en = GetCfNeutronEnergy();
  fParticleGun->SetParticleEnergy(m_partEnergy*MeV);
  // define an event
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

// The following two functions will give you an x and y. z will be kept
// constant; position is in units of cm.
void PrimaryGeneratorAction::MakeACircularBeam(G4double &x, G4double &y)
{
  // for circular beam
  // need radius of detector
  double radius = (7.303-0.0396)/2*G4UniformRand();
  double rando = G4UniformRand();
  // position of center of detector
  double x1, y1;
  x1 = 0;
  y1 = 0;
  x = x1 + radius * cos (rando*360*deg);
  y = y1 + radius * sin (rando*360*deg);
}

void PrimaryGeneratorAction::MakeASquareBeam(G4double &x, G4double &y)
{
  static const G4double in = 2.54*cm;
  // from DetectorConstruction... there is a better way
  auto detBox_dimX = 30 / 2;
  // for square beam
  double maxVal = detBox_dimX;
  x = maxVal * G4UniformRand();
  y = maxVal * G4UniformRand();

  if(G4UniformRand()>0.5) x = -1 * x;

  if(G4UniformRand()>0.5) y = -1 * y;
}

G4double PrimaryGeneratorAction::GetCfNeutronEnergy()
{
	G4double energy = G4UniformRand() * 15 + 1e-9;
	G4double height = G4UniformRand() * 0.48;

	while( height > (exp(-energy/1.209) * sinh( sqrt(0.836*energy))) ) {
		energy = G4UniformRand() * 15;
		height = G4UniformRand() * 0.48;
	}

	return( energy );
}

G4ThreeVector PrimaryGeneratorAction::MakeIsotropic()
{
  G4double cosTheta = 2*G4UniformRand() - 1., phi = 2*3.14*G4UniformRand();
  G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  G4double ux = sinTheta*std::cos(phi),
           uy = sinTheta*std::sin(phi),
           uz = cosTheta;
  G4ThreeVector v(ux,uy,uz);

  return v;
}

//fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
