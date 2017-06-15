
/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 Hiroaki Nishi Laboratory, Keio University, Japan
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as 
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Author: Janaka Wijekoon <janaka@west.sd.ekio.ac.jp>, Hiroaki Nishi <west@sd.keio.ac.jp>
 */

#ifndef DHCP_CLIENT_H
#define DHCP_CLIENT_H

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/address.h"
#include "ns3/random-variable-stream.h"

#include "ns3/dhcp.h"
#include "ns3/dhcp-header.h"

#define DHCP_CLIENT_COMM_PORT 68 // UDP Port number 68 was used as RFC pointedout

namespace ns3 {

class Socket;
class Packet;

class DHCPClient : public Application
{
public:
	DHCPClient (void);
	~DHCPClient (void);
		static TypeId GetTypeId (void);

	/**
		/brief Broadcast DHCP discover messages. When the message is sent, the client should wait 
					untila one or more DHCP server replies for the request. That function is 
					specifically writtne in the HandleDHCPResponse method.
	*/
	void DhcpDiscover ();

private:
	/**
		/brief Handle all DHCP response messages comming to the applicaiton 
	*/
	void HandleDHCPResponse (Ptr<Socket> socket);
	/**
		/brief Get the Transaction Identifier. This is a randomely Genarated unique ID
	*/
	uint32_t GetTransactionId (void);

	virtual void StartApplication (void);
	virtual void StopApplication (void);

	Ipv4Address m_DHCPClientAddress; //!< Client's IP address
	Ipv4Mask m_DHCPClientNetmask; //!< Client's Netmask
	
	bool m_DhcpServerDiscovered; //!< true if the client was able to find a DHCP server

	Ptr<Socket> m_DHCPCommSocket; //!< The UDP socket uses for DHCP Messages
	Ptr<Socket> m_CommSocket; //!< The socket uses for comunicaitoni
	
	uint16_t m_interfaceId; //!< The NetDevice ID that the application is attached to 
  Ptr<Ipv4> m_ipv4; //!< IPv4 reference
	Ptr<UniformRandomVariable> m_rng; //!< Rng stream.
};
}// ns-3 namespace
#endif
