#include "sys.h"
#include <vector>
#include <string>
#include "sprite.h"
#include <list>

SDL_Window* mainwindow = nullptr;
SDL_Renderer* renderer = nullptr;

const std::string image_dir = "../art/";
const std::string image_ext = ".bmp";

std::list<Sprite> spriteStack;

Uint8 key_state_cur[512] = {0};
Uint8 key_state_prev[512] = {0};

Vec2 mouse_pos;
Uint32 mouse_buttons = 0, mouse_buttons_prev = 0;

Vec2 camera_pos;

struct SoundData
{
	std::string filename;
	Mix_Chunk* sound;

	SoundData(const char* filename, Mix_Chunk* sound) : filename(filename), sound(sound) {}
	void destroy()
	{
		Mix_FreeChunk(sound);
	}
};

struct MusicData
{
	std::string filename;
	Mix_Music* music_intro;
	Mix_Music* music_loop;

	MusicData(const char* filename, Mix_Music* music_intro, Mix_Music* music_loop) : filename(filename), music_intro(music_intro), music_loop(music_loop) {}
	void destroy()
	{
		Mix_FreeMusic(music_intro);
		Mix_FreeMusic(music_loop);
	}
};

const std::string sound_path = "../sound/";
const std::string sound_ext = ".wav";
const std::string m_intro_ext = "_intro";
const std::string m_loop_ext = "_loop";

MusicData* cur_music = nullptr;

std::vector<SoundData> sound_data;
std::vector<MusicData> music_data;

struct TextureData
{
	std::string filename;
	SDL_Texture* texture;
	int frame_w, frame_h;

	TextureData(const char* fn, SDL_Texture* tex, int w, int h) : filename(fn), texture(tex), frame_w(w), frame_h(h) {}
	void destroy()
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		printf("delete texture\n");
	}
};

bool is_muted = false;

std::vector<TextureData> textureData;

bool initialize(int argc, char* argv[])
{
	int i;
	for(i = 1; i < argc; i++)
	{
		if(argv[i][0] == '-')
		{
			if(argv[i][1] == 'm')
			{
				is_muted = true;
			}
		}
	}

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("error init %s\n", SDL_GetError());
		return false;
	}

	//init sdl mixer
	if(!is_muted)
	{
		if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("error mixer %s\n",Mix_GetError());
			SDL_Quit();
			return false;
		}
	}

	mainwindow = SDL_CreateWindow(	"Transconsciousness", 
									SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									SCREEN_WIDTH, SCREEN_HEIGHT,
									SDL_WINDOW_SHOWN );

	if(!mainwindow)
	{
		printf("error window\n");
		return false;
	}

	renderer = SDL_CreateRenderer(mainwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!renderer)
	{
		printf("error renderer\n");
		return false;
	}

	return true;
}

void shutDown()
{
	for(auto it = textureData.begin(); it != textureData.end(); it++)
	{
		it->destroy();
	}
	textureData.clear();

	for(auto it = sound_data.begin(); it != sound_data.end(); it++)
	{
		it->destroy();
	}
	sound_data.clear();

	for(auto it = music_data.begin(); it != music_data.end(); it++)
	{
		it->destroy();
	}
	music_data.clear();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(mainwindow);

	SDL_Quit();
}

void clearScreen()
{
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0x0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void flipScreen()
{
	SDL_RenderPresent(renderer);
}

int loadTexture(const char* filename, int frame_w, int frame_h)
{
	SDL_Texture* texture = nullptr;

	int temp_id = getTexture(filename);
	if(temp_id >= 0)
	{
		return temp_id;
	}

	std::string path = image_dir;
	path += filename;
	path += image_ext;
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	if(!surface)
	{
		printf("error loading %s\n", filename);
		return -1;
	}
	
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0x0, 0xFF));
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!texture)
	{
		printf("error texture %s\n", filename);
		return -1;
	}

	SDL_FreeSurface(surface);

	//push texture
	temp_id = textureData.size();
	textureData.push_back(TextureData(filename, texture, frame_w, frame_h));
	printf("texture %d %s %d %d\n", temp_id, filename, frame_w, frame_h);

	return temp_id;
}

int getTexture(const char* filename)
{
	unsigned int i;
	for(i = 0; i < textureData.size(); i++)
	{
		if(textureData[i].filename.compare(filename)==0)
		{
			return i;
		}
	}

	return -1;
}

SDL_Texture* getTextureData(int tex_id, int* frame_w, int* frame_h)
{
	if(tex_id < 0) return nullptr;

	TextureData& td = textureData[tex_id];

	if(frame_w) *frame_w = td.frame_w;
	if(frame_h) *frame_h = td.frame_h;

	return td.texture;
}

void beginSprites()
{
	spriteStack.clear();
}

void pushSprite(Sprite& spr)
{
	//spr.draw();
	spriteStack.push_back(spr);
}

void endSprites()
{
	spriteStack.sort([](const Sprite& s1, const Sprite& s2) {
		return s1.pos.y < s2.pos.y;
	});

	for(auto it = spriteStack.begin(); it != spriteStack.end(); it++)
	{
		it->draw();
	}

}


//input
void updateInput()
{
	memcpy(key_state_prev, key_state_cur, 512);
	const Uint8* tmp = SDL_GetKeyboardState(nullptr);
	memcpy(key_state_cur, tmp, 512);

	int mouse_x,  mouse_y;
	mouse_buttons_prev = mouse_buttons;
	mouse_buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
	mouse_pos.setElements((float)mouse_x, (float)mouse_y);
}

bool isKeyDown(int k)
{
	return key_state_cur[k];
}

bool isKeyUp(int k)
{
	return !key_state_cur[k];
}

bool isKeyPressed(int k)
{
	return key_state_cur[k] && !key_state_prev[k];
}

bool isKeyReleased(int k)
{
	return !key_state_cur[k] && key_state_prev[k];
}

bool isButtonDown(int b)
{
	return mouse_buttons & b;
}

bool isButtonUp(int b)
{
	return !(mouse_buttons & b);
}

bool isButtonPressed(int b)
{
	return (mouse_buttons & b) && !(mouse_buttons_prev & b);
}

bool isButtonReleased(int b)
{
	return !(mouse_buttons & b) && (mouse_buttons_prev & b);
}

void convTilePos(const Vec2 pos, int tile_size, Vec2* tile_p)
{
	if(!tile_p) return;

	int half_ts = tile_size/2;

	int tempx = (int)(pos.x+half_ts) / tile_size;
	int tempy = (int)(pos.y+half_ts) / tile_size;

	tile_p->setElements((float)tempx, (float)tempy);
}

SpriteDirection radianToSpriteDirection(float rad)
{
	float q_pi = M_PI / 4;

	if(abs(rad - 0) <= q_pi)
	{
		return RIGHT_DOWN;
	}
	else if(abs(rad - M_PI/2) <= q_pi)
	{
		return LEFT_DOWN;
	}
	else if(abs(rad - M_PI) <= q_pi)
	{
		return LEFT_UP;
	}
	else //if(abs(rad - 3*M_PI/2) <= q_pi)
	{
		return RIGHT_UP;
	}
}



bool loadSound(const char* filename)
{
	if(is_muted) return false;

	std::string path = sound_path + filename + sound_ext;
	Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
	if(!sound)
	{
		printf("error sound %s\n", filename);
		return false;
	}

	printf("sound %s\n", filename);

	sound_data.push_back(SoundData(filename, sound));
	return true;
}

bool loadMusic(const char* filename)
{
	if(is_muted) return false;

	std::string path = sound_path + filename + m_intro_ext + sound_ext;
	Mix_Music* intro = Mix_LoadMUS(path.c_str());
	if(!intro)
	{
		printf("error intro %s\n", filename);
		return false;
	}
	path = sound_path + filename + m_loop_ext + sound_ext;
	Mix_Music* loop = Mix_LoadMUS(path.c_str());
	if(!loop)
	{
		printf("error intro %s\n", filename);
		return false;
	}
	printf("music %s\n",filename);

	music_data.push_back(MusicData(filename, intro, loop));
	return true;
}

void playSound(const char* filename)
{
	if(is_muted) return;

	int i;
	for(i = 0; i < sound_data.size(); i++)
	{
		SoundData* data = &sound_data[i];

		if(data->filename.compare(filename)==0)
		{
			Mix_PlayChannel(-1, data->sound, 0);
		}
	}
}

static bool is_looping = false;

void playMusic(const char* filename)
{
	if(is_muted) return;

	Mix_HaltMusic();

	int i;
	for(i = 0; i < music_data.size(); i++)
	{
		MusicData* data = &music_data[i];

		if(data->filename.compare(filename)==0)
		{
			Mix_PlayMusic(data->music_intro, 0);
			cur_music = data;
			is_looping = false;
		}
	}
}

void updateMusic()
{
	if(is_muted) return;

	if(!is_looping && cur_music)
	{
		if(!Mix_PlayingMusic())
		{
			Mix_PlayMusic(cur_music->music_loop, -1);
			is_looping = true;
		}
	}
}

bool isMusicPlaying(const char* filename)
{
	if(is_muted) return false;
	if(!cur_music) return false;

	return (cur_music->filename.compare(filename)==0);
}
