#include <assert.h>

#include <stdio.h>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>


// int recv_name(int sock, const char *name)
// {
//   char *buf = NULL;
//   int result = nn_recv (sock, &buf, NN_MSG, 0);
//   if (result > 0)
//     {
//       printf ("%s: RECEIVED \"%s\"\n", name, buf);
//       nn_freemsg (buf);
//     }
//   return result;
// }

int main (const int argc, const char **argv)
{
	int sock=nn_socket(AF_SP,NN_PULL);
	assert(sock>=0);
	
	nn_bind(sock, argv[1]);
	//assert(nn_bind(sock, argv[1]) >= 0);
	while(1){
		char *buf=NULL;
		printf("getting the msg\n");
		int bytes=nn_recv(sock,&buf,NN_MSG,0);
		printf("get the msg\n");
		assert(bytes>=0);
		printf("get %d bytes\n",bytes);
		nn_freemsg(buf);
	}
	return 0;
}