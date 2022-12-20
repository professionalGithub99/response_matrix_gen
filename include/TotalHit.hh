#ifndef TotalHit_h
#define TotalHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4Types.hh"

class G4AttDef;
class G4AttValue;

/// Total hit
///
class TotalHit : public G4VHit
{
public:
  TotalHit();
  TotalHit(const TotalHit&);
  virtual ~TotalHit();

  // operators
  const TotalHit& operator=(const TotalHit&);
  G4int operator==(const TotalHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  // Set methods
  void SetTrackID  (G4int track)      { fTrackID = track; };
  void SetEdep     (G4double de)      { fEdep = de; };
  void SetPos      (G4ThreeVector xyz){ fPos = xyz; };
  void SetVol      (G4String vol){ fVol = vol; };

  // Get methods
  G4int         GetTrackID() const { return fTrackID; };
  G4double      GetEdep()    const { return fEdep; };
  G4ThreeVector GetPos()     const { return fPos; };
  G4String      GetVol()     const { return fVol; };

private:
    G4int         fTrackID;
    G4double      fEdep;
    G4ThreeVector fPos;
    G4String      fVol;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<TotalHit> TotalHitsCollection;

extern G4ThreadLocal G4Allocator<TotalHit>* TotalHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* TotalHit::operator new(size_t)
{
if(!TotalHitAllocator)
    TotalHitAllocator = new G4Allocator<TotalHit>;
return (void *) TotalHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void TotalHit::operator delete(void *hit)
{
TotalHitAllocator->FreeSingle((TotalHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
