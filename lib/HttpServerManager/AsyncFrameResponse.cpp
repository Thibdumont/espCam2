
#include "AsyncFrameResponse.h"

AsyncFrameResponse::AsyncFrameResponse()
{
    fb = esp_camera_fb_get();
    _callback = nullptr;
    _code = 200;
    _contentLength = fb->len;
    _contentType = JPG_CONTENT_TYPE;
    _index = 0;
}

AsyncFrameResponse::~AsyncFrameResponse()
{
    if (fb != nullptr)
    {
        esp_camera_fb_return(fb);
    }
}

size_t AsyncFrameResponse::_fillBuffer(uint8_t *buf, size_t maxLen)
{
    size_t ret = _content(buf, maxLen, _index);
    if (ret != RESPONSE_TRY_AGAIN)
    {
        _index += ret;
    }
    return ret;
}

size_t AsyncFrameResponse::_content(uint8_t *buffer, size_t maxLen, size_t index)
{
    memcpy(buffer, fb->buf + index, maxLen);
    if ((index + maxLen) == fb->len)
    {
        esp_camera_fb_return(fb);
        fb = nullptr;
    }
    return maxLen;
}
