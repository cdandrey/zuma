cmake_minimum_required(VERSION 3.3)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

set(engine_headers
    engine/Engine.h
    engine/GameState.h
)

set(engine_sources
    engine/Engine.cpp
    engine/GameState.cpp
)

set(scenes_headers
    engine/scenes/AbstractHandlerScene.h
    engine/scenes/HandlerSceneGameplay.h
    engine/scenes/HandlerSceneMenu.h
    engine/scenes/HandlerSceneScore.h
    engine/scenes/Scene.h
)

set(scenes_sources
    engine/scenes/HandlerSceneGameplay.cpp
    engine/scenes/HandlerSceneMenu.cpp
    engine/scenes/HandlerSceneScore.cpp
    engine/scenes/Scene.cpp
)

set(components_headers
    components/Button.h
    components/Gameplay.h
    components/MainMenu.h
    components/Score.h
)

set(components_sources
    components/Button.cpp
    components/Gameplay.cpp
    components/MainMenu.cpp
    components/Score.cpp
)

set(objects_headers
    components/objects/AbstractObject.h
    components/objects/ObjectBall.h
    components/objects/ObjectGun.h
)

set(objects_sources
    components/objects/AbstractObject.cpp
    components/objects/ObjectBall.cpp
    components/objects/ObjectGun.cpp
)

set(adapters_headers
    components/adapters/AbstractAdapter.h
    components/adapters/AdapterRotable.h
)

set(adapters_sources
    components/adapters/AbstractAdapter.cpp
    components/adapters/AdapterRotable.cpp
)

set(commands_headers
    components/commands/AbstractCommand.h
    components/commands/CommandRotable.h
)

set(commands_sources
    components/commands/CommandRotable.cpp
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
    ${adapters_headers}
    ${adapters_sources}
    ${commands_headers}
    ${commands_sources}
    ${components_headers}
    ${components_sources}
    ${engine_headers}
    ${engine_sources}
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