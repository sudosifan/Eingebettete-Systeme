#ifndef STIMULI_H_INCLUDED
#define STIMULI_H_INCLUDED


#define SC_INCLUDE_FX
#include <systemc>

//#include <cynw_fixed.h>



//#include <systemc.h>
//#include <esc.h>
//#include <cynw_fixed.h>
//#include "datatypes.h"

typedef sc_dt::sc_fixed<32,16> eq_fixed_t;

SC_MODULE(stimuli)
{

	sc_core::sc_in< bool >             clk;
	sc_core::sc_out< bool >            rst;
  //notice: port naming corresponds DUT names
  // valid_in is an input to the DUT, but an output of the TB
	sc_core::sc_out< bool >            valid_in;
	sc_core::sc_in< bool >             ready_in;
	sc_core::sc_out< eq_fixed_t > x0_in;
	sc_core::sc_out< eq_fixed_t > u0_in;
	sc_core::sc_out< eq_fixed_t > y0_in;
	sc_core::sc_in< bool >             valid_out;
	sc_core::sc_out< bool >            ready_out;
	sc_core::sc_in< eq_fixed_t >  y_out;
	sc_core::sc_out< eq_fixed_t > dx_in;
	sc_core::sc_out< eq_fixed_t > a_in;





  SC_CTOR(stimuli) {
    SC_CTHREAD(source, clk.pos());
  }



  void source()

{

  FILE *fd;
  fd = fopen("sim_out.log", "w");

  // Reset the DUT.
  rst.write( 0 );
  wait(5);
  rst.write( 1 );

  eq_fixed_t step = 0.1;
  for(eq_fixed_t a = 0; a<10; a=a+step) {
    // wait till DUT is ready
    do {
      wait();
    } while(!ready_in.read());
    //std::cout<<"Sending new a: "<<a<<"\n";
    // write initial data
    //x0_out = 0;  u0_out = 1;  y0_out = 0;  dx_out = 0.1;
    x0_in.write(0);
    u0_in.write(1);
    y0_in.write(0);
    dx_in.write(0.1);
    a_in.write(a);
    valid_in.write(true);

    // wait till DUT has read inputs
     do {
      wait();
    } while(ready_in.read());
    valid_in.write(false);

    // wait till DUT is ready and read data
    ready_out.write(true);
    do {
      wait();
    } while(!valid_out.read());

    fprintf(fd, "%f %f\n", a.to_double(), y_out.read().to_double());
   

    // obey the protocol
    wait(1);
    ready_out.write(false);
  }


  fclose(fd);
  sc_core::sc_stop();
}
};

#endif // TB_H_INCLUDED
