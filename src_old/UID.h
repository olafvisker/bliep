#pragma once
#include <vector>

class UID
{
public:
	UID() { }
	~UID() { }

	unsigned int GetNextID()
	{
		int id = 0;
		if (m_freeIDs.size() > 0)
		{
			id = m_freeIDs[0];
			m_freeIDs.erase(m_freeIDs.begin());
		}
		else
			id = m_idCounter++;

		return id;
	}

	void FreeID(unsigned int id)
	{
		m_freeIDs.push_back(id);
	}

private:
	std::vector<unsigned int> m_freeIDs;
	unsigned int m_idCounter = 0;
};