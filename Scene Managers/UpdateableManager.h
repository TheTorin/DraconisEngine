#ifndef _UpdateableManager
#define _UpdateableManager

#include <list>
class Updateable;
class UpdateableManager
{
private:
	using StorageList = std::list<Updateable*>;
	StorageList slist;

public:
	UpdateableManager() = default;
	UpdateableManager(const UpdateableManager&) = delete;
	UpdateableManager& operator=(const UpdateableManager&) = delete;
	~UpdateableManager();

	using ListRef = StorageList::iterator;

	void ProcessElements();

	void Register(Updateable* up, ListRef &ref);
	void Deregister(ListRef ref);
};


#endif _UpdateableManager