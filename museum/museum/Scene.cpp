#include "Scene.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Model.h"
#include "Collision.h"
#include <map>
#include <string>

Renderer* renderer;
Renderer* renderPodium;

map<std::string, Model>* models;
//AABB BOXES
AABB column_downLeft;
AABB column_upLeft;
AABB column_upRight;
AABB column_downRight;
AABB ab_floor;
AABB otherWalls;
AABB middelDino1;
AABB middleDino2;
AABB middleTerrain;

Scene::Scene(GLuint width, GLuint height) :
	Width(width), Height(height)
{

}

Scene::~Scene()
{
	delete renderer;
}

void Scene::Init()
{
	//Shaders
	ResourceManager::LoadShader("Floor.vs", "Floor.fs", "shaderFloor");

	//Textures
	ResourceManager::LoadTexture("../../Dependencies/Textures/Floor.png", "floorTexture");
	ResourceManager::LoadTexture("../../Dependencies/Textures/whiteWall.png", "wallTexture");
	ResourceManager::LoadTexture("../../Dependencies/Textures/Ceiling.png", "ceilingTexture");
	ResourceManager::LoadTexture("../../Dependencies/Textures/OceanFloor.png", "oceanFloorTexture");
	ResourceManager::LoadTexture("../../Dependencies/Textures/underwater-background.png", "oceanWallTexture");
	ResourceManager::LoadTexture("../../Dependencies/Textures/MountainFloor.png", "mountainFloorTexture");
	ResourceManager::LoadTexture("../../Dependencies/Textures/mountain.png", "mountainWallTexture");
	ResourceManager::LoadTexture("../../Dependencies/Textures/desertFloor.png", "desertFloorTexture");
	ResourceManager::LoadTexture("../../Dependencies/Textures/desertWall.png", "desertWallTexture");

	models = new map<std::string, Model>();
	//MODELS
	models->insert({ "Column", Model("../../Dependencies/3DObjects/Column/MinoanColumnB_Low.obj") });
	////Middle zone
	models->insert({ "Dino1", Model("../../Dependencies/3DObjects/Dino1/13623_Quetzalcoatlus_v1_L2.obj") });
	models->insert({ "Dino2",Model("../../Dependencies/3DObjects/Dino2/13632_Chirostenotes_v1_L2.obj") });
	models->insert({ "Grass", Model("../../Dependencies/3DObjects/grass/10438_Circular_Grass_Patch_v1_iterations-2.obj") });
	//Ocean zone
	models->insert({ "Diver", Model("../../Dependencies/3DObjects/ocean/Diver/13018_Aquarium_Deep_Sea_Diver_v1_L1.obj") });
	models->insert({ "PinkFish",Model("../../Dependencies/3DObjects/ocean/PinkFish/13014_Six_Line_Wrasse_v1_l3.obj") });
	models->insert({ "Doris",Model("../../Dependencies/3DObjects/ocean//Doris/13006_Blue_Tang_v1_l3.obj") });
	models->insert({ "GoldenFish",Model("../../Dependencies/3DObjects/ocean/GoldenFish/12265_Fish_v1_L2.obj") });
	models->insert({ "Turtle",Model("../../Dependencies/3DObjects/ocean/Turtle/20446_Sea_Turtle_v1 Textured.obj") });
	models->insert({ "Crab",Model("../../Dependencies/3DObjects/ocean/Crab/10012_crab_v2_iterations-1.obj") });
	models->insert({ "BeautyFish",Model("../../Dependencies/3DObjects/ocean/CoralBeautyFish/13009_Coral_Beauty_Angelfish_v1_l3.obj") });
	models->insert({ "GreenFish",Model("../../Dependencies/3DObjects/ocean/GreenFish/13007_Blue-Green_Reef_Chromis_v2_l3.obj") });
	//Desert Zone
	models->insert({ "Camel",Model("../../Dependencies/3DObjects/desert/camila/Camel.obj") });
	models->insert({ "Armadillo",Model("../../Dependencies/3DObjects/desert/armadillo/10002_Armadillo_v1_L3.obj") });
	models->insert({ "DesertCat",Model("../../Dependencies/3DObjects/desert/pisica de desert/12161_Cat_v1_L2.obj") });
	models->insert({ "Snake",Model("../../Dependencies/3DObjects/desert/sarpe/13105_Ringneck_Snake_v1_l3.obj") });
	models->insert({ "DesertMouse",Model("../../Dependencies/3DObjects/desert/soarece de desert/13099_NorthAmericanMuskrat_v1_l2.obj") });
	models->insert({ "Lizard",Model("../../Dependencies/3DObjects/desert/soparla/12275_Lizard_v1_l2.obj") });
	models->insert({ "Strut",Model("../../Dependencies/3DObjects/desert/Strut/12246_Bird_v2_L2.obj") });
	models->insert({ "DesertEagle",Model("../../Dependencies/3DObjects/desert/vultur/13582_GoldenVulture_V1_L3.obj") });
	models->insert({ "Cactus",Model("../../Dependencies/3DObjects/desert/cactus/10436_Cactus_v1_max2010_it2.obj") });
	//Mountain/forest zone
	models->insert({ "Bear",Model("../../Dependencies/3DObjects/mountain/urs tibetan/13576_Tibetan_Bear_v1_l3.obj") });
	models->insert({ "Wolf",Model("../../Dependencies/3DObjects/mountain/lup/10055_Gray_Wolf_v1_L3.obj") });
	models->insert({ "Deer",Model("../../Dependencies/3DObjects/mountain/deer/12961_White-Tailed_Deer_v1_l2.obj") });
	models->insert({ "Ibex",Model("../../Dependencies/3DObjects/mountain/ibex/13575_Ibex_v1_L1.obj") });
	models->insert({ "Fox",Model("../../Dependencies/3DObjects/mountain/vulpe/13577_Tibetan_Hill_Fox_v1_L3.obj") });
	models->insert({ "Dihor",Model("../../Dependencies/3DObjects/mountain/dihor/10019_ferret_v1_iterations-2.obj") });
	models->insert({ "Veverita",Model("../../Dependencies/3DObjects/mountain/veverita/10051_Squirrel_v2_L3.obj") });
	models->insert({ "Tree", Model("../../dependencies/3DObjects/mountain/Tree/10460_Yellow_Poplar_Tree_v1_L3.obj") });

	//Renderers
	renderer = new Renderer(ResourceManager::GetShader("shaderFloor"));
	renderPodium = new Renderer(ResourceManager::GetShader("shaderFloor"), true);
}

void Scene::SetCamera(Camera* camera)
{
	pCamera = camera;
}

void Scene::Render()
{
	//THE ROOM
	renderer->Draw(ResourceManager::GetTexture("floorTexture"), pCamera, glm::vec3(), glm::vec3(), 0.f, glm::vec3(), NULL);
	//AABB floro
	ab_floor.m_max = glm::vec3(25.0f, -0.5f, 25.0f);
	ab_floor.m_min = glm::vec3(-25.0f, -1.0f, -25.0f);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(0.f, 4.5f + resize, -4.5f - resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(0.f, 4.5f + resize, 5.5f + resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(4.5f + resize, 4.5f + resize, 0.f), glm::vec3(), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(-5.5f - resize, 4.5f + resize, 0.f), glm::vec3(), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("ceilingTexture"), pCamera, glm::vec3(0.f, 5.f + resize, 0.f), glm::vec3(), 0.f, glm::vec3(0.f, 0.f, 1.f), NULL);
	//AABB otherwalls
	otherWalls.m_max = glm::vec3(24.0f, 24.0f, 24.0f);
	otherWalls.m_min = glm::vec3(-24.0f, -0.3f, -24.0f);
	//DESERT WALL + PODIUM
	renderer->Draw(ResourceManager::GetTexture("desertWallTexture"), pCamera, glm::vec3(0.f, 1.f, -4.4f - resize), glm::vec3(0.6f, 0.6f, 0.6f), glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderPodium->Draw(ResourceManager::GetTexture("desertFloorTexture"), pCamera, glm::vec3(0.f, 0.f, -20.f), glm::vec3(23.5f, 1.f, 10.f), 0.0f, glm::vec3(), NULL);
	//MOUNTAIN WALL + PODIUM
	renderPodium->Draw(ResourceManager::GetTexture("mountainFloorTexture"), pCamera, glm::vec3(-20.5f, 0.f, 0.f), glm::vec3(10.f, 1.f, 23.f), 0.0f, glm::vec3(), NULL);
	renderer->Draw(ResourceManager::GetTexture("mountainWallTexture"), pCamera, glm::vec3(-5.0f - resize, 1.f, 0.f), glm::vec3(0.6f, 0.6f, 0.6f), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), 'z');
	//OCEAN FLOOR + PODIUM
	renderer->Draw(ResourceManager::GetTexture("oceanWallTexture"), pCamera, glm::vec3(4.4f + resize, 1.f, 0.f), glm::vec3(0.6f, 0.6f, 0.6f), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), 'z');
	renderPodium->Draw(ResourceManager::GetTexture("oceanFloorTexture"), pCamera, glm::vec3(20.5f, 0.f, 0.f), glm::vec3(10.f, 1.f, 23.f), 0.0f, glm::vec3(), NULL);
}

void Scene::RenderModels()
{
	ModelShader modelShader("modelLoading.vs", "modelLoading.fs");

	modelShader.use();
	glm::mat4 projectionM = pCamera->GetProjectionMatrix();
	glm::mat4 viewM = pCamera->GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projectionM));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(viewM));

	//Draw column Left_Down
	glm::mat4 modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-15.0f, -0.5f, 15.0f));
	modelM = glm::scale(modelM, glm::vec3(0.08f, 0.08f, 0.08f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Column").Draw(modelShader);
	//AABB column
	column_downLeft.m_max = glm::vec3(-15.0f + models->at("Column").m_max.x * 0.08f, 24.0f, 15.0f + models->at("Column").m_max.z * 0.08f);
	column_downLeft.m_min = glm::vec3(-15.0f + models->at("Column").m_min.x * 0.08f, -0.5f, 15.0f + models->at("Column").m_min.z * 0.08f);

	//Draw column Left_Up
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-15.0f, -0.5f, -15.0f));
	modelM = glm::scale(modelM, glm::vec3(0.08f, 0.08f, 0.08f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Column").Draw(modelShader);
	//AABB column
	column_upLeft.m_max = glm::vec3(-15.0f + models->at("Column").m_max.x * 0.08f, 24.0f, -15.0f + models->at("Column").m_max.z * 0.08f);
	column_upLeft.m_min = glm::vec3(-15.0f + models->at("Column").m_min.x * 0.08f, -0.5f, -15.0f + models->at("Column").m_min.z * 0.08f);

	//Draw column Right_Up
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(15.0f, -0.5f, -15.0f));
	modelM = glm::scale(modelM, glm::vec3(0.08f, 0.08f, 0.08f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Column").Draw(modelShader);
	//AABB column
	column_upRight.m_max = glm::vec3(15.0f + models->at("Column").m_max.x * 0.08f, 24.0f, -15.0f + models->at("Column").m_max.z * 0.08f);
	column_upRight.m_min = glm::vec3(15.0f + models->at("Column").m_min.x * 0.08f, -0.5f, -15.0f + models->at("Column").m_min.z * 0.08f);


	//Draw column Right_Down
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(15.0f, -0.5f, 15.0f));
	modelM = glm::scale(modelM, glm::vec3(0.08f, 0.08f, 0.08f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Column").Draw(modelShader);
	//AABB column
	column_downRight.m_max = glm::vec3(15.0f + models->at("Column").m_max.x * 0.08f, 24.0f, 15.0f + models->at("Column").m_max.z * 0.08f);
	column_downRight.m_min = glm::vec3(15.0f + models->at("Column").m_min.x * 0.08f, -0.5f, 15.0f + models->at("Column").m_min.z * 0.08f);


	//////MIDDLE ZONE DRAW
	//Draw Dino1
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-2.0f, 6.f, 0.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::scale(modelM, glm::vec3(0.02f, 0.02f, 0.02f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Dino1").Draw(modelShader);
	middelDino1.m_max = glm::vec3(-2.0f + models->at("Dino1").m_max.x * 0.02f, models->at("Dino1").m_max.y * 0.02f , 0.0f + models->at("Dino1").m_max.z * 0.02f);
	middelDino1.m_min = glm::vec3(-2.0f + models->at("Dino1").m_min.x * 0.02f, 6.0f, 0.0f + models->at("Dino1").m_min.z * 0.08f);

	//Draw Dino2
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(0.0f, 0.3f, 0.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::scale(modelM, glm::vec3(0.15f, 0.15f, 0.15f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Dino2").Draw(modelShader);
	middleDino2.m_max = glm::vec3(0.0f + models->at("Dino2").m_max.x * 0.15f, 0.3f + models->at("Dino2").m_max.y * 0.15f, 0.0f + models->at("Dino2").m_max.z * 0.15f);
	middleDino2.m_min = glm::vec3(0.0f + models->at("Dino2").m_min.x * 0.15f, 0.3f, 0.0f + models->at("Dino2").m_min.z * 0.15f);

	//Draw Grass
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(0.0f, -0.2f, 0.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::scale(modelM, glm::vec3(0.01f, 0.01f, 0.06f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Grass").Draw(modelShader);
	middleTerrain.m_max = glm::vec3(0.0f + models->at("Grass").m_max.x * 0.01f, -0.2f + models->at("Grass").m_max.y * 0.01f, 0.0f + models->at("Grass").m_max.z * 0.06f);
	middleTerrain.m_min = glm::vec3(0.0f + models->at("Grass").m_min.x * 0.01f, -0.2f, 0.0f + models->at("Grass").m_min.z * 0.06f);

	////OCEAN ZONE DRAW
	//Draw Diver
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(18.0f, 0.5f, -6.0f));
	modelM = glm::scale(modelM, glm::vec3(0.8f, 0.8f, 0.8f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Diver").Draw(modelShader);
	//Draw Turtle
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(22.5f, 0.5f, 7.0f));
	modelM = glm::scale(modelM, glm::vec3(0.25f, 0.25f, 0.25f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(250.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Turtle").Draw(modelShader);
	//Draw Crab1
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(20.f, 0.5f, 2.0f));
	modelM = glm::scale(modelM, glm::vec3(0.1f, 0.1f, 0.1f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Crab").Draw(modelShader);
	//Draw Crab2
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(24.f, 0.5f, -2.0f));
	modelM = glm::scale(modelM, glm::vec3(0.1f, 0.1f, 0.1f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Crab").Draw(modelShader);
	//Draw GreenFish1
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(22.0f, 7.0f, -1.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(45.f), glm::vec3(0.f, 0.f, 1.f));
	modelM = glm::scale(modelM, glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("GreenFish").Draw(modelShader);
	//Draw GreenFish2
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(22.0f, 5.0f, -4.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(45.f), glm::vec3(0.f, 0.f, 1.f));
	modelM = glm::scale(modelM, glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("GreenFish").Draw(modelShader);
	//Draw BeautyFish1
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(20.0f, 7.0f, -3.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	//modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("BeautyFish").Draw(modelShader);
	//Draw BeautyFish2
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(21.0f, 3.0f, 1.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	//modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("BeautyFish").Draw(modelShader);
	//Draw BeautyFish3
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(21.0f, 10.0f, 3.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	//modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("BeautyFish").Draw(modelShader);
	//Draw BeautyFish4
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(23.0f, 10.0f, -8.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	//modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("BeautyFish").Draw(modelShader);
	//Draw BeautyFish5
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(23.0f, 3.0f, -10.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	//modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("BeautyFish").Draw(modelShader);
	//Draw BeautyFish6
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(23.0f, 12.0f, -10.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	//modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("BeautyFish").Draw(modelShader);
	//Draw BeautyFish7
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(23.0f, 8.0f, 11.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	//modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("BeautyFish").Draw(modelShader);
	//Draw PinkFish1
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(24.0f, 10.0f, 6.0f));
	modelM = glm::scale(modelM, glm::vec3(0.5f, 0.5f, 0.5f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	//modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("PinkFish").Draw(modelShader);
	//Draw PinkFish2
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(24.0f, 5.0f, 2.0f));
	modelM = glm::scale(modelM, glm::vec3(0.5f, 0.5f, 0.5f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("PinkFish").Draw(modelShader);
	//Draw PinkFish3
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(24.0f, 11.0f, 0.0f));
	modelM = glm::scale(modelM, glm::vec3(0.5f, 0.5f, 0.5f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("PinkFish").Draw(modelShader);
	//Draw Doris1
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(24.0f, 2.0f, 2.0f));
	modelM = glm::scale(modelM, glm::vec3(0.1f, 0.1f, 0.1f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Doris").Draw(modelShader);
	//Draw Doris2
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(24.0f, 4.0f, 12.0f));
	modelM = glm::scale(modelM, glm::vec3(0.1f, 0.1f, 0.1f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Doris").Draw(modelShader);
	//Draw Golden Fish1
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(21.5f, 8.0f, 4.0f));
	modelM = glm::scale(modelM, glm::vec3(0.08f, 0.08f, 0.08f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(-45.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("GoldenFish").Draw(modelShader);
	//Draw Golden Fish2
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(21.5f, 5.0f, 8.0f));
	modelM = glm::scale(modelM, glm::vec3(0.08f, 0.08f, 0.08f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(-45.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("GoldenFish").Draw(modelShader);
	//Draw Golden Fish3
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(20.5f, 3.5f, -1.0f));
	modelM = glm::scale(modelM, glm::vec3(0.08f, 0.08f, 0.08f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(-45.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("GoldenFish").Draw(modelShader);
	//Draw Golden Fish4
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(20.5f, 5.f, -11.0f));
	modelM = glm::scale(modelM, glm::vec3(0.08f, 0.08f, 0.08f));
	modelM = glm::rotate(modelM, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(-45.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("GoldenFish").Draw(modelShader);

	////DESERT ZONE DRAW
	//Draw Lizard
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(5.0f, 5.0f, -23.0f));
	modelM = glm::scale(modelM, glm::vec3(0.1f, 0.1f, 0.1f));
	modelM = glm::rotate(modelM, glm::radians(135.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Lizard").Draw(modelShader);
	////Draw Camel
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(10.0f, 0.5, -20.0f));
	modelM = glm::scale(modelM, glm::vec3(0.01f, 0.01f, 0.01f));
	modelM = glm::rotate(modelM, glm::radians(270.0f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(315.0f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Camel").Draw(modelShader);
	////Draw Desert Mouse
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(3.5f, 0.5f, -23.0f));
	modelM = glm::scale(modelM, glm::vec3(0.1f, 0.1f, 0.1f));
	modelM = glm::rotate(modelM, glm::radians(270.0f), glm::vec3(1.f, 0.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("DesertMouse").Draw(modelShader);
	////Draw Snake
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(4.5f, 0.7f, -18.0f));
	modelM = glm::scale(modelM, glm::vec3(1.0f, 1.0f, 1.0f));
	modelM = glm::rotate(modelM, glm::radians(270.0f), glm::vec3(1.f, 0.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Snake").Draw(modelShader);
	//Draw Strut
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-5.0f, 0.5f, -20.0f));
	modelM = glm::scale(modelM, glm::vec3(0.05f, 0.05f, 0.05f));
	modelM = glm::rotate(modelM, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(315.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Strut").Draw(modelShader);
	////Draw Armadillo
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-10.0f, 0.5f, -18.0f));
	modelM = glm::scale(modelM, glm::vec3(0.025f, 0.025f, 0.025f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(360.f), glm::vec3(0.f, 0.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Armadillo").Draw(modelShader);
	//Draw Desert Cat
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(0.0f, 0.5f, -20.0f));
	modelM = glm::scale(modelM, glm::vec3(0.1f, 0.1f, 0.1f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("DesertCat").Draw(modelShader);
	//Draw Desert Eagle
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(0.0f, 9.5f, -23.0f));
	modelM = glm::scale(modelM, glm::vec3(0.05f, 0.05f, 0.05f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("DesertEagle").Draw(modelShader);
	//Draw Cactus Left
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-10.0f, 0.5f, -15.0f));
	modelM = glm::scale(modelM, glm::vec3(0.05f, 0.05f, 0.05f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Cactus").Draw(modelShader);
	//Draw Cactus right
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(10.0f, 0.5f, -15.0f));
	modelM = glm::scale(modelM, glm::vec3(0.05f, 0.05f, 0.05f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Cactus").Draw(modelShader);


	//Draw mountain/forest animals
	//Draw bear
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-20.0f, 0.5f, -10.0f));
	modelM = glm::scale(modelM, glm::vec3(0.1f, 0.1f, 0.1f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Bear").Draw(modelShader);
	//Draw wolf
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-20.0f, 0.5f, 9.0f));
	modelM = glm::scale(modelM, glm::vec3(0.05f, 0.05f, 0.05f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Wolf").Draw(modelShader);
	//Draw Deer
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-20.0f, 0.5f, 2.0f));
	modelM = glm::scale(modelM, glm::vec3(0.1f, 0.1f, 0.1f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
	modelM = glm::rotate(modelM, glm::radians(315.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Deer").Draw(modelShader);
	//Draw Ibex
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-20.0f, 0.5f, -2.0f));
	modelM = glm::scale(modelM, glm::vec3(0.1f, 0.1f, 0.1f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
	modelM = glm::rotate(modelM, glm::radians(225.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Ibex").Draw(modelShader);
	//Draw fox
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-20.0f, 0.5f, 6.0f));
	modelM = glm::scale(modelM, glm::vec3(0.03f, 0.03f, 0.03f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
	modelM = glm::rotate(modelM, glm::radians(45.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Fox").Draw(modelShader);
	//Draw Veverita
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-17.0f, 0.5f, -6.0f));
	modelM = glm::scale(modelM, glm::vec3(0.03f, 0.03f, 0.03f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Veverita").Draw(modelShader);
	//Draw Dihor
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-17.0f, 0.5f, 0.0f));
	modelM = glm::scale(modelM, glm::vec3(0.03f, 0.03f, 0.03f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Dihor").Draw(modelShader);
	//Draw left tree
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-22.0f, -0.5f, 13.0f));
	modelM = glm::scale(modelM, glm::vec3(0.01f, 0.01f, 0.01f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Tree").Draw(modelShader);
	//Draw right tree
	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-22.0f, -0.5f, -13.0f));
	modelM = glm::scale(modelM, glm::vec3(0.01f, 0.01f, 0.01f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Tree").Draw(modelShader);

}

bool Scene::TeleportingCollWall()
{
	return checkForCollisionWalls(pCamera->GetPosition(), otherWalls);
}

bool Scene::CheckColFloor()
{
	return checkForCollisionObj(pCamera->GetPosition(), ab_floor);
}

bool Scene::CheckCollObj()
{
	return checkForCollisionObj(pCamera->GetPosition(), column_downLeft) ||
		checkForCollisionObj(pCamera->GetPosition(), column_upLeft) ||
		checkForCollisionObj(pCamera->GetPosition(), column_upRight) ||
		checkForCollisionObj(pCamera->GetPosition(), column_downRight) ||
		checkForCollisionObj(pCamera->GetPosition(), middelDino1) ||
		checkForCollisionObj(pCamera->GetPosition(), middleDino2) ||
		checkForCollisionObj(pCamera->GetPosition(), middleTerrain);
}



