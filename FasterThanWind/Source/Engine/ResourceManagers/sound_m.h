#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>

#include <map>
#include <string>

enum SoundName
{
    RES_SOUND_GBL_GENERIC_CLICK
};

class SoundManager
{
    public:
                            SoundManager            ();
        void                loadGlobalSounds        ();
        sf::Sound&          getSound                (const SoundName& name);

    protected:
    private:
        void                        loadSound               (const SoundName& name, const std::string& filePath);

        std::map<SoundName, sf::SoundBuffer>    mSoundBuffers;
        std::map<SoundName, sf::Sound>          mSounds;

        std::string soundPath { "Resources/Sounds/" };
};

#endif // SOUNDMANAGER_H
