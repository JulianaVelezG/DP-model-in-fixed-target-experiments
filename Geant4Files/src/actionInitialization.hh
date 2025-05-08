#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "primaryGenerator.hh"
#include "run.hh"
#include "event.hh"
#include "steppingAction.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
public:
	MyActionInitialization();
	~MyActionInitialization();
	
	virtual void BuildForMaster() const;
	virtual void Build() const;
};

#endif
