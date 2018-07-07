const NBody = document.getElementById('NBody')
const detdiv = document.getElementById('det-setting')

//_________________________________________
// 1. NBody
NBody.addEventListener('change', function () {
    type = /^[0-9]*[1-9][0-9]*$/
    reg = new RegExp(type)
    nbody = parseInt(NBody.value)

    if (NBody.value.match(reg) != null && nbody < 100) {
        detdiv.innerHTML = ""
        updateIDList(nbody)
        addDetectorPage(nbody)
        initialization()
    }
    else {
        alert('必须输入小于100的正整数')
        NBody.value = ''
    }
})

//_________________________________________
// 2. NBody -> updateIDList
function updateIDList(nbody) {
    for (key in newID) delete newID[key]
    newID["-1"] = new Array("-1", "-1", "")

    for (i = 0; i < nbody; i++) {
        index = i + 1
        id = document.getElementById("BodyID" + index)
        if (id) id1 = id.innerHTML
        else id1 = ""
        id2 = settings.get("BodyID" + index)

        if (id1 != "") newID[id1] = new Array(id1, id1, "")
        else if (id2 != "") newID[id2] = new Array(id2, id2, "")
    }
}

//_________________________________________
// 2. NBody -> addDetectorPage 
function addDetectorPage(nbody) {
    for (let index = 0; index < nbody; index++) {
        AddDetectorSetting(index + 1) //start from 1
    }
}

//____________________________________________________________
// 3. NBody -> addDetectorPage -> AddDetectorSetting
// Particle Gun页面的控制数据
// "显示标签", "控件种类", "初始化数据", "id/保存进setting的key", "class/根据此来进行输入量检查"
detContent = {
    "I0": ["ID:", "textmsg", "", "BodyID", ""],
    "I1": ["Name:", "input-text", "", "BodyName", "parmWithString"],
    "I2": ["Material:", "dropdowngrp", "Material", "BodyMatt", ""],
    "I3": ["Shape:", "dropdown", "DetectorShape", "BodyShape", ""],
    "I4": ["Mother ID:", "dropdown", "IDList", "BodyMoth", ""],
    "I5": ["Size(mm):", "input-text", "", "BodySize", ""], //variable length vector
    "I6": ["Position (X,Y,Z):", "input-text", "", "BodyPos", "parmVector"],
    "I7": ["Rotation (X,Y,Z):", "input-text", "", "BodyRot", "parmVector"],
    "I8": ["Visual Color:", "input-color", "", "BodyVisAtt", "parmWithColor"],
    "I9": ["Step Limit:", "input-text", "", "BodyStepLmt", "parmWithLengUnit"],
    "IA": ["Set the SD class-name:", "input-text", "", "BodySDClass", "parmWithString"],
    "IB": ["Set the Hit class-name:", "input-text", "", "BodyHitClass", "parmWithString"],
}


function AddDetectorSetting(index) {

    div = addButtonItem(detdiv,
        'setDetector-bodybtn' + index, 'Set Body' + index + ': ' + iniData['BodyID' + index],
        'setDetector-bodydiv' + index, '设置几何体' + index)


    table = document.createElement('table')
    table.setAttribute('id', 'table' + index)
    div.appendChild(table)

    detcontmp = clone(detContent)
    for (key in detcontmp)
        detcontmp[key][3] = detcontmp[key][3] + index

    addTable(table, detcontmp)
}

//_________________________________________________
//DOM的事件处理函数，对ID进行响应
//注意调用顺序，必须先调用class对应的函数，再调用ID对应的函数
//1. ID = BodyName的事件响应
function bodyNameListener() {
    if (!this.eventList) eventList = 0
    if (this.eventList > 1) this.removeEventLisener('change', bodyNameListener)

    id = this.id
    value = this.value

    // 1. update BodyID, 3.MothID list
    index = id.replace("BodyName", "")
    id2 = "BodyID" + index
    pp2 = document.getElementById(id2)
    pp2.innerText = value.toUpperCase()
    store(id2, value.toUpperCase())

    // 2. update BodyButton
    btn3 = document.getElementById("setDetector-bodybtn" + index)
    btn3.innerText = 'Set Body' + index + ': ' + value.toUpperCase()

    div3 = document.createElement('div')
    div3.setAttribute('id', 'setDetector-bodydiv' + index)
    div3.setAttribute('class', 'demo-meta u-avoid-clicks')
    div3.innerText = '设置几何体' + index
    btn3.appendChild(div3)

    //3. update MothID list
    updateIDList(NBody.value)

    //4. update the ID-dropdown btn
    for (i = 0; i < NBody.value; i++) {
        index = i + 1
        idcont = 'BodyMoth' + index
        td2 = document.getElementById(idcont + '-td2')
        if (!td2) continue
        td2.innerHTML = ""
        addDropDown2(td2, iniMap["IDList"], idcont, 'IDList')
    }

    store(this.id, this.value)
    this.eventList++
}

//2. ID = BodySize的事件响应
function bodySizeListener() {
    if (!this.eventList) eventList = 0
    if (this.eventList > 1) this.removeEventLisener('change', bodySizeListener)

    id = this.id
    value = this.value
    value = value.replace(/\s/g, ",")
    value = value.replace(/,{2,}/g, ",")
    pars = value.split(",")

    shape = document.getElementById(id.replace('BodySize', 'BodyShape') + '-span').innerHTML.split(' ')
    shap = shape[0]
    msge = iniShapeList[shap][2]
    npar = parseInt(iniShapeList[shap][3])

    if (pars.length == npar) this.value = value
    else { myAlert(msge); this.value = ""; }

    store(this.id, this.value)
    this.eventList++
}
