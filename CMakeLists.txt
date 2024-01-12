cmake_minimum_required(VERSION 3.27)
project(Asteroids)

set(CMAKE_CXX_STANDARD 17)

add_executable(Asteroids
        ./Colors.h
        ./Components/Asteroid.h
        ./Components/Bullet.h
        ./Components/Collider.h
        ./Components/Component.h
        ./Components/Motion.h
        ./Components/Renderer.h
        ./Components/Shooter.h
        ./Components/Transform.h
        ./EventHandler.h
        ./Game.h
        ./GameObject.h
        ./LoaderParams.h
        ./Mathf.h
        ./Player.h
        ./SceneManager.h
        ./TextureManager.h
        ./Vector.h
        ./Components/Asteroid.cpp
        ./Components/Bullet.cpp
        ./Components/Collider.cpp
        ./Components/Component.cpp
        ./Components/Motion.cpp
        ./Components/Renderer.cpp
        ./Components/Shooter.cpp
        ./Components/Transform.cpp
        ./EventHandler.cpp
        ./Game.cpp
        ./GameObject.cpp
        ./main.cpp
        ./Mathf.cpp
        ./Player.cpp
        ./SceneManager.cpp
        ./TextureManager.cpp
        ./Vector.cpp
)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

set(NanoSVG_DIR "C:/Users/Bartek/.vcpkg-clion/vcpkg/installed/x64-windows/share/NanoSVG")
set(SDL2_DIR "C:/Users/Bartek/.vcpkg-clion/vcpkg/installed/x64-windows/share/sdl2")
set(SDL2_image_DIR "C:/Users/Bartek/.vcpkg-clion/vcpkg/installed/x64-windows/share/SDL2_image")

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
