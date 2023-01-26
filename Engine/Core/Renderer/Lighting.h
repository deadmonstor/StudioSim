#pragma once
#include <list>

#include "Aixlog.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/RenderEvents.h"

enum class LightUpdateRequest
{
	Color = 1,
	Falloff = 2,
	Position = 4,
	All = Color | Falloff | Position,
};

DEFINE_ENUM_FLAG_OPERATORS(LightUpdateRequest);

class Lighting : public SingletonTemplate<Lighting>
{
public:
	void init();
	void addToLightQueue(const OnLightComponentStarted*);
	void removeFromLightQueue(const OnLightComponentRemoved*);
	void refreshLightData(LightUpdateRequest lightUpdateRequest) const;
	void doLight(const SpriteComponent* spriteRenderer,
	             int& i,
	             const glm::vec2& position,
	             const glm::vec4& lightColorBase,
	             const glm::vec3& falloff,
	             LightUpdateRequest lightUpdateRequest) const;
	void refreshLightData(SpriteComponent* spriteRenderer, LightUpdateRequest lightUpdateRequest) const;
	void onDebugEvent(const OnDebugEventChanged* event);

	[[nodiscard]] const glm::vec4& getAmbientColor() const { return ambientColor; }
	void setAmbientColor(const glm::vec4& _ambientColor) { this->ambientColor = _ambientColor; }
private:
	std::list<Light*> lightRenderQueue;
	glm::vec4 ambientColor = {0.0f, 0.0f, 0.0f, 1.0f};
	bool showMouseLight = false;
	bool debugLightColor = false;
};

struct LightName
{
	LightName(const char* _pos, const char* _color, const char* _falloff)
	{
		auto res = new char[strlen(_pos)+1];
		strcpy_s(res, strlen(_pos)+1, _pos);
		pos = res;

		res = new char[strlen(_color)+1];
		strcpy_s(res, strlen(_color)+1, _color);
		color = res;

		res = new char[strlen(_falloff)+1];
		strcpy_s(res, strlen(_falloff)+1, _falloff);
		falloff = res;
	}

	char* pos;
	char* color;
	char* falloff;
};