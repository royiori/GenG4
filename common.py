#global variables

headStr = ''

mainfilename  = '' 
G4LibPath     = ''
QTLibPath     = ''
addVerbose    = '' 
randomEng     = '' 
actionClass   = '' 
detecClass    = '' 
detmesClass   = ''
physicsClass  = '' 
gunClass      = '' 
gunmesClass   = ''
runClass      = '' 
eventClass    = '' 
stepClass     = '' 
stackClass    = '' 
trackClass    = '' 
analysisClass = '' 

# read as configure
def readTags(key, path) :
    try:  
        file = open(path, "r")  # open file in read mode  
    except IOError as message:     # file open failed  
        print("read file error({0}:{1})".format(message, path))  
        sys.exit(1)  
    
    lines = file.readlines()  

    ind = 0
    mesg = ''
    for line in lines:
        if(line == '#'+key+'#\n') :
            ind = 1
            continue
        elif(line == '#end#\n') :
            ind = 0
            continue
        if(ind == 1) :
            mesg += line

    file.close()
    return mesg





# each detector parameters
class detPar:  
    id = ''
    name = ''  
    matt = ''
    shape= ''
    mothID=''
    nsize= 0
    size = []
    pos  = []
    rot  = []
    vis  = ''
    ven  = ''
    vsd  = ''
    sdclass = ''
    hitclass = ''
    
    detIniFunc = ''
    detSrcInc  = ''
    detSrcIni  = ''
    detSrcVol  = ''
    detSrcVis  = ''
    detSrcSD   = ''
    detMesIniDef = ''
    detMesSrcDef = ''
    detMesSrcDel = ''
    detMesSrcFunc= ''
    dataIncSDClear= ''

    anaIncDef = ''
    anaIncFunc= ''
   
    def __init__(self, config, n, path):  
        self.id = config.get("detector", "BodyID"+n)
        self.name = config.get("detector", "BodyName"+n)
        self.matt = config.get("detector", "BodyMatt"+n)
        self.shape = config.get("detector", "BodyShape"+n)
        self.mothID = config.get("detector", "BodyMoth"+n)

        self.nsize= 0
        self.size = []
        if(self.shape == "Box"): 
            self.nsize = 3
            self.size.append(config.get("detector", "BodySizeA"+n))
            self.size.append(config.get("detector", "BodySizeA"+n))
            self.size.append(config.get("detector", "BodySizeA"+n))
            self.detIniFunc = readTags('detIniFunc_Box', path)
            self.detSrcIni  = readTags('detSrcIni_Box', path)
            self.detSrcVol  = readTags('detSrcVol_Box', path)
            self.detMesIniDef = readTags('detMesIniDef_Box', path)
            self.detMesSrcDef = readTags('detMesSrcDef_Box', path)
            self.detMesSrcDel = readTags('detMesSrcDel_Box', path)
            self.detMesSrcFunc= readTags('detMesSrcFunc_Box', path)
        self.detSrcInc = readTags('detSrcInc', path)    
        self.detSrcVis = readTags('detSrcVis', path)
        self.detSrcSD  = readTags('detSrcSD', path)
        self.dataIncSDDef = readTags('dataIncSDDef', path)
        self.dataIncSDFunc= readTags('dataIncSDFunc', path)
        self.dataIncSDClear=readTags('dataIncSDClear', path)

        self.pos.append(config.get("detector", "BodyPosX"+n))
        self.pos.append(config.get("detector", "BodyPosY"+n))
        self.pos.append(config.get("detector", "BodyPosZ"+n)) 

        self.rot.append(config.get("detector", "BodyRotX"+n))
        self.rot.append(config.get("detector", "BodyRotY"+n))
        self.rot.append(config.get("detector", "BodyRotZ"+n)) 

        self.vis = config.get("detector", "BodyVisAtt"+n)
        self.ven = config.get("detector", "BodyVEnab"+n)
        self.vsd = config.get("detector", "BodyVSold"+n)
        self.sdclass = config.get("detector", "BodySDClass"+n)
        self.hitclass = config.get("detector", "BodyHitClass"+n)


    def GetID(self):  
        return self.id

    def GetName(self):
        return self.name

    def GetSDClass(self):
        return self.sdclass

    def GetHitClass(self):
        return self.hitclass
    
    def GetIncludeFunc(self):
        genstr = self.detIniFunc
        genstr = genstr.replace('$detIniFunc_detID$', self.id)     
        genstr = genstr.replace('$detIniFunc_detName$', self.name)      
        return genstr

    def genDetSrcIni(self):
        genstr = self.detSrcIni
        genstr = genstr.replace('$detSrcIni_detID$', self.id)  
        genstr = genstr.replace('$detSrcIni_detName$', self.name)  
        genstr = genstr.replace('$detSrcIni_detShape$', self.shape)  
        genstr = genstr.replace('$detSrcIni_detMatt$', self.matt)  
        genstr = genstr.replace('$detSrcIni_Siz0$', self.size[0])  
        genstr = genstr.replace('$detSrcIni_Siz1$', self.size[1])  
        genstr = genstr.replace('$detSrcIni_Siz2$', self.size[2])  
        genstr = genstr.replace('$detSrcIni_Pos0$', self.pos[0])  
        genstr = genstr.replace('$detSrcIni_Pos1$', self.pos[1])  
        genstr = genstr.replace('$detSrcIni_Pos2$', self.pos[2])  
        genstr = genstr.replace('$detSrcIni_Rot0$', self.pos[0])  
        genstr = genstr.replace('$detSrcIni_Rot1$', self.pos[1])  
        genstr = genstr.replace('$detSrcIni_Rot2$', self.pos[2])  
        genstr = genstr.replace('$detSrcIni_Vis$', self.vis)
        genstr = genstr.replace('$detSrcIni_vEnable$', self.ven)
        genstr = genstr.replace('$detSrcIni_vSolid$', self.vsd)
        return genstr

    def genDetSrcVol(self):
        genstr = self.detSrcVol
        genstr = genstr.replace('$detSrcVol_detID$', self.id)
        genstr = genstr.replace('$detSrcVol_detMotherID$', self.mothID)
        genstr = genstr.replace('fLogic[-1]', '0')
        if(self.mothID == "-1") :
            genstr = genstr.replace('fDetPar['+self.id+']->Region','//fDetPar['+self.id+']->Region')
        return genstr
    
    def genDetSrcVis(self):
        genstr = self.detSrcVis
        genstr = genstr.replace('$detSrcVol_detID$', self.id)
        return genstr

    def genDetSrcInc(self):
        if(self.sdclass == 'false') :
            return ''
        genstr = self.detSrcInc
        genstr = genstr.replace('$detSrcInc_SDclass$', self.sdclass)
        return genstr
    
    def genDetSrcSD(self):
        if(self.sdclass == 'false') :
            return ''
        genstr = self.detSrcSD
        genstr = genstr.replace('$detSrcSD_detID$', self.id)
        genstr = genstr.replace('$detSrcSD_SDClass$', self.sdclass)
        genstr = genstr.replace('$detSrcSD_SDobj$', self.sdclass+"obj")
        return genstr

    def genDetMesIniDef(self):
        genstr = self.detMesIniDef
        genstr = genstr.replace('$detMesIniDef_detName$', self.name)
        return genstr
    
    def genDetMesSrcDef(self):
        genstr = self.detMesSrcDef
        genstr = genstr.replace('$detMesSrcDef_detName$', self.name)
        return genstr
    
    def genDetMesSrcDel(self):
        genstr = self.detMesSrcDel
        genstr = genstr.replace('$detMesSrcDel_detName$', self.name)
        return genstr

    def genDetMesSrcFunc(self):
        genstr = self.detMesSrcFunc
        genstr = genstr.replace('$detMesSrcFunc_detName$', self.name)
        genstr = genstr.replace('$detMesSrcFunc_detID$', self.id)
        return genstr

    def genAnaIncFunc(self) :
        if(self.sdclass == 'false') : 
            return ''
        genstr = self.genAnaIncFunc
        genstr = genstr.replace()
        return genstr
    
    def genDataIncSDDef(self) :
        if(self.sdclass == 'false') : 
            return ''
        genstr = self.dataIncSDDef
        genstr = genstr.replace('$dataIncSDDef_SDClass$', self.sdclass)
        return genstr

    def genDataIncSDFunc(self) :
        if(self.sdclass == 'false') : 
            return ''
        genstr = self.dataIncSDFunc
        genstr = genstr.replace('$dataIncSDFunc_SDClass$', self.sdclass)
        return genstr

    def genDataIncSDClear(self) :
        if(self.sdclass == 'false') : 
            return ''
        genstr = self.dataIncSDClear
        genstr = genstr.replace('$dataIncSDClear_SDClass$', self.sdclass)
        return genstr


# generate all detectors contents for replacement
class genDet:
    nDetBody = 0
    detParList = []

    def __init__(self, config, path):  
        self.nDetBody = int(config.get("detector", "NBody"))
        for i in range(1, self.nDetBody+1):
            self.detParList.append(detPar(config, str(i), path))
        for i in range(0, self.nDetBody):
            print(self.detParList[i].GetID())

    def genDetIncEnum(self):  
        genstr = "#define SIZE "+str(self.nDetBody)+"\n"
        for i in range(0, self.nDetBody) :
            genstr += "#define "+self.detParList[i].GetID()+" "+str(i)+"\n"
        return genstr
    
    def genDetIncFunc(self):
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].GetIncludeFunc()+"\n"
        return genstr

    def genDetSrcIni(self):
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].genDetSrcIni()+"\n"
        return genstr
    
    def genDetSrcVol(self):
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].genDetSrcVol()+"\n"
        return genstr
    
    def genDetSrcVis(self):
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].genDetSrcVis()
        return genstr
    
    def genDetSrcInc(self):
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].genDetSrcInc()
        return genstr

    def genDetSrcSD(self):
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].genDetSrcSD()
        return genstr

    def genDetMesIniDef(self):
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].genDetMesIniDef()
        return genstr

    def genDetMesSrcDef(self):
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].genDetMesSrcDef()
        return genstr

    def genDetMesSrcDel(self):
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].genDetMesSrcDel()
        return genstr

    def genDetMesSrcFunc(self):
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].genDetMesSrcFunc()
        return genstr

    def genDataIncSDDef(self) :
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].genDataIncSDDef()
        return genstr

    def genDataIncSDFunc(self) : 
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].genDataIncSDFunc()
        return genstr

    def genDataIncSDClear(self) :
        genstr = ''
        for i in range(0, self.nDetBody) :
            genstr += self.detParList[i].genDataIncSDClear()
        return genstr



# generate gun contents for replacement
class genGun:
    type = 0
    gunIncFunc = ''
    gunSrcIni  = ''
    gunSrcAct  = ''
    gunMesIniDef = ''
    gunMesSrcDef = ''
    gunMesSrcDel = ''
    gunMesSrcFunc= ''

    def __init__(self, config, path):  
        self.type = config.get("gun", "Type")
        if(self.type == 'mono') :
            Particle = config.get("gun", "Particle")
            Energy   = config.get("gun", "Energy")
            Position = config.get("gun", "Position")
            Direction = config.get("gun", "Direction")
            self.gunIncFunc = readTags('gunIncFunc_mono', path)
            self.gunSrcIni  = readTags('gunSrcIni_mono', path)
            self.gunSrcAct  = readTags('gunSrcAct_mono', path)
            self.gunMesIniDef = readTags('gunMesIniDef_mono', path)
            self.gunMesSrcDef = readTags('gunMesSrcDef_mono', path)
            self.gunMesSrcDel = readTags('gunMesSrcDel_mono', path)
            self.gunMesSrcFunc = readTags('gunMesSrcFunc_mono', path)
            self.gunSrcIni = self.gunSrcIni.replace('$gunSrcIni_Particle$',Particle)
            self.gunSrcIni = self.gunSrcIni.replace('$gunSrcIni_Energy$',Energy)
            self.gunSrcIni = self.gunSrcIni.replace('$gunSrcIni_Position$',Position)
            self.gunSrcIni = self.gunSrcIni.replace('$gunSrcIni_Direction$',Direction)
    
    def genGunIncFunc(self):
        return self.gunIncFunc
    def genGunSrcIni(self):
        return self.gunSrcIni
    def genGunSrcAct(self):
        return self.gunSrcAct
    def genGunMesIniDef(self):
        return self.gunMesIniDef
    def genGunMesSrcDef(self):
        return self.gunMesSrcDef
    def genGunMesSrcDel(self):
        return self.gunMesSrcDel
    def genGunMesSrcFunc(self):
        return self.gunMesSrcFunc