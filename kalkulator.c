#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_STOS 1024

double stos[MAX_STOS];
int sp = 0;
char wyraz[255];
char wynik[255];



void push(double element)
{
    if (sp < MAX_STOS)
        stos[sp++] = element;
    else
	printf("push: Przepelnienie stosu!\n");
}



double pop(void)
{
    if (sp > 0)
        return stos[--sp];

    return 0;
}









void konwerterONP(char *wynik, char *s)
{
    char x, y;

    while (x = *s++) {
        if (((x >= '0') && (x <= '9')) || (x == '.')) {
            /* kopiowanie calej liczby z wejscia na wyjscie */
            do
                *wynik++ = x;
            while (x = *s, (((x >= '0') && (x <= '9')) || (x == '.')) && s++);
            *wynik++ = ' ';

	} else if (x == '(')
            push((double)'(');

	else if (x == ')')
            while ((y = (char)pop()) != '(')
                *wynik++ = y, *wynik++ = ' ';

	else {
            while (y = (char)pop(),y && ((y == '^') ||((y == '*') || (y == '/')) && (x != '^') ||((y == '+') || (y == '-')) && (x != '*') &&(x != '/') && (x != '^')))
                *wynik++ = y, *wynik++ = ' ';

            push((double)y);
            push((double)x);
        }
    }

    while (x = (char)pop())
        *wynik++ = x, *wynik++ = ' ';

    *wynik = '\0';
}

















void policz(char *wyrazenie){
 int pozycja, j;
int warunek;
unsigned int i=0;
int dlugosc;
char wyraz[255];
double a,b;
float liczba=0;



while (i<strlen(wyrazenie)){


  if ((wyrazenie[i]>='0')&&(wyrazenie[i]<='9')){
    warunek=0;
    pozycja=i;
    j=i+1;

    while(warunek==0){
        if (((wyrazenie[j]!='.')&&(((wyrazenie[j])<'0')||(wyrazenie[j]>'9')))){
            warunek=1;
            break;
        }
        j++;
    }

    memset(wyraz,' ',255);
    dlugosc=j-pozycja;
    strncpy(wyraz,wyrazenie+pozycja,dlugosc);
    liczba=atof(wyraz);
    push((double)liczba);
    i=j;
  }
  else
 if ((wyrazenie[i]=='-')){
    a=pop();
    b=pop();
    b=b-a;
    push(b);
 }
 else
if (wyrazenie[i]=='+'){
   a=pop();
   b=pop();
    a=a+b;
    push(a);
}
else
/*
if (wyrazenie[i]=='^'){
    a=pop();
   b=pop();
   int i=0;
    float c=b;
    for(i=0;i<(int)a;i++){
        b=b*c;
    }
    push(b);
}

else
    */
if (wyrazenie[i]=='*'){
    a=pop();
   b=pop();
   b=a*b;
    push(b);
}
else
if (wyrazenie[i]=='/'){
     a=pop();
    b=pop();
    b=b/a;
    push(b);

}


i++;
}

   if (sp==1)
    {
       printf("%lf",stos[sp-1]);
    }

}






int sprawdz(char *argument){
int i=0;
int nawias1=0;
int nawias2=0;
while (i<strlen(argument)){
    if ((isspace(argument[i])==0)&&((argument[i]<'0')||(argument[i]>'9'))&&(argument[i]!='.')&&(argument[i]!='/')&&(argument[i]!='*')&&(argument[i]!='+')&&(argument[i]!='-')&&(argument[i]!='(')&&(argument[i]!=')'))

{
  return -1;
}
    if (argument[i]=='('){nawias1++; }
    if (argument[i]==')'){nawias2++; }
i++;
}
if (nawias1>nawias2){

    return -2;
}
else if  (nawias1<nawias2) {
return -3;
}

return 0;
}






int main(int argc, char *argv[]){



int i=1;
        while(i<argc){

        if (i==1)
                {
                    strcpy(wyraz,argv[i]);

                 }

        else
                   {

        strcat (wyraz, argv[i]);


        }
        i++;
        }




if (sprawdz(wyraz)==-1){
            printf("podano zly parametr ");
            return -1;
}

if (sprawdz(wyraz)==-2){  printf("blad niedomknieto nawiasu/ow");  return -1;}

else

if (sprawdz(wyraz)==-3){ printf("blad brak nawiasu otwierajacego");  return -1;}


konwerterONP(wynik,wyraz);

policz(wynik);

return 0;

};

