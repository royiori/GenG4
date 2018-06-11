const settings = require('electron-settings')
const NDET = 10

// alert("->load variable")
var iniData = {
    "EntryFuncName": "main",
    "G4LibPath": "",
    "QTLibPath": "",
    "AddUsrVerbose": "Yes",
    "RandomEngine": "RanecuEngine",
    "PhysicsProcess": "QBBC",
    "ActionClass": "MyActionInitialization",
    "AnalysisClass": "MyAnalysisManager",
    "DetectorClass": "MyDetectorConstruction",
    "DetMesgeClass": "MyDetectorMessenger",
    "PhysicsClass": "QBBC",
    "GunClass": "MyGunAction",
    "GunMesgeClass": "MyGunMessenger",
    "RunClass": "MyRunAction",
    "EventClass": "MyEvtAction",
    "StackClass": "MyStackAction",
    "TrackClass": "MyTrackAction",
    "StepClass": "MyStepAction",
    "NBody": "2",
}

var iniDetKey = [
    "BodyID",
    "BodyName",
    "BodyMatt",
    "BodyShape",
    "BodyMoth",
    "BodySize",
    "BodyPos",
    "BodyRot",
    "BodyVisAtt",
    "BodyStepLmt",
    "BodySDClass",
    "BodyHitClass",
]


// ..
// Yes or no key : "name_for_user", "used in G4"
var iniYNList = {
    "Yes":   ["Yes",    "1", ""],
    "No":    ["No",     "0", ""],
    "Unset": ["Unset", "-1", ""],
}

// ..
// random engine key : "name_for_user", "name_in_G4","description"
var iniRndList = {
    "HepJamesRandom": ["HepJamesRandom", "", ""],
    "DRand48Engine":  ["DRand48Engine",  "", ""],
    "DualRand":       ["DualRand",       "", ""],
    "Hurd160Engine":  ["Hurd160Engine",  "", ""],
    "Hurd288Engine":  ["Hurd288Engine",  "", ""],
    "MTwistEngine":   ["MTwistEngine",   "", ""],
    "NonRandomEngine":["NonRandomEngine","", ""],
    "RandEngine":     ["RandEngine",     "", ""],
    "RanecuEngine":   ["RanecuEngine",   "", ""],
    "Ranlux64Engine": ["Ranlux64Engine", "", ""],
    "RanluxEngine":   ["RanluxEngine",   "", ""],
    "RanshiEngine":   ["RanshiEngine",   "", ""],
    "TripleRand":     ["TripleRand",     "", ""],
}

//..
// shape key : "name_for_user", "name_in_G4", "description", "nsize_parameters", "parameter_description"
var iniShapeList = {
    "G4Box":    ["G4Box",    "G4Box",    "", "3", "x", "y", "z", ""],
    "G4Para":   ["G4Para",   "G4Para",   "", "3", "x", "y", "z", ""],
    "G4Trd":    ["G4Trd",    "G4Trd",    "", "3", "x", "y", "z", ""],
    "G4Tubs":   ["G4Tubs",   "G4Tubs",   "", "3", "x", "y", "z", ""],
    "G4CutTubs":["G4CutTubs","G4CutTubs","", "3", "x", "y", "z", ""],
    "G4Cons":   ["G4Cons",   "G4Cons",   "", "3", "x", "y", "z", ""],
    "G4Sphere": ["G4Sphere", "G4Sphere", "", "3", "x", "y", "z", ""],
    "G4Orb":    ["G4Orb",    "G4Orb",    "", "3", "x", "y", "z", ""],
    "G4Torus":  ["G4Torus",  "G4Torus",  "", "3", "x", "y", "z", ""],
}

//..
// physics key : "name_for_user", "name_in_G4", "description"
var iniPhyicsList = {
    "FTFP_BERT"            : ["FTFP_BERT", "FTFP_BERT", ""],
    "FTFP_BERT_ATL"        : ["FTFP_BERT_ATL", "FTFP_BERT_ATL", ""],
    "FTFP_BERT_HP"         : ["FTFP_BERT_HP", "FTFP_BERT_HP", ""],
    "FTFP_BERT_TRV"        : ["FTFP_BERT_TRV", "FTFP_BERT_TRV", ""],
    "FTFP_INCLXX"          : ["FTFP_INCLXX", "FTFP_INCLXX", ""],
    "FTFP_INCLXX_HP"       : ["FTFP_INCLXX_HP", "FTFP_INCLXX_HP", ""],
    "FTF_BIC"              : ["FTF_BIC", "FTF_BIC", ""],
    "G4GenericPhysicsList" : ["G4GenericPhysicsList", "G4GenericPhysicsList", ""],
    "G4PhysListFactory"    : ["G4PhysListFactory", "G4PhysListFactory", ""],
    "INCLXXPhysicsListHelper": ["INCLXXPhysicsListHelper", "INCLXXPhysicsListHelper", ""],
    "LBE"                  : ["LBE", "LBE", ""],
    "NuBeam"               : ["NuBeam", "NuBeam", ""],
    "QBBC"                 : ["QBBC", "QBBC", ""],
    "QGSP_BERT"            : ["QGSP_BERT", "QGSP_BERT", ""],
    "QGSP_BERT_HP"         : ["QGSP_BERT_HP", "QGSP_BERT_HP", ""],
    "QGSP_BIC"             : ["QGSP_BIC", "QGSP_BIC", ""],
    "QGSP_BIC_AllHP"       : ["QGSP_BIC_AllHP", "QGSP_BIC_AllHP", ""],
    "QGSP_BIC_HP"          : ["QGSP_BIC_HP", "QGSP_BIC_HP", ""],
    "QGSP_FTFP_BERT"       : ["QGSP_FTFP_BERT", "QGSP_FTFP_BERT", ""],
    "QGSP_INCLXX"          : ["QGSP_INCLXX", "QGSP_INCLXX", ""],
    "QGSP_INCLXX_HP"       : ["QGSP_INCLXX_HP", "QGSP_INCLXX_HP", ""],
    "QGS_BIC"              : ["QGS_BIC", "QGS_BIC", ""],
    "Shielding"            : ["Shielding", "Shielding", ""],
    "User Define"          : ["User Define", "User Define", ""],
}

//原子序数或者是组分数， 汉语名称， 英语名称， Geant4里的名字， 密度， 电离能
var iniMattList = {
    "CEPC-ECal": [
        "14", "硅", "Si", "G4_Si", "2.33", "173",
        "74", "钨", "W", "G4_W", "19.3", "727",
        "3", "锗酸铋", "BGO", "G4_BGO", "7.13", "534.1",
        "3", "硅酸镥", "LSO", "Lu2SiO5", "7.4", "**",
        "3", "硅酸钇镥", "LYSO", "LYSO", "7.4", "**"
    ],
    "CEPC-DHCAL": [
        "26", "铁", "Fe", "G4_Fe", "7.874", "286",
        "3", "不锈钢", "STAINLESS-STEEL", "G4_STAINLESS-STEEL", "8", "0",
        "18", "氩气", "Ar", "G4_Ar", "0.00166201", "188",
        "3", "酚醛塑料/电木", "BAKELITE", "G4_BAKELITE", "1.25", "72.4",
        "4", "聚酰亚胺", "KAPTON", "G4_KAPTON", "1.42", "79.6"
    ],
    "JUNO": [
        "5", "液闪", "LS", "LS", "0.859", "**",
        "6", "掺钆液闪", "GdLS", "GdDopedLS", "0.8602", "**",
        "3", "有机玻璃", "Acrylic", "Acrylic", "1.18", "**",
        "2", "ESR反射膜", "ESR", "ESR", "1.0", "**",
        "2", "Tyvek反射膜", "Tyvek", "Tyvek", "0.94", "**",
        "2", "溴化镧", "LaBr3", "LaBr3", "5.06", "**",
    ],
    "Pandax": [
        "54", "氙气", "Xe", "G4_Xe", "0.00548536", "482",
        "54", "10.0气压氙气", "Xe", "Xe_P10_0", "0.0548536", "482",
    ],
    "UCAS LAB": [
        "18", "0.1气压氩气", "Ar", "Ar_P0_1", "0.000166201", "188",
        "18", "0.3气压氩气", "Ar", "Ar_P0_3", "0.000498603", "188",
        "18", "0.5气压氩气", "Ar", "Ar_P0_5", "0.000831005", "188",
        "18", "0.8气压氩气", "Ar", "Ar_P0_8", "0.001329608", "188",
        "18", "1.0气压氩气", "Ar", "Ar_P1_0", "0.00166201", "188",
        "18", "1.5气压氩气", "Ar", "Ar_P1_5", "0.002493015", "188",
        "18", "2.0气压氩气", "Ar", "Ar_P2_0", "0.00332402", "188",
        "18", "2.5气压氩气", "Ar", "Ar_P2_5", "0.004155025", "188",
        "18", "3.0气压氩气", "Ar", "Ar_P3_0", "0.00498603", "188",
        "18", "3.5气压氩气", "Ar", "Ar_P3_5", "0.005817035", "188",
        "18", "4.0气压氩气", "Ar", "Ar_P4_0", "0.00664804", "188",
        "18", "5.0气压氩气", "Ar", "Ar_P5_0", "0.00831005", "188",
        "18", "10.0气压氩气", "Ar", "Ar_P10_0", "0.0166201", "188",
        "2", "四氟化碳", "fluorocarbon", "CF4", "0.00372", "**",
        "2", "3气压四氟化碳", "fluorocarbon", "CF4_P3_0", "0.01116", "**",
        "2", "5气压四氟化碳", "fluorocarbon", "CF4_P5_0", "0.0186", "**",
        "2", "10气压四氟化碳", "fluorocarbon", "CF4_P10_0", "0.0372", "**",
    ],
    "UCAS Gas": [
        "2", "He/DME=20/80", "He/DME=20/80", "He_20_DME_80", "0.001932", "**",
        "2", "0.5P He/DME=20/80", "He/DME=20/80", "He_20_DME_80_P0_5", "0.001932*0.5", "**",
        "2", "0.6P He/DME=20/80", "He/DME=20/80", "He_20_DME_80_P0_6", "0.001932*0.6", "**",
        "2", "0.7P He/DME=20/80", "He/DME=20/80", "He_20_DME_80_P0_7", "0.001932*0.7", "**",
        "2", "0.8P He/DME=20/80", "He/DME=20/80", "He_20_DME_80_P0_8", "0.001932*0.8", "**",
        "2", "Ne/DME=80/20", "Ne/DME=80/20", "Ne_80_DME_20", "0.00111416", "**",
        "2", "0.5P Ne/DME=80/20", "Ne/DME=80/20", "Ne_80_DME_20_P0_5", "0.00111416*0.5", "**",
        "2", "0.6P Ne/DME=80/20", "Ne/DME=80/20", "Ne_80_DME_20_P0_6", "0.00111416*0.6", "**",
        "2", "0.7P Ne/DME=80/20", "Ne/DME=80/20", "Ne_80_DME_20_P0_7", "0.00111416*0.7", "**",
        "2", "0.8P Ne/DME=80/20", "Ne/DME=80/20", "Ne_80_DME_20_P0_8", "0.00111416*0.8", "**",
        "2", "Ne/CF4=95/5", "Ne/CF4=95/5", "Ne_95_CF4_5", "0.00104119", "**",
        "2", "0.5P Ne/CF4=95/5", "Ne/CF4=95/5", "Ne_95_CF4_5_P0_5", "0.00104119*0.5", "**",
        "2", "0.6P Ne/CF4=95/5", "Ne/CF4=95/5", "Ne_95_CF4_5_P0_6", "0.00104119*0.6", "**",
        "2", "0.7P Ne/CF4=95/5", "Ne/CF4=95/5", "Ne_95_CF4_5_P0_7", "0.00104119*0.7", "**",
        "2", "0.8P Ne/CF4=95/5", "Ne/CF4=95/5", "Ne_95_CF4_5_P0_8", "0.00104119*0.8", "**",
    ],
    "element": [
        "1", "氢气", "H", "G4_H", "8.3748e-05", "19.2",
        "2", "氦气", "He", "G4_He", "0.000166322", "41.8",
        "3", "锂", "Li", "G4_Li", "0.534", "40",
        "4", "铍", "Be", "G4_Be", "1.848", "63.7",
        "5", "硼", "B", "G4_B", "2.37", "76",
        "6", "碳", "C", "G4_C", "2", "81",
        "7", "氮气", "N", "G4_N", "0.0011652", "82",
        "8", "氧气", "O", "G4_O", "0.00133151", "95",
        "9", "氟气", "F", "G4_F", "0.00158029", "115",
        "10", "氖气", "Ne", "G4_Ne", "0.000838505", "137",
        "11", "钠", "Na", "G4_Na", "0.971", "149",
        "12", "镁", "Mg", "G4_Mg", "1.74", "156",
        "13", "铝", "Al", "G4_Al", "2.699", "166",
        "14", "硅", "Si", "G4_Si", "2.33", "173",
        "15", "磷", "P", "G4_P", "2.2", "173",
        "16", "硫", "S", "G4_S", "2", "180",
        "17", "氯气", "Cl", "G4_Cl", "0.00299473", "174",
        "18", "氩气", "Ar", "G4_Ar", "0.00166201", "188",
        "19", "钾", "K", "G4_K", "0.862", "190",
        "20", "钙", "Ca", "G4_Ca", "1.55", "191",
        "21", "钪", "Sc", "G4_Sc", "2.989", "216",
        "22", "钛", "Ti", "G4_Ti", "4.54", "233",
        "23", "钒", "V", "G4_V", "6.11", "245",
        "24", "铬", "Cr", "G4_Cr", "7.18", "257",
        "25", "锰", "Mn", "G4_Mn", "7.44", "272",
        "26", "铁", "Fe", "G4_Fe", "7.874", "286",
        "27", "钴", "Co", "G4_Co", "8.9", "297",
        "28", "镍", "Ni", "G4_Ni", "8.902", "311",
        "29", "铜", "Cu", "G4_Cu", "8.96", "322",
        "30", "锌", "Zn", "G4_Zn", "7.133", "330",
        "31", "镓", "Ga", "G4_Ga", "5.904", "334",
        "32", "锗", "Ge", "G4_Ge", "5.323", "350",
        "33", "砷", "As", "G4_As", "5.73", "347",
        "34", "硒", "Se", "G4_Se", "4.5", "348",
        "35", "溴", "Br", "G4_Br", "0.0070721", "343",
        "36", "氪气", "Kr", "G4_Kr", "0.00347832", "352",
        "37", "铷", "Rb", "G4_Rb", "1.532", "363",
        "38", "锶", "Sr", "G4_Sr", "2.54", "366",
        "39", "钇", "Y", "G4_Y", "4.469", "379",
        "40", "锆", "Zr", "G4_Zr", "6.506", "393",
        "41", "铌", "Nb", "G4_Nb", "8.57", "417",
        "42", "钼", "Mo", "G4_Mo", "10.22", "424",
        "43", "锝", "Tc", "G4_Tc", "11.5", "428",
        "44", "钌", "Ru", "G4_Ru", "12.41", "441",
        "45", "铑", "Rh", "G4_Rh", "12.41", "449",
        "46", "钯", "Pd", "G4_Pd", "12.02", "470",
        "47", "银", "Ag", "G4_Ag", "10.5", "470",
        "48", "镉", "Cd", "G4_Cd", "8.65", "469",
        "49", "铟", "In", "G4_In", "7.31", "488",
        "50", "锡", "Sn", "G4_Sn", "7.31", "488",
        "51", "锑", "Sb", "G4_Sb", "6.691", "487",
        "52", "碲", "Te", "G4_Te", "6.24", "485",
        "53", "碘", "I", "G4_I", "4.93", "491",
        "54", "氙气", "Xe", "G4_Xe", "0.00548536", "482",
        "55", "铯", "Cs", "G4_Cs", "1.873", "488",
        "56", "钡", "Ba", "G4_Ba", "3.5", "491",
        "57", "镧", "La", "G4_La", "6.154", "501",
        "58", "铈", "Ce", "G4_Ce", "6.657", "523",
        "59", "镨", "Pr", "G4_Pr", "6.71", "535",
        "60", "钕", "Nd", "G4_Nd", "6.9", "546",
        "61", "钷", "Pm", "G4_Pm", "7.22", "560",
        "62", "钐", "Sm", "G4_Sm", "7.46", "574",
        "63", "铕", "Eu", "G4_Eu", "5.243", "580",
        "64", "钆", "Gd", "G4_Gd", "7.9004", "591",
        "65", "铽", "Tb", "G4_Tb", "8.229", "614",
        "66", "镝", "Dy", "G4_Dy", "8.55", "628",
        "67", "钬", "Ho", "G4_Ho", "8.795", "650",
        "68", "铒", "Er", "G4_Er", "9.066", "658",
        "69", "铥", "Tm", "G4_Tm", "9.321", "674",
        "70", "镱", "Yb", "G4_Yb", "6.73", "684",
        "71", "镥", "Lu", "G4_Lu", "9.84", "694",
        "72", "铪", "Hf", "G4_Hf", "13.31", "705",
        "73", "钽", "Ta", "G4_Ta", "16.654", "718",
        "74", "钨", "W", "G4_W", "19.3", "727",
        "75", "铼", "Re", "G4_Re", "21.02", "736",
        "76", "锇", "Os", "G4_Os", "22.57", "746",
        "77", "铱", "Ir", "G4_Ir", "22.42", "757",
        "78", "铂", "Pt", "G4_Pt", "21.45", "790",
        "79", "金", "Au", "G4_Au", "19.32", "790",
        "80", "汞", "Hg", "G4_Hg", "13.546", "800",
        "81", "铊", "Tl", "G4_Tl", "11.72", "810",
        "82", "铅", "Pb", "G4_Pb", "11.35", "823",
        "83", "铋", "Bi", "G4_Bi", "9.747", "823",
        "84", "钋", "Po", "G4_Po", "9.32", "830",
        "85", "砹", "At", "G4_At", "9.32", "825",
        "86", "氡", "Rn", "G4_Rn", "0.00900662", "794",
        "87", "钫", "Fr", "G4_Fr", "1", "827",
        "88", "镭", "Ra", "G4_Ra", "5", "826",
        "89", "锕", "Ac", "G4_Ac", "10.07", "841",
        "90", "钍", "Th", "G4_Th", "11.72", "847",
        "91", "镤", "Pa", "G4_Pa", "15.37", "878",
        "92", "铀", "U", "G4_U", "18.95", "890",
        "93", "镎", "Np", "G4_Np", "20.25", "902",
        "94", "钚", "Pu", "G4_Pu", "19.84", "921",
        "95", "镅", "Am", "G4_Am", "13.67", "934",
        "96", "锔", "Cm", "G4_Cm", "13.51", "939",
        "97", "锫", "Bk", "G4_Bk", "14", "952",
        "98", "锎", "Cf", "G4_Cf", "10", "966"
    ],
    "compound": [
        "6", "组织", "A-150_TISSUE", "G4_A-150_TISSUE", "1.127", "65.1",
        "3", "丙酮", "ACETONE", "G4_ACETONE", "0.7899", "64.2",
        "2", "乙炔", "ACETYLENE", "G4_ACETYLENE", "0.0010967", "58.2",
        "3", "腺嘌呤", "ADENINE", "G4_ADENINE", "1.6", "71.4",
        "7", "脂肪", "ADIPOSE_TISSUE_ICRP", "G4_ADIPOSE_TISSUE_ICRP", "0.95", "63.2",
        "4", "空气", "AIR", "G4_AIR", "0.00120479", "85.7",
        "4", "丙胺酸", "ALANINE", "G4_ALANINE", "1.42", "71.9",
        "2", "氧化铝", "ALUMINUM_OXIDE", "G4_ALUMINUM_OXIDE", "33.97", "145.2",
        "3", "琥珀", "AMBER", "G4_AMBER", "1.1", "63.2",
        "2", "氨水", "AMMONIA", "G4_AMMONIA", "0.000826019", "53.7",
        "3", "苯胺", "ANILINE", "G4_ANILINE", "1.0235", "66.2",
        "2", "蒽", "ANTHRACENE", "G4_ANTHRACENE", "1.283", "69.5",
        "6", "骨头", "B-100_BONE", "G4_B-100_BONE", "1.45", "85.9",
        "3", "酚醛塑料/电木", "BAKELITE", "G4_BAKELITE", "1.25", "72.4",
        "2", "氟化钡", "BARIUM_FLUORIDE", "G4_BARIUM_FLUORIDE", "4.89", "375.9",
        "3", "硫酸钡", "BARIUM_SULFATE", "G4_BARIUM_SULFATE", "4.5", "285.7",
        "2", "苯", "BENZENE", "G4_BENZENE", "0.87865", "63.4",
        "2", "氧化铍", "BERYLLIUM_OXIDE", "G4_BERYLLIUM_OXIDE", "3.01", "93.2",
        "3", "锗酸铋", "BGO", "G4_BGO", "7.13", "534.1",
        "10", "血", "BLOOD_ICRP", "G4_BLOOD_ICRP", "1.06", "75.2",
        "8", "致密的骨头", "BONE_COMPACT_ICRU", "G4_BONE_COMPACT_ICRU", "1.85", "91.9",
        "9", "皮层的骨头", "BONE_CORTICAL_ICRP", "G4_BONE_CORTICAL_ICRP", "1.92", "110",
        "2", "碳化硼", "BORON_CARBIDE", "G4_BORON_CARBIDE", "2.52", "84.7",
        "2", "氧化硼", "BORON_OXIDE", "G4_BORON_OXIDE", "1.812", "99.6",
        "9", "脑", "BRAIN_ICRP", "G4_BRAIN_ICRP", "1.04", "73.3",
        "2", "丁烷", "BUTANE", "G4_BUTANE", "0.00249343", "48.3",
        "3", "丁醇", "N-BUTYL_ALCOHOL", "G4_N-BUTYL_ALCOHOL", "0.8098", "59.9",
        "5", "C-552", "C-552", "G4_C-552", "1.76", "86.8",
        "2", "碲化镉", "CADMIUM_TELLURIDE", "G4_CADMIUM_TELLURIDE", "6.2", "539.3",
        "3", "钨酸镉", "CADMIUM_TUNGSTATE", "G4_CADMIUM_TUNGSTATE", "7.9", "468.3",
        "3", "碳酸钙", "CALCIUM_CARBONATE", "G4_CALCIUM_CARBONATE", "2.8", "136.4",
        "2", "氟化钙", "CALCIUM_FLUORIDE", "G4_CALCIUM_FLUORIDE", "3.18", "166",
        "2", "氧化钙", "CALCIUM_OXIDE", "G4_CALCIUM_OXIDE", "3.3", "176.1",
        "3", "硫酸钙", "CALCIUM_SULFATE", "G4_CALCIUM_SULFATE", "2.96", "152.3",
        "3", "钨酸钙", "CALCIUM_TUNGSTATE", "G4_CALCIUM_TUNGSTATE", "6.062", "395",
        "2", "二氧化碳", "CARBON_DIOXIDE", "G4_CARBON_DIOXIDE", "0.00184212", "85",
        "2", "四氯化碳", "CARBON_TETRACHLORIDE", "G4_CARBON_TETRACHLORIDE", "1.594", "166.3",
        "3", "玻璃纤维", "CELLULOSE_CELLOPHANE", "G4_CELLULOSE_CELLOPHANE", "1.42", "77.6",
        "3", "丁酸纤维", "CELLULOSE_BUTYRATE", "G4_CELLULOSE_BUTYRATE", "1.2", "74.6",
        "4", "硝酸纤维", "CELLULOSE_NITRATE", "G4_CELLULOSE_NITRATE", "1.49", "87",
        "5", "硫酸铈", "CERIC_SULFATE", "G4_CERIC_SULFATE", "1.03", "76.7",
        "2", "氟化铯", "CESIUM_FLUORIDE", "G4_CESIUM_FLUORIDE", "4.115", "440.7",
        "2", "碘化铯", "CESIUM_IODIDE", "G4_CESIUM_IODIDE", "4.51", "553.1",
        "3", "氯苯", "CHLOROBENZENE", "G4_CHLOROBENZENE", "1.1058", "89.1",
        "3", "氯仿", "CHLOROFORM", "G4_CHLOROFORM", "1.4832", "156",
        "10", "混凝土", "CONCRETE", "G4_CONCRETE", "2.3", "135.2",
        "2", "环乙炔", "CYCLOHEXANE", "G4_CYCLOHEXANE", "0.779", "56.4",
        "3", "邻二氯苯", "1,2-DICHLOROBENZENE", "G4_1,2-DICHLOROBENZENE", "1.3048", "106.5",
        "4", "二氯二乙醚", "DICHLORODIETHYL_ETHER", "G4_DICHLORODIETHYL_ETHER", "1.2199", "103.3",
        "3", "二氯乙烷", "1,2-DICHLOROETHANE", "G4_1,2-DICHLOROETHANE", "1.2351", "111.9",
        "3", "乙醚", "DIETHYL_ETHER", "G4_DIETHYL_ETHER", "0.71378", "60",
        "4", "二甲基甲酰胺", "N,N-DIMETHYL_FORMAMIDE", "G4_N,N-DIMETHYL_FORMAMIDE", "0.9487", "66.6",
        "4", "二甲亚砜", "DIMETHYL_SULFOXIDE", "G4_DIMETHYL_SULFOXIDE", "1.1014", "98.6",
        "2", "乙烷", "ETHANE", "G4_ETHANE", "0.00125324", "45.4",
        "3", "乙醇", "ETHYL_ALCOHOL", "G4_ETHYL_ALCOHOL", "0.7893", "62.9",
        "3", "乙基纤维", "ETHYL_CELLULOSE", "G4_ETHYL_CELLULOSE", "1.13", "69.3",
        "2", "乙烯", "ETHYLENE", "G4_ETHYLENE", "0.00117497", "50.7",
        "8", "眼球", "EYE_LENS_ICRP", "G4_EYE_LENS_ICRP", "1.07", "73.3",
        "2", "氧化铁", "FERRIC_OXIDE", "G4_FERRIC_OXIDE", "5.2", "227.3",
        "2", "硼化铁", "FERROBORIDE", "G4_FERROBORIDE", "7.15", "261",
        "2", "氧化铁", "FERROUS_OXIDE", "G4_FERROUS_OXIDE", "5.7", "248.6",
        "7", "硫酸铁", "FERROUS_SULFATE", "G4_FERROUS_SULFATE", "1.024", "76.4",
        "3", "氟利昂", "FREON-12", "G4_FREON-12", "1.12", "143",
        "3", "氟利昂", "FREON-12B2", "G4_FREON-12B2", "1.8", "284.9",
        "3", "氟利昂", "FREON-13", "G4_FREON-13", "0.95", "126.6",
        "3", "氟利昂", "FREON-13B1", "G4_FREON-13B1", "1.5", "210.5",
        "3", "氟利昂", "FREON-13I1", "G4_FREON-13I1", "1.8", "293.5",
        "3", "硫氧化钆", "GADOLINIUM_OXYSULFIDE", "G4_GADOLINIUM_OXYSULFIDE", "7.44", "493.3",
        "2", "砷化镓", "GALLIUM_ARSENIDE", "G4_GALLIUM_ARSENIDE", "5.31", "384.9",
        "5", "凝胶感光乳剂", "GEL_PHOTO_EMULSION", "G4_GEL_PHOTO_EMULSION", "1.2914", "74.8",
        "6", "高硼硅玻璃", "Pyrex_Glass", "G4_Pyrex_Glass", "2.23", "134",
        "5", "玻璃铅", "GLASS_LEAD", "G4_GLASS_LEAD", "6.22", "526.4",
        "4", "玻璃板", "GLASS_PLATE", "G4_GLASS_PLATE", "2.4", "145.4",
        "3", "葡萄糖", "GLUCOSE", "G4_GLUCOSE", "1.54", "77.2",
        "4", "谷氨酸盐", "GLUTAMINE", "G4_GLUTAMINE", "1.46", "73.3",
        "3", "甘油", "GLYCEROL", "G4_GLYCEROL", "1.2613", "72.6",
        "4", "鸟嘌呤", "GUANINE", "G4_GUANINE", "2.2", "75",
        "4", "石膏", "GYPSUM", "G4_GYPSUM", "2.32", "129.7",
        "2", "正庚烷", "N-HEPTANE", "G4_N-HEPTANE", "0.68376", "54.4",
        "2", "正己烷", "N-HEXANE", "G4_N-HEXANE", "0.6603", "54",
        "4", "聚酰亚胺", "KAPTON", "G4_KAPTON", "1.42", "79.6",
        "3", "溴氧化镧", "LANTHANUM_OXYBROMIDE", "G4_LANTHANUM_OXYBROMIDE", "6.28", "439.7",
        "3", "氧硫化镧", "LANTHANUM_OXYSULFIDE", "G4_LANTHANUM_OXYSULFIDE", "5.86", "421.2",
        "2", "氧化铅", "LEAD_OXIDE", "G4_LEAD_OXIDE", "9.53", "766.7",
        "3", "氨基化锂", "LITHIUM_AMIDE", "G4_LITHIUM_AMIDE", "1.178", "55.5",
        "3", "碳酸锂", "LITHIUM_CARBONATE", "G4_LITHIUM_CARBONATE", "2.11", "87.9",
        "2", "氟化锂", "LITHIUM_FLUORIDE", "G4_LITHIUM_FLUORIDE", "2.635", "94",
        "2", "氢化锂", "LITHIUM_HYDRIDE", "G4_LITHIUM_HYDRIDE", "0.82", "36.5",
        "2", "碘化锂", "LITHIUM_IODIDE", "G4_LITHIUM_IODIDE", "3.494", "485.1",
        "2", "氧化锂", "LITHIUM_OXIDE", "G4_LITHIUM_OXIDE", "2.013", "73.6",
        "3", "四硼酸锂", "LITHIUM_TETRABORATE", "G4_LITHIUM_TETRABORATE", "2.44", "94.6",
        "9", "肺", "LUNG_ICRP", "G4_LUNG_ICRP", "1.04", "75.3",
        "5", "蜡", "M3_WAX", "G4_M3_WAX", "1.05", "67.9",
        "3", "碳酸镁", "MAGNESIUM_CARBONATE", "G4_MAGNESIUM_CARBONATE", "2.958", "118",
        "2", "氟化镁", "MAGNESIUM_FLUORIDE", "G4_MAGNESIUM_FLUORIDE", "3", "134.3",
        "2", "氧化镁", "MAGNESIUM_OXIDE", "G4_MAGNESIUM_OXIDE", "3.58", "143.8",
        "3", "四硼酸镁", "MAGNESIUM_TETRABORATE", "G4_MAGNESIUM_TETRABORATE", "2.53", "108.3",
        "2", "碘化镁", "MERCURIC_IODIDE", "G4_MERCURIC_IODIDE", "6.36", "684.5",
        "2", "甲烷", "METHANE", "G4_METHANE", "0.000667151", "41.7",
        "3", "甲醇", "METHANOL", "G4_METHANOL", "0.7914", "67.6",
        "5", "混合D蜡", "MIX_D_WAX", "G4_MIX_D_WAX", "0.99", "60.9",
        "6", "组织", "MS20_TISSUE", "G4_MS20_TISSUE", "1", "75.1",
        "9", "骨骼肌", "MUSCLE_SKELETAL_ICRP", "G4_MUSCLE_SKELETAL_ICRP", "1.05", "75.3",
        "8", "横纹肌", "MUSCLE_STRIATED_ICRU", "G4_MUSCLE_STRIATED_ICRU", "1.04", "74.7",
        "4", "含蔗糖肌", "MUSCLE_WITH_SUCROSE", "G4_MUSCLE_WITH_SUCROSE", "1.11", "74.3",
        "4", "无蔗糖肌", "MUSCLE_WITHOUT_SUCROSE", "G4_MUSCLE_WITHOUT_SUCROSE", "1.07", "74.2",
        "2", "萘", "NAPHTHALENE", "G4_NAPHTHALENE", "1.145", "68.4",
        "4", "硝基苯", "NITROBENZENE", "G4_NITROBENZENE", "1.19867", "75.8",
        "2", "氧化氮", "NITROUS_OXIDE", "G4_NITROUS_OXIDE", "0.00183094", "84.9",
        "4", "尼龙", "NYLON-8062", "G4_NYLON-8062", "1.08", "64.3",
        "4", "尼龙", "NYLON-6-6", "G4_NYLON-6-6", "1.14", "63.9",
        "4", "尼龙", "NYLON-6-10", "G4_NYLON-6-10", "1.14", "63.2",
        "4", "尼龙", "NYLON-11_RILSAN", "G4_NYLON-11_RILSAN", "1.425", "61.6",
        "2", "辛烷", "OCTANE", "G4_OCTANE", "0.7026", "54.7",
        "2", "石蜡", "PARAFFIN", "G4_PARAFFIN", "0.93", "55.9",
        "2", "正戊烷", "N-PENTANE", "G4_N-PENTANE", "0.6262", "53.6",
        "8", "感光乳剂", "PHOTO_EMULSION", "G4_PHOTO_EMULSION", "3.815", "331",
        "2", "塑料/乙烯基甲苯", "PLASTIC_SC_VINYLTOLUENE", "G4_PLASTIC_SC_VINYLTOLUENE", "1.032", "64.7",
        "2", "二氧化钚", "PLUTONIUM_DIOXIDE", "G4_PLUTONIUM_DIOXIDE", "11.46", "746.5",
        "3", "聚丙烯腈", "POLYACRYLONITRILE", "G4_POLYACRYLONITRILE", "1.17", "69.6",
        "3", "聚碳酸酯", "POLYCARBONATE", "G4_POLYCARBONATE", "1.2", "73.1",
        "3", "聚氯苯乙烯", "POLYCHLOROSTYRENE", "G4_POLYCHLOROSTYRENE", "1.3", "81.7",
        "2", "聚乙烯", "POLYETHYLENE", "G4_POLYETHYLENE", "0.94", "57.4",
        "3", "聚脂薄膜", "MYLAR", "G4_MYLAR", "1.4", "78.7",
        "3", "树脂玻璃", "PLEXIGLASS", "G4_PLEXIGLASS", "1.19", "74",
        "3", "聚甲醛", "POLYOXYMETHYLENE", "G4_POLYOXYMETHYLENE", "1.425", "77.4",
        "2", "聚丙烯", "POLYPROPYLENE", "G4_POLYPROPYLENE", "0.9", "56.5",
        "2", "聚苯乙烯(塑闪)", "POLYSTYRENE", "G4_POLYSTYRENE", "1.06", "68.7",
        "2", "特氟隆", "TEFLON", "G4_TEFLON", "2.2", "99.1",
        "3", "聚三氟氯乙烯", "POLYTRIFLUOROCHLOROETHYLENE", "G4_POLYTRIFLUOROCHLOROETHYLENE", "2.1", "120.7",
        "3", "多乙酸乙烯酯", "POLYVINYL_ACETATE", "G4_POLYVINYL_ACETATE", "1.19", "73.7",
        "3", "聚乙烯醇", "POLYVINYL_ALCOHOL", "G4_POLYVINYL_ALCOHOL", "1.3", "69.7",
        "3", "聚乙烯醇缩丁醛", "POLYVINYL_BUTYRAL", "G4_POLYVINYL_BUTYRAL", "1.12", "67.2",
        "3", "聚氯乙烯", "POLYVINYL_CHLORIDE", "G4_POLYVINYL_CHLORIDE", "1.3", "108.2",
        "3", "聚偏二氯乙烯", "POLYVINYLIDENE_CHLORIDE", "G4_POLYVINYLIDENE_CHLORIDE", "1.7", "134.3",
        "3", "聚偏二氟乙烯", "POLYVINYLIDENE_FLUORIDE", "G4_POLYVINYLIDENE_FLUORIDE", "1.76", "88.8",
        "4", "吡咯烷酮", "POLYVINYL_PYRROLIDONE", "G4_POLYVINYL_PYRROLIDONE", "1.25", "67.7",
        "2", "碘化钾", "POTASSIUM_IODIDE", "G4_POTASSIUM_IODIDE", "3.13", "431.9",
        "2", "氧化钾", "POTASSIUM_OXIDE", "G4_POTASSIUM_OXIDE", "2.32", "189.9",
        "2", "丙烷", "PROPANE", "G4_PROPANE", "0.00187939", "47.1",
        "2", "异丙烷", "lPROPANE", "G4_lPROPANE", "0.43", "52",
        "3", "正丙醇", "N-PROPYL_ALCOHOL", "G4_N-PROPYL_ALCOHOL", "0.8035", "61.1",
        "3", "吡啶", "PYRIDINE", "G4_PYRIDINE", "0.9819", "66.2",
        "2", "丁基橡胶", "RUBBER_BUTYL", "G4_RUBBER_BUTYL", "0.92", "56.5",
        "2", "天然橡胶", "RUBBER_NATURAL", "G4_RUBBER_NATURAL", "0.92", "59.8",
        "3", "氯丁橡胶", "RUBBER_NEOPRENE", "G4_RUBBER_NEOPRENE", "1.23", "93",
        "2", "二氧化硅", "SILICON_DIOXIDE", "G4_SILICON_DIOXIDE", "SiO_22.32", "139.2",
        "2", "溴化银", "SILVER_BROMIDE", "G4_SILVER_BROMIDE", "6.473", "486.6",
        "2", "氯化银", "SILVER_CHLORIDE", "G4_SILVER_CHLORIDE", "5.56", "398.4",
        "3", "卤化银", "SILVER_HALIDES", "G4_SILVER_HALIDES", "6.47", "487.1",
        "2", "碘化银", "SILVER_IODIDE", "G4_SILVER_IODIDE", "6.01", "543.5",
        "9", "皮肤", "SKIN_ICRP", "G4_SKIN_ICRP", "1.09", "72.7",
        "3", "碳酸钠", "SODIUM_CARBONATE", "G4_SODIUM_CARBONATE", "2.532", "125",
        "2", "碘化钠", "SODIUM_IODIDE", "G4_SODIUM_IODIDE", "3.667", "452",
        "2", "氧化钠", "SODIUM_MONOXIDE", "G4_SODIUM_MONOXIDE", "2.27", "148.8",
        "3", "硝酸钠", "SODIUM_NITRATE", "G4_SODIUM_NITRATE", "2.261", "114.6",
        "2", "芪", "STILBENE", "G4_STILBENE", "0.9707", "67.7",
        "3", "蔗糖", "SUCROSE", "G4_SUCROSE", "1.5805", "77.5",
        "2", "三联苯", "TERPHENYL", "G4_TERPHENYL", "1.234", "71.7",
        "9", "睾丸", "TESTIS_ICRP", "G4_TESTIS_ICRP", "1.04", "75",
        "2", "四氯乙烯", "TETRACHLOROETHYLENE", "G4_TETRACHLOROETHYLENE", "1.625", "159.2",
        "2", "氯化铊", "THALLIUM_CHLORIDE", "G4_THALLIUM_CHLORIDE", "7.004", "690.3",
        "9", "软组织", "TISSUE_SOFT_ICRP", "G4_TISSUE_SOFT_ICRP", "1.03", "72.3",
        "4", "软组织", "TISSUE_SOFT_ICRU-4", "G4_TISSUE_SOFT_ICRU-4", "1", "74.9",
        "4", "组织甲烷", "TISSUE-METHANE", "G4_TISSUE-METHANE", "0.00106409", "61.2",
        "4", "组织丙烷", "TISSUE-PROPANE", "G4_TISSUE-PROPANE", "0.00182628", "59.5",
        "2", "二氧化钛", "TITANIUM_DIOXIDE", "G4_TITANIUM_DIOXIDE", "4.26", "179.5",
        "2", "甲苯", "TOLUENE", "G4_TOLUENE", "0.8669", "62.5",
        "3", "三氯乙烯", "TRICHLOROETHYLENE", "G4_TRICHLOROETHYLENE", "1.46", "148.1",
        "4", "磷酸三乙酯", "TRIETHYL_PHOSPHATE", "G4_TRIETHYL_PHOSPHATE", "1.07", "81.2",
        "2", "六氟化钨", "TUNGSTEN_HEXAFLUORIDE", "G4_TUNGSTEN_HEXAFLUORIDE", "2.4", "354.4",
        "2", "二碳化铀", "URANIUM_DICARBIDE", "G4_URANIUM_DICARBIDE", "11.28", "752",
        "2", "碳化铀", "URANIUM_MONOCARBIDE", "G4_URANIUM_MONOCARBIDE", "13.63", "862",
        "2", "氧化铀", "URANIUM_OXIDE", "G4_URANIUM_OXIDE", "10.96", "720.6",
        "4", "尿素", "UREA", "G4_UREA", "1.323", "72.8",
        "4", "缬氨酸", "VALINE", "G4_VALINE", "1.23", "67.7",
        "3", "氟橡胶", "VITON", "G4_VITON", "1.8", "98.6",
        "2", "水", "WATER", "G4_WATER", "H_2O1", "78",
        "2", "水蒸气", "WATER_VAPOR", "G4_WATER_VAPOR", "H_2O-Gas0.000756182", "71.6",
        "2", "二甲苯", "XYLENE", "G4_XYLENE", "0.87", "61.8",
        "1", "石墨", "GRAPHITE", "G4_GRAPHITE", "Graphite2.21", "78"
    ],
    "NuclearMaterial": [
        "1", "液态氢", "lH2", "G4_lH2", "0.0708", "21.8",
        "1", "液态氮", "lN2", "G4_lN2", "0.807", "82",
        "1", "液态氧", "lO2", "G4_lO2", "1.141", "95",
        "1", "液态氩", "lAr", "G4_lAr", "1.396", "188",
        "1", "液态氪", "lKr", "G4_lKr", "2.418", "352",
        "1", "液态氙", "lXe", "G4_lXe", "2.953", "482",
        "3", "钨酸铅", "PbWO4", "G4_PbWO4", "8.28", "0",
        "1", "真空", "Galactic", "G4_Galactic", "1e-25", "21.8",
        "3", "透明合成树脂", "LUCITE", "G4_LUCITE", "1.19", "74",
        "3", "黄铜", "BRASS", "G4_BRASS", "8.52", "0",
        "3", "青铜", "BRONZE", "G4_BRONZE", "8.82", "0",
        "3", "不锈钢", "STAINLESS-STEEL", "G4_STAINLESS-STEEL", "8", "0",
        "3", "碳本酸丙烯乙酸镜片", "CR39", "G4_CR39", "1.32", "0",
        "3", "十八醇", "OCTADECANOL", "G4_OCTADECANOL", "0.812", "0"
    ],
    "SpaceMaterial": [
        "4", "聚对苯二甲酰对苯二胺", "KEVLAR", "G4_KEVLAR", "1.44", "0",
        "3", "涤纶", "DACRON", "G4_DACRON", "1.4", "0",
        "3", "氯丁橡胶", "NEOPRENE", "G4_NEOPRENE", "1.23", "0"
    ],
    "BioMaterial": [
        "4", "", "CYTOSINE", "G4_CYTOSINE", "1.55", "72",
        "4", "", "THYMINE", "G4_THYMINE", "1.23", "72",
        "4", "", "URACIL", "G4_URACIL", "1.32", "72",
        "3", "", "DNA_ADENINE", "G4_DNA_ADENINE", "1", "72",
        "4", "", "DNA_GUANINE", "G4_DNA_GUANINE", "1", "72",
        "4", "", "DNA_CYTOSINE", "G4_DNA_CYTOSINE", "1", "72",
        "4", "", "DNA_THYMINE", "G4_DNA_THYMINE", "1", "72",
        "4", "", "DNA_URACIL", "G4_DNA_URACIL", "1", "72",
        "4", "", "DNA_ADENOSINE", "G4_DNA_ADENOSINE", "1", "72",
        "4", "", "DNA_GUANOSINE", "G4_DNA_GUANOSINE", "1", "72",
        "4", "", "DNA_CYTIDINE", "G4_DNA_CYTIDINE", "1", "72",
        "4", "", "DNA_URIDINE", "G4_DNA_URIDINE", "1", "72",
        "4", "", "DNA_METHYLURIDINE", "G4_DNA_METHYLURIDINE", "1", "72",
        "2", "", "DNA_MONOPHOSPHATE", "G4_DNA_MONOPHOSPHATE", "1", "72",
        "5", "", "DNA_A", "G4_DNA_A", "1", "72",
        "5", "", "DNA_G", "G4_DNA_G", "1", "72",
        "5", "", "DNA_C", "G4_DNA_C", "1", "72",
        "5", "", "DNA_U", "G4_DNA_U", "1", "72",
        "5", "", "DNA_MU", "G4_DNA_MU", "1", "72"
    ]
}

var iniGunList = {
    "Resource": [
        "e+", "钠-22", "<sub style='font-size: 25px;'>11</sub>Na<sup style=' font-size: 25px;'>22</sup>", "2.6 Years", "580 keV",
        "gamma", "钠-22", "<sub style='font-size: 25px;'>11</sub>Na<sup style=' font-size: 25px;'>22</sup>", "2.6 Years", "1275 keV",
        "e-", "钾-40", "<sub style='font-size: 25px;'>19</sub>K<sup style=' font-size: 25px;'>40</sup>", "9.9E8 Years", "1330 keV",
        "gamma", "钾-40", "<sub style='font-size: 25px;'>19</sub>K<sup style=' font-size: 25px;'>40</sup>", "9.9E8 Years", "1460 keV",
        "gamma", "钴-60", "<sub style='font-size: 25px;'>27</sub>Co<sup style=' font-size: 25px;'>60</sup>", "270 Days", "1173 keV",
        "gamma", "钴-60", "<sub style='font-size: 25px;'>27</sub>Co<sup style=' font-size: 25px;'>60</sup>", "270 Days", "1333 keV",
        "e-", "锶-90", "<sub style='font-size: 25px;'>38</sub>Sr<sup style=' font-size: 25px;'>90</sup>", "19.9 Years", "546 keV",
        "e-", "铯-137", "<sub style='font-size: 25px;'>55</sub>Cs<sup style=' font-size: 25px;'>137</sup>", "33.2 Years", "512 keV",
        "e-", "铯-137", "<sub style='font-size: 25px;'>55</sub>Cs<sup style=' font-size: 25px;'>137</sup>", "33.2 Years", "1173 keV",
        "gamma", "铯-137", "<sub style='font-size: 25px;'>55</sub>Cs<sup style=' font-size: 25px;'>137</sup>", "33.2 Years", "662 keV",
        "alpha", "钋-210", "<sub style='font-size: 25px;'>84</sub>Po<sup style=' font-size: 25px;'>210</sup>", "138.4 Days", "5305 keV",
        "alpha", "铀-238", "<sub style='font-size: 25px;'>92</sub>U<sup style=' font-size: 25px;'>238</sup>", "4.5E9 Years", "4267 keV",
        "alpha", "钚-239", "<sub style='font-size: 25px;'>94</sub>Pu<sup style=' font-size: 25px;'>239</sup>", "2.4E4 Years", "5245 keV",
        "alpha", "镅-241", "<sub style='font-size: 25px;'>95</sub>Am<sup style=' font-size: 25px;'>241</sup>", "4.3E2 Years", "5486 keV",
        "gamma", "镅-241", "<sub style='font-size: 25px;'>95</sub>Am<sup style=' font-size: 25px;'>241</sup>", "4.3E2 Years", "60 keV"
    ],
    "Particle": [
        "proton", "质子", "p", "1/2", "+",
        "neutron", "中子", "n", "1/2", "+",
        "mu-", "负缪子", "&mu;<sup>-</sup>", "1/2", "",
        "mu+", "正缪子", "&mu;<sup>+</sup>", "1/2", "",
        "e-", "电子", "e<sup>-</sup>", "1/2", "",
        "e+", "正电子", "e<sup>+</sup>", "1/2", "",
        "alpha", "氦核", "&alpha;<sup>2+</sup>", "", "",
        "gamma", "光子", "&gamma;", "1", "--",
        "pi+", "正徘介子", "&pi;<sup>+</sup>", "0", "-",
        "pi0", "徘介子", "&pi;<sup>0</sup>", "0", "-+",
        "pi-", "负徘介子", "&pi;<sup>-</sup>", "0", "-"
    ]
}


//--------------------------------------------
// Map between drop-down button & object list
var iniMap = {
    "AddUsrVerbose"  : iniYNList,
    "RandomEngine"   : iniRndList,
    "PhysicsProcess" : iniPhyicsList,
    "DetectorShape"  : iniShapeList,
    "Material"       : iniMattList,
}

// read from setting
for (key in iniData) {
    value = settings.get(key)
    if (value && value!="") {
        iniData[key] = value
        // alert('Read '+key+" as "+value)
    }
}

for (index = 1; index <= NDET; index++) {
    iniDetKey.forEach(function (element) {
        key = element + index
        value = settings.get(key)
        if (value) iniData[key] = value
        else iniData[key] = ""
    })
}



function addDropDown(topdiv, idcont, droplist) {
    dropdown = document.createElement('div')
    dropdown.setAttribute('class', 'dropdown')
    topdiv.appendChild(dropdown)

    span = document.createElement('span')
    span.setAttribute('class', 'dropbtn')
    span.setAttribute('id', idcont + '-span')
    span.innerHTML=iniData[idcont]
    topdiv.appendChild(span)
    
    //.. add content ..
    div = document.createElement('div')
    div.setAttribute('class', 'dropdown-content')
    topdiv.appendChild(div)

    for (key in iniMap[droplist]) {
        la = document.createElement('a')
        la.id = idcont + '=' + iniMap[droplist][key][0]
        la.innerHTML = iniMap[droplist][key][0]
        div.appendChild(la)

        la.addEventListener('click', function () {
            id = this.id.split('=')
            idcont = id[0]
            value  = id[1]

            span = document.getElementById(idcont + '-span')
            span.innerHTML = value
            settings.set(idcont, value)
            // alert("Set " + idcont + " to " + value)
        })
    }
}

function addGroupDropDown(topdiv, idcont, droplist) {
    select = document.createElement('select')
    select.setAttribute('data-placeholder','Click to set...')
    select.setAttribute('class', 'chosen-select')
    select.setAttribute('id', idcont)
    topdiv.appendChild(select)

    opt = document.createElement('option')
    select.appendChild(opt)

    for (key in iniMap[droplist]) {
        optg = document.createElement('optgroup')
        optg.setAttribute('label',key)
        select.appendChild(optg)

        for( var i=0; i<iniMap[droplist][key].length; i+=6) {
            opt = document.createElement('option')
            opt.innerHTML = iniMap[droplist][key][i+1]+" "+iniMap[droplist][key][i+2]
            optg.appendChild(opt)
        }
    }
}

function addInputListener(input)
{
    id = input.getAttribute('id')
    val = settings.get(id)
    if (val) input.value = val

    input.addEventListener('change', function () {
        id = this.id
        val= this.value
        if (val) settings.set(id, val)
    })    
}
// alert("->load variable done")