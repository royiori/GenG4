#global variables

headStr = ''

mainfilename  = '' 
addVerbose    = '' 
randomEng     = '' 
actionClass   = '' 
detecClass    = '' 
physicsClass  = '' 
gunClass      = '' 
runClass      = '' 
eventClass    = '' 
stepClass     = '' 
stackClass    = '' 
trackClass    = '' 
analysisClass = '' 
detTemplate = []

# class for read the template
class ReadDetTemplate : 
    detSrcVis = ''
    detIniFunc_Box = ''
    detSrcIni_Box = ''
    detSrcVol_Box = ''

    def __init__(self, path) :
        self.detSrcVis = ''
        self.detIniFunc_Box = ''
        self.detSrcIni_Box = ''
        self.detSrcVol_Box = ''

        try:  
            file = open(path, "r")  # open file in read mode  
        except IOError as message:     # file open failed  
            print("read file error({0}:{1})".format(message, path))  
            sys.exit(1)  
  
        lines = file.readlines()  

        idetSrcVis = 0
        idetIniFunc_Box = 0
        idetSrcIni_Box = 0
        idetSrcVol_Box = 0

        for line in lines:
            if(line == '#detSrcVis#\n') :
                idetSrcVis = 1
                continue
            elif(line == '#detIniFunc_Box#\n'):
                idetIniFunc_Box = 1
                continue
            elif(line == '#detSrcIni_Box#\n'):
                idetSrcIni_Box = 1
                continue
            elif(line == '#detSrcVol_Box#\n') :
                idetSrcVol_Box = 1
                continue
            elif(line == '#end#\n') :
                idetSrcVis = 0
                idetIniFunc_Box = 0
                idetSrcIni_Box = 0
                idetSrcVol_Box = 0
                continue
            
            if(idetSrcVis == 1) :
                self.detSrcVis += line
            if(idetIniFunc_Box == 1) :
                self.detIniFunc_Box += line
            if(idetSrcIni_Box == 1) :
                self.detSrcIni_Box += line
            if(idetSrcVol_Box == 1) :
                self.detSrcVol_Box += line
        
        file.close() 

    def getDetSrcVis(self):
        return self.detSrcVis
    def getDetIniFunc_Box(self) :
        return self.detIniFunc_Box
    def getDetSrcIni_Box(self) :
        return self.detSrcIni_Box
    def getDetSrcVol_Box(self) :
        return self.detSrcVol_Box


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
    
    detIniFunc = ''
    detSrcIni  = ''
    detSrcVol  = ''
    detSrcVis  = ''

    def __init__(self, config, n):  
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
            self.detIniFunc = detTemplate.getDetIniFunc_Box()
            self.detSrcIni  = detTemplate.getDetSrcIni_Box()
            self.detSrcVol  = detTemplate.getDetSrcVol_Box()

        self.detSrcVis = detTemplate.getDetSrcVis()

        self.pos.append(config.get("detector", "BodyPosX"+n))
        self.pos.append(config.get("detector", "BodyPosY"+n))
        self.pos.append(config.get("detector", "BodyPosZ"+n)) 

        self.rot.append(config.get("detector", "BodyRotX"+n))
        self.rot.append(config.get("detector", "BodyRotY"+n))
        self.rot.append(config.get("detector", "BodyRotZ"+n)) 

        self.vis = config.get("detector", "BodyVisAtt"+n)
        self.ven = config.get("detector", "BodyVEnab"+n)
        self.vsd = config.get("detector", "BodyVSold"+n)

    def GetID(self):  
        return self.id

    def GetName(self):
        return self.name
    
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
        return genstr
    
    def genDetSrcVis(self):
        genstr = self.detSrcVis
        genstr = genstr.replace('$detSrcVol_detID$', self.id)
        return genstr


# generate all detectors contents for replacement
class genDet:
    nDetBody = 0
    detParList = []

    def __init__(self, config):  
        self.nDetBody = int(config.get("detector", "NBody"))
        for i in range(1, self.nDetBody+1):
            self.detParList.append(detPar(config, str(i)))
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
