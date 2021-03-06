
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4UniformMagField.hh"
#include "G4AutoDelete.hh"

#include "G4ProductionCuts.hh"
#include "G4HadronicProcessStore.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"
#include "G4SDManager.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Verbose.hh"

#include "$MyDetectorConstruction$.hh"
#include "$MyDetectorMessenger$.hh"
$detSrcInc$

$MyDetectorConstruction$::$MyDetectorConstruction$()
    : G4VUserDetectorConstruction()
{
  if (verbose)
    G4cout << "====>$MyDetectorConstruction$::$MyDetectorConstruction$()" << G4endl;

  fStepLimit = 0;
  checkOverlaps = 0;
  for (int i = 0; i < SIZE; i++) fDetPar[i] = new MyDetectorParameters();
  for (int i = 0; i < SIZE; i++) fSolid[i] = NULL;
  for (int i = 0; i < SIZE; i++) fLogic[i] = NULL;
  for (int i = 0; i < SIZE; i++) fPhysc[i] = NULL;

  fDetectorMessenger = new $MyDetectorMessenger$(this);

  DefineMaterials();

$detSrcIni$

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

$MyDetectorConstruction$::~$MyDetectorConstruction$()
{
  delete fDetectorMessenger;
  delete fStepLimit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume *$MyDetectorConstruction$::Construct()
{
  if (verbose)
    G4cout << "====>$MyDetectorConstruction$::Construct()" << G4endl;

  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume *$MyDetectorConstruction$::DefineVolumes()
{
  if (verbose)
    G4cout << "====>G4VPhysicalVolume* MyDetectorConstruction::DefineVolumes()" << G4endl;

  for (int i = 0; i < SIZE; i++)
  {
    if (fPhysc[i] != NULL) delete fPhysc[i];
    if (fLogic[i] != NULL) delete fLogic[i];
    if (fSolid[i] != NULL) delete fSolid[i];
  }

  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // Define volume

$detSrcVol$

  G4SDManager* SDManager = G4SDManager::GetSDMpointer();
$detSrcSD$

$detSrcVis$

  return fPhysc[WORLD];;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyDetectorConstruction$::Update()
{
  G4RunManager::GetRunManager()->ReinitializeGeometry();
  G4RunManager::GetRunManager()->DefineWorldVolume(DefineVolumes());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void $MyDetectorConstruction$::SetMaterial(int id, G4String materialName)
{
  if (verbose)
    G4cout << "====>void $MyDetectorConstruction$::SetMaterial(int id, G4String materialName)" << G4endl;

  // search the material by its name, or build it from nist data base
  G4Material *pttoMaterial = G4NistManager::Instance()->FindOrBuildMaterial(materialName);

  if (pttoMaterial && fDetPar[id]->Material != pttoMaterial)
  {
    fDetPar[id]->Matt = materialName;
    fDetPar[id]->Material = pttoMaterial;
    if (fLogic[id])
      fLogic[id]->SetMaterial(fDetPar[id]->Material);
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  }
}

void $MyDetectorConstruction$::DefineMaterials()
{
  //This function illustrates the possible ways to define materials

  G4String symbol;             //a=mass of a mole;
  G4double a, z, density;      //z=mean number of protons;  

  G4int ncomponents, natoms;
  G4double fractionmass;
  G4double temperature, pressure;
 
  //-----------------------------------------------------------------------------
  // define Elements
  //
  G4Element* H  = new G4Element("Hydrogen", symbol="H",  z= 1, a=   1.01*g/mole);
  G4Element* He = new G4Element("Helium",   symbol="He", z= 2.,a=   4.00*g/mole);
  G4Element* C  = new G4Element("Carbon",   symbol="C",  z= 6, a=  12.01*g/mole);
  G4Element* elN= new G4Element("Nitrogen", symbol="N",  z= 7, a=  14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen",   symbol="O",  z= 8, a=  16.00*g/mole);
  G4Element* F  = new G4Element("Fluorine", symbol="F",  z= 9, a=  19.00*g/mole);
  G4Element* Ne = new G4Element("Neon",     symbol="Ne", z=10, a=  20.17*g/mole);
  G4Element* Na = new G4Element("Sodium",   symbol="Na", z=11, a=  22.99*g/mole);
  G4Element* Si = new G4Element("Silicon",  symbol="Si", z=14, a=  28.09*g/mole);
  G4Element* S  = new G4Element("Sulfur",   symbol="S",  z=16.,a=  32.066*g/mole);
  G4Element* Ar = new G4Element("Argon",    symbol="Ar", z=18, a=  39.95*g/mole);
  G4Element* Cr = new G4Element("Chrome",   symbol="Cr", z=25, a=  51.996*g/mole);
  G4Element* Fe = new G4Element("Iron"  ,   symbol="Fe", z=26, a=  55.845*g/mole);
  G4Element* Co = new G4Element("Cobalt",   symbol="Co", z=27, a=  58.933*g/mole);
  G4Element* Ni = new G4Element("Nickel",   symbol="Ni", z=28, a=  58.693*g/mole);
  G4Element* Br = new G4Element("Bromine",  symbol="Br", z=35, a=  79.904*g/mole);
  G4Element* Y  = new G4Element("Yttrium",  symbol="Y",  z=39, a=  88.91*g/mole);
  G4Element* I  = new G4Element("Iodine",   symbol="I" , z=53, a= 126.90*g/mole);
  G4Element* Xe = new G4Element("Xenon",    symbol="Xe", z=54, a= 131.29*g/mole);
  G4Element* La = new G4Element("Lanthanum",symbol="La", z=57, a= 138.9055*g/mole);
  G4Element* Ce = new G4Element("Cerium",   symbol="Ce", z=58, a= 140.12*g/mole);
  G4Element* Lu = new G4Element("Lutetium", symbol="Lu", z=71, a= 174.97*g/mole);
  G4Element* W  = new G4Element("Tungsten", symbol="W",  z=74, a= 183.850*g/mole);

  G4Isotope* GdIsotope1 = new G4Isotope("Gd_152", 64, 152, 152.0*g/mole);
  G4Isotope* GdIsotope2 = new G4Isotope("Gd_154", 64, 154, 154.0*g/mole);
  G4Isotope* GdIsotope3 = new G4Isotope("Gd_155", 64, 155, 155.0*g/mole);
  G4Isotope* GdIsotope4 = new G4Isotope("Gd_156", 64, 156, 156.0*g/mole);
  G4Isotope* GdIsotope5 = new G4Isotope("Gd_157", 64, 157, 157.0*g/mole);
  G4Isotope* GdIsotope6 = new G4Isotope("Gd_158", 64, 158, 158.0*g/mole);
  G4Isotope* GdIsotope7 = new G4Isotope("Gd_160", 64, 160, 160.0*g/mole);

  G4Element* Gd = new G4Element("Gadolinium", "Gd", 7);
  Gd->AddIsotope(GdIsotope1, 100.0*0.002*152/157.318*perCent);
  Gd->AddIsotope(GdIsotope2, 100.0*0.022*154/157.318*perCent);
  Gd->AddIsotope(GdIsotope3, 100.0*0.149*155/157.318*perCent);
  Gd->AddIsotope(GdIsotope4, 100.0*0.206*156/157.318*perCent);
  Gd->AddIsotope(GdIsotope5, 100.0*0.157*157/157.318*perCent);
  Gd->AddIsotope(GdIsotope6, 100.0*0.247*158/157.318*perCent);
  Gd->AddIsotope(GdIsotope7, 100.0*0.217*160/157.318*perCent);


  //-----------------------------------------------------------------------------
  // define simple materials
  //
  new G4Material("H2Liq"    , z= 1, a= 1.01*g/mole, density= 70.8*mg/cm3);
  new G4Material("Beryllium", z= 4, a= 9.01*g/mole, density= 1.848*g/cm3);
  new G4Material("Aluminium", z=13, a=26.98*g/mole, density= 2.700*g/cm3);
  new G4Material("Silicon"  , z=14, a=28.09*g/mole, density= 2.330*g/cm3);
  new G4Material("Iron",      z=26, a= 55.85*g/mole, density= 7.870*g/cm3);
  new G4Material("Copper",    z=29, a= 63.55*g/mole, density= 8.960*g/cm3);
  new G4Material("Germanium", z=32, a= 72.61*g/mole, density= 5.323*g/cm3);
  new G4Material("Silver",    z=47, a=107.87*g/mole, density= 10.50*g/cm3);
  new G4Material("Tungsten",  z=74, a=183.85*g/mole, density= 19.30*g/cm3);
  new G4Material("Gold",      z=79, a=196.97*g/mole, density= 19.32*g/cm3);
  new G4Material("Lead",      z=82, a=207.19*g/mole, density= 11.35*g/cm3);

  //-----------------------------------------------------------------------------
  // define scintillator
  // 定义闪烁体
  G4Material* CH = new G4Material("Plastic",density= 1.04*g/cm3, ncomponents=2);
  CH->AddElement(C, natoms=1);
  CH->AddElement(H, natoms=1);

  G4Material* NaI = new G4Material("NaI", density= 3.67*g/cm3, ncomponents=2);
  NaI->AddElement(Na, natoms=1);
  NaI->AddElement(I , natoms=1);
  NaI->GetIonisation()->SetMeanExcitationEnergy(452*eV);

  G4Material* LaBr3 = new G4Material("LaBr3", density= 5.06*g/cm3, ncomponents=2);
  LaBr3->AddElement(La, natoms=1);
  LaBr3->AddElement(Br, natoms=3);

  G4Material* LSO = new G4Material("Lu2SiO5", 7.4*g/cm3, 3);
  LSO->AddElement(Lu, 2);
  LSO->AddElement(Si, 1);
  LSO->AddElement(O , 5);

  // LYSO:Ce,   Assuming Lu2(x-1)Y2(x)SiO5:Ce. x=10%, Ce=5%. 
  // So, Ce=5%, LYSO=95%.(mole faction) => mass fraction: Ce=0.19%, LYSO=99.91%
  // then for LYSO, the same as above
  G4Material *Scint_mat = new G4Material("Scint", density=7.4*g/cm3, ncomponents = 4);
  Scint_mat->AddElement(Lu, 71*perCent);
  Scint_mat->AddElement(Si, 7*perCent);
  Scint_mat->AddElement(O, 18*perCent);
  Scint_mat->AddElement(Y, 4*perCent);

  G4Material *LYSO = new G4Material("LYSO", density=7.4*g/cm3, ncomponents = 2);
  LYSO->AddMaterial(Scint_mat, 99.81*perCent);
  LYSO->AddElement(Ce, 0.19*perCent);

  //-----------------------------------------------------------------------------
  // define metal
  // 定义金属
  G4Material* Graphite = new G4Material("Graphite", density= 1.7*g/cm3, ncomponents=1);
  Graphite->AddElement(C, fractionmass=1.);

  //Havar 合金
  G4Material* Havar = new G4Material("Havar", density= 8.3*g/cm3, ncomponents=5);
  Havar->AddElement(Cr, fractionmass=0.1785);
  Havar->AddElement(Fe, fractionmass=0.1822);
  Havar->AddElement(Co, fractionmass=0.4452);
  Havar->AddElement(Ni, fractionmass=0.1310);
  Havar->AddElement(W , fractionmass=0.0631);

  //-----------------------------------------------------------------------------
  // define water
  // 定义水
  G4Material* H2O = new G4Material("Water",density= 1.000*g/cm3, ncomponents=2);
  H2O->AddElement(H, natoms=2);
  H2O->AddElement(O, natoms=1);
  H2O->GetIonisation()->SetMeanExcitationEnergy(78*eV);

  G4Material* steam = new G4Material("WaterSteam", density= 1.0*mg/cm3, ncomponents=1);
  steam->AddMaterial(H2O, fractionmass=1.);
  steam->GetIonisation()->SetMeanExcitationEnergy(71.6*eV);

  //-----------------------------------------------------------------------------  
  // example of vacuum
  // 定义真空
  density     = universe_mean_density;    //from PhysicalConstants.h
  pressure    = 3.e-18*pascal;
  temperature = 2.73*kelvin;
  new G4Material("Galactic", z=1, a=1.01*g/mole,density, kStateGas,temperature,pressure);

  //-----------------------------------------------------------------------------
  // JUNO & Dayabay etc. related
  //  
  G4Material* LS = new G4Material("LS", 0.859*g/cm3, 5);
  LS->AddElement(C, 0.87924);
  LS->AddElement(H, 0.1201);
  LS->AddElement(O, 0.00034);
  LS->AddElement(elN, 0.00027);
  LS->AddElement(S, 0.00005);

  G4Material* ESR = new G4Material("ESR", 1.0*g/cm3, 2);
  ESR->AddElement(H, 2.*1.00794/(12.0107+2.*1.00794));
  ESR->AddElement(C, 12.0107/(12.0107+2.*1.00794));

  G4Material* Tyvek = new G4Material("Tyvek", 0.94*g/cm3, 2);
  Tyvek->AddElement(C, 2);
  Tyvek->AddElement(H, 4);

  G4Material* Acrylic = new G4Material("Acrylic", 1.18*g/cm3, 3);
  Acrylic->AddElement(C, 0.59984);
  Acrylic->AddElement(H, 0.08055);
  Acrylic->AddElement(O, 0.31961);

  G4Material* GdLS  = new G4Material("GdDopedLS", 0.8602*g/cm3, 6);
  GdLS->AddElement(C,  0.87705);
  GdLS->AddElement(H,  0.12051);
  GdLS->AddElement(O,  0.00109);
  GdLS->AddElement(Gd, 0.0010315);
  GdLS->AddElement(elN,  0.00027);
  GdLS->AddElement(S,  0.00005);

  //-----------------------------------------------------------------------------
  // define air
  // 定义空气
  G4Material* Air = new G4Material("Air", density= 1.290*mg/cm3, ncomponents=2);
  Air->AddElement(elN, fractionmass=0.7);
  Air->AddElement(O, fractionmass=0.3);

  G4Material* Air20 = new G4Material("Air20", density= 1.205*mg/cm3, ncomponents=2, kStateGas, 293.*kelvin, 1.*atmosphere);
  Air20->AddElement(elN, fractionmass=0.7);
  Air20->AddElement(O, fractionmass=0.3);

  //-----------------------------------------------------------------------------
  // define argon and xenon
  // 定义氩气和氙气
  new G4Material("ArgonGas", z=18, a=39.948*g/mole, density= 1.782*mg/cm3, kStateGas, 273.15*kelvin, 1*atmosphere);
  new G4Material("XenonGas", z=54, a=131.29*g/mole, density= 5.458*mg/cm3, kStateGas, 293.15*kelvin, 1*atmosphere);

  new G4Material("Ar_P0_1", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 0.1, kStateGas, 293.15*kelvin, atmosphere * 1.5);
  new G4Material("Ar_P0_3", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 0.3, kStateGas, 293.15*kelvin, atmosphere * 1.5);
  new G4Material("Ar_P0_5", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 0.5, kStateGas, 293.15*kelvin, atmosphere * 1.5);
  new G4Material("Ar_P0_8", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 0.8, kStateGas, 293.15*kelvin, atmosphere * 1.5);
  new G4Material("Ar_P1_0", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 1.0, kStateGas, 293.15*kelvin, atmosphere * 1.5);
  new G4Material("Ar_P2_0", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 2.0, kStateGas, 293.15*kelvin, atmosphere * 2.0);
  new G4Material("Ar_P2_5", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 2.5, kStateGas, 293.15*kelvin, atmosphere * 2.5);
  new G4Material("Ar_P3_0", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 3.0, kStateGas, 293.15*kelvin, atmosphere * 3.0);
  new G4Material("Ar_P3_5", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 3.5, kStateGas, 293.15*kelvin, atmosphere * 3.5);
  new G4Material("Ar_P4_0", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 4.0, kStateGas, 293.15*kelvin, atmosphere * 4.0);
  new G4Material("Ar_P5_0", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 5.0, kStateGas, 293.15*kelvin, atmosphere * 5.0);
  new G4Material("Ar_P10_0",z=18, a=39.95*g/mole, 1.782*mg/cm3 *10.0, kStateGas, 293.15*kelvin, atmosphere * 10.0);

  new G4Material("Xe_P10_0", z=54, a=131.29*g/mole, 5.48536*mg/cm3 * 10.0, kStateGas, 293.15*kelvin, atmosphere * 10.0);

  G4Material* lAr = new G4Material("liquidArgon", density= 1.390*g/cm3, ncomponents=1);
  lAr->AddElement(Ar, natoms=1);

  G4Material* lXe = new G4Material("liquidXenon", density= 2.942*g/cm3, ncomponents=1);
  lXe->AddElement(Xe, natoms=1);



  //-----------------------------------------------------------------------------
  // my concern of gas
  //  
  // define higher pressure of Argon
  // 

  //-----------------------------------------------------------------------------
  // examples of gas
  //  
  G4Material* CO2 = new G4Material("CarbonicGas", density= 1.977*mg/cm3, ncomponents=2);
  CO2->AddElement(C, natoms=1);
  CO2->AddElement(O, natoms=2);

  G4Material* CF4 = new G4Material("CF4", density= 3.720*mg/cm3, ncomponents=2);
  CF4->AddElement(C, natoms=1);
  CF4->AddElement(F, natoms=4);

  G4Material* CF4_P3 = new G4Material("CF4_P3_0", density= 3.0 * 3.720*mg/cm3, ncomponents=2);
  CF4_P3->AddElement(C, natoms=1);
  CF4_P3->AddElement(F, natoms=4);

  G4Material* CF4_P5 = new G4Material("CF4_P5_0", density= 5.0 * 3.720*mg/cm3, ncomponents=2);
  CF4_P5->AddElement(C, natoms=1);
  CF4_P5->AddElement(F, natoms=4);

  G4Material* CF4_P10 = new G4Material("CF4_P10_0", density= 10.0 * 3.720*mg/cm3, ncomponents=2);
  CF4_P10->AddElement(C, natoms=1);
  CF4_P10->AddElement(F, natoms=4);

  //double rho_DME=0.00197, rho_He=0.0001786, rho_Ne=0.0009002, rho_CF4=0.00372;
  G4Material* DME = new G4Material("DME",density=0.00197*g/cm3,ncomponents=3);
  DME->AddElement(H,natoms=6);
  DME->AddElement(C,natoms=2);
  DME->AddElement(O,natoms=1);

  //-----------------------------------------------------------------------------
  // examples of gas mixture
  //  
  G4Material* ArCO2 = new G4Material("ArgonCO2",   density= 1.8223*mg/cm3, ncomponents=2);
  ArCO2->AddElement (Ar,  fractionmass=0.7844);
  ArCO2->AddMaterial(CO2, fractionmass=0.2156);

  //---------------- He:DME = 20:80 -------------------
  G4Material* He_20_DME_80 = new G4Material("He_20_DME_80",density = 0.001932*g/cm3,ncomponents=2);
  He_20_DME_80->AddElement(He,    fractionmass=2.7*perCent);
  He_20_DME_80->AddMaterial(DME,fractionmass=97.3*perCent);

  G4Material* He_20_DME_80_P0_5 = new G4Material("He_20_DME_80_P0_5",density = 0.001932*0.5*g/cm3,ncomponents=2);
  He_20_DME_80_P0_5->AddElement(He,    fractionmass=2.7*perCent);
  He_20_DME_80_P0_5->AddMaterial(DME,fractionmass=97.3*perCent);

  G4Material* He_20_DME_80_P0_6 = new G4Material("He_20_DME_80_P0_6",density = 0.001932*0.6*g/cm3,ncomponents=2);
  He_20_DME_80_P0_6->AddElement(He,    fractionmass=2.7*perCent);
  He_20_DME_80_P0_6->AddMaterial(DME,fractionmass=97.3*perCent);

  G4Material* He_20_DME_80_P0_7 = new G4Material("He_20_DME_80_P0_7",density = 0.001932*0.7*g/cm3,ncomponents=2);
  He_20_DME_80_P0_7->AddElement(He,    fractionmass=2.7*perCent);
  He_20_DME_80_P0_7->AddMaterial(DME,fractionmass=97.3*perCent);

  G4Material* He_20_DME_80_P0_8 = new G4Material("He_20_DME_80_P0_8",density = 0.001932*0.8*g/cm3,ncomponents=2);
  He_20_DME_80_P0_8->AddElement(He,    fractionmass=2.7*perCent);
  He_20_DME_80_P0_8->AddMaterial(DME,fractionmass=97.3*perCent);

  //---------------- Ne:DME = 80:20 -------------------
  G4Material* Ne_80_DME_20 = new G4Material("Ne_80_DME_20",density = 0.00111416*g/cm3,ncomponents=2);
  Ne_80_DME_20->AddElement(Ne,    fractionmass=99.92*perCent);
  Ne_80_DME_20->AddMaterial(DME,fractionmass=0.08*perCent);

  G4Material* Ne_80_DME_20_P0_5 = new G4Material("Ne_80_DME_20_P0_5",density = 0.00111416*0.5*g/cm3,ncomponents=2);
  Ne_80_DME_20_P0_5->AddElement(Ne,    fractionmass=99.92*perCent);
  Ne_80_DME_20_P0_5->AddMaterial(DME,fractionmass=0.08*perCent);

  G4Material* Ne_80_DME_20_P0_6 = new G4Material("Ne_80_DME_20_P0_6",density = 0.00111416*0.6*g/cm3,ncomponents=2);
  Ne_80_DME_20_P0_6->AddElement(Ne,    fractionmass=99.92*perCent);
  Ne_80_DME_20_P0_6->AddMaterial(DME,fractionmass=0.08*perCent);

  G4Material* Ne_80_DME_20_P0_7 = new G4Material("Ne_80_DME_20_P0_7",density = 0.00111416*0.7*g/cm3,ncomponents=2);
  Ne_80_DME_20_P0_7->AddElement(Ne,    fractionmass=99.92*perCent);
  Ne_80_DME_20_P0_7->AddMaterial(DME,fractionmass=0.08*perCent);

  G4Material* Ne_80_DME_20_P0_8 = new G4Material("Ne_80_DME_20_P0_8",density = 0.00111416*0.8*g/cm3,ncomponents=2);
  Ne_80_DME_20_P0_8->AddElement(Ne,    fractionmass=99.92*perCent);
  Ne_80_DME_20_P0_8->AddMaterial(DME,fractionmass=0.08*perCent);

  //---------------- Ne:CF4 = 95:5 -------------------
  G4Material* Ne_95_CF4_5 = new G4Material("Ne_95_CF4_5", density = 0.00104119*g/cm3, ncomponents = 2);
  Ne_95_CF4_5->AddElement(Ne  , fractionmass = 82.14*perCent);
  Ne_95_CF4_5->AddMaterial(CF4, fractionmass = 17.86*perCent);

  G4Material* Ne_95_CF4_5_P0_5 = new G4Material("Ne_95_CF4_5_P0_5", density = 0.00104119*0.5*g/cm3, ncomponents = 2);
  Ne_95_CF4_5_P0_5->AddElement(Ne  , fractionmass = 82.14*perCent);
  Ne_95_CF4_5_P0_5->AddMaterial(CF4, fractionmass = 17.86*perCent);

  G4Material* Ne_95_CF4_5_P0_6 = new G4Material("Ne_95_CF4_5_P0_6", density = 0.00104119*0.6*g/cm3, ncomponents = 2);
  Ne_95_CF4_5_P0_6->AddElement(Ne  , fractionmass = 82.14*perCent);
  Ne_95_CF4_5_P0_6->AddMaterial(CF4, fractionmass = 17.86*perCent);

  G4Material* Ne_95_CF4_5_P0_7 = new G4Material("Ne_95_CF4_5_P0_7", density = 0.00104119*0.7*g/cm3, ncomponents = 2);
  Ne_95_CF4_5_P0_7->AddElement(Ne  , fractionmass = 82.14*perCent);
  Ne_95_CF4_5_P0_7->AddMaterial(CF4, fractionmass = 17.86*perCent);

  G4Material* Ne_95_CF4_5_P0_8 = new G4Material("Ne_95_CF4_5_P0_8", density = 0.00104119*0.8*g/cm3, ncomponents = 2);
  Ne_95_CF4_5_P0_8->AddElement(Ne  , fractionmass = 82.14*perCent);
  Ne_95_CF4_5_P0_8->AddMaterial(CF4, fractionmass = 17.86*perCent);

  //G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......