#include "audio_controller.hpp"

using namespace engine;

AudioController::~AudioController(){}

void AudioController::init(){
	for(auto audio_row : audio_map){
		auto audio = audio_row.second;
		audio->init();
	}
}

void AudioController::shutdown(){
	for(auto audio_row : audio_map){
		auto audio = audio_row.second;
		audio->shutdown();
		audio = NULL;
	}
}

void AudioController::updateCode(){
	for(auto audio_row : audio_map){
		auto audio = audio_row.second;
		if(audio->isEnabled()){
			audio->updateCode();
		}
	}
}

AudioController::AudioController(){
	this->componentState = State::ENABLED;
}

AudioController::AudioController(GameObject &gameObject){
	this->gameObject = &gameObject;
	this->componentState = State::ENABLED;
}

void AudioController::AddAudio(std::string audio_name, AudioComponent &audio){
	audio_map[audio_name] = &audio;
}

void AudioController::PlayAudio(std::string audio_name){

	auto audio_to_be_played = audio_map.find(audio_name);

	if(audio_to_be_played != audio_map.end()){
		audio_to_be_played->second->play(-1, -1);

	}else{
		ERROR("This audio doesn't exist.");
	}
}

void AudioController::StopAudio(std::string audio_name){
	auto audio_to_be_played = audio_map.find(audio_name);

	if(audio_to_be_played != audio_map.end()){
		audio_to_be_played->second->stop(-1);
	}else{
		ERROR("Audio couldn't be found!");
	}
}

void AudioController::StopAllAudios(){
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
}


void AudioController::PauseAudio(std::string audio_name){
	auto audio_to_be_played = audio_map.find(audio_name);

	if(audio_to_be_played != audio_map.end()){
		audio_to_be_played->second->pause(-1);
	}else{
		ERROR("Animation couldn't be found!");
	}
}

AudioState AudioController::GetAudioState(std::string audio_name){
	auto audio = audio_map.find(audio_name);

	if(audio == audio_map.end()){
		ERROR("Audio doesn't exist");
	}

	return audio->second->audioState;
}
