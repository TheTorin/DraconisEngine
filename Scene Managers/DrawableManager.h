#ifndef _DrawableManager
#define _DrawableManager

#include <list>
class Drawable;
class DrawableManager
{
private:
	using DrawingList = std::list<Drawable*>;
	DrawingList dlist;

public:
	DrawableManager() = default;
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator=(const DrawableManager&) = delete;
	~DrawableManager();

	using ListRef = DrawingList::iterator;

	void ProcessElements();
	void Process2DElements();

	void Register(Drawable* draw, ListRef &ref);
	void Deregister(ListRef ref);
};


#endif _DrawableManager