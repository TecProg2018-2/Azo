/**
  * @file audio_component.cpp
  * @brief Purpose: Contains all the methods related to AudioComponent.
  *
  * GPL v3.0 License
  * Copyright (c) 2017 Azo
  *
  * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
  */
#include "audio_component.hpp"
#include "game.hpp"


using namespace engine;

/*
 *@brief Default constructor for the AudioComponent.
 *
 * @return "void".
 */
AudioComponent::AudioComponent() {}

AudioComponent::~AudioComponent() {}

/*
 *@brief Constructor for the AudioComponent
 *
 * Initializes all parameters of the audio component
 *
 */
AudioComponent::AudioComponent(GameObject &gameObject,std::string audioPath,
							  	bool isMusic, bool playOnStart) {

	this->gameObject = &gameObject;
	this->audioPath = audioPath;//path to audio file
	this->isMusic = isMusic;	//bool to check if music exists
	this->playOnStart = playOnStart;
	this->audioState = AudioState::STOPPED;
	this->music = nullptr;
	this->sound = nullptr;
}

/*
 *@brief Method to initialize the in game Audio
 *
 *@return "void"
 */
void AudioComponent::init() {

	INFO("init audio component");

	// Checks if audio in question is music or sound effect
	if (isMusic) {
		music = Game::instance.getAssetsManager().LoadMusic(audioPath);

		if (music == NULL) {
			ERROR("Invalid Music Path (Music = NULL): " << audioPath);
		} else {

		}

	} else {
		sound = Game::instance.getAssetsManager().LoadSound(audioPath);

		if (sound == NULL) {
			ERROR("Invalid Sound Path (Sound = NULL): " << audioPath);
		} else {
			//Nothing to do
		}
	}

}


void AudioComponent::updateCode() {

	if (playOnStart) {
		play (-1, -1); // Plays audio once until end
		playOnStart = false;
	} else {
		//Nothing to do
	}
}

/*
 *@brief Method to shut down the Audio component
 *
 *@return "void"
*/
void AudioComponent::shutdown() {

	INFO("shutdown audio component");

	stop(-1);

	if(music != nullptr) {
		Mix_FreeMusic(music);
		music = nullptr;
	} else {
		//Nothing to do
	}

	if(sound != nullptr) {
		sound = nullptr;
	} else {
		//Nothing to do
	}
}

/*
 *@brief Method to change the audio state to PLAYING
 *
 *@return "void".
 */
void AudioComponent::play(int loops, int channel) {

	INFO("AudioComponent::Play audio: " << audioPath);

	//checks if the audio in question is music or sound effect
	if (isMusic) {

		if (audioState == AudioState::STOPPED) {
			Mix_PlayMusic (music, loops);
			INFO("Play music: " << audioPath);
		} else if (audioState == AudioState::PAUSED) {
			Mix_ResumeMusic();
			INFO("Resume music: " << audioPath);
		} else {
			//Nothing to do
		}

	} else {

		if (audioState == AudioState::STOPPED){
			Mix_PlayChannel(channel, sound, 0);
			INFO("Play sound: " << audioPath);
		} else if (audioState == AudioState::PAUSED){
			Mix_Resume(channel);
			INFO("Resume sound: " << audioPath);
		} else {
			//Nothing to do
		}
	}

	audioState = AudioState::PLAYING;
}

/*
 *@brief Method to change the audio state to STOPPED
 *
 *@return "void".
 */
void AudioComponent::stop(int channel){

	INFO("AudioComponent::Stop audio: " << audioPath);

	//checks if the audio in question is music or sound effect
	if (isMusic){
		Mix_HaltMusic();
		INFO("Stop music: " << audioPath);
	} else {
		Mix_HaltChannel(channel);
		INFO("Stop sound: " << audioPath);
	}

	audioState = AudioState::STOPPED;
}

/*@brief Method to change the audio state to PAUSED
 *
 *@return "void"
 */
void AudioComponent::pause(int channel) {

	INFO("AudioComponent::Pause audio: " << audioPath);

	//checks if the audio in question is music or sound effect
	if (isMusic) {
		Mix_PauseMusic();
		INFO("Pause music: " << audioPath);
	} else {
		Mix_Pause(channel);
		INFO("Pause sound: " << audioPath);
	}

	audioState = AudioState::PAUSED;
}
