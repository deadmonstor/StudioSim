#include "PlannedBehaviour.h"

void PlannedBehaviour::destroy()
{
	if (eventResponseID != -1)
	{
		Griddy::Events::unsubscribe(this, &PlannedBehaviour::EventResponse, eventResponseID);
		eventResponseID = -1;
	}

	CleanUp();

	Component::destroy();
}

void PlannedBehaviour::start()
{
	if (eventResponseID == -1)
		eventResponseID = Griddy::Events::subscribe(this, &PlannedBehaviour::EventResponse);

	GenerateBehaviourList();

	GenerateEffects();

	initialized = true;

	Component::start();
}

//Read an event to find changes in planning or invoke state transitions.
void PlannedBehaviour::EventResponse(const BehaviourEvent* event)
{
	if (event->targetBehaviour == this)
	{
		LOG_INFO("PlannedBehaviour receives event");
		//find change in behaviour, or invoke an event with state transition
		//continue here....
	}
}

//performs planning and chooses the action with the highest fitness
void PlannedBehaviour::Act()
{
	//for the moment, planning happens in one go, but it'd be more effective to splice it over time
	WorldAnalysis();
	ActionAnalysis();
	int fitIndex = -1;
	int highestFitness = 0;
	for (int i = 0; i < availableActions.size(); i++)
	{
		if (availableActions[i].first > highestFitness)
		{
			highestFitness = availableActions[i].first;
			fitIndex = i;
		}
	}
	if (fitIndex > 0)
	{
		availableActions[fitIndex].second->Act();
	}

	//reset fitness values
	for (auto i : availableActions)
	{
		i.first = 0;
	}
}


//examines the game world to find current effects.
void PlannedBehaviour::WorldAnalysis()
{
	//EXAMPLE IMPLEMENTATION:
	int distance = 2;

	//if distance to target is less than 5, etc...
	if (distance <= 5)
	{
		//changes the example effect to active, and changes the influence
		effects[0].active = true;
		effects[0].influencedActions[0].first = 5 - distance;
	}
	else {
		effects[0].active = false;
	}
	//now the influence grows the smaller "distance" is, but the effect is turned off if its larger than 5

}

//examines effects to find fitness values of available behaviours
void PlannedBehaviour::ActionAnalysis()
{
	//A LOT OF LOOPS. Need to work on this. Could be optimized with hash lookups?

	//for each effect, add its influence on available actions. 
	for (auto effect : effects)
	{
		for (auto influence : effect.influencedActions)
		{
			for (auto action : availableActions)
			{
				if (action.second == influence.second)
				{
					action.first += influence.first;
				}
			}
		}
	}
}

//Create the list of available behaviours
void PlannedBehaviour::GenerateBehaviourList()
{
	//Example behaviour inserted into action list
	availableActions.push_back(std::make_pair(0, new Behaviour()));


	//initializes the behaviours
	for (auto i : availableActions)
	{
		if (i.second->GetInitValue() == false)
		{
			i.second->start();
		}
	}
}

//Create the list of possible effects
void PlannedBehaviour::GenerateEffects()
{
	Effect e = Effect("example");
	FitAction influence = std::make_pair(1, availableActions[0].second);
	e.influencedActions.push_back(influence);
}


//Removes leftover data making the component ready to delete.
void PlannedBehaviour::CleanUp()
{
	//clear the priority queue
	effects.clear();
	//delete behaviour pointers
	for (auto i : availableActions)
	{
		i.second->destroy();
		delete i.second;
	}
	availableActions.clear();
}
