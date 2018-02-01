/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "dhcp-client-helper.h"
#include "ns3/uinteger.h"
#include "ns3/string.h"
#include "ns3/dhcp.h"
#include "ns3/names.h"
#include "ns3/dhcp-client.h"
namespace ns3 {
// For DHCP Client
	DHCPClientHelper::DHCPClientHelper (void)
	{
		std::cout << "cli:1" << std::endl;
		m_factory.SetTypeId (DHCPClient::GetTypeId ());
	}
	
	void
	DHCPClientHelper::SetAttribute (std::string name, const AttributeValue &value)
	{
		std::cout << "cli:2" << std::endl;
 		m_factory.Set (name, value);
	}

	ApplicationContainer
	DHCPClientHelper::Install (Ptr<Node> node) const
	{
		std::cout << "cli:3" << std::endl;
  	return ApplicationContainer (InstallPriv (node));
	}

	ApplicationContainer
	DHCPClientHelper::Install (std::string nodeName) const
	{
		std::cout << "cli:4" << std::endl;
  	Ptr<Node> node = Names::Find<Node> (nodeName);
  	return ApplicationContainer (InstallPriv (node));
	}

	ApplicationContainer
	DHCPClientHelper::Install (NodeContainer c) const
	{
		std::cout << "cli:5" << std::endl;
  	ApplicationContainer apps;
  	for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      apps.Add (InstallPriv (*i));
    }

  	return apps;
	}

	Ptr<Application>
	DHCPClientHelper::InstallPriv (Ptr<Node> node) const
	{
		std::cout << "cli:6" << std::endl;
  	Ptr<Application> app = m_factory.Create<DHCPClient> ();
  	node->AddApplication (app);

  	return app;
	}
}
