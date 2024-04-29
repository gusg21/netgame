import enum

class ServerEvent(enum.Enum):
    NONE = 0
    CLIENT_JOIN = 1
    REQUEST_LOBBY_NAMES = 2
    REQUEST_START_GAME = 3
    REQUEST_CARD_STATE = 4
    MOVE_CARD = 5

class ClientEvent(enum.Enum):
    NONE = 0
    QUIT = 1
    ACK_JOIN = 2
    LIST_LOBBY_NAMES = 3
    START_GAME = 4
    CARD_STATE = 5