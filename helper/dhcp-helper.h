/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef DHCP_HELPER_H
#define DHCP_HELPER_H

#include "ns3/dhcp.h"
#include <stdint.h>
#include "ns3/application-container.h"
#include "ns3/node-container.h"
#include "ns3/object-factory.h"
#include "ns3/ipv4-address.h"
#include "ns3/enum.h"

#include "ns3/dhcp-server.h"
namespace ns3 {
class DHCPServerHelper
{
public:
	DHCPServerHelper (void);
	void SetAttribute (std::string name, const AttributeValue &value);
  ApplicationContainer Install (Ptr<Node> node) const;
  ApplicationContainer Install (std::string nodeName) const;
  ApplicationContainer Install (NodeContainer c) const;
	// TODO remove this method
	void GetNextAddress (Ptr<Application> app); 
private:
  Ptr<Application> InstallPriv (Ptr<Node> node) const;
  ObjectFactory m_factory; //!< Object factory.
};

class DHCPClientHelper
{
public:
	DHCPClientHelper (void);
	void SetAttribute (std::string name, const AttributeValue &value);
	
  ApplicationContainer Install (Ptr<Node> node) const;
  ApplicationContainer Install (std::string nodeName) const;
  ApplicationContainer Install (NodeContainer c) const;

private:
  Ptr<Application> InstallPriv (Ptr<Node> node) const;
  ObjectFactory m_factory; //!< Object factory.
};
}

#endif /* DHCP_HELPER_H */

