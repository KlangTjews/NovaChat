#pragma once

#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include <map>
#include <iostream>

 //储存ini文件段落
struct Sectioninfo {
	std::map<std::string, std::string> _section_datas;

	Sectioninfo() {};

	~Sectioninfo() {
		_section_datas.clear();
	}

	Sectioninfo(const Sectioninfo& src) {
		_section_datas = src._section_datas;
	}

	Sectioninfo& operator=(const Sectioninfo& src) {
		if (&src == this) {
			return *this;
		}

		this->_section_datas = src._section_datas;
		return *this;
	}

	std::string operator[](const std::string& key) {
		if (_section_datas.find(key) == _section_datas.end()) {
			return ""; //未找到返回空值
		}
		return _section_datas[key];
	}

	std::string GetValue(const std::string& key) {
		if (_section_datas.find(key) == _section_datas.end()) {
			return "";
		}
		return _section_datas[key];
	}
};

class ConfigMgr {
public:

	~ConfigMgr() {
		_config_map.clear();
	}

	ConfigMgr(const ConfigMgr& src) {
		this->_config_map = src._config_map;
	}

	Sectioninfo operator[](const std::string& section) {
		if (_config_map.find(section) == _config_map.end()) {
			return Sectioninfo(); //返回默认构造结构体
		}
		return _config_map[section];
	}

	ConfigMgr& operator=(const ConfigMgr& src) {
		if (&src == this) {
			return *this;
		}
		this->_config_map = src._config_map;
	}

	static ConfigMgr& Inst() {
		static ConfigMgr cfg_mgr;
		return cfg_mgr;
	}

	std::string GetValue(const std::string& section, const std::string& key);
private:
	ConfigMgr();

	std::map<std::string, Sectioninfo> _config_map; //实现三级map结构
};