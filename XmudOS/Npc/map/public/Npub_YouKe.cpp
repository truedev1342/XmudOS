// Npub_YouKe.cpp: implementation of the CNpub_YouKe class.
//
//////////////////////////////////////////////////////////////////////

#include "..\..\stdafx.h"
#include "Npub_YouKe.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpub_YouKe::CNpub_YouKe()
{
	static int number = 0;
	int age;

	number ++;
	szCName = "遊客";
	szEName.Format("youke%d",number);
	szLong = "這是路過的遊客。";
	if(random(3)==2)
		szSex = "F";
	else
		szSex = "M";
	nAttitude = NP_friendly | NP_apprentice;
	nShen = random(100)-20;
	switch(random(2))
	{
	case 0:
		age = 20 + random(40);
		
		nAge =  age;


		if(szSex[0] == 'F')
			szXFileName.Format("pmudznfn0%d",random(2)+1);
		else
			szXFileName.Format("pmudznnz0%d",random(5)+1);
		SetSkill("BaseUnarmed",	random(30));
		SetSkill("BaseDodge",	random(30));
		nDamage = 5;
		nCombat_exp =  150+age*10;
				
		nMoney += 10*( 3+age/3 ) + random(10);
		break;
	case 1:
		age = random(10);
		nAge =  14 + age * 3 ;

		if(nAge > 25)
			if(szSex[0] == 'F')
				szXFileName.Format("pmudznfn0%d",random(2)+1);
			else
				szXFileName.Format("pmudznnz0%d",random(5)+1);
		else
			if(szSex[0] == 'F')
				szXFileName.Format("pmudsnv0%d",random(5)+1);
			else
				szXFileName.Format("pmudsn0%d",random(5)+1);
			
		nCombat_exp =  500 + 5 * age;
		nMoney += 10*( 1 + age ) + random(20);
		break;
	}
}

CNpub_YouKe::~CNpub_YouKe()
{

}
