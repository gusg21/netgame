//
// Created by angus.goucher on 4/18/2024.
//

#include "networker.h"

net::Networker::Networker() {
	SockLibInit();

	m_Socket = new Socket(Socket::Family::INET, Socket::Type::STREAM);
}

void net::Networker::Update() {

}