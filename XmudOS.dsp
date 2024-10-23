# Microsoft Developer Studio Project File - Name="XmudOS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XmudOS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XmudOS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XmudOS.mak" CFG="XmudOS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XmudOS - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XmudOS - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/XMudOS", MEAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XmudOS - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /GR /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 lib\Goods.lib lib\Npc.lib lib\Skill.lib lib\map.lib /nologo /subsystem:windows /incremental:yes /machine:I386 /out:"..\exe\XmudOS_Release.exe"
# SUBTRACT LINK32 /debug /nodefaultlib

!ELSEIF  "$(CFG)" == "XmudOS - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x404 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 lib\goods.lib lib\npc.lib lib\map.lib lib\skill.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"nafxcw.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"mfcs42.lib" /nodefaultlib:"mfc42.lib" /out:"..\exe\XmudOS_debug.exe"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "XmudOS - Win32 Release"
# Name "XmudOS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ActiveObject.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdApprentice.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdAsk.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdChangeMap.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdChannelTalk.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdCreateNewPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdDaZuoAndTuNa.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdDrinkAndEat.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdEmote.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdGiveDropPick.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdKillProc.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdLearn.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdOffLine.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdPlayerLogon.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdPlayerLogonGetData.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdPractice.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdUserLogon.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdWieldAndUnW.cpp
# End Source File
# Begin Source File

SOURCE=.\combat.cpp
# End Source File
# Begin Source File

SOURCE=.\commandcheck.cpp
# End Source File
# Begin Source File

SOURCE=.\Condition.cpp
# End Source File
# Begin Source File

SOURCE=.\Fight.cpp
# End Source File
# Begin Source File

SOURCE=.\hash.cpp
# End Source File
# Begin Source File

SOURCE=.\HeartBeat.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadAllNeedFill.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadGameFile.cpp
# End Source File
# Begin Source File

SOURCE=.\MainWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\npc\map\dainty\N_BankMaster.cpp
# End Source File
# Begin Source File

SOURCE=.\npc\map\guanhua\N_EventNpc.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialActEnd.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ThreadPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\XmudOS.cpp
# End Source File
# Begin Source File

SOURCE=.\XmudOS.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ActiveObject.h
# End Source File
# Begin Source File

SOURCE=.\CmdEmote.h
# End Source File
# Begin Source File

SOURCE=.\CmdPlayerLogon.h
# End Source File
# Begin Source File

SOURCE=.\CommandCheck.h
# End Source File
# Begin Source File

SOURCE=.\Common.h
# End Source File
# Begin Source File

SOURCE=.\Condition.h
# End Source File
# Begin Source File

SOURCE=.\Config.h
# End Source File
# Begin Source File

SOURCE=.\Fight.h
# End Source File
# Begin Source File

SOURCE=.\hash.h
# End Source File
# Begin Source File

SOURCE=.\LoadAllNeedFill.h
# End Source File
# Begin Source File

SOURCE=.\MainWnd.h
# End Source File
# Begin Source File

SOURCE=.\Player.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShowMsg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\XmudOS.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\xmudos\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\XmudOS.ico
# End Source File
# Begin Source File

SOURCE=.\res\XmudOS.rc2
# End Source File
# End Group
# Begin Group "wgs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\wgs\Common.cpp

!IF  "$(CFG)" == "XmudOS - Win32 Release"

!ELSEIF  "$(CFG)" == "XmudOS - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\wgs\Common.h

!IF  "$(CFG)" == "XmudOS - Win32 Release"

!ELSEIF  "$(CFG)" == "XmudOS - Win32 Debug"

# PROP Intermediate_Dir "Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\wgs\DS_API.cpp
# End Source File
# Begin Source File

SOURCE=.\wgs\DS_API.h
# End Source File
# Begin Source File

SOURCE=.\wgs\StreamSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\wgs\StreamSocket.h
# End Source File
# Begin Source File

SOURCE=.\wgs\Wsa_xtra.h
# End Source File
# End Group
# Begin Group "GameDate"

# PROP Default_Filter ""
# End Group
# End Target
# End Project
