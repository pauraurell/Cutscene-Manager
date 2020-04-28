#ifndef __j1CUTSCENEMANAGER_H__
#define __j1CUTSCENEMANAGER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"

enum BlackBarsFases
{
	None,
	FadeIn,
	Drawing,
	FadeOut
};

class j1CutsceneManager : public j1Module
{
public:

	j1CutsceneManager();
	virtual ~j1CutsceneManager();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate(float dt);

	bool Update(float dt);

	bool PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

	//-------------Black Bars Functions-------------//
	void BlackBars_FadeIn();
	void BlackBars_Draw();
	void BlackBars_FadeOut();

private:

	//-------------Black Bars Variables-------------//
	int alpha;
	SDL_Rect top_rect, down_rect;
	BlackBarsFases fase;
};

#endif // __j1SCENE_H__