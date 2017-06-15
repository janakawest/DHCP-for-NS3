/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/log.h"
#include "ns3/ipv4-address.h"
#include "ns3/address-utils.h"
#include "ns3/nstime.h"
#include "ns3/inet-socket-address.h"
#include "ns3/socket.h"
#include "ns3/udp-socket.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/enum.h"
#include "ns3/abort.h"
#include "ns3/random-variable-stream.h"

#include "dhcp.h"
#include "dhcp-client.h"
#include "dhcp-header.h"

namespace ns3
{
	DHCPClient::DHCPClient ()
	{
		/*cstrctr*/
		m_rng = CreateObject<UniformRandomVariable> ();
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
			.AddAttribute ("InterfaceId",
										"The interface that bound for the application",
										UintegerValue (1),
										MakeUintegerAccessor (&DHCPClient::m_interfaceId),
										MakeUintegerChecker<uint16_t> ())
			;
		return tid;
	}
	
	void
	DHCPClient::StartApplication (void)
	{
		if (m_DHCPCommSocket == 0)
		{
      TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
			m_DHCPCommSocket = Socket::CreateSocket (GetNode (), tid);
			InetSocketAddress local = InetSocketAddress (m_DHCPClientAddress, DHCP_CLIENT_COMM_PORT);
			m_DHCPCommSocket->Bind (local);
		}
		m_DHCPCommSocket->SetRecvCallback (MakeCallback (&DHCPClient::HandleDHCPResponse, this));

		if (!m_DhcpServerDiscovered)
			DhcpDiscover ();			
		//TODO 
		// Implement the communicaiton socket and necessry methods
	}
	
	void 
	DHCPClient::StopApplication ()
	{
		NS_LOG_FUNCTION (this);
		
		if (m_DHCPCommSocket != 0)
		{
			m_DHCPCommSocket->Close ();
			m_DHCPCommSocket->SetRecvCallback (MakeNullCallback <void, Ptr<Socket> > ());
		}
		
		// TODO
		// Close the Communication Socket and the necessary attributes
		DoDispose ();
	}
	
	void 
	DHCPClient::HandleDHCPResponse (Ptr<Socket> socket)
	{
		//TODO 
	}

	void 
	DHCPClient::DhcpDiscover ()
	{
		Address macAddress;
		std::ostringstream oss;

		Ptr<Packet> DhcpDiscover = Create<Packet> ();
		DHCPMessage DhcpDiscoverHeader;

		DhcpDiscoverHeader.SetOpcode (DHCPMessage::DHCPDISCOVER);
		DhcpDiscoverHeader.SetHtype (DHCPMessage::ETHERNET);
		// Get the attached MAC address
		macAddress = GetNode ()->GetDevice (m_interfaceId)->GetAddress ();
		oss << macAddress;

		std::cout << macAddress << std::endl;

		DhcpDiscoverHeader.SetHlen (macAddress.GetLength ());
		DhcpDiscoverHeader.SetXid (GetTransactionId ());
		DhcpDiscoverHeader.SetFlags (1>>16);
		DhcpDiscoverHeader.SetCiaddr ("0");
		DhcpDiscoverHeader.SetYiaddr ("0");
		DhcpDiscoverHeader.SetSiaddr ("0");
		DhcpDiscoverHeader.SetGiaddr ("0");

		DhcpDiscoverHeader.SetChaddr (oss.str ());

 		DhcpDiscover->AddHeader (DhcpDiscoverHeader);
		m_DHCPCommSocket->SendTo (DhcpDiscover, 0, Ipv4Address ("255.255.255.255"));

		m_DhcpServerDiscovered = 1;
	}
	uint32_t
	DHCPClient::GetTransactionId (void)
	{
		// This is an arbitarary number
		return m_rng->GetValue (1, 100000000);		
	}

}
