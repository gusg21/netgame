import socketserver
import time
import enum

class GameEvent(enum.Enum):
    NONE = 0
    QUIT = 1

def create_packet(event: GameEvent, data: bytearray = bytearray()) -> bytearray:
    packet = bytearray()
    packet.append(event.value)  # type
    packet.append(len(data))    # data length
    packet.extend(data)         # data
    return packet

class ConnectionHandler(socketserver.BaseRequestHandler):
    def handle(self) -> None:
        data = self.request.recv(1024).strip()
        print(f"{time.strftime('%a %H:%M:%S')}: {data}")

        # Return response
        # self.request.sendall(create_packet(GameEvent.QUIT))

        return super().handle()

def main():
    print("Opening server...")
    server = socketserver.TCPServer(("localhost", 1719), ConnectionHandler)
    
    with server:
        server.serve_forever()

if __name__ == "__main__":
    main()