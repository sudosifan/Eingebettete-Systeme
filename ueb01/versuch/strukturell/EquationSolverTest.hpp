#ifndef INCLUDED_EQUATION_SOLVER_TEST_HPP
#define INCLUDED_EQUATION_SOLVER_TEST_HPP

#include <fstream>
#include "datatypes.hpp"

SC_MODULE(EquationSolverTest) {
public:
  sc_out<eq_fixed_t> x0_out;
  sc_out<eq_fixed_t> u0_out;
  sc_out<eq_fixed_t> y0_out;
  sc_out<eq_fixed_t> dx_out;
  sc_out<eq_fixed_t> a_out;
  sc_in<eq_fixed_t> y_in;

  // Clock/Reset Signale
  sc_in<bool> clk;
  sc_out<bool> rst;
  
  // Handshake-Protokoll für Eingangssignale
  sc_in<bool> valid_in;
  sc_out<bool> ready_in;

  // Handshake-Protokoll für Ausgangssignale
  sc_out<bool> valid_out;
  sc_in<bool> ready_out;

  SC_CTOR(EquationSolverTest) {
    SC_CTHREAD(main, clk.neg());
    
    /*tf = sc_create_vcd_trace_file("tb");

    sc_trace(tf, clk, "CLOCK");
    sc_trace(tf, ready_in, "READY_IN");
    sc_trace(tf, valid_in, "VALID_IN");
    sc_trace(tf, ready_out, "READY_OUT");
    sc_trace(tf, valid_out, "VALID_OUT");*/
  }

  /*~EquationSolverTest() {
    sc_close_vcd_trace_file(tf);
  }*/

private:
  eq_fixed_t a,y;
  //sc_trace_file* tf;

  void main() {
    sc_clock *clk_p = dynamic_cast<sc_clock *>(clk.get_interface());
    sc_time clock_period = clk_p->period();

    std::ofstream data("sim.data");
    
    rst = false;
    wait(5);
    rst = true;

    for(a = 0; a < 10; a += 0.1) {    
      sc_time start = sc_time_stamp();

      dataOut();

      dataIn();

      data << a << " " << y << std::endl;
      
      std::cout << "Finished iteration: " << ((sc_time_stamp()-start)/clock_period) << std::endl; 
    }

    sc_stop();
  }
  
  void dataIn() {

    ready_in = true;
    do {
      wait();
    } while (!valid_in);

    // Input signals valid -> store them
    y = y_in;

    ready_in = false;
    // wait();
  }

  void dataOut() {
    // wait until peer is ready
    do {
      wait();
    } while(!ready_out);

    // set data and flag
    x0_out = 0;
    u0_out = 1;
    y0_out = 0;
    dx_out = 0.1;
    a_out = a;
    valid_out = true;

    // wait until peer has stored the data
    do {
      wait();
    } while(ready_out);

    // reset data and flag
    x0_out = 0;
    u0_out = 0;
    y0_out = 0;
    dx_out = 0;
    a_out = 0;
    valid_out = false;
    // wait();
  }

};

#endif // INCLUDED_EQUATION_SOLVER_TEST_HPP
