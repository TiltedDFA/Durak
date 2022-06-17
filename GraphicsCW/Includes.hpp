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
constexpr auto screenHeight = 1050; // This globally declares the screenheight
extern inline int encrypt_data(int data)noexcept{ return ~data; } // This is the function used to encrypt all the data stored during runtime so that 3rd party applications are unable to tamper with the program as it runs

#endif
