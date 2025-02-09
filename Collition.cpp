#include "Collition.h"

bool Collition::BtB(Object& obj1, Object& obj2) {

	if (obj2.GetCorner(0).x < obj1.GetCorner(1).x && obj1.GetCorner(0).x < obj2.GetCorner(1).x &&
		obj2.GetCorner(2).y < obj1.GetCorner(1).y && obj1.GetCorner(2).y < obj2.GetCorner(1).y) {
		return true;
	} else {
		return false;
	}

}

bool Collition::BtP(Object* obj, Vector2 point) {

	if (obj->GetCorner(0).x < point.x && obj->GetCorner(1).x > point.x && obj->GetCorner(1).y > point.y && obj->GetCorner(2).y < point.y) {
		return true;
	} else {
		return false;
	}

}

bool Collition::CTP(Object* obj, Vector2 point) {
	if ((obj->GetPos().x - point.x) * (obj->GetPos().x - point.x) + (obj->GetPos().y - point.y) * (obj->GetPos().y - point.y) <= (obj->GetScale().x * obj->GetSize().x / 2) * (obj->GetScale().x * obj->GetSize().x / 2)) {
		return true;
	} else {
		return false;
	}
}

bool Collition::CtC(Object* obj1, Object* obj2) {
	if ((obj1->GetPos().x - obj2->GetPos().x) * (obj1->GetPos().x - obj2->GetPos().x) + (obj1->GetPos().y - obj2->GetPos().y) * (obj1->GetPos().y - obj2->GetPos().y) <= (obj1->GetScale().x * obj1->GetSize().x + obj2->GetScale().x * obj2->GetSize().x) * (obj1->GetScale().x * obj1->GetSize().x + obj2->GetScale().x * obj2->GetSize().x)) {
		return true;
	} else {
		return false;
	}
}
