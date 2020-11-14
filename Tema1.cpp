#include "Tema1.h"
#include <vector>
#include <iostream>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include "Defines.h"
#include <cstdlib>
#include <ctime>

#define current_arrow arrow_projectils[i]
#define current_balloon balloons[i]

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}



void Tema1::Init()
{

	window->SetSize(init_window_width, init_window_height);
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);




	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = init_player_height;

	// computing dependencies
	this->game_area_height = init_window_height - init_scoreboard_height - init_powerbar_height;
	this->game_area_width = init_window_width;
	player_min_y = init_powerbar_height;
	player_max_y = game_area_height - init_player_height + init_powerbar_height;


	// player
	corner = glm::vec3(0, 0, 0);
	Mesh* player = Object2D::CreatePlayer("player", corner, squareSide, glm::vec3(0, 1, 1), false);
	AddMeshToList(player);

	// arrow trigger
	corner = glm::vec3(0, 0, 0);
	Mesh* arrow = Object2D::CreateArrow("arrow", corner, squareSide, glm::vec3(0, 1, 1), false);
	AddMeshToList(arrow);


	// game area
	corner = glm::vec3(0, init_powerbar_height, 0);
	Mesh* gameActionArea = Object2D::CreateRectangle("game_area", corner, this->game_area_width, this->game_area_height, glm::vec3(0.1f, 0.1f, 0.1f), true);
	AddMeshToList(gameActionArea);


	// arrow projectils
	corner = glm::vec3(0, 0, 0);
	for (int i = 0; i < max_arrow_instances; i++) {
		Mesh* arroww = Object2D::CreateArrow("arrows" + i, corner, squareSide, glm::vec3(1, 0, 0.1f), false);
		AddMeshToList(arroww);
	}


	corner = glm::vec3(0, 0, 0);
	for (int i = 0; i < max_balloon_instances; i++) {
		Mesh* balloonss;
		if (i % 2 == 0) {
			balloonss = Object2D::CreateBalloon("balloons" + i, corner, squareSide / 2, glm::vec3(1, 0.5f, 0.1f), false);
			balloons[i].isRed = false;
		}
		else {
			balloonss = Object2D::CreateBalloon("balloons" + i, corner, squareSide / 2, glm::vec3(1, 0, 0), false);
			balloons[i].isRed = true;
		}
		AddMeshToList(balloonss);
	}

	srand((unsigned int)time(NULL));
	begin = clock();
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{

	// TODO draw player
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(player_position.x, player_position.y);
	RenderMesh2D(meshes["player"], shaders["VertexColor"], modelMatrix);

	// TODO draw arrow
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(player_position.x, player_position.y + (init_player_height / 2));
	modelMatrix *= Transform2D::Rotate(arrow_angle);
	RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);



	// TODO draw arrow projectils
	for (int i = 0; i < max_arrow_instances; i++) {
		// draw existing arrow projectiles
		if (current_arrow.isOutOfScreen == false) {
			arrow_projectils[i].moveAndUpdatePosition();
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(current_arrow.pos.x, current_arrow.pos.y);
			modelMatrix *= Transform2D::Rotate(current_arrow.angle);
			RenderMesh2D(meshes["arrows" + i], shaders["VertexColor"], modelMatrix);

			// check for screen exit
			if (current_arrow.checkIfOutOfScreen()) {
				current_arrow.isOutOfScreen = true;
			}
		}
	}


	// TODO draw baloons and check for collision
	for (int i = 0; i < max_balloon_instances; i++) {
		// draw exiting balloons
		if (!current_balloon.isOutOfScreen) {

			current_balloon.climbUp();
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(current_balloon.position.x, current_balloon.position.y);
			RenderMesh2D(meshes["balloons" + i], shaders["VertexColor"], modelMatrix);

			// check if them exited the screen
			if (current_balloon.isOutOfScreenCheck()) {
				current_balloon.isOutOfScreen = true;
			}

			// check for collision
			for (int ii = 0; ii < max_arrow_instances; ii++) {
				Position arrowPos = arrow_projectils[ii].pos;
				float arrow_lenght = init_player_height * (1.0f + (glm::sqrt(3) / 20.0f));
				
				// arrow top position now
				// translated with ellipse center to origin, plus half of ellipse because center of ellipse was set be me being on bottom
				float arrow_top_x = arrowPos.x + arrow_lenght * cos(arrow_projectils[ii].angle) - current_balloon.position.x;
				float arrow_top_y = arrowPos.y + arrow_lenght * sin(arrow_projectils[ii].angle) - current_balloon.position.y - (init_player_height / 2);

				float a = (0.7f) * (init_player_height / 2.0);
				float b = init_player_height / 2.0;

				if (((arrow_top_x * arrow_top_x) / (a * a)) + ((arrow_top_y * arrow_top_y) / (b * b)) <= 1) {
					// collision
					cout << "collision" << endl;
				}

			}

		}
		else {
			// maybe add them 
			end = clock();
			if (double(end - begin) / CLOCKS_PER_SEC > balloon_respawn_time) {
				int randNum = rand() % (init_window_width - balloon_start_width + 1) + balloon_start_width;
				current_balloon.resetPosition(randNum);
				current_balloon.isOutOfScreen = false;
				begin = end;
			}
			
		}
	}

	// TODO draw scoreboard
	RenderMesh2D(meshes["game_area"], shaders["VertexColor"], glm::mat3(1));

	// TODO draw lifebar


	

}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W))
	{
		Position old = this->player_position;
		this->player_position.setValue(old.x, glm::min(old.y + player_y_step, player_max_y));
	}
	if (window->KeyHold(GLFW_KEY_S))
	{
		Position old = this->player_position;
		this->player_position.setValue(old.x, glm::max(old.y - player_y_step, player_min_y));
	}

}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	mouse_x = mouseX;
	mouse_y = init_window_height - mouseY;
	int center_x = player_position.x;
	int center_y = player_position.y + (init_player_height / 2);
	float tangent = ((center_y - mouse_y) * 1.0f) / (center_x - mouse_x);
	arrow_angle =  glm::atan(tangent);
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (window->MouseHold(GLFW_MOUSE_BUTTON_1)) {
		int arrow_target = -1;
		for (int i = 0; i < max_arrow_instances; i++) {
			if (current_arrow.isOutOfScreen) {
				arrow_target = i;
				break;
			}
		}

		// strike an arrow
		if (arrow_target != -1) {
			arrow_projectils[arrow_target].angle = arrow_angle;
			arrow_projectils[arrow_target].origin_position.x = player_position.x;
			arrow_projectils[arrow_target].origin_position.y = player_position.y + init_player_height / 2;
			arrow_projectils[arrow_target].isOutOfScreen = false;
			arrow_projectils[arrow_target].distance_from_origin = 0;
			arrow_projectils[arrow_target].step_distance = arrow_x_step;

		}
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

