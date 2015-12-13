#ifndef UTILS_H
#define UTILS_H

#include <boost/smart_ptr.hpp>
#include "token.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

typedef boost::shared_ptr<Token> TokenPtr;
typedef boost::property_tree::ptree::value_type node;
typedef boost::property_tree::ptree ptree;

#endif // COLOR_H