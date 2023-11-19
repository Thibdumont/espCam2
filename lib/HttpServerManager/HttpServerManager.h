#ifndef HTTP_SERVER_MANAGER_H
#define HTTP_SERVER_MANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "AsyncJpegStreamResponse.h"
#include "AsyncFrameResponse.h"
#include "RobotStateManager.h"

class HttpServerManager
{
public:
    HttpServerManager(RobotStateManager *);
    AsyncWebSocket *getWebSocket();
    static void staticOnCapture(AsyncWebServerRequest *request, void *thisInstance)
    {
        HttpServerManager *self = reinterpret_cast<HttpServerManager *>(thisInstance);
        self->onCapture(request);
    }
    static void staticOnStream(AsyncWebServerRequest *request, void *thisInstance)
    {
        HttpServerManager *self = reinterpret_cast<HttpServerManager *>(thisInstance);
        self->onStream(request);
    }

    static void staticOnWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len, void *thisInstance)
    {
        HttpServerManager *self = reinterpret_cast<HttpServerManager *>(thisInstance);
        self->onWebSocketEvent(server, client, type, arg, data, len);
    }

private:
    RobotStateManager *robotStateManager;
    AsyncWebSocketClient *asyncWebSocketClient;
    AsyncWebServer *webServer = new AsyncWebServer(80);
    AsyncWebSocket *webSocket = new AsyncWebSocket("/ws");
    void init();
    void registerUIFiles();
    void onRoot(AsyncWebServerRequest *);
    void onCapture(AsyncWebServerRequest *);
    void onStream(AsyncWebServerRequest *);
    void onWebSocketEvent(AsyncWebSocket *, AsyncWebSocketClient *, AwsEventType, void *, uint8_t *, size_t);
    void processCommands(char *json);
};

#endif
