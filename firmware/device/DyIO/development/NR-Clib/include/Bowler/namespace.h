/*
 * namespace.h
 *
 *  Created on: Aug 15, 2010
 *      Author: hephaestus
 */

#ifndef NAMESPACE_H_
#define NAMESPACE_H_
#include <stdio.h>

//#define USE_LINKED_LIST_NAMESPACE

typedef BYTE packetEventCallback(BowlerPacket *);
typedef BYTE asyncEventCallback(BowlerPacket *);

typedef struct __attribute__((__packed__)) _RPC_LIST{
	//This is the bowler method for this RPC
	BYTE bowlerMethod;
	//This is the 4 byte code for of the RPC
	unsigned long rpc;
	//This is the callback function pointer for execution of the method
	packetEventCallback * callback;
	//This is the linked list field
	struct _RPC_LIST * next;
} RPC_LIST;

typedef struct __attribute__((__packed__)) _NAMESPACE_LIST{
	//This is the string that identifies the names pace
	const char *  namespaceString;
	//This is the linked list of the RPC's
	RPC_LIST * rpcSet;
	//This is the callback function pointer for checking for async.
	asyncEventCallback * asyncEventCheck;
	//This is the linked list field
	struct _NAMESPACE_LIST * next;
} NAMESPACE_LIST;

RPC_LIST * getRpcByID(NAMESPACE_LIST * namespace,unsigned long  rpcId, BYTE bowlerMethod);
void addNamespaceToList(NAMESPACE_LIST * newNs);
void addRpcToNamespace(NAMESPACE_LIST * namespace,RPC_LIST * rpc );
NAMESPACE_LIST * getNamespaceAtIndex(int index);
BYTE getNumberOfNamespaces();


//bcs.safe
#define SAFE					0x65666173 // 'safe'  Get/Set the safe-mode parameters

typedef struct __attribute__((__packed__)) _NAMESPACE{
		unsigned char len;
		const unsigned char * name;
} NAMESPACE;

typedef struct __attribute__((__packed__)) _NAMESPACE_SET{
		unsigned char numNamespaces;
		NAMESPACE  names[8];
} NAMESPACE_SET;

#endif /* NAMESPACE_H_ */
