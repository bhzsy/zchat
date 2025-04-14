#pragma once
#include "const.h"
struct SectionInfo
{
	SectionInfo() {}
	~SectionInfo() {
		_section_date.clear();
	}
	SectionInfo(const SectionInfo& src)
	{
		_section_date = src._section_date;
	}
	
	std::map<std::string, std::string> _section_date;
	SectionInfo& operator = (const SectionInfo& src)
	{
		if (&src == this)
		{
			return *this;
		}
		this->_section_date = src._section_date;
	}
	std::string  operator[](const std::string& key) {
		if (_section_date.find(key) == _section_date.end()) {
			return "";
		}
		return _section_date[key];
	}

	std::string GetValue(const std::string& key) {
		if (_section_date.find(key) == _section_date.end()) {
			return "";
		}
		// 这里可以添加一些边界检查  
		return _section_date[key];
	}
};
class ConfigMgr
{
public:
	~ConfigMgr() {
		_config_map.clear();
	}
	SectionInfo operator[](const std::string& section)
	{
		if (_config_map.find(section) == _config_map.end())
		{
			return SectionInfo();
		}
		return _config_map[section];
	}
	ConfigMgr& operator = (const ConfigMgr& src)
	{
		if (&src == this)
		{
			return *this;
		}
		this->_config_map = src._config_map;
	}
	ConfigMgr(const ConfigMgr& src)
	{
		this->_config_map = src._config_map;
	}
	static ConfigMgr& Inst() {
		static ConfigMgr cfg_mgr;
		return cfg_mgr;
	}
	std::string GetValue(const std::string& section, const std::string& key);
private:
	std::map<std::string, SectionInfo> _config_map;
	ConfigMgr();
};

