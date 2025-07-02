// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCore.h for the primary calling header

#include "VCore__pch.h"
#include "VCore___024root.h"

void VCore___024root___ico_sequent__TOP__0(VCore___024root* vlSelf);

void VCore___024root___eval_ico(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_ico\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VCore___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void VCore___024root___ico_sequent__TOP__0(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___ico_sequent__TOP__0\n"); );
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
    vlSelfRef.Core__DOT__DU__DOT___instDecoder_io_ctrl_RegFileEnable_en 
        = ((0x33U == (0x7fU & vlSelfRef.io_instIn)) 
           | (0x13U == (0x7fU & vlSelfRef.io_instIn)));
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
    vlSelfRef.Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg 
        = ((~ (IData)(vlSelfRef.Core__DOT__DU__DOT___instDecoder_io_ctrl_RegFileEnable_en)) 
           & (0x73U == (0x7fU & vlSelfRef.io_instIn)));
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

void VCore___024root___eval_triggers__ico(VCore___024root* vlSelf);

bool VCore___024root___eval_phase__ico(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_phase__ico\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    VCore___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        VCore___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void VCore___024root___eval_act(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_act\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void VCore___024root___nba_sequent__TOP__0(VCore___024root* vlSelf);
void VCore___024root___nba_sequent__TOP__1(VCore___024root* vlSelf);

void VCore___024root___eval_nba(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_nba\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCore___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCore___024root___nba_sequent__TOP__1(vlSelf);
    }
}

VL_INLINE_OPT void VCore___024root___nba_sequent__TOP__0(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___nba_sequent__TOP__0\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ Core__DOT___DU_io_aluSrc1;
    Core__DOT___DU_io_aluSrc1 = 0;
    IData/*31:0*/ Core__DOT___DU_io_aluSrc2;
    Core__DOT___DU_io_aluSrc2 = 0;
    CData/*0:0*/ Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0;
    Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0 = 0;
    IData/*31:0*/ __VdfgRegularize_h2dd05df0_0_1;
    __VdfgRegularize_h2dd05df0_0_1 = 0;
    // Body
    vlSelfRef.Core__DOT__FU__DOT__pcReg = ((IData)(vlSelfRef.reset)
                                            ? 0x80000000U
                                            : ((IData)(vlSelfRef.io_setPcEn)
                                                ? vlSelfRef.io_testSetPcVal
                                                : ((IData)(4U) 
                                                   + vlSelfRef.Core__DOT__FU__DOT__pcReg)));
    Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0 
        = (((IData)(vlSelfRef.Core__DOT__DU__DOT___instDecoder_io_ctrl_RegFileEnable_en) 
            | (IData)(vlSelfRef.io_testEn)) & (0U != (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)));
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (~ (0U != (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx))))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_0 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (1U == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_1 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (2U == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_2 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (3U == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_3 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (4U == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_4 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (5U == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_5 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (6U == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_6 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (7U == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_7 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (8U == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_8 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (9U == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_9 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (0xaU == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_10 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (0xbU == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_11 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (0xcU == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_12 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (0xdU == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_13 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (0xeU == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_14 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    if (((IData)(Core__DOT__DU__DOT__regFile__DOT__unnamedblk1__DOT___GEN_0) 
         & (0xfU == (IData)(vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregIdx)))) {
        vlSelfRef.Core__DOT__DU__DOT__regFile__DOT__regFile_15 
            = vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal;
    }
    vlSelfRef.io_instAddr = vlSelfRef.Core__DOT__FU__DOT__pcReg;
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
    Core__DOT___DU_io_aluSrc2 = ((0x33U == (0x7fU & vlSelfRef.io_instIn))
                                  ? ((0U == (0xfU & 
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
                                                                      >> 0x14U)), 5U)))))
                                  : VL_SHIFTR_III(32,32,32, vlSelfRef.io_instIn, 0x14U));
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
    vlSelfRef.Core__DOT__DU__DOT____Vcellinp__regFile__io_wregVal 
        = ((IData)(vlSelfRef.io_testEn) ? vlSelfRef.io_testVal
            : ((0U == (IData)(vlSelfRef.Core__DOT___DU_io_ctrl_AluOp_op))
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
                                            : 0xffffffffU)))))))));
}

void VCore___024root____Vdpiimwrap_Core__DOT__DU__DOT__instDecoder__DOT__sim_exit__DOT__sim_exit_TOP();

VL_INLINE_OPT void VCore___024root___nba_sequent__TOP__1(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___nba_sequent__TOP__1\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg) 
         & (~ (IData)(vlSelfRef.Core__DOT__DU__DOT__instDecoder__DOT__sim_exit__DOT__prev)))) {
        VCore___024root____Vdpiimwrap_Core__DOT__DU__DOT__instDecoder__DOT__sim_exit__DOT__sim_exit_TOP();
    }
    vlSelfRef.Core__DOT__DU__DOT__instDecoder__DOT__sim_exit__DOT__prev 
        = vlSelfRef.Core__DOT__DU__DOT__instDecoder__DOT____Vcellinp__sim_exit__triSg;
}

void VCore___024root___eval_triggers__act(VCore___024root* vlSelf);

bool VCore___024root___eval_phase__act(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_phase__act\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    VCore___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        VCore___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool VCore___024root___eval_phase__nba(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_phase__nba\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        VCore___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCore___024root___dump_triggers__ico(VCore___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VCore___024root___dump_triggers__nba(VCore___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VCore___024root___dump_triggers__act(VCore___024root* vlSelf);
#endif  // VL_DEBUG

void VCore___024root___eval(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            VCore___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("Core.sv", 2, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (VCore___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            VCore___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("Core.sv", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                VCore___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("Core.sv", 2, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (VCore___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (VCore___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void VCore___024root___eval_debug_assertions(VCore___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCore___024root___eval_debug_assertions\n"); );
    VCore__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clock & 0xfeU)))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY(((vlSelfRef.reset & 0xfeU)))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY(((vlSelfRef.io_testEn & 0xfeU)))) {
        Verilated::overWidthError("io_testEn");}
    if (VL_UNLIKELY(((vlSelfRef.io_testIdx & 0xf0U)))) {
        Verilated::overWidthError("io_testIdx");}
    if (VL_UNLIKELY(((vlSelfRef.io_testRdIdx & 0xf0U)))) {
        Verilated::overWidthError("io_testRdIdx");}
    if (VL_UNLIKELY(((vlSelfRef.io_setPcEn & 0xfeU)))) {
        Verilated::overWidthError("io_setPcEn");}
}
#endif  // VL_DEBUG
