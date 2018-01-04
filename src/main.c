
#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void INThandler(){
        exit(0);
}

char keymap[55] = {
0,
0x1b, //Esc
'1',
'2',
'3',
'4',
'5',
'6',
'7',
'8',
'9',
'0',
'-',
'=',
8, //backspace
9, //tab
'q',
'w',
'e',
'r',
't',
'y',
'u',
'i',
'o',
'p',
'[',
']',
13, //enter
255, //caps
'a',
's', 
'd',
'f',
'g',
'h',
'j',
'k',
'l',
';',
0x27,
0,
254, //shift
0x5C,
'z',
'x',
'c',
'v',
'b',
'n',
'm',
',',
'.',
'/',
254
};

int main()
{
        char devname[] = "/dev/input/event0";
        int device = open(devname, O_RDONLY);
        struct input_event ev;

        signal(SIGINT, INThandler);

        while(1)
        {
                read(device,&ev, sizeof(ev));
                if(ev.type == 1 && ev.value == 1){
                        printf("Key: %d State: %i key %c \n",ev.code,ev.value,keymap[ev.code] );
                }
        }
}
