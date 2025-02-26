# TCP client program (Python 3 version)

import socket
import sys

MAX_LINE = 256

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <server_host> <port>", file=sys.stderr)
        sys.exit(1)

    host = sys.argv[1]
    port = int(sys.argv[2])

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        server_address = (host, port)
        s.connect(server_address)
        print("Connected to the server. Type messages, press enter to send, 'ctrl+d' to quit.")
    except socket.error as e:
        print(f"{sys.argv[0]}: connect error: {e}", file=sys.stderr)
        s.close()
        sys.exit(1)

    try:
        while True:
            line = input()
            if line:
                line = line[:MAX_LINE-2] + '\n\0'
                s.sendall(line.encode())
            data = s.recv(MAX_LINE)
            print(f"Server says: {data.decode()[:-1]}")  # Adjusted for the correct removal of '\0'
    except EOFError:
        pass
    finally:
        print(f"{sys.argv[0]}: Connection closed by client.")
        s.close()

if __name__ == "__main__":
    main()

