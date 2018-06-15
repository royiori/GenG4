const inilists = document.querySelectorAll('input.ini-need-store')

Array.prototype.forEach.call(inilists, (inilist) => {
    addInputListener(inilist)
})

// alert("->load ini-listener")

window.onload = function () {
    addTable(projTable, projContent)
    addTable(envTable, envContent)
    addTable(basicTable, basicContent)
    addTable(classNameTable, classNameContent)

    addTable(physicsTable, physicsContent)

    NBody.value = settings.get('NBody')
    nbody = parseInt(NBody.value)
    updateIDList(nbody)
    addDetectorPage(nbody)

    addTable(gunTable, gunContent)

    initialization()
}


