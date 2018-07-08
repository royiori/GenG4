const inilists = document.querySelectorAll('input.ini-need-store')

Array.prototype.forEach.call(inilists, (inilist) => {
    addInputListener(inilist)
})

// alert("->load ini-listener")

window.onload = function () {
    addTable(envTable, envContent)
    addTable(projTable, projContent)
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


