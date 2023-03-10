//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
#include "EventAction.hh"
#include "Run.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4String.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "TotalHit.hh"
#include "Analysis.hh"
#include "HistoProcessing.h"
#include "TMath.h"

EventAction::EventAction()
: G4UserEventAction(), fdetHCID(-1)
{
  //theTree = new TTree("test","tree");
  //int fent;
  //theTree->Branch();
}

EventAction::~EventAction()
{
    G4cout << "Deleting EventAction";
    G4cout<<"...done"<<G4endl;
}

void EventAction::BeginOfEventAction(const G4Event* event)
{
  auto analysisManager = G4AnalysisManager::Instance();
  // set event data members to zero
  totEdep  = 0;
  Edep_gam = 0;
  Edep_neu = 0;
  Edep_deu = 0;
  Edep_pro = 0;
  Edep_ele = 0;
  Edep_pos = 0;
  Edep_alp = 0;
  Edep_car = 0;
  b_incident = false;
  trackN.clear();
  trackE.clear();

  totEdepPix.clear();
  for(int i=0; i<LibConstants::numberOfPixelsInDetector;i++)
    totEdepPix.push_back(0);
  // Set up histograms
  analysisManager->GetH1Id("Det0_src");       // 0
  analysisManager->GetH1Id("Det0_gam_lo");  // 1
  analysisManager->GetH1Id("Det0_gam_smear"); // 3
  analysisManager->GetH1Id("Det0_gam_scat");  // 4
  analysisManager->GetH1Id("Det0_neu_eDep");  // 5
  analysisManager->GetH1Id("Det0_neu_lo");    // 6
  analysisManager->GetH1Id("Det0_neu_smear"); // 7
  //analysisManager->GetH1Id("Det0_eDep_gam");    // 4
  //analysisManager->GetH1Id("Det0_eDep_deu");    // 5
}

TotalHitsCollection*
EventAction::GetHitsCollection(G4int hcID, const G4Event* event) const
{
  auto hitsCollection
    = static_cast<TotalHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection )
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}


void EventAction::ProcessEvent()
{
  ;
}

void EventAction::FillTrack(G4double edep, G4double tN)
{
  trackN.push_back(tN);
  trackE.push_back(edep*MeV);
}
void EventAction::FillTrackGam(G4double edep, G4double tN)
{
  trackN_gam.push_back(tN);
  trackE_gam.push_back(edep*MeV);
}

void EventAction::FillTrackNeu(G4double edep, G4double tN)
{
  trackN_neu.push_back(tN);
  trackE_neu.push_back(edep*MeV);
}

void EventAction::FillTrackDeu(G4double edep, G4double tN)
{
  trackN_deu.push_back(tN);
  trackE_deu.push_back(edep*MeV);
}
void EventAction::FillTrackPro(G4double edep, G4double tN)
{
  trackN_pro.push_back(tN);
  trackE_pro.push_back(edep*MeV);
}
void EventAction::FillTrackEle(G4double edep, G4double tN)
{
  trackN_ele.push_back(tN);
  trackE_ele.push_back(edep*MeV);
}
void EventAction::FillTrackPos(G4double edep, G4double tN)
{
  trackN_pos.push_back(tN);
  trackE_pos.push_back(edep*MeV);
}
void EventAction::FillTrackAlp(G4double edep, G4double tN)
{
  trackN_alp.push_back(tN);
  trackE_alp.push_back(edep*MeV);
}
void EventAction::FillTrackCar(G4double edep, G4double tN)
{
  trackN_car.push_back(tN);
  trackE_car.push_back(edep*MeV);
}

void EventAction::EndOfEventAction(const G4Event* event)
{
  // set tree values to -999 for uniform filling
  double t_sourceEn = -999;
  double t_edep_tot   = -999;
  double t_lo_neu     = -999;
  double t_lo_gam     = -999;
  double t_lo_tot     = -999;
  int    t_eventN     = -999;
  // set resolution parameters
  // EJ309 for SPD
  //double alpha =  0.096;//-0.04;//.16;//.00426;
  //double beta  =  0.01; //.087;//.1234;
  //double gamma =  0.008;//.033;//.0579;
  // EJ301D for SPD
  //double alpha =  0.05221;//-0.04;//.16;//.00426;
  //double beta  =  0.06386; //.087;//.1234;
  //double gamma =  0.03521;//.033;//.0579;
  // Stilbene 2-in for UND
  //double alpha =  0.06743;//-0.04;//.16;//.00426;
  //double beta  =  0.06593; //.087;//.1234;
  //double gamma =  0.02755;//.033;//.0579;
  //double alpha =  0.1757;//-0.04;//.16;//.00426;
  //double beta  =  0.07589; //.087;//.1234;
  //double gamma =  0.01011;//.033;//.0579;
  // Stilbene 1-in for UND
  //double alpha =  0.06743;//-0.04;//.16;//.00426;
  //double beta  =  0.06593; //.087;//.1234;
  //double gamma =  0.02755;//.033;//.0579;
  // ODeSSA
  //double alpha =  0.1757;//-0.04;//.16;//.00426;
  //double beta  =  0.07589; //.087;//.1234;
  //double gamma =  0.01011;//.033;//.0579;
  // 3-in EJ301DH 
  double alpha = 3.17137E-5;;
  double beta = 1.40287E-1;
  double gamma = 1.94422E-2;
  // 3-in EJ315
  //double alpha =  7.9E-4;;//-0.04;//.16;//.00426;
  //double beta  =  1.5E-1; //.087;//.1234;
  //double gamma =  9.1E-4;//.033;//.0579;

  // grab event number
  t_eventN = event->GetEventID();
  // grab instance of analysis manager and run action
  auto analysisManager = G4AnalysisManager::Instance();
  auto myRunAction = (RunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
  // orginating particle energy 
  t_sourceEn = myRunAction->GetSourceParticleEnergy();
  analysisManager->FillH1(0,t_sourceEn*MeV); // source energy
  //if(Edep_deu > 0.0) analysisManager->FillH1(1,Edep_deu*MeV); // neu
  
  // *** For gamma-ray source ***
  if( Edep_gam > 0.0) 
  {
    analysisManager->FillH1(1,Edep_gam*MeV); // neu
    auto gam_LO = hp.smearElectronEDep(Edep_gam, alpha,beta,gamma);
    analysisManager->FillH1(2,gam_LO*MeV);
    if(incidentEn != 4430) 
    {
      //cout << incidentEn << endl;
      analysisManager->FillH1(3,gam_LO*MeV); // scattered
    }
  }

  if(Edep_deu > 0.0) 
  {
    // total energy 
    //t_edep_tot = totEdep;
    //t_lo_tot = hp.smearElectronEDep(t_edep_tot,alpha,beta,gamma);
    //analysisManager->FillH1(1,t_edep_tot);
    //analysisManager->FillH1(2,t_lo_tot);
    // smear the energy for total
    //double sE = hp.smearElectronEDep(Edep_gam,alpha,beta,gamma);
    //double sDeu = p0*en-(p1)*(1-TMath::Exp(-en*p2));
    // TODO: need to fix this in SD
    //if(Edep_neu > 0.0) analysisManager->FillH1(3,Edep_neu*MeV); // neu
    //if(Edep_gam > 0.0) analysisManager->FillH1(4,sE*MeV); // gam
    // ************************
    // deuteron info processing
    // ************************
    if(Edep_deu > 0.0 && trackN.size() > 0)
    {
      // Odessa
      /*auto p0 = 604.6 / 1000.;
      auto p1 = 1732.4 / 1000.;
      auto p2 = 0.294;*/
      auto p0 = 572/1000.;
      auto p1 = 2394/1000.;
      auto p2 = 200/1000.;

      // smear the deuteron energy
      // sort deu tracks
      auto uniqueTrackN = trackN;
      sort( uniqueTrackN.begin(), uniqueTrackN.end() );
      uniqueTrackN.erase( unique( uniqueTrackN.begin(), uniqueTrackN.end() ), uniqueTrackN.end() );

      vector<double> deuTrackEn;
      for(int i=0; i<uniqueTrackN.size(); i++) deuTrackEn.push_back(0);

      // loop through track steps
      for(int i=0; i<trackN.size(); i++)
      {
        for(int j=0; j<uniqueTrackN.size(); j++)
        {
          //cout << trackN[i] << " " << uniqueTrackN[j] << endl;
          if( trackN[i] == uniqueTrackN[j] ) deuTrackEn[j] += trackE[i];
        }
      }
      double deu_LO = 0;
      for(auto en : deuTrackEn)
      {
        // this fills the track tree
        deu_LO += (p0*en-(p1)*(1-TMath::Exp(-en*p2)));//*8/9; // for EJ315
        analysisManager->FillNtupleIColumn(1, 0, t_eventN);
        analysisManager->FillNtupleDColumn(1, 1, en);
        analysisManager->FillNtupleDColumn(1, 2, deu_LO);
        analysisManager->AddNtupleRow(1);
        //deu_LO += .029*en*en + 0.108*en + 2.56 * TMath::Power(10,-16);
      }
      analysisManager->FillH1(4,Edep_deu*MeV);
      analysisManager->FillH1(5,deu_LO*MeV); // without resolution
      // Right now this will only work for a deuterated detector
      t_lo_neu = hp.smearElectronEDep(deu_LO, alpha,beta,gamma);//0.131,0.08,0.062);//.0045,0.07,0.0048);
      //t_lo_neu = 1.05*deu_LO;//0.131,0.08,0.062);//.0045,0.07,0.0048);
      analysisManager->FillH1(6,t_lo_neu*MeV); // with resolution
    }
  }
  // Fill Event tree
  analysisManager->FillNtupleIColumn(0, 0, t_eventN);
  analysisManager->FillNtupleDColumn(0, 1, t_sourceEn);
  analysisManager->FillNtupleDColumn(0, 2, totEdep);
  analysisManager->FillNtupleDColumn(0, 3, t_lo_tot);
  analysisManager->FillNtupleDColumn(0, 4, t_lo_neu);
  //analysisManager->FillNtupleDColumn(0, 5, t_lo_gam);
  analysisManager->AddNtupleRow(0);

}

void EventAction::ProcessDeuteronTrackInfo()
{

}
