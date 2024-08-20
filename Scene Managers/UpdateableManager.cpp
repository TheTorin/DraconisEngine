#include "UpdateableManager.h"
#include "UpdateableAttorney.h"

void UpdateableManager::Register(Updateable* up, ListRef &ref)
{
	ref = slist.insert(slist.end(), up);
}

void UpdateableManager::Deregister(ListRef ref)
{
	slist.erase(ref);
}

void UpdateableManager::ProcessElements()
{
	ListRef it;
	for (it = slist.begin(); it != slist.end(); it++)
	{
		UpdateableAttorney::UpdateLoop::Update(*it);
	}
}

UpdateableManager::~UpdateableManager()
{
	slist.clear();
}