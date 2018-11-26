/**
 * @file assets_manager.cpp
 * @brief Purpose: Contains general scope to the assets_manager.
 *
 * GLP v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#include "assets_manager.hpp"
#include "game.hpp"

using namespace engine;// Used to avoid write engine::Game engine::Game::instance;.

/**
* @brief Default constructor for the assets manager.
*
* @return "void".
*/
	AssetsManager::AssetsManager() {}


	// Load image into image map.
	Image* AssetsManager::LoadImage(std::string imagePath) {
		ASSERT(imagePath != "", "Animation::CreateAnimation, imagePath is empty.");
		//DEBUG("Image Map size before loading " << imageMap.size());

		if (imageMap.find(imagePath) == imageMap.end()) {
			INFO("Loading a new image asset.");

			SDL_Surface *image = NULL;

			if (imagePath != "") {
				//Nothing to do for the imagePath is valid
			} else {
				ERROR("Invalid Image Path: " << imagePath);
			}

			image = IMG_Load(imagePath.c_str());

			if (image != NULL) {
				//Nothing to do for the image was loaded
			} else {
				ERROR("Couldn't load sprite.");
			}

			SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(Game::instance.sdlElements.getCanvas(), image);

			if (imageTexture != NULL) {
				//Nothing to do for the imageTexture was created
			} else {
				ERROR("Couldn't create texture from image: " << SDL_GetError());
			}

			InsertIntoImageMap(imagePath, image, imageTexture);

			SDL_FreeSurface(image);

		} else {
		}

		return imageMap[imagePath];
	}

	/**
	 * @brief create a new Struct Image variable, which whom we will add to the map.
	 *
	 *  Insert images on the map.
	 *
	 * @param imagePath string that says the path of the map.
	 *
	 * @return "void".
	*/
	void AssetsManager::InsertIntoImageMap(std::string imagePath, SDL_Surface* image, SDL_Texture *imageTexture) {
		ASSERT(imagePath != "", "Image path can't be empty.");
		ASSERT(imageTexture != NULL, "Image texture can't be empty.");
		ASSERT(image != NULL, "SDL_Suface pointer can't be null.");

		Image *assetsManagerImage = new Image;

		assetsManagerImage->texture = imageTexture;
		assetsManagerImage->width = image->w;
		assetsManagerImage->height = image->h;

		// Insert image into image map.
		imageMap[imagePath] = assetsManagerImage;
	}

	// Load music into music map.
	Mix_Music* AssetsManager::LoadMusic(std::string audioPath) {
		DEBUG("Trying to load music " << audioPath);
		DEBUG("Music Map size before loading " << musicMap.size());

		if (musicMap.find(audioPath) == musicMap.end()) {
		 	INFO("Loading a new music asset.");

			Mix_Music * music = Mix_LoadMUS(audioPath.c_str());

			if(music != NULL) {
				//Nothing to do for the audioPath is correct
			} else {
				ERROR("Could not load music from path " << audioPath);
			}

			InsertIntoMusicMap(audioPath, music);

		} else {
		}

		return musicMap[audioPath];
	}

	/**
	 * @brief insert music on the map.
	 *
	 * @param string audioPath that is responsible for the music on map.
	 * @param string Mix_Music variable to store music playing in the game.
	 * @param string music responsible for the music in the game.
	 *
	 * @return "void".
	*/
	void AssetsManager::InsertIntoMusicMap(std::string audioPath, Mix_Music * music) {
		ASSERT(audioPath != "", "Music path can't be empty.");
		ASSERT(music != NULL, "Mix_Music pointer can't be null.");

		// Insert music into image map.
		musicMap[audioPath] = music;
		DEBUG("Music Map size after inserting " << musicMap.size());
	}


	// Load sound into sound map.
	Mix_Chunk* AssetsManager::LoadSound(std::string audioPath) {
		DEBUG("Trying to load Sound " << audioPath);
		DEBUG("Sound Map size before loading " << soundMap.size());

		if (soundMap.find(audioPath) == soundMap.end()) {
			INFO("Loading a new sound asset.");

			Mix_Chunk * sound = Mix_LoadWAV(audioPath.c_str());

			if (sound != NULL) {
				//Nothing to do for the audioPath is not null
			} else {
				ERROR("Could not load sound from path " << audioPath);
			}

			InsertIntoSoundMap(audioPath, sound);

		} else {
		}

		return soundMap[audioPath];
	}

	/**
	 * @brief insert sound on the map.
	 *
	 * @param string audioPath that say the audio path.
	 * @param string Mix_Chunk variable to store the sound effects.
	 * @param string sound.
	 *
	 *@return "void".
	*/
	void AssetsManager::InsertIntoSoundMap(std::string audioPath, Mix_Chunk * sound) {
		ASSERT(audioPath != "", "Sound path can't be empty.");
		ASSERT(sound != NULL, "Mix_Chunk pointer can't be null.");

		// Insert sound into image map.
		soundMap[audioPath] = sound;
		DEBUG("Sound Map size after inserting " << soundMap.size());
	}
