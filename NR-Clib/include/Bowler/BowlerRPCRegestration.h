/*
 * BowlerRPCRegestration.h
 *
 *  Created on: Sep 29, 2010
 *      Author: hephaestus
 */

#ifndef BOWLERRPCREGESTRATION_H_
#define BOWLERRPCREGESTRATION_H_

#define MAX_NUM_RPC 15
uint8_t addRPC(uint8_t method,const char * rpc,void( *_callback)(BowlerPacket*));
#if !defined(USE_LINKED_LIST_NAMESPACE)
uint8_t setMethodCallback(uint8_t method,BYTE( *_callback)(BowlerPacket*));
#endif

typedef void rpcCallback(BowlerPacket *);

typedef struct  _RPC_HANDLER{
		unsigned long rpc;
		rpcCallback * callback;
} RPC_HANDLER;


typedef struct  _RPC_HANDLER_SET{
		unsigned char numRPC;
		RPC_HANDLER handlers[MAX_NUM_RPC];
} RPC_HANDLER_SET;


typedef uint8_t methodCallback(BowlerPacket *);

typedef struct  _METHOD_HANDLER{
		unsigned char set;
		methodCallback * callback;
} METHOD_HANDLER;

#endif /* BOWLERRPCREGESTRATION_H_ */
