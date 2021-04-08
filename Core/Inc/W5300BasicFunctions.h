/*
 * W5300BasicFunctions.h
 *
 *  Created on: 2021. 4. 8.
 *      Author: javakys
 */

#ifndef INC_W5300BASICFUNCTIONS_H_
#define INC_W5300BASICFUNCTIONS_H_

#include "wizchip_conf.h"

void Reset_W5300(void);
void W5300_write(uint32_t addr, iodata_t wd);
iodata_t W5300_read(uint32_t addr);


#endif /* INC_W5300BASICFUNCTIONS_H_ */
