
class instance_slave_pens : public InstanceMapScript
{
public:
    instance_slave_pens() : InstanceMapScript("instance_slave_pens", 547) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_slave_pens_script(map);
    }

    struct instance_slave_pens_script : public InstanceScript
    {
        instance_slave_pens_script(Map* pMap) : InstanceScript(pMap) { }
    };
};

void AddSC_instance_slave_pens()
{
    new instance_slave_pens();
}
