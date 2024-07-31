#include <iostream>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <string>
using namespace std;
int main(int argc,char** argv )
{
    if(argc<2){
        cout<<"please enter ./http_server port"<<endl;
        exit(1);
    }
    sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    addr.sin_family=AF_INET;
    addr.sin_port=htons(stoi(argv[1]));
   addr.sin_addr.s_addr=INADDR_ANY;

    bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));

    listen(sockfd,5);

    sockaddr_in readdr;
    memset(&readdr,0,sizeof(readdr));
    socklen_t len=sizeof(readdr);
    while(1){
        int refd = accept(sockfd, (struct sockaddr *)&readdr, &len);
        cout<<refd<<endl;
        if(refd<0){
            perror("accept");
            exit(1);
        }
        string buf;
        buf+="HTTP/1.0 200 OK\n";
        buf+="Content-Type: text/html\n";
        buf+="\n";
        buf+="html\n";
        buf+="<h1> hello world </h1>";
        write(refd,buf.c_str(),buf.size());
    }
    return 0;
}