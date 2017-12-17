
#ifndef DEF_KARAZHAN_H
#define DEF_KARAZHAN_H

#define DATA_ATTUMEN_EVENT               0
#define DATA_MOROES_EVENT                1
#define DATA_MAIDENOFVIRTUE_EVENT        2
#define DATA_OPTIONAL_BOSS_EVENT         3
#define DATA_OPERA_EVENT                 4
#define DATA_CURATOR_EVENT               5
#define DATA_SHADEOFARAN_EVENT           6
#define DATA_TERESTIAN_EVENT             7
#define DATA_NETHERSPITE_EVENT           8
#define DATA_CHESS_EVENT                 9
#define DATA_MALCHEZZAR_EVENT           10
#define DATA_NIGHTBANE_EVENT            11

#define DATA_OPERA_PERFORMANCE          13 //which event has been chosen?
#define DATA_OPERA_OZ_DEATHCOUNT        14

#define DATA_KILREK                     15
#define DATA_TERESTIAN                  16
#define DATA_MOROES                     17
#define DATA_GAMEOBJECT_CURTAINS        18
#define DATA_GAMEOBJECT_STAGEDOORLEFT   19
#define DATA_GAMEOBJECT_STAGEDOORRIGHT  20
#define DATA_GAMEOBJECT_LIBRARY_DOOR    21
#define DATA_GAMEOBJECT_MASSIVE_DOOR    22
#define DATA_GAMEOBJECT_NETHER_DOOR     23
#define DATA_GAMEOBJECT_GAME_DOOR       24
#define DATA_GAMEOBJECT_GAME_EXIT_DOOR  25 

#define DATA_IMAGE_OF_MEDIVH            26
#define DATA_MASTERS_TERRACE_DOOR_1     27
#define DATA_MASTERS_TERRACE_DOOR_2     28
#define DATA_CHESS_ECHO_OF_MEDIVH       29
#define CHESS_EVENT_TEAM                30
#define DATA_CHESS_REINIT_PIECES        31
#define DATA_CHESS_CHECK_PIECES_ALIVE   32
#define DATA_CHESS_GAME_PHASE           33
#define DATA_MALCHEZAAR                 34

#define KZScriptName "instance_karazhan"
#define DataHeader "KZ"

uint32 const EncounterCount = 12;

// Opera Performances
#define EVENT_OZ        1
#define EVENT_HOOD      2
#define EVENT_RAJ       3

enum KZMiscCreatures {
    //chess
    NPC_MEDIVH   = 16816, //Echo of Medivh
    NPC_PAWN_H   = 17469,
    NPC_PAWN_A   = 17211,
    NPC_KNIGHT_H = 21748,
    NPC_KNIGHT_A = 21664,
    NPC_QUEEN_H  = 21750,
    NPC_QUEEN_A  = 21683,
    NPC_BISHOP_H = 21747,
    NPC_BISHOP_A = 21682,
    NPC_ROOK_H   = 21726,
    NPC_ROOK_A   = 21160,
    NPC_KING_H   = 21752,
    NPC_KING_A   = 21684,

    //bosses
    NPC_HYAKISS_THE_LURKER          = 16179,
    NPC_ROKAD_THE_RAVAGER           = 16181,
    NPC_SHADIKITH_THE_GLIDER        = 16180,
    NPC_TERESTIAN_ILLHOOF           = 15688,
    NPC_MOROES                      = 15687,
    NPC_NIGHTBANE                   = 17225,
    NPC_ATTUMEN_UNMOUNTED           = 15550,
    NPC_ATTUMEN_MOUNTED             = 16152,
    NPC_MIDNIGHT                    = 16151,
    NPC_MALCHEZAAR                  = 15690,

    // Trash
    NPC_COLDMIST_WIDOW              = 16171,
    NPC_COLDMIST_STALKER            = 16170,
    NPC_SHADOWBAT                   = 16173,
    NPC_VAMPIRIC_SHADOWBAT          = 16175,
    NPC_GREATER_SHADOWBAT           = 16174,
    NPC_PHASE_HOUND                 = 16178,
    NPC_DREADBEAST                  = 16177,
    NPC_SHADOWBEAST                 = 16176,
    NPC_KILREK                      = 17229
};

enum KZGameObjectIds
{
    OPERA_BACKDROP_WIZARD_OF_OZ         = 183442,
    OPERA_WIZARD_OF_OZ_HAY              = 183496,

    OPERA_BACKDROP_ROMEO_AND_JULIET     = 183443,
    OPERA_ROMEO_AND_JULIET_MOON         = 183494,
    OPERA_ROMEO_AND_JULIET_BALCONY      = 183495,

    OPERA_BACKDROP_RED_RIDING           = 183491,
    OPERA_RED_RIDING_HOOD_TREE          = 183492,
    OPERA_RED_RIDING_HOOD_HOUSE         = 183493,

    GO_STAGE_CURTAIN                = 183932,
    GO_STAGE_DOOR_LEFT              = 184278,
    GO_STAGE_DOOR_RIGHT             = 184279,
    GO_PRIVATE_LIBRARY_DOOR         = 184517,
    GO_MASSIVE_DOOR                 = 185521,
    GO_GAMESMAN_HALL_DOOR           = 184276,
    GO_GAMESMAN_HALL_EXIT_DOOR      = 184277,
    GO_NETHERSPACE_DOOR             = 185134,
    GO_MASTERS_TERRACE_DOOR         = 184274,
    GO_MASTERS_TERRACE_DOOR2        = 184280,
    GO_SIDE_ENTRANCE_DOOR           = 184275,
    GO_DUST_COVERED_CHEST           = 185119
};

typedef enum ChessGamePhase
{
    NOTSTARTED      = 0,
    PVE_WARMUP      = 1, // Medivh has been spoken too but king isn't controlled yet
    INPROGRESS_PVE  = 2,
    FAILED          = 4,
    PVE_FINISHED    = 5,
    PVP_WARMUP      = 6,
    INPROGRESS_PVP  = 7  // Get back to PVE_FINISHED after that
} GamePhase;

template <class AI, class T>
inline AI* GetKarazhanAI(T* obj)
{
    return GetInstanceAI<AI>(obj, KZScriptName);
}

#endif

