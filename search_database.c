/*
NAME : JYOTHISH B CHANDRAN
DATE :
DESCRIPTION :
SAMPLE INPUT :
SAMPLE OUTPUT :
 */

#include "inverted_search.h"

Status search_DB(word_l *word[26],char *search_w)
{
    //finding index of the search key
    int index = toupper(search_w[0]) % 65;

    if(word[index] == NULL)
    {
	return DATA_NOT_FOUND;
    }

    word_l *temp_w = word[index];

    while(temp_w != NULL && strcasecmp(temp_w->word_name,search_w))
    {
	temp_w = temp_w->word_link;
    }

    if(temp_w == NULL)
	return DATA_NOT_FOUND;

    printf("The word %s is present in %d file/s\n",search_w,temp_w->file_count);

    //traverse files
    f_name *temp_f = temp_w->f_link;

    while(temp_f)
    {
	printf("In FIle : %s %d time/s\n",temp_f->file_name,temp_f->word_count);
	temp_f = temp_f->file_link;
    }

    return SUCCESS;

}

