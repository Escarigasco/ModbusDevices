#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <modbus/modbus.h>
#include <math.h>
#include<pthread.h>



int main(int argc, char **argv)
{





    int error_checker=0;


    const int baud=19200;
    const char parity='N';
    const int stop_bit=1;
    const int no_of_bit=8;


    int i=0;
    int g=0;

   

    //https://github.com/stephane/libmodbus - Readme with modbus functions descritpions
    /***Modbus Master Init***/
    modbus_t* ctx;
    ctx = ctx = modbus_new_tcp("192.168.1.4", 502);
 
    
     
    /***(1) Start Monitoring - check operating conditions***/

    while(1) { //(1) Start Monitoring
 
	modbus_t *ctx;
	uint16_t tab_reg[1]={0};
	uint16_t inp_tab_reg[1]={0};
	uint8_t tab_bit[1]={0};
	uint8_t inp_tab_bit[1]={0};
	int nPort = 80;
	int rc;
	int i=0;

	ctx = modbus_new_tcp("127.0.0.1", nPort);
	if (modbus_connect(ctx) == -1) {
	    fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
	    modbus_free(ctx);
	    return -1;
	}
	for (i=0;i<100;i++){
		rc = modbus_read_registers(ctx, i, 1, tab_reg);
		rc = modbus_read_input_bits(ctx, i, 1, inp_tab_bit);
		rc = modbus_read_input_registers(ctx, i, 1, inp_tab_reg);
		rc = modbus_read_bits(ctx, i, 1, tab_bit);
		printf("Input bit %d: %d\n ",i,&inp_tab_bit);
		printf("Bit %d: %d\n ",i,&tab_bit);
		printf("Input register %d: %d\n ",i,&inp_tab_reg);
		printf("Input register %d: %d\n ",i,&tab_reg);

	}

	if (rc == -1) {
	    fprintf(stderr, "%s\n", modbus_strerror(errno));
	    return -1;
	}

	for (i=0; i < rc; i++) {
	    printf("reg[%d]=%d (0x%X)\n", i, tab_reg[i], tab_reg[i]);
	}


      
 	}

	modbus_close(ctx);
	modbus_free(ctx); 
}


