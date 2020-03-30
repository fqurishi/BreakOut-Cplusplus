#include "functions.h"

//load sound from resource
sf::SoundBuffer functions::LoadBufferFromResource(const std::string& name)
{
	HRSRC rsrcData = FindResource(NULL, name.c_str(), RT_RCDATA);
	if (!rsrcData)
		throw std::runtime_error("Failed to find resource.");

	DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
	if (rsrcDataSize <= 0)
		throw std::runtime_error("Size of resource is 0.");

	HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
	if (!grsrcData)
		throw std::runtime_error("Failed to load resource.");

	LPVOID firstByte = LockResource(grsrcData);
	if (!firstByte)
		throw std::runtime_error("Failed to lock resource.");

	sf::SoundBuffer buffer;
	if (!buffer.loadFromMemory(firstByte, rsrcDataSize))
		throw std::runtime_error("Failed to load buffer from memory.");

	return buffer;
}

//load font from resource
sf::Font functions::LoadFontFromResource(const std::string& name)
{
	HRSRC rsrcData = FindResource(NULL, name.c_str(), RT_RCDATA);
	if (!rsrcData)
		throw std::runtime_error("Failed to find resource.");

	DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
	if (rsrcDataSize <= 0)
		throw std::runtime_error("Size of resource is 0.");

	HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
	if (!grsrcData)
		throw std::runtime_error("Failed to load resource.");

	LPVOID firstByte = LockResource(grsrcData);
	if (!firstByte)
		throw std::runtime_error("Failed to lock resource.");

	sf::Font font;
	if (!font.loadFromMemory(firstByte, rsrcDataSize))
		throw std::runtime_error("Failed to load font from memory.");

	return font;
}
