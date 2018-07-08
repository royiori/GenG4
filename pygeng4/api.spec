# -*- mode: python -*-

block_cipher = None


a = Analysis(['api.py'],
             pathex=['/Users/liuqian/Documents/GitHub/GenG4/pygeng4'],
             binaries=[],
             datas=[],
             hiddenimports = [ #for gevent 1.3.1
                'gevent.__greenlet_primitives',
                'gevent.__hub_local',
                'gevent.__hub_primitives',
                'gevent.__ident',
                'gevent.__imap',
                'gevent.__semaphore',
                'gevent.__tracer',
                'gevent.__waiter',
                'gevent._event',
                'gevent._greenlet',
                'gevent._local',
                'gevent._queue',

                # info steal from gevent.monkey patch_all() args
                'gevent.os',
                'gevent.time',
                'gevent.thread',
                # 'gevent.sys',
                'gevent.socket',
                'gevent.select',
                'gevent.ssl',
                # 'gevent.httplib',
                'gevent.subprocess',
                'gevent.builtins',
                'gevent.signal',

                'gevent.libev',
                'gevent.libev.corecext',
                'gevent.libev.corecffi',
                'gevent.libev.watcher',

                'gevent.libuv',
                'gevent.libuv._corecffi',
                'gevent.libuv.loop',
                'gevent.libuv.watcher',
             ],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          exclude_binaries=True,
          name='api',
          debug=False,
          strip=False,
          upx=True,
          console=True )
coll = COLLECT(exe,
               a.binaries,
               a.zipfiles,
               a.datas,
               strip=False,
               upx=True,
               name='api')
