////////////////////////
//
#include "DetectorSD.hh"
#include "TotalHit.hh"
#include "Run.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

#include "G4ParticleTypes.hh"
#include "G4HadronicProcess.hh"

#include "TMath.h"

DetectorSD::DetectorSD(G4String name)
: G4VSensitiveDetector(name), hitsCollection(0), HCID(-1)
{
    G4String HCname = "detectorHits";
    collectionName.insert(HCname);
    G4cout << "your sensitive detector's name is " << name << G4endl;
}

DetectorSD::~DetectorSD()
{}

void DetectorSD::Initialize(G4HCofThisEvent* hce)
{
  hitsCollection = new TotalHitsCollection
  (SensitiveDetectorName,collectionName[0]);
  if (HCID<0)
  {
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);
  }

  hce->AddHitsCollection(HCID,hitsCollection);
}

G4bool DetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  //G4cout << "process hits..........................................." << G4endl;
  // energy deposit
  G4double edep = aStep->GetTotalEnergyDeposit();

  //if (edep==0.) return false;

  TotalHit* newHit = new TotalHit();

  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4StepPoint* postStepPoint = aStep->GetPostStepPoint();

  // get some values
  G4int eventID
  = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();

  G4String strVolName =
  aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();

  G4int intVolName      = atoi(strVolName);
  G4int stepID          = aStep->GetTrack()->GetCurrentStepNumber();
  G4int trackID         = aStep->GetTrack()->GetTrackID();
  G4double edepStep     = aStep->GetTotalEnergyDeposit();
  G4ThreeVector inpos   = preStepPoint->GetPosition();
  G4ThreeVector outpos  = postStepPoint->GetPosition();
  G4int parentTrackID   = aStep->GetTrack()->GetParentID();
  G4int pdgNum = aStep->GetTrack()->GetDefinition()->GetPDGEncoding();
  G4double kE          = preStepPoint->GetKineticEnergy()/CLHEP::keV;
  G4double time_mu     = aStep->GetPreStepPoint()->GetGlobalTime()/CLHEP::microsecond;

  // look at values for just an event
  EventAction* myEventAction
  = (EventAction*)(G4EventManager::GetEventManager()->GetUserEventAction());
  // tally energies for event types
  myEventAction->AddEdep(edepStep*MeV);
  // look at the incident energy
  if(!myEventAction->checkIncidentEn())
  {
    myEventAction->setIncidentEn(kE);
    myEventAction->setIncidentEnFlg(true);
  }  
  myEventAction->AddPixEdep(edepStep, intVolName);
  //cout << pdgNum  << endl;
  // if it is a carbon or proton tally the energy
  if(pdgNum == 2212)
  //if(pdgNum == 1000060120) // this is carbon
  {  
    myEventAction->AddEdepNeu(edepStep*MeV);
  }
  // if it is an electron tally the energy
  if(pdgNum == 11 || pdgNum == -11)
    myEventAction->AddEdepGam(edepStep*MeV);
  
  //if(pdgNum == 2212)     // this is proton
  if(pdgNum == 1000010020) // this is deuteron
  {
    myEventAction->FillTrack(edepStep*MeV,trackID);
    myEventAction->AddEdepDeu(edepStep*MeV);
  }
	return true;
}


void DetectorSD::processReactionInfo(const G4Step* aStep)
{
  //
}

void DetectorSD::EndOfEvent(G4HCofThisEvent* hce)
{
	int nhitC = hitsCollection->GetSize();
	if(!nhitC) return;

	int HIT_VERBOSITY=0;
	if(HIT_VERBOSITY >= 2 && nhitC)
	{
		G4cout<<"<<<End of Hit Collections <" << SensitiveDetectorName << "/"<<collectionName[0]
		<<">: " << nhitC << " hits." << G4endl;
		for (int i=0; i<nhitC; i++)
		{
			(*hitsCollection)[i]->Print();
		}
	}

	return;
}
