#ifndef EQSOLV_H_INCLUDED
#define EQSOLV_H_INCLUDED

#include "datatypes.h"

SC_MODULE(EquationSolver)
{
public:
  sc_core::sc_in< bool >        clk;
  sc_core::sc_in< bool >        rst;
  sc_core::sc_in< bool >        valid_in;
  sc_core::sc_out< bool >       ready_in;
  sc_core::sc_in< eq_fixed_t >  x0_in;
  sc_core::sc_in< eq_fixed_t >  u0_in;
  sc_core::sc_in< eq_fixed_t >  y0_in;
  sc_core::sc_out< bool >       valid_out;
  sc_core::sc_in< bool >        ready_out;
  sc_core::sc_out< eq_fixed_t > y_out;
  sc_core::sc_in< eq_fixed_t >  dx_in;
  sc_core::sc_in< eq_fixed_t >  a_in;
  sc_core::sc_in< eq_fixed_t >  const3_in;



  SC_CTOR(EquationSolver) {
    SC_CTHREAD(thread0, clk.pos());
    reset_signal_is(rst, false);

    // don't initialize data members or output ports here
    // in the constructor. do it in the reset() function instead.
  }

 private:

  void thread0();
  void reset();
  void dataIn();
  void dataOut();

  // place any additional functions or data members here
  //  eq_fixed_t x;
  //  eq_fixed_t u;
  //eq_fixed_t y;
  //eq_fixed_t x1;
  //eq_fixed_t u1;
  //eq_fixed_t y1;
/*   double x; */
/*   double u; */
/*   double y; */
/*   double x1; */
/*   double u1; */
/*   double y1; */
/*   sc_int<32> x; */
/*   sc_int<32> u; */
/*   sc_int<32> y; */
/*   sc_int<32> x1; */
/*   sc_int<32> u1; */
/*   sc_int<32> y1; */

  eq_fixed_t x;
  eq_fixed_t u;
  eq_fixed_t y;
  eq_fixed_t x1;
  eq_fixed_t u1;
  eq_fixed_t y1; 
  eq_fixed_t a;
  eq_fixed_t dx;

  //eq_fixed_t yout;
  //eq_fixed_t c3;
  //eq_fixed_t dx3;


};

#endif // EQSOLV_H_INCLUDED
