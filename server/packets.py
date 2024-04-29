import struct

from events import ClientEvent, ServerEvent

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
        packet.extend(struct.pack("BB", self._event.value, len(self._data)))  # type, length
        packet.extend(self._data)         # data
        return packet

class ServerPacket():
    def __init__(self, data: bytearray) -> None:
        if len(data) < 2:
            raise ValueError(data)

        self._event = data[0]
        self._data = data[1:]
    
    def get_event(self) -> ServerEvent:
        return ServerEvent(self._event)
    
    def get_data(self) -> bytearray:
        return self._data