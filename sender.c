#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "sender.h"
#include <nanomsg/nn.h>
#include <unistd.h>
#include <nanomsg/pipeline.h>


void sendMessage(struct NanoSenderSession* this, char *msg)
{
  int sz_msg = strlen (msg); // '\0' too
  int bytes = nn_send (this->sock, msg, sz_msg, NN_DONTWAIT);
  printf("send ok\n");
  return;
  //assert (bytes == sz_msg);
  //return nn_shutdown (sock, 0);
}
int connectToSock(struct NanoSenderSession* this){
  //this->url=url;
  printf("connecting...\n");
  int sock=nn_socket(AF_SP,NN_PUSH);
  this->sock=sock;
  //assert(sock>=0);
  if(sock<0){
    return -1;
  }
  //assert(strlen(this->url)>0);
  if(strlen(this->url)<=0){
    return -2;
  }
  //assert(nn_connect(sock, this->url) >= 0);
  if(nn_connect(sock, this->url) < 0){
    return -3;
  }
  return sock;
}
int disconnectSock(struct NanoSenderSession* this){
  return nn_shutdown(this->sock,0);
}
struct NanoSenderSession* newNanoSenderSession(char* url){
  struct NanoSenderSession *nss;
  nss=malloc(sizeof(struct NanoSenderSession));
  nss->url=url;
  nss->sendMessage=sendMessage;
  nss->connect=connectToSock;
  nss->disconnect=disconnectSock;
  //nss->this=nss;
  return nss;
}



// int main (const int argc, const char **argv)
// {
//   //char* buf1,buf2,buf3;
//   printf("%s\n",argv[1]);
//   nss=newNanoSenderSession(argv[1]);
//   nss->connect(nss);
//   printf("connect ok\n");
//   // buf1=readFile("./text.txt",450);
//   // buf2=readFile("./text.txt",4550);
//   // buf3=readFile("./text.txt",45550);
//   readFile("./text.txt");
//   int m=0;
//   if(signal(SIGINT,sig_handler)==SIG_ERR)
//     printf("\ncan not catch SIGINT\n");
//    while(1){
//   //   if(m%3==0){
//       //printf("sending buffer 1:---%d\n",strlen(buf1));
//       m++;
//       nss->sendMessage(nss,buf1);
//       //sleep(30);
//       m++;
//       nss->sendMessage(nss,buf2);
//       //sleep(30);
//       m++;
//       nss->sendMessage(nss,buf3);
//       //sleep(30);
//     //}else ifs(m%3==1){
//        //printf("sending buffer 2:---%d\n",strlen(buf2));
//       //sleep(10);
//       //nss->sendMessage(nss,buf2);
//     // //}else{
//     //   printf("sending buffer 3:---%d\n",strlen(buf3));
//       //nss->sendMessage(nss,buf3);
//     // //}
//     // m++;
//     //sleep(30);
//       printf("%d msg has sended\n",m );
//   }
//   //return nss->disconnect(nss);
// }
