#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int wordSeparater(char *exp, int *exp_cnt);
int decodeData( char *s, int len );

char tmp[128];

int main(void)
{
	printf("Content-type:text/html\n\n");
	char query_string[128];
	strcpy(query_string, getenv("QUERY_STRING"));	
	decodeData(query_string, strlen(query_string));

	int i,j;

	for(int k=12;k<strlen(query_string);k++)
	{
		tmp[i++] = query_string[k];
	}

	printf("%s\n", tmp);

	int ans = 0;
	int operand[10];
	int operator[9];

	int operand_cnt;

	i = j = 0;
	operand_cnt = 0;

	int len = strlen(tmp);

	printf("G=%s;", tmp);
	printf("H=;");

	while(i < len)
	{
		printf("%c", tmp[i]);

		if('+' == tmp[i])
		{
			operator[j++] = tmp[i];
			i++;
		}
		else if('=' == tmp[i])
		{
			break;
		}
		else
		{
			operand[operand_cnt++] = wordSeparater(tmp, &i);
		}
	}

	j = 0;
	int subtotal = operand[0];

	// 加算回路未完成(式のパースまでは完了)
	for(i=1;i<operand_cnt;i++)
	{
		if('+' == operator[j])
		{
			subtotal += operand[i];
			j++;
		}
	}

	printf("%d\n", subtotal);

	return 0;
}

/* オペランドを取り出して整数に変換 */
int wordSeparater(char *exp, int *exp_cnt)
{
	int save = *exp_cnt;
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

	*exp_cnt = save + k;

	return ans;
}

/* URLデコード処理*/
int decodeData( char *s, int len )
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
