/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "dhcp.h"

#include <iomanip>
#include <iostream>
#include <fstream>

#include "ns3/simulator.h" 
#include "ns3/log.h"
#include "ns3/abort.h"
#include "ns3/timer.h"

#include "ns3/ipv4-address-helper.h"
#include "ns3/ipv4.h"
#include "ns3/ipv4-address-generator.h"

#include "ns3/node.h"
#include "ns3/socket-factory.h"
#include "ns3/address-utils.h"
#include "ns3/nstime.h"
#include "ns3/inet-socket-address.h"
#include "ns3/socket.h"
#include "ns3/udp-socket.h"

#include "dhcp.h"
#include "dhcp-client.h"
#include "dhcp-header.h"

namespace ns3
{
	DHCPClient::DHCPClient ()
	{
		/*cstrctr*/
	}
	DHCPClient::~DHCPClient ()
	{
		/*dstrctr*/
	}
	NS_LOG_COMPONENT_DEFINE ("DHCPClient");
	NS_OBJECT_ENSURE_REGISTERED (DHCPClient);
	TypeId
	DHCPClient::GetTypeId (void)
	{
		static TypeId tid = TypeId ("ns3::DHCPClient")
			.SetParent <Application> ()
			.AddConstructor <DHCPClient> ()
			.AddAttribute ("SetClientAddress",
										"IP address of the Client.",
										Ipv4AddressValue (),
										MakeIpv4AddressAccessor (&DHCPClient::m_DHCPClientAddress),
										MakeIpv4AddressChecker ())
   	 	.AddAttribute ("SetNetMask",
				            "Network Mask of the Client.",
										Ipv4MaskValue (),
										MakeIpv4MaskAccessor (&DHCPClient::m_DHCPClientNetmask),
										MakeIpv4MaskChecker ())
			;
		return tid;
	}
}

