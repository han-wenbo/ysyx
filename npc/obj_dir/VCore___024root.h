// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VCore.h for the primary calling header

#ifndef VERILATED_VCORE___024ROOT_H_
#define VERILATED_VCORE___024ROOT_H_  // guard

#include "verilated.h"


class VCore__Syms;

class alignas(VL_CACHE_LINE_BYTES) VCore___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clock,0,0);
    CData/*0:0*/ Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg;
    VL_IN8(reset,0,0);
    VL_IN8(io_testEn,0,0);
    VL_IN8(io_testIdx,3,0);
    VL_IN8(io_testRdIdx,3,0);
    VL_IN8(io_setPcEn,0,0);
    CData/*3:0*/ Core__DOT___DU_io_ctrl_AluOp_op;
    CData/*0:0*/ Core__DOT__DU__DOT___instDecoder_io_ctrl_RegFileEnable_en;
    CData/*3:0*/ Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx;
    CData/*0:0*/ Core__DOT__DU__DOT__instDecoder__DOT__sim_exit__DOT__prev;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg__0;
    CData/*0:0*/ __VactDidInit;
    CData/*0:0*/ __VactContinue;
    VL_OUT(io_instAddr,31,0);
    VL_IN(io_instIn,31,0);
    VL_IN(io_testVal,31,0);
    VL_OUT(io_testRdVal,31,0);
    VL_IN(io_testSetPcVal,31,0);
    IData/*31:0*/ Core__DOT__FU__DOT__pcReg;
    IData/*31:0*/ Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_0;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_1;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_2;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_3;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_4;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_5;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_6;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_7;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_8;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_9;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_10;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_11;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_12;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_13;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_14;
    IData/*31:0*/ Core__DOT__DU__DOT__regFile__DOT__regFile_15;
    VlWide<16>/*511:0*/ Core__DOT__DU__DOT__regFile__DOT___GEN;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    VCore__Syms* const vlSymsp;

    // CONSTRUCTORS
    VCore___024root(VCore__Syms* symsp, const char* v__name);
    ~VCore___024root();
    VL_UNCOPYABLE(VCore___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
