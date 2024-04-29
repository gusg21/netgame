//
// Created by angus.goucher on 4/18/2024.
//

#include "networker.h"

#include "eventqueue.h"

net::Networker::Networker()
{
    SockLibInit();

    m_Socket = new Socket(Socket::Family::INET, Socket::Type::STREAM);
    m_Socket->Connect(Address("127.0.0.1", 1719));
    m_Socket->SetNonBlockingMode(true);
}

void net::Networker::PostGameEvents(EventQueue* queue)
{
    char buffer[2048] = { 0 };
    int32_t bytesRecvd = m_Socket->Recv(buffer, 2047);
    if (bytesRecvd > 0) {
        char* packetStart = buffer;

        unsigned char packetType = *(packetStart + 0);

        while (packetType != NET_NONE_EVENT) {
            unsigned char packetDataLength = *(packetStart + 1);
            char* packetData = packetStart + 2;

            printf("NETWORKER: INFO: Incoming packet type %d, len %d\n", packetType, packetDataLength);
            switch (packetType) {
            case NET_CLIENT_QUIT_EVENT:
                queue->PostEvent({ .Type = EVENT_QUIT_EVENT });
                break;
            case NET_CLIENT_ACK_JOIN_EVENT:
                queue->PostEvent({ .Type = EVENT_ACK_JOIN_EVENT });
                break;
            case NET_CLIENT_LIST_LOBBY_NAMES_EVENT: {
                Event event = { .Type = EVENT_LIST_LOBBY_NAMES_EVENT };
                memcpy(event.Data.AsListLobbyNamesEvent.names, packetData, 255);
                queue->PostEvent(event);
                break;
            }
            case NET_CLIENT_START_GAME:
                queue->PostEvent({ .Type = EVENT_START_GAME_EVENT });
                break;
            case NET_CLIENT_CARD_STATE: {
                Event event {};
                event.Type = EVENT_CARD_STATE_EVENT;
                memcpy(event.Data.AsCardStateEvent.States, packetData, packetDataLength); // Works?
                queue->PostEvent(event);
                break;
            }
            default:
                printf("NETWORKER: WARN: Unhandled packet type %d\n", packetType);
                break;
            }

            packetStart += packetDataLength + 2; // (type (1 byte) + length (1 byte) = packet header size of 2)
            packetType = *(packetStart + 0);
        }
    }
}

void net::Networker::SendServerEvent(net::ServerEvent event)
{
    // Send the event
    const char* packet = (const char*)&event;
    m_Socket->Send(packet, sizeof(ServerEvent));
}
