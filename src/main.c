#include "keymap.h"
#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h> 
#include <locale.h>
//extern char keymap[55][2];

int shift = 0;
int keycode;

void exportOut( int keycode, int shift );
int lang( );
void INThandler(){
        exit(0);
}

int main()
{
        char devname[] = "/dev/input/event0";
        int device = open(devname, O_RDONLY);
        struct input_event ev;

        signal(SIGINT, INThandler);

        while(1)
        {
                read(device,&ev, sizeof(ev));
                if(ev.type == 1 && ev.value >= 1)
                {
                keycode = ev.code;
                    if( keycode == 42 || keycode == 54 )
                    {
                        shift = 1;
                        do  
                        {
                            read(device,&ev, sizeof(ev));
                            keycode = ev.code;
                            if(ev.type == 1 && ev.value >= 1 ){
                                exportOut( keycode, shift );
                            }
                        } while(    !(( keycode == 42 && ev.value == 0 )||( keycode == 54 && ev.value == 0 )) ); 
                        shift = 0;
                    }
                    else
                        exportOut( keycode, shift ); 
                }
        }
   // return 0;
}
void exportOut( int keycode, int shift )
{
    if( lang() == '0')
    {
        printf("Key: %s \n",keymap[keycode][shift] );
    }
    else
    {
        printf("Key: %s \n",keymap_ru[keycode][shift] );
    }
}
int lang() {
    int c;
    //~ pp - pipe pointer
    FILE *pp;
    extern FILE *popen();
 
    if ( !(pp=popen("xset -q | grep LED | awk '{print $10}' | cut -c 5", "r")) )
        return 10;
 
    while ( (c=fgetc(pp)) != EOF ) {
        return c;
        //putc(c, stdout);
//~ fflush нужна, чтобы не возникало задержки из-за буферизации
        fflush(pp);
    }
    
    pclose(pp);
    return 10;
/*
FILE *popen_result;
    char buff;
    popen_result = popen("xset -q | grep LED | awk '{print $10}' | cut -c 5", "r");
    if(!popen_result){
            printf("Can't execute command\n");
    }
    while( popen_result!=NULL){
        return buff;
    }
    pclose(popen_result);
*/
}
