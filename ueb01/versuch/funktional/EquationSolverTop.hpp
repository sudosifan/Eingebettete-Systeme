#ifndef INCLUDED_EQUATION_SOLVER_TOP
#define INCLUDED_EQUATION_SOLVER_TOP

#include "EquationSolver.hpp"
#include "EquationSolverTest.hpp"

SC_MODULE(EquationSolverTop) {
public:
  SC_CTOR(EquationSolverTop)
    : solver("solver"),
      test("test"),
      clk("CLK", 5, SC_NS)
  {
    solver.x0_in(x0);
    solver.u0_in(u0);
    solver.y0_in(y0);
    solver.dx_in(dx);
    solver.a_in(a);
    solver.y_out(y);
    solver.clk(clk);
    solver.rst(rst); 
    solver.valid_in(valid_req);
    solver.ready_in(ready_req);
    solver.valid_out(valid_res);
    solver.ready_out(ready_res);

    test.x0_out(x0);
    test.u0_out(u0);
    test.y0_out(y0);
    test.dx_out(dx);
    test.a_out(a);
    test.y_in(y);
    test.clk(clk);
    test.rst(rst); 
    test.valid_in(valid_res);
    test.ready_in(ready_res);
    test.valid_out(valid_req);
    test.ready_out(ready_req);
  }

private:
  EquationSolver solver;
  EquationSolverTest test;

  sc_signal<eq_fixed_t> x0;
  sc_signal<eq_fixed_t> u0;
  sc_signal<eq_fixed_t> y0;
  sc_signal<eq_fixed_t> dx;
  sc_signal<eq_fixed_t> a;
  sc_signal<eq_fixed_t> y;

  // Clock/Reset Signale
  sc_clock clk;
  sc_signal<bool> rst;

  // Handshake-Protokoll für Requests
  sc_signal<bool> valid_req;
  sc_signal<bool> ready_req;

  // Handshake-Protokoll für Ergebnisse
  sc_signal<bool> valid_res;
  sc_signal<bool> ready_res;
};

#endif // INCLUDED_EQUATION_SOLVER_TOP
