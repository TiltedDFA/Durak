#ifndef TEXTURES_HPP
#define TEXTURES_HPP
#include "raylib.h"



Rectangle playButton = { 773, 509, 287, 105 };

Rectangle settingsButton = { 773, 754, 287, 105 };

Vector2 mP = { 0.0f,0.0f }; //This is to store the mouse position

inline std::array<std::pair<bool, std::string>, 4> screens;


#endif
