#ifndef __j1CutsceneCharacters_H__
#define __j1CutsceneCharacters_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1CutsceneManager.h"
#include <list>
using namespace std;

using namespace std;

struct CutsceneObject;

class j1CutsceneCharacters :public j1Module
{
public:

	j1CutsceneCharacters();
	~j1CutsceneCharacters();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate(float dt);

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

	//Checks if any of the quads is doing a cutscene
	void CutsceneListener();

public:

	iPoint player_pos;
	iPoint character1_pos;
	iPoint character2_pos;

	CutsceneObject player;
	CutsceneObject character1;
	CutsceneObject character2;
	
	bool input;
};

#endif
