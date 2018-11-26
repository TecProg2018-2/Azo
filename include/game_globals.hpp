/**
 * @file game_globals.hpp
 * @brief Purpose: Set the game globals constants.
 * 
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 * 
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 * 
 * This file implements the game globals constants.
*/
#ifndef GAME_GLOBALS_HPP
#define GAME_GLOBALS_HPP

#include <string>

namespace global {
	const std::string GAME_NAME = "Azo";
	const int WINDOWN_WIDTH = 800;   // Pixels.
	const int WINDOWN_HEIGHT = 494;  // Pixels
	const int FRAME_RATE = 60;      // Frames per Second (FPS)
	const std::string PLAYER_SCENE = "playerScene";
}

#endif
