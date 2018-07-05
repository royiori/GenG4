//_________________________________________________
//增加DOM到页面中

//_________________________________________________
//增加一个Electron类型的ButtonItem, id1/id2为项目的两行名称div
function addButtonItem(topdiv, id1, cont1, id2, cont2) {
    div1 = document.createElement('div')
    div1.setAttribute('class', 'demo')

    div2 = document.createElement('div')
    div2.setAttribute('class', 'demo-wrapper')

    but3 = document.createElement('button')
    but3.setAttribute('id', id1)
    but3.setAttribute('class', 'js-container-target demo-toggle-button')
    but3.innerText = cont1

    div3 = document.createElement('div')
    div3.setAttribute('id', id2)
    div3.setAttribute('class', 'demo-meta u-avoid-clicks')
    div3.innerText = cont2

    div4 = document.createElement('div')
    div4.setAttribute('class', 'demo-box')

    topdiv.appendChild(div1)
    div1.appendChild(div2)
    div2.appendChild(but3)
    div2.appendChild(div4)
    but3.appendChild(div3)

    but3.addEventListener('click', (event) => {
        const parent = event.target.parentElement
        parent.classList.toggle('is-open')
    })

    return div4
}

//_________________________________________________
//增加一个表格
//1. Table
function addTable(tablediv, content) {
    for (key in content) {
        label = content[key][0]
        dom = content[key][1]
        inival = content[key][2]
        idcont = content[key][3]
        classnm = content[key][4]

        tr = document.createElement('tr')
        td1 = document.createElement('td')
        p1 = document.createElement('p')
        p1.innerText = label
        td2 = document.createElement('td')
        td2.setAttribute('id', idcont + '-td2')
        tablediv.appendChild(tr)
        tr.appendChild(td1)
        tr.appendChild(td2)
        td1.appendChild(p1)

        addDOM(td2, dom, inival, idcont, classnm)
    }
}

//2. Table -> addDom (according the dom flag)
function addDOM(topdiv, dom, inival, idcont, classnm) {
    switch (dom) {
        case ("textmsg"): addTextMsg(topdiv, inival, idcont, classnm)
            break
        case ("input-text"): addInputText(topdiv, inival, idcont, classnm)
            break
        case ("input-color"): addInputColor(topdiv, inival, idcont, classnm)
            break
        case ("dropdown"): addDropDown(topdiv, inival, idcont, classnm)
            break
        case ("dropdown-chosen"): addDropDownChosen(topdiv, inival, idcont, classnm)
            break
        case ("dropdowngrp"): addDropDownGroup(topdiv, inival, idcont, classnm)
            break
            defalt: break
    }
}

//3. Table -> addDom -> addTextMsg
function addTextMsg(topdiv, inival, idcont, classnm) {
    p2 = document.createElement('p')
    p2.setAttribute('id', idcont)
    topdiv.appendChild(p2)

    p2.innerHTML = (inival == "") ? iniData[idcont] : inival
}

//3. Table -> addDom -> addInputText
function addInputText(topdiv, inival, idcont, classnm) {
    input = document.createElement('input')
    input.setAttribute('id', idcont)
    input.setAttribute('type', 'text')
    input.setAttribute('class', classnm)
    topdiv.appendChild(input)

    input.value = (inival == "") ? iniData[idcont] : inival
}

//3. Table -> addDom -> addInputColor
function addInputColor(topdiv, inival, idcont, classnm) {
    input = document.createElement('input')
    input.setAttribute('id', idcont)
    input.setAttribute('type', 'color')
    input.setAttribute('class', 'colorInput ' + classnm)
    topdiv.appendChild(input)

    input.value = (inival == "") ? iniData[idcont] : inival
}

//3. Table -> addDom -> addDropDown
function addDropDown(topdiv, inival, idcont, classnm) {
    dropdown = document.createElement('div')
    dropdown.setAttribute('id', idcont + '-dropdown')
    dropdown.setAttribute('class', 'dropdown')
    topdiv.appendChild(dropdown)

    span = document.createElement('span')
    span.setAttribute('id', idcont + '-span')
    span.setAttribute('class', 'dropbtn ' + classnm)
    span.innerHTML = iniData[idcont]
    dropdown.appendChild(span)

    //.. add content ..
    div = document.createElement('div')
    div.setAttribute('id', idcont + '-dropdowncont')
    div.setAttribute('class', 'dropdown-content')
    dropdown.appendChild(div)

    for (key in iniMap[inival]) {
        la = document.createElement('a')
        la.id = idcont + '=' + iniMap[inival][key][0]
        la.innerHTML = iniMap[inival][key][0]
        div.appendChild(la)

        la.addEventListener('click', function () {
            id = this.id.split('=')
            idcont = id[0]
            value = id[1]

            span = document.getElementById(idcont + '-span')
            span.innerHTML = value
            store(idcont, value)
        })
    }
}

//3. Table -> addDom -> addDropDownChosen
function addDropDownChosen(topdiv, inival, idcont, classnm) {
    select = document.createElement('select')
    select.setAttribute('data-placeholder', 'Click to set...')
    select.setAttribute('class', 'chosen-select ' + classnm)
    select.setAttribute('id', idcont)
    topdiv.appendChild(select)

    opt = document.createElement('option')
    select.appendChild(opt)

    for (key in iniMap[inival]) {
        opt = document.createElement('option')
        opt.innerHTML = iniMap[inival][key][0]
        if (opt.innerHTML == iniData[idcont]) opt.setAttribute("selected", "")
        select.appendChild(opt)
    }
}

//3. Table -> addDom -> addDropDownGroup
function addDropDownGroup(topdiv, inival, idcont, classnm) {
    select = document.createElement('select')
    select.setAttribute('data-placeholder', 'Click to set...')
    select.setAttribute('class', 'chosen-select ' + classnm)
    select.setAttribute('id', idcont)
    topdiv.appendChild(select)

    opt = document.createElement('option')
    select.appendChild(opt)

    for (key in iniMap[inival]) {
        optg = document.createElement('optgroup')
        optg.setAttribute('label', key)
        select.appendChild(optg)

        for (var i = 0; i < iniMap[inival][key].length; i += 6) {
            opt = document.createElement('option')
            opt.innerHTML = iniMap[inival][key][i + 1] + " " + iniMap[inival][key][i + 2]
            if (opt.innerText == iniData[idcont]) opt.setAttribute("selected", "")
            optg.appendChild(opt)
        }
    }
}

//_________________________________________________
//DOM的事件处理函数
//1. 字符串的input
function parmWithString() {
    if (!this.eventList) eventList = 0
    if (this.eventList > 1) this.removeEventLisener('change', parmWithString)

    value = this.value
    var containSpecial = RegExp(/[(\ )(\~)(\!)(\@)(\#)(\$)(\%)(\^)(\&)(\*)(\()(\))(\-)(\_)(\+)(\=)(\[)(\])(\{)(\})(\|)(\\)(\;)(\:)(\')(\")(\,)(\.)(\/)(\<)(\>)(\?)(\)]+/);
    if (parseFloat(value) || containSpecial.test(value)) {
        alert("注意:输入必须为字符串，且不可包含特殊字符")
        this.value = ""
    }

    store(this.id, this.value)
    this.eventList++
}

//2. 路径的input
function parmWithPath() {
    if (!this.eventList) eventList = 0
    if (this.eventList > 1) this.removeEventLisener('change', parmWithPath)

    value = this.value
    var containSpecial = RegExp(/[(\ )(\~)(\!)(\@)(\#)(\$)(\%)(\^)(\&)(\*)(\()(\))(\+)(\=)(\[)(\])(\{)(\})(\|)(\;)(\:)(\')(\,)(\\)(\<)(\>)(\?)(\)]+/);
    if (parseFloat(value) || containSpecial.test(value)) {
        alert("注意:输入必须为字符串，且不可包含特殊字符")
        this.value = ""
    }

    store(this.id, this.value)
    this.eventList++
}

//3. 能量的input
function parmWithEngUnit() {
    if (!this.eventList) eventList = 0
    if (this.eventList > 1) this.removeEventLisener('change', parmWithEngUnit)

    inputeng = this.value.toLowerCase()
    inputEngNumber = parseFloat(inputeng)

    if (inputeng.indexOf("tev") > 0) this.value = inputEngNumber + " TeV"
    else if (inputeng.indexOf("gev") > 0) this.value = inputEngNumber + " GeV"
    else if (inputeng.indexOf("mev") > 0) this.value = inputEngNumber + " MeV"
    else if (inputeng.indexOf("kev") > 0) this.value = inputEngNumber + " keV"
    else if (inputeng.indexOf("ev") > 0) this.value = inputEngNumber + " eV"
    else { alert("注意，输入参考格式为：1 GeV"); this.value = "" }

    store(this.id, this.value)
    this.eventList++
}

//4. 长度的input
function parmWithLengUnit() {
    if (!this.eventList) eventList = 0
    if (this.eventList > 1) this.removeEventLisener('change', parmWithLengUnit)

    inputthk = this.value.toLowerCase()
    inputThkNumber = parseFloat(inputeng)

    if (inputthk.indexOf("um") > 0) this.value = inputThkNumber + " um"
    else if (inputthk.indexOf("mm") > 0) this.value = inputThkNumber + " mm"
    else if (inputthk.indexOf("cm") > 0) this.value = inputThkNumber + " cm"
    else if (inputthk.indexOf("km") > 0) this.value = inputThkNumber + " km"
    else if (inputthk.indexOf("m") > 0) this.value = inputThkNumber + " m"
    else { alert("注意，输入参考格式为：1 mm"); this.value = "" }

    store(this.id, this.value)
    this.eventList++
}

//5. 颜色的input
function parmWithColor() {
    if (!this.eventList) eventList = 0
    if (this.eventList > 1) this.removeEventLisener('change', parmWithColor)

    store(this.id, this.value)
    this.eventList++
}

//6. 矢量的input
function parmVector() {
    if (!this.eventList) eventList = 0
    if (this.eventList > 1) this.removeEventLisener('change', parmVector)

    id = this.id
    value = this.value
    value = value.replace(/\s/g, ",")
    value = value.replace(/,{2,}/g, ",")
    pars = value.split(",")

    if (pars.length == 3) this.value = value
    else { alert("注意，输入参考格式为：1，1，1"); this.value = "" }

    store(this.id, this.value)
    this.eventList++
}


//_________________________________________________
// 通用函数
//1. 对象的浅拷贝
function clone(myObj) {
    if (typeof (myObj) != 'object') return myObj;
    if (myObj == null) return myObj;
    var myNewObj = new Object();
    for (var i in myObj)
        myNewObj[i] = clone(myObj[i]);
    return myNewObj;
}


//2. 响应函数的初始化
function initialization() {
    $(".parmWithString").change(parmWithString)
    $(".parmWithPath").change(parmWithPath)
    $(".parmWithEngUnit").change(parmWithEngUnit)
    $(".parmWithLengUnit").change(parmWithLengUnit)
    $(".parmWithColor").change(parmWithColor)
    $(".parmVector").change(parmVector)

    $(".chosen-select").chosen({ width: "60%" })
    $('.chosen-select').on('change', function (evt, params) {
        // alert("Set as "+params.selected)
        store(this.id, params.selected)
    });

    $("input[id^='BodyName']").change(bodyNameListener)
    $("input[id^='BodySize']").change(bodySizeListener)
    $(".gunparticle").change(particleListListener)

    //$("#ParticleList").on('change', function (evt, params) {alert("test")})
}

//3. 刷新iniData并保存至settings
function store(id, value) {
    if(value && value != "") {
        iniData[id] = value
        settings.set(id, value)
        // alert("save: " + id + " = " + value)
    }
}