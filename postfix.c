/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
    lparen = 0,  /* ( 왼쪽 괄호 */
    rparen = 9,  /* ) 오른쪽 괄호*/
    times = 7,   /* * 곱셈 */
    divide =6,  /* / 나눗셈 */
    plus = 5,    /* + 덧셈 */
    minus = 4,   /* - 뺄셈 */
    operand = 1 /* 피연산자 */
} precedence;

 //배열과 변수를 전역으로 선언하여 어떤 함수에서도 이용할 수 있도록 하였다.
char infixExp[MAX_EXPRESSION_SIZE] = { NULL };      /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE] = { 0 };   /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];   /* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];      /* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;      /* evalStack용 top */

int evalResult = 0;      /* 계산 결과를 저장 */

void postfixPush(char x)  //postfixStack 배열에 값을 넣는 함수
{
    postfixStack[++postfixStackTop] = x;  //postfixStack의 가장 위의 원소에 x갑을 대입한다. (postfixStackTop는 마지막에 넣은 갑의 인덱스를 가리키고 있기 때문에 값을 넣을 때 Top을 증가 시켜야 한다. )
}

char postfixPop()  //postfixStack 배열에 값 빼는 함수 (postfixStackTop을 1 감소 시켜준다. -> 따로 top을 변경시켜주지 않아도 된다.)
{
    char x;  //문자형 변수 선언
    if (postfixStackTop == -1) // 만약 해당 스택이 공백이라면 가장 위를 가리키는 변수가 -1이라는 것은 해당 스택이 비었다는 것
        return '\0';  //함수를 종료한다.
    else {  //해당 스택이 빈 스택이 아니라면
        x = postfixStack[postfixStackTop--];  //x에 스택에서 가장 마지막에 들어온 원소를 x에 저장하고 난 후에 postfixStackTop을 1 감소 시켜 제일 상단에 위치한 원소를 빼준다.
    }
    return x;  //마지막에 들어온 원소를 반환해준다.
}


void evalPush(int x)  //evalStack 배열에 값을 넣는 함수
{
    evalStack[++evalStackTop] = x;//evalStack의 가장 위의 원소에 x갑을 대입한다. (evalStack의 값을 증가 시켜 다음 공간을 가리키도록 한다)
}

int evalPop()//evalStack 배열에 값 빼는 함수 (evalStackTop을  감소 시켜준다. -> 따로 top을 변경시켜주지 않아도 된다.)
{
    if (evalStackTop == -1)  //만약 해당 스택이 공백이라면 가장 위를 가리키는 변수가 -1이라는 것은 해당 스택이 비었다는 것
        return -1;  //-1을 반환한다.
    else  //해당 스택이 빈 스택이 아니라면
        return evalStack[evalStackTop--];  //해당 스택에 제일 마지막에 들어온 원소를 반환하고 evalStackTop을 감소 시켜 제일 상단에 위치한 원소를 빼준다.
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()  //중위 표기식 입력
{
    printf("Type the expression >>> ");  //안내문을 출력하고
	fflush(stdout);  //입력 버퍼를 비워준 뒤
    scanf("%s", infixExp);  //중위 표기식을 입력받는다.
}

precedence getToken(char symbol)  //입력받은 문자열에서 연산자와 피연산자를 구분하여 우선순위를 정의해 놓은 구조체 멤버변수를 반화해준다.
{
    switch (symbol) {
    case '(': return lparen;   //왼쪽 괄호
    case ')': return rparen; //오른쪽 괄호
    case '+': return plus; //플러스
    case '-': return minus; //마이너스
    case '/': return divide;  //나누기
    case '*': return times;  //곱하기
    default: return operand;  //연산자가 아니라면 피연산자이을 알려준다
    }

}

precedence getPriority(char x)  //우선순위를 찾는 함수
{
    return getToken(x);  //getToken 함수를 호출하여 연산자의 토큰 반환 받아 그대로 반환해 준다.
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)  //문자열을 넘겨받아 해당 문자열중 첫번째  문자를 postfixExp에 저장하는 함수
{
    if (postfixExp == '\0') //postfixExp가 NULL이라면
        strncpy(postfixExp, c, 1);  //넘겨받은 문자 하나를 postfixExp에 복사하고
    else  //비어있지 않다면
        strncat(postfixExp, c, 1); //넘겨 받은 문자 하나를 postfixExp 뒤에 붙힌다.
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix() //입력받은 중위표기식을 후위 표기식으로 변환하는 함수
{
    /* infixExp의 문자 하나씩을 읽기위한 포인터 */
    char* exp = infixExp;
    char x; /* 문자하나를 임시로 저장하기 위한 변수 */
    char temp; //문자 하나를 임시로 저장하기 위한 변수 선언
    /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */

    while (*exp != '\0')  //중위 표기식을 입력받은 inifixExp의 값이 남아있다면  (중위 표기식을 다 후위 표기식으로 변환하지 않았다면)
    {
        x = getPriority(*exp);  //x에 exp의 첫번째에 들어있는 원소의 우선순위를 저장한다.
        if (x == operand)  //그 값이 피연산자라면
        {
            printf(" %c ",*exp);  //값을 출력하고
            charCat(exp);  //charCat함수를 호출하여 해당 값을 postfixExp에 저장한다.
        }
        else if (x == rparen) //그 값이 오른쪽 괄호면
               {
                   while (getPriority(postfixStack[postfixStackTop]) != lparen)  //왼쪽 괄호가 나올때까지
                   {
                       temp = postfixPop();  //temp에 현재까지 postfixStack에 들어 있는 값중 가장 먼저 들어온 원소를 pop하여  temp에 저장하고
                       printf(" %c", temp);  //해당 연산자를 출력 한 후
                       charCat(&temp); //그 연산자를 postfixExp에 저장한다.
                   }
                   postfixPop();  //왼쪽 괄호를 스택에서 꺼낸다.
               }
        else if (postfixStackTop == -1)  //그 값이 피연산자가 아닌데 stack에 들어 있는 값이 없다면
        {
            postfixPush(*exp);  //그 값을 postfixStack에 push해준다.
        }

        else if (x >= getPriority(postfixStack[postfixStackTop]))  //그 값이 Stack에 들어 있는 값보다 우선순위가 높거나 같으면
        {
           if (x == 7 && getPriority(postfixStack[postfixStackTop]) == 6)  //*와 /의 우선순위는 임의로 나눠놨지만 실제 연산에선 똑같기 때문에  값이 *일때 들어 있는 값이 /이라면
            {
                temp = postfixPop();  //temp에서 pop을 이용하여 Stack에 있는 /를 저장하고
                charCat(&temp); //charCat함수를 이용하여 postfixExp에 /를 넣어주고
                printf(" %c", temp);  // '/'연산자 출력
                postfixPush(*exp);  //현재 가지고 있던 *를 다시 push해준다.
            }
           else if (x == 5 && getPriority(postfixStack[postfixStackTop]) == 4)  //마찬가지고 +와-의 우선순위는 임의로 나눠놨지만 실제 연산에선 똑같기 때문에  값이 +일때 들어 있는 값이 -이라면
           {   temp = postfixPop();//temp에서 pop을 이용하여 Stack에 있는'-'를 저장하고
                charCat(&temp);//charCat함수를 이용하여 postfixExp에 -를 넣어주고
                printf(" %c", temp);  //'-' 연산자 출력
                postfixPush(*exp);//현재 가지고 있던 '+'를 다시 push해준다.
            }
            else  //아니라면
                postfixPush(*exp);  //그 값을 postfixExp에 push한다.
        }

        else  //우선순위가 Stack에 들어 있는 값보다 작다면
           {
        	while (x!=lparen&& postfixStackTop !=-1&&(x < getPriority(postfixStack[postfixStackTop])))
        	{
                   temp = postfixPop();  // temp에 현재 Stack에 들어 있는 값을 pop하여 저장한 후 빼고
                   charCat(&temp);  //뺀 값을 postfixExp 에 저장한 후6/
                   printf(" %c",temp);  // 뺀 연산자 출력
            } //값의 우선순위가 Stack에 들어 있는 값보다 작고, 해당 스택이 빈 스택이 아니며 그 값이 왼쪽 괄호가 아니면 계속 반복한다.
               postfixPush(*exp);//값보다 우선순위가 놓은 값을 Stack에서 다 뺐으면 값 x를 Stack에 저장한다.
           }
        exp++;  //exp의 처음 시작 주소를 하나씩 변경하여 다음 문자를 가리키도록 한다.
    }
    while (postfixStackTop != -1)  //중위 표기식을 후위 표기식에 저장하는게 끝났고 후위표기식을 저장하는 postfixStack의 값이 비어있지 않다면 입력한 순서대로 pop하여 저장해준다.
    {
        x = postfixPop();  //postfixPop함수를 호출하여 x에 스택에 제일 위에 있는 연산자를 저장한 후 Stack에서 뺀다.
        charCat(&x);  //뺀 연산자를 postfixExp에 저장하고
        printf(" %c", x);  //출력한다.
    } // 스택이 빌때까지 계속한다.
    printf("\n");//한줄 넘기기
}
void debug()  //입력한 중위표기식, 바꾼 후위표기식, 후위표기식을 이용해 계산한 결과 값, 현재 postStack에 들어 있는 값을 출력해주는 함수
{
    printf("\n---DEBUG\n");  //안내문 출력
    printf("infixExp =  %s\n", infixExp); //중위표기식을 출력
    printf("postExp =  %s\n", postfixExp);  //후위 표기식 출력
    printf("eval result = %d\n", evalResult);  //계산한 결과 값 출력

    printf("postfixStack : ");  //안내문 출력
    for (int i = 0; i < MAX_STACK_SIZE; i++)  //스택의 크기만큼 반복하여
        printf("%c  ", postfixStack[i]);  //postStack에 들어 있는 값을 출력

    printf("\n");  //한줄 넘기기

}

void reset() //Stack을 리셋해주는 함수
{
    infixExp[0] = '\0';  //중위 표기식과 후위표기식이 들어 있는 문자열을 초기화 시켜준다.
    postfixExp[0] = '\0';

    for (int i = 0; i < MAX_STACK_SIZE; i++)  //스택의 크기만큼 반복하여
        postfixStack[i] = '\0';  //postfixStack에 들어 있는 값을 초기화 시켜준다.

    postfixStackTop = -1;  //스택의 초기 top값을 변경시켜준다. 값을 입력할 때는 ++연산자를 이용하여 배열의 첫 원소부터 값을 넣을 수 있도록 하기 위해 -1로 변경시킨다.
    evalStackTop = -1;
    evalResult = 0;  //계산 결과 값을 0으로 초기화 시켜준다.
}

void evaluation()  //바꾼 후위표기식을 이용해 계산하는 함수
{
    /* postfixExp, evalStack을 이용한 계산 */
    char x; // 문자 하나를 저장하기 위한 변수
    char* exp = postfixExp;  //postfixExp의 문자를 하나씩 읽기 위한 포인터
    int op1, op2;  //postfixExp에 들어 있는 숫자를 저장할 변수
    while (*exp != '\0')  //postfixExp에 문자가 남아있다면
    {
        x = getPriority(*exp);  //postfixExp의 첫번째 원소의 우선순위를 저장하고
        if (x == 1)  // 그 값이 피연산자라면
        {
            evalPush(*exp);  //evalStack에 push한다.
        }
        else  //연산자라면
        {
            op1 = evalPop()-'0'; //evalStack에 들어 있는 숫자를 들어간 순서대로 pop해준다. 이때 evalpop은 문자열이고 op1,op2는 int형이므로 '0'을 빼주어 아스키 코드에서 숫자로 변경해준다.
            op2 = evalPop()-'0';
            switch(x)  //연산자의 값에 따라 결과 저장
            {
                case plus: evalPush(op1 + op2+'0');    break;  //'+' 연산자라면 op1+op2를 evalStack에 저장하
                case minus: evalPush(op2 - op1+'0');   break;  //'-'연산자라면 op2-op1을 evalStack에 저장 (먼저 들어 온 값이 먼저 나가는 Stack의 특성 상 op2-op1을 해주어야 한다.)
                case times: evalPush(op1 * op2+'0');   break; //'*'연산자라면 op1*op2를 evalStack에 저장
                case divide: evalPush(op2 / op1+'0');  break;//'/'연산자라면 op2/op1을 ecalStack에 저장
            }  //값들을 저장할 때 정수형 값을 문자형으로 바꾸는 것이므로 '0'을 더해주어 아스키 코드로 변경한다.
        }

        exp++;  //exp가 가리키는 주소를 변경시켜 postfixExp에 있는 값을 전부 계산할 수 있도록 한다.
    }

    evalResult = evalPop()-'0'; //계산이 완료되었다면 evalPop을 통해 결과값을 evalResult에 저장하는데 이때 아스키 코드 값을 정수형으로 바꾸는 것이므로 '0'을 빼준다.
}


int main()
{
    char command;  //메뉴를 입력받을 변수

    do {
        printf("----------------------------------------------------------------\n");  //안내문 출력
        printf("               Infix to Postfix, then Evaluation     \n");
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");  //안내문 출력 후
		fflush(stdout);  //버퍼를 비우고
        scanf(" %c", &command);  //메뉴를 입력

        switch (command) {  //스위치 문을 이용해
        case 'i': case 'I':  //Infix를 선택하였다면
            getInfix();  //getInfix함수를 호출하여 중위 표기식을 입력받는다.
            break;//스위치 문을 빠져나간다.
        case 'p': case 'P':  //Postfix를 선택했다면
            toPostfix();  //topostfix함수를 호출하여 중위표기식을 후위표기식으로 변경한다.
            break;  //스위치 문을 빠져나간다.
        case 'e': case 'E':  //Eval을 선택했다면
            evaluation();  //evaluation 함수를 호출하여 후위표기식을 계산한 후 결과를 저장한다.
            break;//스위치 문을 빠져나간다,
        case 'd': case 'D':  //Debug를 선택했다면
            debug();  //debug함수를 호출하여 정보를 출력하고
            break; //스위치 문을 빠져나간다.
        case 'r': case 'R':  //Reset을 선택했다면
            reset();  //reset함수를 호출하여 스택들과 계산 결과 값들을 초기화해주고
            break;  //스위치 문을 빠져 나간다.
        case 'q': case 'Q':  //Quit를 선택했다면
            break;  //스위치문을 중료한다
        default:  //메뉴를 잘못 선택했다면
            printf("\n     >>>>>   Concentration!!   <<<<<     \n");  //안내문 출력 후
            break;  //스위치 문을 종료한다.
        }

    } while (command != 'q' && command != 'Q');  //quit를 선택했을 때는 반복문을 빠져 나온다.

    printf("프로그램 종료 \n");  //안내문을 출력 한 후

    return 0;  //프로그램을 종료한다.


}
