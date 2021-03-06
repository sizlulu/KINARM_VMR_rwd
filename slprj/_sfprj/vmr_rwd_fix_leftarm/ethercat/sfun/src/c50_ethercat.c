/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ethercat_sfun.h"
#include "c50_ethercat.h"
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
#define c50_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)
#define c50_IN_ReadNext                ((uint8_T)1U)
#define c50_IN_disable                 ((uint8_T)2U)
#define c50_IN_setup                   ((uint8_T)3U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c50_ethercat(SFc50_ethercatInstanceStruct *chartInstance);
static void initialize_params_c50_ethercat(SFc50_ethercatInstanceStruct
  *chartInstance);
static void enable_c50_ethercat(SFc50_ethercatInstanceStruct *chartInstance);
static void disable_c50_ethercat(SFc50_ethercatInstanceStruct *chartInstance);
static void c50_update_debugger_state_c50_ethercat(SFc50_ethercatInstanceStruct *
  chartInstance);
static void ext_mode_exec_c50_ethercat(SFc50_ethercatInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c50_ethercat(SFc50_ethercatInstanceStruct
  *chartInstance);
static void set_sim_state_c50_ethercat(SFc50_ethercatInstanceStruct
  *chartInstance, const mxArray *c50_st);
static void c50_set_sim_state_side_effects_c50_ethercat
  (SFc50_ethercatInstanceStruct *chartInstance);
static void finalize_c50_ethercat(SFc50_ethercatInstanceStruct *chartInstance);
static void sf_gateway_c50_ethercat(SFc50_ethercatInstanceStruct *chartInstance);
static void mdl_start_c50_ethercat(SFc50_ethercatInstanceStruct *chartInstance);
static void initSimStructsc50_ethercat(SFc50_ethercatInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c50_machineNumber, uint32_T
  c50_chartNumber, uint32_T c50_instanceNumber);
static const mxArray *c50_sf_marshallOut(void *chartInstanceVoid, void
  *c50_inData);
static int32_T c50_emlrt_marshallIn(SFc50_ethercatInstanceStruct *chartInstance,
  const mxArray *c50_b_sfEvent, const char_T *c50_identifier);
static int32_T c50_b_emlrt_marshallIn(SFc50_ethercatInstanceStruct
  *chartInstance, const mxArray *c50_u, const emlrtMsgIdentifier *c50_parentId);
static void c50_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c50_mxArrayInData, const char_T *c50_varName, void *c50_outData);
static const mxArray *c50_b_sf_marshallOut(void *chartInstanceVoid, void
  *c50_inData);
static uint8_T c50_c_emlrt_marshallIn(SFc50_ethercatInstanceStruct
  *chartInstance, const mxArray *c50_b_is_active_c50_ethercat, const char_T
  *c50_identifier);
static uint8_T c50_d_emlrt_marshallIn(SFc50_ethercatInstanceStruct
  *chartInstance, const mxArray *c50_u, const emlrtMsgIdentifier *c50_parentId);
static const mxArray *c50_e_emlrt_marshallIn(SFc50_ethercatInstanceStruct
  *chartInstance, const mxArray *c50_b_setSimStateSideEffectsInfo, const char_T *
  c50_identifier);
static const mxArray *c50_f_emlrt_marshallIn(SFc50_ethercatInstanceStruct
  *chartInstance, const mxArray *c50_u, const emlrtMsgIdentifier *c50_parentId);
static int32_T c50__s32_d_(SFc50_ethercatInstanceStruct *chartInstance, real_T
  c50_b);
static void init_dsm_address_info(SFc50_ethercatInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc50_ethercatInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c50_ethercat(SFc50_ethercatInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc50_ethercat(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  *chartInstance->c50_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c50_doSetSimStateSideEffects = 0U;
  chartInstance->c50_setSimStateSideEffectsInfo = NULL;
  *chartInstance->c50_is_active_c50_ethercat = 0U;
  *chartInstance->c50_is_c50_ethercat = c50_IN_NO_ACTIVE_CHILD;
  *chartInstance->c50_lastTriggerValue = 0;
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c50_enable = 0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c50_complete = 0;
  }
}

static void initialize_params_c50_ethercat(SFc50_ethercatInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c50_ethercat(SFc50_ethercatInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c50_ethercat(SFc50_ethercatInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c50_update_debugger_state_c50_ethercat(SFc50_ethercatInstanceStruct *
  chartInstance)
{
  uint32_T c50_prevAniVal;
  c50_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (*chartInstance->c50_is_active_c50_ethercat == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 15U, *chartInstance->c50_sfEvent);
  }

  if (*chartInstance->c50_is_c50_ethercat == c50_IN_setup) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c50_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c50_sfEvent);
  }

  if (*chartInstance->c50_is_c50_ethercat == c50_IN_ReadNext) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c50_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c50_sfEvent);
  }

  if (*chartInstance->c50_is_c50_ethercat == c50_IN_disable) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c50_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c50_sfEvent);
  }

  _SFD_SET_ANIMATION(c50_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static void ext_mode_exec_c50_ethercat(SFc50_ethercatInstanceStruct
  *chartInstance)
{
  c50_update_debugger_state_c50_ethercat(chartInstance);
}

static const mxArray *get_sim_state_c50_ethercat(SFc50_ethercatInstanceStruct
  *chartInstance)
{
  const mxArray *c50_st;
  const mxArray *c50_y = NULL;
  int32_T c50_hoistedGlobal;
  int32_T c50_u;
  const mxArray *c50_b_y = NULL;
  int32_T c50_b_hoistedGlobal;
  int32_T c50_b_u;
  const mxArray *c50_c_y = NULL;
  int32_T c50_c_hoistedGlobal;
  int32_T c50_c_u;
  const mxArray *c50_d_y = NULL;
  uint8_T c50_d_hoistedGlobal;
  uint8_T c50_d_u;
  const mxArray *c50_e_y = NULL;
  uint8_T c50_e_hoistedGlobal;
  uint8_T c50_e_u;
  const mxArray *c50_f_y = NULL;
  c50_st = NULL;
  c50_st = NULL;
  c50_y = NULL;
  sf_mex_assign(&c50_y, sf_mex_createcellmatrix(5, 1), false);
  c50_hoistedGlobal = *chartInstance->c50_complete;
  c50_u = c50_hoistedGlobal;
  c50_b_y = NULL;
  sf_mex_assign(&c50_b_y, sf_mex_create("y", &c50_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c50_y, 0, c50_b_y);
  c50_b_hoistedGlobal = *chartInstance->c50_enable;
  c50_b_u = c50_b_hoistedGlobal;
  c50_c_y = NULL;
  sf_mex_assign(&c50_c_y, sf_mex_create("y", &c50_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c50_y, 1, c50_c_y);
  c50_c_hoistedGlobal = *chartInstance->c50_lastTriggerValue;
  c50_c_u = c50_c_hoistedGlobal;
  c50_d_y = NULL;
  sf_mex_assign(&c50_d_y, sf_mex_create("y", &c50_c_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c50_y, 2, c50_d_y);
  c50_d_hoistedGlobal = *chartInstance->c50_is_active_c50_ethercat;
  c50_d_u = c50_d_hoistedGlobal;
  c50_e_y = NULL;
  sf_mex_assign(&c50_e_y, sf_mex_create("y", &c50_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c50_y, 3, c50_e_y);
  c50_e_hoistedGlobal = *chartInstance->c50_is_c50_ethercat;
  c50_e_u = c50_e_hoistedGlobal;
  c50_f_y = NULL;
  sf_mex_assign(&c50_f_y, sf_mex_create("y", &c50_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c50_y, 4, c50_f_y);
  sf_mex_assign(&c50_st, c50_y, false);
  return c50_st;
}

static void set_sim_state_c50_ethercat(SFc50_ethercatInstanceStruct
  *chartInstance, const mxArray *c50_st)
{
  const mxArray *c50_u;
  c50_u = sf_mex_dup(c50_st);
  *chartInstance->c50_complete = c50_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("complete", c50_u, 0)), "complete");
  *chartInstance->c50_enable = c50_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("enable", c50_u, 1)), "enable");
  *chartInstance->c50_lastTriggerValue = c50_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("lastTriggerValue", c50_u, 2)), "lastTriggerValue");
  *chartInstance->c50_is_active_c50_ethercat = c50_c_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c50_ethercat", c50_u, 3)),
     "is_active_c50_ethercat");
  *chartInstance->c50_is_c50_ethercat = c50_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_c50_ethercat", c50_u, 4)), "is_c50_ethercat");
  sf_mex_assign(&chartInstance->c50_setSimStateSideEffectsInfo,
                c50_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "setSimStateSideEffectsInfo", c50_u, 5)), "setSimStateSideEffectsInfo"),
                true);
  sf_mex_destroy(&c50_u);
  chartInstance->c50_doSetSimStateSideEffects = 1U;
  c50_update_debugger_state_c50_ethercat(chartInstance);
  sf_mex_destroy(&c50_st);
}

static void c50_set_sim_state_side_effects_c50_ethercat
  (SFc50_ethercatInstanceStruct *chartInstance)
{
  if (chartInstance->c50_doSetSimStateSideEffects != 0) {
    chartInstance->c50_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c50_ethercat(SFc50_ethercatInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c50_setSimStateSideEffectsInfo);
}

static void sf_gateway_c50_ethercat(SFc50_ethercatInstanceStruct *chartInstance)
{
  boolean_T c50_out;
  boolean_T c50_b_out;
  boolean_T c50_c_out;
  boolean_T c50_d_out;
  boolean_T guard1 = false;
  c50_set_sim_state_side_effects_c50_ethercat(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 15U, *chartInstance->c50_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c50_lastTriggerValue, 0U, 1U, 0U,
                        *chartInstance->c50_sfEvent, false);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c50_complete, 4U, 1U, 0U,
                        *chartInstance->c50_sfEvent, false);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c50_enable, 3U, 1U, 0U,
                        *chartInstance->c50_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c50_readState, 2U, 1U, 0U,
                        *chartInstance->c50_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c50_triggerWriting, 1U, 1U, 0U,
                        *chartInstance->c50_sfEvent, false);
  *chartInstance->c50_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 15U, *chartInstance->c50_sfEvent);
  if (*chartInstance->c50_is_active_c50_ethercat == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 15U,
                 *chartInstance->c50_sfEvent);
    *chartInstance->c50_is_active_c50_ethercat = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, *chartInstance->c50_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, *chartInstance->c50_sfEvent);
    *chartInstance->c50_is_c50_ethercat = c50_IN_setup;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c50_sfEvent);
    *chartInstance->c50_enable = 0;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c50_enable, 3U, 4U, 2U,
                          *chartInstance->c50_sfEvent, false);
  } else {
    switch (*chartInstance->c50_is_c50_ethercat) {
     case c50_IN_ReadNext:
      CV_CHART_EVAL(15, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U,
                   *chartInstance->c50_sfEvent);
      c50_out = (CV_TRANSITION_EVAL(3U, (int32_T)_SFD_CCP_CALL(3U, 0,
        CV_RELATIONAL_EVAL(5U, 3U, 0, *chartInstance->c50_readState, 1.0, -1, 0U,
                           *chartInstance->c50_readState == 1.0) != 0U,
        *chartInstance->c50_sfEvent)) != 0);
      if (c50_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, *chartInstance->c50_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c50_sfEvent);
        *chartInstance->c50_is_c50_ethercat = c50_IN_disable;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c50_sfEvent);
        *chartInstance->c50_enable = 0;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c50_enable, 3U, 4U, 1U,
                              *chartInstance->c50_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                     *chartInstance->c50_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *chartInstance->c50_sfEvent);
      break;

     case c50_IN_disable:
      CV_CHART_EVAL(15, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                   *chartInstance->c50_sfEvent);
      c50_b_out = (CV_TRANSITION_EVAL(1U, (int32_T)_SFD_CCP_CALL(1U, 0,
        CV_RELATIONAL_EVAL(5U, 1U, 0, *chartInstance->c50_readState, 2.0, -1, 0U,
                           *chartInstance->c50_readState == 2.0) != 0U,
        *chartInstance->c50_sfEvent)) != 0);
      guard1 = false;
      if (c50_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, *chartInstance->c50_sfEvent);
        *chartInstance->c50_complete = 1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c50_complete, 4U, 5U, 1U, *
                              chartInstance->c50_sfEvent, false);
        guard1 = true;
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U,
                     *chartInstance->c50_sfEvent);
        c50_c_out = (CV_TRANSITION_EVAL(5U, (int32_T)_SFD_CCP_CALL(5U, 0,
          CV_RELATIONAL_EVAL(5U, 5U, 0, *chartInstance->c50_readState, 3.0, -1,
                             0U, *chartInstance->c50_readState == 3.0) != 0U,
          *chartInstance->c50_sfEvent)) != 0);
        if (c50_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, *chartInstance->c50_sfEvent);
          *chartInstance->c50_complete = -1;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c50_complete, 4U, 5U, 5U,
                                *chartInstance->c50_sfEvent, false);
          guard1 = true;
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                       *chartInstance->c50_sfEvent);
        }
      }

      if (guard1 == true) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, *chartInstance->c50_sfEvent);
        *chartInstance->c50_lastTriggerValue = c50__s32_d_(chartInstance,
          *chartInstance->c50_triggerWriting);
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c50_lastTriggerValue, 0U,
                              5U, 4U, *chartInstance->c50_sfEvent, false);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c50_sfEvent);
        *chartInstance->c50_is_c50_ethercat = c50_IN_setup;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c50_sfEvent);
        *chartInstance->c50_enable = 0;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c50_enable, 3U, 4U, 2U,
                              *chartInstance->c50_sfEvent, false);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, *chartInstance->c50_sfEvent);
      break;

     case c50_IN_setup:
      CV_CHART_EVAL(15, 0, 3);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                   *chartInstance->c50_sfEvent);
      c50_d_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0,
        CV_RELATIONAL_EVAL(5U, 2U, 0, *chartInstance->c50_triggerWriting,
                           (real_T)*chartInstance->c50_lastTriggerValue, -1, 1U,
                           *chartInstance->c50_triggerWriting != (real_T)
                           *chartInstance->c50_lastTriggerValue) != 0U,
        *chartInstance->c50_sfEvent)) != 0);
      if (c50_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, *chartInstance->c50_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c50_sfEvent);
        *chartInstance->c50_is_c50_ethercat = c50_IN_ReadNext;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c50_sfEvent);
        *chartInstance->c50_enable = 1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c50_enable, 3U, 4U, 0U,
                              *chartInstance->c50_sfEvent, false);
        *chartInstance->c50_complete = 0;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c50_complete, 4U, 4U, 0U, *
                              chartInstance->c50_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                     *chartInstance->c50_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, *chartInstance->c50_sfEvent);
      break;

     default:
      CV_CHART_EVAL(15, 0, 0);

      /* Unreachable state, for coverage only */
      *chartInstance->c50_is_c50_ethercat = c50_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c50_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, *chartInstance->c50_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ethercatMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c50_ethercat(SFc50_ethercatInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc50_ethercat(SFc50_ethercatInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c50_machineNumber, uint32_T
  c50_chartNumber, uint32_T c50_instanceNumber)
{
  (void)c50_machineNumber;
  (void)c50_chartNumber;
  (void)c50_instanceNumber;
}

const mxArray *sf_c50_ethercat_get_eml_resolved_functions_info(void)
{
  const mxArray *c50_nameCaptureInfo = NULL;
  c50_nameCaptureInfo = NULL;
  sf_mex_assign(&c50_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c50_nameCaptureInfo;
}

static const mxArray *c50_sf_marshallOut(void *chartInstanceVoid, void
  *c50_inData)
{
  const mxArray *c50_mxArrayOutData = NULL;
  int32_T c50_u;
  const mxArray *c50_y = NULL;
  SFc50_ethercatInstanceStruct *chartInstance;
  chartInstance = (SFc50_ethercatInstanceStruct *)chartInstanceVoid;
  c50_mxArrayOutData = NULL;
  c50_u = *(int32_T *)c50_inData;
  c50_y = NULL;
  sf_mex_assign(&c50_y, sf_mex_create("y", &c50_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c50_mxArrayOutData, c50_y, false);
  return c50_mxArrayOutData;
}

static int32_T c50_emlrt_marshallIn(SFc50_ethercatInstanceStruct *chartInstance,
  const mxArray *c50_b_sfEvent, const char_T *c50_identifier)
{
  int32_T c50_y;
  emlrtMsgIdentifier c50_thisId;
  c50_thisId.fIdentifier = c50_identifier;
  c50_thisId.fParent = NULL;
  c50_y = c50_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c50_b_sfEvent),
    &c50_thisId);
  sf_mex_destroy(&c50_b_sfEvent);
  return c50_y;
}

static int32_T c50_b_emlrt_marshallIn(SFc50_ethercatInstanceStruct
  *chartInstance, const mxArray *c50_u, const emlrtMsgIdentifier *c50_parentId)
{
  int32_T c50_y;
  int32_T c50_i0;
  (void)chartInstance;
  sf_mex_import(c50_parentId, sf_mex_dup(c50_u), &c50_i0, 1, 6, 0U, 0, 0U, 0);
  c50_y = c50_i0;
  sf_mex_destroy(&c50_u);
  return c50_y;
}

static void c50_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c50_mxArrayInData, const char_T *c50_varName, void *c50_outData)
{
  const mxArray *c50_b_sfEvent;
  const char_T *c50_identifier;
  emlrtMsgIdentifier c50_thisId;
  int32_T c50_y;
  SFc50_ethercatInstanceStruct *chartInstance;
  chartInstance = (SFc50_ethercatInstanceStruct *)chartInstanceVoid;
  c50_b_sfEvent = sf_mex_dup(c50_mxArrayInData);
  c50_identifier = c50_varName;
  c50_thisId.fIdentifier = c50_identifier;
  c50_thisId.fParent = NULL;
  c50_y = c50_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c50_b_sfEvent),
    &c50_thisId);
  sf_mex_destroy(&c50_b_sfEvent);
  *(int32_T *)c50_outData = c50_y;
  sf_mex_destroy(&c50_mxArrayInData);
}

static const mxArray *c50_b_sf_marshallOut(void *chartInstanceVoid, void
  *c50_inData)
{
  const mxArray *c50_mxArrayOutData = NULL;
  real_T c50_u;
  const mxArray *c50_y = NULL;
  SFc50_ethercatInstanceStruct *chartInstance;
  chartInstance = (SFc50_ethercatInstanceStruct *)chartInstanceVoid;
  c50_mxArrayOutData = NULL;
  c50_u = *(real_T *)c50_inData;
  c50_y = NULL;
  sf_mex_assign(&c50_y, sf_mex_create("y", &c50_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c50_mxArrayOutData, c50_y, false);
  return c50_mxArrayOutData;
}

static uint8_T c50_c_emlrt_marshallIn(SFc50_ethercatInstanceStruct
  *chartInstance, const mxArray *c50_b_is_active_c50_ethercat, const char_T
  *c50_identifier)
{
  uint8_T c50_y;
  emlrtMsgIdentifier c50_thisId;
  c50_thisId.fIdentifier = c50_identifier;
  c50_thisId.fParent = NULL;
  c50_y = c50_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c50_b_is_active_c50_ethercat), &c50_thisId);
  sf_mex_destroy(&c50_b_is_active_c50_ethercat);
  return c50_y;
}

static uint8_T c50_d_emlrt_marshallIn(SFc50_ethercatInstanceStruct
  *chartInstance, const mxArray *c50_u, const emlrtMsgIdentifier *c50_parentId)
{
  uint8_T c50_y;
  uint8_T c50_u0;
  (void)chartInstance;
  sf_mex_import(c50_parentId, sf_mex_dup(c50_u), &c50_u0, 1, 3, 0U, 0, 0U, 0);
  c50_y = c50_u0;
  sf_mex_destroy(&c50_u);
  return c50_y;
}

static const mxArray *c50_e_emlrt_marshallIn(SFc50_ethercatInstanceStruct
  *chartInstance, const mxArray *c50_b_setSimStateSideEffectsInfo, const char_T *
  c50_identifier)
{
  const mxArray *c50_y = NULL;
  emlrtMsgIdentifier c50_thisId;
  c50_y = NULL;
  c50_thisId.fIdentifier = c50_identifier;
  c50_thisId.fParent = NULL;
  sf_mex_assign(&c50_y, c50_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c50_b_setSimStateSideEffectsInfo), &c50_thisId), false);
  sf_mex_destroy(&c50_b_setSimStateSideEffectsInfo);
  return c50_y;
}

static const mxArray *c50_f_emlrt_marshallIn(SFc50_ethercatInstanceStruct
  *chartInstance, const mxArray *c50_u, const emlrtMsgIdentifier *c50_parentId)
{
  const mxArray *c50_y = NULL;
  (void)chartInstance;
  (void)c50_parentId;
  c50_y = NULL;
  sf_mex_assign(&c50_y, sf_mex_duplicatearraysafe(&c50_u), false);
  sf_mex_destroy(&c50_u);
  return c50_y;
}

static int32_T c50__s32_d_(SFc50_ethercatInstanceStruct *chartInstance, real_T
  c50_b)
{
  int32_T c50_a;
  c50_a = (int32_T)c50_b;
  if ((real_T)c50_a != (c50_b < 0.0 ? muDoubleScalarCeil(c50_b) :
                        muDoubleScalarFloor(c50_b))) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, 1U, 0U, *chartInstance->c50_sfEvent,
      false);
  }

  return c50_a;
}

static void init_dsm_address_info(SFc50_ethercatInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc50_ethercatInstanceStruct *chartInstance)
{
  chartInstance->c50_sfEvent = (int32_T *)ssGetDWork_wrapper(chartInstance->S, 0);
  chartInstance->c50_isStable = (boolean_T *)ssGetDWork_wrapper(chartInstance->S,
    1);
  chartInstance->c50_is_active_c50_ethercat = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 2);
  chartInstance->c50_is_c50_ethercat = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 3);
  chartInstance->c50_triggerWriting = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c50_readState = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c50_enable = (int32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c50_complete = (int32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c50_lastTriggerValue = (int32_T *)ssGetDWork_wrapper
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
void sf_c50_ethercat_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1172987961U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2113447571U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1871266399U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(686711380U);
}

mxArray* sf_c50_ethercat_get_post_codegen_info(void);
mxArray *sf_c50_ethercat_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("vnb6NSEzdVRfosFviFupGD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
      pr[0] = (double)(1);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c50_ethercat_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c50_ethercat_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c50_ethercat_jit_fallback_info(void)
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

mxArray *sf_c50_ethercat_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c50_ethercat_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c50_ethercat(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[159],T\"complete\",},{M[1],M[135],T\"enable\",},{M[3],M[165],T\"lastTriggerValue\",},{M[8],M[0],T\"is_active_c50_ethercat\",},{M[9],M[0],T\"is_c50_ethercat\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c50_ethercat_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc50_ethercatInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc50_ethercatInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ethercatMachineNumber_,
           50,
           3,
           6,
           0,
           5,
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
          _SFD_SET_DATA_PROPS(0,0,0,0,"lastTriggerValue");
          _SFD_SET_DATA_PROPS(1,1,1,0,"triggerWriting");
          _SFD_SET_DATA_PROPS(2,1,1,0,"readState");
          _SFD_SET_DATA_PROPS(3,2,0,1,"enable");
          _SFD_SET_DATA_PROPS(4,2,0,1,"complete");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_CH_SUBSTATE_COUNT(3);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_CH_SUBSTATE_INDEX(2,2);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
        }

        _SFD_CV_INIT_CHART(3,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 35 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 35 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 1, 1, 1, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 15 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(3,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 15 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(3,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 15 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(5,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 15 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(5,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 15 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 15 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c50_sf_marshallOut,(MexInFcnForType)c50_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c50_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c50_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c50_sf_marshallOut,(MexInFcnForType)c50_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c50_sf_marshallOut,(MexInFcnForType)c50_sf_marshallIn);
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
    SFc50_ethercatInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc50_ethercatInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c50_triggerWriting);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c50_readState);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c50_enable);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c50_complete);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c50_lastTriggerValue);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "skGKDaML8sbRfNKqGRjmsdE";
}

static void sf_check_dwork_consistency(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    const uint32_T *sfunDWorkChecksum = sf_get_sfun_dwork_checksum();
    mxArray *infoStruct = load_ethercat_optimization_info();
    mxArray* mxRTWDWorkChecksum = sf_get_dwork_info_from_mat_file(S,
      sf_get_instance_specialization(), infoStruct, 50, "dworkChecksum");
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

static void sf_opaque_initialize_c50_ethercat(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc50_ethercatInstanceStruct*) chartInstanceVar
    )->S);
  chart_debug_initialization(((SFc50_ethercatInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c50_ethercat((SFc50_ethercatInstanceStruct*)
    chartInstanceVar);
  initialize_c50_ethercat((SFc50_ethercatInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c50_ethercat(void *chartInstanceVar)
{
  enable_c50_ethercat((SFc50_ethercatInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c50_ethercat(void *chartInstanceVar)
{
  disable_c50_ethercat((SFc50_ethercatInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c50_ethercat(void *chartInstanceVar)
{
  sf_gateway_c50_ethercat((SFc50_ethercatInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c50_ethercat(void *chartInstanceVar)
{
  ext_mode_exec_c50_ethercat((SFc50_ethercatInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c50_ethercat(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c50_ethercat((SFc50_ethercatInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c50_ethercat(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c50_ethercat((SFc50_ethercatInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c50_ethercat(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc50_ethercatInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ethercat_optimization_info();
    }

    finalize_c50_ethercat((SFc50_ethercatInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc50_ethercat((SFc50_ethercatInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c50_ethercat(SimStruct *S)
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
    initialize_params_c50_ethercat((SFc50_ethercatInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

mxArray *sf_c50_ethercat_get_testpoint_info(void)
{
  return NULL;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x5'type','isSigned','wordLength','bias','slope','exponent','isScaledDouble','isComplex','size'{{T\"int32\",,,,,,,M[0],M[]},{T\"boolean\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"int32\",,,,,,,M[0],M[]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 5, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 3323263640U, 2624476869U, 3153540571U,
    4146977340U };

  return checksum;
}

static void mdlSetWorkWidths_c50_ethercat(SimStruct *S)
{
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ethercat_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      50);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,50,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,50);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,50,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,50,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,50);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3462266944U));
  ssSetChecksum1(S,(3758302583U));
  ssSetChecksum2(S,(3601672848U));
  ssSetChecksum3(S,(1814380937U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c50_ethercat(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c50_ethercat(SimStruct *S)
{
  SFc50_ethercatInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc50_ethercatInstanceStruct *)utMalloc(sizeof
    (SFc50_ethercatInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc50_ethercatInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c50_ethercat;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c50_ethercat;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c50_ethercat;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c50_ethercat;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c50_ethercat;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c50_ethercat;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c50_ethercat;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c50_ethercat;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c50_ethercat;
  chartInstance->chartInfo.mdlStart = mdlStart_c50_ethercat;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c50_ethercat;
  chartInstance->chartInfo.extModeExec = sf_opaque_ext_mode_exec_c50_ethercat;
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

void c50_ethercat_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c50_ethercat(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c50_ethercat(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c50_ethercat(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c50_ethercat_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
