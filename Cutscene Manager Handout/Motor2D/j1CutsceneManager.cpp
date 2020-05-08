#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1CutsceneCharacters.h"
#include "j1CutsceneManager.h"


j1CutsceneManager::j1CutsceneManager() : j1Module()
{
	name.create("cutscene");
}

// Destructor
j1CutsceneManager::~j1CutsceneManager()
{}


// Called before the first frame
bool j1CutsceneManager::Start()
{
	black_bars.fase = None;
	black_bars.alpha = 0;
	int bar_height = 100;

	black_bars.top_rect.x = 0;
	black_bars.top_rect.y = 0;
	black_bars.top_rect.w = App->win->width;
	black_bars.top_rect.h = bar_height;

	black_bars.down_rect.x = 0;
	black_bars.down_rect.y = App->win->height - bar_height;
	black_bars.down_rect.w = App->win->width;
	black_bars.down_rect.h = bar_height;

	result = data.load_file("CutsceneEditor.xml");
	cutsceneManager = data.document_element();

	LOG("Starting Cutscene Manager");

	return true;
}

// Called each loop iteration
bool j1CutsceneManager::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool j1CutsceneManager::PostUpdate(float dt)
{

	//Black Bars Drawing
	switch (black_bars.fase)
	{
	case FadeIn:
		black_bars.FadeIn();
		break;
	case Drawing:
		black_bars.Draw();
		break;
	case FadeOut:
		black_bars.FadeOut();
		break;
	}
	return true;
}

// Called before quitting
bool j1CutsceneManager::CleanUp()
{

	return true;
}

void BlackBars::FadeIn()
{
	//TODO 5.2: Complete this function doing a smooth fade in raising the value of the alpha 
	// (alpha = 0: invisible, alpha = 255: Completely black)

}

void BlackBars::Draw()
{
	//TODO 5.1: Draw both quads unsing the alpha variable. Both rects are (top_rect and down_rect) already 
	// created, you just have to draw them.

}

void BlackBars::FadeOut()
{
	//TODO 5.2: Similar to fade out

}

void j1CutsceneManager::StartCutscene(string name)
{
	if (!SomethingActive())
	{
		for (pugi::xml_node cutscene = cutsceneManager.child("cutscene"); cutscene; cutscene = cutscene.next_sibling("cutscene"))
		{
			if (cutscene.attribute("name").as_string() == name)
			{
				LoadSteps(cutscene);

				if (black_bars.fase == None) { black_bars.fase = FadeIn; }
			}
		}
		if (App->characters->player.active) {App->characters->player.UpdateStep(); }
		if (App->characters->character1.active) {App->characters->character1.UpdateStep(); }
		if (App->characters->character2.active) { App->characters->character2.UpdateStep(); }
		if (App->render->cinematic_camera.active) { App->render->cinematic_camera.UpdateStep(); }
	}
}

bool j1CutsceneManager::LoadSteps(pugi::xml_node node)
{
	//TODO 1: Check the structure of the Cutscene Editor xml and fill this function. You just have to get the attributes from
	// the xml and push the step to the list of the correspondent Cutscene Object depending on its objective and set the active 
	// bool to true of each loaded Cutscene Object.
	

	return true;
}

void j1CutsceneManager::DoCutscene(CutsceneObject &character, iPoint &objective_position)
{
	Step step = character.current_step;

	if(character.active)
	{

		Movement(step, objective_position);

		//TODO 4: This todo is very easy, just check if the object position is equal to the last position of the cutscene and if it 
		// is call the FinishCutscene function. If it has reached the step.position but it is not the last one just call the Update step 
		// function you've just made right before.
		
		
	}
}

void j1CutsceneManager::Movement(Step &step, iPoint &objective_position)
{
	//TODO 2: Now we want to move the object to the destiny point. To do that compare the object postion with the position
	// we want to reach and move it with the speed values.


}


void CutsceneObject::UpdateStep()
{
	//TODO 3: Now that the object will move wherever we want, we have to call this function every time the object reaches a point.
	// To do this, in this function you just have to update the current_step value with the next step in the list.

	
}

void j1CutsceneManager::FinishCutscene(CutsceneObject& character)
{
	character.steps.clear();
	character.active = false;
	App->characters->input = true;

	if (black_bars.fase == Drawing) { black_bars.fase = FadeOut; }
}

bool j1CutsceneManager::SomethingActive()
{
	bool ret;
	if (App->characters->player.active || App->characters->character1.active || App->characters->character2.active){ret = true;}
	else { ret = false; }
	return ret;
}
