/************************************
 * nvic.c							              *								
 * Created on: Mar 14, 2020			    *
 *  Author: Esraa Awad				      *
 * *********************************/
#ifndef NVIC_H
#define NVIC_H



/**** Configuration of numbers of sub group bits for stm23***
 * options:													                        *
 *			1-NVIC_PRIGROUP								                      *
 * 			2-NVIC_NonSubPriority							                  *
 * 			3-NVIC_OneSubthreeGroup							                *
 * 			4-NVIC_TwoSubTwoGroup							                  *
 * 			5-NVIC_ThreeSubOneGroup							                *
 * 			6-NVIC_NonGroupPriority							                *
 *															                            *
 ************************************************************/

#define 	NVIC_PRIGROUP				NVIC_TwoSubTwoGroup

/******************************** Interrupt request numbers ******************/
#define NVIC_IRQ0		  0U
#define NVIC_IRQ1		  1U
#define NVIC_IRQ2		  2U
#define NVIC_IRQ3		  3U
#define NVIC_IRQ4		  4U
#define NVIC_IRQ5		  5U
#define NVIC_IRQ6		  6U
#define NVIC_IRQ7		  7U
#define NVIC_IRQ8		  8U
#define NVIC_IRQ9		  9U
#define NVIC_IRQ10		10U
#define NVIC_IRQ11		11U
#define NVIC_IRQ12		12U
#define NVIC_IRQ13		13U
#define NVIC_IRQ14		14U
#define NVIC_IRQ15		15U
#define NVIC_IRQ16		16U
#define NVIC_IRQ17		17U
#define NVIC_IRQ18		18U
#define NVIC_IRQ19		19U
#define NVIC_IRQ20		20U
#define NVIC_IRQ21		21U
#define NVIC_IRQ22		22U
#define NVIC_IRQ23		23U
#define NVIC_IRQ24		24U
#define NVIC_IRQ25		25U
#define NVIC_IRQ26		26U
#define NVIC_IRQ27		27U
#define NVIC_IRQ28		28U
#define NVIC_IRQ29		29U
#define NVIC_IRQ30		30U
#define NVIC_IRQ31		31U
#define NVIC_IRQ32		32U
#define NVIC_IRQ33		33U
#define NVIC_IRQ34		34U
#define NVIC_IRQ35		35U
#define NVIC_IRQ36		36U
#define NVIC_IRQ37		37U
#define NVIC_IRQ38		38U
#define NVIC_IRQ39		39U
#define NVIC_IRQ40		40U
#define NVIC_IRQ41		41U
#define NVIC_IRQ42		42U
#define NVIC_IRQ43		43U
#define NVIC_IRQ44		44U
#define NVIC_IRQ45		45U
#define NVIC_IRQ46		46U
#define NVIC_IRQ47		47U
#define NVIC_IRQ48		48U
#define NVIC_IRQ49		49U
#define NVIC_IRQ50		50U
#define NVIC_IRQ51		51U
#define NVIC_IRQ52		52U
#define NVIC_IRQ53		53U
#define NVIC_IRQ54		54U
#define NVIC_IRQ55		55U
#define NVIC_IRQ56		56U
#define NVIC_IRQ57		57U
#define NVIC_IRQ58		58U
#define NVIC_IRQ59		59U
#define NVIC_IRQ60		60U
#define NVIC_IRQ61		61U
#define NVIC_IRQ62		62U
#define NVIC_IRQ63		63U
#define NVIC_IRQ64		64U
#define NVIC_IRQ65		65U
#define NVIC_IRQ66		66U
#define NVIC_IRQ67		67U
#define NVIC_IRQ68		68U
#define NVIC_IRQ69		69U
#define NVIC_IRQ70		70U
#define NVIC_IRQ71		71U
#define NVIC_IRQ72		72U
#define NVIC_IRQ73		73U
#define NVIC_IRQ74		74U
#define NVIC_IRQ75		75U
#define NVIC_IRQ76		76U
#define NVIC_IRQ77		77U
#define NVIC_IRQ78		78U
#define NVIC_IRQ79		79U
#define NVIC_IRQ80		80U
#define NVIC_IRQ81		81U
#define NVIC_IRQ82		82U
#define NVIC_IRQ83		83U
#define NVIC_IRQ84		84U
#define NVIC_IRQ85		85U
#define NVIC_IRQ86		86U
#define NVIC_IRQ87		87U
#define NVIC_IRQ88		88U
#define NVIC_IRQ89		89U
#define NVIC_IRQ90		90U
#define NVIC_IRQ91		91U
#define NVIC_IRQ92		92U
#define NVIC_IRQ93		93U
#define NVIC_IRQ94		94U
#define NVIC_IRQ95		95U
#define NVIC_IRQ96		96U
#define NVIC_IRQ97		97U
#define NVIC_IRQ98		98U
#define NVIC_IRQ99		99U
#define NVIC_IRQ100		100U
#define NVIC_IRQ101		101U
#define NVIC_IRQ102		102U
#define NVIC_IRQ103		103U
#define NVIC_IRQ104		104U
#define NVIC_IRQ105		105U
#define NVIC_IRQ106		106U
#define NVIC_IRQ107		107U
#define NVIC_IRQ108	  108U
#define NVIC_IRQ109		109U
#define NVIC_IRQ110		110U
#define NVIC_IRQ111		111U
#define NVIC_IRQ112		112U
#define NVIC_IRQ113		113U
#define NVIC_IRQ114		114U
#define NVIC_IRQ115		115U
#define NVIC_IRQ116		116U
#define NVIC_IRQ117		117U
#define NVIC_IRQ118		118U
#define NVIC_IRQ119		119U
#define NVIC_IRQ120		120U
#define NVIC_IRQ121		121U
#define NVIC_IRQ022		122U
#define NVIC_IRQ123		123U
#define NVIC_IRQ124		124U
#define NVIC_IRQ125		125U
#define NVIC_IRQ126		126U
#define NVIC_IRQ127		127U
#define NVIC_IRQ128		128U
#define NVIC_IRQ129		129U
#define NVIC_IRQ130		130U
#define NVIC_IRQ131		131U
#define NVIC_IRQ132		132U
#define NVIC_IRQ133		133U
#define NVIC_IRQ134		134U
#define NVIC_IRQ135		135U
#define NVIC_IRQ136		136U
#define NVIC_IRQ137		137U
#define NVIC_IRQ138		138U
#define NVIC_IRQ139		139U
#define NVIC_IRQ140		140U
#define NVIC_IRQ141		141U
#define NVIC_IRQ142		142U
#define NVIC_IRQ143		143U
#define NVIC_IRQ144		144U
#define NVIC_IRQ145		145U
#define NVIC_IRQ146		146U
#define NVIC_IRQ147		147U
#define NVIC_IRQ148		148U
#define NVIC_IRQ149		149U
#define NVIC_IRQ150		150U
#define NVIC_IRQ151		151U
#define NVIC_IRQ152		152U
#define NVIC_IRQ153		153U
#define NVIC_IRQ154		154U
#define NVIC_IRQ155		155U
#define NVIC_IRQ156		156U
#define NVIC_IRQ157		157U
#define NVIC_IRQ158		158U
#define NVIC_IRQ159		159U
#define NVIC_IRQ160		160U
#define NVIC_IRQ161		161U
#define NVIC_IRQ162		162U
#define NVIC_IRQ163		163U
#define NVIC_IRQ164		164U
#define NVIC_IRQ165		165U
#define NVIC_IRQ166		166U
#define NVIC_IRQ167		167U
#define NVIC_IRQ168		168U
#define NVIC_IRQ169		169U
#define NVIC_IRQ170		170U
#define NVIC_IRQ171		171U
#define NVIC_IRQ172		172U
#define NVIC_IRQ173		173U
#define NVIC_IRQ174		174U
#define NVIC_IRQ175		175U
#define NVIC_IRQ176		176U
#define NVIC_IRQ177		177U
#define NVIC_IRQ178		178U
#define NVIC_IRQ179		179U
#define NVIC_IRQ180		180U
#define NVIC_IRQ181		181U
#define NVIC_IRQ182		182U
#define NVIC_IRQ183		183U
#define NVIC_IRQ184		184U
#define NVIC_IRQ185		185U
#define NVIC_IRQ186		186U
#define NVIC_IRQ187		187U
#define NVIC_IRQ188		188U
#define NVIC_IRQ189		189U
#define NVIC_IRQ190		190U
#define NVIC_IRQ191		191U
#define NVIC_IRQ192		192U
#define NVIC_IRQ193		193U
#define NVIC_IRQ194		194U
#define NVIC_IRQ195		195U
#define NVIC_IRQ196		196U
#define NVIC_IRQ197		197U
#define NVIC_IRQ198		198U
#define NVIC_IRQ199		199U
#define NVIC_IRQ200		200U
#define NVIC_IRQ201		201U
#define NVIC_IRQ202		202U
#define NVIC_IRQ203		203U
#define NVIC_IRQ204		204U
#define NVIC_IRQ205		205U
#define NVIC_IRQ206		206U
#define NVIC_IRQ207		207U
#define NVIC_IRQ208		208U
#define NVIC_IRQ209		209U
#define NVIC_IRQ210		210U
#define NVIC_IRQ211		211U
#define NVIC_IRQ212		212U
#define NVIC_IRQ213		213U
#define NVIC_IRQ214		214U
#define NVIC_IRQ215		215U
#define NVIC_IRQ216		216U
#define NVIC_IRQ217		217U
#define NVIC_IRQ218		218U
#define NVIC_IRQ219		219U
#define NVIC_IRQ220		220U
#define NVIC_IRQ221		221U
#define NVIC_IRQ222		222U
#define NVIC_IRQ223		223U
#define NVIC_IRQ224		224U
#define NVIC_IRQ225		225U
#define NVIC_IRQ226		224U
#define NVIC_IRQ227		227U
#define NVIC_IRQ228		228U
#define NVIC_IRQ229		229U
#define NVIC_IRQ230		230U
#define NVIC_IRQ231		231U
#define NVIC_IRQ232		232U
#define NVIC_IRQ233		233U
#define NVIC_IRQ234		234U
#define NVIC_IRQ235		235U
#define NVIC_IRQ236		236U
#define NVIC_IRQ237		237U
#define NVIC_IRQ238		238U
#define NVIC_IRQ239		239U
#define NVIC_IRQ240		240U










/******************************* FUNCTIONS PROTOTYPES **************************/


/* Description: this API shall initialize Interrupt by set the Bits number of priority sub group Bits and premation bits
 * Input: void
 * Output: void */
void NVIC_voidInitPriority (void);




/*Description : This API shall Enable interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: Error_s  */
ERROR_STATUS NVIC_u8EnableIRQ (u8 Copy_u8IntReqNum);



/*Description : This API shall Disable interrupt
 * Input: Interrupt request number NVIC_IRQx
 * output: Error_s  */
ERROR_STATUS NVIC_u8DisbaleIRQ (u8 Copy_u8IntReqNum);










/*Description : This API clear pending of interrupt request number
 * Input: Interrupt request number NVIC_IRQx
 * output: u8 ERROR STATUS*/

ERROR_STATUS NVIC_u8ClearPending (u8 Copy_u8IntReqNum);





/**********************************************************************************************

 * Function to Disable IRQ Interrupts ( Disable all exception except NMI and hard fault)

 * return Type :- void

 * Input Argument :- void

 *************************************************************************************************/

void NVIC_DisableAllInterrupt(void);



/**********************************************************************************************

 * Function to Enable IRQ Interrupts.

 * return Type :- void

 * Input Argument :- void

 *************************************************************************************************/

void NVIC_EnableAllInterrupt(void);



/**********************************************************************************************

 * Function to Disable all fault exceptions.

 * return Type :- void

 * Input Argument :- void

 *************************************************************************************************/

void NVIC_DisableAllFaults(void);

/* System reset*/
 void NVIC_ResetSystem(void);

#endif
