
//create DB function definition

#include "inverted_search.h"


Status create_DB(word_l *word[26], f_arg *head_fname)
{
    while(head_fname != NULL)
    {
	FILE *fptr = NULL;
	int status;
	status = open_file_and_validate(head_fname,&fptr);
	if(status == FAILURE)
	    return FAILURE;
	else if( status == FILE_EMPTY)
	{
	    head_fname = head_fname->f_arg_link;
	    continue;
	}

	rewind(fptr);
	char ch[MAX_SIZE_WORD];
	while(fscanf(fptr,"%s",ch) == 1)
	{
	    //generate index and store
	    int index = toupper(ch[0]) % 65;

	    if(word[index] == NULL)
	    {
		word_l *new_w;
		//create word node
		create_word_node(&new_w,ch);

		f_name *new_f;
		//create file node
		create_file_node(&new_f,head_fname->file);

		word[index] = new_w;
		new_w->f_link = new_f;
		continue;
	    }

	    //take temp for word node
	    word_l *temp_w = word[index],*temp2_w = NULL;
	    while(temp_w != NULL && strcasecmp(temp_w->word_name,ch))
	    {
		temp2_w = temp_w;
		temp_w = temp_w->word_link;
	    }

	    //check matching word found or not
	    if(temp_w != NULL)
	    {
		f_name *temp_f = temp_w->f_link, *temp2_f=NULL;

		//traverse to find the file node if node create new node
		while(temp_f != NULL && strcasecmp(temp_f->file_name,head_fname->file))
		{
		    temp2_f = temp_f;
		    temp_f = temp_f->file_link;
		}

		//if file node already present the increment count
		if(temp_f != NULL)
		{
		    temp_f->word_count++;
		    continue;
		}

		f_name *new_f;
		//create file node
		create_file_node(&new_f,head_fname->file);

		//linking new file node
		temp2_f->file_link = new_f;
		//updating file count
		temp_w->file_count++;
		continue;
	    }
	    word_l *new_w;
	    //create word node
	    create_word_node(&new_w,ch);

	    f_name *new_f;
	    //create file node
	    create_file_node(&new_f,head_fname->file);


	    new_w->f_link = new_f;
	    temp2_w->word_link = new_w;

	}
	head_fname = head_fname->f_arg_link;
    }
    return SUCCESS;
}


//create word node
void create_word_node(word_l **new,char *word)
{
    (*new) = malloc(sizeof(word_l));

    //update values and link
    (*new)->file_count = 1;
    strcpy((*new)->word_name,word);
    (*new)->f_link = NULL;
    (*new)->word_link = NULL;
}

//create file node
void create_file_node(f_name **new,char *file)
{
    (*new) = malloc(sizeof(f_name));

    //update values and link
    (*new)->word_count = 1;
    strcpy((*new)->file_name,file);
    (*new)->file_link = NULL;
}


Status open_file_and_validate (f_arg *head_fname, FILE ** fptr)
{
    (*fptr) = fopen(head_fname->file, "r");
    if (!(*fptr))
    {
	printf ("File %s does not exist\n", head_fname->file);
    }

    //check that the file is empty or not

    rewind((*fptr));
    if(fgetc((*fptr)) == EOF)
    {
	printf("INFO : The file %s is empty\n",head_fname->file);
	return FILE_EMPTY;
    }


    return SUCCESS;

}


