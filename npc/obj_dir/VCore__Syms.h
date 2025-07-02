// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCORE__SYMS_H_
#define VERILATED_VCORE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VCore.h"

// INCLUDE MODULE CLASSES
#include "VCore___024root.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)VCore__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VCore* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VCore___024root                TOP;

    // CONSTRUCTORS
    VCore__Syms(VerilatedContext* contextp, const char* namep, VCore* modelp);
    ~VCore__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
