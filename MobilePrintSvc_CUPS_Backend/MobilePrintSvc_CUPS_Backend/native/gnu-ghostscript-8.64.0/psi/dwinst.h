/* Copyright (C) 2001-2006 Artifex Software, Inc.
   All Rights Reserved.
  
  This file is part of GNU ghostscript

  GNU ghostscript is free software; you can redistribute it and/or
  modify it under the terms of the version 2 of the GNU General Public
  License as published by the Free Software Foundation.

  GNU ghostscript is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  ghostscript; see the file COPYING. If not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

// $Id: dwinst.h,v 1.8 2007/09/11 15:23:54 Arabidopsis Exp $

#ifndef dwinst_INCLUDED
#  define dwinst_INCLUDED

// Definitions for Ghostscript installer

#ifndef MAXSTR
#ifdef MAX_PATH
#define MAXSTR MAX_PATH
#else
#define MAXSTR 256
#endif
#endif

class CInstall  
{
public:
	CInstall();
	virtual ~CInstall();
	void SetMessageFunction(void(*fn)(const char *));
	void AddMessage(const char *message);
	const char *GetMainDir();
	const char *GetUninstallName();
	BOOL GetPrograms(BOOL bUseCommon, char *buf, int buflen);
	BOOL Init(const char *szSourceDir, const char *szFileList);
	BOOL InstallFiles(BOOL bNoCopy, BOOL *pbQuit);
	BOOL InstallFile(char *filename, BOOL bNoCopy);
	BOOL MakeDir(const char *dirname);
	FILE * MakeTemp(char *name);

	BOOL SetAllUsers(BOOL bUseCommon);
	void SetTargetDir(const char *szTargetDir);
	void SetTargetGroup(const char *szTargetGroup);

	BOOL StartMenuBegin();
	BOOL StartMenuEnd();
	BOOL StartMenuAdd(const char *szDescription, const char *szProgram, const char *szArguments);

	BOOL UpdateRegistryBegin();
	BOOL UpdateRegistryKey(const char *product, const char *version);
	BOOL UpdateRegistryValue(const char *product, const char *version, const char *name, const char *value);
	BOOL UpdateRegistryEnd();

	BOOL WriteUninstall(const char *prog, BOOL bNoCopy);
	BOOL MakeLog(void);

	void CleanUp(void);

        void AppendFileNew(const char *filename);

private:
	BOOL m_bNoCopy;
	BOOL m_bUseCommon;
	BOOL m_bQuit;

	// Source directory
	char m_szSourceDir[MAXSTR];

	// File containing list of files to install
	char m_szFileList[MAXSTR];

	// Target directory for program and fonts.
	char m_szTargetDir[MAXSTR];

	// Target Group for shortcut
	char m_szTargetGroup[MAXSTR];

	// Directory where the Start Menu is located.
	char m_szPrograms[MAXSTR];

	// Name used for uninstall
	char m_szUninstallName[MAXSTR];

	// Main directory prefix, where log files should be written
	char m_szMainDir[MAXSTR];

	// Full directory where log files should be written
	char m_szLogDir[MAXSTR];

	// Temporary log files for uninstall
	char m_szFileNew[MAXSTR];
	char m_szRegistryNew[MAXSTR];
	char m_szRegistryOld[MAXSTR];
	char m_szShellNew[MAXSTR];
	char m_szShellOld[MAXSTR];

	// Log files
	FILE * m_fLogNew;
	FILE * m_fLogOld;


	BOOL SetRegistryValue(HKEY hkey, const char *value_name, const char *value);
	BOOL CreateShellLink(LPCSTR description, LPCSTR program, LPCSTR arguments, LPCSTR icon = NULL, int nIconIndex = 0);
	void CopyFileContents(FILE *df, FILE *sf);
	void ResetReadonly(const char *filename);

	void(*AddMessageFn)(const char *);

};


#endif /* dwinst_INCLUDED */
