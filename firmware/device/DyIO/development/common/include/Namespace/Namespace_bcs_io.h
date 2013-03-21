/*
 * Namespace_bcs_io.h
 *
 *  Created on: Mar 21, 2013
 *      Author: hephaestus
 */

#ifndef NAMESPACE_BCS_IO_H_
#define NAMESPACE_BCS_IO_H_

//bcs.io
#define GCHM				0x6D686367// Get channel mode
#define GACM				0x6D636167// Get all channel mode
#define SCHV				0x76686373// Set channel value
#define SACV				0x76636173// Set all channel values
#define GCHV				0x76686367// Get channel value
#define GACV				0x76636167// Get all channel values
#define CCHN				0x6E686363// Configure channel
#define ASYN				0x6e797361 // 'asyn'  Set/Get asynchronous mode
#define GCHC				0x63686367 // 'gchc'  Get Channel Count
#define GCML				0x6c6d6367 // 'gcml'  Get channel Mode List

int getNumberOfIOChannels();// Returns the number of IO channels availible


#endif /* NAMESPACE_BCS_IO_H_ */
