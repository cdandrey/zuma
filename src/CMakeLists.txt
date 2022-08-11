cmake_minimum_required(VERSION 3.2)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

set(scenes_headers
    scenes/AbstractHandlerScene.h
    scenes/HandlerSceneGameplay.h
    scenes/HandlerSceneMenu.h
    scenes/HandlerSceneScore.h
    scenes/Scene.h
)

set(scenes_sources
    scenes/HandlerSceneGameplay.cpp
    scenes/HandlerSceneMenu.cpp
    scenes/HandlerSceneScore.cpp
    scenes/Scene.cpp
)

set(components_headers
    components/Button.h
    components/Gameplay.h
    components/Gun.h
    components/MainMenu.h
)

set(components_sources
    components/Button.cpp
    components/Gameplay.cpp
    components/Gun.cpp
    components/MainMenu.cpp
)

set(objects_headers
    components/objects/AbstractObject.h
)

set(objects_sources
    components/objects/AbstractObject.cpp
)

set(types_headers
    types/ExceptionError.h
    types/Property.h
    types/Property_internal.h
)

set(types_sources
    types/ExceptionError.cpp
)

add_library(ZumaLib
    STATIC
    Engine.h
    Engine.cpp
    GameState.h
    GameState.cpp
    ${components_headers}
    ${components_sources}
    ${objects_headers}
    ${objects_sources}
    ${scenes_headers}
    ${scenes_sources}
    ${types_headers}
    ${types_sources}
)

target_link_libraries(ZumaLib
    sfml-graphics
    sfml-system
    sfml-window
)

target_compile_definitions(ZumaLib
    PUBLIC
    UNICODE
    _UNICODE
)