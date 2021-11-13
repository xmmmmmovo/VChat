import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


def main():
    s.connect("127.0.0.1", 9000)
    s.sendall(b"114514")
    res = s.recv(1024)
    print(res)


main()
