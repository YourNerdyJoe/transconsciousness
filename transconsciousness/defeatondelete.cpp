#include "defeatondelete.h"
#include "engine.h"

DefeatOnDelete::DefeatOnDelete(GameObject* parent) : Component(parent)
{
}

DefeatOnDelete::~DefeatOnDelete()
{
	Engine::setState(Engine::S_DEFEAT);
}
