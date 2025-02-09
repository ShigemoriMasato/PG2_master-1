#pragma once
#include "Object.h"

namespace Collition {

	/// <summary>
	/// BoxToBox
	/// </summary>
	bool BtB(Object& obj1, Object& obj2);

	/// <summary>
	/// BoxToPoint
	/// </summary>
	bool BtP(Object* obj, Vector2 point);

	/// <summary>
	/// CircleToPoint
	/// </summary>
	bool CTP(Object* obj, Vector2 point);

	/// <summary>
	/// CircleToCircle
	/// </summary>
	bool CtC(Object* obj1, Object* obj2);

};
