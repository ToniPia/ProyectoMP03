#pragma once

// Helpers:

// ---

//* Directional Keys:
enum directionKeys { UP, RIGHT, DOWN, LEFT };

//* Collision System:
struct Point {
	int x, y;

	Point(int pointX, int pointY) { x = pointX; y = pointY; };
};

