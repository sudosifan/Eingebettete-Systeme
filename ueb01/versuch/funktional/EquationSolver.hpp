#ifndef INCLUDED_EQUATION_SOLVER_HPP
#define INCLUDED_EQUATION_SOLVER_HPP

#include "datatypes.hpp"

SC_MODULE(EquationSolver) {
public:
  // Eingangssignale
  sc_in<eq_fixed_t> x0_in;
  sc_in<eq_fixed_t> u0_in;
  sc_in<eq_fixed_t> y0_in;
  sc_in<eq_fixed_t> dx_in;
  sc_in<eq_fixed_t> a_in;

  // Ausgangssignale
  sc_out<eq_fixed_t> y_out;

  // Clock/Reset Signale
  sc_in<bool> clk;
  sc_in<bool> rst;

  // Handshake-Protokoll für Eingangssignale
  sc_in<bool> valid_in;
  sc_out<bool> ready_in;

  // Handshake-Protokoll für Ausgangssignale
  sc_out<bool> valid_out;
  sc_in<bool> ready_out;

  // Konstruktor
  SC_CTOR(EquationSolver) {
    // main ist sensitiv auf positive Taktflanke
    SC_CTHREAD(main, clk.pos());
    // Active-Low reset
    reset_signal_is(rst, false);
  }

private:
  // Variablen -> Diese werden zu Registern in der strukturellen
  // Implementierung
  eq_fixed_t x, u, y;
  eq_fixed_t x1, u1, y1;
  eq_fixed_t a, dx;

  void main() {

    // Reset-Funktionalität sind alle Anweisungen bis zum ersten Aufruf von
    // wait().
    reset();

    while(true) {
      // Lese Eingangssignale in Register ein
      dataIn();

      // TODO:
      // Approximiere den Wert von y. Dazu sind iterativ die neuen Werte x1, u1
      // und y1 aus den alten Werten x, u und y zu berechnen. Anschließend
      // können die alten Werte mit den neuen Werten überschrieben werden.
      // (Hinweis: es werden ausschließlich die Variablen x, u, y, x1, u1, y1,
      // sowie a und dx benötigt!)

      ...

      // Schreibe Aussgangssignale
      dataOut();
    }
  }

  void reset() {
    y_out = 0;
    valid_out = false;
    wait();
  }

  void dataIn() {
    ready_in = true;
    do {
      wait();
    } while (!valid_in);

    // Input signals valid -> store them
    x = x0_in;
    u = u0_in;
    y = y0_in;
    a = a_in;
    dx = dx_in;
    
    ready_in = false;
  }
  
  void dataOut() {
    // wait until peer is ready
    do {
      wait();
    } while(!ready_out);

    // set data and flag
    y_out = y;
    valid_out = true;

    // wait until peer has stored the data
    do {
      wait();
    } while(ready_out);

    // reset data and flag
    y_out = 0;
    valid_out = false;
  }
};

#endif // INCLUDED_EQUATION_SOLVER_HPP
