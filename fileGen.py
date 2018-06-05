import os
import common as com

def loadArray(path, records):  
    try:  
        file = open(path, "r")     # open file in read mode  
    except IOError as message:     # file open failed  
        print("read file error({0}:{1})".format(message, path))  
        sys.exit(1)  
  
    lines = file.readlines()  
    for line in lines:  
        records.append(line)  
  
    file.close() 


def saveArray(path, records):  
    try:  
        file = open(path, "w")     # open file in write mode  
    except IOError as message:     # file open failed  
        print("write file error({0}:{1})".format(message, path))  
        sys.exit(1)  
  
    file.writelines(records)  
  
    file.close()


def readIniMain(config):
    com.mainfilename = config.get("main", "EntryFuncName")
    com.G4LibPath    = config.get("main", "G4LibPath")
    com.QTLibPath    = config.get("main", "QTLibPath")
    com.addVerbose   = config.get("main", "AddUsrVerbose") 
    com.randomEng    = config.get("main", "RandomEngine")
    com.actionClass  = config.get("main", "ActionClass")
    com.detecClass   = config.get("main", "DetectorClass")
    com.detmesClass  = config.get("main", "DetMesgeClass")
    com.physicsClass = config.get("main", "PhysicsClass")
    com.gunClass     = config.get("main", "GunClass")
    com.gunmesClass  = config.get("main", "GunMesgeClass")
    com.runClass     = config.get("main", "RunClass")
    com.eventClass   = config.get("main", "EventClass")
    com.stepClass    = config.get("main", "StepClass")
    com.stackClass   = config.get("main", "StackClass")
    com.trackClass   = config.get("main", "TrackClass")
    com.analysisClass= config.get("main", "AnalysisClass")


def commonReplaceSub(recIn, recOut):
    for line in recIn:
        filter = line
        filter = filter.replace('$MAINENTRYS$', com.mainfilename)  
        filter = filter.replace('$G4LIBPATH$', com.G4LibPath)  
        filter = filter.replace('$QTLIBPATH$', com.QTLibPath)  
        filter = filter.replace('$MyActionInitialization$', com.actionClass)  
        filter = filter.replace('$MyDetectorConstruction$', com.detecClass)  
        filter = filter.replace('$MyDetectorMessenger$', com.detmesClass)
        filter = filter.replace('$MyPhysics$', com.physicsClass)  
        filter = filter.replace('$Verbose$', com.addVerbose)  
        filter = filter.replace('$RandomEng$', com.randomEng)  
        filter = filter.replace('$MyActionInitialization$', com.actionClass)  
        filter = filter.replace('$MyPrimaryGeneratorAction$', com.gunClass)  
        filter = filter.replace('$MyPrimaryGeneratorMessenger$', com.gunmesClass)  
        filter = filter.replace('$MyRunAction$', com.runClass)  
        filter = filter.replace('$MyEventAction$', com.eventClass)  
        filter = filter.replace('$MySteppingAction$', com.stepClass)  
        filter = filter.replace('$MyStackingAction$', com.stackClass)  
        filter = filter.replace('$MyTrackingAction$', com.trackClass)  
        filter = filter.replace('$MyAnalysisManager$',com.analysisClass)
        recOut.append(filter)  


def commonReplace(srcPath, outPath):
    srcIn = []  
    loadArray(srcPath, srcIn)  
  
    srcOut = []
    if('CMakeList' in srcPath) :
        com.headStr = com.headStr.replace('//', '#')
        srcOut.append(com.headStr)
    else :
        com.headStr = com.headStr.replace('#', '//')
        srcOut.append(com.headStr)
    commonReplaceSub(srcIn, srcOut)
    saveArray(outPath, srcOut)


def detReplace(genDet, outPath):
    srcIn = []
    loadArray(outPath, srcIn)

    srcOut = []
    for line in srcIn:
        filter = line
        filter = filter.replace('$detIncEnum$', genDet.genDetIncEnum())  
        filter = filter.replace('$detIncFunc$', genDet.genDetIncFunc())  

        filter = filter.replace('$detSrcIni$', genDet.genDetSrcIni())  
        filter = filter.replace('$detSrcVol$', genDet.genDetSrcVol())  
        filter = filter.replace('$detSrcInc$', genDet.genDetSrcInc())  
        filter = filter.replace('$detSrcVis$', genDet.genDetSrcVis())  
        filter = filter.replace('$detSrcSD$' , genDet.genDetSrcSD())  

        filter = filter.replace('$detMesIniDef$', genDet.genDetMesIniDef())
        filter = filter.replace('$detMesSrcDef$', genDet.genDetMesSrcDef())
        filter = filter.replace('$detMesSrcDel$', genDet.genDetMesSrcDel())
        filter = filter.replace('$detMesSrcFunc$', genDet.genDetMesSrcFunc())
        srcOut.append(filter)  

    saveArray(outPath, srcOut)


def gunReplace(genGun, outPath):
    srcIn = []
    loadArray(outPath, srcIn)

    srcOut = []
    for line in srcIn:
        filter = line
        filter = filter.replace('$gunIncFunc$', genGun.genGunIncFunc())  
        filter = filter.replace('$gunSrcIni$', genGun.genGunSrcIni())  
        filter = filter.replace('$gunSrcAct$', genGun.genGunSrcAct())  
        filter = filter.replace('$gunMesIniDef$', genGun.genGunMesIniDef())  
        filter = filter.replace('$gunMesSrcDef$', genGun.genGunMesSrcDef())  
        filter = filter.replace('$gunMesSrcDel$', genGun.genGunMesSrcDel())  
        filter = filter.replace('$gunMesSrcFunc$', genGun.genGunMesSrcFunc())  

        srcOut.append(filter)  

    saveArray(outPath, srcOut)



def sdReplace(detPar, outPath) :
    srcIn = []
    loadArray(outPath, srcIn)

    srcOut = []
    for line in srcIn : 
        filter = line
        filter = filter.replace('$SDClass$', detPar.GetSDClass()) 
        filter = filter.replace('$HitClass$', detPar.GetHitClass()) 

        srcOut.append(filter)  
    
    saveArray(outPath, srcOut)




def smReplace(genDet, outPath) :
    srcIn = []
    loadArray(outPath, srcIn)

    srcOut = []
    for line in srcIn : 
        filter = line
        filter = filter.replace('$DataIncSDDef$', genDet.genDataIncSDDef()) 
        filter = filter.replace('$DataIncSDFunc$', genDet.genDataIncSDFunc()) 
        filter = filter.replace('$DataIncSDClear$', genDet.genDataIncSDClear()) 

        srcOut.append(filter)  
    
    saveArray(outPath, srcOut)
