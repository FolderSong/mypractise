#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> 

int main(void)
{
    int pid = 0;
    int status = 0;

    #if 0
    printf("entering main process---\n");
    ret = execl("/bin/bash","bash", "-c","http --version",NULL);
    printf("exiting main process with %d----\n",ret );
    #endif

	pid = vfork();
	if( pid < 0 )
	{
		printf( "(out)vfork error\n" );
		goto LAB_ERR;
	}

	if( pid == 0 )
	{
        printf("entering child process---\n");
		if( execl("/bin/bash","bash", "-c","http --version",(char*)0 ) < 0 )
		{
			printf( "(out)Err on execl %s\n", strerror(errno) );
			_exit( -1 );
		}
	}
	else
	{
        printf("entering main  process---\n");
		while( waitpid(pid, &status, 0) < 0 )
		{
			printf( "waitpid error pid:%d %s\n", pid, strerror(errno));
			goto LAB_ERR;
		}
	}
	
	return 0;
LAB_ERR:
	return -1;
}