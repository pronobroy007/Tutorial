#include <iostream>
#include <unistd.h>
#include <irrKlang.h>

using namespace std;
using namespace irrklang;

void playMusic();

int main(int argc, char* argv[])
{
    //print all device list...
    ISoundDeviceList* ls = createSoundDeviceList();
    std::cout << "Total device : " << ls->getDeviceCount() << std::endl;
    std::cout << "All Deviece List ..........." << std::endl;
    for(int i = 0; i < ls->getDeviceCount(); i++)
        std::cout << "Device ID : " << ls->getDeviceID(i) <<" \nDiscription : " << ls->getDeviceDescription(i) << std::endl;
    std::cout << ".................." << std::endl;

    playMusic();
    return 0;
}


void playMusic()
{
    ISoundEngine* engin = createIrrKlangDevice();
    ISoundSource* source = engin->addSoundSourceFromFile("audio.mp3");
    ISound* snd = engin->play2D(source, true, true);

    snd->setIsPaused(false);
	snd->setVolume(0.4);

	int i;
	cin >> i;

    //Cleane up........
    snd->drop();
    engin->drop();
    engin->removeSoundSource(source);
}

