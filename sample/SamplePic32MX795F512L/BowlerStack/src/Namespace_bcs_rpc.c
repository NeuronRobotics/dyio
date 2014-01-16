#include "Bowler/Bowler.h"



static const char rpcNSName[]   = "bcs.rpc.*;0.3;;";


BOOL _rpc(BowlerPacket * Packet){
	Packet->use.head.Method = BOWLER_POST;
	Packet->use.head.RPC = GetRPCValue("_rpc");
        int index = 0;
        int nsIndex = Packet->use.data[index++];
        int rpcIndex = Packet->use.data[index++];
        Packet->use.data[index++] = getNumberOfRpcs(nsIndex);
        RPC_LIST * rpc = getRpcByIndex(getNamespaceAtIndex(nsIndex),rpcIndex);
        if(rpc == NULL){
            ERR(Packet,0,9);
            return FALSE;
        }
        UINT32_UNION rpcValue;
        rpcValue.Val = GetRPCValue((char*)rpc->rpc);
        int i;
        for(i=0;i<4;i++){
            Packet->use.data[index++] = rpcValue.v[i];
        }
        
        Packet->use.head.DataLegnth = 4+index;
	return TRUE;
}
BOOL _rpcArgs(BowlerPacket * Packet){
	Packet->use.head.Method = BOWLER_POST;
	Packet->use.head.RPC = GetRPCValue("args");
        int index = 0;
        int nsIndex = Packet->use.data[index++];
        int rpcIndex = Packet->use.data[index++];

        RPC_LIST * rpc = getRpcByIndex(getNamespaceAtIndex(nsIndex),rpcIndex);
        if(rpc == NULL){
            ERR(Packet,0,10);
            return FALSE;
        }
        //UINT32_UNION rpcValue;
        //rpcValue.Val = GetRPCValue((char*)rpc->rpc);
        int i;
        Packet->use.data[(index++)] = rpc->bowlerMethod;
        int argNumIndex = index;
        Packet->use.data[(index++)] = 0;// place holder for number of arguments
        if(rpc->arguments != NULL){
           //add non NULL arguments
            i=0;
            while(rpc->arguments[i]!= 0){
                Packet->use.data[(index++)]= rpc->arguments[i++];
                Packet->use.data[argNumIndex]++;
            }
        }
        //Packet->use.data[(index++)] = 0;

        Packet->use.data[(index++)] = rpc->responseMethod;
        argNumIndex = index;
        Packet->use.data[(index++)] = 0;// place holder for number of arguments
        if(rpc->responseArguments != NULL){
           //add non NULL arguments
            i=0;
            while(rpc->responseArguments[i]!=0){
                Packet->use.data[(index++)]= rpc->responseArguments[i++];
                Packet->use.data[argNumIndex]++;
            }
        }
        //Packet->use.data[(index++)] = 0;

        Packet->use.head.DataLegnth = 4+index;
	return TRUE;
}
//Get RPC's
static RPC_LIST bcsRpc__RPC={	.bowlerMethod=BOWLER_GET,
                                .rpc="_rpc",
                                .callback=&_rpc,
                                .arguments=((const char [3]){BOWLER_I08,
                                                            BOWLER_I08,
                                                            0}),// Calling arguments
                                .responseMethod=BOWLER_POST,// response method
                                .responseArguments=( (const char [5]){BOWLER_I08,
                                                                    BOWLER_I08,
                                                                    BOWLER_I08,
                                                                    BOWLER_ASCII,
                                                                    0}),// Response arguments
                                .next = NULL //Termination
};
//Get RPC's
static RPC_LIST bcsRpc_ARGS={	.bowlerMethod=BOWLER_GET,
                                .rpc="args",
                                .callback=&_rpcArgs,
                                .arguments=((const char [3]){BOWLER_I08,//namespace index
                                                            BOWLER_I08,//rpc index
                                                            0}),// Calling arguments
                                .responseMethod=BOWLER_POST,// response method
                                .responseArguments=((const char [7]){ BOWLER_I08,//namespace index
                                                                    BOWLER_I08,//rpc index
                                                                    BOWLER_I08,//Downstream method
                                                                    BOWLER_STR,//downstream arguments
                                                                    BOWLER_I08,//upstream method
                                                                    BOWLER_STR,//upstream arguments
                                                                    0}),// Response arguments
                                .next = NULL //Termination
};


static NAMESPACE_LIST bcsRpc ={	rpcNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                NULL,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};



static BOOL namespcaedAdded = FALSE;

NAMESPACE_LIST * getBcsRpcNamespace(){
	if(!namespcaedAdded){
		//GET
		addRpcToNamespace(&bcsRpc,& bcsRpc__RPC);
                addRpcToNamespace(&bcsRpc,& bcsRpc_ARGS);
		namespcaedAdded =TRUE;
	}

	return &bcsRpc;
}
