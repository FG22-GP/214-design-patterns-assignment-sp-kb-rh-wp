#pragma once
#include "Image.h"
#include <list>
#include "Component.h"



class GameObject
{
public:
    virtual ~GameObject() = default;

    Image* image;
    void SetPosition(SDL_FPoint* point);
    void Move(SDL_FPoint* direction, float distance);
    SDL_FPoint* GetPosition() { return image->position; }
    virtual void Update(float deltaTime);
    void AddComponent(Component* component);
    
    static GameObject* Instantiate(SDL_FPoint* position = nullptr, SDL_FPoint* size = nullptr,
                                   const char* imagePath = nullptr);
    static void UpdateAll(float deltaTime);
    static void RenderAll();
    inline static std::list<GameObject*>* gameObjects = new std::list<GameObject*>();
    

protected:
    std::list<Component*>* components;

private:
    GameObject(const char* path, SDL_FPoint* position, SDL_FPoint* size);
};
