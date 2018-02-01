/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/core-module.h"
#include "ns3/dhcp-client-helper.h"
#include "ns3/dhcp-server-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/command-line.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("DHCPExample");

int
main (int argc, char *argv[])
{
	CommandLine cmd;
	cmd.Parse(argc,argv);

	NodeContainer csmaNodes;
	csmaNodes.Create (5);

	CsmaHelper csma;

	csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
	csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

	NetDeviceContainer csmaDevices;
	csmaDevices = csma.Install (csmaNodes);

	InternetStackHelper stack;
	stack.Install (csmaNodes);

	Ipv4AddressHelper address;
	address.SetBase ("10.1.1.0", "255.255.255.0");

	Ipv4InterfaceContainer csmaInterfaces;
	csmaInterfaces = address.Assign (csmaDevices);

	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
	//UdpEchoServerHelper echoServer (9);
	//ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get (0));

	DHCPServerHelper dhcpserver;
	dhcpserver.SetAttribute ("SetServerAddress", 
														Ipv4AddressValue (csmaNodes.Get (0)->GetObject<Ipv4> ()
														->GetAddress (1, 0).GetLocal ()));
  ApplicationContainer serverApps = dhcpserver.Install (csmaNodes.Get (0));

	serverApps.Start (Seconds (1.0));
	serverApps.Stop (Seconds (50.0));

	//dhcpserver.GetNextAddress (serverApps.Get (0));
	//dhcpserver.GetNextAddress (serverApps.Get (0));
	//dhcpserver.GetNextAddress (serverApps.Get (0));
	//dhcpserver.GetNextAddress (serverApps.Get (0));
	//dhcpserver.GetNextAddress (serverApps.Get (0));
	//dhcpserver.GetNextAddress (serverApps.Get (0));
	//dhcpserver.GetNextAddress (serverApps.Get (0));
	
	DHCPClientHelper dhcpClient;
	dhcpClient.SetAttribute ("InterfaceId", UintegerValue (0));
	ApplicationContainer clientApps = dhcpClient.Install (csmaNodes.Get (4));
	

//	UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (0), 9);
//
//	echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
//	echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.)));
//	echoClient.SetAttribute ("PacketSize", UintegerValue (1024));
//
//	ApplicationContainer clientApps = echoClient.Install (csmaNodes.Get (2));
//
	clientApps.Start (Seconds (200.0));
	clientApps.Stop (Seconds (500.0));

	Simulator::Stop (Seconds (502));
	Simulator::Run ();
	Simulator::Destroy ();
	return 0;
}
