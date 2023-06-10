#ifndef ASYNC_JPEG_STREAM_RESPONSE_H
#define ASYNC_JPEG_STREAM_RESPONSE_H

#include "esp_camera.h"
#include "ESPAsyncWebServer.h"
#include "AsyncCommon.h"

/*
From : me-no-dev
https://gist.github.com/me-no-dev/d34fba51a8f059ac559bf62002e61aa3
*/

#define PART_BOUNDARY "123456789000000000000987654321"
static const char *STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char *STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char *STREAM_PART = "Content-Type: %s\r\nContent-Length: %u\r\n\r\n";

typedef struct
{
    camera_fb_t *fb;
    size_t index;
} camera_frame_t;

class AsyncJpegStreamResponse : public AsyncAbstractResponse
{
private:
    camera_frame_t _frame;
    size_t _index;
    size_t _jpg_buf_len;
    uint8_t *_jpg_buf;
    long lastAsyncRequest;

public:
    AsyncJpegStreamResponse();
    ~AsyncJpegStreamResponse();
    bool _sourceValid() const { return true; };
    virtual size_t _fillBuffer(uint8_t *buf, size_t maxLen);
    size_t _content(uint8_t *buffer, size_t maxLen, size_t index);
};

#endif
