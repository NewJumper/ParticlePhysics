#include <iostream>
#include <string>
#include <vector>

#include "Particle.cpp"
#include "raylib.h"
#include "Settings.h"

int main() {
	InitWindow((int)windowSize.x, (int)windowSize.y, "particle physics");
	SetTargetFPS(1000);

	std::vector<Particle> particles;
	int cooldown = GetFPS() / 20;

	while (!WindowShouldClose()) {
		for (auto& particle : particles) {
			particle.Update();
		}

		BeginDrawing();
		ClearBackground(BLACK);

		DrawCircleV(borderCenter, borderRadius, { 32, 40, 53, 255 });
		for (auto& particle : particles) {
			particle.Draw();
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && cooldown == 0) {
			cooldown = GetFPS() / 20;
			Color randomColor = { (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255 };
			particles.emplace_back(GetMousePosition(), 10.0f, randomColor);
		}
		if (cooldown != 0) cooldown--;

		DrawText(std::to_string(GetFPS()).c_str(), 10, 10, 20, WHITE);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
