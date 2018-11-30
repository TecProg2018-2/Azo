/**
 * @file assets_manager.cpp
 * @brief Purpose: Contains general scope to the assets_manager.
 *
 * GLP v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#include <fstream>
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


			if (imagePath == "") {		
				errorLog(ErrorType::EMPTY_STRING, "AssetsManager::LoadImage");		
				ERROR("Invalid Image Path: " << imagePath);
			} else {
				//Nothing to do for the imagePath is valid
			}
			
			image = IMG_Load(imagePath.c_str());

			if (image == NULL) {
				errorLog(ErrorType::NULL_POINTER, "AssetsManager::LoadImage");
				ERROR("Couldn't load sprite.");
			} else {
				//Nothing to do for the image was loaded
			}

			SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(Game::instance.sdlElements.getCanvas(), image);

			if (imageTexture != NULL) {
				//Nothing to do for the imageTexture was created
			} else {
				errorLog(ErrorType::NULL_POINTER, "AssetsManager::LoadImage");
				ERROR("Couldn't create texture from image: " << SDL_GetError());
			}

			InsertIntoImageMap(imagePath, image, imageTexture);

			SDL_FreeSurface(image);

		} else {
			DEBUG("Image: " << imagePath << " already loaded!");
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

			if(music == NULL) {
				errorLog(ErrorType::NULL_POINTER, "AssetsManager::LoadMusic");
				ERROR("Could not load music from path " << audioPath);
			} else {
				//Nothing to do for the audioPath is correct
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

			if (sound == NULL) {
				ERROR("Could not load sound from path " << audioPath);
				errorLog(ErrorType::NULL_POINTER, "AssetsManager::LoadSound");
			} else {
				//Nothing to do for the audioPath is not null
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

	/*
	*@brief Method to log error messages.
	*
	* Writes a file with error message, function containing error and time.
	*/
	void AssetsManager::errorLog(ErrorType code, std::string file){
		std::ofstream outfile;
		outfile.open("../errorLog.txt", std::ofstream::out | std::ofstream::app);
		time_t now = time(0);
		std::string dt = ctime(&now); //convert to string
		outfile << "Function: " + file << std::endl;
		outfile << "Date: " + dt << std::endl;
		
		switch(code) {
			case ErrorType::DIVI_BY_ZERO:
				outfile << "Error: division by zero" << std::endl;
				break;
			case ErrorType::EMPTY_STRING:
				outfile << "Error: empty String" << std::endl;
				break;
			case ErrorType::NULL_POINTER:
				outfile << "Error: null pointer" << std::endl;
				break;
			case ErrorType::WRONG_TYPE:
				outfile << "Error: wrong type" << std::endl;
				break;
			default:
				outfile << "Error: no matching file" << std::endl;
		}
		outfile << "===============" << std::endl;
		outfile.close();
	}