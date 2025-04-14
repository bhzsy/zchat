#include "ConfigMgr.h"

std::string ConfigMgr::GetValue(const std::string& section, const std::string& key)
{
	if (_config_map.find(section) == _config_map.end()) {
		return "";
	}

	return _config_map[section].GetValue(key);
}

ConfigMgr::ConfigMgr()
{
	boost::filesystem::path current_path = boost::filesystem::current_path();
	boost::filesystem::path config_path = current_path / "Config.ini";
	std::cout << config_path << "\n";
	boost::property_tree::ptree pt;
	boost::property_tree::read_ini(config_path.string(), pt);

	for (const auto& section_pair : pt)
	{
		const std::string& section_name = section_pair.first;
		const boost::property_tree::ptree& section_tree = section_pair.second;

		std::map< std::string, std::string> section_config;
		for (const auto& key_value_pair : section_tree)
		{
			const std::string& name = key_value_pair.first;
			const std::string& value = key_value_pair.second.get_value<std::string>();
			section_config[name] = value;
		}
		SectionInfo section;
		section._section_date = section_config;
		_config_map[section_name] = section;

	}
	for (const auto& section_entry : _config_map) {
		const std::string& section_name = section_entry.first;
		SectionInfo section_config = section_entry.second;
		std::cout << "[" << section_name << "]" << std::endl;
		for (const auto& key_value_pair : section_config._section_date) {
			std::cout << key_value_pair.first << "=" << key_value_pair.second << std::endl;
		}
	}
}