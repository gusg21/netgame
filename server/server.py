import socketserver
import socket
# import time
import datetime
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
    def __init__(self, name: str = "UNKNOWN PLAYER") -> None:
        self.name = name
        self.joined: bool = False

class Game():
    def __init__(self) -> None:
        print("Game constructed.")
        self._players: dict[socket.socket, PlayerData] = {}

    def add_player(self, socket: socket.socket) -> None:
        self._players[socket] = PlayerData()

    def remove_player(self, socket: socket.socket) -> None:
        print(self._players.keys())
        self._players.pop(socket)
    
    def has_player_with_socket(self, socket: socket) -> bool:
        return socket in self._players

    def player_join(self, socket: socket.socket, name: str) -> None:
        self._players[socket].name = name
        self._players[socket].joined = True

    def get_player_name(self, socket: socket.socket) -> str | None:
        if socket in self._players:
            return self._players[socket].name
        return None
    
    def get_player_names(self) -> list[str]:
        return [data.name for data in self._players.values() if data.joined]

class ClientHandler(socketserver.BaseRequestHandler):
    _game = Game()

    def client_print(self, text: object):
        print(f"{datetime.datetime.now().strftime("%m/%d/%Y, %H:%M:%S")}: {ClientHandler._game.get_player_name(self.request)}: " + str(text))

    def process_server_packet(self, packet: ServerPacket) -> ClientPacket | None:
        my_name = ClientHandler._game.get_player_name(self.request)
        if my_name:
            # print(f"Packet from {my_name = }")
            pass
        else:
            ClientHandler._game.add_player(self.request)
            self.client_print(f"New socket incoming from {self.client_address = }")

        match packet.get_event():
            case ServerEvent.NONE:
                pass
            case ServerEvent.CLIENT_JOIN:
                name = packet.get_data().decode().replace("\0", "").strip()
                self.client_print(f"Client joining ({name = })")
                ClientHandler._game.player_join(self.request, name)
                return ClientPacket(ClientEvent.ACK_JOIN)
            case ServerEvent.REQUEST_LOBBY_NAMES:
                return ClientPacket(ClientEvent.LIST_LOBBY_NAMES, ";".join(ClientHandler._game.get_player_names()).encode())
            case _:
                self.client_print(f"Can't handle packet of event {packet.get_event() = }")
                pass

    def handle(self) -> None:
        while True:
            # Read packet
            try:
                raw_bytes = self.request.recv(1024)
            except ConnectionError:
                name = ClientHandler._game.get_player_name(self.request)
                self.client_print(f"Connection to the client failed!")
                return

            # Parse
            server_packet = ServerPacket(raw_bytes)

            # Process
            response = self.process_server_packet(server_packet)

            # Return responses
            if response != None:
                self.request.sendall(response.to_bytes())

    def finish(self):
        ClientHandler._game.remove_player(self.request)

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer): pass

def main():
    print("Opening server...")
    server = ThreadedTCPServer(("localhost", 1719), ClientHandler)
    
    with server:
        server.serve_forever()

if __name__ == "__main__":
    main()