/*
Copyright 2019 Jared Mackey

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define EE_HANDS

// The lily's encoder is flipped and is low res
#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTION 2

// Put in to save some space on flash
#define NO_DEBUG
#define NO_PRINT

// Makes MT keys respond faster
#define IGNORE_MOD_TAP_INTERRUPT

