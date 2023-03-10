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
    G4double             Edep_pro;
    G4double             Edep_ele;
    G4double             Edep_pos;
    G4double             Edep_alp;
    G4double             Edep_car;
    G4double             totEdep;
    vector<G4double>     totEdepPix;
    vector<G4double>     trackN;
    vector<G4double>     trackE;
    //make a track for each particle
    vector<G4double>     trackN_neu;
    vector<G4double>     trackN_deu;
    vector<G4double>     trackN_gam;
    vector<G4double>     trackN_pro;
    vector<G4double>     trackN_ele;
    vector<G4double>     trackN_pos;
    vector<G4double>     trackN_alp;
    vector<G4double>     trackN_car;
    vector<G4double>     trackE_neu;
    vector<G4double>     trackE_deu;
    vector<G4double>     trackE_gam;
    vector<G4double>     trackE_pro;
    vector<G4double>     trackE_ele;
    vector<G4double>     trackE_pos;
    vector<G4double>     trackE_alp;
    vector<G4double>     trackE_car;
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
    inline void AddEdepPro(G4double edep) { Edep_pro += edep;}
    inline void AddEdepEle(G4double edep) { Edep_ele += edep;}
    inline void AddEdepPos(G4double edep) { Edep_pos += edep;}
    inline void AddEdepAlp(G4double edep) { Edep_alp += edep;}
    inline void AddEdepCar(G4double edep) { Edep_car += edep;}

    // This is a tree full of steps
    void FillTrack(G4double edep, G4double tN);
    void FillTrackGam(G4double edep, G4double tN);
    void FillTrackNeu(G4double edep, G4double tN);
    void FillTrackDeu(G4double edep, G4double tN);
    void FillTrackPro(G4double edep, G4double tN);
    void FillTrackEle(G4double edep, G4double tN);
    void FillTrackPos(G4double edep, G4double tN);
    void FillTrackAlp(G4double edep, G4double tN);
    void FillTrackCar(G4double edep, G4double tN);


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
