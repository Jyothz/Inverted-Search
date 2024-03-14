// Display Database

#include "inverted_search.h"

Status display_DB(word_l *word[26])
{
    int i=0,flag=0;
    for(i = 0; i<26; i++)
    {
	word_l *temp_w = word[i];

	while(temp_w)
	{
	    //printf word file count and file name word count
	    printf("[%d] [%s] %d ",i,temp_w->word_name,temp_w->file_count);

	    //file node traversing
	    f_name *temp_f = temp_w->f_link;

	    //priting each file node
	    while(temp_f)
	    {
		printf("file/s : File : %s %d ",temp_f->file_name,temp_f->word_count);
		temp_f = temp_f->file_link;
	    }

	    temp_w = temp_w->word_link;
	    putchar('\n');
	    flag=1;
	}
    }
    if(flag)
	return SUCCESS;
    else
	return FILE_EMPTY;
}

