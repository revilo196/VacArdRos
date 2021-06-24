#ifndef _ROS_vacbot_msgs_MotorCurrent_h
#define _ROS_vacbot_msgs_MotorCurrent_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace vacbot_msgs
{

  class MotorCurrent : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _current_l_type;
      _current_l_type current_l;
      typedef float _current_r_type;
      _current_r_type current_r;

    MotorCurrent():
      header(),
      current_l(0),
      current_r(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_current_l;
      u_current_l.real = this->current_l;
      *(outbuffer + offset + 0) = (u_current_l.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_current_l.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_current_l.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_current_l.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->current_l);
      union {
        float real;
        uint32_t base;
      } u_current_r;
      u_current_r.real = this->current_r;
      *(outbuffer + offset + 0) = (u_current_r.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_current_r.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_current_r.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_current_r.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->current_r);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_current_l;
      u_current_l.base = 0;
      u_current_l.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_current_l.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_current_l.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_current_l.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->current_l = u_current_l.real;
      offset += sizeof(this->current_l);
      union {
        float real;
        uint32_t base;
      } u_current_r;
      u_current_r.base = 0;
      u_current_r.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_current_r.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_current_r.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_current_r.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->current_r = u_current_r.real;
      offset += sizeof(this->current_r);
     return offset;
    }

    virtual const char * getType() override { return "vacbot_msgs/MotorCurrent"; };
    virtual const char * getMD5() override { return "15bb4b6027f9d45c4c9659e593fc792e"; };

  };

}
#endif
