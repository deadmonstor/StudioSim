#pragma once
#include <map>
#include "Core/Components/AI/Behaviour.h"

//Pair of fitness value and behaviour
typedef std::pair<int, Behaviour*> FitAction;

class PlannedBehaviour :
    public Behaviour
{
protected:
//Internal struct defining effects on the fitness of available behaviours
    struct Effect
    {
        //Each element contains effect value and the targeted behaviour
        std::unordered_map<std::string, FitAction> influencedActions;

        bool active = false;
    };


//Properties:
protected:
    //Dictionary of behaviours this planner can use, with their fitness values. Map is searched by name string
    std::unordered_map<std::string, FitAction> availableActions;

    //Dictionary of effects which affect the fitness of behaviours. Searched by name.
    std::unordered_map<std::string, Effect> effects;
   
    Behaviour* fittestAction;

//Methods
public:
    PlannedBehaviour();
    PlannedBehaviour(bool isInFSMParam);
    void destroy() override;
    void start() override;
    void update() override {}
    void lateUpdate() override{}

    void EventResponse(BehaviourEvent* event) override;

    //performs planning and chooses the action with the highest fitness
    void Act() override;



    //examines the game world to find currently active effects.
    virtual void WorldAnalysis();

    //examines effects to find fitness values of available behaviours
    virtual void ActionAnalysis();

    //Examines the fittness values to find the most fit action
    Behaviour* FindFittestAction();

protected:

    //Create and initialize behaviours
    virtual void GenerateBehaviourList();

    //Create the list of possible effects
    virtual void GenerateEffects();

    //Removes leftover data making the component ready to delete.
    void CleanUp();

    FunctionMap CreateFunctionMap() override
    {
        FunctionMap map = {};
        map[typeid(OnMouseDown)] =
            [](Behaviour* pointer, Griddy::Event* event)
        {
            dynamic_cast<PlannedBehaviour*>(pointer)->ExampleMappedFunction(event);
        };
        return map;
    }

private:
    void ExampleMappedFunction(Griddy::Event* event)
    {
        OnMouseDown* eventCasted = (OnMouseDown*)event;
        //do something with the converted event
    }
};

