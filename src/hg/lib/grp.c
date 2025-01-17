/* grp.c was originally generated by the autoSql program, which also 
 * generated grp.h and grp.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "grp.h"


void grpStaticLoad(char **row, struct grp *ret)
/* Load a row from grp table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->name = row[0];
ret->label = row[1];
ret->priority = atof(row[2]);
ret->defaultIsClosed = row[3] ? TRUE : FALSE;
}

static struct grp *grpLoad(char **row, int fieldCount)
/* Load a grp from row fetched with select * from grp
 * from database.  Dispose of this with grpFree(). */
{
struct grp *ret;

AllocVar(ret);
ret->name = cloneString(row[0]);
ret->label = cloneString(row[1]);
ret->priority = atof(row[2]);
// We tolerate installations where grp table does not have a defaultIsClosed field.
if(fieldCount >= 4)
    ret->defaultIsClosed = (isNotEmpty(row[3]) && *row[3] == '1') ? TRUE : FALSE;
else
    ret->defaultIsClosed = FALSE;
return ret;
}

struct grp *grpLoadAll(char *fileName) 
/* Load all grp from a tab-separated file.
 * Dispose of this with grpFreeList(). */
{
struct grp *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];
row[3] = NULL; // tolerate missing optional defaultIsClosed

while (lineFileRow(lf, row))
    {
    el = grpLoad(row, ArraySize(row));
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct grp *grpCommaIn(char **pS, struct grp *ret)
/* Create a grp out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new grp */
{
char *s = *pS;
int count = countChars(s, ',');

if (ret == NULL)
    AllocVar(ret);
ret->name = sqlStringComma(&s);
ret->label = sqlStringComma(&s);
ret->priority = sqlFloatComma(&s);
if(count > 3)
    ret->defaultIsClosed = sqlFloatComma(&s) ? TRUE : FALSE;
else
    ret->defaultIsClosed = FALSE;
*pS = s;
return ret;
}

struct grp *grpLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all grp from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with grpFreeList(). */
{
struct grp *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = grpLoad(row, sqlCountColumns(sr));
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void grpFree(struct grp **pEl)
/* Free a single dynamically allocated grp such as created
 * with grpLoad(). */
{
struct grp *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->label);
freez(pEl);
}

void grpFreeList(struct grp **pList)
/* Free a list of dynamically allocated grp's */
{
struct grp *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    grpFree(&el);
    }
*pList = NULL;
}

void grpOutput(struct grp *el, FILE *f, char sep, char lastSep) 
/* Print out grp.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->label);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%f", el->priority);
fputc(sep,f);
fprintf(f, "%d", el->defaultIsClosed);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

int grpCmpPriority(const void *va, const void *vb)
/* Compare to sort based on priority. */
{
const struct grp *a = *((struct grp **)va);
const struct grp *b = *((struct grp **)vb);
double dif = a->priority - b->priority;
if (dif < 0) return -1;
if (dif > 0) return 1;
return 0;
}

int grpCmpName(const void *va, const void *vb)
/* Compare to sort based on name. */
{
const struct grp *a = *((struct grp **)va);
const struct grp *b = *((struct grp **)vb);
return strcmp(a->name, b->name);
}

void replaceOrAdd(struct grp **pList, struct grp *newone)
/* Add the grp to the list no matter what.  Replace the grp
 * one the list with the new grp if their names match. */
{
struct grp *newList = NULL;
boolean replaced = FALSE;
while (*pList != NULL)
    {
    struct grp *oldone = slPopHead(pList);
    if (sameString(oldone->name, newone->name))
	{
	grpFree(&oldone);
	slAddHead(&newList, newone);
	replaced = TRUE;
	newList = slCat(newList, *pList);
	break;
	}
    else 
	slAddHead(&newList, oldone);
    }
if (!replaced)
    slAddHead(&newList, newone);
*pList = newList;
}

void grpSuperimpose(struct grp **listA, struct grp **listB)
/* Replace all the grps in listA with the same names of those in
 * listB.  Ones in B that aren't the same get put in A too.  
 * The function returns with the new list A, and the empty list
 * B. */
{
while (*listB != NULL)
    {
    struct grp *newone = slPopHead(listB);
    replaceOrAdd(listA, newone);
    }
}
