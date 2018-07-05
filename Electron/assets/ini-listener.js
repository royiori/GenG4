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

const zerorpc = require("zerorpc")
let client = new zerorpc.Client()
client.connect("tcp://127.0.0.1:4242")

let formula = document.querySelector('#formula')
let result = document.querySelector('#result')
formula.addEventListener('input', () => {
  client.invoke("calc", formula.value, (error, res) => {
    if(error) {
      console.error(error)
    } else {
      result.textContent = res
    }
  })
})
formula.dispatchEvent(new Event('input'))

