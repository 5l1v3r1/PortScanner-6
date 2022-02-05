#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>
// =======================================================================================
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
// =======================================================================================
int main(int argc , char **argv){
	struct hostent *host;
	int err, i , sock ,port;
	char hostname[100];
	struct sockaddr_in sa;
// =======================================================================================
	printf(GRN"==============="RED"["BLU" Poet Scanner"RED "]"GRN"===============\n");
	printf(GRN"Enter hostname or IP \n"RED">>  "YEL);
	fgets(hostname , sizeof(hostname), stdin);
	printf(GRN"Enter port \n"RED">>  "YEL);
	scanf("%d", &port);
// =======================================================================================
	strncpy((char*)&sa , "" , sizeof sa);
	sa.sin_family = AF_INET;
// =======================================================================================
	printf(GRN"["RED"-"GRN"]"BLU"Starting"RED" ...\n");
	if(isdigit(hostname[0])){
		sa.sin_addr.s_addr = inet_addr(hostname);
	}else if( (host = gethostbyname(hostname)) != 0){
		strncpy((char*)&sa.sin_addr , (char*)host->h_addr , sizeof sa.sin_addr);
	}else{
		herror(hostname);
		exit(2);
	}

	printf(GRN"["RED"-"GRN"]"YEL"scan report for "GRN"%s\n" ,hostname );
// =======================================================================================	
	sa.sin_port = htons(port);
	sock = socket(AF_INET , SOCK_STREAM , 0);
// =======================================================================================		
	if(sock < 0) {
		perror("\nSocket");
		exit(1);
	}
	err = connect(sock , (struct sockaddr*)&sa , sizeof sa);	
	if( err < 0 ){
		printf(RED"%s %s %s\r" , hostname , port, strerror(errno));
		fflush(stdout);
	}else{
		printf(BLU"%d "RED"open\n",  port);
	}
// =======================================================================================
	close(sock);
	printf("\r");
	fflush(stdout);
	return(0);
// =======================================================================================
}