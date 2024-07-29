// CDDAMusicJson.cpp : Defines the entry point for the application.
// C:/Users/danke/OneDrive/Desktop/Giochi/CDDA/dda/userdata/sound/Otopack/music

#include <CDDAMusicJson.hpp>
#include <CDDAFileFncs.hpp>
#include <iostream>
int main() {
  
    cdda::MusicSet ms{true};
    ms.getMusic("C:/Users/danke/OneDrive/Desktop/Giochi/CDDA/dda/userdata/sound/Otopack/music");
    cdda::writeMusicSet(ms);

    nlohmann::json j2(ms);
    std::cout << std::setw(4) << j2;
}
