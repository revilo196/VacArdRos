#ifndef _ROS_vacbot_msgs_OpticalDelta_h
#define _ROS_vacbot_msgs_OpticalDelta_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace vacbot_msgs
{

  class OpticalDelta : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _deltaX_type;
      _deltaX_type deltaX;
      typedef float _deltaY_type;
      _deltaY_type deltaY;
      typedef float _deltaAngle_type;
      _deltaAngle_type deltaAngle;
      typedef uint8_t _state_type;
      _state_type state;

    OpticalDelta():
      header(),
      deltaX(0),
      deltaY(0),
      deltaAngle(0),
      state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_deltaX;
      u_deltaX.real = this->deltaX;
      *(outbuffer + offset + 0) = (u_deltaX.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_deltaX.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_deltaX.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_deltaX.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->deltaX);
      union {
        float real;
        uint32_t base;
      } u_deltaY;
      u_deltaY.real = this->deltaY;
      *(outbuffer + offset + 0) = (u_deltaY.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_deltaY.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_deltaY.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_deltaY.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->deltaY);
      union {
        float real;
        uint32_t base;
      } u_deltaAngle;
      u_deltaAngle.real = this->deltaAngle;
      *(outbuffer + offset + 0) = (u_deltaAngle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_deltaAngle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_deltaAngle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_deltaAngle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->deltaAngle);
      *(outbuffer + offset + 0) = (this->state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_deltaX;
      u_deltaX.base = 0;
      u_deltaX.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_deltaX.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_deltaX.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_deltaX.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->deltaX = u_deltaX.real;
      offset += sizeof(this->deltaX);
      union {
        float real;
        uint32_t base;
      } u_deltaY;
      u_deltaY.base = 0;
      u_deltaY.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_deltaY.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_deltaY.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_deltaY.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->deltaY = u_deltaY.real;
      offset += sizeof(this->deltaY);
      union {
        float real;
        uint32_t base;
      } u_deltaAngle;
      u_deltaAngle.base = 0;
      u_deltaAngle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_deltaAngle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_deltaAngle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_deltaAngle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->deltaAngle = u_deltaAngle.real;
      offset += sizeof(this->deltaAngle);
      this->state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->state);
     return offset;
    }

    virtual const char * getType() override { return "vacbot_msgs/OpticalDelta"; };
    virtual const char * getMD5() override { return "4647cb93f1714a5793d6f0083265e40f"; };

  };

}
#endif
