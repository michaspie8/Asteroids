cmake_minimum_required(VERSION 3.27)
project(Asteroids)

set(CMAKE_CXX_STANDARD 17)

add_executable(Asteroids main.cpp
        GameObject.cpp
        GameObject.h
        Colors.h
        Component.cpp
        Component.h
        EventHandler.cpp
        EventHandler.h
        Game.cpp
        Game.h
        LoaderParams.h
        Mathf.cpp
        Mathf.h
        Motion.cpp
        Motion.h
        Player.cpp
        Player.h
        Renderer.cpp
        Renderer.h
        TextureManager.cpp
        TextureManager.h
        Transform.cpp
        Transform.h
        Vector.cpp
        Vector.h
        Asteroid.h
        Asteroid.cpp
        Shooter.cpp
        Shooter.h
        Bullet.cpp
        Bullet.h
        Collider.cpp
        Collider.h
)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(NanoSVG CONFIG REQUIRED)
target_link_libraries(Asteroids PRIVATE NanoSVG::nanosvg NanoSVG::nanosvgrast)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(Asteroids
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

find_package(SDL2_image CONFIG REQUIRED)
target_link_libraries(Asteroids PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

find_package(sdl2-gfx CONFIG REQUIRED)
target_link_libraries(Asteroids PRIVATE SDL2::SDL2_gfx)

#[[
find_package(OpenGL REQUIRED)
target_link_libraries(Asteroids PRIVATE OpenGL::GL)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Asteroids PRIVATE glfw)]]
