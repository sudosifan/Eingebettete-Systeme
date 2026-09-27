#include "EquationSolver.h"

//////////////////////////////////////////////////////////////////////
// EquationSolver.cc - single thread SC_MODULE 
//////////////////////////////////////////////////////////////////////

//
// reset() - EquationSolver reset code
//
// Every SC_CTHREAD to be synthesized must implement reset using a
// global reset_signal_is statement (in the constructor). The reset
// functionality itself consists of a single CYN_PROTOCOL block that
// contains a single wait() call at the end. This code can be placed
// in a reset function, which is called at the top of thread0(). All
// functionality within this protocol block will appear in the reset
// state of the FSM created by Cynthesizer.
//
void EquationSolver::reset()
{
  {
#pragma HLS protocol floating
    // Put reset code here
    // Make sure to initialize all output ports
    // and all data members of the module.
    
    // You should not check for the reset signal itself being active
    // here (e.g. do not use "if (rst == 0)" ). Putting a conditional
    // check in the reset code will generate a Cynthesizer warning
    // because the RTL output may violate RTL coding guidelines. The
    // reset_signal_is mechanism of SystemC ensures that code before
    // the first wait() statement is executed every time reset is
    // active, so you do not need to check for the reset being active.
    
    // The reset block should end with a wait() call (this is the
    // first wait() in the thread). 

    y_out=0;
    valid_out = 0;
    
    wait();
  }
}

//
// dataIn() - input hardware interface
//
// This function represents the input interface of the SC_MODULE.
// Place code within the CYN_PROTOCOL block of this function that
// will implement the protocol and timing necessary to read data
// into the design.
//
void EquationSolver::dataIn()
{
  {
#pragma HLS protocol floating
    // Put input interface code here 

    // Aufgabe 3.2a)
    // Hier muss das Handshake-Eingabeprotokoll implementiert werden.
    // Ziel ist es, die Variablen x, u, y, a und dx von den jeweiligen
    // Ports x0_in, u0_in, y0_in, a_in, dx_in zu lesen. Mit dem Signal
    // ready_in signalisiert man der Testbench, dass man Daten lesen
    // moechte. Mit dem Signal valid_in signalisiert die Testbench diesem
    // Modul, dass die Daten jetzt gelesen werden koennen.
  }
}

//
// dataOut() - output hardware interface
//
// This function represents the output interface of the SC_MODULE.
// Place code within the CYN_PROTOCOL block of this function that
// will implement the protocol and timing necessary to output data
// from the design.
//
void EquationSolver::dataOut()
{
  {
#pragma HLS protocol floating
    // Put output interface code here
    
    // Aufgabe 3.2b)
    // Hier muss das Handshake-Ausgabeprotokoll implementiert werden.
    // Ziel ist es, die Variable  y, auf den jeweiligen Ausgangsport
    // y_out zu schreiben. Mit dem Signal
    // ready_out signalisiert die Testbench, dass sie Daten lesen
    // moechte. Mit dem Signal valid_out signalisiert man der Testbench 
    // dass die Daten jetzt gelesen werden koennen.
  }
}

//
// thread0() - main module thread
//
// All of the functionality of the single SC_CTHREAD design should
// be placed within this thread. The functionality can consist of as many
// method calls with argument passing as desired.
//
void EquationSolver::thread0()
{
  // Call the reset function. This must be done at the top of the
  // thread for correct reset handling. It is not necessary to define
  // a separate reset function, but the reset functionality must
  // appear as a single CYN_PROTOCOL block with a single wait() at the
  // end, and it must be the first executable code in the thread's
  // body.

  reset();

  while( true ) {
    dataIn();
    //----------
    // Aufgabe 3.3
    // ---------
    // Der Differenzialgleichungsloeser aus dem letzten Praktikum.
    // Dieser Code muss noch angepasst werden.
    // Zum Testen muss aber zuerst das Ein-/Ausgabeprotokoll implementiert werden.
//#define TEST_PROTOCOL
#ifdef TEST_PROTOCOL
    y = eq_fixed_t(0.05)*a;
#else // TEST_PROTOCOL
datapath_loop:
    while(x < a) {
      x1 = x + dx;
      u1 = u - (eq_fixed_t(3) * x * u * dx) - (eq_fixed_t(3) * y * dx);
      y1 = y + (u * dx);

      x = x1;
      u = u1;
      y = y1;
    }
#endif // TEST_PROTOCOL
   
    dataOut();
  }
}
