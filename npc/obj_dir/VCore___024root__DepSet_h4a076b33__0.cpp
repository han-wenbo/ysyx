// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCore.h for the primary calling header

#include "VCore__pch.h"
#include "VCore__Syms.h"
#include "VCore___024root.h"

extern "C" void sim_exit();

VL_INLINE_OPT void VCore___024root____Vdpiimwrap_Core__DOT__DU__DOT__instDecoder__DOT__sim_exit__DOT__sim_exit_TOP() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root____Vdpiimwrap_Core__DOT__DU__DOT__instDecoder__DOT__sim_exit__DOT__sim_exit_TOP\n"); );
    // Body
    sim_exit();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCore___024root___dump_triggers__ico(VCore___024root* vlSelf);
#endif  // VL_DEBUG

void VCore___024root___eval_triggers__ico(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_triggers__ico\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.setBit(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VCore___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCore___024root___dump_triggers__act(VCore___024root* vlSelf);
#endif  // VL_DEBUG

void VCore___024root___eval_triggers__act(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_triggers__act\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.setBit(0U, ((IData)(vlSelfRef.clock) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0))));
    vlSelfRef.__VactTriggered.setBit(1U, ((IData)(vlSelfRef.Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg) 
                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg__0)));
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
    vlSelfRef.__Vtrigprevexpr___TOP__Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg__0 
        = vlSelfRef.Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg;
    if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VactDidInit)))))) {
        vlSelfRef.__VactDidInit = 1U;
        vlSelfRef.__VactTriggered.setBit(1U, 1U);
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VCore___024root___dump_triggers__act(vlSelf);
    }
#endif
}
