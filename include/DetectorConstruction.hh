#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4Material;

#include "G4VUserDetectorConstruction.hh"
#include "MaterialsDefinition.hh"
#include "globals.hh"
#include "G4PVPlacement.hh"

#include<vector>

class DetectorConstruction : public G4VUserDetectorConstruction
{
  private:

  public:
    DetectorConstruction();
    ~DetectorConstruction();

  public:
    G4VPhysicalVolume* Construct();
    void ConstructSDandField();

    // my methods

  protected:
    std::vector<G4VisAttributes*> fVisAttributes;


};

#endif
