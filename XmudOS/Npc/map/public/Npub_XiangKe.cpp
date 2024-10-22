
#include "..\..\stdafx.h"
#include "Npub_XiangKe.h"

CNpub_XiangKe::CNpub_XiangKe()
{
	static int number = 0;
	int age;

	number ++;
	szCName = "¶i­»«È";
	szEName.Format("jinxiangke%d",number);
	if(random(3)==2)
		szSex = "F";
	else
		szSex = "M";

	nAttitude = NP_friendly | NP_apprentice;
	nShen = 100+random(100);
	switch(random(2))
	{
	case 0:
		age = 20 + random(40);
		
		nAge =  age;


		if(szSex[0] == 'F')
			szXFileName.Format("pmudznfn0%d",random(2)+1);
		else
			szXFileName.Format("pmudznnz0%d",random(5)+1);
		SetSkill("BaseUnarmed",	20);
		SetSkill("BaseDodge",	20);
		nDamage = 5;
		nCombat_exp =  150+age*10;
				
		nMoney += 10*( 3+age/3 );
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
		nMoney += 10*( 1 + age/2 );
		break;
	}
}

CNpub_XiangKe::~CNpub_XiangKe()
{

}
