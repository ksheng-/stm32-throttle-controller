function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/ADC_Read */
	this.urlHashMap["etc:128"] = "etc.c:55,237&etc.h:64";
	/* <Root>/ADC_Read3 */
	this.urlHashMap["etc:114"] = "etc.c:63,241&etc.h:65";
	/* <Root>/Abs */
	this.urlHashMap["etc:68"] = "etc.c:100&etc.h:66";
	/* <Root>/Function-Call
Subsystem */
	this.urlHashMap["etc:42"] = "msg=rtwMsg_notTraceable&block=etc:42";
	/* <Root>/GPIO_Write */
	this.urlHashMap["etc:115"] = "etc.c:106";
	/* <Root>/Gain */
	this.urlHashMap["etc:71"] = "msg=rtwMsg_notTraceable&block=etc:71";
	/* <Root>/STM32_Config */
	this.urlHashMap["etc:39"] = "etc.c:53";
	/* <Root>/Saturation */
	this.urlHashMap["etc:117"] = "msg=rtwMsg_notTraceable&block=etc:117";
	/* <Root>/Sign */
	this.urlHashMap["etc:104"] = "msg=rtwMsg_notTraceable&block=etc:104";
	/* <Root>/Sum1 */
	this.urlHashMap["etc:106"] = "etc.c:71";
	/* <Root>/Timers */
	this.urlHashMap["etc:40"] = "etc.c:114,245";
	/* <S1>/Compare */
	this.urlHashMap["etc:127:2"] = "msg=rtwMsg_reducedBlock&block=etc:127:2";
	/* <S1>/Constant */
	this.urlHashMap["etc:127:3"] = "msg=rtwMsg_reducedBlock&block=etc:127:3";
	/* <S2>/Derivative Gain */
	this.urlHashMap["etc:69:1668"] = "etc.c:76";
	/* <S2>/Filter */
	this.urlHashMap["etc:69:1670"] = "etc.c:75,111&etc.h:68";
	/* <S2>/Filter Coefficient */
	this.urlHashMap["etc:69:1671"] = "etc.c:74";
	/* <S2>/Integral Gain */
	this.urlHashMap["etc:69:1667"] = "etc.c:103";
	/* <S2>/Integrator */
	this.urlHashMap["etc:69:1669"] = "etc.c:83,108&etc.h:67";
	/* <S2>/Proportional Gain */
	this.urlHashMap["etc:69:1666"] = "etc.c:84";
	/* <S2>/Saturate */
	this.urlHashMap["etc:69:1673"] = "etc.c:89,98";
	/* <S2>/Sum */
	this.urlHashMap["etc:69:1665"] = "etc.c:82";
	/* <S2>/SumD */
	this.urlHashMap["etc:69:1672"] = "etc.c:77";
	/* <S3>/GPIO_Write */
	this.urlHashMap["etc:41"] = "msg=rtwMsg_notTraceable&block=etc:41";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "etc"};
	this.sidHashMap["etc"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "etc:127"};
	this.sidHashMap["etc:127"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "etc:69"};
	this.sidHashMap["etc:69"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<S3>"] = {sid: "etc:42"};
	this.sidHashMap["etc:42"] = {rtwname: "<S3>"};
	this.rtwnameHashMap["<Root>/ADC_Read"] = {sid: "etc:128"};
	this.sidHashMap["etc:128"] = {rtwname: "<Root>/ADC_Read"};
	this.rtwnameHashMap["<Root>/ADC_Read3"] = {sid: "etc:114"};
	this.sidHashMap["etc:114"] = {rtwname: "<Root>/ADC_Read3"};
	this.rtwnameHashMap["<Root>/Abs"] = {sid: "etc:68"};
	this.sidHashMap["etc:68"] = {rtwname: "<Root>/Abs"};
	this.rtwnameHashMap["<Root>/Compare To Zero"] = {sid: "etc:127"};
	this.sidHashMap["etc:127"] = {rtwname: "<Root>/Compare To Zero"};
	this.rtwnameHashMap["<Root>/Controller"] = {sid: "etc:69"};
	this.sidHashMap["etc:69"] = {rtwname: "<Root>/Controller"};
	this.rtwnameHashMap["<Root>/Function-Call Subsystem"] = {sid: "etc:42"};
	this.sidHashMap["etc:42"] = {rtwname: "<Root>/Function-Call Subsystem"};
	this.rtwnameHashMap["<Root>/GPIO_Write"] = {sid: "etc:115"};
	this.sidHashMap["etc:115"] = {rtwname: "<Root>/GPIO_Write"};
	this.rtwnameHashMap["<Root>/Gain"] = {sid: "etc:71"};
	this.sidHashMap["etc:71"] = {rtwname: "<Root>/Gain"};
	this.rtwnameHashMap["<Root>/STM32_Config"] = {sid: "etc:39"};
	this.sidHashMap["etc:39"] = {rtwname: "<Root>/STM32_Config"};
	this.rtwnameHashMap["<Root>/Saturation"] = {sid: "etc:117"};
	this.sidHashMap["etc:117"] = {rtwname: "<Root>/Saturation"};
	this.rtwnameHashMap["<Root>/Sign"] = {sid: "etc:104"};
	this.sidHashMap["etc:104"] = {rtwname: "<Root>/Sign"};
	this.rtwnameHashMap["<Root>/Sum1"] = {sid: "etc:106"};
	this.sidHashMap["etc:106"] = {rtwname: "<Root>/Sum1"};
	this.rtwnameHashMap["<Root>/Timers"] = {sid: "etc:40"};
	this.sidHashMap["etc:40"] = {rtwname: "<Root>/Timers"};
	this.rtwnameHashMap["<S1>/u"] = {sid: "etc:127:1"};
	this.sidHashMap["etc:127:1"] = {rtwname: "<S1>/u"};
	this.rtwnameHashMap["<S1>/Compare"] = {sid: "etc:127:2"};
	this.sidHashMap["etc:127:2"] = {rtwname: "<S1>/Compare"};
	this.rtwnameHashMap["<S1>/Constant"] = {sid: "etc:127:3"};
	this.sidHashMap["etc:127:3"] = {rtwname: "<S1>/Constant"};
	this.rtwnameHashMap["<S1>/y"] = {sid: "etc:127:5"};
	this.sidHashMap["etc:127:5"] = {rtwname: "<S1>/y"};
	this.rtwnameHashMap["<S2>/u"] = {sid: "etc:69:1"};
	this.sidHashMap["etc:69:1"] = {rtwname: "<S2>/u"};
	this.rtwnameHashMap["<S2>/Derivative Gain"] = {sid: "etc:69:1668"};
	this.sidHashMap["etc:69:1668"] = {rtwname: "<S2>/Derivative Gain"};
	this.rtwnameHashMap["<S2>/Filter"] = {sid: "etc:69:1670"};
	this.sidHashMap["etc:69:1670"] = {rtwname: "<S2>/Filter"};
	this.rtwnameHashMap["<S2>/Filter Coefficient"] = {sid: "etc:69:1671"};
	this.sidHashMap["etc:69:1671"] = {rtwname: "<S2>/Filter Coefficient"};
	this.rtwnameHashMap["<S2>/Integral Gain"] = {sid: "etc:69:1667"};
	this.sidHashMap["etc:69:1667"] = {rtwname: "<S2>/Integral Gain"};
	this.rtwnameHashMap["<S2>/Integrator"] = {sid: "etc:69:1669"};
	this.sidHashMap["etc:69:1669"] = {rtwname: "<S2>/Integrator"};
	this.rtwnameHashMap["<S2>/Proportional Gain"] = {sid: "etc:69:1666"};
	this.sidHashMap["etc:69:1666"] = {rtwname: "<S2>/Proportional Gain"};
	this.rtwnameHashMap["<S2>/Saturate"] = {sid: "etc:69:1673"};
	this.sidHashMap["etc:69:1673"] = {rtwname: "<S2>/Saturate"};
	this.rtwnameHashMap["<S2>/Sum"] = {sid: "etc:69:1665"};
	this.sidHashMap["etc:69:1665"] = {rtwname: "<S2>/Sum"};
	this.rtwnameHashMap["<S2>/SumD"] = {sid: "etc:69:1672"};
	this.sidHashMap["etc:69:1672"] = {rtwname: "<S2>/SumD"};
	this.rtwnameHashMap["<S2>/y"] = {sid: "etc:69:10"};
	this.sidHashMap["etc:69:10"] = {rtwname: "<S2>/y"};
	this.rtwnameHashMap["<S3>/TOGGLE GREEN LED"] = {sid: "etc:44"};
	this.sidHashMap["etc:44"] = {rtwname: "<S3>/TOGGLE GREEN LED"};
	this.rtwnameHashMap["<S3>/GPIO_Write"] = {sid: "etc:41"};
	this.sidHashMap["etc:41"] = {rtwname: "<S3>/GPIO_Write"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
