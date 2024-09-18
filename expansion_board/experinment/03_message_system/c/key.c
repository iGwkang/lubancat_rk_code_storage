/*
*
*   file: key.c
*   update: 2024-09-12
*
*/

#include "key.h"

static int fd_key;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

volatile static int key_value = KEY_NORMAL;

/*****************************
 * @brief : 按键信号函数
 * @param : 接收到的信号编号
 * @return: none
*****************************/
static void sigio_key_func(int sig)
{
	struct input_event event;
	while (read(fd_key, &event, sizeof(event)) == sizeof(event))
	{   
        if (event.value)
        {
            pthread_mutex_lock(&lock);

            switch (event.code)
            {
                case 11:    // key1
                    //printf("key1 was pressed!\n");
                    key_value = KEY1_PRESSED;
                    break;
                case 2:     // key2
                    //printf("key2 was pressed!\n");
                    key_value = KEY2_PRESSED;
                    break;
                case 3:     // key3
                    //printf("key3 was pressed!\n");
                    key_value = KEY3_PRESSED;
                    break;
                default:
                    break;
            }

            pthread_mutex_unlock(&lock);
        }
	}
}

/*****************************
 * @brief : 按键初始化
 * @param : key_event 按键输入事件
 * @return: 0成功 -1失败
*****************************/
int key_init(const char *key_event)
{
    int	flags;

    fd_key = open(key_event, O_RDWR | O_NONBLOCK);    
    if (fd_key < 0)
    {
        fprintf(stderr, "can not open %s\n", key_event);
        return -1;
    }

    signal(SIGIO, sigio_key_func);                          
    fcntl(fd_key, F_SETOWN, getpid());                          
    flags = fcntl(fd_key, F_GETFL);                     
	fcntl(fd_key, F_SETFL, flags | FASYNC);     

    return 0;                
}

/*****************************
 * @brief : 获取按键值
 * @param : none
 * @return: 11 key1按下，12 key2按下，13 key3按下
*****************************/
int key_get_value()
{
    int temp = key_value;
    if(temp == KEY_NORMAL)
        return temp;

    pthread_mutex_lock(&lock);
    key_value = KEY_NORMAL;
    pthread_mutex_unlock(&lock);

    return temp;
}

/*****************************
 * @brief : 按键反初始化
 * @param : none
 * @return: none
*****************************/
void key_exit()
{
    if(fd_key > 0)
        close(fd_key);
}