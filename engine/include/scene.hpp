/**
 * @file scene.hpp
 * @brief Purpose: Contains the Scene class declaration.
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
 */
#ifndef SCENE_ENGINE_HPP
#define SCENE_ENGINE_HPP

#include <iostream>
#include <unordered_map>
#include "sdl2include.h"
#include "game_object.hpp"

namespace engine {

	/*
	 *@brief Class for possible Scene States
	 *
	 *Enum class used to differentiate Scene States
	 */
	enum class SceneState {
		FIRST_TIME,
		RUNNED,
	};

	/*
	 *@brief a Scene class
	 *
	 *It'a how the engine will manage the Scenes that appear on screen
	 */
	class Scene {

	public:
		Scene();
		Scene(std::string sceneName);

		virtual void init();
		virtual void shutdown();
		virtual void draw();
		virtual void updateCode();
		virtual void restart();

		inline std::string getSceneName() {
			return sceneName;
		}

		void deleteKeyList();
		void addGameObject(engine::GameObject &gameObject);
		void removeGameObject(std::string &gameObjectName);

		engine::GameObject & getGameObject(std::string & gameObjectName);
		SceneState mState = SceneState::FIRST_TIME;

	protected:
		std::map<std::string, engine::GameObject *> gameObjectMap;
		std::list<std::string> mKeyList;
		std::string sceneName;
	};
}

#endif
