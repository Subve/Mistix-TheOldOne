#pragma once
#include "Headers.h"
template <typename Derived, typename T>
class ResourceManager {
public:
	ResourceManager(const std::string& l_patchFile) {
		LoadPaths(l_patchFile);
	}
	~ResourceManager() { PurgeResources(); }
	
	T* GetResource(const std::string& l_id) {
		auto res = Find(l_id);
		return(res ? res->first : nullptr);
	}
	std::string GetPath(const std::string& l_id) {
		auto path = m_paths.find(l_id);
		return(path != m_paths.end() ? path->second : "");
	}
	bool RequireResource(const std::string& l_id) {
		auto res = Find(l_id);
		if (res) {
			++res->second;
			return true;

		}
		auto path = m_paths.find(l_id);
		if (path == m_paths.end()) { return false; }
		T* resource = Load(path->second);
		if (!resource) { return false; }
		m_resources.emplace(l_id, std::make_pair(recource, 1));
		return true;
	}
	bool RelaseResource(const std::string& l_id) {
		auto res = Find(l_id);
		if (!res) { return false; }
		--res->second;
		if (!res->second) { Unload(l_id); }
		return false;

	}

private:
	std::unordered_map<std::string,
		std::pair<T*, unsigned int>> m_resources;
	std::unordered_map<std::string, std::string> m_paths;

};
