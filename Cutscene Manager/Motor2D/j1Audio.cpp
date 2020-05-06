#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

j1Audio::j1Audio() : j1Module()
{
	music = NULL;
	name.create("audio");
}

// Destructor
j1Audio::~j1Audio()
{}



bool j1Audio::Awake(pugi::xml_node & config)
{

	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		active = false;
		ret = true;
	}

	// load support for the JPG and PNG image formats
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		active = false;
		ret = true;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		active = false;
		ret = true;
	}

	return ret;
}

// Called before quitting
bool j1Audio::CleanUp()
{
	if(!active)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if(music != NULL)
	{
		Mix_FreeMusic(music);
	}

	for (int i = 0; i < fx.size(); i++) {
		Mix_FreeChunk(fx[i]);
	}

	fx.clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

bool j1Audio::Update(float dt) {
	if (musicToFree && !Mix_PlayingMusic()) {
		Mix_FreeMusic(music);
		music = nullptr;
		musicToFree = false;
	}
	return true;
}

// Play a music file
bool j1Audio::PlayMusic(const char* path, float fade_time)
{
	//Mix_VolumeMusic(128 * volumemusic);
	bool ret = true;

	if(!active)
		return false;

	if(music != NULL)
	{
		Mix_HaltMusic();

		Mix_FreeMusic(music);
	}

	p2SString tmp("%s%s", music_directory.GetString(), path);

	music = Mix_LoadMUS(tmp.GetString());

	if(music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());

		ret = false;
	}
	else
	{
		if(fade_time > 0.0f)
		{
			if(Mix_FadeInMusic(music, -1, (int) (fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());

				ret = false;
			}
		}
		else
		{
			if(Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play music %s. Mix_GetError(): %s", path, Mix_GetError());

				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);

	return ret;
}

void j1Audio::PauseMusic(float fade_time)
{
	if (music != nullptr)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic(int(fade_time * 900.0f));
			musicToFree = true;
		}
		else
		{
			Mix_HaltMusic();
		}
	}
}


// Load WAV
unsigned int j1Audio::LoadFx(const char* path)
{
	unsigned int ret = 0;

	if (!active)
		return 0;

	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());

	}
	else
	{
		fx.push_back(chunk);
		ret = fx.size();
	}

	return ret;
}

// Play WAV
bool j1Audio::PlayFx(int channel, unsigned int id, int repeat)
{
	bool ret = false;

	if (!active)
		return false;

	if (id > 0 && id <= fx.size())
	{
		if (fx[id - 1] != nullptr) Mix_PlayChannel(channel, fx[id - 1], repeat);
		else LOG("Could not play audio because there is no fx.");
		//Mix_VolumeChunk(fx[id - 1], (volumefx*128));
	}

	return ret;
}


void j1Audio::StopFx() {
	Mix_HaltChannel(-1);

}
bool j1Audio::channelFinished() {
	bool ret = false;
		return ret;
}

bool j1Audio::Save(pugi::xml_node& data) const
{
	pugi::xml_node music = data.append_child("volumemusic");
	pugi::xml_node fx = data.append_child("volumefx");
	music.append_attribute("value") = volumemusic;
	fx.append_attribute("value") = volumefx;
	return true;
}

bool j1Audio::Load(pugi::xml_node& data)
{
	volumemusic = data.child("volumemusic").attribute("value").as_float();
	volumefx = data.child("volumefx").attribute("value").as_float();
	return true;
}
void j1Audio::musicvolume(float value) {
	volumemusic = value;
	Mix_VolumeMusic(128 * volumemusic);
}

float j1Audio::fxvolume(float value) {
	volumefx = value;
	return volumefx;
}

void j1Audio::SetChannelVolume(int channel, int volume)
{
	Mix_Volume(channel, volume);
}

