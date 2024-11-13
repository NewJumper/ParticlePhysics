#include <vector>

#include "raylib.h"
#include "raymath.h"
#include "Settings.h"

class Particle {
public:
	Vector2 position;
	Vector2 velocity;
	float radius;
	Color color;

	Particle(Vector2 position, float radius, Color color) : position(position), velocity({ 0, 0 }), radius(radius), color(color) {}

	void Update() {
		float restitution = 1.0f;

		// apply gravity
		velocity.y += 3 * GetFrameTime();

		Vector2 prevPos = position;

		// update position based on velocity
		position.x += velocity.x;
		position.y += velocity.y;

		Vector2 dist = { borderCenter.x - position.x, borderCenter.y - position.y};
		float distToCenter = sqrtf(dist.x * dist.x + dist.y * dist.y);
		float speed = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
		if (distToCenter + radius > borderRadius) {
			// vector projection
			float proj = -2 * (velocity.x * dist.x + velocity.y * dist.y) / abs(dist.x * dist.x + dist.y * dist.y);
			Vector2 reflectVector = { proj * dist.x, proj * dist.y };
			velocity = Vector2Add(velocity, reflectVector);
			velocity = Vector2Scale(velocity, restitution);

			position.x = prevPos.x;
			position.y = prevPos.y;
		}
	}

	void Draw() const {
		DrawCircleV(position, radius, color);
		if (showVectors) DrawLine((int)position.x, (int)position.y, (int)(position.x + 30 * velocity.x), (int)(position.y + 30 * velocity.y), color);
	}
};
