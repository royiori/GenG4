const inilists = document.querySelectorAll('input.ini-need-store')

Array.prototype.forEach.call(inilists, (inilist) => {
    addInputListener(inilist)
})

$(".chosen-select").chosen({width: "45%"})