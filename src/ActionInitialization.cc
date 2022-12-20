//
/// \file ActionInitialization.cc
/// \brief Implementation of the ActionInitialization class

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorActionGPS.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "DetectorSD.hh"

#include <iostream>
#include <string>
#include <sstream>

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{
  // Set output file name to date and time if a specfic file name is not
  // entered.
  auto time = std::time(nullptr);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&time), "%F_%T"); // ISO 8601 without timezone information.
  auto s = ss.str();
  std::replace(s.begin(), s.end(), ':', '-');
  m_oFN = s;
}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{
  auto ra = new RunAction(m_oFN);
  SetUserAction(ra);}

void ActionInitialization::SetParticleEnergy(double en)
{
  m_partEnergy = en;
}

void ActionInitialization::SetOutFileName(std::string fN)
{
  std::stringstream ss;
  ss << "_en_" << fN << ".root";
  auto s = ss.str();
  m_oFN = s;
}

void ActionInitialization::Build() const
{
  auto pg = new PrimaryGeneratorAction(m_partEnergy);
  SetUserAction(pg);
  //SetUserAction(new PrimaryGeneratorActionGPS);
  auto ra = new RunAction(m_oFN);
  SetUserAction(ra);
  SetUserAction(new EventAction);
}
