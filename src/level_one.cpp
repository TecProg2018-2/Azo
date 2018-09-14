#include "level_one.hpp"

using namespace Azo;

LevelOne::LevelOne(){}

LevelOne::LevelOne(std::string name){
	this->scene_name = name;

	CreateGameObjects();
}

void LevelOne::Restart(){
	gameObject_map.clear();

	//TODO(Roger): Add objects to be recreated one by one, here, instead of recalling CreateGameObjects.
	CreateGameObjects();

}

// Create new game objects for the level one here. Remember:
// the order used to add they to the scene is important.
void LevelOne::CreateGameObjects(){
	DEBUG("Creating Level One Game Objects.");

	DEBUG("Creating level_one object.");
	m_level_one = new engine::GameObject("level_one", std::make_pair(0, 0));

	m_level_background_1 = new engine::ImageComponent(*m_level_one, "backgrounds/level_one_part_one.png", 1);
	m_level_one->AddComponent(*m_level_background_1);

	m_level_background_2 = new engine::ImageComponent(*m_level_one, "backgrounds/level_one_part_two.png", 1, std::make_pair(8188, 0));
	m_level_one->AddComponent(*m_level_background_2);

	m_level_background_3 = new engine::ImageComponent(*m_level_one, "backgrounds/level_one_part_three.png", 1, std::make_pair(16379, 0));
	m_level_one->AddComponent(*m_level_background_3);

	mAudioController = new engine::AudioController();
	m_level_theme = new engine::AudioComponent(*m_level_one, "audios/banjo.ogg", true, true);
	mAudioController->AddAudio("tema_level_one", *m_level_theme);
	m_level_one->AddComponent(*mAudioController);

	this->AddGameObject(*m_level_one);



	DEBUG("Creating ground.");
	m_ground = new Obstacle("ground", std::make_pair(0, 404.5), ObstacleType::GROUND);
	this->AddGameObject(*m_ground);


	DEBUG("Creating obstacle car 1.");
	m_obstacle_car_1 = new Obstacle("obstacle_car_1", std::make_pair(1135, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*m_obstacle_car_1);


	DEBUG("Creating spike 1.");
	m_spike_1 = new Obstacle("obstacle_spike_1", std::make_pair(1349, 340), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*m_spike_1);


	DEBUG("Creating obstacle box 0_1.");
	m_obstacle_box_0_1 = new Obstacle("obstacle_box_0_1", std::make_pair(1309, 310), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_0_1);


	DEBUG("Creating obstacle aerial 1 - box.");
	m_obstacle_aerial_1 = new Obstacle("obstacle_aerial_1", std::make_pair(1350, 250), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_aerial_1);


	DEBUG("Creating part 1.");
	m_part_1 = new Obstacle("part_1", std::make_pair(1500, 80), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_1);


	DEBUG("Creating obstacle aerial 2 - post.");
	m_obstacle_aerial_2 = new Obstacle("obstacle_aerial_2", std::make_pair(1755, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_2);


	DEBUG("Creating part 1_1.");
	m_part_1_1 = new Obstacle("part_1_1", std::make_pair(1890, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_1_1);


	DEBUG("Creating obstacle aerial 3 - post.");
	m_obstacle_aerial_3 = new Obstacle("obstacle_aerial_3", std::make_pair(2030, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_3);


	DEBUG("Creating part 2.");
	m_part_2 = new Obstacle("part_2", std::make_pair(2225, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_2);


	DEBUG("Creating obstacle box 1.");
	m_obstacle_box_1 = new Obstacle("obstacle_box_1", std::make_pair(2225, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_1);


	DEBUG("Creating obstacle box 2.");
	m_obstacle_box_2 = new Obstacle("obstacle_box_2", std::make_pair(2645, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_2);


	DEBUG("Creating obstacle box 2_1.");
	m_obstacle_box_2_1 = new Obstacle("obstacle_box_2_1", std::make_pair(2779, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_2_1);


	DEBUG("Creating obstacle aerial 4 - box.");
	m_obstacle_aerial_4 = new Obstacle("obstacle_aerial_4", std::make_pair(2820, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_aerial_4);


	DEBUG("Creating part 3.")
	m_part_3 = new Obstacle("part_3", std::make_pair(2975, 310), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_3);


	DEBUG("Creating obstacle car 2.");
	m_obstacle_car_2 = new Obstacle("obstacle_car_2", std::make_pair(3040, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*m_obstacle_car_2);


	DEBUG("Creating part 4.");
	m_part_4 = new Obstacle("part_4", std::make_pair(3285, 100), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_4);


	DEBUG("Creating obstacle aerial 5 - post.");
	m_obstacle_aerial_5 = new Obstacle("obstacle_aerial_5", std::make_pair(3510, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_5);


	DEBUG("Creating part 4_1.");
	m_part_4_1 = new Obstacle("part_4_1", std::make_pair(3655, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_4_1);


	DEBUG("Creating obstacle aerial 6 - post.");
	m_obstacle_aerial_6 = new Obstacle("obstacle_aerial_6", std::make_pair(3675, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_6);


	DEBUG("Creating part 5.");
	m_part_5 = new Obstacle("part_5", std::make_pair(3975, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_5);


	DEBUG("Creating obstacle box 3.");
	m_obstacle_box_3 = new Obstacle("obstacle_box_3", std::make_pair(3975, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_3);


	DEBUG("Creating obstacle rock 1");
	m_obstacle_rock_1 = new Obstacle("obstacle_rock_1", std::make_pair(4300, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*m_obstacle_rock_1);


	DEBUG("Creating part 6.");
	m_part_6 = new Obstacle("part_6", std::make_pair(4460, 350), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_6);


	DEBUG("Creating obstacle aerial 7 - post.");
	m_obstacle_aerial_7 = new Obstacle("obstacle_aerial_7", std::make_pair(4660, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_7);


	DEBUG("Creating obstacle rock 2");
	m_obstacle_rock_2 = new Obstacle("obstacle_rock_2", std::make_pair(4855, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*m_obstacle_rock_2);


	DEBUG("Creating part 7.");
	m_part_7 = new Obstacle("part_7", std::make_pair(5015, 350), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_7);


	DEBUG("Creating obstacle aerial 8 - post.");
	m_obstacle_aerial_8 = new Obstacle("obstacle_aerial_8", std::make_pair(5215, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_8);


	DEBUG("Creating part 7_1.");
	m_part_7_1 = new Obstacle("part_7_1", std::make_pair(5360, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_7_1);


	DEBUG("Creating obstacle aerial 9 - post.");
	m_obstacle_aerial_9 = new Obstacle("obstacle_aerial_9", std::make_pair(5380, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_9);


	DEBUG("Creating part 8.");
	m_part_8 = new Obstacle("part_8", std::make_pair(5570, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_8);


	DEBUG("Creating part 9.");
	m_part_9 = new Obstacle("part_9", std::make_pair(6100, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_9);


	DEBUG("Creating obstacle aerial 10 - post.");
	m_obstacle_aerial_10 = new Obstacle("obstacle_aerial_10", std::make_pair(6150, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_10);


	DEBUG("Creating part 10.");
	m_part_10 = new Obstacle("part_10", std::make_pair(6340, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_10);


	DEBUG("Creating obstacle car 3.");
	m_obstacle_car_3 = new Obstacle("obstacle_car_3", std::make_pair(6700, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*m_obstacle_car_3);


	DEBUG("Creating part 11.");
	m_part_11 = new Obstacle("part_11", std::make_pair(6890, 80), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_11);


	DEBUG("Creating obstacle aerial 11 - post.");
	m_obstacle_aerial_11 = new Obstacle("obstacle_aerial_11", std::make_pair(7005, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_11);


	DEBUG("Creating part 12.");
	m_part_12 = new Obstacle("part_12", std::make_pair(7160, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_12);


	DEBUG("Creating obstacle aerial 12 - post.");
	m_obstacle_aerial_12 = new Obstacle("obstacle_aerial_12", std::make_pair(7180, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_12);


	DEBUG("Creating part 13.");
	m_part_13 = new Obstacle("part_13", std::make_pair(7540, 220), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_13);


	DEBUG("Creating part 14.");
	m_part_14 = new Obstacle("part_14", std::make_pair(7830, 220), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_14);


	DEBUG("Creating part 15.");
	m_part_15 = new Obstacle("part_15", std::make_pair(8040, 220), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_15);


	DEBUG("Creating part 16.");
	m_part_16 = new Obstacle("part_16", std::make_pair(8390, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_16);


	DEBUG("Creating obstacle aerial 13 - post.");
	m_obstacle_aerial_13 = new Obstacle("obstacle_aerial_13", std::make_pair(8570, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_13);


	DEBUG("Creating spike 2.");
	m_spike_2 = new Obstacle("obstacle_spike_2", std::make_pair(8880, 330), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*m_spike_2);


	DEBUG("Creating obstacle box 4.");
	m_obstacle_box_4 = new Obstacle("obstacle_box_4", std::make_pair(8820, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_4);


	DEBUG("Creating spike 3.");
	m_spike_3 = new Obstacle("obstacle_spike_3", std::make_pair(9120, 330), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*m_spike_3);


	DEBUG("Creating obstacle box 5.");
	m_obstacle_box_5 = new Obstacle("obstacle_box_5", std::make_pair(9117, 300), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_box_5);


	DEBUG("Creating spike 4.");
	m_spike_4 = new Obstacle("obstacle_spike_4", std::make_pair(9360, 330), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*m_spike_4);


	DEBUG("Creating obstacle box 6.");
	m_obstacle_box_6 = new Obstacle("obstacle_box_6", std::make_pair(9358, 300), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_box_6);


	DEBUG("Creating obstacle aerial 14 - box.");
	m_obstacle_aerial_14 = new Obstacle("obstacle_aerial_14", std::make_pair(9358, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_aerial_14);


	DEBUG("Creating obstacle box 7.");
	m_obstacle_box_7 = new Obstacle("obstacle_box_7", std::make_pair(9599, 300), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_box_7);


	DEBUG("Creating obstacle aerial 15 - box.");
	m_obstacle_aerial_15 = new Obstacle("obstacle_aerial_15", std::make_pair(9599, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_aerial_15);


	DEBUG("Creating part 17.");
	m_part_17 = new Obstacle("part_17", std::make_pair(9770, 350), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_17);


	DEBUG("Creating obstacle rock 3");
	m_obstacle_rock_3 = new Obstacle("obstacle_rock_3", std::make_pair(10070, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*m_obstacle_rock_3);


	DEBUG("Creating obstacle box 8.");
	m_obstacle_box_8 = new Obstacle("obstacle_box_8", std::make_pair(10480, 310), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_8);


	DEBUG("Creating part 18.");
	m_part_18 = new Obstacle("part_18", std::make_pair(10560, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_18);


	DEBUG("Creating obstacle aerial 16 - post.");
	m_obstacle_aerial_16 = new Obstacle("obstacle_aerial_16", std::make_pair(10730, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_16);


	DEBUG("Creating obstacle rock 4");
	m_obstacle_rock_4 = new Obstacle("obstacle_rock_4", std::make_pair(10930, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*m_obstacle_rock_4);


	DEBUG("Creating obstacle rock 5");
	m_obstacle_rock_5 = new Obstacle("obstacle_rock_5", std::make_pair(11180, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*m_obstacle_rock_5);


	DEBUG("Creating obstacle aerial 17 - post.");
	m_obstacle_aerial_17 = new Obstacle("obstacle_aerial_17", std::make_pair(11465, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_17);


	DEBUG("Creating obstacle box 9.");
	m_obstacle_box_9 = new Obstacle("obstacle_box_9", std::make_pair(11850, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_9);


	DEBUG("Creating obstacle box 10.");
	m_obstacle_box_10 = new Obstacle("obstacle_box_10", std::make_pair(11984, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_10);


	DEBUG("Creating obstacle aerial 18 - box.");
	m_obstacle_aerial_18 = new Obstacle("obstacle_aerial_18", std::make_pair(12025, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_aerial_18);


	DEBUG("Creating part 19.");
	m_part_19 = new Obstacle("part_19", std::make_pair(12180, 340), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_19);


	DEBUG("Creating obstacle aerial 19 - post.");
	m_obstacle_aerial_19 = new Obstacle("obstacle_aerial_19", std::make_pair(12370, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_19);


	DEBUG("Creating obstacle rock 6");
	m_obstacle_rock_6 = new Obstacle("obstacle_rock_6", std::make_pair(12600, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*m_obstacle_rock_6);


	DEBUG("Creating obstacle rock 7");
	m_obstacle_rock_7 = new Obstacle("obstacle_rock_7", std::make_pair(12850, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*m_obstacle_rock_7);


	DEBUG("Creating obstacle rock 8");
	m_obstacle_rock_8 = new Obstacle("obstacle_rock_8", std::make_pair(13100, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*m_obstacle_rock_8);


	DEBUG("Creating obstacle car 4.");
	m_obstacle_car_4 = new Obstacle("obstacle_car_4", std::make_pair(13570, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*m_obstacle_car_4);


	DEBUG("Creating part 20.");
	m_part_20 = new Obstacle("part_20", std::make_pair(13860, 70), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_20);


	DEBUG("Creating obstacle car 5.");
	m_obstacle_car_5 = new Obstacle("obstacle_car_5", std::make_pair(14200, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*m_obstacle_car_5);


	DEBUG("Creating spike 5.");
	m_spike_5 = new Obstacle("obstacle_spike_5", std::make_pair(14414, 340), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*m_spike_5);


	DEBUG("Creating obstacle box 11.");
	m_obstacle_box_11 = new Obstacle("obstacle_box_11", std::make_pair(14374, 310), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*m_obstacle_box_11);


	DEBUG("Creating obstacle aerial 20 - box.");
	m_obstacle_aerial_20 = new Obstacle("obstacle_aerial_20", std::make_pair(14415, 250), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*m_obstacle_aerial_20);


	DEBUG("Creating part 21.");
	m_part_21 = new Obstacle("part_21", std::make_pair(14565, 80), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_21);


	DEBUG("Creating obstacle aerial 21 - post.");
	m_obstacle_aerial_21 = new Obstacle("obstacle_aerial_21", std::make_pair(14820, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_21);


	DEBUG("Creating obstacle rock 9");
	m_obstacle_rock_9 = new Obstacle("obstacle_rock_9", std::make_pair(15000, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*m_obstacle_rock_9);


	DEBUG("Creating obstacle aerial 22 - post.");
	m_obstacle_aerial_22 = new Obstacle("obstacle_aerial_22", std::make_pair(15300, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*m_obstacle_aerial_22);


	DEBUG("Creating part 22.");
	m_part_22 = new Obstacle("part_22", std::make_pair(15530, 140), ObstacleType::MACHINE_PART);
	this->AddGameObject(*m_part_22);


	DEBUG("Creating Player.");
	m_player = new Player("player", std::make_pair(165, 280));
	this->AddGameObject(*m_player);

	CreateEndingScreen();
	AddLevelParents();

	m_level_code = new LevelOneCode(*m_level_one);
	m_level_one->AddComponent(*m_level_code);

}

void LevelOne::CreateEndingScreen(){
	m_winning_screen_object = new engine::GameObject("winning_screen", std::make_pair(0, 0));
	m_winning_screen_object->mObjectState = engine::ObjectState::DISABLED;

	m_winning_screen = new engine::BackgroundComponent(*m_winning_screen_object, "general_images/tela_vitoria.png");

	m_winning_screen_object->AddComponent(*m_winning_screen);
	this->AddGameObject(*m_winning_screen_object);

	m_losing_parts_screen_object = new engine::GameObject("losing_parts", std::make_pair(0, 0));
	m_losing_parts_screen_object->mObjectState = engine::ObjectState::DISABLED;

	m_losing_parts_screen = new engine::BackgroundComponent(*m_losing_parts_screen_object, "general_images/tela_derrota.png");

	m_losing_parts_screen_object->AddComponent(*m_losing_parts_screen);
	this->AddGameObject(*m_losing_parts_screen_object);

	m_losing_death_screen_object = new engine::GameObject("losing_death", std::make_pair(0, 0));
	m_losing_death_screen_object->mObjectState = engine::ObjectState::DISABLED;

	m_losing_death_screen = new engine::BackgroundComponent(*m_losing_death_screen_object, "general_images/tela_morte.png");

	m_losing_death_screen_object->AddComponent(*m_losing_death_screen);
	this->AddGameObject(*m_losing_death_screen_object);

	m_arrow = new engine::GameObject("arrow", std::make_pair(0, 0));
	m_arrow->mObjectState = engine::ObjectState::DISABLED;

	m_arrow_image = new engine::ImageComponent(*m_arrow, "general_images/arrow.png", 1);

	m_arrow->AddComponent(*m_arrow_image);
	this->AddGameObject(*m_arrow);
}


void LevelOne::AddLevelParents(){
	DEBUG("Adding level parents.");

	m_level_one->mParentList.push_back(m_obstacle_car_1);
	m_level_one->mParentList.push_back(m_obstacle_aerial_1);
	m_level_one->mParentList.push_back(m_obstacle_box_0_1);
	m_level_one->mParentList.push_back(m_spike_1);
	m_level_one->mParentList.push_back(m_part_1);
	m_level_one->mParentList.push_back(m_obstacle_aerial_2);
	m_level_one->mParentList.push_back(m_part_1_1);
	m_level_one->mParentList.push_back(m_obstacle_aerial_3);
	m_level_one->mParentList.push_back(m_part_2);
	m_level_one->mParentList.push_back(m_obstacle_box_1);
	m_level_one->mParentList.push_back(m_obstacle_box_2);
	m_level_one->mParentList.push_back(m_obstacle_aerial_4);
	m_level_one->mParentList.push_back(m_obstacle_box_2_1);
	m_level_one->mParentList.push_back(m_part_3);
	m_level_one->mParentList.push_back(m_obstacle_car_2);
	m_level_one->mParentList.push_back(m_part_4);
	m_level_one->mParentList.push_back(m_obstacle_aerial_5);
	m_level_one->mParentList.push_back(m_part_4_1);
	m_level_one->mParentList.push_back(m_obstacle_aerial_6);
	m_level_one->mParentList.push_back(m_part_5);
	m_level_one->mParentList.push_back(m_obstacle_box_3);
	m_level_one->mParentList.push_back(m_obstacle_rock_1);
	m_level_one->mParentList.push_back(m_part_6);
	m_level_one->mParentList.push_back(m_obstacle_aerial_7);
	m_level_one->mParentList.push_back(m_obstacle_rock_2);
	m_level_one->mParentList.push_back(m_part_7);
	m_level_one->mParentList.push_back(m_obstacle_aerial_8);
	m_level_one->mParentList.push_back(m_part_7_1);
	m_level_one->mParentList.push_back(m_obstacle_aerial_9);
	m_level_one->mParentList.push_back(m_part_8);
	m_level_one->mParentList.push_back(m_part_9);
	m_level_one->mParentList.push_back(m_obstacle_aerial_10);
	m_level_one->mParentList.push_back(m_part_10);
	m_level_one->mParentList.push_back(m_obstacle_car_3);
	m_level_one->mParentList.push_back(m_part_11);
	m_level_one->mParentList.push_back(m_obstacle_aerial_11);
	m_level_one->mParentList.push_back(m_part_12);
	m_level_one->mParentList.push_back(m_obstacle_aerial_12);
	m_level_one->mParentList.push_back(m_part_13);
	m_level_one->mParentList.push_back(m_part_14);
	m_level_one->mParentList.push_back(m_part_15);
	m_level_one->mParentList.push_back(m_part_16);
	m_level_one->mParentList.push_back(m_obstacle_aerial_13);
	m_level_one->mParentList.push_back(m_spike_2);
	m_level_one->mParentList.push_back(m_obstacle_box_4);
	m_level_one->mParentList.push_back(m_spike_3);
	m_level_one->mParentList.push_back(m_obstacle_box_5);
	m_level_one->mParentList.push_back(m_spike_4);
	m_level_one->mParentList.push_back(m_obstacle_box_6);
	m_level_one->mParentList.push_back(m_obstacle_aerial_14);
	m_level_one->mParentList.push_back(m_obstacle_box_7);
	m_level_one->mParentList.push_back(m_obstacle_aerial_15);
	m_level_one->mParentList.push_back(m_part_17);
	m_level_one->mParentList.push_back(m_obstacle_rock_3);
	m_level_one->mParentList.push_back(m_obstacle_box_8);
	m_level_one->mParentList.push_back(m_part_18);
	m_level_one->mParentList.push_back(m_obstacle_aerial_16);
	m_level_one->mParentList.push_back(m_obstacle_rock_4);
	m_level_one->mParentList.push_back(m_obstacle_rock_5);
	m_level_one->mParentList.push_back(m_obstacle_aerial_17);
	m_level_one->mParentList.push_back(m_obstacle_box_9);
	m_level_one->mParentList.push_back(m_obstacle_box_10);
	m_level_one->mParentList.push_back(m_obstacle_aerial_18);
	m_level_one->mParentList.push_back(m_part_19);
	m_level_one->mParentList.push_back(m_obstacle_aerial_19);
	m_level_one->mParentList.push_back(m_obstacle_rock_6);
	m_level_one->mParentList.push_back(m_obstacle_rock_7);
	m_level_one->mParentList.push_back(m_obstacle_rock_8);
	m_level_one->mParentList.push_back(m_obstacle_car_4);
	m_level_one->mParentList.push_back(m_part_20);
	m_level_one->mParentList.push_back(m_obstacle_car_5);
	m_level_one->mParentList.push_back(m_obstacle_aerial_20);
	m_level_one->mParentList.push_back(m_obstacle_box_11);
	m_level_one->mParentList.push_back(m_spike_5);
	m_level_one->mParentList.push_back(m_part_21);
	m_level_one->mParentList.push_back(m_obstacle_aerial_21);
	m_level_one->mParentList.push_back(m_obstacle_rock_9);
	m_level_one->mParentList.push_back(m_obstacle_aerial_22);
	m_level_one->mParentList.push_back(m_part_22);

	m_level_one->mParentList.push_back(m_winning_screen_object);
	m_level_one->mParentList.push_back(m_losing_parts_screen_object);
	m_level_one->mParentList.push_back(m_losing_death_screen_object);
	m_level_one->mParentList.push_back(m_arrow);

	m_level_one->mParentList.push_back(m_player);
	m_level_one->mParentList.push_back(m_ground);
}
