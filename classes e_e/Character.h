#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <SFML/Graphics.hpp>
//#include "Equipment.h"

class Character
{
	public:
		Character(std::string Name);
		virtual ~Character();
		
		virtual bool skill0(Character &enemy)=0;
		virtual bool skill1(Character &enemy)=0;
		virtual bool skill2(Character &enemy)=0;
		virtual bool skill3(Character &enemy)=0;
		virtual bool skill4(Character &enemy)=0;
		virtual void updateStatus();
		virtual void updateSkills()=0;
		virtual bool levelUp();
		
		
		bool applyDmg(Character &enemy, int skillNumber);
		void getDmgDealt(int skillNumber, float &refDMG, float &refTRUEDMG);
		void receivedDmg(float &DMG, float&TRUEDMG);
		
		

		int hpMax, hpCur, mpMax, mpCur, lvl, block, parry, evade, acc, critChance, critDmg, spd;
			//Status base:            
		int hpMax_, mpMax_, 			 block_,parry_,evade_,acc_,critChance_,critDmg_,spd_;
			//Status modifier:
		int hpMod,    mpMod;
		
		int atk, trueAtk, atkMod, def, defMod, prot, finalatk;
		    //prot=percentage (-x% dmg)  def=pure (-x dmg) 
		
		int skillPoints, exp, EXP;
		int vit, str, dex, mag, cha, lck;
		std::string name, className;
		int classID;
		//Equipment equip[EQUIP_N]; //0=armor  1=rHand  2=lHand  n-1=buff
		
		int skillAtkMod[5], skillAccMod[5], skillCritChanceMod[5];
		bool skillTrueDmg[5];
		std::string skillName[5];
};

#endif
