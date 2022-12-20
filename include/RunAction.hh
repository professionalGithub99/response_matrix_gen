//
/// \file RunAction.hh
/// \brief Definition of the RunAction class

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "TotalHit.hh"
#include "MyLib_Constants.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
// c++ classes
#include <string>
#include <cstdlib>

using namespace std;

class G4Run;
class Run;
class G4LogicalVolume;

/// Run action class

class RunAction : public G4UserRunAction
{
  public:
    RunAction(std::string fN);
    virtual ~RunAction();

    virtual G4Run* GenerateRun();
    virtual void   BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
    TFile *fout;
    TTree *stepTTree;
    TTree *eventTTree;
    TTree *hitTTree;
    TH1F  *h1_eDep;
    TH1F  *h_source;
		time_t startTime;

    // data members for steps
    G4int feventID;
    G4int fstepID;
    G4double fdepE;
    G4double fx;
    G4double fy;
    G4double fz;
    G4double fpostx;
    G4double fposty;
    G4double fpostz;
    G4String fptype;
    G4double ftime;
    G4int ftrackID;
    G4double fkE;
    G4int fpID;
    G4int fvname;
    G4int fpdg;
    G4int fProcessName;
    G4int fSubProcessName;
    G4int fCreatorProcessName;
    G4int fCreatorSubProcessName;
    G4String fvolStrName;
    G4int fintVolName;

    // data members for an event
    G4double ftotDepE;
    G4double ftotDepEPix[LibConstants::numberOfPixelsInDetector];
    vector<G4double> fpixDepEnergy;
    G4double fSourcePartEn;

    Run*                       fRun;
    G4bool   fPrint;      //optional printing


  public:
    inline G4double GetStartTime(){return startTime;}

    inline void SetPrimaryE(G4double pE){fdepE=pE;}

    // set event values
    inline void SetTotEDep(G4double energy){ftotDepE=energy;}
    inline void SetSourceParticleEnergy(G4double energy){fSourcePartEn=energy;}
    inline double GetSourceParticleEnergy(){return fSourcePartEn;}

    //inline void SetPixTotEDep(vector<G4double> pixDepEnergy;)
	  //inline void FillStepTTree(){stepTTree->Fill();}
	  //void FillEventTTree(vector<G4double> pixDepEnergy);
    //void FillHitTree(SimEvent evt);
	  //void MakeEventBranch(G4String branchName);
};

#endif
