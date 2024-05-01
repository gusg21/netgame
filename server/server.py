import socketserver
# import time
import datetime
import struct

from events import ClientEvent, ServerEvent
from packets import ClientPacket, ServerPacket
from game import Game

class ClientHandler(socketserver.BaseRequestHandler):
    _game = None

    def construct_the_game() -> None:
        ClientHandler._game = Game()

    def broadcast(packet: ClientPacket) -> None:
        for player_sock, data in ClientHandler._game.get_players().items():
            if data.joined:
                player_sock.send(packet.to_bytes())

    def get_the_game(self) -> Game:
        return ClientHandler._game

    def client_print(self, text: object):
        print(f"{datetime.datetime.now().strftime("%m/%d/%Y, %H:%M:%S")}: {ClientHandler._game.get_player_name(self.request)}: " + str(text))

    def process_server_packet(self, packet: ServerPacket) -> list[ClientPacket] | ClientPacket | None:
        # Debug Info
        my_name = self.get_the_game().get_player_name(self.request)
        if my_name:
            # print(f"Packet from {my_name = }")
            pass
        else:
            self.get_the_game().add_player(self.request)
            self.client_print(f"New socket incoming from {self.client_address = }")

        # Handle packet event
        match packet.get_event():
            case ServerEvent.NONE:
                pass
            case ServerEvent.CLIENT_JOIN:
                name = packet.get_data().decode().replace("\0", "").strip()
                self.client_print(f"Client joining ({name = })")
                if self.get_the_game().player_join(self.request, name):
                    return ClientPacket(ClientEvent.ACK_JOIN)
                else:
                    self.client_print("Can't join game.")
                    return None # Can't join (game in progress, etc.)
            case ServerEvent.REQUEST_LOBBY_NAMES:
                return ClientPacket(ClientEvent.LIST_LOBBY_NAMES, ";".join(self.get_the_game().get_player_names()).encode())
            case ServerEvent.REQUEST_START_GAME:
                if self.get_the_game().is_in_lobby() and self.get_the_game().get_player_count() > 1:
                    self.get_the_game().start_game()
                    ClientHandler.broadcast(ClientPacket(ClientEvent.START_GAME))
                    return None
                else:
                    self.client_print("Can't start the game.")
                    return None
            case ServerEvent.REQUEST_CARD_STATE:
                data = bytearray()
                for card in self.get_the_game().get_cards():
                    data.extend(card.to_bytes())
                return ClientPacket(ClientEvent.CARD_STATE, data)
            case ServerEvent.PICK_UP_CARD:
                card_id = packet.get_data()[0]
                self.client_print(f"Picking up card {card_id=}")
                if self.get_the_game().can_pick_up_card(card_id, self.request):
                    raw_data = bytearray()
                    raw_data.append(card_id)
                    self.get_the_game().pick_up_card(card_id, self.request)
                    return ClientPacket(ClientEvent.ALLOW_CARD_MOVE, data=raw_data)
                else:
                    return None
            case ServerEvent.PUT_DOWN_CARD:
                card_id = packet.get_data()[0]
                raw_data = bytearray()
                raw_data.append(card_id)
                self.get_the_game().put_down_card(card_id, self.request)
                pack = ClientPacket(ClientEvent.FINISH_CARD_MOVE, data=raw_data)
                for combo in self.get_the_game().get_card_combos():
                    combo_data = bytearray()
                    combo_data.extend(struct.pack("ff", combo[0], combo[1]))
                    ClientHandler.broadcast(ClientPacket(ClientEvent.CARDS_COMBINED, data=combo_data))
                if self.get_the_game().is_complete():
                    ClientHandler.broadcast(ClientPacket(ClientEvent.GAME_FINISHED, data=self.get_the_game().get_game_finished_data()))
                    self.get_the_game().finish_game()
                return pack
            case ServerEvent.MOVE_CARD:
                id, x, y = struct.unpack("Iff", packet.get_data()[:12])
                self.get_the_game().update_card(id, x, y, self.request)
                return None
            case _:
                self.client_print(f"Can't handle packet of event {packet.get_event() = }")
                pass

    def handle(self) -> None:
        while True:
            # Read packet
            try:
                raw_bytes = self.request.recv(1024)
            except ConnectionError:
                self.client_print(f"Connection to the client failed!")
                return

            # Parse
            try:
                server_packet = ServerPacket(raw_bytes)
            except ValueError:
                self.client_print(f"Client served empty packet, disconnecting...")
                return

            # Process
            response = self.process_server_packet(server_packet)

            # Return responses
            if response != None:
                if isinstance(response, list):
                    for r in response:
                        self.request.sendall(r.to_bytes())
                else:
                    self.request.sendall(response.to_bytes())
                

    def finish(self):
        ClientHandler._game.remove_player(self.request)

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer): pass

def server_print(text: object):
    print(f"{datetime.datetime.now().strftime("%m/%d/%Y, %H:%M:%S")}: SERVER: " + str(text))

def main():
    server_print("Opening server...")
    server = ThreadedTCPServer(("localhost", 1719), ClientHandler)
    ClientHandler.construct_the_game()
    
    with server:
        server.serve_forever()

if __name__ == "__main__":
    main()