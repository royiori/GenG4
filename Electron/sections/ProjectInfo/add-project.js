const projTable = document.getElementById('projTable')
const envTable = document.getElementById('envTable')
const basicTable = document.getElementById('basicTable')
const classNameTable = document.getElementById('classNameTable')

//____________________________________________________________
// Project Info页面的控制数据
// "显示标签", "控件种类", "初始化数据", "id/保存进setting的key", "class/根据此来进行输入量检查"
projContent = {
    "EntryFuncName"   : ["Set the name of the main function:", "input-text", "", "EntryFuncName"  , "parmWithString"],    
}

envContent = {
    "G4LibPath"   : ["Set the path of the G4 library:", "input-text", "", "G4LibPath"  , "parmWithPath"],
    "QTLibPath"   : ["Set the path of the QT library:", "input-text", "", "QTLibPath"  , "parmWithPath"],    
}

basicContent = {
    "Verbose": ["Set the default verbose output control level:", "dropdown", "AddUsrVerbose", "AddUsrVerbose", ""],
    "Random" : ["Set the Random Engine:",                        "dropdown", "RandomEngine",  "RandomEngine",  ""],
}

classNameContent = {
    "ActionClass"   : ["Action Initialization:", "input-text", "", "ActionClass"  , "parmWithString"],    
    "AnalysisClass" : ["Analysis Manager:     ", "input-text", "", "AnalysisClass", "parmWithString"],
    "DetectorClass" : ["Detector Construction:", "input-text", "", "DetectorClass", "parmWithString"],
    "DetMesgeClass" : ["Detector Messenger:   ", "input-text", "", "DetMesgeClass", "parmWithString"],
    "PhysicsClass"  : ["Physics Process:      ", "input-text", "", "PhysicsClass" , "parmWithString"],  
    "GunClass"      : ["Primary Generator:    ", "input-text", "", "GunClass"     , "parmWithString"],         
    "GunMesgeClass" : ["Primary Messenger:    ", "input-text", "", "GunMesgeClass", "parmWithString"],
    "RunClass"      : ["Run Class:            ", "input-text", "", "RunClass"     , "parmWithString"],      
    "EventClass"    : ["Event Class:          ", "input-text", "", "EventClass"   , "parmWithString"],      
    "StackClass"    : ["Stack Class:          ", "input-text", "", "StackClass"   , "parmWithString"],      
    "TrackClass"    : ["Track Class:          ", "input-text", "", "TrackClass"   , "parmWithString"],      
    "StepClass"     : ["Step Class:           ", "input-text", "", "StepClass"    , "parmWithString"],      
}