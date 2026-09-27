#ifndef INCLUDED_EQUATION_SOLVER_HPP
#define INCLUDED_EQUATION_SOLVER_HPP

#include "datatypes.hpp"
#include "Resources.hpp"

SC_MODULE(EquationSolver) {
public:
    typedef eq_fixed_t T;

    // Eingangssignale
    sc_in<T> x0_in;
    sc_in<T> uo_in;
    sc_in<T> yo_in;
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
    // Komponenten instantiieren
    Add add;          // Addierer
    Sub sub;          // Subtrahierer
    Ge  cmp;          // Komparator (>=)
    Mul mul1;         // Multiplizierer 1
    Mul mul2;         // Multiplizierer 2
    Mul mul3;         // Multiplizierer 3

    Reg ra;           // Register für Eingangssignal a
    Reg rdx;          // Register für Eingangssignal dx
    Reg rx;           // Register für Eingangssignal/Variable x
    Reg ry;           // Register für Eingangssignal/Variable y
    Reg ru;           // Register für Eingangssignal/Variable u
    Reg r1;           // Register für Zwischenergebnis z1
    Reg r2;           // Register für Zwischenergebnis z2
    Reg r3;           // Register für Zwischenergebnis z3
    Reg r4;           // Register für Zwischenergebnis z4
    Reg r5;           // Register für Zwischenergebnis z5
    Reg r6;           // Register für Zwischenergebnis z6

    Mux mx;           // Multiplexer vor Register rx (Port d)
    Mux my;           // Multiplexer vor Register ry (Port d)
    Mux mu;           // Multiplexer vor Register ru (Port d)
    Mux ma1;          // Multiplexer vor Addierer (Port in1)
    Mux ma2;          // Multiplexer vor Addierer (Port in2)
    Mux ms1;          // Multiplexer vor Subtrahierer (Port in1)
    Mux ms2;          // Multiplexer vor Subtrahierer (Port in2)
    Mux mm11;         // Multiplexer vor Multiplizierer 1 (Port in1)
    Mux mm12;         // Multiplexer vor Multiplizierer 1 (Port in2)
    Mux mm21;         // Multiplexer vor Multiplizierer 2 (Port in1)
    Mux mm22;         // Multiplexer vor Multiplizierer 2 (Port in2)

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
    sc_signal<bool> cmp_out;

    // Multiplizierer 1
    sc_signal<T> mul1_in1;
    sc_signal<T> mul1_in2;
    sc_signal<T> mul1_out;

    // Multiplizierer 2
    sc_signal<T> mul2_in1;
    sc_signal<T> mul2_in2;
    sc_signal<T> mul2_out;

    // Multiplizierer 3
    sc_signal<T> mul3_out;

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
    sc_signal<T> r1_q;
    sc_signal<bool> r1_ce;

    // Register r2
    sc_signal<T> r2_q;
    sc_signal<bool> r2_ce;

    // Register r3
    sc_signal<T> r3_q;
    sc_signal<bool> r3_ce;

    // Register r4
    sc_signal<T> r4_q;
    sc_signal<bool> r4_ce;

    // Register r5
    sc_signal<T> r5_q;
    sc_signal<bool> r5_ce;

    // Register r6
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
    sc_signal<bool> mm21_sel;
    sc_signal<bool> mm22_sel;

    // Konstanten
    sc_signal<T> const_3;

public:
    SC_CTOR(EquationSolver)
        : add("add"),
          sub("sub"),
          cmp("cmp"),
          mul1("mul1"),
          mul2("mul2"),
          mul3("mul3"),
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
          mm21("mm21"),
          mm22("mm22")
    {
        SC_CTHREAD(main, clk.pos());
        reset_signal_is(rst, false);

        // Ports mit Ports/Signalen verknüpfen
        add.in1(add_in1);
        add.in2(add_in2);
        add.out(add_out);

        sub.in1(sub_in1);
        sub.in2(sub_in2);
        sub.out(sub_out);

        cmp.in1(rx_q);
        cmp.in2(ra_q);
        cmp.out(cmp_out);

        mul1.in1(mul1_in1);
        mul1.in2(mul1_in2);
        mul1.out(mul1_out);

        mul2.in1(mul2_in1);
        mul2.in2(mul2_in2);
        mul2.out(mul2_out);

        mul3.in1(ru_q);
        mul3.in2(rdx_q);
        mul3.out(mul3_out);

        ra.d(a_in);
        ra.q(ra_q);
        ra.ce(ra_ce);
        ra.clk(clk);

        rdx.d(dx_in);
        rdx.q(rdx_q);
        rdx.ce(rdx_ce);
        rdx.clk(clk);

        rx.d(rx_d);
        rx.q(rx_q);
        rx.ce(rx_ce);
        rx.clk(clk);

        ry.d(ry_d);
        ry.q(ry_q);
        ry.ce(ry_ce);
        ry.clk(clk);

        ru.d(ru_d);
        ru.q(ru_q);
        ru.ce(ru_ce);
        ru.clk(clk);

        r1.d(mul1_out);
        r1.q(r1_q);
        r1.ce(r1_ce);
        r1.clk(clk);

        r2.d(mul2_out);
        r2.q(r2_q);
        r2.ce(r2_ce);
        r2.clk(clk);

        r3.d(mul3_out);
        r3.q(r3_q);
        r3.ce(r3_ce);
        r3.clk(clk);

        r4.d(mul1_out);
        r4.q(r4_q);
        r4.ce(r4_ce);
        r4.clk(clk);

        r5.d(mul2_out);
        r5.q(r5_q);
        r5.ce(r5_ce);
        r5.clk(clk);

        r6.d(sub_out);
        r6.q(r6_q);
        r6.ce(r6_ce);
        r6.clk(clk);

        mx.in0(x0_in);
        mx.in1(add_out);
        mx.out(rx_d);
        mx.sel(mx_sel);

        my.in0(yo_in);
        my.in1(add_out);
        my.out(ry_d);
        my.sel(my_sel);

        mu.in0(uo_in);
        mu.in1(sub_out);
        mu.out(ru_d);
        mu.sel(mu_sel);

        ma1.in0(r3_q);
        ma1.in1(rx_q);
        ma1.out(add_in1);
        ma1.sel(ma1_sel);

        ma2.in0(ry_q);
        ma2.in1(rdx_q);
        ma2.out(add_in2);
        ma2.sel(ma2_sel);

        ms1.in0(ru_q);
        ms1.in1(r6_q);
        ms1.out(sub_in1);
        ms1.sel(ms1_sel);

        ms2.in0(r5_q);
        ms2.in1(r4_q);
        ms2.out(sub_in2);
        ms2.sel(ms2_sel);

        mm11.in0(const_3);
        mm11.in1(rdx_q);
        mm11.out(mul1_in1);
        mm11.sel(mm11_sel);

        mm12.in0(ry_q);
        mm12.in1(r1_q);
        mm12.out(mul1_in2);
        mm12.sel(mm12_sel);

        mm21.in0(const_3);
        mm21.in1(r2_q);
        mm21.out(mul2_in1);
        mm21.sel(mm21_sel);

        mm22.in0(rx_q);
        mm22.in1(r3_q);
        mm22.out(mul2_in2);
        mm22.sel(mm22_sel);

        const_3 = 3;

        // Trace-Datei öffnen
        tf = sc_create_vcd_trace_file("sim");
        sc_trace(tf, clk, "CLOCK");
        sc_trace(tf, ready_in, "READY_IN");
        sc_trace(tf, valid_in, "VALID_IN");
        sc_trace(tf, ready_out, "READY_OUT");
        sc_trace(tf, valid_out, "VALID_OUT");
        sc_trace(tf, x0_in, "X0_IN");
        sc_trace(tf, uo_in, "UO_IN");
        sc_trace(tf, yo_in, "YO_IN");
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
        sc_close_vcd_trace_file(tf);
    }

private:
    sc_trace_file* tf;

    void main() {
        reset();
        while(true) {
            dataIn();
            while(true) {
                // t = 0
                mm11_sel = 0;
                mm12_sel = 0;
                mm21_sel = 0;
                mm22_sel = 0;
                wait();

                // t = 1
                if(cmp_out) break; // x >= a
                wait();

                // t = 2
                ma1_sel = 1;
                ma2_sel = 1;
                mx_sel = 1;
                rx_ce = 1;
                r1_ce = 1;
                r2_ce = 1;
                r3_ce = 1;
                wait();

                // t = 3
                mm11_sel = 1;
                mm12_sel = 1;
                mm21_sel = 1;
                mm22_sel = 1;
                ma1_sel = 0;
                ma2_sel = 0;
                my_sel = 1;
                ry_ce = 1;
                r1_ce = 0;
                r2_ce = 0;
                r3_ce = 0;
                rx_ce = 0;
                wait();

                // t = 4
                ry_ce = 0;
                wait();

                // t = 5
                r4_ce = 1;
                r5_ce = 1;
                wait();

                // t = 6
                ms1_sel = 0;
                ms2_sel = 0;
                r6_ce = 1;
                r4_ce = 0;
                r5_ce = 0;
                wait();

                // t = 7
                ms1_sel = 1;
                ms2_sel = 1;
                mu_sel = 1;
                ru_ce = 1;
                r6_ce = 0;
                wait();

                // t = 8
                ru_ce = 0;
                break;
            }
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

        rx_ce = 0;
        ru_ce = 0;
        ry_ce = 0;
        ra_ce = 0;
        rdx_ce = 0;
        ready_in = false;
    }

    void dataOut() {
        do {
            wait();
        } while(!ready_out);

        y_out = ry_q;
        valid_out = true;

        do {
            wait();
        } while(ready_out);

        y_out = 0;
        valid_out = false;
    }
};

#endif // INCLUDED_EQUATION_SOLVER_HPP