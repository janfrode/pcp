#ifndef KMTIME_H
#define KMTIME_H

#include <sys/time.h>

class QIcon;

class KmTime
{
public:
    typedef enum {
	StoppedState	= 0,
	ForwardState	= 1,
	BackwardState	= 2,
    } State;

    typedef enum {
	StepMode	= 0,
	NormalMode	= 1,
	FastMode	= 2,
    } Mode;

    typedef enum {
	NoSource	= -1,
	HostSource	= 0,
	ArchiveSource	= 1,
    } Source;

    typedef enum {
	Set		= (1<<0),	// client -> server
	Step		= (1<<1),	// server -> clients
	TZ		= (1<<2),	// server -> clients
	VCRMode		= (1<<3),	// server -> clients
	VCRModeDrag	= (1<<4),	// server -> clients
	GUIShow		= (1<<5),	// client -> server
	GUIHide		= (1<<6),	// client -> server
	Bounds		= (1<<7),	// client -> server
	ACK		= (1<<8),	// client -> server (except handshake)
	GUIStyle	= (1<<9),	// client <-> server (both ways)
    } Command;

    static const unsigned int Magic = 0x54494D45;	// "TIME"

    typedef struct {
	unsigned int	magic;
	unsigned int	length;
	KmTime::Command	command;
	KmTime::Source	source;
	KmTime::State	state;
	KmTime::Mode	mode;
	struct timeval	delta;
	struct timeval	position;
	struct timeval	start;		// archive only
	struct timeval	end;		// archive only
	unsigned char	data[0];	// arbitrary length ($TZ/style)
    } Packet;

    typedef enum {
	ForwardOn,		ForwardOff,
	StoppedOn,		StoppedOff,
	BackwardOn,		BackwardOff,
	FastForwardOn,		FastForwardOff,
	FastBackwardOn,		FastBackwardOff,
	StepForwardOn,		StepForwardOff,
	StepBackwardOn,		StepBackwardOff,
	IconCount
    } Icon;

    typedef enum {
	Milliseconds,
	Seconds,
	Minutes,
	Hours,
	Days,
	Weeks,
    } DeltaUnits;

    typedef enum {
	DebugApp	= 0x1,
	DebugProtocol 	= 0x2,
    } DebugOptions;

    static const int BasePort = 43334;
    static const int FastModeDelay = 100;	// milliseconds
    static const int DefaultDelta = 2;		// seconds

    static QIcon *icon(KmTime::Icon);
    static double defaultSpeed(double delta)
	{ return 2.0 * delta; }		// num deltas per second
    static double minimumSpeed(double delta)
	{ return 0.1 * delta; }		// min deltas per second
    static double maximumSpeed(double delta)
	{ return 1000.0 * delta; }	// max deltas per second

    static void timevalAdd(struct timeval *a, struct timeval *b);
    static void timevalSub(struct timeval *a, struct timeval *b);
    static int timevalNonZero(struct timeval *a);
    static int timevalCompare(struct timeval *a, struct timeval *b);

    static void secondsToTimeval(double value, struct timeval *tv);
    static double secondsFromTimeval(struct timeval *tv);

    static double unitsToSeconds(double value, DeltaUnits units);
    static double secondsToUnits(double value, DeltaUnits units);
};

#endif	// KMTIME_H
