/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "dhcp-helper.h"
#include "ns3/uinteger.h"
#include "ns3/string.h"
#include "ns3/dhcp.h"
#include "ns3/names.h"
#include "ns3/dhcp-server.h"
#include "ns3/dhcp-client.h"
namespace ns3 {
// For DHCP Server
	DHCPServerHelper::DHCPServerHelper (void)
	{
		m_factory.SetTypeId (DHCPServer::GetTypeId ());
	}
	
	void
	DHCPServerHelper::SetAttribute (std::string name, const AttributeValue &value)
	{
 		m_factory.Set (name, value);
	}

	// TODO remove this method
	void 
	DHCPServerHelper::GetNextAddress (Ptr<Application> app)
	{
		std::cout << 
							app->GetObject<DHCPServer> ()->GetNextAddress () << 
							std::endl;
	}
	
	ApplicationContainer
	DHCPServerHelper::Install (Ptr<Node> node) const
	{
  	return ApplicationContainer (InstallPriv (node));
	}

	ApplicationContainer
	DHCPServerHelper::Install (std::string nodeName) const
	{
  	Ptr<Node> node = Names::Find<Node> (nodeName);
  	return ApplicationContainer (InstallPriv (node));
	}

	ApplicationContainer
	DHCPServerHelper::Install (NodeContainer c) const
	{
  	ApplicationContainer apps;
  	for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      apps.Add (InstallPriv (*i));
    }

  	return apps;
	}

	Ptr<Application>
	DHCPServerHelper::InstallPriv (Ptr<Node> node) const
	{
  	Ptr<Application> app = m_factory.Create<DHCPServer> ();
  	node->AddApplication (app);

  	return app;
	}

// For DHCP Client
	DHCPClientHelper::DHCPClientHelper (void)
	{
		m_factory.SetTypeId (DHCPClient::GetTypeId ());
	}
	
	void
	DHCPClientHelper::SetAttribute (std::string name, const AttributeValue &value)
	{
 		m_factory.Set (name, value);
	}

	ApplicationContainer
	DHCPClientHelper::Install (Ptr<Node> node) const
	{
  	return ApplicationContainer (InstallPriv (node));
	}

	ApplicationContainer
	DHCPClientHelper::Install (std::string nodeName) const
	{
  	Ptr<Node> node = Names::Find<Node> (nodeName);
  	return ApplicationContainer (InstallPriv (node));
	}

	ApplicationContainer
	DHCPClientHelper::Install (NodeContainer c) const
	{
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
  	Ptr<Application> app = m_factory.Create<DHCPClient> ();
  	node->AddApplication (app);

  	return app;
	}
}
