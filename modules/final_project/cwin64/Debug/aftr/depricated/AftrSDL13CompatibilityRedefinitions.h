#pragma once
#ifndef STEAMIE_SDL13_COMPATIBILITY_REFINITIONS_H
#define STEAMIE_SDL13_COMPATIBILITY_REFINITIONS_H

//These are so the mouse selection can work in SDL1.2.13 and
//still compile (but be non-functional) in SDL1.3
//#define SDLK_LCTRL 0
//#define SDLK_LSHIFT 0
//#define SDLK_LALT 0
//#define SDLK_COMMA 0

//These definitions enable the STEAMiE SDL 1.2.13 Compliant code
//to compile when including the SDL 1.3 header files...
//#define SDL_GetKeyState SDL_GetKeyboardState

