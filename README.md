# 2D-Systolic-Array-Multiplier

This repository implements a synthesizable two dimensional systolic array that can be configured to multiply 2 square matrices of any dimension.

The `rtl` sub-directory contains the RTL written in System Verilog and the `tb` sub-directory contains the test bench written in C++ and simulated using Verilator.

## TL;DR

Requirements: `Verilator` and `GNU Make`.

To simulate the TB generating random NxN input matrices, driving the DUT ports and displaying the result matrix generated by the DUT:

1. Clone the repository:
```
git clone https://github.com/tms4517/2D-Systolic-Array-Multiplier.git
```
2. By default the RTL and TB are configured to a matrix size of 4x4.

To modify the default matrix size: `cd rtl`, open `topSystolicArray.sv` and modify the paramater `N`. And, `cd tb`, open `tb_topSystolicArray.sv` and modify the macro `N`. Note,  `N` > 2 and verilator crashes for large matrix dimensions (>100 on my PC).

3. Run the simulation:
```
cd tb && make all
```

## Introduction

### Systolic architectures

(describe and explain paper)

### Existing implementations

(describe Google's TPU)

## Design

(Summary of design)

## Verification

(Summary of verification)

## Further Work

(SIMD processor)
(unpacked data types to perform synthesis)

**STATUS**: RTL & TB complete. Documentation in progress.
