#include <iostream>
#include <string>
#include <unistd.h>
#include <boost/log/trivial.hpp>
#include "src/BoostLogger.h"

using namespace std;

int main(int argc, char **argv) {
    BoostLogger &logger = BoostLogger::get_instance();
    logger.set_filter(boost::log::trivial::trace);

    BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
    BOOST_LOG_TRIVIAL(info) << "This is an informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
    BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "and this is a fatal severity message";

	cout << "Hello World" << endl;
	return 0;

}
