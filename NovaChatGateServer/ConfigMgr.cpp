#include "ConfigMgr.h"

ConfigMgr::ConfigMgr() {
	 //获取并构建路径
	boost::filesystem::path current_path = boost::filesystem::current_path();
	boost::filesystem::path config_path = current_path / "config.ini";
	std::cout << "配置文件路径:" << config_path << std::endl;

	 //ptree读取文件
	boost::property_tree::ptree pt;
	boost::property_tree::read_ini(config_path.string(), pt);

	 //遍历ini中所有section
	for (const auto& section_pair : pt) {
		const std::string& section_name = section_pair.first; //section名
		const boost::property_tree::ptree& section_tree = section_pair.second; //section条目

		std::map<std::string, std::string> section_config;
		for (const auto& key_value_pair : section_tree) {
			const std::string& key = key_value_pair.first;
			const std::string& value = key_value_pair.second.get_value<std::string>();
			section_config[key] = value;
		}

		Sectioninfo sectioninfo;
		sectioninfo._section_datas = section_config;
		_config_map[section_name] = sectioninfo; //将section的key-value对保存到config_map中  
	}

	for (const auto& section_entry : _config_map) {
		const std::string& section_name = section_entry.first;
		Sectioninfo section_config = section_entry.second;
		std::cout << "[" << section_name << "]" << std::endl;

		for (const auto& key_value_pair : section_config._section_datas) {
			std::cout << key_value_pair.first << "=" << key_value_pair.second << std::endl;
		}
	}
}

std::string ConfigMgr::GetValue(const std::string& section, const std::string& key) {
	if (_config_map.find(section) == _config_map.end()) {
		return "";
	}
	return _config_map[section].GetValue(key);
}