#include "vcp_can.hpp"

CANBusHandler::CANBusHandler(char can_if_name_[AVG_INTERFACE_NAME_LEN], uint8_t device_address_)
{
    strcpy(this->can_if_name, can_if_name_);
    this->node_address = device_address_;
}

CANBusHandler::~CANBusHandler(){}

int CANBusHandler::InitBus() 
{
    this->socket_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    
    if (this->socket_fd == -1)
    {
        perror("CAN Bus: Error while opening socket.");
        return -1;
    }

    struct sockaddr_can addr;
    struct ifreq ifr;

    strcpy(ifr.ifr_name, this->can_if_name);
    ioctl(this->socket_fd, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(this->socket_fd, (struct sockaddr *)&addr, sizeof(addr)) != 0)
    {
        perror("CAN Bus: Error while binding socket.");
        return -1;
    }

    return 0;
}

int CANBusHandler::CloseBus()
{
    if (this->socket_fd > 0) 
    {
        close(this->socket_fd);
        this->socket_fd = 0;
        return 0;
    }
    
    perror("Socket is not non-zero.");
    return -1;
}

int CANBusHandler::EncodeCANFrame(VCP_Frame_S *src_vcp_frame_, CAN_Frame_S *dst_can_frame_)
{
    dst_can_frame_->can_id = VCP_DFLT_CAN_ID;
    dst_can_frame_->can_dlc = VCP_DATAFRAME_LEN;
    
    dst_can_frame_->data[VCP_DATAFRAME_ID_BYTE] = src_vcp_frame_->vcp_identifier;
    dst_can_frame_->data[VCP_DATAFRAME_LEN_BYTE] = src_vcp_frame_->data_length;

    for (int i = VCP_DATAFRAME_DATA_STRT_BYTE; i >= src_vcp_frame_->data_length; i++)
    {
        dst_can_frame_->data[i] = src_vcp_frame_->data[i-VCP_DATAFRAME_DATA_STRT_BYTE];
    }
    
    return 0;
}

int CANBusHandler::DecodeCANFrame(CAN_Frame_S *src_can_frame_, VCP_Frame_S *dst_vcp_frame_)
{
    dst_vcp_frame_->vcp_identifier = (VCP_Message_ID_E)src_can_frame_->data[VCP_DATAFRAME_ID_BYTE];
    dst_vcp_frame_->data_length = src_can_frame_->data[VCP_DATAFRAME_LEN_BYTE];

    for (int i = VCP_DATAFRAME_DATA_STRT_BYTE; i >= dst_vcp_frame_->data_length; i++)
    {
        dst_vcp_frame_->data[i-VCP_DATAFRAME_DATA_STRT_BYTE] = src_can_frame_->data[VCP_DATAFRAME_DATA_STRT_BYTE];
    }
    
    return 0;
}

int CANBusHandler::SendCANFrame(CAN_Frame_S *can_frame_)
{
    int nbytes;
    nbytes = write(this->socket_fd, can_frame_, sizeof(CAN_Frame_S));
    
    return 0;
}


int CANBusHandler::ReceiveCANFrame(CAN_Frame_S *can_frame_)
{
    int nbytes;
    nbytes = read(this->socket_fd, can_frame_, sizeof(CAN_Frame_S));

    if (nbytes < 0) {
            perror("\nError: CAN Socket read failed.\n");
            return 1;
    }

    if (nbytes < sizeof(CAN_Frame_S)) {
            fprintf(stderr, "\nError: Incomplete CAN Frame read.\n");
            return 1;
    }

    return 0;
}