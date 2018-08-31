#ifndef SCENE_ENGINE_HPP
#define SCENE_ENGINE_HPP

#include <iostream>
#include "sdl2include.h"
#include "game_object.hpp"
#include <unordered_map>

namespace engine {
	enum class SceneState {
		FIRST_TIME,
		RUNNED,
	};

	class Scene {
		public:
			Scene();
			Scene(std::string scene_name);

			virtual void init();
			virtual void shutdown();
			virtual void draw();
			virtual void updateCode();
			virtual void Restart();

			inline std::string GetSceneName() {
				return scene_name;
			}

			void DeleteKeyList();

			void AddGameObject(engine::GameObject &gameObject);
			engine::GameObject & GetGameObject(std::string & gameObject_name);
			void RemoveGameObject(std::string &gameObject_name);

			SceneState m_state = SceneState::FIRST_TIME;

		protected:
			std::map<std::string, engine::GameObject *> gameObject_map;
			std::list<std::string> m_key_list;
			std::string scene_name;
	};
}

#endif
