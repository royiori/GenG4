#detIniFunc_Box#
  void Set$detIniFunc_detName$SizeHalfX(G4double x) {fDetPar[$detIniFunc_detID$]->Siz[0] = x;}
  void Set$detIniFunc_detName$SizeHalfY(G4double y) {fDetPar[$detIniFunc_detID$]->Siz[1] = y;}
  void Set$detIniFunc_detName$SizeHalfZ(G4double z) {fDetPar[$detIniFunc_detID$]->Siz[2] = z;}
  G4double Get$detIniFunc_detName$SizeHalfX() { return fDetPar[$detIniFunc_detID$]->Siz[0]; }
  G4double Get$detIniFunc_detName$SizeHalfY() { return fDetPar[$detIniFunc_detID$]->Siz[1]; }
  G4double Get$detIniFunc_detName$SizeHalfZ() { return fDetPar[$detIniFunc_detID$]->Siz[2]; }
#end#
#detSrcIni_Box#
  fDetPar[$detSrcIni_detID$]->Name  = "$detSrcIni_detName$";
  fDetPar[$detSrcIni_detID$]->VType = "$detSrcIni_detShape$";
  fDetPar[$detSrcIni_detID$]->Matt  = "$detSrcIni_detMatt$";
  fDetPar[$detSrcIni_detID$]->Siz[0] = $detSrcIni_Siz0$*mm;
  fDetPar[$detSrcIni_detID$]->Siz[1] = $detSrcIni_Siz1$*mm;
  fDetPar[$detSrcIni_detID$]->Siz[2] = $detSrcIni_Siz2$*mm;
  fDetPar[$detSrcIni_detID$]->Pos[0] = $detSrcIni_Pos0$*mm;
  fDetPar[$detSrcIni_detID$]->Pos[1] = $detSrcIni_Pos1$*mm;
  fDetPar[$detSrcIni_detID$]->Pos[2] = $detSrcIni_Pos2$*mm;
  fDetPar[$detSrcIni_detID$]->Rot[0] = $detSrcIni_Rot0$;
  fDetPar[$detSrcIni_detID$]->Rot[1] = $detSrcIni_Rot1$;
  fDetPar[$detSrcIni_detID$]->Rot[2] = $detSrcIni_Rot2$;
  fDetPar[$detSrcIni_detID$]->visAtt = new G4VisAttributes(G4Colour($detSrcIni_Vis$));
  fDetPar[$detSrcIni_detID$]->visAtt->SetVisibility($detSrcIni_vEnable$);
  fDetPar[$detSrcIni_detID$]->visAtt->SetForceSolid($detSrcIni_vSolid$);
  fDetPar[$detSrcIni_detID$]->Material = NULL;
  fDetPar[$detSrcIni_detID$]->Region = NULL;
  SetMaterial($detSrcIni_detID$, fDetPar[$detSrcIni_detID$]->Matt);
#end#
#detSrcVol_Box#
  fSolid[$detSrcVol_detID$]  = new G4Box(fDetPar[$detSrcVol_detID$]->Name, fDetPar[$detSrcVol_detID$]->Siz[0], fDetPar[$detSrcVol_detID$]->Siz[1], fDetPar[$detSrcVol_detID$]->Siz[2]);

  fLogic[$detSrcVol_detID$] = new G4LogicalVolume(fSolid[$detSrcVol_detID$], fDetPar[$detSrcVol_detID$]->Material, fDetPar[$detSrcVol_detID$]->Name);

  fPhysc[$detSrcVol_detID$] = new G4PVPlacement(0, 
                                    G4ThreeVector(fDetPar[$detSrcVol_detID$]->Pos[0], fDetPar[$detSrcVol_detID$]->Pos[1], fDetPar[$detSrcVol_detID$]->Pos[2]), 
                                    fLogic[$detSrcVol_detID$], fDetPar[$detSrcVol_detID$]->Name, 
                                    fLogic[$detSrcVol_detMotherID$], false, 0);

#end#
#detSrcVis#
  fLogic[$detSrcVol_detID$]->SetVisAttributes(fDetPar[$detSrcVol_detID$]->visAtt);
#end#

#detMesIniDef_Box#
  G4UIcmdWithADoubleAndUnit* f$detMesIniDef_detName$SizeXCmd;
  G4UIcmdWithADoubleAndUnit* f$detMesIniDef_detName$SizeYCmd;
  G4UIcmdWithADoubleAndUnit* f$detMesIniDef_detName$SizeZCmd;
  G4UIcmdWithAString       * f$detMesIniDef_detName$MatCmd;
#end#
#detMesSrcDef_Box#
  f$detMesSrcDef_detName$MatCmd = new G4UIcmdWithAString("/MySimulation/det/set$detMesSrcDef_detName$Material", this);
  f$detMesSrcDef_detName$MatCmd->SetGuidance("Select Material of the $detMesSrcDef_detName$.");
  f$detMesSrcDef_detName$MatCmd->SetParameterName("choice", false);
  f$detMesSrcDef_detName$MatCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  f$detMesSrcDef_detName$SizeXCmd = new G4UIcmdWithADoubleAndUnit("/MySimulation/det/set$detMesSrcDef_detName$X", this);
  f$detMesSrcDef_detName$SizeXCmd->SetUnitCategory("Length");
  f$detMesSrcDef_detName$SizeXCmd->SetParameterName("$detMesSrcDef_detName$X", false);
  f$detMesSrcDef_detName$SizeXCmd->SetRange("$detMesSrcDef_detName$X>0.");
  f$detMesSrcDef_detName$SizeXCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  f$detMesSrcDef_detName$SizeXCmd->SetToBeBroadcasted(false);

  f$detMesSrcDef_detName$SizeYCmd = new G4UIcmdWithADoubleAndUnit("/MySimulation/det/set$detMesSrcDef_detName$Y", this);
  f$detMesSrcDef_detName$SizeYCmd->SetUnitCategory("Length");
  f$detMesSrcDef_detName$SizeYCmd->SetParameterName("$detMesSrcDef_detName$Y", false);
  f$detMesSrcDef_detName$SizeYCmd->SetRange("$detMesSrcDef_detName$Y>0.");
  f$detMesSrcDef_detName$SizeYCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  f$detMesSrcDef_detName$SizeYCmd->SetToBeBroadcasted(false);

  f$detMesSrcDef_detName$SizeZCmd = new G4UIcmdWithADoubleAndUnit("/MySimulation/det/set$detMesSrcDef_detName$Z", this);
  f$detMesSrcDef_detName$SizeZCmd->SetUnitCategory("Length");
  f$detMesSrcDef_detName$SizeZCmd->SetParameterName("$detMesSrcDef_detName$Z", false);
  f$detMesSrcDef_detName$SizeZCmd->SetRange("$detMesSrcDef_detName$Z>0.");
  f$detMesSrcDef_detName$SizeZCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  f$detMesSrcDef_detName$SizeZCmd->SetToBeBroadcasted(false);
#end#
#detMesSrcDel_Box#
  delete f$detMesSrcDel_detName$SizeZCmd; 
  delete f$detMesSrcDel_detName$SizeYCmd;
  delete f$detMesSrcDel_detName$SizeXCmd; 
  delete f$detMesSrcDel_detName$MatCmd; 
#end#
#detMesSrcFunc_Box#
  if (command == f$detMesSrcFunc_detName$SizeXCmd)
    fDetectorConstruction->Set$detMesSrcFunc_detName$SizeHalfX(0.5*f$detMesSrcFunc_detName$SizeXCmd->GetNewDoubleValue(newValue));
  if (command == f$detMesSrcFunc_detName$SizeYCmd)
    fDetectorConstruction->Set$detMesSrcFunc_detName$SizeHalfY(0.5*f$detMesSrcFunc_detName$SizeYCmd->GetNewDoubleValue(newValue));
  if (command == f$detMesSrcFunc_detName$SizeZCmd)
    fDetectorConstruction->Set$detMesSrcFunc_detName$SizeHalfZ(0.5*f$detMesSrcFunc_detName$SizeZCmd->GetNewDoubleValue(newValue));
  if (command == f$detMesSrcFunc_detName$MatCmd)
    fDetectorConstruction->SetMaterial($detMesSrcFunc_detID$, newValue);
#end#







