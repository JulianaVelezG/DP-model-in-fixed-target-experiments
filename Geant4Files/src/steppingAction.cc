#include "steppingAction.hh"
#include "trackInformation.hh"
#include "trackingAction.hh"
#include <iomanip>


SteppingAction::SteppingAction(MyEventAction *eventAction)
{
	gammaFile.open("gamma.txt", std::ios::app);
	piZeroFile.open("piZero.txt",std::ios::app);
	gammaDecay.open("gammaDecay.txt", std::ios::app);
	gammaPiZeroExit.open("gammaPiZeroExit.txt", std::ios::app);
	
	gammaFile <<"energy,px,py,pz,processID\n";
	piZeroFile <<"energy,mass,px,py,pz\n";*/
	gammaDecay <<"energy\n";
	gammaPiZeroExit<<"energy\n";
}

SteppingAction::~SteppingAction()
{
	gammaFile.close();
	piZeroFile.close();
	gammaDecay.close();
	gammaPiZeroExit.close();
}

void SteppingAction::UserSteppingAction(const G4Step *step)
{
	//Track information
	G4Track *track = step->GetTrack();
	G4ThreeVector momentum = track->GetMomentum();
	G4String particleName = track->GetDefinition()->GetParticleName();
	G4AnalysisManager *man = G4AnalysisManager::Instance();	
	
	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	
	//momentum, mass and energy
	G4double px = momentum[0]/MeV;
	G4double py = momentum[1]/MeV;
	G4double pz = momentum[2]/MeV;
	G4double mass = track->GetDefinition()->GetPDGMass()/MeV;
	G4double energy = track->GetKineticEnergy()/MeV;
	
	
	//saving in root files
	if(particleName == "gamma")
	{
		// getting process of production
		const G4VProcess *creatorProcess = track->GetCreatorProcess();
		G4String processName = "Primary";
		if(creatorProcess)
		{
			processName = creatorProcess->GetProcessName();
		}
		
		static std::map<G4String, int> processMap = {
			{"neutronInelastic", 0},
			{"protonInelastic", 1},
			{"nCapture", 2},
			{"annihil", 3},
			{"eBrem", 4},
			{"alphaInelastic", 5},
			{"hBertiniCaptureAtRest", 6},
			{"He3Inelastic", 7},
			{"Decay", 8},
			{"muMinusCaptureAtRest", 9},
			{"pi+Inelastic", 10},
			{"dInelastic", 11},
			{"photonNuclear", 12},
			{"pi-Inelastic", 13},
			{"tInelastic", 14},
		};
		
		auto it = processMap.find(processName);
		int processID = (it != processMap.end()) ? it->second : -1;
		
		// check if the photon has left the target
		G4StepPoint *prePoint = step->GetPreStepPoint();
		G4StepPoint *postPoint = step->GetPostStepPoint();
		G4VPhysicalVolume *preVol = prePoint->GetPhysicalVolume();
		G4VPhysicalVolume *postVol = postPoint->GetPhysicalVolume();
		G4String preVolName = preVol ? preVol->GetName() : "NULL";
		G4String postVolName = postVol ? postVol->GetName() : "NULL";
		G4bool exitingTarget = false;
		
		if(preVolName != "physTargetDUNE")
		{
			exitingTarget = true;
		}
		
		if(preVolName == "physTargetDUNE" && postVolName != "physTargetDUNE")
		{
			exitingTarget = true;
		}
		if (exitingTarget)
		{
			man->FillNtupleIColumn(0, 0, evt);
			man->FillNtupleDColumn(0, 1, energy);
			man->FillNtupleDColumn(0, 2, px);
			man->FillNtupleDColumn(0, 3, py);
			man->FillNtupleDColumn(0, 4, pz);
			man->FillNtupleIColumn(0, 5, processID);
			man->AddNtupleRow(0);
		
			gammaFile << energy << "," << px << "," << py << "," << pz << "," << processName <<"\n";
		}
	}
	
	if (particleName == "pi0")
	{
		//getting creator process
		const G4VProcess *creatorProcess = track->GetCreatorProcess();
		G4String ProcessName = "Primary";
		if(creatorProcess)
		{
			ProcessName = creatorProcess->GetProcessName();
		}
		
		static std::map<G4String, int> processMap = {
			{"neutronInelastic", 0},
			{"protonInelastic", 1},
			{"nCapture", 2},
			{"annihil", 3},
			{"eBrem", 4},
			{"alphaInelastic", 5},
			{"hBertiniCaptureAtRest", 6},
			{"He3Inelastic", 7},
			{"Decay", 8},
			{"muMinusCaptureAtRest", 9},
			{"pi+Inelastic", 10},
			{"dInelastic", 11},
			{"photonNuclear", 12},
			{"pi-Inelastic", 13},
			{"tInelastic", 14},
		};
		
		auto it = processMap.find(ProcessName);
		int processID = (it != processMap.end()) ? it->second : -1;
	
		// getting the process that pi0 undergoes	
		G4String processName = "Undefined";
		if(step->GetPostStepPoint()->GetProcessDefinedStep() != nullptr)
		{
			processName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
		}
		
		// getting the energy of the products of the pi0 decay
		const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();
		for(size_t i = 0; i<secondaries->size(); i++)
		{
			G4String secName = (*secondaries)[i]->GetDefinition()->GetParticleName();
			G4double secEnergy = (*secondaries)[i]->GetKineticEnergy()/MeV;
			if (secName == "gamma")
			{
				gammaDecay << secEnergy << "\n";
				
				man->FillNtupleIColumn(2, 0, evt);
				man->FillNtupleDColumn(2, 1, secEnergy);
				man->AddNtupleRow(2);
				
				// check if the photon left the target
				G4StepPoint *prePoint = step->GetPreStepPoint();
				G4StepPoint *postPoint = step->GetPostStepPoint();
				G4VPhysicalVolume *preVol = prePoint->GetPhysicalVolume();
				G4VPhysicalVolume *postVol = postPoint->GetPhysicalVolume();
				G4String preVolName = preVol ? preVol->GetName() : "NULL";
				G4String postVolName = postVol ? postVol->GetName() : "NULL";
				
				G4bool exitingTarget = (postVolName != "physTargetDUNE");
				if(preVolName == "physTargetDUNE" && postVolName != "physTargetDUNE")
				{
					exitingTarget = true;
				}
				
				if(exitingTarget)
				{
					gammaPiZeroExit << secEnergy << "\n";
					man->FillNtupleIColumn(3, 0, evt);
					man->FillNtupleDColumn(3, 1, secEnergy);
					man->AddNtupleRow(3);
				}
				
			}

		}
		
		G4double energy = track->GetTotalEnergy() / MeV;
		G4double computedMass = std::sqrt(energy*energy - momentum.mag2()) / MeV;
		
		man->FillNtupleIColumn(1, 0, evt);
		man->FillNtupleDColumn(1, 1, energy);
		man->FillNtupleDColumn(1, 2, mass);
		man->FillNtupleDColumn(1, 3, px);
		man->FillNtupleDColumn(1, 4, py);
		man->FillNtupleDColumn(1, 5, pz);
		man->FillNtupleIColumn(1, 6, processID);
		man->AddNtupleRow(1);
			
		
		if(computedMass == mass)
		{	
			piZeroFile << std::fixed << std::setprecision(16) << energy << "," << mass << "," << px << "," << py << "," << pz << "," << "\n";
		}
	}
	
}
