#ifndef ASYNC_FRAME_RESPONSE_H
#define ASYNC_FRAME_RESPONSE_H

#include "esp_camera.h"
#include "ESPAsyncWebServer.h"
#include "AsyncCommon.h"

/*
From : me-no-dev
https://gist.github.com/me-no-dev/d34fba51a8f059ac559bf62002e61aa3
*/
class AsyncFrameResponse : public AsyncAbstractResponse
{
private:
    camera_fb_t *fb;
    size_t _index;

public:
    AsyncFrameResponse();
    ~AsyncFrameResponse();
    bool _sourceValid() const { return fb != nullptr; };
    virtual size_t _fillBuffer(uint8_t *buf, size_t maxLen);
    size_t _content(uint8_t *buffer, size_t maxLen, size_t index);
};

#endif
