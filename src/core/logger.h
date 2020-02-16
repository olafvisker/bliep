#pragma once
#include <plog/Log.h>

namespace bliep {
	namespace Logger{
		void Init(const char* filepath, bool clean_start, size_t max_file_size=0);
	};
}

