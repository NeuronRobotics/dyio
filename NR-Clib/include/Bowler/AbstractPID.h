/**
 * @file AbstractPID.h
 *
 * Created on: Apr 9, 2010
 * @author Kevin Harrington
 */

#ifndef ABSTRACTPID_H_
#define ABSTRACTPID_H_
#include "Bowler_Helper.h"
#include "namespace.h"
#include "Scheduler.h"

#define IntegralSize  10

//bcs.pid
#define _PID				0x6469705f // '_pid'  Get/Set the pid setpoint
#define CPID				0x64697063 // 'cpid'  Configure PID
#define CPDV				0x76647063 // 'cpdv'  Configure PD Velocity controler
#define APID				0x64697061 // 'apid'  Get/Set all PID channels
#define RPID				0x64697072 // 'rpid'  Reset a PID channel
#define _VPD				0x6470765f // '_vpd'    PID velocity command
#define KPID				0x6469706b // 'kpid'  Kill all PID controllers
#define PIDL				0x6c646970 // 'pidl'  PID limit event
#define GPDC				0x63647067 // 'gpdc'  Get PID count

typedef enum _PidLimitType {
    NO_LIMIT = (0xff),

    LOWERLIMIT = (0x00),

    INDEXEVENT = (0x01),

    UPPERLIMIT = (0x02),

    OVERCURRENT = (0x03),

    CONTROLLER_ERROR = (0x04)
} PidLimitType;

typedef enum _PidCalibrationType {
    CALIBRARTION_Uncalibrated = (0),
    CALIBRARTION_DONE = (1),
    CALIBRARTION_hysteresis = (2),
    CALIBRARTION_home_up = (3),
    CALIBRARTION_home_down = (4),
    CALIBRARTION_home_velocity = (5)

} PidCalibrationType;

typedef struct __attribute__((__packed__)) _PidLimitEvent {
    int group;
    PidLimitType type;
    float time;
    signed long int value;
    signed long int latchTickError;
    //	boolean stopOnIndex;
}
PidLimitEvent;

/**
 * These are your Control Constants
 */
typedef enum _CAL_STATE {
    forward = 0,
    backward = 1,
    done = 2
} CAL_STATE;

/**
 * This is the storage struct for all the information needed to run the PID calculation
 * Note that this has no assumptions on the type of inputs or type of outputs
 * It also has no assumptions on the time step it is run over. It stores previous time and
 * will calculate scaling based on that and the current time
 */
typedef struct __attribute__((__packed__)) _AbsPID_Config {

    unsigned char Enabled;
    unsigned char Polarity;
    float IndexLatchValue;
    unsigned char stopOnIndex;
    unsigned char useIndexLatch;
    unsigned char Async;

    struct __attribute__((__packed__)) {
        float P;
        float I;
        float D;
    }
    K;

    struct __attribute__((__packed__)) {
        float P;
        float D;
    }
    V;
    int upperHistoresis;
    int lowerHistoresis;
    int stop;
    PidCalibrationType calibrationState;
    float offset;
    float tipsScale;

}
AbsPID_Config;

typedef struct __attribute__((__packed__)) _AbsPID {

    //unsigned char           channel;
    float SetPoint;
    float CurrentState;
    float PreviousError;
    //unsigned int            integralCircularBufferIndex;
    float integralTotal;
    float integralSize;
    float Output;
    float OutputSet;
    // This must be in MS
    float PreviousTime;
    float lastPushedValue;
    float lastPushedTime;

    struct  __attribute__((__packed__)) {
        unsigned char calibrating;
        unsigned char calibrated;
        CAL_STATE state;
        //RunEveryData timer;
    } calibration;

    struct  __attribute__((__packed__)) {
        //RunEveryData timer;
        float homingStallBound;
        float previousValue;
        float lastTime;
        float homedValue;
    } homing;
    RunEveryData timer;
    AbsPID_Config config;
    INTERPOLATE_DATA interpolate;
}
AbsPID;

typedef struct __attribute__((__packed__)) _DYIO_PID {
    unsigned char inputMode;
    unsigned char inputChannel;
    unsigned char outputMode;
    unsigned char outputChannel;
    unsigned char outVal;
}
DYIO_PID;

typedef struct __attribute__((__packed__)) _PD_VEL {
    boolean enabled;
    float unitsPerSeCond;
    float lastPosition;
    float lastVelocity;
    float lastTime;
    float currentOutputVel;
}
PD_VEL;
/**
 * RunAbstractPIDCalc
 * @param state A pointer to the AbsPID struct to run the calculations on
 * @param CurrentTime a float of the time it is called in MS for use by the PID calculation
 */
void RunAbstractPIDCalc(AbsPID * state, float CurrentTime);

/**
 * Set the PID constants
 * @param group which group to set
 * @param p constant
 * @param i constant
 * @param d constant
 */
void setPIDConstants(int group, float p, float i, float d);
/**
 * InitAbsPID
 * @param state A pointer to the AbsPID the initialize
 * @param KP the Proportional Constant
 * @param KI the Integral Constant
 * @param KD the Derivative Constant
 * @param time the starting time
 */
void InitAbsPIDWithPosition(AbsPID * state, float KP, float KI, float KD, float time, float currentPosition);
void InitAbsPID(AbsPID * state, float KP, float KI, float KD, float time);
/**
 * Handle a PID packet.
 * @return True if the packet was processed, False if it was not  PID packet
 */
boolean ProcessPIDPacket(BowlerPacket * Packet);
/**
 * @param groups a pointer the the array of PID groups
 * @param the number of PID groups
 * @param getPositionPtr function pointer to the get position function
 * @param setPositionPtr function pointer to the set position function
 * @param resetPositionPtr function pointer to the re-set position function
 * @param pidAsyncCallbackPtr function pointer to push an async value
 */
void InitilizePidController(AbsPID * groups,
        PD_VEL * vel,
        int numberOfGroups,
        float (*getPositionPtr)(int),
        void (*setOutputPtr)(int, float),
        int (*resetPositionPtr)(int, int),
        void (*onPidConfigurePtr)(int),
        PidLimitEvent * (*checkPIDLimitEventsPtr)(uint8_t group));
/**
 * This sets a different set of control loop math.
 * @param math a function pointer to the math calculation to be used in place of the PID math
 */
void SetControllerMath(void (*math)(AbsPID *, float));

int getNumberOfPidChannels();

void SetPIDEnabled(uint8_t index, boolean enabled);

boolean isPidEnabled(uint8_t i);
uint8_t SetPIDTimedPointer(AbsPID * conf,float val, float current,float ms);
uint8_t SetPIDTimed(uint8_t chan, float val, float ms);
uint8_t SetPID(uint8_t chan, float val);
int GetPIDPosition(uint8_t chan);

uint8_t ZeroPID(uint8_t chan);
/**
 * Runs both Control and Coms
 */
void RunPID(BowlerPacket *Packet, boolean (*pidAsyncCallbackPtr)(BowlerPacket *Packet));
/**
 * THis function runs the Comunication for the PID controller
 */
void RunPIDComs(BowlerPacket *Packet, boolean (*pidAsyncCallbackPtr)(BowlerPacket *Packet));
/**
 * This runs the get input/math/set output for the PID controller
 */
void RunPIDControl();
void RunPDVel(uint8_t chan);
float runPdVelocityFromPointer(PD_VEL* vel, float currentState,float KP, float KD);
void StartPDVel(uint8_t chan, float unitsPerSeCond, float ms);
void pushPID(BowlerPacket *Packet, boolean (*pidAsyncCallbackPtr)(BowlerPacket *Packet), uint8_t chan, int32_t value, float time);
void pushPIDLimitEvent(BowlerPacket *Packet, boolean (*pidAsyncCallbackPtr)(BowlerPacket *Packet), PidLimitEvent * event);

void checkLinkHomingStatus(int group);
/***
 * This is a getter for the interpolation state
 */
boolean isPIDInterpolating(int index);

/**
 * This function checks the PID channel to see if it has settled at the setpoint plus or minus a bound
 * @param index
 * @param plusOrMinus
 * @return
 */
boolean isPIDArrivedAtSetpoint(int index, float plusOrMinus);

boolean processPIDGet(BowlerPacket * Packet);

boolean processPIDPost(BowlerPacket * Packet);
boolean processPIDCrit(BowlerPacket * Packet);

NAMESPACE_LIST * getBcsPidNamespace();

AbsPID * getPidGroupDataTable(int group);
PD_VEL * getPidVelocityDataTable(int group);
void pushAllPIDPositions(BowlerPacket *Packet, boolean (*pidAsyncCallbackPtr)(BowlerPacket *Packet));

void SetPIDCalibrateionState(int group, PidCalibrationType state);

PidCalibrationType GetPIDCalibrateionState(int group);

int getUpperPidHistoresis(int group);
int getLowerPidHistoresis(int group);
int getPidStop(int group);

float getMs();

void updatePidAsync();
void pidReset(uint8_t chan, int32_t val);
float pidResetNoStop(uint8_t chan, int32_t val);
void pushAllPIDPositions(BowlerPacket *Packet, boolean (*pidAsyncCallbackPtr)(BowlerPacket *Packet));

CAL_STATE pidHysterisis(int group);
void startHomingLink(int group, PidCalibrationType type,float homedValue);
void runPidHysterisisCalibration(int group);
boolean processRunAutoCal(BowlerPacket * Packet);

void OnPidConfigure(int v);

void setOutput(int group, float val);

#endif /* ABSTRACTPID_H_ */
