#pragma once
#include <iostream>


template <typename T>
class redirect_stream_wrapper
{
private:
    T& stream;
    std::streambuf* const old_buf;

public:
    bool redirected;
    redirect_stream_wrapper(T& src)
        :old_buf(src.rdbuf()), stream(src), redirected(false) {
    }
    ~redirect_stream_wrapper() {
        redirect_back();
    }
    void redirect(T& dest) {
        stream.rdbuf(dest.rdbuf());
        redirected = true;
    }
    void redirect_back() {
        stream.rdbuf(old_buf);
        redirected = false;
    }
};
