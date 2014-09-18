//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pc/shared/datamanager.hpp>

#include <mlk/containers/container_utl.h>
#include <mlk/log/log.h>

namespace pc {

	DataManager::DataManager(const std::string& directory)
			: mDirectoryHandle{directory}
			, mIsValid{mDirectoryHandle.exists()} { }

	void DataManager::registerFile(const std::pair<std::string, EndingIndex>& pair) {
		mRegisteredFiles.emplace(pair);
	}

	void DataManager::loadAllFiles() {
		auto dirContent(mDirectoryHandle.get_content<true>());
		for(const auto& entry : dirContent) {
			if(!mlk::cnt::exists_map_first(entry.name, mRegisteredFiles))
				continue;

			mFileHandle.reopen(entry.path, std::ios::in);
			if(!mFileHandle.exists())
				continue;
			loadFile(mFileHandle.read_all(), entry.name);
		}
	}



	void DataManager::loadFile(const mlk::data_packet& data, const std::string& name) {
		switch(mRegisteredFiles[name]) {
			case EndingIndex::graphics: {
				sf::Texture tmp;
				tmp.loadFromMemory(data.data(), data.size());
				mGraphicsStorage.emplace(name, tmp);
			} break;

			case EndingIndex::audio: {
				sf::SoundBuffer tmp;
				tmp.loadFromMemory(data.data(), data.size());
				mAudioStorage.emplace(name, tmp);
			} break;

			case EndingIndex::font: {
				sf::Font tmp;
				tmp.loadFromMemory(data.data(), data.size());
				mFontStorage.emplace(name, tmp);
			} break;

			case EndingIndex::raw:
				mRawStorage.emplace(name, data);
				break;
		}

		mlk::lout("pc::DataManager") << "Loaded file '" << name << "' as " <<
				static_cast<int>(mRegisteredFiles[name]) << " (" << data.size() << " bytes)";
	}
}