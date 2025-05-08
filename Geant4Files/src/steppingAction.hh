#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "run.hh"

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTypes.hh"
#include "G4VProcess.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include <fstream>
#include "event.hh"
#include "G4StepPoint.hh"

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(MyEventAction *eventAction);
	~SteppingAction();
	
	virtual void UserSteppingAction(const G4Step*);
	
private:
	std::ofstream gammaFile;
	std::ofstream piZeroFile;
	std::ofstream gammaDecay;
	std::ofstream gammaPiZeroExit;
	
};

#endif


