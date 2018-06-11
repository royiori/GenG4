const settings = require('electron-settings')

// alert("->load add-dropdown")
// Import and add each content to the dropdown button
const dropdowns = document.querySelectorAll('div.dropdown')
Array.prototype.forEach.call(dropdowns, (dropdown) => {
    key = dropdown.getAttribute('id')
    addDropDown(dropdown, key, key)
})

// alert("->load add-dropdown done")