/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "dhcp.h"

#include <iomanip>
#include <iostream>
#include <fstream>

#include "ns3/simulator.h" 
#include "ns3/log.h"
#include "ns3/abort.h"
#include "ns3/node-list.h"
#include "ns3/node.h"
#include "ns3/timer.h"


NS_LOG_COMPONENT_DEFINE ("DHCPBindRecord"); 

namespace ns3 {

	DHCPBindingEntry::DHCPBindingEntry (void)
	{	/*cstrctr*/}

	DHCPBindingEntry::DHCPBindingEntry ( std::string mac,
 								std::string ip,
								uint32_t issuedTime, 
								uint32_t leasedTime)
	{ /*cstrctr*/}

	DHCPBindingEntry::~DHCPBindingEntry ()
	{ /*dstrctr*/}

	DHCPBindTable::DHCPBindTable ()
	{ /*cstrctr*/}
	DHCPBindTable::~DHCPBindTable ()
	{ /*dstrctr*/}

  //NOTE: At the moment this implementation supports only one DHCP network Range
	void
	DHCPBindTable::LoadParameters (void)
	{
		std::string line = "";
		std::fstream myfile ("dhcpconf");
		if (myfile.is_open())
		{
			std::string tmp;
			while (getline (myfile, line))
			{
				std::istringstream iss(line);
				std::string param;
				iss >> param;
				if (param == "subnet")
				{
					iss >> m_networkAddress;
					iss >> tmp;
					iss >> m_networkMask;
				}
				else if (param == "range")
				{
					iss >> m_rangeLowerBound;
					iss >> m_rangeUpperBound;
				}
				else if (param == "dns")
				{ 
					iss >> m_dnsAddress;
				}
				else if (param == "gateway")
				{
					iss >> m_gatewayAddress;
				}
				else if (param == "max-lease-time")
				{
					iss >> m_maxLeaseTime;
				}
				else if (param == "default-lease-time")
				{
					iss >> m_defaultLeaseTime;
				}
			}
			std::cout << m_rangeLowerBound << std::endl;
			myfile.close();
		}
	}
}//namespce

