//save database to file function


#include "inverted_search.h"

Status save_DB(word_l *word[26],char *fname)
{
    FILE *fptr;

    if(validate_and_open_save(fname,&fptr) == FAILURE)
	return FAILURE;

    rewind(fptr);
    int i=0;
    word_l *temp_w;
    for(i=0; i<26; i++)
    {
	temp_w = word[i];

	while(temp_w)
	{
	    fprintf(fptr,"%s:%d:%s:%d:","#",i,temp_w->word_name,temp_w->file_count);

	    f_name *temp_f = temp_w->f_link;
	    while(temp_f)
	    {
		fprintf(fptr,"%s:%d:",temp_f->file_name,temp_f->word_count);
		temp_f = temp_f->file_link;
	    }
	    fprintf(fptr,"#\n");
	    temp_w = temp_w->word_link;
	}

    }

    fclose(fptr);
    return SUCCESS;
}



Status validate_and_open_save(char *fname,FILE **fptr)
{
    if(!strstr(fname,".txt"))
    {
	printf("Please provide .txt file\n");
	return FAILURE;
    }

    //open file

    (*fptr) = fopen(fname,"w");
    if(!(*fptr))
    {
	printf("ERROR : File doesn't exist\n");
	return FAILURE;
    }

}
