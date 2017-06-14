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
#include "dhcp-server.h"
#include "dhcp-header.h"

namespace ns3
{
	DHCPServer::DHCPServer ()
	{
		m_initialized = false;
		DoInitialize ();
	}
	DHCPServer::~DHCPServer ()
	{
		DoDispose ();
	}
	NS_LOG_COMPONENT_DEFINE ("DHCPServer");
	NS_OBJECT_ENSURE_REGISTERED (DHCPServer);
	TypeId
	DHCPServer::GetTypeId (void)
	{
		static TypeId tid = TypeId ("ns3::DHCPServer")
			.SetParent <Application> ()
			.AddConstructor <DHCPServer> ()
			.AddAttribute ("SetServerAddress",
										"IP address of the server.",
										Ipv4AddressValue (),
										MakeIpv4AddressAccessor (&DHCPServer::m_DHCPServerAddress),
										MakeIpv4AddressChecker ())
   	 	.AddAttribute ("SetNetMask",
				            "Network Mask of the server.",
										Ipv4MaskValue (),
										MakeIpv4MaskAccessor (&DHCPServer::m_DHCPServerNetMask),
										MakeIpv4MaskChecker ())
			;
		return tid;
	}

	void DHCPServer::DoInitialize (void)
	{
		// TODO fix this bug to initializing two times
		if (!m_initialized)
		{
			/// Initialize the Currently leased IP address
			m_currentLeasedAddress = "";
			/// Initialize the Socket for BOOTPMEssages
			m_socket = 0;		
			/// Load the parameters given in dhcpconf file
			LoadParameters ();
			/// Set the network parameters according to the loaded parameters
			SetNetworkParameters ();
			m_initialized = true;
		}
	}

	void DHCPServer::DoDispose (void)
	{
		//TODO
	}
	void
  DHCPServer::LoadParameters (void)
	{ 
    std::string line = "";
    std::fstream myfile ("/repos/ns-3-allinone/ns-allinone-3.26/ns-3.26/src/dhcp/model/dhcpconf");
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
      myfile.close();
    }
		else
		{
			//TODO handle the exeption
		}
	}
  //TODO this is dipricated
	void
  DHCPServer::SetNetworkParameters (void)
  {
    m_ipv4.SetBase (Ipv4Address (m_networkAddress.c_str ()),
                  Ipv4Mask (m_networkMask.c_str ()));
  }

  std::string
  DHCPServer::GetNextAddress (void)
  {
    std::ostringstream oss;
		uint32_t nextAddress;
		if (m_currentLeasedAddress == "")
			nextAddress = Ipv4Address (m_rangeLowerBound.c_str ()).Get () + 1;
    else
			nextAddress = Ipv4Address (m_currentLeasedAddress.c_str ()).Get () + 1;

		if (nextAddress <= Ipv4Address (m_rangeUpperBound.c_str ()).Get ())
		{
			oss << Ipv4Address (nextAddress);
    	return m_currentLeasedAddress = oss.str ();
		}
		else 
			return "";
  }
	void 
	DHCPServer::StartApplication (void)
	{
		NS_LOG_FUNCTION (this);
				
		if (m_socket == 0)
		{
      TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
			m_socket = Socket::CreateSocket (GetNode (), tid);
			InetSocketAddress local = InetSocketAddress (m_DHCPServerAddress, DHCP_COMM_PORT);
			m_socket->Bind (local);
		}
		m_socket->SetRecvCallback (MakeCallback (&DHCPServer::HandleDHCPRequest, this));
	}

	void 
	DHCPServer::StopApplication ()
	{
		NS_LOG_FUNCTION (this);
		
		if (m_socket != 0)
		{
			m_socket->Close ();
			m_socket->SetRecvCallback (MakeNullCallback <void, Ptr<Socket> > ());
		}
		DoDispose ();
	}
	
	void 
	DHCPServer::HandleDHCPRequest (Ptr<Socket> socket)
	{
		//TODO
	}
}
