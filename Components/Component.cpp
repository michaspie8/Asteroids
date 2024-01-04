//
// Created by Michal on 31.12.2023.
//

#include "Component.h"
#include "../GameObject.h"

void Component::clean() {
    getGameObject()->removeComponent(this);
    delete this;
}

