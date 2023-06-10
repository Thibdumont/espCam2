#ifndef ASYNC_BUFFER_RESPONSE_H
#define ASYNC_BUFFER_RESPONSE_H

#include <Arduino.h>
#include "ESPAsyncWebServer.h"

/*
From : me-no-dev
https://gist.github.com/me-no-dev/d34fba51a8f059ac559bf62002e61aa3
*/

class AsyncBufferResponse : public AsyncAbstractResponse
{
private:
    uint8_t *_buf;
    size_t _len;
    size_t _index;

public:
    AsyncBufferResponse(uint8_t *buf, size_t len, const char *contentType);
    ~AsyncBufferResponse();
    bool _sourceValid() const { return _buf != nullptr; };
    virtual size_t _fillBuffer(uint8_t *buf, size_t maxLen);
    size_t _content(uint8_t *buffer, size_t maxLen, size_t index);
};

#endif
