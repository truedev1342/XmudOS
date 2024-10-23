# Microsoft Developer Studio Project File - Name="Npc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Npc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Npc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Npc.mak" CFG="Npc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Npc - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Npc - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Npc", KHAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Npc - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\Npc.lib"

!ELSEIF  "$(CFG)" == "Npc - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x404 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\Npc.lib"

!ENDIF 

# Begin Target

# Name "Npc - Win32 Release"
# Name "Npc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\map\guanhua\CEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\InitAllNpc.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_BankMaster.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_BiaoTou.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_ChinYunWai.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_Disciple.cpp
# End Source File
# Begin Source File

SOURCE=.\map\guanhua\N_EventNpc.cpp
# End Source File
# Begin Source File

SOURCE=.\map\waei\N_Girl.cpp
# End Source File
# Begin Source File

SOURCE=.\map\waei\N_OldWoman.cpp
# End Source File
# Begin Source File

SOURCE=.\map\waei\N_OldWoman2.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_PawnMaster.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_Runner.cpp
# End Source File
# Begin Source File

SOURCE=.\map\waei\N_Seller.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_Smith.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_WeaponSeller.cpp
# End Source File
# Begin Source File

SOURCE=.\map\waei\N_XLiumang.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_YunBing.cpp
# End Source File
# Begin Source File

SOURCE=.\map\emei\Nem_XiaoNiGu.cpp
# End Source File
# Begin Source File

SOURCE=.\map\emei\Nem_YiHe.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Nem_YiLin.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Ngb_Dizi.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Nhs_ChinZuYang.cpp
# End Source File
# Begin Source File

SOURCE=.\map\huashan\Nhs_ShiJie.cpp
# End Source File
# Begin Source File

SOURCE=.\Npc.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_Bing.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_Boy.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_Child.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_DaoKe.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_Girl.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_JiaDing.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_JianKe.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_LiuMang.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_LiuMangTou.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_TiaoFu.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_TuFei.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_TuFeitou.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_WuJiang.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_XiangKe.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_XiaoEr.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_YaYi.cpp
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_YouKe.cpp
# End Source File
# Begin Source File

SOURCE=.\map\shaolin\Nsl_Dao.cpp
# End Source File
# Begin Source File

SOURCE=.\map\shaolin\Nsl_DaoChen.cpp
# End Source File
# Begin Source File

SOURCE=.\map\shaolin\Nsl_Daosheng.cpp
# End Source File
# Begin Source File

SOURCE=.\map\shaolin\Nsl_DaoXiang2.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Nsl_KongMin.cpp
# End Source File
# Begin Source File

SOURCE=.\map\shaolin\Nsl_SaMi.cpp
# End Source File
# Begin Source File

SOURCE=.\map\wudang\Nwd_DaoTong.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Nwd_WangKangYu.cpp
# End Source File
# Begin Source File

SOURCE=.\map\wudang\Nwd_XiaoCui.cpp
# End Source File
# Begin Source File

SOURCE=.\map\xingxiu\Nxx_Dizi.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Nxx_WeaponMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\map\yangzhou\Nyz_AQingSao.cpp
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Nzm_DiziW.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\map\guanhua\CEvent.h
# End Source File
# Begin Source File

SOURCE=.\map\guanhua\CEventCommon.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_BankMaster.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_BiaoTou.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_ChinYunWai.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_Disciple.h
# End Source File
# Begin Source File

SOURCE=.\map\guanhua\N_EventNpc.h
# End Source File
# Begin Source File

SOURCE=.\map\waei\N_Girl.h
# End Source File
# Begin Source File

SOURCE=.\map\waei\N_Host.h
# End Source File
# Begin Source File

SOURCE=.\map\waei\N_OldWoman.h
# End Source File
# Begin Source File

SOURCE=.\map\waei\N_OldWoman2.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_PawnMaster.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_Runner.h
# End Source File
# Begin Source File

SOURCE=.\map\waei\N_Seller.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_Smith.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_WeaponSeller.h
# End Source File
# Begin Source File

SOURCE=.\map\waei\N_XLiumang.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\N_YunBing.h
# End Source File
# Begin Source File

SOURCE=.\map\emei\Nem_XiaoNiGu.h
# End Source File
# Begin Source File

SOURCE=.\map\emei\Nem_YiHe.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Nem_YiLin.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Ngb_Dizi.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Nhs_ChinZuYang.h
# End Source File
# Begin Source File

SOURCE=.\map\huashan\Nhs_ShiJie.h
# End Source File
# Begin Source File

SOURCE=.\Npc.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_Bing.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_Boy.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_Child.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_DaoKe.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_Girl.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_JiaDing.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_JianKe.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_LiuMang.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_LiuMangTou.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_TiaoFu.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_TuFei.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_TuFeitou.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_WuJiang.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_XiangKe.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_XiaoEr.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_YaYi.h
# End Source File
# Begin Source File

SOURCE=.\map\public\Npub_YouKe.h
# End Source File
# Begin Source File

SOURCE=.\map\shaolin\Nsl_Dao.h
# End Source File
# Begin Source File

SOURCE=.\map\shaolin\Nsl_DaoChen.h
# End Source File
# Begin Source File

SOURCE=.\map\shaolin\Nsl_Daosheng.h
# End Source File
# Begin Source File

SOURCE=.\map\shaolin\Nsl_DaoXiang2.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Nsl_KongMin.h
# End Source File
# Begin Source File

SOURCE=.\map\shaolin\Nsl_SaMi.h
# End Source File
# Begin Source File

SOURCE=.\map\wudang\Nwd_DaoTong.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Nwd_WangKangYu.h
# End Source File
# Begin Source File

SOURCE=.\map\wudang\Nwd_XiaoCui.h
# End Source File
# Begin Source File

SOURCE=.\map\xingxiu\Nxx_Dizi.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Nxx_WeaponMgr.h
# End Source File
# Begin Source File

SOURCE=.\map\yangzhou\Nyz_AQingSao.h
# End Source File
# Begin Source File

SOURCE=.\map\dainty\Nzm_DiziW.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# End Target
# End Project
