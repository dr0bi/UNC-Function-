#include "WebSocket.h"
#include <utility>
namespace unc::websocket_api {
WebSocket::WebSocket(std::shared_ptr<Transport> t):transport_(std::move(t)){}
bool WebSocket::connect(const std::string& url) { return transport_ && transport_->connect(url); }
bool WebSocket::send(const std::string& message) { return transport_ && transport_->connected() && transport_->send(message); }
void WebSocket::close() { if(transport_) transport_->close(); }
bool WebSocket::connected() const { return transport_ && transport_->connected(); }
void WebSocket::on_message(std::function<void(std::string)> h) { if(transport_) transport_->set_message_handler(std::move(h)); }
void WebSocket::on_close(std::function<void()> h) { if(transport_) transport_->set_close_handler(std::move(h)); }
} // namespace unc::websocket_api
