#ifndef ASTEROIDS_TEXTUREMANAGER_H
#define ASTEROIDS_TEXTUREMANAGER_H

#include <map>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <nanosvg/nanosvg.h>
#include "Vector.h"

class TextureManager {
public:
    void load(std::string path, std::string id, bool loadAnyway = false);

    void loadVector(std::string path, std::string id, bool loadAnyway = false);

    void draw(std::string id, int x, int y, int w = 0, int h = 0);

    void draw(SDL_Texture *texture, int x, int y, int w = 0, int h = 0);

    void
    drawFrameEx(std::string id, int row, int column, int frameW, int frameH, int x, int y, int w, int h, float angle);

    void drawVectorTexture(std::string id, Vector2 position, float w, float h, float angle);

    void drawVectorTexture(std::string id, Vector2 position, float angle, float w, float h, Vector2 pivot);


    NSVGimage *getVectorTexture(std::string id) { return m_VectorTextureMap[id]; };

    SDL_Texture *getTexture(std::string id) { return m_TextureMap[id]; };

    static TextureManager *getInstance();   // Singleton.
private:
    static TextureManager *s_pInstance;     // Singleton.

    static Vector2 RotatePoint(Vector2 pointToRotate, Vector2 centerPoint, float angle);

    void drawCubicBez(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int strokeWidth,
                      Uint32 color);


    std::map<std::string, SDL_Texture *> m_TextureMap;   // Texturekeeping
    std::map<std::string, NSVGimage *> m_VectorTextureMap;   // Texturekeeping




    void
    drawFrameEx(std::string id, int row, int column, int frameW, int frameH, Vector2 pos, int w, int h, float angle);
};

#endif //ASTEROIDS_TEXTUREMANAGER_H