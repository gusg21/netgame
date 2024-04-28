import socketserver
import socket
import time
import enum

class ClientEvent(enum.Enum):
    NONE = 0
    QUIT = 1
    ACK_JOIN = 2
    LIST_LOBBY_NAMES = 3

class ClientPacket():
    def __init__(self, event: ClientEvent, data: bytearray = bytearray()):
        self._event = event
        self._data = data

    def get_event(self) -> ClientEvent:
        return self._event
    
    def get_data(self) -> bytearray:
        return self._data

    def to_bytes(self) -> bytes:
        packet = bytearray()
        packet.append(self._event.value)  # type
        packet.append(len(self._data))    # data length
        packet.extend(self._data)         # data
        return packet

class ServerEvent(enum.Enum):
    NONE = 0
    CLIENT_JOIN = 1
    REQUEST_LOBBY_NAMES = 2

class ServerPacket():
    def __init__(self, data: bytearray) -> None:
        assert len(data) > 1, "Need data to construct ServerPacket!"

        self._event = data[0]
        self._data = data[1:]
    
    def get_event(self) -> ServerEvent:
        return ServerEvent(self._event)
    
    def get_data(self) -> bytearray:
        return self._data

class PlayerData():
    def __init__(self, name) -> None:
        self.name = name

class Game():
    def __init__(self) -> None:
        print("Game constructed.")
        self._players: dict[socket.socket, PlayerData] = {}

    def add_player(self, name: str, socket: socket.socket) -> None:
        self._players[socket] = PlayerData(name)

    def remove_player(self, socket: socket.socket) -> None:
        self._players.pop(socket)
    
    def has_player_with_socket(self, socket: socket) -> bool:
        return socket in self._players

    def get_player_name(self, socket: socket.socket) -> str | None:
        if socket in self._players:
            return self._players[socket].name
        return None
    
    def get_player_names(self) -> list[str]:
        return [data.name for data in self._players.values()]

class ConnectionHandler(socketserver.BaseRequestHandler):
    _game = Game()

    def process_server_packet(self, packet: ServerPacket) -> ClientPacket | None:
        my_name = type(self)._game.get_player_name(self.request)
        if my_name:
            print(f"Packet from {my_name = }")
        else:
            print("New socket incoming")

        match packet.get_event():
            case ServerEvent.NONE:
                pass
            case ServerEvent.CLIENT_JOIN:
                name = packet.get_data().decode().replace("\0", "").strip()
                print(f"Client joining ({name = })")
                type(self)._game.add_player(name, self.request)
                return ClientPacket(ClientEvent.ACK_JOIN)
            case ServerEvent.REQUEST_LOBBY_NAMES:
                return ClientPacket(ClientEvent.LIST_LOBBY_NAMES, ";".join(type(self)._game.get_player_names()).encode())
            case _:
                print(f"Can't handle packet of event {packet.get_event() = }")
                pass

    def handle(self) -> None:
        while True:
            # Read packet
            try:
                raw_bytes = self.request.recv(1024)
            except ConnectionError:
                name = type(self)._game.get_player_name(self.request)
                print(f"Connection to the client ({name = }) failed!")
                return

            # Parse
            server_packet = ServerPacket(raw_bytes)

            # Process
            response = self.process_server_packet(server_packet)

            # Return responses
            if response != None:
                self.request.sendall(response.to_bytes())

def main():
    print("Opening server...")
    server = socketserver.TCPServer(("localhost", 1719), ConnectionHandler)
    
    with server:
        server.serve_forever()

if __name__ == "__main__":
    main()