/**
 * @file obstacle.hpp
 * @brief Purpose: Contains the Obstacle class declaration.
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#ifndef OBSTACLE
#define OBSTACLE

#include "game_object.hpp"
#include "invisible_block.hpp"
#include "machine_part_code.hpp"

namespace Azo {

	/**
	 * @brief Class for possible Obstacle Types.
	 *
	 * Enum class used to differentiate obstacle types accordingly
	 * for sprite images and sizing purposes.
	 */
	enum class ObstacleType {
		GROUND,
		WESTERN_BOX,
		WESTERN_RAISED_BOX,
		WESTERN_CAR,
		WESTERN_ROCK,
		WESTERN_SPIKE,
		MACHINE_PART,
		WESTERN_POST
	};


	/**
	 * @brief Class for MachinePart state.
	 *
	 * Used to report the state of the game colectible MachinePart
	 * to ensure it is displayed correctly based on its state.
	 */
	enum class MachinePartState {
		COLLECTED,
		NON_COLLECTED,
		NON_MACHINE,
		FINISHED,
	};

	/**
		 * @brief Class to inform possible error and fucntion status.
		 *
		 * Enum class used to differentiate errors inside the obstacle.
		 */
		enum class FunctionStatusObstacle {
			WRONGTYPE,
			SUCCESS,
	};


	/**
	 * @brief Obstacle class for in-game objects with collision.
	 *
	 * Used to create game objects that the player has to avoid in order to
	 * progress or has to collect in-game(such as MachineParts).
	 */
	class Obstacle : public engine::GameObject {
		public:
			std::pair<double, double> mPositionRelativeToParent;
			std::list<InvisibleBlock *> mBlockList;
			ObstacleType mObstacleType;
			MachinePartState mMachinePartState = MachinePartState::NON_MACHINE;
			Obstacle();
			virtual ~Obstacle();
			Obstacle(std::string name, std::pair<double, double> positionRelativeToParent, ObstacleType obstacleType);
			void shutdown();
			void errorLog(std::string file);
			/**
			 * @brief Method for class name.
			 *
			 * Inline method for returning the class' name.
			 */
			inline std::string getClassName(){
				return "obstacle";
			}
		private:
			// Initializing pointes for components
			engine::ImageComponent *mObstacleImage = NULL;
			engine::AudioController *mAudioController = NULL;
			engine::Animation *mTurning = NULL;
			engine::AudioComponent *mCollected = NULL;
			std::vector<engine::Sprite *> mTurningAnimationSprites;
			MachinePartCode *mMachinePartCode = NULL;
			FunctionStatusObstacle errorCode = FunctionStatusObstacle::SUCCESS;
			void createComponents();
			void createBlocks();
			void generateTurningAnimation();

	};
}

#endif
