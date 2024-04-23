//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_EVENTQUEUE_H
#define NETGAME_EVENTQUEUE_H

#include <queue>
#include <raylib.h>

namespace net {
	struct KeyEvent {
		uint32_t Key;
		bool Pressed;
	};

	struct CustomEvent {
		void* Data;
	};

	union Event {
		uint32_t Type;

		KeyEvent AsKeyEvent;
		CustomEvent AsCustomEvent;
	};

	class EventQueue {
	public:
		bool IsEmpty() { return m_Queue.empty(); };
		Event PopNextEvent();

	private:
		std::queue<Event> m_Queue;
	};
}

#endif