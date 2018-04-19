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



