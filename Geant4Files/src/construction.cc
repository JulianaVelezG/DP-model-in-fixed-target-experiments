#include "construction.hh"


MyDetectorConstruction::MyDetectorConstruction()
{}


MyDetectorConstruction::~MyDetectorConstruction()
{}


G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4bool checkOverlaps = true;
	
	G4NistManager *nist = G4NistManager::Instance();
	
	G4Element *Fe = new G4Element("Iron", "Fe", 26, 55.845*g/mole);
	G4Element *Mn = new G4Element("Manganese", "Mn", 25, 54.94*g/mole);
	G4Element *Si = new G4Element("Silicon", "Si", 14, 28.09*g/mole);
	G4Element *Cr = new G4Element("Chromium", "Cr", 24, 52*g/mole);
	G4Element *Ni = new G4Element("Nickel", "Ni", 28, 58.7*g/mole);
	G4Element *C = new G4Element("Carbon", "C", 6, 12.01*g/mole);
	
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	G4Material *targetMaterial = nist->FindOrBuildMaterial("G4_Hg");
	G4Material *steel = new G4Material("steel", 8.02*g/cm3,5);
	steel->AddElement(Mn, 0.02);
	steel->AddElement(Si, 0.01);
	steel->AddElement(Cr, 0.19);
	steel->AddElement(Ni, 0.10);
	steel->AddElement(Fe, 0.68);
	G4Material *graphite = new G4Material("graphite", 2.25*g/cm3,1);
	graphite->AddElement(C, 1);
	
	G4double xWorld = 20*m;
	G4double yWorld = 20*m;
	G4double zWorld = 20*m;
	
	G4double xTargetSNS = 39.9*cm;
	G4double yTargetSNS = 10.4*cm;
	G4double zTargetSNS = 50*cm;
	
	G4double rTargetDUNE = 8*mm;
	G4double zTargetDUNE = 2.2*m;
	
	G4double posxTarget = 0;
	G4double posyTarget = 0;
	G4double poszTarget = 1.1*m;
	
	G4double xTargetCasing = 40.9*cm;
	G4double yTargetCasing = 11.4*cm;
	G4double zTargetCasing = 51*cm;
	
	G4Box *solidWorld = new G4Box("solidWorld", xWorld/2, yWorld/2, zWorld/2);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicWorld, "physWorld", 0, false, 0, checkOverlaps);
	
	/* SNS
	
	G4Box *solidTargetCasing = new G4Box("solidTargetCasing", xTargetCasing/2, yTargetCasing/2, zTargetCasing/2);
	G4LogicalVolume *logicTargetCasing = new G4LogicalVolume(solidTargetCasing, steel, "logicTargetCasing");
	G4VPhysicalVolume *physTargetCasing = new G4PVPlacement(0, G4ThreeVector(posxTarget, posyTarget, poszTarget), logicTargetCasing, "physTargetCasing", logicWorld, false, 0, checkOverlaps);
	
	G4Box *solidTarget = new G4Box("solidTarget", xTargetSNS/2, yTargetSNS/2, zTargetSNS/2);
	G4LogicalVolume *logicTarget = new G4LogicalVolume(solidTarget, targetMaterial, "logicTarget");
	G4VPhysicalVolume *physTarget = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicTarget, "physTarget", logicTargetCasing, false, 0, checkOverlaps);*/
	
	//DUNE
	
	G4Tubs *solidTargetDUNE = new G4Tubs("solidTargetDUNE", 0, rTargetDUNE, zTargetDUNE/2, 0, 360*deg);
	G4LogicalVolume *logicTargetDUNE = new G4LogicalVolume(solidTargetDUNE, graphite, "logicTargetDUNE");
	G4VPhysicalVolume *physTargetDUNE = new G4PVPlacement(nullptr, G4ThreeVector(posxTarget, posyTarget, poszTarget), logicTargetDUNE, "physTargetDUNE", logicWorld, false, 0, checkOverlaps);
	
	
	
	return physWorld;
}
