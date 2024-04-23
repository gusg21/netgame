#include "state.h"
#include "actor.h"
#include <memory>

void net::State::Update()
{
}

void net::State::Draw()
{
}

void net::State::AddActor(std::shared_ptr<Actor> actor)
{
	m_Actors.push_back(actor);
}
