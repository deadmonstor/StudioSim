#pragma once
#include <map>
#include <vector>

#include "glm/vec2.hpp"

class Pivot
{
public:
	inline static glm::vec2 BottomLeft = glm::vec2(0.0, 0.0);
	inline static glm::vec2 BottomCenter = glm::vec2(0.5, 0.0);
	inline static glm::vec2 BottomRight = glm::vec2(1.0, 0.0);
	inline static glm::vec2 TopLeft = glm::vec2(0.0, 1.0);
	inline static glm::vec2 TopCenter = glm::vec2(0.5, 1.0);
	inline static glm::vec2 TopRight = glm::vec2(1.0, 1.0);
	inline static glm::vec2 LeftCenter = glm::vec2(0.0, 0.5);
	inline static glm::vec2 RightCenter = glm::vec2(1.0, 0.5);
	inline static glm::vec2 Center = glm::vec2(0.5, 0.5);

	inline static const char* names[9] = { 
										"BottomLeft", 
										"BottomCenter", 
										"BottomRight", 
										"TopLeft", 
										"TopCenter", 
										"TopRight", 
										"LeftCenter", 
										"RightCenter", 
										"Center"
										};


	inline static std::map<int, glm::vec2> IDtoPivot =
	{
		{ 0, BottomLeft },
		{ 1, BottomCenter },
		{ 2, BottomRight },
		{ 3, TopLeft },
		{ 4, TopCenter },
		{ 5, TopRight },
		{ 6, LeftCenter },
		{ 7, RightCenter },
		{ 8, Center }
	};

	static int getIDFromPivot(const glm::vec2 pivot)
	{
		for (auto it = IDtoPivot.begin(); it != IDtoPivot.end(); ++it)
		{
			if (it->second == pivot)
			{
				return it->first;
			}
		}
		
		return -1;
	}
};
