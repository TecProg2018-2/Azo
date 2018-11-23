/**
  * @file timer.cpp
  * @brief Purpose: Contains all the methods related to the Timer class.
  *
  * GPL v3.0 License
  * Copyright (c) 2017 Azo
  *
  * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
 */
#include "timer.hpp"
#include <ctime>
#include <fstream>
#include <iostream>
#include "log.h"

using namespace engine;

/*
 *@brief Constructor for the timer.
 *
 *Resets elapsed time to zero
 */
Timer::Timer() {
  DEBUG("Creating Timer");
	Reset();
}

Timer::~Timer() {}


/*
 *@brief Method to do a timer step
 *
 *updated the total elapsed time with present time
 */
void Timer::step() {
	elapsedTicks = SDL_GetTicks();
}


/*
 *@brief Method to reset the timer
 *
 * Reset startTicks and sets all other attributes to zero
 */
void Timer::Reset() {
  DEBUG("Resetting Timer");
	startTicks = SDL_GetTicks();
	elapsedTicks = 0.0f;
	deltaTime = 0.0f;
}

/*
 *@brief Method to calculate elapsed time since last step
 *
 * Calculates difference from present tick to total elapsed ticks
 */
void Timer::DeltaTime() {  
	deltaTime = SDL_GetTicks() - elapsedTicks;
}

/*
 *@brief Method to get elapsed time since last step
 *
 *@return the elapsed time
 */
float Timer::getDeltaTime() {
  DEBUG("Getting DeltaTime"); // Logging done here so it doesn't affect the timer.
	return deltaTime;
}
