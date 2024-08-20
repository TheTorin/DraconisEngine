#include "DrawableManager.h"
#include "DrawableAttorney.h"

void DrawableManager::Register(Drawable* draw, ListRef &ref)
{
	ref = dlist.insert(dlist.end(), draw);
}

void DrawableManager::Deregister(ListRef ref)
{
	dlist.erase(ref);
}

void DrawableManager::ProcessElements()
{
	DrawingList::iterator it;
	for (it = dlist.begin(); it != dlist.end(); it++)
	{
		DrawableAttorney::DrawLoop::Draw(*it);
	}
}

void DrawableManager::Process2DElements()
{
	DrawingList::iterator it;
	for (it = dlist.begin(); it != dlist.end(); it++)
	{
		DrawableAttorney::DrawLoop::Draw2D(*it);
	}
}

DrawableManager::~DrawableManager()
{
	dlist.clear();
}