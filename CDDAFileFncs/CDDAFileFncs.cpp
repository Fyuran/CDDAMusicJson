#include "CDDAFileFncs.hpp"
#include <fstream>
#include <regex>

namespace cdda {
    using json = nlohmann::json;
    const std::string MusicSet::type = "playlist";
    const std::string MusicSet::id = "title";

    MusicSet::MusicSet() : shuffle(true) {}
    MusicSet::MusicSet(bool shuffle) : shuffle(shuffle) {}
    MusicSet::MusicSet(bool shuffle, std::vector<File> files) : shuffle(shuffle), files(files) {}
    MusicSet::MusicSet(const MusicSet& other) : shuffle(other.shuffle), files(other.files) {}
    MusicSet::MusicSet(MusicSet&& other) noexcept : shuffle(other.shuffle), files(std::move(files)) {}
    MusicSet& MusicSet::operator=(MusicSet&& other) noexcept {
        this->shuffle = other.shuffle;
        this->files = std::move(other.files);

        return *this;
    }

    MusicSet& MusicSet::operator=(const MusicSet& other) {
        if (this == &other)
            return *this;

        this->shuffle = other.shuffle;
        this->files = other.files;
        return *this;
    }


    void MusicSet::setShuffle(const bool shuffle) {
        this->shuffle = shuffle;
    }

    bool MusicSet::getShuffle() const {
        return shuffle;
    }

    const std::vector<File>& MusicSet::getFiles() const {
        return files;
    }

    void MusicSet::setFiles(std::vector<File> files) {
        this->files = files;
    }

    void MusicSet::addFile(fs::path path, uint_fast8_t volume) {
        files.push_back(File(fs::relative(path, path.parent_path().parent_path()), volume));
    }
    void MusicSet::addFile(File file) {
        files.push_back(file);
    }

    void to_json(json& j, const MusicSet& ms) {
        j = json{
            {"type", MusicSet::type},
            {"playlists", {{
                {"id", MusicSet::id}, {"shuffle", ms.getShuffle()}, {"files", ms.getFiles()}
                }}
            }
        };

    }

    void from_json(const json& j, MusicSet& ms) {
        auto shuffle = j.at(0).at("playlists").at(0).at("shuffle").get<bool>();
        ms.setShuffle(shuffle);

        auto files = j.at(0).at("playlists").at(0).at("files").get<std::vector<File>>();
        ms.setFiles(files);
    }

    void to_json(json& j, const File& file) {
        std::regex reg{ "\\\\" };
        std::string fixedString = std::regex_replace(file.path.string(), reg, "/");

        j = json{ {"file", fixedString}, {"volume", file.volume} };
    }

    void from_json(const json& j, File& file) {
        j.at("file").get_to(file.path);
        j.at("volume").get_to(file.volume);
    }

    void writeMusicSet(const MusicSet& ms, fs::path path) {
        json j{ ms };
        if (fs::exists(path)) {
            std::ofstream musicFolder{ path/"musicset.json", std::ios::trunc | std::ios::out};
            if (musicFolder) {
                musicFolder << std::setw(4) << j;
            }
            musicFolder.close();
        }
    }
	void MusicSet::getMusic(fs::path path) {
		fs::directory_iterator dit{ path };
        
		if (fs::exists(path)) {
			for (const auto& it : dit) {
				const auto& path{ it.path() };
				for (const auto& ext : validExt) {
					if (path.extension() == ext)
                        files.push_back(File{ "music"/fs::relative(path, path.parent_path()), 100});
				}
			}
		}
	}

}
