# Server

## How to run the server ?

To run the server you need to have an server.properties, the file must be in the root of the directory server.

By default, if the file doesn't exist, the server generate the file with default value. The default value are :

```properties
{
    PROJECT_FILE=project.json
    PORT=4242
}
```

## How to understand the server ?

### Configuration

We have an class Config, this class is used to read and write in the server.properties. If you want add more field in the server.properties, you need to add the field in the default value and in the class Config.

```C++
namespace RType::Server
{
    class Config
    {
    public:
        Config(const std::string &file);
        ~Config();

        std::string &getField(const std::string &field);
        void setField(const std::string &field, const std::string &value);

        void save();

        void saveDefault(const std::unordered_map<std::string, std::string> &fields);

    private:
        std::string m_file;

        std::unordered_map<std::string, std::string> m_fields;
    };
} // namespace RType::Server
```

### Server

The server is the main class of the server, this class is used to run the server. The server is composed of a runtime, a network handler and a configuration.

```C++
namespace RType::Server
{

    class Server
    {
        using Runtime = RType::Runtime::IRuntime;
        using Registry = RType::Runtime::ECS::Registry;

    public:
        Server();
        ~Server();
        void run();

        void handleCommand(const std::string &command);

    private:
        long m_startingTimestamp;

        std::string m_fileProject;
        unsigned int m_port;

        bool m_running;
        std::shared_ptr<Runtime> m_runtime;
        void *m_libHandle;

        std::shared_ptr<RType::Runtime::ServerNetworkHandler> m_networkHandler;

        std::unique_ptr<Config> m_config;
        std::thread m_commandThread;
    };
}; // namespace RType::Server
```

In the constructor, we initialize the configuration, the runtime, the network handler and the command thread.

The command thread is used to read the command in the console. The command are used to interact with the server. Their commands are : `stop` to stop the server, `dump` to list all entity in the server.

The runtime, so the ECS is implemented in the runtime library. The runtime library is loaded in the constructor.

```C++
Server::Server()
{
    m_startingTimestamp =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    SERVER_LOG_INFO("Loading server...");
    try {
        SERVER_LOG_INFO("Loading config file...");
        m_config = std::make_unique<Config>("server.properties");

        SERVER_LOG_INFO("Loading runtime library...");
        m_libHandle = RType::Utils::Modules::LoadSharedLibrary("runtime");
        ASSERT(m_libHandle, "Failed to load runtime library")

        SERVER_LOG_INFO("Trying to get runtime entry point...");
        RType::Runtime::IRuntime *(*runtimeEntry)() =
            (RType::Runtime::IRuntime * (*)()) RType::Utils::Modules::GetFunction(m_libHandle, "RuntimeEntry");
        ASSERT(runtimeEntry, "Failed to get runtime entry point")
        SERVER_LOG_INFO("Runtime entry point loaded");

        SERVER_LOG_INFO("Initializing runtime...");
        m_runtime = std::shared_ptr<RType::Runtime::IRuntime>(runtimeEntry());
        m_runtime->Init();
        SERVER_LOG_INFO("Runtime initialized");
    } catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }

    this->m_fileProject = m_config->getField("PROJECT_FILE");
    SERVER_LOG_INFO("Project file: {0}", this->m_fileProject);
    m_runtime->setProjectPath(".");

    m_runtime->setServer(true);

    try {
        this->m_port = std::stoi(m_config->getField("PORT"));
    } catch (std::exception &e) {
        throw std::runtime_error("Invalid port");
    }
    if (this->m_port < 1024 || this->m_port > 65535)
        throw std::runtime_error("Invalid port range");

    m_networkHandler = std::make_shared<RType::Runtime::ServerNetworkHandler>(m_runtime);
}
```
