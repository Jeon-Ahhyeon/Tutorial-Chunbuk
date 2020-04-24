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

 /* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum {
    lparen = 0,  /* ( ���� ��ȣ */
    rparen = 9,  /* ) ������ ��ȣ*/
    times = 7,   /* * ���� */
    divide =6,  /* / ������ */
    plus = 5,    /* + ���� */
    minus = 4,   /* - ���� */
    operand = 1 /* �ǿ����� */
} precedence;

 //�迭�� ������ �������� �����Ͽ� � �Լ������� �̿��� �� �ֵ��� �Ͽ���.
char infixExp[MAX_EXPRESSION_SIZE] = { NULL };      /* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE] = { 0 };   /* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];   /* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];      /* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;      /* evalStack�� top */

int evalResult = 0;      /* ��� ����� ���� */

void postfixPush(char x)  //postfixStack �迭�� ���� �ִ� �Լ�
{
    postfixStack[++postfixStackTop] = x;  //postfixStack�� ���� ���� ���ҿ� x���� �����Ѵ�. (postfixStackTop�� �������� ���� ���� �ε����� ����Ű�� �ֱ� ������ ���� ���� �� Top�� ���� ���Ѿ� �Ѵ�. )
}

char postfixPop()  //postfixStack �迭�� �� ���� �Լ� (postfixStackTop�� 1 ���� �����ش�. -> ���� top�� ����������� �ʾƵ� �ȴ�.)
{
    char x;  //������ ���� ����
    if (postfixStackTop == -1) // ���� �ش� ������ �����̶�� ���� ���� ����Ű�� ������ -1�̶�� ���� �ش� ������ ����ٴ� ��
        return '\0';  //�Լ��� �����Ѵ�.
    else {  //�ش� ������ �� ������ �ƴ϶��
        x = postfixStack[postfixStackTop--];  //x�� ���ÿ��� ���� �������� ���� ���Ҹ� x�� �����ϰ� �� �Ŀ� postfixStackTop�� 1 ���� ���� ���� ��ܿ� ��ġ�� ���Ҹ� ���ش�.
    }
    return x;  //�������� ���� ���Ҹ� ��ȯ���ش�.
}


void evalPush(int x)  //evalStack �迭�� ���� �ִ� �Լ�
{
    evalStack[++evalStackTop] = x;//evalStack�� ���� ���� ���ҿ� x���� �����Ѵ�. (evalStack�� ���� ���� ���� ���� ������ ����Ű���� �Ѵ�)
}

int evalPop()//evalStack �迭�� �� ���� �Լ� (evalStackTop��  ���� �����ش�. -> ���� top�� ����������� �ʾƵ� �ȴ�.)
{
    if (evalStackTop == -1)  //���� �ش� ������ �����̶�� ���� ���� ����Ű�� ������ -1�̶�� ���� �ش� ������ ����ٴ� ��
        return -1;  //-1�� ��ȯ�Ѵ�.
    else  //�ش� ������ �� ������ �ƴ϶��
        return evalStack[evalStackTop--];  //�ش� ���ÿ� ���� �������� ���� ���Ҹ� ��ȯ�ϰ� evalStackTop�� ���� ���� ���� ��ܿ� ��ġ�� ���Ҹ� ���ش�.
}


/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()  //���� ǥ��� �Է�
{
    printf("Type the expression >>> ");  //�ȳ����� ����ϰ�
	fflush(stdout);  //�Է� ���۸� ����� ��
    scanf("%s", infixExp);  //���� ǥ����� �Է¹޴´�.
}

precedence getToken(char symbol)  //�Է¹��� ���ڿ����� �����ڿ� �ǿ����ڸ� �����Ͽ� �켱������ ������ ���� ����ü ��������� ��ȭ���ش�.
{
    switch (symbol) {
    case '(': return lparen;   //���� ��ȣ
    case ')': return rparen; //������ ��ȣ
    case '+': return plus; //�÷���
    case '-': return minus; //���̳ʽ�
    case '/': return divide;  //������
    case '*': return times;  //���ϱ�
    default: return operand;  //�����ڰ� �ƴ϶�� �ǿ��������� �˷��ش�
    }

}

precedence getPriority(char x)  //�켱������ ã�� �Լ�
{
    return getToken(x);  //getToken �Լ��� ȣ���Ͽ� �������� ��ū ��ȯ �޾� �״�� ��ȯ�� �ش�.
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)  //���ڿ��� �Ѱܹ޾� �ش� ���ڿ��� ù��°  ���ڸ� postfixExp�� �����ϴ� �Լ�
{
    if (postfixExp == '\0') //postfixExp�� NULL�̶��
        strncpy(postfixExp, c, 1);  //�Ѱܹ��� ���� �ϳ��� postfixExp�� �����ϰ�
    else  //������� �ʴٸ�
        strncat(postfixExp, c, 1); //�Ѱ� ���� ���� �ϳ��� postfixExp �ڿ� ������.
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix() //�Է¹��� ����ǥ����� ���� ǥ������� ��ȯ�ϴ� �Լ�
{
    /* infixExp�� ���� �ϳ����� �б����� ������ */
    char* exp = infixExp;
    char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */
    char temp; //���� �ϳ��� �ӽ÷� �����ϱ� ���� ���� ����
    /* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */

    while (*exp != '\0')  //���� ǥ����� �Է¹��� inifixExp�� ���� �����ִٸ�  (���� ǥ����� �� ���� ǥ������� ��ȯ���� �ʾҴٸ�)
    {
        x = getPriority(*exp);  //x�� exp�� ù��°�� ����ִ� ������ �켱������ �����Ѵ�.
        if (x == operand)  //�� ���� �ǿ����ڶ��
        {
            printf(" %c ",*exp);  //���� ����ϰ�
            charCat(exp);  //charCat�Լ��� ȣ���Ͽ� �ش� ���� postfixExp�� �����Ѵ�.
        }
        else if (x == rparen) //�� ���� ������ ��ȣ��
               {
                   while (getPriority(postfixStack[postfixStackTop]) != lparen)  //���� ��ȣ�� ���ö�����
                   {
                       temp = postfixPop();  //temp�� ������� postfixStack�� ��� �ִ� ���� ���� ���� ���� ���Ҹ� pop�Ͽ�  temp�� �����ϰ�
                       printf(" %c", temp);  //�ش� �����ڸ� ��� �� ��
                       charCat(&temp); //�� �����ڸ� postfixExp�� �����Ѵ�.
                   }
                   postfixPop();  //���� ��ȣ�� ���ÿ��� ������.
               }
        else if (postfixStackTop == -1)  //�� ���� �ǿ����ڰ� �ƴѵ� stack�� ��� �ִ� ���� ���ٸ�
        {
            postfixPush(*exp);  //�� ���� postfixStack�� push���ش�.
        }

        else if (x >= getPriority(postfixStack[postfixStackTop]))  //�� ���� Stack�� ��� �ִ� ������ �켱������ ���ų� ������
        {
           if (x == 7 && getPriority(postfixStack[postfixStackTop]) == 6)  //*�� /�� �켱������ ���Ƿ� ���������� ���� ���꿡�� �Ȱ��� ������  ���� *�϶� ��� �ִ� ���� /�̶��
            {
                temp = postfixPop();  //temp���� pop�� �̿��Ͽ� Stack�� �ִ� /�� �����ϰ�
                charCat(&temp); //charCat�Լ��� �̿��Ͽ� postfixExp�� /�� �־��ְ�
                printf(" %c", temp);  // '/'������ ���
                postfixPush(*exp);  //���� ������ �ִ� *�� �ٽ� push���ش�.
            }
           else if (x == 5 && getPriority(postfixStack[postfixStackTop]) == 4)  //���������� +��-�� �켱������ ���Ƿ� ���������� ���� ���꿡�� �Ȱ��� ������  ���� +�϶� ��� �ִ� ���� -�̶��
           {   temp = postfixPop();//temp���� pop�� �̿��Ͽ� Stack�� �ִ�'-'�� �����ϰ�
                charCat(&temp);//charCat�Լ��� �̿��Ͽ� postfixExp�� -�� �־��ְ�
                printf(" %c", temp);  //'-' ������ ���
                postfixPush(*exp);//���� ������ �ִ� '+'�� �ٽ� push���ش�.
            }
            else  //�ƴ϶��
                postfixPush(*exp);  //�� ���� postfixExp�� push�Ѵ�.
        }

        else  //�켱������ Stack�� ��� �ִ� ������ �۴ٸ�
           {
        	while (x!=lparen&& postfixStackTop !=-1&&(x < getPriority(postfixStack[postfixStackTop])))
        	{
                   temp = postfixPop();  // temp�� ���� Stack�� ��� �ִ� ���� pop�Ͽ� ������ �� ����
                   charCat(&temp);  //�� ���� postfixExp �� ������ ��6/
                   printf(" %c",temp);  // �� ������ ���
            } //���� �켱������ Stack�� ��� �ִ� ������ �۰�, �ش� ������ �� ������ �ƴϸ� �� ���� ���� ��ȣ�� �ƴϸ� ��� �ݺ��Ѵ�.
               postfixPush(*exp);//������ �켱������ ���� ���� Stack���� �� ������ �� x�� Stack�� �����Ѵ�.
           }
        exp++;  //exp�� ó�� ���� �ּҸ� �ϳ��� �����Ͽ� ���� ���ڸ� ����Ű���� �Ѵ�.
    }
    while (postfixStackTop != -1)  //���� ǥ����� ���� ǥ��Ŀ� �����ϴ°� ������ ����ǥ����� �����ϴ� postfixStack�� ���� ������� �ʴٸ� �Է��� ������� pop�Ͽ� �������ش�.
    {
        x = postfixPop();  //postfixPop�Լ��� ȣ���Ͽ� x�� ���ÿ� ���� ���� �ִ� �����ڸ� ������ �� Stack���� ����.
        charCat(&x);  //�� �����ڸ� postfixExp�� �����ϰ�
        printf(" %c", x);  //����Ѵ�.
    } // ������ �������� ����Ѵ�.
    printf("\n");//���� �ѱ��
}
void debug()  //�Է��� ����ǥ���, �ٲ� ����ǥ���, ����ǥ����� �̿��� ����� ��� ��, ���� postStack�� ��� �ִ� ���� ������ִ� �Լ�
{
    printf("\n---DEBUG\n");  //�ȳ��� ���
    printf("infixExp =  %s\n", infixExp); //����ǥ����� ���
    printf("postExp =  %s\n", postfixExp);  //���� ǥ��� ���
    printf("eval result = %d\n", evalResult);  //����� ��� �� ���

    printf("postfixStack : ");  //�ȳ��� ���
    for (int i = 0; i < MAX_STACK_SIZE; i++)  //������ ũ�⸸ŭ �ݺ��Ͽ�
        printf("%c  ", postfixStack[i]);  //postStack�� ��� �ִ� ���� ���

    printf("\n");  //���� �ѱ��

}

void reset() //Stack�� �������ִ� �Լ�
{
    infixExp[0] = '\0';  //���� ǥ��İ� ����ǥ����� ��� �ִ� ���ڿ��� �ʱ�ȭ �����ش�.
    postfixExp[0] = '\0';

    for (int i = 0; i < MAX_STACK_SIZE; i++)  //������ ũ�⸸ŭ �ݺ��Ͽ�
        postfixStack[i] = '\0';  //postfixStack�� ��� �ִ� ���� �ʱ�ȭ �����ش�.

    postfixStackTop = -1;  //������ �ʱ� top���� ��������ش�. ���� �Է��� ���� ++�����ڸ� �̿��Ͽ� �迭�� ù ���Һ��� ���� ���� �� �ֵ��� �ϱ� ���� -1�� �����Ų��.
    evalStackTop = -1;
    evalResult = 0;  //��� ��� ���� 0���� �ʱ�ȭ �����ش�.
}

void evaluation()  //�ٲ� ����ǥ����� �̿��� ����ϴ� �Լ�
{
    /* postfixExp, evalStack�� �̿��� ��� */
    char x; // ���� �ϳ��� �����ϱ� ���� ����
    char* exp = postfixExp;  //postfixExp�� ���ڸ� �ϳ��� �б� ���� ������
    int op1, op2;  //postfixExp�� ��� �ִ� ���ڸ� ������ ����
    while (*exp != '\0')  //postfixExp�� ���ڰ� �����ִٸ�
    {
        x = getPriority(*exp);  //postfixExp�� ù��° ������ �켱������ �����ϰ�
        if (x == 1)  // �� ���� �ǿ����ڶ��
        {
            evalPush(*exp);  //evalStack�� push�Ѵ�.
        }
        else  //�����ڶ��
        {
            op1 = evalPop()-'0'; //evalStack�� ��� �ִ� ���ڸ� �� ������� pop���ش�. �̶� evalpop�� ���ڿ��̰� op1,op2�� int���̹Ƿ� '0'�� ���־� �ƽ�Ű �ڵ忡�� ���ڷ� �������ش�.
            op2 = evalPop()-'0';
            switch(x)  //�������� ���� ���� ��� ����
            {
                case plus: evalPush(op1 + op2+'0');    break;  //'+' �����ڶ�� op1+op2�� evalStack�� ������
                case minus: evalPush(op2 - op1+'0');   break;  //'-'�����ڶ�� op2-op1�� evalStack�� ���� (���� ��� �� ���� ���� ������ Stack�� Ư�� �� op2-op1�� ���־�� �Ѵ�.)
                case times: evalPush(op1 * op2+'0');   break; //'*'�����ڶ�� op1*op2�� evalStack�� ����
                case divide: evalPush(op2 / op1+'0');  break;//'/'�����ڶ�� op2/op1�� ecalStack�� ����
            }  //������ ������ �� ������ ���� ���������� �ٲٴ� ���̹Ƿ� '0'�� �����־� �ƽ�Ű �ڵ�� �����Ѵ�.
        }

        exp++;  //exp�� ����Ű�� �ּҸ� ������� postfixExp�� �ִ� ���� ���� ����� �� �ֵ��� �Ѵ�.
    }

    evalResult = evalPop()-'0'; //����� �Ϸ�Ǿ��ٸ� evalPop�� ���� ������� evalResult�� �����ϴµ� �̶� �ƽ�Ű �ڵ� ���� ���������� �ٲٴ� ���̹Ƿ� '0'�� ���ش�.
}


int main()
{
    char command;  //�޴��� �Է¹��� ����

    do {
        printf("----------------------------------------------------------------\n");  //�ȳ��� ���
        printf("               Infix to Postfix, then Evaluation     \n");
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");  //�ȳ��� ��� ��
		fflush(stdout);  //���۸� ����
        scanf(" %c", &command);  //�޴��� �Է�

        switch (command) {  //����ġ ���� �̿���
        case 'i': case 'I':  //Infix�� �����Ͽ��ٸ�
            getInfix();  //getInfix�Լ��� ȣ���Ͽ� ���� ǥ����� �Է¹޴´�.
            break;//����ġ ���� ����������.
        case 'p': case 'P':  //Postfix�� �����ߴٸ�
            toPostfix();  //topostfix�Լ��� ȣ���Ͽ� ����ǥ����� ����ǥ������� �����Ѵ�.
            break;  //����ġ ���� ����������.
        case 'e': case 'E':  //Eval�� �����ߴٸ�
            evaluation();  //evaluation �Լ��� ȣ���Ͽ� ����ǥ����� ����� �� ����� �����Ѵ�.
            break;//����ġ ���� ����������,
        case 'd': case 'D':  //Debug�� �����ߴٸ�
            debug();  //debug�Լ��� ȣ���Ͽ� ������ ����ϰ�
            break; //����ġ ���� ����������.
        case 'r': case 'R':  //Reset�� �����ߴٸ�
            reset();  //reset�Լ��� ȣ���Ͽ� ���õ�� ��� ��� ������ �ʱ�ȭ���ְ�
            break;  //����ġ ���� ���� ������.
        case 'q': case 'Q':  //Quit�� �����ߴٸ�
            break;  //����ġ���� �߷��Ѵ�
        default:  //�޴��� �߸� �����ߴٸ�
            printf("\n     >>>>>   Concentration!!   <<<<<     \n");  //�ȳ��� ��� ��
            break;  //����ġ ���� �����Ѵ�.
        }

    } while (command != 'q' && command != 'Q');  //quit�� �������� ���� �ݺ����� ���� ���´�.

    printf("���α׷� ���� \n");  //�ȳ����� ��� �� ��

    return 0;  //���α׷��� �����Ѵ�.


}
