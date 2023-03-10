#include "DetectorConstruction.hh"
#include "DetectorSD.hh"
#include "MaterialsDefinition.hh"

#include "TMath.h"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4Polyhedra.hh"
#include "G4Polycone.hh"

#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4ios.hh"
#include "G4RotationMatrix.hh"

#include <iostream>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream
#include <fstream>

#ifndef PI
#define PI 3.14159265358979312
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(), fVisAttributes()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
    for (G4int i=0; i<G4int(fVisAttributes.size()); ++i) { delete fVisAttributes[i]; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  ///////////////////////////////////////
  // Variables
  ///////////////////////////////////////

  G4bool   checkOverlaps = true;
  G4double in = 2.54 * cm;

  ///////////////////////////////////////
  // Materials
  ///////////////////////////////////////
  G4Material *theMaterial;
  MaterialsDefinition matDef;
  matDef.DefineMaterials();

  ///////////////////////////////////////
  // World
  ///////////////////////////////////////

  // experimental hall (world volume)
  theMaterial = matDef.GetMaterial( MATAIR );

  ////////////////////////////////////////////////////////////////////
  //  World volume                                                  //
  ////////////////////////////////////////////////////////////////////

  G4double worldVol_x = 4.0*m;    // Full length along X axis
  G4double worldVol_y = worldVol_x; // Full length along Y axis
  G4double worldVol_z = worldVol_x; // Full length along Z axis

  // World
  auto worldVol_solid = new G4Box("worldVol_solid", worldVol_x/2.0, worldVol_y/2.0, worldVol_z/2.0);
  // Create a World logical volume
  auto worldVol_logV = new G4LogicalVolume(worldVol_solid, theMaterial, "worldVol_logV");
  worldVol_logV->SetVisAttributes(G4VisAttributes::GetInvisible());
  // Create World physical volume
  auto worldVol_physV = new G4PVPlacement(0, G4ThreeVector(0,0,0), worldVol_logV, "worldVol_physV", 0, false,  0);


  ///____THE FOLLOWING UNCOMMENT BLOCK IS A SINGLE GROUP ___//
 // Al casing
  /*double oD = 7.62; // [cm]  
  double ssThickness = 0.079; // [cm]
  double iD = oD - (2 * ssThickness); 
  double ssHeight = 7.62; // [cm] 
  //__________________________
  G4Tubs* housing = new G4Tubs("housing", 0, oD*cm/2, ssHeight*cm/2, 0.*deg, 360.*deg);
  theMaterial = matDef.GetMaterial( MATVAC );
  auto housingLogical = new G4LogicalVolume(housing,theMaterial,"housingLogical");

  new G4PVPlacement(0,
            G4ThreeVector(0.*m,0.*m,0.*m),
            housingLogical,
            "housing",
            worldVol_logV,
            false,
            0);
  
  // PTFE 0.8 mm -> 0.08 cm 
  double ptfeThickness = 0.08; // [cm]
  double ptfeHeight = ssHeight - ssThickness;
  G4Tubs* ptfe = new G4Tubs("ptfe", 0, iD*cm/2, ptfeHeight*cm/2, 0.*deg, 360.*deg);
  theMaterial = matDef.GetMaterial( MATVAC );
  auto ptfeLogical = new G4LogicalVolume(ptfe,theMaterial,"ptfeLogical");

  new G4PVPlacement(0,
            G4ThreeVector(0.*m,0.*m,-0.5*ssThickness*cm),
            ptfeLogical,
            "ptfe",
            housingLogical,
            false,
            0);
 
  // ODeSSa
  iD = iD - 2*ptfeThickness;
  auto scintHeight = ptfeHeight - ptfeThickness;
  G4Tubs* scint = new G4Tubs("scint", 0.*cm, iD*cm/2, scintHeight*cm/2, 0.*deg, 360.*deg);
  theMaterial = matDef.GetMaterial( MATEJ315 );
  auto f_scintLogical = new G4LogicalVolume(scint,theMaterial,"scint");
  new G4PVPlacement(0,
            G4ThreeVector(0.,0.,0*cm),
            f_scintLogical,
            "scint",
            ptfeLogical,
            false,
            0);
            */
  //Al casing 
  double oD = 7.94; //[cm]
  double iD = 7.62; //[cm]
  double alThicknessRadial = (oD-iD)/2; //[cm]
  double alHeight = 7.78;
  double scintHeight = 7.62;
  double alThicknessAxial = alHeight - scintHeight; //[cm]
  G4Tubs* housing = new G4Tubs("housing", 0, oD*cm/2, alHeight*cm/2, 0, 360.*deg);
  theMaterial = matDef.GetMaterial( MATAL );
  G4LogicalVolume* housingLogical= new G4LogicalVolume(housing, theMaterial, "housingLogical");
  new G4PVPlacement(0, G4ThreeVector(0*m,0*m,0*m), housingLogical, "housing",worldVol_logV, false, 0);
  theMaterial = matDef.GetMaterial(MATEJ301DH);
  G4Tubs* scint = new G4Tubs("scint", 0, iD*cm/2, scintHeight*cm/2, 0, 360.*deg);
  auto f_scintLogical = new G4LogicalVolume(scint,theMaterial,"scint");
  new G4PVPlacement(0, G4ThreeVector(0*m,0*m,-alThicknessAxial*cm/2), f_scintLogical, "scint", housingLogical, false, 0);
  
  // 1-in stilbene __ Al casing
  //
  // parameters in units of [mm]
  /*double oD = 2.54; // [cm] 
  double oH = 2.54; 
  double ssThickness = 0.1524; // [cm]
  double ssOD = oD + (2 * ssThickness); 
  double ssH  = 2.54 + ssThickness; // [cm] 
  //__________________________
  G4Tubs* housing = new G4Tubs("housing", 0, ssOD*cm/2, ssH*cm/2, 0.*deg, 360.*deg);
  theMaterial = matDef.GetMaterial( MATSS );
  auto housingLogical = new G4LogicalVolume(housing,theMaterial,"housingLogical");

  new G4PVPlacement(0,
            G4ThreeVector(0.*m,0.*m,0.*m),
            housingLogical,
            "housing",
            worldVol_logV,
            false,
            0);
  
  // scintillator
  G4Tubs* scint = new G4Tubs("scint", 0.*cm, oD*cm/2, (oH-ssThickness)*cm/2, 0.*deg, 360.*deg);
  theMaterial = matDef.GetMaterial( MATSTILBENE );
  auto f_scintLogical = new G4LogicalVolume(scint,theMaterial,"scint");
  new G4PVPlacement(0,
            G4ThreeVector(0.,0.,-ssThickness*cm),
            f_scintLogical,
            "scint",
            housingLogical,
            false,
            0);
  */
  // scint
  // 1-in stilbene
  /*G4Tubs* scint = new G4Tubs("1", 0.*in,1.*in/2, 15.*mm/2, 0.*deg, 360.*deg);
  theMaterial = matDef.GetMaterial( MATDSTILBENE );
  auto f_scintLogical = new G4LogicalVolume(scint,theMaterial,"1");
  new G4PVPlacement(0,
            G4ThreeVector(0.*in,0.*in,0*in),
            f_scintLogical,
            "1",
            worldVol_logV,
            false,
            0);
  */
  // *******************
  // add target material
  // *******************
  theMaterial = matDef.GetMaterial( MATW );
  // comment out below if you just want to propagate the thickness
  //thickness = matDef.GetTargetThickness(fTargetMaterialName); // gives thickness for 20 g/cc (Ad)
  G4Box *targetSolid = new G4Box("targetSolid",30.48/2*cm,30.48/2*cm,2.54/2*cm);

 auto targetLV
    = new G4LogicalVolume(
                 targetSolid,        // its solid
                 theMaterial,        // its material
                 "targetLV");        // its name


   double platePos = 1.*(0.5 + (oD/2*cm)/100); 
   /*new G4PVPlacement(
                 0,                            // rotation
                 G4ThreeVector(0., 0.*cm, platePos*m),  // position
                 targetLV,                     // logical volume
                 "target",                     // name
                  worldVol_logV,               // mother volume
                 false,                        // boolean operation
                 0                             // copy number
                 );
  */
  // add point source material
  //
  /*theMaterial = matDef.GetMaterial( MATPMMA );

  auto srcSolid
    = new G4Tubs("srcSolid",
                 0.*in, 1./2*in, 0.25/2*in,0.*deg, 360.*deg); // its size

  auto srcLV
    = new G4LogicalVolume(
                 srcSolid,        // its solid
                 theMaterial, // its material
                 "srcLV");        // its name

   new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 1*2.54*cm), // its position
                 srcLV,           // its logical volume
                 "src",            // its name
                 worldVol_logV,          // its mother  volume
                 false,            // no boolean operation
                 0                 // copy number
               );  // checking overlap
  */
  G4VisAttributes *grayAtt = new G4VisAttributes();
  grayAtt->SetColour(G4Colour::Gray());//0.0,0.0,0.0);
  grayAtt->SetForceSolid(false);
  grayAtt->SetForceWireframe(true);
  
  G4VisAttributes *redAtt = new G4VisAttributes();
  redAtt->SetColour(G4Colour::Red());//0.0,0.0,0.0);
  redAtt->SetForceSolid(false);
  redAtt->SetForceWireframe(true);

  G4VisAttributes *blueAtt = new G4VisAttributes();
  blueAtt->SetColour(G4Colour::Blue());//0.0,0.0,0.0);
  blueAtt->SetForceSolid(true);
  //blueAtt->SetForceWireframe(true);
 
  housingLogical->SetVisAttributes( grayAtt );
  //ptfeLogical->SetVisAttributes( redAtt );
  f_scintLogical->SetVisAttributes( blueAtt ); 
  
  return worldVol_physV;
}

void DetectorConstruction::ConstructSDandField()
{
   ////////////////////
   //sensitive detector
   ////////////////////
   G4String sdName = "scint";
   DetectorSD* aSD = new DetectorSD(sdName);
   G4SDManager::GetSDMpointer()->AddNewDetector(aSD);
   SetSensitiveDetector("scint",  aSD );
   //SetSensitiveDetector("cylDetPartIII_logV",  aSD );
   //SetSensitiveDetector("cylDetTriPartII_logV",  aSD );


   /*G4SDManager* sdManager = G4SDManager::GetSDMpointer();
   //use the sensitive detector type flag for mask, instead of adding a new one for target
   DetectorSD *sDetector = new DetectorSD("LiqScint", "LiqScint", 0);
   sdManager->AddNewDetector(sDetector);
   cylDetPartI_logV->SetSensitiveDetector(sDetector);
   cylDetTriPartII_logV->SetSensitiveDetector(sDetector);
   cylDetPartIII_logV->SetSensitiveDetector(sDetector);*/
}
