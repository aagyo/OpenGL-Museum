#ifndef COLLISION_H
#define COLLISION_H
#include<glm.hpp>

struct AABB
{
	glm::vec3 m_min;
	glm::vec3 m_max;
};

bool checkForCollisionObj(glm::vec3 cameraPosition,AABB BBArray)
{
	float sqDist = 0.0f;

	for (int i = 0; i < 3; i++)
	{
		// For each axis, count any excess distance outside box extents
		float v = cameraPosition[i];
		if (v < BBArray.m_min[i])
			sqDist += (BBArray.m_min[i] - v) * (BBArray.m_min[i] - v);
		else
			if (v > BBArray.m_max[i])
				sqDist += (v - BBArray.m_max[i]) * (v - BBArray.m_max[i]);
	}
	if (sqDist < 1)
	{
		if (cameraPosition.x <= BBArray.m_max.x || cameraPosition.x >= BBArray.m_min.x &&
			cameraPosition.y <= BBArray.m_max.y || cameraPosition.y >= BBArray.m_min.y &&
			cameraPosition.z <= BBArray.m_max.z || cameraPosition.z >= BBArray.m_min.z
			)
			return true;
	}
	return false;
}

bool checkForCollisionWalls(glm::vec3 cameraPosition, AABB BBArray)
{
	float sqDist = 0.0f;

	for (int i = 0; i < 3; i++)
	{
		// For each axis, count any excess distance outside box extents
		float v = cameraPosition[i];
		if (v < BBArray.m_min[i])
			sqDist += (BBArray.m_min[i] - v) * (BBArray.m_min[i] - v);
		else
			if (v > BBArray.m_max[i])
				sqDist += (v - BBArray.m_max[i]) * (v - BBArray.m_max[i]);
	}

	bool collisionX = sqDist >= 0 && cameraPosition.x <= BBArray.m_min[0] || cameraPosition.x >= BBArray.m_max[0];
	bool collisionY = sqDist >= 0 && cameraPosition.y <= BBArray.m_min[1] || cameraPosition.y >= BBArray.m_max[1];
	bool collisionZ = sqDist >= 0 && cameraPosition.z <= BBArray.m_min[2] || cameraPosition.z >= BBArray.m_max[2];

	return collisionX || collisionY || collisionZ;
}
#endif




