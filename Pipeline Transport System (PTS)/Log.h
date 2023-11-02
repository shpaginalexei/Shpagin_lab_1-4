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

//
//class redirect_output_wrapper
//{
//private:
//    std::ostream& stream;
//    std::streambuf* const old_buf;
//public:
//    redirect_output_wrapper(std::ostream& src)
//        :old_buf(src.rdbuf()), stream(src) {
//    }
//    ~redirect_output_wrapper() {
//        stream.rdbuf(old_buf);
//    }
//    void redirect(std::ostream& dest) {
//        stream.rdbuf(dest.rdbuf());
//    }
//};
//
//class redirect_input_wrapper
//{
//private:
//    std::istream& stream;
//    std::streambuf* const old_buf;
//
//public:
//    bool redirected;
//    redirect_input_wrapper(std::istream& src)
//        :old_buf(src.rdbuf()), stream(src), redirected(false) {
//    }
//    ~redirect_input_wrapper() {
//        redirect_back();
//    }
//    void redirect(std::istream& dest) {
//        stream.rdbuf(dest.rdbuf());
//        redirected = true;
//    }
//    void redirect_back() {
//        stream.rdbuf(old_buf);
//        redirected = false;
//    }
//};
