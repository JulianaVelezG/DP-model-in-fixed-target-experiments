#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4PhysListFactory.hh"
#include "G4DecayPhysics.hh"

#include "G4ProductionCutsTable.hh"
#include "G4Gamma.hh"
#include "G4RegionStore.hh"

#include "construction.hh"
#include "QGSP_BERT.hh"
#include "actionInitialization.hh"


int main(int argc, char** argv)
{
	G4UIExecutive *ui = 0;
	
	if(argc == 1)
	{
		ui = new G4UIExecutive(argc, argv);
	}
	
	#ifdef G4MULTITHREADED
		G4MTRunManager *runManager = new G4MTRunManager;
	#else
		G4RunManager *runManager = new G4RunManager;
	#endif
	
	G4PhysListFactory factory;
	G4VModularPhysicsList *physList = factory.GetReferencePhysList("QGSP_BERT");
	
	//Physics lists
	runManager->SetUserInitialization(physList);	
	
	//Detector construction
	runManager->SetUserInitialization(new MyDetectorConstruction());
	
	//Action Initialization
	runManager->SetUserInitialization(new MyActionInitialization());
		
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	if(ui)
	{
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();	
	}
	else
	{
		G4String command = "/control/execute ";
		G4String filename = argv[1];
		UImanager->ApplyCommand(command+filename);
	}
		

	return 0;
}
