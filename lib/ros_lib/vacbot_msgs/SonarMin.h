#ifndef _ROS_vacbot_msgs_SonarMin_h
#define _ROS_vacbot_msgs_SonarMin_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace vacbot_msgs
{

  class SonarMin : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      float ranges[3];
      float angles[3];

    SonarMin():
      header(),
      ranges(),
      angles()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_rangesi;
      u_rangesi.real = this->ranges[i];
      *(outbuffer + offset + 0) = (u_rangesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rangesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rangesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rangesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ranges[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_anglesi;
      u_anglesi.real = this->angles[i];
      *(outbuffer + offset + 0) = (u_anglesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_anglesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_anglesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_anglesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angles[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_rangesi;
      u_rangesi.base = 0;
      u_rangesi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rangesi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rangesi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rangesi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ranges[i] = u_rangesi.real;
      offset += sizeof(this->ranges[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_anglesi;
      u_anglesi.base = 0;
      u_anglesi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_anglesi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_anglesi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_anglesi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angles[i] = u_anglesi.real;
      offset += sizeof(this->angles[i]);
      }
     return offset;
    }

    virtual const char * getType() override { return "vacbot_msgs/SonarMin"; };
    virtual const char * getMD5() override { return "79e24f2a3a0d70e2b8e089de0a365254"; };

  };

}
#endif
