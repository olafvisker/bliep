#include <plog/Appenders/ConsoleAppender.h>

#include "logger.h"

namespace bliep {
    void Logger::Init(const char* filepath, bool clean_start, size_t max_file_size) {
        static plog::RollingFileAppender<plog::CsvFormatter> fa(filepath, max_file_size);
        static plog::ConsoleAppender<plog::TxtFormatter> ca;
        plog::init(plog::verbose, &fa).addAppender(&ca);
        if (clean_start) { fa.rollLogFiles(); }
    } 
}