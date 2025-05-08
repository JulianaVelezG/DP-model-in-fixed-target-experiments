#include "actionInitialization.hh"
#include "steppingAction.hh"
#include "trackingAction.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const
{
	MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);
}

void MyActionInitialization::Build() const
{
	MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);

	MyEventAction *eventAction = new MyEventAction(runAction);
	SetUserAction(eventAction);
	
	MyPrimaryGenerator *generator = new MyPrimaryGenerator();
	SetUserAction(generator);
	
	SteppingAction *steppingAction = new SteppingAction(eventAction);
	SetUserAction(steppingAction);
}
