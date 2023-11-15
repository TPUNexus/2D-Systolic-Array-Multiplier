#include <stdlib.h>
#include <iostream>
#include <cstdlib>

#include <verilated.h>         // Common verilator routines.
#include <verilated_vcd_c.h>   // Write waverforms to a VCD file.

#include "VtopSystolicArray.h" // Verilated DUT.

#define MAX_SIM_TIME 100  // Number of clk edges.
#define RESET_NEG_EDGE 5  // Clk edge number to deassert arst.

#define VERIF_START_TIME 7

vluint64_t sim_time    = 0;
vluint64_t posedge_cnt = 0;

// Assert arst only on the first clock edge.
// Note: By default all signals are initialized to 0, so there's no need to drive
// the other inputs to '0.
void dut_reset (VtopSystolicArray *dut)
{
  dut->i_arst = 0;

  if ((sim_time > 2) && (sim_time < RESET_NEG_EDGE))
  {
    dut->i_arst = 1;
  }
}

// Assert validInput after every 10 clk cycles (after reset).
void toggle_i_validInput(VtopSystolicArray *dut)
{
  dut->i_validInput = 0;

  if ((posedge_cnt%15 == 0) && (sim_time >= RESET_NEG_EDGE))
  {
    dut->i_validInput = 1;
  }
}

void driveInputMatrices(VtopSystolicArray *dut)
{
  dut->i_a[0] = 0;
  dut->i_a[1] = 0;
  dut->i_a[2] = 0;
  dut->i_a[3] = 0;
  dut->i_b[0] = 0;
  dut->i_b[1] = 0;
  dut->i_b[2] = 0;
  dut->i_b[3] = 0;

  if ((posedge_cnt%15 == 0) && (sim_time >= RESET_NEG_EDGE))
  {
    dut->i_a[0] = 0x01010101;
    dut->i_a[1] = 0x01010101;
    dut->i_a[2] = 0x01010101;
    dut->i_a[3] = 0x01010101;

    dut->i_b[0] = 0x01010101;
    dut->i_b[1] = 0x01010101;
    dut->i_b[2] = 0x01010101;
    dut->i_b[3] = 0x01010101;
  }
}

int main(int argc, char** argv, char** env)
{
  srand (time(NULL));
  Verilated::commandArgs(argc, argv);
  VtopSystolicArray *dut = new VtopSystolicArray; // Instantiate DUT.

  // {{{ Set-up waveform dumping.

    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

  // }}} Set-up waveform dumping.

  while (sim_time < MAX_SIM_TIME)
  {
    dut_reset(dut);

    dut->i_clk ^= 1; // Toggle clk to create pos and neg edge.

    dut->eval(); // Evaluate all the signals in the DUT on each clock edge.

    if (dut->i_clk == 1)
    {
      posedge_cnt++;

      toggle_i_validInput(dut);
      driveInputMatrices(dut);
    }

    // Write all the traced signal values into the waveform dump file.
    m_trace->dump(sim_time);

    sim_time++;
  }

  m_trace->close();
  delete dut;
  exit(EXIT_SUCCESS);
}
