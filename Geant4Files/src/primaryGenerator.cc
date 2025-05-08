#include "primaryGenerator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
	
}


MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}


void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

	//particle position
	G4double x = 0;
	G4double y = 0;
	G4double z = -1*m;
	
	G4ThreeVector pos(x, y, z);
	
	//particle momentum direction
	G4double px = 0;
	G4double py = 0;
	G4double pz = 1;
	
	G4ThreeVector mom(px, py, pz);
	
	//particle type
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle("proton");
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	//fParticleGun->SetParticleEnergy(1*GeV);
	fParticleGun->SetParticleEnergy(120*GeV);
	fParticleGun->SetParticleDefinition(particle);	
	
	//create vertex
	fParticleGun->GeneratePrimaryVertex(anEvent);
}
