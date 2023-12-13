## How to setup UDPServer

```C++
RType::Network::IOContextHolder ioContext;
RType::Network::UDPServer server(*ioContext, 4242);

server.startReceive();
ioContext.run();
```

## How to setup UDPClient

```C++
RType::Network::IOContextHolder m_ioContext;
RType::Network::UDPClient client(*m_ioContext, "127.0.0.1", 4242);

client.startReceiveFromServer();
ioContext.run();
```