#pragma once
#include <list>

class UiObject
{
public:
    virtual ~UiObject() = default;
    virtual void Render() = 0;

    static void RenderAll();

protected:
    inline static std::list<UiObject*>* uiObjects = new std::list<UiObject*>();
};
