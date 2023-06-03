#include "Character.h"
#include <math.h>
#include <iostream>

Character::Character(std::string Name = "character_name")
{
	hpMax_=50; hpMax=50; hpCur=50; mpMax_=50; lvl=1; evade_=5; block_=0; parry_=0; critChance_=5; critDmg_=180; acc_=80; spd_=1;
	vit=3; dex=3; mag=3; cha=3; lck=3;
	skillPoints=12; exp=100; EXP=100;
	finalatk=100;
	

	atk=0; atkMod=100;
	def=0; defMod=100;
	prot=0;
	trueAtk=0; 
	
	for(int i=0;i<5;i++)
	{
		skillAtkMod[i]=100;
		skillAccMod[i]=100;
		skillCritChanceMod[i]=100;
		skillTrueDmg[i]=false;
	}

	name=Name;
}

Character::~Character()
{
}

bool Character::applyDmg(Character &enemy, int skillNumber)
{
	float	tempDMG, tempTRUEDMG;
	int 	appliedDMG;
	
	this->getDmgDealt(skillNumber, tempDMG, tempTRUEDMG); //gets pure atk
	enemy.receivedDmg(tempDMG, tempTRUEDMG);			//applies def and prot
		
	appliedDMG = tempDMG + tempTRUEDMG;
	enemy.hpCur -= appliedDMG;
	
	if(appliedDMG >= 0)
		return true;
	else return false;
}

void Character::getDmgDealt(int skillNumber, float &refDMG, float &refTRUEDMG)
{
	float totalDmg, totalTrueDmg;
	
	totalDmg = atk			* atkMod/100.f * skillAtkMod[skillNumber]/100.f;
	totalTrueDmg = trueAtk	* atkMod/100.f * skillAtkMod[skillNumber]/100.f;
	
		
	/*for(int j=0;j<EQUIP_N;j++) //each loop gets the type's dmg of item bonuses
	{
		totalAtk += equip[j].Atk[i];
		totalatk *= equip[j].atk[i]/100.f;
		
		totalTrueAtk += equip[j].trueAtk[i];
		totalTrueatk *= equip[j].trueatk[i]/100.f;
	}
	*/
	
	refDMG		= totalDmg;
	refTRUEDMG	= totalTrueDmg;
}

void Character::receivedDmg(float &DMG, float &TRUEDMG)
{
	float DEF, PROT;
	
	DEF = def * defMod/100.f;
	PROT = prot/100.f;

	/*
	for(int j=0;j<EQUIP_N;j++) //each loop gets the type's def of item bonuses
	{
		totalDef += equip[j].Def;
		totaldefmod *= equip[j].def/100.f;
		
		totalProt	  += equip[j].prot/100.f;
	}
	*/
	
	DMG *= 1.f - PROT;
	DMG -= DEF;	//percentage is applied before pure defense, of course
	
	if(DMG<0)		DMG=0;			//don't want characters to heal their enemies, right?
	if(TRUEDMG<0)	TRUEDMG=0;
	
	return;
}

bool Character::levelUp()
{
	if(exp<EXP) return false;
	
	lvl++;
	exp -= EXP;
	EXP *= 1.2;
	skillPoints += 6;
	updateStatus();
	updateSkills();
	return true;
}

void Character::updateStatus()
{
	const int HP_old=hpMax, MP_old=mpMax;
	
	hpMax = ( hpMax_ + hpMod * (vit-3) ) * pow(1.1 , lvl-1); //this formula makes each level have 10% more HP and MP than the previous one
	mpMax = ( mpMax_ + mpMod * (mag-3) ) * pow(1.1 , lvl-1);
	hpCur += hpMax - HP_old;
	mpCur += mpMax - MP_old;	//character will recover hp/mp that is added    eg.  60/100 -> level up -> 70/110
	
	//EVADE
	float temp=0;						//this is a logarithm that will converge to ~102
	for(int i=0; i<dex-3; i++)			//temp added each loop:
		temp += pow( 1.02, -(i-35) );	//	2 @ 0;   1.346 @ 20;  1 @ 35;   0.74 @ 50;  0.45 @ 75;  0.28 @100;   0.038 @200;  5*10^-9 @1000;
	evade = evade_ + temp;				//total temp: 
										//  2 at 0;  34.7 at 20;  52 at 35;  64 at 50;  79.3 at 75;  88 at 100;  100 at 200;  ~102 at 1000; 
	
	//CRIT CHANCE
	temp=0;
	for(int i=0; i<dex-3; i++)
		temp += pow( 1.02, -(i-35) );
	critChance = critChance_ + temp/2;  //crit chance will weight 1/2 on dex && 1 on luck      (total crit chance will be 3/2 of evade)
	temp=0;
	for(int i=0; i<lck-3; i++)
		temp += pow( 1.02, -(i-35) );
	critChance += temp;
	
	//CRIT DAMAGE
	temp=0;
	for(int i=0; i<dex-3; i++)
		temp += pow( 1.02, -(i-35) );
	critDmg = critDmg_ * ( (temp/2) + 100 )/100;  //crit damage will depend 1/3 on dex && 2/3 on luck   (total crit dmg will be 1/1 of evade)
	temp=0;							//multiply so that it will increase in percentage of normal crit dmg modifier
	for(int i=0; i<lck-3; i++)
		temp += pow( 1.02, -(i-35) );
	critDmg *= ( (temp*2/3) + 100 )/100; //juros composto entao eh um pouco mais que a evade na real
	
	
	temp=0;
	for(int i=0; i<dex-3; i++)
		temp += pow( 1.02, -(i-35) );
	acc = acc_ + temp/2;  //     (accuracy will be 1/2 of evade (base acc is 80%, it will converge to 130%) )
	
	
	temp=0;
	for(int i=0; i<dex-3; i++)
		temp += pow( 1.01, -(i-35) );
	spd = spd_ + temp/10;  //   (speed will be 1/10 of evade (not exactly since 1.02 is 1.01 here) )
	                       //that change was made so it will increase slower at first but more constantly after 35 points allocated in dex
	                       //   ( 1.417 at 0;  0.86 at 50;  0.52 at 100; )
	
	
	//other statuses like atk[i] are class-specific and will be implemented separately
	//this mother-function will be called and then other changes will be made accordingly
}

