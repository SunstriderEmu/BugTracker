
class ItemTest : ItemScript
{
public:
    ItemTest() : ItemScript("item_test") {}

    bool OnUse(Player* player, Item* _Item, SpellCastTargets const& targets) override
    {
        player->Say("Item test!", LANG_UNIVERSAL);
        return true;
    }
};


void AddSC_item_test()
{
    new ItemTest();
}

