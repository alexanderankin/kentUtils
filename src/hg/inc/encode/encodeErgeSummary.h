/* encodeErgeSummary.h was originally generated by the autoSql program, which also 
 * generated encodeErgeSummary.c and encodeErgeSummary.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef ENCODEERGESUMMARY_H
#define ENCODEERGESUMMARY_H

#define ENCODEERGESUMMARY_NUM_COLS 14

struct encodeErgeSummary
/* ENCODE experimental data from dbERGEII */
    {
    struct encodeErgeSummary *next;  /* Next in singly linked list. */
    char *chrom;	/* Human chromosome */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Name of read - up to 255 characters */
    unsigned score;	/* Score from 0-1000.  1000 is best */
    char strand[2];	/* Value should be + or - */
    unsigned thickStart;	/* Start of where display should be thick (start codon) */
    unsigned thickEnd;	/* End of where display should be thick (stop codon) */
    unsigned reserved;	/* Always zero for now */
    unsigned blockCount;	/* Number of separate blocks (regions without gaps) */
    unsigned *blockSizes;	/* Comma separated list of block sizes */
    unsigned *chromStarts;	/* Start position of each block in relative to chromStart */
    char *Id;	/* dbERGEII Id */
    char *color;	/* RGB color values */
    };

struct encodeErgeSummary *encodeErgeSummaryLoad(char **row);
/* Load a encodeErgeSummary from row fetched with select * from encodeErgeSummary
 * from database.  Dispose of this with encodeErgeSummaryFree(). */

struct encodeErgeSummary *encodeErgeSummaryLoadAll(char *fileName);
/* Load all encodeErgeSummary from whitespace-separated file.
 * Dispose of this with encodeErgeSummaryFreeList(). */

struct encodeErgeSummary *encodeErgeSummaryLoadAllByChar(char *fileName, char chopper);
/* Load all encodeErgeSummary from chopper separated file.
 * Dispose of this with encodeErgeSummaryFreeList(). */

#define encodeErgeSummaryLoadAllByTab(a) encodeErgeSummaryLoadAllByChar(a, '\t');
/* Load all encodeErgeSummary from tab separated file.
 * Dispose of this with encodeErgeSummaryFreeList(). */

struct encodeErgeSummary *encodeErgeSummaryCommaIn(char **pS, struct encodeErgeSummary *ret);
/* Create a encodeErgeSummary out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new encodeErgeSummary */

void encodeErgeSummaryFree(struct encodeErgeSummary **pEl);
/* Free a single dynamically allocated encodeErgeSummary such as created
 * with encodeErgeSummaryLoad(). */

void encodeErgeSummaryFreeList(struct encodeErgeSummary **pList);
/* Free a list of dynamically allocated encodeErgeSummary's */

void encodeErgeSummaryOutput(struct encodeErgeSummary *el, FILE *f, char sep, char lastSep);
/* Print out encodeErgeSummary.  Separate fields with sep. Follow last field with lastSep. */

#define encodeErgeSummaryTabOut(el,f) encodeErgeSummaryOutput(el,f,'\t','\n');
/* Print out encodeErgeSummary as a line in a tab-separated file. */

#define encodeErgeSummaryCommaOut(el,f) encodeErgeSummaryOutput(el,f,',',',');
/* Print out encodeErgeSummary as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* ENCODEERGESUMMARY_H */
