#ifndef ASTEROIDS_EVENTHANDLER_H
#define ASTEROIDS_EVENTHANDLER_H

#include <SDL.h>
#include "Vector.h"

class EventHandler {
public:

    void update();

    // Getters
    [[nodiscard]] Vector2 getJoystickAxes() const { return m_JoystickAxes; };

    [[nodiscard]] bool isMouseButtonDown(int button) { return m_MouseButtonState[button]; };

    [[nodiscard]] bool isKeyboardKeyDown(SDL_Scancode key) { return m_KeyboardState[key]; };

    static EventHandler *getInstance();


private:

    const Uint8 *m_KeyboardState;
    bool m_MouseButtonState[3];
    const Vector2 m_JoystickAxes = Vector2(0, 0);
    static EventHandler *s_pInstance;

    EventHandler();
};

enum MouseButton {
    LEFT = 0,
    RIGHT = 1,
    MIDDLE = 2
};

#endif //ASTEROIDS_EVENTHANDLER_H
