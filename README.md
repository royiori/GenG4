# GenG4

1. To distribute:
    1.1 Pack the python:
        a) goto the base folder of this project and run: 
                pyinstaller ./pygeng4/api.py 

        b) a api.spec will be generated automatically. Modify *.spec accordingly.
        c) remove the ./build and ./dist
                rm -rf ./build
                rm -rf ./dist

        d) run: pyinstaller pygeng4/api.spec --distpath pygeng4dist
                pyinstaller ./pygeng4/api.spec --distpath pygeng4dist

        e) remove the ./build folder
                rm -rf ./build

        f) goto ./pygeng4dist/api/ and run ./api to see whether is works or not. 
                cd ./pygeng4dist/api
                ./api

        g) open another terminal, and run:
           zerorpc tcp://localhost:4242 g4gen "pathToYourG4gen.ini/G4gen.ini"

        h) you'll find the error output message on the host terminal. Fix it accordingly.

        i) the common error is caused by the missing template files. 
           Copy them to under the ./pygeng4dist/api/ folder


   
    1.2 Pack the electron:
        a) before we pack the electron, try: "npm start" and click the 'generat' button to see it works or not
        b) if it works find, then goto the base folder of this project and run: 
            ./node_modules/.bin/electron-packager . --overwrite --ignore="pygeng4$" --ignore="\.vscode"
 

    1.3 Repack
        a) all commands:
            pyinstaller ./pygeng4/api.spec --distpath pygeng4dist
            rm -rf ./build
            ./node_modules/.bin/electron-packager . --overwrite --ignore="pygeng4$" --ignore="\.vscode"
            cp -r ./pygeng4/template ./GenG4-darwin-x64/GenG4.app/Contents/Resources/app/pygeng4dist/api/











