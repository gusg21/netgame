import datetime
import enum
import random
import socket
import struct
import math

from packets import ClientPacket

class PlayerData():
    def __init__(self, name: str = "UNKNOWN PLAYER") -> None:
        self.name = name
        self.joined: bool = False

class GameState(enum.Enum):
    LOBBY = 0
    GAME = 1
    FINISH = 2

class Card():
    next_id = 1

    def __init__(self, value: int, x: float, y: float):
        self.id = Card.next_id
        self.value = value
        self.x = x
        self.y = y
        self.owner: socket.socket = None

        Card.next_id += 1
        if Card.next_id == 0: # 0 counts as a non-existent card
            Card.next_id = 1

    def to_bytes(self) -> bytearray:
        array = bytearray()
        array.extend(struct.pack("IIff", self.id, self.value, self.x, self.y))
        return array

    def distance_to(self, other):
        return math.dist((self.x, self.y), (other.x, other.y))

class Game():
    def __init__(self) -> None:
        self.game_print("Game constructed.")
        self._players: dict[socket.socket, PlayerData] = {}
        self._state: GameState = GameState.LOBBY
        self._cards: list[Card] = []
        self._combos: list[tuple[float, float]] = []

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
        self._combos.clear()
        for _ in range(2):
            self._cards.append(Card(random.randint(1, 10), random.randrange(-100, 100), random.randrange(-100, 100)))

    def get_cards(self) -> list[Card]:
        return self._cards

    def update_card(self, id: int, x: float, y: float, player: socket.socket):
        for card in self._cards:
            if card.id == id and card.owner == player:
                card.x = x
                card.y = y
    
    def can_pick_up_card(self, id: int, player: socket.socket) -> bool:
        if id == 0:
            self.game_print(f"Player {player} attempted to bick up NULL card")
            return False
        for card in self._cards:
            if card.id == id:
                if card.owner == None:
                    self.game_print(f"Player {player} picked up card {id=}")
                    return True
        return False

    def pick_up_card(self, id: int, player: socket.socket):
        if id == 0:
            return
        for card in self._cards:
            if card.id == id:
                card.owner = player
    
    def put_down_card(self, id: int, player: socket.socket):
        if id == 0:
            return 0
        for card in self._cards:
            if card.id == id:
                if card.owner != player:
                    self.game_print("Different player attempting to release already held card!")
                else:
                    card.owner = None
                    self.stack_cards()

    def get_card_combos(self):
        combos = self._combos.copy()
        self._combos.clear()
        return combos

    def stack_cards(self):
        # O(n^2) :(
        for card in self._cards:
            if card.id == 0:
                continue

            for other_card in self._cards:
                if other_card.id == 0:
                    continue

                if card == other_card:
                    continue
                    
                if card.distance_to(other_card) < 20 and card.value == other_card.value:
                    avg_x = (card.x + other_card.x) / 2.0
                    avg_y = (card.y + other_card.y) / 2.0
                    other_card.id = 0
                    card.x = avg_x
                    card.y = avg_y
                    self._combos.append((avg_x, avg_y))

    def is_complete(self):
        unstacked_vals = []
        for card in self._cards:
            if card.id == 0:
                continue
            if card.value not in unstacked_vals:
                unstacked_vals.append(card.value)
            else:
                return False
        return True
    
    def finish_game(self):
        self._state = GameState.FINISH