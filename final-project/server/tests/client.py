import socket
import select
import sys
import os

ip = "127.0.0.1"
port = 12345

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.connect((ip, port))
    while True:
        slist = [sys.stdin, server]
        read_sockets, write_socket, error_socket = select.select(slist, [], [])

        for socks in read_sockets:
            if socks == server:
                message = socks.recv(2048)
                print(message)
            else:
                message = sys.stdin.readline()
                server.send(message)
                sys.stdout.write("<You>")
                sys.stdout.write(message)
                sys.stdout.flush()
    server.close()


main()
