#include "component.h"

namespace bliep {
    unsigned int Components::GetId(std::type_index t) { 
        if (m_component_type_indices.count(t)) { return m_component_type_indices[t]; }
        unsigned int new_index = m_curr_component_type_uid++;
        m_component_type_indices[t] = new_index;
        return new_index;
    }
        
    bool Components::FlagsMatch(unsigned f1, unsigned f2) { return (f1 & ~f2) == 0; }
};