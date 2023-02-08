#pragma once

namespace boost
{

class noncopyable
{
  protected:
    noncopyable(const noncopyable& other) = delete;
    noncopyable& operator=(const noncopyable& other) = delete;
};

} /* namespace boost */
