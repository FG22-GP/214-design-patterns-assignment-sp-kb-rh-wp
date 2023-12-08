#include "UiObject.h"

void UiObject::RenderAll()
{
    for (auto it = uiObjects->begin(); it != uiObjects->end(); ++it)
    {
        (*it)->Render();
    }
}
