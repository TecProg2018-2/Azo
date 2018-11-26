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
#include <ctime>
#include <fstream>
#include <iostream>

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
	DEBUG("Creating Audio Component.");
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

	DEBUG("Init audio component");

	// Checks if audio in question is music or sound effect
	if (isMusic) {
		DEBUG("Playing Music" << audioPath);
		music = Game::instance.getAssetsManager().LoadMusic(audioPath);

		if (music == NULL) {
			ERROR("Invalid Music Path (Music = NULL): " << audioPath);
			errorLog(ErrorTypeAudioComponent::NULL_POINTER, "AudioComponent::init");
		} else {

		}

	} else {
		DEBUG("Playing Sound" << audioPath);
		sound = Game::instance.getAssetsManager().LoadSound(audioPath);

		if (sound == NULL) {
			ERROR("Invalid Sound Path (Sound = NULL): " << audioPath);
			errorLog(ErrorTypeAudioComponent::NULL_POINTER, "AudioComponent::init");
		} else {
			//Nothing to do
		}
	}

}


void AudioComponent::updateCode() {

	if (playOnStart) {
		DEBUG("Playing audio on startup");
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

	DEBUG("Shutdown audio component");

	stop(-1);

	if(music != nullptr) {
		Mix_FreeMusic(music);
		music = nullptr;
	} else {
		DEBUG("No music to shutdown");
		//Nothing to do
	}

	if(sound != nullptr) {
		DEBUG("No sound to shutdown");
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
		DEBUG("Audio is music");
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
		DEBUG("Audio is sound");
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
	DEBUG("Changing AudioState to PLAYING");
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
	DEBUG("Changing AudioState to PAUSED");
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
	DEBUG("Changing AudioState to PAUSED");
	audioState = AudioState::PAUSED;
}


/*
 *@brief Method to log error messages.
 *
 * Writes a file with error message, function containing error and time.
 */
void AudioComponent::errorLog(ErrorTypeAudioComponent code, std::string file){
    std::ofstream outfile;
    outfile.open("../errorLog.txt", std::ofstream::out | std::ofstream::app);
    time_t now = time(0);
    std::string dt = ctime(&now); //convert to string
	outfile << "Function: " + file << std::endl;
    outfile << "Date: " + dt << std::endl;

    switch(code) {
        case ErrorTypeAudioComponent::DIVI_BY_ZERO:
            outfile << "Error: division by zero" << std::endl;
            break;
        case ErrorTypeAudioComponent::EMPTY_STRING:
            outfile << "Error: empty String" << std::endl;
            break;
        case ErrorTypeAudioComponent::NULL_POINTER:
            outfile << "Error: null pointer" << std::endl;
            break;
        case ErrorTypeAudioComponent::WRONG_TYPE:
            outfile << "Error: wrong type" << std::endl;
			break;
		default:
			outfile << "Error: no matching file" << std::endl;
    }
    outfile << "===============" << std::endl;
    outfile.close();
}
