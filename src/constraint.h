#pragma once
#include "verletObject.h"

class Constraint
{
public:
	virtual ~Constraint() = default;
	virtual bool isWithin(VerletObject& object) const = 0;
	virtual void applyConstraint(VerletObject& object) const = 0;
};

