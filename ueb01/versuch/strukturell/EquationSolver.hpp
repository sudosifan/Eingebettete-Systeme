#ifndef INCLUDED_EQUATION_SOLVER_HPP
#define INCLUDED_EQUATION_SOLVER_HPP

#include "datatypes.hpp"
#include "Resources.hpp"

SC_MODULE(EquationSolver) {
public:
  typedef eq_fixed_t T;

  // Eingangssignale
  sc_in<T> x0_in;
  sc_in<T> u0_in;
  sc_in<T> y0_in;
  sc_in<T> dx_in;
  sc_in<T> a_in;

  // Ausgangssignale
  sc_out<T> y_out;

  // Clock/Reset Signale
  sc_in<bool> clk;
  sc_in<bool> rst;

  // Handshake-Protokoll für Eingangssignale
  sc_in<bool> valid_in;
  sc_out<bool> ready_in;

  // Handshake-Protokoll für Ausgangssignale
  sc_out<bool> valid_out;
  sc_in<bool> ready_out;

private:
  // TODO:
  // Komponenten instanttiieren
  
  Add add;  // Addierer
  Sub sub;  // Subtrahierer
  Ge cmp;   // Komparator (>=)
  Mul mul1; // Multiplizierer 1
  ...

  Reg ra;   // Register für Eingangssignal a
  Reg rdx;  // Register für Eingangssignal dx
  Reg rx;   // Register für Eingangssignal/Variable x
  Reg ry;   // Register für Eingangssignal/Variable y
  Reg ru;   // Register für Eingangssignal/Variable u
  Reg r1;   // Register für Zwischenergebnis z1
  Reg r2;   // Register für Zwischenergebnis z2
  Reg r3;   // Register für Zwischenergebnis z3
  Reg r4;   // Register für Zwischenergebnis z4
  Reg r5;   // Register für Zwischenergebnis z5
  Reg r6;   // Register für Zwischenergebnis z6

  Mux mx;   // Multiplexer vor Register rx (Port d)
  Mux my;   // Multiplexer vor Register ry (Port d)
  Mux mu;   // Multiplexer vor Register ru (Port d)
  Mux ma1;  // Multiplexer vor Addierer (Port in1)
  Mux ma2;  // Multiplexer vor Addierer (Port in2)
  Mux ms1;  // Multiplexer vor Subtrahierer (Port in1)
  Mux ms2;  // Multiplexer vor Subtrahierer (Port in2)
  Mux mm11; // Multiplexer vor Multiplizierer 1 (Port in1)
  Mux mm12; // Multiplexer vor Multiplizierer 1 (Port in2)
  ...

  // TODO:
  // Signale instantiieren
  
  // Addierer
  sc_signal<T> add_in1;
  sc_signal<T> add_in2;
  sc_signal<T> add_out;

  // Subtrahierer
  sc_signal<T> sub_in1;
  sc_signal<T> sub_in2;
  sc_signal<T> sub_out;
  
  // Komparator
  //sc_signal<T> cmp_in1; -> ra_q
  //sc_signal<T> cmp_in2; -> rx_q
  sc_signal<bool> cmp_out;
  
  // Multiplizerer 1
  sc_signal<T> mul1_in1;
  sc_signal<T> mul1_in2;
  sc_signal<T> mul1_out;
  
  ...  

  // Register ra
  sc_signal<T> ra_d;
  sc_signal<T> ra_q;
  sc_signal<bool> ra_ce;
  
  // Register rdx
  sc_signal<T> rdx_d;
  sc_signal<T> rdx_q;
  sc_signal<bool> rdx_ce;
  
  // Register rx
  sc_signal<T> rx_d;
  sc_signal<T> rx_q;
  sc_signal<bool> rx_ce;
  
  // Register ry
  sc_signal<T> ry_d;
  sc_signal<T> ry_q;
  sc_signal<bool> ry_ce;
  
  // Register ru
  sc_signal<T> ru_d;
  sc_signal<T> ru_q;
  sc_signal<bool> ru_ce;
  
  // Register r1
  //sc_signal<T> r1_d; -> mul?_out
  sc_signal<T> r1_q;
  sc_signal<bool> r1_ce;
  
  // Register r2
  //sc_signal<T> r2_d; -> mul?_out
  sc_signal<T> r2_q;
  sc_signal<bool> r2_ce;
  
  // Register r3
  //sc_signal<T> r3_d; -> mul?_out
  sc_signal<T> r3_q;
  sc_signal<bool> r3_ce;
  
  // Register r4
  //sc_signal<T> r4_d; -> mul?_out
  sc_signal<T> r4_q;
  sc_signal<bool> r4_ce;
  
  // Register r5
  //sc_signal<T> r5_d; -> mul?_out
  sc_signal<T> r5_q;
  sc_signal<bool> r5_ce;
  
  // Register r6
  //sc_signal<T> r6_d; -> sub_out
  sc_signal<T> r6_q;
  sc_signal<bool> r6_ce;

  // Auswahlsignale für Multiplexer
  sc_signal<bool> mx_sel;
  sc_signal<bool> my_sel;
  sc_signal<bool> mu_sel;
  sc_signal<bool> ma1_sel;
  sc_signal<bool> ma2_sel;
  sc_signal<bool> ms1_sel;
  sc_signal<bool> ms2_sel;
  sc_signal<bool> mm11_sel;
  sc_signal<bool> mm12_sel;
  
  ...

  // Konstanten -> Werden entsprechend im Konstruktor initialisiert
  sc_signal<T> const_3;
  
public:
  // TODO: Konstruktoraufrufe für Komponenten
  SC_CTOR(EquationSolver)
    : add("add"),
      sub("sub"),
      cmp("cmp"),
      mul1("mul1"),
      ...
      ra("ra"),
      rdx("rdx"),
      rx("rx"),
      ry("ry"),
      ru("ru"),
      r1("r1"),
      r2("r2"),
      r3("r3"),
      r4("r4"),
      r5("r5"),
      r6("r6"),
      mx("mx"),
      my("my"),
      mu("mu"),
      ma1("ma1"),
      ma2("ma2"),
      ms1("ms1"),
      ms2("ms2"),
      mm11("mm11"),
      mm12("mm12"),
      ...
  {
    SC_CTHREAD(main, clk.pos());
    reset_signal_is(rst, false);

    // TODO: Ports mit Ports/Signalen verknüpfen
    
    // Addierer
    add.in1(add_in1);
    add.in2(add_in2);
    add.out(add_out);
  
    // Subtrahierer
    sub.in1(sub_in1);
    sub.in2(sub_in2);
    sub.out(sub_out);

    // Komparator
    cmp.in1(rx_q);
    cmp.in2(ra_q);
    cmp.out(cmp_out);

    // Multiplizierer 1
    mul1.in1(mul1_in1);
    mul1.in2(mul1_in2);
    mul1.out(mul1_out);
   
    ... 
    
    // Register ra
    ra.d(a_in);
    ra.q(ra_q);
    ra.ce(ra_ce);
    ra.clk(clk);

    // Register rdx
    rdx.d(dx_in);
    rdx.q(rdx_q);
    rdx.ce(rdx_ce); 
    rdx.clk(clk);
    
    // Register rx
    rx.d(rx_d);
    rx.q(rx_q);
    rx.ce(rx_ce); 
    rx.clk(clk);

    // Register ry
    ry.d(ry_d);
    ry.q(ry_q);
    ry.ce(ry_ce); 
    ry.clk(clk);
    
    // Register ru
    ru.d(ru_d);
    ru.q(ru_q);
    ru.ce(ru_ce); 
    ru.clk(clk);

    // Register r1
    r1.d(mul1_out);
    r1.q(r1_q);
    r1.ce(r1_ce); 
    r1.clk(clk);
    
    // Register r2
    r2.d(mul2_out);
    r2.q(r2_q);
    r2.ce(r2_ce); 
    r2.clk(clk);
    
    // Register r3
    r3.d(mul3_out);
    r3.q(r3_q);
    r3.ce(r3_ce); 
    r3.clk(clk);

    // Register r4
    r4.d(mul1_out);
    r4.q(r4_q);
    r4.ce(r4_ce); 
    r4.clk(clk);

    // Register r5
    r5.d(mul2_out);
    r5.q(r5_q);
    r5.ce(r5_ce); 
    r5.clk(clk);
    
    // Register r6
    r6.d(sub_out);
    r6.q(r6_q);
    r6.ce(r6_ce); 
    r6.clk(clk);
    

    // Multiplexer mx vor rx
    mx.in0(x0_in);
    mx.in1(add_out);
    mx.out(rx_d);
    mx.sel(mx_sel);
    
    // Multiplexer my vor ry
    my.in0(y0_in);
    my.in1(add_out);
    my.out(ry_d);
    my.sel(my_sel);
    
    // Multiplexer mu vor ru
    mu.in0(u0_in);
    mu.in1(sub_out);
    mu.out(ru_d);
    mu.sel(mu_sel);
    
    // Multiplexer ma1 vor add.in1
    ma1.in0(r3_q);
    ma1.in1(rx_q);
    ma1.out(add_in1);
    ma1.sel(ma1_sel);
    
    // Multiplexer ma2 vor add.in2
    ma2.in0(ry_q);
    ma2.in1(rdx_q);
    ma2.out(add_in2);
    ma2.sel(ma2_sel);
    
    // Multiplexer ms1 vor sub.in1
    ms1.in0(ru_q);
    ms1.in1(r6_q);
    ms1.out(sub_in1);
    ms1.sel(ms1_sel);
    
    // Multiplexer ms2 vor sub.in2
    ms2.in0(r5_q);
    ms2.in1(r4_q);
    ms2.out(sub_in2);
    ms2.sel(ms2_sel);
   
    // Multiplexer mm11 vor mul1.in1
    mm11.in0(...);
    mm11.in1(...);
    mm11.out(mul1_in1);
    mm11.sel(mm11_sel);
  
    // Multiplexer mm12 vor mul1.in2
    mm12.in0(...);
    mm12.in1(...);
    mm12.out(mul1_in2);
    mm12.sel(mm12_sel);

    ... 
   
    // Konstante Signalwerte initialisieren
    const_3 = 3;

    // Trace-Datei öffnen
    tf = sc_create_vcd_trace_file("sim");

    // TODO: Signale zum Trace hinzufügen
    sc_trace(tf, clk, "CLOCK");
    sc_trace(tf, ready_in, "READY_IN");
    sc_trace(tf, valid_in, "VALID_IN");
    sc_trace(tf, ready_out, "READY_OUT");
    sc_trace(tf, valid_out, "VALID_OUT");
    sc_trace(tf, x0_in, "X0_IN");
    sc_trace(tf, u0_in, "U0_IN");
    sc_trace(tf, y0_in, "Y0_IN");
    sc_trace(tf, dx_in, "DX_IN");
    sc_trace(tf, a_in, "A_IN");
    sc_trace(tf, ra_q, "RA_Q");
    sc_trace(tf, rdx_q, "RDX_Q");
    sc_trace(tf, rx_q, "RX_Q");
    sc_trace(tf, ru_q, "RU_Q");
    sc_trace(tf, ry_q, "RY_Q");
    sc_trace(tf, r1_q, "R1_Q");
    sc_trace(tf, r2_q, "R2_Q");
    sc_trace(tf, r3_q, "R3_Q");
    sc_trace(tf, r4_q, "R4_Q");
    sc_trace(tf, r5_q, "R5_Q");
    sc_trace(tf, r6_q, "R6_Q");
    sc_trace(tf, mul1_out, "MUL1_OUT");
    sc_trace(tf, mul2_out, "MUL2_OUT");
    sc_trace(tf, mul3_out, "MUL3_OUT");
    sc_trace(tf, add_out, "ADD_OUT");
    sc_trace(tf, sub_out, "SUB_OUT");
    sc_trace(tf, cmp_out, "CMP_OUT");
  }

  ~EquationSolver() {
    // Trace-Datei schließen
    sc_close_vcd_trace_file(tf);
  }

private:
  sc_trace_file* tf;

  void main() {

    reset();


    while(true) {
      // Lese Eingangssignale in Register ein
      dataIn();

      while(true) {
        
        // TODO: Setze CLOCK_ENABLE-Signale der Register und SEL-Signale der
        // Multiplexer. Hinweis: Das sind genau die folgenden Signale:
        // ra_ce
        // rdx_ce
        // rx_ce
        // ry_ce
        // ru_ce
        // r1_ce
        // r2_ce
        // r3_ce
        // r4_ce
        // r5_ce
        //
        // mx_sel
        // my_sel
        // mu_sel
        // ma1_sel
        // ma2_sel
        // ms1_sel
        // ms2_sel
        // mm11_sel
        // mm12_sel
        // ...
        
        // t = 0
        // Gestartete Operationen:
        //  v1 (Multiplexer mm11_sel, mm12_sel)
        mm11_sel = ...;
        mm12_sel = ...;
        //  v10 (Keine Multiplexer vorgeschaltet, im nächsten Zustand fertig)
        ...
        // Laufende Operationen:
        ...
        // Beendete Operationen:
        ...

        wait();
        // t = 1
        // Gestartete Operationen:
        ...
        // Laufende Operationen:
        //  v1
        ...
        // Beendete Operationen:
        //  v10
        if(cmp_out) break; // x >= a
        ...
       
        wait();
        // t = 2
        // Gestartete Operationen:
        ...
        // Laufende Operationen:
        //  v1 (im nächsten Zustand fertig)
        r1_ce = 1;
        ...
        // Beendete Operationen:
        ...

        wait();
        // t = 3
        // Gestartete Operationen:
        ...
        // Laufende Operationen:
        ...
        // Beendete Operationen:
        //  v1
        r1_ce = 0;
        ...

        wait();
        // t = 4
        // Gestartete Operationen:
        ...
        // Laufende Operationen:
        ...
        // Beendete Operationen:
        ...

        wait();
        // t = 5
        // Gestartete Operationen:
        ...
        // Laufende Operationen:
        ...
        // Beendete Operationen:
        ...

        wait();
        // t = 6
        // Gestartete Operationen:
        ...
        // Laufende Operationen:
        ...
        // Beendete Operationen:
        ...

        wait();
        // t = 7
        // Gestartete Operationen:
        ...
        // Laufende Operationen:
        ...
        // Beendete Operationen:
        ...

        wait();
        // t = 8
        // Gestartete Operationen:
        ...
        // Laufende Operationen:
        ...
        // Beendete Operationen:
        ...
      }
      
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
    
    mx_sel = 0;
    mu_sel = 0;
    my_sel = 0;
    
    rx_ce = 1;
    ru_ce = 1;
    ry_ce = 1;
    ra_ce = 1;
    rdx_ce = 1;
    
    ready_in = true;
    do {
      wait();
    } while (!valid_in);

    // Input signals stored
    rx_ce = 0;
    ru_ce = 0;
    ry_ce = 0;
    ra_ce = 0;
    rdx_ce = 0;
    
    ready_in = false;
  }
  
  void dataOut() {
    // wait until peer is ready
    do {
      wait();
    } while(!ready_out);

    // set data and flag
    y_out = ry_q;
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
