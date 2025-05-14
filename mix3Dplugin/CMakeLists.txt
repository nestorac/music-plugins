cmake_minimum_required(VERSION 3.15)

project(Mix3DPlugin VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "/opt/juce")
find_package(JUCE CONFIG REQUIRED)

# Buscar GTK explícitamente
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(WEBKIT2GTK REQUIRED webkit2gtk-4.1)

# Ensure the WebKit include dirs are visible to all targets
include_directories(${WEBKIT2GTK_INCLUDE_DIRS})


juce_add_plugin(Mix3DPlugin
    COMPANY_NAME "YourCompany"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    VST3_CATEGORY "Fx"
    FORMATS VST3
    PRODUCT_NAME "Mix3DPlugin"
)

# ATENCIÓN: Solo tus fuentes aquí
target_sources(Mix3DPlugin PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

# Enlazar con JUCE y GTK
target_link_libraries(Mix3DPlugin PRIVATE
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_gui_extra
    ${GTK3_LIBRARIES}
)

target_include_directories(Mix3DPlugin PRIVATE
    ${GTK3_INCLUDE_DIRS}
)
