#ifndef VCP_MESSAGES_H
#define VCP_MESSAGES_H

#include <stdint.h>

const uint8_t VCT_DATAFRAME_LEN       = 8;
const uint8_t VCT_MAX_PAXLOAD_LEN     = 6;
const uint8_t DATA_START_BYTE         = 2;

// VCT Message Identifier Enum

typedef enum : uint8_t 
{
    L_THRUSTER_CTRL_ID  = 0,
    R_THRUSTER_CTRL_ID  = 1,
    LEAK_FLAG_ID        = 2,
    PINGER_ANGLE_ID     = 3,
    HYDROPHONE_FREQ_ID  = 4,
    PRESSURE_VAL_ID     = 5,
} VCP_Message_ID_E;

// VCT Frame
// Basic Frame for the Protocol

typedef struct VCP_Frame_S
{
    VCP_Message_ID_E     vcp_identifier;
    uint8_t              data_length;
    uint8_t              data[VCT_MAX_PAXLOAD_LEN]; 
} VCP_Frame_S;

// Thruster Control Struct
// Unit: Pulses (for PWM)

typedef struct ThrusterCtrl_PWM_S
{
    uint16_t    thruster_f;
    uint16_t    thruster_m;
    uint16_t    thruster_b;
} ThrusterCtrl_PWM_S;

// Circuit Pinger Frequency
// Unit: Kilohertz (kHz)

typedef enum : uint8_t
{
    HYDRO_FREQ_25_KHZ = 0,
    HYDRO_FREQ_30_KHZ = 1,
    HYDRO_FREQ_35_KHZ = 2,
    HYDRO_FREQ_40_KHZ = 3,
} HydroFreq_KHz_E;

// Leak Flag
// No Unit

typedef enum : uint8_t 
{
    NO_LEAK = 0,
    LEAK = 1,
} LeakFlag_E;

// Pinger Direction Yaw Angle
// Unit: Degrees (Deg)

typedef float PingerAngle_Deg_t;

// Pressure 
// Unit: mbar 

typedef float Pressure_Mbar_t;

#endif