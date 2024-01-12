//
// Created by Michal on 09.01.2024.
//

#ifndef ASTEROIDS_UIMANAGER_H
#define ASTEROIDS_UIMANAGER_H

#include <string>

class UIManager {

public:
    UIManager() = default;

    ~UIManager() = default;

    void draw();

    void clean();



protected:
    std::string *m_ScoreText;


};


#endif //ASTEROIDS_UIMANAGER_H
