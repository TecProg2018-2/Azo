#include "assets_manager.hpp"
#include "game.hpp"

using namespace engine;

AssetsManager::AssetsManager(){}


// Load image into image map if we couldn't find it isn't loaded yet.
// If it's already loaded, return it.
Image* AssetsManager::LoadImage(std::string imagePath){
	DEBUG("Trying to load image " << imagePath);
	//DEBUG("Image Map size before loading " << image_map.size());

	if(image_map.find(imagePath) == image_map.end()){
		INFO("Loading a new image asset.");

		SDL_Surface *image = NULL;

		if(imagePath == ""){
			ERROR("Invalid Image Path: " << imagePath);
		}

		image = IMG_Load(imagePath.c_str());

		if(image == NULL){
			ERROR("Couldn't load sprite.");
		}

		SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(Game::instance.sdl_elements.GetCanvas(), image);

		if(imageTexture == NULL){
			ERROR("Couldn't create texture from image: " << SDL_GetError());
		}

		InsertIntoImageMap(imagePath, image, imageTexture);

		SDL_FreeSurface(image);

	}else{
		// Nothing to do.
		DEBUG("Image: " << imagePath << " already loaded!");
	}

	return image_map[imagePath];
}

// Create a new Struct Image variable, which whom we will add to the map.
void AssetsManager::InsertIntoImageMap(std::string imagePath, SDL_Surface* image, SDL_Texture *imageTexture){
	ASSERT(imagePath != "", "Image path can't be empty.");
	ASSERT(image != NULL, "SDL_Suface pointer can't be null.");

	Image *assets_manager_image = new Image;

	assets_manager_image->texture = imageTexture;
	assets_manager_image->width = image->w;
	assets_manager_image->height = image->h;

	// Insert image into image map.
	image_map[imagePath] = assets_manager_image;
	DEBUG("Image Map size after inserting " << image_map.size());
}

// Load music into music map if we couldn't find it isn't loaded yet.
// If it's already loaded, return it.
Mix_Music* AssetsManager::LoadMusic(std::string audio_path){
	DEBUG("Trying to load music " << audio_path);
	DEBUG("Music Map size before loading " << music_map.size());

	if(music_map.find(audio_path) == music_map.end()){
		INFO("Loading a new music asset.");

		Mix_Music * music = Mix_LoadMUS(audio_path.c_str());

		if(music == NULL){
			ERROR("Could not load music from path " << audio_path);
		}

		InsertIntoMusicMap(audio_path, music);

	}else{
		// Nothing to do.
		DEBUG("Music: " << audio_path << " already loaded!");
	}

	return music_map[audio_path];
}

// We will add a music to map.
void AssetsManager::InsertIntoMusicMap(std::string audio_path, Mix_Music * music){
	ASSERT(audio_path != "", "Music path can't be empty.");
	ASSERT(music != NULL, "Mix_Music pointer can't be null.");

	// Insert music into image map.
	music_map[audio_path] = music;
	DEBUG("Music Map size after inserting " << music_map.size());
}


// Load sound into sound map if we couldn't find it isn't loaded yet.
// If it's already loaded, return it.
Mix_Chunk* AssetsManager::LoadSound(std::string audio_path){
	DEBUG("Trying to load Sound " << audio_path);
	DEBUG("Sound Map size before loading " << sound_map.size());

	if(sound_map.find(audio_path) == sound_map.end()){
		INFO("Loading a new sound asset.");

		Mix_Chunk * sound = Mix_LoadWAV(audio_path.c_str());

		if(sound == NULL){
			ERROR("Could not load sound from path " << audio_path);
		}

		InsertIntoSoundMap(audio_path, sound);

	}else{
		// Nothing to do.
		DEBUG("Sound: " << audio_path << " already loaded!");
	}

	return sound_map[audio_path];
}

// We will add a sound to map.
void AssetsManager::InsertIntoSoundMap(std::string audio_path, Mix_Chunk * sound){
	ASSERT(audio_path != "", "Sound path can't be empty.");
	ASSERT(sound != NULL, "Mix_Chunk pointer can't be null.");

	// Insert sound into image map.
	sound_map[audio_path] = sound;
	DEBUG("Sound Map size after inserting " << sound_map.size());
}
