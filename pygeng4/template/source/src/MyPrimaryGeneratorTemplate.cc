#gunIncFunc_mono#
  void SetRootFileName(G4String fileName) {fRootFileName = fileName;};
  void SetTxtFileName(G4String fileName)  {fTxtFileName  = fileName;};
  void SetProgFileName(G4String fileName) {fProgFileName = fileName;};

  G4String GetRootFileName() {return fRootFileName;}
  G4String GetTxtFileName()  {return fTxtFileName;}
  G4String GetProgressFileName() {return fProgFileName;}

private:
  G4ParticleGun *fParticleGun;
  G4String fRootFileName;
  G4String fTxtFileName;
  G4String fProgFileName;
#end#
#gunSrcIni_mono#
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);
  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("$gunSrcIni_Particle$");

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy($gunSrcIni_Energy$);
  fParticleGun->SetParticlePosition(G4ThreeVector($gunSrcIni_Position$));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector($gunSrcIni_Direction$));
#end#
#gunSrcAct_mono#
  fParticleGun->GeneratePrimaryVertex(anEvent);
#end#
#gunMesIniDef_mono#

#end#
#gunMesSrcDef_mono#

#end#
#gunMesSrcDel_mono#

#end#
#gunMesSrcFunc_mono#

#end#



#gunIncFunc_gps#
private:
  G4GeneralParticleSource *fParticleSourceGun; 
#end#
#gunSrcIni_gps#
  // default general particle source
  fParticleSourceGun = new G4GeneralParticleSource();
  fParticleSourceGun->SetParticleDefinition(particle);

  G4SPSEneDistribution *eneDist = fParticleSourceGun->GetCurrentSource()->GetEneDist() ;
  eneDist->SetEnergyDisType("Mono");
  eneDist->SetMonoEnergy(30.*MeV);
 
  G4SPSPosDistribution *posDist = fParticleSourceGun->GetCurrentSource()->GetPosDist() ;
  posDist->SetPosDisType("Plane");
  posDist->SetPosDisShape("Circle");
  posDist->SetRadius(20.0*cm);
  posDist->SetCentreCoords(G4ThreeVector(0.,0.,0.));

  G4SPSAngDistribution *angDist = fParticleSourceGun->GetCurrentSource()->GetAngDist() ;
  angDist->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.)) ;
#end#
#gunSrcAct_gps#
  fParticleSourceGun->GeneratePrimaryVertex(anEvent);
#end#
#gunMesIniDef_gps#

#end#
#gunMesSrcDef_gps# 

#end#
#gunMesSrcDel_gps# 

#end#
#gunMesSrcFunc_gps# 

#end#
