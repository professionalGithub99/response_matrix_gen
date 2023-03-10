#include "MaterialsDefinition.hh"

#include "globals.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#define _tostr(a) #a
#define tostr(a) _tostr(a)

MaterialsDefinition::MaterialsDefinition()
{
  manager = G4NistManager::Instance();

	matAir = manager->FindOrBuildMaterial("G4_AIR");
  matVac = manager->FindOrBuildMaterial("G4_Galactic");
  matAl  = manager->FindOrBuildMaterial("G4_Al");
  matB   = manager->FindOrBuildMaterial("G4_B");
  //G4Material * H2O           = nistManager->FindOrBuildMaterial("G4_WATER");
  //G4Material * al_mat        = nistManager->FindOrBuildMaterial("G4_Al");
  //G4Material * concrete_mat  = nistManager->FindOrBuildMaterial("G4_CONCRETE");
  // Set pointers to NULL
  matPMMA      = 0;
  matEffPMT    = 0;
  matMuMetal   = 0;
  matEJ309     = 0;
  matEJ309B1   = 0;
  matEJ309B25  = 0;
  matEJ309B5   = 0;
  matPyrex     = 0;
  matEJ301DH   = 0;
  matEJ315     = 0;
  matDStilbene = 0;
  matOdessa    = 0;
  matStilbene  = 0;
  matSS        = 0;
  matPTFE      = 0;
  matW         = 0;
}//END of constructor

MaterialsDefinition::~MaterialsDefinition()
{

	G4cout<<"Deleting MaterialsDefinition...";

	G4cout<<"done"<<G4endl;
}

void MaterialsDefinition::DefineMaterials()
{
  G4Material *theMaterial = NULL;
  G4double density, fractionmass;;
  G4int    ncomponents, natoms;
  G4double inches = 2.54 * cm;

  G4NistManager* nistManager = G4NistManager::Instance();

  ///////////////////////////////////////
  // Materials
  ///////////////////////////////////////
  // My isotopes
  // Deuterium
  G4double a,z;
  G4String name,symbol;
  a=2.01*g/mole;

  //G4Element *elD = new G4Element(name="Deuterium",symbol="D",z=1.,a);
  G4Isotope* D  = new G4Isotope("Deuteron", 1, 2, 2.0141018* CLHEP::g / CLHEP::mole);
  G4Element* elD = new G4Element("Deuterium","elD", 1);
  elD->AddIsotope(D, 1);

  ///////////
  // Elements
  ///////////
  G4Element* H  = nistManager->FindOrBuildElement("H");  // Z=1
  G4Element* B  = nistManager->FindOrBuildElement("B");  // Z=5
  G4Element* C  = nistManager->FindOrBuildElement("C");  // Z=6
  G4Element* O  = nistManager->FindOrBuildElement("O");  // Z=8
  G4Element* F  = nistManager->FindOrBuildElement("F");  // Z=9
  G4Element* Na = nistManager->FindOrBuildElement("Na"); // Z=11
  G4Element* Mg = nistManager->FindOrBuildElement("Mg"); // Z=12
  G4Element* Si = nistManager->FindOrBuildElement("Si"); // Z=14
  G4Element* P  = nistManager->FindOrBuildElement("P");  // Z=15
  G4Element* K  = nistManager->FindOrBuildElement("K");  // Z=19
  G4Element* Al = nistManager->FindOrBuildElement("Al");
  G4Element* Fe = nistManager->FindOrBuildElement("Fe");
  G4Element* Ni = nistManager->FindOrBuildElement("Ni");
  G4Element* Cr = nistManager->FindOrBuildElement("Cr");
  G4Element* Mn = nistManager->FindOrBuildElement("Ni");


  // Materials
  matW   = manager->FindOrBuildMaterial("G4_W");

  //G4Material* matD = new G4Material("matD", 0.00018* CLHEP::g / CLHEP::cm3, 1);
  //matD->AddElement(elD, 1);
  //
  // Stainless steel
  matSS = new G4Material("StainlessSteel", density= 8.06*g/cm3, ncomponents=6);
  matSS->AddElement(C, fractionmass=0.001);
  matSS->AddElement(Si, fractionmass=0.007);
  matSS->AddElement(Cr, fractionmass=0.18);
  matSS->AddElement(Mn, fractionmass=0.01);
  matSS->AddElement(Fe, fractionmass=0.712);
  matSS->AddElement(Ni, fractionmass=0.09);

  // EJ309
  ////////
  density = 0.959*g / cm3;
  matEJ309 = new G4Material("matEJ309", density, ncomponents=2);
  matEJ309->AddElement(H, natoms=543);
  matEJ309->AddElement(C, natoms=435);

  // EJ-309B-5%
  // EJ-309 loaded with 5% natural boron
  density = 0.963*g / cm3;
  G4Material* matEJ309B5 = new G4Material("matEJ309B5", density, ncomponents=3);
  matEJ309B5->AddElement(H, fractionmass=0.093);
  matEJ309B5->AddElement(C, fractionmass=0.857);
  matEJ309B5->AddElement(B, fractionmass=0.05);

  // EJ-309B-2.5%
  density = 0.964*g / cm3;
  matEJ309B25 = new G4Material("matEJ309B25", density, ncomponents=3);
  matEJ309B25->AddElement(H, fractionmass=0.094);
  matEJ309B25->AddElement(C, fractionmass=0.881);
  matEJ309B25->AddElement(B, fractionmass=0.025);

  // EJ-309B-1%
  density = 0.965*g / cm3;
  matEJ309B1 = new G4Material("matEJ309B1", density, ncomponents=3);
  matEJ309B1->AddElement(H, fractionmass=0.094);
  matEJ309B1->AddElement(C, fractionmass=0.896);
  matEJ309B1->AddElement(B, fractionmass=0.01);


  //EJ301DH 
  //note it doesnt fully match the paper on ej301d in ratio between d and c but also paper doesnt specify the H 
  //which is why I added H
  density = 1.030*g /cm3; 
  matEJ301DH = new G4Material("matEJ301DH", density, ncomponents=3);
  matEJ301DH->AddElement(elD, natoms = 4720);
  matEJ301DH->AddElement(H, natoms = 116);
  matEJ301DH->AddElement(C, natoms = 3990);

  // EJ-315
  density = 0.954*g / cm3;
  matEJ315 = new G4Material("matEJ315", density, ncomponents=3); //3
  matEJ315->AddElement(H, fractionmass=.0005);     // 1
  matEJ315->AddElement(C, fractionmass=.859995);   // 141
  matEJ315->AddElement(elD, fractionmass=.143);    // 141

  // D-stilbene from Fred's paper
  density = 1.24*g / cm3;
  matDStilbene = new G4Material("matDStilbene", density, ncomponents=2); //3
  //matEJ315->AddElement(H, fractionmass=.0005);     // 1
  matDStilbene->AddElement(C, natoms=14);   // 141
  matDStilbene->AddElement(elD, natoms=12);    // 141

  // Odessa deuterated liquid
  // From Check via Mike's email
  density = 0.954 * g / cm3; // density of EJ0315
  matOdessa = new G4Material("matOdessa", density, ncomponents=3); //3
  matOdessa->AddElement(H,   natoms = 4);     
  matOdessa->AddElement(C,   natoms = 501);   
  matOdessa->AddElement(elD, natoms = 496);   

  //
  // PMMA
  ///////
  density = 1.19*g/cm3;
  matPMMA = new G4Material("matPMMA", density, ncomponents=3);
  matPMMA->AddElement(C, natoms=5);
  matPMMA->AddElement(O, natoms=2);
  matPMMA->AddElement(H, natoms=8);

  //
  // PTFE
  ///////
  density = 2.25*g/cm3;
  matPTFE = new G4Material("matPTFE", density, ncomponents=2);
  matPTFE->AddElement(C, natoms=2);
  matPTFE->AddElement(F, natoms=4);

  //
  // matEffPMT
  ////////////
  density = 0.05*2.23*g/cm3; //about 5% of the density of the glass
  matEffPMT = new G4Material("matEffPMT", density, ncomponents=6);

  matEffPMT->AddElement(B, fractionmass=0.040064);
  matEffPMT->AddElement(O, fractionmass=0.539562);
  matEffPMT->AddElement(Na, fractionmass=0.028191);
  matEffPMT->AddElement(Mg, fractionmass=0.011644);
  matEffPMT->AddElement(P, fractionmass=0.377220);
  matEffPMT->AddElement(K, fractionmass=0.003321);

  //
  // matPyrex
  ////////////
  density = 2.23*g/cm3; //about 5% of the density of the glass
  matPyrex = new G4Material("matPyrex", density, ncomponents=6);

  matPyrex->AddElement(B, fractionmass=0.040064);
  matPyrex->AddElement(O, fractionmass=0.539562);
  matPyrex->AddElement(Na, fractionmass=0.028191);
  matPyrex->AddElement(Mg, fractionmass=0.011644);
  matPyrex->AddElement(P, fractionmass=0.377220);
  matPyrex->AddElement(K, fractionmass=0.003321);

  //
  // muMetal
  //////////
  density = 8.25*g/cm3;
  matMuMetal = new G4Material("matMuMetal", density, ncomponents=2);
  matMuMetal->AddElement(Ni, fractionmass=0.8);
  matMuMetal->AddElement(Fe, fractionmass=0.2);

  // 
  // stainless steel
  matSS = new G4Material("StainlessSteel", density= 8.06*g/cm3, ncomponents=6);
  matSS->AddElement(C, fractionmass=0.001);
  matSS->AddElement(Si, fractionmass=0.007);
  matSS->AddElement(Cr, fractionmass=0.18);
  matSS->AddElement(Mn, fractionmass=0.01);
  matSS->AddElement(Fe, fractionmass=0.712);
  matSS->AddElement(Ni, fractionmass=0.09);

  // H-stilbene
  density = 1.16*g / cm3;
  matStilbene = new G4Material("matStilbene", density, ncomponents=2); //3
  //matEJ315->AddElement(H, fractionmass=.0005);     // 1
  matStilbene->AddElement(C, natoms=14);   // 141
  matStilbene->AddElement(H, natoms=12);    // 141

}

G4Material * MaterialsDefinition::GetMaterial(materialName matName)
{
  G4Material *theMaterial = NULL;

  switch( matName )
  {
    case MATVAC:
      theMaterial = matVac; //defined in constructor
      break;

    case MATW:
      theMaterial = matW; //defined in constructor
      break;

    case MATAIR:
      theMaterial = matAir; //defined in constructor
      break;

    case MATAL:
      theMaterial = matAl; //defined in constructor
      break;

    case MATB:
      theMaterial = matB; //defined in constructor
      break;

    case MATPMMA:
      theMaterial = matPMMA; //defined in constructor
      break;

    case MATPTFE:
      theMaterial = matPTFE; //defined in constructor
      break;

    case MATEFFPMT:
      theMaterial = matEffPMT; //defined in constructor
      break;

    case MATMUMETAL:
      theMaterial = matMuMetal; //defined in constructor
      break;

    case MATEJ309:
      theMaterial = matEJ309; //defined in constructor
      break;

    case MATEJ309B1:
      theMaterial = matEJ309B1; //defined in constructor
      break;

    case MATEJ309B25:
      theMaterial = matEJ309B25; //defined in constructor
      break;

    case MATEJ309B5:
      theMaterial = matEJ309B25; //defined in constructor
      break;

    case MATEJ301DH:
      theMaterial = matEJ301DH; //defined in constructor
      break;

    case MATEJ315:
      theMaterial = matEJ315; //defined in constructor
      break;

    case MATDSTILBENE:
      theMaterial = matDStilbene; //defined in constructor
      break;

    case MATPYREX:
      theMaterial = matPyrex; //defined in constructor
      break;

    case MATSS:
      theMaterial = matSS; //defined in constructor
      break;

    case MATODESSA:
      theMaterial = matOdessa; //defined in constructor
      break;

    case MATSTILBENE:
      theMaterial = matStilbene; //defined in constructor
      break;

    /*case :
      theMaterial = ; //defined in constructor
      break;*/

    default:
      G4cout<<"ERROR: Requested Material does not exist.\n";
      break;

  }

  return theMaterial;
}
