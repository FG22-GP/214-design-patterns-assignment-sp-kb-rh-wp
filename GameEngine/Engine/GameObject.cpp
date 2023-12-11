#include "GameObject.h"

#include <charconv>
#include <cmath>
#include <string>

GameObject::GameObject(const char* path, SDL_FPoint* position, SDL_FPoint* size)
{
    image = new Image(path, position, size);
    components = new std::list<Component*>();
}

void GameObject::SetPosition(SDL_FPoint* point)
{
    image->position = point;
}

void GameObject::Move(SDL_FPoint* direction, const float distance)
{
    auto newPosition = new SDL_FPoint{
        image->position->x + direction->x * distance, image->position->y - direction->y * distance
    };
    SetPosition(newPosition);
}

void GameObject::Update(float deltaTime)
{
    for (auto it = components->begin(); it != components->end(); ++it)
    {
        (*it)->Update(*this, deltaTime);
    }
}

void GameObject::AddComponent(Component* component)
{
    components->push_back(component);
}

GameObject* GameObject::Instantiate(SDL_FPoint* position, SDL_FPoint* size, const char* imagePath)
{
    const auto go = new GameObject(imagePath, position, size);
    gameObjects->push_back(go);
    return go;
}

void GameObject::UpdateAll(const float deltaTime)
{
    for (auto it = gameObjects->begin(); it != gameObjects->end(); ++it)
    {
        (*it)->Update(deltaTime);
    }
}

void GameObject::RenderAll()
{
    for (auto it = gameObjects->begin(); it != gameObjects->end(); ++it)
    {
        (*it)->image->Render();
    }
}
