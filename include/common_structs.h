#ifndef _COMMON_STRUCTS_H_
#define _COMMON_STRUCTS_H_

#ifndef TARGET_N64
#include <libultraship.h>
#else
#include <ultra64.h>
#endif

/**
 * @brief A 3D vector with floating-point components.
 */
typedef f32 Vec3f[3];

/**
 * @brief A 4D vector with floating-point components.
 */
typedef f32 Vec4f[4];

/**
 * @brief A 3D vector with integer components.
 */
typedef s32 Vec3iu[3];

/**
 * @brief A 3D vector with short integer components.
 */
typedef s16 Vec3s[3];

/**
 * @brief A 3D vector with unsigned short integer components.
 */
typedef u16 Vec3su[3];

/**
 * @brief A 4D vector with short integer components.
 */
typedef s16 Vec4s[4];

/**
 * @brief A 3x3 matrix with floating-point components.
 */
typedef f32 Mat3[3][3];

/**
 * @brief A 4x4 matrix with floating-point components.
 */
typedef f32 Mat4[4][4];

/**
 * @brief A 3D vector structure with named floating-point components.
 * @note This may not be a real structure from the original game.
 */
typedef struct {
    f32 x, y, z;
} Vec3fs;

/**
 * @brief An enumeration for controller buttons used in ghost data.
 * This allows using button names instead of hex values.
 */
typedef enum { A = 0x80, B = 0x40, Z = 0x20, R = 0x10 } GhostController;

/***  types.h  ***/

/**
 * @brief Defines the behavior of a CPU player on a track segment.
 */
typedef struct {
    /* 0x0 */ s16 pathPointStart; ///< The starting waypoint of the segment.
    /* 0x2 */ s16 pathPointEnd;   ///< The ending waypoint of the segment.
    /* 0x4 */ s32 type;           ///< The type of behavior for this segment.
} CPUBehaviour; // size = 0x8

/**
 * @brief An enumeration of the possible states for a Signal Processor (SP) task.
 */
enum SpTaskState {
    SPTASK_STATE_NOT_STARTED,   ///< The task has not yet started.
    SPTASK_STATE_RUNNING,       ///< The task is currently running.
    SPTASK_STATE_INTERRUPTED,   ///< The task has been interrupted.
    SPTASK_STATE_FINISHED,      ///< The task has finished processing.
    SPTASK_STATE_FINISHED_DP    ///< The task is finished, and the Display Processor (DP) is done.
};

/**
 * @brief A structure representing a Signal Processor (SP) task.
 */
struct SPTask {
    /*0x00*/ OSTask task;                  ///< The underlying OS task.
    /*0x40*/ OSMesgQueue* msgqueue;        ///< The message queue to notify upon completion.
    /*0x44*/ OSMesg msg;                   ///< The message to send upon completion.
    /*0x48*/ enum SpTaskState state;       ///< The current state of the task.
}; // size = 0x4C, align = 0x8

/**
 * @brief A structure for handling V-blank events.
 */
struct VblankHandler {
    OSMesgQueue* queue; ///< The message queue to send the V-blank message to.
    OSMesg msg;         ///< The message to send on V-blank.
};

struct D_80150158 {
    s16 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
};

/**
 * @brief A structure representing the state of a controller.
 */
struct Controller {
    s16 rawStickX;       ///< The raw X-axis value of the analog stick.
    s16 rawStickY;       ///< The raw Y-axis value of the analog stick.
    s16 rightRawStickX;  ///< The raw X-axis value of the right analog stick.
    s16 rightRawStickY;  ///< The raw Y-axis value of the right analog stick.
    u16 button;          ///< A bitmask of currently held buttons.
    u16 buttonPressed;   ///< A bitmask of buttons pressed this frame.
    u16 buttonDepressed; ///< A bitmask of buttons released this frame.
    u16 stickDirection;  ///< The direction of the analog stick as a bitmask.
    u16 stickPressed;    ///< A bitmask of stick directions pressed this frame.
    u16 stickDepressed;  ///< A bitmask of stick directions released this frame.
};

// Camera path struct? Or something like that. For GP race won scene?
struct UnkStruct_80287500 {
    Vec3f unk0; // xyz coordinates?
    f32 unkC;
    f32 unk10;
    f32 unk14; // rotation?
    s32 unk18;
    s32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    s32 unk38;
};

struct UnkStruct_800DDB40 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u16 unk24;
    u16 unk26;
};

struct UnkStruct_802B53C8 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
};
// end math util structs

struct UnkStruct_800DDB68 {
    s32* D_800ED600;
    s32* D_800ED608;
    s32* D_800ED610;
    s32* D_800ED618;
    s32* D_800ED620;
    s32* D_800ED628;
    s32* D_800ED630;
    s32* D_800ED638;
};
/*** Types.h end ***/

struct Skybox {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
};

typedef struct {
    u8 button;
    s8 frameDuration;
    s8 stickY;
    s8 stickX;
} StaffGhost;
// 80160ADC Banana's remaining

/**
 * @brief A structure for handling collision data.
 */
typedef struct {
    /* 0x00 */ u16 unk30;
    /* 0x02 */ u16 unk32;
    /* 0x04 */ u16 unk34;
    /* 0x06 */ u16 meshIndexYX;         ///< Index of the collision mesh in the YX plane.
    /* 0x08 */ u16 meshIndexZY;         ///< Index of the collision mesh in the ZY plane.
    /* 0x0A */ u16 meshIndexZX;         ///< Index of the collision mesh in the ZX plane.
    /* 0x0C */ Vec3f surfaceDistance;   ///< Distance from the object to the surface in each plane.
    /* 0x18 */ Vec3f unk48;
    /* 0x24 */ Vec3f unk54;
    /* 0x30 */ Vec3f orientationVector; ///< The normal vector of the surface.
    /* 0x3C */ f32 unk6C;
} Collision;

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ f32 scale;
    /* 0x10 */ u16 unk_010;
    /* 0x12 */ u16 type;
    /* 0x14 */ f32 surfaceType;
    /* 0x18 */ f32 unk_018;
    /* 0x1C */ s16 isAlive;
    /* 0x1E */ s16 unk_01E;
    /* 0x20 */ s16 unk_020;
    /* 0x22 */ s16 unk_022;
    /* 0x24 */ f32 unk_024;
    /* 0x28 */ f32 unk_028;
    /* 0x2C */ s16 unk_02C;
    /* 0x2E */ s16 unk_02E;
    /* 0x30 */ s16 unk_030;
    /* 0x32 */ s16 unk_032;
    /* 0x34 */ s16 unk_034;
    /* 0x36 */ s16 unk_036;
    /* 0x38 */ s16 red;
    /* 0x3A */ s16 green;
    /* 0x3C */ s16 blue;
    /* 0x3E */ s16 alpha;
    /* 0x40 */ s16 unk_040;
    /* 0x42 */ s16 unk_042;
    /* 0x44 */ s16 unk_044;
    /* 0x46 */ s16 unk_046;
} UnkPlayerStruct258; // size = 0x48

// This struct is almost identical to the GBI Vtx_t type,
// except that its missing the "flag" member.
typedef struct {
    s16 ob[3]; /* x, y, z */
    s16 tc[2]; /* texture coord */
    s8 ca[4];  /* color & alpha */
} CourseVtx;

/*
This struct has been copied (with only minor modifications) from
https://github.com/micro500/mariokart64/wiki/Surface-Map
on January 23rd, 2022
The original author is assumed to be RenaKunisaki
*/
typedef struct {
    /* 0x00 */ u16 flags;
    // Top bytes is a collections of flags, bottom byte is of unknown purpose
    // bit 7: 1 = only tangible if landed on, not if driven onto?
    //       very weird. game crashes sometimes when playing with this.
    // bit 6: 1 = Lakitu can drop you here (XXX verify)
    // bit 4: 1 = out of bounds
    // bit 3: 1 = player tumbles upon contact (may fall right through)
    /* 0x02 */ u16 surfaceType;

    // For AABB bounding-box style collision. Box style collision is cheaper than checking each vtx.
    /* 0x04 */ s16 minX;  // Minimum x coordinate
    s16 minY;             // Minimum y coordinate
    s16 minZ;             // Minimum z coordinate
    s16 maxX;             // Maximum x coordinate
    s16 maxY;             // Maximum y coordinate
    /* 0x0A */ s16 maxZ;  // Maximum z coordinate
    /* 0x10 */ Vtx* vtx1; // pointer to the 3 vertices of this poly
    Vtx* vtx2;
    Vtx* vtx3;
    // Face normal. Should really be Vec3f normal
    /* 0x1C */ f32 normalX;
    /* 0x20 */ f32 normalY;
    /* 0x24 */ f32 normalZ;
    /* 0x28 */ f32 distance;
} CollisionTriangle; // size = 0x2C

/**
 * @brief A structure representing a kart's tyre.
 */
typedef struct {
    /* 0x00 */ Vec3f pos;                 ///< The position of the tyre in 3D space.
    /* 0x0C */ u8 surfaceType;            ///< The type of surface the tyre is currently on.
    /* 0x0D */ u8 surfaceFlags;           ///< Flags related to the surface.
    /* 0x0E */ u16 collisionMeshIndex;    ///< The index of the collision mesh the tyre is interacting with.
    /* 0x10 */ f32 baseHeight;            ///< The height of the tyre relative to the ground.
    /* 0x14 */ s32 unk_14;                ///< Lighting-related properties.
} KartTyre; // size = 0x18

#define FRONT_LEFT 0
#define FRONT_RIGHT 1
#define BACK_LEFT 2
#define BACK_RIGHT 3

struct UnkPlayerInner {
    /* 0xDB4 */ s16 unk0;
    /* 0xDB6 */ s16 unk2;
    /* 0xDB8 */ f32 unk4;
    /* 0xDBC */ f32 unk8;
    /* 0xDC0 */ f32 unkC;
    /* 0xDC4 */ f32 unk10;
    /* 0xDC8 */ f32 unk14;
    /* 0xDCC */ s16 unk18;
    /* 0xDCE */ s16 unk1A;
    /* 0xDD0 */ s16 unk1C;
    /* 0xDD2 */ s16 unk1E;
    /* 0xDD4 */ s16 unk20;
};

/**
 * @brief The main structure representing a player in the game.
 */
typedef struct {
    /* 0x0000 */ u16 type;                 ///< Bitmask of player properties (human, CPU, etc.).
    /* 0x0002 */ u16 unk_002;
    /* 0x0004 */ s16 currentRank;          ///< The player's current rank in the race.
    /* 0x0006 */ u16 unk_006;
    /* 0x0008 */ s16 lapCount;             ///< The number of laps the player has completed.
    /* 0x000A */ char unk_00A[0x2];
    /* 0x000C */ s32 soundEffects;         ///< Bitmask of active sound effects.
    /* 0x0010 */ s16 currentItemCopy;      ///< A copy of the player's current item.
    /* 0x0012 */ s16 unk_012;
    /* 0x0014 */ Vec3f pos;                ///< The player's position in 3D space.
    /* 0x0020 */ Vec3f oldPos;             ///< The player's position in the previous frame.
    /* 0x002C */ Vec3s rotation;           ///< The player's rotation angles.
    /* 0x0032 */ char unk_032[0x2];
    /* 0x0034 */ Vec3f velocity;           ///< The player's velocity vector.
    /* 0x0040 */ s16 unk_040;
    /* 0x0042 */ s16 unk_042;
    /* 0x0044 */ s16 unk_044;
    /* 0x0046 */ u16 unk_046;
    /* 0x0048 */ Vec4s unk_048;
    /* 0x0050 */ Vec4s unk_050;
    /* 0x0058 */ f32 unk_058;
    /* 0x005C */ f32 unk_05C;
    /* 0x0060 */ f32 unk_060;
    /* 0x0064 */ Vec3f unk_064;
    /* 0x0070 */ f32 boundingBoxSize;      ///< The size of the player's bounding box.
    /* 0x0074 */ f32 unk_074;
    /* 0x0078 */ s16 unk_078;
    /* 0x007A */ s16 hopFrameCounter;      ///< A counter for the kart hop animation.
    /* 0x007C */ s32 unk_07C;
    /* 0x0080 */ f32 boostPower;           ///< The power of the player's current boost.
    /* 0x0084 */ f32 unk_084;
    /* 0x0088 */ f32 unk_088;
    /* 0x008C */ f32 kartPropulsionStrength; ///< The strength of the kart's propulsion.
    /* 0x0090 */ f32 unk_090;
    /* 0x0094 */ f32 speed;                ///< The player's current speed.
    /* 0x0098 */ f32 unk_098;
    /* 0x009C */ f32 currentSpeed;         ///< The player's current speed (used for calculations).
    /* 0x00A0 */ f32 unk_0A0;
    /* 0x00A4 */ f32 unk_0A4;
    /* 0x00A8 */ s16 unk_0A8;
    /* 0x00AA */ s16 unk_0AA;
    /* 0x00AC */ s16 unk_0AC;
    /* 0x00AE */ s16 unk_0AE;
    /* 0x00B0 */ s16 unk_0B0;
    /* 0x00B2 */ s16 unk_0B2;
    /* 0x00B4 */ u16 unk_0B4;
    /* 0x00B6 */ u16 unk_0B6;
    /* 0x00B8 */ f32 unk_0B8;
    /* 0x00BC */ u32 effects;              ///< Bitmask of active effects (e.g., boost, lightning).
    /* 0x00C0 */ s16 unk_0C0;
    /* 0x00C2 */ s16 unk_0C2;
    /* 0x00C4 */ s16 slopeAccel;           ///< Acceleration due to the slope of the track.
    /* 0x00C6 */ s16 alpha;                ///< The player's alpha transparency.
    /* 0x00C8 */ s16 unk_0C8;
    /* 0x00CA */ s16 unk_0CA;
    /* 0x00CC */ Vec4s unk_0CC;
    /* 0x00D4 */ Vec4s unk_0D4;
    /* 0x00DC */ s16 boostTimer;           ///< A timer for the boost effect.
    /* 0x00DE */ u16 waterInteractionFlags; ///< Flags for interaction with water.
    /* 0x00E0 */ s16 unk_0E0;
    /* 0x00E2 */ s16 unk_0E2;
    /* 0x00E4 */ f32 unk_0E4;
    /* 0x00E8 */ f32 unk_0E8;
    /* 0x00EC */ f32 kartHopVelocity;      ///< The vertical velocity of a kart hop.
    /* 0x00F0 */ f32 kartHopJerk;          ///< The jerk (rate of change of acceleration) of a kart hop.
    /* 0x00F4 */ f32 kartHopAcceleration;  ///< The vertical acceleration of a kart hop.
    /* 0x00F8 */ u16 surfaceType;          ///< The type of surface the player is currently on.
    /* 0x00FA */ s16 unk_0FA;
    /* 0x00FC */ f32 kartFriction;         ///< The friction of the kart.
    /* 0x0100 */ f32 kartGravity;          ///< The gravity acting on the kart.
    /* 0x0104 */ f32 unk_104;
    /* 0x0108 */ f32 hopVerticalOffset;    ///< The vertical offset from a hop.
    /* 0x010C */ s16 unk_10C;
    /* 0x010E */ char unk_10E[0x2];
    /* 0x0110 */ Collision collision;      ///< The player's collision data.
    /* 0x0150 */ Mat3 unk_150;
    /* 0x0174 */ Mat3 orientationMatrix;    ///< The player's orientation matrix.
    /* 0x0198 */ KartTyre tyres[4];         ///< Data for each of the kart's four tyres.
    /* 0x01F8 */ f32 unk_1F8;
    /* 0x01FC */ f32 unk_1FC;
    /* 0x0200 */ u32 unk_200;
    /* 0x0204 */ s16 driftDuration;        ///< The duration of the player's drift.
    /* 0x0206 */ s16 unk_206;
    /* 0x0208 */ f32 unk_208;
    /* 0x020C */ f32 unk_20C;
    /* 0x0210 */ f32 unk_210;
    /* 0x0214 */ f32 topSpeed;             ///< The player's top speed.
    /* 0x0218 */ f32 unk_218;
    /* 0x021C */ f32 unk_21C;
    /* 0x0220 */ s16 nearestPathPointId;   ///< The ID of the nearest waypoint.
    /* 0x0222 */ s16 unk_222;
    /* 0x0224 */ f32 size;                 ///< The size of the player's character.
    /* 0x0228 */ s16 unk_228;
    /* 0x022A */ s16 driftState;           ///< The current state of the player's drift.
    /* 0x022C */ f32 previousSpeed;        ///< The player's speed in the previous frame.
    /* 0x0230 */ f32 unk_230;
    /* 0x0234 */ s16 unk_234;
    /* 0x0236 */ s16 unk_236;
    /* 0x0238 */ s16 unk_238;
    /* 0x023A */ s16 unk_23A;
    /* 0x023C */ f32 unk_23C;
    /* 0x0240 */ s32 tyreSpeed;            ///< The rotational speed of the tyres.
    /* 0x0244 */ u16 animFrameSelector[4]; ///< The active animation frame selector.
    /* 0x024C */ u16 animGroupSelector[4]; ///< The active animation group selector.
    /* 0x0254 */ u16 characterId;          ///< The ID of the player's character.
    /* 0x0256 */ u16 unk_256;
    /* 0x0258 */ UnkPlayerStruct258 particlePool0[10];
    /* 0x06D8 */ UnkPlayerStruct258 particlePool1[10];
    /* 0x0C98 */ UnkPlayerStruct258 particlePool2[10];
    /* 0x1278 */ UnkPlayerStruct258 particlePool3[10];
    /* 0x0D98 */ s16 unk_D98;
    /* 0x0D9A */ s16 unk_D9A;
    /* 0x0D9C */ f32 unk_D9C;
    /* 0x0DA0 */ f32 unk_DA0;
    /* 0x0DA4 */ s16 unk_DA4;
    /* 0x0DA6 */ s16 unk_DA6;
    /* 0x0DA8 */ f32 unk_DA8;
    /* 0x0DAC */ f32 unk_DAC;
    /* 0x0DB0 */ f32 unk_DB0;
    /* 0x0DB4 */ struct UnkPlayerInner unk_DB4;
    /* 0x0DB6 */ // s16 unk_DB6;
    /* 0x0DB8 */ // f32 unk_DB8;
    /* 0x0DBC */ // f32 unk_DBC;
    /* 0x0DC0 */ // f32 unk_DC0;
    /* 0x0DC4 */ // f32 unk_DC4;
    /* 0x0DC8 */ // f32 unk_DC8;
    /* 0x0DCC */ // s16 unk_DCC;
    /* 0x0DCE */ // s16 unk_DCE;
    /* 0x0DD0 */ // s16 unk_DD0;
    /* 0x0DD2 */ // s16 unk_DD2;
    /* 0x0DD4 */ // s16 unk_DD4;

    u32 nControlFlags; ///< Flags for whether the player is human, AI, or network-controlled.
    s32 nCharacter;    ///< The player's character choice over the network.
    s32 nStartingRank; ///< The player's starting rank.
    u32 nHasAuthority; ///< Whether this client has authority over the player.
} Player; // size = 0xDD8

enum POOL_1_PARTICLE_TYPES {
    NO_PARTICLE,
    DRIFT_PARTICLE,
    GROUND_PARTICLE,
    GRASS_PARTICLE,
    POOL_1_PARTICLE_TYPE_4,
    POOL_1_PARTICLE_TYPE_5,
    POOL_1_PARTICLE_TYPE_6,
    POOL_1_PARTICLE_TYPE_7,
    POOL_1_PARTICLE_TYPE_8,
    POOL_1_PARTICLE_TYPE_9
};

typedef struct {
    // Something related to time trial ghost data?
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 ghostDataSaved;
    /* 0x05 */ s8 courseIndex;
    /* 0x06 */ u8 characterId;
    /* 0x07 */ u8 unk_07[0x3C];
    /* 0x43 */ u8 pad_43[0x7F - 0x43];
    /* 0x7F */ u8 checksum;
} struct_8018EE10_entry; // size = 0x80

typedef struct {
    uint8_t r, g, b;
} RGB8;

typedef struct {
    /* 0x00 */ u16 red;
    /* 0x02 */ u16 green;
    /* 0x04 */ u16 blue;
    /* 0x06 */ u16 alpha;
} RGBA16; // size = 0x08

// Something related to human players
// Also might be used for the camera during the post race screens
typedef struct {
    /* 0x00 */ f32 unknownScaling; // Looks to be some type of scaling, unknown use
    /* 0x04 */ f32 rankScaling;    // Scaling done on the rank text in the bottom left corner of the screen
                                   // All time measurements are in centiseconds
    /* 0x08 */ u32 someTimer;      // The someTimers seem to always have the same value, the total time since race start
    /* 0x0C */ u32 someTimer1;
    /* 0x10 */ u32 timeLastTouchedFinishLine; // Sum of time of all completed laps
    // Times at which each lap was completed
    union {
        struct {
            /* 0x14 */ u32 lap1CompletionTime;
            /* 0x18 */ u32 lap2CompletionTime;
            /* 0x1C */ u32 lap3CompletionTime;
        };
        u32 lapCompletionTimes[3];
    };
    // Time each lap took to complete
    union {
        struct {
            /* 0x20 */ u32 lap1Duration;
            /* 0x24 */ u32 lap2Duration;
            /* 0x28 */ u32 lap3Duration;
        };
        u32 lapDurations[3];
    };
    // Integer parts of the player's X/Y/X coordinates
    /* 0x2C */ s32 posXInt;
    /* 0x30 */ s32 posYInt;
    /* 0x34 */ s32 posZInt;
    /* 0x38 */ s32 unk_38;
    // Timer for how long the on screen should blink on lap completion
    // Blinking occurs as long as this is a non-zero value.
    // Other on screen effects may override the blinking
    /* 0x3C */ s16 blinkTimer;
    /* 0x3E */ s16 speedometerX;
    /* 0x40 */ s16 speedometerY;
    /* 0x42 */ s16 itemBoxX;
    /* 0x44 */ s16 itemBoxY;
    /* 0x46 */ s16 slideItemBoxX;
    /* 0x48 */ s16 slideItemBoxY;
    // These 2 s16's have values, but I have yet to identify any places that read them
    /* 0x4A */ s16 unk_4A;
    /* 0x4C */ s16 unk_4C;
    /* 0x4E */ s16 timerX; // X coordinate of the on screen timer
    // These 4 X coordinates are "slide" values
    union {
        struct {
            /* 0x50 */ s16 lap1CompletionTimeX; // Pulls double-duty as timerAfterImage1X
            /* 0x52 */ s16 lap2CompletionTimeX; // Pulls double-duty as timerAfterImage2X
            /* 0x54 */ s16 lap3CompletionTimeX;
        };
        /* 0x50 */ s16 lapCompletionTimeXs[3];
    };
    /* 0x56 */ s16 totalTimeX;
    /* 0x58 */ s16 timerY; // Y coordinate of the on screen timer (used as Y coordinate for lap completion times in
                           // post-race screen)
    /* 0x5A */ s16 lapX;   // X coordinate of the on screen lap counter
                           // 0x5C and 0x5E seem to be relative to lapX
    /* 0x5C */ s16 lapAfterImage1X;
    /* 0x5E */ s16 lapAfterImage2X;
    /* 0x60 */ s16 lapY;  // Y coordinate of the on screen lap counter
    /* 0x62 */ s16 rankX; // X coordinate of the on screen rank indicator
    /* 0x64 */ s16 rankY; // Y coordinate of the on screen rank indicator
    /* 0x66 */ s16
        slideRankX; // Adds with the other rankX, used during post race screen to make the rank "slide" into place
    /* 0x68 */ s16
        slideRankY; // Adds with the other rankY, used during post race screen to make the rank "slide" into place
    /* 0x6A */ s16 stagingPosition; // Position to take during race staging
    // These s16's occasionally have values, but I have yet to identify any places that read them
    // They appear to have values when in 3/4 player split screen mode, otherwise they're 0
    /* 0x6C */ s16 unk_6C;
    /* 0x6E */ s16 unk_6E;
    /* 0x70 */ s8 raceCompleteBool; // Indicates if race is over?
    /* 0x71 */ s8 lapCount;         // This increases to 3 when a race is over, while alsoLapCount stays at 2
    /* 0x72 */ s8 alsoLapCount;
    // Related to the timer blinking on lap completion
    // If blinkTimer is counting down:
    //     0: Show timer
    //     1: Hide timer
    //     2: ? Seems to be a transition state, never lasts a long enough for blinkTimer to tick
    /* 0x73 */ s8 blinkState;
    /* 0x74 */ s8 unk_74;
    /* 0x75 */ s8 unk_75;
    /* 0x76 */ u8 itemOverride; // Something related to item generation. If non-zero, it determines the item you get
    /* 0x77 */ s8 unk_77;
    // 0x78 to 0x7F appear to be some type of "state" trackers for the lap and timer text during a race start
    // When a race starts those texts (and their afterimages) slide in and "bounce" a bit. These states control the
    // bouncing (somehow)
    /* 0x78 */ u8 unk_78;
    /* 0x79 */ u8 unk_79;
    /* 0x7A */ u8 unk_7A;
    /* 0x7B */ u8 unk_7B;
    /* 0x7C */ u8 unk_7C;
    /* 0x7D */ u8 unk_7D;
    /* 0x7E */ u8 unk_7E;
    /* 0x7F */ u8 unk_7F;
    /* 0x80 */ u8 unk_80;
    /* 0x81 */ u8 unk_81;
    /* 0x82 */ s8 unk_82;
    /* 0x83 */ s8 unk_83;
} hud_player;

#define HUD_PLAYERS_SIZE 4

#endif
