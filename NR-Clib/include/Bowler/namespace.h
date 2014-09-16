/*
 * namespace.h
 *
 *  Created on: Aug 15, 2010
 *      Author: hephaestus
 */

#ifndef NAMESPACE_H_
#define NAMESPACE_H_

#define USE_LINKED_LIST_NAMESPACE

typedef BOOL packetEventCallback(BowlerPacket *);
typedef BOOL asyncEventCallback(BowlerPacket *,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *));

typedef struct  _RPC_LIST{
	//This is the bowler method for this RPC
	BYTE bowlerMethod;
	//This is the 4 byte code for of the RPC
	const char * rpc;
	//This is the callback function pointer for execution of the method
	packetEventCallback * callback;
        //This is the array of argument data types
	const char * arguments;
        //This is the bowler method for this RPC
	BYTE responseMethod;
        //This is the array of argument data types
	const char * responseArguments;
        
	//This is the linked list field
	struct _RPC_LIST * next;
} RPC_LIST;

typedef struct _NAMESPACE_LIST{
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
RPC_LIST * getRpcByIndex(NAMESPACE_LIST * namespace,BYTE index);
void addNamespaceToList(NAMESPACE_LIST * newNs);
void addRpcToNamespace(NAMESPACE_LIST * namespace,RPC_LIST * rpc );
NAMESPACE_LIST * getNamespaceAtIndex(int index);
BYTE getNumberOfNamespaces();
BYTE getNumberOfRpcs(int namespaceIndex);

void RunNamespaceAsync(BowlerPacket *Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet));


//bcs.safe
#define SAFE					0x65666173 // 'safe'  Get/Set the safe-mode parameters

typedef struct  _NAMESPACE{
		unsigned char len;
		const unsigned char * name;
} NAMESPACE;

typedef struct  _NAMESPACE_SET{
		unsigned char numNamespaces;
		NAMESPACE  names[8];
} NAMESPACE_SET;

#endif /* NAMESPACE_H_ */
