/// \file EventAction.hh
/// \brief Definition of the EventAction class
#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "RunAction.hh"
#include "globals.hh"
#include "HistoProcessing.h"
// C++ classes
#include <vector>
#include <array>

// my classes
#include "MyLib_Constants.h"
// named constants
//const G4int kNumDet = 1;

/// Event action class
///

class EventAction : public G4UserEventAction
{
  private:
    // data members
    EventAction*         fEventAction;
    G4int                fdetHCID;
    TotalHitsCollection* hitsCollection;
    G4double             Edep_neu;
    G4double             Edep_deu;
    G4double             Edep_gam;
    G4double             totEdep;
    vector<G4double>     totEdepPix;
    vector<G4double>     trackN;
    vector<G4double>     trackE;
    TTree                *theTree;
    //G4double totEdepPix[LibConstants::numberOfPixelsInDetector];
    G4double             fSourcePartEn;
    HistoProcessing      hp;
    G4double             incidentEn;
    bool                 b_incident;
    // Deuteron variables


  public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
    
    // my methods
    TotalHitsCollection* GetHitsCollection(G4int hcID,
                                            const G4Event* event) const;

    void ProcessEvent();
    
    bool checkIncidentEn() { return b_incident;}
    void setIncidentEnFlg(bool setVal) {b_incident = setVal;}
    void setIncidentEn(G4double setVal) {incidentEn = setVal;}

    inline void AddEdep(G4double edep) { totEdep += edep;}
    inline void AddEdepGam(G4double edep) { Edep_gam += edep;}
    inline void AddEdepNeu(G4double edep) { Edep_neu += edep;}
    inline void AddEdepDeu(G4double edep) { Edep_deu += edep;}
    // This is a tree full of steps
    void FillTrack(G4double edep, G4double tN);

    void AddPixEdep(G4double edep, G4int pixIntName) //
    {
      totEdepPix.at(pixIntName) += edep;
    }

    inline void SetSourceParticleEnergy(G4double energy){fSourcePartEn=energy;}

    void ProcessDeuteronTrackInfo();

    G4int fDetHistoID[7];

    time_t simStartTime;
};


#endif
