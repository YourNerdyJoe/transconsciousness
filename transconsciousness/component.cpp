#include "component.h"

Component::Component(GameObject* parent) : parent(parent)
{
}

Component::~Component()
{
}

void Component::update()
{
}

void Component::handleMessage(const Message* msg)
{
}

void Component::render()
{
}
