#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int OperandCatch(char *exp, int *exp_cnt);

char tmp[128];

/* デコード処理*/
int decode_data( char *s, int len )
{
   /* len はs が保持するデータのサイズ*/
   int i, j, k;     /* カウンタ類*/
   char buf, *s1;   /* 作業領域*/

   s1 = malloc (len + 1); /* エラー処理は省略*/

   for( i = 0, j = 0; i < len; i++, j++ ){
     if( s[i] == '+' ){
       s1[j] = ' ';
       continue;
     }
     if( s[i] != '%' ){
       s1[j] = s[i];
       continue;
     }
     buf = '\0';
     for( k = 0 ; k < 2 ; k++){
       buf *= 16;
       if( s[++i] >= 'A' )
         buf += (s[i] - 'A' + 10);
       else
         buf += (s[i] - '0');
     }
     s1[j] = buf;
   }

   for( i = 0; i < j; i++ ) /* 書き戻し*/
     s[i] = s1[i];
   s[i] = '\0';

   free( s1 );
   return 0;
}

void getElement(char *str)
{
	int i=0;
	int j=0;

	while('=' != str[i])
	{
		i++;		
	}
	for(i=i+1;i<128;i++)
	{
		tmp[j++] = str[i];
	}
}

int main(void)
{
	printf("Content-type:text/html\n\n");
	char query_string[128];
	strcpy(query_string, getenv("QUERY_STRING"));
	getElement(query_string);
	
	decode_data(tmp, strlen(tmp));
	printf("%s", tmp);

	int ans = 0;
	int operand[10];
	int operator[9];

	int i,j;
	int operand_cnt;

	i = j = 0;
	operand_cnt = 0;

	int len = strlen(tmp);

	while(i < len)
	{
		if('+' == tmp[i])
		{
			i += 1;
		}
		else
		{
			operand[operand_cnt] = OperandCatch(tmp, &i);
			operand_cnt++;
		}

		i++;
	}

	for(i=0;i<operand_cnt;i++)
	{
		ans += operand[i];
	}

	printf("%d\n", ans);

	return 0;
}

int OperandCatch(char *exp, int *exp_cnt)
{
	int i,k;
	char tmp_operand[5];
	int ans = 0;

	i = *exp_cnt;
	k = 0;

	while('+' != exp[i])
	{
		if('=' == exp[i])
			break;

		tmp_operand[k] = exp[i];

		i++; k++;
	}

	tmp_operand[k] = '\0';

	ans += atoi(tmp_operand);

	*exp_cnt = i;

	return ans;
}

