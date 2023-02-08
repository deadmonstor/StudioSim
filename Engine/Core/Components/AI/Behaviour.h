#pragma once
#include "Core/Component.h"

#include "Util/Events/Events.h"
#include "Util/Events/AIEvents.h"

#include <map>
#include <Util/Events/EngineEvents.h>

//Type definition for a map that attaches functions to particular types.
typedef std::map<std::type_index, std::function<void(Behaviour* pointer, Griddy::Event*)>> FunctionMap;

//Interface defining AI behaviours. Derive this interface into unique game behaviours.
class Behaviour : public Component
{

//Properties
protected:
	bool initialized = false;
	int32_t eventResponseID = -1;
	FunctionMap map;
	bool isInFSM = false;

//Public Methods
public:
	Behaviour() : isInFSM(false) { map = CreateFunctionMap(); }
	Behaviour(bool isInFSMParam);
	//Function defining a single-shot behaviour
	virtual void Act() {}
	virtual void EventResponse(BehaviourEvent* event);



	void start() override;
	void update() override {}
	void lateUpdate() override {}
	void destroy() override;

	bool GetInitValue() { return initialized; }

//Protected Methods
protected:
	//Initializes a map which assigns a function to a particular event type. Override this in child behaviours.
	virtual FunctionMap CreateFunctionMap()
	{
		FunctionMap map = {};
		map[typeid(OnMouseDown)] =
			[](Behaviour* pointer, Griddy::Event* event)
		{
			dynamic_cast<Behaviour*>(pointer)->ExampleMappedFunction(event);
		};
		return map;
	};
private:
	void ExampleMappedFunction(Griddy::Event* event)
	{
		OnMouseDown* eventCasted = (OnMouseDown*)event;
		//do something with the converted event
	}
};
