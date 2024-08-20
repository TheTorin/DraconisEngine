#ifndef GAME_H
#define GAME_H

#include "AzulCore.h"

class Draconis: public Engine
{
	friend class DraconisAttorney;
private:
	// constructor
	Draconis() {};
	Draconis(const Draconis&) = delete;
	Draconis& operator=(const Draconis&) = delete;
	~Draconis() = default;

	static Draconis* ptrInstance;

	static Draconis& Instance()
	{
		if (!ptrInstance)
		{
			ptrInstance = new Draconis();
		}
		return *ptrInstance;
	}

	//legacy
	Draconis(const char* windowName, const int Width, const int Height);

	//Information Methods
	int privGetHeight() { return this->getHeight(); };
	int privGetWidth() { return this->getWidth(); };
	float getTime() { return this->GetTimeInSeconds(); };
	void privSetClear(float r, float g, float b, float a) { this->SetClearColor(r, g, b, a); };
	void privSetWidthHeight(int w, int h) { this->setWidthHeight(w, h); };
	void privSetWindowName(const char* name) { this->setWindowName(name); };

	// Methods Users need to overload
    virtual void Initialize();
    virtual void LoadContent();
	virtual void Update();
    virtual void Draw();
    virtual void UnLoadContent();

	//User Defined Methods
	void LoadAllResources();
	void GameStart();
	void GameEnd();

	static void Terminate();

public:	
	static void runGame() { Instance().run(); };
	static void endGame() { Instance().Terminate(); };

	static int getWindowHeight() { return Instance().privGetHeight(); };
	static int getWindowWidth() { return Instance().privGetWidth(); };
	static void setClear(float r, float g, float b, float a) { Instance().privSetClear(r, g, b, a); };
	static void setWidthAndHeight(int w, int h) { Instance().privSetWidthHeight(w, h); };
	static void setNameOfWindow(const char* name) { Instance().privSetWindowName(name); };
};

#endif