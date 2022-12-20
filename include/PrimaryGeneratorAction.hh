#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4DataVector.hh"
#include "Randomize.hh"
#include "vector"

#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;
class G4ParticleGun;
class G4Box;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction(double partEnergy);
    ~PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
    void MakeASquareBeam(G4double &x, G4double &y);
    void MakeACircularBeam(G4double &x, G4double &y);
    G4double GetCfNeutronEnergy();
    G4ThreeVector MakeIsotropic();

  private:
    G4ParticleGun*  fParticleGun;
    G4double m_partEnergy; // [MeV]
};

#endif
