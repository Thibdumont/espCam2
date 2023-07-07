#include "HttpServerManager.h"

HttpServerManager::HttpServerManager(
    FileSystemManager *fileSystemManager,
    CameraManager *cameraManager)
{
    this->fileSystemManager = fileSystemManager;
    this->cameraManager = cameraManager;
    init();
}

AsyncWebSocket *HttpServerManager::getWebSocket()
{
    return webSocket;
}

void HttpServerManager::init()
{
    registerUIFiles();

    webServer->on("/capture", HTTP_GET,
                  [this](AsyncWebServerRequest *request)
                  { HttpServerManager::staticOnCapture(request, this); });
    webServer->on("/stream", HTTP_GET,
                  [this](AsyncWebServerRequest *request)
                  { HttpServerManager::staticOnStream(request, this); });

    webSocket->onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
                       { HttpServerManager::staticOnWebSocketEvent(server, client, type, arg, data, len, this); });
    webServer->addHandler(webSocket);

    webServer->begin();
    Serial.println("HTTP server started");
}

void HttpServerManager::registerUIFiles()
{
    webServer->on("/",
                  HTTP_GET,
                  [this](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/index.html", "text/html"); });

    webServer->on("/main.js",
                  HTTP_GET,
                  [this](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/main.js", "text/javascript"); });

    webServer->on("/polyfills.js",
                  HTTP_GET,
                  [this](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/polyfills.js", "text/javascript"); });

    webServer->on("/runtime.js",
                  HTTP_GET,
                  [this](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/runtime.js", "text/javascript"); });

    webServer->on("/styles.css",
                  HTTP_GET,
                  [this](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/styles.css", "text/css"); });
}

void HttpServerManager::onCapture(AsyncWebServerRequest *request)
{
    AsyncFrameResponse *response = new AsyncFrameResponse();
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
}

void HttpServerManager::onStream(AsyncWebServerRequest *request)
{
    AsyncJpegStreamResponse *response = new AsyncJpegStreamResponse();
    if (!response)
    {
        request->send(501);
        return;
    }
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
}

void HttpServerManager::onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_DATA)
    {
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->final && info->index == 0 && info->len == len)
        {
            // the whole message is in a single frame and we got all of it's data
            if (info->opcode == WS_TEXT)
            {
                data[len] = 0;
                Serial2.println((char *)data);
                processCommands((char *)data);
            }
        }
    }
    else if (type == WS_EVT_CONNECT)
    {
        Serial.println("Websocket client connection received");
        client->text("Connection established");
        asyncWebSocketClient = client;
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        asyncWebSocketClient = nullptr;
        Serial.println("Client disconnected");
    }
}

void HttpServerManager::processCommands(char *json)
{
    StaticJsonDocument<200> jsonDoc;
    deserializeJson(jsonDoc, json);

    if (jsonDoc.containsKey("cameraResolution"))
    {
        cameraManager->changeResolution((int)jsonDoc["cameraResolution"]);
    }
    else if (jsonDoc.containsKey("cameraQuality"))
    {
        cameraManager->changeQuality((int)jsonDoc["cameraQuality"]);
    }
    else if (jsonDoc.containsKey("cameraContrast"))
    {
        cameraManager->changeContrast((int)jsonDoc["cameraContrast"]);
    }
    else if (jsonDoc.containsKey("cameraBrightness"))
    {
        cameraManager->changeBrightness((int)jsonDoc["cameraBrightness"]);
    }
    else if (jsonDoc.containsKey("cameraSaturation"))
    {
        cameraManager->changeSaturation((int)jsonDoc["cameraSaturation"]);
    }
}