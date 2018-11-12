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

using namespace engine;

AudioController::~AudioController() {}

/*
 *@brief Method to initialize the in game audio.
 */
void AudioController::init() {
	DEBUG("Init AudioController");
	for(auto audioRow : audioMap) {
		auto audio = audioRow.second;
		audio->init();
	}
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
 *@brief overwritten constructor for the AudioController.
 */
AudioController::AudioController() {
	DEBUG("Create AudioController");
	this->componentState = State::ENABLED;
}

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
		ERROR("Audio " >> audioName >> " couldn't be found!");
	}
}

void AudioController::stopAllAudios() {
	DEBUG("Stopping all audios");
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
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
		ERROR("Audio " >> audioName >> " couldn't be found!");
	}
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
