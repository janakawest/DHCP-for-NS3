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
}// End of the Namespace
