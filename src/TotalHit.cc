// my classes
#include "TotalHit.hh"
// G4 user classes
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
// c++ classes
#include <iomanip>
#include <iostream>

using namespace std;
////////////////////
////////////////////

G4ThreadLocal G4Allocator<TotalHit>* TotalHitAllocator=0;

TotalHit::TotalHit()
 : G4VHit(),
   fTrackID(-1),
   fEdep(0.),
   fPos(G4ThreeVector())
{}


TotalHit::~TotalHit() {}


TotalHit::TotalHit(const TotalHit& right)
  : G4VHit()
{
  fTrackID   = right.fTrackID;
  fEdep      = right.fEdep;
  fPos       = right.fPos;
}


const TotalHit& TotalHit::operator=(const TotalHit& right)
{
  fTrackID   = right.fTrackID;
  fEdep      = right.fEdep;
  fPos       = right.fPos;

  return *this;
}


G4int TotalHit::operator==(const TotalHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}
