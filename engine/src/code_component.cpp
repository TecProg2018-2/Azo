#include "code_component.hpp"


using namespace engine;

CodeComponent::CodeComponent(){}

CodeComponent::CodeComponent(GameObject &gameObject){
	this->gameObject = &gameObject;
	this->componentState = State::ENABLED;
}

void CodeComponent::Init(){}

void CodeComponent::Shutdown(){}

void CodeComponent::UpdateCode(){}
