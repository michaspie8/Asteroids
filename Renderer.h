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

//Place were texture will be rendered.
// If its corner, the corner of texture will be the position point
// If center, the center will be pos point
enum RenderPosition {

    CENTER,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

//Pivot of rotation:
//if parent pivot is parent's position
//if object pivot is object position
//if combine pivot is object absolute position
//if there is no parent pivot will be object position
enum RenderRotation {
    PARENT,
    OBJECT,
    OBJECT_ABSOLUTE
};

//TODO add animation component and use this to draw animations



class Renderer : public Component {

public:
    Renderer(std::string textureId, RenderType renderType = RenderType::VECTOR,
             std::string name = "Renderer", RenderRotation renderRotation = RenderRotation::PARENT,
             RenderPosition renderPosition = RenderPosition::CENTER) : Component(name) {
        m_TextureID = textureId;
        m_RenderType = renderType;
        m_RenderRotation = renderRotation;
        m_RenderPosition = renderPosition;
    };

    ~Renderer() override = default;

    void draw() override;

    void update() override;

    void clean() override;

    void setTextureId(std::string textureId);

    void setRenderType(RenderType renderType);

    void setRenderRotation(RenderRotation renderRotation);

    void setRenderPosition(RenderPosition renderPosition);

    RenderRotation getRenderRotation();

    RenderPosition getRenderPosition();

    Vector2 getRenderPositionVector();

    Vector2 getRenderRotationVector();

    std::string getTextureId();

    RenderType getRenderType();

protected:
    std::string m_TextureID;
    RenderType m_RenderType;
    RenderPosition m_RenderPosition;
    RenderRotation m_RenderRotation;


};

#endif //ASTEROIDS_RENDERER_H
