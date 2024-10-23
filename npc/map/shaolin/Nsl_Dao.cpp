///////////////////////////////////////////////////////////////////////////////////////////////
// 此為少林派道字輩弟子共用的cpp文件，包含有幾個與少林玩家升級有關的函數

// 少林派的輩份從上到下依次為: 渡，玄，澄，慧，道，清，（虛，明，空，圓，淨，法，……）
// 少林派的代數從上到下依次為: 35, 36, 37, 38, 39, 40, （41, 41, 41, 41, 41, 41,     ） 
// 只有拜清法比丘為師並出家之後才有輩份，否則算是俗家弟子，不排輩。
// 少林俗家弟子只能向別的玩家或清法，虛明，虛通三個npc學武功，並且不能進入少林寺內。
// 拜玩家為師不改輩份，如有玄字輩的玩家，收了一個俗家弟子，則這個俗家弟子還是俗家弟子，名字不改。

#include "stdafx.h"
#include "Nsl_Dao.h"
// 接受物品
TRetInfo accept_object ( CActiveObject *me, CActiveObject *you, CGoods *obj )
{
	TRetInfo ri;
/*	ri.bRet = FALSE;
	POSITION pos;
	// 這個人已拿過推薦信
	if (you->GetTemp ("Have_Letter").szValue == "Dao" && you->GetGoods((char *)(LPCTSTR)"道字輩推薦信")!= NULL)
		TRet_return("怎麼樣，你拿我的推薦信去拜師了嗎 ?");

	// 這個人沒拿過推薦信，且有達摩令，並且比自己晚一輩
	if (obj->lpGoods->szCName == "damoling"
		&& you->nGeneration == me->nGeneration + 1
		&& you->GetTemp ("Have_Letter").szValue != "Dao")
	{
		you->SetTemp ("Fight_Ok", "Dao");
		pos = you->GetGoods (obj);
		if (pos != NULL) you->listequip.RemoveAt (pos);
		delete obj->lpGoods;
		TRet_return("好，既然已得到方丈許可，我們就來驗證一下武功。");
	}
	// 此人有下級推薦信
	if (you->GetTemp ("Have_Letter").szValue == "Qing" && obj->lpGoods->szEName =="letter_qing")
	{
		you->SetTemp ("Apprentice_Ok", "Dao");
		pos = you->GetGoods (obj);
		if (pos != NULL) you->listequip.RemoveAt (pos);
		delete obj->lpGoods;
		TRet_return(GetSpecialName(you, 1) + "，你願意拜我為師嗎?");
	}
	//要將東西還給玩家
	pos = me->GetGoods( obj );
	if(pos != NULL)
	{
		me->listequip.RemoveAt (pos);
		you->listequip.AddTail (obj);
		ri.szRet.Format("%s將%s還給%s。", me->szCName , obj->lpGoods->szCName, you->szCName );
		you->SendMsgToAll (ri.szRet);
	}
	TRet_return("這東西對我可沒什麼用");*/
	return ri;
}

/*
接受東西( 人，物品)
{
	if (人有本級推薦信)
		你拿我的推薦信去拜師了嗎?
		return;
	if (物品==damoling
		&& 人比自己小一輩
		&& 沒拿過信)
		{
			好，既然已得到方丈許可，我們就來驗證一下武功。
			銷毀damoling
			return;
		}
	if (物品==下級推薦信)
	{
		人->settemp ( apprentice_ok );
		說: 人，你願意拜我為師嗎?
		銷毀下級推薦信;
		return;
	}
	這東西對我沒有用
	把物品還給人
}
*/

TRetInfo Do_Fight( CActiveObject *me, CActiveObject *you)
{
	TRetInfo ri;
/*	ri.bRet = FALSE;
	if (you->GetTemp ("Fight_Ok").szValue != "Dao")
		return ri;
//  if(我還在打)
	// 繼續打;
	if (me->nEff_qi *100 / me->GetMaxQi() < 50)
	{
		you->SetTemp ("Have_Letter", "Dao");
		CGoods * lpLetter = GetNormalClass("Letter_Dao");
		you->listequip.AddTail (lpLetter);
		ri.szRet.Format("%s給%s一封推薦信。", me->szCName, you->szCName );
		you->SendMsgToAll(ri.szRet);

		ri.szRet.Format("%s %s %s %d %s",SZADDGOODS,"推薦信","空",1,"封");
		you->SendMsg(ri.szRet);
	}
	if (you->nEff_qi *100 / you->GetMaxQi() < 50)
	{
		ri.szRet.Format("看來，%s還得多加練習，方能在少林諸多弟子中出人頭地！", GetSpecialName(you, 1));
		you->SendMsgToAll(ri.szRet);
		you->SendMsg(ri.szRet);
		return ri;
	}
	you->DeleteTemp("Fight_Ok");
	ri.bRet = TRUE;*/
	return ri;
}

/*
戰斗 (人)
{
	人勝
		青出於藍勝於藍，不愧是少林寺的佳弟子 ! 恭喜你了
		給推薦信
	人敗
		看來, 還得多加練習，方能在少林諸多弟子中出人頭地 
}
*/
TRetInfo Do_Apprenticre(CActiveObject *me, CActiveObject *you)
{
	TRetInfo ri;
/*	ri.bRet = FALSE;
	if(you->szFamily != "少林派")
		TRet_return(GetSpecialName(you,1) + "與本派素無來往，不知此話從何談起？");
//	if (you是俗家弟子)
//		TRet_return(GetSpecialName(who,1) + "是俗家弟子，不能在寺內學藝。");
	if (you->nGeneration <= me->nGeneration )
		TRet_return("貧僧哪里敢當！");
	if (you->nGeneration = me->nGeneration + 1 && you->szCName.Left (2)== "清")
		ri.szRet.Format ("哈哈，%s的徒弟怎麼跑我這里來了?", you->szTeacher);
	if (you->nGeneration = me->nGeneration + 2 ) 
	{
		if (you->GetTemp ("Apprentice_Ok").szValue == "Dao")
		{
			you->DeleteTemp ("Have_Letter");
			you->DeleteTemp ("Apprentice_Ok");
			ri.szRet.Format ("是%s叫你來找我的吧，哈哈哈，貧僧又得一可塑之才，真是可喜可賀！", you->szTeacher);
			you->SendMsgToAll (ri.szRet );
			you->SendMsg (ri.szRet );
			CString newname = "清" + you->szCName.Right (2);
			ri.szRet.Format ("從今以後你的法名叫做%s，恭喜你榮升為少林派清字輩弟子", newname);
		}
		else 
			TRet_return (GetSpecialName(you, 1) + "，你沒有推薦信，不能越級拜師。");
	}
	ri.bRet = TRUE;*/
	return ri;
}
/*
拜師(人)
{
	if (人->szFamily != "少林派")
	{
		人與本派素無來往，不知此話從何談起？
		return;
	}
	if (人是俗家弟子)
	{
		人是俗家弟子，不能在寺內學藝。
		return;
	}
	if (人的輩份比自己高或與自己平輩)
	{
		貧僧哪里敢當！
		return;
	}
	if (人比自己小一輩 && 人->szCName[0..1] == 自己下一輩的字)
	{
		哈哈，人->MasterName的徒弟怎麼跑我這里來了?
	}
	if (人比自己小兩輩)
	{
		if (人->gettemp(apprentice_ok))
		{
			是人-> mastername叫你來找我的吧，哈哈哈。。。
			貧僧又得一可塑之才，真是可喜可賀
			人-> szCName = ("清"，"道"，"慧") + szCName[2..3];
			從今以後你的法名叫做" + new_name + "，恭喜你榮升為少林派(清"，"道"，"慧")字輩弟子 !
			執行拜師儀式;
			return;
		}
		else
		{
			你沒有推薦信，不能越級拜師。
		}
	}
	return;
}

*/
// 清法收徒無特殊要求
