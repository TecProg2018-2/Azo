/**
* @file sprite.hpp
* @brief Purpose: Contains the components of the sprite.
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* Notice: TheAzo, TheAzoTeam
* https://github.com/TecProg2018-2/Azo
*
* This file implements the main sprite component its declaration and state.
*/
#ifndef SPRITE_HPP
#define SPRITE_HPP

namespace engine {

	class Sprite {

	public:
		Sprite(
			unsigned int spriteWidth, unsigned int spriteHeight,
			unsigned int spriteX, unsigned int spriteY
		);

		void setSpriteWidth(unsigned int newSpriteWidth);
		unsigned int getSpriteWidth();

		void setSpriteHeight(unsigned int newSpriteHeight);
		unsigned int getSpriteHeight();

		void setSpriteX(unsigned int newSpriteX);
		unsigned int getSpriteX();

		void setSpriteY(unsigned int newSpriteY);
		unsigned int getSpriteY();

	private:
		unsigned int spriteWidth;
		unsigned int spriteHeight;
		unsigned int spriteX;
		unsigned int spriteY;

	public:
		Sprite();
		~Sprite();
	};
}

#endif
