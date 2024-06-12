#pragma once

#include "hittable.hpp"

#include "utility.hpp"
#include <vector>

class HittableList : public Hittable
{
public:
	HittableList() = default;
	HittableList(std::shared_ptr<Hittable> object) { Add(object); }
	
	void Clear() { m_Objects.clear(); }
	void Add(std::shared_ptr<Hittable> object) { m_Objects.emplace_back(object); }
	
	bool Hit(const Ray& ray, float rayXmin, float rayXMax, HitRecord& hitRecord) const override;

public:
	std::vector<std::shared_ptr<Hittable>> m_Objects;
};