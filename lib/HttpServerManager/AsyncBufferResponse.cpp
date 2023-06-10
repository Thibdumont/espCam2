
#include "AsyncBufferResponse.h"

AsyncBufferResponse::AsyncBufferResponse(uint8_t *buf, size_t len, const char *contentType)
{
    _buf = buf;
    _len = len;
    _callback = nullptr;
    _code = 200;
    _contentLength = _len;
    _contentType = contentType;
    _index = 0;
}

AsyncBufferResponse::~AsyncBufferResponse()
{
    if (_buf != nullptr)
    {
        free(_buf);
    }
}

size_t AsyncBufferResponse::_fillBuffer(uint8_t *buf, size_t maxLen)
{
    size_t ret = _content(buf, maxLen, _index);
    if (ret != RESPONSE_TRY_AGAIN)
    {
        _index += ret;
    }
    return ret;
}

size_t AsyncBufferResponse::_content(uint8_t *buffer, size_t maxLen, size_t index)
{
    memcpy(buffer, _buf + index, maxLen);
    if ((index + maxLen) == _len)
    {
        free(_buf);
        _buf = nullptr;
    }
    return maxLen;
}
