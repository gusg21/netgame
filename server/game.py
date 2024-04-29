import datetime
import enum
import random
import socket
import struct

from packets import ClientPacket

class PlayerData():
    def __init__(self, name: str = "UNKNOWN PLAYER") -> None:
        self.name = name
        self.joined: bool = False

class GameState(enum.Enum):
    LOBBY = 0
    GAME = 1

class Card():
    next_id = 1

    def __init__(self, value: int, x: float, y: float):
        self.id = Card.next_id
        self.value = value
        self.x = x
        self.y = y

        Card.next_id += 1
        if Card.next_id == 0: # 0 counts as a non-existent card
            Card.next_id = 1

    def to_bytes(self) -> bytearray:
        array = bytearray()
        array.extend(struct.pack("IIff", self.id, self.value, self.x, self.y))
        return array

class Game():
    def __init__(self) -> None:
        self.game_print("Game constructed.")
        self._players: dict[socket.socket, PlayerData] = {}
        self._state: GameState = GameState.LOBBY
        self._cards: list[Card] = []

    def game_print(self, text: object):
        print(f"{datetime.datetime.now().strftime("%m/%d/%Y, %H:%M:%S")}: GAME: " + str(text))

    def add_player(self, socket: socket.socket) -> None:
        self._players[socket] = PlayerData()

    def remove_player(self, socket: socket.socket) -> None:
        # print(self._players.keys())
        self._players.pop(socket)

        if self.get_player_count() == 0:
            self._state = GameState.LOBBY
            self.game_print("All players left; returning to LOBBY")
    
    def has_player_with_socket(self, socket: socket) -> bool:
        return socket in self._players

    def player_join(self, socket: socket.socket, name: str) -> bool:
        if self._state == GameState.LOBBY:
            data = self._players[socket]
            data.name = name
            data.joined = True
            return True
        else:
            return False

    def get_player_name(self, socket: socket.socket) -> str | None:
        if socket in self._players:
            return self._players[socket].name
        return None
    
    def get_player_names(self) -> list[str]:
        return [data.name for data in self._players.values() if data.joined]
    
    def get_player_count(self) -> int:
        return len([data for data in self._players.values() if data.joined])
    
    def get_players(self) -> dict[socket.socket, PlayerData]:
        return self._players
    
    def is_in_lobby(self) -> bool:
        return self._state == GameState.LOBBY

    def is_in_game(self) -> bool:
        return self._state == GameState.GAME

    def start_game(self) -> None:
        self.game_print("Game begun! Entering GAME")
        self._state = GameState.GAME
        
        self.game_print("Setting up play...")
        self._cards.clear()
        for _ in range(10):
            self._cards.append(Card(random.randint(1, 10), random.randrange(-200, 200), random.randrange(-100, 100)))

    def get_cards(self) -> list[Card]:
        return self._cards

    def update_card(self, id, x, y):
        for card in self._cards:
            if card.id == id:
                card.x = x
                card.y = y