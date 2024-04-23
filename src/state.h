#pragma once
#include <vector>
#include <memory>
#include "actor.h"

namespace net {
	class State {
	public:
		void Update();
		void Draw();

		void AddActor(std::shared_ptr<Actor> actor);

	private:
		std::vector<std::shared_ptr<Actor>> m_Actors;
	};
}