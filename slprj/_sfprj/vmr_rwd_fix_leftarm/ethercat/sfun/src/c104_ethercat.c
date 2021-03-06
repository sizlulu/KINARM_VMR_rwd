/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ethercat_sfun.h"
#include "c104_ethercat.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "ethercat_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c104_IN_NO_ACTIVE_CHILD        ((uint8_T)0U)
#define c104_IN_DoneClearing           ((uint8_T)1U)
#define c104_IN_ReadNextEMCY           ((uint8_T)2U)
#define c104_IN_ReceivedFloat          ((uint8_T)3U)
#define c104_IN_StartOverwrite         ((uint8_T)4U)
#define c104_IN_StartReadingCount      ((uint8_T)5U)
#define c104_IN_disableCount           ((uint8_T)6U)
#define c104_IN_disableEMCY            ((uint8_T)7U)
#define c104_IN_setup                  ((uint8_T)8U)
#define c104_IN_startEMCYs             ((uint8_T)9U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance);
static void initialize_params_c104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance);
static void enable_c104_ethercat(SFc104_ethercatInstanceStruct *chartInstance);
static void disable_c104_ethercat(SFc104_ethercatInstanceStruct *chartInstance);
static void c104_update_debugger_state_c104_ethercat
  (SFc104_ethercatInstanceStruct *chartInstance);
static void ext_mode_exec_c104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c104_ethercat(SFc104_ethercatInstanceStruct *
  chartInstance);
static void set_sim_state_c104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_st);
static void c104_set_sim_state_side_effects_c104_ethercat
  (SFc104_ethercatInstanceStruct *chartInstance);
static void finalize_c104_ethercat(SFc104_ethercatInstanceStruct *chartInstance);
static void sf_gateway_c104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance);
static void mdl_start_c104_ethercat(SFc104_ethercatInstanceStruct *chartInstance);
static void c104_chartstep_c104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance);
static void initSimStructsc104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c104_machineNumber, uint32_T
  c104_chartNumber, uint32_T c104_instanceNumber);
static const mxArray *c104_sf_marshallOut(void *chartInstanceVoid, void
  *c104_inData);
static int32_T c104_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_b_sfEvent, const char_T *c104_identifier);
static int32_T c104_b_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_u, const emlrtMsgIdentifier *c104_parentId);
static void c104_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c104_mxArrayInData, const char_T *c104_varName, void *c104_outData);
static const mxArray *c104_b_sf_marshallOut(void *chartInstanceVoid, void
  *c104_inData);
static const mxArray *c104_c_sf_marshallOut(void *chartInstanceVoid, void
  *c104_inData);
static const mxArray *c104_d_sf_marshallOut(void *chartInstanceVoid, void
  *c104_inData);
static void c104_c_emlrt_marshallIn(SFc104_ethercatInstanceStruct *chartInstance,
  const mxArray *c104_b_emcyReadTrigger, const char_T *c104_identifier, int32_T
  c104_y[2]);
static void c104_d_emlrt_marshallIn(SFc104_ethercatInstanceStruct *chartInstance,
  const mxArray *c104_u, const emlrtMsgIdentifier *c104_parentId, int32_T
  c104_y[2]);
static void c104_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c104_mxArrayInData, const char_T *c104_varName, void *c104_outData);
static const mxArray *c104_e_sf_marshallOut(void *chartInstanceVoid, void
  *c104_inData);
static void c104_e_emlrt_marshallIn(SFc104_ethercatInstanceStruct *chartInstance,
  const mxArray *c104_b_emcyValPump, const char_T *c104_identifier, real_T
  c104_y[3]);
static void c104_f_emlrt_marshallIn(SFc104_ethercatInstanceStruct *chartInstance,
  const mxArray *c104_u, const emlrtMsgIdentifier *c104_parentId, real_T c104_y
  [3]);
static void c104_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c104_mxArrayInData, const char_T *c104_varName, void *c104_outData);
static real_T c104_g_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_b_currReadIdx, const char_T
  *c104_identifier);
static real_T c104_h_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_u, const emlrtMsgIdentifier *c104_parentId);
static void c104_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c104_mxArrayInData, const char_T *c104_varName, void *c104_outData);
static uint8_T c104_i_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_b_is_active_c104_ethercat, const char_T
  *c104_identifier);
static uint8_T c104_j_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_u, const emlrtMsgIdentifier *c104_parentId);
static const mxArray *c104_k_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_b_setSimStateSideEffectsInfo, const char_T
  *c104_identifier);
static const mxArray *c104_l_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_u, const emlrtMsgIdentifier *c104_parentId);
static int32_T c104__s32_d_(SFc104_ethercatInstanceStruct *chartInstance, real_T
  c104_b);
static void init_dsm_address_info(SFc104_ethercatInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc104_ethercatInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance)
{
  int32_T c104_i0;
  int32_T c104_i1;
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc104_ethercat(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  *chartInstance->c104_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c104_doSetSimStateSideEffects = 0U;
  chartInstance->c104_setSimStateSideEffectsInfo = NULL;
  *chartInstance->c104_is_active_c104_ethercat = 0U;
  *chartInstance->c104_is_c104_ethercat = c104_IN_NO_ACTIVE_CHILD;
  *chartInstance->c104_currReadIdx = 0.0;
  *chartInstance->c104_valuesToRead = 0.0;
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c104_triggerCountRead = 0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    for (c104_i0 = 0; c104_i0 < 2; c104_i0++) {
      (*chartInstance->c104_emcyReadTrigger)[c104_i0] = 0;
    }
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 3) != 0)) {
    *chartInstance->c104_countOverwriteTrigger = 0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 4) != 0)) {
    for (c104_i1 = 0; c104_i1 < 3; c104_i1++) {
      (*chartInstance->c104_emcyValPump)[c104_i1] = 0.0;
    }
  }
}

static void initialize_params_c104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c104_ethercat(SFc104_ethercatInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c104_ethercat(SFc104_ethercatInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c104_update_debugger_state_c104_ethercat
  (SFc104_ethercatInstanceStruct *chartInstance)
{
  uint32_T c104_prevAniVal;
  c104_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (*chartInstance->c104_is_active_c104_ethercat == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 66U, *chartInstance->c104_sfEvent);
  }

  if (*chartInstance->c104_is_c104_ethercat == c104_IN_setup) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, *chartInstance->c104_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, *chartInstance->c104_sfEvent);
  }

  if (*chartInstance->c104_is_c104_ethercat == c104_IN_StartReadingCount) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, *chartInstance->c104_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, *chartInstance->c104_sfEvent);
  }

  if (*chartInstance->c104_is_c104_ethercat == c104_IN_disableCount) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, *chartInstance->c104_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, *chartInstance->c104_sfEvent);
  }

  if (*chartInstance->c104_is_c104_ethercat == c104_IN_startEMCYs) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, *chartInstance->c104_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, *chartInstance->c104_sfEvent);
  }

  if (*chartInstance->c104_is_c104_ethercat == c104_IN_ReadNextEMCY) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c104_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c104_sfEvent);
  }

  if (*chartInstance->c104_is_c104_ethercat == c104_IN_disableEMCY) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, *chartInstance->c104_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, *chartInstance->c104_sfEvent);
  }

  if (*chartInstance->c104_is_c104_ethercat == c104_IN_DoneClearing) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c104_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c104_sfEvent);
  }

  if (*chartInstance->c104_is_c104_ethercat == c104_IN_ReceivedFloat) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c104_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c104_sfEvent);
  }

  if (*chartInstance->c104_is_c104_ethercat == c104_IN_StartOverwrite) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *chartInstance->c104_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c104_sfEvent);
  }

  _SFD_SET_ANIMATION(c104_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static void ext_mode_exec_c104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance)
{
  c104_update_debugger_state_c104_ethercat(chartInstance);
}

static const mxArray *get_sim_state_c104_ethercat(SFc104_ethercatInstanceStruct *
  chartInstance)
{
  const mxArray *c104_st;
  const mxArray *c104_y = NULL;
  int32_T c104_hoistedGlobal;
  int32_T c104_u;
  const mxArray *c104_b_y = NULL;
  const mxArray *c104_c_y = NULL;
  const mxArray *c104_d_y = NULL;
  int32_T c104_b_hoistedGlobal;
  int32_T c104_b_u;
  const mxArray *c104_e_y = NULL;
  real_T c104_c_hoistedGlobal;
  real_T c104_c_u;
  const mxArray *c104_f_y = NULL;
  real_T c104_d_hoistedGlobal;
  real_T c104_d_u;
  const mxArray *c104_g_y = NULL;
  uint8_T c104_e_hoistedGlobal;
  uint8_T c104_e_u;
  const mxArray *c104_h_y = NULL;
  uint8_T c104_f_hoistedGlobal;
  uint8_T c104_f_u;
  const mxArray *c104_i_y = NULL;
  c104_st = NULL;
  c104_st = NULL;
  c104_y = NULL;
  sf_mex_assign(&c104_y, sf_mex_createcellmatrix(8, 1), false);
  c104_hoistedGlobal = *chartInstance->c104_countOverwriteTrigger;
  c104_u = c104_hoistedGlobal;
  c104_b_y = NULL;
  sf_mex_assign(&c104_b_y, sf_mex_create("y", &c104_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c104_y, 0, c104_b_y);
  c104_c_y = NULL;
  sf_mex_assign(&c104_c_y, sf_mex_create("y",
    *chartInstance->c104_emcyReadTrigger, 6, 0U, 1U, 0U, 1, 2), false);
  sf_mex_setcell(c104_y, 1, c104_c_y);
  c104_d_y = NULL;
  sf_mex_assign(&c104_d_y, sf_mex_create("y", *chartInstance->c104_emcyValPump,
    0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c104_y, 2, c104_d_y);
  c104_b_hoistedGlobal = *chartInstance->c104_triggerCountRead;
  c104_b_u = c104_b_hoistedGlobal;
  c104_e_y = NULL;
  sf_mex_assign(&c104_e_y, sf_mex_create("y", &c104_b_u, 6, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c104_y, 3, c104_e_y);
  c104_c_hoistedGlobal = *chartInstance->c104_currReadIdx;
  c104_c_u = c104_c_hoistedGlobal;
  c104_f_y = NULL;
  sf_mex_assign(&c104_f_y, sf_mex_create("y", &c104_c_u, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c104_y, 4, c104_f_y);
  c104_d_hoistedGlobal = *chartInstance->c104_valuesToRead;
  c104_d_u = c104_d_hoistedGlobal;
  c104_g_y = NULL;
  sf_mex_assign(&c104_g_y, sf_mex_create("y", &c104_d_u, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c104_y, 5, c104_g_y);
  c104_e_hoistedGlobal = *chartInstance->c104_is_active_c104_ethercat;
  c104_e_u = c104_e_hoistedGlobal;
  c104_h_y = NULL;
  sf_mex_assign(&c104_h_y, sf_mex_create("y", &c104_e_u, 3, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c104_y, 6, c104_h_y);
  c104_f_hoistedGlobal = *chartInstance->c104_is_c104_ethercat;
  c104_f_u = c104_f_hoistedGlobal;
  c104_i_y = NULL;
  sf_mex_assign(&c104_i_y, sf_mex_create("y", &c104_f_u, 3, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c104_y, 7, c104_i_y);
  sf_mex_assign(&c104_st, c104_y, false);
  return c104_st;
}

static void set_sim_state_c104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_st)
{
  const mxArray *c104_u;
  int32_T c104_iv0[2];
  int32_T c104_i2;
  real_T c104_dv0[3];
  int32_T c104_i3;
  c104_u = sf_mex_dup(c104_st);
  *chartInstance->c104_countOverwriteTrigger = c104_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("countOverwriteTrigger", c104_u, 0)),
     "countOverwriteTrigger");
  c104_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "emcyReadTrigger", c104_u, 1)), "emcyReadTrigger", c104_iv0);
  for (c104_i2 = 0; c104_i2 < 2; c104_i2++) {
    (*chartInstance->c104_emcyReadTrigger)[c104_i2] = c104_iv0[c104_i2];
  }

  c104_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("emcyValPump",
    c104_u, 2)), "emcyValPump", c104_dv0);
  for (c104_i3 = 0; c104_i3 < 3; c104_i3++) {
    (*chartInstance->c104_emcyValPump)[c104_i3] = c104_dv0[c104_i3];
  }

  *chartInstance->c104_triggerCountRead = c104_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("triggerCountRead", c104_u, 3)),
    "triggerCountRead");
  *chartInstance->c104_currReadIdx = c104_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("currReadIdx", c104_u, 4)), "currReadIdx");
  *chartInstance->c104_valuesToRead = c104_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("valuesToRead", c104_u, 5)), "valuesToRead");
  *chartInstance->c104_is_active_c104_ethercat = c104_i_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c104_ethercat", c104_u,
       6)), "is_active_c104_ethercat");
  *chartInstance->c104_is_c104_ethercat = c104_i_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_c104_ethercat", c104_u, 7)),
    "is_c104_ethercat");
  sf_mex_assign(&chartInstance->c104_setSimStateSideEffectsInfo,
                c104_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    ("setSimStateSideEffectsInfo", c104_u, 8)), "setSimStateSideEffectsInfo"),
                true);
  sf_mex_destroy(&c104_u);
  chartInstance->c104_doSetSimStateSideEffects = 1U;
  c104_update_debugger_state_c104_ethercat(chartInstance);
  sf_mex_destroy(&c104_st);
}

static void c104_set_sim_state_side_effects_c104_ethercat
  (SFc104_ethercatInstanceStruct *chartInstance)
{
  if (chartInstance->c104_doSetSimStateSideEffects != 0) {
    chartInstance->c104_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c104_ethercat(SFc104_ethercatInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c104_setSimStateSideEffectsInfo);
}

static void sf_gateway_c104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance)
{
  int32_T c104_i4;
  int32_T c104_i5;
  int32_T c104_i6;
  int32_T c104_i7;
  c104_set_sim_state_side_effects_c104_ethercat(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 66U, *chartInstance->c104_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c104_overwriteStatus, 6U, 1U, 0U,
                        *chartInstance->c104_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c104_valuesToRead, 1U, 1U, 0U,
                        *chartInstance->c104_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c104_currReadIdx, 0U, 1U, 0U,
                        *chartInstance->c104_sfEvent, false);
  for (c104_i4 = 0; c104_i4 < 3; c104_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c104_emcyValPump)[c104_i4], 10U, 1U,
                          0U, *chartInstance->c104_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c104_countOverwriteTrigger, 9U,
                        1U, 0U, *chartInstance->c104_sfEvent, false);
  for (c104_i5 = 0; c104_i5 < 2; c104_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c104_emcyValues)[c104_i5], 5U, 1U, 0U,
                          *chartInstance->c104_sfEvent, false);
  }

  for (c104_i6 = 0; c104_i6 < 2; c104_i6++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c104_emcyReadTrigger)[c104_i6],
                          8U, 1U, 0U, *chartInstance->c104_sfEvent, false);
  }

  for (c104_i7 = 0; c104_i7 < 2; c104_i7++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c104_countValues)[c104_i7], 4U, 1U,
                          0U, *chartInstance->c104_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c104_triggerCountRead, 7U, 1U,
                        0U, *chartInstance->c104_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c104_driveID, 3U, 1U, 0U,
                        *chartInstance->c104_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c104_triggerReading, 2U, 1U, 0U,
                        *chartInstance->c104_sfEvent, false);
  *chartInstance->c104_sfEvent = CALL_EVENT;
  c104_chartstep_c104_ethercat(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ethercatMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c104_ethercat(SFc104_ethercatInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c104_chartstep_c104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance)
{
  boolean_T c104_out;
  int32_T c104_i8;
  boolean_T c104_b_out;
  int32_T c104_i9;
  int32_T c104_i10;
  int32_T c104_i11;
  int32_T c104_i12;
  int32_T c104_i13;
  boolean_T c104_c_out;
  boolean_T c104_d_out;
  boolean_T c104_e_out;
  boolean_T c104_f_out;
  boolean_T c104_g_out;
  int32_T c104_i14;
  int32_T c104_i15;
  int32_T c104_i16;
  boolean_T c104_h_out;
  int32_T c104_i17;
  int32_T c104_i18;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 66U,
               *chartInstance->c104_sfEvent);
  if (*chartInstance->c104_is_active_c104_ethercat == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 66U,
                 *chartInstance->c104_sfEvent);
    *chartInstance->c104_is_active_c104_ethercat = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 66U, *chartInstance->c104_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, *chartInstance->c104_sfEvent);
    *chartInstance->c104_is_c104_ethercat = c104_IN_setup;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, *chartInstance->c104_sfEvent);
  } else {
    switch (*chartInstance->c104_is_c104_ethercat) {
     case c104_IN_DoneClearing:
      CV_CHART_EVAL(66, 0, 1);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, *chartInstance->c104_sfEvent);
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c104_sfEvent);
      *chartInstance->c104_is_c104_ethercat = c104_IN_setup;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, *chartInstance->c104_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *chartInstance->c104_sfEvent);
      break;

     case c104_IN_ReadNextEMCY:
      CV_CHART_EVAL(66, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U,
                   *chartInstance->c104_sfEvent);
      c104_out = (CV_TRANSITION_EVAL(5U, (int32_T)_SFD_CCP_CALL(5U, 0,
        CV_RELATIONAL_EVAL(5U, 5U, 0, (*chartInstance->c104_emcyValues)[1], 1.0,
                           -1, 0U, (*chartInstance->c104_emcyValues)[1] == 1.0)
        != 0U, *chartInstance->c104_sfEvent)) != 0);
      if (c104_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, *chartInstance->c104_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c104_sfEvent);
        *chartInstance->c104_is_c104_ethercat = c104_IN_disableEMCY;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, *chartInstance->c104_sfEvent);
        (*chartInstance->c104_emcyReadTrigger)[0] = 0;
        for (c104_i8 = 0; c104_i8 < 2; c104_i8++) {
          _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c104_emcyReadTrigger)
                                [c104_i8], 8U, 4U, 6U,
                                *chartInstance->c104_sfEvent, false);
        }
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                     *chartInstance->c104_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, *chartInstance->c104_sfEvent);
      break;

     case c104_IN_ReceivedFloat:
      CV_CHART_EVAL(66, 0, 3);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                   *chartInstance->c104_sfEvent);
      c104_b_out = (CV_TRANSITION_EVAL(8U, (int32_T)_SFD_CCP_CALL(8U, 0,
        CV_RELATIONAL_EVAL(5U, 8U, 0, *chartInstance->c104_currReadIdx,
                           *chartInstance->c104_valuesToRead, -1, 3U,
                           *chartInstance->c104_currReadIdx <=
                           *chartInstance->c104_valuesToRead) != 0U,
        *chartInstance->c104_sfEvent)) != 0);
      if (c104_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, *chartInstance->c104_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c104_sfEvent);
        *chartInstance->c104_is_c104_ethercat = c104_IN_ReadNextEMCY;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c104_sfEvent);
        (*chartInstance->c104_emcyReadTrigger)[0] = 1;
        for (c104_i9 = 0; c104_i9 < 2; c104_i9++) {
          _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c104_emcyReadTrigger)
                                [c104_i9], 8U, 4U, 1U,
                                *chartInstance->c104_sfEvent, false);
        }

        (*chartInstance->c104_emcyReadTrigger)[1] = c104__s32_d_(chartInstance, *
          chartInstance->c104_currReadIdx);
        for (c104_i10 = 0; c104_i10 < 2; c104_i10++) {
          _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c104_emcyReadTrigger)
                                [c104_i10], 8U, 4U, 1U,
                                *chartInstance->c104_sfEvent, false);
        }
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, *chartInstance->c104_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c104_sfEvent);
        *chartInstance->c104_is_c104_ethercat = c104_IN_StartOverwrite;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *chartInstance->c104_sfEvent);
        *chartInstance->c104_countOverwriteTrigger = 1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c104_countOverwriteTrigger,
                              9U, 4U, 3U, *chartInstance->c104_sfEvent, false);
        (*chartInstance->c104_emcyValPump)[0] = 0.0;
        for (c104_i11 = 0; c104_i11 < 3; c104_i11++) {
          _SFD_DATA_RANGE_CHECK((*chartInstance->c104_emcyValPump)[c104_i11],
                                10U, 4U, 3U, *chartInstance->c104_sfEvent, false);
        }

        (*chartInstance->c104_emcyValPump)[1] = 0.0;
        for (c104_i12 = 0; c104_i12 < 3; c104_i12++) {
          _SFD_DATA_RANGE_CHECK((*chartInstance->c104_emcyValPump)[c104_i12],
                                10U, 4U, 3U, *chartInstance->c104_sfEvent, false);
        }

        (*chartInstance->c104_emcyValPump)[2] = 0.0;
        for (c104_i13 = 0; c104_i13 < 3; c104_i13++) {
          _SFD_DATA_RANGE_CHECK((*chartInstance->c104_emcyValPump)[c104_i13],
                                10U, 4U, 3U, *chartInstance->c104_sfEvent, false);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, *chartInstance->c104_sfEvent);
      break;

     case c104_IN_StartOverwrite:
      CV_CHART_EVAL(66, 0, 4);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 12U,
                   *chartInstance->c104_sfEvent);
      c104_c_out = (CV_TRANSITION_EVAL(12U, (int32_T)_SFD_CCP_CALL(12U, 0,
        CV_RELATIONAL_EVAL(5U, 12U, 0, *chartInstance->c104_overwriteStatus, 1.0,
                           -1, 0U, *chartInstance->c104_overwriteStatus == 1.0)
        != 0U, *chartInstance->c104_sfEvent)) != 0);
      if (c104_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, *chartInstance->c104_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c104_sfEvent);
        *chartInstance->c104_is_c104_ethercat = c104_IN_DoneClearing;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c104_sfEvent);
        *chartInstance->c104_countOverwriteTrigger = 0;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c104_countOverwriteTrigger,
                              9U, 4U, 0U, *chartInstance->c104_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                     *chartInstance->c104_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, *chartInstance->c104_sfEvent);
      break;

     case c104_IN_StartReadingCount:
      CV_CHART_EVAL(66, 0, 5);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U,
                   *chartInstance->c104_sfEvent);
      c104_d_out = (CV_TRANSITION_EVAL(3U, (int32_T)_SFD_CCP_CALL(3U, 0,
        CV_RELATIONAL_EVAL(5U, 3U, 0, (*chartInstance->c104_countValues)[1], 1.0,
                           -1, 0U, (*chartInstance->c104_countValues)[1] == 1.0)
        != 0U, *chartInstance->c104_sfEvent)) != 0);
      if (c104_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, *chartInstance->c104_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, *chartInstance->c104_sfEvent);
        *chartInstance->c104_is_c104_ethercat = c104_IN_disableCount;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, *chartInstance->c104_sfEvent);
        *chartInstance->c104_triggerCountRead = 0;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c104_triggerCountRead, 7U,
                              4U, 5U, *chartInstance->c104_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                     *chartInstance->c104_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, *chartInstance->c104_sfEvent);
      break;

     case c104_IN_disableCount:
      CV_CHART_EVAL(66, 0, 6);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                   *chartInstance->c104_sfEvent);
      c104_e_out = (CV_TRANSITION_EVAL(1U, (int32_T)_SFD_CCP_CALL(1U, 0,
        CV_RELATIONAL_EVAL(5U, 1U, 0, (*chartInstance->c104_countValues)[1], 2.0,
                           -1, 5U, (*chartInstance->c104_countValues)[1] >= 2.0)
        != 0U, *chartInstance->c104_sfEvent)) != 0);
      if (c104_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, *chartInstance->c104_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                     *chartInstance->c104_sfEvent);
        c104_f_out = (CV_TRANSITION_EVAL(10U, (int32_T)_SFD_CCP_CALL(10U, 0,
          CV_RELATIONAL_EVAL(5U, 10U, 0, (*chartInstance->c104_countValues)[0],
                             0.0, -1, 0U, (*chartInstance->c104_countValues)[0] ==
                             0.0) != 0U, *chartInstance->c104_sfEvent)) != 0);
        if (c104_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, *chartInstance->c104_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, *chartInstance->c104_sfEvent);
          *chartInstance->c104_is_c104_ethercat = c104_IN_setup;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, *chartInstance->c104_sfEvent);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, *chartInstance->c104_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, *chartInstance->c104_sfEvent);
          *chartInstance->c104_is_c104_ethercat = c104_IN_startEMCYs;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, *chartInstance->c104_sfEvent);
          *chartInstance->c104_currReadIdx = 1.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c104_currReadIdx, 0U, 4U, 8U,
                                *chartInstance->c104_sfEvent, false);
          *chartInstance->c104_valuesToRead = (*chartInstance->c104_countValues)
            [1];
          _SFD_DATA_RANGE_CHECK(*chartInstance->c104_valuesToRead, 1U, 4U, 8U,
                                *chartInstance->c104_sfEvent, false);
        }
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                     *chartInstance->c104_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, *chartInstance->c104_sfEvent);
      break;

     case c104_IN_disableEMCY:
      CV_CHART_EVAL(66, 0, 7);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U,
                   *chartInstance->c104_sfEvent);
      c104_g_out = (CV_TRANSITION_EVAL(6U, (int32_T)_SFD_CCP_CALL(6U, 0,
        CV_RELATIONAL_EVAL(5U, 6U, 0, (*chartInstance->c104_emcyValues)[1], 2.0,
                           -1, 5U, (*chartInstance->c104_emcyValues)[1] >= 2.0)
        != 0U, *chartInstance->c104_sfEvent)) != 0);
      if (c104_g_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, *chartInstance->c104_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, *chartInstance->c104_sfEvent);
        *chartInstance->c104_is_c104_ethercat = c104_IN_ReceivedFloat;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c104_sfEvent);
        (*chartInstance->c104_emcyValPump)[0] = 1.0;
        for (c104_i14 = 0; c104_i14 < 3; c104_i14++) {
          _SFD_DATA_RANGE_CHECK((*chartInstance->c104_emcyValPump)[c104_i14],
                                10U, 4U, 2U, *chartInstance->c104_sfEvent, false);
        }

        (*chartInstance->c104_emcyValPump)[1] = *chartInstance->c104_driveID;
        for (c104_i15 = 0; c104_i15 < 3; c104_i15++) {
          _SFD_DATA_RANGE_CHECK((*chartInstance->c104_emcyValPump)[c104_i15],
                                10U, 4U, 2U, *chartInstance->c104_sfEvent, false);
        }

        (*chartInstance->c104_emcyValPump)[2] = (*chartInstance->c104_emcyValues)
          [0];
        for (c104_i16 = 0; c104_i16 < 3; c104_i16++) {
          _SFD_DATA_RANGE_CHECK((*chartInstance->c104_emcyValPump)[c104_i16],
                                10U, 4U, 2U, *chartInstance->c104_sfEvent, false);
        }

        (*chartInstance->c104_currReadIdx)++;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c104_currReadIdx, 0U, 4U, 2U,
                              *chartInstance->c104_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                     *chartInstance->c104_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, *chartInstance->c104_sfEvent);
      break;

     case c104_IN_setup:
      CV_CHART_EVAL(66, 0, 8);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                   *chartInstance->c104_sfEvent);
      c104_h_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0,
        CV_RELATIONAL_EVAL(5U, 2U, 0, *chartInstance->c104_triggerReading, 1.0,
                           -1, 0U, *chartInstance->c104_triggerReading == 1.0)
        != 0U, *chartInstance->c104_sfEvent)) != 0);
      if (c104_h_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, *chartInstance->c104_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, *chartInstance->c104_sfEvent);
        *chartInstance->c104_is_c104_ethercat = c104_IN_StartReadingCount;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, *chartInstance->c104_sfEvent);
        *chartInstance->c104_triggerCountRead = 1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c104_triggerCountRead, 7U,
                              4U, 4U, *chartInstance->c104_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                     *chartInstance->c104_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, *chartInstance->c104_sfEvent);
      break;

     case c104_IN_startEMCYs:
      CV_CHART_EVAL(66, 0, 9);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, *chartInstance->c104_sfEvent);
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, *chartInstance->c104_sfEvent);
      *chartInstance->c104_is_c104_ethercat = c104_IN_ReadNextEMCY;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c104_sfEvent);
      (*chartInstance->c104_emcyReadTrigger)[0] = 1;
      for (c104_i17 = 0; c104_i17 < 2; c104_i17++) {
        _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c104_emcyReadTrigger)
                              [c104_i17], 8U, 4U, 1U,
                              *chartInstance->c104_sfEvent, false);
      }

      (*chartInstance->c104_emcyReadTrigger)[1] = c104__s32_d_(chartInstance,
        *chartInstance->c104_currReadIdx);
      for (c104_i18 = 0; c104_i18 < 2; c104_i18++) {
        _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c104_emcyReadTrigger)
                              [c104_i18], 8U, 4U, 1U,
                              *chartInstance->c104_sfEvent, false);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, *chartInstance->c104_sfEvent);
      break;

     default:
      CV_CHART_EVAL(66, 0, 0);

      /* Unreachable state, for coverage only */
      *chartInstance->c104_is_c104_ethercat = c104_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c104_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 66U, *chartInstance->c104_sfEvent);
}

static void initSimStructsc104_ethercat(SFc104_ethercatInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c104_machineNumber, uint32_T
  c104_chartNumber, uint32_T c104_instanceNumber)
{
  (void)c104_machineNumber;
  (void)c104_chartNumber;
  (void)c104_instanceNumber;
}

const mxArray *sf_c104_ethercat_get_eml_resolved_functions_info(void)
{
  const mxArray *c104_nameCaptureInfo = NULL;
  c104_nameCaptureInfo = NULL;
  sf_mex_assign(&c104_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c104_nameCaptureInfo;
}

static const mxArray *c104_sf_marshallOut(void *chartInstanceVoid, void
  *c104_inData)
{
  const mxArray *c104_mxArrayOutData = NULL;
  int32_T c104_u;
  const mxArray *c104_y = NULL;
  SFc104_ethercatInstanceStruct *chartInstance;
  chartInstance = (SFc104_ethercatInstanceStruct *)chartInstanceVoid;
  c104_mxArrayOutData = NULL;
  c104_u = *(int32_T *)c104_inData;
  c104_y = NULL;
  sf_mex_assign(&c104_y, sf_mex_create("y", &c104_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c104_mxArrayOutData, c104_y, false);
  return c104_mxArrayOutData;
}

static int32_T c104_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_b_sfEvent, const char_T *c104_identifier)
{
  int32_T c104_y;
  emlrtMsgIdentifier c104_thisId;
  c104_thisId.fIdentifier = c104_identifier;
  c104_thisId.fParent = NULL;
  c104_y = c104_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c104_b_sfEvent),
    &c104_thisId);
  sf_mex_destroy(&c104_b_sfEvent);
  return c104_y;
}

static int32_T c104_b_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_u, const emlrtMsgIdentifier *c104_parentId)
{
  int32_T c104_y;
  int32_T c104_i19;
  (void)chartInstance;
  sf_mex_import(c104_parentId, sf_mex_dup(c104_u), &c104_i19, 1, 6, 0U, 0, 0U, 0);
  c104_y = c104_i19;
  sf_mex_destroy(&c104_u);
  return c104_y;
}

static void c104_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c104_mxArrayInData, const char_T *c104_varName, void *c104_outData)
{
  const mxArray *c104_b_sfEvent;
  const char_T *c104_identifier;
  emlrtMsgIdentifier c104_thisId;
  int32_T c104_y;
  SFc104_ethercatInstanceStruct *chartInstance;
  chartInstance = (SFc104_ethercatInstanceStruct *)chartInstanceVoid;
  c104_b_sfEvent = sf_mex_dup(c104_mxArrayInData);
  c104_identifier = c104_varName;
  c104_thisId.fIdentifier = c104_identifier;
  c104_thisId.fParent = NULL;
  c104_y = c104_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c104_b_sfEvent),
    &c104_thisId);
  sf_mex_destroy(&c104_b_sfEvent);
  *(int32_T *)c104_outData = c104_y;
  sf_mex_destroy(&c104_mxArrayInData);
}

static const mxArray *c104_b_sf_marshallOut(void *chartInstanceVoid, void
  *c104_inData)
{
  const mxArray *c104_mxArrayOutData = NULL;
  real_T c104_u;
  const mxArray *c104_y = NULL;
  SFc104_ethercatInstanceStruct *chartInstance;
  chartInstance = (SFc104_ethercatInstanceStruct *)chartInstanceVoid;
  c104_mxArrayOutData = NULL;
  c104_u = *(real_T *)c104_inData;
  c104_y = NULL;
  sf_mex_assign(&c104_y, sf_mex_create("y", &c104_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c104_mxArrayOutData, c104_y, false);
  return c104_mxArrayOutData;
}

static const mxArray *c104_c_sf_marshallOut(void *chartInstanceVoid, void
  *c104_inData)
{
  const mxArray *c104_mxArrayOutData = NULL;
  int32_T c104_i20;
  real_T c104_u[2];
  const mxArray *c104_y = NULL;
  SFc104_ethercatInstanceStruct *chartInstance;
  chartInstance = (SFc104_ethercatInstanceStruct *)chartInstanceVoid;
  c104_mxArrayOutData = NULL;
  for (c104_i20 = 0; c104_i20 < 2; c104_i20++) {
    c104_u[c104_i20] = (*(real_T (*)[2])c104_inData)[c104_i20];
  }

  c104_y = NULL;
  sf_mex_assign(&c104_y, sf_mex_create("y", c104_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c104_mxArrayOutData, c104_y, false);
  return c104_mxArrayOutData;
}

static const mxArray *c104_d_sf_marshallOut(void *chartInstanceVoid, void
  *c104_inData)
{
  const mxArray *c104_mxArrayOutData = NULL;
  int32_T c104_i21;
  int32_T c104_u[2];
  const mxArray *c104_y = NULL;
  SFc104_ethercatInstanceStruct *chartInstance;
  chartInstance = (SFc104_ethercatInstanceStruct *)chartInstanceVoid;
  c104_mxArrayOutData = NULL;
  for (c104_i21 = 0; c104_i21 < 2; c104_i21++) {
    c104_u[c104_i21] = (*(int32_T (*)[2])c104_inData)[c104_i21];
  }

  c104_y = NULL;
  sf_mex_assign(&c104_y, sf_mex_create("y", c104_u, 6, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c104_mxArrayOutData, c104_y, false);
  return c104_mxArrayOutData;
}

static void c104_c_emlrt_marshallIn(SFc104_ethercatInstanceStruct *chartInstance,
  const mxArray *c104_b_emcyReadTrigger, const char_T *c104_identifier, int32_T
  c104_y[2])
{
  emlrtMsgIdentifier c104_thisId;
  c104_thisId.fIdentifier = c104_identifier;
  c104_thisId.fParent = NULL;
  c104_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c104_b_emcyReadTrigger),
    &c104_thisId, c104_y);
  sf_mex_destroy(&c104_b_emcyReadTrigger);
}

static void c104_d_emlrt_marshallIn(SFc104_ethercatInstanceStruct *chartInstance,
  const mxArray *c104_u, const emlrtMsgIdentifier *c104_parentId, int32_T
  c104_y[2])
{
  int32_T c104_iv1[2];
  int32_T c104_i22;
  (void)chartInstance;
  sf_mex_import(c104_parentId, sf_mex_dup(c104_u), c104_iv1, 1, 6, 0U, 1, 0U, 1,
                2);
  for (c104_i22 = 0; c104_i22 < 2; c104_i22++) {
    c104_y[c104_i22] = c104_iv1[c104_i22];
  }

  sf_mex_destroy(&c104_u);
}

static void c104_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c104_mxArrayInData, const char_T *c104_varName, void *c104_outData)
{
  const mxArray *c104_b_emcyReadTrigger;
  const char_T *c104_identifier;
  emlrtMsgIdentifier c104_thisId;
  int32_T c104_y[2];
  int32_T c104_i23;
  SFc104_ethercatInstanceStruct *chartInstance;
  chartInstance = (SFc104_ethercatInstanceStruct *)chartInstanceVoid;
  c104_b_emcyReadTrigger = sf_mex_dup(c104_mxArrayInData);
  c104_identifier = c104_varName;
  c104_thisId.fIdentifier = c104_identifier;
  c104_thisId.fParent = NULL;
  c104_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c104_b_emcyReadTrigger),
    &c104_thisId, c104_y);
  sf_mex_destroy(&c104_b_emcyReadTrigger);
  for (c104_i23 = 0; c104_i23 < 2; c104_i23++) {
    (*(int32_T (*)[2])c104_outData)[c104_i23] = c104_y[c104_i23];
  }

  sf_mex_destroy(&c104_mxArrayInData);
}

static const mxArray *c104_e_sf_marshallOut(void *chartInstanceVoid, void
  *c104_inData)
{
  const mxArray *c104_mxArrayOutData = NULL;
  int32_T c104_i24;
  real_T c104_u[3];
  const mxArray *c104_y = NULL;
  SFc104_ethercatInstanceStruct *chartInstance;
  chartInstance = (SFc104_ethercatInstanceStruct *)chartInstanceVoid;
  c104_mxArrayOutData = NULL;
  for (c104_i24 = 0; c104_i24 < 3; c104_i24++) {
    c104_u[c104_i24] = (*(real_T (*)[3])c104_inData)[c104_i24];
  }

  c104_y = NULL;
  sf_mex_assign(&c104_y, sf_mex_create("y", c104_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c104_mxArrayOutData, c104_y, false);
  return c104_mxArrayOutData;
}

static void c104_e_emlrt_marshallIn(SFc104_ethercatInstanceStruct *chartInstance,
  const mxArray *c104_b_emcyValPump, const char_T *c104_identifier, real_T
  c104_y[3])
{
  emlrtMsgIdentifier c104_thisId;
  c104_thisId.fIdentifier = c104_identifier;
  c104_thisId.fParent = NULL;
  c104_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c104_b_emcyValPump),
    &c104_thisId, c104_y);
  sf_mex_destroy(&c104_b_emcyValPump);
}

static void c104_f_emlrt_marshallIn(SFc104_ethercatInstanceStruct *chartInstance,
  const mxArray *c104_u, const emlrtMsgIdentifier *c104_parentId, real_T c104_y
  [3])
{
  real_T c104_dv1[3];
  int32_T c104_i25;
  (void)chartInstance;
  sf_mex_import(c104_parentId, sf_mex_dup(c104_u), c104_dv1, 1, 0, 0U, 1, 0U, 1,
                3);
  for (c104_i25 = 0; c104_i25 < 3; c104_i25++) {
    c104_y[c104_i25] = c104_dv1[c104_i25];
  }

  sf_mex_destroy(&c104_u);
}

static void c104_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c104_mxArrayInData, const char_T *c104_varName, void *c104_outData)
{
  const mxArray *c104_b_emcyValPump;
  const char_T *c104_identifier;
  emlrtMsgIdentifier c104_thisId;
  real_T c104_y[3];
  int32_T c104_i26;
  SFc104_ethercatInstanceStruct *chartInstance;
  chartInstance = (SFc104_ethercatInstanceStruct *)chartInstanceVoid;
  c104_b_emcyValPump = sf_mex_dup(c104_mxArrayInData);
  c104_identifier = c104_varName;
  c104_thisId.fIdentifier = c104_identifier;
  c104_thisId.fParent = NULL;
  c104_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c104_b_emcyValPump),
    &c104_thisId, c104_y);
  sf_mex_destroy(&c104_b_emcyValPump);
  for (c104_i26 = 0; c104_i26 < 3; c104_i26++) {
    (*(real_T (*)[3])c104_outData)[c104_i26] = c104_y[c104_i26];
  }

  sf_mex_destroy(&c104_mxArrayInData);
}

static real_T c104_g_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_b_currReadIdx, const char_T
  *c104_identifier)
{
  real_T c104_y;
  emlrtMsgIdentifier c104_thisId;
  c104_thisId.fIdentifier = c104_identifier;
  c104_thisId.fParent = NULL;
  c104_y = c104_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c104_b_currReadIdx),
    &c104_thisId);
  sf_mex_destroy(&c104_b_currReadIdx);
  return c104_y;
}

static real_T c104_h_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_u, const emlrtMsgIdentifier *c104_parentId)
{
  real_T c104_y;
  real_T c104_d0;
  (void)chartInstance;
  sf_mex_import(c104_parentId, sf_mex_dup(c104_u), &c104_d0, 1, 0, 0U, 0, 0U, 0);
  c104_y = c104_d0;
  sf_mex_destroy(&c104_u);
  return c104_y;
}

static void c104_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c104_mxArrayInData, const char_T *c104_varName, void *c104_outData)
{
  const mxArray *c104_b_currReadIdx;
  const char_T *c104_identifier;
  emlrtMsgIdentifier c104_thisId;
  real_T c104_y;
  SFc104_ethercatInstanceStruct *chartInstance;
  chartInstance = (SFc104_ethercatInstanceStruct *)chartInstanceVoid;
  c104_b_currReadIdx = sf_mex_dup(c104_mxArrayInData);
  c104_identifier = c104_varName;
  c104_thisId.fIdentifier = c104_identifier;
  c104_thisId.fParent = NULL;
  c104_y = c104_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c104_b_currReadIdx),
    &c104_thisId);
  sf_mex_destroy(&c104_b_currReadIdx);
  *(real_T *)c104_outData = c104_y;
  sf_mex_destroy(&c104_mxArrayInData);
}

static uint8_T c104_i_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_b_is_active_c104_ethercat, const char_T
  *c104_identifier)
{
  uint8_T c104_y;
  emlrtMsgIdentifier c104_thisId;
  c104_thisId.fIdentifier = c104_identifier;
  c104_thisId.fParent = NULL;
  c104_y = c104_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c104_b_is_active_c104_ethercat), &c104_thisId);
  sf_mex_destroy(&c104_b_is_active_c104_ethercat);
  return c104_y;
}

static uint8_T c104_j_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_u, const emlrtMsgIdentifier *c104_parentId)
{
  uint8_T c104_y;
  uint8_T c104_u0;
  (void)chartInstance;
  sf_mex_import(c104_parentId, sf_mex_dup(c104_u), &c104_u0, 1, 3, 0U, 0, 0U, 0);
  c104_y = c104_u0;
  sf_mex_destroy(&c104_u);
  return c104_y;
}

static const mxArray *c104_k_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_b_setSimStateSideEffectsInfo, const char_T
  *c104_identifier)
{
  const mxArray *c104_y = NULL;
  emlrtMsgIdentifier c104_thisId;
  c104_y = NULL;
  c104_thisId.fIdentifier = c104_identifier;
  c104_thisId.fParent = NULL;
  sf_mex_assign(&c104_y, c104_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c104_b_setSimStateSideEffectsInfo), &c104_thisId), false);
  sf_mex_destroy(&c104_b_setSimStateSideEffectsInfo);
  return c104_y;
}

static const mxArray *c104_l_emlrt_marshallIn(SFc104_ethercatInstanceStruct
  *chartInstance, const mxArray *c104_u, const emlrtMsgIdentifier *c104_parentId)
{
  const mxArray *c104_y = NULL;
  (void)chartInstance;
  (void)c104_parentId;
  c104_y = NULL;
  sf_mex_assign(&c104_y, sf_mex_duplicatearraysafe(&c104_u), false);
  sf_mex_destroy(&c104_u);
  return c104_y;
}

static int32_T c104__s32_d_(SFc104_ethercatInstanceStruct *chartInstance, real_T
  c104_b)
{
  int32_T c104_a;
  c104_a = (int32_T)c104_b;
  if ((real_T)c104_a != (c104_b < 0.0 ? muDoubleScalarCeil(c104_b) :
                         muDoubleScalarFloor(c104_b))) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, 1U, 0U, *chartInstance->c104_sfEvent,
      false);
  }

  return c104_a;
}

static void init_dsm_address_info(SFc104_ethercatInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc104_ethercatInstanceStruct
  *chartInstance)
{
  chartInstance->c104_sfEvent = (int32_T *)ssGetDWork_wrapper(chartInstance->S,
    0);
  chartInstance->c104_isStable = (boolean_T *)ssGetDWork_wrapper
    (chartInstance->S, 1);
  chartInstance->c104_is_active_c104_ethercat = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 2);
  chartInstance->c104_is_c104_ethercat = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 3);
  chartInstance->c104_triggerReading = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c104_driveID = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c104_triggerCountRead = (int32_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c104_countValues = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c104_emcyReadTrigger = (int32_T (*)[2])
    ssGetOutputPortSignal_wrapper(chartInstance->S, 2);
  chartInstance->c104_emcyValues = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c104_countOverwriteTrigger = (int32_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 3);
  chartInstance->c104_emcyValPump = (real_T (*)[3])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c104_currReadIdx = (real_T *)ssGetDWork_wrapper
    (chartInstance->S, 4);
  chartInstance->c104_valuesToRead = (real_T *)ssGetDWork_wrapper
    (chartInstance->S, 5);
  chartInstance->c104_overwriteStatus = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
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
void sf_c104_ethercat_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2269200913U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(632070806U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2710360911U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2645271960U);
}

mxArray* sf_c104_ethercat_get_post_codegen_info(void);
mxArray *sf_c104_ethercat_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("UZjFbtQYzoFuxtUyPKRSjD");
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
      pr[0] = (double)(2);
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
      pr[0] = (double)(2);
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

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(8));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(8));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(8));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c104_ethercat_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c104_ethercat_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c104_ethercat_jit_fallback_info(void)
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

mxArray *sf_c104_ethercat_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c104_ethercat_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c104_ethercat(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x8'type','srcId','name','auxInfo'{{M[1],M[215],T\"countOverwriteTrigger\",},{M[1],M[213],T\"emcyReadTrigger\",},{M[1],M[216],T\"emcyValPump\",},{M[1],M[211],T\"triggerCountRead\",},{M[3],M[217],T\"currReadIdx\",},{M[3],M[222],T\"valuesToRead\",},{M[8],M[0],T\"is_active_c104_ethercat\",},{M[9],M[0],T\"is_c104_ethercat\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 8, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c104_ethercat_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc104_ethercatInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc104_ethercatInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ethercatMachineNumber_,
           104,
           9,
           13,
           0,
           11,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_ethercatMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_ethercatMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _ethercatMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,0,0,0,"currReadIdx");
          _SFD_SET_DATA_PROPS(1,0,0,0,"valuesToRead");
          _SFD_SET_DATA_PROPS(2,1,1,0,"triggerReading");
          _SFD_SET_DATA_PROPS(3,1,1,0,"driveID");
          _SFD_SET_DATA_PROPS(4,1,1,0,"countValues");
          _SFD_SET_DATA_PROPS(5,1,1,0,"emcyValues");
          _SFD_SET_DATA_PROPS(6,1,1,0,"overwriteStatus");
          _SFD_SET_DATA_PROPS(7,2,0,1,"triggerCountRead");
          _SFD_SET_DATA_PROPS(8,2,0,1,"emcyReadTrigger");
          _SFD_SET_DATA_PROPS(9,2,0,1,"countOverwriteTrigger");
          _SFD_SET_DATA_PROPS(10,2,0,1,"emcyValPump");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(8,0,0);
          _SFD_CH_SUBSTATE_COUNT(9);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_CH_SUBSTATE_INDEX(2,2);
          _SFD_CH_SUBSTATE_INDEX(3,3);
          _SFD_CH_SUBSTATE_INDEX(4,4);
          _SFD_CH_SUBSTATE_INDEX(5,5);
          _SFD_CH_SUBSTATE_INDEX(6,6);
          _SFD_CH_SUBSTATE_INDEX(7,7);
          _SFD_CH_SUBSTATE_INDEX(8,8);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
        }

        _SFD_CV_INIT_CHART(9,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 20 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 20 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 20 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(3,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 20 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(3,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 20 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 20 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 5, 5, 5, 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 20 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(10,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 20 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(10,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(11,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(5,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 19 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(5,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 29 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(8,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 29 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 3, 3, 3, 3, 3 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(8,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(6,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 19 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 5, 5, 5, 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(6,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 21 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(12,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 21 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(12,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c104_b_sf_marshallOut,(MexInFcnForType)
          c104_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c104_b_sf_marshallOut,(MexInFcnForType)
          c104_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c104_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c104_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c104_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c104_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c104_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c104_sf_marshallOut,(MexInFcnForType)c104_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_INT32,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c104_d_sf_marshallOut,(MexInFcnForType)
            c104_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(9,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c104_sf_marshallOut,(MexInFcnForType)c104_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c104_e_sf_marshallOut,(MexInFcnForType)
            c104_c_sf_marshallIn);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _ethercatMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc104_ethercatInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc104_ethercatInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c104_triggerReading);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c104_driveID);
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c104_triggerCountRead);
        _SFD_SET_DATA_VALUE_PTR(4U, *chartInstance->c104_countValues);
        _SFD_SET_DATA_VALUE_PTR(8U, *chartInstance->c104_emcyReadTrigger);
        _SFD_SET_DATA_VALUE_PTR(5U, *chartInstance->c104_emcyValues);
        _SFD_SET_DATA_VALUE_PTR(9U, chartInstance->c104_countOverwriteTrigger);
        _SFD_SET_DATA_VALUE_PTR(10U, *chartInstance->c104_emcyValPump);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c104_currReadIdx);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c104_valuesToRead);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c104_overwriteStatus);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s6RcW5yiU3ZweNok7pK1d8E";
}

static void sf_check_dwork_consistency(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    const uint32_T *sfunDWorkChecksum = sf_get_sfun_dwork_checksum();
    mxArray *infoStruct = load_ethercat_optimization_info();
    mxArray* mxRTWDWorkChecksum = sf_get_dwork_info_from_mat_file(S,
      sf_get_instance_specialization(), infoStruct, 104, "dworkChecksum");
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

static void sf_opaque_initialize_c104_ethercat(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc104_ethercatInstanceStruct*) chartInstanceVar
    )->S);
  chart_debug_initialization(((SFc104_ethercatInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c104_ethercat((SFc104_ethercatInstanceStruct*)
    chartInstanceVar);
  initialize_c104_ethercat((SFc104_ethercatInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c104_ethercat(void *chartInstanceVar)
{
  enable_c104_ethercat((SFc104_ethercatInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c104_ethercat(void *chartInstanceVar)
{
  disable_c104_ethercat((SFc104_ethercatInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c104_ethercat(void *chartInstanceVar)
{
  sf_gateway_c104_ethercat((SFc104_ethercatInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c104_ethercat(void *chartInstanceVar)
{
  ext_mode_exec_c104_ethercat((SFc104_ethercatInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c104_ethercat(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c104_ethercat((SFc104_ethercatInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c104_ethercat(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c104_ethercat((SFc104_ethercatInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c104_ethercat(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc104_ethercatInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ethercat_optimization_info();
    }

    finalize_c104_ethercat((SFc104_ethercatInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc104_ethercat((SFc104_ethercatInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c104_ethercat(SimStruct *S)
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
    initialize_params_c104_ethercat((SFc104_ethercatInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

mxArray *sf_c104_ethercat_get_testpoint_info(void)
{
  return NULL;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x6'type','isSigned','wordLength','bias','slope','exponent','isScaledDouble','isComplex','size'{{T\"int32\",,,,,,,M[0],M[]},{T\"boolean\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"double\",,,,,,,M[0],M[]},{T\"double\",,,,,,,M[0],M[]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 6, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 2916794536U, 554565360U, 2479569735U,
    2185685532U };

  return checksum;
}

static void mdlSetWorkWidths_c104_ethercat(SimStruct *S)
{
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ethercat_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      104);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,104,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,104);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,104,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,104,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,104);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1247110324U));
  ssSetChecksum1(S,(697370539U));
  ssSetChecksum2(S,(1665143589U));
  ssSetChecksum3(S,(2226209443U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c104_ethercat(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c104_ethercat(SimStruct *S)
{
  SFc104_ethercatInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc104_ethercatInstanceStruct *)utMalloc(sizeof
    (SFc104_ethercatInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc104_ethercatInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c104_ethercat;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c104_ethercat;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c104_ethercat;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c104_ethercat;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c104_ethercat;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c104_ethercat;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c104_ethercat;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c104_ethercat;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c104_ethercat;
  chartInstance->chartInfo.mdlStart = mdlStart_c104_ethercat;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c104_ethercat;
  chartInstance->chartInfo.extModeExec = sf_opaque_ext_mode_exec_c104_ethercat;
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

void c104_ethercat_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c104_ethercat(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c104_ethercat(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c104_ethercat(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c104_ethercat_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
