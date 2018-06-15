const generator = document.getElementById('generator')
const genOutput = document.getElementById('genOutput')

function getMattCode(value){
    code = ""

     for (key in iniMattList) {
         for (var i = 0; i < iniMattList[key].length; i += 6) {
            item = iniMattList[key][i + 1] + " " + iniMattList[key][i + 2]
            if (value == item) {
                code = iniMattList[key][i+3]
                break 
            }
        }
    }
    return code
}

function getShapeCode(value) {
    code = ""

     for (key in iniShapeList) {
        item = iniShapeList[key][0]
        if (value == item) {
            code = iniShapeList[key][1]
            break 
        }
    }

    return code
}

function getGunCode(value){
    code = value

     for (key in iniParticleList) {
         for (var i = 0; i < iniParticleList[key].length; i += 6) {
            div = document.createElement('div')
            item = iniParticleList[key][i + 1] + " " + iniParticleList[key][i + 2]
            div.innerHTML = item
            if (value == div.innerText) {
                code = iniParticleList[key][i]
                delete div
                break 
            }
            delete div
        }
    }
    return code
}

generator.addEventListener('click', function () {
    conreg = new RegExp(/c\d/, 'g')

    mesg = "<br />output:<br>"
    for(mkey in iniData) 
    {
        if(conreg.test(mkey)) {
            mesg = mesg + "________________________________<br><p>[" +iniData[mkey] + "]</p>"
        }
        else if(mkey=="cend") {
            break
        }
        else if(mkey == "NBody") {
            mesg =  mesg + "<p>" + mkey + " : " + iniData[mkey] + "</p><br />"

            for(index=1; index<=parseInt(iniData[mkey]); index++) 
            {
                iniDetKey.forEach(function (element) {
                    nkey = element + index
                    value = iniData[nkey]
                    if(nkey.indexOf("BodyMatt")==0) value = getMattCode(value)
                    if(nkey.indexOf("BodyShap")==0) value = getShapeCode(value)

                    mesg =  mesg + "<p>" + nkey+" : " + value + "</p>"
                })
                if(index != parseInt(iniData[mkey]))
                    mesg = mesg + "<br />"
            }
        }
        else if(mkey.indexOf("GunParticle")==0) {
            value = iniData[mkey]
            value = getGunCode(value)
            mesg =  mesg + "<p>" + mkey+" : " + value + "</p>"
        }
        else {
            mesg =  mesg + "<p>" + mkey+" : " + iniData[mkey] + "</p>"
        }
    }
    genOutput.innerHTML = mesg
})