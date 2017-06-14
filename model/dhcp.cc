/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "dhcp.h"

#include "ns3/simulator.h" 
#include "ns3/log.h"
#include "ns3/abort.h"
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
	{
		DoInitialize (); 
	}
	DHCPBindTable::~DHCPBindTable ()
	{
		DoDispose (); 
	}

	void 
	DHCPBindTable::DoInitialize (void)
	{
	}

	void
	DHCPBindTable::DoDispose (void)
	{
		//TODO write necessary instructions
	}

	void
	DHCPBindTable::AddRecord (std::string MACAddress, std::string IPAddress, uint32_t issuedTime, uint32_t leasedTime)
	{
		DHCPBindingEntry* newEntry  = new DHCPBindingEntry (MACAddress, 
																												IPAddress, 
																												issuedTime, 
																												leasedTime);

		Time delay;
		EventId removeEvent;

	  delay = Seconds (leasedTime) + Seconds (m_rng->GetValue (0.0, 2.0));
	  removeEvent = Simulator::Schedule (delay, &DHCPBindTable::DeleteRecord, this, newEntry);

		m_dhcpTable.push_front (std::make_pair (newEntry, removeEvent));
	}

	bool 
	DHCPBindTable::DeleteRecord (DHCPBindingEntry* record)
	{
		NS_LOG_FUNCTION (this << record);

		bool retValue = false;

		for (DHCPRecordI it = m_dhcpTable.begin (); it != m_dhcpTable.end (); it++)
		{
			if (it->first->GetMAC () == record->GetMAC () &&
					it->first->GetIP () == record->GetIP ())
			{
				m_dhcpTable.erase (it);
				retValue = true;
				break;
			}
		}
		return retValue;
	}

	DHCPBindTable::DHCPRecordI 
	DHCPBindTable::FindARecordforMAC (std::string MACAddress, bool &found)
	{
		NS_LOG_FUNCTION (this << MACAddress);
		DHCPRecordI foundRecord;
		bool retValue = false;
		for (DHCPRecordI it = m_dhcpTable.begin (); it != m_dhcpTable.end (); it ++)
		{
			if (it->first->GetMAC () == MACAddress)
			{
				foundRecord = it;
				retValue = true;
				break;
			}
		}
		found  = retValue;
		return foundRecord;
	}

	DHCPBindTable::DHCPRecordI 
	DHCPBindTable::FindARecordforIP (std::string IPAddress, bool &found)
	{
		NS_LOG_FUNCTION (this << IPAddress);
		DHCPRecordI foundRecord;
		bool retValue = false;
		for (DHCPRecordI it = m_dhcpTable.begin (); it != m_dhcpTable.end (); it ++)
		{
			if (it->first->GetIP () == IPAddress)
			{
				foundRecord = it;
				retValue = true;
				break;
			}
		}
		found  = retValue;
		return foundRecord;
	}
}//namespce

