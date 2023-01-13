#pragma once
#include "Core/Components/AI/Behaviour.h"
#include <queue>

//Pair of fitness value and behaviour
typedef std::pair<int, Behaviour*> FitAction;

class PlannedBehaviour :
    public Behaviour
{
//Internal struct defining effects on the fitness of available behaviours
    struct Effect
    {
        Effect(std::string nameParam) : name(nameParam) {}
        //Name of the effect
        std::string name;

        //Each element contains effect value and the targeted behaviour
        std::vector<FitAction> influencedActions;

        bool active = false;
    };


//Properties:
protected:
    //List of behaviours this planner can use, with their fitness values
    std::vector<FitAction> availableActions;

    //List of effects which affect the fitness of behaviours
    std::vector<Effect> effects;
    
    
//Methods
public:

    void destroy() override;
    void start() override;
    void update() override {}
    void lateUpdate() override{}

    //Read an event to find changes in planning or invoke state transitions.
    void EventResponse(const BehaviourEvent* event) override;

    //performs planning and chooses the action with the highest fitness
    void Act() override;



    //examines the game world to find currently active effects.
    virtual void WorldAnalysis();

    //examines effects to find fitness values of available behaviours
    virtual void ActionAnalysis();

protected:
    //Create the list of available behaviours
    virtual void GenerateBehaviourList();

    //Create the list of possible effects
    virtual void GenerateEffects();

    //Removes leftover data making the component ready to delete.
    void CleanUp();
};

