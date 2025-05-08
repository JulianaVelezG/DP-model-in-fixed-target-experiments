#include "run.hh"
#include "G4RunManager.hh"

MyRunAction::MyRunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	man->CreateNtuple("gamma", "Gamma data");
	man->CreateNtupleIColumn("Event");
	man->CreateNtupleDColumn("Energy");
	man->CreateNtupleDColumn("pX");
	man->CreateNtupleDColumn("pY");
	man->CreateNtupleDColumn("pZ");
	man->CreateNtupleIColumn("process");
	man->FinishNtuple(0);
	
	man->CreateNtuple("piZero", "Pi0 data");
	man->CreateNtupleIColumn("Event");
	man->CreateNtupleDColumn("Energy");
	man->CreateNtupleDColumn("mass");
	man->CreateNtupleDColumn("pX");
	man->CreateNtupleDColumn("pY");
	man->CreateNtupleDColumn("pZ");
	man->CreateNtupleIColumn("process");
	man->FinishNtuple(1);
	
	man->CreateNtuple("gammaDecay", "Photon energy");
	man->CreateNtupleIColumn("Event");
	man->CreateNtupleDColumn("Energy");
	man->FinishNtuple(2);
	
	man->CreateNtuple("gammaPiZeroExit", "Photon energy");
	man->CreateNtupleIColumn("Event");
	man->CreateNtupleDColumn("Energy");
	man->FinishNtuple(3);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run *run)
{
	G4int runID = run->GetRunID();
	std::stringstream strRunID;
	strRunID << runID;
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->OpenFile("products" + strRunID.str() + ".root");
	
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->Write();
	man->CloseFile();
	
	delete G4RunManager::GetRunManager()->GetUserSteppingAction();
}
