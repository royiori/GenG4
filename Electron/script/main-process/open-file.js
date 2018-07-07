const {ipcMain, dialog} = require('electron')

ipcMain.on('open-file-dialog', (event, arg) => {
  dialog.showOpenDialog({
    properties: ['openFile', 'openDirectory']
  }, (files) => {
    if (files) {
      event.sender.send('selected-directory', files + ":" + arg) 
    }
  })
})
