#ifndef INCLUDED_RESOURCES_HPP
#define INCLUDED_RESOURCES_HPP

#include "datatypes.hpp"
    
// Addierer
SC_MODULE(Add) {
public:
  sc_in<eq_fixed_t> in1;
  sc_in<eq_fixed_t> in2;
  sc_out<eq_fixed_t> out;

  SC_CTOR(Add) {
    SC_METHOD(update);
    sensitive << in1 << in2;

    SC_METHOD(present);
    sensitive << delay;
    dont_initialize();
  }

private:
  sc_event delay;

  void update() {
    delay.cancel();
    delay.notify(sc_time(2, SC_NS));
  }
  void present() { out = in1 + in2; }
};

// Subtrahierer
SC_MODULE(Sub) {
public:
  sc_in<eq_fixed_t> in1;
  sc_in<eq_fixed_t> in2;
  sc_out<eq_fixed_t> out;

  SC_CTOR(Sub) {
    SC_METHOD(update);
    sensitive << in1 << in2;

    SC_METHOD(present);
    sensitive << delay;
    dont_initialize();
  }

private:
  sc_event delay;

  void update() {
    delay.cancel();
    delay.notify(sc_time(2, SC_NS));
  }
  void present() { out = in1 - in2; }
};

// Multiplizierer
SC_MODULE(Mul) {
public:
  sc_in<eq_fixed_t> in1;
  sc_in<eq_fixed_t> in2;
  sc_out<eq_fixed_t> out;

  SC_CTOR(Mul) {
    SC_METHOD(update);
    sensitive << in1 << in2;

    SC_METHOD(present);
    sensitive << delay;
    dont_initialize();
  }

private:
  sc_event delay;

  void update() {
    delay.cancel();
    delay.notify(sc_time(10, SC_NS));
  }
  void present() { out = in1 * in2; }
};

// Komparator (in1 > in2)
SC_MODULE(Gt) {
public:
  sc_in<eq_fixed_t> in1;
  sc_in<eq_fixed_t> in2;
  sc_out<bool> out;

  SC_CTOR(Gt) {
    SC_METHOD(update);
    sensitive << in1 << in2;

    SC_METHOD(present);
    sensitive << delay;
    dont_initialize();
  }

private:
  sc_event delay;

  void update() {
    delay.cancel();
    delay.notify(sc_time(1.5, SC_NS));
  }
  void present() { out = in1 > in2; }
};

// Komparator (in1 >= in2)
SC_MODULE(Ge) {
public:
  sc_in<eq_fixed_t> in1;
  sc_in<eq_fixed_t> in2;
  sc_out<bool> out;
  
  SC_CTOR(Ge) {
    SC_METHOD(update);
    sensitive << in1 << in2;

    SC_METHOD(present);
    sensitive << delay;
    dont_initialize();
  }

private:
  sc_event delay;

  void update() {
    delay.cancel();
    delay.notify(sc_time(1.5, SC_NS));
  }
  void present() { out = in1 >= in2; }
};

SC_MODULE(Mux) {
public:
  sc_in<bool> sel;
  // Wird weitergeleitet falls sel = 0
  sc_in<eq_fixed_t> in0;
  // Wird weitergelitet falls sel = 1
  sc_in<eq_fixed_t> in1;
  sc_out<eq_fixed_t> out;
  
  SC_CTOR(Mux) {
    SC_METHOD(update);
    sensitive << in0 << in1 << sel;

    SC_METHOD(present);
    sensitive << delay;
    dont_initialize();
  }

private:
  sc_event delay;

  void update() {
    delay.cancel();
    delay.notify(sc_time(1, SC_NS));
  }
  void present() { out = sel ? in1 : in0; }
};


SC_MODULE(Reg) {
public:
  // Dateneingang
  sc_in<eq_fixed_t> d;
  // Gespeicherter Wert
  sc_out<eq_fixed_t> q;
  // d wird bei pos. Taktflanke übernommen, falls ce = 1 (clock enable)
  sc_in<bool> ce;
  // Clock
  sc_in<bool> clk;

  SC_CTOR(Reg) {
    SC_METHOD(update);
    dont_initialize();
    sensitive << clk.pos();
  }

private:
  void update() {
    //std::cout << "Reg::go()" << std::endl;
    if(ce) q = d;
  }
};

#endif // INCLUDED_RESOURCES_HPP
