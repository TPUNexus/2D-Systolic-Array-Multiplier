// This module implements a Processing Element (PE). It performs an 8-bit
// multiply-accumulate operation.

`default_nettype none

module pe
  ( input  var logic        i_clk
  , input  var logic        i_arst

  , input  var logic [7:0]  i_a
  , input  var logic [7:0]  i_b

  , output var logic [7:0]  o_a
  , output var logic [7:0]  o_b
  , output var logic [15:0] o_y
  );

  // {{{ MAC

  logic [15:0] mult;

  always_comb
    mult = i_a*i_b;

  logic [15:0] mac_d, mac_q;

  always_ff @(posedge i_clk, posedge i_arst)
    if (i_arst)
      mac_q <= '0;
    else
      mac_q <= mac_d;

  always_comb
    mac_d = mac_q + mult;

  always_comb
    o_y = mac_q;

  // }}} MAC

  // {{{ Register inputs and assign them to outputs

  logic [7:0] a_q, b_q;

  always_ff @(posedge i_clk, posedge i_arst)
    if (i_arst)
      a_q <= '0;
    else
      a_q <= i_a;

  always_ff @(posedge i_clk, posedge i_arst)
    if (i_arst)
      b_q <= '0;
    else
      b_q <= i_b;

  always_comb
    o_a = a_q;

  always_comb
    o_b = b_q;

  // }}} Register inputs and assign them to outputs

endmodule

`resetall
