#pragma once

#include<vector>
#include<filesystem>
#include<array>
#include<nlohmann/json.hpp>

namespace cdda {
	namespace fs = std::filesystem;

	struct File {
		fs::path path;
		uint_fast8_t volume{ 100 };
	};

	class MusicSet {
	private:

		bool shuffle;
		std::vector<File> files;

	public:
		MusicSet();
		MusicSet(bool shuffle);
		MusicSet(bool shuffle, std::vector<File> files);
		MusicSet(const MusicSet& other);
		MusicSet(MusicSet&& other) noexcept;
		MusicSet& operator=(const MusicSet& other);
		MusicSet& operator=(MusicSet&& other) noexcept;

		static const std::string type;
		static const std::string id;

		void setShuffle(const bool shuffle);
		bool getShuffle() const;
		const std::vector<File>& getFiles() const;
		void setFiles(std::vector<File> files);
		void addFile(fs::path path, uint_fast8_t volume = 100);
		void addFile(File file);
		void getMusic(fs::path path = fs::current_path());
	};

	void to_json(nlohmann::json& j, const MusicSet& ms);
	void from_json(const nlohmann::json& j, MusicSet& ms);
	void to_json(nlohmann::json& j, const File& file);
	void from_json(const nlohmann::json& j, File& file);

	void writeMusicSet(const MusicSet& ms, fs::path path = fs::current_path());

	const inline std::array<std::string, 7> validExt = { ".ogg", ".wav", ".mp3", ".m4p", ".flac", ".dss", ".aac" };

}