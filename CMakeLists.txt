cmake_minimum_required(VERSION 3.28)
project(lab_9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Укажите правильный путь к вашей установке Qt
set(QT_INSTALL_PATH "C:/Users/aleks/Downloads/Qt6.2.8-Windows-x86_64-MinGW11.2.0-20240609/Qt6.2.8-Windows-x86_64-MinGW11.2.0")
set(CMAKE_PREFIX_PATH "${QT_INSTALL_PATH}/lib/cmake")

find_package(Qt6 COMPONENTS Widgets Core Sql REQUIRED)

add_executable(lab_9
        main.cpp
        lab_9.cpp
        lab_9.h
        Shapes.cpp
        Shapes.h
        Head.h
)

target_link_libraries(lab_9
        Qt6::Widgets
        Qt6::Core
        Qt6::Sql
)

# Копирование необходимых DLL для Windows
if(WIN32)
    # Копирование platform plugin
    add_custom_command(TARGET lab_9 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:lab_9>/platforms"
    )

    add_custom_command(TARGET lab_9 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll"
            "$<TARGET_FILE_DIR:lab_9>/platforms/"
    )

    # Копирование основных Qt6 DLL
    set(QT6_DLLS
            Core
            Gui
            Widgets
            Sql
    )

    foreach(QT_LIB IN LISTS QT6_DLLS)
        add_custom_command(TARGET lab_9 POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}.dll"
                "$<TARGET_FILE_DIR:lab_9>"
        )
    endforeach()

    # Копирование дополнительных зависимостей
    add_custom_command(TARGET lab_9 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/bin/Qt6Core.dll"
            "$<TARGET_FILE_DIR:lab_9>"
    )

    # Копирование ICU библиотек, если используются
    file(GLOB ICU_DLLS "${QT_INSTALL_PATH}/bin/icu*.dll")
    foreach(ICU_DLL IN LISTS ICU_DLLS)
        add_custom_command(TARGET lab_9 POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${ICU_DLL}"
                "$<TARGET_FILE_DIR:lab_9>"
        )
    endforeach()
endif()