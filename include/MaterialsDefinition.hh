#ifndef MaterialsDefinition_H
#define MaterialsDefinition_H 1

#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

enum materialName
{
  MATVAC,MATAIR,MATAL,MATB,MATPMMA,MATEFFPMT,MATMUMETAL,MATEJ309,MATEJ309B1,
  MATEJ309B25,MATEJ309B5, MATPYREX, MATEJ301DH, MATEJ315, MATDSTILBENE, MATODESSA,
  MATSTILBENE, MATSS, MATPTFE, MATW
};//END of enum materialName


class MaterialsDefinition
{
public:

    MaterialsDefinition();
    ~MaterialsDefinition();

    void DefineMaterials();
    G4Material * GetMaterial( materialName matName );

private:

    G4NistManager *manager;

    G4Material *matVac, *matAir, *matSS;

    G4Material *matAl, *matB, *matFe, *matW;

    G4Material *matPMMA, *matEffPMT, *matMuMetal, *matPyrex, *matPTFE;

    G4Material *matEJ309, *matEJ309B1, *matEJ309B25, *matEJ309B5, *matEJ301DH, *matEJ315;

    G4Material *matDStilbene, *matOdessa, *matStilbene;
};//END of class MaterialsDefinition

#endif
