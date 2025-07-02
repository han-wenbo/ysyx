// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VCore__pch.h"

//============================================================
// Constructors

VCore::VCore(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VCore__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , io_testEn{vlSymsp->TOP.io_testEn}
    , io_testIdx{vlSymsp->TOP.io_testIdx}
    , io_testRdIdx{vlSymsp->TOP.io_testRdIdx}
    , io_setPcEn{vlSymsp->TOP.io_setPcEn}
    , io_instAddr{vlSymsp->TOP.io_instAddr}
    , io_instIn{vlSymsp->TOP.io_instIn}
    , io_testVal{vlSymsp->TOP.io_testVal}
    , io_testRdVal{vlSymsp->TOP.io_testRdVal}
    , io_testSetPcVal{vlSymsp->TOP.io_testSetPcVal}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VCore::VCore(const char* _vcname__)
    : VCore(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VCore::~VCore() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VCore___024root___eval_debug_assertions(VCore___024root* vlSelf);
#endif  // VL_DEBUG
void VCore___024root___eval_static(VCore___024root* vlSelf);
void VCore___024root___eval_initial(VCore___024root* vlSelf);
void VCore___024root___eval_settle(VCore___024root* vlSelf);
void VCore___024root___eval(VCore___024root* vlSelf);

void VCore::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VCore::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VCore___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VCore___024root___eval_static(&(vlSymsp->TOP));
        VCore___024root___eval_initial(&(vlSymsp->TOP));
        VCore___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VCore___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VCore::eventsPending() { return false; }

uint64_t VCore::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VCore::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VCore___024root___eval_final(VCore___024root* vlSelf);

VL_ATTR_COLD void VCore::final() {
    VCore___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VCore::hierName() const { return vlSymsp->name(); }
const char* VCore::modelName() const { return "VCore"; }
unsigned VCore::threads() const { return 1; }
void VCore::prepareClone() const { contextp()->prepareClone(); }
void VCore::atClone() const {
    contextp()->threadPoolpOnClone();
}
