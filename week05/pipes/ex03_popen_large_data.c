// Passing Large Data
// To avoid having to declare a very large buffer, we can just use 
// multiple fread or fwrite calls and process the data in parts


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
    FILE *read_fp;
    char buffer[BUFSIZ + 1];
    int chars_read;
    memset(buffer, '\0', sizeof(buffer));
    read_fp = popen("ps -ax | grep '/usr/sbin'", "r");
    if (read_fp != NULL) {
        chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
        while (chars_read > 0) {
            buffer[chars_read - 1] = '\0';
            printf("Reading:-\n %s\n", buffer);
            chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
        }
        pclose(read_fp);
        exit(EXIT_SUCCESS);
        }
    exit(EXIT_FAILURE);
}

/*
localhost:/home/alphapeeler/OsSp25/week05 # gcc ex03_popen_large_data.c -o ex03_popen_large_data.o
localhost:/home/alphapeeler/OsSp25/week05 # ./ex03_popen_large_data.o 
Reading:-
   590 ?        Ss     0:00 /usr/sbin/haveged -w 1024 -v 0 -F
  642 ?        Ssl    0:04 /usr/sbin/NetworkManager --no-daemon
  646 ?        Ssl    0:00 /usr/sbin/irqbalance --foreground
  747 ?        Sl     0:01 /usr/sbin/VBoxService --pidfile /var/run/vboxadd-service.sh
  767 ?        Ssl    0:00 /usr/sbin/ModemManager
  858 ?        S      0:00 /usr/sbin/chronyd
  884 ?        Ss     0:00 /usr/sbin/cron -n
 2209 pts/1    S+     0:00 sh -c -- ps -ax | grep '/usr/sbin'
 2211 pts/1    S+     0:00 grep /usr/sbin
localhost:/home/alphapeeler/OsSp25/week05 # 

*/
