/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/core-module.h"
#include "ns3/dhcp-helper.h"

#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-routing-table-entry.h"

using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("DHCPimpleExample");

int 
main (int argc, char *argv[])
{
  bool verbose = true;

  CommandLine cmd;

  cmd.AddValue ("verbose", "Tell application to log if true", verbose);

  cmd.Parse (argc,argv);


  Ptr<Node> sendai = CreateObject<Node> (); // 1
  Names::Add ("SendaiRouter", sendai); 

	Ptr<Node> DHCPServer = CreateObject<Node> ();
  Names::Add ("DHCPServer", DHCPServer);
	Ptr<Node> client = CreateObject<Node> ();
  Names::Add ("DHCPClient", client);

  //client<-->Router
  NodeContainer net1 (DHCPServer, client, sendai); // Sendai --> i1

  //NS_LOG_INFO ("Set 1Gbps Links.");
  PointToPointHelper p2p_1Gbps;
  p2p_1Gbps.SetDeviceAttribute ("DataRate", StringValue ("1Gbps"));
  p2p_1Gbps.SetChannelAttribute ("Delay", StringValue ("2ms")); // Transmission Delay is a guess

	// links between clients and their gateway routers
	NetDeviceContainer ndc1 = p2p_1Gbps.Install (net1);// net1 Sendai --> i1

	InternetStackHelper internetNodes;
	internetNodes.Install (net1);

	//NS_LOG_INFO ("Assign IPv4 Addresses.");
	Ipv4AddressHelper ipv4;

	// For clients
	ipv4.SetBase ("192.168.16.0","255.255.255.252");
	Ipv4InterfaceContainer iic1 = ipv4.Assign (ndc1);	// Sendai,i1 <--> client1,1

	DHCPServerHelper dhcpserver;
	//dhcpserver.SetAttribute ("SetServerAddress", 
	//											Ipv4AddressValue (DHCPServer->GetObject<Ipv4> ()->GetAddress (1, 0).GetLocal ()));
  ApplicationContainer appsLocal = dhcpserver.Install (DHCPServer);	
	dhcpserver.GetNextAddress (appsLocal.Get (0));
	dhcpserver.GetNextAddress (appsLocal.Get (0));
	dhcpserver.GetNextAddress (appsLocal.Get (0));
	dhcpserver.GetNextAddress (appsLocal.Get (0));
	dhcpserver.GetNextAddress (appsLocal.Get (0));
	dhcpserver.GetNextAddress (appsLocal.Get (0));
	dhcpserver.GetNextAddress (appsLocal.Get (0));

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}


