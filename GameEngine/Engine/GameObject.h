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
    void Move(SDL_FPoint* direction, float distance, bool clampToScreen = false, bool destroyOffScreen = false);

    void SetRotation(float angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

    SDL_FPoint* GetPosition() { return image->position; }
    SDL_FPoint* GetCenterPosition();
    float GetRotation() { return image->angle; }
    SDL_RendererFlip GetFlip() { return image->flip; }
    void DestroyGameObject();

    virtual void Update(float deltaTime);

    void AddComponent(Component* component);
    
    static GameObject* Instantiate(SDL_FPoint* position = nullptr, SDL_FPoint* size = nullptr,
                                   const char* imagePath = nullptr, float angle = 0);
    static void UpdateAll(float deltaTime);
    static void RenderAll();
    static void DeleteDestroyedGameObjects();
    inline static std::list<GameObject*>* gameObjects = new std::list<GameObject*>();
    inline static std::list<GameObject*>* pendingForDelete = new std::list<GameObject*>();

    std::list<Component*>* components;

    bool destroyTag;

private:
    GameObject(const char* path, SDL_FPoint* position, SDL_FPoint* size, float angle = 0);
};
