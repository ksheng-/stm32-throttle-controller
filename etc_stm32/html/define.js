function CodeDefine() { 
this.def = new Array();
this.def["rtDW"] = {file: "etc_c.html",line:40,type:"var"};
this.def["rtM_"] = {file: "etc_c.html",line:43,type:"var"};
this.def["rtM"] = {file: "etc_c.html",line:44,type:"var"};
this.def["etc_step"] = {file: "etc_c.html",line:47,type:"fcn"};
this.def["etc_initialize"] = {file: "etc_c.html",line:136,type:"fcn"};
this.def["RT_MODEL"] = {file: "etc_h.html",line:60,type:"type"};
this.def["DW"] = {file: "etc_h.html",line:69,type:"type"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:68,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:69,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:70,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:71,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:72,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:73,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:74,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:75,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:81,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:82,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:83,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:84,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:85,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:86,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:87,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:88,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:89,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:107,type:"type"};
this.def["G_NbAdcConf"] = {file: "etc_ADC_c.html",line:40,type:"var"};
this.def["G_ADC_Data"] = {file: "etc_ADC_c.html",line:43,type:"var"};
this.def["G_ADC_Handler"] = {file: "etc_ADC_c.html",line:44,type:"var"};
this.def["ADC1_RegularConvertedValue"] = {file: "etc_ADC_c.html",line:47,type:"var"};
this.def["ADC1_DataLink"] = {file: "etc_ADC_c.html",line:50,type:"var"};
this.def["ADC2_RegularConvertedValue"] = {file: "etc_ADC_c.html",line:53,type:"var"};
this.def["ADC2_DataLink"] = {file: "etc_ADC_c.html",line:56,type:"var"};
this.def["HAL_ADC_ConvCpltCallback"] = {file: "etc_ADC_c.html",line:63,type:"fcn"};
this.def["ADC_DataLinkTypeDef"] = {file: "etc_ADC_h.html",line:59,type:"type"};
this.def["G_TIM_Data"] = {file: "etc_TIM_c.html",line:40,type:"var"};
this.def["G_TIM_Handler"] = {file: "etc_TIM_c.html",line:41,type:"var"};
this.def["TIM1_DataLink"] = {file: "etc_TIM_c.html",line:44,type:"var"};
this.def["G_TIM1_PollTimeOut"] = {file: "etc_TIM_c.html",line:47,type:"var"};
this.def["TIM_DataLinkTypeDef"] = {file: "etc_TIM_h.html",line:95,type:"type"};
this.def["TIM_ChTypeDef"] = {file: "etc_TIM_h.html",line:108,type:"type"};
this.def["OverrunFlags"] = {file: "main_c.html",line:50,type:"var"};
this.def["autoReloadTimerLoopVal_S"] = {file: "main_c.html",line:53,type:"var"};
this.def["remainAutoReloadTimerLoopVal_S"] = {file: "main_c.html",line:56,type:"var"};
this.def["main"] = {file: "main_c.html",line:67,type:"fcn"};
this.def["HAL_SYSTICK_Callback"] = {file: "main_c.html",line:134,type:"fcn"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["etc_c.html"] = "../etc.c";
	this.html2Root["etc_c.html"] = "etc_c.html";
	this.html2SrcPath["etc_h.html"] = "../etc.h";
	this.html2Root["etc_h.html"] = "etc_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.html2SrcPath["STM32_Config_h.html"] = "../STM32_Config.h";
	this.html2Root["STM32_Config_h.html"] = "STM32_Config_h.html";
	this.html2SrcPath["etc_ADC_c.html"] = "../etc_ADC.c";
	this.html2Root["etc_ADC_c.html"] = "etc_ADC_c.html";
	this.html2SrcPath["etc_ADC_h.html"] = "../etc_ADC.h";
	this.html2Root["etc_ADC_h.html"] = "etc_ADC_h.html";
	this.html2SrcPath["etc_TIM_c.html"] = "../etc_TIM.c";
	this.html2Root["etc_TIM_c.html"] = "etc_TIM_c.html";
	this.html2SrcPath["etc_TIM_h.html"] = "../etc_TIM.h";
	this.html2Root["etc_TIM_h.html"] = "etc_TIM_h.html";
	this.html2SrcPath["main_c.html"] = "../main.c";
	this.html2Root["main_c.html"] = "main_c.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"etc_c.html","etc_h.html","rtwtypes_h.html","STM32_Config_h.html","etc_ADC_c.html","etc_ADC_h.html","etc_TIM_c.html","etc_TIM_h.html","main_c.html"];
