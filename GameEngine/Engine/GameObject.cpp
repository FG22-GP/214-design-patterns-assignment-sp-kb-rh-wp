﻿#include "GameObject.h"

#include <charconv>
#include <cmath>
#include <string>
#include "PlayerInputComponent.h"
#include <typeinfo>
#include "HelperFunctions.h"


GameObject::GameObject(const char* path, SDL_FPoint* position, SDL_FPoint* size, float angle)
{
    image = new Image(path, position, size, angle);
    components = new std::list<Component*>();
}

void GameObject::SetPosition(SDL_FPoint* point)
{
    image->position = point;
}

void GameObject::SetRotation(float angle, SDL_RendererFlip flip)
{
    image->angle = angle;
    image->flip = flip;
}

SDL_FPoint* GameObject::GetCenterPosition()
{
    return new SDL_FPoint{image->position->x + image->size->x / 2, image->position->y + image->size->y / 2 };
}

void GameObject::Move(SDL_FPoint* direction, const float distance, bool clampToScreen)
{
    auto newPosition = new SDL_FPoint{
        image->position->x + direction->x * distance, image->position->y - direction->y * distance
    };

    if (clampToScreen)
    {
        int maxX;
        int maxY;

        SDL_RenderGetLogicalSize(Renderer::GetRenderer(), &maxX, &maxY);

        maxX -= image->size->x;
        maxY -= image->size->y;

        newPosition->x = SDL_clamp(newPosition->x, 0, maxX);
        newPosition->y = SDL_clamp(newPosition->y, 0, maxY);
    }

    SetPosition(newPosition);
}

void GameObject::DestroyGameObject()
{
    destroyTag = true;
}

void GameObject::Update(float deltaTime)
{
    for (auto it = components->begin(); it != components->end(); ++it)
    {
        (*it)->Update(deltaTime);
    }
}

void GameObject::AddComponent(Component* component)
{
    component->parent = this;
    components->push_back(component);
}

GameObject* GameObject::Instantiate(SDL_FPoint* position, SDL_FPoint* size, const char* imagePath, float angle)
{
    const auto go = new GameObject(imagePath, position, size, angle);
    gameObjects->push_back(go);
    return go;
}

void GameObject::UpdateAll(const float deltaTime)
{
    for (auto it = gameObjects->begin(); it != gameObjects->end(); ++it)
    {
        if ((*it)->destroyTag) continue;
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

void GameObject::DeleteDestroyedGameObjects()
{    
    std::list<GameObject*>::iterator it = gameObjects->begin();

    while (it != gameObjects->end())
    {
        if ((*it)->destroyTag)
        {
            pendingForDelete->push_back(*it);
            it = gameObjects->erase(it);
        }
        else
        {
            ++it;
        }
    }

    while (!pendingForDelete->empty()) {
        delete pendingForDelete->front();
        pendingForDelete->pop_front();
    }
}