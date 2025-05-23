/*
 * Copyright (C) 1997-2001 Id Software, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
 * USA.
 *
 * =======================================================================
 *
 * The header file for the generic part of the menu system
 *
 * =======================================================================
 */

#ifndef CL_MENU_QMENU_H
#define CL_MENU_QMENU_H

#define RCOLUMN_OFFSET  16
#define LCOLUMN_OFFSET -16

#define MAXMENUITEMS 64

#define MTYPE_SLIDER        0
#define MTYPE_LIST          1
#define MTYPE_ACTION        2
#define MTYPE_SPINCONTROL   3
#define MTYPE_SEPARATOR     4
#define MTYPE_FIELD         5
#define MTYPE_BITMAP        6

#define QMF_LEFT_JUSTIFY        0x00000001
#define QMF_GRAYED              0x00000002
#define QMF_NUMBERSONLY         0x00000004
#define QMF_HIGHLIGHT_IF_FOCUS  0x00000008
#define QMF_INACTIVE            0x00000010

enum {
	KEYS_ALL	= 0,
	KEYS_KEYBOARD_MOUSE,
	KEYS_CONTROLLER,
	KEYS_CONTROLLER_ALT
};

typedef struct _tag_menuframework
{
	int x, y;
	int cursor;

	int nitems;
	void *items[64];

	const char *statusbar;

	void (*draw)(void);
	const char *(*key)(int k);
	void (*cursordraw)(struct _tag_menuframework *m);
} menuframework_s;

typedef struct
{
	int type;
	const char *name;
	int x, y;
	menuframework_s *parent;
	int cursor_offset;
	int localdata[4];
	unsigned flags;

	const char *statusbar;

	void (*callback)(void *self);
	void (*statusbarfunc)(void *self);
	void (*ownerdraw)(void *self);
	void (*cursordraw)(void *self);
} menucommon_s;

typedef struct
{
	menucommon_s    generic;
	char *          focuspic;
	char *          errorpic;
	char *          alttext;
	int             width;
	int             height;
} menubitmap_s;

typedef struct
{
	menucommon_s generic;

	char buffer[80];
	int cursor;
	int length;
	int visible_length;
} menufield_s;

typedef struct
{
	menucommon_s generic;

	char *	cvar;
	float	minvalue;
	float	maxvalue;
	float	slidestep;
	char *	printformat;
	qboolean	abs;
} menuslider_s;

typedef struct
{
	menucommon_s generic;

	int curvalue;

	const char **itemnames;
} menulist_s;

typedef struct
{
	menucommon_s generic;
} menuaction_s;

typedef struct
{
	menucommon_s generic;
} menuseparator_s;

void M_PushMenu(menuframework_s* menu);

void Field_ResetCursor(menuframework_s *m);
qboolean Field_Key(menufield_s *field, int key);

void Menu_AddItem(menuframework_s *menu, void *item);
void Menu_AdjustCursor(menuframework_s *menu, int dir);
void Menu_Center(menuframework_s *menu);
void Menu_Draw(menuframework_s *menu);
void *Menu_ItemAtCursor(menuframework_s *m);
qboolean Menu_SelectItem(menuframework_s *s);
void Menu_SetStatusBar(menuframework_s *s, const char *string);
void Menu_SlideItem(menuframework_s *s, int dir);

void Menu_DrawString(int, int, const char *);
void Menu_DrawStringDark(int, int, const char *);
void Menu_DrawStringR2L(int, int, const char *);
void Menu_DrawStringR2LDark(int, int, const char *);

float ClampCvar(float min, float max, float value);

#endif
