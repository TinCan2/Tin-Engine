#include "FunctionalObject.hpp"
#include <algorithm>

using namespace Tin;

//Construction and Destruction
FunctionalObject::FunctionalObject() {
	updateList.push_back(this);
}

FunctionalObject::~FunctionalObject() {
	std::vector<FunctionalObject*>::iterator it = std::find(updateList.begin(), updateList.end(), this);
	updateList.erase(it);
}


//Object Access
void FunctionalObject::UpdateObjects() {
	for (size_t i = 0; i < updateList.size(); i++) updateList[i]->OnUpdate();
}


//Statics
std::vector<FunctionalObject*> FunctionalObject::updateList;