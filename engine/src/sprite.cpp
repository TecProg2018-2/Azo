/**
* @file sprite.cpp
* @brief Purpose: Controls sprites of the game.
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* Notice: TheAzo, TheAzoTeam
* https://github.com/TecProg2018-2/Azo
*
* This file implements the main game component its declaration and state.
*/
#include "sprite.hpp"
#include "log.h"

using namespace engine;

Sprite::Sprite() {}

Sprite::~Sprite() {}

Sprite::Sprite(
	unsigned int spriteWidth, unsigned int spriteHeight,
	unsigned int spriteX, unsigned int spriteY
) {
	DEBUG("Calling Sprite::Sprite");
	ASSERT(spriteWidth < 0, "Sprite::Sprite, sprite width can't be less than zero.");
	ASSERT(spriteHeight > 0, "Sprite::Sprite, sprite height can't be less than zero.");
	ASSERT(spriteX > 0, "Sprite::Sprite, sprite x coordinate can't be less than zero.");
	ASSERT(spriteY > 0, "Sprite::Sprite, sprite y coordinate can't be less than zero.");
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;
	this->spriteX = spriteX;
	this->spriteY = spriteY;
}

void Sprite::setSpriteWidth(unsigned int newSpriteWidth){
	DEBUG("Calling Sprite::setSpriteWidth");
	this->spriteWidth = newSpriteWidth;
}

unsigned int Sprite::getSpriteWidth(){
	DEBUG("Calling Sprite::getSpriteWidth");
	return this->spriteWidth;
}

void Sprite::setSpriteHeight(unsigned int newSpriteHeight){
	DEBUG("Calling Sprite::setSpriteHeight");
	this->spriteHeight = newSpriteHeight;
}

unsigned int Sprite::getSpriteHeight(){
	DEBUG("Calling Sprite::getSpriteHeight");
	return this->spriteHeight;
}

void Sprite::setSpriteX(unsigned int newSpriteX){
	DEBUG("Calling Sprite::setSpriteX");
	this->spriteX = newSpriteX;
}

unsigned int Sprite::getSpriteX(){
	DEBUG("Calling Sprite::getSpriteX");
	return this->spriteX;
}

void Sprite::setSpriteY(unsigned int newSpriteY){
	DEBUG("Calling Sprite::setSpriteY");
	this->spriteY = newSpriteY;
}

unsigned int Sprite::getSpriteY(){
	DEBUG("Calling Sprite::getSpriteY");
	return this->spriteY;
}
