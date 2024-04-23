#pragma once
#include <vector>
#include <memory>
#include "actor.h"

namespace net {
	class State {
	public:
		void Update();
		void Draw();

		bool GetValidity() { return m_Valid; }
		void SetValidity(bool valid) { m_Valid = valid; }

		void AddActor(std::shared_ptr<Actor> actor);

	private:
		bool m_Valid = false;

		std::vector<std::shared_ptr<Actor>> m_Actors;
	};
}