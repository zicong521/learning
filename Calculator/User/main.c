#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_usart.h"

#include "stdlib.h"
#include "math.h"
#include "string.h"
static void Show_Message(void);


char KeyValue = 0 ;//全局变量 键值为 0 意味着没有输入
char ans[10];
int main(void)
{

    char str[10];

    uint16_t pstr = 0;

    float answer = 0 ;


    /* 按键初始化 */
    KEY_GPIO_Config();

    /* 初始化USART 配置模式为 115200 8-N-1 */
    USART_Config();

    GENERAL_TIM_Mode_Config();

    Show_Message();



    while(1)
    {
        switch(KeyValue)
        {
        case 0:
            break;
        case 7://检测到退格
            if(pstr>=1)
            {
                pstr-- ;
            }
            KeyValue = 0;
            break;
        case 14://检测到输出

            str[pstr] = '\0';//终止符

            printf("%s\n",str);//打印表达书
            printf("\t = ");

            ans[0]='$';//标识符
            ans[1] = '\0';
            strcat(ans,str);
            answer = Calculator(ans);
            printf("%f\n",answer);

            memset(str,0,10);
            memset(ans,0,10);
            pstr=0;

            break;
        default://其他值存到字符数组里
            str[pstr++] = KeyValue;
            KeyValue =0;
        }
    }
}


static void Show_Message(void)
{

    printf("\r\n   请输入要计算的表达式 支持小括号 浮点数 负数 \n \n");
    printf("\n    *：shift   # 为退格   A B C D ： + - *  /   \n");
    printf("\n   shift+A : (  shift +B :)  shift +C : 输出  \n");
    printf("\n");
}





typedef enum {
    KeyState_1=0,
    KeyState_2,
    KeyState_3,
    KeyState_4
} KeyState;

uint16_t shift_flag = 0;
void KeyScan()
{
    static KeyState judge = KeyState_1;//状态一
    switch(judge)
    {
    case KeyState_1:
        //把B12-B15先置1
        GPIO_SetBits(GPIOB,GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15);
        if((GPIOA->IDR & 0x00f0) !=0x0000)//有按键按下，跳转到state2
        {
            judge = KeyState_2;
        }
        else
        {
            judge = KeyState_1; //说明没有按下
            KeyValue = 0;
        }
        break;
    case KeyState_2:
        GPIO_SetBits(GPIOB,GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15);
        if((GPIOA->IDR & 0x00f0) !=0x0000)
        {
            judge = KeyState_3;//说明不为干扰 确实有按键按下
        }
        else
        {
            judge = KeyState_1;//回到state1
            KeyValue = 0;
        }
        break;
    case KeyState_3:
        //读取按键 一排一排扫描
        //在此处添加一个shift检测
        GPIO_SetBits(GPIOB,GPIO_Pin_12 | GPIO_Pin_15 );
        GPIO_ResetBits(GPIOB, GPIO_Pin_13 |GPIO_Pin_14  );
        if((GPIOA->IDR & 0x00f0) == 0x0090)
        {
            KeyValue=40;
            judge = KeyState_4;
            break;
        }

        GPIO_SetBits(GPIOB,GPIO_Pin_13 | GPIO_Pin_15);
        GPIO_ResetBits(GPIOB, GPIO_Pin_12 |GPIO_Pin_14 );
        if((GPIOA->IDR & 0x00f0) == 0x0090)
        {
            KeyValue=41;
            judge = KeyState_4;
            break;
        }

        GPIO_SetBits(GPIOB,GPIO_Pin_14| GPIO_Pin_15 );
        GPIO_ResetBits(GPIOB, GPIO_Pin_12 |GPIO_Pin_13 );
        if((GPIOA->IDR & 0x00f0) == 0x0090)
        {
            KeyValue=14;
            judge = KeyState_4;
            break;
        }




        //第一排检测 无shift
        GPIO_SetBits(GPIOB,GPIO_Pin_12 );
        GPIO_ResetBits(GPIOB, GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15);
        switch(GPIOA->IDR & 0x00f0)
        {
        case 0x0080:
            KeyValue=43;
            break;
        case 0x0040:
            KeyValue=51;
            break;
        case 0x0020:
            KeyValue=50;
            break;
        case 0x0010:
            KeyValue=49;
            break;
        }
        //第二排检测
        GPIO_SetBits(GPIOB,GPIO_Pin_13 );
        GPIO_ResetBits(GPIOB, GPIO_Pin_12 |GPIO_Pin_14 | GPIO_Pin_15);
        switch(GPIOA->IDR & 0x00f0)
        {
        case 0x0080:
            KeyValue=45;
            break;
        case 0x0040:
            KeyValue=54;
            break;
        case 0x0020:
            KeyValue=53;
            break;
        case 0x0010:
            KeyValue=52;
            break;
        }
        //第三排检测
        GPIO_SetBits(GPIOB,GPIO_Pin_14 );
        GPIO_ResetBits(GPIOB, GPIO_Pin_12 |GPIO_Pin_13 | GPIO_Pin_15);
        switch(GPIOA->IDR & 0x00f0)
        {
        case 0x0080:
            KeyValue=42;
            break;
        case 0x0040:
            KeyValue=57;
            break;
        case 0x0020:
            KeyValue=56;
            break;
        case 0x0010:
            KeyValue=55;
            break;
        }
        //第四排检测
        GPIO_SetBits(GPIOB,GPIO_Pin_15 );
        GPIO_ResetBits(GPIOB, GPIO_Pin_12 |GPIO_Pin_13 | GPIO_Pin_14);
        switch(GPIOA->IDR & 0x00f0)
        {
        case 0x0080:
            KeyValue=47;
            break;
        case 0x0040:
            KeyValue=7;
            break;
        case 0x0020:
            KeyValue=48;
            break;
        }
        if(KeyValue != 0)
        {
            judge = KeyState_4;//读取完成  跳转到state4状态
        }
        else
        {
            judge = KeyState_3;
        }
        break;

    case KeyState_4://按键松开之后调到state1
        GPIO_SetBits(GPIOB,GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15);
        if((GPIOA->IDR & 0x00f0)!=0x0000)//说明还没有松开
        {
            judge = KeyState_4;
            KeyValue = 0;
        }
        else
        {
            judge = KeyState_1;
            KeyValue = 0;
        }
        break;
    }
}
float Calculator(char a[])
{
    int i = 1, j, k, m, cnt = 0, t1 = 0, t2 = 0, t3 = 0;
    char nibo[10], zhan2[10];
    double x, n, l, z = 0, zhan3[10];
    typedef struct
    {
        double d1;
        int d2;
    } dd;
    typedef struct
    {
        dd data[10];
        int top;
    } zhan1;
    zhan1 *shu;
    shu = (zhan1 *)malloc(sizeof(zhan1));
    shu->top = 0;
    while (a[i] != '\0')
    {
        if (a[i] >= '0' && a[i] <= '9')
        {
            z = 0;
            j = i + 1;
            while (a[j] >= '0' && a[j] <= '9')
            {
                j++;
            }
            j--;
            for (k = i; k <= j; k++)
            {
                z = z * 10 + a[k] - '0';
            }
            j = j + 1;
            x = z;
            if (a[j] == '.')
            {
                l = 1;
                i = j + 1;
                j = i + 1;
                while (a[j] >= '0' && a[j] <= '9')
                {
                    j++;
                }
                j--;
                for (k = i; k <= j; k++)
                {
                    n = pow(0.1, l);
                    l = l + 1;
                    x = x + n * (a[k] - '0');
                }
                i = j + 1;
            }
            else
                i = j;
            shu->data[++shu->top].d1 = x;
            shu->data[shu->top].d2 = ++cnt;
            nibo[++t1] = '0' + shu->data[shu->top].d2;
            nibo[t1 + 1] = '\0';
        }
        else if (a[i] == '(')
        {
            zhan2[++t2] = a[i];
            i++;
        }
        else if (a[i] == ')')
        {
            j = t2;
            while (zhan2[j] != '(')
            {
                nibo[++t1] = zhan2[j];
                nibo[t1 + 1] = '\0';
                j--;
            }
            t2 = j - 1;
            i++;
        }
        else if (a[i] == '+')
        {
            while (t2 > 0 && zhan2[t2] != '(')
            {
                nibo[++t1] = zhan2[t2];
                nibo[t1 + 1] = '\0';
                t2--;
            }
            zhan2[++t2] = a[i];
            i++;
        }
        else if (a[i] == '-')
        {
            if (a[i - 1] == '$')
            {
                a[0] = '0';
                i = 0;
            }
            else if (a[i - 1] == '(')
            {
                a[i - 1] = '0';
                a[i - 2] = '(';
                i = i - 2;
                t2--;
            }
            else
            {
                while (t2 > 0 && zhan2[t2] != '(')
                {
                    nibo[++t1] = zhan2[t2];
                    nibo[t1 + 1] = '\0';
                    t2--;
                }
                zhan2[++t2] = a[i];
                i++;
            }
        }
        else if (a[i] == '*' || a[i] == '/')
        {
            while (zhan2[t2] == '*' || zhan2[t2] == '/' || zhan2[t2] == '^' || zhan2[t2] == '#')
            {
                nibo[++t1] = zhan2[t2];
                nibo[t1 + 1] = '\0';
                t2--;
            }
            zhan2[++t2] = a[i];
            i++;
        }
        else if (a[i] == '^' || a[i] == '#')
        {
            while (zhan2[t2] == '^' || zhan2[t2] == '#')
            {
                nibo[++t1] = zhan2[t2];
                nibo[t1 + 1] = '\0';
                t2--;
            }
            zhan2[++t2] = a[i];
            i++;
        }
    }
    while (t2 > 0)
    {
        nibo[++t1] = zhan2[t2];
        nibo[t1 + 1] = '\0';
        t2--;
    }
    j = 1;
    t3 = 0;
    while (j <= t1)
    {
        if (nibo[j] >= '0' && nibo[j] != '^' && nibo[j] != '#') //
        {
            for (i = 1; i <= shu->top; i++)
            {
                if ((int)(nibo[j] - '0') == shu->data[i].d2)
                {
                    m = i;
                    break;
                }
            }
            zhan3[++t3] = shu->data[m].d1;
        }
        else if (nibo[j] == '+')
        {
            zhan3[t3 - 1] = zhan3[t3 - 1] + zhan3[t3];
            t3--;
        }
        else if (nibo[j] == '-')
        {
            zhan3[t3 - 1] = zhan3[t3 - 1] - zhan3[t3];
            t3--;
        }
        else if (nibo[j] == '*')
        {
            zhan3[t3 - 1] = zhan3[t3 - 1] * zhan3[t3];
            t3--;
        }
        else if (nibo[j] == '/')
        {
            zhan3[t3 - 1] = zhan3[t3 - 1] / zhan3[t3];
            t3--;
        }
        else if (nibo[j] == '^')
        {
            zhan3[t3 - 1] = pow(zhan3[t3 - 1], zhan3[t3]);
            t3--;
        }
        else if (nibo[j] == '#')
        {
            zhan3[t3] = sqrt(zhan3[t3]);
        }
        j++;
    }
    free(shu);
    return zhan3[t3];
}

/*********************************************END OF FILE**********************/
