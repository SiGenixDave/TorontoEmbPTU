#define   __fltinfo__

/* header */
#define   FAULTPACKET1        UINT_16             faultid;FAULTPACKET2        
#define   FAULTPACKET2        UINT_16             loggerid;FAULTPACKET3        
#define   FAULTPACKET3        UINT_32             index;FAULTPACKET4        
#define   FAULTPACKET4        UINT_8              TimeStamp[6];FAULTPACKET5        
#define   FAULTPACKET5        UINT_16             DataLogNumber;FAULTPACKET6        
#define   FAULTPACKET6        INT_32              ptuBatteryVoltage;FAULTPACKET7        
#define   FAULTPACKET7        UINT_16             ptuVehicleId;FAULTPACKET8        
#define   FAULTPACKET8        UINT_32             ptuCarSpeed;FAULTPACKET9        
#define   FAULTPACKET9        UINT_16             ptuDcu1State;FAULTPACKET10       
#define   FAULTPACKET10       INT_32              ptuTeDelDcu1;FAULTPACKET11       
#define   FAULTPACKET11       INT_32              ptuTeReqDcu1;FAULTPACKET12       
#define   FAULTPACKET12       UINT_16             ptuDcu2State;FAULTPACKET13       
#define   FAULTPACKET13       INT_32              ptuTeDelDcu2;FAULTPACKET14       
#define   FAULTPACKET14       INT_32              ptuTeReqDcu2;FAULTPACKET15       
#define   FAULTPACKET15       UINT_16             ptuEncValPrim;FAULTPACKET16       
#define   FAULTPACKET16       UINT_16             ptuEncValSec;FAULTPACKET17       
#define   FAULTPACKET17       INT_32              ptuFbPres1;FAULTPACKET18       
#define   FAULTPACKET18       UINT_16             ptuTrk1Mode;FAULTPACKET19       
#define   FAULTPACKET19       INT_32              ptuFbPres2;FAULTPACKET20       
#define   FAULTPACKET20       UINT_16             ptuTrk2Mode;FAULTPACKET21       
#define   FAULTPACKET21       UINT_32             ptuOdometer;FAULTPACKET22       
#define   FAULTPACKET22       UINT_16             ptuVcuId;FAULTPACKET23       
#define   FAULTPACKET23       UINT_16             ptuMasterSlave;FAULTPACKET24       
#define   FAULTPACKET24       INT_32              ptuLineVolt1;FAULTPACKET25       
#define   FAULTPACKET25       INT_32              ptuLineVolt2;
#define   FAULTPACKETPROLOG   FAULTPACKET1

#define   Propulsion          0


/* task */
#define   PtuFaultTest        0

#define   TESTIO_ID           0
struct    fltTestStr          {
          FAULTPACKETPROLOG
          INT_16              testvarI161;
          UINT_16             testvarU161;
          UINT_16             testvarU162;
          UINT_32             testvarU32;
} __attribute__ ((packed));


/* task */
#define   Velocity            1

#define   E_TACH_FAILED_ID    0
struct    fltTachFailedStr    {
          FAULTPACKETPROLOG
          UINT_16             tachID;
          UINT_16             tachFailureCause;
} __attribute__ ((packed));

/* #define   E_WHEEL_DIAM_BAD_ID 3 */
struct    fltWheelDiamDiffStr {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          UINT_16             wdiffAxleWheelDiam;
          UINT_32             otherWheelDiam;
} __attribute__ ((packed));


/* task */
#define   Direction           2

#define   DIR_CHANGE_ID       0
struct    flt_dirchange_str   {
          FAULTPACKETPROLOG
          UINT_16             directionRequest1;
          UINT_16             directionRequest2;
} __attribute__ ((packed));

#define   DIR_INVALID_ID      1
struct    flt_dirinvalid_str  {
          FAULTPACKETPROLOG
          UINT_16             directionRequest1;
          UINT_16             directionRequest2;
} __attribute__ ((packed));

#define   DIR_MISMATCH_ID     2
struct    flt_mismatch_str    {
          FAULTPACKETPROLOG
          UINT_16             directionCommand;
          UINT_16             directionFeedback;
          UINT_16             dcuId;
          INT_32              truckVelocity;
} __attribute__ ((packed));


/* task */
#define   Protection          3

#define   E_COLL_SHOE_FAULT   0
struct    flt_Blown_Collect_Fuse_Str {
          FAULTPACKETPROLOG
          INT_16              lineVoltage1;
          INT_16              lineVoltage2;
          UINT_32             ITSPosition;
} __attribute__ ((packed));

#define   PROT_BV_ID          1
struct    fltBattVoltStr      {
          FAULTPACKETPROLOG
          INT_32              batteryVoltage;
} __attribute__ ((packed));

#define   E_ER_MISMATCH       2
struct    fltErMismatchStr    {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          UINT_16             opModeReq;
          UINT_16             emergRelayStatus;
} __attribute__ ((packed));

#define   E_PROP_INP_CIRCUIT_FAILURE 3
struct    fltHighVoltInMonStr {
          FAULTPACKETPROLOG
          INT_16              lineVoltage1;
          INT_16              lineVoltage2;
          UINT_16             railGapStat;
          UINT_32             ITSPosition;
          INT_32              CSDistanceTraveled;
          UINT_16             TruckID;
} __attribute__ ((packed));

#define   PROT_HVB_GND_FLT_ID 4
struct    fltHvbGndFltStr     {
          FAULTPACKETPROLOG
          INT_16              lineCurrent;
          INT_16              returnCurrent;
          UINT_16             invID;
          INT_16              hvbCount;
} __attribute__ ((packed));

#define   E_FILTER_CAP_CHARGE_FAULT 5
struct    fltInvFiltCapChargeFaultStr {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
} __attribute__ ((packed));

#define   E_ITSSWITCH_FAULT   6
struct    fltItsLVFaultStr    {
          FAULTPACKETPROLOG
          UINT_32             ITSPosition;
          UINT_16             RunPos;
          UINT_16             TestPos;
          INT_16              lineVoltage;
} __attribute__ ((packed));

#define   E_LINE_RET_OFFSET_HIGH 7
struct    fltLineReturnCurrOffsetStr {
          FAULTPACKETPROLOG
          INT_16              lineCurrent;
          INT_16              returnCurrent;
          UINT_16             offsetFailed;
          INT_32              offsetCorrValue;
} __attribute__ ((packed));

#define   E_LINK_OVERCURRENT_FAULT 8
struct    fltLinkOverCurrentFaultStr {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          INT_32              linkCurrent;
} __attribute__ ((packed));

#define   E_FB_UPSI_EB_LLV    9
struct    fltLlvEbStr         {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
} __attribute__ ((packed));

#define   E_LOAD_WEIGH_FAULT  10
struct    fltLoadWeighStr     {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          INT_16              LoadWeighTruck1;
          INT_16              LoadWeighTruck2;
} __attribute__ ((packed));

#define   PROT_PCU_LOCKOUT_ID 11
struct    fltLockoutStr       {
          FAULTPACKETPROLOG
          UINT_16             lockoutCause;
} __attribute__ ((packed));

#define   E_MOTOR_OVERTEMP    12
struct    fltMotorOverTempStr {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          INT_32              motorTemp;
} __attribute__ ((packed));

#define   PROT_OLR_RESET_ID   13
struct    fltOlrResetFltStr   {
          FAULTPACKETPROLOG
          UINT_16             invID;
          INT_16              olrStatus;
          UINT_32             olrTripCount;
          UINT_16             olrResetCount;
} __attribute__ ((packed));

#define   PROT_OLR_TRIP_ID    14
struct    fltOlrTripStr       {
          FAULTPACKETPROLOG
          UINT_16             invID;
          INT_16              olrStatus;
          UINT_32             olrTripCount;
          INT_16              lineCurrent;
} __attribute__ ((packed));

#define   PROT_OVERCURR_ID    15
struct    fltOvercurrStr      {
          FAULTPACKETPROLOG
          INT_16              lineCurrent;
          UINT_16             invID;
          UINT_16             overcurrCount;
} __attribute__ ((packed));

#define   E_OVERSPEED_PENALTY_FAULT_ID 16
struct    fltOverspeedEventStr {
          FAULTPACKETPROLOG
          UINT_16             scsStatus;
          UINT_32             carSpeed;
          UINT_16             porStatus;
} __attribute__ ((packed));

#define   E_POR_MISMATCH_EVENT_ID 17
struct    fltPorMismatchEventStr {
          FAULTPACKETPROLOG
          UINT_16             scsStatus;
          UINT_32             penaltyBrakeRequest;
          UINT_16             porStatus;
} __attribute__ ((packed));

#define   E_POWER_BAL_SUP_FAULT 18
#define   E_POWER_BAL_SUP_FAULT_LOCKOUT 19
struct    fltPowerBalanceSupFaultStr {
          FAULTPACKETPROLOG
          UINT_16             ProtDcuID;
          UINT_32             CalcMotorPower;
          UINT_32             brakeChopperPower;
          UINT_32             dcLinkInputPower;
} __attribute__ ((packed));

#define   PROT_POWER_UP_FAIL  20
struct    fltPowerUpFailStr   {
          FAULTPACKETPROLOG
          UINT_16             powUpFail;
} __attribute__ ((packed));

#define   E_STALL_DET_EVENT   21
struct    fltStallDetStr      {
          FAULTPACKETPROLOG
          INT_16              teDelDcu1;
          INT_16              teDelDcu2;
          UINT_16             pbStatus;
          INT_32              resPres;
          INT_32              fbCommand1;
          INT_32              fbCommand2;
} __attribute__ ((packed));

#define   E_TC1420_AMBIENTAIR_TEMP_ALARM 22
struct    fltTC1420AmbientAlarmStr {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          INT_16              ambientAirTemp;
} __attribute__ ((packed));

#define   E_TC1420_GROUNDFAULT 23
#define   E_TC1420_INPUTGROUND_LOCKOUT 24
struct    fltTC1420GroundFaultStr {
          FAULTPACKETPROLOG
          UINT_16             ProtDcuID;
          INT_32              linkCurrent;
} __attribute__ ((packed));

#define   E_TC1420_HEATSINK_ALARM 25
struct    fltTC1420HeatsinkTempAlarmStr {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          INT_16              heatSinkTemp;
} __attribute__ ((packed));


/* task */
#define   TcFault             4

#define   PCN_FAILURE_ID      0
struct    fltIpPcnFailureStr  {
          FAULTPACKETPROLOG
          UINT_16             pcnMcId;
          UINT_16             pcnVersionStatus;
          UINT_16             pcnComStatus;
} __attribute__ ((packed));

#define   TIMS_COM_FAILED_ID  1
#define   TIMS_COM_OK_ID      2
struct    fltIpTimsFailureStr {
          FAULTPACKETPROLOG
          UINT_16             timsComStatus;
} __attribute__ ((packed));


/* task */
#define   MasterSlave         5

#define   E_VCU_WATCHDOG_FAILURE 0
struct    fltMasterSlaveFailureStr {
          FAULTPACKETPROLOG
          UINT_16             failedVCUMVB;
          UINT_16             goodVCUMVB;
          UINT_16             localToken;
          UINT_16             msSwapReason;
} __attribute__ ((packed));

#define   E_VCU_MVBADDRESS_FAILURE 1
struct    fltMsAddressFaultStr {
          FAULTPACKETPROLOG
          UINT_16             goodVCUMVB;
          UINT_16             ipAddNum1;
          UINT_16             ipAddNum2;
          UINT_16             ipAddNum3;
          UINT_16             ipAddNum4;
} __attribute__ ((packed));


/* task */
#define   FrictionBrake       6

#define   E_FB_APPLIED_POWER_FAULT 0
struct    fltFbAppliedPowerStr {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          UINT_16             mode;
          INT_32              fbPres1;
          INT_32              fbPres2;
} __attribute__ ((packed));

#define   E_FB_BVD_FAULT      1
struct    fltFbBvdStr         {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          UINT_16             k1Command;
          UINT_16             k1Feedback;
          UINT_16             k2Command;
          UINT_16             k2Feedback;
          UINT_16             k3Command;
          UINT_16             k3Feedback;
} __attribute__ ((packed));

#define   E_FB_INVALID_FAULT  2
struct    fltFbInvalidStr     {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          INT_32              fbCom1;
          INT_32              fbCom2;
          INT_32              fbPres1;
          INT_32              fbPres2;
} __attribute__ ((packed));

#define   E_FB_LLV_FAULT      3
struct    fltFbLlvStr         {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          INT_32              fbPres1;
          INT_32              fbPres2;
          INT_32              expectedFbPres1;
          INT_32              expectedFbPres2;
          INT_32              loadWeight1;
          INT_32              loadWeight2;
          UINT_16             loadWeightStatus1;
          UINT_16             loadWeightStatus2;
} __attribute__ ((packed));

#define   E_FB_MARP_FAULT     4
struct    fltFbMarpStr        {
          FAULTPACKETPROLOG
          INT_32              resPres;
} __attribute__ ((packed));

#define   E_FB_RANGE_FAULT    5
struct    fltFbRangeStr       {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          INT_32              fbPres1;
          INT_32              fbPres2;
} __attribute__ ((packed));

#define   E_PB_APPLIED_FAULT  6
struct    fltPbAppliedStr     {
          FAULTPACKETPROLOG
          UINT_16             pbCommand;
          UINT_16             pbStatus;
          UINT_16             pbCutoutStatus;
          INT_32              fbPres1;
          INT_32              fbPres2;
} __attribute__ ((packed));

#define   E_PB_CUTOUT_FAULT   7
struct    fltPbCutoutStr      {
          FAULTPACKETPROLOG
          UINT_16             pbStatus;
          UINT_16             pbCutoutStatus;
} __attribute__ ((packed));

#define   E_PB_MISMATCH_FAULT 8
struct    fltPbMismatchStr    {
          FAULTPACKETPROLOG
          UINT_16             pbCommand;
          UINT_16             pbStatus;
} __attribute__ ((packed));



/* task */
#define   ZeroVelocity        8

#define   E_ZEROVEL_CH1_MISMATCH 0
#define   E_ZEROVEL_CH2_MISMATCH 1
struct    flt_zeroVelocity_str {
          FAULTPACKETPROLOG
          UINT_16             car_state;
          UINT_16             ch1_command;
          UINT_16             ch1_status;
          UINT_16             ch2_status;
} __attribute__ ((packed));













#define   Engineering         1


/* task */
/* #define   PtuFaultTest        0 */

#define   LOG_SIZE_EVENT      0
struct    LOGSIZESTR          {
          FAULTPACKETPROLOG
          UINT_32             logSize1;
          UINT_32             logSize2;
          UINT_32             logSize3;
          UINT_32             logSize4;
          UINT_32             logSize5;
          UINT_32             logSize6;
          UINT_32             logSize7;
          UINT_32             logSize8;
          UINT_32             logSize9;
          UINT_32             logSize10;
          UINT_32             logSize11;
} __attribute__ ((packed));


/* task */
/* #define   Velocity            1 */

#define   E_WHEEL_DIAM_LOW_ID 0
struct    fltWheelDiamBadStr  {
          FAULTPACKETPROLOG
          UINT_32             wdAxleId;
          INT_32              wdAxleRPM;
          UINT_32             wdAxleOpStat;
          INT_32              tachWheelDiam;
          UINT_32             otherWheelDiam;
          UINT_32             refWheelDiam;
          INT_32              refWheelRPM;
} __attribute__ ((packed));

#define   E_WHEEL_DIAM_DIFF_CHECK 1
struct    fltWheelDiamCalcdiffCheckStr {
          FAULTPACKETPROLOG
          UINT_32             wdAxleId;
          INT_32              wdCarState;
          INT_32              calcWheelDiam;
          UINT_32             prevCalcWheelDiam;
          UINT_32             refWheelDiam;
          INT_32              refWheelRPM;
          INT_32              wdAxleRPM;
} __attribute__ ((packed));

#define   E_REF_WHEEL_CHANGE_ID 2
struct    fltWheelDiamChgStr  {
          FAULTPACKETPROLOG
          UINT_32             wdBbram;
          INT_32              wdChgReason;
          UINT_32             wdAxle4;
          UINT_32             wdReqChg;
} __attribute__ ((packed));

#define   E_WHEEL_DIAM_BAD_ID 3
/* struct    fltWheelDiamDiffStr {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          UINT_16             wdiffAxleWheelDiam;
          UINT_32             otherWheelDiam;
}; */


/* task */
/* #define   Direction           2 */

#define   DIR_ROLLBACK_ID     0
struct    flt_rollback_str    {
          FAULTPACKETPROLOG
          UINT_16             directionCommand1;
          UINT_16             directionCommand2;
          INT_32              carVelocity;
          INT_32              operatorRequest;
} __attribute__ ((packed));


/* task */
/* #define   Protection          3 */

#define   PROT_ROLLBACK_ID    0
struct    flt_rollback_prot_str {
          FAULTPACKETPROLOG
          INT_32              rbVel;
          UINT_16             rbScs;
          UINT_16             mileage;
} __attribute__ ((packed));

#define   E_BRAKE_RATE_FAULT  1
struct    fltBrakeRateStr     {
          FAULTPACKETPROLOG
          UINT_16             modeReq;
          INT_32              carRate;
          INT_32              operatorRequest;
          UINT_16             slideIndication;
} __attribute__ ((packed));

#define   PROT_CAR_ID_ID      2
struct    fltCarIdStr         {
          FAULTPACKETPROLOG
          UINT_16             carInput1;
          UINT_16             carInput2;
} __attribute__ ((packed));

#define   E_CAR_STATS_GENERAL 3
struct    fltCarStatisticsGeneralStr {
          FAULTPACKETPROLOG
          UINT_32             CSTimeInEmerg;
          UINT_32             CSTimeInMotion;
          UINT_32             CSAvgLoadWeight;
          UINT_32             CSTimeVcuAlive;
          INT_32              CSDistanceTraveled;
          INT_32              CSAverageSpeed;
          INT_32              CSMasterSlaveSwap;
          UINT_32             CSTimeSinceLast;
} __attribute__ ((packed));

#define   E_CAR_STAT_TRUCK_ENERGY 4
struct    fltCarStatsTruckEnergyStr {
          FAULTPACKETPROLOG
          UINT_32             CSEnergyConsumedTK1;
          UINT_32             CSEnergyRegenTK1;
          INT_32              CSEnergyNonRegenTk1;
          INT_32              CSEnergyFrictionBrakeTK1;
          UINT_32             CSEnergyConsumedTK2;
          UINT_32             CSEnergyRegenTk2;
          INT_32              CSEnergyNonRegenTk2;
          INT_32              CSEnergyFrictionBrakeTk2;
} __attribute__ ((packed));

#define   E_CAR_STAT_TK_INV_STAT 5
struct    fltCarStatTruckInverterStatStr {
          FAULTPACKETPROLOG
          UINT_32             CSTimeInvDelPowTk1;
          INT_32              CSTimeInvDelNonRegBRKTk1;
          UINT_32             CSTimeInvDelRegBrkTk1;
          UINT_32             CSTimeInvDelPowTk2;
          INT_32              CSTimeInvDelNonRegBRKTk2;
          UINT_32             CSTimeInvDelRegBrkTk2;
} __attribute__ ((packed));

#define   E_INVFAULT_APP      6
struct    fltDcuDiagAppSpecStr {
          FAULTPACKETPROLOG
          UINT_16             ProtDcuID;
          UINT_32             DiagWord13;
} __attribute__ ((packed));

#define   E_INVFAULT_ROTARY   7
struct    fltDcuDiagRotOnlyStr {
          FAULTPACKETPROLOG
          UINT_16             ProtDcuID;
          UINT_32             DiagWord9;
          UINT_32             DiagWord10;
} __attribute__ ((packed));

#define   E_INVERTERFAULTS_COMMON 8
struct    fltDcuDiagWordCommonStr {
          FAULTPACKETPROLOG
          UINT_16             ProtDcuID;
          UINT_32             DiagWord1;
          INT_32              DiagWord2;
          UINT_32             DiagWord3;
          INT_32              DiagWord4;
          UINT_32             DiagWord5;
          INT_32              DiagWord6;
} __attribute__ ((packed));

#define   E_INVERTER_ISOLATION 9
struct    fltDcuReasonforIsolationStr {
          FAULTPACKETPROLOG
          UINT_16             ProtDcuID;
          UINT_32             DCUReasonforIsolation;
} __attribute__ ((packed));

#define   E_EMERG_BRAKE_CMD   10
struct    fltEmergRelayStatusEventStr {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          UINT_16             emergRelayStatus;
} __attribute__ ((packed));

#define   E_IO_MODULE_FAULT   11
struct    fltIOModuleStr      {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          UINT_16             IOModuleID;
          UINT_32             IOModFailReason;
} __attribute__ ((packed));

#define   PROT_LOW_LV_ID      12
struct    fltLowLvStr         {
          FAULTPACKETPROLOG
          INT_16              lineVoltage;
          UINT_16             invID;
} __attribute__ ((packed));

#define   E_MVB_COMM_FAULT    13
struct    fltMvbCommFailureStr {
          FAULTPACKETPROLOG
          UINT_16             ProtDcuID;
          UINT_16             TelegramID;
} __attribute__ ((packed));

#define   E_OVERSPEED_ALARM_EVENT_ID 14
#define   E_OVERSPEED_PENALTY_REC_ID 15
/* struct    fltOverspeedEventStr {
          FAULTPACKETPROLOG
          UINT_16             scsStatus;
          UINT_32             carSpeed;
          UINT_16             porStatus;
}; */

#define   E_PROP_EMERG_SHUTDOWN_EVENT 16
struct    fltPropEmergShutdownStr {
          FAULTPACKETPROLOG
          UINT_16             propEmergShutdownTLStatus;
} __attribute__ ((packed));

#define   E_PROP_ISO_CMD_EVENT 17
struct    fltPropIsolationCmdEventStr {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          UINT_16             PropIsoCmdStatus;
} __attribute__ ((packed));


/* task */
/* #define   TcFault             4 */

#define   ATO_FSB_EVENT_ID    0
struct    flt_ATOFsb_str      {
          FAULTPACKETPROLOG
          UINT_16             controllerID;
          UINT_16             ZVRDTrainline;
          UINT_32             TimsFSBReq;
} __attribute__ ((packed));

#define   MC_INVALID_ID       1
#define   ATO_INVALID_ID      2
struct    flt_mc_invalid_str  {
          FAULTPACKETPROLOG
          UINT_16             masterControllerId;
          UINT_16             mcEncoderValue;
          UINT_16             mcSwitchValue;
} __attribute__ ((packed));


/* task */
/* #define   MasterSlave         5 */

#define   E_MASTER_SLAVE_SWAP_REASON 0
/* struct    fltMasterSlaveFailureStr {
          FAULTPACKETPROLOG
          UINT_16             failedVCUMVB;
          UINT_16             goodVCUMVB;
          UINT_16             localToken;
          UINT_16             msSwapReason;
}; */


/* task */
/* #define   FrictionBrake       6 */

#define   BVD1_SU_FAULT_ID    0
#define   BVD2_SU_FAULT_ID    1
struct    flt_st_bvd_str      {
          FAULTPACKETPROLOG
          UINT_16             failedRelay;
} __attribute__ ((packed));

#define   E_FB_CUTOUT_FAULT   2
struct    fltFbCutoutStr      {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          UINT_16             fbCutout;
          UINT_16             srvcCutout1;
          UINT_16             srvcCutout2;
          INT_32              fbPres1;
          INT_32              fbPres2;
} __attribute__ ((packed));


/* task */
#define   SpinSlide           7

#define   E_SLIDE_DETECT_ASYNC 0
#define   E_SLIDE_DETECT_SYNC 1
#define   E_SPIN_DETECT_SYNC  2
#define   E_SPIN_DETECT_ASYNC 3
struct    flt_ss_async_sync_str {
          FAULTPACKETPROLOG
          INT_32              carRate;
          UINT_32             axleSpeed1;
          INT_32              axleRate1;
          UINT_32             axleSpeed2;
          INT_32              axleRate2;
          UINT_32             AxleID;
          INT_32              rateReqMotion;
          UINT_16             TruckID;
} __attribute__ ((packed));

#define   E_SLIDE_TIMEOUT     4
#define   E_SPIN_TIMEOUT      5
struct    flt_ss_timeout_str  {
          FAULTPACKETPROLOG
          UINT_16             TruckID;
          INT_32              carRate;
          UINT_32             carSpeed;
          UINT_32             axleSpeed1;
          INT_32              axleRate1;
          UINT_32             axleSpeed2;
          INT_32              axleRate2;
} __attribute__ ((packed));

#define   E_SPIN_DETECT_VELOCITY 6
#define   E_SLIDE_DETECT_VELOCITY 7
struct    flt_ss_velocity_str {
          FAULTPACKETPROLOG
          INT_32              carRate;
          UINT_32             axleSpeed1;
          INT_32              axleRate1;
          UINT_32             axleSpeed2;
          INT_32              axleRate2;
          UINT_32             AxleID;
          INT_32              rateReqMotion;
          UINT_16             TruckID;
} __attribute__ ((packed));



/* task */
#define   SelfTest            9

#define   ST_NOT_ALLOWED_FLT  0
struct    fltStNotAllowedStr  {
          FAULTPACKETPROLOG
          UINT_16             maintAllowed;
} __attribute__ ((packed));











