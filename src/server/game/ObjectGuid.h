
#ifndef ObjectGuid_h__
#define ObjectGuid_h__

#include "ByteBuffer.h"
#include "ObjectDefines.h"

#include <functional>
#include <unordered_set>

enum TypeID
{
    TYPEID_OBJECT        = 0,
    TYPEID_ITEM          = 1,
    TYPEID_CONTAINER     = 2,
    TYPEID_UNIT          = 3,
    TYPEID_PLAYER        = 4,
    TYPEID_GAMEOBJECT    = 5,
    TYPEID_DYNAMICOBJECT = 6,
    TYPEID_CORPSE        = 7
};

#define NUM_CLIENT_OBJECT_TYPES             8

enum TypeMask
{
    TYPEMASK_OBJECT         = 0x0001,
    TYPEMASK_ITEM           = 0x0002,
    TYPEMASK_CONTAINER      = 0x0006,                       // TYPEMASK_ITEM | 0x0004
    TYPEMASK_UNIT           = 0x0008,                       // creature
    TYPEMASK_PLAYER         = 0x0010,
    TYPEMASK_GAMEOBJECT     = 0x0020,
    TYPEMASK_DYNAMICOBJECT  = 0x0040,
    TYPEMASK_CORPSE         = 0x0080,
    TYPEMASK_SEER           = TYPEMASK_PLAYER | TYPEMASK_UNIT | TYPEMASK_DYNAMICOBJECT
};

class PackedGuid;

struct PackedGuidReader
{
    explicit PackedGuidReader(uint64 guid) 
    { 
        GuidPtr = new uint64();
        *GuidPtr = guid;
    }
    ~PackedGuidReader() 
    {
        delete GuidPtr;
    }
    uint64* GuidPtr;
};

class TC_GAME_API ObjectGuid
{
    public:
        static ObjectGuid const Empty;

        ObjectGuid() : _guid(0) { }
        explicit ObjectGuid(uint64 guid) : _guid(guid) { }
        ObjectGuid(HighGuid hi, uint32 entry, uint32 counter) : _guid(counter ? uint64(counter) | (uint64(entry) << 24) | (uint64(hi) << 48) : 0) { }
        ObjectGuid(HighGuid hi, uint32 counter) : _guid(counter ? uint64(counter) | (uint64(hi) << 48) : 0) { }

        operator uint64() const { return _guid; }
        //PackedGuidReader ReadAsPacked() { return PackedGuidReader(*this); }
        PackedGuidReader ReadAsPacked() { return PackedGuidReader(this->GetRawValue()); }

        void Set(uint64 guid) { _guid = guid; }
        void Clear() { _guid = 0; }

        PackedGuid WriteAsPacked() const;

        uint64   GetRawValue() const { return _guid; }
        HighGuid GetHigh() const { return HighGuid((_guid >> 48) & 0x0000FFFF); }
        uint32   GetEntry() const { return HasEntry() ? uint32((_guid >> 24) & UI64LIT(0x0000000000FFFFFF)) : 0; }
        uint32   GetCounter()  const
        {
            return HasEntry()
                   ? uint32(_guid & UI64LIT(0x0000000000FFFFFF))
                   : uint32(_guid & UI64LIT(0x00000000FFFFFFFF));
        }

        static uint32 GetMaxCounter(HighGuid high)
        {
            return HasEntry(high)
                   ? uint32(0x00FFFFFF)
                   : uint32(0xFFFFFFFF);
        }

        uint32 GetMaxCounter() const { return GetMaxCounter(GetHigh()); }

        bool IsEmpty()             const { return _guid == 0; }
        bool IsCreature()          const { return GetHigh() == HIGHGUID_UNIT; }
        bool IsPet()               const { return GetHigh() == HIGHGUID_PET; }
        bool IsVehicle()           const { return GetHigh() == HIGHGUID_VEHICLE; }
        bool IsCreatureOrPet()     const { return IsCreature() || IsPet(); }
        bool IsCreatureOrVehicle() const { return IsCreature() || IsVehicle(); }
        bool IsAnyTypeCreature()   const { return IsCreature() || IsPet() || IsVehicle(); }
        bool IsPlayer()            const { return !IsEmpty() && GetHigh() == HIGHGUID_PLAYER; }
        bool IsUnit()              const { return IsAnyTypeCreature() || IsPlayer(); }
        bool IsItem()              const { return GetHigh() == HIGHGUID_ITEM; }
        bool IsGameObject()        const { return GetHigh() == HIGHGUID_GAMEOBJECT; }
        bool IsDynamicObject()     const { return GetHigh() == HIGHGUID_DYNAMICOBJECT; }
        bool IsCorpse()            const { return GetHigh() == HIGHGUID_CORPSE; }
        bool IsTransport()         const { return GetHigh() == HIGHGUID_TRANSPORT; }
        bool IsMOTransport()       const { return GetHigh() == HIGHGUID_MO_TRANSPORT; }
        bool IsAnyTypeGameObject() const { return IsGameObject() || IsTransport() || IsMOTransport(); }
        bool IsInstance()          const { return GetHigh() == HIGHGUID_INSTANCE; }
        bool IsGroup()             const { return GetHigh() == HIGHGUID_GROUP; }

        static TypeID GetTypeId(HighGuid high)
        {
            switch (high)
            {
                case HIGHGUID_ITEM:         return TYPEID_ITEM;
                //case HIGHGUID_CONTAINER:    return TYPEID_CONTAINER; HIGHGUID_CONTAINER==HIGHGUID_ITEM currently
                case HIGHGUID_UNIT:         return TYPEID_UNIT;
                case HIGHGUID_PET:          return TYPEID_UNIT;
                case HIGHGUID_PLAYER:       return TYPEID_PLAYER;
                case HIGHGUID_GAMEOBJECT:   return TYPEID_GAMEOBJECT;
                case HIGHGUID_DYNAMICOBJECT: return TYPEID_DYNAMICOBJECT;
                case HIGHGUID_CORPSE:       return TYPEID_CORPSE;
                case HIGHGUID_MO_TRANSPORT: return TYPEID_GAMEOBJECT;
                case HIGHGUID_TRANSPORT: return TYPEID_GAMEOBJECT;
                case HIGHGUID_VEHICLE:      return TYPEID_UNIT;
                // unknown
                case HIGHGUID_INSTANCE:
                case HIGHGUID_GROUP:
                default:                    return TYPEID_OBJECT;
            }
        }

        TypeID GetTypeId() const { return GetTypeId(GetHigh()); }

        bool operator!() const { return IsEmpty(); }
        bool operator== (ObjectGuid const& guid) const { return GetRawValue() == guid.GetRawValue(); }
        bool operator!= (ObjectGuid const& guid) const { return GetRawValue() != guid.GetRawValue(); }
        bool operator< (ObjectGuid const& guid) const { return GetRawValue() < guid.GetRawValue(); }

        static char const* GetTypeName(HighGuid high);
        char const* GetTypeName() const { return !IsEmpty() ? GetTypeName(GetHigh()) : "None"; }
        std::string ToString() const;

    private:
        static bool HasEntry(HighGuid high)
        {
            switch (high)
            {
                case HIGHGUID_ITEM:
                case HIGHGUID_PLAYER:
                case HIGHGUID_DYNAMICOBJECT:
                case HIGHGUID_CORPSE:
                case HIGHGUID_MO_TRANSPORT:
                case HIGHGUID_INSTANCE:
                case HIGHGUID_GROUP:
                    return false;
                case HIGHGUID_GAMEOBJECT:
                case HIGHGUID_TRANSPORT:
                case HIGHGUID_UNIT:
                case HIGHGUID_PET:
                case HIGHGUID_VEHICLE:
                default:
                    return true;
            }
        }

        bool HasEntry() const { return HasEntry(GetHigh()); }

        explicit ObjectGuid(uint32 const&) = delete;                 // no implementation, used to catch wrong type assignment
        ObjectGuid(HighGuid, uint32, uint64 counter) = delete;       // no implementation, used to catch wrong type assignment
        ObjectGuid(HighGuid, uint64 counter) = delete;               // no implementation, used to catch wrong type assignment

        uint64 _guid;
};

// Some Shared defines
typedef std::set<uint64> GuidSet;
typedef std::list<uint64> GuidList;
typedef std::deque<uint64> GuidDeque;
typedef std::vector<uint64> GuidVector;
typedef std::unordered_set<uint64> GuidUnorderedSet;

// minimum buffer size for packed guid is 9 bytes
#define PACKED_GUID_MIN_BUFFER_SIZE 9

class TC_GAME_API PackedGuid
{
        friend TC_GAME_API ByteBuffer& operator<<(ByteBuffer& buf, PackedGuid const& guid);

    public:
        explicit PackedGuid() : _packedGuid(PACKED_GUID_MIN_BUFFER_SIZE) { _packedGuid.appendPackGUID(0); }
        explicit PackedGuid(uint64 guid) : _packedGuid(PACKED_GUID_MIN_BUFFER_SIZE) { _packedGuid.appendPackGUID(guid); }

        void Set(uint64 guid) { _packedGuid.wpos(0); _packedGuid.appendPackGUID(guid); }

        size_t size() const { return _packedGuid.size(); }

    private:
        ByteBuffer _packedGuid;
};

template<HighGuid high>
class TC_GAME_API ObjectGuidGenerator
{
    public:
        explicit ObjectGuidGenerator(uint32 start = 1) : _nextGuid(start) { }

        void Set(uint32 val) { _nextGuid = val; }
        uint32 Generate();
        uint32 GetNextAfterMaxUsed() const { return _nextGuid; }

    private:
        uint32 _nextGuid;
};

TC_GAME_API ByteBuffer& operator<<(ByteBuffer& buf, ObjectGuid const& guid);
TC_GAME_API ByteBuffer& operator>>(ByteBuffer& buf, ObjectGuid&       guid);

TC_GAME_API ByteBuffer& operator<<(ByteBuffer& buf, PackedGuid const& guid);
TC_GAME_API ByteBuffer& operator>>(ByteBuffer& buf, PackedGuidReader const& guid);

#endif // ObjectGuid_h__
