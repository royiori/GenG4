#gunIncFunc_mono#
private:
  G4ParticleGun *fParticleGun; 
#end#
#gunSrcIni_mono#
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);
  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("$gunSrcIni_Particle$");

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy('$gunSrcIni_Energy$');
  fParticleGun->SetParticlePosition(G4ThreeVector('$gunSrcIni_Position'));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector('gunSrcIni_Direction'));
#end#
#gunSrcAct_mono#
  fParticleGun->GeneratePrimaryVertex(anEvent);
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

