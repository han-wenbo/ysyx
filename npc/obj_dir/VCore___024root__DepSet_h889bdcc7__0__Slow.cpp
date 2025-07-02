// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCore.h for the primary calling header

#include "VCore__pch.h"
#include "VCore___024root.h"

VL_ATTR_COLD void VCore___024root___eval_static(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_static\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
    vlSelfRef.__Vtrigprevexpr___TOP__Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg__0 
        = vlSelfRef.Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg;
}

VL_ATTR_COLD void VCore___024root___eval_initial__TOP(VCore___024root* vlSelf);

VL_ATTR_COLD void VCore___024root___eval_initial(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_initial\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VCore___024root___eval_initial__TOP(vlSelf);
}

VL_ATTR_COLD void VCore___024root___eval_initial__TOP(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_initial__TOP\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.Core__DOT__DU__DOT__instDecoder__DOT__sim_exit__DOT__prev = 0U;
}

VL_ATTR_COLD void VCore___024root___eval_final(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_final\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCore___024root___dump_triggers__stl(VCore___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool VCore___024root___eval_phase__stl(VCore___024root* vlSelf);

VL_ATTR_COLD void VCore___024root___eval_settle(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_settle\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x64U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            VCore___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("Core.sv", 2, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (VCore___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCore___024root___dump_triggers__stl(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___dump_triggers__stl\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VCore___024root___stl_sequent__TOP__0(VCore___024root* vlSelf);

VL_ATTR_COLD void VCore___024root___eval_stl(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_stl\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VCore___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void VCore___024root___stl_sequent__TOP__0(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___stl_sequent__TOP__0\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ Core__DOT___DU_io_aluSrc1;
    Core__DOT___DU_io_aluSrc1 = 0;
    IData/*31:0*/ Core__DOT___DU_io_aluSrc2;
    Core__DOT___DU_io_aluSrc2 = 0;
    IData/*31:0*/ __VdfgRegularize_h2dd05df0_0_1;
    __VdfgRegularize_h2dd05df0_0_1 = 0;
    // Body
    vlSelfRef.io_instAddr = vlSelfRef.Core__DOT__FU__DOT__pcReg;
    vlSelfRef.Core__DOT__DU__DOT___instDecoder_io_ctrl_RegFileEnable_en 
        = ((0x33U == (0x7fU & vlSelfRef.io_instIn)) 
           | (0x13U == (0x7fU & vlSelfRef.io_instIn)));
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[0U] 
        = vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_0;
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[1U] 
        = vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_1;
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[2U] 
        = (IData)((((QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_3)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_2))));
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[3U] 
        = (IData)(((((QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_3)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_2))) 
                   >> 0x20U));
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[4U] 
        = vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_4;
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[5U] 
        = vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_5;
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[6U] 
        = (IData)((((QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_7)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_6))));
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[7U] 
        = (IData)(((((QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_7)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_6))) 
                   >> 0x20U));
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[8U] 
        = vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_8;
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[9U] 
        = vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_9;
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[0xaU] 
        = (IData)((((QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_11)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_10))));
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[0xbU] 
        = (IData)(((((QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_11)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_10))) 
                   >> 0x20U));
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[0xcU] 
        = vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_12;
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[0xdU] 
        = vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_13;
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[0xeU] 
        = (IData)((((QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_15)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_14))));
    vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[0xfU] 
        = (IData)(((((QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_15)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_14))) 
                   >> 0x20U));
    if ((0x33U == (0x7fU & vlSelfRef.io_instIn))) {
        vlSelfRef.Core__DOT___DU_io_ctrl_AluOp_op = 
            ((IData)((0U == (0x7f80U & vlSelfRef.io_instIn)))
              ? 0U : (7U & (vlSelfRef.io_instIn >> 0xcU)));
        Core__DOT___DU_io_aluSrc2 = ((0U == (0xfU & 
                                             (vlSelfRef.io_instIn 
                                              >> 0x14U)))
                                      ? 0U : (((0U 
                                                == 
                                                (0x1fU 
                                                 & VL_SHIFTL_III(9,9,32, 
                                                                 (0xfU 
                                                                  & (vlSelfRef.io_instIn 
                                                                     >> 0x14U)), 5U)))
                                                ? 0U
                                                : (
                                                   vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[
                                                   (((IData)(0x1fU) 
                                                     + 
                                                     (0x1ffU 
                                                      & VL_SHIFTL_III(9,9,32, 
                                                                      (0xfU 
                                                                       & (vlSelfRef.io_instIn 
                                                                          >> 0x14U)), 5U))) 
                                                    >> 5U)] 
                                                   << 
                                                   ((IData)(0x20U) 
                                                    - 
                                                    (0x1fU 
                                                     & VL_SHIFTL_III(9,9,32, 
                                                                     (0xfU 
                                                                      & (vlSelfRef.io_instIn 
                                                                         >> 0x14U)), 5U))))) 
                                              | (vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[
                                                 (0xfU 
                                                  & (VL_SHIFTL_III(9,9,32, 
                                                                   (0xfU 
                                                                    & (vlSelfRef.io_instIn 
                                                                       >> 0x14U)), 5U) 
                                                     >> 5U))] 
                                                 >> 
                                                 (0x1fU 
                                                  & VL_SHIFTL_III(9,9,32, 
                                                                  (0xfU 
                                                                   & (vlSelfRef.io_instIn 
                                                                      >> 0x14U)), 5U)))));
    } else {
        vlSelfRef.Core__DOT___DU_io_ctrl_AluOp_op = 
            ((0x13U == (0x7fU & vlSelfRef.io_instIn))
              ? (7U & (vlSelfRef.io_instIn >> 0xcU))
              : 0xfU);
        Core__DOT___DU_io_aluSrc2 = VL_SHIFTR_III(32,32,32, vlSelfRef.io_instIn, 0x14U);
    }
    vlSelfRef.Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg 
        = ((~ (IData)(vlSelfRef.Core__DOT__DU__DOT___instDecoder_io_ctrl_RegFileEnable_en)) 
           & (0x73U == (0x7fU & vlSelfRef.io_instIn)));
    vlSelfRef.io_testRdVal = (((0U == (0x1fU & VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.io_testRdIdx), 5U)))
                                ? 0U : (vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[
                                        (((IData)(0x1fU) 
                                          + (0x1ffU 
                                             & VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.io_testRdIdx), 5U))) 
                                         >> 5U)] << 
                                        ((IData)(0x20U) 
                                         - (0x1fU & 
                                            VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.io_testRdIdx), 5U))))) 
                              | (vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[
                                 (0xfU & (VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.io_testRdIdx), 5U) 
                                          >> 5U))] 
                                 >> (0x1fU & VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.io_testRdIdx), 5U))));
    __VdfgRegularize_h2dd05df0_0_1 = (((0U == (0x1fU 
                                               & VL_SHIFTL_III(9,9,32, 
                                                               (0xfU 
                                                                & (vlSelfRef.io_instIn 
                                                                   >> 0xfU)), 5U)))
                                        ? 0U : (vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[
                                                (((IData)(0x1fU) 
                                                  + 
                                                  (0x1ffU 
                                                   & VL_SHIFTL_III(9,9,32, 
                                                                   (0xfU 
                                                                    & (vlSelfRef.io_instIn 
                                                                       >> 0xfU)), 5U))) 
                                                 >> 5U)] 
                                                << 
                                                ((IData)(0x20U) 
                                                 - 
                                                 (0x1fU 
                                                  & VL_SHIFTL_III(9,9,32, 
                                                                  (0xfU 
                                                                   & (vlSelfRef.io_instIn 
                                                                      >> 0xfU)), 5U))))) 
                                      | (vlSelfRef.Core__DOT__DU__DOT__regFile__DOT___GEN[
                                         (0xfU & (VL_SHIFTL_III(9,9,32, 
                                                                (0xfU 
                                                                 & (vlSelfRef.io_instIn 
                                                                    >> 0xfU)), 5U) 
                                                  >> 5U))] 
                                         >> (0x1fU 
                                             & VL_SHIFTL_III(9,9,32, 
                                                             (0xfU 
                                                              & (vlSelfRef.io_instIn 
                                                                 >> 0xfU)), 5U))));
    Core__DOT___DU_io_aluSrc1 = ((0U == (0xfU & (vlSelfRef.io_instIn 
                                                 >> 0xfU)))
                                  ? 0U : __VdfgRegularize_h2dd05df0_0_1);
    if (vlSelfRef.io_testEn) {
        vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx 
            = (0xfU & (IData)(vlSelfRef.io_testIdx));
        vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal 
            = vlSelfRef.io_testVal;
    } else {
        vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx 
            = (0xfU & (vlSelfRef.io_instIn >> 7U));
        vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal 
            = ((0U == (IData)(vlSelfRef.Core__DOT___DU_io_ctrl_AluOp_op))
                ? (Core__DOT___DU_io_aluSrc1 + Core__DOT___DU_io_aluSrc2)
                : ((1U == (IData)(vlSelfRef.Core__DOT___DU_io_ctrl_AluOp_op))
                    ? ((IData)(1U) + ((~ Core__DOT___DU_io_aluSrc2) 
                                      + Core__DOT___DU_io_aluSrc1))
                    : ((2U == (IData)(vlSelfRef.Core__DOT___DU_io_ctrl_AluOp_op))
                        ? ((0U == (0xfU & (vlSelfRef.io_instIn 
                                           >> 0xfU)))
                            ? 0xffffffffU : (~ __VdfgRegularize_h2dd05df0_0_1))
                        : ((3U == (IData)(vlSelfRef.Core__DOT___DU_io_ctrl_AluOp_op))
                            ? (Core__DOT___DU_io_aluSrc1 
                               & Core__DOT___DU_io_aluSrc2)
                            : ((4U == (IData)(vlSelfRef.Core__DOT___DU_io_ctrl_AluOp_op))
                                ? (Core__DOT___DU_io_aluSrc1 
                                   | Core__DOT___DU_io_aluSrc2)
                                : ((5U == (IData)(vlSelfRef.Core__DOT___DU_io_ctrl_AluOp_op))
                                    ? (Core__DOT___DU_io_aluSrc1 
                                       ^ Core__DOT___DU_io_aluSrc2)
                                    : ((6U == (IData)(vlSelfRef.Core__DOT___DU_io_ctrl_AluOp_op))
                                        ? VL_LTS_III(32, Core__DOT___DU_io_aluSrc1, Core__DOT___DU_io_aluSrc2)
                                        : ((7U == (IData)(vlSelfRef.Core__DOT___DU_io_ctrl_AluOp_op))
                                            ? (Core__DOT___DU_io_aluSrc1 
                                               == Core__DOT___DU_io_aluSrc2)
                                            : 0xffffffffU))))))));
    }
}

VL_ATTR_COLD void VCore___024root___eval_triggers__stl(VCore___024root* vlSelf);

VL_ATTR_COLD bool VCore___024root___eval_phase__stl(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_phase__stl\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    VCore___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        VCore___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCore___024root___dump_triggers__ico(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___dump_triggers__ico\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VCore___024root___dump_triggers__act(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___dump_triggers__act\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clock)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @( Core.DU.instDecoder.__Vcellinp__sim_exit__triSg)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VCore___024root___dump_triggers__nba(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___dump_triggers__nba\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clock)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @( Core.DU.instDecoder.__Vcellinp__sim_exit__triSg)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VCore___024root___ctor_var_reset(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___ctor_var_reset\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->clock = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5452235342940299466ull);
    vlSelf->reset = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9928399931838511862ull);
    vlSelf->io_instAddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13797510823723336000ull);
    vlSelf->io_instIn = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15100584590098240156ull);
    vlSelf->io_testEn = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5931963888187501729ull);
    vlSelf->io_testIdx = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 5378016260786805398ull);
    vlSelf->io_testVal = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7306205822586745323ull);
    vlSelf->io_testRdIdx = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 18406769110062469292ull);
    vlSelf->io_testRdVal = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11943967695688158918ull);
    vlSelf->io_setPcEn = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5139390848706236805ull);
    vlSelf->io_testSetPcVal = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 416118538674224236ull);
    vlSelf->Core__DOT___DU_io_ctrl_AluOp_op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10164035688393485391ull);
    vlSelf->Core__DOT__FU__DOT__pcReg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8660840891344431780ull);
    vlSelf->Core__DOT__DU__DOT___instDecoder_io_ctrl_RegFileEnable_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3492842566578319295ull);
    vlSelf->Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1610571943597608301ull);
    vlSelf->Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 17593610419205752875ull);
    vlSelf->Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3860928037360066699ull);
    vlSelf->Core__DOT__DU__DOT__instDecoder__DOT__sim_exit__DOT__prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15876684429819122232ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1488147701546967902ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 351307856892857573ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11354421038931922172ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17119004245713539688ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_4 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10005303461667214757ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_5 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6756714142253039619ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_6 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15932207803116612064ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_7 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14289977212639654742ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_8 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17100748930418852078ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_9 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15406533804160379696ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_10 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3155941486367087993ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_11 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1444210972491875923ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_12 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 119943181015350079ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_13 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2315493199326598892ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_14 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10215006837180556479ull);
    vlSelf->Core__DOT__DU__DOT__regFile__DOT__regFile_15 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2215524291900159457ull);
    VL_SCOPED_RAND_RESET_W(512, vlSelf->Core__DOT__DU__DOT__regFile__DOT___GEN, __VscopeHash, 11944563593120532916ull);
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13272892335938733197ull);
    vlSelf->__Vtrigprevexpr___TOP__Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4636768299909745872ull);
    vlSelf->__VactDidInit = 0;
}
