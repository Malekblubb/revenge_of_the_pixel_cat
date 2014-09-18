//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_SHARED_DATAMANAGER
#define PC_SHARED_DATAMANAGER

#include <pc/core/engine_component.hpp>

#include <mlk/filesystem/fs_handle.h>

#include <map>

namespace pc {

	enum class EndingIndex : short {
		graphics = 0,
		audio,

		font,
		raw
	};

	class DataManager : public EngineComponent {
		mlk::fs::dir_handle mDirectoryHandle;
		mlk::fs::file_handle mFileHandle;
		std::map<std::string, EndingIndex> mRegisteredFiles;
		bool mIsValid;

		// data
		std::map<std::string, sf::Texture> mGraphicsStorage;
		std::map<std::string, sf::SoundBuffer> mAudioStorage;
		std::map<std::string, sf::Font> mFontStorage;
		std::map<std::string, mlk::data_packet> mRawStorage;
		std::tuple<
				std::map<std::string, sf::Texture>*,
				std::map<std::string, sf::SoundBuffer>*,
				std::map<std::string, sf::Font>*,
				std::map<std::string, mlk::data_packet>*
		> mMaster{&mGraphicsStorage, &mAudioStorage, &mFontStorage, &mRawStorage};
		using MasterType = decltype(mMaster);

	public:
		DataManager(const std::string& directory);

		void registerFile(const std::pair<std::string, EndingIndex>& pair);
		void loadAllFiles();

		template<EndingIndex ending>
		const auto& get(const std::string& name) {
			return std::get<static_cast<int>(ending)>(mMaster)->at(name);
		}

	private:
		void loadFile(const mlk::data_packet& data, const std::string& name);
	};
}

#endif // PC_SHARED_DATAMANAGER
