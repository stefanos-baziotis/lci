/* Declarations for decllist.c

	Copyright (C) 2004-8 Kostas Chatzikokolakis
	This file is part of LCI

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details. */

#ifndef DECLLIST_H
#define DECLLIST_H

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include "grammar.h"


typedef struct tag_idlist {
	char id[50];
	struct tag_idlist *next;
} IDLIST;

typedef struct tag_decl {
	const char *id;
	TERM *term;
	struct tag_decl *next;
	IDLIST aliases;

	//for DFS
	int flag;
	struct tag_decl *prev;
} DECL;

typedef struct tag_oper{ 
	const char *id;
	int preced;
	ASS_TYPE assoc;
	struct tag_oper *next;
} OPER;

typedef struct {
	DECL *start;
	DECL *end;
	int size;
} CYCLE;


void termAddDecl(const char *id, TERM *term);
DECL *getDecl(const char *id);
TERM *termFromDecl(const char *id);

void buildAliasList(DECL *d);
int searchAliasList(IDLIST *list, const char *id);
void findAliases(TERM *t, IDLIST *list);

int findCycle();
CYCLE dfs(DECL *curNode);
int getCycleSize(DECL *start, DECL *end);
void removeCycle(CYCLE c);

TERM *getIndexTerm(int varno, int n, char *tuple);
void printDeclList(const char *id);

OPER *getOper(const char *id);
void addOper(const char *id, int preced, ASS_TYPE assoc);


#endif


