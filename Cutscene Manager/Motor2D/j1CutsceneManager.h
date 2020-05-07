#ifndef __j1CUTSCENEMANAGER_H__
#define __j1CUTSCENEMANAGER_H__

#include "j1Module.h"
#include "SDL/include/SDL.h"
#include "p2Point.h"
#include <list>

using namespace std;

enum BlackBarsFases
{
	None,
	FadeIn,
	Drawing,
	FadeOut
};

struct Step
{
	string objective;
	iPoint position;
	iPoint speed;
};

struct CutsceneObject 
{
	list <Step> steps;
	Step current_step;
	bool active;
};

class BlackBars
{
public:
	int alpha;
	SDL_Rect top_rect, down_rect;
	BlackBarsFases fase;
	int bar_height;

	void FadeIn();
	void Draw();
	void FadeOut();
};


class j1CutsceneManager : public j1Module
{
public:

	j1CutsceneManager();
	virtual ~j1CutsceneManager();

	// Called before render is available
	bool Awake(pugi::xml_node& config) { return true; };

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate(float dt) { return true; }

	bool Update(float dt);

	bool PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();
	
	//Start a cutscene
	void StartCutscene(string name);

	//Load the cutscene steps from the xml
	bool LoadSteps(pugi::xml_node node);

	//Make the objective of the step move to the desired position
	void DoCutscene(CutsceneObject& character, iPoint& objective_position);

	//Update positions
	void Movement(Step& step, iPoint& objective_position);


	//Pass to the next step of the cutsecne
	void UpdateStep(CutsceneObject& character);

	//Finish the cutscene
	void FinishCutscene(CutsceneObject& character);

	bool SomethingActive();
	
public:

	BlackBars black_bars;

	pugi::xml_document data;
	pugi::xml_parse_result result;
	pugi::xml_node cutsceneManager;

};

#endif // __j1SCENE_H__