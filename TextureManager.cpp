#include "Game.h"
#include "TextureManager.h"
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_render.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2_gfxPrimitives_font.h>
#include <cmath>

#include <string>
#include "Vector.h"
#include "Mathf.h"

#define NANOSVG_IMPLEMENTATION
#define NANOSVG_ALL_COLOR_KEYWORDS

#include <nanosvg/nanosvg.h>

// static
TextureManager *TextureManager::s_pInstance = nullptr;

// static
TextureManager *TextureManager::getInstance() {
    if (!s_pInstance)
        s_pInstance = new TextureManager;
    return s_pInstance;
}

void TextureManager::load(std::string path, std::string id, bool loadAnyway) {
    if (m_TextureMap[id] != nullptr && !loadAnyway) return;
    SDL_RWops *rw = SDL_RWFromFile(path.c_str(), "r");
    SDL_Surface *surface = IMG_LoadSVG_RW(rw);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::getInstance()->getRenderer(), surface);
    SDL_FreeSurface(surface);
    //SDL_RWclose(rw);

    m_TextureMap[id] = texture;
}

void TextureManager::loadVector(std::string path, std::string id, bool loadAnyway) {
    if (m_VectorTextureMap[id] != nullptr && !loadAnyway) return;
    NSVGimage *image = nsvgParseFromFile(path.c_str(), "px", 96);
    image->width = 64;
    image->height = 64;

    m_VectorTextureMap[id] = image;
}

void TextureManager::draw(std::string id, int x, int y, int w, int h) {
    SDL_Rect srcRect, destRect;

    srcRect.x = srcRect.y = 0;
    SDL_QueryTexture(m_TextureMap[id], NULL, NULL, &srcRect.w, &srcRect.h);

    destRect.x = x;
    destRect.y = y;
    if (w) destRect.w = w;
    else destRect.w = srcRect.w;

    if (h) destRect.h = h;
    else destRect.h = srcRect.h;

    SDL_RenderCopy(Game::getInstance()->getRenderer(), m_TextureMap[id], &srcRect, &destRect);
}

void
TextureManager::drawFrameEx(std::string id, int row, int column, int frameW, int frameH, int x, int y, int w, int h,
                            float angle) {
    SDL_Rect srcRect, destRect;

    srcRect.x = row * frameW;
    srcRect.y = column * frameH;

    srcRect.w = frameW;
    srcRect.h = frameH;

    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;


//    SDL_RenderCopy(Game::getInstance()->getRenderer(), m_TextureMap[id], &srcRect, &destRect);
    SDL_RenderCopyEx(Game::getInstance()->getRenderer(), m_TextureMap[id], &srcRect, &destRect, angle, 0,
                     SDL_FLIP_NONE);
}

void TextureManager::drawFrameEx(std::string id, int row, int column, int frameW, int frameH, Vector2 pos, int w,
                                 int h, float angle) {
    drawFrameEx(id, row, column, frameW, frameH, pos.x, pos.y, w, h, angle);
}


void TextureManager::draw(SDL_Texture *texture, int x, int y, int w, int h) {
    SDL_Rect srcRect, destRect;

    srcRect.x = srcRect.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);

    destRect.x = x;
    destRect.y = y;
    if (w) destRect.w = w;
    else destRect.w = srcRect.w;

    if (h) destRect.h = h;
    else destRect.h = srcRect.h;

    SDL_RenderCopy(Game::getInstance()->getRenderer(), texture, &srcRect, &destRect);
}

Vector2 TextureManager::RotatePoint(Vector2 pointToRotate, Vector2 centerPoint, float angle) {
    float x = pointToRotate.x - centerPoint.x;
    float y = pointToRotate.y - centerPoint.y;
    float rotatedX = x * cos(angle * M_PI / 180) - y * sin(angle * M_PI / 180);
    float rotatedY = x * sin(angle * M_PI / 180) + y * cos(angle * M_PI / 180);
    return Vector2(rotatedX + centerPoint.x, rotatedY + centerPoint.y);
}


void TextureManager::drawVectorTexture(std::string id, Vector2 position, float w, float h, float angle) {
    //get texture
    NSVGimage *image = m_VectorTextureMap[id];

    for (NSVGshape *shape = image->shapes; shape != nullptr; shape = shape->next) {

        for (NSVGpath *path = shape->paths; path != nullptr; path = path->next) {
            for (int i = 0; i < path->npts - 1; i += 3) {
                float *p = &path->pts[i * 2];
                // make copies of points
                float *d = new float[8];
                for (int j = 0; j < 8; j++) {
                    d[j] = p[j];
                }
                //Apply scale to points
                for (int j = 0; j < 8; j += 2) {
                    d[j] *= w / image->width;
                    d[j + 1] *= h / image->height;
                }
                //Apply position to points
                for (int j = 0; j < 8; j += 2) {
                    d[j] += position.x - w / 2;
                    d[j + 1] += position.y - h / 2;
                }

                //Apply rotation to points
                for (int j = 0; j < 8; j += 2) {
                    Vector2 point = RotatePoint(Vector2(d[j], d[j + 1]), Vector2(position.x, position.y), angle);
                    d[j] = point.x;
                    d[j + 1] = point.y;
                }

                drawCubicBez(d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7], shape->strokeWidth, shape->stroke.color);
            }
        }
    }
    // Delete
    //nsvgDelete(image);

}

//Same as above bot with pivot point, and position needs to be calculeted pls edit the other one, after testing that one, update this
void TextureManager::drawVectorTexture(std::string id, Vector2 position, float angle, float w, float h, Vector2 pivot) {
    //get texture
    NSVGimage *image = m_VectorTextureMap[id];

    for (NSVGshape *shape = image->shapes; shape != nullptr; shape = shape->next) {

        for (NSVGpath *path = shape->paths; path != nullptr; path = path->next) {
            for (int i = 0; i < path->npts - 1; i += 3) {
                float *p = &path->pts[i * 2];
                // make copies of points
                float *d = new float[8];
                for (int j = 0; j < 8; j++) {
                    d[j] = p[j];
                }
                //Apply scale to points
                for (int j = 0; j < 8; j += 2) {
                    d[j] *= w / image->width;
                    d[j + 1] *= h / image->height;
                }
                //Apply position to points
                for (int j = 0; j < 8; j += 2) {
                    d[j] += position.x;
                    d[j + 1] += position.y;
                }
                //Apply rotation to points
                for (int j = 0; j < 8; j += 2) {
                    Vector2 point = RotatePoint(Vector2(d[j], d[j + 1]), pivot, angle);
                    d[j] = point.x;
                    d[j + 1] = point.y;
                }

                drawCubicBez(d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7],
                             shape->strokeWidth * (w + h / 2) / (image->width + image->height) / 2,
                             shape->stroke.color);
            }
        }
    }
    // Delete
    //nsvgDelete(image);

}


void TextureManager::drawCubicBez(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,
                                  int strokeWidth, Uint32 color) {

    //draw bezier curve
    float t = 0;
    float step = 0.01f;
    Vector2 lastPoint = Vector2(x1, y1);
    while (t < 1) {
        Vector2 point = Vector2(
                Mathf::bezier(x1, x2, x3, x4, t),
                Mathf::bezier(y1, y2, y3, y4, t)
        );
        thickLineColor(Game::getInstance()->getRenderer(), (Sint16) lastPoint.x, (Sint16) lastPoint.y, (Sint16) point.x,
                       (Sint16) point.y, (Uint8) strokeWidth, color);
        lastPoint = point;
        t += step;
    }

}