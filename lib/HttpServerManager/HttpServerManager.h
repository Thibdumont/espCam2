#ifndef HTTP_SERVER_MANAGER_H
#define HTTP_SERVER_MANAGER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "AsyncJpegStreamResponse.h"
#include "AsyncFrameResponse.h"
#include "fileSystemManager.h"
#include <LittleFS.h>

class HttpServerManager
{
public:
    HttpServerManager(FileSystemManager *);
    AsyncWebSocket *getWebSocket();
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
    FileSystemManager *fileSystemManager;
    AsyncWebSocketClient *asyncWebSocketClient;
    AsyncWebServer *webServer = new AsyncWebServer(80);
    AsyncWebSocket *webSocket = new AsyncWebSocket("/ws");
    void init();
    void registerUIFiles();
    void onRoot(AsyncWebServerRequest *);
    void onAction(AsyncWebServerRequest *);
    void onCapture(AsyncWebServerRequest *);
    void onStream(AsyncWebServerRequest *);
    void processAction(AsyncWebServerRequest *, String);
    void onWebSocketEvent(AsyncWebSocket *, AsyncWebSocketClient *, AwsEventType, void *, uint8_t *, size_t);
};

#endif
