#pragma once

struct Vector2i {
	int x, y;
};

inline Vector2i operator/(const Vector2i& first, int second) { return { first.x / second, first.y / second }; };