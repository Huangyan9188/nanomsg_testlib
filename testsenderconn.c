#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "sender.h"
// #include <nanomsg/nn.h>
// #include <unistd.h>
// #include <nanomsg/pipeline.h>

static char* buf1;
static char* buf2;
static char* buf3;
static struct NanoSenderSession* nss;

void readFile(char* filepath){
  printf("reading file\n");
  //printf("length:%d\n",length );
  FILE *fp1;
  //char* buf;
  buf1=(char*)malloc(450*sizeof(char));
  buf2=(char*)malloc(4500*sizeof(char));
  buf3=(char*)malloc(45000*sizeof(char));
  //char buf[45551];
  fp1=fopen(filepath,"r");
  printf("opening %s\n",filepath );
  fgets(buf1,449,fp1);
  fgets(buf2,4449,fp1);
  fgets(buf3,44449,fp1);
  printf("get out all the byte\n");
  //buf[length-1]='\0';

  fclose(fp1);
  //return buf;
}


void sig_handler(int signo){
  if(signo==SIGINT){
    printf("free the buffers used\n");
    free(buf1);
    free(buf2);
    free(buf3);
    nss->disconnect(nss);
  }
  exit(0);
}

int main(int argc, char const *argv[])
{
	/* code */
  int totalconn=0;
  int totaldisconn=0;
  int successconn=0;
  int successdisconn=0;
  int errconn=0;
  int errdisconn=0;

	struct NanoSenderSession* nss;
	//nss=newNanoSenderSession(argv[1]);
  nss=newNanoSenderSession("ipc:///tmp/libra_imu.ipc");
  while(1){
    if(nss->connect(nss)<0){
      printf("Error for connecting\n");
      //totalconn++;
      errconn++;
    }else{
     // totalconn++
      successconn++;
      printf("success connect\n" );
    }
    totalconn++;
    usleep(500);
    if(nss->disconnect(nss)==-1){
      printf("Error for disconnecting\n");
      printf("%s\n",strerror(errno));
      errdisconn++;
    }else{
      printf("success disconnect sock\n");
      successdisconn++;
    }
    totaldisconn++;
    printf("%d,%d,%d,%d,%d,%d\n",totalconn,totaldisconn,successconn,successdisconn,errconn,errdisconn);
    usleep(500);
  }
	//if(nss->connect(nss)<0)
	//readFile("./text.txt");


	 //  int m=0;
  // if(signal(SIGINT,sig_handler)==SIG_ERR)
  //   printf("\ncan not catch SIGINT\n");
  //  while(1){
  // //   if(m%3==0){
  //     //printf("sending buffer 1:---%d\n",strlen(buf1));
  //     m++;
  //     nss->sendMessage(nss,buf1);
  //     sleep(3);
  //     m++;
  //     nss->sendMessage(nss,buf2);
  //     sleep(3);
  //     m++;
  //     nss->sendMessage(nss,buf3);
  //     sleep(3);
  //   //}else ifs(m%3==1){
  //      //printf("sending buffer 2:---%d\n",strlen(buf2));
  //     //sleep(10);
  //     //nss->sendMessage(nss,buf2);
  //   // //}else{
  //   //   printf("sending buffer 3:---%d\n",strlen(buf3));
  //     //nss->sendMessage(nss,buf3);
  //   // //}
  //   // m++;
  //   //sleep(30);
  //     printf("%d msg has sended\n",m );
  // }
  //return nss->disconnect(nss);
  return 0;
}
