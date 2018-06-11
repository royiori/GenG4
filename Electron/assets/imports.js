const links = document.querySelectorAll('link[rel="import"]')
const debug = 1
// Import and add each page to the DOM
// alert("->load imports")
Array.prototype.forEach.call(links, (link) => {
  let template = link.import.querySelector('.task-template')
  let clone = document.importNode(template.content, true)
  if (link.href.match('about.html')) {
    document.querySelector('body').appendChild(clone)
  } else {
    document.querySelector('.content').appendChild(clone)
  }
})
// alert("->load imports done")
