#pragma once
#include "iclientmode.hpp"

class Entity;

class CMoveHelper {
public:
	bool	first_run_of_iunctions : 1;
	bool	game_code_moved_player : 1;
	int	    player_handle;
	int	    impulse_command;
	Vector	view_angles;
	Vector	abs_view_angles;
	int	    buttons;
	int	    old_buttons;
	float	forward_move;
	float	side_move;
	float	up_move;
	float	max_speed;
	float	client_max_speed;
	Vector	velocity;
	Vector	angles;
	Vector	old_angles;
	float	out_step_height;
	Vector	wish_velocity;
	Vector	jump_velocity;
	Vector	constraint_center;
	float	constraint_radius;
	float	constraint_width;
	float	constraint_speed_factor;
	float	u0[5];
	Vector	abs_origin;
	virtual	void u1() = 0;
	virtual void setHost(Entity* host) = 0;
};

class CMoveData {
public:
	bool    first_run_of_instructions : 1;
	bool    game_code_moved_player : 1;
	int     player_handle;
	int     impulse_command;
	Vector	view_angles;
	Vector	abs_view_angles;
	int     buttons;
	int     old_buttons;
	float   fw_move;
	float   sd_move;
	float   up_move;
	float   max_speed;
	float   client_max_speed;
	Vector	velocity;
	Vector	angles;
	Vector	old_angles;
	float   step_height;
	Vector	wish_velocity;
	Vector	jump_velocity;
	Vector	constraint_center;
	float   constraint_radius;
	float   constraint_width;
	float   constraint_speed_factor;
	float   u0[ 5 ];
	Vector	abs_origin;
};

class IGameMovement {
public:
	void ProcessMovement(Entity* player, CMoveData* move) {
		typedef void (*Fn)(void* , Entity* , CMoveData* );
		return getVirtualFunc<Fn>(this, 2)(this, player, move);
	}

	void StartTrackPredictionErrors(Entity* player) {
		typedef void (*Fn)(void* , Entity* );
		return getVirtualFunc<Fn>(this, 4)(this, player);
	}

	void FinishTrackPredictionErrors(Entity* player) {
		typedef void (*Fn)(void* , Entity* );
		return getVirtualFunc<Fn>(this, 5)(this, player);
	}
};

class IPrediction {
public:
    bool InPrediction() {
        typedef bool (*Fn)(void*);
        return getVirtualFunc<Fn>(this, 14)(this);
	}

	void RunCommand(Entity* player, CUserCmd* cmd, CMoveHelper* helper ) {
        typedef void (*Fn)(void*, Entity*, CUserCmd*, CMoveHelper*);
        return getVirtualFunc<Fn>(this, 19)(this, player, cmd, helper);
	}

	void SetupMove(Entity* player, CUserCmd* cmd, CMoveHelper* helper, CMoveData* move) {
		typedef void (*Fn)(void* , Entity* , CUserCmd* , CMoveHelper* , CMoveData* );
		return getVirtualFunc<Fn>(this, 21)(this, player, cmd, helper, move);
	}

	void FinishMove(Entity* player, CUserCmd* cmd, CMoveData* move) {
		typedef void (*Fn)(void*, Entity*, CUserCmd*, CMoveData*);
		return getVirtualFunc<Fn>(this, 22)(this, player, cmd, move);
	}
};
