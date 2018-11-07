#ifndef  _CALLBACK_H
#define  _CALLBACK_H

#include "snmp_pp/snmp_pp.h"
#include "snmp_pp/collect.h"
#include "snmp_pp/notifyqueue.h"

void TrapCallBack( int reason, Snmp_pp::Snmp *snmp, Snmp_pp::Pdu &pdu, Snmp_pp::SnmpTarget &target, void *cd);
#endif
