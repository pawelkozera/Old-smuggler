#ifndef RESOURCES_H
#define RESOURCES_H

#include "interactiveobject.h"


class Resources : public InteractiveObject
{
public:
    Resources(QString img_name);

    void show_text();
};

#endif // RESOURCES_H
