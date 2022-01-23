#pragma once
#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include <utility>
#include "raylib.h"
#include "raymath.h"
#include <fstream>
#include <iterator>
#include <cassert>
constexpr auto fileName = "SAVE.txt";// This globally declares the filename
constexpr auto screenWidth = 1920;// This globally declares screenwidth
constexpr auto screenHeight = 1050; // This globallydeclares the screenheight

inline int encrypt_data(int data)noexcept { return ~data; }


#endif
