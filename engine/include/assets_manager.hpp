/**
 * @file assets_manager.hpp
 * @brief Purpose: Contains general scope to the assets_manager.
 *
 * GLP v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#ifndef ASSETS_MANAGER_HPP
#define ASSETS_MANAGER_HPP

#include <iostream>
#include <unordered_map>

#include "sdl2include.h"
#include "log.h"

namespace engine {

	//struct used to map width and height from a image or a sprite.
	struct Image {
		SDL_Texture * texture;
		unsigned int width;
		unsigned int height;
	};

	/*
	 * @brief Class for possible errors types.
	 * 
	 * Enum class used to differentiate errors inside the menu.
	 */ 
	enum class ErrorType {
		DIVI_BY_ZERO,
		NULL_POINTER,
		EMPTY_STRING,
		WRONG_TYPE,
		NO_MATCHING_FILE,
	};

	/**
	 * @brief AssetsManager class.
	 *
	 * This class is responsible for assets the Image map, music map and sound map.
	 *
	*/
	class AssetsManager {
		private:
			std::unordered_map<std::string, Image *> imageMap;     // Map of all images already loaded.
			std::unordered_map<std::string, Mix_Music *> musicMap; // Map of all musics already loaded.
			std::unordered_map<std::string, Mix_Chunk *> soundMap; // Map of all sounds already loaded.
		public:
			AssetsManager();

			Image* LoadImage(std::string imagePath);

			Mix_Music* LoadMusic(std::string audioPath);

			Mix_Chunk * LoadSound(std::string audioPath);

			void errorLog(ErrorType code, std::string file);

		private:
			void InsertIntoImageMap(std::string imagePath, SDL_Surface* image, SDL_Texture *imageTexture);
			void InsertIntoMusicMap(std::string audioPath, Mix_Music * music);
			void InsertIntoSoundMap(std::string audioPath, Mix_Chunk * sound);
	};
}

#endif
