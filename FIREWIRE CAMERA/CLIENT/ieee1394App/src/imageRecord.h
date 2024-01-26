/*
#include <vxWorks.h>
#include <semLib.h>
#include "ellLib.h"
#include "fast_lock.h"
#include "link.h"
#include "tsDefs.h"
*/

#ifndef INCimageSIZEH
#define INCimageSIZEH
typedef enum {
	imageSIZE_1,
	imageSIZE_2
}imageSIZE;
#endif /*INCimageSIZEH*/

#ifndef INCimageENAH
#define INCimageENAH
typedef enum {
	imageENA_D,
	imageENA_E
}imageENA;
#endif /*INCimageENAH*/
#ifndef INCimageH
#define INCimageH
typedef struct imageRecord {
	char		name[29]; /*Record Name*/
	char		desc[29]; /*Descriptor*/
	char		asg[29]; /*Access Security Group*/
	unsigned short	scan;	/*Scan Mechanism*/
	unsigned short	pini;	/*Process at iocInit*/
	short		phas;	/*Scan Phase*/
	short		evnt;	/*Event Number*/
	short		tse;	/*Time Stamp Event*/
	DBLINK		tsel;	/*Time Stamp Link*/
	unsigned short	dtyp;	/*Device Type*/
	short		disv;	/*Disable Value*/
	short		disa;	/*Disable*/
	DBLINK		sdis;	/*Scanning Disable*/
	FAST_LOCK	mlok;	/*Monitor fastlock*/
	ELLLIST		mlis;	/*Monitor List*/
	unsigned char	disp;	/*Disable putField*/
	unsigned char	proc;	/*Force Processing*/
	unsigned short	stat;	/*Alarm Status*/
	unsigned short	sevr;	/*Alarm Severity*/
	unsigned short	nsta;	/*New Alarm Status*/
	unsigned short	nsev;	/*New Alarm Severity*/
	unsigned short	acks;	/*Alarm Ack Severity*/
	unsigned short	ackt;	/*Alarm Ack Transient*/
	unsigned short	diss;	/*Disable Alarm Sevrty*/
	unsigned char	lcnt;	/*Lock Count*/
	unsigned char	pact;	/*Record active*/
	unsigned char	putf;	/*dbPutField process*/
	unsigned char	rpro;	/*Reprocess */
	void		*asp;	/*Access Security Pvt*/
	void		*ppn;	/*addr of PUTNOTIFY*/
	void		*ppnn;	/*next record PUTNOTIFY*/
	void		*spvt;	/*Scan Private*/
	void		*rset;	/*Address of RSET*/
	struct dset	*dset;	/*DSET address*/
	void		*dpvt;	/*Device Private*/
	void		*rdes;	/*Address of dbRecordType*/
	void		*lset;	/*Lock Set*/
	unsigned short	prio;	/*Scheduling Priority*/
	unsigned char	tpro;	/*Trace Processing*/
	char bkpt;	/*Break Point*/
	unsigned char	udf;	/*Undefined*/
	TS_STAMP	time;	/*Time*/
	DBLINK		flnk;	/*Forward Process Link*/
	double		vers;	/*Code Version*/
	unsigned short	enab;	/*Record Enable*/
	double		rate;	/*Rate Limit (sec)*/
	unsigned long	pmtk;	/*Prev Monitor Tick*/
	double		val;	/*Result*/
	DBLINK		inp;	/*Input Specification*/
	char		vxnm[40]; /*vxWorks symbol*/
	unsigned short	size;	/*Bytes/Pixel*/
	unsigned long	xres;	/*X Res - Pixels*/
	unsigned long	yres;	/*Y Res - Scan Lines*/
	unsigned long	rxst;	/*ROI X Start*/
	unsigned long	rxsz;	/*ROI X Size*/
	unsigned long	ryst;	/*ROI Y Start*/
	unsigned long	rysz;	/*ROI Y Size*/
	void * l0;	/*Scan Line*/
	void * l1;	/*Scan Line*/
	void * l2;	/*Scan Line*/
	void * l3;	/*Scan Line*/
	void * l4;	/*Scan Line*/
	void * l5;	/*Scan Line*/
	void * l6;	/*Scan Line*/
	void * l7;	/*Scan Line*/
	void * l8;	/*Scan Line*/
	void * l9;	/*Scan Line*/
	void * l10;	/*Scan Line*/
	void * l11;	/*Scan Line*/
	void * l12;	/*Scan Line*/
	void * l13;	/*Scan Line*/
	void * l14;	/*Scan Line*/
	void * l15;	/*Scan Line*/
	void * l16;	/*Scan Line*/
	void * l17;	/*Scan Line*/
	void * l18;	/*Scan Line*/
	void * l19;	/*Scan Line*/
	void * l20;	/*Scan Line*/
	void * l21;	/*Scan Line*/
	void * l22;	/*Scan Line*/
	void * l23;	/*Scan Line*/
	void * l24;	/*Scan Line*/
	void * l25;	/*Scan Line*/
	void * l26;	/*Scan Line*/
	void * l27;	/*Scan Line*/
	void * l28;	/*Scan Line*/
	void * l29;	/*Scan Line*/
	void * l30;	/*Scan Line*/
	void * l31;	/*Scan Line*/
	void * l32;	/*Scan Line*/
	void * l33;	/*Scan Line*/
	void * l34;	/*Scan Line*/
	void * l35;	/*Scan Line*/
	void * l36;	/*Scan Line*/
	void * l37;	/*Scan Line*/
	void * l38;	/*Scan Line*/
	void * l39;	/*Scan Line*/
	void * l40;	/*Scan Line*/
	void * l41;	/*Scan Line*/
	void * l42;	/*Scan Line*/
	void * l43;	/*Scan Line*/
	void * l44;	/*Scan Line*/
	void * l45;	/*Scan Line*/
	void * l46;	/*Scan Line*/
	void * l47;	/*Scan Line*/
	void * l48;	/*Scan Line*/
	void * l49;	/*Scan Line*/
	void * l50;	/*Scan Line*/
	void * l51;	/*Scan Line*/
	void * l52;	/*Scan Line*/
	void * l53;	/*Scan Line*/
	void * l54;	/*Scan Line*/
	void * l55;	/*Scan Line*/
	void * l56;	/*Scan Line*/
	void * l57;	/*Scan Line*/
	void * l58;	/*Scan Line*/
	void * l59;	/*Scan Line*/
	void * l60;	/*Scan Line*/
	void * l61;	/*Scan Line*/
	void * l62;	/*Scan Line*/
	void * l63;	/*Scan Line*/
	void * l64;	/*Scan Line*/
	void * l65;	/*Scan Line*/
	void * l66;	/*Scan Line*/
	void * l67;	/*Scan Line*/
	void * l68;	/*Scan Line*/
	void * l69;	/*Scan Line*/
	void * l70;	/*Scan Line*/
	void * l71;	/*Scan Line*/
	void * l72;	/*Scan Line*/
	void * l73;	/*Scan Line*/
	void * l74;	/*Scan Line*/
	void * l75;	/*Scan Line*/
	void * l76;	/*Scan Line*/
	void * l77;	/*Scan Line*/
	void * l78;	/*Scan Line*/
	void * l79;	/*Scan Line*/
	void * l80;	/*Scan Line*/
	void * l81;	/*Scan Line*/
	void * l82;	/*Scan Line*/
	void * l83;	/*Scan Line*/
	void * l84;	/*Scan Line*/
	void * l85;	/*Scan Line*/
	void * l86;	/*Scan Line*/
	void * l87;	/*Scan Line*/
	void * l88;	/*Scan Line*/
	void * l89;	/*Scan Line*/
	void * l90;	/*Scan Line*/
	void * l91;	/*Scan Line*/
	void * l92;	/*Scan Line*/
	void * l93;	/*Scan Line*/
	void * l94;	/*Scan Line*/
	void * l95;	/*Scan Line*/
	void * l96;	/*Scan Line*/
	void * l97;	/*Scan Line*/
	void * l98;	/*Scan Line*/
	void * l99;	/*Scan Line*/
	void * l100;	/*Scan Line*/
	void * l101;	/*Scan Line*/
	void * l102;	/*Scan Line*/
	void * l103;	/*Scan Line*/
	void * l104;	/*Scan Line*/
	void * l105;	/*Scan Line*/
	void * l106;	/*Scan Line*/
	void * l107;	/*Scan Line*/
	void * l108;	/*Scan Line*/
	void * l109;	/*Scan Line*/
	void * l110;	/*Scan Line*/
	void * l111;	/*Scan Line*/
	void * l112;	/*Scan Line*/
	void * l113;	/*Scan Line*/
	void * l114;	/*Scan Line*/
	void * l115;	/*Scan Line*/
	void * l116;	/*Scan Line*/
	void * l117;	/*Scan Line*/
	void * l118;	/*Scan Line*/
	void * l119;	/*Scan Line*/
	void * l120;	/*Scan Line*/
	void * l121;	/*Scan Line*/
	void * l122;	/*Scan Line*/
	void * l123;	/*Scan Line*/
	void * l124;	/*Scan Line*/
	void * l125;	/*Scan Line*/
	void * l126;	/*Scan Line*/
	void * l127;	/*Scan Line*/
	void * l128;	/*Scan Line*/
	void * l129;	/*Scan Line*/
	void * l130;	/*Scan Line*/
	void * l131;	/*Scan Line*/
	void * l132;	/*Scan Line*/
	void * l133;	/*Scan Line*/
	void * l134;	/*Scan Line*/
	void * l135;	/*Scan Line*/
	void * l136;	/*Scan Line*/
	void * l137;	/*Scan Line*/
	void * l138;	/*Scan Line*/
	void * l139;	/*Scan Line*/
	void * l140;	/*Scan Line*/
	void * l141;	/*Scan Line*/
	void * l142;	/*Scan Line*/
	void * l143;	/*Scan Line*/
	void * l144;	/*Scan Line*/
	void * l145;	/*Scan Line*/
	void * l146;	/*Scan Line*/
	void * l147;	/*Scan Line*/
	void * l148;	/*Scan Line*/
	void * l149;	/*Scan Line*/
	void * l150;	/*Scan Line*/
	void * l151;	/*Scan Line*/
	void * l152;	/*Scan Line*/
	void * l153;	/*Scan Line*/
	void * l154;	/*Scan Line*/
	void * l155;	/*Scan Line*/
	void * l156;	/*Scan Line*/
	void * l157;	/*Scan Line*/
	void * l158;	/*Scan Line*/
	void * l159;	/*Scan Line*/
	void * l160;	/*Scan Line*/
	void * l161;	/*Scan Line*/
	void * l162;	/*Scan Line*/
	void * l163;	/*Scan Line*/
	void * l164;	/*Scan Line*/
	void * l165;	/*Scan Line*/
	void * l166;	/*Scan Line*/
	void * l167;	/*Scan Line*/
	void * l168;	/*Scan Line*/
	void * l169;	/*Scan Line*/
	void * l170;	/*Scan Line*/
	void * l171;	/*Scan Line*/
	void * l172;	/*Scan Line*/
	void * l173;	/*Scan Line*/
	void * l174;	/*Scan Line*/
	void * l175;	/*Scan Line*/
	void * l176;	/*Scan Line*/
	void * l177;	/*Scan Line*/
	void * l178;	/*Scan Line*/
	void * l179;	/*Scan Line*/
	void * l180;	/*Scan Line*/
	void * l181;	/*Scan Line*/
	void * l182;	/*Scan Line*/
	void * l183;	/*Scan Line*/
	void * l184;	/*Scan Line*/
	void * l185;	/*Scan Line*/
	void * l186;	/*Scan Line*/
	void * l187;	/*Scan Line*/
	void * l188;	/*Scan Line*/
	void * l189;	/*Scan Line*/
	void * l190;	/*Scan Line*/
	void * l191;	/*Scan Line*/
	void * l192;	/*Scan Line*/
	void * l193;	/*Scan Line*/
	void * l194;	/*Scan Line*/
	void * l195;	/*Scan Line*/
	void * l196;	/*Scan Line*/
	void * l197;	/*Scan Line*/
	void * l198;	/*Scan Line*/
	void * l199;	/*Scan Line*/
	void * l200;	/*Scan Line*/
	void * l201;	/*Scan Line*/
	void * l202;	/*Scan Line*/
	void * l203;	/*Scan Line*/
	void * l204;	/*Scan Line*/
	void * l205;	/*Scan Line*/
	void * l206;	/*Scan Line*/
	void * l207;	/*Scan Line*/
	void * l208;	/*Scan Line*/
	void * l209;	/*Scan Line*/
	void * l210;	/*Scan Line*/
	void * l211;	/*Scan Line*/
	void * l212;	/*Scan Line*/
	void * l213;	/*Scan Line*/
	void * l214;	/*Scan Line*/
	void * l215;	/*Scan Line*/
	void * l216;	/*Scan Line*/
	void * l217;	/*Scan Line*/
	void * l218;	/*Scan Line*/
	void * l219;	/*Scan Line*/
	void * l220;	/*Scan Line*/
	void * l221;	/*Scan Line*/
	void * l222;	/*Scan Line*/
	void * l223;	/*Scan Line*/
	void * l224;	/*Scan Line*/
	void * l225;	/*Scan Line*/
	void * l226;	/*Scan Line*/
	void * l227;	/*Scan Line*/
	void * l228;	/*Scan Line*/
	void * l229;	/*Scan Line*/
	void * l230;	/*Scan Line*/
	void * l231;	/*Scan Line*/
	void * l232;	/*Scan Line*/
	void * l233;	/*Scan Line*/
	void * l234;	/*Scan Line*/
	void * l235;	/*Scan Line*/
	void * l236;	/*Scan Line*/
	void * l237;	/*Scan Line*/
	void * l238;	/*Scan Line*/
	void * l239;	/*Scan Line*/
	void * l240;	/*Scan Line*/
	void * l241;	/*Scan Line*/
	void * l242;	/*Scan Line*/
	void * l243;	/*Scan Line*/
	void * l244;	/*Scan Line*/
	void * l245;	/*Scan Line*/
	void * l246;	/*Scan Line*/
	void * l247;	/*Scan Line*/
	void * l248;	/*Scan Line*/
	void * l249;	/*Scan Line*/
	void * l250;	/*Scan Line*/
	void * l251;	/*Scan Line*/
	void * l252;	/*Scan Line*/
	void * l253;	/*Scan Line*/
	void * l254;	/*Scan Line*/
	void * l255;	/*Scan Line*/
	void * l256;	/*Scan Line*/
	void * l257;	/*Scan Line*/
	void * l258;	/*Scan Line*/
	void * l259;	/*Scan Line*/
	void * l260;	/*Scan Line*/
	void * l261;	/*Scan Line*/
	void * l262;	/*Scan Line*/
	void * l263;	/*Scan Line*/
	void * l264;	/*Scan Line*/
	void * l265;	/*Scan Line*/
	void * l266;	/*Scan Line*/
	void * l267;	/*Scan Line*/
	void * l268;	/*Scan Line*/
	void * l269;	/*Scan Line*/
	void * l270;	/*Scan Line*/
	void * l271;	/*Scan Line*/
	void * l272;	/*Scan Line*/
	void * l273;	/*Scan Line*/
	void * l274;	/*Scan Line*/
	void * l275;	/*Scan Line*/
	void * l276;	/*Scan Line*/
	void * l277;	/*Scan Line*/
	void * l278;	/*Scan Line*/
	void * l279;	/*Scan Line*/
	void * l280;	/*Scan Line*/
	void * l281;	/*Scan Line*/
	void * l282;	/*Scan Line*/
	void * l283;	/*Scan Line*/
	void * l284;	/*Scan Line*/
	void * l285;	/*Scan Line*/
	void * l286;	/*Scan Line*/
	void * l287;	/*Scan Line*/
	void * l288;	/*Scan Line*/
	void * l289;	/*Scan Line*/
	void * l290;	/*Scan Line*/
	void * l291;	/*Scan Line*/
	void * l292;	/*Scan Line*/
	void * l293;	/*Scan Line*/
	void * l294;	/*Scan Line*/
	void * l295;	/*Scan Line*/
	void * l296;	/*Scan Line*/
	void * l297;	/*Scan Line*/
	void * l298;	/*Scan Line*/
	void * l299;	/*Scan Line*/
	void * l300;	/*Scan Line*/
	void * l301;	/*Scan Line*/
	void * l302;	/*Scan Line*/
	void * l303;	/*Scan Line*/
	void * l304;	/*Scan Line*/
	void * l305;	/*Scan Line*/
	void * l306;	/*Scan Line*/
	void * l307;	/*Scan Line*/
	void * l308;	/*Scan Line*/
	void * l309;	/*Scan Line*/
	void * l310;	/*Scan Line*/
	void * l311;	/*Scan Line*/
	void * l312;	/*Scan Line*/
	void * l313;	/*Scan Line*/
	void * l314;	/*Scan Line*/
	void * l315;	/*Scan Line*/
	void * l316;	/*Scan Line*/
	void * l317;	/*Scan Line*/
	void * l318;	/*Scan Line*/
	void * l319;	/*Scan Line*/
	void * l320;	/*Scan Line*/
	void * l321;	/*Scan Line*/
	void * l322;	/*Scan Line*/
	void * l323;	/*Scan Line*/
	void * l324;	/*Scan Line*/
	void * l325;	/*Scan Line*/
	void * l326;	/*Scan Line*/
	void * l327;	/*Scan Line*/
	void * l328;	/*Scan Line*/
	void * l329;	/*Scan Line*/
	void * l330;	/*Scan Line*/
	void * l331;	/*Scan Line*/
	void * l332;	/*Scan Line*/
	void * l333;	/*Scan Line*/
	void * l334;	/*Scan Line*/
	void * l335;	/*Scan Line*/
	void * l336;	/*Scan Line*/
	void * l337;	/*Scan Line*/
	void * l338;	/*Scan Line*/
	void * l339;	/*Scan Line*/
	void * l340;	/*Scan Line*/
	void * l341;	/*Scan Line*/
	void * l342;	/*Scan Line*/
	void * l343;	/*Scan Line*/
	void * l344;	/*Scan Line*/
	void * l345;	/*Scan Line*/
	void * l346;	/*Scan Line*/
	void * l347;	/*Scan Line*/
	void * l348;	/*Scan Line*/
	void * l349;	/*Scan Line*/
	void * l350;	/*Scan Line*/
	void * l351;	/*Scan Line*/
	void * l352;	/*Scan Line*/
	void * l353;	/*Scan Line*/
	void * l354;	/*Scan Line*/
	void * l355;	/*Scan Line*/
	void * l356;	/*Scan Line*/
	void * l357;	/*Scan Line*/
	void * l358;	/*Scan Line*/
	void * l359;	/*Scan Line*/
	void * l360;	/*Scan Line*/
	void * l361;	/*Scan Line*/
	void * l362;	/*Scan Line*/
	void * l363;	/*Scan Line*/
	void * l364;	/*Scan Line*/
	void * l365;	/*Scan Line*/
	void * l366;	/*Scan Line*/
	void * l367;	/*Scan Line*/
	void * l368;	/*Scan Line*/
	void * l369;	/*Scan Line*/
	void * l370;	/*Scan Line*/
	void * l371;	/*Scan Line*/
	void * l372;	/*Scan Line*/
	void * l373;	/*Scan Line*/
	void * l374;	/*Scan Line*/
	void * l375;	/*Scan Line*/
	void * l376;	/*Scan Line*/
	void * l377;	/*Scan Line*/
	void * l378;	/*Scan Line*/
	void * l379;	/*Scan Line*/
	void * l380;	/*Scan Line*/
	void * l381;	/*Scan Line*/
	void * l382;	/*Scan Line*/
	void * l383;	/*Scan Line*/
	void * l384;	/*Scan Line*/
	void * l385;	/*Scan Line*/
	void * l386;	/*Scan Line*/
	void * l387;	/*Scan Line*/
	void * l388;	/*Scan Line*/
	void * l389;	/*Scan Line*/
	void * l390;	/*Scan Line*/
	void * l391;	/*Scan Line*/
	void * l392;	/*Scan Line*/
	void * l393;	/*Scan Line*/
	void * l394;	/*Scan Line*/
	void * l395;	/*Scan Line*/
	void * l396;	/*Scan Line*/
	void * l397;	/*Scan Line*/
	void * l398;	/*Scan Line*/
	void * l399;	/*Scan Line*/
	void * l400;	/*Scan Line*/
	void * l401;	/*Scan Line*/
	void * l402;	/*Scan Line*/
	void * l403;	/*Scan Line*/
	void * l404;	/*Scan Line*/
	void * l405;	/*Scan Line*/
	void * l406;	/*Scan Line*/
	void * l407;	/*Scan Line*/
	void * l408;	/*Scan Line*/
	void * l409;	/*Scan Line*/
	void * l410;	/*Scan Line*/
	void * l411;	/*Scan Line*/
	void * l412;	/*Scan Line*/
	void * l413;	/*Scan Line*/
	void * l414;	/*Scan Line*/
	void * l415;	/*Scan Line*/
	void * l416;	/*Scan Line*/
	void * l417;	/*Scan Line*/
	void * l418;	/*Scan Line*/
	void * l419;	/*Scan Line*/
	void * l420;	/*Scan Line*/
	void * l421;	/*Scan Line*/
	void * l422;	/*Scan Line*/
	void * l423;	/*Scan Line*/
	void * l424;	/*Scan Line*/
	void * l425;	/*Scan Line*/
	void * l426;	/*Scan Line*/
	void * l427;	/*Scan Line*/
	void * l428;	/*Scan Line*/
	void * l429;	/*Scan Line*/
	void * l430;	/*Scan Line*/
	void * l431;	/*Scan Line*/
	void * l432;	/*Scan Line*/
	void * l433;	/*Scan Line*/
	void * l434;	/*Scan Line*/
	void * l435;	/*Scan Line*/
	void * l436;	/*Scan Line*/
	void * l437;	/*Scan Line*/
	void * l438;	/*Scan Line*/
	void * l439;	/*Scan Line*/
	void * l440;	/*Scan Line*/
	void * l441;	/*Scan Line*/
	void * l442;	/*Scan Line*/
	void * l443;	/*Scan Line*/
	void * l444;	/*Scan Line*/
	void * l445;	/*Scan Line*/
	void * l446;	/*Scan Line*/
	void * l447;	/*Scan Line*/
	void * l448;	/*Scan Line*/
	void * l449;	/*Scan Line*/
	void * l450;	/*Scan Line*/
	void * l451;	/*Scan Line*/
	void * l452;	/*Scan Line*/
	void * l453;	/*Scan Line*/
	void * l454;	/*Scan Line*/
	void * l455;	/*Scan Line*/
	void * l456;	/*Scan Line*/
	void * l457;	/*Scan Line*/
	void * l458;	/*Scan Line*/
	void * l459;	/*Scan Line*/
	void * l460;	/*Scan Line*/
	void * l461;	/*Scan Line*/
	void * l462;	/*Scan Line*/
	void * l463;	/*Scan Line*/
	void * l464;	/*Scan Line*/
	void * l465;	/*Scan Line*/
	void * l466;	/*Scan Line*/
	void * l467;	/*Scan Line*/
	void * l468;	/*Scan Line*/
	void * l469;	/*Scan Line*/
	void * l470;	/*Scan Line*/
	void * l471;	/*Scan Line*/
	void * l472;	/*Scan Line*/
	void * l473;	/*Scan Line*/
	void * l474;	/*Scan Line*/
	void * l475;	/*Scan Line*/
	void * l476;	/*Scan Line*/
	void * l477;	/*Scan Line*/
	void * l478;	/*Scan Line*/
	void * l479;	/*Scan Line*/
	void * l480;	/*Scan Line*/
	void * l481;	/*Scan Line*/
	void * l482;	/*Scan Line*/
	void * l483;	/*Scan Line*/
	void * l484;	/*Scan Line*/
	void * l485;	/*Scan Line*/
	void * l486;	/*Scan Line*/
	void * l487;	/*Scan Line*/
	void * l488;	/*Scan Line*/
	void * l489;	/*Scan Line*/
	void * l490;	/*Scan Line*/
	void * l491;	/*Scan Line*/
	void * l492;	/*Scan Line*/
	void * l493;	/*Scan Line*/
	void * l494;	/*Scan Line*/
	void * l495;	/*Scan Line*/
	void * l496;	/*Scan Line*/
	void * l497;	/*Scan Line*/
	void * l498;	/*Scan Line*/
	void * l499;	/*Scan Line*/
	void * l500;	/*Scan Line*/
	void * l501;	/*Scan Line*/
	void * l502;	/*Scan Line*/
	void * l503;	/*Scan Line*/
	void * l504;	/*Scan Line*/
	void * l505;	/*Scan Line*/
	void * l506;	/*Scan Line*/
	void * l507;	/*Scan Line*/
	void * l508;	/*Scan Line*/
	void * l509;	/*Scan Line*/
	void * l510;	/*Scan Line*/
	void * l511;	/*Scan Line*/
	void * l512;	/*Scan Line*/
	void * l513;	/*Scan Line*/
	void * l514;	/*Scan Line*/
	void * l515;	/*Scan Line*/
	void * l516;	/*Scan Line*/
	void * l517;	/*Scan Line*/
	void * l518;	/*Scan Line*/
	void * l519;	/*Scan Line*/
	void * l520;	/*Scan Line*/
	void * l521;	/*Scan Line*/
	void * l522;	/*Scan Line*/
	void * l523;	/*Scan Line*/
	void * l524;	/*Scan Line*/
	void * l525;	/*Scan Line*/
	void * l526;	/*Scan Line*/
	void * l527;	/*Scan Line*/
	void * l528;	/*Scan Line*/
	void * l529;	/*Scan Line*/
	void * l530;	/*Scan Line*/
	void * l531;	/*Scan Line*/
	void * l532;	/*Scan Line*/
	void * l533;	/*Scan Line*/
	void * l534;	/*Scan Line*/
	void * l535;	/*Scan Line*/
	void * l536;	/*Scan Line*/
	void * l537;	/*Scan Line*/
	void * l538;	/*Scan Line*/
	void * l539;	/*Scan Line*/
	void * l540;	/*Scan Line*/
	void * l541;	/*Scan Line*/
	void * l542;	/*Scan Line*/
	void * l543;	/*Scan Line*/
	void * l544;	/*Scan Line*/
	void * l545;	/*Scan Line*/
	void * l546;	/*Scan Line*/
	void * l547;	/*Scan Line*/
	void * l548;	/*Scan Line*/
	void * l549;	/*Scan Line*/
	void * l550;	/*Scan Line*/
	void * l551;	/*Scan Line*/
	void * l552;	/*Scan Line*/
	void * l553;	/*Scan Line*/
	void * l554;	/*Scan Line*/
	void * l555;	/*Scan Line*/
	void * l556;	/*Scan Line*/
	void * l557;	/*Scan Line*/
	void * l558;	/*Scan Line*/
	void * l559;	/*Scan Line*/
	void * l560;	/*Scan Line*/
	void * l561;	/*Scan Line*/
	void * l562;	/*Scan Line*/
	void * l563;	/*Scan Line*/
	void * l564;	/*Scan Line*/
	void * l565;	/*Scan Line*/
	void * l566;	/*Scan Line*/
	void * l567;	/*Scan Line*/
	void * l568;	/*Scan Line*/
	void * l569;	/*Scan Line*/
	void * l570;	/*Scan Line*/
	void * l571;	/*Scan Line*/
	void * l572;	/*Scan Line*/
	void * l573;	/*Scan Line*/
	void * l574;	/*Scan Line*/
	void * l575;	/*Scan Line*/
	void * l576;	/*Scan Line*/
	void * l577;	/*Scan Line*/
	void * l578;	/*Scan Line*/
	void * l579;	/*Scan Line*/
	void * l580;	/*Scan Line*/
	void * l581;	/*Scan Line*/
	void * l582;	/*Scan Line*/
	void * l583;	/*Scan Line*/
	void * l584;	/*Scan Line*/
	void * l585;	/*Scan Line*/
	void * l586;	/*Scan Line*/
	void * l587;	/*Scan Line*/
	void * l588;	/*Scan Line*/
	void * l589;	/*Scan Line*/
	void * l590;	/*Scan Line*/
	void * l591;	/*Scan Line*/
	void * l592;	/*Scan Line*/
	void * l593;	/*Scan Line*/
	void * l594;	/*Scan Line*/
	void * l595;	/*Scan Line*/
	void * l596;	/*Scan Line*/
	void * l597;	/*Scan Line*/
	void * l598;	/*Scan Line*/
	void * l599;	/*Scan Line*/
	void * l600;	/*Scan Line*/
	void * l601;	/*Scan Line*/
	void * l602;	/*Scan Line*/
	void * l603;	/*Scan Line*/
	void * l604;	/*Scan Line*/
	void * l605;	/*Scan Line*/
	void * l606;	/*Scan Line*/
	void * l607;	/*Scan Line*/
	void * l608;	/*Scan Line*/
	void * l609;	/*Scan Line*/
	void * l610;	/*Scan Line*/
	void * l611;	/*Scan Line*/
	void * l612;	/*Scan Line*/
	void * l613;	/*Scan Line*/
	void * l614;	/*Scan Line*/
	void * l615;	/*Scan Line*/
	void * l616;	/*Scan Line*/
	void * l617;	/*Scan Line*/
	void * l618;	/*Scan Line*/
	void * l619;	/*Scan Line*/
	void * l620;	/*Scan Line*/
	void * l621;	/*Scan Line*/
	void * l622;	/*Scan Line*/
	void * l623;	/*Scan Line*/
	void * l624;	/*Scan Line*/
	void * l625;	/*Scan Line*/
	void * l626;	/*Scan Line*/
	void * l627;	/*Scan Line*/
	void * l628;	/*Scan Line*/
	void * l629;	/*Scan Line*/
	void * l630;	/*Scan Line*/
	void * l631;	/*Scan Line*/
	void * l632;	/*Scan Line*/
	void * l633;	/*Scan Line*/
	void * l634;	/*Scan Line*/
	void * l635;	/*Scan Line*/
	void * l636;	/*Scan Line*/
	void * l637;	/*Scan Line*/
	void * l638;	/*Scan Line*/
	void * l639;	/*Scan Line*/
	void * l640;	/*Scan Line*/
	void * l641;	/*Scan Line*/
	void * l642;	/*Scan Line*/
	void * l643;	/*Scan Line*/
	void * l644;	/*Scan Line*/
	void * l645;	/*Scan Line*/
	void * l646;	/*Scan Line*/
	void * l647;	/*Scan Line*/
	void * l648;	/*Scan Line*/
	void * l649;	/*Scan Line*/
	void * l650;	/*Scan Line*/
	void * l651;	/*Scan Line*/
	void * l652;	/*Scan Line*/
	void * l653;	/*Scan Line*/
	void * l654;	/*Scan Line*/
	void * l655;	/*Scan Line*/
	void * l656;	/*Scan Line*/
	void * l657;	/*Scan Line*/
	void * l658;	/*Scan Line*/
	void * l659;	/*Scan Line*/
	void * l660;	/*Scan Line*/
	void * l661;	/*Scan Line*/
	void * l662;	/*Scan Line*/
	void * l663;	/*Scan Line*/
	void * l664;	/*Scan Line*/
	void * l665;	/*Scan Line*/
	void * l666;	/*Scan Line*/
	void * l667;	/*Scan Line*/
	void * l668;	/*Scan Line*/
	void * l669;	/*Scan Line*/
	void * l670;	/*Scan Line*/
	void * l671;	/*Scan Line*/
	void * l672;	/*Scan Line*/
	void * l673;	/*Scan Line*/
	void * l674;	/*Scan Line*/
	void * l675;	/*Scan Line*/
	void * l676;	/*Scan Line*/
	void * l677;	/*Scan Line*/
	void * l678;	/*Scan Line*/
	void * l679;	/*Scan Line*/
	void * l680;	/*Scan Line*/
	void * l681;	/*Scan Line*/
	void * l682;	/*Scan Line*/
	void * l683;	/*Scan Line*/
	void * l684;	/*Scan Line*/
	void * l685;	/*Scan Line*/
	void * l686;	/*Scan Line*/
	void * l687;	/*Scan Line*/
	void * l688;	/*Scan Line*/
	void * l689;	/*Scan Line*/
	void * l690;	/*Scan Line*/
	void * l691;	/*Scan Line*/
	void * l692;	/*Scan Line*/
	void * l693;	/*Scan Line*/
	void * l694;	/*Scan Line*/
	void * l695;	/*Scan Line*/
	void * l696;	/*Scan Line*/
	void * l697;	/*Scan Line*/
	void * l698;	/*Scan Line*/
	void * l699;	/*Scan Line*/
	void * l700;	/*Scan Line*/
	void * l701;	/*Scan Line*/
	void * l702;	/*Scan Line*/
	void * l703;	/*Scan Line*/
	void * l704;	/*Scan Line*/
	void * l705;	/*Scan Line*/
	void * l706;	/*Scan Line*/
	void * l707;	/*Scan Line*/
	void * l708;	/*Scan Line*/
	void * l709;	/*Scan Line*/
	void * l710;	/*Scan Line*/
	void * l711;	/*Scan Line*/
	void * l712;	/*Scan Line*/
	void * l713;	/*Scan Line*/
	void * l714;	/*Scan Line*/
	void * l715;	/*Scan Line*/
	void * l716;	/*Scan Line*/
	void * l717;	/*Scan Line*/
	void * l718;	/*Scan Line*/
	void * l719;	/*Scan Line*/
	void * l720;	/*Scan Line*/
	void * l721;	/*Scan Line*/
	void * l722;	/*Scan Line*/
	void * l723;	/*Scan Line*/
	void * l724;	/*Scan Line*/
	void * l725;	/*Scan Line*/
	void * l726;	/*Scan Line*/
	void * l727;	/*Scan Line*/
	void * l728;	/*Scan Line*/
	void * l729;	/*Scan Line*/
	void * l730;	/*Scan Line*/
	void * l731;	/*Scan Line*/
	void * l732;	/*Scan Line*/
	void * l733;	/*Scan Line*/
	void * l734;	/*Scan Line*/
	void * l735;	/*Scan Line*/
	void * l736;	/*Scan Line*/
	void * l737;	/*Scan Line*/
	void * l738;	/*Scan Line*/
	void * l739;	/*Scan Line*/
	void * l740;	/*Scan Line*/
	void * l741;	/*Scan Line*/
	void * l742;	/*Scan Line*/
	void * l743;	/*Scan Line*/
	void * l744;	/*Scan Line*/
	void * l745;	/*Scan Line*/
	void * l746;	/*Scan Line*/
	void * l747;	/*Scan Line*/
	void * l748;	/*Scan Line*/
	void * l749;	/*Scan Line*/
	void * l750;	/*Scan Line*/
	void * l751;	/*Scan Line*/
	void * l752;	/*Scan Line*/
	void * l753;	/*Scan Line*/
	void * l754;	/*Scan Line*/
	void * l755;	/*Scan Line*/
	void * l756;	/*Scan Line*/
	void * l757;	/*Scan Line*/
	void * l758;	/*Scan Line*/
	void * l759;	/*Scan Line*/
	void * l760;	/*Scan Line*/
	void * l761;	/*Scan Line*/
	void * l762;	/*Scan Line*/
	void * l763;	/*Scan Line*/
	void * l764;	/*Scan Line*/
	void * l765;	/*Scan Line*/
	void * l766;	/*Scan Line*/
	void * l767;	/*Scan Line*/
	void * l768;	/*Scan Line*/
	void * l769;	/*Scan Line*/
	void * l770;	/*Scan Line*/
	void * l771;	/*Scan Line*/
	void * l772;	/*Scan Line*/
	void * l773;	/*Scan Line*/
	void * l774;	/*Scan Line*/
	void * l775;	/*Scan Line*/
	void * l776;	/*Scan Line*/
	void * l777;	/*Scan Line*/
	void * l778;	/*Scan Line*/
	void * l779;	/*Scan Line*/
	void * l780;	/*Scan Line*/
	void * l781;	/*Scan Line*/
	void * l782;	/*Scan Line*/
	void * l783;	/*Scan Line*/
	void * l784;	/*Scan Line*/
	void * l785;	/*Scan Line*/
	void * l786;	/*Scan Line*/
	void * l787;	/*Scan Line*/
	void * l788;	/*Scan Line*/
	void * l789;	/*Scan Line*/
	void * l790;	/*Scan Line*/
	void * l791;	/*Scan Line*/
	void * l792;	/*Scan Line*/
	void * l793;	/*Scan Line*/
	void * l794;	/*Scan Line*/
	void * l795;	/*Scan Line*/
	void * l796;	/*Scan Line*/
	void * l797;	/*Scan Line*/
	void * l798;	/*Scan Line*/
	void * l799;	/*Scan Line*/
	void * l800;	/*Scan Line*/
	void * l801;	/*Scan Line*/
	void * l802;	/*Scan Line*/
	void * l803;	/*Scan Line*/
	void * l804;	/*Scan Line*/
	void * l805;	/*Scan Line*/
	void * l806;	/*Scan Line*/
	void * l807;	/*Scan Line*/
	void * l808;	/*Scan Line*/
	void * l809;	/*Scan Line*/
	void * l810;	/*Scan Line*/
	void * l811;	/*Scan Line*/
	void * l812;	/*Scan Line*/
	void * l813;	/*Scan Line*/
	void * l814;	/*Scan Line*/
	void * l815;	/*Scan Line*/
	void * l816;	/*Scan Line*/
	void * l817;	/*Scan Line*/
	void * l818;	/*Scan Line*/
	void * l819;	/*Scan Line*/
	void * l820;	/*Scan Line*/
	void * l821;	/*Scan Line*/
	void * l822;	/*Scan Line*/
	void * l823;	/*Scan Line*/
	void * l824;	/*Scan Line*/
	void * l825;	/*Scan Line*/
	void * l826;	/*Scan Line*/
	void * l827;	/*Scan Line*/
	void * l828;	/*Scan Line*/
	void * l829;	/*Scan Line*/
	void * l830;	/*Scan Line*/
	void * l831;	/*Scan Line*/
	void * l832;	/*Scan Line*/
	void * l833;	/*Scan Line*/
	void * l834;	/*Scan Line*/
	void * l835;	/*Scan Line*/
	void * l836;	/*Scan Line*/
	void * l837;	/*Scan Line*/
	void * l838;	/*Scan Line*/
	void * l839;	/*Scan Line*/
	void * l840;	/*Scan Line*/
	void * l841;	/*Scan Line*/
	void * l842;	/*Scan Line*/
	void * l843;	/*Scan Line*/
	void * l844;	/*Scan Line*/
	void * l845;	/*Scan Line*/
	void * l846;	/*Scan Line*/
	void * l847;	/*Scan Line*/
	void * l848;	/*Scan Line*/
	void * l849;	/*Scan Line*/
	void * l850;	/*Scan Line*/
	void * l851;	/*Scan Line*/
	void * l852;	/*Scan Line*/
	void * l853;	/*Scan Line*/
	void * l854;	/*Scan Line*/
	void * l855;	/*Scan Line*/
	void * l856;	/*Scan Line*/
	void * l857;	/*Scan Line*/
	void * l858;	/*Scan Line*/
	void * l859;	/*Scan Line*/
	void * l860;	/*Scan Line*/
	void * l861;	/*Scan Line*/
	void * l862;	/*Scan Line*/
	void * l863;	/*Scan Line*/
	void * l864;	/*Scan Line*/
	void * l865;	/*Scan Line*/
	void * l866;	/*Scan Line*/
	void * l867;	/*Scan Line*/
	void * l868;	/*Scan Line*/
	void * l869;	/*Scan Line*/
	void * l870;	/*Scan Line*/
	void * l871;	/*Scan Line*/
	void * l872;	/*Scan Line*/
	void * l873;	/*Scan Line*/
	void * l874;	/*Scan Line*/
	void * l875;	/*Scan Line*/
	void * l876;	/*Scan Line*/
	void * l877;	/*Scan Line*/
	void * l878;	/*Scan Line*/
	void * l879;	/*Scan Line*/
	void * l880;	/*Scan Line*/
	void * l881;	/*Scan Line*/
	void * l882;	/*Scan Line*/
	void * l883;	/*Scan Line*/
	void * l884;	/*Scan Line*/
	void * l885;	/*Scan Line*/
	void * l886;	/*Scan Line*/
	void * l887;	/*Scan Line*/
	void * l888;	/*Scan Line*/
	void * l889;	/*Scan Line*/
	void * l890;	/*Scan Line*/
	void * l891;	/*Scan Line*/
	void * l892;	/*Scan Line*/
	void * l893;	/*Scan Line*/
	void * l894;	/*Scan Line*/
	void * l895;	/*Scan Line*/
	void * l896;	/*Scan Line*/
	void * l897;	/*Scan Line*/
	void * l898;	/*Scan Line*/
	void * l899;	/*Scan Line*/
	void * l900;	/*Scan Line*/
	void * l901;	/*Scan Line*/
	void * l902;	/*Scan Line*/
	void * l903;	/*Scan Line*/
	void * l904;	/*Scan Line*/
	void * l905;	/*Scan Line*/
	void * l906;	/*Scan Line*/
	void * l907;	/*Scan Line*/
	void * l908;	/*Scan Line*/
	void * l909;	/*Scan Line*/
	void * l910;	/*Scan Line*/
	void * l911;	/*Scan Line*/
	void * l912;	/*Scan Line*/
	void * l913;	/*Scan Line*/
	void * l914;	/*Scan Line*/
	void * l915;	/*Scan Line*/
	void * l916;	/*Scan Line*/
	void * l917;	/*Scan Line*/
	void * l918;	/*Scan Line*/
	void * l919;	/*Scan Line*/
	void * l920;	/*Scan Line*/
	void * l921;	/*Scan Line*/
	void * l922;	/*Scan Line*/
	void * l923;	/*Scan Line*/
	void * l924;	/*Scan Line*/
	void * l925;	/*Scan Line*/
	void * l926;	/*Scan Line*/
	void * l927;	/*Scan Line*/
	void * l928;	/*Scan Line*/
	void * l929;	/*Scan Line*/
	void * l930;	/*Scan Line*/
	void * l931;	/*Scan Line*/
	void * l932;	/*Scan Line*/
	void * l933;	/*Scan Line*/
	void * l934;	/*Scan Line*/
	void * l935;	/*Scan Line*/
	void * l936;	/*Scan Line*/
	void * l937;	/*Scan Line*/
	void * l938;	/*Scan Line*/
	void * l939;	/*Scan Line*/
	void * l940;	/*Scan Line*/
	void * l941;	/*Scan Line*/
	void * l942;	/*Scan Line*/
	void * l943;	/*Scan Line*/
	void * l944;	/*Scan Line*/
	void * l945;	/*Scan Line*/
	void * l946;	/*Scan Line*/
	void * l947;	/*Scan Line*/
	void * l948;	/*Scan Line*/
	void * l949;	/*Scan Line*/
	void * l950;	/*Scan Line*/
	void * l951;	/*Scan Line*/
	void * l952;	/*Scan Line*/
	void * l953;	/*Scan Line*/
	void * l954;	/*Scan Line*/
	void * l955;	/*Scan Line*/
	void * l956;	/*Scan Line*/
	void * l957;	/*Scan Line*/
	void * l958;	/*Scan Line*/
	void * l959;	/*Scan Line*/
	void * l960;	/*Scan Line*/
	void * l961;	/*Scan Line*/
	void * l962;	/*Scan Line*/
	void * l963;	/*Scan Line*/
	void * l964;	/*Scan Line*/
	void * l965;	/*Scan Line*/
	void * l966;	/*Scan Line*/
	void * l967;	/*Scan Line*/
	void * l968;	/*Scan Line*/
	void * l969;	/*Scan Line*/
	void * l970;	/*Scan Line*/
	void * l971;	/*Scan Line*/
	void * l972;	/*Scan Line*/
	void * l973;	/*Scan Line*/
	void * l974;	/*Scan Line*/
	void * l975;	/*Scan Line*/
	void * l976;	/*Scan Line*/
	void * l977;	/*Scan Line*/
	void * l978;	/*Scan Line*/
	void * l979;	/*Scan Line*/
	void * l980;	/*Scan Line*/
	void * l981;	/*Scan Line*/
	void * l982;	/*Scan Line*/
	void * l983;	/*Scan Line*/
	void * l984;	/*Scan Line*/
	void * l985;	/*Scan Line*/
	void * l986;	/*Scan Line*/
	void * l987;	/*Scan Line*/
	void * l988;	/*Scan Line*/
	void * l989;	/*Scan Line*/
	void * l990;	/*Scan Line*/
	void * l991;	/*Scan Line*/
	void * l992;	/*Scan Line*/
	void * l993;	/*Scan Line*/
	void * l994;	/*Scan Line*/
	void * l995;	/*Scan Line*/
	void * l996;	/*Scan Line*/
	void * l997;	/*Scan Line*/
	void * l998;	/*Scan Line*/
	void * l999;	/*Scan Line*/
	void * l1000;	/*Scan Line*/
	void * l1001;	/*Scan Line*/
	void * l1002;	/*Scan Line*/
	void * l1003;	/*Scan Line*/
	void * l1004;	/*Scan Line*/
	void * l1005;	/*Scan Line*/
	void * l1006;	/*Scan Line*/
	void * l1007;	/*Scan Line*/
	void * l1008;	/*Scan Line*/
	void * l1009;	/*Scan Line*/
	void * l1010;	/*Scan Line*/
	void * l1011;	/*Scan Line*/
	void * l1012;	/*Scan Line*/
	void * l1013;	/*Scan Line*/
	void * l1014;	/*Scan Line*/
	void * l1015;	/*Scan Line*/
	void * l1016;	/*Scan Line*/
	void * l1017;	/*Scan Line*/
	void * l1018;	/*Scan Line*/
	void * l1019;	/*Scan Line*/
	void * l1020;	/*Scan Line*/
	void * l1021;	/*Scan Line*/
	void * l1022;	/*Scan Line*/
	void * l1023;	/*Scan Line*/
} imageRecord;
#define imageRecordNAME	0
#define imageRecordDESC	1
#define imageRecordASG	2
#define imageRecordSCAN	3
#define imageRecordPINI	4
#define imageRecordPHAS	5
#define imageRecordEVNT	6
#define imageRecordTSE	7
#define imageRecordTSEL	8
#define imageRecordDTYP	9
#define imageRecordDISV	10
#define imageRecordDISA	11
#define imageRecordSDIS	12
#define imageRecordMLOK	13
#define imageRecordMLIS	14
#define imageRecordDISP	15
#define imageRecordPROC	16
#define imageRecordSTAT	17
#define imageRecordSEVR	18
#define imageRecordNSTA	19
#define imageRecordNSEV	20
#define imageRecordACKS	21
#define imageRecordACKT	22
#define imageRecordDISS	23
#define imageRecordLCNT	24
#define imageRecordPACT	25
#define imageRecordPUTF	26
#define imageRecordRPRO	27
#define imageRecordASP	28
#define imageRecordPPN	29
#define imageRecordPPNN	30
#define imageRecordSPVT	31
#define imageRecordRSET	32
#define imageRecordDSET	33
#define imageRecordDPVT	34
#define imageRecordRDES	35
#define imageRecordLSET	36
#define imageRecordPRIO	37
#define imageRecordTPRO	38
#define imageRecordBKPT	39
#define imageRecordUDF	40
#define imageRecordTIME	41
#define imageRecordFLNK	42
#define imageRecordVERS	43
#define imageRecordENAB	44
#define imageRecordRATE	45
#define imageRecordPMTK	46
#define imageRecordVAL	47
#define imageRecordINP	48
#define imageRecordVXNM	49
#define imageRecordSIZE	50
#define imageRecordXRES	51
#define imageRecordYRES	52
#define imageRecordRXST	53
#define imageRecordRXSZ	54
#define imageRecordRYST	55
#define imageRecordRYSZ	56
#define imageRecordL0	57
#define imageRecordL1	58
#define imageRecordL2	59
#define imageRecordL3	60
#define imageRecordL4	61
#define imageRecordL5	62
#define imageRecordL6	63
#define imageRecordL7	64
#define imageRecordL8	65
#define imageRecordL9	66
#define imageRecordL10	67
#define imageRecordL11	68
#define imageRecordL12	69
#define imageRecordL13	70
#define imageRecordL14	71
#define imageRecordL15	72
#define imageRecordL16	73
#define imageRecordL17	74
#define imageRecordL18	75
#define imageRecordL19	76
#define imageRecordL20	77
#define imageRecordL21	78
#define imageRecordL22	79
#define imageRecordL23	80
#define imageRecordL24	81
#define imageRecordL25	82
#define imageRecordL26	83
#define imageRecordL27	84
#define imageRecordL28	85
#define imageRecordL29	86
#define imageRecordL30	87
#define imageRecordL31	88
#define imageRecordL32	89
#define imageRecordL33	90
#define imageRecordL34	91
#define imageRecordL35	92
#define imageRecordL36	93
#define imageRecordL37	94
#define imageRecordL38	95
#define imageRecordL39	96
#define imageRecordL40	97
#define imageRecordL41	98
#define imageRecordL42	99
#define imageRecordL43	100
#define imageRecordL44	101
#define imageRecordL45	102
#define imageRecordL46	103
#define imageRecordL47	104
#define imageRecordL48	105
#define imageRecordL49	106
#define imageRecordL50	107
#define imageRecordL51	108
#define imageRecordL52	109
#define imageRecordL53	110
#define imageRecordL54	111
#define imageRecordL55	112
#define imageRecordL56	113
#define imageRecordL57	114
#define imageRecordL58	115
#define imageRecordL59	116
#define imageRecordL60	117
#define imageRecordL61	118
#define imageRecordL62	119
#define imageRecordL63	120
#define imageRecordL64	121
#define imageRecordL65	122
#define imageRecordL66	123
#define imageRecordL67	124
#define imageRecordL68	125
#define imageRecordL69	126
#define imageRecordL70	127
#define imageRecordL71	128
#define imageRecordL72	129
#define imageRecordL73	130
#define imageRecordL74	131
#define imageRecordL75	132
#define imageRecordL76	133
#define imageRecordL77	134
#define imageRecordL78	135
#define imageRecordL79	136
#define imageRecordL80	137
#define imageRecordL81	138
#define imageRecordL82	139
#define imageRecordL83	140
#define imageRecordL84	141
#define imageRecordL85	142
#define imageRecordL86	143
#define imageRecordL87	144
#define imageRecordL88	145
#define imageRecordL89	146
#define imageRecordL90	147
#define imageRecordL91	148
#define imageRecordL92	149
#define imageRecordL93	150
#define imageRecordL94	151
#define imageRecordL95	152
#define imageRecordL96	153
#define imageRecordL97	154
#define imageRecordL98	155
#define imageRecordL99	156
#define imageRecordL100	157
#define imageRecordL101	158
#define imageRecordL102	159
#define imageRecordL103	160
#define imageRecordL104	161
#define imageRecordL105	162
#define imageRecordL106	163
#define imageRecordL107	164
#define imageRecordL108	165
#define imageRecordL109	166
#define imageRecordL110	167
#define imageRecordL111	168
#define imageRecordL112	169
#define imageRecordL113	170
#define imageRecordL114	171
#define imageRecordL115	172
#define imageRecordL116	173
#define imageRecordL117	174
#define imageRecordL118	175
#define imageRecordL119	176
#define imageRecordL120	177
#define imageRecordL121	178
#define imageRecordL122	179
#define imageRecordL123	180
#define imageRecordL124	181
#define imageRecordL125	182
#define imageRecordL126	183
#define imageRecordL127	184
#define imageRecordL128	185
#define imageRecordL129	186
#define imageRecordL130	187
#define imageRecordL131	188
#define imageRecordL132	189
#define imageRecordL133	190
#define imageRecordL134	191
#define imageRecordL135	192
#define imageRecordL136	193
#define imageRecordL137	194
#define imageRecordL138	195
#define imageRecordL139	196
#define imageRecordL140	197
#define imageRecordL141	198
#define imageRecordL142	199
#define imageRecordL143	200
#define imageRecordL144	201
#define imageRecordL145	202
#define imageRecordL146	203
#define imageRecordL147	204
#define imageRecordL148	205
#define imageRecordL149	206
#define imageRecordL150	207
#define imageRecordL151	208
#define imageRecordL152	209
#define imageRecordL153	210
#define imageRecordL154	211
#define imageRecordL155	212
#define imageRecordL156	213
#define imageRecordL157	214
#define imageRecordL158	215
#define imageRecordL159	216
#define imageRecordL160	217
#define imageRecordL161	218
#define imageRecordL162	219
#define imageRecordL163	220
#define imageRecordL164	221
#define imageRecordL165	222
#define imageRecordL166	223
#define imageRecordL167	224
#define imageRecordL168	225
#define imageRecordL169	226
#define imageRecordL170	227
#define imageRecordL171	228
#define imageRecordL172	229
#define imageRecordL173	230
#define imageRecordL174	231
#define imageRecordL175	232
#define imageRecordL176	233
#define imageRecordL177	234
#define imageRecordL178	235
#define imageRecordL179	236
#define imageRecordL180	237
#define imageRecordL181	238
#define imageRecordL182	239
#define imageRecordL183	240
#define imageRecordL184	241
#define imageRecordL185	242
#define imageRecordL186	243
#define imageRecordL187	244
#define imageRecordL188	245
#define imageRecordL189	246
#define imageRecordL190	247
#define imageRecordL191	248
#define imageRecordL192	249
#define imageRecordL193	250
#define imageRecordL194	251
#define imageRecordL195	252
#define imageRecordL196	253
#define imageRecordL197	254
#define imageRecordL198	255
#define imageRecordL199	256
#define imageRecordL200	257
#define imageRecordL201	258
#define imageRecordL202	259
#define imageRecordL203	260
#define imageRecordL204	261
#define imageRecordL205	262
#define imageRecordL206	263
#define imageRecordL207	264
#define imageRecordL208	265
#define imageRecordL209	266
#define imageRecordL210	267
#define imageRecordL211	268
#define imageRecordL212	269
#define imageRecordL213	270
#define imageRecordL214	271
#define imageRecordL215	272
#define imageRecordL216	273
#define imageRecordL217	274
#define imageRecordL218	275
#define imageRecordL219	276
#define imageRecordL220	277
#define imageRecordL221	278
#define imageRecordL222	279
#define imageRecordL223	280
#define imageRecordL224	281
#define imageRecordL225	282
#define imageRecordL226	283
#define imageRecordL227	284
#define imageRecordL228	285
#define imageRecordL229	286
#define imageRecordL230	287
#define imageRecordL231	288
#define imageRecordL232	289
#define imageRecordL233	290
#define imageRecordL234	291
#define imageRecordL235	292
#define imageRecordL236	293
#define imageRecordL237	294
#define imageRecordL238	295
#define imageRecordL239	296
#define imageRecordL240	297
#define imageRecordL241	298
#define imageRecordL242	299
#define imageRecordL243	300
#define imageRecordL244	301
#define imageRecordL245	302
#define imageRecordL246	303
#define imageRecordL247	304
#define imageRecordL248	305
#define imageRecordL249	306
#define imageRecordL250	307
#define imageRecordL251	308
#define imageRecordL252	309
#define imageRecordL253	310
#define imageRecordL254	311
#define imageRecordL255	312
#define imageRecordL256	313
#define imageRecordL257	314
#define imageRecordL258	315
#define imageRecordL259	316
#define imageRecordL260	317
#define imageRecordL261	318
#define imageRecordL262	319
#define imageRecordL263	320
#define imageRecordL264	321
#define imageRecordL265	322
#define imageRecordL266	323
#define imageRecordL267	324
#define imageRecordL268	325
#define imageRecordL269	326
#define imageRecordL270	327
#define imageRecordL271	328
#define imageRecordL272	329
#define imageRecordL273	330
#define imageRecordL274	331
#define imageRecordL275	332
#define imageRecordL276	333
#define imageRecordL277	334
#define imageRecordL278	335
#define imageRecordL279	336
#define imageRecordL280	337
#define imageRecordL281	338
#define imageRecordL282	339
#define imageRecordL283	340
#define imageRecordL284	341
#define imageRecordL285	342
#define imageRecordL286	343
#define imageRecordL287	344
#define imageRecordL288	345
#define imageRecordL289	346
#define imageRecordL290	347
#define imageRecordL291	348
#define imageRecordL292	349
#define imageRecordL293	350
#define imageRecordL294	351
#define imageRecordL295	352
#define imageRecordL296	353
#define imageRecordL297	354
#define imageRecordL298	355
#define imageRecordL299	356
#define imageRecordL300	357
#define imageRecordL301	358
#define imageRecordL302	359
#define imageRecordL303	360
#define imageRecordL304	361
#define imageRecordL305	362
#define imageRecordL306	363
#define imageRecordL307	364
#define imageRecordL308	365
#define imageRecordL309	366
#define imageRecordL310	367
#define imageRecordL311	368
#define imageRecordL312	369
#define imageRecordL313	370
#define imageRecordL314	371
#define imageRecordL315	372
#define imageRecordL316	373
#define imageRecordL317	374
#define imageRecordL318	375
#define imageRecordL319	376
#define imageRecordL320	377
#define imageRecordL321	378
#define imageRecordL322	379
#define imageRecordL323	380
#define imageRecordL324	381
#define imageRecordL325	382
#define imageRecordL326	383
#define imageRecordL327	384
#define imageRecordL328	385
#define imageRecordL329	386
#define imageRecordL330	387
#define imageRecordL331	388
#define imageRecordL332	389
#define imageRecordL333	390
#define imageRecordL334	391
#define imageRecordL335	392
#define imageRecordL336	393
#define imageRecordL337	394
#define imageRecordL338	395
#define imageRecordL339	396
#define imageRecordL340	397
#define imageRecordL341	398
#define imageRecordL342	399
#define imageRecordL343	400
#define imageRecordL344	401
#define imageRecordL345	402
#define imageRecordL346	403
#define imageRecordL347	404
#define imageRecordL348	405
#define imageRecordL349	406
#define imageRecordL350	407
#define imageRecordL351	408
#define imageRecordL352	409
#define imageRecordL353	410
#define imageRecordL354	411
#define imageRecordL355	412
#define imageRecordL356	413
#define imageRecordL357	414
#define imageRecordL358	415
#define imageRecordL359	416
#define imageRecordL360	417
#define imageRecordL361	418
#define imageRecordL362	419
#define imageRecordL363	420
#define imageRecordL364	421
#define imageRecordL365	422
#define imageRecordL366	423
#define imageRecordL367	424
#define imageRecordL368	425
#define imageRecordL369	426
#define imageRecordL370	427
#define imageRecordL371	428
#define imageRecordL372	429
#define imageRecordL373	430
#define imageRecordL374	431
#define imageRecordL375	432
#define imageRecordL376	433
#define imageRecordL377	434
#define imageRecordL378	435
#define imageRecordL379	436
#define imageRecordL380	437
#define imageRecordL381	438
#define imageRecordL382	439
#define imageRecordL383	440
#define imageRecordL384	441
#define imageRecordL385	442
#define imageRecordL386	443
#define imageRecordL387	444
#define imageRecordL388	445
#define imageRecordL389	446
#define imageRecordL390	447
#define imageRecordL391	448
#define imageRecordL392	449
#define imageRecordL393	450
#define imageRecordL394	451
#define imageRecordL395	452
#define imageRecordL396	453
#define imageRecordL397	454
#define imageRecordL398	455
#define imageRecordL399	456
#define imageRecordL400	457
#define imageRecordL401	458
#define imageRecordL402	459
#define imageRecordL403	460
#define imageRecordL404	461
#define imageRecordL405	462
#define imageRecordL406	463
#define imageRecordL407	464
#define imageRecordL408	465
#define imageRecordL409	466
#define imageRecordL410	467
#define imageRecordL411	468
#define imageRecordL412	469
#define imageRecordL413	470
#define imageRecordL414	471
#define imageRecordL415	472
#define imageRecordL416	473
#define imageRecordL417	474
#define imageRecordL418	475
#define imageRecordL419	476
#define imageRecordL420	477
#define imageRecordL421	478
#define imageRecordL422	479
#define imageRecordL423	480
#define imageRecordL424	481
#define imageRecordL425	482
#define imageRecordL426	483
#define imageRecordL427	484
#define imageRecordL428	485
#define imageRecordL429	486
#define imageRecordL430	487
#define imageRecordL431	488
#define imageRecordL432	489
#define imageRecordL433	490
#define imageRecordL434	491
#define imageRecordL435	492
#define imageRecordL436	493
#define imageRecordL437	494
#define imageRecordL438	495
#define imageRecordL439	496
#define imageRecordL440	497
#define imageRecordL441	498
#define imageRecordL442	499
#define imageRecordL443	500
#define imageRecordL444	501
#define imageRecordL445	502
#define imageRecordL446	503
#define imageRecordL447	504
#define imageRecordL448	505
#define imageRecordL449	506
#define imageRecordL450	507
#define imageRecordL451	508
#define imageRecordL452	509
#define imageRecordL453	510
#define imageRecordL454	511
#define imageRecordL455	512
#define imageRecordL456	513
#define imageRecordL457	514
#define imageRecordL458	515
#define imageRecordL459	516
#define imageRecordL460	517
#define imageRecordL461	518
#define imageRecordL462	519
#define imageRecordL463	520
#define imageRecordL464	521
#define imageRecordL465	522
#define imageRecordL466	523
#define imageRecordL467	524
#define imageRecordL468	525
#define imageRecordL469	526
#define imageRecordL470	527
#define imageRecordL471	528
#define imageRecordL472	529
#define imageRecordL473	530
#define imageRecordL474	531
#define imageRecordL475	532
#define imageRecordL476	533
#define imageRecordL477	534
#define imageRecordL478	535
#define imageRecordL479	536
#define imageRecordL480	537
#define imageRecordL481	538
#define imageRecordL482	539
#define imageRecordL483	540
#define imageRecordL484	541
#define imageRecordL485	542
#define imageRecordL486	543
#define imageRecordL487	544
#define imageRecordL488	545
#define imageRecordL489	546
#define imageRecordL490	547
#define imageRecordL491	548
#define imageRecordL492	549
#define imageRecordL493	550
#define imageRecordL494	551
#define imageRecordL495	552
#define imageRecordL496	553
#define imageRecordL497	554
#define imageRecordL498	555
#define imageRecordL499	556
#define imageRecordL500	557
#define imageRecordL501	558
#define imageRecordL502	559
#define imageRecordL503	560
#define imageRecordL504	561
#define imageRecordL505	562
#define imageRecordL506	563
#define imageRecordL507	564
#define imageRecordL508	565
#define imageRecordL509	566
#define imageRecordL510	567
#define imageRecordL511	568
#define imageRecordL512	569
#define imageRecordL513	570
#define imageRecordL514	571
#define imageRecordL515	572
#define imageRecordL516	573
#define imageRecordL517	574
#define imageRecordL518	575
#define imageRecordL519	576
#define imageRecordL520	577
#define imageRecordL521	578
#define imageRecordL522	579
#define imageRecordL523	580
#define imageRecordL524	581
#define imageRecordL525	582
#define imageRecordL526	583
#define imageRecordL527	584
#define imageRecordL528	585
#define imageRecordL529	586
#define imageRecordL530	587
#define imageRecordL531	588
#define imageRecordL532	589
#define imageRecordL533	590
#define imageRecordL534	591
#define imageRecordL535	592
#define imageRecordL536	593
#define imageRecordL537	594
#define imageRecordL538	595
#define imageRecordL539	596
#define imageRecordL540	597
#define imageRecordL541	598
#define imageRecordL542	599
#define imageRecordL543	600
#define imageRecordL544	601
#define imageRecordL545	602
#define imageRecordL546	603
#define imageRecordL547	604
#define imageRecordL548	605
#define imageRecordL549	606
#define imageRecordL550	607
#define imageRecordL551	608
#define imageRecordL552	609
#define imageRecordL553	610
#define imageRecordL554	611
#define imageRecordL555	612
#define imageRecordL556	613
#define imageRecordL557	614
#define imageRecordL558	615
#define imageRecordL559	616
#define imageRecordL560	617
#define imageRecordL561	618
#define imageRecordL562	619
#define imageRecordL563	620
#define imageRecordL564	621
#define imageRecordL565	622
#define imageRecordL566	623
#define imageRecordL567	624
#define imageRecordL568	625
#define imageRecordL569	626
#define imageRecordL570	627
#define imageRecordL571	628
#define imageRecordL572	629
#define imageRecordL573	630
#define imageRecordL574	631
#define imageRecordL575	632
#define imageRecordL576	633
#define imageRecordL577	634
#define imageRecordL578	635
#define imageRecordL579	636
#define imageRecordL580	637
#define imageRecordL581	638
#define imageRecordL582	639
#define imageRecordL583	640
#define imageRecordL584	641
#define imageRecordL585	642
#define imageRecordL586	643
#define imageRecordL587	644
#define imageRecordL588	645
#define imageRecordL589	646
#define imageRecordL590	647
#define imageRecordL591	648
#define imageRecordL592	649
#define imageRecordL593	650
#define imageRecordL594	651
#define imageRecordL595	652
#define imageRecordL596	653
#define imageRecordL597	654
#define imageRecordL598	655
#define imageRecordL599	656
#define imageRecordL600	657
#define imageRecordL601	658
#define imageRecordL602	659
#define imageRecordL603	660
#define imageRecordL604	661
#define imageRecordL605	662
#define imageRecordL606	663
#define imageRecordL607	664
#define imageRecordL608	665
#define imageRecordL609	666
#define imageRecordL610	667
#define imageRecordL611	668
#define imageRecordL612	669
#define imageRecordL613	670
#define imageRecordL614	671
#define imageRecordL615	672
#define imageRecordL616	673
#define imageRecordL617	674
#define imageRecordL618	675
#define imageRecordL619	676
#define imageRecordL620	677
#define imageRecordL621	678
#define imageRecordL622	679
#define imageRecordL623	680
#define imageRecordL624	681
#define imageRecordL625	682
#define imageRecordL626	683
#define imageRecordL627	684
#define imageRecordL628	685
#define imageRecordL629	686
#define imageRecordL630	687
#define imageRecordL631	688
#define imageRecordL632	689
#define imageRecordL633	690
#define imageRecordL634	691
#define imageRecordL635	692
#define imageRecordL636	693
#define imageRecordL637	694
#define imageRecordL638	695
#define imageRecordL639	696
#define imageRecordL640	697
#define imageRecordL641	698
#define imageRecordL642	699
#define imageRecordL643	700
#define imageRecordL644	701
#define imageRecordL645	702
#define imageRecordL646	703
#define imageRecordL647	704
#define imageRecordL648	705
#define imageRecordL649	706
#define imageRecordL650	707
#define imageRecordL651	708
#define imageRecordL652	709
#define imageRecordL653	710
#define imageRecordL654	711
#define imageRecordL655	712
#define imageRecordL656	713
#define imageRecordL657	714
#define imageRecordL658	715
#define imageRecordL659	716
#define imageRecordL660	717
#define imageRecordL661	718
#define imageRecordL662	719
#define imageRecordL663	720
#define imageRecordL664	721
#define imageRecordL665	722
#define imageRecordL666	723
#define imageRecordL667	724
#define imageRecordL668	725
#define imageRecordL669	726
#define imageRecordL670	727
#define imageRecordL671	728
#define imageRecordL672	729
#define imageRecordL673	730
#define imageRecordL674	731
#define imageRecordL675	732
#define imageRecordL676	733
#define imageRecordL677	734
#define imageRecordL678	735
#define imageRecordL679	736
#define imageRecordL680	737
#define imageRecordL681	738
#define imageRecordL682	739
#define imageRecordL683	740
#define imageRecordL684	741
#define imageRecordL685	742
#define imageRecordL686	743
#define imageRecordL687	744
#define imageRecordL688	745
#define imageRecordL689	746
#define imageRecordL690	747
#define imageRecordL691	748
#define imageRecordL692	749
#define imageRecordL693	750
#define imageRecordL694	751
#define imageRecordL695	752
#define imageRecordL696	753
#define imageRecordL697	754
#define imageRecordL698	755
#define imageRecordL699	756
#define imageRecordL700	757
#define imageRecordL701	758
#define imageRecordL702	759
#define imageRecordL703	760
#define imageRecordL704	761
#define imageRecordL705	762
#define imageRecordL706	763
#define imageRecordL707	764
#define imageRecordL708	765
#define imageRecordL709	766
#define imageRecordL710	767
#define imageRecordL711	768
#define imageRecordL712	769
#define imageRecordL713	770
#define imageRecordL714	771
#define imageRecordL715	772
#define imageRecordL716	773
#define imageRecordL717	774
#define imageRecordL718	775
#define imageRecordL719	776
#define imageRecordL720	777
#define imageRecordL721	778
#define imageRecordL722	779
#define imageRecordL723	780
#define imageRecordL724	781
#define imageRecordL725	782
#define imageRecordL726	783
#define imageRecordL727	784
#define imageRecordL728	785
#define imageRecordL729	786
#define imageRecordL730	787
#define imageRecordL731	788
#define imageRecordL732	789
#define imageRecordL733	790
#define imageRecordL734	791
#define imageRecordL735	792
#define imageRecordL736	793
#define imageRecordL737	794
#define imageRecordL738	795
#define imageRecordL739	796
#define imageRecordL740	797
#define imageRecordL741	798
#define imageRecordL742	799
#define imageRecordL743	800
#define imageRecordL744	801
#define imageRecordL745	802
#define imageRecordL746	803
#define imageRecordL747	804
#define imageRecordL748	805
#define imageRecordL749	806
#define imageRecordL750	807
#define imageRecordL751	808
#define imageRecordL752	809
#define imageRecordL753	810
#define imageRecordL754	811
#define imageRecordL755	812
#define imageRecordL756	813
#define imageRecordL757	814
#define imageRecordL758	815
#define imageRecordL759	816
#define imageRecordL760	817
#define imageRecordL761	818
#define imageRecordL762	819
#define imageRecordL763	820
#define imageRecordL764	821
#define imageRecordL765	822
#define imageRecordL766	823
#define imageRecordL767	824
#define imageRecordL768	825
#define imageRecordL769	826
#define imageRecordL770	827
#define imageRecordL771	828
#define imageRecordL772	829
#define imageRecordL773	830
#define imageRecordL774	831
#define imageRecordL775	832
#define imageRecordL776	833
#define imageRecordL777	834
#define imageRecordL778	835
#define imageRecordL779	836
#define imageRecordL780	837
#define imageRecordL781	838
#define imageRecordL782	839
#define imageRecordL783	840
#define imageRecordL784	841
#define imageRecordL785	842
#define imageRecordL786	843
#define imageRecordL787	844
#define imageRecordL788	845
#define imageRecordL789	846
#define imageRecordL790	847
#define imageRecordL791	848
#define imageRecordL792	849
#define imageRecordL793	850
#define imageRecordL794	851
#define imageRecordL795	852
#define imageRecordL796	853
#define imageRecordL797	854
#define imageRecordL798	855
#define imageRecordL799	856
#define imageRecordL800	857
#define imageRecordL801	858
#define imageRecordL802	859
#define imageRecordL803	860
#define imageRecordL804	861
#define imageRecordL805	862
#define imageRecordL806	863
#define imageRecordL807	864
#define imageRecordL808	865
#define imageRecordL809	866
#define imageRecordL810	867
#define imageRecordL811	868
#define imageRecordL812	869
#define imageRecordL813	870
#define imageRecordL814	871
#define imageRecordL815	872
#define imageRecordL816	873
#define imageRecordL817	874
#define imageRecordL818	875
#define imageRecordL819	876
#define imageRecordL820	877
#define imageRecordL821	878
#define imageRecordL822	879
#define imageRecordL823	880
#define imageRecordL824	881
#define imageRecordL825	882
#define imageRecordL826	883
#define imageRecordL827	884
#define imageRecordL828	885
#define imageRecordL829	886
#define imageRecordL830	887
#define imageRecordL831	888
#define imageRecordL832	889
#define imageRecordL833	890
#define imageRecordL834	891
#define imageRecordL835	892
#define imageRecordL836	893
#define imageRecordL837	894
#define imageRecordL838	895
#define imageRecordL839	896
#define imageRecordL840	897
#define imageRecordL841	898
#define imageRecordL842	899
#define imageRecordL843	900
#define imageRecordL844	901
#define imageRecordL845	902
#define imageRecordL846	903
#define imageRecordL847	904
#define imageRecordL848	905
#define imageRecordL849	906
#define imageRecordL850	907
#define imageRecordL851	908
#define imageRecordL852	909
#define imageRecordL853	910
#define imageRecordL854	911
#define imageRecordL855	912
#define imageRecordL856	913
#define imageRecordL857	914
#define imageRecordL858	915
#define imageRecordL859	916
#define imageRecordL860	917
#define imageRecordL861	918
#define imageRecordL862	919
#define imageRecordL863	920
#define imageRecordL864	921
#define imageRecordL865	922
#define imageRecordL866	923
#define imageRecordL867	924
#define imageRecordL868	925
#define imageRecordL869	926
#define imageRecordL870	927
#define imageRecordL871	928
#define imageRecordL872	929
#define imageRecordL873	930
#define imageRecordL874	931
#define imageRecordL875	932
#define imageRecordL876	933
#define imageRecordL877	934
#define imageRecordL878	935
#define imageRecordL879	936
#define imageRecordL880	937
#define imageRecordL881	938
#define imageRecordL882	939
#define imageRecordL883	940
#define imageRecordL884	941
#define imageRecordL885	942
#define imageRecordL886	943
#define imageRecordL887	944
#define imageRecordL888	945
#define imageRecordL889	946
#define imageRecordL890	947
#define imageRecordL891	948
#define imageRecordL892	949
#define imageRecordL893	950
#define imageRecordL894	951
#define imageRecordL895	952
#define imageRecordL896	953
#define imageRecordL897	954
#define imageRecordL898	955
#define imageRecordL899	956
#define imageRecordL900	957
#define imageRecordL901	958
#define imageRecordL902	959
#define imageRecordL903	960
#define imageRecordL904	961
#define imageRecordL905	962
#define imageRecordL906	963
#define imageRecordL907	964
#define imageRecordL908	965
#define imageRecordL909	966
#define imageRecordL910	967
#define imageRecordL911	968
#define imageRecordL912	969
#define imageRecordL913	970
#define imageRecordL914	971
#define imageRecordL915	972
#define imageRecordL916	973
#define imageRecordL917	974
#define imageRecordL918	975
#define imageRecordL919	976
#define imageRecordL920	977
#define imageRecordL921	978
#define imageRecordL922	979
#define imageRecordL923	980
#define imageRecordL924	981
#define imageRecordL925	982
#define imageRecordL926	983
#define imageRecordL927	984
#define imageRecordL928	985
#define imageRecordL929	986
#define imageRecordL930	987
#define imageRecordL931	988
#define imageRecordL932	989
#define imageRecordL933	990
#define imageRecordL934	991
#define imageRecordL935	992
#define imageRecordL936	993
#define imageRecordL937	994
#define imageRecordL938	995
#define imageRecordL939	996
#define imageRecordL940	997
#define imageRecordL941	998
#define imageRecordL942	999
#define imageRecordL943	1000
#define imageRecordL944	1001
#define imageRecordL945	1002
#define imageRecordL946	1003
#define imageRecordL947	1004
#define imageRecordL948	1005
#define imageRecordL949	1006
#define imageRecordL950	1007
#define imageRecordL951	1008
#define imageRecordL952	1009
#define imageRecordL953	1010
#define imageRecordL954	1011
#define imageRecordL955	1012
#define imageRecordL956	1013
#define imageRecordL957	1014
#define imageRecordL958	1015
#define imageRecordL959	1016
#define imageRecordL960	1017
#define imageRecordL961	1018
#define imageRecordL962	1019
#define imageRecordL963	1020
#define imageRecordL964	1021
#define imageRecordL965	1022
#define imageRecordL966	1023
#define imageRecordL967	1024
#define imageRecordL968	1025
#define imageRecordL969	1026
#define imageRecordL970	1027
#define imageRecordL971	1028
#define imageRecordL972	1029
#define imageRecordL973	1030
#define imageRecordL974	1031
#define imageRecordL975	1032
#define imageRecordL976	1033
#define imageRecordL977	1034
#define imageRecordL978	1035
#define imageRecordL979	1036
#define imageRecordL980	1037
#define imageRecordL981	1038
#define imageRecordL982	1039
#define imageRecordL983	1040
#define imageRecordL984	1041
#define imageRecordL985	1042
#define imageRecordL986	1043
#define imageRecordL987	1044
#define imageRecordL988	1045
#define imageRecordL989	1046
#define imageRecordL990	1047
#define imageRecordL991	1048
#define imageRecordL992	1049
#define imageRecordL993	1050
#define imageRecordL994	1051
#define imageRecordL995	1052
#define imageRecordL996	1053
#define imageRecordL997	1054
#define imageRecordL998	1055
#define imageRecordL999	1056
#define imageRecordL1000	1057
#define imageRecordL1001	1058
#define imageRecordL1002	1059
#define imageRecordL1003	1060
#define imageRecordL1004	1061
#define imageRecordL1005	1062
#define imageRecordL1006	1063
#define imageRecordL1007	1064
#define imageRecordL1008	1065
#define imageRecordL1009	1066
#define imageRecordL1010	1067
#define imageRecordL1011	1068
#define imageRecordL1012	1069
#define imageRecordL1013	1070
#define imageRecordL1014	1071
#define imageRecordL1015	1072
#define imageRecordL1016	1073
#define imageRecordL1017	1074
#define imageRecordL1018	1075
#define imageRecordL1019	1076
#define imageRecordL1020	1077
#define imageRecordL1021	1078
#define imageRecordL1022	1079
#define imageRecordL1023	1080
#endif /*INCimageH*/
#ifdef GEN_SIZE_OFFSET
int imageRecordSizeOffset(dbRecordType *pdbRecordType)
{
    imageRecord *prec = 0;
  pdbRecordType->papFldDes[0]->size=sizeof(prec->name);
  pdbRecordType->papFldDes[0]->offset=(short)((char *)&prec->name - (char *)prec);
  pdbRecordType->papFldDes[1]->size=sizeof(prec->desc);
  pdbRecordType->papFldDes[1]->offset=(short)((char *)&prec->desc - (char *)prec);
  pdbRecordType->papFldDes[2]->size=sizeof(prec->asg);
  pdbRecordType->papFldDes[2]->offset=(short)((char *)&prec->asg - (char *)prec);
  pdbRecordType->papFldDes[3]->size=sizeof(prec->scan);
  pdbRecordType->papFldDes[3]->offset=(short)((char *)&prec->scan - (char *)prec);
  pdbRecordType->papFldDes[4]->size=sizeof(prec->pini);
  pdbRecordType->papFldDes[4]->offset=(short)((char *)&prec->pini - (char *)prec);
  pdbRecordType->papFldDes[5]->size=sizeof(prec->phas);
  pdbRecordType->papFldDes[5]->offset=(short)((char *)&prec->phas - (char *)prec);
  pdbRecordType->papFldDes[6]->size=sizeof(prec->evnt);
  pdbRecordType->papFldDes[6]->offset=(short)((char *)&prec->evnt - (char *)prec);
  pdbRecordType->papFldDes[7]->size=sizeof(prec->tse);
  pdbRecordType->papFldDes[7]->offset=(short)((char *)&prec->tse - (char *)prec);
  pdbRecordType->papFldDes[8]->size=sizeof(prec->tsel);
  pdbRecordType->papFldDes[8]->offset=(short)((char *)&prec->tsel - (char *)prec);
  pdbRecordType->papFldDes[9]->size=sizeof(prec->dtyp);
  pdbRecordType->papFldDes[9]->offset=(short)((char *)&prec->dtyp - (char *)prec);
  pdbRecordType->papFldDes[10]->size=sizeof(prec->disv);
  pdbRecordType->papFldDes[10]->offset=(short)((char *)&prec->disv - (char *)prec);
  pdbRecordType->papFldDes[11]->size=sizeof(prec->disa);
  pdbRecordType->papFldDes[11]->offset=(short)((char *)&prec->disa - (char *)prec);
  pdbRecordType->papFldDes[12]->size=sizeof(prec->sdis);
  pdbRecordType->papFldDes[12]->offset=(short)((char *)&prec->sdis - (char *)prec);
  pdbRecordType->papFldDes[13]->size=sizeof(prec->mlok);
  pdbRecordType->papFldDes[13]->offset=(short)((char *)&prec->mlok - (char *)prec);
  pdbRecordType->papFldDes[14]->size=sizeof(prec->mlis);
  pdbRecordType->papFldDes[14]->offset=(short)((char *)&prec->mlis - (char *)prec);
  pdbRecordType->papFldDes[15]->size=sizeof(prec->disp);
  pdbRecordType->papFldDes[15]->offset=(short)((char *)&prec->disp - (char *)prec);
  pdbRecordType->papFldDes[16]->size=sizeof(prec->proc);
  pdbRecordType->papFldDes[16]->offset=(short)((char *)&prec->proc - (char *)prec);
  pdbRecordType->papFldDes[17]->size=sizeof(prec->stat);
  pdbRecordType->papFldDes[17]->offset=(short)((char *)&prec->stat - (char *)prec);
  pdbRecordType->papFldDes[18]->size=sizeof(prec->sevr);
  pdbRecordType->papFldDes[18]->offset=(short)((char *)&prec->sevr - (char *)prec);
  pdbRecordType->papFldDes[19]->size=sizeof(prec->nsta);
  pdbRecordType->papFldDes[19]->offset=(short)((char *)&prec->nsta - (char *)prec);
  pdbRecordType->papFldDes[20]->size=sizeof(prec->nsev);
  pdbRecordType->papFldDes[20]->offset=(short)((char *)&prec->nsev - (char *)prec);
  pdbRecordType->papFldDes[21]->size=sizeof(prec->acks);
  pdbRecordType->papFldDes[21]->offset=(short)((char *)&prec->acks - (char *)prec);
  pdbRecordType->papFldDes[22]->size=sizeof(prec->ackt);
  pdbRecordType->papFldDes[22]->offset=(short)((char *)&prec->ackt - (char *)prec);
  pdbRecordType->papFldDes[23]->size=sizeof(prec->diss);
  pdbRecordType->papFldDes[23]->offset=(short)((char *)&prec->diss - (char *)prec);
  pdbRecordType->papFldDes[24]->size=sizeof(prec->lcnt);
  pdbRecordType->papFldDes[24]->offset=(short)((char *)&prec->lcnt - (char *)prec);
  pdbRecordType->papFldDes[25]->size=sizeof(prec->pact);
  pdbRecordType->papFldDes[25]->offset=(short)((char *)&prec->pact - (char *)prec);
  pdbRecordType->papFldDes[26]->size=sizeof(prec->putf);
  pdbRecordType->papFldDes[26]->offset=(short)((char *)&prec->putf - (char *)prec);
  pdbRecordType->papFldDes[27]->size=sizeof(prec->rpro);
  pdbRecordType->papFldDes[27]->offset=(short)((char *)&prec->rpro - (char *)prec);
  pdbRecordType->papFldDes[28]->size=sizeof(prec->asp);
  pdbRecordType->papFldDes[28]->offset=(short)((char *)&prec->asp - (char *)prec);
  pdbRecordType->papFldDes[29]->size=sizeof(prec->ppn);
  pdbRecordType->papFldDes[29]->offset=(short)((char *)&prec->ppn - (char *)prec);
  pdbRecordType->papFldDes[30]->size=sizeof(prec->ppnn);
  pdbRecordType->papFldDes[30]->offset=(short)((char *)&prec->ppnn - (char *)prec);
  pdbRecordType->papFldDes[31]->size=sizeof(prec->spvt);
  pdbRecordType->papFldDes[31]->offset=(short)((char *)&prec->spvt - (char *)prec);
  pdbRecordType->papFldDes[32]->size=sizeof(prec->rset);
  pdbRecordType->papFldDes[32]->offset=(short)((char *)&prec->rset - (char *)prec);
  pdbRecordType->papFldDes[33]->size=sizeof(prec->dset);
  pdbRecordType->papFldDes[33]->offset=(short)((char *)&prec->dset - (char *)prec);
  pdbRecordType->papFldDes[34]->size=sizeof(prec->dpvt);
  pdbRecordType->papFldDes[34]->offset=(short)((char *)&prec->dpvt - (char *)prec);
  pdbRecordType->papFldDes[35]->size=sizeof(prec->rdes);
  pdbRecordType->papFldDes[35]->offset=(short)((char *)&prec->rdes - (char *)prec);
  pdbRecordType->papFldDes[36]->size=sizeof(prec->lset);
  pdbRecordType->papFldDes[36]->offset=(short)((char *)&prec->lset - (char *)prec);
  pdbRecordType->papFldDes[37]->size=sizeof(prec->prio);
  pdbRecordType->papFldDes[37]->offset=(short)((char *)&prec->prio - (char *)prec);
  pdbRecordType->papFldDes[38]->size=sizeof(prec->tpro);
  pdbRecordType->papFldDes[38]->offset=(short)((char *)&prec->tpro - (char *)prec);
  pdbRecordType->papFldDes[39]->size=sizeof(prec->bkpt);
  pdbRecordType->papFldDes[39]->offset=(short)((char *)&prec->bkpt - (char *)prec);
  pdbRecordType->papFldDes[40]->size=sizeof(prec->udf);
  pdbRecordType->papFldDes[40]->offset=(short)((char *)&prec->udf - (char *)prec);
  pdbRecordType->papFldDes[41]->size=sizeof(prec->time);
  pdbRecordType->papFldDes[41]->offset=(short)((char *)&prec->time - (char *)prec);
  pdbRecordType->papFldDes[42]->size=sizeof(prec->flnk);
  pdbRecordType->papFldDes[42]->offset=(short)((char *)&prec->flnk - (char *)prec);
  pdbRecordType->papFldDes[43]->size=sizeof(prec->vers);
  pdbRecordType->papFldDes[43]->offset=(short)((char *)&prec->vers - (char *)prec);
  pdbRecordType->papFldDes[44]->size=sizeof(prec->enab);
  pdbRecordType->papFldDes[44]->offset=(short)((char *)&prec->enab - (char *)prec);
  pdbRecordType->papFldDes[45]->size=sizeof(prec->rate);
  pdbRecordType->papFldDes[45]->offset=(short)((char *)&prec->rate - (char *)prec);
  pdbRecordType->papFldDes[46]->size=sizeof(prec->pmtk);
  pdbRecordType->papFldDes[46]->offset=(short)((char *)&prec->pmtk - (char *)prec);
  pdbRecordType->papFldDes[47]->size=sizeof(prec->val);
  pdbRecordType->papFldDes[47]->offset=(short)((char *)&prec->val - (char *)prec);
  pdbRecordType->papFldDes[48]->size=sizeof(prec->inp);
  pdbRecordType->papFldDes[48]->offset=(short)((char *)&prec->inp - (char *)prec);
  pdbRecordType->papFldDes[49]->size=sizeof(prec->vxnm);
  pdbRecordType->papFldDes[49]->offset=(short)((char *)&prec->vxnm - (char *)prec);
  pdbRecordType->papFldDes[50]->size=sizeof(prec->size);
  pdbRecordType->papFldDes[50]->offset=(short)((char *)&prec->size - (char *)prec);
  pdbRecordType->papFldDes[51]->size=sizeof(prec->xres);
  pdbRecordType->papFldDes[51]->offset=(short)((char *)&prec->xres - (char *)prec);
  pdbRecordType->papFldDes[52]->size=sizeof(prec->yres);
  pdbRecordType->papFldDes[52]->offset=(short)((char *)&prec->yres - (char *)prec);
  pdbRecordType->papFldDes[53]->size=sizeof(prec->rxst);
  pdbRecordType->papFldDes[53]->offset=(short)((char *)&prec->rxst - (char *)prec);
  pdbRecordType->papFldDes[54]->size=sizeof(prec->rxsz);
  pdbRecordType->papFldDes[54]->offset=(short)((char *)&prec->rxsz - (char *)prec);
  pdbRecordType->papFldDes[55]->size=sizeof(prec->ryst);
  pdbRecordType->papFldDes[55]->offset=(short)((char *)&prec->ryst - (char *)prec);
  pdbRecordType->papFldDes[56]->size=sizeof(prec->rysz);
  pdbRecordType->papFldDes[56]->offset=(short)((char *)&prec->rysz - (char *)prec);
  pdbRecordType->papFldDes[57]->size=sizeof(prec->l0);
  pdbRecordType->papFldDes[57]->offset=(short)((char *)&prec->l0 - (char *)prec);
  pdbRecordType->papFldDes[58]->size=sizeof(prec->l1);
  pdbRecordType->papFldDes[58]->offset=(short)((char *)&prec->l1 - (char *)prec);
  pdbRecordType->papFldDes[59]->size=sizeof(prec->l2);
  pdbRecordType->papFldDes[59]->offset=(short)((char *)&prec->l2 - (char *)prec);
  pdbRecordType->papFldDes[60]->size=sizeof(prec->l3);
  pdbRecordType->papFldDes[60]->offset=(short)((char *)&prec->l3 - (char *)prec);
  pdbRecordType->papFldDes[61]->size=sizeof(prec->l4);
  pdbRecordType->papFldDes[61]->offset=(short)((char *)&prec->l4 - (char *)prec);
  pdbRecordType->papFldDes[62]->size=sizeof(prec->l5);
  pdbRecordType->papFldDes[62]->offset=(short)((char *)&prec->l5 - (char *)prec);
  pdbRecordType->papFldDes[63]->size=sizeof(prec->l6);
  pdbRecordType->papFldDes[63]->offset=(short)((char *)&prec->l6 - (char *)prec);
  pdbRecordType->papFldDes[64]->size=sizeof(prec->l7);
  pdbRecordType->papFldDes[64]->offset=(short)((char *)&prec->l7 - (char *)prec);
  pdbRecordType->papFldDes[65]->size=sizeof(prec->l8);
  pdbRecordType->papFldDes[65]->offset=(short)((char *)&prec->l8 - (char *)prec);
  pdbRecordType->papFldDes[66]->size=sizeof(prec->l9);
  pdbRecordType->papFldDes[66]->offset=(short)((char *)&prec->l9 - (char *)prec);
  pdbRecordType->papFldDes[67]->size=sizeof(prec->l10);
  pdbRecordType->papFldDes[67]->offset=(short)((char *)&prec->l10 - (char *)prec);
  pdbRecordType->papFldDes[68]->size=sizeof(prec->l11);
  pdbRecordType->papFldDes[68]->offset=(short)((char *)&prec->l11 - (char *)prec);
  pdbRecordType->papFldDes[69]->size=sizeof(prec->l12);
  pdbRecordType->papFldDes[69]->offset=(short)((char *)&prec->l12 - (char *)prec);
  pdbRecordType->papFldDes[70]->size=sizeof(prec->l13);
  pdbRecordType->papFldDes[70]->offset=(short)((char *)&prec->l13 - (char *)prec);
  pdbRecordType->papFldDes[71]->size=sizeof(prec->l14);
  pdbRecordType->papFldDes[71]->offset=(short)((char *)&prec->l14 - (char *)prec);
  pdbRecordType->papFldDes[72]->size=sizeof(prec->l15);
  pdbRecordType->papFldDes[72]->offset=(short)((char *)&prec->l15 - (char *)prec);
  pdbRecordType->papFldDes[73]->size=sizeof(prec->l16);
  pdbRecordType->papFldDes[73]->offset=(short)((char *)&prec->l16 - (char *)prec);
  pdbRecordType->papFldDes[74]->size=sizeof(prec->l17);
  pdbRecordType->papFldDes[74]->offset=(short)((char *)&prec->l17 - (char *)prec);
  pdbRecordType->papFldDes[75]->size=sizeof(prec->l18);
  pdbRecordType->papFldDes[75]->offset=(short)((char *)&prec->l18 - (char *)prec);
  pdbRecordType->papFldDes[76]->size=sizeof(prec->l19);
  pdbRecordType->papFldDes[76]->offset=(short)((char *)&prec->l19 - (char *)prec);
  pdbRecordType->papFldDes[77]->size=sizeof(prec->l20);
  pdbRecordType->papFldDes[77]->offset=(short)((char *)&prec->l20 - (char *)prec);
  pdbRecordType->papFldDes[78]->size=sizeof(prec->l21);
  pdbRecordType->papFldDes[78]->offset=(short)((char *)&prec->l21 - (char *)prec);
  pdbRecordType->papFldDes[79]->size=sizeof(prec->l22);
  pdbRecordType->papFldDes[79]->offset=(short)((char *)&prec->l22 - (char *)prec);
  pdbRecordType->papFldDes[80]->size=sizeof(prec->l23);
  pdbRecordType->papFldDes[80]->offset=(short)((char *)&prec->l23 - (char *)prec);
  pdbRecordType->papFldDes[81]->size=sizeof(prec->l24);
  pdbRecordType->papFldDes[81]->offset=(short)((char *)&prec->l24 - (char *)prec);
  pdbRecordType->papFldDes[82]->size=sizeof(prec->l25);
  pdbRecordType->papFldDes[82]->offset=(short)((char *)&prec->l25 - (char *)prec);
  pdbRecordType->papFldDes[83]->size=sizeof(prec->l26);
  pdbRecordType->papFldDes[83]->offset=(short)((char *)&prec->l26 - (char *)prec);
  pdbRecordType->papFldDes[84]->size=sizeof(prec->l27);
  pdbRecordType->papFldDes[84]->offset=(short)((char *)&prec->l27 - (char *)prec);
  pdbRecordType->papFldDes[85]->size=sizeof(prec->l28);
  pdbRecordType->papFldDes[85]->offset=(short)((char *)&prec->l28 - (char *)prec);
  pdbRecordType->papFldDes[86]->size=sizeof(prec->l29);
  pdbRecordType->papFldDes[86]->offset=(short)((char *)&prec->l29 - (char *)prec);
  pdbRecordType->papFldDes[87]->size=sizeof(prec->l30);
  pdbRecordType->papFldDes[87]->offset=(short)((char *)&prec->l30 - (char *)prec);
  pdbRecordType->papFldDes[88]->size=sizeof(prec->l31);
  pdbRecordType->papFldDes[88]->offset=(short)((char *)&prec->l31 - (char *)prec);
  pdbRecordType->papFldDes[89]->size=sizeof(prec->l32);
  pdbRecordType->papFldDes[89]->offset=(short)((char *)&prec->l32 - (char *)prec);
  pdbRecordType->papFldDes[90]->size=sizeof(prec->l33);
  pdbRecordType->papFldDes[90]->offset=(short)((char *)&prec->l33 - (char *)prec);
  pdbRecordType->papFldDes[91]->size=sizeof(prec->l34);
  pdbRecordType->papFldDes[91]->offset=(short)((char *)&prec->l34 - (char *)prec);
  pdbRecordType->papFldDes[92]->size=sizeof(prec->l35);
  pdbRecordType->papFldDes[92]->offset=(short)((char *)&prec->l35 - (char *)prec);
  pdbRecordType->papFldDes[93]->size=sizeof(prec->l36);
  pdbRecordType->papFldDes[93]->offset=(short)((char *)&prec->l36 - (char *)prec);
  pdbRecordType->papFldDes[94]->size=sizeof(prec->l37);
  pdbRecordType->papFldDes[94]->offset=(short)((char *)&prec->l37 - (char *)prec);
  pdbRecordType->papFldDes[95]->size=sizeof(prec->l38);
  pdbRecordType->papFldDes[95]->offset=(short)((char *)&prec->l38 - (char *)prec);
  pdbRecordType->papFldDes[96]->size=sizeof(prec->l39);
  pdbRecordType->papFldDes[96]->offset=(short)((char *)&prec->l39 - (char *)prec);
  pdbRecordType->papFldDes[97]->size=sizeof(prec->l40);
  pdbRecordType->papFldDes[97]->offset=(short)((char *)&prec->l40 - (char *)prec);
  pdbRecordType->papFldDes[98]->size=sizeof(prec->l41);
  pdbRecordType->papFldDes[98]->offset=(short)((char *)&prec->l41 - (char *)prec);
  pdbRecordType->papFldDes[99]->size=sizeof(prec->l42);
  pdbRecordType->papFldDes[99]->offset=(short)((char *)&prec->l42 - (char *)prec);
  pdbRecordType->papFldDes[100]->size=sizeof(prec->l43);
  pdbRecordType->papFldDes[100]->offset=(short)((char *)&prec->l43 - (char *)prec);
  pdbRecordType->papFldDes[101]->size=sizeof(prec->l44);
  pdbRecordType->papFldDes[101]->offset=(short)((char *)&prec->l44 - (char *)prec);
  pdbRecordType->papFldDes[102]->size=sizeof(prec->l45);
  pdbRecordType->papFldDes[102]->offset=(short)((char *)&prec->l45 - (char *)prec);
  pdbRecordType->papFldDes[103]->size=sizeof(prec->l46);
  pdbRecordType->papFldDes[103]->offset=(short)((char *)&prec->l46 - (char *)prec);
  pdbRecordType->papFldDes[104]->size=sizeof(prec->l47);
  pdbRecordType->papFldDes[104]->offset=(short)((char *)&prec->l47 - (char *)prec);
  pdbRecordType->papFldDes[105]->size=sizeof(prec->l48);
  pdbRecordType->papFldDes[105]->offset=(short)((char *)&prec->l48 - (char *)prec);
  pdbRecordType->papFldDes[106]->size=sizeof(prec->l49);
  pdbRecordType->papFldDes[106]->offset=(short)((char *)&prec->l49 - (char *)prec);
  pdbRecordType->papFldDes[107]->size=sizeof(prec->l50);
  pdbRecordType->papFldDes[107]->offset=(short)((char *)&prec->l50 - (char *)prec);
  pdbRecordType->papFldDes[108]->size=sizeof(prec->l51);
  pdbRecordType->papFldDes[108]->offset=(short)((char *)&prec->l51 - (char *)prec);
  pdbRecordType->papFldDes[109]->size=sizeof(prec->l52);
  pdbRecordType->papFldDes[109]->offset=(short)((char *)&prec->l52 - (char *)prec);
  pdbRecordType->papFldDes[110]->size=sizeof(prec->l53);
  pdbRecordType->papFldDes[110]->offset=(short)((char *)&prec->l53 - (char *)prec);
  pdbRecordType->papFldDes[111]->size=sizeof(prec->l54);
  pdbRecordType->papFldDes[111]->offset=(short)((char *)&prec->l54 - (char *)prec);
  pdbRecordType->papFldDes[112]->size=sizeof(prec->l55);
  pdbRecordType->papFldDes[112]->offset=(short)((char *)&prec->l55 - (char *)prec);
  pdbRecordType->papFldDes[113]->size=sizeof(prec->l56);
  pdbRecordType->papFldDes[113]->offset=(short)((char *)&prec->l56 - (char *)prec);
  pdbRecordType->papFldDes[114]->size=sizeof(prec->l57);
  pdbRecordType->papFldDes[114]->offset=(short)((char *)&prec->l57 - (char *)prec);
  pdbRecordType->papFldDes[115]->size=sizeof(prec->l58);
  pdbRecordType->papFldDes[115]->offset=(short)((char *)&prec->l58 - (char *)prec);
  pdbRecordType->papFldDes[116]->size=sizeof(prec->l59);
  pdbRecordType->papFldDes[116]->offset=(short)((char *)&prec->l59 - (char *)prec);
  pdbRecordType->papFldDes[117]->size=sizeof(prec->l60);
  pdbRecordType->papFldDes[117]->offset=(short)((char *)&prec->l60 - (char *)prec);
  pdbRecordType->papFldDes[118]->size=sizeof(prec->l61);
  pdbRecordType->papFldDes[118]->offset=(short)((char *)&prec->l61 - (char *)prec);
  pdbRecordType->papFldDes[119]->size=sizeof(prec->l62);
  pdbRecordType->papFldDes[119]->offset=(short)((char *)&prec->l62 - (char *)prec);
  pdbRecordType->papFldDes[120]->size=sizeof(prec->l63);
  pdbRecordType->papFldDes[120]->offset=(short)((char *)&prec->l63 - (char *)prec);
  pdbRecordType->papFldDes[121]->size=sizeof(prec->l64);
  pdbRecordType->papFldDes[121]->offset=(short)((char *)&prec->l64 - (char *)prec);
  pdbRecordType->papFldDes[122]->size=sizeof(prec->l65);
  pdbRecordType->papFldDes[122]->offset=(short)((char *)&prec->l65 - (char *)prec);
  pdbRecordType->papFldDes[123]->size=sizeof(prec->l66);
  pdbRecordType->papFldDes[123]->offset=(short)((char *)&prec->l66 - (char *)prec);
  pdbRecordType->papFldDes[124]->size=sizeof(prec->l67);
  pdbRecordType->papFldDes[124]->offset=(short)((char *)&prec->l67 - (char *)prec);
  pdbRecordType->papFldDes[125]->size=sizeof(prec->l68);
  pdbRecordType->papFldDes[125]->offset=(short)((char *)&prec->l68 - (char *)prec);
  pdbRecordType->papFldDes[126]->size=sizeof(prec->l69);
  pdbRecordType->papFldDes[126]->offset=(short)((char *)&prec->l69 - (char *)prec);
  pdbRecordType->papFldDes[127]->size=sizeof(prec->l70);
  pdbRecordType->papFldDes[127]->offset=(short)((char *)&prec->l70 - (char *)prec);
  pdbRecordType->papFldDes[128]->size=sizeof(prec->l71);
  pdbRecordType->papFldDes[128]->offset=(short)((char *)&prec->l71 - (char *)prec);
  pdbRecordType->papFldDes[129]->size=sizeof(prec->l72);
  pdbRecordType->papFldDes[129]->offset=(short)((char *)&prec->l72 - (char *)prec);
  pdbRecordType->papFldDes[130]->size=sizeof(prec->l73);
  pdbRecordType->papFldDes[130]->offset=(short)((char *)&prec->l73 - (char *)prec);
  pdbRecordType->papFldDes[131]->size=sizeof(prec->l74);
  pdbRecordType->papFldDes[131]->offset=(short)((char *)&prec->l74 - (char *)prec);
  pdbRecordType->papFldDes[132]->size=sizeof(prec->l75);
  pdbRecordType->papFldDes[132]->offset=(short)((char *)&prec->l75 - (char *)prec);
  pdbRecordType->papFldDes[133]->size=sizeof(prec->l76);
  pdbRecordType->papFldDes[133]->offset=(short)((char *)&prec->l76 - (char *)prec);
  pdbRecordType->papFldDes[134]->size=sizeof(prec->l77);
  pdbRecordType->papFldDes[134]->offset=(short)((char *)&prec->l77 - (char *)prec);
  pdbRecordType->papFldDes[135]->size=sizeof(prec->l78);
  pdbRecordType->papFldDes[135]->offset=(short)((char *)&prec->l78 - (char *)prec);
  pdbRecordType->papFldDes[136]->size=sizeof(prec->l79);
  pdbRecordType->papFldDes[136]->offset=(short)((char *)&prec->l79 - (char *)prec);
  pdbRecordType->papFldDes[137]->size=sizeof(prec->l80);
  pdbRecordType->papFldDes[137]->offset=(short)((char *)&prec->l80 - (char *)prec);
  pdbRecordType->papFldDes[138]->size=sizeof(prec->l81);
  pdbRecordType->papFldDes[138]->offset=(short)((char *)&prec->l81 - (char *)prec);
  pdbRecordType->papFldDes[139]->size=sizeof(prec->l82);
  pdbRecordType->papFldDes[139]->offset=(short)((char *)&prec->l82 - (char *)prec);
  pdbRecordType->papFldDes[140]->size=sizeof(prec->l83);
  pdbRecordType->papFldDes[140]->offset=(short)((char *)&prec->l83 - (char *)prec);
  pdbRecordType->papFldDes[141]->size=sizeof(prec->l84);
  pdbRecordType->papFldDes[141]->offset=(short)((char *)&prec->l84 - (char *)prec);
  pdbRecordType->papFldDes[142]->size=sizeof(prec->l85);
  pdbRecordType->papFldDes[142]->offset=(short)((char *)&prec->l85 - (char *)prec);
  pdbRecordType->papFldDes[143]->size=sizeof(prec->l86);
  pdbRecordType->papFldDes[143]->offset=(short)((char *)&prec->l86 - (char *)prec);
  pdbRecordType->papFldDes[144]->size=sizeof(prec->l87);
  pdbRecordType->papFldDes[144]->offset=(short)((char *)&prec->l87 - (char *)prec);
  pdbRecordType->papFldDes[145]->size=sizeof(prec->l88);
  pdbRecordType->papFldDes[145]->offset=(short)((char *)&prec->l88 - (char *)prec);
  pdbRecordType->papFldDes[146]->size=sizeof(prec->l89);
  pdbRecordType->papFldDes[146]->offset=(short)((char *)&prec->l89 - (char *)prec);
  pdbRecordType->papFldDes[147]->size=sizeof(prec->l90);
  pdbRecordType->papFldDes[147]->offset=(short)((char *)&prec->l90 - (char *)prec);
  pdbRecordType->papFldDes[148]->size=sizeof(prec->l91);
  pdbRecordType->papFldDes[148]->offset=(short)((char *)&prec->l91 - (char *)prec);
  pdbRecordType->papFldDes[149]->size=sizeof(prec->l92);
  pdbRecordType->papFldDes[149]->offset=(short)((char *)&prec->l92 - (char *)prec);
  pdbRecordType->papFldDes[150]->size=sizeof(prec->l93);
  pdbRecordType->papFldDes[150]->offset=(short)((char *)&prec->l93 - (char *)prec);
  pdbRecordType->papFldDes[151]->size=sizeof(prec->l94);
  pdbRecordType->papFldDes[151]->offset=(short)((char *)&prec->l94 - (char *)prec);
  pdbRecordType->papFldDes[152]->size=sizeof(prec->l95);
  pdbRecordType->papFldDes[152]->offset=(short)((char *)&prec->l95 - (char *)prec);
  pdbRecordType->papFldDes[153]->size=sizeof(prec->l96);
  pdbRecordType->papFldDes[153]->offset=(short)((char *)&prec->l96 - (char *)prec);
  pdbRecordType->papFldDes[154]->size=sizeof(prec->l97);
  pdbRecordType->papFldDes[154]->offset=(short)((char *)&prec->l97 - (char *)prec);
  pdbRecordType->papFldDes[155]->size=sizeof(prec->l98);
  pdbRecordType->papFldDes[155]->offset=(short)((char *)&prec->l98 - (char *)prec);
  pdbRecordType->papFldDes[156]->size=sizeof(prec->l99);
  pdbRecordType->papFldDes[156]->offset=(short)((char *)&prec->l99 - (char *)prec);
  pdbRecordType->papFldDes[157]->size=sizeof(prec->l100);
  pdbRecordType->papFldDes[157]->offset=(short)((char *)&prec->l100 - (char *)prec);
  pdbRecordType->papFldDes[158]->size=sizeof(prec->l101);
  pdbRecordType->papFldDes[158]->offset=(short)((char *)&prec->l101 - (char *)prec);
  pdbRecordType->papFldDes[159]->size=sizeof(prec->l102);
  pdbRecordType->papFldDes[159]->offset=(short)((char *)&prec->l102 - (char *)prec);
  pdbRecordType->papFldDes[160]->size=sizeof(prec->l103);
  pdbRecordType->papFldDes[160]->offset=(short)((char *)&prec->l103 - (char *)prec);
  pdbRecordType->papFldDes[161]->size=sizeof(prec->l104);
  pdbRecordType->papFldDes[161]->offset=(short)((char *)&prec->l104 - (char *)prec);
  pdbRecordType->papFldDes[162]->size=sizeof(prec->l105);
  pdbRecordType->papFldDes[162]->offset=(short)((char *)&prec->l105 - (char *)prec);
  pdbRecordType->papFldDes[163]->size=sizeof(prec->l106);
  pdbRecordType->papFldDes[163]->offset=(short)((char *)&prec->l106 - (char *)prec);
  pdbRecordType->papFldDes[164]->size=sizeof(prec->l107);
  pdbRecordType->papFldDes[164]->offset=(short)((char *)&prec->l107 - (char *)prec);
  pdbRecordType->papFldDes[165]->size=sizeof(prec->l108);
  pdbRecordType->papFldDes[165]->offset=(short)((char *)&prec->l108 - (char *)prec);
  pdbRecordType->papFldDes[166]->size=sizeof(prec->l109);
  pdbRecordType->papFldDes[166]->offset=(short)((char *)&prec->l109 - (char *)prec);
  pdbRecordType->papFldDes[167]->size=sizeof(prec->l110);
  pdbRecordType->papFldDes[167]->offset=(short)((char *)&prec->l110 - (char *)prec);
  pdbRecordType->papFldDes[168]->size=sizeof(prec->l111);
  pdbRecordType->papFldDes[168]->offset=(short)((char *)&prec->l111 - (char *)prec);
  pdbRecordType->papFldDes[169]->size=sizeof(prec->l112);
  pdbRecordType->papFldDes[169]->offset=(short)((char *)&prec->l112 - (char *)prec);
  pdbRecordType->papFldDes[170]->size=sizeof(prec->l113);
  pdbRecordType->papFldDes[170]->offset=(short)((char *)&prec->l113 - (char *)prec);
  pdbRecordType->papFldDes[171]->size=sizeof(prec->l114);
  pdbRecordType->papFldDes[171]->offset=(short)((char *)&prec->l114 - (char *)prec);
  pdbRecordType->papFldDes[172]->size=sizeof(prec->l115);
  pdbRecordType->papFldDes[172]->offset=(short)((char *)&prec->l115 - (char *)prec);
  pdbRecordType->papFldDes[173]->size=sizeof(prec->l116);
  pdbRecordType->papFldDes[173]->offset=(short)((char *)&prec->l116 - (char *)prec);
  pdbRecordType->papFldDes[174]->size=sizeof(prec->l117);
  pdbRecordType->papFldDes[174]->offset=(short)((char *)&prec->l117 - (char *)prec);
  pdbRecordType->papFldDes[175]->size=sizeof(prec->l118);
  pdbRecordType->papFldDes[175]->offset=(short)((char *)&prec->l118 - (char *)prec);
  pdbRecordType->papFldDes[176]->size=sizeof(prec->l119);
  pdbRecordType->papFldDes[176]->offset=(short)((char *)&prec->l119 - (char *)prec);
  pdbRecordType->papFldDes[177]->size=sizeof(prec->l120);
  pdbRecordType->papFldDes[177]->offset=(short)((char *)&prec->l120 - (char *)prec);
  pdbRecordType->papFldDes[178]->size=sizeof(prec->l121);
  pdbRecordType->papFldDes[178]->offset=(short)((char *)&prec->l121 - (char *)prec);
  pdbRecordType->papFldDes[179]->size=sizeof(prec->l122);
  pdbRecordType->papFldDes[179]->offset=(short)((char *)&prec->l122 - (char *)prec);
  pdbRecordType->papFldDes[180]->size=sizeof(prec->l123);
  pdbRecordType->papFldDes[180]->offset=(short)((char *)&prec->l123 - (char *)prec);
  pdbRecordType->papFldDes[181]->size=sizeof(prec->l124);
  pdbRecordType->papFldDes[181]->offset=(short)((char *)&prec->l124 - (char *)prec);
  pdbRecordType->papFldDes[182]->size=sizeof(prec->l125);
  pdbRecordType->papFldDes[182]->offset=(short)((char *)&prec->l125 - (char *)prec);
  pdbRecordType->papFldDes[183]->size=sizeof(prec->l126);
  pdbRecordType->papFldDes[183]->offset=(short)((char *)&prec->l126 - (char *)prec);
  pdbRecordType->papFldDes[184]->size=sizeof(prec->l127);
  pdbRecordType->papFldDes[184]->offset=(short)((char *)&prec->l127 - (char *)prec);
  pdbRecordType->papFldDes[185]->size=sizeof(prec->l128);
  pdbRecordType->papFldDes[185]->offset=(short)((char *)&prec->l128 - (char *)prec);
  pdbRecordType->papFldDes[186]->size=sizeof(prec->l129);
  pdbRecordType->papFldDes[186]->offset=(short)((char *)&prec->l129 - (char *)prec);
  pdbRecordType->papFldDes[187]->size=sizeof(prec->l130);
  pdbRecordType->papFldDes[187]->offset=(short)((char *)&prec->l130 - (char *)prec);
  pdbRecordType->papFldDes[188]->size=sizeof(prec->l131);
  pdbRecordType->papFldDes[188]->offset=(short)((char *)&prec->l131 - (char *)prec);
  pdbRecordType->papFldDes[189]->size=sizeof(prec->l132);
  pdbRecordType->papFldDes[189]->offset=(short)((char *)&prec->l132 - (char *)prec);
  pdbRecordType->papFldDes[190]->size=sizeof(prec->l133);
  pdbRecordType->papFldDes[190]->offset=(short)((char *)&prec->l133 - (char *)prec);
  pdbRecordType->papFldDes[191]->size=sizeof(prec->l134);
  pdbRecordType->papFldDes[191]->offset=(short)((char *)&prec->l134 - (char *)prec);
  pdbRecordType->papFldDes[192]->size=sizeof(prec->l135);
  pdbRecordType->papFldDes[192]->offset=(short)((char *)&prec->l135 - (char *)prec);
  pdbRecordType->papFldDes[193]->size=sizeof(prec->l136);
  pdbRecordType->papFldDes[193]->offset=(short)((char *)&prec->l136 - (char *)prec);
  pdbRecordType->papFldDes[194]->size=sizeof(prec->l137);
  pdbRecordType->papFldDes[194]->offset=(short)((char *)&prec->l137 - (char *)prec);
  pdbRecordType->papFldDes[195]->size=sizeof(prec->l138);
  pdbRecordType->papFldDes[195]->offset=(short)((char *)&prec->l138 - (char *)prec);
  pdbRecordType->papFldDes[196]->size=sizeof(prec->l139);
  pdbRecordType->papFldDes[196]->offset=(short)((char *)&prec->l139 - (char *)prec);
  pdbRecordType->papFldDes[197]->size=sizeof(prec->l140);
  pdbRecordType->papFldDes[197]->offset=(short)((char *)&prec->l140 - (char *)prec);
  pdbRecordType->papFldDes[198]->size=sizeof(prec->l141);
  pdbRecordType->papFldDes[198]->offset=(short)((char *)&prec->l141 - (char *)prec);
  pdbRecordType->papFldDes[199]->size=sizeof(prec->l142);
  pdbRecordType->papFldDes[199]->offset=(short)((char *)&prec->l142 - (char *)prec);
  pdbRecordType->papFldDes[200]->size=sizeof(prec->l143);
  pdbRecordType->papFldDes[200]->offset=(short)((char *)&prec->l143 - (char *)prec);
  pdbRecordType->papFldDes[201]->size=sizeof(prec->l144);
  pdbRecordType->papFldDes[201]->offset=(short)((char *)&prec->l144 - (char *)prec);
  pdbRecordType->papFldDes[202]->size=sizeof(prec->l145);
  pdbRecordType->papFldDes[202]->offset=(short)((char *)&prec->l145 - (char *)prec);
  pdbRecordType->papFldDes[203]->size=sizeof(prec->l146);
  pdbRecordType->papFldDes[203]->offset=(short)((char *)&prec->l146 - (char *)prec);
  pdbRecordType->papFldDes[204]->size=sizeof(prec->l147);
  pdbRecordType->papFldDes[204]->offset=(short)((char *)&prec->l147 - (char *)prec);
  pdbRecordType->papFldDes[205]->size=sizeof(prec->l148);
  pdbRecordType->papFldDes[205]->offset=(short)((char *)&prec->l148 - (char *)prec);
  pdbRecordType->papFldDes[206]->size=sizeof(prec->l149);
  pdbRecordType->papFldDes[206]->offset=(short)((char *)&prec->l149 - (char *)prec);
  pdbRecordType->papFldDes[207]->size=sizeof(prec->l150);
  pdbRecordType->papFldDes[207]->offset=(short)((char *)&prec->l150 - (char *)prec);
  pdbRecordType->papFldDes[208]->size=sizeof(prec->l151);
  pdbRecordType->papFldDes[208]->offset=(short)((char *)&prec->l151 - (char *)prec);
  pdbRecordType->papFldDes[209]->size=sizeof(prec->l152);
  pdbRecordType->papFldDes[209]->offset=(short)((char *)&prec->l152 - (char *)prec);
  pdbRecordType->papFldDes[210]->size=sizeof(prec->l153);
  pdbRecordType->papFldDes[210]->offset=(short)((char *)&prec->l153 - (char *)prec);
  pdbRecordType->papFldDes[211]->size=sizeof(prec->l154);
  pdbRecordType->papFldDes[211]->offset=(short)((char *)&prec->l154 - (char *)prec);
  pdbRecordType->papFldDes[212]->size=sizeof(prec->l155);
  pdbRecordType->papFldDes[212]->offset=(short)((char *)&prec->l155 - (char *)prec);
  pdbRecordType->papFldDes[213]->size=sizeof(prec->l156);
  pdbRecordType->papFldDes[213]->offset=(short)((char *)&prec->l156 - (char *)prec);
  pdbRecordType->papFldDes[214]->size=sizeof(prec->l157);
  pdbRecordType->papFldDes[214]->offset=(short)((char *)&prec->l157 - (char *)prec);
  pdbRecordType->papFldDes[215]->size=sizeof(prec->l158);
  pdbRecordType->papFldDes[215]->offset=(short)((char *)&prec->l158 - (char *)prec);
  pdbRecordType->papFldDes[216]->size=sizeof(prec->l159);
  pdbRecordType->papFldDes[216]->offset=(short)((char *)&prec->l159 - (char *)prec);
  pdbRecordType->papFldDes[217]->size=sizeof(prec->l160);
  pdbRecordType->papFldDes[217]->offset=(short)((char *)&prec->l160 - (char *)prec);
  pdbRecordType->papFldDes[218]->size=sizeof(prec->l161);
  pdbRecordType->papFldDes[218]->offset=(short)((char *)&prec->l161 - (char *)prec);
  pdbRecordType->papFldDes[219]->size=sizeof(prec->l162);
  pdbRecordType->papFldDes[219]->offset=(short)((char *)&prec->l162 - (char *)prec);
  pdbRecordType->papFldDes[220]->size=sizeof(prec->l163);
  pdbRecordType->papFldDes[220]->offset=(short)((char *)&prec->l163 - (char *)prec);
  pdbRecordType->papFldDes[221]->size=sizeof(prec->l164);
  pdbRecordType->papFldDes[221]->offset=(short)((char *)&prec->l164 - (char *)prec);
  pdbRecordType->papFldDes[222]->size=sizeof(prec->l165);
  pdbRecordType->papFldDes[222]->offset=(short)((char *)&prec->l165 - (char *)prec);
  pdbRecordType->papFldDes[223]->size=sizeof(prec->l166);
  pdbRecordType->papFldDes[223]->offset=(short)((char *)&prec->l166 - (char *)prec);
  pdbRecordType->papFldDes[224]->size=sizeof(prec->l167);
  pdbRecordType->papFldDes[224]->offset=(short)((char *)&prec->l167 - (char *)prec);
  pdbRecordType->papFldDes[225]->size=sizeof(prec->l168);
  pdbRecordType->papFldDes[225]->offset=(short)((char *)&prec->l168 - (char *)prec);
  pdbRecordType->papFldDes[226]->size=sizeof(prec->l169);
  pdbRecordType->papFldDes[226]->offset=(short)((char *)&prec->l169 - (char *)prec);
  pdbRecordType->papFldDes[227]->size=sizeof(prec->l170);
  pdbRecordType->papFldDes[227]->offset=(short)((char *)&prec->l170 - (char *)prec);
  pdbRecordType->papFldDes[228]->size=sizeof(prec->l171);
  pdbRecordType->papFldDes[228]->offset=(short)((char *)&prec->l171 - (char *)prec);
  pdbRecordType->papFldDes[229]->size=sizeof(prec->l172);
  pdbRecordType->papFldDes[229]->offset=(short)((char *)&prec->l172 - (char *)prec);
  pdbRecordType->papFldDes[230]->size=sizeof(prec->l173);
  pdbRecordType->papFldDes[230]->offset=(short)((char *)&prec->l173 - (char *)prec);
  pdbRecordType->papFldDes[231]->size=sizeof(prec->l174);
  pdbRecordType->papFldDes[231]->offset=(short)((char *)&prec->l174 - (char *)prec);
  pdbRecordType->papFldDes[232]->size=sizeof(prec->l175);
  pdbRecordType->papFldDes[232]->offset=(short)((char *)&prec->l175 - (char *)prec);
  pdbRecordType->papFldDes[233]->size=sizeof(prec->l176);
  pdbRecordType->papFldDes[233]->offset=(short)((char *)&prec->l176 - (char *)prec);
  pdbRecordType->papFldDes[234]->size=sizeof(prec->l177);
  pdbRecordType->papFldDes[234]->offset=(short)((char *)&prec->l177 - (char *)prec);
  pdbRecordType->papFldDes[235]->size=sizeof(prec->l178);
  pdbRecordType->papFldDes[235]->offset=(short)((char *)&prec->l178 - (char *)prec);
  pdbRecordType->papFldDes[236]->size=sizeof(prec->l179);
  pdbRecordType->papFldDes[236]->offset=(short)((char *)&prec->l179 - (char *)prec);
  pdbRecordType->papFldDes[237]->size=sizeof(prec->l180);
  pdbRecordType->papFldDes[237]->offset=(short)((char *)&prec->l180 - (char *)prec);
  pdbRecordType->papFldDes[238]->size=sizeof(prec->l181);
  pdbRecordType->papFldDes[238]->offset=(short)((char *)&prec->l181 - (char *)prec);
  pdbRecordType->papFldDes[239]->size=sizeof(prec->l182);
  pdbRecordType->papFldDes[239]->offset=(short)((char *)&prec->l182 - (char *)prec);
  pdbRecordType->papFldDes[240]->size=sizeof(prec->l183);
  pdbRecordType->papFldDes[240]->offset=(short)((char *)&prec->l183 - (char *)prec);
  pdbRecordType->papFldDes[241]->size=sizeof(prec->l184);
  pdbRecordType->papFldDes[241]->offset=(short)((char *)&prec->l184 - (char *)prec);
  pdbRecordType->papFldDes[242]->size=sizeof(prec->l185);
  pdbRecordType->papFldDes[242]->offset=(short)((char *)&prec->l185 - (char *)prec);
  pdbRecordType->papFldDes[243]->size=sizeof(prec->l186);
  pdbRecordType->papFldDes[243]->offset=(short)((char *)&prec->l186 - (char *)prec);
  pdbRecordType->papFldDes[244]->size=sizeof(prec->l187);
  pdbRecordType->papFldDes[244]->offset=(short)((char *)&prec->l187 - (char *)prec);
  pdbRecordType->papFldDes[245]->size=sizeof(prec->l188);
  pdbRecordType->papFldDes[245]->offset=(short)((char *)&prec->l188 - (char *)prec);
  pdbRecordType->papFldDes[246]->size=sizeof(prec->l189);
  pdbRecordType->papFldDes[246]->offset=(short)((char *)&prec->l189 - (char *)prec);
  pdbRecordType->papFldDes[247]->size=sizeof(prec->l190);
  pdbRecordType->papFldDes[247]->offset=(short)((char *)&prec->l190 - (char *)prec);
  pdbRecordType->papFldDes[248]->size=sizeof(prec->l191);
  pdbRecordType->papFldDes[248]->offset=(short)((char *)&prec->l191 - (char *)prec);
  pdbRecordType->papFldDes[249]->size=sizeof(prec->l192);
  pdbRecordType->papFldDes[249]->offset=(short)((char *)&prec->l192 - (char *)prec);
  pdbRecordType->papFldDes[250]->size=sizeof(prec->l193);
  pdbRecordType->papFldDes[250]->offset=(short)((char *)&prec->l193 - (char *)prec);
  pdbRecordType->papFldDes[251]->size=sizeof(prec->l194);
  pdbRecordType->papFldDes[251]->offset=(short)((char *)&prec->l194 - (char *)prec);
  pdbRecordType->papFldDes[252]->size=sizeof(prec->l195);
  pdbRecordType->papFldDes[252]->offset=(short)((char *)&prec->l195 - (char *)prec);
  pdbRecordType->papFldDes[253]->size=sizeof(prec->l196);
  pdbRecordType->papFldDes[253]->offset=(short)((char *)&prec->l196 - (char *)prec);
  pdbRecordType->papFldDes[254]->size=sizeof(prec->l197);
  pdbRecordType->papFldDes[254]->offset=(short)((char *)&prec->l197 - (char *)prec);
  pdbRecordType->papFldDes[255]->size=sizeof(prec->l198);
  pdbRecordType->papFldDes[255]->offset=(short)((char *)&prec->l198 - (char *)prec);
  pdbRecordType->papFldDes[256]->size=sizeof(prec->l199);
  pdbRecordType->papFldDes[256]->offset=(short)((char *)&prec->l199 - (char *)prec);
  pdbRecordType->papFldDes[257]->size=sizeof(prec->l200);
  pdbRecordType->papFldDes[257]->offset=(short)((char *)&prec->l200 - (char *)prec);
  pdbRecordType->papFldDes[258]->size=sizeof(prec->l201);
  pdbRecordType->papFldDes[258]->offset=(short)((char *)&prec->l201 - (char *)prec);
  pdbRecordType->papFldDes[259]->size=sizeof(prec->l202);
  pdbRecordType->papFldDes[259]->offset=(short)((char *)&prec->l202 - (char *)prec);
  pdbRecordType->papFldDes[260]->size=sizeof(prec->l203);
  pdbRecordType->papFldDes[260]->offset=(short)((char *)&prec->l203 - (char *)prec);
  pdbRecordType->papFldDes[261]->size=sizeof(prec->l204);
  pdbRecordType->papFldDes[261]->offset=(short)((char *)&prec->l204 - (char *)prec);
  pdbRecordType->papFldDes[262]->size=sizeof(prec->l205);
  pdbRecordType->papFldDes[262]->offset=(short)((char *)&prec->l205 - (char *)prec);
  pdbRecordType->papFldDes[263]->size=sizeof(prec->l206);
  pdbRecordType->papFldDes[263]->offset=(short)((char *)&prec->l206 - (char *)prec);
  pdbRecordType->papFldDes[264]->size=sizeof(prec->l207);
  pdbRecordType->papFldDes[264]->offset=(short)((char *)&prec->l207 - (char *)prec);
  pdbRecordType->papFldDes[265]->size=sizeof(prec->l208);
  pdbRecordType->papFldDes[265]->offset=(short)((char *)&prec->l208 - (char *)prec);
  pdbRecordType->papFldDes[266]->size=sizeof(prec->l209);
  pdbRecordType->papFldDes[266]->offset=(short)((char *)&prec->l209 - (char *)prec);
  pdbRecordType->papFldDes[267]->size=sizeof(prec->l210);
  pdbRecordType->papFldDes[267]->offset=(short)((char *)&prec->l210 - (char *)prec);
  pdbRecordType->papFldDes[268]->size=sizeof(prec->l211);
  pdbRecordType->papFldDes[268]->offset=(short)((char *)&prec->l211 - (char *)prec);
  pdbRecordType->papFldDes[269]->size=sizeof(prec->l212);
  pdbRecordType->papFldDes[269]->offset=(short)((char *)&prec->l212 - (char *)prec);
  pdbRecordType->papFldDes[270]->size=sizeof(prec->l213);
  pdbRecordType->papFldDes[270]->offset=(short)((char *)&prec->l213 - (char *)prec);
  pdbRecordType->papFldDes[271]->size=sizeof(prec->l214);
  pdbRecordType->papFldDes[271]->offset=(short)((char *)&prec->l214 - (char *)prec);
  pdbRecordType->papFldDes[272]->size=sizeof(prec->l215);
  pdbRecordType->papFldDes[272]->offset=(short)((char *)&prec->l215 - (char *)prec);
  pdbRecordType->papFldDes[273]->size=sizeof(prec->l216);
  pdbRecordType->papFldDes[273]->offset=(short)((char *)&prec->l216 - (char *)prec);
  pdbRecordType->papFldDes[274]->size=sizeof(prec->l217);
  pdbRecordType->papFldDes[274]->offset=(short)((char *)&prec->l217 - (char *)prec);
  pdbRecordType->papFldDes[275]->size=sizeof(prec->l218);
  pdbRecordType->papFldDes[275]->offset=(short)((char *)&prec->l218 - (char *)prec);
  pdbRecordType->papFldDes[276]->size=sizeof(prec->l219);
  pdbRecordType->papFldDes[276]->offset=(short)((char *)&prec->l219 - (char *)prec);
  pdbRecordType->papFldDes[277]->size=sizeof(prec->l220);
  pdbRecordType->papFldDes[277]->offset=(short)((char *)&prec->l220 - (char *)prec);
  pdbRecordType->papFldDes[278]->size=sizeof(prec->l221);
  pdbRecordType->papFldDes[278]->offset=(short)((char *)&prec->l221 - (char *)prec);
  pdbRecordType->papFldDes[279]->size=sizeof(prec->l222);
  pdbRecordType->papFldDes[279]->offset=(short)((char *)&prec->l222 - (char *)prec);
  pdbRecordType->papFldDes[280]->size=sizeof(prec->l223);
  pdbRecordType->papFldDes[280]->offset=(short)((char *)&prec->l223 - (char *)prec);
  pdbRecordType->papFldDes[281]->size=sizeof(prec->l224);
  pdbRecordType->papFldDes[281]->offset=(short)((char *)&prec->l224 - (char *)prec);
  pdbRecordType->papFldDes[282]->size=sizeof(prec->l225);
  pdbRecordType->papFldDes[282]->offset=(short)((char *)&prec->l225 - (char *)prec);
  pdbRecordType->papFldDes[283]->size=sizeof(prec->l226);
  pdbRecordType->papFldDes[283]->offset=(short)((char *)&prec->l226 - (char *)prec);
  pdbRecordType->papFldDes[284]->size=sizeof(prec->l227);
  pdbRecordType->papFldDes[284]->offset=(short)((char *)&prec->l227 - (char *)prec);
  pdbRecordType->papFldDes[285]->size=sizeof(prec->l228);
  pdbRecordType->papFldDes[285]->offset=(short)((char *)&prec->l228 - (char *)prec);
  pdbRecordType->papFldDes[286]->size=sizeof(prec->l229);
  pdbRecordType->papFldDes[286]->offset=(short)((char *)&prec->l229 - (char *)prec);
  pdbRecordType->papFldDes[287]->size=sizeof(prec->l230);
  pdbRecordType->papFldDes[287]->offset=(short)((char *)&prec->l230 - (char *)prec);
  pdbRecordType->papFldDes[288]->size=sizeof(prec->l231);
  pdbRecordType->papFldDes[288]->offset=(short)((char *)&prec->l231 - (char *)prec);
  pdbRecordType->papFldDes[289]->size=sizeof(prec->l232);
  pdbRecordType->papFldDes[289]->offset=(short)((char *)&prec->l232 - (char *)prec);
  pdbRecordType->papFldDes[290]->size=sizeof(prec->l233);
  pdbRecordType->papFldDes[290]->offset=(short)((char *)&prec->l233 - (char *)prec);
  pdbRecordType->papFldDes[291]->size=sizeof(prec->l234);
  pdbRecordType->papFldDes[291]->offset=(short)((char *)&prec->l234 - (char *)prec);
  pdbRecordType->papFldDes[292]->size=sizeof(prec->l235);
  pdbRecordType->papFldDes[292]->offset=(short)((char *)&prec->l235 - (char *)prec);
  pdbRecordType->papFldDes[293]->size=sizeof(prec->l236);
  pdbRecordType->papFldDes[293]->offset=(short)((char *)&prec->l236 - (char *)prec);
  pdbRecordType->papFldDes[294]->size=sizeof(prec->l237);
  pdbRecordType->papFldDes[294]->offset=(short)((char *)&prec->l237 - (char *)prec);
  pdbRecordType->papFldDes[295]->size=sizeof(prec->l238);
  pdbRecordType->papFldDes[295]->offset=(short)((char *)&prec->l238 - (char *)prec);
  pdbRecordType->papFldDes[296]->size=sizeof(prec->l239);
  pdbRecordType->papFldDes[296]->offset=(short)((char *)&prec->l239 - (char *)prec);
  pdbRecordType->papFldDes[297]->size=sizeof(prec->l240);
  pdbRecordType->papFldDes[297]->offset=(short)((char *)&prec->l240 - (char *)prec);
  pdbRecordType->papFldDes[298]->size=sizeof(prec->l241);
  pdbRecordType->papFldDes[298]->offset=(short)((char *)&prec->l241 - (char *)prec);
  pdbRecordType->papFldDes[299]->size=sizeof(prec->l242);
  pdbRecordType->papFldDes[299]->offset=(short)((char *)&prec->l242 - (char *)prec);
  pdbRecordType->papFldDes[300]->size=sizeof(prec->l243);
  pdbRecordType->papFldDes[300]->offset=(short)((char *)&prec->l243 - (char *)prec);
  pdbRecordType->papFldDes[301]->size=sizeof(prec->l244);
  pdbRecordType->papFldDes[301]->offset=(short)((char *)&prec->l244 - (char *)prec);
  pdbRecordType->papFldDes[302]->size=sizeof(prec->l245);
  pdbRecordType->papFldDes[302]->offset=(short)((char *)&prec->l245 - (char *)prec);
  pdbRecordType->papFldDes[303]->size=sizeof(prec->l246);
  pdbRecordType->papFldDes[303]->offset=(short)((char *)&prec->l246 - (char *)prec);
  pdbRecordType->papFldDes[304]->size=sizeof(prec->l247);
  pdbRecordType->papFldDes[304]->offset=(short)((char *)&prec->l247 - (char *)prec);
  pdbRecordType->papFldDes[305]->size=sizeof(prec->l248);
  pdbRecordType->papFldDes[305]->offset=(short)((char *)&prec->l248 - (char *)prec);
  pdbRecordType->papFldDes[306]->size=sizeof(prec->l249);
  pdbRecordType->papFldDes[306]->offset=(short)((char *)&prec->l249 - (char *)prec);
  pdbRecordType->papFldDes[307]->size=sizeof(prec->l250);
  pdbRecordType->papFldDes[307]->offset=(short)((char *)&prec->l250 - (char *)prec);
  pdbRecordType->papFldDes[308]->size=sizeof(prec->l251);
  pdbRecordType->papFldDes[308]->offset=(short)((char *)&prec->l251 - (char *)prec);
  pdbRecordType->papFldDes[309]->size=sizeof(prec->l252);
  pdbRecordType->papFldDes[309]->offset=(short)((char *)&prec->l252 - (char *)prec);
  pdbRecordType->papFldDes[310]->size=sizeof(prec->l253);
  pdbRecordType->papFldDes[310]->offset=(short)((char *)&prec->l253 - (char *)prec);
  pdbRecordType->papFldDes[311]->size=sizeof(prec->l254);
  pdbRecordType->papFldDes[311]->offset=(short)((char *)&prec->l254 - (char *)prec);
  pdbRecordType->papFldDes[312]->size=sizeof(prec->l255);
  pdbRecordType->papFldDes[312]->offset=(short)((char *)&prec->l255 - (char *)prec);
  pdbRecordType->papFldDes[313]->size=sizeof(prec->l256);
  pdbRecordType->papFldDes[313]->offset=(short)((char *)&prec->l256 - (char *)prec);
  pdbRecordType->papFldDes[314]->size=sizeof(prec->l257);
  pdbRecordType->papFldDes[314]->offset=(short)((char *)&prec->l257 - (char *)prec);
  pdbRecordType->papFldDes[315]->size=sizeof(prec->l258);
  pdbRecordType->papFldDes[315]->offset=(short)((char *)&prec->l258 - (char *)prec);
  pdbRecordType->papFldDes[316]->size=sizeof(prec->l259);
  pdbRecordType->papFldDes[316]->offset=(short)((char *)&prec->l259 - (char *)prec);
  pdbRecordType->papFldDes[317]->size=sizeof(prec->l260);
  pdbRecordType->papFldDes[317]->offset=(short)((char *)&prec->l260 - (char *)prec);
  pdbRecordType->papFldDes[318]->size=sizeof(prec->l261);
  pdbRecordType->papFldDes[318]->offset=(short)((char *)&prec->l261 - (char *)prec);
  pdbRecordType->papFldDes[319]->size=sizeof(prec->l262);
  pdbRecordType->papFldDes[319]->offset=(short)((char *)&prec->l262 - (char *)prec);
  pdbRecordType->papFldDes[320]->size=sizeof(prec->l263);
  pdbRecordType->papFldDes[320]->offset=(short)((char *)&prec->l263 - (char *)prec);
  pdbRecordType->papFldDes[321]->size=sizeof(prec->l264);
  pdbRecordType->papFldDes[321]->offset=(short)((char *)&prec->l264 - (char *)prec);
  pdbRecordType->papFldDes[322]->size=sizeof(prec->l265);
  pdbRecordType->papFldDes[322]->offset=(short)((char *)&prec->l265 - (char *)prec);
  pdbRecordType->papFldDes[323]->size=sizeof(prec->l266);
  pdbRecordType->papFldDes[323]->offset=(short)((char *)&prec->l266 - (char *)prec);
  pdbRecordType->papFldDes[324]->size=sizeof(prec->l267);
  pdbRecordType->papFldDes[324]->offset=(short)((char *)&prec->l267 - (char *)prec);
  pdbRecordType->papFldDes[325]->size=sizeof(prec->l268);
  pdbRecordType->papFldDes[325]->offset=(short)((char *)&prec->l268 - (char *)prec);
  pdbRecordType->papFldDes[326]->size=sizeof(prec->l269);
  pdbRecordType->papFldDes[326]->offset=(short)((char *)&prec->l269 - (char *)prec);
  pdbRecordType->papFldDes[327]->size=sizeof(prec->l270);
  pdbRecordType->papFldDes[327]->offset=(short)((char *)&prec->l270 - (char *)prec);
  pdbRecordType->papFldDes[328]->size=sizeof(prec->l271);
  pdbRecordType->papFldDes[328]->offset=(short)((char *)&prec->l271 - (char *)prec);
  pdbRecordType->papFldDes[329]->size=sizeof(prec->l272);
  pdbRecordType->papFldDes[329]->offset=(short)((char *)&prec->l272 - (char *)prec);
  pdbRecordType->papFldDes[330]->size=sizeof(prec->l273);
  pdbRecordType->papFldDes[330]->offset=(short)((char *)&prec->l273 - (char *)prec);
  pdbRecordType->papFldDes[331]->size=sizeof(prec->l274);
  pdbRecordType->papFldDes[331]->offset=(short)((char *)&prec->l274 - (char *)prec);
  pdbRecordType->papFldDes[332]->size=sizeof(prec->l275);
  pdbRecordType->papFldDes[332]->offset=(short)((char *)&prec->l275 - (char *)prec);
  pdbRecordType->papFldDes[333]->size=sizeof(prec->l276);
  pdbRecordType->papFldDes[333]->offset=(short)((char *)&prec->l276 - (char *)prec);
  pdbRecordType->papFldDes[334]->size=sizeof(prec->l277);
  pdbRecordType->papFldDes[334]->offset=(short)((char *)&prec->l277 - (char *)prec);
  pdbRecordType->papFldDes[335]->size=sizeof(prec->l278);
  pdbRecordType->papFldDes[335]->offset=(short)((char *)&prec->l278 - (char *)prec);
  pdbRecordType->papFldDes[336]->size=sizeof(prec->l279);
  pdbRecordType->papFldDes[336]->offset=(short)((char *)&prec->l279 - (char *)prec);
  pdbRecordType->papFldDes[337]->size=sizeof(prec->l280);
  pdbRecordType->papFldDes[337]->offset=(short)((char *)&prec->l280 - (char *)prec);
  pdbRecordType->papFldDes[338]->size=sizeof(prec->l281);
  pdbRecordType->papFldDes[338]->offset=(short)((char *)&prec->l281 - (char *)prec);
  pdbRecordType->papFldDes[339]->size=sizeof(prec->l282);
  pdbRecordType->papFldDes[339]->offset=(short)((char *)&prec->l282 - (char *)prec);
  pdbRecordType->papFldDes[340]->size=sizeof(prec->l283);
  pdbRecordType->papFldDes[340]->offset=(short)((char *)&prec->l283 - (char *)prec);
  pdbRecordType->papFldDes[341]->size=sizeof(prec->l284);
  pdbRecordType->papFldDes[341]->offset=(short)((char *)&prec->l284 - (char *)prec);
  pdbRecordType->papFldDes[342]->size=sizeof(prec->l285);
  pdbRecordType->papFldDes[342]->offset=(short)((char *)&prec->l285 - (char *)prec);
  pdbRecordType->papFldDes[343]->size=sizeof(prec->l286);
  pdbRecordType->papFldDes[343]->offset=(short)((char *)&prec->l286 - (char *)prec);
  pdbRecordType->papFldDes[344]->size=sizeof(prec->l287);
  pdbRecordType->papFldDes[344]->offset=(short)((char *)&prec->l287 - (char *)prec);
  pdbRecordType->papFldDes[345]->size=sizeof(prec->l288);
  pdbRecordType->papFldDes[345]->offset=(short)((char *)&prec->l288 - (char *)prec);
  pdbRecordType->papFldDes[346]->size=sizeof(prec->l289);
  pdbRecordType->papFldDes[346]->offset=(short)((char *)&prec->l289 - (char *)prec);
  pdbRecordType->papFldDes[347]->size=sizeof(prec->l290);
  pdbRecordType->papFldDes[347]->offset=(short)((char *)&prec->l290 - (char *)prec);
  pdbRecordType->papFldDes[348]->size=sizeof(prec->l291);
  pdbRecordType->papFldDes[348]->offset=(short)((char *)&prec->l291 - (char *)prec);
  pdbRecordType->papFldDes[349]->size=sizeof(prec->l292);
  pdbRecordType->papFldDes[349]->offset=(short)((char *)&prec->l292 - (char *)prec);
  pdbRecordType->papFldDes[350]->size=sizeof(prec->l293);
  pdbRecordType->papFldDes[350]->offset=(short)((char *)&prec->l293 - (char *)prec);
  pdbRecordType->papFldDes[351]->size=sizeof(prec->l294);
  pdbRecordType->papFldDes[351]->offset=(short)((char *)&prec->l294 - (char *)prec);
  pdbRecordType->papFldDes[352]->size=sizeof(prec->l295);
  pdbRecordType->papFldDes[352]->offset=(short)((char *)&prec->l295 - (char *)prec);
  pdbRecordType->papFldDes[353]->size=sizeof(prec->l296);
  pdbRecordType->papFldDes[353]->offset=(short)((char *)&prec->l296 - (char *)prec);
  pdbRecordType->papFldDes[354]->size=sizeof(prec->l297);
  pdbRecordType->papFldDes[354]->offset=(short)((char *)&prec->l297 - (char *)prec);
  pdbRecordType->papFldDes[355]->size=sizeof(prec->l298);
  pdbRecordType->papFldDes[355]->offset=(short)((char *)&prec->l298 - (char *)prec);
  pdbRecordType->papFldDes[356]->size=sizeof(prec->l299);
  pdbRecordType->papFldDes[356]->offset=(short)((char *)&prec->l299 - (char *)prec);
  pdbRecordType->papFldDes[357]->size=sizeof(prec->l300);
  pdbRecordType->papFldDes[357]->offset=(short)((char *)&prec->l300 - (char *)prec);
  pdbRecordType->papFldDes[358]->size=sizeof(prec->l301);
  pdbRecordType->papFldDes[358]->offset=(short)((char *)&prec->l301 - (char *)prec);
  pdbRecordType->papFldDes[359]->size=sizeof(prec->l302);
  pdbRecordType->papFldDes[359]->offset=(short)((char *)&prec->l302 - (char *)prec);
  pdbRecordType->papFldDes[360]->size=sizeof(prec->l303);
  pdbRecordType->papFldDes[360]->offset=(short)((char *)&prec->l303 - (char *)prec);
  pdbRecordType->papFldDes[361]->size=sizeof(prec->l304);
  pdbRecordType->papFldDes[361]->offset=(short)((char *)&prec->l304 - (char *)prec);
  pdbRecordType->papFldDes[362]->size=sizeof(prec->l305);
  pdbRecordType->papFldDes[362]->offset=(short)((char *)&prec->l305 - (char *)prec);
  pdbRecordType->papFldDes[363]->size=sizeof(prec->l306);
  pdbRecordType->papFldDes[363]->offset=(short)((char *)&prec->l306 - (char *)prec);
  pdbRecordType->papFldDes[364]->size=sizeof(prec->l307);
  pdbRecordType->papFldDes[364]->offset=(short)((char *)&prec->l307 - (char *)prec);
  pdbRecordType->papFldDes[365]->size=sizeof(prec->l308);
  pdbRecordType->papFldDes[365]->offset=(short)((char *)&prec->l308 - (char *)prec);
  pdbRecordType->papFldDes[366]->size=sizeof(prec->l309);
  pdbRecordType->papFldDes[366]->offset=(short)((char *)&prec->l309 - (char *)prec);
  pdbRecordType->papFldDes[367]->size=sizeof(prec->l310);
  pdbRecordType->papFldDes[367]->offset=(short)((char *)&prec->l310 - (char *)prec);
  pdbRecordType->papFldDes[368]->size=sizeof(prec->l311);
  pdbRecordType->papFldDes[368]->offset=(short)((char *)&prec->l311 - (char *)prec);
  pdbRecordType->papFldDes[369]->size=sizeof(prec->l312);
  pdbRecordType->papFldDes[369]->offset=(short)((char *)&prec->l312 - (char *)prec);
  pdbRecordType->papFldDes[370]->size=sizeof(prec->l313);
  pdbRecordType->papFldDes[370]->offset=(short)((char *)&prec->l313 - (char *)prec);
  pdbRecordType->papFldDes[371]->size=sizeof(prec->l314);
  pdbRecordType->papFldDes[371]->offset=(short)((char *)&prec->l314 - (char *)prec);
  pdbRecordType->papFldDes[372]->size=sizeof(prec->l315);
  pdbRecordType->papFldDes[372]->offset=(short)((char *)&prec->l315 - (char *)prec);
  pdbRecordType->papFldDes[373]->size=sizeof(prec->l316);
  pdbRecordType->papFldDes[373]->offset=(short)((char *)&prec->l316 - (char *)prec);
  pdbRecordType->papFldDes[374]->size=sizeof(prec->l317);
  pdbRecordType->papFldDes[374]->offset=(short)((char *)&prec->l317 - (char *)prec);
  pdbRecordType->papFldDes[375]->size=sizeof(prec->l318);
  pdbRecordType->papFldDes[375]->offset=(short)((char *)&prec->l318 - (char *)prec);
  pdbRecordType->papFldDes[376]->size=sizeof(prec->l319);
  pdbRecordType->papFldDes[376]->offset=(short)((char *)&prec->l319 - (char *)prec);
  pdbRecordType->papFldDes[377]->size=sizeof(prec->l320);
  pdbRecordType->papFldDes[377]->offset=(short)((char *)&prec->l320 - (char *)prec);
  pdbRecordType->papFldDes[378]->size=sizeof(prec->l321);
  pdbRecordType->papFldDes[378]->offset=(short)((char *)&prec->l321 - (char *)prec);
  pdbRecordType->papFldDes[379]->size=sizeof(prec->l322);
  pdbRecordType->papFldDes[379]->offset=(short)((char *)&prec->l322 - (char *)prec);
  pdbRecordType->papFldDes[380]->size=sizeof(prec->l323);
  pdbRecordType->papFldDes[380]->offset=(short)((char *)&prec->l323 - (char *)prec);
  pdbRecordType->papFldDes[381]->size=sizeof(prec->l324);
  pdbRecordType->papFldDes[381]->offset=(short)((char *)&prec->l324 - (char *)prec);
  pdbRecordType->papFldDes[382]->size=sizeof(prec->l325);
  pdbRecordType->papFldDes[382]->offset=(short)((char *)&prec->l325 - (char *)prec);
  pdbRecordType->papFldDes[383]->size=sizeof(prec->l326);
  pdbRecordType->papFldDes[383]->offset=(short)((char *)&prec->l326 - (char *)prec);
  pdbRecordType->papFldDes[384]->size=sizeof(prec->l327);
  pdbRecordType->papFldDes[384]->offset=(short)((char *)&prec->l327 - (char *)prec);
  pdbRecordType->papFldDes[385]->size=sizeof(prec->l328);
  pdbRecordType->papFldDes[385]->offset=(short)((char *)&prec->l328 - (char *)prec);
  pdbRecordType->papFldDes[386]->size=sizeof(prec->l329);
  pdbRecordType->papFldDes[386]->offset=(short)((char *)&prec->l329 - (char *)prec);
  pdbRecordType->papFldDes[387]->size=sizeof(prec->l330);
  pdbRecordType->papFldDes[387]->offset=(short)((char *)&prec->l330 - (char *)prec);
  pdbRecordType->papFldDes[388]->size=sizeof(prec->l331);
  pdbRecordType->papFldDes[388]->offset=(short)((char *)&prec->l331 - (char *)prec);
  pdbRecordType->papFldDes[389]->size=sizeof(prec->l332);
  pdbRecordType->papFldDes[389]->offset=(short)((char *)&prec->l332 - (char *)prec);
  pdbRecordType->papFldDes[390]->size=sizeof(prec->l333);
  pdbRecordType->papFldDes[390]->offset=(short)((char *)&prec->l333 - (char *)prec);
  pdbRecordType->papFldDes[391]->size=sizeof(prec->l334);
  pdbRecordType->papFldDes[391]->offset=(short)((char *)&prec->l334 - (char *)prec);
  pdbRecordType->papFldDes[392]->size=sizeof(prec->l335);
  pdbRecordType->papFldDes[392]->offset=(short)((char *)&prec->l335 - (char *)prec);
  pdbRecordType->papFldDes[393]->size=sizeof(prec->l336);
  pdbRecordType->papFldDes[393]->offset=(short)((char *)&prec->l336 - (char *)prec);
  pdbRecordType->papFldDes[394]->size=sizeof(prec->l337);
  pdbRecordType->papFldDes[394]->offset=(short)((char *)&prec->l337 - (char *)prec);
  pdbRecordType->papFldDes[395]->size=sizeof(prec->l338);
  pdbRecordType->papFldDes[395]->offset=(short)((char *)&prec->l338 - (char *)prec);
  pdbRecordType->papFldDes[396]->size=sizeof(prec->l339);
  pdbRecordType->papFldDes[396]->offset=(short)((char *)&prec->l339 - (char *)prec);
  pdbRecordType->papFldDes[397]->size=sizeof(prec->l340);
  pdbRecordType->papFldDes[397]->offset=(short)((char *)&prec->l340 - (char *)prec);
  pdbRecordType->papFldDes[398]->size=sizeof(prec->l341);
  pdbRecordType->papFldDes[398]->offset=(short)((char *)&prec->l341 - (char *)prec);
  pdbRecordType->papFldDes[399]->size=sizeof(prec->l342);
  pdbRecordType->papFldDes[399]->offset=(short)((char *)&prec->l342 - (char *)prec);
  pdbRecordType->papFldDes[400]->size=sizeof(prec->l343);
  pdbRecordType->papFldDes[400]->offset=(short)((char *)&prec->l343 - (char *)prec);
  pdbRecordType->papFldDes[401]->size=sizeof(prec->l344);
  pdbRecordType->papFldDes[401]->offset=(short)((char *)&prec->l344 - (char *)prec);
  pdbRecordType->papFldDes[402]->size=sizeof(prec->l345);
  pdbRecordType->papFldDes[402]->offset=(short)((char *)&prec->l345 - (char *)prec);
  pdbRecordType->papFldDes[403]->size=sizeof(prec->l346);
  pdbRecordType->papFldDes[403]->offset=(short)((char *)&prec->l346 - (char *)prec);
  pdbRecordType->papFldDes[404]->size=sizeof(prec->l347);
  pdbRecordType->papFldDes[404]->offset=(short)((char *)&prec->l347 - (char *)prec);
  pdbRecordType->papFldDes[405]->size=sizeof(prec->l348);
  pdbRecordType->papFldDes[405]->offset=(short)((char *)&prec->l348 - (char *)prec);
  pdbRecordType->papFldDes[406]->size=sizeof(prec->l349);
  pdbRecordType->papFldDes[406]->offset=(short)((char *)&prec->l349 - (char *)prec);
  pdbRecordType->papFldDes[407]->size=sizeof(prec->l350);
  pdbRecordType->papFldDes[407]->offset=(short)((char *)&prec->l350 - (char *)prec);
  pdbRecordType->papFldDes[408]->size=sizeof(prec->l351);
  pdbRecordType->papFldDes[408]->offset=(short)((char *)&prec->l351 - (char *)prec);
  pdbRecordType->papFldDes[409]->size=sizeof(prec->l352);
  pdbRecordType->papFldDes[409]->offset=(short)((char *)&prec->l352 - (char *)prec);
  pdbRecordType->papFldDes[410]->size=sizeof(prec->l353);
  pdbRecordType->papFldDes[410]->offset=(short)((char *)&prec->l353 - (char *)prec);
  pdbRecordType->papFldDes[411]->size=sizeof(prec->l354);
  pdbRecordType->papFldDes[411]->offset=(short)((char *)&prec->l354 - (char *)prec);
  pdbRecordType->papFldDes[412]->size=sizeof(prec->l355);
  pdbRecordType->papFldDes[412]->offset=(short)((char *)&prec->l355 - (char *)prec);
  pdbRecordType->papFldDes[413]->size=sizeof(prec->l356);
  pdbRecordType->papFldDes[413]->offset=(short)((char *)&prec->l356 - (char *)prec);
  pdbRecordType->papFldDes[414]->size=sizeof(prec->l357);
  pdbRecordType->papFldDes[414]->offset=(short)((char *)&prec->l357 - (char *)prec);
  pdbRecordType->papFldDes[415]->size=sizeof(prec->l358);
  pdbRecordType->papFldDes[415]->offset=(short)((char *)&prec->l358 - (char *)prec);
  pdbRecordType->papFldDes[416]->size=sizeof(prec->l359);
  pdbRecordType->papFldDes[416]->offset=(short)((char *)&prec->l359 - (char *)prec);
  pdbRecordType->papFldDes[417]->size=sizeof(prec->l360);
  pdbRecordType->papFldDes[417]->offset=(short)((char *)&prec->l360 - (char *)prec);
  pdbRecordType->papFldDes[418]->size=sizeof(prec->l361);
  pdbRecordType->papFldDes[418]->offset=(short)((char *)&prec->l361 - (char *)prec);
  pdbRecordType->papFldDes[419]->size=sizeof(prec->l362);
  pdbRecordType->papFldDes[419]->offset=(short)((char *)&prec->l362 - (char *)prec);
  pdbRecordType->papFldDes[420]->size=sizeof(prec->l363);
  pdbRecordType->papFldDes[420]->offset=(short)((char *)&prec->l363 - (char *)prec);
  pdbRecordType->papFldDes[421]->size=sizeof(prec->l364);
  pdbRecordType->papFldDes[421]->offset=(short)((char *)&prec->l364 - (char *)prec);
  pdbRecordType->papFldDes[422]->size=sizeof(prec->l365);
  pdbRecordType->papFldDes[422]->offset=(short)((char *)&prec->l365 - (char *)prec);
  pdbRecordType->papFldDes[423]->size=sizeof(prec->l366);
  pdbRecordType->papFldDes[423]->offset=(short)((char *)&prec->l366 - (char *)prec);
  pdbRecordType->papFldDes[424]->size=sizeof(prec->l367);
  pdbRecordType->papFldDes[424]->offset=(short)((char *)&prec->l367 - (char *)prec);
  pdbRecordType->papFldDes[425]->size=sizeof(prec->l368);
  pdbRecordType->papFldDes[425]->offset=(short)((char *)&prec->l368 - (char *)prec);
  pdbRecordType->papFldDes[426]->size=sizeof(prec->l369);
  pdbRecordType->papFldDes[426]->offset=(short)((char *)&prec->l369 - (char *)prec);
  pdbRecordType->papFldDes[427]->size=sizeof(prec->l370);
  pdbRecordType->papFldDes[427]->offset=(short)((char *)&prec->l370 - (char *)prec);
  pdbRecordType->papFldDes[428]->size=sizeof(prec->l371);
  pdbRecordType->papFldDes[428]->offset=(short)((char *)&prec->l371 - (char *)prec);
  pdbRecordType->papFldDes[429]->size=sizeof(prec->l372);
  pdbRecordType->papFldDes[429]->offset=(short)((char *)&prec->l372 - (char *)prec);
  pdbRecordType->papFldDes[430]->size=sizeof(prec->l373);
  pdbRecordType->papFldDes[430]->offset=(short)((char *)&prec->l373 - (char *)prec);
  pdbRecordType->papFldDes[431]->size=sizeof(prec->l374);
  pdbRecordType->papFldDes[431]->offset=(short)((char *)&prec->l374 - (char *)prec);
  pdbRecordType->papFldDes[432]->size=sizeof(prec->l375);
  pdbRecordType->papFldDes[432]->offset=(short)((char *)&prec->l375 - (char *)prec);
  pdbRecordType->papFldDes[433]->size=sizeof(prec->l376);
  pdbRecordType->papFldDes[433]->offset=(short)((char *)&prec->l376 - (char *)prec);
  pdbRecordType->papFldDes[434]->size=sizeof(prec->l377);
  pdbRecordType->papFldDes[434]->offset=(short)((char *)&prec->l377 - (char *)prec);
  pdbRecordType->papFldDes[435]->size=sizeof(prec->l378);
  pdbRecordType->papFldDes[435]->offset=(short)((char *)&prec->l378 - (char *)prec);
  pdbRecordType->papFldDes[436]->size=sizeof(prec->l379);
  pdbRecordType->papFldDes[436]->offset=(short)((char *)&prec->l379 - (char *)prec);
  pdbRecordType->papFldDes[437]->size=sizeof(prec->l380);
  pdbRecordType->papFldDes[437]->offset=(short)((char *)&prec->l380 - (char *)prec);
  pdbRecordType->papFldDes[438]->size=sizeof(prec->l381);
  pdbRecordType->papFldDes[438]->offset=(short)((char *)&prec->l381 - (char *)prec);
  pdbRecordType->papFldDes[439]->size=sizeof(prec->l382);
  pdbRecordType->papFldDes[439]->offset=(short)((char *)&prec->l382 - (char *)prec);
  pdbRecordType->papFldDes[440]->size=sizeof(prec->l383);
  pdbRecordType->papFldDes[440]->offset=(short)((char *)&prec->l383 - (char *)prec);
  pdbRecordType->papFldDes[441]->size=sizeof(prec->l384);
  pdbRecordType->papFldDes[441]->offset=(short)((char *)&prec->l384 - (char *)prec);
  pdbRecordType->papFldDes[442]->size=sizeof(prec->l385);
  pdbRecordType->papFldDes[442]->offset=(short)((char *)&prec->l385 - (char *)prec);
  pdbRecordType->papFldDes[443]->size=sizeof(prec->l386);
  pdbRecordType->papFldDes[443]->offset=(short)((char *)&prec->l386 - (char *)prec);
  pdbRecordType->papFldDes[444]->size=sizeof(prec->l387);
  pdbRecordType->papFldDes[444]->offset=(short)((char *)&prec->l387 - (char *)prec);
  pdbRecordType->papFldDes[445]->size=sizeof(prec->l388);
  pdbRecordType->papFldDes[445]->offset=(short)((char *)&prec->l388 - (char *)prec);
  pdbRecordType->papFldDes[446]->size=sizeof(prec->l389);
  pdbRecordType->papFldDes[446]->offset=(short)((char *)&prec->l389 - (char *)prec);
  pdbRecordType->papFldDes[447]->size=sizeof(prec->l390);
  pdbRecordType->papFldDes[447]->offset=(short)((char *)&prec->l390 - (char *)prec);
  pdbRecordType->papFldDes[448]->size=sizeof(prec->l391);
  pdbRecordType->papFldDes[448]->offset=(short)((char *)&prec->l391 - (char *)prec);
  pdbRecordType->papFldDes[449]->size=sizeof(prec->l392);
  pdbRecordType->papFldDes[449]->offset=(short)((char *)&prec->l392 - (char *)prec);
  pdbRecordType->papFldDes[450]->size=sizeof(prec->l393);
  pdbRecordType->papFldDes[450]->offset=(short)((char *)&prec->l393 - (char *)prec);
  pdbRecordType->papFldDes[451]->size=sizeof(prec->l394);
  pdbRecordType->papFldDes[451]->offset=(short)((char *)&prec->l394 - (char *)prec);
  pdbRecordType->papFldDes[452]->size=sizeof(prec->l395);
  pdbRecordType->papFldDes[452]->offset=(short)((char *)&prec->l395 - (char *)prec);
  pdbRecordType->papFldDes[453]->size=sizeof(prec->l396);
  pdbRecordType->papFldDes[453]->offset=(short)((char *)&prec->l396 - (char *)prec);
  pdbRecordType->papFldDes[454]->size=sizeof(prec->l397);
  pdbRecordType->papFldDes[454]->offset=(short)((char *)&prec->l397 - (char *)prec);
  pdbRecordType->papFldDes[455]->size=sizeof(prec->l398);
  pdbRecordType->papFldDes[455]->offset=(short)((char *)&prec->l398 - (char *)prec);
  pdbRecordType->papFldDes[456]->size=sizeof(prec->l399);
  pdbRecordType->papFldDes[456]->offset=(short)((char *)&prec->l399 - (char *)prec);
  pdbRecordType->papFldDes[457]->size=sizeof(prec->l400);
  pdbRecordType->papFldDes[457]->offset=(short)((char *)&prec->l400 - (char *)prec);
  pdbRecordType->papFldDes[458]->size=sizeof(prec->l401);
  pdbRecordType->papFldDes[458]->offset=(short)((char *)&prec->l401 - (char *)prec);
  pdbRecordType->papFldDes[459]->size=sizeof(prec->l402);
  pdbRecordType->papFldDes[459]->offset=(short)((char *)&prec->l402 - (char *)prec);
  pdbRecordType->papFldDes[460]->size=sizeof(prec->l403);
  pdbRecordType->papFldDes[460]->offset=(short)((char *)&prec->l403 - (char *)prec);
  pdbRecordType->papFldDes[461]->size=sizeof(prec->l404);
  pdbRecordType->papFldDes[461]->offset=(short)((char *)&prec->l404 - (char *)prec);
  pdbRecordType->papFldDes[462]->size=sizeof(prec->l405);
  pdbRecordType->papFldDes[462]->offset=(short)((char *)&prec->l405 - (char *)prec);
  pdbRecordType->papFldDes[463]->size=sizeof(prec->l406);
  pdbRecordType->papFldDes[463]->offset=(short)((char *)&prec->l406 - (char *)prec);
  pdbRecordType->papFldDes[464]->size=sizeof(prec->l407);
  pdbRecordType->papFldDes[464]->offset=(short)((char *)&prec->l407 - (char *)prec);
  pdbRecordType->papFldDes[465]->size=sizeof(prec->l408);
  pdbRecordType->papFldDes[465]->offset=(short)((char *)&prec->l408 - (char *)prec);
  pdbRecordType->papFldDes[466]->size=sizeof(prec->l409);
  pdbRecordType->papFldDes[466]->offset=(short)((char *)&prec->l409 - (char *)prec);
  pdbRecordType->papFldDes[467]->size=sizeof(prec->l410);
  pdbRecordType->papFldDes[467]->offset=(short)((char *)&prec->l410 - (char *)prec);
  pdbRecordType->papFldDes[468]->size=sizeof(prec->l411);
  pdbRecordType->papFldDes[468]->offset=(short)((char *)&prec->l411 - (char *)prec);
  pdbRecordType->papFldDes[469]->size=sizeof(prec->l412);
  pdbRecordType->papFldDes[469]->offset=(short)((char *)&prec->l412 - (char *)prec);
  pdbRecordType->papFldDes[470]->size=sizeof(prec->l413);
  pdbRecordType->papFldDes[470]->offset=(short)((char *)&prec->l413 - (char *)prec);
  pdbRecordType->papFldDes[471]->size=sizeof(prec->l414);
  pdbRecordType->papFldDes[471]->offset=(short)((char *)&prec->l414 - (char *)prec);
  pdbRecordType->papFldDes[472]->size=sizeof(prec->l415);
  pdbRecordType->papFldDes[472]->offset=(short)((char *)&prec->l415 - (char *)prec);
  pdbRecordType->papFldDes[473]->size=sizeof(prec->l416);
  pdbRecordType->papFldDes[473]->offset=(short)((char *)&prec->l416 - (char *)prec);
  pdbRecordType->papFldDes[474]->size=sizeof(prec->l417);
  pdbRecordType->papFldDes[474]->offset=(short)((char *)&prec->l417 - (char *)prec);
  pdbRecordType->papFldDes[475]->size=sizeof(prec->l418);
  pdbRecordType->papFldDes[475]->offset=(short)((char *)&prec->l418 - (char *)prec);
  pdbRecordType->papFldDes[476]->size=sizeof(prec->l419);
  pdbRecordType->papFldDes[476]->offset=(short)((char *)&prec->l419 - (char *)prec);
  pdbRecordType->papFldDes[477]->size=sizeof(prec->l420);
  pdbRecordType->papFldDes[477]->offset=(short)((char *)&prec->l420 - (char *)prec);
  pdbRecordType->papFldDes[478]->size=sizeof(prec->l421);
  pdbRecordType->papFldDes[478]->offset=(short)((char *)&prec->l421 - (char *)prec);
  pdbRecordType->papFldDes[479]->size=sizeof(prec->l422);
  pdbRecordType->papFldDes[479]->offset=(short)((char *)&prec->l422 - (char *)prec);
  pdbRecordType->papFldDes[480]->size=sizeof(prec->l423);
  pdbRecordType->papFldDes[480]->offset=(short)((char *)&prec->l423 - (char *)prec);
  pdbRecordType->papFldDes[481]->size=sizeof(prec->l424);
  pdbRecordType->papFldDes[481]->offset=(short)((char *)&prec->l424 - (char *)prec);
  pdbRecordType->papFldDes[482]->size=sizeof(prec->l425);
  pdbRecordType->papFldDes[482]->offset=(short)((char *)&prec->l425 - (char *)prec);
  pdbRecordType->papFldDes[483]->size=sizeof(prec->l426);
  pdbRecordType->papFldDes[483]->offset=(short)((char *)&prec->l426 - (char *)prec);
  pdbRecordType->papFldDes[484]->size=sizeof(prec->l427);
  pdbRecordType->papFldDes[484]->offset=(short)((char *)&prec->l427 - (char *)prec);
  pdbRecordType->papFldDes[485]->size=sizeof(prec->l428);
  pdbRecordType->papFldDes[485]->offset=(short)((char *)&prec->l428 - (char *)prec);
  pdbRecordType->papFldDes[486]->size=sizeof(prec->l429);
  pdbRecordType->papFldDes[486]->offset=(short)((char *)&prec->l429 - (char *)prec);
  pdbRecordType->papFldDes[487]->size=sizeof(prec->l430);
  pdbRecordType->papFldDes[487]->offset=(short)((char *)&prec->l430 - (char *)prec);
  pdbRecordType->papFldDes[488]->size=sizeof(prec->l431);
  pdbRecordType->papFldDes[488]->offset=(short)((char *)&prec->l431 - (char *)prec);
  pdbRecordType->papFldDes[489]->size=sizeof(prec->l432);
  pdbRecordType->papFldDes[489]->offset=(short)((char *)&prec->l432 - (char *)prec);
  pdbRecordType->papFldDes[490]->size=sizeof(prec->l433);
  pdbRecordType->papFldDes[490]->offset=(short)((char *)&prec->l433 - (char *)prec);
  pdbRecordType->papFldDes[491]->size=sizeof(prec->l434);
  pdbRecordType->papFldDes[491]->offset=(short)((char *)&prec->l434 - (char *)prec);
  pdbRecordType->papFldDes[492]->size=sizeof(prec->l435);
  pdbRecordType->papFldDes[492]->offset=(short)((char *)&prec->l435 - (char *)prec);
  pdbRecordType->papFldDes[493]->size=sizeof(prec->l436);
  pdbRecordType->papFldDes[493]->offset=(short)((char *)&prec->l436 - (char *)prec);
  pdbRecordType->papFldDes[494]->size=sizeof(prec->l437);
  pdbRecordType->papFldDes[494]->offset=(short)((char *)&prec->l437 - (char *)prec);
  pdbRecordType->papFldDes[495]->size=sizeof(prec->l438);
  pdbRecordType->papFldDes[495]->offset=(short)((char *)&prec->l438 - (char *)prec);
  pdbRecordType->papFldDes[496]->size=sizeof(prec->l439);
  pdbRecordType->papFldDes[496]->offset=(short)((char *)&prec->l439 - (char *)prec);
  pdbRecordType->papFldDes[497]->size=sizeof(prec->l440);
  pdbRecordType->papFldDes[497]->offset=(short)((char *)&prec->l440 - (char *)prec);
  pdbRecordType->papFldDes[498]->size=sizeof(prec->l441);
  pdbRecordType->papFldDes[498]->offset=(short)((char *)&prec->l441 - (char *)prec);
  pdbRecordType->papFldDes[499]->size=sizeof(prec->l442);
  pdbRecordType->papFldDes[499]->offset=(short)((char *)&prec->l442 - (char *)prec);
  pdbRecordType->papFldDes[500]->size=sizeof(prec->l443);
  pdbRecordType->papFldDes[500]->offset=(short)((char *)&prec->l443 - (char *)prec);
  pdbRecordType->papFldDes[501]->size=sizeof(prec->l444);
  pdbRecordType->papFldDes[501]->offset=(short)((char *)&prec->l444 - (char *)prec);
  pdbRecordType->papFldDes[502]->size=sizeof(prec->l445);
  pdbRecordType->papFldDes[502]->offset=(short)((char *)&prec->l445 - (char *)prec);
  pdbRecordType->papFldDes[503]->size=sizeof(prec->l446);
  pdbRecordType->papFldDes[503]->offset=(short)((char *)&prec->l446 - (char *)prec);
  pdbRecordType->papFldDes[504]->size=sizeof(prec->l447);
  pdbRecordType->papFldDes[504]->offset=(short)((char *)&prec->l447 - (char *)prec);
  pdbRecordType->papFldDes[505]->size=sizeof(prec->l448);
  pdbRecordType->papFldDes[505]->offset=(short)((char *)&prec->l448 - (char *)prec);
  pdbRecordType->papFldDes[506]->size=sizeof(prec->l449);
  pdbRecordType->papFldDes[506]->offset=(short)((char *)&prec->l449 - (char *)prec);
  pdbRecordType->papFldDes[507]->size=sizeof(prec->l450);
  pdbRecordType->papFldDes[507]->offset=(short)((char *)&prec->l450 - (char *)prec);
  pdbRecordType->papFldDes[508]->size=sizeof(prec->l451);
  pdbRecordType->papFldDes[508]->offset=(short)((char *)&prec->l451 - (char *)prec);
  pdbRecordType->papFldDes[509]->size=sizeof(prec->l452);
  pdbRecordType->papFldDes[509]->offset=(short)((char *)&prec->l452 - (char *)prec);
  pdbRecordType->papFldDes[510]->size=sizeof(prec->l453);
  pdbRecordType->papFldDes[510]->offset=(short)((char *)&prec->l453 - (char *)prec);
  pdbRecordType->papFldDes[511]->size=sizeof(prec->l454);
  pdbRecordType->papFldDes[511]->offset=(short)((char *)&prec->l454 - (char *)prec);
  pdbRecordType->papFldDes[512]->size=sizeof(prec->l455);
  pdbRecordType->papFldDes[512]->offset=(short)((char *)&prec->l455 - (char *)prec);
  pdbRecordType->papFldDes[513]->size=sizeof(prec->l456);
  pdbRecordType->papFldDes[513]->offset=(short)((char *)&prec->l456 - (char *)prec);
  pdbRecordType->papFldDes[514]->size=sizeof(prec->l457);
  pdbRecordType->papFldDes[514]->offset=(short)((char *)&prec->l457 - (char *)prec);
  pdbRecordType->papFldDes[515]->size=sizeof(prec->l458);
  pdbRecordType->papFldDes[515]->offset=(short)((char *)&prec->l458 - (char *)prec);
  pdbRecordType->papFldDes[516]->size=sizeof(prec->l459);
  pdbRecordType->papFldDes[516]->offset=(short)((char *)&prec->l459 - (char *)prec);
  pdbRecordType->papFldDes[517]->size=sizeof(prec->l460);
  pdbRecordType->papFldDes[517]->offset=(short)((char *)&prec->l460 - (char *)prec);
  pdbRecordType->papFldDes[518]->size=sizeof(prec->l461);
  pdbRecordType->papFldDes[518]->offset=(short)((char *)&prec->l461 - (char *)prec);
  pdbRecordType->papFldDes[519]->size=sizeof(prec->l462);
  pdbRecordType->papFldDes[519]->offset=(short)((char *)&prec->l462 - (char *)prec);
  pdbRecordType->papFldDes[520]->size=sizeof(prec->l463);
  pdbRecordType->papFldDes[520]->offset=(short)((char *)&prec->l463 - (char *)prec);
  pdbRecordType->papFldDes[521]->size=sizeof(prec->l464);
  pdbRecordType->papFldDes[521]->offset=(short)((char *)&prec->l464 - (char *)prec);
  pdbRecordType->papFldDes[522]->size=sizeof(prec->l465);
  pdbRecordType->papFldDes[522]->offset=(short)((char *)&prec->l465 - (char *)prec);
  pdbRecordType->papFldDes[523]->size=sizeof(prec->l466);
  pdbRecordType->papFldDes[523]->offset=(short)((char *)&prec->l466 - (char *)prec);
  pdbRecordType->papFldDes[524]->size=sizeof(prec->l467);
  pdbRecordType->papFldDes[524]->offset=(short)((char *)&prec->l467 - (char *)prec);
  pdbRecordType->papFldDes[525]->size=sizeof(prec->l468);
  pdbRecordType->papFldDes[525]->offset=(short)((char *)&prec->l468 - (char *)prec);
  pdbRecordType->papFldDes[526]->size=sizeof(prec->l469);
  pdbRecordType->papFldDes[526]->offset=(short)((char *)&prec->l469 - (char *)prec);
  pdbRecordType->papFldDes[527]->size=sizeof(prec->l470);
  pdbRecordType->papFldDes[527]->offset=(short)((char *)&prec->l470 - (char *)prec);
  pdbRecordType->papFldDes[528]->size=sizeof(prec->l471);
  pdbRecordType->papFldDes[528]->offset=(short)((char *)&prec->l471 - (char *)prec);
  pdbRecordType->papFldDes[529]->size=sizeof(prec->l472);
  pdbRecordType->papFldDes[529]->offset=(short)((char *)&prec->l472 - (char *)prec);
  pdbRecordType->papFldDes[530]->size=sizeof(prec->l473);
  pdbRecordType->papFldDes[530]->offset=(short)((char *)&prec->l473 - (char *)prec);
  pdbRecordType->papFldDes[531]->size=sizeof(prec->l474);
  pdbRecordType->papFldDes[531]->offset=(short)((char *)&prec->l474 - (char *)prec);
  pdbRecordType->papFldDes[532]->size=sizeof(prec->l475);
  pdbRecordType->papFldDes[532]->offset=(short)((char *)&prec->l475 - (char *)prec);
  pdbRecordType->papFldDes[533]->size=sizeof(prec->l476);
  pdbRecordType->papFldDes[533]->offset=(short)((char *)&prec->l476 - (char *)prec);
  pdbRecordType->papFldDes[534]->size=sizeof(prec->l477);
  pdbRecordType->papFldDes[534]->offset=(short)((char *)&prec->l477 - (char *)prec);
  pdbRecordType->papFldDes[535]->size=sizeof(prec->l478);
  pdbRecordType->papFldDes[535]->offset=(short)((char *)&prec->l478 - (char *)prec);
  pdbRecordType->papFldDes[536]->size=sizeof(prec->l479);
  pdbRecordType->papFldDes[536]->offset=(short)((char *)&prec->l479 - (char *)prec);
  pdbRecordType->papFldDes[537]->size=sizeof(prec->l480);
  pdbRecordType->papFldDes[537]->offset=(short)((char *)&prec->l480 - (char *)prec);
  pdbRecordType->papFldDes[538]->size=sizeof(prec->l481);
  pdbRecordType->papFldDes[538]->offset=(short)((char *)&prec->l481 - (char *)prec);
  pdbRecordType->papFldDes[539]->size=sizeof(prec->l482);
  pdbRecordType->papFldDes[539]->offset=(short)((char *)&prec->l482 - (char *)prec);
  pdbRecordType->papFldDes[540]->size=sizeof(prec->l483);
  pdbRecordType->papFldDes[540]->offset=(short)((char *)&prec->l483 - (char *)prec);
  pdbRecordType->papFldDes[541]->size=sizeof(prec->l484);
  pdbRecordType->papFldDes[541]->offset=(short)((char *)&prec->l484 - (char *)prec);
  pdbRecordType->papFldDes[542]->size=sizeof(prec->l485);
  pdbRecordType->papFldDes[542]->offset=(short)((char *)&prec->l485 - (char *)prec);
  pdbRecordType->papFldDes[543]->size=sizeof(prec->l486);
  pdbRecordType->papFldDes[543]->offset=(short)((char *)&prec->l486 - (char *)prec);
  pdbRecordType->papFldDes[544]->size=sizeof(prec->l487);
  pdbRecordType->papFldDes[544]->offset=(short)((char *)&prec->l487 - (char *)prec);
  pdbRecordType->papFldDes[545]->size=sizeof(prec->l488);
  pdbRecordType->papFldDes[545]->offset=(short)((char *)&prec->l488 - (char *)prec);
  pdbRecordType->papFldDes[546]->size=sizeof(prec->l489);
  pdbRecordType->papFldDes[546]->offset=(short)((char *)&prec->l489 - (char *)prec);
  pdbRecordType->papFldDes[547]->size=sizeof(prec->l490);
  pdbRecordType->papFldDes[547]->offset=(short)((char *)&prec->l490 - (char *)prec);
  pdbRecordType->papFldDes[548]->size=sizeof(prec->l491);
  pdbRecordType->papFldDes[548]->offset=(short)((char *)&prec->l491 - (char *)prec);
  pdbRecordType->papFldDes[549]->size=sizeof(prec->l492);
  pdbRecordType->papFldDes[549]->offset=(short)((char *)&prec->l492 - (char *)prec);
  pdbRecordType->papFldDes[550]->size=sizeof(prec->l493);
  pdbRecordType->papFldDes[550]->offset=(short)((char *)&prec->l493 - (char *)prec);
  pdbRecordType->papFldDes[551]->size=sizeof(prec->l494);
  pdbRecordType->papFldDes[551]->offset=(short)((char *)&prec->l494 - (char *)prec);
  pdbRecordType->papFldDes[552]->size=sizeof(prec->l495);
  pdbRecordType->papFldDes[552]->offset=(short)((char *)&prec->l495 - (char *)prec);
  pdbRecordType->papFldDes[553]->size=sizeof(prec->l496);
  pdbRecordType->papFldDes[553]->offset=(short)((char *)&prec->l496 - (char *)prec);
  pdbRecordType->papFldDes[554]->size=sizeof(prec->l497);
  pdbRecordType->papFldDes[554]->offset=(short)((char *)&prec->l497 - (char *)prec);
  pdbRecordType->papFldDes[555]->size=sizeof(prec->l498);
  pdbRecordType->papFldDes[555]->offset=(short)((char *)&prec->l498 - (char *)prec);
  pdbRecordType->papFldDes[556]->size=sizeof(prec->l499);
  pdbRecordType->papFldDes[556]->offset=(short)((char *)&prec->l499 - (char *)prec);
  pdbRecordType->papFldDes[557]->size=sizeof(prec->l500);
  pdbRecordType->papFldDes[557]->offset=(short)((char *)&prec->l500 - (char *)prec);
  pdbRecordType->papFldDes[558]->size=sizeof(prec->l501);
  pdbRecordType->papFldDes[558]->offset=(short)((char *)&prec->l501 - (char *)prec);
  pdbRecordType->papFldDes[559]->size=sizeof(prec->l502);
  pdbRecordType->papFldDes[559]->offset=(short)((char *)&prec->l502 - (char *)prec);
  pdbRecordType->papFldDes[560]->size=sizeof(prec->l503);
  pdbRecordType->papFldDes[560]->offset=(short)((char *)&prec->l503 - (char *)prec);
  pdbRecordType->papFldDes[561]->size=sizeof(prec->l504);
  pdbRecordType->papFldDes[561]->offset=(short)((char *)&prec->l504 - (char *)prec);
  pdbRecordType->papFldDes[562]->size=sizeof(prec->l505);
  pdbRecordType->papFldDes[562]->offset=(short)((char *)&prec->l505 - (char *)prec);
  pdbRecordType->papFldDes[563]->size=sizeof(prec->l506);
  pdbRecordType->papFldDes[563]->offset=(short)((char *)&prec->l506 - (char *)prec);
  pdbRecordType->papFldDes[564]->size=sizeof(prec->l507);
  pdbRecordType->papFldDes[564]->offset=(short)((char *)&prec->l507 - (char *)prec);
  pdbRecordType->papFldDes[565]->size=sizeof(prec->l508);
  pdbRecordType->papFldDes[565]->offset=(short)((char *)&prec->l508 - (char *)prec);
  pdbRecordType->papFldDes[566]->size=sizeof(prec->l509);
  pdbRecordType->papFldDes[566]->offset=(short)((char *)&prec->l509 - (char *)prec);
  pdbRecordType->papFldDes[567]->size=sizeof(prec->l510);
  pdbRecordType->papFldDes[567]->offset=(short)((char *)&prec->l510 - (char *)prec);
  pdbRecordType->papFldDes[568]->size=sizeof(prec->l511);
  pdbRecordType->papFldDes[568]->offset=(short)((char *)&prec->l511 - (char *)prec);
  pdbRecordType->papFldDes[569]->size=sizeof(prec->l512);
  pdbRecordType->papFldDes[569]->offset=(short)((char *)&prec->l512 - (char *)prec);
  pdbRecordType->papFldDes[570]->size=sizeof(prec->l513);
  pdbRecordType->papFldDes[570]->offset=(short)((char *)&prec->l513 - (char *)prec);
  pdbRecordType->papFldDes[571]->size=sizeof(prec->l514);
  pdbRecordType->papFldDes[571]->offset=(short)((char *)&prec->l514 - (char *)prec);
  pdbRecordType->papFldDes[572]->size=sizeof(prec->l515);
  pdbRecordType->papFldDes[572]->offset=(short)((char *)&prec->l515 - (char *)prec);
  pdbRecordType->papFldDes[573]->size=sizeof(prec->l516);
  pdbRecordType->papFldDes[573]->offset=(short)((char *)&prec->l516 - (char *)prec);
  pdbRecordType->papFldDes[574]->size=sizeof(prec->l517);
  pdbRecordType->papFldDes[574]->offset=(short)((char *)&prec->l517 - (char *)prec);
  pdbRecordType->papFldDes[575]->size=sizeof(prec->l518);
  pdbRecordType->papFldDes[575]->offset=(short)((char *)&prec->l518 - (char *)prec);
  pdbRecordType->papFldDes[576]->size=sizeof(prec->l519);
  pdbRecordType->papFldDes[576]->offset=(short)((char *)&prec->l519 - (char *)prec);
  pdbRecordType->papFldDes[577]->size=sizeof(prec->l520);
  pdbRecordType->papFldDes[577]->offset=(short)((char *)&prec->l520 - (char *)prec);
  pdbRecordType->papFldDes[578]->size=sizeof(prec->l521);
  pdbRecordType->papFldDes[578]->offset=(short)((char *)&prec->l521 - (char *)prec);
  pdbRecordType->papFldDes[579]->size=sizeof(prec->l522);
  pdbRecordType->papFldDes[579]->offset=(short)((char *)&prec->l522 - (char *)prec);
  pdbRecordType->papFldDes[580]->size=sizeof(prec->l523);
  pdbRecordType->papFldDes[580]->offset=(short)((char *)&prec->l523 - (char *)prec);
  pdbRecordType->papFldDes[581]->size=sizeof(prec->l524);
  pdbRecordType->papFldDes[581]->offset=(short)((char *)&prec->l524 - (char *)prec);
  pdbRecordType->papFldDes[582]->size=sizeof(prec->l525);
  pdbRecordType->papFldDes[582]->offset=(short)((char *)&prec->l525 - (char *)prec);
  pdbRecordType->papFldDes[583]->size=sizeof(prec->l526);
  pdbRecordType->papFldDes[583]->offset=(short)((char *)&prec->l526 - (char *)prec);
  pdbRecordType->papFldDes[584]->size=sizeof(prec->l527);
  pdbRecordType->papFldDes[584]->offset=(short)((char *)&prec->l527 - (char *)prec);
  pdbRecordType->papFldDes[585]->size=sizeof(prec->l528);
  pdbRecordType->papFldDes[585]->offset=(short)((char *)&prec->l528 - (char *)prec);
  pdbRecordType->papFldDes[586]->size=sizeof(prec->l529);
  pdbRecordType->papFldDes[586]->offset=(short)((char *)&prec->l529 - (char *)prec);
  pdbRecordType->papFldDes[587]->size=sizeof(prec->l530);
  pdbRecordType->papFldDes[587]->offset=(short)((char *)&prec->l530 - (char *)prec);
  pdbRecordType->papFldDes[588]->size=sizeof(prec->l531);
  pdbRecordType->papFldDes[588]->offset=(short)((char *)&prec->l531 - (char *)prec);
  pdbRecordType->papFldDes[589]->size=sizeof(prec->l532);
  pdbRecordType->papFldDes[589]->offset=(short)((char *)&prec->l532 - (char *)prec);
  pdbRecordType->papFldDes[590]->size=sizeof(prec->l533);
  pdbRecordType->papFldDes[590]->offset=(short)((char *)&prec->l533 - (char *)prec);
  pdbRecordType->papFldDes[591]->size=sizeof(prec->l534);
  pdbRecordType->papFldDes[591]->offset=(short)((char *)&prec->l534 - (char *)prec);
  pdbRecordType->papFldDes[592]->size=sizeof(prec->l535);
  pdbRecordType->papFldDes[592]->offset=(short)((char *)&prec->l535 - (char *)prec);
  pdbRecordType->papFldDes[593]->size=sizeof(prec->l536);
  pdbRecordType->papFldDes[593]->offset=(short)((char *)&prec->l536 - (char *)prec);
  pdbRecordType->papFldDes[594]->size=sizeof(prec->l537);
  pdbRecordType->papFldDes[594]->offset=(short)((char *)&prec->l537 - (char *)prec);
  pdbRecordType->papFldDes[595]->size=sizeof(prec->l538);
  pdbRecordType->papFldDes[595]->offset=(short)((char *)&prec->l538 - (char *)prec);
  pdbRecordType->papFldDes[596]->size=sizeof(prec->l539);
  pdbRecordType->papFldDes[596]->offset=(short)((char *)&prec->l539 - (char *)prec);
  pdbRecordType->papFldDes[597]->size=sizeof(prec->l540);
  pdbRecordType->papFldDes[597]->offset=(short)((char *)&prec->l540 - (char *)prec);
  pdbRecordType->papFldDes[598]->size=sizeof(prec->l541);
  pdbRecordType->papFldDes[598]->offset=(short)((char *)&prec->l541 - (char *)prec);
  pdbRecordType->papFldDes[599]->size=sizeof(prec->l542);
  pdbRecordType->papFldDes[599]->offset=(short)((char *)&prec->l542 - (char *)prec);
  pdbRecordType->papFldDes[600]->size=sizeof(prec->l543);
  pdbRecordType->papFldDes[600]->offset=(short)((char *)&prec->l543 - (char *)prec);
  pdbRecordType->papFldDes[601]->size=sizeof(prec->l544);
  pdbRecordType->papFldDes[601]->offset=(short)((char *)&prec->l544 - (char *)prec);
  pdbRecordType->papFldDes[602]->size=sizeof(prec->l545);
  pdbRecordType->papFldDes[602]->offset=(short)((char *)&prec->l545 - (char *)prec);
  pdbRecordType->papFldDes[603]->size=sizeof(prec->l546);
  pdbRecordType->papFldDes[603]->offset=(short)((char *)&prec->l546 - (char *)prec);
  pdbRecordType->papFldDes[604]->size=sizeof(prec->l547);
  pdbRecordType->papFldDes[604]->offset=(short)((char *)&prec->l547 - (char *)prec);
  pdbRecordType->papFldDes[605]->size=sizeof(prec->l548);
  pdbRecordType->papFldDes[605]->offset=(short)((char *)&prec->l548 - (char *)prec);
  pdbRecordType->papFldDes[606]->size=sizeof(prec->l549);
  pdbRecordType->papFldDes[606]->offset=(short)((char *)&prec->l549 - (char *)prec);
  pdbRecordType->papFldDes[607]->size=sizeof(prec->l550);
  pdbRecordType->papFldDes[607]->offset=(short)((char *)&prec->l550 - (char *)prec);
  pdbRecordType->papFldDes[608]->size=sizeof(prec->l551);
  pdbRecordType->papFldDes[608]->offset=(short)((char *)&prec->l551 - (char *)prec);
  pdbRecordType->papFldDes[609]->size=sizeof(prec->l552);
  pdbRecordType->papFldDes[609]->offset=(short)((char *)&prec->l552 - (char *)prec);
  pdbRecordType->papFldDes[610]->size=sizeof(prec->l553);
  pdbRecordType->papFldDes[610]->offset=(short)((char *)&prec->l553 - (char *)prec);
  pdbRecordType->papFldDes[611]->size=sizeof(prec->l554);
  pdbRecordType->papFldDes[611]->offset=(short)((char *)&prec->l554 - (char *)prec);
  pdbRecordType->papFldDes[612]->size=sizeof(prec->l555);
  pdbRecordType->papFldDes[612]->offset=(short)((char *)&prec->l555 - (char *)prec);
  pdbRecordType->papFldDes[613]->size=sizeof(prec->l556);
  pdbRecordType->papFldDes[613]->offset=(short)((char *)&prec->l556 - (char *)prec);
  pdbRecordType->papFldDes[614]->size=sizeof(prec->l557);
  pdbRecordType->papFldDes[614]->offset=(short)((char *)&prec->l557 - (char *)prec);
  pdbRecordType->papFldDes[615]->size=sizeof(prec->l558);
  pdbRecordType->papFldDes[615]->offset=(short)((char *)&prec->l558 - (char *)prec);
  pdbRecordType->papFldDes[616]->size=sizeof(prec->l559);
  pdbRecordType->papFldDes[616]->offset=(short)((char *)&prec->l559 - (char *)prec);
  pdbRecordType->papFldDes[617]->size=sizeof(prec->l560);
  pdbRecordType->papFldDes[617]->offset=(short)((char *)&prec->l560 - (char *)prec);
  pdbRecordType->papFldDes[618]->size=sizeof(prec->l561);
  pdbRecordType->papFldDes[618]->offset=(short)((char *)&prec->l561 - (char *)prec);
  pdbRecordType->papFldDes[619]->size=sizeof(prec->l562);
  pdbRecordType->papFldDes[619]->offset=(short)((char *)&prec->l562 - (char *)prec);
  pdbRecordType->papFldDes[620]->size=sizeof(prec->l563);
  pdbRecordType->papFldDes[620]->offset=(short)((char *)&prec->l563 - (char *)prec);
  pdbRecordType->papFldDes[621]->size=sizeof(prec->l564);
  pdbRecordType->papFldDes[621]->offset=(short)((char *)&prec->l564 - (char *)prec);
  pdbRecordType->papFldDes[622]->size=sizeof(prec->l565);
  pdbRecordType->papFldDes[622]->offset=(short)((char *)&prec->l565 - (char *)prec);
  pdbRecordType->papFldDes[623]->size=sizeof(prec->l566);
  pdbRecordType->papFldDes[623]->offset=(short)((char *)&prec->l566 - (char *)prec);
  pdbRecordType->papFldDes[624]->size=sizeof(prec->l567);
  pdbRecordType->papFldDes[624]->offset=(short)((char *)&prec->l567 - (char *)prec);
  pdbRecordType->papFldDes[625]->size=sizeof(prec->l568);
  pdbRecordType->papFldDes[625]->offset=(short)((char *)&prec->l568 - (char *)prec);
  pdbRecordType->papFldDes[626]->size=sizeof(prec->l569);
  pdbRecordType->papFldDes[626]->offset=(short)((char *)&prec->l569 - (char *)prec);
  pdbRecordType->papFldDes[627]->size=sizeof(prec->l570);
  pdbRecordType->papFldDes[627]->offset=(short)((char *)&prec->l570 - (char *)prec);
  pdbRecordType->papFldDes[628]->size=sizeof(prec->l571);
  pdbRecordType->papFldDes[628]->offset=(short)((char *)&prec->l571 - (char *)prec);
  pdbRecordType->papFldDes[629]->size=sizeof(prec->l572);
  pdbRecordType->papFldDes[629]->offset=(short)((char *)&prec->l572 - (char *)prec);
  pdbRecordType->papFldDes[630]->size=sizeof(prec->l573);
  pdbRecordType->papFldDes[630]->offset=(short)((char *)&prec->l573 - (char *)prec);
  pdbRecordType->papFldDes[631]->size=sizeof(prec->l574);
  pdbRecordType->papFldDes[631]->offset=(short)((char *)&prec->l574 - (char *)prec);
  pdbRecordType->papFldDes[632]->size=sizeof(prec->l575);
  pdbRecordType->papFldDes[632]->offset=(short)((char *)&prec->l575 - (char *)prec);
  pdbRecordType->papFldDes[633]->size=sizeof(prec->l576);
  pdbRecordType->papFldDes[633]->offset=(short)((char *)&prec->l576 - (char *)prec);
  pdbRecordType->papFldDes[634]->size=sizeof(prec->l577);
  pdbRecordType->papFldDes[634]->offset=(short)((char *)&prec->l577 - (char *)prec);
  pdbRecordType->papFldDes[635]->size=sizeof(prec->l578);
  pdbRecordType->papFldDes[635]->offset=(short)((char *)&prec->l578 - (char *)prec);
  pdbRecordType->papFldDes[636]->size=sizeof(prec->l579);
  pdbRecordType->papFldDes[636]->offset=(short)((char *)&prec->l579 - (char *)prec);
  pdbRecordType->papFldDes[637]->size=sizeof(prec->l580);
  pdbRecordType->papFldDes[637]->offset=(short)((char *)&prec->l580 - (char *)prec);
  pdbRecordType->papFldDes[638]->size=sizeof(prec->l581);
  pdbRecordType->papFldDes[638]->offset=(short)((char *)&prec->l581 - (char *)prec);
  pdbRecordType->papFldDes[639]->size=sizeof(prec->l582);
  pdbRecordType->papFldDes[639]->offset=(short)((char *)&prec->l582 - (char *)prec);
  pdbRecordType->papFldDes[640]->size=sizeof(prec->l583);
  pdbRecordType->papFldDes[640]->offset=(short)((char *)&prec->l583 - (char *)prec);
  pdbRecordType->papFldDes[641]->size=sizeof(prec->l584);
  pdbRecordType->papFldDes[641]->offset=(short)((char *)&prec->l584 - (char *)prec);
  pdbRecordType->papFldDes[642]->size=sizeof(prec->l585);
  pdbRecordType->papFldDes[642]->offset=(short)((char *)&prec->l585 - (char *)prec);
  pdbRecordType->papFldDes[643]->size=sizeof(prec->l586);
  pdbRecordType->papFldDes[643]->offset=(short)((char *)&prec->l586 - (char *)prec);
  pdbRecordType->papFldDes[644]->size=sizeof(prec->l587);
  pdbRecordType->papFldDes[644]->offset=(short)((char *)&prec->l587 - (char *)prec);
  pdbRecordType->papFldDes[645]->size=sizeof(prec->l588);
  pdbRecordType->papFldDes[645]->offset=(short)((char *)&prec->l588 - (char *)prec);
  pdbRecordType->papFldDes[646]->size=sizeof(prec->l589);
  pdbRecordType->papFldDes[646]->offset=(short)((char *)&prec->l589 - (char *)prec);
  pdbRecordType->papFldDes[647]->size=sizeof(prec->l590);
  pdbRecordType->papFldDes[647]->offset=(short)((char *)&prec->l590 - (char *)prec);
  pdbRecordType->papFldDes[648]->size=sizeof(prec->l591);
  pdbRecordType->papFldDes[648]->offset=(short)((char *)&prec->l591 - (char *)prec);
  pdbRecordType->papFldDes[649]->size=sizeof(prec->l592);
  pdbRecordType->papFldDes[649]->offset=(short)((char *)&prec->l592 - (char *)prec);
  pdbRecordType->papFldDes[650]->size=sizeof(prec->l593);
  pdbRecordType->papFldDes[650]->offset=(short)((char *)&prec->l593 - (char *)prec);
  pdbRecordType->papFldDes[651]->size=sizeof(prec->l594);
  pdbRecordType->papFldDes[651]->offset=(short)((char *)&prec->l594 - (char *)prec);
  pdbRecordType->papFldDes[652]->size=sizeof(prec->l595);
  pdbRecordType->papFldDes[652]->offset=(short)((char *)&prec->l595 - (char *)prec);
  pdbRecordType->papFldDes[653]->size=sizeof(prec->l596);
  pdbRecordType->papFldDes[653]->offset=(short)((char *)&prec->l596 - (char *)prec);
  pdbRecordType->papFldDes[654]->size=sizeof(prec->l597);
  pdbRecordType->papFldDes[654]->offset=(short)((char *)&prec->l597 - (char *)prec);
  pdbRecordType->papFldDes[655]->size=sizeof(prec->l598);
  pdbRecordType->papFldDes[655]->offset=(short)((char *)&prec->l598 - (char *)prec);
  pdbRecordType->papFldDes[656]->size=sizeof(prec->l599);
  pdbRecordType->papFldDes[656]->offset=(short)((char *)&prec->l599 - (char *)prec);
  pdbRecordType->papFldDes[657]->size=sizeof(prec->l600);
  pdbRecordType->papFldDes[657]->offset=(short)((char *)&prec->l600 - (char *)prec);
  pdbRecordType->papFldDes[658]->size=sizeof(prec->l601);
  pdbRecordType->papFldDes[658]->offset=(short)((char *)&prec->l601 - (char *)prec);
  pdbRecordType->papFldDes[659]->size=sizeof(prec->l602);
  pdbRecordType->papFldDes[659]->offset=(short)((char *)&prec->l602 - (char *)prec);
  pdbRecordType->papFldDes[660]->size=sizeof(prec->l603);
  pdbRecordType->papFldDes[660]->offset=(short)((char *)&prec->l603 - (char *)prec);
  pdbRecordType->papFldDes[661]->size=sizeof(prec->l604);
  pdbRecordType->papFldDes[661]->offset=(short)((char *)&prec->l604 - (char *)prec);
  pdbRecordType->papFldDes[662]->size=sizeof(prec->l605);
  pdbRecordType->papFldDes[662]->offset=(short)((char *)&prec->l605 - (char *)prec);
  pdbRecordType->papFldDes[663]->size=sizeof(prec->l606);
  pdbRecordType->papFldDes[663]->offset=(short)((char *)&prec->l606 - (char *)prec);
  pdbRecordType->papFldDes[664]->size=sizeof(prec->l607);
  pdbRecordType->papFldDes[664]->offset=(short)((char *)&prec->l607 - (char *)prec);
  pdbRecordType->papFldDes[665]->size=sizeof(prec->l608);
  pdbRecordType->papFldDes[665]->offset=(short)((char *)&prec->l608 - (char *)prec);
  pdbRecordType->papFldDes[666]->size=sizeof(prec->l609);
  pdbRecordType->papFldDes[666]->offset=(short)((char *)&prec->l609 - (char *)prec);
  pdbRecordType->papFldDes[667]->size=sizeof(prec->l610);
  pdbRecordType->papFldDes[667]->offset=(short)((char *)&prec->l610 - (char *)prec);
  pdbRecordType->papFldDes[668]->size=sizeof(prec->l611);
  pdbRecordType->papFldDes[668]->offset=(short)((char *)&prec->l611 - (char *)prec);
  pdbRecordType->papFldDes[669]->size=sizeof(prec->l612);
  pdbRecordType->papFldDes[669]->offset=(short)((char *)&prec->l612 - (char *)prec);
  pdbRecordType->papFldDes[670]->size=sizeof(prec->l613);
  pdbRecordType->papFldDes[670]->offset=(short)((char *)&prec->l613 - (char *)prec);
  pdbRecordType->papFldDes[671]->size=sizeof(prec->l614);
  pdbRecordType->papFldDes[671]->offset=(short)((char *)&prec->l614 - (char *)prec);
  pdbRecordType->papFldDes[672]->size=sizeof(prec->l615);
  pdbRecordType->papFldDes[672]->offset=(short)((char *)&prec->l615 - (char *)prec);
  pdbRecordType->papFldDes[673]->size=sizeof(prec->l616);
  pdbRecordType->papFldDes[673]->offset=(short)((char *)&prec->l616 - (char *)prec);
  pdbRecordType->papFldDes[674]->size=sizeof(prec->l617);
  pdbRecordType->papFldDes[674]->offset=(short)((char *)&prec->l617 - (char *)prec);
  pdbRecordType->papFldDes[675]->size=sizeof(prec->l618);
  pdbRecordType->papFldDes[675]->offset=(short)((char *)&prec->l618 - (char *)prec);
  pdbRecordType->papFldDes[676]->size=sizeof(prec->l619);
  pdbRecordType->papFldDes[676]->offset=(short)((char *)&prec->l619 - (char *)prec);
  pdbRecordType->papFldDes[677]->size=sizeof(prec->l620);
  pdbRecordType->papFldDes[677]->offset=(short)((char *)&prec->l620 - (char *)prec);
  pdbRecordType->papFldDes[678]->size=sizeof(prec->l621);
  pdbRecordType->papFldDes[678]->offset=(short)((char *)&prec->l621 - (char *)prec);
  pdbRecordType->papFldDes[679]->size=sizeof(prec->l622);
  pdbRecordType->papFldDes[679]->offset=(short)((char *)&prec->l622 - (char *)prec);
  pdbRecordType->papFldDes[680]->size=sizeof(prec->l623);
  pdbRecordType->papFldDes[680]->offset=(short)((char *)&prec->l623 - (char *)prec);
  pdbRecordType->papFldDes[681]->size=sizeof(prec->l624);
  pdbRecordType->papFldDes[681]->offset=(short)((char *)&prec->l624 - (char *)prec);
  pdbRecordType->papFldDes[682]->size=sizeof(prec->l625);
  pdbRecordType->papFldDes[682]->offset=(short)((char *)&prec->l625 - (char *)prec);
  pdbRecordType->papFldDes[683]->size=sizeof(prec->l626);
  pdbRecordType->papFldDes[683]->offset=(short)((char *)&prec->l626 - (char *)prec);
  pdbRecordType->papFldDes[684]->size=sizeof(prec->l627);
  pdbRecordType->papFldDes[684]->offset=(short)((char *)&prec->l627 - (char *)prec);
  pdbRecordType->papFldDes[685]->size=sizeof(prec->l628);
  pdbRecordType->papFldDes[685]->offset=(short)((char *)&prec->l628 - (char *)prec);
  pdbRecordType->papFldDes[686]->size=sizeof(prec->l629);
  pdbRecordType->papFldDes[686]->offset=(short)((char *)&prec->l629 - (char *)prec);
  pdbRecordType->papFldDes[687]->size=sizeof(prec->l630);
  pdbRecordType->papFldDes[687]->offset=(short)((char *)&prec->l630 - (char *)prec);
  pdbRecordType->papFldDes[688]->size=sizeof(prec->l631);
  pdbRecordType->papFldDes[688]->offset=(short)((char *)&prec->l631 - (char *)prec);
  pdbRecordType->papFldDes[689]->size=sizeof(prec->l632);
  pdbRecordType->papFldDes[689]->offset=(short)((char *)&prec->l632 - (char *)prec);
  pdbRecordType->papFldDes[690]->size=sizeof(prec->l633);
  pdbRecordType->papFldDes[690]->offset=(short)((char *)&prec->l633 - (char *)prec);
  pdbRecordType->papFldDes[691]->size=sizeof(prec->l634);
  pdbRecordType->papFldDes[691]->offset=(short)((char *)&prec->l634 - (char *)prec);
  pdbRecordType->papFldDes[692]->size=sizeof(prec->l635);
  pdbRecordType->papFldDes[692]->offset=(short)((char *)&prec->l635 - (char *)prec);
  pdbRecordType->papFldDes[693]->size=sizeof(prec->l636);
  pdbRecordType->papFldDes[693]->offset=(short)((char *)&prec->l636 - (char *)prec);
  pdbRecordType->papFldDes[694]->size=sizeof(prec->l637);
  pdbRecordType->papFldDes[694]->offset=(short)((char *)&prec->l637 - (char *)prec);
  pdbRecordType->papFldDes[695]->size=sizeof(prec->l638);
  pdbRecordType->papFldDes[695]->offset=(short)((char *)&prec->l638 - (char *)prec);
  pdbRecordType->papFldDes[696]->size=sizeof(prec->l639);
  pdbRecordType->papFldDes[696]->offset=(short)((char *)&prec->l639 - (char *)prec);
  pdbRecordType->papFldDes[697]->size=sizeof(prec->l640);
  pdbRecordType->papFldDes[697]->offset=(short)((char *)&prec->l640 - (char *)prec);
  pdbRecordType->papFldDes[698]->size=sizeof(prec->l641);
  pdbRecordType->papFldDes[698]->offset=(short)((char *)&prec->l641 - (char *)prec);
  pdbRecordType->papFldDes[699]->size=sizeof(prec->l642);
  pdbRecordType->papFldDes[699]->offset=(short)((char *)&prec->l642 - (char *)prec);
  pdbRecordType->papFldDes[700]->size=sizeof(prec->l643);
  pdbRecordType->papFldDes[700]->offset=(short)((char *)&prec->l643 - (char *)prec);
  pdbRecordType->papFldDes[701]->size=sizeof(prec->l644);
  pdbRecordType->papFldDes[701]->offset=(short)((char *)&prec->l644 - (char *)prec);
  pdbRecordType->papFldDes[702]->size=sizeof(prec->l645);
  pdbRecordType->papFldDes[702]->offset=(short)((char *)&prec->l645 - (char *)prec);
  pdbRecordType->papFldDes[703]->size=sizeof(prec->l646);
  pdbRecordType->papFldDes[703]->offset=(short)((char *)&prec->l646 - (char *)prec);
  pdbRecordType->papFldDes[704]->size=sizeof(prec->l647);
  pdbRecordType->papFldDes[704]->offset=(short)((char *)&prec->l647 - (char *)prec);
  pdbRecordType->papFldDes[705]->size=sizeof(prec->l648);
  pdbRecordType->papFldDes[705]->offset=(short)((char *)&prec->l648 - (char *)prec);
  pdbRecordType->papFldDes[706]->size=sizeof(prec->l649);
  pdbRecordType->papFldDes[706]->offset=(short)((char *)&prec->l649 - (char *)prec);
  pdbRecordType->papFldDes[707]->size=sizeof(prec->l650);
  pdbRecordType->papFldDes[707]->offset=(short)((char *)&prec->l650 - (char *)prec);
  pdbRecordType->papFldDes[708]->size=sizeof(prec->l651);
  pdbRecordType->papFldDes[708]->offset=(short)((char *)&prec->l651 - (char *)prec);
  pdbRecordType->papFldDes[709]->size=sizeof(prec->l652);
  pdbRecordType->papFldDes[709]->offset=(short)((char *)&prec->l652 - (char *)prec);
  pdbRecordType->papFldDes[710]->size=sizeof(prec->l653);
  pdbRecordType->papFldDes[710]->offset=(short)((char *)&prec->l653 - (char *)prec);
  pdbRecordType->papFldDes[711]->size=sizeof(prec->l654);
  pdbRecordType->papFldDes[711]->offset=(short)((char *)&prec->l654 - (char *)prec);
  pdbRecordType->papFldDes[712]->size=sizeof(prec->l655);
  pdbRecordType->papFldDes[712]->offset=(short)((char *)&prec->l655 - (char *)prec);
  pdbRecordType->papFldDes[713]->size=sizeof(prec->l656);
  pdbRecordType->papFldDes[713]->offset=(short)((char *)&prec->l656 - (char *)prec);
  pdbRecordType->papFldDes[714]->size=sizeof(prec->l657);
  pdbRecordType->papFldDes[714]->offset=(short)((char *)&prec->l657 - (char *)prec);
  pdbRecordType->papFldDes[715]->size=sizeof(prec->l658);
  pdbRecordType->papFldDes[715]->offset=(short)((char *)&prec->l658 - (char *)prec);
  pdbRecordType->papFldDes[716]->size=sizeof(prec->l659);
  pdbRecordType->papFldDes[716]->offset=(short)((char *)&prec->l659 - (char *)prec);
  pdbRecordType->papFldDes[717]->size=sizeof(prec->l660);
  pdbRecordType->papFldDes[717]->offset=(short)((char *)&prec->l660 - (char *)prec);
  pdbRecordType->papFldDes[718]->size=sizeof(prec->l661);
  pdbRecordType->papFldDes[718]->offset=(short)((char *)&prec->l661 - (char *)prec);
  pdbRecordType->papFldDes[719]->size=sizeof(prec->l662);
  pdbRecordType->papFldDes[719]->offset=(short)((char *)&prec->l662 - (char *)prec);
  pdbRecordType->papFldDes[720]->size=sizeof(prec->l663);
  pdbRecordType->papFldDes[720]->offset=(short)((char *)&prec->l663 - (char *)prec);
  pdbRecordType->papFldDes[721]->size=sizeof(prec->l664);
  pdbRecordType->papFldDes[721]->offset=(short)((char *)&prec->l664 - (char *)prec);
  pdbRecordType->papFldDes[722]->size=sizeof(prec->l665);
  pdbRecordType->papFldDes[722]->offset=(short)((char *)&prec->l665 - (char *)prec);
  pdbRecordType->papFldDes[723]->size=sizeof(prec->l666);
  pdbRecordType->papFldDes[723]->offset=(short)((char *)&prec->l666 - (char *)prec);
  pdbRecordType->papFldDes[724]->size=sizeof(prec->l667);
  pdbRecordType->papFldDes[724]->offset=(short)((char *)&prec->l667 - (char *)prec);
  pdbRecordType->papFldDes[725]->size=sizeof(prec->l668);
  pdbRecordType->papFldDes[725]->offset=(short)((char *)&prec->l668 - (char *)prec);
  pdbRecordType->papFldDes[726]->size=sizeof(prec->l669);
  pdbRecordType->papFldDes[726]->offset=(short)((char *)&prec->l669 - (char *)prec);
  pdbRecordType->papFldDes[727]->size=sizeof(prec->l670);
  pdbRecordType->papFldDes[727]->offset=(short)((char *)&prec->l670 - (char *)prec);
  pdbRecordType->papFldDes[728]->size=sizeof(prec->l671);
  pdbRecordType->papFldDes[728]->offset=(short)((char *)&prec->l671 - (char *)prec);
  pdbRecordType->papFldDes[729]->size=sizeof(prec->l672);
  pdbRecordType->papFldDes[729]->offset=(short)((char *)&prec->l672 - (char *)prec);
  pdbRecordType->papFldDes[730]->size=sizeof(prec->l673);
  pdbRecordType->papFldDes[730]->offset=(short)((char *)&prec->l673 - (char *)prec);
  pdbRecordType->papFldDes[731]->size=sizeof(prec->l674);
  pdbRecordType->papFldDes[731]->offset=(short)((char *)&prec->l674 - (char *)prec);
  pdbRecordType->papFldDes[732]->size=sizeof(prec->l675);
  pdbRecordType->papFldDes[732]->offset=(short)((char *)&prec->l675 - (char *)prec);
  pdbRecordType->papFldDes[733]->size=sizeof(prec->l676);
  pdbRecordType->papFldDes[733]->offset=(short)((char *)&prec->l676 - (char *)prec);
  pdbRecordType->papFldDes[734]->size=sizeof(prec->l677);
  pdbRecordType->papFldDes[734]->offset=(short)((char *)&prec->l677 - (char *)prec);
  pdbRecordType->papFldDes[735]->size=sizeof(prec->l678);
  pdbRecordType->papFldDes[735]->offset=(short)((char *)&prec->l678 - (char *)prec);
  pdbRecordType->papFldDes[736]->size=sizeof(prec->l679);
  pdbRecordType->papFldDes[736]->offset=(short)((char *)&prec->l679 - (char *)prec);
  pdbRecordType->papFldDes[737]->size=sizeof(prec->l680);
  pdbRecordType->papFldDes[737]->offset=(short)((char *)&prec->l680 - (char *)prec);
  pdbRecordType->papFldDes[738]->size=sizeof(prec->l681);
  pdbRecordType->papFldDes[738]->offset=(short)((char *)&prec->l681 - (char *)prec);
  pdbRecordType->papFldDes[739]->size=sizeof(prec->l682);
  pdbRecordType->papFldDes[739]->offset=(short)((char *)&prec->l682 - (char *)prec);
  pdbRecordType->papFldDes[740]->size=sizeof(prec->l683);
  pdbRecordType->papFldDes[740]->offset=(short)((char *)&prec->l683 - (char *)prec);
  pdbRecordType->papFldDes[741]->size=sizeof(prec->l684);
  pdbRecordType->papFldDes[741]->offset=(short)((char *)&prec->l684 - (char *)prec);
  pdbRecordType->papFldDes[742]->size=sizeof(prec->l685);
  pdbRecordType->papFldDes[742]->offset=(short)((char *)&prec->l685 - (char *)prec);
  pdbRecordType->papFldDes[743]->size=sizeof(prec->l686);
  pdbRecordType->papFldDes[743]->offset=(short)((char *)&prec->l686 - (char *)prec);
  pdbRecordType->papFldDes[744]->size=sizeof(prec->l687);
  pdbRecordType->papFldDes[744]->offset=(short)((char *)&prec->l687 - (char *)prec);
  pdbRecordType->papFldDes[745]->size=sizeof(prec->l688);
  pdbRecordType->papFldDes[745]->offset=(short)((char *)&prec->l688 - (char *)prec);
  pdbRecordType->papFldDes[746]->size=sizeof(prec->l689);
  pdbRecordType->papFldDes[746]->offset=(short)((char *)&prec->l689 - (char *)prec);
  pdbRecordType->papFldDes[747]->size=sizeof(prec->l690);
  pdbRecordType->papFldDes[747]->offset=(short)((char *)&prec->l690 - (char *)prec);
  pdbRecordType->papFldDes[748]->size=sizeof(prec->l691);
  pdbRecordType->papFldDes[748]->offset=(short)((char *)&prec->l691 - (char *)prec);
  pdbRecordType->papFldDes[749]->size=sizeof(prec->l692);
  pdbRecordType->papFldDes[749]->offset=(short)((char *)&prec->l692 - (char *)prec);
  pdbRecordType->papFldDes[750]->size=sizeof(prec->l693);
  pdbRecordType->papFldDes[750]->offset=(short)((char *)&prec->l693 - (char *)prec);
  pdbRecordType->papFldDes[751]->size=sizeof(prec->l694);
  pdbRecordType->papFldDes[751]->offset=(short)((char *)&prec->l694 - (char *)prec);
  pdbRecordType->papFldDes[752]->size=sizeof(prec->l695);
  pdbRecordType->papFldDes[752]->offset=(short)((char *)&prec->l695 - (char *)prec);
  pdbRecordType->papFldDes[753]->size=sizeof(prec->l696);
  pdbRecordType->papFldDes[753]->offset=(short)((char *)&prec->l696 - (char *)prec);
  pdbRecordType->papFldDes[754]->size=sizeof(prec->l697);
  pdbRecordType->papFldDes[754]->offset=(short)((char *)&prec->l697 - (char *)prec);
  pdbRecordType->papFldDes[755]->size=sizeof(prec->l698);
  pdbRecordType->papFldDes[755]->offset=(short)((char *)&prec->l698 - (char *)prec);
  pdbRecordType->papFldDes[756]->size=sizeof(prec->l699);
  pdbRecordType->papFldDes[756]->offset=(short)((char *)&prec->l699 - (char *)prec);
  pdbRecordType->papFldDes[757]->size=sizeof(prec->l700);
  pdbRecordType->papFldDes[757]->offset=(short)((char *)&prec->l700 - (char *)prec);
  pdbRecordType->papFldDes[758]->size=sizeof(prec->l701);
  pdbRecordType->papFldDes[758]->offset=(short)((char *)&prec->l701 - (char *)prec);
  pdbRecordType->papFldDes[759]->size=sizeof(prec->l702);
  pdbRecordType->papFldDes[759]->offset=(short)((char *)&prec->l702 - (char *)prec);
  pdbRecordType->papFldDes[760]->size=sizeof(prec->l703);
  pdbRecordType->papFldDes[760]->offset=(short)((char *)&prec->l703 - (char *)prec);
  pdbRecordType->papFldDes[761]->size=sizeof(prec->l704);
  pdbRecordType->papFldDes[761]->offset=(short)((char *)&prec->l704 - (char *)prec);
  pdbRecordType->papFldDes[762]->size=sizeof(prec->l705);
  pdbRecordType->papFldDes[762]->offset=(short)((char *)&prec->l705 - (char *)prec);
  pdbRecordType->papFldDes[763]->size=sizeof(prec->l706);
  pdbRecordType->papFldDes[763]->offset=(short)((char *)&prec->l706 - (char *)prec);
  pdbRecordType->papFldDes[764]->size=sizeof(prec->l707);
  pdbRecordType->papFldDes[764]->offset=(short)((char *)&prec->l707 - (char *)prec);
  pdbRecordType->papFldDes[765]->size=sizeof(prec->l708);
  pdbRecordType->papFldDes[765]->offset=(short)((char *)&prec->l708 - (char *)prec);
  pdbRecordType->papFldDes[766]->size=sizeof(prec->l709);
  pdbRecordType->papFldDes[766]->offset=(short)((char *)&prec->l709 - (char *)prec);
  pdbRecordType->papFldDes[767]->size=sizeof(prec->l710);
  pdbRecordType->papFldDes[767]->offset=(short)((char *)&prec->l710 - (char *)prec);
  pdbRecordType->papFldDes[768]->size=sizeof(prec->l711);
  pdbRecordType->papFldDes[768]->offset=(short)((char *)&prec->l711 - (char *)prec);
  pdbRecordType->papFldDes[769]->size=sizeof(prec->l712);
  pdbRecordType->papFldDes[769]->offset=(short)((char *)&prec->l712 - (char *)prec);
  pdbRecordType->papFldDes[770]->size=sizeof(prec->l713);
  pdbRecordType->papFldDes[770]->offset=(short)((char *)&prec->l713 - (char *)prec);
  pdbRecordType->papFldDes[771]->size=sizeof(prec->l714);
  pdbRecordType->papFldDes[771]->offset=(short)((char *)&prec->l714 - (char *)prec);
  pdbRecordType->papFldDes[772]->size=sizeof(prec->l715);
  pdbRecordType->papFldDes[772]->offset=(short)((char *)&prec->l715 - (char *)prec);
  pdbRecordType->papFldDes[773]->size=sizeof(prec->l716);
  pdbRecordType->papFldDes[773]->offset=(short)((char *)&prec->l716 - (char *)prec);
  pdbRecordType->papFldDes[774]->size=sizeof(prec->l717);
  pdbRecordType->papFldDes[774]->offset=(short)((char *)&prec->l717 - (char *)prec);
  pdbRecordType->papFldDes[775]->size=sizeof(prec->l718);
  pdbRecordType->papFldDes[775]->offset=(short)((char *)&prec->l718 - (char *)prec);
  pdbRecordType->papFldDes[776]->size=sizeof(prec->l719);
  pdbRecordType->papFldDes[776]->offset=(short)((char *)&prec->l719 - (char *)prec);
  pdbRecordType->papFldDes[777]->size=sizeof(prec->l720);
  pdbRecordType->papFldDes[777]->offset=(short)((char *)&prec->l720 - (char *)prec);
  pdbRecordType->papFldDes[778]->size=sizeof(prec->l721);
  pdbRecordType->papFldDes[778]->offset=(short)((char *)&prec->l721 - (char *)prec);
  pdbRecordType->papFldDes[779]->size=sizeof(prec->l722);
  pdbRecordType->papFldDes[779]->offset=(short)((char *)&prec->l722 - (char *)prec);
  pdbRecordType->papFldDes[780]->size=sizeof(prec->l723);
  pdbRecordType->papFldDes[780]->offset=(short)((char *)&prec->l723 - (char *)prec);
  pdbRecordType->papFldDes[781]->size=sizeof(prec->l724);
  pdbRecordType->papFldDes[781]->offset=(short)((char *)&prec->l724 - (char *)prec);
  pdbRecordType->papFldDes[782]->size=sizeof(prec->l725);
  pdbRecordType->papFldDes[782]->offset=(short)((char *)&prec->l725 - (char *)prec);
  pdbRecordType->papFldDes[783]->size=sizeof(prec->l726);
  pdbRecordType->papFldDes[783]->offset=(short)((char *)&prec->l726 - (char *)prec);
  pdbRecordType->papFldDes[784]->size=sizeof(prec->l727);
  pdbRecordType->papFldDes[784]->offset=(short)((char *)&prec->l727 - (char *)prec);
  pdbRecordType->papFldDes[785]->size=sizeof(prec->l728);
  pdbRecordType->papFldDes[785]->offset=(short)((char *)&prec->l728 - (char *)prec);
  pdbRecordType->papFldDes[786]->size=sizeof(prec->l729);
  pdbRecordType->papFldDes[786]->offset=(short)((char *)&prec->l729 - (char *)prec);
  pdbRecordType->papFldDes[787]->size=sizeof(prec->l730);
  pdbRecordType->papFldDes[787]->offset=(short)((char *)&prec->l730 - (char *)prec);
  pdbRecordType->papFldDes[788]->size=sizeof(prec->l731);
  pdbRecordType->papFldDes[788]->offset=(short)((char *)&prec->l731 - (char *)prec);
  pdbRecordType->papFldDes[789]->size=sizeof(prec->l732);
  pdbRecordType->papFldDes[789]->offset=(short)((char *)&prec->l732 - (char *)prec);
  pdbRecordType->papFldDes[790]->size=sizeof(prec->l733);
  pdbRecordType->papFldDes[790]->offset=(short)((char *)&prec->l733 - (char *)prec);
  pdbRecordType->papFldDes[791]->size=sizeof(prec->l734);
  pdbRecordType->papFldDes[791]->offset=(short)((char *)&prec->l734 - (char *)prec);
  pdbRecordType->papFldDes[792]->size=sizeof(prec->l735);
  pdbRecordType->papFldDes[792]->offset=(short)((char *)&prec->l735 - (char *)prec);
  pdbRecordType->papFldDes[793]->size=sizeof(prec->l736);
  pdbRecordType->papFldDes[793]->offset=(short)((char *)&prec->l736 - (char *)prec);
  pdbRecordType->papFldDes[794]->size=sizeof(prec->l737);
  pdbRecordType->papFldDes[794]->offset=(short)((char *)&prec->l737 - (char *)prec);
  pdbRecordType->papFldDes[795]->size=sizeof(prec->l738);
  pdbRecordType->papFldDes[795]->offset=(short)((char *)&prec->l738 - (char *)prec);
  pdbRecordType->papFldDes[796]->size=sizeof(prec->l739);
  pdbRecordType->papFldDes[796]->offset=(short)((char *)&prec->l739 - (char *)prec);
  pdbRecordType->papFldDes[797]->size=sizeof(prec->l740);
  pdbRecordType->papFldDes[797]->offset=(short)((char *)&prec->l740 - (char *)prec);
  pdbRecordType->papFldDes[798]->size=sizeof(prec->l741);
  pdbRecordType->papFldDes[798]->offset=(short)((char *)&prec->l741 - (char *)prec);
  pdbRecordType->papFldDes[799]->size=sizeof(prec->l742);
  pdbRecordType->papFldDes[799]->offset=(short)((char *)&prec->l742 - (char *)prec);
  pdbRecordType->papFldDes[800]->size=sizeof(prec->l743);
  pdbRecordType->papFldDes[800]->offset=(short)((char *)&prec->l743 - (char *)prec);
  pdbRecordType->papFldDes[801]->size=sizeof(prec->l744);
  pdbRecordType->papFldDes[801]->offset=(short)((char *)&prec->l744 - (char *)prec);
  pdbRecordType->papFldDes[802]->size=sizeof(prec->l745);
  pdbRecordType->papFldDes[802]->offset=(short)((char *)&prec->l745 - (char *)prec);
  pdbRecordType->papFldDes[803]->size=sizeof(prec->l746);
  pdbRecordType->papFldDes[803]->offset=(short)((char *)&prec->l746 - (char *)prec);
  pdbRecordType->papFldDes[804]->size=sizeof(prec->l747);
  pdbRecordType->papFldDes[804]->offset=(short)((char *)&prec->l747 - (char *)prec);
  pdbRecordType->papFldDes[805]->size=sizeof(prec->l748);
  pdbRecordType->papFldDes[805]->offset=(short)((char *)&prec->l748 - (char *)prec);
  pdbRecordType->papFldDes[806]->size=sizeof(prec->l749);
  pdbRecordType->papFldDes[806]->offset=(short)((char *)&prec->l749 - (char *)prec);
  pdbRecordType->papFldDes[807]->size=sizeof(prec->l750);
  pdbRecordType->papFldDes[807]->offset=(short)((char *)&prec->l750 - (char *)prec);
  pdbRecordType->papFldDes[808]->size=sizeof(prec->l751);
  pdbRecordType->papFldDes[808]->offset=(short)((char *)&prec->l751 - (char *)prec);
  pdbRecordType->papFldDes[809]->size=sizeof(prec->l752);
  pdbRecordType->papFldDes[809]->offset=(short)((char *)&prec->l752 - (char *)prec);
  pdbRecordType->papFldDes[810]->size=sizeof(prec->l753);
  pdbRecordType->papFldDes[810]->offset=(short)((char *)&prec->l753 - (char *)prec);
  pdbRecordType->papFldDes[811]->size=sizeof(prec->l754);
  pdbRecordType->papFldDes[811]->offset=(short)((char *)&prec->l754 - (char *)prec);
  pdbRecordType->papFldDes[812]->size=sizeof(prec->l755);
  pdbRecordType->papFldDes[812]->offset=(short)((char *)&prec->l755 - (char *)prec);
  pdbRecordType->papFldDes[813]->size=sizeof(prec->l756);
  pdbRecordType->papFldDes[813]->offset=(short)((char *)&prec->l756 - (char *)prec);
  pdbRecordType->papFldDes[814]->size=sizeof(prec->l757);
  pdbRecordType->papFldDes[814]->offset=(short)((char *)&prec->l757 - (char *)prec);
  pdbRecordType->papFldDes[815]->size=sizeof(prec->l758);
  pdbRecordType->papFldDes[815]->offset=(short)((char *)&prec->l758 - (char *)prec);
  pdbRecordType->papFldDes[816]->size=sizeof(prec->l759);
  pdbRecordType->papFldDes[816]->offset=(short)((char *)&prec->l759 - (char *)prec);
  pdbRecordType->papFldDes[817]->size=sizeof(prec->l760);
  pdbRecordType->papFldDes[817]->offset=(short)((char *)&prec->l760 - (char *)prec);
  pdbRecordType->papFldDes[818]->size=sizeof(prec->l761);
  pdbRecordType->papFldDes[818]->offset=(short)((char *)&prec->l761 - (char *)prec);
  pdbRecordType->papFldDes[819]->size=sizeof(prec->l762);
  pdbRecordType->papFldDes[819]->offset=(short)((char *)&prec->l762 - (char *)prec);
  pdbRecordType->papFldDes[820]->size=sizeof(prec->l763);
  pdbRecordType->papFldDes[820]->offset=(short)((char *)&prec->l763 - (char *)prec);
  pdbRecordType->papFldDes[821]->size=sizeof(prec->l764);
  pdbRecordType->papFldDes[821]->offset=(short)((char *)&prec->l764 - (char *)prec);
  pdbRecordType->papFldDes[822]->size=sizeof(prec->l765);
  pdbRecordType->papFldDes[822]->offset=(short)((char *)&prec->l765 - (char *)prec);
  pdbRecordType->papFldDes[823]->size=sizeof(prec->l766);
  pdbRecordType->papFldDes[823]->offset=(short)((char *)&prec->l766 - (char *)prec);
  pdbRecordType->papFldDes[824]->size=sizeof(prec->l767);
  pdbRecordType->papFldDes[824]->offset=(short)((char *)&prec->l767 - (char *)prec);
  pdbRecordType->papFldDes[825]->size=sizeof(prec->l768);
  pdbRecordType->papFldDes[825]->offset=(short)((char *)&prec->l768 - (char *)prec);
  pdbRecordType->papFldDes[826]->size=sizeof(prec->l769);
  pdbRecordType->papFldDes[826]->offset=(short)((char *)&prec->l769 - (char *)prec);
  pdbRecordType->papFldDes[827]->size=sizeof(prec->l770);
  pdbRecordType->papFldDes[827]->offset=(short)((char *)&prec->l770 - (char *)prec);
  pdbRecordType->papFldDes[828]->size=sizeof(prec->l771);
  pdbRecordType->papFldDes[828]->offset=(short)((char *)&prec->l771 - (char *)prec);
  pdbRecordType->papFldDes[829]->size=sizeof(prec->l772);
  pdbRecordType->papFldDes[829]->offset=(short)((char *)&prec->l772 - (char *)prec);
  pdbRecordType->papFldDes[830]->size=sizeof(prec->l773);
  pdbRecordType->papFldDes[830]->offset=(short)((char *)&prec->l773 - (char *)prec);
  pdbRecordType->papFldDes[831]->size=sizeof(prec->l774);
  pdbRecordType->papFldDes[831]->offset=(short)((char *)&prec->l774 - (char *)prec);
  pdbRecordType->papFldDes[832]->size=sizeof(prec->l775);
  pdbRecordType->papFldDes[832]->offset=(short)((char *)&prec->l775 - (char *)prec);
  pdbRecordType->papFldDes[833]->size=sizeof(prec->l776);
  pdbRecordType->papFldDes[833]->offset=(short)((char *)&prec->l776 - (char *)prec);
  pdbRecordType->papFldDes[834]->size=sizeof(prec->l777);
  pdbRecordType->papFldDes[834]->offset=(short)((char *)&prec->l777 - (char *)prec);
  pdbRecordType->papFldDes[835]->size=sizeof(prec->l778);
  pdbRecordType->papFldDes[835]->offset=(short)((char *)&prec->l778 - (char *)prec);
  pdbRecordType->papFldDes[836]->size=sizeof(prec->l779);
  pdbRecordType->papFldDes[836]->offset=(short)((char *)&prec->l779 - (char *)prec);
  pdbRecordType->papFldDes[837]->size=sizeof(prec->l780);
  pdbRecordType->papFldDes[837]->offset=(short)((char *)&prec->l780 - (char *)prec);
  pdbRecordType->papFldDes[838]->size=sizeof(prec->l781);
  pdbRecordType->papFldDes[838]->offset=(short)((char *)&prec->l781 - (char *)prec);
  pdbRecordType->papFldDes[839]->size=sizeof(prec->l782);
  pdbRecordType->papFldDes[839]->offset=(short)((char *)&prec->l782 - (char *)prec);
  pdbRecordType->papFldDes[840]->size=sizeof(prec->l783);
  pdbRecordType->papFldDes[840]->offset=(short)((char *)&prec->l783 - (char *)prec);
  pdbRecordType->papFldDes[841]->size=sizeof(prec->l784);
  pdbRecordType->papFldDes[841]->offset=(short)((char *)&prec->l784 - (char *)prec);
  pdbRecordType->papFldDes[842]->size=sizeof(prec->l785);
  pdbRecordType->papFldDes[842]->offset=(short)((char *)&prec->l785 - (char *)prec);
  pdbRecordType->papFldDes[843]->size=sizeof(prec->l786);
  pdbRecordType->papFldDes[843]->offset=(short)((char *)&prec->l786 - (char *)prec);
  pdbRecordType->papFldDes[844]->size=sizeof(prec->l787);
  pdbRecordType->papFldDes[844]->offset=(short)((char *)&prec->l787 - (char *)prec);
  pdbRecordType->papFldDes[845]->size=sizeof(prec->l788);
  pdbRecordType->papFldDes[845]->offset=(short)((char *)&prec->l788 - (char *)prec);
  pdbRecordType->papFldDes[846]->size=sizeof(prec->l789);
  pdbRecordType->papFldDes[846]->offset=(short)((char *)&prec->l789 - (char *)prec);
  pdbRecordType->papFldDes[847]->size=sizeof(prec->l790);
  pdbRecordType->papFldDes[847]->offset=(short)((char *)&prec->l790 - (char *)prec);
  pdbRecordType->papFldDes[848]->size=sizeof(prec->l791);
  pdbRecordType->papFldDes[848]->offset=(short)((char *)&prec->l791 - (char *)prec);
  pdbRecordType->papFldDes[849]->size=sizeof(prec->l792);
  pdbRecordType->papFldDes[849]->offset=(short)((char *)&prec->l792 - (char *)prec);
  pdbRecordType->papFldDes[850]->size=sizeof(prec->l793);
  pdbRecordType->papFldDes[850]->offset=(short)((char *)&prec->l793 - (char *)prec);
  pdbRecordType->papFldDes[851]->size=sizeof(prec->l794);
  pdbRecordType->papFldDes[851]->offset=(short)((char *)&prec->l794 - (char *)prec);
  pdbRecordType->papFldDes[852]->size=sizeof(prec->l795);
  pdbRecordType->papFldDes[852]->offset=(short)((char *)&prec->l795 - (char *)prec);
  pdbRecordType->papFldDes[853]->size=sizeof(prec->l796);
  pdbRecordType->papFldDes[853]->offset=(short)((char *)&prec->l796 - (char *)prec);
  pdbRecordType->papFldDes[854]->size=sizeof(prec->l797);
  pdbRecordType->papFldDes[854]->offset=(short)((char *)&prec->l797 - (char *)prec);
  pdbRecordType->papFldDes[855]->size=sizeof(prec->l798);
  pdbRecordType->papFldDes[855]->offset=(short)((char *)&prec->l798 - (char *)prec);
  pdbRecordType->papFldDes[856]->size=sizeof(prec->l799);
  pdbRecordType->papFldDes[856]->offset=(short)((char *)&prec->l799 - (char *)prec);
  pdbRecordType->papFldDes[857]->size=sizeof(prec->l800);
  pdbRecordType->papFldDes[857]->offset=(short)((char *)&prec->l800 - (char *)prec);
  pdbRecordType->papFldDes[858]->size=sizeof(prec->l801);
  pdbRecordType->papFldDes[858]->offset=(short)((char *)&prec->l801 - (char *)prec);
  pdbRecordType->papFldDes[859]->size=sizeof(prec->l802);
  pdbRecordType->papFldDes[859]->offset=(short)((char *)&prec->l802 - (char *)prec);
  pdbRecordType->papFldDes[860]->size=sizeof(prec->l803);
  pdbRecordType->papFldDes[860]->offset=(short)((char *)&prec->l803 - (char *)prec);
  pdbRecordType->papFldDes[861]->size=sizeof(prec->l804);
  pdbRecordType->papFldDes[861]->offset=(short)((char *)&prec->l804 - (char *)prec);
  pdbRecordType->papFldDes[862]->size=sizeof(prec->l805);
  pdbRecordType->papFldDes[862]->offset=(short)((char *)&prec->l805 - (char *)prec);
  pdbRecordType->papFldDes[863]->size=sizeof(prec->l806);
  pdbRecordType->papFldDes[863]->offset=(short)((char *)&prec->l806 - (char *)prec);
  pdbRecordType->papFldDes[864]->size=sizeof(prec->l807);
  pdbRecordType->papFldDes[864]->offset=(short)((char *)&prec->l807 - (char *)prec);
  pdbRecordType->papFldDes[865]->size=sizeof(prec->l808);
  pdbRecordType->papFldDes[865]->offset=(short)((char *)&prec->l808 - (char *)prec);
  pdbRecordType->papFldDes[866]->size=sizeof(prec->l809);
  pdbRecordType->papFldDes[866]->offset=(short)((char *)&prec->l809 - (char *)prec);
  pdbRecordType->papFldDes[867]->size=sizeof(prec->l810);
  pdbRecordType->papFldDes[867]->offset=(short)((char *)&prec->l810 - (char *)prec);
  pdbRecordType->papFldDes[868]->size=sizeof(prec->l811);
  pdbRecordType->papFldDes[868]->offset=(short)((char *)&prec->l811 - (char *)prec);
  pdbRecordType->papFldDes[869]->size=sizeof(prec->l812);
  pdbRecordType->papFldDes[869]->offset=(short)((char *)&prec->l812 - (char *)prec);
  pdbRecordType->papFldDes[870]->size=sizeof(prec->l813);
  pdbRecordType->papFldDes[870]->offset=(short)((char *)&prec->l813 - (char *)prec);
  pdbRecordType->papFldDes[871]->size=sizeof(prec->l814);
  pdbRecordType->papFldDes[871]->offset=(short)((char *)&prec->l814 - (char *)prec);
  pdbRecordType->papFldDes[872]->size=sizeof(prec->l815);
  pdbRecordType->papFldDes[872]->offset=(short)((char *)&prec->l815 - (char *)prec);
  pdbRecordType->papFldDes[873]->size=sizeof(prec->l816);
  pdbRecordType->papFldDes[873]->offset=(short)((char *)&prec->l816 - (char *)prec);
  pdbRecordType->papFldDes[874]->size=sizeof(prec->l817);
  pdbRecordType->papFldDes[874]->offset=(short)((char *)&prec->l817 - (char *)prec);
  pdbRecordType->papFldDes[875]->size=sizeof(prec->l818);
  pdbRecordType->papFldDes[875]->offset=(short)((char *)&prec->l818 - (char *)prec);
  pdbRecordType->papFldDes[876]->size=sizeof(prec->l819);
  pdbRecordType->papFldDes[876]->offset=(short)((char *)&prec->l819 - (char *)prec);
  pdbRecordType->papFldDes[877]->size=sizeof(prec->l820);
  pdbRecordType->papFldDes[877]->offset=(short)((char *)&prec->l820 - (char *)prec);
  pdbRecordType->papFldDes[878]->size=sizeof(prec->l821);
  pdbRecordType->papFldDes[878]->offset=(short)((char *)&prec->l821 - (char *)prec);
  pdbRecordType->papFldDes[879]->size=sizeof(prec->l822);
  pdbRecordType->papFldDes[879]->offset=(short)((char *)&prec->l822 - (char *)prec);
  pdbRecordType->papFldDes[880]->size=sizeof(prec->l823);
  pdbRecordType->papFldDes[880]->offset=(short)((char *)&prec->l823 - (char *)prec);
  pdbRecordType->papFldDes[881]->size=sizeof(prec->l824);
  pdbRecordType->papFldDes[881]->offset=(short)((char *)&prec->l824 - (char *)prec);
  pdbRecordType->papFldDes[882]->size=sizeof(prec->l825);
  pdbRecordType->papFldDes[882]->offset=(short)((char *)&prec->l825 - (char *)prec);
  pdbRecordType->papFldDes[883]->size=sizeof(prec->l826);
  pdbRecordType->papFldDes[883]->offset=(short)((char *)&prec->l826 - (char *)prec);
  pdbRecordType->papFldDes[884]->size=sizeof(prec->l827);
  pdbRecordType->papFldDes[884]->offset=(short)((char *)&prec->l827 - (char *)prec);
  pdbRecordType->papFldDes[885]->size=sizeof(prec->l828);
  pdbRecordType->papFldDes[885]->offset=(short)((char *)&prec->l828 - (char *)prec);
  pdbRecordType->papFldDes[886]->size=sizeof(prec->l829);
  pdbRecordType->papFldDes[886]->offset=(short)((char *)&prec->l829 - (char *)prec);
  pdbRecordType->papFldDes[887]->size=sizeof(prec->l830);
  pdbRecordType->papFldDes[887]->offset=(short)((char *)&prec->l830 - (char *)prec);
  pdbRecordType->papFldDes[888]->size=sizeof(prec->l831);
  pdbRecordType->papFldDes[888]->offset=(short)((char *)&prec->l831 - (char *)prec);
  pdbRecordType->papFldDes[889]->size=sizeof(prec->l832);
  pdbRecordType->papFldDes[889]->offset=(short)((char *)&prec->l832 - (char *)prec);
  pdbRecordType->papFldDes[890]->size=sizeof(prec->l833);
  pdbRecordType->papFldDes[890]->offset=(short)((char *)&prec->l833 - (char *)prec);
  pdbRecordType->papFldDes[891]->size=sizeof(prec->l834);
  pdbRecordType->papFldDes[891]->offset=(short)((char *)&prec->l834 - (char *)prec);
  pdbRecordType->papFldDes[892]->size=sizeof(prec->l835);
  pdbRecordType->papFldDes[892]->offset=(short)((char *)&prec->l835 - (char *)prec);
  pdbRecordType->papFldDes[893]->size=sizeof(prec->l836);
  pdbRecordType->papFldDes[893]->offset=(short)((char *)&prec->l836 - (char *)prec);
  pdbRecordType->papFldDes[894]->size=sizeof(prec->l837);
  pdbRecordType->papFldDes[894]->offset=(short)((char *)&prec->l837 - (char *)prec);
  pdbRecordType->papFldDes[895]->size=sizeof(prec->l838);
  pdbRecordType->papFldDes[895]->offset=(short)((char *)&prec->l838 - (char *)prec);
  pdbRecordType->papFldDes[896]->size=sizeof(prec->l839);
  pdbRecordType->papFldDes[896]->offset=(short)((char *)&prec->l839 - (char *)prec);
  pdbRecordType->papFldDes[897]->size=sizeof(prec->l840);
  pdbRecordType->papFldDes[897]->offset=(short)((char *)&prec->l840 - (char *)prec);
  pdbRecordType->papFldDes[898]->size=sizeof(prec->l841);
  pdbRecordType->papFldDes[898]->offset=(short)((char *)&prec->l841 - (char *)prec);
  pdbRecordType->papFldDes[899]->size=sizeof(prec->l842);
  pdbRecordType->papFldDes[899]->offset=(short)((char *)&prec->l842 - (char *)prec);
  pdbRecordType->papFldDes[900]->size=sizeof(prec->l843);
  pdbRecordType->papFldDes[900]->offset=(short)((char *)&prec->l843 - (char *)prec);
  pdbRecordType->papFldDes[901]->size=sizeof(prec->l844);
  pdbRecordType->papFldDes[901]->offset=(short)((char *)&prec->l844 - (char *)prec);
  pdbRecordType->papFldDes[902]->size=sizeof(prec->l845);
  pdbRecordType->papFldDes[902]->offset=(short)((char *)&prec->l845 - (char *)prec);
  pdbRecordType->papFldDes[903]->size=sizeof(prec->l846);
  pdbRecordType->papFldDes[903]->offset=(short)((char *)&prec->l846 - (char *)prec);
  pdbRecordType->papFldDes[904]->size=sizeof(prec->l847);
  pdbRecordType->papFldDes[904]->offset=(short)((char *)&prec->l847 - (char *)prec);
  pdbRecordType->papFldDes[905]->size=sizeof(prec->l848);
  pdbRecordType->papFldDes[905]->offset=(short)((char *)&prec->l848 - (char *)prec);
  pdbRecordType->papFldDes[906]->size=sizeof(prec->l849);
  pdbRecordType->papFldDes[906]->offset=(short)((char *)&prec->l849 - (char *)prec);
  pdbRecordType->papFldDes[907]->size=sizeof(prec->l850);
  pdbRecordType->papFldDes[907]->offset=(short)((char *)&prec->l850 - (char *)prec);
  pdbRecordType->papFldDes[908]->size=sizeof(prec->l851);
  pdbRecordType->papFldDes[908]->offset=(short)((char *)&prec->l851 - (char *)prec);
  pdbRecordType->papFldDes[909]->size=sizeof(prec->l852);
  pdbRecordType->papFldDes[909]->offset=(short)((char *)&prec->l852 - (char *)prec);
  pdbRecordType->papFldDes[910]->size=sizeof(prec->l853);
  pdbRecordType->papFldDes[910]->offset=(short)((char *)&prec->l853 - (char *)prec);
  pdbRecordType->papFldDes[911]->size=sizeof(prec->l854);
  pdbRecordType->papFldDes[911]->offset=(short)((char *)&prec->l854 - (char *)prec);
  pdbRecordType->papFldDes[912]->size=sizeof(prec->l855);
  pdbRecordType->papFldDes[912]->offset=(short)((char *)&prec->l855 - (char *)prec);
  pdbRecordType->papFldDes[913]->size=sizeof(prec->l856);
  pdbRecordType->papFldDes[913]->offset=(short)((char *)&prec->l856 - (char *)prec);
  pdbRecordType->papFldDes[914]->size=sizeof(prec->l857);
  pdbRecordType->papFldDes[914]->offset=(short)((char *)&prec->l857 - (char *)prec);
  pdbRecordType->papFldDes[915]->size=sizeof(prec->l858);
  pdbRecordType->papFldDes[915]->offset=(short)((char *)&prec->l858 - (char *)prec);
  pdbRecordType->papFldDes[916]->size=sizeof(prec->l859);
  pdbRecordType->papFldDes[916]->offset=(short)((char *)&prec->l859 - (char *)prec);
  pdbRecordType->papFldDes[917]->size=sizeof(prec->l860);
  pdbRecordType->papFldDes[917]->offset=(short)((char *)&prec->l860 - (char *)prec);
  pdbRecordType->papFldDes[918]->size=sizeof(prec->l861);
  pdbRecordType->papFldDes[918]->offset=(short)((char *)&prec->l861 - (char *)prec);
  pdbRecordType->papFldDes[919]->size=sizeof(prec->l862);
  pdbRecordType->papFldDes[919]->offset=(short)((char *)&prec->l862 - (char *)prec);
  pdbRecordType->papFldDes[920]->size=sizeof(prec->l863);
  pdbRecordType->papFldDes[920]->offset=(short)((char *)&prec->l863 - (char *)prec);
  pdbRecordType->papFldDes[921]->size=sizeof(prec->l864);
  pdbRecordType->papFldDes[921]->offset=(short)((char *)&prec->l864 - (char *)prec);
  pdbRecordType->papFldDes[922]->size=sizeof(prec->l865);
  pdbRecordType->papFldDes[922]->offset=(short)((char *)&prec->l865 - (char *)prec);
  pdbRecordType->papFldDes[923]->size=sizeof(prec->l866);
  pdbRecordType->papFldDes[923]->offset=(short)((char *)&prec->l866 - (char *)prec);
  pdbRecordType->papFldDes[924]->size=sizeof(prec->l867);
  pdbRecordType->papFldDes[924]->offset=(short)((char *)&prec->l867 - (char *)prec);
  pdbRecordType->papFldDes[925]->size=sizeof(prec->l868);
  pdbRecordType->papFldDes[925]->offset=(short)((char *)&prec->l868 - (char *)prec);
  pdbRecordType->papFldDes[926]->size=sizeof(prec->l869);
  pdbRecordType->papFldDes[926]->offset=(short)((char *)&prec->l869 - (char *)prec);
  pdbRecordType->papFldDes[927]->size=sizeof(prec->l870);
  pdbRecordType->papFldDes[927]->offset=(short)((char *)&prec->l870 - (char *)prec);
  pdbRecordType->papFldDes[928]->size=sizeof(prec->l871);
  pdbRecordType->papFldDes[928]->offset=(short)((char *)&prec->l871 - (char *)prec);
  pdbRecordType->papFldDes[929]->size=sizeof(prec->l872);
  pdbRecordType->papFldDes[929]->offset=(short)((char *)&prec->l872 - (char *)prec);
  pdbRecordType->papFldDes[930]->size=sizeof(prec->l873);
  pdbRecordType->papFldDes[930]->offset=(short)((char *)&prec->l873 - (char *)prec);
  pdbRecordType->papFldDes[931]->size=sizeof(prec->l874);
  pdbRecordType->papFldDes[931]->offset=(short)((char *)&prec->l874 - (char *)prec);
  pdbRecordType->papFldDes[932]->size=sizeof(prec->l875);
  pdbRecordType->papFldDes[932]->offset=(short)((char *)&prec->l875 - (char *)prec);
  pdbRecordType->papFldDes[933]->size=sizeof(prec->l876);
  pdbRecordType->papFldDes[933]->offset=(short)((char *)&prec->l876 - (char *)prec);
  pdbRecordType->papFldDes[934]->size=sizeof(prec->l877);
  pdbRecordType->papFldDes[934]->offset=(short)((char *)&prec->l877 - (char *)prec);
  pdbRecordType->papFldDes[935]->size=sizeof(prec->l878);
  pdbRecordType->papFldDes[935]->offset=(short)((char *)&prec->l878 - (char *)prec);
  pdbRecordType->papFldDes[936]->size=sizeof(prec->l879);
  pdbRecordType->papFldDes[936]->offset=(short)((char *)&prec->l879 - (char *)prec);
  pdbRecordType->papFldDes[937]->size=sizeof(prec->l880);
  pdbRecordType->papFldDes[937]->offset=(short)((char *)&prec->l880 - (char *)prec);
  pdbRecordType->papFldDes[938]->size=sizeof(prec->l881);
  pdbRecordType->papFldDes[938]->offset=(short)((char *)&prec->l881 - (char *)prec);
  pdbRecordType->papFldDes[939]->size=sizeof(prec->l882);
  pdbRecordType->papFldDes[939]->offset=(short)((char *)&prec->l882 - (char *)prec);
  pdbRecordType->papFldDes[940]->size=sizeof(prec->l883);
  pdbRecordType->papFldDes[940]->offset=(short)((char *)&prec->l883 - (char *)prec);
  pdbRecordType->papFldDes[941]->size=sizeof(prec->l884);
  pdbRecordType->papFldDes[941]->offset=(short)((char *)&prec->l884 - (char *)prec);
  pdbRecordType->papFldDes[942]->size=sizeof(prec->l885);
  pdbRecordType->papFldDes[942]->offset=(short)((char *)&prec->l885 - (char *)prec);
  pdbRecordType->papFldDes[943]->size=sizeof(prec->l886);
  pdbRecordType->papFldDes[943]->offset=(short)((char *)&prec->l886 - (char *)prec);
  pdbRecordType->papFldDes[944]->size=sizeof(prec->l887);
  pdbRecordType->papFldDes[944]->offset=(short)((char *)&prec->l887 - (char *)prec);
  pdbRecordType->papFldDes[945]->size=sizeof(prec->l888);
  pdbRecordType->papFldDes[945]->offset=(short)((char *)&prec->l888 - (char *)prec);
  pdbRecordType->papFldDes[946]->size=sizeof(prec->l889);
  pdbRecordType->papFldDes[946]->offset=(short)((char *)&prec->l889 - (char *)prec);
  pdbRecordType->papFldDes[947]->size=sizeof(prec->l890);
  pdbRecordType->papFldDes[947]->offset=(short)((char *)&prec->l890 - (char *)prec);
  pdbRecordType->papFldDes[948]->size=sizeof(prec->l891);
  pdbRecordType->papFldDes[948]->offset=(short)((char *)&prec->l891 - (char *)prec);
  pdbRecordType->papFldDes[949]->size=sizeof(prec->l892);
  pdbRecordType->papFldDes[949]->offset=(short)((char *)&prec->l892 - (char *)prec);
  pdbRecordType->papFldDes[950]->size=sizeof(prec->l893);
  pdbRecordType->papFldDes[950]->offset=(short)((char *)&prec->l893 - (char *)prec);
  pdbRecordType->papFldDes[951]->size=sizeof(prec->l894);
  pdbRecordType->papFldDes[951]->offset=(short)((char *)&prec->l894 - (char *)prec);
  pdbRecordType->papFldDes[952]->size=sizeof(prec->l895);
  pdbRecordType->papFldDes[952]->offset=(short)((char *)&prec->l895 - (char *)prec);
  pdbRecordType->papFldDes[953]->size=sizeof(prec->l896);
  pdbRecordType->papFldDes[953]->offset=(short)((char *)&prec->l896 - (char *)prec);
  pdbRecordType->papFldDes[954]->size=sizeof(prec->l897);
  pdbRecordType->papFldDes[954]->offset=(short)((char *)&prec->l897 - (char *)prec);
  pdbRecordType->papFldDes[955]->size=sizeof(prec->l898);
  pdbRecordType->papFldDes[955]->offset=(short)((char *)&prec->l898 - (char *)prec);
  pdbRecordType->papFldDes[956]->size=sizeof(prec->l899);
  pdbRecordType->papFldDes[956]->offset=(short)((char *)&prec->l899 - (char *)prec);
  pdbRecordType->papFldDes[957]->size=sizeof(prec->l900);
  pdbRecordType->papFldDes[957]->offset=(short)((char *)&prec->l900 - (char *)prec);
  pdbRecordType->papFldDes[958]->size=sizeof(prec->l901);
  pdbRecordType->papFldDes[958]->offset=(short)((char *)&prec->l901 - (char *)prec);
  pdbRecordType->papFldDes[959]->size=sizeof(prec->l902);
  pdbRecordType->papFldDes[959]->offset=(short)((char *)&prec->l902 - (char *)prec);
  pdbRecordType->papFldDes[960]->size=sizeof(prec->l903);
  pdbRecordType->papFldDes[960]->offset=(short)((char *)&prec->l903 - (char *)prec);
  pdbRecordType->papFldDes[961]->size=sizeof(prec->l904);
  pdbRecordType->papFldDes[961]->offset=(short)((char *)&prec->l904 - (char *)prec);
  pdbRecordType->papFldDes[962]->size=sizeof(prec->l905);
  pdbRecordType->papFldDes[962]->offset=(short)((char *)&prec->l905 - (char *)prec);
  pdbRecordType->papFldDes[963]->size=sizeof(prec->l906);
  pdbRecordType->papFldDes[963]->offset=(short)((char *)&prec->l906 - (char *)prec);
  pdbRecordType->papFldDes[964]->size=sizeof(prec->l907);
  pdbRecordType->papFldDes[964]->offset=(short)((char *)&prec->l907 - (char *)prec);
  pdbRecordType->papFldDes[965]->size=sizeof(prec->l908);
  pdbRecordType->papFldDes[965]->offset=(short)((char *)&prec->l908 - (char *)prec);
  pdbRecordType->papFldDes[966]->size=sizeof(prec->l909);
  pdbRecordType->papFldDes[966]->offset=(short)((char *)&prec->l909 - (char *)prec);
  pdbRecordType->papFldDes[967]->size=sizeof(prec->l910);
  pdbRecordType->papFldDes[967]->offset=(short)((char *)&prec->l910 - (char *)prec);
  pdbRecordType->papFldDes[968]->size=sizeof(prec->l911);
  pdbRecordType->papFldDes[968]->offset=(short)((char *)&prec->l911 - (char *)prec);
  pdbRecordType->papFldDes[969]->size=sizeof(prec->l912);
  pdbRecordType->papFldDes[969]->offset=(short)((char *)&prec->l912 - (char *)prec);
  pdbRecordType->papFldDes[970]->size=sizeof(prec->l913);
  pdbRecordType->papFldDes[970]->offset=(short)((char *)&prec->l913 - (char *)prec);
  pdbRecordType->papFldDes[971]->size=sizeof(prec->l914);
  pdbRecordType->papFldDes[971]->offset=(short)((char *)&prec->l914 - (char *)prec);
  pdbRecordType->papFldDes[972]->size=sizeof(prec->l915);
  pdbRecordType->papFldDes[972]->offset=(short)((char *)&prec->l915 - (char *)prec);
  pdbRecordType->papFldDes[973]->size=sizeof(prec->l916);
  pdbRecordType->papFldDes[973]->offset=(short)((char *)&prec->l916 - (char *)prec);
  pdbRecordType->papFldDes[974]->size=sizeof(prec->l917);
  pdbRecordType->papFldDes[974]->offset=(short)((char *)&prec->l917 - (char *)prec);
  pdbRecordType->papFldDes[975]->size=sizeof(prec->l918);
  pdbRecordType->papFldDes[975]->offset=(short)((char *)&prec->l918 - (char *)prec);
  pdbRecordType->papFldDes[976]->size=sizeof(prec->l919);
  pdbRecordType->papFldDes[976]->offset=(short)((char *)&prec->l919 - (char *)prec);
  pdbRecordType->papFldDes[977]->size=sizeof(prec->l920);
  pdbRecordType->papFldDes[977]->offset=(short)((char *)&prec->l920 - (char *)prec);
  pdbRecordType->papFldDes[978]->size=sizeof(prec->l921);
  pdbRecordType->papFldDes[978]->offset=(short)((char *)&prec->l921 - (char *)prec);
  pdbRecordType->papFldDes[979]->size=sizeof(prec->l922);
  pdbRecordType->papFldDes[979]->offset=(short)((char *)&prec->l922 - (char *)prec);
  pdbRecordType->papFldDes[980]->size=sizeof(prec->l923);
  pdbRecordType->papFldDes[980]->offset=(short)((char *)&prec->l923 - (char *)prec);
  pdbRecordType->papFldDes[981]->size=sizeof(prec->l924);
  pdbRecordType->papFldDes[981]->offset=(short)((char *)&prec->l924 - (char *)prec);
  pdbRecordType->papFldDes[982]->size=sizeof(prec->l925);
  pdbRecordType->papFldDes[982]->offset=(short)((char *)&prec->l925 - (char *)prec);
  pdbRecordType->papFldDes[983]->size=sizeof(prec->l926);
  pdbRecordType->papFldDes[983]->offset=(short)((char *)&prec->l926 - (char *)prec);
  pdbRecordType->papFldDes[984]->size=sizeof(prec->l927);
  pdbRecordType->papFldDes[984]->offset=(short)((char *)&prec->l927 - (char *)prec);
  pdbRecordType->papFldDes[985]->size=sizeof(prec->l928);
  pdbRecordType->papFldDes[985]->offset=(short)((char *)&prec->l928 - (char *)prec);
  pdbRecordType->papFldDes[986]->size=sizeof(prec->l929);
  pdbRecordType->papFldDes[986]->offset=(short)((char *)&prec->l929 - (char *)prec);
  pdbRecordType->papFldDes[987]->size=sizeof(prec->l930);
  pdbRecordType->papFldDes[987]->offset=(short)((char *)&prec->l930 - (char *)prec);
  pdbRecordType->papFldDes[988]->size=sizeof(prec->l931);
  pdbRecordType->papFldDes[988]->offset=(short)((char *)&prec->l931 - (char *)prec);
  pdbRecordType->papFldDes[989]->size=sizeof(prec->l932);
  pdbRecordType->papFldDes[989]->offset=(short)((char *)&prec->l932 - (char *)prec);
  pdbRecordType->papFldDes[990]->size=sizeof(prec->l933);
  pdbRecordType->papFldDes[990]->offset=(short)((char *)&prec->l933 - (char *)prec);
  pdbRecordType->papFldDes[991]->size=sizeof(prec->l934);
  pdbRecordType->papFldDes[991]->offset=(short)((char *)&prec->l934 - (char *)prec);
  pdbRecordType->papFldDes[992]->size=sizeof(prec->l935);
  pdbRecordType->papFldDes[992]->offset=(short)((char *)&prec->l935 - (char *)prec);
  pdbRecordType->papFldDes[993]->size=sizeof(prec->l936);
  pdbRecordType->papFldDes[993]->offset=(short)((char *)&prec->l936 - (char *)prec);
  pdbRecordType->papFldDes[994]->size=sizeof(prec->l937);
  pdbRecordType->papFldDes[994]->offset=(short)((char *)&prec->l937 - (char *)prec);
  pdbRecordType->papFldDes[995]->size=sizeof(prec->l938);
  pdbRecordType->papFldDes[995]->offset=(short)((char *)&prec->l938 - (char *)prec);
  pdbRecordType->papFldDes[996]->size=sizeof(prec->l939);
  pdbRecordType->papFldDes[996]->offset=(short)((char *)&prec->l939 - (char *)prec);
  pdbRecordType->papFldDes[997]->size=sizeof(prec->l940);
  pdbRecordType->papFldDes[997]->offset=(short)((char *)&prec->l940 - (char *)prec);
  pdbRecordType->papFldDes[998]->size=sizeof(prec->l941);
  pdbRecordType->papFldDes[998]->offset=(short)((char *)&prec->l941 - (char *)prec);
  pdbRecordType->papFldDes[999]->size=sizeof(prec->l942);
  pdbRecordType->papFldDes[999]->offset=(short)((char *)&prec->l942 - (char *)prec);
  pdbRecordType->papFldDes[1000]->size=sizeof(prec->l943);
  pdbRecordType->papFldDes[1000]->offset=(short)((char *)&prec->l943 - (char *)prec);
  pdbRecordType->papFldDes[1001]->size=sizeof(prec->l944);
  pdbRecordType->papFldDes[1001]->offset=(short)((char *)&prec->l944 - (char *)prec);
  pdbRecordType->papFldDes[1002]->size=sizeof(prec->l945);
  pdbRecordType->papFldDes[1002]->offset=(short)((char *)&prec->l945 - (char *)prec);
  pdbRecordType->papFldDes[1003]->size=sizeof(prec->l946);
  pdbRecordType->papFldDes[1003]->offset=(short)((char *)&prec->l946 - (char *)prec);
  pdbRecordType->papFldDes[1004]->size=sizeof(prec->l947);
  pdbRecordType->papFldDes[1004]->offset=(short)((char *)&prec->l947 - (char *)prec);
  pdbRecordType->papFldDes[1005]->size=sizeof(prec->l948);
  pdbRecordType->papFldDes[1005]->offset=(short)((char *)&prec->l948 - (char *)prec);
  pdbRecordType->papFldDes[1006]->size=sizeof(prec->l949);
  pdbRecordType->papFldDes[1006]->offset=(short)((char *)&prec->l949 - (char *)prec);
  pdbRecordType->papFldDes[1007]->size=sizeof(prec->l950);
  pdbRecordType->papFldDes[1007]->offset=(short)((char *)&prec->l950 - (char *)prec);
  pdbRecordType->papFldDes[1008]->size=sizeof(prec->l951);
  pdbRecordType->papFldDes[1008]->offset=(short)((char *)&prec->l951 - (char *)prec);
  pdbRecordType->papFldDes[1009]->size=sizeof(prec->l952);
  pdbRecordType->papFldDes[1009]->offset=(short)((char *)&prec->l952 - (char *)prec);
  pdbRecordType->papFldDes[1010]->size=sizeof(prec->l953);
  pdbRecordType->papFldDes[1010]->offset=(short)((char *)&prec->l953 - (char *)prec);
  pdbRecordType->papFldDes[1011]->size=sizeof(prec->l954);
  pdbRecordType->papFldDes[1011]->offset=(short)((char *)&prec->l954 - (char *)prec);
  pdbRecordType->papFldDes[1012]->size=sizeof(prec->l955);
  pdbRecordType->papFldDes[1012]->offset=(short)((char *)&prec->l955 - (char *)prec);
  pdbRecordType->papFldDes[1013]->size=sizeof(prec->l956);
  pdbRecordType->papFldDes[1013]->offset=(short)((char *)&prec->l956 - (char *)prec);
  pdbRecordType->papFldDes[1014]->size=sizeof(prec->l957);
  pdbRecordType->papFldDes[1014]->offset=(short)((char *)&prec->l957 - (char *)prec);
  pdbRecordType->papFldDes[1015]->size=sizeof(prec->l958);
  pdbRecordType->papFldDes[1015]->offset=(short)((char *)&prec->l958 - (char *)prec);
  pdbRecordType->papFldDes[1016]->size=sizeof(prec->l959);
  pdbRecordType->papFldDes[1016]->offset=(short)((char *)&prec->l959 - (char *)prec);
  pdbRecordType->papFldDes[1017]->size=sizeof(prec->l960);
  pdbRecordType->papFldDes[1017]->offset=(short)((char *)&prec->l960 - (char *)prec);
  pdbRecordType->papFldDes[1018]->size=sizeof(prec->l961);
  pdbRecordType->papFldDes[1018]->offset=(short)((char *)&prec->l961 - (char *)prec);
  pdbRecordType->papFldDes[1019]->size=sizeof(prec->l962);
  pdbRecordType->papFldDes[1019]->offset=(short)((char *)&prec->l962 - (char *)prec);
  pdbRecordType->papFldDes[1020]->size=sizeof(prec->l963);
  pdbRecordType->papFldDes[1020]->offset=(short)((char *)&prec->l963 - (char *)prec);
  pdbRecordType->papFldDes[1021]->size=sizeof(prec->l964);
  pdbRecordType->papFldDes[1021]->offset=(short)((char *)&prec->l964 - (char *)prec);
  pdbRecordType->papFldDes[1022]->size=sizeof(prec->l965);
  pdbRecordType->papFldDes[1022]->offset=(short)((char *)&prec->l965 - (char *)prec);
  pdbRecordType->papFldDes[1023]->size=sizeof(prec->l966);
  pdbRecordType->papFldDes[1023]->offset=(short)((char *)&prec->l966 - (char *)prec);
  pdbRecordType->papFldDes[1024]->size=sizeof(prec->l967);
  pdbRecordType->papFldDes[1024]->offset=(short)((char *)&prec->l967 - (char *)prec);
  pdbRecordType->papFldDes[1025]->size=sizeof(prec->l968);
  pdbRecordType->papFldDes[1025]->offset=(short)((char *)&prec->l968 - (char *)prec);
  pdbRecordType->papFldDes[1026]->size=sizeof(prec->l969);
  pdbRecordType->papFldDes[1026]->offset=(short)((char *)&prec->l969 - (char *)prec);
  pdbRecordType->papFldDes[1027]->size=sizeof(prec->l970);
  pdbRecordType->papFldDes[1027]->offset=(short)((char *)&prec->l970 - (char *)prec);
  pdbRecordType->papFldDes[1028]->size=sizeof(prec->l971);
  pdbRecordType->papFldDes[1028]->offset=(short)((char *)&prec->l971 - (char *)prec);
  pdbRecordType->papFldDes[1029]->size=sizeof(prec->l972);
  pdbRecordType->papFldDes[1029]->offset=(short)((char *)&prec->l972 - (char *)prec);
  pdbRecordType->papFldDes[1030]->size=sizeof(prec->l973);
  pdbRecordType->papFldDes[1030]->offset=(short)((char *)&prec->l973 - (char *)prec);
  pdbRecordType->papFldDes[1031]->size=sizeof(prec->l974);
  pdbRecordType->papFldDes[1031]->offset=(short)((char *)&prec->l974 - (char *)prec);
  pdbRecordType->papFldDes[1032]->size=sizeof(prec->l975);
  pdbRecordType->papFldDes[1032]->offset=(short)((char *)&prec->l975 - (char *)prec);
  pdbRecordType->papFldDes[1033]->size=sizeof(prec->l976);
  pdbRecordType->papFldDes[1033]->offset=(short)((char *)&prec->l976 - (char *)prec);
  pdbRecordType->papFldDes[1034]->size=sizeof(prec->l977);
  pdbRecordType->papFldDes[1034]->offset=(short)((char *)&prec->l977 - (char *)prec);
  pdbRecordType->papFldDes[1035]->size=sizeof(prec->l978);
  pdbRecordType->papFldDes[1035]->offset=(short)((char *)&prec->l978 - (char *)prec);
  pdbRecordType->papFldDes[1036]->size=sizeof(prec->l979);
  pdbRecordType->papFldDes[1036]->offset=(short)((char *)&prec->l979 - (char *)prec);
  pdbRecordType->papFldDes[1037]->size=sizeof(prec->l980);
  pdbRecordType->papFldDes[1037]->offset=(short)((char *)&prec->l980 - (char *)prec);
  pdbRecordType->papFldDes[1038]->size=sizeof(prec->l981);
  pdbRecordType->papFldDes[1038]->offset=(short)((char *)&prec->l981 - (char *)prec);
  pdbRecordType->papFldDes[1039]->size=sizeof(prec->l982);
  pdbRecordType->papFldDes[1039]->offset=(short)((char *)&prec->l982 - (char *)prec);
  pdbRecordType->papFldDes[1040]->size=sizeof(prec->l983);
  pdbRecordType->papFldDes[1040]->offset=(short)((char *)&prec->l983 - (char *)prec);
  pdbRecordType->papFldDes[1041]->size=sizeof(prec->l984);
  pdbRecordType->papFldDes[1041]->offset=(short)((char *)&prec->l984 - (char *)prec);
  pdbRecordType->papFldDes[1042]->size=sizeof(prec->l985);
  pdbRecordType->papFldDes[1042]->offset=(short)((char *)&prec->l985 - (char *)prec);
  pdbRecordType->papFldDes[1043]->size=sizeof(prec->l986);
  pdbRecordType->papFldDes[1043]->offset=(short)((char *)&prec->l986 - (char *)prec);
  pdbRecordType->papFldDes[1044]->size=sizeof(prec->l987);
  pdbRecordType->papFldDes[1044]->offset=(short)((char *)&prec->l987 - (char *)prec);
  pdbRecordType->papFldDes[1045]->size=sizeof(prec->l988);
  pdbRecordType->papFldDes[1045]->offset=(short)((char *)&prec->l988 - (char *)prec);
  pdbRecordType->papFldDes[1046]->size=sizeof(prec->l989);
  pdbRecordType->papFldDes[1046]->offset=(short)((char *)&prec->l989 - (char *)prec);
  pdbRecordType->papFldDes[1047]->size=sizeof(prec->l990);
  pdbRecordType->papFldDes[1047]->offset=(short)((char *)&prec->l990 - (char *)prec);
  pdbRecordType->papFldDes[1048]->size=sizeof(prec->l991);
  pdbRecordType->papFldDes[1048]->offset=(short)((char *)&prec->l991 - (char *)prec);
  pdbRecordType->papFldDes[1049]->size=sizeof(prec->l992);
  pdbRecordType->papFldDes[1049]->offset=(short)((char *)&prec->l992 - (char *)prec);
  pdbRecordType->papFldDes[1050]->size=sizeof(prec->l993);
  pdbRecordType->papFldDes[1050]->offset=(short)((char *)&prec->l993 - (char *)prec);
  pdbRecordType->papFldDes[1051]->size=sizeof(prec->l994);
  pdbRecordType->papFldDes[1051]->offset=(short)((char *)&prec->l994 - (char *)prec);
  pdbRecordType->papFldDes[1052]->size=sizeof(prec->l995);
  pdbRecordType->papFldDes[1052]->offset=(short)((char *)&prec->l995 - (char *)prec);
  pdbRecordType->papFldDes[1053]->size=sizeof(prec->l996);
  pdbRecordType->papFldDes[1053]->offset=(short)((char *)&prec->l996 - (char *)prec);
  pdbRecordType->papFldDes[1054]->size=sizeof(prec->l997);
  pdbRecordType->papFldDes[1054]->offset=(short)((char *)&prec->l997 - (char *)prec);
  pdbRecordType->papFldDes[1055]->size=sizeof(prec->l998);
  pdbRecordType->papFldDes[1055]->offset=(short)((char *)&prec->l998 - (char *)prec);
  pdbRecordType->papFldDes[1056]->size=sizeof(prec->l999);
  pdbRecordType->papFldDes[1056]->offset=(short)((char *)&prec->l999 - (char *)prec);
  pdbRecordType->papFldDes[1057]->size=sizeof(prec->l1000);
  pdbRecordType->papFldDes[1057]->offset=(short)((char *)&prec->l1000 - (char *)prec);
  pdbRecordType->papFldDes[1058]->size=sizeof(prec->l1001);
  pdbRecordType->papFldDes[1058]->offset=(short)((char *)&prec->l1001 - (char *)prec);
  pdbRecordType->papFldDes[1059]->size=sizeof(prec->l1002);
  pdbRecordType->papFldDes[1059]->offset=(short)((char *)&prec->l1002 - (char *)prec);
  pdbRecordType->papFldDes[1060]->size=sizeof(prec->l1003);
  pdbRecordType->papFldDes[1060]->offset=(short)((char *)&prec->l1003 - (char *)prec);
  pdbRecordType->papFldDes[1061]->size=sizeof(prec->l1004);
  pdbRecordType->papFldDes[1061]->offset=(short)((char *)&prec->l1004 - (char *)prec);
  pdbRecordType->papFldDes[1062]->size=sizeof(prec->l1005);
  pdbRecordType->papFldDes[1062]->offset=(short)((char *)&prec->l1005 - (char *)prec);
  pdbRecordType->papFldDes[1063]->size=sizeof(prec->l1006);
  pdbRecordType->papFldDes[1063]->offset=(short)((char *)&prec->l1006 - (char *)prec);
  pdbRecordType->papFldDes[1064]->size=sizeof(prec->l1007);
  pdbRecordType->papFldDes[1064]->offset=(short)((char *)&prec->l1007 - (char *)prec);
  pdbRecordType->papFldDes[1065]->size=sizeof(prec->l1008);
  pdbRecordType->papFldDes[1065]->offset=(short)((char *)&prec->l1008 - (char *)prec);
  pdbRecordType->papFldDes[1066]->size=sizeof(prec->l1009);
  pdbRecordType->papFldDes[1066]->offset=(short)((char *)&prec->l1009 - (char *)prec);
  pdbRecordType->papFldDes[1067]->size=sizeof(prec->l1010);
  pdbRecordType->papFldDes[1067]->offset=(short)((char *)&prec->l1010 - (char *)prec);
  pdbRecordType->papFldDes[1068]->size=sizeof(prec->l1011);
  pdbRecordType->papFldDes[1068]->offset=(short)((char *)&prec->l1011 - (char *)prec);
  pdbRecordType->papFldDes[1069]->size=sizeof(prec->l1012);
  pdbRecordType->papFldDes[1069]->offset=(short)((char *)&prec->l1012 - (char *)prec);
  pdbRecordType->papFldDes[1070]->size=sizeof(prec->l1013);
  pdbRecordType->papFldDes[1070]->offset=(short)((char *)&prec->l1013 - (char *)prec);
  pdbRecordType->papFldDes[1071]->size=sizeof(prec->l1014);
  pdbRecordType->papFldDes[1071]->offset=(short)((char *)&prec->l1014 - (char *)prec);
  pdbRecordType->papFldDes[1072]->size=sizeof(prec->l1015);
  pdbRecordType->papFldDes[1072]->offset=(short)((char *)&prec->l1015 - (char *)prec);
  pdbRecordType->papFldDes[1073]->size=sizeof(prec->l1016);
  pdbRecordType->papFldDes[1073]->offset=(short)((char *)&prec->l1016 - (char *)prec);
  pdbRecordType->papFldDes[1074]->size=sizeof(prec->l1017);
  pdbRecordType->papFldDes[1074]->offset=(short)((char *)&prec->l1017 - (char *)prec);
  pdbRecordType->papFldDes[1075]->size=sizeof(prec->l1018);
  pdbRecordType->papFldDes[1075]->offset=(short)((char *)&prec->l1018 - (char *)prec);
  pdbRecordType->papFldDes[1076]->size=sizeof(prec->l1019);
  pdbRecordType->papFldDes[1076]->offset=(short)((char *)&prec->l1019 - (char *)prec);
  pdbRecordType->papFldDes[1077]->size=sizeof(prec->l1020);
  pdbRecordType->papFldDes[1077]->offset=(short)((char *)&prec->l1020 - (char *)prec);
  pdbRecordType->papFldDes[1078]->size=sizeof(prec->l1021);
  pdbRecordType->papFldDes[1078]->offset=(short)((char *)&prec->l1021 - (char *)prec);
  pdbRecordType->papFldDes[1079]->size=sizeof(prec->l1022);
  pdbRecordType->papFldDes[1079]->offset=(short)((char *)&prec->l1022 - (char *)prec);
  pdbRecordType->papFldDes[1080]->size=sizeof(prec->l1023);
  pdbRecordType->papFldDes[1080]->offset=(short)((char *)&prec->l1023 - (char *)prec);
    pdbRecordType->rec_size = sizeof(*prec);
    return(0);
}
#endif /*GEN_SIZE_OFFSET*/
