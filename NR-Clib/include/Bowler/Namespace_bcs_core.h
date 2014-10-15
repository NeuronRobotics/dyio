/*
 * Namespace_bcs_core.h
 *
 *  Created on: Mar 1, 2013
 *      Author: hephaestus
 */

#ifndef NAMESPACE_BCS_CORE_H_
#define NAMESPACE_BCS_CORE_H_

#include "namespace.h"
#include "Defines.h"

//bcs.core
#define _ERR					0x7272655f // '_err'  The Error RPC
#define _RDY					0x7964725f // '_rdy'  The ready RPC
#define _PNG					0x676E705F // '_png'  Generic ping
#define _NMS					0x736d6e5f // '_nms'  Namespace RPC

/**
 * Initializes core and returns a pointer to the namespace list
 */
NAMESPACE_LIST * getBcsCoreNamespace();
NAMESPACE_LIST * getBcsRpcNamespace();

#endif /* NAMESPACE_BCS_CORE_H_ */
