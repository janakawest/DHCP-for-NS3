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
		reocrds for the entries.
		*/

	public:

		DHCPBindingEntry (void);
		/*
		 * /brief constructor 
		 * /param mac the MAC address
		 * /param ip the IP address
		 * /param issuedTime the time that the lease was issued
		 * /param leasedTime the maximum time that the record is issued for*/
		DHCPBindingEntry ( std::string mac = std::string (""),
 								std::string ip = std::string (""),
								uint32_t issuedTime = 0, 
								uint32_t leasedTime = 0, 
								);

		~DHCPBindingEntry ();

		/*
		 * /brief Get and Set the issue time value
				This valued would be updated evertime the same MAC address, 
				i.e., client, ask for DHCP lease*/
		void SetIssuedTime (uint32_t issuedTime)
		{
			m_issuedTime = issuedTime;
		}
		uint32_t GetIssuedTime (void) const
		{
			return m_issuedTime;
		}

		/*
		 * /brief Get and Set leased time. 
				This time defines the maximum time period a 
			 	client can use a given IP. */
		void SetLeasedTime (uint32_t leasedTime)
		{
			m_leasedTime = leasedTime;
		}
		uint32_t GetLeasedTime (void) const
		{
			return m_leasedTime;
		}

		/*
		 * /brief Get and set the MAC address*/
		void SetMAC (std::string mac)
		{
			m_MAC = mac;
		}
		std::string GetMAC (void) const
		{
			return m_MAC;
		}

		/*
		 * /brief Get and set the leased IP address*/
		void SetIP (std::string ip)
		{
			m_IP = ip;
		}
		std::string GetIP (void) const
		{
			return m_IP;
		}
	private:
		string m_MAC; //!< The MAC address
		string m_IP; //!< The leased IP address
		uint32_t m_issuedTime; //!< The issued time 
		uint32_t m_releaseTime; //!< The leased time
};
std::ostream operator<< (std::ostream& os, DHCPBindingEntry const& entry);

class DHCPBindTable
{
	/**
		Class that is working as the DINDING structure explained in the RFC.
		*/
	public:
		DHCPBindingTable ();
		~DHCPBindingTable ();

  /// Container for a DHCP Bind entries
	typedef std::pair <DHCPBindingEntry*, EventId> BindRecordPair;

	/// Container for an instance of a Bind Entry table
	typedef std::list<std::pair <DHCPBindingEntry*, EventId> > BindRecordInstance;

	/// Iterator for a Binding Record
  typedef std::list<std::pair <DHCPBindingEntry*, EventId> >::iterator BindRecordI;

	/// Constant Iterator for Binding Record
  typedef std::list<std::pair <DHCPBindingEntry*, EventId> >::const_iterator BindRecordRecordCI;

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

