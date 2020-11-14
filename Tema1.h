#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "utils/Position.h"
#include "Defines.h"
#include "utils/Arrow.h"
#include "utils/Balloon.h"
#include <ctime>


class Tema1 : public SimpleScene {
	public:
		Tema1();
		~Tema1();
		void Init() override;


	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

protected:
	Position player_position = Position(init_player_x, init_player_y);
	glm::mat3 modelMatrix;
	int game_area_height;
	int game_area_width;
	int player_min_y;
	int player_max_y;
	int mouse_x;
	int mouse_y;
	float arrow_angle;

	clock_t begin;
	clock_t end;
	
	Arrow arrow_projectils[max_arrow_instances];
	Balloon balloons[max_balloon_instances];
};