# include "recordKeeper.h"

/***
 * filestream.c will act as a container for I/O functions. Reading 
 * will take place in recordKeeper.c
***/

// Data file to be opened/read/parsed/closed.
FILE * inputStream;


/**
 * startInputStream() will open the file used
 * to input data
 **/
int fs_startInputStream(char * filename)
{
    if( filename == NULL || strlen(filename) < 1)
        return 1;
    
    inputStream = fopen(filename, "r");
    if(inputStream != NULL)
        return 0;
    else
        return 1;
}


/**
 * 
 * fs_closeInputStream() will close the file used
 * to input data.
 **/
int fs_closeInputStream()
{
    if(fclose(inputStream))
        return 1;
    
    return 0;
}

/**
 * Function getEntryFormat() will take in a given line of the timesheet
 * file and check if it is ISO or 'standard' time format.
 * 
 * parameters: 
 *  char * entry: record entry data to be checked
 * 
 * returns: int with format id, 0 on no match, and -1 on regex error.
 * */
int fs_getEntryFormat(char * entry) 
{ 
    if(entry == NULL)
        return 0;
    
	regex_t regexISO, regexSTD;
	int isoreti = 0;
	int stdreti = 0;

    isoreti = regcomp(&regexISO, "^[0-9]{4}-[0-9]{2}-[0-9]+ [0-9]+:[0-9]{2}", REG_EXTENDED);
    stdreti = regcomp(&regexSTD, "^[0-9]{1,2}:[0-9]{2} [a-z]{2},[0-9]{1,2}:[0-9]{2} [a-z]{2}", REG_EXTENDED);
	
	if(isoreti || stdreti)
		return -1;
	
	isoreti = regexec(&regexISO, entry, 0 , NULL, 0);
    stdreti = regexec(&regexSTD, entry, 0, NULL, 0);
    
    if(!isoreti)
        return ISO_FORMAT;
    else if (!stdreti)
        return STANDARD_FORMAT;
    else if(isoreti == REG_NOMATCH && stdreti == REG_NOMATCH)
        return 0;
    else
        return -1;
}
// returns a pointer to a file hamdle.
FILE * fs_getStream(){return inputStream;}
