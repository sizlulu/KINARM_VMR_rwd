/* Include files */

#include <stddef.h>
#include "blas.h"
#include "KINARM_loads_sfun.h"
#include "c39_KINARM_loads.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "KINARM_loads_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);

/* Type Definitions */

/* Named Constants */
#define c39_event_e_clk                (0)
#define CALL_EVENT                     (-1)
#define c39_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)
#define c39_IN_Ramp_Down               ((uint8_T)1U)
#define c39_IN_Ramp_Down2              ((uint8_T)2U)
#define c39_IN_Ramp_Up_Main            ((uint8_T)3U)
#define c39_IN_Wait_for_Go             ((uint8_T)4U)
#define c39_IN_Ramp_Up                 ((uint8_T)1U)
#define c39_IN_Ramp_Up2                ((uint8_T)2U)
#define c39_IN_Ramp_Up_Done            ((uint8_T)3U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance);
static void initialize_params_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct *
  chartInstance);
static void enable_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance);
static void disable_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance);
static void c39_update_debugger_state_c39_KINARM_loads
  (SFc39_KINARM_loadsInstanceStruct *chartInstance);
static void ext_mode_exec_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c39_KINARM_loads
  (SFc39_KINARM_loadsInstanceStruct *chartInstance);
static void set_sim_state_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_st);
static void c39_set_sim_state_side_effects_c39_KINARM_loads
  (SFc39_KINARM_loadsInstanceStruct *chartInstance);
static void finalize_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance);
static void sf_gateway_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance);
static void mdl_start_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance);
static void c39_chartstep_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance);
static void initSimStructsc39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance);
static void c39_exit_internal_Ramp_Up_Main(SFc39_KINARM_loadsInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c39_machineNumber, uint32_T
  c39_chartNumber, uint32_T c39_instanceNumber);
static const mxArray *c39_sf_marshallOut(void *chartInstanceVoid, void
  *c39_inData);
static int8_T c39_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_u, const emlrtMsgIdentifier *c39_parentId);
static void c39_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c39_mxArrayInData, const char_T *c39_varName, void *c39_outData);
static const mxArray *c39_b_sf_marshallOut(void *chartInstanceVoid, void
  *c39_inData);
static int32_T c39_b_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_u, const emlrtMsgIdentifier *c39_parentId);
static void c39_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c39_mxArrayInData, const char_T *c39_varName, void *c39_outData);
static const mxArray *c39_c_sf_marshallOut(void *chartInstanceVoid, void
  *c39_inData);
static uint8_T c39_c_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_b_is_Ramp_Up_Main, const char_T
  *c39_identifier);
static uint8_T c39_d_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_u, const emlrtMsgIdentifier *c39_parentId);
static void c39_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c39_mxArrayInData, const char_T *c39_varName, void *c39_outData);
static const mxArray *c39_d_sf_marshallOut(void *chartInstanceVoid, void
  *c39_inData);
static real_T c39_e_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_b_scaling, const char_T *c39_identifier);
static real_T c39_f_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_u, const emlrtMsgIdentifier *c39_parentId);
static void c39_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c39_mxArrayInData, const char_T *c39_varName, void *c39_outData);
static uint32_T c39_g_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_b_temporalCounter_i1, const char_T
  *c39_identifier);
static uint32_T c39_h_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_u, const emlrtMsgIdentifier *c39_parentId);
static const mxArray *c39_i_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_b_setSimStateSideEffectsInfo, const char_T *
  c39_identifier);
static const mxArray *c39_j_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_u, const emlrtMsgIdentifier *c39_parentId);
static void init_dsm_address_info(SFc39_KINARM_loadsInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc39_KINARM_loadsInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc39_KINARM_loads(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c39_doSetSimStateSideEffects = 0U;
  chartInstance->c39_setSimStateSideEffectsInfo = NULL;
  *chartInstance->c39_temporalCounter_i1 = 0U;
  *chartInstance->c39_temporalCounter_i1 = 0U;
  *chartInstance->c39_is_Ramp_Up_Main = c39_IN_NO_ACTIVE_CHILD;
  *chartInstance->c39_temporalCounter_i1 = 0U;
  *chartInstance->c39_temporalCounter_i1 = 0U;
  *chartInstance->c39_is_active_c39_KINARM_loads = 0U;
  *chartInstance->c39_is_c39_KINARM_loads = c39_IN_NO_ACTIVE_CHILD;
  *chartInstance->c39_tick = 0.0;
  *chartInstance->c39_tickCount = 0.0;
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c39_scaling = 0.0;
  }
}

static void initialize_params_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct *
  chartInstance)
{
  (void)chartInstance;
}

static void enable_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c39_update_debugger_state_c39_KINARM_loads
  (SFc39_KINARM_loadsInstanceStruct *chartInstance)
{
  uint32_T c39_prevAniVal;
  c39_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (*chartInstance->c39_is_active_c39_KINARM_loads == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 6U, *chartInstance->c39_sfEvent);
  }

  if (*chartInstance->c39_is_c39_KINARM_loads == c39_IN_Ramp_Up_Main) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c39_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c39_sfEvent);
  }

  if (*chartInstance->c39_is_Ramp_Up_Main == c39_IN_Ramp_Up) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *chartInstance->c39_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c39_sfEvent);
  }

  if (*chartInstance->c39_is_Ramp_Up_Main == c39_IN_Ramp_Up2) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, *chartInstance->c39_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, *chartInstance->c39_sfEvent);
  }

  if (*chartInstance->c39_is_Ramp_Up_Main == c39_IN_Ramp_Up_Done) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, *chartInstance->c39_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, *chartInstance->c39_sfEvent);
  }

  if (*chartInstance->c39_is_c39_KINARM_loads == c39_IN_Wait_for_Go) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, *chartInstance->c39_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, *chartInstance->c39_sfEvent);
  }

  if (*chartInstance->c39_is_c39_KINARM_loads == c39_IN_Ramp_Down2) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c39_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c39_sfEvent);
  }

  if (*chartInstance->c39_is_c39_KINARM_loads == c39_IN_Ramp_Down) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c39_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c39_sfEvent);
  }

  _SFD_SET_ANIMATION(c39_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static void ext_mode_exec_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance)
{
  c39_update_debugger_state_c39_KINARM_loads(chartInstance);
}

static const mxArray *get_sim_state_c39_KINARM_loads
  (SFc39_KINARM_loadsInstanceStruct *chartInstance)
{
  const mxArray *c39_st;
  const mxArray *c39_y = NULL;
  real_T c39_hoistedGlobal;
  real_T c39_u;
  const mxArray *c39_b_y = NULL;
  real_T c39_b_hoistedGlobal;
  real_T c39_b_u;
  const mxArray *c39_c_y = NULL;
  real_T c39_c_hoistedGlobal;
  real_T c39_c_u;
  const mxArray *c39_d_y = NULL;
  uint8_T c39_d_hoistedGlobal;
  uint8_T c39_d_u;
  const mxArray *c39_e_y = NULL;
  uint8_T c39_e_hoistedGlobal;
  uint8_T c39_e_u;
  const mxArray *c39_f_y = NULL;
  uint8_T c39_f_hoistedGlobal;
  uint8_T c39_f_u;
  const mxArray *c39_g_y = NULL;
  uint32_T c39_g_hoistedGlobal;
  uint32_T c39_g_u;
  const mxArray *c39_h_y = NULL;
  c39_st = NULL;
  c39_st = NULL;
  c39_y = NULL;
  sf_mex_assign(&c39_y, sf_mex_createcellmatrix(7, 1), false);
  c39_hoistedGlobal = *chartInstance->c39_scaling;
  c39_u = c39_hoistedGlobal;
  c39_b_y = NULL;
  sf_mex_assign(&c39_b_y, sf_mex_create("y", &c39_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c39_y, 0, c39_b_y);
  c39_b_hoistedGlobal = *chartInstance->c39_tick;
  c39_b_u = c39_b_hoistedGlobal;
  c39_c_y = NULL;
  sf_mex_assign(&c39_c_y, sf_mex_create("y", &c39_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c39_y, 1, c39_c_y);
  c39_c_hoistedGlobal = *chartInstance->c39_tickCount;
  c39_c_u = c39_c_hoistedGlobal;
  c39_d_y = NULL;
  sf_mex_assign(&c39_d_y, sf_mex_create("y", &c39_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c39_y, 2, c39_d_y);
  c39_d_hoistedGlobal = *chartInstance->c39_is_active_c39_KINARM_loads;
  c39_d_u = c39_d_hoistedGlobal;
  c39_e_y = NULL;
  sf_mex_assign(&c39_e_y, sf_mex_create("y", &c39_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c39_y, 3, c39_e_y);
  c39_e_hoistedGlobal = *chartInstance->c39_is_c39_KINARM_loads;
  c39_e_u = c39_e_hoistedGlobal;
  c39_f_y = NULL;
  sf_mex_assign(&c39_f_y, sf_mex_create("y", &c39_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c39_y, 4, c39_f_y);
  c39_f_hoistedGlobal = *chartInstance->c39_is_Ramp_Up_Main;
  c39_f_u = c39_f_hoistedGlobal;
  c39_g_y = NULL;
  sf_mex_assign(&c39_g_y, sf_mex_create("y", &c39_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c39_y, 5, c39_g_y);
  c39_g_hoistedGlobal = *chartInstance->c39_temporalCounter_i1;
  c39_g_u = c39_g_hoistedGlobal;
  c39_h_y = NULL;
  sf_mex_assign(&c39_h_y, sf_mex_create("y", &c39_g_u, 7, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c39_y, 6, c39_h_y);
  sf_mex_assign(&c39_st, c39_y, false);
  return c39_st;
}

static void set_sim_state_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_st)
{
  const mxArray *c39_u;
  c39_u = sf_mex_dup(c39_st);
  *chartInstance->c39_scaling = c39_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("scaling", c39_u, 0)), "scaling");
  *chartInstance->c39_tick = c39_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("tick", c39_u, 1)), "tick");
  *chartInstance->c39_tickCount = c39_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("tickCount", c39_u, 2)), "tickCount");
  *chartInstance->c39_is_active_c39_KINARM_loads = c39_c_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c39_KINARM_loads",
       c39_u, 3)), "is_active_c39_KINARM_loads");
  *chartInstance->c39_is_c39_KINARM_loads = c39_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_c39_KINARM_loads", c39_u, 4)),
    "is_c39_KINARM_loads");
  *chartInstance->c39_is_Ramp_Up_Main = c39_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_Ramp_Up_Main", c39_u, 5)), "is_Ramp_Up_Main");
  *chartInstance->c39_temporalCounter_i1 = c39_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("temporalCounter_i1", c39_u, 6)),
    "temporalCounter_i1");
  sf_mex_assign(&chartInstance->c39_setSimStateSideEffectsInfo,
                c39_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "setSimStateSideEffectsInfo", c39_u, 7)), "setSimStateSideEffectsInfo"),
                true);
  sf_mex_destroy(&c39_u);
  chartInstance->c39_doSetSimStateSideEffects = 1U;
  c39_update_debugger_state_c39_KINARM_loads(chartInstance);
  sf_mex_destroy(&c39_st);
}

static void c39_set_sim_state_side_effects_c39_KINARM_loads
  (SFc39_KINARM_loadsInstanceStruct *chartInstance)
{
  if (chartInstance->c39_doSetSimStateSideEffects != 0) {
    if (*chartInstance->c39_is_c39_KINARM_loads == c39_IN_Ramp_Down) {
      if (sf_mex_sub(chartInstance->c39_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 2) == 0.0) {
        *chartInstance->c39_temporalCounter_i1 = 0U;
      }
    }

    if (*chartInstance->c39_is_c39_KINARM_loads == c39_IN_Ramp_Down2) {
      if (sf_mex_sub(chartInstance->c39_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 3) == 0.0) {
        *chartInstance->c39_temporalCounter_i1 = 0U;
      }
    }

    if (*chartInstance->c39_is_Ramp_Up_Main == c39_IN_Ramp_Up) {
      if (sf_mex_sub(chartInstance->c39_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 5) == 0.0) {
        *chartInstance->c39_temporalCounter_i1 = 0U;
      }
    }

    if (*chartInstance->c39_is_Ramp_Up_Main == c39_IN_Ramp_Up2) {
      if (sf_mex_sub(chartInstance->c39_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 6) == 0.0) {
        *chartInstance->c39_temporalCounter_i1 = 0U;
      }
    }

    chartInstance->c39_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c39_setSimStateSideEffectsInfo);
}

static void sf_gateway_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance)
{
  c39_set_sim_state_side_effects_c39_KINARM_loads(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 6U, *chartInstance->c39_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c39_robot_type, 6U, 1U, 0U,
                        *chartInstance->c39_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c39_tickCount, 1U, 1U, 0U,
                        *chartInstance->c39_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c39_down_duration, 5U, 1U, 0U,
                        *chartInstance->c39_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c39_up_duration, 4U, 1U, 0U,
                        *chartInstance->c39_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c39_Run_Status, 3U, 1U, 0U,
                        *chartInstance->c39_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c39_tick, 0U, 1U, 0U,
                        *chartInstance->c39_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c39_scaling, 7U, 1U, 0U,
                        *chartInstance->c39_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c39_Motors_Disabled, 2U, 1U, 0U,
                        *chartInstance->c39_sfEvent, false);
  if (*chartInstance->c39_temporalCounter_i1 < MAX_uint32_T) {
    (*chartInstance->c39_temporalCounter_i1)++;
  }

  *chartInstance->c39_sfEvent = c39_event_e_clk;
  _SFD_CE_CALL(EVENT_BEFORE_BROADCAST_TAG, c39_event_e_clk,
               *chartInstance->c39_sfEvent);
  c39_chartstep_c39_KINARM_loads(chartInstance);
  _SFD_CE_CALL(EVENT_AFTER_BROADCAST_TAG, c39_event_e_clk,
               *chartInstance->c39_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_KINARM_loadsMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c39_chartstep_c39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance)
{
  boolean_T c39_temp;
  uint32_T c39_u0;
  boolean_T c39_out;
  boolean_T c39_b_temp;
  uint32_T c39_u1;
  boolean_T c39_b_out;
  boolean_T c39_c_out;
  boolean_T c39_c_temp;
  uint32_T c39_u2;
  boolean_T c39_d_out;
  boolean_T c39_d_temp;
  uint32_T c39_u3;
  boolean_T c39_e_out;
  boolean_T c39_f_out;
  boolean_T c39_g_out;
  boolean_T c39_e_temp;
  boolean_T c39_f_temp;
  boolean_T c39_g_temp;
  boolean_T c39_h_out;
  boolean_T c39_i_out;
  boolean_T guard1 = false;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 6U, *chartInstance->c39_sfEvent);
  if (*chartInstance->c39_is_active_c39_KINARM_loads == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 6U, *chartInstance->c39_sfEvent);
    *chartInstance->c39_is_active_c39_KINARM_loads = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, *chartInstance->c39_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, *chartInstance->c39_sfEvent);
    *chartInstance->c39_is_c39_KINARM_loads = c39_IN_Wait_for_Go;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, *chartInstance->c39_sfEvent);
    *chartInstance->c39_scaling = 0.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c39_scaling, 7U, 4U, 6U,
                          *chartInstance->c39_sfEvent, false);
  } else {
    switch (*chartInstance->c39_is_c39_KINARM_loads) {
     case c39_IN_Ramp_Down:
      CV_CHART_EVAL(6, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                   *chartInstance->c39_sfEvent);
      c39_temp = (_SFD_CCP_CALL(10U, 0, *chartInstance->c39_sfEvent ==
        c39_event_e_clk != 0U, *chartInstance->c39_sfEvent) != 0);
      if (c39_temp) {
        c39_u0 = _SFD_TRANS_TEMPORAL_THRESHOLD((uint32_T)
          *chartInstance->c39_tickCount, 32U, 10U);
        c39_temp = (_SFD_CCP_CALL(10U, 1, *chartInstance->c39_temporalCounter_i1
          >= c39_u0 != 0U, *chartInstance->c39_sfEvent) != 0);
      }

      c39_out = (CV_TRANSITION_EVAL(10U, (int32_T)c39_temp) != 0);
      if (c39_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, *chartInstance->c39_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c39_sfEvent);
        *chartInstance->c39_is_c39_KINARM_loads = c39_IN_Ramp_Down2;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c39_sfEvent);
        *chartInstance->c39_temporalCounter_i1 = 0U;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                     *chartInstance->c39_sfEvent);
        if (*chartInstance->c39_sfEvent == c39_event_e_clk) {
          CV_STATE_EVAL(0, 0, 2);
          (*chartInstance->c39_tick)++;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c39_tick, 0U, 4U, 0U,
                                *chartInstance->c39_sfEvent, false);
          *chartInstance->c39_scaling = 1.0 - 2.0 * muDoubleScalarPower
            (*chartInstance->c39_tick / *chartInstance->c39_down_duration, 2.0);
          _SFD_DATA_RANGE_CHECK(*chartInstance->c39_scaling, 7U, 4U, 0U,
                                *chartInstance->c39_sfEvent, false);
        } else {
          CV_STATE_EVAL(0, 0, 1);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *chartInstance->c39_sfEvent);
      break;

     case c39_IN_Ramp_Down2:
      CV_CHART_EVAL(6, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U,
                   *chartInstance->c39_sfEvent);
      c39_b_temp = (_SFD_CCP_CALL(4U, 0, *chartInstance->c39_sfEvent ==
        c39_event_e_clk != 0U, *chartInstance->c39_sfEvent) != 0);
      if (c39_b_temp) {
        c39_u1 = _SFD_TRANS_TEMPORAL_THRESHOLD((uint32_T)
          (*chartInstance->c39_down_duration - *chartInstance->c39_tickCount),
          32U, 4U);
        c39_b_temp = (_SFD_CCP_CALL(4U, 1,
          *chartInstance->c39_temporalCounter_i1 >= c39_u1 != 0U,
          *chartInstance->c39_sfEvent) != 0);
      }

      c39_b_out = (CV_TRANSITION_EVAL(4U, (int32_T)c39_b_temp) != 0);
      if (c39_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, *chartInstance->c39_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c39_sfEvent);
        *chartInstance->c39_is_c39_KINARM_loads = c39_IN_Wait_for_Go;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, *chartInstance->c39_sfEvent);
        *chartInstance->c39_scaling = 0.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c39_scaling, 7U, 4U, 6U,
                              *chartInstance->c39_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                     *chartInstance->c39_sfEvent);
        if (*chartInstance->c39_sfEvent == c39_event_e_clk) {
          CV_STATE_EVAL(1, 0, 2);
          (*chartInstance->c39_tick)++;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c39_tick, 0U, 4U, 1U,
                                *chartInstance->c39_sfEvent, false);
          *chartInstance->c39_scaling = 2.0 * muDoubleScalarPower
            (muDoubleScalarAbs(*chartInstance->c39_tick /
                               *chartInstance->c39_down_duration - 0.5) - 0.5,
             2.0);
          _SFD_DATA_RANGE_CHECK(*chartInstance->c39_scaling, 7U, 4U, 1U,
                                *chartInstance->c39_sfEvent, false);
        } else {
          CV_STATE_EVAL(1, 0, 1);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, *chartInstance->c39_sfEvent);
      break;

     case c39_IN_Ramp_Up_Main:
      CV_CHART_EVAL(6, 0, 3);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                   *chartInstance->c39_sfEvent);
      c39_c_out = (CV_TRANSITION_EVAL(11U, (int32_T)_SFD_CCP_CALL(11U, 0,
        CV_RELATIONAL_EVAL(5U, 11U, 0, *chartInstance->c39_Motors_Disabled, 0.0,
                           -1, 4U, *chartInstance->c39_Motors_Disabled > 0.0) !=
        0U, *chartInstance->c39_sfEvent)) != 0);
      guard1 = false;
      if (c39_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, *chartInstance->c39_sfEvent);
        c39_exit_internal_Ramp_Up_Main(chartInstance);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c39_sfEvent);
        *chartInstance->c39_is_c39_KINARM_loads = c39_IN_Wait_for_Go;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, *chartInstance->c39_sfEvent);
        *chartInstance->c39_scaling = 0.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c39_scaling, 7U, 4U, 6U,
                              *chartInstance->c39_sfEvent, false);
        guard1 = true;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                     *chartInstance->c39_sfEvent);
        switch (*chartInstance->c39_is_Ramp_Up_Main) {
         case c39_IN_Ramp_Up:
          CV_STATE_EVAL(2, 0, 1);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 9U,
                       *chartInstance->c39_sfEvent);
          c39_c_temp = (_SFD_CCP_CALL(9U, 0, *chartInstance->c39_sfEvent ==
            c39_event_e_clk != 0U, *chartInstance->c39_sfEvent) != 0);
          if (c39_c_temp) {
            c39_u2 = _SFD_TRANS_TEMPORAL_THRESHOLD((uint32_T)
              *chartInstance->c39_tickCount, 32U, 9U);
            c39_c_temp = (_SFD_CCP_CALL(9U, 1,
              *chartInstance->c39_temporalCounter_i1 >= c39_u2 != 0U,
              *chartInstance->c39_sfEvent) != 0);
          }

          c39_d_out = (CV_TRANSITION_EVAL(9U, (int32_T)c39_c_temp) != 0);
          if (c39_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, *chartInstance->c39_sfEvent);
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c39_sfEvent);
            *chartInstance->c39_is_Ramp_Up_Main = c39_IN_Ramp_Up2;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, *chartInstance->c39_sfEvent);
            *chartInstance->c39_temporalCounter_i1 = 0U;
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                         *chartInstance->c39_sfEvent);
            if (*chartInstance->c39_sfEvent == c39_event_e_clk) {
              CV_STATE_EVAL(3, 0, 2);
              (*chartInstance->c39_tick)++;
              _SFD_DATA_RANGE_CHECK(*chartInstance->c39_tick, 0U, 4U, 3U,
                                    *chartInstance->c39_sfEvent, false);
              *chartInstance->c39_scaling = 2.0 * muDoubleScalarPower
                (*chartInstance->c39_tick / *chartInstance->c39_up_duration, 2.0);
              _SFD_DATA_RANGE_CHECK(*chartInstance->c39_scaling, 7U, 4U, 3U,
                                    *chartInstance->c39_sfEvent, false);
            } else {
              CV_STATE_EVAL(3, 0, 1);
            }
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, *chartInstance->c39_sfEvent);
          guard1 = true;
          break;

         case c39_IN_Ramp_Up2:
          CV_STATE_EVAL(2, 0, 2);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U,
                       *chartInstance->c39_sfEvent);
          c39_d_temp = (_SFD_CCP_CALL(3U, 0, *chartInstance->c39_sfEvent ==
            c39_event_e_clk != 0U, *chartInstance->c39_sfEvent) != 0);
          if (c39_d_temp) {
            c39_u3 = _SFD_TRANS_TEMPORAL_THRESHOLD((uint32_T)
              (*chartInstance->c39_up_duration - *chartInstance->c39_tickCount),
              32U, 3U);
            c39_d_temp = (_SFD_CCP_CALL(3U, 1,
              *chartInstance->c39_temporalCounter_i1 >= c39_u3 != 0U,
              *chartInstance->c39_sfEvent) != 0);
          }

          c39_e_out = (CV_TRANSITION_EVAL(3U, (int32_T)c39_d_temp) != 0);
          if (c39_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, *chartInstance->c39_sfEvent);
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, *chartInstance->c39_sfEvent);
            *chartInstance->c39_is_Ramp_Up_Main = c39_IN_Ramp_Up_Done;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, *chartInstance->c39_sfEvent);
            *chartInstance->c39_scaling = 1.0;
            _SFD_DATA_RANGE_CHECK(*chartInstance->c39_scaling, 7U, 4U, 5U,
                                  *chartInstance->c39_sfEvent, false);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                         *chartInstance->c39_sfEvent);
            if (*chartInstance->c39_sfEvent == c39_event_e_clk) {
              CV_STATE_EVAL(4, 0, 2);
              (*chartInstance->c39_tick)++;
              _SFD_DATA_RANGE_CHECK(*chartInstance->c39_tick, 0U, 4U, 4U,
                                    *chartInstance->c39_sfEvent, false);
              *chartInstance->c39_scaling = 1.0 - 2.0 * muDoubleScalarPower
                (muDoubleScalarAbs(*chartInstance->c39_tick /
                                   *chartInstance->c39_up_duration - 0.5) - 0.5,
                 2.0);
              _SFD_DATA_RANGE_CHECK(*chartInstance->c39_scaling, 7U, 4U, 4U,
                                    *chartInstance->c39_sfEvent, false);
            } else {
              CV_STATE_EVAL(4, 0, 1);
            }
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, *chartInstance->c39_sfEvent);
          guard1 = true;
          break;

         case c39_IN_Ramp_Up_Done:
          CV_STATE_EVAL(2, 0, 3);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                       *chartInstance->c39_sfEvent);
          c39_f_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0,
            CV_RELATIONAL_EVAL(5U, 2U, 0, *chartInstance->c39_Run_Status, 0.0,
                               -1, 0U, *chartInstance->c39_Run_Status == 0.0) !=
            0U, *chartInstance->c39_sfEvent)) != 0);
          if (c39_f_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, *chartInstance->c39_sfEvent);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U,
                         *chartInstance->c39_sfEvent);
            c39_g_out = (CV_TRANSITION_EVAL(7U, (int32_T)_SFD_CCP_CALL(7U, 0,
              CV_RELATIONAL_EVAL(5U, 7U, 0, *chartInstance->c39_down_duration,
                                 0.0, -1, 4U, *chartInstance->c39_down_duration >
                                 0.0) != 0U, *chartInstance->c39_sfEvent)) != 0);
            if (c39_g_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U,
                           *chartInstance->c39_sfEvent);
              *chartInstance->c39_is_Ramp_Up_Main = c39_IN_NO_ACTIVE_CHILD;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, *chartInstance->c39_sfEvent);
              *chartInstance->c39_is_c39_KINARM_loads = c39_IN_NO_ACTIVE_CHILD;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c39_sfEvent);
              _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 7U,
                           *chartInstance->c39_sfEvent);
              *chartInstance->c39_tickCount = *chartInstance->c39_down_duration /
                2.0;
              _SFD_DATA_RANGE_CHECK(*chartInstance->c39_tickCount, 1U, 5U, 7U,
                                    *chartInstance->c39_sfEvent, false);
              *chartInstance->c39_is_c39_KINARM_loads = c39_IN_Ramp_Down;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c39_sfEvent);
              *chartInstance->c39_temporalCounter_i1 = 0U;
              *chartInstance->c39_tick = 0.0;
              _SFD_DATA_RANGE_CHECK(*chartInstance->c39_tick, 0U, 4U, 0U,
                                    *chartInstance->c39_sfEvent, false);
            } else {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U,
                           *chartInstance->c39_sfEvent);
              *chartInstance->c39_is_Ramp_Up_Main = c39_IN_NO_ACTIVE_CHILD;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, *chartInstance->c39_sfEvent);
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c39_sfEvent);
              *chartInstance->c39_is_c39_KINARM_loads = c39_IN_Wait_for_Go;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, *chartInstance->c39_sfEvent);
              *chartInstance->c39_scaling = 0.0;
              _SFD_DATA_RANGE_CHECK(*chartInstance->c39_scaling, 7U, 4U, 6U,
                                    *chartInstance->c39_sfEvent, false);
            }
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                         *chartInstance->c39_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, *chartInstance->c39_sfEvent);
          if (*chartInstance->c39_is_c39_KINARM_loads != c39_IN_Ramp_Up_Main) {
          } else {
            guard1 = true;
          }
          break;

         default:
          CV_STATE_EVAL(2, 0, 0);

          /* Unreachable state, for coverage only */
          *chartInstance->c39_is_Ramp_Up_Main = c39_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c39_sfEvent);
          guard1 = true;
          break;
        }
      }

      if (guard1 == true) {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, *chartInstance->c39_sfEvent);
      }
      break;

     case c39_IN_Wait_for_Go:
      CV_CHART_EVAL(6, 0, 4);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                   *chartInstance->c39_sfEvent);
      c39_e_temp = (_SFD_CCP_CALL(1U, 0, CV_RELATIONAL_EVAL(5U, 1U, 0,
        *chartInstance->c39_Run_Status, 0.0, -1, 4U,
        *chartInstance->c39_Run_Status > 0.0) != 0U, *chartInstance->c39_sfEvent)
                    != 0);
      if (c39_e_temp) {
        c39_e_temp = (_SFD_CCP_CALL(1U, 1, CV_RELATIONAL_EVAL(5U, 1U, 1,
          *chartInstance->c39_Motors_Disabled, 0.0, -1, 0U,
          *chartInstance->c39_Motors_Disabled == 0.0) != 0U,
          *chartInstance->c39_sfEvent) != 0);
      }

      c39_f_temp = c39_e_temp;
      if (c39_f_temp) {
        c39_g_temp = (_SFD_CCP_CALL(1U, 2, CV_RELATIONAL_EVAL(5U, 1U, 2,
          *chartInstance->c39_robot_type, 0.0, -1, 0U,
          *chartInstance->c39_robot_type == 0.0) != 0U,
          *chartInstance->c39_sfEvent) != 0);
        if (!c39_g_temp) {
          c39_g_temp = (_SFD_CCP_CALL(1U, 3, CV_RELATIONAL_EVAL(5U, 1U, 3,
            *chartInstance->c39_robot_type, 2.0, -1, 0U,
            *chartInstance->c39_robot_type == 2.0) != 0U,
            *chartInstance->c39_sfEvent) != 0);
        }

        c39_f_temp = c39_g_temp;
      }

      c39_h_out = (CV_TRANSITION_EVAL(1U, (int32_T)c39_f_temp) != 0);
      if (c39_h_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, *chartInstance->c39_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U,
                     *chartInstance->c39_sfEvent);
        c39_i_out = (CV_TRANSITION_EVAL(5U, (int32_T)_SFD_CCP_CALL(5U, 0,
          CV_RELATIONAL_EVAL(5U, 5U, 0, *chartInstance->c39_up_duration, 0.0, -1,
                             4U, *chartInstance->c39_up_duration > 0.0) != 0U,
          *chartInstance->c39_sfEvent)) != 0);
        if (c39_i_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, *chartInstance->c39_sfEvent);
          *chartInstance->c39_is_c39_KINARM_loads = c39_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, *chartInstance->c39_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 5U,
                       *chartInstance->c39_sfEvent);
          *chartInstance->c39_tickCount = *chartInstance->c39_up_duration / 2.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c39_tickCount, 1U, 5U, 5U,
                                *chartInstance->c39_sfEvent, false);
          *chartInstance->c39_is_c39_KINARM_loads = c39_IN_Ramp_Up_Main;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c39_sfEvent);
          *chartInstance->c39_is_Ramp_Up_Main = c39_IN_Ramp_Up;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *chartInstance->c39_sfEvent);
          *chartInstance->c39_temporalCounter_i1 = 0U;
          *chartInstance->c39_tick = 0.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c39_tick, 0U, 4U, 3U,
                                *chartInstance->c39_sfEvent, false);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, *chartInstance->c39_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, *chartInstance->c39_sfEvent);
          *chartInstance->c39_is_c39_KINARM_loads = c39_IN_Ramp_Up_Main;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c39_sfEvent);
          *chartInstance->c39_is_Ramp_Up_Main = c39_IN_Ramp_Up_Done;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, *chartInstance->c39_sfEvent);
          *chartInstance->c39_scaling = 1.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c39_scaling, 7U, 4U, 5U,
                                *chartInstance->c39_sfEvent, false);
        }
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                     *chartInstance->c39_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, *chartInstance->c39_sfEvent);
      break;

     default:
      CV_CHART_EVAL(6, 0, 0);

      /* Unreachable state, for coverage only */
      *chartInstance->c39_is_c39_KINARM_loads = c39_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c39_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, *chartInstance->c39_sfEvent);
}

static void initSimStructsc39_KINARM_loads(SFc39_KINARM_loadsInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c39_exit_internal_Ramp_Up_Main(SFc39_KINARM_loadsInstanceStruct
  *chartInstance)
{
  switch (*chartInstance->c39_is_Ramp_Up_Main) {
   case c39_IN_Ramp_Up:
    CV_STATE_EVAL(2, 1, 1);
    *chartInstance->c39_is_Ramp_Up_Main = c39_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c39_sfEvent);
    break;

   case c39_IN_Ramp_Up2:
    CV_STATE_EVAL(2, 1, 2);
    *chartInstance->c39_is_Ramp_Up_Main = c39_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, *chartInstance->c39_sfEvent);
    break;

   case c39_IN_Ramp_Up_Done:
    CV_STATE_EVAL(2, 1, 3);
    *chartInstance->c39_is_Ramp_Up_Main = c39_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, *chartInstance->c39_sfEvent);
    break;

   default:
    CV_STATE_EVAL(2, 1, 0);
    *chartInstance->c39_is_Ramp_Up_Main = c39_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c39_sfEvent);
    break;
  }
}

static void init_script_number_translation(uint32_T c39_machineNumber, uint32_T
  c39_chartNumber, uint32_T c39_instanceNumber)
{
  (void)c39_machineNumber;
  (void)c39_chartNumber;
  (void)c39_instanceNumber;
}

const mxArray *sf_c39_KINARM_loads_get_eml_resolved_functions_info(void)
{
  const mxArray *c39_nameCaptureInfo = NULL;
  c39_nameCaptureInfo = NULL;
  sf_mex_assign(&c39_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c39_nameCaptureInfo;
}

static const mxArray *c39_sf_marshallOut(void *chartInstanceVoid, void
  *c39_inData)
{
  const mxArray *c39_mxArrayOutData = NULL;
  int8_T c39_u;
  const mxArray *c39_y = NULL;
  SFc39_KINARM_loadsInstanceStruct *chartInstance;
  chartInstance = (SFc39_KINARM_loadsInstanceStruct *)chartInstanceVoid;
  c39_mxArrayOutData = NULL;
  c39_u = *(int8_T *)c39_inData;
  c39_y = NULL;
  sf_mex_assign(&c39_y, sf_mex_create("y", &c39_u, 2, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c39_mxArrayOutData, c39_y, false);
  return c39_mxArrayOutData;
}

static int8_T c39_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_u, const emlrtMsgIdentifier *c39_parentId)
{
  int8_T c39_y;
  int8_T c39_i0;
  (void)chartInstance;
  sf_mex_import(c39_parentId, sf_mex_dup(c39_u), &c39_i0, 1, 2, 0U, 0, 0U, 0);
  c39_y = c39_i0;
  sf_mex_destroy(&c39_u);
  return c39_y;
}

static void c39_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c39_mxArrayInData, const char_T *c39_varName, void *c39_outData)
{
  const mxArray *c39_b_e_clk;
  const char_T *c39_identifier;
  emlrtMsgIdentifier c39_thisId;
  int8_T c39_y;
  SFc39_KINARM_loadsInstanceStruct *chartInstance;
  chartInstance = (SFc39_KINARM_loadsInstanceStruct *)chartInstanceVoid;
  c39_b_e_clk = sf_mex_dup(c39_mxArrayInData);
  c39_identifier = c39_varName;
  c39_thisId.fIdentifier = c39_identifier;
  c39_thisId.fParent = NULL;
  c39_y = c39_emlrt_marshallIn(chartInstance, sf_mex_dup(c39_b_e_clk),
    &c39_thisId);
  sf_mex_destroy(&c39_b_e_clk);
  *(int8_T *)c39_outData = c39_y;
  sf_mex_destroy(&c39_mxArrayInData);
}

static const mxArray *c39_b_sf_marshallOut(void *chartInstanceVoid, void
  *c39_inData)
{
  const mxArray *c39_mxArrayOutData = NULL;
  int32_T c39_u;
  const mxArray *c39_y = NULL;
  SFc39_KINARM_loadsInstanceStruct *chartInstance;
  chartInstance = (SFc39_KINARM_loadsInstanceStruct *)chartInstanceVoid;
  c39_mxArrayOutData = NULL;
  c39_u = *(int32_T *)c39_inData;
  c39_y = NULL;
  sf_mex_assign(&c39_y, sf_mex_create("y", &c39_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c39_mxArrayOutData, c39_y, false);
  return c39_mxArrayOutData;
}

static int32_T c39_b_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_u, const emlrtMsgIdentifier *c39_parentId)
{
  int32_T c39_y;
  int32_T c39_i1;
  (void)chartInstance;
  sf_mex_import(c39_parentId, sf_mex_dup(c39_u), &c39_i1, 1, 6, 0U, 0, 0U, 0);
  c39_y = c39_i1;
  sf_mex_destroy(&c39_u);
  return c39_y;
}

static void c39_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c39_mxArrayInData, const char_T *c39_varName, void *c39_outData)
{
  const mxArray *c39_b_sfEvent;
  const char_T *c39_identifier;
  emlrtMsgIdentifier c39_thisId;
  int32_T c39_y;
  SFc39_KINARM_loadsInstanceStruct *chartInstance;
  chartInstance = (SFc39_KINARM_loadsInstanceStruct *)chartInstanceVoid;
  c39_b_sfEvent = sf_mex_dup(c39_mxArrayInData);
  c39_identifier = c39_varName;
  c39_thisId.fIdentifier = c39_identifier;
  c39_thisId.fParent = NULL;
  c39_y = c39_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c39_b_sfEvent),
    &c39_thisId);
  sf_mex_destroy(&c39_b_sfEvent);
  *(int32_T *)c39_outData = c39_y;
  sf_mex_destroy(&c39_mxArrayInData);
}

static const mxArray *c39_c_sf_marshallOut(void *chartInstanceVoid, void
  *c39_inData)
{
  const mxArray *c39_mxArrayOutData = NULL;
  uint8_T c39_u;
  const mxArray *c39_y = NULL;
  SFc39_KINARM_loadsInstanceStruct *chartInstance;
  chartInstance = (SFc39_KINARM_loadsInstanceStruct *)chartInstanceVoid;
  c39_mxArrayOutData = NULL;
  c39_u = *(uint8_T *)c39_inData;
  c39_y = NULL;
  sf_mex_assign(&c39_y, sf_mex_create("y", &c39_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c39_mxArrayOutData, c39_y, false);
  return c39_mxArrayOutData;
}

static uint8_T c39_c_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_b_is_Ramp_Up_Main, const char_T
  *c39_identifier)
{
  uint8_T c39_y;
  emlrtMsgIdentifier c39_thisId;
  c39_thisId.fIdentifier = c39_identifier;
  c39_thisId.fParent = NULL;
  c39_y = c39_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c39_b_is_Ramp_Up_Main),
    &c39_thisId);
  sf_mex_destroy(&c39_b_is_Ramp_Up_Main);
  return c39_y;
}

static uint8_T c39_d_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_u, const emlrtMsgIdentifier *c39_parentId)
{
  uint8_T c39_y;
  uint8_T c39_u4;
  (void)chartInstance;
  sf_mex_import(c39_parentId, sf_mex_dup(c39_u), &c39_u4, 1, 3, 0U, 0, 0U, 0);
  c39_y = c39_u4;
  sf_mex_destroy(&c39_u);
  return c39_y;
}

static void c39_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c39_mxArrayInData, const char_T *c39_varName, void *c39_outData)
{
  const mxArray *c39_b_is_Ramp_Up_Main;
  const char_T *c39_identifier;
  emlrtMsgIdentifier c39_thisId;
  uint8_T c39_y;
  SFc39_KINARM_loadsInstanceStruct *chartInstance;
  chartInstance = (SFc39_KINARM_loadsInstanceStruct *)chartInstanceVoid;
  c39_b_is_Ramp_Up_Main = sf_mex_dup(c39_mxArrayInData);
  c39_identifier = c39_varName;
  c39_thisId.fIdentifier = c39_identifier;
  c39_thisId.fParent = NULL;
  c39_y = c39_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c39_b_is_Ramp_Up_Main),
    &c39_thisId);
  sf_mex_destroy(&c39_b_is_Ramp_Up_Main);
  *(uint8_T *)c39_outData = c39_y;
  sf_mex_destroy(&c39_mxArrayInData);
}

static const mxArray *c39_d_sf_marshallOut(void *chartInstanceVoid, void
  *c39_inData)
{
  const mxArray *c39_mxArrayOutData = NULL;
  real_T c39_u;
  const mxArray *c39_y = NULL;
  SFc39_KINARM_loadsInstanceStruct *chartInstance;
  chartInstance = (SFc39_KINARM_loadsInstanceStruct *)chartInstanceVoid;
  c39_mxArrayOutData = NULL;
  c39_u = *(real_T *)c39_inData;
  c39_y = NULL;
  sf_mex_assign(&c39_y, sf_mex_create("y", &c39_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c39_mxArrayOutData, c39_y, false);
  return c39_mxArrayOutData;
}

static real_T c39_e_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_b_scaling, const char_T *c39_identifier)
{
  real_T c39_y;
  emlrtMsgIdentifier c39_thisId;
  c39_thisId.fIdentifier = c39_identifier;
  c39_thisId.fParent = NULL;
  c39_y = c39_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c39_b_scaling),
    &c39_thisId);
  sf_mex_destroy(&c39_b_scaling);
  return c39_y;
}

static real_T c39_f_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_u, const emlrtMsgIdentifier *c39_parentId)
{
  real_T c39_y;
  real_T c39_d0;
  (void)chartInstance;
  sf_mex_import(c39_parentId, sf_mex_dup(c39_u), &c39_d0, 1, 0, 0U, 0, 0U, 0);
  c39_y = c39_d0;
  sf_mex_destroy(&c39_u);
  return c39_y;
}

static void c39_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c39_mxArrayInData, const char_T *c39_varName, void *c39_outData)
{
  const mxArray *c39_b_scaling;
  const char_T *c39_identifier;
  emlrtMsgIdentifier c39_thisId;
  real_T c39_y;
  SFc39_KINARM_loadsInstanceStruct *chartInstance;
  chartInstance = (SFc39_KINARM_loadsInstanceStruct *)chartInstanceVoid;
  c39_b_scaling = sf_mex_dup(c39_mxArrayInData);
  c39_identifier = c39_varName;
  c39_thisId.fIdentifier = c39_identifier;
  c39_thisId.fParent = NULL;
  c39_y = c39_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c39_b_scaling),
    &c39_thisId);
  sf_mex_destroy(&c39_b_scaling);
  *(real_T *)c39_outData = c39_y;
  sf_mex_destroy(&c39_mxArrayInData);
}

static uint32_T c39_g_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_b_temporalCounter_i1, const char_T
  *c39_identifier)
{
  uint32_T c39_y;
  emlrtMsgIdentifier c39_thisId;
  c39_thisId.fIdentifier = c39_identifier;
  c39_thisId.fParent = NULL;
  c39_y = c39_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c39_b_temporalCounter_i1), &c39_thisId);
  sf_mex_destroy(&c39_b_temporalCounter_i1);
  return c39_y;
}

static uint32_T c39_h_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_u, const emlrtMsgIdentifier *c39_parentId)
{
  uint32_T c39_y;
  uint32_T c39_u5;
  (void)chartInstance;
  sf_mex_import(c39_parentId, sf_mex_dup(c39_u), &c39_u5, 1, 7, 0U, 0, 0U, 0);
  c39_y = c39_u5;
  sf_mex_destroy(&c39_u);
  return c39_y;
}

static const mxArray *c39_i_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_b_setSimStateSideEffectsInfo, const char_T *
  c39_identifier)
{
  const mxArray *c39_y = NULL;
  emlrtMsgIdentifier c39_thisId;
  c39_y = NULL;
  c39_thisId.fIdentifier = c39_identifier;
  c39_thisId.fParent = NULL;
  sf_mex_assign(&c39_y, c39_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c39_b_setSimStateSideEffectsInfo), &c39_thisId), false);
  sf_mex_destroy(&c39_b_setSimStateSideEffectsInfo);
  return c39_y;
}

static const mxArray *c39_j_emlrt_marshallIn(SFc39_KINARM_loadsInstanceStruct
  *chartInstance, const mxArray *c39_u, const emlrtMsgIdentifier *c39_parentId)
{
  const mxArray *c39_y = NULL;
  (void)chartInstance;
  (void)c39_parentId;
  c39_y = NULL;
  sf_mex_assign(&c39_y, sf_mex_duplicatearraysafe(&c39_u), false);
  sf_mex_destroy(&c39_u);
  return c39_y;
}

static void init_dsm_address_info(SFc39_KINARM_loadsInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc39_KINARM_loadsInstanceStruct
  *chartInstance)
{
  chartInstance->c39_e_clk = (int8_T *)(ssGetInputPortSignalPtrs_wrapper
    (chartInstance->S, 5))[0U];
  chartInstance->c39_sfEvent = (int32_T *)ssGetDWork_wrapper(chartInstance->S, 0);
  chartInstance->c39_isStable = (boolean_T *)ssGetDWork_wrapper(chartInstance->S,
    1);
  chartInstance->c39_is_active_c39_KINARM_loads = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 2);
  chartInstance->c39_is_c39_KINARM_loads = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 3);
  chartInstance->c39_is_Ramp_Up_Main = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 4);
  chartInstance->c39_Motors_Disabled = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c39_scaling = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c39_tick = (real_T *)ssGetDWork_wrapper(chartInstance->S, 5);
  chartInstance->c39_Run_Status = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c39_up_duration = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c39_down_duration = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c39_tickCount = (real_T *)ssGetDWork_wrapper(chartInstance->S,
    6);
  chartInstance->c39_robot_type = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c39_temporalCounter_i1 = (uint32_T *)ssGetDWork_wrapper
    (chartInstance->S, 7);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

static uint32_T* sf_get_sfun_dwork_checksum(void);
void sf_c39_KINARM_loads_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2762758999U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(8097418U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(815614781U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2987555800U);
}

mxArray* sf_c39_KINARM_loads_get_post_codegen_info(void);
mxArray *sf_c39_KINARM_loads_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("SpaBnO2qzCSZTzTVDa1rzC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c39_KINARM_loads_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c39_KINARM_loads_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c39_KINARM_loads_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("early");
  mxArray *fallbackReason = mxCreateString("ext_mode");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c39_KINARM_loads_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c39_KINARM_loads_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c39_KINARM_loads(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x7'type','srcId','name','auxInfo'{{M[1],M[23],T\"scaling\",},{M[3],M[24],T\"tick\",},{M[3],M[28],T\"tickCount\",},{M[8],M[0],T\"is_active_c39_KINARM_loads\",},{M[9],M[0],T\"is_c39_KINARM_loads\",},{M[9],M[7],T\"is_Ramp_Up_Main\",},{M[11],M[30],T\"temporalCounter_i1\",S'et','os','ct'{{T\"ev\",M1x4[3 5 6 4],M[1]}}}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 7, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c39_KINARM_loads_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc39_KINARM_loadsInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc39_KINARM_loadsInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _KINARM_loadsMachineNumber_,
           39,
           7,
           12,
           0,
           8,
           1,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_KINARM_loadsMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_KINARM_loadsMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _KINARM_loadsMachineNumber_,
            chartInstance->chartNumber,
            1,
            1,
            1);
          _SFD_SET_DATA_PROPS(0,0,0,0,"tick");
          _SFD_SET_DATA_PROPS(1,0,0,0,"tickCount");
          _SFD_SET_DATA_PROPS(2,1,1,0,"Motors_Disabled");
          _SFD_SET_DATA_PROPS(3,1,1,0,"Run_Status");
          _SFD_SET_DATA_PROPS(4,1,1,0,"up_duration");
          _SFD_SET_DATA_PROPS(5,1,1,0,"down_duration");
          _SFD_SET_DATA_PROPS(6,1,1,0,"robot_type");
          _SFD_SET_DATA_PROPS(7,2,0,1,"scaling");
          _SFD_EVENT_SCOPE(0,1);
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_CH_SUBSTATE_COUNT(4);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_CH_SUBSTATE_INDEX(2,2);
          _SFD_CH_SUBSTATE_INDEX(3,6);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,3);
          _SFD_ST_SUBSTATE_INDEX(2,0,3);
          _SFD_ST_SUBSTATE_INDEX(2,1,4);
          _SFD_ST_SUBSTATE_INDEX(2,2,5);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
        }

        _SFD_CV_INIT_CHART(4,1,0,0);

        {
          static unsigned int sStartDecMap[] = { 22 };

          static unsigned int sEndDecMap[] = { 27 };

          _SFD_CV_INIT_STATE(0,0,0,0,0,1,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          static unsigned int sStartDecMap[] = { 15 };

          static unsigned int sEndDecMap[] = { 20 };

          _SFD_CV_INIT_STATE(1,0,0,0,0,1,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(2,3,1,1,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartDecMap[] = { 20 };

          static unsigned int sEndDecMap[] = { 25 };

          _SFD_CV_INIT_STATE(3,0,0,0,0,1,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          static unsigned int sStartDecMap[] = { 13 };

          static unsigned int sEndDecMap[] = { 18 };

          _SFD_CV_INIT_STATE(4,0,0,0,0,1,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 20, 44, 63 };

          static unsigned int sEndGuardMap[] = { 14, 38, 59, 78 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, 3, -2, -3 };

          _SFD_CV_INIT_TRANS(1,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 20, 44, 63 };

          static unsigned int sEndRelationalopMap[] = { 14, 38, 59, 78 };

          static int sRelationalopEps[] = { -1, -1, -1, -1 };

          static int sRelationalopType[] = { 4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0,
            4, 0, 0, 0, 4, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(11,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 18 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 4, 4, 4, 4, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(11,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 30, 0 };

          static unsigned int sEndGuardMap[] = { 35, 36 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(4,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(8,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 16, 0 };

          static unsigned int sEndGuardMap[] = { 21, 22 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(10,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(7,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 16 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 4, 4, 4, 4, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(7,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 14 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 14 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 14 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(5,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 14 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 4, 4, 4, 4, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(5,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 16, 0 };

          static unsigned int sEndGuardMap[] = { 21, 22 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(9,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 28, 0 };

          static unsigned int sEndGuardMap[] = { 33, 34 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(3,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c39_d_sf_marshallOut,(MexInFcnForType)
          c39_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c39_d_sf_marshallOut,(MexInFcnForType)
          c39_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c39_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c39_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c39_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c39_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c39_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c39_d_sf_marshallOut,(MexInFcnForType)
          c39_d_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _KINARM_loadsMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc39_KINARM_loadsInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc39_KINARM_loadsInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c39_Motors_Disabled);
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c39_scaling);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c39_tick);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c39_Run_Status);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c39_up_duration);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c39_down_duration);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c39_tickCount);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c39_robot_type);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sjB9SGvVKVMkFuIzPqD2KsC";
}

static void sf_check_dwork_consistency(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    const uint32_T *sfunDWorkChecksum = sf_get_sfun_dwork_checksum();
    mxArray *infoStruct = load_KINARM_loads_optimization_info();
    mxArray* mxRTWDWorkChecksum = sf_get_dwork_info_from_mat_file(S,
      sf_get_instance_specialization(), infoStruct, 39, "dworkChecksum");
    if (mxRTWDWorkChecksum != NULL) {
      double *pr = mxGetPr(mxRTWDWorkChecksum);
      if ((uint32_T)pr[0] != sfunDWorkChecksum[0] ||
          (uint32_T)pr[1] != sfunDWorkChecksum[1] ||
          (uint32_T)pr[2] != sfunDWorkChecksum[2] ||
          (uint32_T)pr[3] != sfunDWorkChecksum[3]) {
        sf_mex_error_message("Code generation and simulation targets registered different sets of persistent variables for the block. "
                             "External or Rapid Accelerator mode simulation requires code generation and simulation targets to "
                             "register the same set of persistent variables for this block. "
                             "This discrepancy is typically caused by MATLAB functions that have different code paths for "
                             "simulation and code generation targets where these code paths define different sets of persistent variables. "
                             "Please identify these code paths in the offending block and rewrite the MATLAB code so that "
                             "the set of persistent variables is the same between simulation and code generation.");
      }
    }
  }
}

static void sf_opaque_initialize_c39_KINARM_loads(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc39_KINARM_loadsInstanceStruct*)
    chartInstanceVar)->S);
  chart_debug_initialization(((SFc39_KINARM_loadsInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c39_KINARM_loads((SFc39_KINARM_loadsInstanceStruct*)
    chartInstanceVar);
  initialize_c39_KINARM_loads((SFc39_KINARM_loadsInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c39_KINARM_loads(void *chartInstanceVar)
{
  enable_c39_KINARM_loads((SFc39_KINARM_loadsInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c39_KINARM_loads(void *chartInstanceVar)
{
  disable_c39_KINARM_loads((SFc39_KINARM_loadsInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c39_KINARM_loads(void *chartInstanceVar)
{
  sf_gateway_c39_KINARM_loads((SFc39_KINARM_loadsInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c39_KINARM_loads(void *chartInstanceVar)
{
  ext_mode_exec_c39_KINARM_loads((SFc39_KINARM_loadsInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c39_KINARM_loads(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c39_KINARM_loads((SFc39_KINARM_loadsInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c39_KINARM_loads(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c39_KINARM_loads((SFc39_KINARM_loadsInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c39_KINARM_loads(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc39_KINARM_loadsInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_KINARM_loads_optimization_info();
    }

    finalize_c39_KINARM_loads((SFc39_KINARM_loadsInstanceStruct*)
      chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc39_KINARM_loads((SFc39_KINARM_loadsInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c39_KINARM_loads(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c39_KINARM_loads((SFc39_KINARM_loadsInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

mxArray *sf_c39_KINARM_loads_get_testpoint_info(void)
{
  return NULL;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x8'type','isSigned','wordLength','bias','slope','exponent','isScaledDouble','isComplex','size'{{T\"int32\",,,,,,,M[0],M[]},{T\"boolean\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"double\",,,,,,,M[0],M[]},{T\"double\",,,,,,,M[0],M[]},{T\"uint32\",,,,,,,M[0],M[]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 8, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 1724620448U, 3335412165U, 3353573579U,
    4259520096U };

  return checksum;
}

static void mdlSetWorkWidths_c39_KINARM_loads(SimStruct *S)
{
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_KINARM_loads_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      39);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,39,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,39);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,39,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,39,1);
    }

    ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,39);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1778708535U));
  ssSetChecksum1(S,(136124246U));
  ssSetChecksum2(S,(13513502U));
  ssSetChecksum3(S,(3246475779U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c39_KINARM_loads(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c39_KINARM_loads(SimStruct *S)
{
  SFc39_KINARM_loadsInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc39_KINARM_loadsInstanceStruct *)utMalloc(sizeof
    (SFc39_KINARM_loadsInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc39_KINARM_loadsInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c39_KINARM_loads;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c39_KINARM_loads;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c39_KINARM_loads;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c39_KINARM_loads;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c39_KINARM_loads;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c39_KINARM_loads;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c39_KINARM_loads;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c39_KINARM_loads;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c39_KINARM_loads;
  chartInstance->chartInfo.mdlStart = mdlStart_c39_KINARM_loads;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c39_KINARM_loads;
  chartInstance->chartInfo.extModeExec =
    sf_opaque_ext_mode_exec_c39_KINARM_loads;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->isEnhancedMooreMachine = 0;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->fCheckOverflow = sf_runtime_overflow_check_is_on(S);
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
}

void c39_KINARM_loads_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c39_KINARM_loads(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c39_KINARM_loads(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c39_KINARM_loads(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c39_KINARM_loads_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
