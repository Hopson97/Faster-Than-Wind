#include "sound_m.h"

#include <iostream>

SoundManager::SoundManager()
:   soundPath   ("Resources/Sounds/")
{
    loadGlobalSounds();
}

void SoundManager::loadGlobalSounds()
{
   loadSound(RES_SOUND_GBL_GENERIC_CLICK, soundPath + "click.ogg");
}

void SoundManager::loadSound(const SoundName& name, const std::string& filePath)
{
    mSoundBuffers[name].loadFromFile(filePath);
    mSounds[name].setBuffer( mSoundBuffers[name] );
}

sf::Sound& SoundManager::getSound (const SoundName& name)
{
    return mSounds[name];
}
