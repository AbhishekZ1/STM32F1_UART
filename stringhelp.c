# include "stringhelp.h"

// clear string
void clear_string(char str[])
	{
    int i =0;
    while (str[i]!='\0')
		{
		  str[i]='\0';
			i++;
		}
	}
// returns length of string
int str_length(char str[])
	{
    int count=0;
		while (str[count]!='\0')
		{
		  count++; 
		}
		return count;
	}
/// if str2 is substring of str
int Find_StringIn(char str[], char str2[]) 
	{
    int i = 0, j = 0;
    int len1 = str_length(str);
    int len2 = str_length(str2);

    while (i < len1) 
		{
					if (str[i] == str2[j]) 
						{
						
							if (j == len2) 
							{
									return 1;  // Match found
							}
							j++;
						 } 
					 else 
							{
								if (j > 0)
									{
										i = i - j;  // Reset i to check from next character
										j = 0;
									}
							}
					i++;
			}

    return 0;  // Match not found
	}
	
/// join str1str2
	
void contactStr(char str1[],char str2[])
	{
		int i =0,j=0;
		while (str1[i] !='\0')
			{
				i++;
			
			}
		while (str2[j]!='\0')
			{
				str1[i+j]=str2[j];
				j++;
			}

	}

void int2char(int num, char str[]) 
	{
			char lstr[30];
			int cnt = 0;
			int div = 10;
			int j = 0;

			while (num >= div) 
				{
					lstr[cnt] = num % div + 0x30;
					num /= 10;
					cnt++;
			 }

			lstr[cnt] = num + 0x30;

			for (j = cnt; j >= 0; j--) 
			 {
					str[cnt - j] = lstr[j];
			 }

			str[cnt + 1] = '\0';  // Add null terminator
	}
/// 
int char2int(char str[])
	{
			int result = 0;
			int stop = 0;
			int Strlen = str_length(str);
			int j = 0;
			char check[1];

			for(j = 0; j < Strlen; j++)
				{
						check[0] = str[j];
						if(Find_StringIn(check, "0123456789") == 0)
							{
									stop = 1;
									break;
							}
				}

			if(stop == 0)
				{
						for(j = 0; j < Strlen; j++)
							{
									result = result * 10 + (str[j] - 0x30);
							}
				}

			return result;
	}


