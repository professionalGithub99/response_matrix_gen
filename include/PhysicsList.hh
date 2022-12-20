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
#ifndef MATTA_PHYSICSLIST_H
#define MATTA_PHYSICSLIST_H

#include<CLHEP/Units/SystemOfUnits.h>
#include<G4VModularPhysicsList.hh>
#include<QGSP_BERT_HP.hh>
// includes from GenSim

namespace Physics
{

/*!
* @brief A physics list that includes the standard QGSP_BERT_HP processes for
* most things but uses Livermore E&M physics
*/
class PhysicsList : public G4VModularPhysicsList
{
public:
    PhysicsList();
    ~PhysicsList() final;

    void ConstructParticle() final;
    void ConstructProcess() final;
    void SetCuts() final;

private:
    G4VPhysicsConstructor* emPhys{nullptr}; ///< electromagnetic physics
    QGSP_BERT_HP* hadrPhys{nullptr}; ///< Hadronic physics
};

} // namespace Physics

#endif  // MATTA_PHYSICSLIST_H
