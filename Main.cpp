#include <iostream>
#include <string>
#include <vector>

#include "Particle.cpp"
#include "raylib.h"
#include "Settings.h"

bool showVectors = false;

int main() {
	InitWindow((int)windowSize.x, (int)windowSize.y, "particle physics");
	SetTargetFPS(1000);

	std::vector<Particle*> particles;
	int cooldown = GetFPS() / 20;

	while (!WindowShouldClose()) {
		for (auto* particle : particles) {
			particle.Update(particles);
		}

		BeginDrawing();
		ClearBackground(BLACK);

		DrawCircleV(borderCenter, borderRadius, { 32, 40, 53, 255 });
		for (auto& particle : particles) {
			particle.Draw();
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cooldown == 0) {
			cooldown = GetFPS() / 20;
			Color randomColor = { (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255 };
			particles.emplace_back(GetMousePosition(), 10.0f, randomColor);
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			particles.pop_back();
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
			showVectors = !showVectors;
		}
		if (cooldown != 0) cooldown--;

		DrawText((std::to_string(GetFPS()) + " fps").c_str(), 10, 10, 20, WHITE);
		DrawText(("P: " + std::to_string(particles.size())).c_str(), 10, 30, 20, WHITE);
		DrawText(("D: " + std::to_string(showVectors ? 1 : 0)).c_str(), 10, 50, 20, WHITE);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
