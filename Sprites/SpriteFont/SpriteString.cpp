#include "SpriteString.h"

SpriteString::SpriteString(SpriteFont* sf, std::string s, float x, float y)
{
	Set(sf, s, x, y);
}

SpriteString::SpriteString(const SpriteString& other)
{
	posx = other.posx;
	posy = other.posy;
	height = other.height;
	width = other.width;

	glyphs = other.glyphs;
}

void SpriteString::Set(SpriteFont* sf, std::string s, float x, float y)
{
	glyphs.clear();

	posx = x;
	posy = y;

	height = 0;
	width = 0;

	for (size_t i = 0; i < s.size(); i++)
	{
		SpriteFont::Glyph* g = sf->GetGlyph(s[i]);

		width += g->GetWidth();
		if (g->GetHeight() > height) height = g->GetHeight();

		glyphs.push_back(g);
	}
}

void SpriteString::Set(float x, float y)
{
	posx = x;
	posy = y;
}

void SpriteString::Render()
{
	float tempWidth = 0;

	for (size_t i = 0; i < glyphs.size(); i++)
	{
		glyphs[i]->SetPosition(posx + tempWidth, posy);
		tempWidth += glyphs[i]->GetWidth();
		glyphs[i]->Render();
	}
}

SpriteString::~SpriteString()
{
	glyphs.clear();
}