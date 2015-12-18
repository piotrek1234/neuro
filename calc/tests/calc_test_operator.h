/*
 * calc_test_operator.h
 * Contains operator<< and boost::test_tools::print_log_value template for tested classes.
 */
#ifndef CALC_TEST_OPERATOR_H
#define CALC_TEST_OPERATOR_H

#include <ostream>
#include <sstream>
#include "../src/hex.h"
/*#include "../src/modadditionalaction.h"
#include "../src/modpriority.h"
#include "../src/modlife.h"
#include "../src/modattack.h"*/

//Hex
namespace std{
std::ostream& operator<<(std::ostream& s, const Hex& h) {
  s << "Hex(" << h.getQ() << ',' << h.getR() << ')';
  return s;
}}
/*namespace std{
std::ostream& operator<<(std::ostream& s, const ModAdditionalAction& m) {
  std::stringstream kierunki;
  for(auto i=m.getDirectionBegin(); i!=m.getDirectionEnd(); ++i)
    kierunki << *i;
  s << "ModAddAct(" << kierunki.str() << ')';
  return s;
}}*/
/*namespace boost { namespace test_tools {
template<>
struct print_log_value<Hex> {
void operator()( std::ostream& os, Hex const& ts)
{ ::operator<<(os,ts); }};}}*/
//


#endif // CALC_TEST_OPERATOR_H
