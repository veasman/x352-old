#pragma once
#include "../sdk.hpp"

class PlayerMoveHelper {
public:
	bool	firstRunOfIunctions : 1;
	bool	gameCodeMovedPlayer : 1;
	int	playerHandle;
	int	impulseCommand;
	Vector	viewAngles;
	Vector	absViewAngles;
	int	buttons;
	int	oldButtons;
	float	forwardMove;
	float	sideMove;
	float	upMove;
	float	maxSpeed;
	float	clientMaxSpeed;
	Vector	velocity;
	Vector	angles;
	Vector	oldAngles;
	float	outStepHeight;
	Vector	wishVelocity;
	Vector	jumpVelocity;
	Vector	constraintCenter;
	float	constraintRadius;
	float	constraintWidth;
	float	constraintSpeedFactor;
	float	u0[5];
	Vector	absOrigin;
	virtual	void u1() = 0;
	virtual void setHost(player_t *host) = 0;
};

class PlayerMoveData {
public:
	bool    firstRunOfInstructions : 1;
	bool    gameCodeMovedPlayer : 1;
	int     playerHandle;
	int     impulseCommand;
	Vector	viewAngles;
	Vector	absViewAngles;
	int     buttons;
	int     oldButtons;
	float   fwMove;
	float   sdMove;
	float   upMove;
	float   maxSpeed;
	float   clientMaxSpeed;
	Vector	velocity;
	Vector	angles;
	Vector	oldAngles;
	float   stepHeight;
	Vector	wishVelocity;
	Vector	jumpVelocity;
	Vector	constraintCenter;
	float   constraintRadius;
	float   constraintWidth;
	float   constraintSpeedFactor;
	float   u0[ 5 ];
	Vector	absOrigin;
};

class VirtualGameMovement {

public:
	virtual				~VirtualGameMovement( void ) {}
	virtual void			processMovement( player_t *player, PlayerMoveData *move ) = 0;
	virtual void			reset( void ) = 0;
	virtual void			startTrackPredictionErrors( player_t *player ) = 0;
	virtual void			finishTrackPredictionErrors( player_t *player ) = 0;
	virtual void			diffPrint( char const *fmt, ... ) = 0;
	virtual Vector const	&getPlayerMins( bool ducked ) const = 0;
	virtual Vector const	&getPlayerMaxs( bool ducked ) const = 0;
	virtual Vector const	&getPlayerViewOffset( bool ducked ) const = 0;
	virtual bool			isMovingPlayerStuck( void ) const = 0;
	virtual player_t		*getMovingPlayer( void ) const = 0;
	virtual void			unblockPosher( player_t *player, player_t *pusher ) = 0;
	virtual void			setupMovementBounds( PlayerMoveData *move ) = 0;
};

class PlayerGameMovement : public VirtualGameMovement {
public:
	virtual ~PlayerGameMovement(void) { }
};

class playerPrediction {
public:
	bool inPrediction() {
        typedef bool (*Fn)(void*);
        return getVirtualFunc<Fn>(this, 14)(this);
	}

	void run_command( player_t* player, CUserCmd* cmd, PlayerMoveHelper* helper ) {
        typedef void (*Fn)(void*, player_t*, CUserCmd*, PlayerMoveHelper*);
        return getVirtualFunc<Fn>(this, 19)(this, player, cmd, helper);
    }

	void setup_move( player_t* player, CUserCmd* cmd, PlayerMoveHelper* helper, void* data ) {
        typedef void (*Fn)(void*, player_t*, CUserCmd*, PlayerMoveHelper*, void*);
        return getVirtualFunc<Fn>(this, 20)(this, player, cmd, helper, data);
	}

	void finish_move( player_t* player, CUserCmd* cmd, void* data ) {
        typedef void (*Fn)(void*, player_t*, CUserCmd*, void*);
        return getVirtualFunc<Fn>(this, 21)(this, player, cmd, data);
	}
};
