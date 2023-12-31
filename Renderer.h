//
// Created by Michal on 30.12.2023.
//

#ifndef ASTEROIDS_RENDERER_H
#define ASTEROIDS_RENDERER_H

#include "Component.h"
#include "TextureManager.h"

//Fr sprite can be vector too,
//but the vector image is converted to sprite on load
//and a vector renderer draws all vector images,
//not just imports it to sprite
enum class RenderType {
    SPRITE,
    VECTOR
};

//TODO add animation component and use this to draw animations



class Renderer : public Component {

public:
    Renderer(std::string textureId, RenderType renderType = RenderType::VECTOR,
             std::string name = "Renderer") : Component(name) {
        m_TextureID = textureId;
        m_RenderType = renderType;
    };

    ~Renderer() override = default;

    void draw() override;

    void update() override;

    void clean() override;

    void setTextureId(std::string textureId);

    void setRenderType(RenderType renderType);

    std::string getTextureId();

    RenderType getRenderType();

protected:
    std::string m_TextureID;
    RenderType m_RenderType = RenderType::VECTOR;


};

#endif //ASTEROIDS_RENDERER_H
