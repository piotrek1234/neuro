/*
 * calc_test_operator.h
 * Contains operator<< and boost::test_tools::print_log_value template for tested classes.
 */
#ifndef CALC_TEST_OPERATOR_H
#define CALC_TEST_OPERATOR_H

#include <ostream>
#include "../src/hex.h"

//Hex
std::ostream& operator<<(std::ostream& s, const Hex& h) {
  s << "Hex(" << h.getQ() << ',' << h.getR() << ')';
  return s;
}
namespace boost { namespace test_tools {
template<>
struct print_log_value<Hex> {
void operator()( std::ostream& os, Hex const& ts)
{ ::operator<<(os,ts); }};}}
//


#endif // CALC_TEST_OPERATOR_H
