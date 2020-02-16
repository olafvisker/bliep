#pragma once
#include <string>

namespace bliep {
    class Asset {
        public:
            Asset() { };
            Asset(std::string name, const std::string& path) : m_name(name), m_path(path) { };
            virtual ~Asset() { }

            unsigned GetId()      const{ return m_id; }
            std::string GetName() const{ return m_name; }
            std::string GetPath() const{ return m_path; }

        private:
            unsigned m_id;
            std::string m_name;
            std::string m_path;
    };
}