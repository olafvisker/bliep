#pragma once
#include <typeindex>
#include <unordered_map>

namespace bliep {
    struct Component { virtual ~Component() { } };

    namespace Components {
        unsigned int GetId(std::type_index t);       
        bool FlagsMatch(unsigned f1, unsigned f2);
        template<typename T> int GetId() { return GetId(typeid(T)); }


        namespace {
            #pragma GCC diagnostic ignored "-Wunused-variable" 
            unsigned int m_curr_component_type_uid = 0;
            std::unordered_map<std::type_index, int> m_component_type_indices;        
        }     
    }
};