/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef DHCP_H
#define DHCP_H

#include <cassert>                                                                                        
#include <list>                                                                                           
#include <sys/types.h>

#include "ns3/ipv4-address.h"
#include "ns3/timer.h"
#include "ns3/node.h"
#include "ns3/random-variable-stream.h"
#include "ns3/ipv4.h"
#include "ns3/net-device.h"
#include "ns3/output-stream-wrapper.h"
namespace ns3 {
class DHCPBindingEntry
{
	/**
		Class that is used to record the BINDING structure 
		explained in the RFC. This class facilitates the necessary
		reocrds for the entries.*/
};
std::ostream operator<< (std::ostream& os, DHCPBindingEntry const& entry);

class DHCPBindTable
{
	/**
		Class that is working as the DINDING structure explained in the RFC.
		*/
};

class DynamicConfigurationEntry
{
};
std::ostream operator<< (std::ostream& os, DynamicConfigurationEntry const& entry);

class DynamicConfigurationTable
{
};
}
#endif /* DHCP_H */

