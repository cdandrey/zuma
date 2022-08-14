cmake_minimum_required(VERSION 3.3)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

set(controls_headers
    controls/Engine.h
    controls/GameWorld.h
    controls/GameState.h
)

set(controls_sources
    controls/Engine.cpp
    controls/GameWorld.cpp
    controls/GameState.cpp
)

set(handlers_headers
    scenes/handlers/AbstractHandlerScene.h
    scenes/handlers/HandlerSceneGameplay.h
    scenes/handlers/HandlerSceneMenu.h
    scenes/handlers/HandlerSceneScore.h
)

set(handlers_sources
    scenes/handlers/HandlerSceneGameplay.cpp
    scenes/handlers/HandlerSceneMenu.cpp
    scenes/handlers/HandlerSceneScore.cpp
)

set(components_headers
    scenes/components/Button.h
)

set(components_sources
    scenes/components/Button.cpp
)
 
set(scenes_headers
    scenes/SceneGameplay.h
    scenes/SceneMainMenu.h
    scenes/SceneScore.h
)

set(scenes_sources
    scenes/SceneGameplay.cpp
    scenes/SceneMainMenu.cpp
    scenes/SceneScore.cpp
)

set(objects_headers
    scenes/objects/AbstractObject.h
    scenes/objects/ObjectBall.h
    scenes/objects/ObjectGun.h
)

set(objects_sources
    scenes/objects/AbstractObject.cpp
    scenes/objects/ObjectBall.cpp
    scenes/objects/ObjectGun.cpp
)

set(adapters_headers
    scenes/adapters/AbstractAdapter.h
    scenes/adapters/AdapterMovable.h
    scenes/adapters/AdapterRotable.h
)

set(adapters_sources
    scenes/adapters/AbstractAdapter.cpp
    scenes/adapters/AdapterMovable.cpp
    scenes/adapters/AdapterRotable.cpp
)

set(commands_headers
    scenes/commands/AbstractCommand.h
    scenes/commands/CommandCircleMovable.h
    scenes/commands/CommandMovable.h
    scenes/commands/CommandRotable.h
)

set(commands_sources
    scenes/commands/CommandCircleMovable.cpp
    scenes/commands/CommandMovable.cpp
    scenes/commands/CommandRotable.cpp
)

set(configs_headers
    configs/Config.h
)

set(types_headers
    types/ExceptionError.h
    types/Property.h
    types/Property_internal.h
)

set(types_sources
    types/ExceptionError.cpp
)

set(utils_headers
    utils/Randomizer.h
)

set(utils_sources
    utils/Randomizer.cpp
)

add_library(ZumaLib
    STATIC
    ${adapters_headers}
    ${adapters_sources}
    ${commands_headers}
    ${commands_sources}
    ${scenes_headers}
    ${scenes_sources}
    ${components_headers}
    ${components_sources}
    ${controls_headers}
    ${controls_sources}
    ${objects_headers}
    ${objects_sources}
    ${handlers_headers}
    ${handlers_sources}
    ${types_headers}
    ${types_sources}
    ${configs_headers}
    ${utils_headers}
    ${utils_sources}
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