
#ifndef PrimaryGeneratorActionGPS_h
#define PrimaryGeneratorActionGPS_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;
class G4Event;


class PrimaryGeneratorActionGPS : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorActionGPS();
   ~PrimaryGeneratorActionGPS();

    virtual void GeneratePrimaries(G4Event*);

  private:
    G4GeneralParticleSource* fParticleGun;
};


#endif


