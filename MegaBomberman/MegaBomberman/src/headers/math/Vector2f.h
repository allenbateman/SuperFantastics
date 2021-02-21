#pragma once

struct Vector2f {
	float x, y;
};

inline void operator*=(Vector2f& origin, float value) { origin.x *= value; origin.y *= value; }
inline void operator-=(Vector2f& origin, float value) { origin.x -= value; origin.y -= value; }