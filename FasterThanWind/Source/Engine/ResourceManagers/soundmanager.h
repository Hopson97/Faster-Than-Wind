#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>

#include <vector>
#include <string>

enum SoundName
{
    RES_SOUND_GBL_CLICK
};

class SoundManager
{
    public:
        SoundManager();
        void            loadGlobalSounds        ();
        sf::SoundBuffer& getSound                (const SoundName& name);

    protected:
    private:
        void            loadSound               (const SoundName& name, const std::string& filePath);

        std::vector<sf::SoundBuffer> mSounds;
        std::string soundPath;

        sf::SoundBuffer test;
};

#endif // SOUNDMANAGER_H
