from __future__ import print_function
from G4gen import G4gen as real_G4Gen
import sys
import zerorpc

class G4GenApi(object) : 
    def g4gen(self, text) :
        try : 
            return real_G4Gen(text)
        except Exception as e:
            return -99
    def echo(self, text) :
        return text

def parse_port():
    port = 4242
    try:
        port = int(sys.argv[1])
    except Exception as e:
        pass
    return '{}'.format(port)

def main():
    addr = 'tcp://127.0.0.1:' + parse_port()
    s = zerorpc.Server(G4GenApi())
    s.bind(addr)
    print('start running on {}'.format(addr))
    s.run()

if __name__ == '__main__':
    main()
