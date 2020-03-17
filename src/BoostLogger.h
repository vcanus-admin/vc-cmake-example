//
// Created by SG Lee on 2019/10/27.
//

#ifndef SEGMENT_MEASUREMENT_SEARCH_BOOSTLOGGER_H
#define SEGMENT_MEASUREMENT_SEARCH_BOOSTLOGGER_H

#include <memory>
#include <boost/log/common.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/keywords/format.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
//#include <boost/log/sources/global_logger_storage.hpp>
//#include <boost/log/sinks/text_file_backend.hpp>
//#include <boost/log/sources/record_ostream.hpp>

namespace logger = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

//    BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
//    BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
//    BOOST_LOG_TRIVIAL(info) << "This is an informational severity message";
//    BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
//    BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
//    BOOST_LOG_TRIVIAL(fatal) << "and this is a fatal severity message";

class BoostLogger{
private:
    BoostLogger() {
        sink_console_log = nullptr;
        sink_file_log = nullptr;
        init();
    }
    ~BoostLogger() {
//        if(sink_console_log)
//            sink_console_log->flush();
//        if(sink_file_log)
//            sink_file_log->flush();
    }
    BoostLogger(const BoostLogger &) = delete;
    BoostLogger &operator=(const BoostLogger &) = delete;
private:
    boost::shared_ptr<sinks::synchronous_sink<sinks::text_ostream_backend>> sink_console_log;
    boost::shared_ptr<sinks::synchronous_sink<sinks::text_file_backend>> sink_file_log;
private:
    void init() {
        sink_console_log = logger::add_console_log(
                std::cout,
                keywords::auto_flush = true,
                boost::log::keywords::format = ">> %Message%");
        sink_file_log = logger::add_file_log(
                keywords::target = "logs/", keywords::file_name = "%y%m%d_%3N.log",
                keywords::rotation_size = 10 * 1024 * 1024, // rolling with every 10MB
//                keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), //12시마다 rotate
                keywords::auto_flush = true,
                keywords::scan_method = sinks::file::scan_matching,
                keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%]: %Message%");

        logger::core::get()->set_filter(logger::trivial::severity >= logger::trivial::info);
        logger::add_common_attributes();
    }
public:
    inline static BoostLogger &get_instance() {
        static BoostLogger instance;
        return instance;
    }
    void set_filter(const logger::trivial::severity_level &level) {
        logger::core::get()->set_filter(logger::trivial::severity >= level);
    }
private:
};
#endif //SEGMENT_MEASUREMENT_SEARCH_BOOSTLOGGER_H
