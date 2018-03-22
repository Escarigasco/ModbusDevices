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



int main(void)
{

    int error_checker=0;
    modbus_t *ctx;
    uint16_t tab_reg[2];
    uint16_t *inp_tab_reg;
    uint8_t *tab_bit;
    uint8_t *inp_tab_bit;
    int nPort =502;
    int rc;
    int i=0;
    int g=0;

	ctx = modbus_new_tcp("192.168.1.100", nPort);
	if (modbus_connect(ctx) == -1) {
        	fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        	modbus_free(ctx);
       	        return -1;
       }
       printf("connection achieved\n");

    //https://github.com/stephane/libmodbus - Readme with modbus functions descritpions
 
    while(1) { //(1) Start Monitoring

	    /*    for (i=0;i<15;i++){
		        rc = modbus_read_input_bits(ctx, i, 1, inp_tab_bit);
		        printf("Input bit %d: %d\n ",i,&inp_tab_bit);
                sleep(1);
	        }
        
	        for (i=10000;i<10015;i++){
	            rc = modbus_read_bits(ctx, i, 1, tab_bit);
	            printf("Bit %d: %d\n ",i,&tab_bit);
                sleep(1);
	            }
                                      
            for (i=30000;i<30015;i++){
	        rc = modbus_read_input_registers(ctx, i, 1, inp_tab_reg);
	        printf("Input register %d: %d\n ",i,&inp_tab_reg);
            sleep(1);
	        }*/
		const int reference_value = 1000;
		const int n_registers = 1;
        	for (i=40000;i<40015;i++){
	        	rc = modbus_read_registers(ctx, i, n_registers, tab_reg);
			if (rc != n_registers){
				fprintf(stderr, "Reading failed: %s\n", modbus_strerror(errno));
	               	        modbus_free(ctx);
        		        return -1;
			}
	        	printf("Register %d: %d\n ",i,tab_reg[0]);
			//sleep(1);
			if (tab_reg[0] < reference_value){
				sleep(1);
		        }
 
            //sleep(1);
	        }

	        if (rc == -1) {
	            fprintf(stderr, "%s\n", modbus_strerror(errno));
	            return -1;
	        }
 	}

modbus_close(ctx);
modbus_free(ctx); 
}

