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

#ifndef DHCP_HEADER_H
#define DHCP_HEADER_H

#include "ns3/header.h"
#include "ns3/nstime.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv4-header.h"

namespace ns3 {

class DHCPMessage : public Header
{
public:
	enum OperationCode
  {
    BOOTREQUEST=1,
    BOOTREPLY=2   
  };

  // Reference https://tools.ietf.org/html/rfc1700
  /**
     1 Ethernet (10Mb)                                    [JBP]
     2 Experimental Ethernet (3Mb)                        [JBP]
     3 Amateur Radio AX.25                                [PXK]
     4 Proteon ProNET Token Ring                          [JBP]
     5 Chaos                                              [GXP]
     6 IEEE 802 Networks                                  [JBP]
     7 ARCNET                                             [JBP]
     8 Hyperchannel                                       [JBP]
     9 Lanstar                                             [TU]
    10 Autonet Short Address                             [MXB1]
    11 LocalTalk                                         [JKR1]
    12 LocalNet (IBM PCNet or SYTEK LocalNET)             [JXM]
    13 Ultra link                                        [RXD2]
    14 SMDS                                              [GXC1]
    15 Frame Relay                                        [AGM]
    16 Asynchronous Transmission Mode (ATM)              [JXB2]
    17 HDLC                                               [JBP]
    18 Fibre Channel                            [Yakov Rekhter]
    19 Asynchronous Transmission Mode (ATM)      [Mark Laubach]
    20 Serial Line                                        [JBP]
    21 Asynchronous Transmission Mode (ATM)              [MXB1] 
  */
  enum HardwareType
  {
    ETHERNET=1,
    ExpETHERNET=2 
  };
  
  enum HardwareLength
  {
    //TODO: Find and Finish the section
  };

  DHCPMessage ();
  virtual ~ DHCPMessage ();
  
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  /**
   * \brief Return the instance type identifier.
   * \return instance type ID
   */
  virtual TypeId GetInstanceTypeId (void) const;

  virtual void Print (std::ostream& os) const;

  /**
   * \brief Get the serialized size of the packet.
   * \return size
   */
  virtual uint32_t GetSerializedSize (void) const;

  /**
   * \brief Serialize the packet.
   * \param start Buffer iterator
   */
  virtual void Serialize (Buffer::Iterator start) const;

  /**
   * \brief Deserialize the packet.
   * \param start Buffer iterator
   * \return size of the packet
   */
  virtual uint32_t Deserialize (Buffer::Iterator start);
  
private:
  uint8_t m_opcode; //!< Operational Code
  uint8_t m_hType;	//!< Hardware Address Type
	uint8_t m_hLen;		//!< Hardware Address Length
	uint32_t m_xId;		//!< Transaction ID (A Random Number)
	uint16_t m_eCs;		//!< Time ellapsed since the request //TODO: think a method
	uint16_t m_flags; 	//!< Flags
	std::string m_ciaddr; //!< Clients' IP address (refer the RFC)
	std::string m_yiaddr; //!< Your (Client's) IP address 
	std::string m_siaddr; //!< IP address of the next server to be contacted in next bootp
	std::string m_giaddr; //!< Relay agent IP address
	std::string m_chaddr; //!< Client's hardware Address (MAC)
	std::string m_optionGateway; //!< Gateway address from the DHCP server
	std::string m_optionDNS; //!< DNS server IP address
	std::string m_optionDNS2; //!< Secondery DNS server if awailable

	// sname, file, and option feilds are depricated in this implementation.
public:
  /*
  * /brief Get and Set the opcode
  */  
  uint8_t GetOpcode () const
  {
    return m_opcode;
  }
  void SetOpcode (uint8_t opcode)
  {
    m_opcode = opcode;    
  }   
   
  /*
  * /brief Get and Set the Hardware Address Type
  */  
  uint8_t GetHtype () const
  {
    return m_hType;
  }
  void SetHtype (uint8_t htype)
  {
    m_hType = htype;    
  }     
  
  /*
  * /brief Get and Set the Hardware Address Length
  */  
  uint8_t GetHlen () const
  {
    return m_hLen;
  }
  void SetHlen (uint8_t hlen)
  {
    m_hLen = hlen;    
  }     
      
  /*
  * /brief Get and Set the Random ID
  */  
  uint32_t GetXid () const
  {
    return m_xId;
  }
  void SetHlen (uint32_t xid)
  {
    m_xId = xid;    
  }  
   
  /*
  * /brief Get and Set the elapsed Time
  */  
  uint16_t GetEcs () const
  {
    return m_eCs;
  }
  void SetEcs (uint16_t ecs)
  {
    m_eCs = ecs;    
  }
 
  /*
  * /brief Get and Set the Hardware Flags
  */  
  uint16_t GetFlags () const
  {
    return m_flags;
  }
  void SetHlen (uint16_t flags)
  {
    m_flags = flags;    
  }     

  /*
  * /brief Get and Set the Client IP address
  */  
  std::string GetCiaddr () const
  {
    return m_ciaddr;
  }
  void SetCiaddr (std::string ciaddr)
  {
    m_ciaddr = ciaddr;    
  }     

  /*
  * /brief Get and Set the 'your' (client) IP address
  */  
  std::string GetYiaddr () const
  {
    return m_yiaddr;
  }
  void SetYiaddr (std::string yiaddr)
  {
    m_yiaddr = yiaddr;    
  }     

  /*
  * /brief Get and Set the IP address of next server to use in bootstrap
  */  
  std::string GetSiaddr () const
  {
    return m_siaddr;
  }
  void SetSiaddr (std::string siaddr)
  {
    m_siaddr = siaddr;    
  }     

  /*
  * /brief Get and Set Relay agent IP address
  */  
  std::string GetGiaddr () const
  {
    return m_giaddr;
  }
  void SetGiaddr (std::string giaddr)
  {
    m_giaddr = giaddr;    
  }     

  /*
  * /brief Get and Set Client hardware address
  */  
  std::string GetChaddr () const
  {
    return m_chaddr;
  }
  void SetChaddr (std::string chaddr)
  {
    m_chaddr = chaddr;    
  }     

  /*
  * /brief Get and Set the IP address of Default Gateway Option
  */  
  std::string GetOptionGateway () const
  {
    return m_optionGateway;
  }
  void SetOptionGateway (std::string gateway)
  {
    m_optionGateway = gateway;    
  }     

  /*
  * /brief Get and Set Relay agent IP address for option DNS
  */  
  std::string GetOptionDNS () const
  {
    return m_optionDNS;
  }
  void SetOptionDNS (std::string dns)
  {
    m_optionDNS = dns;    
  }     

  /*
  * /brief Get and Set Client hardware address for Option DNS server two
  */  
  std::string GetOptionDNS2 () const
  {
    return m_optionDNS2;
  }
  void SetOptionDNS2 (std::string dns2)
  {
    m_optionDNS2 = dns2;    
  }     
};// end of the Header

static inline std::ostream& operator<< (std::ostream& os, const DHCPMessage & header)
{
  header.Print (os);
  return os;
}
}// ns-3 namespace
#endif
