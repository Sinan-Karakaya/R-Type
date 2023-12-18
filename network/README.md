# How does the network library work and how to use it?

The network library works with Packet exchange. For more information on packets, see rfc-42565.

## How to setup UDPServer

### Receive packets
```C++
RType::Network::IOContextHolder ioContext;
RType::Network::UDPServer server(*ioContext, 4242);

server.startReceive([&](RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint) {
    // Handle
});
ioContext.run();
```

### Send packets
```C++
RType::Network::IOContextHolder ioContext;
RType::Network::UDPServer server(*ioContext, 4242);

RType::Network::PacketPing packet;
asio::ip::udp::endpoint &clientEndpoint;
server.sendData(packet, clientEndpoint);
```

## How to setup UDPClient

### Receive packets
```C++
RType::Network::IOContextHolder m_ioContext;
RType::Network::UDPClient client(*m_ioContext, "127.0.0.1", 4242);

client.startReceiveFromServer([&](RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint) {
    // Handle
});
ioContext.run();
```

### Send packets
```C++
RType::Network::IOContextHolder m_ioContext;
RType::Network::UDPClient client(*m_ioContext, "127.0.0.1", 4242);

RType::Network::PacketPing packet;
client.sendToServer(packet);
```

# Prepare for V2:
Currently packets are hardcoder and it is not possible to master sending packets from systems. It is also not possible to choose the actions to perform when receiving packets.

The aim of this V2 is:
- Implementation of the creation of Packet from editor
- The configuration of actions to be done upon receipt of packets
- Configuration to send packets in entities