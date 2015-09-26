/*********************************************************************
	Rhapsody	: 7.4 
	Login		: sstrane
	Component	: VCUC 
	Configuration 	: Target
	Model Element	: VCU
//!	Generated Date	: Wed, 19, Aug 2015  
	File Path	: RhapVCUC/Target/ProjectPkg/PtuEnumPkg/VCU/VCU.h
*********************************************************************/


#ifndef ProjectPkg_PtuEnumPkg_VCU_VCU_H 

#define ProjectPkg_PtuEnumPkg_VCU_VCU_H 


//## package ProjectPkg::PtuEnumPkg::VCU 

//----------------------------------------------------------------------------
// ProjectPkg/PtuEnumPkg/VCU/VCU.h                                                                  
//----------------------------------------------------------------------------


//#[ ignore 
// This is the Enumeration Type for INT_16 data-type
// Watch Variables. The element "MaxI16WVarId",
// gives the size of INT_16 Watch Variables, which should
// be the last in the list.
enum i16WVarId
{
  Debug16i1,
  Debug16i2,
  Debug16i3,
  Debug16i4,
  Debug16i5,
  Debug16i6,
  
  // Train Control
  TcMaxBrkRate,
  TcMinBrkRate,
  TcMinPwrRate,
  TcMaxPwrRate,
 
  
  MaxI16WVarId // This should be the last element
};



// This is the Enumeration Type for INT_32 data-type
// Watch Variables. The element "MaxI32WVarId",
// gives the size of INT_32 Watch Variables, which should
// be the last in the list.
enum i32WVarId
{
	Debug32i1,
	Debug32i2,
	Debug32i3,
	Debug32i4,
	Debug32i5,
	Debug32i6,
	
	cbramSystemJRL,  
	
	//AX 320 Inputs
	AX320_STATUS,
	AX320_STTBWORD,
	AX320_BATTVOLT,
	AX320_FBPRESS,
	AX320_RETCURRENT,
	AX320_LINECURRENT,
	AX320_LINEVOLTAGE,
	
	//AX 370 Inputs 
	AX370_STATUS,
	AX370_STTBWORD,
	AX370_BATTVOLT,
	AX370_FBPRESS,
	AX370_RETCURRENT,
	AX370_LINECURRENT,
	AX370_LINEVOLTAGE,
	
	//AX 520 Inputs 
	AX520_STATUS,
	AX520_STTBWORD,
	AX520_BATTVOLT,
	AX520_MRPRESS,
	AX520_LWPRESS2,
	AX520_LWPRESS1,
	
    
	//DI 340 Inputs 
	DI340INPUTWORD,
	DI340STSWORD,
	DI340STTBWORD, 
	DI340ITSPOSITION,
	DI340CARID,
	DI340FBCUTOUT,
	DI340OVRSPDRELAY,
	DI340LCBC1,
	DI340LCBC2, 
	DI340ESHUTDOWN, 
	DI340PBCUTOUT,
	DI340ATOSPARE,
	DI340ATOTRNLINE,
	DI340ZEROVELCH1,
	DI340ZEROVELCH2,
	DI340SSTRNLINE,
	
	//DX 330 Inputs 
	DX330INPUTWORD,
	DX330STTBWORD,
	DX330STSWORD,
	DX330BVDFDBKSTAT1,
	DX330K4STAT,
    DX330ERSTATUS1,
	DX330DIRTL1,
	DX330OLRSTAT1,
	DX330PBSTAT,
	
	//DX 360 Inputs 
	DX360STTBWORD,
	DX360STSWORD,
	DX360INPUTWORD,
	DX360BVDFDBKSTAT2,
	DX360K4STAT,
	DX360ERSTATUS2,
	DX360DIRTL2,
	DX360OLRSTAT2,
	
    //DCU1
	DCU1WDTEL16,
	DCU1SPEED1,
	DCU1SPEED2,
	DCU1STATUSWRD1,
	DCU1STATUSWRD2,
	DCU1CTLSTATE,
	DCU1SPD1VALID,
	DCU1SPD2VALID,
	DCU1DBRTEMP,			//dynamic brake resistor temperature
	DCU1CCCCOM,				//close charging contactor command
	DCU1CSCCOM,				//close separation contactor command
	DCU1CCSTAT,				//charging contactor status
	DCU1SCSTAT,				//separation contactor status
	DCU1TEDEL,				//tractive effort delivered
	DCU1LINKVOL,			//link voltage 
	DCU1LINKCUR,			//line current
	DCU1LINKPWR,			//link power
	DCU1CPPWR,				//chopper power
	DCU1MOTPWR,				//motor power
	DCU1AIRTEMP,			//motor converter air temperature
	DCU1HSTEMP,				//heatsink temperature
	DCU1MOT1TEMP,			//motor temperature #1
	DCU1MOT2TEMP,			//motor temperature #2
	DCU1CHGRTEMP,			//charging resistor temperature 
	DCU1TSENABLE,			//traction safe enable 
	DCU1EARTHFLT,			//earth fault detected 
	DCU1RMSCUR,				//motor stator current, RMS
	DCU1DIAGWRD1,           //DCU Diagnostic Word 1
    DCU1DIAGWRD2,           //DCU Diagnostic Word 2
	DCU1DIAGWRD3,           //DCU Diagnostic Word 3
	DCU1DIAGWRD4,           //DCU Diagnostic Word 4
	DCU1DIAGWRD5,           //DCU Diagnostic Word 5
	DCU1DIAGWRD6,           //DCU Diagnostic Word 6
	DCU1DIAGWRD7,           //DCU Diagnostic Word 7
	DCU1DIAGWRD8,           //DCU Diagnostic Word 8
	DCU1DIAGWRD9,           //DCU Diagnostic Word 9 
	DCU1DIAGWRD10,          //DCU Diagnostic Word 10  
	DCU1DIAGWRD13,          //DCU Diagnostic Word 13
	DCU1ISOLATIONCODE,      // Reason for Isolation code from the DCU
	
 
	
	//DCU2
	DCU2WDTEL16,
	DCU2SPEED1,
	DCU2SPEED2,
	DCU2SPEED3,
	DCU2SPEED4,
	DCU2STATUSWRD1,
	DCU2STATUSWRD2,
	DCU2CTLSTATE,
	DCU2SPD1VALID,
	DCU2SPD2VALID,
	DCU2SPD3VALID,
	DCU2SPD4VALID, 
	DCU2DBRTEMP,			//dynamic brake resistor temperature
	DCU2CCCCOM,				//close charging contactor command
	DCU2CSCCOM,				//close separation contactor command
	DCU2CCSTAT,				//charging contactor status
	DCU2SCSTAT,				//separation contactor status
	DCU2TEDEL,				//tractive effort delivered 
	DCU2LINKVOL,			//link voltage
	DCU2LINKCUR,			//line current
	DCU2LINKPWR,			//link power
	DCU2CPPWR,				//chopper power
	DCU2MOTPWR,				//motor power 
	DCU2AIRTEMP,			//motor converter air temperature
	DCU2HSTEMP,				//heatsink temperature 
	DCU2MOT1TEMP,			//motor temperature #1
	DCU2MOT2TEMP,			//motor temperature #2 
	DCU2CHGRTEMP,			//charging resistor temperature  
	DCU2TSENABLE,			//traction safe enable 
	DCU2EARTHFLT,			//earth fault detected 
	DCU2RMSCUR,				//motor stator current, RMS
	DCU2DIAGWRD1,           //DCU Diagnostic Word 1
    DCU2DIAGWRD2,           //DCU Diagnostic Word 2
	DCU2DIAGWRD3,           //DCU Diagnostic Word 3
	DCU2DIAGWRD4,           //DCU Diagnostic Word 4
	DCU2DIAGWRD5,           //DCU Diagnostic Word 5
	DCU2DIAGWRD6,           //DCU Diagnostic Word 6
	DCU2DIAGWRD7,           //DCU Diagnostic Word 7
	DCU2DIAGWRD8,           //DCU Diagnostic Word 8
	DCU2DIAGWRD9,           //DCU Diagnostic Word 9
	DCU2DIAGWRD10,          //DCU Diagnostic Word 10
	DCU2DIAGWRD13,          //DCU Diagnostic Word 10
	DCU2ISOLATIONCODE, 		//DCU Reason for Isolation codes
	
	//motion
    MotPropTEReqTrk1,
    MotFBTEReqTrk1,
    MotPropTEReqTrk2,
    MotFBTEReqTrk2,
    MotSystemJRL,
    MotDbFadeSpeed,
    MOTFBSCALE,
    MOTBTE1,
    MOTBTE2,
    MOTTRK1COMPVAL,      
    MOTCOMPFADERATE,    
    MOTMAXFBTE,
    MotDBFadeJRLTruck1,
    MotDBFadeJRLTruck2,
    MOTTRK1PROPDEV,
    MOTTRK2PROPDEV,
    MOTPROPDEVTHRESH,
    MOTACTUALPROPOUTPUT1,
    MOTACTUALPROPOUTPUT2, 
    MOTFBTED1,
    MOTFBTED2,
    MOTFBTEDEF1,
    MOTFBTEDEF2,
    MOTFILTFBPRES1,
    MOTFILTFBPRES2, 
    MOTTESTFBPRES1,
    MOTTESTFBPRES2, 
    
    MOTFADEOUTPUT1,
	MOTFADEOUTPUT2,
	
	//Mot - False Motor Curve Acceleration Factors
	MOTFMCSTDPERFFACTRK1,
	MOTFMCHIGHPERFFACTRK1,
	MOTFMCSTDPERFFACTRK2,
	MOTFMCHIGHPERFFACTRK2,

	MOTPROPRATEREQTRK1,
	MOTPROPRATEREQTRK2,
 
    
    MOTPROPFACTOR,
    MOTINTFACTOR,
    MOTSIMTIMECONST,
    MOTMATOTEVAR1,
    MOTMATOTEVAR2,
    MOTTRGTEFF1,
    MOTTRGTEFF2,
    MOTIREQUESTTRK1,
    MOTIINTEGRALTRK1,
    MOTICOMMANDTRK1,
    MOTIPREDICTTRK1,
    MOTIREQUESTTRK2,
    MOTIINTEGRALTRK2,
    MOTICOMMANDTRK2,
    MOTIPREDICTTRK2,
	 
	//TrainControl
	 
	 
	//Velocity
	VelAxle1Raw,
	VelAxle2Raw,
	VelAxle3Raw,
	VelAxle4Raw,
	VelAxle1Filtered,
	VelAxle2Filtered,
	VelAxle3Filtered,
	VelAxle4Filtered, 
	VelCarSpeed,
	CarVelocity,
	VelAxle1Rate,
 	VelAxle2Rate,
  	VelAxle3Rate,
  	VelAxle4Rate, 
	VelTruck1Rate,
 	VelTruck2Rate,
 	VelCarRate,
 	VelAxleRefRaw,
 	VelRefRate,
 	VelAxle1AngRate,
 	VelAxle2AngRate,
 	VelAxle3AngRate,
 	VelAxle4AngRate,
 	VelCarAngRate, 
 	carRateConvert, 
 	refSpeedAng, 
 	VelCarAngSpeed,
 	
 
 	 
 	
	//protection
	HVBDCTHRSH1,			//Truck #1 Ground Fault Threshold
	HVBDCTHRSH2,			//Truck #2 Ground Fault Threshold
	PROTLOCTHRES1,			//LC Overcurrent Threshold #1
	PROTLOCTHRES2,			//LC Overcurrent Threshold #2
	PROTFWDSPDLIMLO,        // Forward Speed limit Alarm
	PROTFWDSPDLIMHI,        // Forward Penalty Brake Speed
	PROTREVSPDLIMLO,        // Reverse Speed limit Alarm
	PROTREVSPDLIMHI,        // Reverse Penalty Brake Speed 
	PROTBRKRATESPD,			//Brake Rate Speed Threshold  
	PROTT1LWVAR1,			//Truck 1 load weight calculation variable 1
	PROTT1LWVAR2,			//Truck 1 load weight calculation variable 2
	PROTT2LWVAR1,			//Truck 2 load weight calculation variable 1
	PROTT2LWVAR2,			//Truck 2 load weight calculation variable 2 
	PROTLOSTFBTE,
	PROTLOSTPROPTE,
	
	PROTLLVEBTHRESH1,
	PROTLLVEBTHRESH2,
	PROTMOBADLIFE,			//hours remaining on MOBAD life
	PROTHOURSELAPSED,		//hours elapsed during power off
	PROTBRKRATEDEV,			//brake rate deviation
    PROTROLLTHRES,          // Rollback Odometer Threshold
  	PROTATOBCPTHRES1,       //FSB determination BCP Threshold Truck #1
  	PROTATOBCPTHRES2,       //FSB determination BCP Threshold Truck #2
  
	
	//train control
	TcOperRateReq, 
	
	//friction brake
	MOTFBCOM1,				//Truck #1 Friction Brake Current Command
	MOTFBCOM2,				//Truck #2 Friction Brake Current Command 
	MOTT1ISP1,				//Truck #1 In Shot Pressure #1
	MOTT2ISP1,				//Truck #2 In Shot Pressure #1
	MOTT1ISP2,				//Truck #1 In Shot Pressure #2
	MOTT2ISP2,				//Truck #2 In Shot Pressure #2
	FBSBPRES1,				//snow brake pressure 1
	FBSBPRES2,				//snow brake pressure 2
	FBTRK1EXPEBRAKE,		//expected bcp in emergency 1
	FBTRK2EXPEBRAKE,		//expected bcp in emergency 2
	FBT2SBPRES1,				//snow brake pressure 1
	FBT2SBPRES2,				//snow brake pressure 2 
	FBLLVVAR1,				//variable used in LLV calculation
	FBLLVVAR2,				//variable used in LLV calculation  
	FBPRESSRANGELO,          // variable used on Friction Brake Difference Monitoring
	FBPRESSRANGEHI,          // variable used on Friction Brake Difference Monitoring
	FBCMDDIFFTHRESHOLD,      // variable used on Friction Brake Difference Monitoring
	
	//direction
	RBSPEEDTHRESH,		//rollback speed threshold 
	DIRCHANGESPEED,		//direction change monitoring speed threshold
	
	// Spin Slide
	spinAsyncReadhereThresh,
	spinVelocityReadhereThresh,
	spinSyncReadhereThresh,
	slideEBReadhereAsyncThresh,
	slideSBReadhereAsyncThresh, 
	slideEBReadhereVelocityThresh,
	slideSBReadhereVelocityThresh,
	slideEBReadhereSyncThresh,
	slideSBReadhereSyncThresh,
	spinDetAsyncThresh,
	spinDetVelocityThresh,
	spinDetSyncThresh,
	slideAsyncServiceThresh,
	slideAsyncEmerBrakeThresh,
	slideSyncServiceThresh,
	slideSyncEmerBrakeThresh,
	ssInAxle1Rate,
	ssInAxle2Rate,
	ssInAxle3Rate,
	ssInAxle4Rate,
	ssInAxle1Speed,
	ssInAxle2Speed,
	ssInAxle3Speed,
	ssInAxle4Speed,
	ssInOperRateReq,
	ssInMot1RateReq,
	ssInMot2RateReq,
	ssInCarRate,
	
	ssOutRateJerkLimit1,
	ssOutRateLimit1,
	ssOutRateNonJerkLimit1,
	ssOutRateJerkLimit2,
	ssOutRateLimit2,
	ssOutRateNonJerkLimit2,
  
	LVLOWNRGTHRSH2,
	LVLOWNRGTHRSH1,
	
	//master/slave
	VCUSUTCOM, 
	
	//self test
	STAPPLYPSIT1,						//BVD Apply pressure for truck#1 BVC test
	STCOMMANDPSIT1,						//FB Apply pressure for truck#1 BVC test
	STHOLDPSIT1,						//BVD Hold pressure for truck#1 BVC test
	STRANGEPSIT1,						//FB range pressure for truck#1 BVC test
	STMRPSIT1,							//main reservoir pressure for truck#1 BVC test
	STAPPLYPSIT2,						//BVD Apply pressure for truck#2 BVC test
	STCOMMANDPSIT2,						//FB Apply pressure for truck#2 BVC test
	STHOLDPSIT2,						//BVD Hold pressure for truck#2 BVC test
	STRANGEPSIT2,						//FB range pressure for truck#2 BVC test
	STMRPSIT2,							//main reservoir pressure for truck#2 BVC test



	MaxI32WVarId // This should be the last element
};        



// This is the Enumeration Type for INT_8 data-type
// Watch Variables. The element "MaxI8WVarId",
// gives the size of INT_8 Watch Variables, which should
// be the last in the list.
enum i8WVarId
{
  MaxI8WVarId // This should be the last element
};

// This is the Enumeration Type for UINT_16 data-type
// Watch Variables. The element "MaxU16WVarId",
// gives the size of UINT_16 Watch Variables, which
// should be the last in the list.
enum u16WVarId
{ 
  pHardwareReset,
  cbramPattern,
  cbramCrc,
  cbramTestVar,
  cbramCarId,
  ncbramTestVar,
  cbramHighPerfEnable,
  cbramRefWheelDiam,
  ptuRTSMonMode, 
  ncbraminputCounter,
  IOCounter,
  mvb16PtuOverride,
  mvb64PtuOverride,
  mvb128PtuOverride,
  mvb1024PtuOverride,

  Debug16u1,
  Debug16u2,
  Debug16u3,
  Debug16u4,
  Debug16u5,
  Debug16u6,  
  
  actRequestor,
  ATOMODE,
  ATOEnable, 
  IPATOEnable,
  MC1POWERENABLE,
  MC2POWERENABLE,
  ATO1POWERENABLE,
  ATO2POWERENABLE,
  MC1ENCODERSTATUS,
  MC2ENCODERSTATUS,
  ATO1ENCODERSTATUS,
  ATO2ENCODERSTATUS,

  //Architecture Version
  ARCHVERSION,
  
  //Production Test Outputs
  PRODSTENABLE,
  DX330OUT_K1,
  DX330OUT_K2,
  DX330OUT_K3,
  DX330OUT_PBAPPLY,
  DX330OUT_PBREL,
  DX330OUT_OLR1,
  DX360OUT_K1,
  DX360OUT_K2,
  DX360OUT_K3,
  DX360OUT_POR,
  DX360OUT_OLR2,
  DX360OUT_ZV1,

  
  //direction
  //DIRREQUEST,
  //DIRCOMMAND,
  //DIRFEEDBACK,
   VelTruck2SpeedCalcHi,
   VelTruck2SpeedCalcLo, 
  
   //Velocity
   VelCounter, 
   VelAxle1OpStatus,
   VelAxle2OpStatus,
   VelAxle3OpStatus,
   VelAxle4OpStatus,
   VelAxle1StatFailure,
   VelAxle2StatFailure,
   VelTruck1Status,
   VelTruck2Status,
   VelZeroSpeedFlag,
   VelCarState, 
   VelCarSpeedCalcHi,
   VelCarSpeedCalcLo,  
   VelAxle1WheelDiameter,
   VelAxle2WheelDiameter,
   VelAxle3WheelDiameter,
   VelAxle4WheelDiameter,
   VelTruck1SpeedCalcHi,
   VelTruck1SpeedCalcLo,
   //VelTruck2SpeedCalcHi,
   //VelTruck2SpeedCalcLo, 
   VelCarType,
   VelTruck1RateCalcHi,
   VelTruck1RateCalcLo,
   VelTruck2RateCalcHi,
   VelTruck2RateCalcLo,    
   VelCarRateCalcHi,
   VelCarRateCalcLo, 
   VelRefWheelDiameter, 
   VelCarPosition, 
   VelAxleRefWheelDiameter,
   VelAllWheelSlide,
   CalcWheelDiam1,
   CalcWheelDiam2,
   CalcWheelDiam3,
   CalcWheelDiam4,  
   calcWheelDiamDiffmax1,
   calcWheelDiamDiffmax2,
   calcWheelDiamDiffmax3,
   calcWheelDiamDiffmax4,
   VelRefSpeedSelect, 
   VelSetOdometerFlag,
   velTachResetCmd, 
   
    DIRREQUEST1,			//Truck #1 Direction Request 
	DIRCOMMAND1,			//Truck #1 Direction Command
	DIRFEEDBACK1,			//Truck #1 Direction Feedback
	DIRREQPROPINHIBIT1,		//Truck #1 Direction Request Propulsion Inhibit Request
	DIRMMPROPINHIBIT1,		//Truck #1 Direction Mismatch Discharge Request
	DIRRBPROPINHIBIT,		//Rollback Discharge request
	DIRREQUEST2,			//Truck #2 Direction Request 
	DIRCOMMAND2,			//Truck #2 Direction Command
	DIRFEEDBACK2,			//Truck #2 Direction Feedback
	DIRREQPROPINHIBIT2,		//Truck #2 Direction Request Propulsion Inhibit Request
	DIRMMPROPINHIBIT2,		//Truck #2 Direction Mismatch Discharge Request
	DIRCOMACT2,				//Actual direction command to Truck #2
	DIRREQCHARGE2,			//direction request charge request for truck #2
	DIRREQCHARGE1,			//direction request charge request for truck #1
	DIRFBACT2,				//actual direction feedback from Truck #2 
	DIRCOMTRK1,				//direction command output to truck #1                
	DIRCOMTRK2,				//direction command output to truck #2
	
	// Protection
	PROTCOUNTER,
	PROTCARTYPE,
	PROTCARVALID,
	PROTMONDISABLE, 
	PROTLOCKOUTRESET,
	PROTGOODBEHCOUNT,
	PROTGOODBEHCOUNTB,
	HVBGFL1,				//HVB Grnd Flt Limit #1
	HVBGFL2,				//HVB Grnd Flt Limit #2
	PROTLOCLIMIT1,			//Line Over-Current Limit #1
	PROTLOCLIMIT2,			//Line Over-Current Limit #2 
	PROTOLRSTAT1,			//OLR Status 1
	PROTOLRSTAT2,			//OLR Status 2 
	PROTPCULockoutDCU1,   //Lockout Status of DCU1
    PROTPCULockoutDCU2,   //Lockout Status of DCU1

  	PROTREGENENABLE,          // Enable regenerative braking 
  	PROTBRKRATE,			//brake rate fault 
  	PROTPORCOMMAND, 
  	OLR1COMMAND,
  	OLR2COMMAND, 
  	PROPSTATUS,
  	PROPSTATUSB,
  	PROTTIMSTESTVAL,  
  	PROTNUMFAILEDFB, 
  	PROTBFCDISABLED,	//BFC disable due to no master VCU on at least 1 car
  	PROTPREDEPDATA,		//pre-departure test data
  	PROTPREDEPMODE,		//predeparture test mode 
  	PROTSYSTESTMODE,	//system test mode
  	PROTLVNRGMILE1,       //Mileage limit for High Voltage Input Circuit Monitoring tk1
    PROTLVNRGMILE2,       //Mileage limit for High Voltage Input Circuit Monitoring tk2 
    PROTWSTD,			//wheel slide test data  
    PROTWSTM,			//wheel slide test mode 
    PROTWSTC,			//wheel slide test command
    
    MC1ATOMODE,
	MC2ATOMODE,
	ATO1ATOMODE,
	ATO2ATOMODE,
	MC1ATOFSBREQ,
	MC2ATOFSBREQ,
	ATO1ATOFSBREQ,
	ATO2ATOFSBREQ, 
	
	// IP variables
	ipPtuOverride,
	
	// Train Control
	TcCounter,
	TcOperModeReq,
	TcTcMode,
	TCTURTLEMODE,
	TCINOPFBFLAG,
	MC1BYPASSSTATUS,
	MC2BYPASSSTATUS,
	tcKeydownCountM,
	tcKeydownCountBackup,
	tcOffMaster,
	tcOffBackup,

	
	// DCU Control
	DCU1REQCOMMAND,
	DCU1RESETISOL,
	DCU1CALSTATUS,
	DCU1PUPOVERRIDE,
	
	
	DCU2REQCOMMAND,
	DCU2RESETISOL,
	DCU2CALSTATUS,  
	DCU2PUPOVERRIDE,
	
	
	// Motion
	MotCounter,
	MotMotionModeTrk1,
	MotMotionModeTrk2,
	MotPtuDbCutout,
	MotPtuDbCutout2,
	MotPtuHighPerfEnable,
	MOTWEIGHTFACTOR,
	MOTNUMFAILEDINV,  
	MOTTRK1COMPOFF,
	MOTTRK2COMPOFF,
	MOTTRK1DBFADE,
	MOTTRK2DBFADE,
	MOTTRK1BFCFLAG,
	MOTTRK2BFCFLAG,   
	MOTDBFADEDELAY,  
	MOTMAXFADEINDEX1,
	MOTMAXFADEINDEX2, 
	MOTELAPFADE1,
	MOTELAPFADE2,    
	MOTDBFADEDELAYENABLE,
	 
	MOTFBXFERFUNC,
	MOTPCLENABLE,  
	MOTPCLMODEL, 

	//Master slave Variables
    STARTRED,
  	MVBADDRESS,
  	MYTOKEN,
  	LOCAL_WD,
  	REMOTEVCU_WD,
  	REMOTEVCU_MSSTATUS,
  	PREVREMOTEVCU_WD,
  	PREVREMOTEVCU_MSSTATUS,
  	REDDEADCOUNTER,
  	REMOTEMVBADDRESS,
  	stopKeyDown,  
  	
  	//friction brake
  	MOTT1IST,					//truck #1 in shot time
  	MOTT2IST,					//truck #2 in shot time  
  	FBPBCOMMAND,				//parking brake command 
  	FBPBAPPLYCOM,				//parking brake apply command
  	FBPBRELCOM,					//parking brake apply command        
  	FBSBTIME,					//snow brake time                      
  	FBTRK1DRAGGING,				//truck 1 dragging
  	FBTRK2DRAGGING,				//truck 2 dragging 
  	FBTRK1LLV,					//truck 1 load limiting valve
  	FBTRK2LLV,					//truck 2 load limiting valve
  	FBTRK1CUTOUT,				//truck 1 cutout
  	FBTRK2CUTOUT,				//truck 2 cutout   
  	FBMARF,						//main air reservoir fault 
  	FBTRK1SLIDE,				//truck 1 slide control status
  	FBTRK2SLIDE,				//truck 2 slide control status
  	FBT2SBTIME,					//snow brake time 
  	FBTRK1OVERALLSTATUS,		//Overall Friction Brake Status Truck 1
  	FBTRK2OVERALLSTATUS,        //Overall Friction Brake Status Truck 2
  	PBOVERALLSTATUS,            //Overall Parking Brake Status 
  	SNOWBRAKESTATUS,             //Snow Brake
  	TURTLEMODEREQUESTED,
  	FBISSLIDE,					//in shot during slide 

  	 
  	// Spin Slide
   	ssSchedCounter,
   	ssEnableSlide1,
   	ssEnableSpin1,
	ssModeState1,
   	ssEnableSlide2,
   	ssEnableSpin2,
	ssModeState2,
	spin1MasterState,
	slide1MasterState,
	spin1Active,
	slide1Active,
	spin1CorrectionStage,
	slide1CorrectionStage,
	spin2MasterState,
	slide2MasterState,
	spin2Active,
	slide2Active,
	spin2CorrectionStage,
	slide2CorrectionStage,
	spin1IsEnabledId,
	slide1IsEnabledId,
	spin1InProgressId,
	slide1InProgressId,
	spin2IsEnabledId,
	slide2IsEnabledId,
	spin2InProgressId,
	slide2InProgressId,
	spinReadhereInit,
	spinReadhere,
	slideSbInitDropPercent,
	slideEbInitDropPercent,
	slideSbDropPercent,
	slideEbDropPercent,
	ssInZeroSpeed,
	spinJRKnee1,
	spinJRKnee2,
	spinJRKnee3,
	spinJRKnee4,
	spinJRKnee5,
	spinJRLPercentKnee1,
	spinJRLPercentKnee2,
	spinJRLPercentKnee3,
	spinJRLPercentKnee4,
	spinJRLPercentKnee5,
	slideSBJRKnee1,
	slideSBJRKnee2,
	slideSBJRKnee3,
	slideSBJRKnee4,
	slideSBJRKnee5,
	slideSBJRLPercentKnee1,
	slideSBJRLPercentKnee2,
	slideSBJRLPercentKnee3,
	slideSBJRLPercentKnee4,
	slideSBJRLPercentKnee5,
	slideEBJRKnee1,
	slideEBJRKnee2,
	slideEBJRKnee3,
	slideEBJRKnee4,
	slideEBJRKnee5,
	slideEBJRLPercentKnee1,
	slideEBJRLPercentKnee2,
	slideEBJRLPercentKnee3,
	slideEBJRLPercentKnee4,
	slideEBJRLPercentKnee5,

	slideBVDApplyTime1,
	slideBVDApplyTime2,
	slideBVDApplyTime3,
	slideBVDApplyTime4,
	slideBVDApplyTime5,
	slideBVDHoldTime1,
	slideBVDHoldTime2,
	slideBVDHoldTime3,
	slideBVDHoldTime4,
	slideBVDHoldTime5,
	
	slide1BVDKnee,
	slide2BVDKnee,
	slide1BVDState,
	slide2BVDState,
	slide1BVDCommand,
	slide2BVDCommand,
	
	ssAllWheelSlide,
	ssCarState, 
		
	slideTimeoutEnabled,
  	spinTimeoutEnabled,
  	slideTimeoutEnabledTrk1,
  	spinTimeoutEnabledTrk1,
  	slideTimeoutEnabledTrk2,
  	spinTimeoutEnabledTrk2,  
  	
  	ssAngRateDisable,
  	ssPulseBVDDisable1, 
  	ssPulseBVDDisable2,

	zeroVelCh1Status,
	zeroVelCh2Status,
	zeroVelCarState,
	zeroVelManagerState,
	zeroVelFaultId,
	zeroVelCh1RelayCmd,
	zeroVelCarA,
    zeroVelThresh,
   	zeroVelZeroSpdWhileFaulted,	
   	ch2faultcounter,
   	ch2faultcountlimit,
   	
   	//selftest
   	ST_LIFESIGN,					//self test scheduler counter 
   	STSTATE,						//self test in progress
   	STRESET,						//self test reset 
   	STSUTFLAG,						//startup test flag
   	STPDTFLAG,						//pre-departure test flag 
    STPBTIME,						//parking brake test timing 
    STGENSYSMODE,					//general system mode
    STBVCFC1,						//BVC test fail count
    STBVCFL1,						//BVC test fail limit
    STBVCFC2,						//BVC test fail count
    STBVCFL2,						//BVC test fail limit
    STMAINTBYPASS,	                //Maint Allowed Bypass
	
	CalculateFlag, 
	
a1MasterZBTO, 		    //( Zero buffer counter) 
a1MasterComTO,	        //( circular buffer timeout0 
a1MasterVerTO,          //( Protocol version mismatch)
a1masterQualOneTO,      //(Qualify One Source) 


a1BackupZBTO,           //( Zero buffer counter) 
a1BackupComTO,          //( circular buffer timeout0 
a1BackupVerTO,          //( Protocol version mismatch)
a1BackupQualOneTO,      //(Qualify One Source)

a6MasterZBTO,           //( Zero buffer counter) 
a6MasterComTO,          //( circular buffer timeout0 
a6MasterVerTO,          //( Protocol version mismatch)
a6masterQualOneTO,      //(Qualify One Source)     

a1ATOZBTO,           //( Zero buffer counter) 
a1ATOComTO,          //( circular buffer timeout0 
a1ATOVerTO,          //( Protocol version mismatch)
a1ATOQualOneTO,      //(Qualify One Source) 

a6ATOZBTO,           //( Zero buffer counter) 
a6ATOComTO,          //( circular buffer timeout0 
a6ATOVerTO,          //( Protocol version mismatch)
a6ATOQualOneTO,      //(Qualify One Source) 

a6BackupZBTO,           //( Zero buffer counter) 
a6BackupComTO,          //( circular buffer timeout0 
a6BackupVerTO,          //( Protocol version mismatch)
a6BackupQualOneTO,      //(Qualify One Source)
 
stopTimsBadSwap,	    //stops check for Tims bad swaps  
ipBothOffFlag,
timsKeyDownReqFlag,      //both off process flag
timsKeyDownReq,          // boof off request received from tc
A1MasterOffCtr,          // increments when off is requested on the port
A1BackupOffCtr,
A6MasterOffCtr,
A6BackupOffCtr,  
A1ATOOffCtr, 
A6ATOOffCtr, 
msKeydownCount,			//number of keydowns recd by master slave 

FBPCLHSE,				//psuedo closed loop high speed enable

MaxU16WVarId // This should be the last element
};         



// This is the Enumeration Type for UINT_32 data-type
// Watch Variables. The element "MaxU32WVarId",
// gives the size of UINT_32 Watch Variables, which
// should be the last in the list.
enum u32WVarId
{
  dummy_HealthCounter,
  cbramSwVersion,
  ncbramBramEnd, 
  
  DX330STTB, 
  DI340STTB,
  DX360STTB,
  DX360SelfTest,
  DX330SelfTest,
  AX320_STTBSTATUS,
  AX370_STTBSTATUS,
  AX520_STTBSTATUS,
  
  Debug32u1,
  Debug32u2,
  Debug32u3,
  Debug32u4,
  Debug32u5,
  Debug32u6, 
  

  FB1CMDREQUEST,
  FB2CMDREQUEST,
  
  DCU2WD16Status,
  DCU1WD16Status,
  
  //Velocity
  VelAxle1Speed,
  VelAxle2Speed,
  VelAxle3Speed,
  VelAxle4Speed,  
  //VelAxle1SpeedFiltered,
  //VelAxle2SpeedFiltered,
  VelTruck1Speed,
  VelTruck2Speed, 
  VelOdometer,
  ZeroSpeedStop, 
  ZeroSpeedMove,
  VelRefSpeed, 
  VelSelectedRefSpeed,
  velWdCalcRateThresA1,
  velWdCalcRateThresA2,
  velWdCalcRateThresA3,
  velWdCalcRateThresA4, 
  VelNewOdometerValue,
  
  //protection
   
  HVBDCTMR1,			//HVB DC TIMER #1
  HVBDCTMR2,			//HVB DC TIMER #2 
  HVBGFC1,				//HVB Grnd Flt Count #1
  HVBGFC2,				//HVB Grnd Flt Count #2 
  PROTLOCCOUNT1,		//Line Over-Current Count #1
  PROTLOCCOUNT2,		//Line Over-Current Count #2
  PROTLOCTIMER1,		//LC Overcurrent Timer #1
  PROTLOCTIMER2,		//LC Overcurrent Timer #2
  PROTOLRCOUNT1,		//OLR Trip Count #1
  PROTOLRCOUNT2,		//OLR Trip Count #2
  PROTOLRRESCOUNT1,		//OLR Reset Fault Count #1
  PROTOLRRESCOUNT2,		//OLR Reset Fault Count #2
  isoDCU,      //testof tims
  PROTTM1COUNTER,		//TM#1 Counter
  PROTTM2COUNTER,		//TM#2 Counter
  PROTTM3COUNTER,		//TM#3 Counter
  PROTTM4COUNTER,		//TM#4 Counter
  PROTGU1COUNTER,		//GU#1 Counter
  PROTGU2COUNTER,		//GU#2 Counter
  PROTGU3COUNTER,		//GU#3 Counter
  PROTGU4COUNTER,		//GU#4 Counter
  FBPBMMSETTIME,		//parking brake mismatch set time  
  PROTFLTENUM,          //fault enumeration DCU 2 
  PROTFLTENUMB,         //fault enumeration DCU 1  	
  FBDIFFTIME,           // variable used on Friction Brake Difference Monitoring

  cumVcuAliveTime,
  Cum_En_ConTk1,
  cumEnergyRegenTk2,
  cumEnergyNonRegenTk1,
  Cum_En_ConTk2,
  cumEnergyNonRegenTk2,
  cumEnergyRegenTk1,
  PROTTRAINWEIGHT,			//weight of the entire train
  PROTPTRKWEIGHT,			//weight of the powered trucks 
  
  
  cumFbEffortTk1,		//cumulative friction brake energy
  cumFbEffortTk2,		//cumulative friction brake energy
  PROTCUMMSSWAPS,		//cumulative master/slave swaps
  PROTCUMTIMEEMERG,		//cumulative time in emergency
  PROTCUMTIMEMOTION,	//cumulative time in motion
  
  PROTLLVEBTIME1,
  PROTLLVEBTIME2,
  
  PROTER1MISMATCHTIME,
  PROTER2MISMATCHTIME,
  PROTCURRENTTIME,			//Current POSIX Time 
  
  ITSLVMTMRSet,      //ITS Line Voltage debouce when LV goes below value
  ITSLVMTMRClr,      //ITS Line Voltage debouce when LV goes above value
  
  //train control
  TcMaxSpeedLimitTarget1, //Max speed limiting - low speed at which rate limiting begins
  TcMaxSpeedLimitTarget2, //Max speed limiting - high speed at which point the acceleration rate is limited to 0
  TCINOPFBSPEEDTARGET1,
  TCINOPFBSPEEDTARGET2,
  TEMPSHUTDOWNSTATUS,
  TEMPSHUTDOWNSTATUSB,
  MC1BYPASSOFFTIME,
  MC2BYPASSOFFTIME,
  TCTURTLESPEEDTARGET1,		//Turtle mode speed target 1
  TCTURTLESPEEDTARGET2,		//Turtle mode speed target 2
  TCTURTLETOL,				//Turtle mode tolerange
  TCINOPFBTOL,				//inop friction brake speed limiting tolerance
  
  // DCU Control
  DCU1EXTCOND,
  DCU2EXTCOND,
  
  // Motion
  MotLoadWeighTrk1,
  MotLoadWeighTrk2, 
  MotRBPBrakePressureLimit,
  MotRBPTimerLimit,
  MotRBPBrakePressureLimit2,
  MotRBPTimerLimit2,
  MotCarWeight,
  
  
  //friction brake
  MOTISS,				//in shot speed threshold 
  
  //direction
  RBTIMETHRESH,			//rollback time threshold 
  DCT1NTRLSTOPOP,		//truck 1 neutral request stop operation time 
  DCT2NTRLSTOPOP,		//truck 2 neutral request stop operation time
  DCT1NTRLDSCHRG,		//truck 1 neutral request discharge time
  DCT2NTRLDSCHRG,		//truck 2 neutral request discharge time
  
  // Spin Slide
  ssInCarSpeed,
  slideTimeoutTimer,
  spinTimeoutTimer,
  slideTimeoutTimerTrk1,
  spinTimeoutTimerTrk1,
  slideTimeoutTimerTrk2,
  spinTimeoutTimerTrk2,
  slideVelocityServiceThresh,
  slideVelocityEmerBrakeThresh,
  slideVelocityServicePercent,
  slideVelocityEmerBrakePercent,
  slideVelocityTripThreshold1, 
  slideVelocityTripThreshold2, 
  slideVelocityReadhereThreshold,
  slideEBReadhereVelocityPercent,
  slideSBReadhereVelocityPercent,
  
  spinSpeedThresh,
  slideSpeedThresh,
  
  zeroVelCarSpeed,
  NMmismatchTime,
  VelHighestAxleSpeed,
  gradeAllow,
   
  PROTLVNRGMILE, 
  
  //self test
  STCHGTIME,				//charge time
  STCOMTESTTIME,			//commutation test time
  STIGBTTESTTIME,			//igbt test time
  STLDTESTTIME,				//load test time
  STOPERTIME,				//operation time
  STOVPTESTTIME,			//ovp test time
  STPDCHGTESTTIME,			//passive discharge test time
  STTESTMODETIME,			//test mode response time
  STTESTNOTIME,				//test number response time  
  STSUTINFO,				//startup test info bitmask
  STSUTFAILED,				//startup tests failed info bitmask 
  STPDTINFO,				//pre-departure test info bitmask
  STPDTFAILED,				//pre-departure tests failed info bitmask 
  STK123TIMET1,				//K1 K2 K3 timing for truck 1 BVD test
  STK123TIMET2,				//K1 K2 K3 timing for truck 2 BVD test 
  STK4TIMET1,				//K4 timing for truck 1 BVD test
  STK4TIMET2,				//K4 timing for truck 2 BVD test
  STAPPLYTIMET1,			//BVD Apply timing for truck 1 BVC test
  STDUMPTIMET1,				//BVD Dump timing for truck 1 BVC test
  STFBAPPLYTIMET1,			//FB Apply timing for truck 1 BVC test
  STAPPLYTIMET2,			//BVD Apply timing for truck 2 BVC test
  STDUMPTIMET2,				//BVD Dump timing for truck 2 BVC test
  STFBAPPLYTIMET2,			//FB Apply timing for truck 2 BVC test
  
  timsMessageFault,
   
   
  MaxU32WVarId // This should be the last element
};

// This is the Enumeration Type for UINT_8 data-type
// Watch Variables. The element "MaxU8WVarId",
// gives the size of UINT_8 Watch Variables, which
// should be the last in the list.
enum u8WVarId
{
  cbramFlag, 
  
  // Spin Slide
  slide1AllWheels,
  slide2AllWheels,
  slideDetectEmerBrakeEn,


  slide1BVDEnabled,
  slide2BVDEnabled,
  
  slideFBApplied1,
  slideFBApplied2,
  
  MaxU8WVarId // This should be the last element
};
//#]




#endif  
/*********************************************************************
	File Path	: RhapVCUC/Target/ProjectPkg/PtuEnumPkg/VCU/VCU.h
*********************************************************************/

