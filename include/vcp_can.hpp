#ifndef VCT_I2C_H
#define VCT_I2C_H

#include "vcp_messages.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstdio>

#include <map>
#include <functional>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

typedef struct can_frame CAN_Frame_S;

const uint8_t   VCP_DATAFRAME_LEN               = 8;
const uint8_t   AVG_INTERFACE_NAME_LEN          = 10;
const uint8_t   VCP_DATAFRAME_ID_BYTE           = 0;
const uint8_t   VCP_DATAFRAME_LEN_BYTE          = 1;
const uint8_t   VCP_DATAFRAME_DATA_STRT_BYTE    = 2;
const uint32_t  VCP_DFLT_CAN_ID                 = 0xB1;

class CANBusHandler
{
    public:

        char        can_if_name[AVG_INTERFACE_NAME_LEN];
        uint8_t     node_address;
        uint8_t     socket_fd;

        CANBusHandler(char can_if_name_[AVG_INTERFACE_NAME_LEN], uint8_t device_address_);
        ~CANBusHandler();        
        int InitBus();
        int CloseBus();
        int EncodeCANFrame(VCP_Frame_S *src_vcp_frame_, CAN_Frame_S *dst_can_frame_);
        int DecodeCANFrame(CAN_Frame_S *src_can_frame_, VCP_Frame_S *dst_vcp_frame_);
        int SendCANFrame(CAN_Frame_S *can_frame_);
        int ReceiveCANFrame(CAN_Frame_S *can_frame_);
};

#endif
