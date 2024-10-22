#ifndef __NSL_DAO_H__
#define __NSL_DAO_H__

#include "..\..\Npc.h"
#include "..\..\..\config.h"

TRetInfo accept_object ( CActiveObject *me, CActiveObject *you, CGoods *obj );
TRetInfo Do_Fight( CActiveObject *me, CActiveObject *you);
TRetInfo Do_Apprenticre(CActiveObject *me, CActiveObject *you);
#endif //__NSL_DAO_H__