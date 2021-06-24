#ifndef _ROS_vacbot_msgs_SonarPacket_h
#define _ROS_vacbot_msgs_SonarPacket_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/Range.h"

namespace vacbot_msgs
{

  class SonarPacket : public ros::Msg
  {
    public:
      sensor_msgs::Range ranges[3];

    SonarPacket():
      ranges()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      for( uint32_t i = 0; i < 3; i++){
      offset += this->ranges[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      for( uint32_t i = 0; i < 3; i++){
      offset += this->ranges[i].deserialize(inbuffer + offset);
      }
     return offset;
    }

    virtual const char * getType() override { return "vacbot_msgs/SonarPacket"; };
    virtual const char * getMD5() override { return "b72db098d4ed346ce682a1d5e70d327c"; };

  };

}
#endif
