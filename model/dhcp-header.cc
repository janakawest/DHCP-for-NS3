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

#include <string>
#include "dhcp-header.h"

#include "ns3/assert.h"
#include "ns3/log.h"


namespace ns3 {
	// DHCP Header
	NS_OBJECT_ENSURE_REGISTERED (DHCPMessage);

  DHCPMessage::DHCPMessage ()
	{}
  
  DHCPMessage::~DHCPMessage ()  
  {}        
  
  TypeId
  DHCPMessage::GetTypeId (void)
  {
    static TypeId tid = TypeId ("ns3::DHCPMessage")
                        .SetParent<Header> ()
                        .AddConstructor<DHCPMessage> ();
    return tid;
  }
  TypeId
  DHCPMessage::GetInstanceTypeId (void) const
  {
    return GetTypeId ();
  }

	void 
  DHCPMessage::Print (std::ostream &os) const
  {
		//TODO: Finish this
    //os << " " << RED << m_qName <<
    //   ": type " << m_qType <<
    //   ", class " << m_qClass << RESET << std::endl;
  }
  
  uint32_t 
  DHCPMessage::GetSerializedSize (void) const
  {
    return (2 /*2B to send the size of the query*/ + 
            sizeof (m_opcode) /*size of of the opcode*/ +
            sizeof (m_hType) /*size of of the Hardware Type*/ +
            sizeof (m_hLen) /*size of of ardware adress length*/ +
            sizeof (m_xId) /*size of the transaction ID*/ +
            sizeof (m_eCs) /*size of the time to request*/ +
            sizeof (m_flags) /*size of the flags*/ +
						m_ciaddr.size () + 1 /*size of the IP address and the termination*/ +
						m_yiaddr.size () + 1 /*size of the your IP address and the termination*/ +
						m_siaddr.size () + 1 /*size of the next server IP address and the termination*/ +
						m_giaddr.size () + 1 /*size of the relay agent IP address and the termination*/ +
						m_chaddr.size () + 1 /*size of MAC address and the termination*/ +
						m_optionGateway.size () + 1 /*size of the Gateway IP and the termination*/ +
						m_optionDNS.size () + 1 /*size of the DNS server IP and the termination*/ +
						m_optionDNS2.size () + 1 /*size of the DNS server2 IP and the termination */
				   ); 
  }
  void 
  DHCPMessage::Serialize (Buffer::Iterator start) const
  {
    Buffer::Iterator i = start;

		i.WriteU16 (m_opcode);
		i.WriteU16 (m_hType);
		i.WriteU16 (m_hLen);
		i.WriteHtonU32 (m_xId);
		i.WriteHtonU16 (m_eCs);
		i.WriteHtonU16 (m_flags);
		
		// This method has been used to send variable length strings
		// Client's IP address
	  i.WriteU16 (m_ciaddr.size () + 1);
		i.Write ((uint8_t*) m_ciaddr.c_str (), m_ciaddr.size () + 1);
		// Your Ip address IP address
	  i.WriteU16 (m_yiaddr.size () + 1);
		i.Write ((uint8_t*) m_yiaddr.c_str (), m_yiaddr.size () + 1);
		// Next Servers IP address
	  i.WriteU16 (m_siaddr.size () + 1);
		i.Write ((uint8_t*) m_siaddr.c_str (), m_siaddr.size () + 1);
		// Relay Agent's IP address
	  i.WriteU16 (m_giaddr.size () + 1);
		i.Write ((uint8_t*) m_giaddr.c_str (), m_giaddr.size () + 1);
		// MAC address
	  i.WriteU16 (m_chaddr.size () + 1);
		i.Write ((uint8_t*) m_chaddr.c_str (), m_chaddr.size () + 1);
		// Gateway IP address
	  i.WriteU16 (m_optionGateway.size () + 1);
		i.Write ((uint8_t*) m_optionGateway.c_str (), m_optionGateway.size () + 1);
		// DNS server's IP address
	  i.WriteU16 (m_optionDNS.size () + 1);
		i.Write ((uint8_t*) m_optionDNS.c_str (), m_optionDNS.size () + 1);
		// DNS server 2 IP address
	  i.WriteU16 (m_optionDNS2.size () + 1);
		i.Write ((uint8_t*) m_optionDNS2.c_str (), m_optionDNS2.size () + 1);
  }
  uint32_t 
  DHCPMessage::Deserialize (Buffer::Iterator start)
  {
    Buffer::Iterator i = start;
    uint8_t receivedSize = 0;
		m_ciaddr = ""; //!< Clients' IP address (refer the RFC)
		m_yiaddr = ""; //!< Your (Client's) IP address 
		m_siaddr = ""; //!< IP address of the next server to be contacted in next bootp
		m_giaddr = ""; //!< Relay agent IP address
		m_chaddr = ""; //!< Client's hardware Address (MAC)
		m_optionGateway = ""; //!< Gateway address from the DHCP server
		m_optionDNS = ""; //!< DNS server IP address
		m_optionDNS2 = ""; //!< Secondery DNS server if awailable
		
		m_opcode =  i.ReadU16 (); //!< Operational Code
		m_hType =  i.ReadU16 ();	//!< Hardware Address Type
		m_hLen =  i.ReadU16 ();		//!< Hardware Address Length
		m_xId =  i.ReadNtohU32 ();		//!< Transaction ID (A Random Number)
		m_eCs =  i.ReadNtohU16 ();		//!< Time ellapsed since the request //TODO: think a method
		m_flags =  i.ReadNtohU16 (); 	//!< Flags
		
		// Used for reading variable size strings
		receivedSize = 0;
		receivedSize = i.ReadU16 ();
		char data[receivedSize];
		i.Read ((uint8_t*) data, receivedSize);
		m_ciaddr = data;

		// Used for reading variable size strings
		receivedSize = 0;
		receivedSize = i.ReadU16 ();
		data[receivedSize]={0};
		i.Read ((uint8_t*) data, receivedSize);
		m_yiaddr = data;
    
		// Used for reading variable size strings
		receivedSize = 0;
		receivedSize = i.ReadU16 ();
		data[receivedSize]={0};
		i.Read ((uint8_t*) data, receivedSize);
		m_siaddr = data;
    
		// Used for reading variable size strings
		receivedSize = 0;
		receivedSize = i.ReadU16 ();
		data[receivedSize]={0};
		i.Read ((uint8_t*) data, receivedSize);
		m_giaddr = data;
		
		// Used for reading variable size strings
		receivedSize = 0;
		receivedSize = i.ReadU16 ();
		data[receivedSize]={0};
		i.Read ((uint8_t*) data, receivedSize);
		m_chaddr = data;
		
		// Used for reading variable size strings
		receivedSize = 0;
		receivedSize = i.ReadU16 ();
		data[receivedSize]={0};
		i.Read ((uint8_t*) data, receivedSize);
		m_optionGateway = data;
		
		// Used for reading variable size strings
		receivedSize = 0;
		receivedSize = i.ReadU16 ();
		data[receivedSize]={0};
		i.Read ((uint8_t*) data, receivedSize);
		m_optionDNS = data;
		
		// Used for reading variable size strings
		receivedSize = 0;
		receivedSize = i.ReadU16 ();
		data[receivedSize]={0};
		i.Read ((uint8_t*) data, receivedSize);
		m_optionDNS2 = data;
		
		return DHCPMessage::GetSerializedSize ();
  }	
}// End of the Namespace
