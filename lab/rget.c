/****************
 * Author: Yuan-Yi Chang
 * Date: 2009/11/18
 ****************/
#include <stdio.h>
#include <string.h>

static char * rget(	FILE * in , char * rec_begin_pattern , int * rec_begin_pattern_length , 
			char * read_buf , int * read_buf_size , int * curr_buf_size , 
			char ** curr_rec , int * curr_rec_length , long long * curr_rec_offset , char ** next_rec )
{
	int tmp_find_next_rec , tmp_next_fread , tmp_curr_data;
	if( *next_rec == NULL )	// 一開始 或是準備 read buf
	{
		if( *curr_rec == NULL )
		{
			*curr_rec_offset = ftello( in );

			if(
				// no data
				feof( in )

				// no data
				|| ( *curr_buf_size = fread( read_buf , 1, *read_buf_size , in ) ) == 0

				// no begin pattern , not the same as using strncmp( *curr_rec , rec_begin_pattern ... )
				|| !( *curr_rec = ( char * ) memmem( read_buf , *curr_buf_size , rec_begin_pattern , *rec_begin_pattern_length ) )
			) 
			{
				return NULL;
			}
			else if( ( tmp_find_next_rec = *curr_buf_size - *rec_begin_pattern_length ) > 0 )
			{
				if( !( *next_rec = ( char * ) memmem( read_buf + *rec_begin_pattern_length , tmp_find_next_rec , rec_begin_pattern , *rec_begin_pattern_length ) ) )
				{
					if( !feof( in ) )	// buffer size is too small 
						return NULL;
					// the last record
					*curr_rec_length = *curr_buf_size;
					return *curr_rec;
				}
				*curr_rec_length = *next_rec - *curr_rec ;
				return *curr_rec;
			}
			else
			{
				return NULL;			// input data format error or buffer size is smaller then begin pattern length
			}
		}
	}
	else
	{
		*curr_buf_size = ( *curr_buf_size ) - ( *curr_rec_length );
		*curr_rec = *next_rec;

		*curr_rec_offset = ftello( in ) - *curr_buf_size;

		if( ( tmp_find_next_rec = *curr_buf_size - *rec_begin_pattern_length ) > 0 )
		{
			if( !( *next_rec = ( char * ) memmem( ( *curr_rec ) + *rec_begin_pattern_length , tmp_find_next_rec , rec_begin_pattern , *rec_begin_pattern_length ) ) )
			{
				if( !feof( in ) )	// do mv and find from begining
				{
					tmp_curr_data = *curr_buf_size;
					memcpy( read_buf , *curr_rec , *curr_buf_size );
					tmp_next_fread = ( *read_buf_size ) - ( *curr_buf_size );
					*curr_rec = read_buf;

					// no data
					if( ( *curr_buf_size = fread( read_buf + *curr_buf_size , 1, tmp_next_fread , in ) ) == 0 )
					{
						return NULL;
					}
					*curr_buf_size += tmp_curr_data;

					if( ( tmp_find_next_rec = *curr_buf_size - *rec_begin_pattern_length ) > 0 )
					{
						if( !( *next_rec = ( char * ) memmem( read_buf + *rec_begin_pattern_length , tmp_find_next_rec , rec_begin_pattern , *rec_begin_pattern_length ) ) )
						{
							if( !feof( in ) )	// buffer size is too small 
								return NULL;
							// the last record
							*curr_rec_length = *curr_buf_size;
							return *curr_rec;
						}
						*curr_rec_length = *next_rec - *curr_rec ;
						return *curr_rec;
					}
					else
					{
						return NULL;			// input data format error or buffer size is smaller then begin pattern length
					}

				}
				else	// the last record
				{
					*curr_rec_length = *curr_buf_size;
					return *curr_rec;
				}
			}
			*curr_rec_length = *next_rec - *curr_rec ;
			return *curr_rec;
		}
		else if( !feof(in) )	// do mv and find from begining
		{
			tmp_curr_data = *curr_buf_size;
			memcpy( read_buf , *curr_rec , *curr_buf_size );
			tmp_next_fread = ( *read_buf_size ) - ( *curr_buf_size );
			*curr_rec = read_buf;

			// no data
			if( ( *curr_buf_size = fread( read_buf + *curr_buf_size , 1, tmp_next_fread , in ) ) == 0 )
			{
				return NULL;
			}
			*curr_buf_size += tmp_curr_data;

			if( ( tmp_find_next_rec = *curr_buf_size - *rec_begin_pattern_length ) > 0 )
			{
				if( !( *next_rec = ( char * ) memmem( read_buf + *rec_begin_pattern_length , tmp_find_next_rec , rec_begin_pattern , *rec_begin_pattern_length ) ) )
				{
					if( !feof( in ) )	// buffer size is too small 
						return NULL;

					// the last record
					*curr_rec_length = *curr_buf_size;
					return *curr_rec;
				}
				*curr_rec_length = *next_rec - *curr_rec ;
				return *curr_rec;
			}
			else
			{
				return NULL;			// input data format error or buffer size is smaller then begin pattern length
			}

		}
		else
			return NULL;	// input data format error, end by record begin pattern
	}
	return NULL;
}
void my_stripSlashes( char * str )
{
        int i,j,length;
        length = (int)strlen( str );
        for( i=j=0 ; i<length ; i++,j++ )
        {
                if( str[i] == '\\' && i+1 < length )
                {
                        switch( str[i+1] )
                        {
                                case 'n':
                                        str[j] = '\n';
                                        i++;
                                        break;
                                case 't':
                                        str[j] = '\t';
                                        i++;
                                        break;
                                case 'r':
                                        str[j] = '\r';
                                        i++;
                                        break;
                                default:
                                        str[j] = str[i];
                        }
                }
                else
                        str[j] = str[i];
        }
        str[j] = '\0';
}
int main( int argc , char ** argv )
{
	FILE *in;
	char *readbuf;
	char * curr_rec , *tmp_rec ;
	int len_readbuf , len_rec_begin , len_read , len_curr ;
	long long offset;
	int rec_cnt;

	len_readbuf = 1024*1024*50;
	readbuf = (char*)malloc( sizeof(char)*len_readbuf );
	len_read = len_curr =  0;

	if( argc <2 )
	{
		printf("Usage> a.out \"record_begin_pattern\" \n");
		return 0;
	}
	if( argc <= 2 || ( in = fopen( argv[2] , "rb" ) ) == NULL )
		in = stdin;
	else
		printf( "Read from: %s\n" , argv[2] );
	rec_cnt = 0;
	my_stripSlashes( argv[1] );
	len_rec_begin = strlen( argv[1] );
	while( rget(
		in , 
		argv[1] , 
		&len_rec_begin ,
		readbuf ,
		&len_readbuf ,
		&len_read ,
		&curr_rec ,
		&len_curr ,
		&offset ,
		&tmp_rec
		) != NULL )
	{
/*
		printf("------\n");
		fwrite( curr_rec , len_curr , 1 , stdout );
		printf("\n");
*/
		rec_cnt++;
	}
	printf("Total:%d\n" , rec_cnt );
	if( in != stdin && in != NULL )
		fclose( in );
	free( readbuf );
	return 0;
}
