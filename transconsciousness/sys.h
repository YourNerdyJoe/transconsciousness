#ifndef _SYS_H_
#define _SYS_H_
#include <stdio.h>
#include <SDL.h>
#include "vec2.h"
#include <SDL_mixer.h>

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

enum SpriteDirection {
	RIGHT_DOWN = 0,
	LEFT_DOWN,
	LEFT_UP,
	RIGHT_UP,
};

extern SDL_Window* mainwindow;
extern SDL_Renderer* renderer;

extern Uint8 key_state_cur[512];
extern Uint8 key_state_prev[512];

extern Vec2 mouse_pos;
extern Uint32 mouse_buttons, mouse_buttons_prev;

extern Vec2 camera_pos;

bool initialize(int argc, char* argv[]);
void shutDown();

void clearScreen();
void flipScreen();

int loadTexture(const char* filename, int frame_w, int frame_h);
int getTexture(const char* filename);
SDL_Texture* getTextureData(int tex_id, int* frame_w, int* frame_h);

class Sprite;

void beginSprites();
void pushSprite(Sprite& spr);
void endSprites();

void updateInput();

bool isKeyDown(int k);
bool isKeyUp(int k);
bool isKeyPressed(int k);
bool isKeyReleased(int k);

bool isButtonDown(int b);
bool isButtonUp(int b);
bool isButtonPressed(int b);
bool isButtonReleased(int b);

inline Vec2& getMousePos() { return mouse_pos; }

inline Vec2& getCamera() { return camera_pos; }

void convTilePos(const Vec2 pos, int tile_size, Vec2* tile_p);

SpriteDirection radianToSpriteDirection(float rad);

bool loadSound(const char* filename);
bool loadMusic(const char* filename);

void playSound(const char* filename);
void playMusic(const char* filename);

void updateMusic();

#endif
