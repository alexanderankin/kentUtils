# bed6.sql was originally generated by the autoSql program, which also 
# generated bed6.c and bed6.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Browser extensible data
CREATE TABLE bed6 (
    chrom varchar(255) not null,	# Human chromosome or FPC contig
    chromStart int unsigned not null,	# Start position in chromosome
    chromEnd int unsigned not null,	# End position in chromosome
    name varchar(255) not null,	# Name of item
    score int unsigned not null,	# Score from 0-1000
    strand char(1) not null,	# + or -
              #Indices
    INDEX(chrom,start),
    INDEX(chrom,end)
);