#ifndef  _CALLBACK_H
#define  _CALLBACK_H

#include "snmp_pp/snmp_pp.h"
#include "snmp_pp/collect.h"
#include "snmp_pp/notifyqueue.h"

using namespace Snmp_pp;

void TrapCallBack( int reason, Snmp *snmp, Pdu &pdu, SnmpTarget &target, void *cd);
#endif
