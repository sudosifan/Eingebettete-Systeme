#ifdef __RTL_SIMULATION__
#include "EquationSolver_rtl_wrapper.h"
#define EquationSolver EquationSolver_rtl_wrapper
#else
#include "EquationSolver.h"
#endif




//#define SC_INCLUDE_FX
//#include <systemc>
//#include "datatypes.h"
#include "stimuli.h"

int sc_main(int argc, char* argv[] )
{


    sc_core::sc_clock s_clk("s_clk",10,sc_core::SC_NS);
    sc_core::sc_signal< bool >             rst;
    sc_core::sc_signal< bool >             valid_in;
    sc_core::sc_signal< bool >            ready_in;
    sc_core::sc_signal< eq_fixed_t >  x0_in;
    sc_core::sc_signal< eq_fixed_t >  u0_in;
    sc_core::sc_signal< eq_fixed_t >  y0_in;
    sc_core::sc_signal< bool >            valid_out;
    sc_core::sc_signal< bool >             ready_out;
    sc_core::sc_signal< eq_fixed_t > y_out;
    sc_core::sc_signal< eq_fixed_t >  dx_in;
    sc_core::sc_signal< eq_fixed_t >  a_in;
    sc_core::sc_signal< eq_fixed_t > const3_out;
    EquationSolver *solver = new EquationSolver("EquationSolver");
    stimuli *itb = new stimuli("stimuli");

    solver->const3_in(const3_out);
  const3_out.write(eq_fixed_t(3));
    itb->rst(rst);
    itb->clk(s_clk);
    itb->valid_in(valid_in);
    itb->ready_in(ready_in);
    itb->x0_in(x0_in);
    itb->u0_in(u0_in);
    itb->y0_in(y0_in);
    itb->valid_out(valid_out);
    itb->ready_out(ready_out);
    itb->y_out(y_out);
    itb->dx_in(dx_in);
    itb->a_in(a_in);


    solver->rst(rst);
    solver->clk(s_clk);
    solver->valid_in(valid_in);
    solver->ready_in(ready_in);
    solver->x0_in(x0_in);
    solver->u0_in(u0_in);
    solver->y0_in(y0_in);
    solver->valid_out(valid_out);
    solver->ready_out(ready_out);
    solver->y_out(y_out);
    solver->dx_in(dx_in);
    solver->a_in(a_in);

   // int end_time = 200;
 sc_core::sc_start();
 const3_out.write(eq_fixed_t(3)); 
 return 0;
}

