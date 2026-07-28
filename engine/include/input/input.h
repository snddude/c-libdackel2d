#pragma once

#include "input/key_code.h"
#include "math/vector2.h"

int input_get_axis(KeyCode negative, KeyCode positive);
Vector2 input_get_vector(KeyCode left, KeyCode right, KeyCode down, KeyCode up);
