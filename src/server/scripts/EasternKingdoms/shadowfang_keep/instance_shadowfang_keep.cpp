
/* ScriptData
SDName: Instance_Shadowfang_Keep
SD%Complete: 100
SDComment: Complete, Doors checked
SDCategory: Shadowfang Keep
EndScriptData */


#include "def_shadowfang_keep.h"
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "SpellAuraEffects.h"

#define ENCOUNTERS              4

class instance_shadowfang_keep : public InstanceMapScript
{
public:
    instance_shadowfang_keep() : InstanceMapScript("instance_shadowfang_keep", 33) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_shadowfang_keep_script(map);
    }

    struct instance_shadowfang_keep_script : public InstanceScript
    {
        instance_shadowfang_keep_script(Map *map) : InstanceScript(map) { Initialize(); };

        uint32 Encounters[ENCOUNTERS];
        std::string str_data;

        ObjectGuid DoorCourtyardGUID;
        ObjectGuid DoorSorcererGUID;
        ObjectGuid DoorArugalGUID;

        void Initialize() override
        {
            for (uint32 & Encounter : Encounters)
                Encounter = NOT_STARTED;
        }

        void OnGameObjectCreate(GameObject *go) override
        {
            switch (go->GetEntry())
            {
            case 18895: DoorCourtyardGUID = go->GetGUID();
                if (Encounters[0] == DONE) HandleGameObject(ObjectGuid::Empty, true, go); break;
            case 18972: DoorSorcererGUID = go->GetGUID();
                if (Encounters[2] == DONE) HandleGameObject(ObjectGuid::Empty, true, go); break;
            case 18971: DoorArugalGUID = go->GetGUID();
                if (Encounters[3] == DONE) HandleGameObject(ObjectGuid::Empty, true, go); break;

            }
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case TYPE_FREE_NPC:
                if (data == DONE)
                    HandleGameObject(DoorCourtyardGUID, true);
                Encounters[0] = data;
                break;
            case TYPE_RETHILGORE:
                Encounters[1] = data;
                break;
            case TYPE_FENRUS:
                if (data == DONE)
                    HandleGameObject(DoorSorcererGUID, true);
                Encounters[2] = data;
                break;
            case TYPE_NANDOS:
                if (data == DONE)
                    HandleGameObject(DoorArugalGUID, true);
                Encounters[3] = data;
                break;
            }

            if (data == DONE)
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << Encounters[0] << " " << Encounters[1] << " " << Encounters[2] << " " << Encounters[3];

                str_data = saveStream.str();

                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case TYPE_FREE_NPC:
                return Encounters[0];
            case TYPE_RETHILGORE:
                return Encounters[1];
            case TYPE_FENRUS:
                return Encounters[2];
            case TYPE_NANDOS:
                return Encounters[3];
            }
            return 0;
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;
            return str_data;
            OUT_SAVE_INST_DATA_COMPLETE;
        }

        void Load(const char* in) override
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            std::istringstream loadStream(in);
            loadStream >> Encounters[0] >> Encounters[1] >> Encounters[2] >> Encounters[3];

            for (uint32 & Encounter : Encounters)
            {
                if (Encounter == IN_PROGRESS)
                    Encounter = NOT_STARTED;

            }

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

class spell_shadowfang_keep_haunting_spirits : public SpellScriptLoader
{
public:
    spell_shadowfang_keep_haunting_spirits() : SpellScriptLoader("spell_shadowfang_keep_haunting_spirits") { }

    class spell_shadowfang_keep_haunting_spirits_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_shadowfang_keep_haunting_spirits_AuraScript);

        void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
        {
            isPeriodic = true;
            amplitude = irand(30 * IN_MILLISECONDS, 90 * IN_MILLISECONDS);
        }

        void HandleDummyTick(AuraEffect const* aurEff)
        {
            GetTarget()->CastSpell((Unit*)NULL, aurEff->GetAmount(), true);
        }

        void HandleUpdatePeriodic(AuraEffect* aurEff)
        {
            aurEff->CalculatePeriodic(GetCaster());
        }

        void Register()
        {
            DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_shadowfang_keep_haunting_spirits_AuraScript::CalcPeriodic, EFFECT_0, SPELL_AURA_DUMMY);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_shadowfang_keep_haunting_spirits_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_DUMMY);
            OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_shadowfang_keep_haunting_spirits_AuraScript::HandleUpdatePeriodic, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_shadowfang_keep_haunting_spirits_AuraScript();
    }
};

void AddSC_instance_shadowfang_keep()
{
    new instance_shadowfang_keep();
    new spell_shadowfang_keep_haunting_spirits();
}

