import socket
import sys

class BoardClient:
    
    __num = 0

    def __init__(self, host='localhost', port=4444):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.connect((host, port))
        self.num = BoardClient.__num
        BoardClient.__num += 1
        print("Client {} connected to {} on port {}".format(self.num, host, port))
    
    def send(self, val):
        self.s.send((val+'\n').encode())

    def get(self):
        self.send("?")
        ret = self.s.recv(1024).decode().strip()
        print("Client {} recieved '{}'".format(self.num, ret))
        return ret

    
    def post(self, val):
        self.send("!"+val)
        print("Client {} sent '{}'".format(self.num, val))


if __name__ == '__main__':
    
    cl1 = BoardClient(port=4444)
    cl2 = BoardClient(port=4444)

    cl1.get()
    cl1.post('hi')
    cl2.get()
    cl1.get()
    cl2.post('bye')
    cl1.get()
