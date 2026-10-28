#pragma once
#include <functional>
#include <memory>
#include <string>
namespace unc::websocket_api {
class Transport {
public:
    virtual ~Transport() = default;
    virtual bool connect(const std::string& url) = 0;
    virtual bool send(const std::string& message) = 0;
    virtual void close() = 0;
    virtual bool connected() const = 0;
    virtual void set_message_handler(std::function<void(std::string)> handler) = 0;
    virtual void set_close_handler(std::function<void()> handler) = 0;
};
// Network policy, TLS, and endpoint allowlists belong to the host implementation.
class WebSocket {
public:
    explicit WebSocket(std::shared_ptr<Transport> transport);
    [[nodiscard]] bool connect(const std::string& url);
    [[nodiscard]] bool send(const std::string& message);
    void close();
    [[nodiscard]] bool connected() const;
    void on_message(std::function<void(std::string)> handler);
    void on_close(std::function<void()> handler);
private:
    std::shared_ptr<Transport> transport_;
};
} // namespace unc::websocket_api
