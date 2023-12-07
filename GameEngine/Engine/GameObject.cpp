#include "GameObject.h"

#include <charconv>
#include <cmath>
#include <string>

GameObject::GameObject(const char* path, SDL_Point* position, SDL_Point* size)
{
    image = new Image(path, position, size);
}

void GameObject::SetPosition(SDL_Point* point)
{
    image->position = point;
}

void GameObject::Move(SDL_Point* direction, int distance)
{
    auto newPosition = new SDL_Point{
        image->position->x + direction->x * distance, image->position->y - direction->y * distance
    };
    SetPosition(newPosition);
}

void GameObject::Update(float deltaTime)
{
    for (auto component : components)
    {
        if (component)
        {
            // Update component
        }
    }
}

GameObject* GameObject::Instantiate(SDL_Point* position, SDL_Point* size, const char* imagePath)
{
    auto go = new GameObject(imagePath, position, size);
    gameObjects->push_back(go);
    return go;
}

void GameObject::UpdateAll(float deltaTime)
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
