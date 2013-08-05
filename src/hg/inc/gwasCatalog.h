/* gwasCatalog.h was originally generated by the autoSql program, which also 
 * generated gwasCatalog.c and gwasCatalog.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef GWASCATALOG_H
#define GWASCATALOG_H

#define GWASCATALOG_NUM_COLS 22

enum gwasCatalogCnv
    {
    gwasCatalogY = 0,
    gwasCatalogN = 1,
    };
struct gwasCatalog
/* NHGRI's collection of Genome-Wide Association Studies SNPs */
    {
    struct gwasCatalog *next;  /* Next in singly linked list. */
    char *chrom;	/* Reference sequence chromosome or scaffold */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* ID of SNP associated with trait */
    unsigned pubMedID;	/* PubMed ID of publication of the study */
    char *author;	/* First author of publication */
    char *pubDate;	/* Date of publication */
    char *journal;	/* Journal of publication */
    char *title;	/* Title of publication */
    char *trait;	/* Disease or trait assessed in study */
    char *initSample;	/* Initial sample size */
    char *replSample;	/* Replication sample size */
    char *region;	/* Chromosome band / region of SNP */
    char *genes;	/* Reported Gene(s) */
    char *riskAllele;	/* Strongest SNP-Risk Allele */
    char *riskAlFreq;	/* Risk Allele Frequency */
    char *pValue;	/* p-Value */
    char *pValueDesc;	/* p-Value Description */
    char *orOrBeta;	/* Odds ratio or beta */
    char *ci95;	/* 95% Confidence Interval */
    char *platform;	/* Platform and [SNPs passing QC] */
    enum gwasCatalogCnv cnv;	/* Y if Copy Number Variant */
    };

void gwasCatalogStaticLoad(char **row, struct gwasCatalog *ret);
/* Load a row from gwasCatalog table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct gwasCatalog *gwasCatalogLoad(char **row);
/* Load a gwasCatalog from row fetched with select * from gwasCatalog
 * from database.  Dispose of this with gwasCatalogFree(). */

struct gwasCatalog *gwasCatalogLoadAll(char *fileName);
/* Load all gwasCatalog from whitespace-separated file.
 * Dispose of this with gwasCatalogFreeList(). */

struct gwasCatalog *gwasCatalogLoadAllByChar(char *fileName, char chopper);
/* Load all gwasCatalog from chopper separated file.
 * Dispose of this with gwasCatalogFreeList(). */

#define gwasCatalogLoadAllByTab(a) gwasCatalogLoadAllByChar(a, '\t');
/* Load all gwasCatalog from tab separated file.
 * Dispose of this with gwasCatalogFreeList(). */

struct gwasCatalog *gwasCatalogCommaIn(char **pS, struct gwasCatalog *ret);
/* Create a gwasCatalog out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new gwasCatalog */

void gwasCatalogFree(struct gwasCatalog **pEl);
/* Free a single dynamically allocated gwasCatalog such as created
 * with gwasCatalogLoad(). */

void gwasCatalogFreeList(struct gwasCatalog **pList);
/* Free a list of dynamically allocated gwasCatalog's */

void gwasCatalogOutput(struct gwasCatalog *el, FILE *f, char sep, char lastSep);
/* Print out gwasCatalog.  Separate fields with sep. Follow last field with lastSep. */

#define gwasCatalogTabOut(el,f) gwasCatalogOutput(el,f,'\t','\n');
/* Print out gwasCatalog as a line in a tab-separated file. */

#define gwasCatalogCommaOut(el,f) gwasCatalogOutput(el,f,',',',');
/* Print out gwasCatalog as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* GWASCATALOG_H */
