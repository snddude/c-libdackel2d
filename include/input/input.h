#pragma once

#include "input/key_code.h"

#include <vec2.h>

int input_get_axis(key_code_t negative, key_code_t positive);
vec2i_t input_get_vector(key_code_t left, key_code_t right, key_code_t down, key_code_t up);
