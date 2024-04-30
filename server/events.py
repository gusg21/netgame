import enum

class ServerEvent(enum.Enum):
    NONE = 0
    CLIENT_JOIN = 1
    REQUEST_LOBBY_NAMES = 2
    REQUEST_START_GAME = 3
    REQUEST_CARD_STATE = 4
    MOVE_CARD = 5
    PUT_DOWN_CARD = 6
    PICK_UP_CARD = 7

class ClientEvent(enum.Enum):
    NONE = 0
    QUIT = 1
    ACK_JOIN = 2
    LIST_LOBBY_NAMES = 3
    START_GAME = 4
    CARD_STATE = 5
    DONT_WORRY_ABOUT_IT = 6
    ALLOW_CARD_MOVE = 7
    FINISH_CARD_MOVE = 8
    CARDS_COMBINED = 9
    GAME_FINISHED = 10