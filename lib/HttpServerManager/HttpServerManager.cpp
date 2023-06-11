#include "HttpServerManager.h"

HttpServerManager::HttpServerManager(FileSystemManager *fileSystemManager)
{
    this->fileSystemManager = fileSystemManager;
    init();
}

AsyncWebSocket *HttpServerManager::getWebSocket()
{
    return webSocket;
}

void HttpServerManager::init()
{

    webServer->on("/",
                  HTTP_GET,
                  [this](AsyncWebServerRequest *request)
                  { HttpServerManager::staticOnRoot(request, this); });
    webServer->on("/actions", HTTP_GET,
                  [this](AsyncWebServerRequest *request)
                  { HttpServerManager::staticOnAction(request, this); });
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

void HttpServerManager::onRoot(AsyncWebServerRequest *request)
{
    Serial.println("Root requested");
    request->send(LittleFS, "/index.html", "text/html");
}

void HttpServerManager::onAction(AsyncWebServerRequest *request)
{
    std::array<String, 4> commands = {"direction", "servo",
                                      "speed", "speedAuto"};
    for (const auto &command : commands)
    {
        if (request->hasParam(command))
        {
            processAction(request, command);
        }
    }
}

void HttpServerManager::processAction(AsyncWebServerRequest *request, String param)
{
    request->send(200);
    StaticJsonDocument<200> json;
    json[param] = request->getParam(param)->value();
    serializeJson(json, Serial2);
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