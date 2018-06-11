const settings = require('electron-settings')

const NBody = document.getElementById('NBody')
const detset = document.getElementById('det-setting')

NBody.addEventListener('change', function () {
  type = /^[0-9]*[1-9][0-9]*$/
  reg = new RegExp(type)
  nbody = parseInt(NBody.value)

  if (NBody.value.match(reg) != null && nbody < 100) {
    detset.innerHTML = ""
    for (let index = 0; index < nbody; index++) {
      AddDetectorSetting(index + 1) //start from 1
    }
    $(".chosen-select").chosen({width: "60%"})
  }
  else {
    alert('必须输入小于100的正整数')
    NBody.value = ''
  }
})

//_________________________________________
//
//function RemoveDetectorSetting() {
  //detdiv = document.getElementById('det' + index)
  //while (detdiv.hasChildNodes()) //当div下还存在子节点时 循环继续
  //{
  //  detdiv.removeChild(detdiv.firstChild);
  //}
  //detset.removeChild(detdev)
//}

//_________________________________________
//
function AddDetectorSetting(index) {
  const detdiv = document.getElementById('det-setting')

  div1 = document.createElement('div')
  div1.id = 'det' + index
  div1.setAttribute('class', 'demo det-done')

  div2 = document.createElement('div')
  div2.setAttribute('class', 'demo-wrapper')

  but3 = document.createElement('button')
  but3.setAttribute('class', 'js-container-target demo-toggle-button')
  but3.id = 'setDetector-bodybtn' + index

  div3 = document.createElement('div')
  div3.setAttribute('class', 'demo-meta u-avoid-clicks')
  div3.id = 'setDetector-bodydiv' + index

  div4 = document.createElement('div')
  div4.setAttribute('class', 'demo-box')

  table = document.createElement('table')

  content = new Array(
    "ID:", "BodyID",
    "Name:", "BodyName",
    "Material:", "BodyMatt",
    "Shape:", "BodyShape",
    "Mother ID:", "BodyMoth",
    "Size (...):", "BodySize",
    "Position (X,Y,Z):", "BodyPos",
    "Rotation (X,Y,Z):", "BodyRot",
    "Visual Color:", "BodyVisAtt",
    "Step Limit:", "BodyStepLmt",
    "Set the SD class:", "BodySDClass",
    "Set the Hit class:", "BodyHitClass"
  )

  for (i = 0; i < content.length; i += 2) {
    tr = document.createElement('tr')
    td1 = document.createElement('td')
    p1 = document.createElement('p')
    p1.innerText = content[i]

    td2 = document.createElement('td')
    table.appendChild(tr)
    tr.appendChild(td1)
    tr.appendChild(td2)
    td1.appendChild(p1)

    idtemp = content[i + 1] + index
    const defaultVal = settings.get(idtemp)

    if (i == 0 * 2) { //ID
      pp = document.createElement('p')
      pp.setAttribute('id', idtemp)
      td2.appendChild(pp)

      if (defaultVal) 
      {
        pp.innerText = defaultVal
        but3.innerText = 'Set Body' + index + ': '+defaultVal
        div3.innerText = '设置几何体'+ index + ' ' + defaultVal
      }
      else {
        but3.innerText = 'Set Body' + index 
        div3.innerText = '设置几何体'+ index 
      }
    }
    else if (i == 1 * 2) { //Name, accept Name input(id/input) and set ID to the uppercase(id2/pp2)
      input = document.createElement('input')
      input.setAttribute('type', 'text')
      input.setAttribute('id', idtemp)
      td2.appendChild(input)

      if (defaultVal) input.value = defaultVal

      input.addEventListener('change', function () {
        id = this.id
        value = this.value

        if (value == value.toUpperCase()) {
          alert('必须同时包含有大小写的字母')
          this.value = ''
        } 
        else { 
          index = id.replace("BodyName","")
          id2 = "BodyID"+index
          pp2 = document.getElementById("BodyID"+index)
          pp2.innerText = value.toUpperCase()
          settings.set(id, value) 
          settings.set(id2, pp2.innerText) 

          btn3 = document.getElementById("setDetector-bodybtn" + index)
          btn3.innerText = 'Set Body' + index + ': '+value.toUpperCase()

          div3 = document.createElement('div')
          div3.setAttribute('class', 'demo-meta u-avoid-clicks')
          div3.id = 'setDetector-bodydiv' + index
          div3.innerText = '设置几何体'+ index + value.toUpperCase()
          btn3.appendChild(div3)
        }
      })
    }
    else if (i == 2 * 2) { //Material
      addGroupDropDown(td2, idtemp, 'Material')
    }
    else if (i == 3 * 2) { //SHAPE
      addDropDown(td2, idtemp, 'DetectorShape')
    }
    else if(i == 8 * 2) {
      input = document.createElement('input')
      input.setAttribute('type', 'color')
      input.setAttribute('class', 'colorInput')
      input.id = idtemp
      td2.appendChild(input)

      if (defaultVal) {
        input.value = defaultVal
      }

      input.addEventListener('change', function () {
        settings.set(this.id, this.value)
      })
    }
    else {
      input = document.createElement('input')
      input.setAttribute('type', 'text')
      input.setAttribute('class', 'ini-need-store')
      input.setAttribute('id', idtemp)
      td2.appendChild(input)
    }
  }

  detdiv.appendChild(div1)
  div1.appendChild(div2)
  div2.appendChild(but3)
  div2.appendChild(div4)
  but3.appendChild(div3)
  div4.appendChild(table)

  but3.addEventListener('click', (event) => {
    const parent = event.target.parentElement
    parent.classList.toggle('is-open')
  })
}
