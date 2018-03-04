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



modbus_mapping_t *mb_mapping;
pthread_t tid[2];


void update_modbus_server(void)
	{
	uint16_t i;
	uint8_t bit=1;
	

	for(i=0; i<99; i++)
			{
					mb_mapping->tab_input_bits[i]=1;
					mb_mapping->tab_bits[i] = 1;
					mb_mapping->tab_registers[i]=i;
					mb_mapping->tab_input_registers[i]=i;
			}


	}



void* modbus_comms(void *arg)
	{

	int socket;
	modbus_t *ctx;
	int rc;
	int nPort = 88;
	uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];

	printf("Waiting for TCP connection on Port %i \n",nPort);
	ctx = modbus_new_tcp("127.0.0.1", nPort);
	printf("Context Created");
	socket = modbus_tcp_listen(ctx, 1);
	modbus_tcp_accept(ctx, &socket);
	printf("TCP connection started!\n");

	while(1)
			{

			rc = modbus_receive(ctx, query);
			if (rc >= 0)
					
					modbus_reply(ctx, query, rc, mb_mapping);
					
			else
					{
					// Connection closed by the client or server
					printf("Con Closed.\n");
					modbus_close(ctx); // close
					// immediately start waiting for another request again
					modbus_tcp_accept(ctx, &socket);
					}

			}
	printf("Quit the loop: %s\n", modbus_strerror(errno));
	modbus_mapping_free(mb_mapping);
	close(socket);
	modbus_free(ctx);

	}



int main(void)
	{


	int err;
	
	//keep this
	mb_mapping = modbus_mapping_new(100,100,100,100);
	if (mb_mapping == NULL)
			{
			fprintf(stderr, "Failed to allocate the mapping: %s\n", modbus_strerror(errno));
			return -1;
			}
	update_modbus_server();
	err = pthread_create(&(tid[0]), NULL, &modbus_comms, NULL);
	if (err != 0)
			{
			printf("\n can't create thread Modbus :[%s]", strerror(err));
			}
	



	pthread_join(tid[0], NULL);


	modbus_mapping_free(mb_mapping);

	return 0;
	}

