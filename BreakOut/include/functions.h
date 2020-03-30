#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>

class functions
{
    public:

        sf::SoundBuffer LoadBufferFromResource(const std::string& name);
        sf::Font LoadFontFromResource(const std::string& name);
};

#endif // FUNCTIONS_H
