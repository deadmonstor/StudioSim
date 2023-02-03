#include "PlannedBehaviour.h"

PlannedBehaviour::PlannedBehaviour()
{
	isInFSM = false;
	fittestAction = nullptr;
	map = CreateFunctionMap();
}

PlannedBehaviour::PlannedBehaviour(bool isInFSMParam)
{
	isInFSM = isInFSMParam;
	map = CreateFunctionMap();
}

void PlannedBehaviour::destroy()
{
	if (eventResponseID != -1)
	{
		Griddy::Events::unsubscribe(this, &PlannedBehaviour::EventResponse, eventResponseID);
		eventResponseID = -1;
	}



	Component::destroy();
}

void PlannedBehaviour::start()
{
	if (!isInFSM)
	{
		if (eventResponseID == -1)
			eventResponseID = Griddy::Events::subscribe(this, &PlannedBehaviour::EventResponse);
	}
	
	GenerateBehaviourList();

	GenerateEffects();

	initialized = true;

	Component::start();
}

void PlannedBehaviour::EventResponse(BehaviourEvent* event)
{
	if (event->targetBehaviour == this)
	{
		for (auto action : availableActions)
		{
			event->targetBehaviour = action.second.second;
			action.second.second->EventResponse(event);
		}
	}
}

//performs planning and chooses the action with the highest fitness
void PlannedBehaviour::Act()
{
	//planning happens in one go, but it'd be more effective to splice it over time
	WorldAnalysis();
	ActionAnalysis();

	//If the action was found, act the action
	if (fittestAction != nullptr)
	{
		fittestAction->Act();
	}

	//reset fitness values
	for (auto i : availableActions)
	{
		i.second.first = 0;
	}
	//end turn
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
		effects["ExampleEffect"].active = true;
		effects["ExampleEffect"].influencedActions["ExampleAction"].first = 5 - distance;
	}
	else {
		effects["ExampleEffect"].active = false;
	}
	//now the influence grows the smaller "distance" is, but the effect is turned off if its larger than 5

}

//examines effects to find fitness values of available behaviours
void PlannedBehaviour::ActionAnalysis()
{

	//for each effect, add its influence on available actions. 
	for (auto& effect : effects)
	{
		if (effect.second.active)
		{
			for (auto& influence : effect.second.influencedActions)
			{
				//add the influence value to the fitness value
				availableActions[influence.first].first += influence.second.first;
			}
		}
	}
	fittestAction = FindFittestAction();
}

Behaviour* PlannedBehaviour::FindFittestAction()
{
	std::string fitName;
	int highestFitness = -1;

	//Find action with highest fitness
	for (auto& action : availableActions)
	{
		if (action.second.first > highestFitness)
		{
			highestFitness = action.second.first;
			fitName = action.first;
		}
	}
	if (!fitName.empty())
	{
		return availableActions[fitName].second;
	}
	return nullptr;
}

//Create the list of available behaviours
void PlannedBehaviour::GenerateBehaviourList()
{
	//Example behaviour inserted into action list
	availableActions["ExampleAction"] = std::make_pair(0, new Behaviour());

	//example behaviour initializer
	if (availableActions["ExampleAction"].second->GetInitValue() == false)
	{
		availableActions["ExampleAction"].second->start();
	}
}

//Create the list of possible effects
void PlannedBehaviour::GenerateEffects()
{
	//"example" effect is created with an "exampleAction" behaviour as one of its influenced actions.
	effects["ExampleEffect"] = Effect();
	FitAction influence = std::make_pair(0, availableActions["ExampleAction"].second);
	effects["ExampleEffect"].influencedActions["ExampleAction"] = influence;
}


//Removes leftover data making the component ready to delete.
void PlannedBehaviour::CleanUp()
{
	//clear the priority queue
	effects.clear();
	//delete behaviour pointers
	for (auto i : availableActions)
	{
		i.second.second->destroy();
		delete i.second.second;
	}
	availableActions.clear();
}
