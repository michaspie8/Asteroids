#ifndef ASTEROIDS_LOADERPARAMS_H
#define ASTEROIDS_LOADERPARAMS_H

#include "Vector.h"
#include <string>
#include <utility>

// SDLGameObject
class LoaderParams {
public:
    LoaderParams(Vector2 pos, int w, int h, float angle, std::string id, std::string name = "GameObject",
                 std::string tag = "", bool enabled = true, bool marked = false)
            : m_Name(std::move(name)),
              m_Tag(std::move(tag)),
              m_Position(pos),
              m_Width(w),
              m_Height(h),
              m_Angle(angle),
              m_TextureId(std::move(id)),
              m_Enabled(enabled),
              m_MarkedForDeletion(marked) {};

    std::string m_Name;
    std::string m_Tag;
    Vector2 m_Position;
    int m_Width;
    int m_Height;
    float m_Angle;
    bool m_Enabled;
    bool m_MarkedForDeletion;
    std::string m_TextureId;


};

#endif //ASTEROIDS_LOADERPARAMS_H