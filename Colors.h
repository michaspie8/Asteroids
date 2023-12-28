//
// Created by Michal on 28.12.2023.
//

#ifndef ASTEROIDS_COLORS_H
#define ASTEROIDS_COLORS_H
//note: all of these colors don't have alpha channel
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define ASTEROID_BLACK 0x0F0C0C
#define ASTEROID_GREY 0xE8EDEA
#define ASTEROID_DARK_GREY 0x747AAA
#define ASTEROID_GREEN 0x2EFF62
#define ASTEROID_RED 0xFF2E3A
#define ASTEROID_BLUE 0x2E47FF
#define ASTEROID_BLUE2 0x586BFF
#define ASTEROID_YELLOW FFD02E

static SDL_Color colorFromHEX(uint32_t hex) {
    SDL_Color color;
    color.r = (hex >> 16) & 0xFF;
    color.g = (hex >> 8) & 0xFF;
    color.b = hex & 0xFF;
    color.a = 0xFF;
    return color;
}


#endif //ASTEROIDS_COLORS_H
