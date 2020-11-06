#include "Tema1.h"
#include <vector>
#include <iostream>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include "Defines.h"


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

	// arrow
	corner = glm::vec3(0, 0, 0);
	Mesh* arrow = Object2D::CreateArrow("arrow", corner, squareSide, glm::vec3(0, 1, 1), false);
	AddMeshToList(arrow);


	// game area
	corner = glm::vec3(0, init_powerbar_height, 0);
	Mesh* gameActionArea = Object2D::CreateRectangle("game_area", corner, this->game_area_width, this->game_area_height, glm::vec3(0.1f, 0.1f, 0.1f), true);
	AddMeshToList(gameActionArea);



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


	// TODO draw scoreboard
	RenderMesh2D(meshes["game_area"], shaders["VertexColor"], glm::mat3(1));

	// TODO draw lifebar


	// TODO draw objects
	

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
	mouse_y = mouseY;

	int center_x = player_position.x;
	int center_y = player_position.y + (init_player_height / 2);

	float tangent = ((center_y - mouseY) * 1.0f) / (center_x - mouseX);
	arrow_angle = (-1) *  glm::atan(tangent);
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
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

