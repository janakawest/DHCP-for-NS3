/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "dhcp-server-helper.h"
#include "ns3/uinteger.h"
#include "ns3/string.h"
#include "ns3/dhcp.h"
#include "ns3/names.h"
#include "ns3/dhcp-server.h"
namespace ns3 {
// For DHCP Server
	DHCPServerHelper::DHCPServerHelper (void)
	{
		std::cout << "srv:1" << std::endl;
		m_factory.SetTypeId (DHCPServer::GetTypeId ());
	}
	
	void
	DHCPServerHelper::SetAttribute (std::string name, const AttributeValue &value)
	{
		std::cout << "srv:2" << std::endl;
 		m_factory.Set (name, value);
	}

	// TODO remove this method
	void 
	DHCPServerHelper::GetNextAddress (Ptr<Application> app)
	{
		//std::cout << "srv:3" << std::endl;
		std::cout << 
							app->GetObject<DHCPServer> ()->GetNextAddress () << 
							std::endl;
	}
	
	ApplicationContainer
	DHCPServerHelper::Install (Ptr<Node> node) const
	{
		std::cout << "srv:3" << std::endl;
  	return ApplicationContainer (InstallPriv (node));
	}

	ApplicationContainer
	DHCPServerHelper::Install (std::string nodeName) const
	{
		std::cout << "srv:4" << std::endl;
  	Ptr<Node> node = Names::Find<Node> (nodeName);
  	return ApplicationContainer (InstallPriv (node));
	}

	ApplicationContainer
	DHCPServerHelper::Install (NodeContainer c) const
	{
		std::cout << "srv:5" << std::endl;
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
		std::cout << "srv:6" << std::endl;
  	Ptr<Application> app = m_factory.Create<DHCPServer> ();
  	node->AddApplication (app);

  	return app;
	}

}
