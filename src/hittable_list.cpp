#include "hittable_list.hpp"

bool HittableList::Hit(const Ray& ray, Interval& rayInterval, HitRecord& hitRecord) const
{
	HitRecord tempRecord;
	bool hasHit = false;
	float closest = rayInterval.m_Max;

	for (const auto& object : m_Objects)
	{
		Interval tempInterval = Interval(rayInterval.m_Min, closest);

		if (object->Hit(ray, tempInterval, tempRecord))
		{
			hasHit = true;
			closest = tempRecord.x;
			hitRecord = tempRecord;
		}
	}
	
	return hasHit;
}