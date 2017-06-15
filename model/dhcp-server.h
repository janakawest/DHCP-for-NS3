
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

#ifndef DHCP_SERVER_H
#define DHCP_SERVER_H

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/address.h"
#include "ns3/random-variable-stream.h"

#include "ns3/dhcp.h"
#include "ns3/dhcp-header.h"

#define DHCP_SERVER_COMM_PORT 67 // UDP Port number 67 was used as RFC pointedout

namespace ns3 {

class Socket;
class Packet;

class DHCPServer : public Application
{
public:
	DHCPServer (void);
	~DHCPServer (void);
		static TypeId GetTypeId (void);
  /**
    /brief Load the preconfigured parameters from the file dhcpconf file.
    */
  void LoadParameters (void);

  /**
    /brief Set the network parameters according to the configuration file. 
    This function accesses the network address, MASK, and range
    and assign those values to IPV4 address class. */
  void SetNetworkParameters (void);

  /**
    /brief This mehtod returns the next available address in the range of
    IP ddresses. 
    /returns the IP address (a string value). */
  std::string GetNextAddress (void);

	void DoInitialize (void);
	void DoDispose (void);

private:
	
	void HandleDHCPRequest (Ptr<Socket> socket);
	virtual void StartApplication (void);
	virtual void StopApplication (void);

	/// Note: String Variables are used for IP address for the conveniency
  std::string m_networkAddress; //!< the network address DHCP support
  std::string m_networkMask; //!< netmask
  std::string m_rangeUpperBound; //!< the Upper buond of the lease range
  std::string m_rangeLowerBound; //!< the lower bound of the lease range
  std::string m_dnsAddress; //!< Option DNS address
  std::string m_gatewayAddress; //!< Option Gateway Address
  uint32_t m_maxLeaseTime; //!< Maximum Leasing time
  uint32_t m_defaultLeaseTime; //!< deafault lease time
  std::string m_currentLeasedAddress; //!< currently offered address	
	Ipv4AddressHelper m_ipv4; //!< IPv4 address helper for dynamic allocation

	Ipv4Address m_DHCPServerAddress; //!< The Server Address
	Ipv4Mask m_DHCPServerNetMask; //!< The Server netmask

	bool m_initialized; //!< indicate that the module is initialied

	Ptr<Socket> m_socket; //!< The UDP socket used for BootPMessages

};
} // end of ns-3 namespace
#endif
