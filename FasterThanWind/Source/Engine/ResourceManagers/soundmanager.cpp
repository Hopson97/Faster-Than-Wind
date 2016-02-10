#include "soundmanager.h"
#include <memory>
SoundManager::SoundManager()
:   soundPath   ("Resources/Sounds/")
{
    loadGlobalSounds();
}

void SoundManager::loadGlobalSounds()
{
   //loadSound(RES_SOUND_GBL_CLICK, "Resources/Sounds/click.ogg");
   // mSounds[RES_SOUND_GBL_CLICK] = test;

    //loadSound(RES_SOUND_GBL_CLICK, soundPath + "click.ogg");
    //mSounds[RES_SOUND_GBL_CLICK].loadFromFile("Resources/Sounds/click.ogg");

}

void SoundManager::loadSound(const SoundName& name, const std::string& filePath)
{
    if(! mSounds[name].loadFromFile(filePath) ) {
        return;
    }
}

sf::SoundBuffer& SoundManager::getSound (const SoundName& name)
{
    return mSounds[name];
}
