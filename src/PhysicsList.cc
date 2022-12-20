/***************************************************************************//**
********************************************************************************
**
** @author James Till Matta
** @date 9 Apr, 2020
**
** @copyright Copyright (C) 2020 James Till Matta
**
********************************************************************************
*******************************************************************************/
#include"PhysicsList.hh"
#include<G4RegionStore.hh>
#include<G4EmLivermorePhysics.hh>
#include<G4LossTableManager.hh>
/*#include<G4PhotoNuclearProcess.hh>*/
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

namespace Physics
{

PhysicsList::PhysicsList()
{
    //always create EM physics
    emPhys = new G4EmLivermorePhysics();
    hadrPhys = new QGSP_BERT_HP();
    for(int physInd = 0; true; ++physInd)
    {
        auto elem = const_cast<G4VPhysicsConstructor*>(hadrPhys->GetPhysics(physInd));  //NOLINT, Needs must when the devil drives
        if(elem == nullptr)
        {
            // end of list so no more to register
            break;
        }
        if(elem->GetPhysicsName() == "G4EmStandard")
        {
            //make sure EM physics overrides whatever hadrPhys set
            G4cout << "Replacing EM physics 'G4EmStandard' with: '" << emPhys->GetPhysicsName() << "'" << G4endl;
            ReplacePhysics(emPhys);
        }
        else
        {
            G4cout << "Registering QGSP_BERT_HP physics: '" << elem->GetPhysicsName() << "'" << G4endl;
            RegisterPhysics(elem);
        }
    }
}

PhysicsList::~PhysicsList()
{}

void PhysicsList::ConstructParticle()
{
    G4VModularPhysicsList::ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
    G4VModularPhysicsList::ConstructProcess();
    
    // decay physics
    G4VPhysicsConstructor *decPhysicsList = new G4DecayPhysics();
    decPhysicsList->ConstructProcess();
  
    G4VPhysicsConstructor *radDecPhysicsList = new G4RadioactiveDecayPhysics();
    radDecPhysicsList->ConstructProcess();
}

void PhysicsList::SetCuts()
{
    hadrPhys->SetCuts();
    /*//force higher accuracy for hadronic physics within the det volume
    G4Region* region = G4RegionStore::GetInstance()->GetRegion("ScintillatorRegion");
    if(region != nullptr)
    {
        auto cuts = new G4ProductionCuts();
        cuts->SetProductionCut(1 * um);
        region->SetProductionCuts(cuts);
    }*/
    G4cout << "Setting cuts for precision EM physics list." << G4endl;
    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(250 * CLHEP::eV, 1 * CLHEP::GeV);
    SetCutValue(1 * CLHEP::um, "gamma");
    SetCutValue(1 * CLHEP::um, "e-");
    SetCutValue(1 * CLHEP::um, "e+");
}

} // namespace Physics

