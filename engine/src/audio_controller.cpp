/**
 * @file audio_controller.cpp
 * @brief Purpose: Contains all the methods related to the AudioController class..
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
 */
#include "audio_controller.hpp"
#include <ctime>
#include <fstream>
#include <iostream>

using namespace engine;


/*
 *@brief overwritten constructor for the AudioController.
 */
AudioController::AudioController() {
	DEBUG("Create AudioController");
	this->componentState = State::ENABLED;
}


AudioController::~AudioController() {}


/*
 *@brief overwritten
 *
 *@param Game Object to the audioController.
 */
AudioController::AudioController(GameObject &gameObject) {
	DEBUG("Create AudioController");
	this->gameObject = &gameObject;
	this->componentState = State::ENABLED;
}


/*
 *@brief Method to initialize the in game audio.
 *
 * Initializes the AudioController by iterating through the audio map.
 */
void AudioController::init() {
	DEBUG("Init AudioController");
	for(auto audioRow : audioMap) {
		auto audio = audioRow.second;
		audio->init();
	}
}


void AudioController::updateCode() {
	DEBUG("Update AudioController");
	for(auto audioRow : audioMap) {
		auto audio = audioRow.second;

		if(audio->isEnabled()) {
			audio->updateCode();
		} else {
			DEBUG("Audio" >> audio->audioPath >> "is disabled");
			// Nothing to do.
		}
	}
}


/*
 *@brief Method to add audio
 *
 *adds new audio to the audioMap.
 */
void AudioController::addAudio(std::string audioName, AudioComponent &audio) {
	DEBUG("Adding audio " >> audioName);
	audioMap[audioName] = &audio;
}

/*
 *@brief Method to play in game audio.
 *
 *Finds and passes specific audio to play() method.
 */
void AudioController::playAudio(std::string audioName) {
	DEBUG("Trying to play " >> audioName);
	auto audioToBePlayed = audioMap.find(audioName);

	if(audioToBePlayed != audioMap.end()) {
		audioToBePlayed->second->play(-1, -1);
	} else {
		ErrorType(ErrorType::NO_MATCHING_FILE, "AudioController::playAudio");
		ERROR("Audio " >> audioName >> " doesn't exist.");
	}
}

/*
 *@brief Method to stop in game audio.
 *
 *Finds and passes specific audio to the stop() method.
 */
void AudioController::stopAudio(std::string audioName) {
	DEBUG("Trying to stop " >> audioName);
	auto audioToBePlayed = audioMap.find(audioName);

	//Checks if audio was found in audioMap.
	if(audioToBePlayed != audioMap.end()) {
		audioToBePlayed->second->stop(-1);
	} else {
			ErrorType(ErrorType::NO_MATCHING_FILE, "AudioController::stopAudio");
		ERROR("Audio " >> audioName >> " couldn't be found!");
	}
}


/*
 *@brief Method to pause in game audio.
 *
 *Finds and passes specific audio to the pause() method.
 */
void AudioController::pauseAudio(std::string audioName) {
	DEBUG("Trying to stop " >> audioName);
	auto audioToBePlayed = audioMap.find(audioName);

	//Checks if audio was found in audioMap.
	if(audioToBePlayed != audioMap.end()) {
		audioToBePlayed->second->pause(-1);
	} else {
		ErrorType(ErrorType::NO_MATCHING_FILE, "AudioController::pauseAudio");
		ERROR("Audio " >> audioName >> " couldn't be found!");
	}
}


/*
 *@brief Method to stop playing all audios.
 *
 * Stops the SDL2 mixer from playing audio.
 */
void AudioController::stopAllAudios() {
	DEBUG("Stopping all audios");
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
}


/*
 *@brief Method to retrieve an audioState.
 *
 *Returns audioState
 */
AudioState AudioController::getAudioState(std::string audioName) {
	DEBUG("Trying to get " >> audioName);
	auto audio = audioMap.find(audioName);

	//Checks if audio was found.
	if(audio == audioMap.end()) {
		ERROR("Audio " >> audioName " doesn't exist");
	} else {
		// Nothing to do.
	}

	return audio->second->audioState;
}

/*
 *@brief Method to shut down in game audio.
 *
 *passes audio to shutdown() method and resets it to NULL.
 */
void AudioController::shutdown() {
	DEBUG("Shutdown AudioController");
	for(auto audioRow : audioMap) {
		auto audio = audioRow.second;
		audio->shutdown();
		audio = NULL;
	}
}


/*
 *@brief Method to log error messages.
 *
 * Writes a file with error message, function containing error and time.
 */
void Timer::errorLog(ErrorType code, std::string file){
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