#pragma once
#include <string>

class Asset
{
public:
	Asset(unsigned int id, const std::string& path) : m_id(id), m_path(path) { }
	virtual ~Asset() { }

	inline unsigned int GetAssetID() { return m_id; }
	inline std::string GetPath() { return m_path; }

private:
	unsigned int m_id;
	std::string m_path;
};