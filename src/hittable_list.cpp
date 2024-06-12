#include "hittable_list.hpp"

bool HittableList::Hit(const Ray& ray, float rayXmin, float rayXMax, HitRecord& hitRecord) const
{
	HitRecord tempRecord;
	bool hasHit = false;
	float closest = rayXMax;

	for (const auto& object : m_Objects)
	{
		if (object->Hit(ray, rayXmin, closest, tempRecord))
		{
			hasHit = true;
			closest = tempRecord.x;
			hitRecord = tempRecord;
		}
	}
	
	return hasHit;
}