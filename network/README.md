# Comment fonctionne la librairie network et comment s'en servir ?

## How to setup UDPServer
```C++
RType::Network::IOContextHolder ioContext;
RType::Network::UDPServer server(*ioContext, 4242);

server.startReceive([&](RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint) {
    // Handle
});
ioContext.run();
```

## How to setup UDPClient
```C++
RType::Network::IOContextHolder m_ioContext;
RType::Network::UDPClient client(*m_ioContext, "127.0.0.1", 4242);

client.startReceiveFromServer([&](RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint) {
    // Handle
});
ioContext.run();
```

# Prepare for V2:
Currently packets are hardcoder and it is not possible to master sending packets from systems. It is also not possible to choose the actions to perform when receiving packets.

The aim of this V2 is:
- Implementation of the creation of Packet from editor
- The configuration of actions to be done upon receipt of packets
- Configuration to send packets in entities