#pragma once
#include "Image.h"
#include <list>

class GameObject
{
public:
    virtual ~GameObject() = default;

    Image* image;
    void SetPosition(SDL_Point* point);
    void Move(SDL_Point* direction, int distance);
    SDL_Point* GetPosition() { return image->position; }
    virtual void Update(float deltaTime);

    static GameObject* Instantiate(SDL_Point* position = nullptr, SDL_Point* size = nullptr,
                                   const char* imagePath = nullptr);
    static void UpdateAll(float deltaTime);
    static void RenderAll();
    inline static std::list<GameObject*>* gameObjects = new std::list<GameObject*>();

protected:
    std::list<bool> components;

private:
    GameObject(const char* path, SDL_Point* position, SDL_Point* size);
};
