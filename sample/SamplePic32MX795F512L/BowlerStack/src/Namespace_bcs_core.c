#include "Bowler/Bowler.h"

/**
 * Initializes core and returns a pointer to the namespace list
 */

BOOL _nms(BowlerPacket * Packet);
BOOL _png(BowlerPacket * Packet);

#define USE_LINKED_LIST_NAMESPACE

#if defined(USE_LINKED_LIST_NAMESPACE)
const char coreName[] = "bcs.core.*;0.3;;";


static RPC_LIST bcsCore_nms={	BOWLER_GET,
                                "_nms",
                                &_nms,
                                ((const char [2]){  BOWLER_I08,
                                                    0}),// Calling arguments
                                BOWLER_POST,// response method
                                ((const char [3]){  BOWLER_ASCII,
                                                    BOWLER_I08,
                                                    0}),// Response arguments
                                NULL //Termination
};
static RPC_LIST bcsCore_png={	BOWLER_GET,
                                "_png",
                                &_png,
                                NULL,// Calling arguments
                                BOWLER_POST,// response method
                                NULL,// Response arguments
                                NULL //Termination
};

static NAMESPACE_LIST bcsCore ={	coreName,// The string defining the namespace
                                        NULL,// the first element in the RPC string
                                        NULL,// no async for this namespace
                                        NULL// no initial elements to the other namesapce field.
};



BYTE getNumberOfNamespaces(){
	int i=1;
	NAMESPACE_LIST * tmp = getBcsCoreNamespace();

	while(tmp->next != NULL){
		tmp = tmp->next;
		i++;
	}
	return i;
}

BYTE getNumberOfRpcs(int namespaceIndex){
	int i=1;
	RPC_LIST * tmp = getNamespaceAtIndex(namespaceIndex)->rpcSet;
        if(tmp == NULL){
            return 0;
        }
	while(tmp->next != NULL){
		tmp = tmp->next;
		i++;
	}
	return i;
}

NAMESPACE_LIST * getNamespaceAtIndex(int index){
    if(index>=getNumberOfNamespaces()){
        return NULL;
    }
    int i=0;
    NAMESPACE_LIST * tmp = getBcsCoreNamespace();
    while(i != index){
            if(tmp->next !=NULL){
                    tmp = tmp->next;
                    i++;
            }else{
                    //walked off the end of the list
                    return NULL;
            }
    }
    return tmp;
}


BOOL _png(BowlerPacket * Packet){
	Packet->use.head.Method = BOWLER_POST;
	Packet->use.head.RPC = GetRPCValue("_png");
	Packet->use.head.DataLegnth = 4;
	return TRUE;
}

BOOL _nms(BowlerPacket * Packet){
	if(Packet->use.head.DataLegnth==4){
		Packet->use.head.DataLegnth=5;
		Packet->use.head.Method = BOWLER_POST;
		Packet->use.data[0]=getNumberOfNamespaces();
		//println("Have ");
		//p_int(namespace.numNamespaces);
		//println(" namespaces");
	}else if(Packet->use.head.DataLegnth==5){
		if(Packet->use.data[0]<getNumberOfNamespaces()){
			//print("\nSending: ");
			Packet->use.head.DataLegnth=4;
			Packet->use.head.Method = BOWLER_POST;
			//NAMESPACE tmp = namespace.names[Packet->use.data[0]];

			NAMESPACE_LIST * tmpList =getNamespaceAtIndex(Packet->use.data[0]);

			//print((char *)tmp.name);
			unsigned char i=0;
			while(tmpList->namespaceString[i]!='\0'){
				Packet->use.data[i]=tmpList->namespaceString[i];
				Packet->use.head.DataLegnth++;
				i++;
			}
                        Packet->use.data[i++] = 0;//null terminate the string
                        Packet->use.head.DataLegnth++;
                        Packet->use.data[i++] = getNumberOfNamespaces();//Append the number of namespaces
                        Packet->use.head.DataLegnth++;
		}else{
			ERR(Packet,0,5);
		}
	}else{
		ERR(Packet,0,4);
	}
	return TRUE;
}

void addRpcToNamespace(NAMESPACE_LIST * namespace,RPC_LIST * rpc ){
	if(namespace ==NULL || rpc == NULL){
		setPrintLevelErrorPrint();
		println_E("Can not add null RPC or Null namespace");
		while(1);
	}
	rpc->next=NULL;
	if(namespace->rpcSet == NULL){
		namespace->rpcSet = rpc;
		return;
	}
	RPC_LIST * tmp = namespace->rpcSet;
	do{
		if (tmp == rpc){
			//this pointer has already been added
			return;
		}
		if(tmp->next != NULL)
			tmp=tmp->next;
	}while(tmp->next != NULL);

	tmp->next = rpc;

}

void addNamespaceToList(NAMESPACE_LIST * newNs){
	if(newNs ==NULL ){
		setPrintLevelErrorPrint();
		println_E("Can not add null RPC or Null namespace");
		while(1);
	}
	newNs->next=NULL;

	NAMESPACE_LIST * tmp = getBcsCoreNamespace();
	do{
		if(tmp == newNs){
			//this namespace is already regestered
			return;
		}
		if(tmp->next != NULL)
			tmp = tmp->next;
	}while(tmp->next != NULL);

	tmp->next = newNs;
}


RPC_LIST * getRpcByID(NAMESPACE_LIST * namespace,unsigned long  rpcId, BYTE bowlerMethod){
	if(namespace == NULL)
		return NULL;
	RPC_LIST * rpc =  namespace->rpcSet;
	//null check
	if(rpc !=NULL){
		//Loop over the RPC list looking for a match to the RPC
		do{
			if(		rpcId			== 	GetRPCValue((char*)rpc->rpc) &&
					bowlerMethod	==	rpc->bowlerMethod ){
				//Found matching RPC and Method to parse
				return rpc;
			}
			//null check and move to the next RPC
			rpc= rpc->next;
		}while(rpc != NULL );
	}
	return NULL;
}

RPC_LIST * getRpcByIndex(NAMESPACE_LIST * namespace,BYTE index){
	if(namespace == NULL)
		return NULL;
	RPC_LIST * rpc =  namespace->rpcSet;
        int iterator = 0;
	//null check
	if(rpc !=NULL){
		//Loop over the RPC list looking for a match to the RPC
		do{
			if(iterator++ ==index ){
				//Found matching RPC and Method to parse
				return rpc;
			}
			//null check and move to the next RPC
			rpc= rpc->next;
		}while(rpc != NULL );
	}
	return NULL;
}

void RunNamespaceAsync(BowlerPacket *Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
    if(pidAsyncCallbackPtr != NULL){
        NAMESPACE_LIST * tmp = getBcsCoreNamespace();
	do{
            if(tmp->asyncEventCheck != NULL){
                tmp->asyncEventCheck(Packet,pidAsyncCallbackPtr);
            }
            if(tmp->next != NULL)
               tmp = tmp->next;
            else{
                tmp=NULL;
            }
	}while(tmp != NULL  );
    }
}

static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * getBcsCoreNamespace(){
	if(!namespcaedAdded){
            namespcaedAdded =TRUE;
            addRpcToNamespace(&bcsCore,& bcsCore_png);
            addRpcToNamespace(&bcsCore,& bcsCore_nms);
	}
	return &bcsCore;
}

#endif
