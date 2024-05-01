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
            case NET_CLIENT_QUIT:
                queue->PostEvent({ .Type = EVENT_QUIT_EVENT });
                break;
            case NET_CLIENT_ACK_JOIN:
                queue->PostEvent({ .Type = EVENT_ACK_JOIN_EVENT });
                break;
            case NET_CLIENT_LIST_LOBBY_NAMES: {
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
            case NET_CLIENT_ALLOW_CARD_MOVE: {
                Event event {};
                event.Type = EVENT_ALLOW_CARD_MOVE_EVENT;
                event.Data.AsAllowCardMoveEvent.CardId = packetData[0];
                queue->PostEvent(event);
                break;
            }
            case NET_CLIENT_FINISH_CARD_MOVE: {
                Event event {};
                event.Type = EVENT_FINISH_CARD_MOVE_EVENT;
                event.Data.AsFinishCardMoveEvent.CardId = packetData[0];
                queue->PostEvent(event);
                break;
            }
            case NET_CLIENT_CARDS_COMBINED: {
                Event event {};
                event.Type = EVENT_CARDS_COMBINED_EVENT;
                event.Data.AsCardsCombinedEvent.X = *(float*)&packetData[0];
                event.Data.AsCardsCombinedEvent.Y = *(float*)&packetData[sizeof(float)];
                queue->PostEvent(event);
                break;
            }
            case NET_CLIENT_GAME_FINISHED: {
                Event event {};
                event.Type = EVENT_GAME_FINISHED;
                memcpy(event.Data.AsGameFinishedEvent.Infos, packetData, EVENT_NUM_GAME_FINISH_INFOS * sizeof(GameFinishInfo));
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
