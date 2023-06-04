#ifndef HTTP_SERVER_MANAGER_H
#define HTTP_SERVER_MANAGER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

class HttpServerManager
{
public:
    HttpServerManager();
    static void staticOnRoot(AsyncWebServerRequest *request, void *thisInstance)
    {
        HttpServerManager *self = reinterpret_cast<HttpServerManager *>(thisInstance);
        self->onRoot(request);
    }
    static void staticOnAction(AsyncWebServerRequest *request, void *thisInstance)
    {
        HttpServerManager *self = reinterpret_cast<HttpServerManager *>(thisInstance);
        self->onAction(request);
    }
    static void staticOnWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len, void *thisInstance)
    {
        HttpServerManager *self = reinterpret_cast<HttpServerManager *>(thisInstance);
        self->onWebSocketEvent(server, client, type, arg, data, len);
    }

private:
    AsyncWebSocketClient *asyncWebSocketClient;
    AsyncWebServer *webServer = new AsyncWebServer(8080);
    AsyncWebSocket *webSocket = new AsyncWebSocket("/ws");
    void init();
    void onRoot(AsyncWebServerRequest *);
    void onAction(AsyncWebServerRequest *);
    void processAction(AsyncWebServerRequest *, String);
    void onWebSocketEvent(AsyncWebSocket *, AsyncWebSocketClient *, AwsEventType, void *, uint8_t *, size_t);
};

#endif
