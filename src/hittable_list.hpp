#pragma once

#include <vector>

#include "utility.hpp"
#include "hittable.hpp"

struct HitRecord;

class HittableList : public Hittable
{
public:
	HittableList() = default;
	HittableList(std::shared_ptr<Hittable> object) { Add(object); }
	
	void Clear() { m_Objects.clear(); }
	void Add(std::shared_ptr<Hittable> object) { m_Objects.emplace_back(object); }
	
	bool Hit(const Ray& ray, Interval rayInterval, HitRecord& hitRecord) const override;

public:
	std::vector<std::shared_ptr<Hittable>> m_Objects;
};