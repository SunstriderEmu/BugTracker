/*

RECAP

Lieutenant Jackspring sells Grand Marshal's weapons.  (lvl 60)
Sergeant Major Clate  sells Field Marshal's sets.     (lvl 60)
Grand Marshal's set and weapons were removed in patch 2.4.0 (some months before season 4 started) but we prefer to remove them with season 3 since their prices are the same of S1 gear.

                               ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                              |                   SEASON 1                  |                   SEASON 2                  |                   SEASON 3                  |                   SEASON 4                  |
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
[A] CAPTAIN_DIRGEHAMMER       | Grand Marshal's set + off set + S1 off set  | Grand Marshal's set + off set               | S1 set                                      | S2 set                                      |
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
[A] CAPTAIN_ONEAL             | Grand Marshal's weapons                     | Grand Marshal's weapons                     | S1 weapons                                  | S2 weapons                                  |
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
[A] LIEUTENANT_TRISTIA        |/////////////////////////////////////////////| S2 off set                                  | S2 rings + S3 off set                       | S3 rings + S4 off set                       |
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////|
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
[H] LADY_PALANSEER            | High Warlord's set + off set + S1 off set   | High Warlord's set + off set                | S1 set                                      | S2 set                                      |
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
[H] SERGEANT_THUNDERHORN      | High Warlord's weapons                      | High Warlord's weapons                      | S1 weapons                                  | S2 weapons                                  |
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
[H] @SERGEANT_KIEN            |/////////////////////////////////////////////| S2 off set                                  |/////////////////////////////////////////////|/////////////////////////////////////////////|
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
[H] @DORIS_VOLANTHIUS         |/////////////////////////////////////////////|/////////////////////////////////////////////| S2 rings + S3 off set                       | S3 rings + S4 off set                       |
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////|
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
[N] VIXTON_PINCHWHISTLE       | S1 Set + weapons                            | S1 Set + weapons                            |/////////////////////////////////////////////|/////////////////////////////////////////////|
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
[N] KRIXEL_PINCHWHISTLE       |/////////////////////////////////////////////| S2 Set + weapons                            | S2 Set + weapons                            |/////////////////////////////////////////////|
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
[N] LEENIE_SMILEY_SMALLS      |/////////////////////////////////////////////|/////////////////////////////////////////////| S3 Set + weapons                            | S3 Set + weapons                            |
[N] EXPLODYNE_FIZZLESPURT     |/////////////////////////////////////////////|/////////////////////////////////////////////|                                             |                                             |
[N] ECTON_BRASSTUMBLER        |/////////////////////////////////////////////|/////////////////////////////////////////////|                                             |                                             |
[N] MEMINNIE                  |/////////////////////////////////////////////|/////////////////////////////////////////////|                                             |                                             |
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
[N] BIG_ZOKK_TORQUEWRENCH     |/////////////////////////////////////////////|/////////////////////////////////////////////|/////////////////////////////////////////////| S4 Set + weapons                            |
[N] GRIKKIN_COPPERSPRING      |/////////////////////////////////////////////|/////////////////////////////////////////////|/////////////////////////////////////////////|                                             |
[N] FRIXEE_BRASSTUMBLER       |/////////////////////////////////////////////|/////////////////////////////////////////////|/////////////////////////////////////////////|                                             |
[N] EVEE_COPPERSPRING         |/////////////////////////////////////////////|/////////////////////////////////////////////|/////////////////////////////////////////////|                                             |
[N] ONTOK_SHATTERHORN         |/////////////////////////////////////////////|/////////////////////////////////////////////|/////////////////////////////////////////////|                                             |
------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|---------------------------------------------|
*/

# Seasons
SET @SEASON_1 := 72;
SET @SEASON_2 := 73;
SET @SEASON_3 := 74;
SET @SEASON_4 := 75;

# Vendor NPCs
SET @CAPTAIN_DIRGEHAMMER    := 14;
SET @LIEUTENANT_TRISTIA     := 18;
SET @CAPTAIN_ONEAL          := 23;
SET @ONTOK_SHATTERHORN      := 1808;
SET @LEENIE_SMILEY_SMALLS   := 17557;
SET @EVEE_COPPERSPRING      := 21653;
SET @ECTON_BRASSTUMBLER     := 22984;
SET @EXPLODYNE_FIZZLESPURT  := 67189;
SET @FRIXEE_BRASSTUMBLER    := 75065;
SET @MEMINNIE               := 70192;
SET @GRIKKIN_COPPERSPRING   := 75101;
SET @LADY_PALANSEER         := 85163;
SET @SERGEANT_THUNDERHORN   := 85165;
SET @BIG_ZOKK_TORQUEWRENCH  := 90413;
SET @KRIXEL_PINCHWHISTLE    := 310979;
SET @VIXTON_PINCHWHISTLE    := 310980;
SET @SERGEANT_KIEN          := 311131;
SET @DORIS_VOLANTHIUS       := 311132;

DELETE FROM npc_vendor WHERE entry IN (@CAPTAIN_DIRGEHAMMER,@LIEUTENANT_TRISTIA,@CAPTAIN_ONEAL,@ONTOK_SHATTERHORN,@LEENIE_SMILEY_SMALLS,@EVEE_COPPERSPRING,@ECTON_BRASSTUMBLER,@EXPLODYNE_FIZZLESPURT,@FRIXEE_BRASSTUMBLER,@MEMINNIE,@GRIKKIN_COPPERSPRING,@LADY_PALANSEER,@SERGEANT_THUNDERHORN,@BIG_ZOKK_TORQUEWRENCH,@KRIXEL_PINCHWHISTLE,@VIXTON_PINCHWHISTLE,@SERGEANT_KIEN,@DORIS_VOLANTHIUS);

DELETE FROM game_event_creature WHERE guid IN (0,@CAPTAIN_DIRGEHAMMER,@LIEUTENANT_TRISTIA,@CAPTAIN_ONEAL,@ONTOK_SHATTERHORN,@LEENIE_SMILEY_SMALLS,@EVEE_COPPERSPRING,@ECTON_BRASSTUMBLER,@EXPLODYNE_FIZZLESPURT,@FRIXEE_BRASSTUMBLER,@MEMINNIE,@GRIKKIN_COPPERSPRING,@LADY_PALANSEER,@SERGEANT_THUNDERHORN,@BIG_ZOKK_TORQUEWRENCH,@KRIXEL_PINCHWHISTLE,@VIXTON_PINCHWHISTLE,@SERGEANT_KIEN,@DORIS_VOLANTHIUS);
INSERT INTO game_event_creature (guid, event) VALUES
(@LIEUTENANT_TRISTIA,     @SEASON_2),
(@LIEUTENANT_TRISTIA,     @SEASON_3),
(@LIEUTENANT_TRISTIA,     @SEASON_4),
(@SERGEANT_KIEN,          @SEASON_2),
(@DORIS_VOLANTHIUS,       @SEASON_3),
(@DORIS_VOLANTHIUS,       @SEASON_4),
(@VIXTON_PINCHWHISTLE,    @SEASON_1),
(@VIXTON_PINCHWHISTLE,    @SEASON_2),
(@KRIXEL_PINCHWHISTLE,    @SEASON_2),
(@KRIXEL_PINCHWHISTLE,    @SEASON_3),
(@LEENIE_SMILEY_SMALLS,   @SEASON_3),
(@EXPLODYNE_FIZZLESPURT,  @SEASON_3),
(@ECTON_BRASSTUMBLER,     @SEASON_3),
(@MEMINNIE,               @SEASON_3),
(@LEENIE_SMILEY_SMALLS,   @SEASON_4),
(@EXPLODYNE_FIZZLESPURT,  @SEASON_4),
(@ECTON_BRASSTUMBLER,     @SEASON_4),
(@MEMINNIE,               @SEASON_4),
(@BIG_ZOKK_TORQUEWRENCH,  @SEASON_4),
(@GRIKKIN_COPPERSPRING,   @SEASON_4),
(@FRIXEE_BRASSTUMBLER,    @SEASON_4),
(@EVEE_COPPERSPRING,      @SEASON_4),
(@ONTOK_SHATTERHORN,      @SEASON_4);

# Costs
-- HP    Honor Point
-- AP    Arena Point
-- AB    Arathi Basin Mark
-- AV    Alterac Valley Mark
-- ES    Eye of the Storm Mark
-- WSG   Warsong Gulch Mark
-- R     Rating
SET @COST_15300_HP_10_ES            := 127;
SET @COST_11934_HP_10_AV            := 129;
SET @COST_30600_HP_40_AB            := 131;
SET @COST_14280_HP_40_AB            := 172;
SET @COST_5500_HP_20_AV             := 202;
SET @COST_8750_HP_30_AV             := 203;
SET @COST_8750_HP_30_WSG            := 204;
SET @COST_5500_HP_20_AB             := 205;
SET @COST_15300_HP_20_ES            := 348;
SET @COST_20400_HP_40_AV            := 360;
SET @COST_17850_HP_40_AB            := 1923;
SET @COST_27000_HP_40_AV            := 2237;
SET @COST_25200_HP_20_ES            := 2238;
SET @COST_18000_HP_20_ES            := 2239;
SET @COST_9000_HP_20_ES             := 2240;
SET @COST_8000_HP_10_ES             := 2241;
SET @COST_15000_HP_20_ES            := 2242;
SET @COST_11934_HP_10_ES            := 2248;
SET @COST_10500_HP_20_AV            := 2277;
SET @COST_11250_HP_20_AB            := 2278;
SET @COST_14500_HP_30_AB            := 2279;
SET @COST_14500_HP_30_AV            := 2280;
SET @COST_14500_HP_30_WSG           := 2281;
SET @COST_1125_AP                   := 2283;
SET @COST_1500_AP                   := 2288;
SET @COST_30000_HP_40_AV            := 2289;
SET @COST_1875_AP_20_WSG_1575_R     := 2337;
SET @COST_1000_AP_1750_R            := 2339;
SET @COST_1500_AP_2200_R            := 2359;
SET @COST_3750_AP_2050_R            := 2360;
SET @COST_3150_AP_2050_R            := 2361;
SET @COST_2625_AP_2050_R            := 2362;
SET @COST_1125_AP_2050_R            := 2363;
SET @COST_1875_AP_2050_R            := 2364;
SET @COST_1875_AP_1700_R            := 2365;
SET @COST_1875_AP_1550_R            := 2366;
SET @COST_2520_AP_1800_R            := 2385;
SET @COST_3000_AP_1800_R            := 2386;
SET @COST_900_AP                    := 2387;
SET @COST_800_AP                    := 2388;
SET @COST_2100_AP_1800_R            := 2389;
SET @COST_900_AP_1800_R             := 2390;
SET @COST_1500_AP_1800_R            := 2391;
SET @COST_1200_AP_1950_R            := 2392;
SET @COST_17850_HP_40_ES_1700_R     := 2400;
SET @COST_11794_HP_20_WSG_1600_R    := 2401;
SET @COST_15300_HP_10_AV_1650_R     := 2402;
SET @COST_9199_HP_20_WSG            := 2405;
SET @COST_13923_HP_40_ES            := 2406;

# Season 1
DELETE FROM game_event_npc_vendor WHERE event = @SEASON_1;
INSERT INTO game_event_npc_vendor (event, guid, item, maxcount, incrtime, ExtendedCost) VALUES
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28613, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Chain Armor
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28614, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Chain Gauntlets
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28615, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Chain Helm
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28616, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Chain Leggings
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28617, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Chain Spaulders
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28618, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Dragonhide Gloves
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28619, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Dragonhide Helm
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28620, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Dragonhide Legguards
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28622, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Dragonhide Spaulders
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28623, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Dragonhide Tunic
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28624, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Dreadweave Gloves
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28625, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Dreadweave Hood
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28626, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Dreadweave Leggings
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28627, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Dreadweave Mantle
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28628, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Dreadweave Robe
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28679, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Lamellar Chestpiece
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28680, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Lamellar Gauntlets
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28681, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Lamellar Helm
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28724, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Lamellar Legguards
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28683, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Lamellar Shoulders
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28684, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Leather Gloves
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28685, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Leather Helm
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28686, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Leather Legguards
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28687, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Leather Spaulders
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28688, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Leather Tunic
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28689, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Linked Armor
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28690, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Linked Gauntlets
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28691, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Linked Helm
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28692, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Linked Leggings
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28693, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Linked Spaulders
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28694, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Mail Armor
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28695, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Mail Gauntlets
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28696, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Mail Helm
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28697, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Mail Leggings
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28698, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Mail Spaulders
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28699, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Plate Chestpiece
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28700, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Plate Gauntlets
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28701, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Plate Helm
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28702, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Plate Legguards
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28703, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Plate Shoulders
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28704, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Satin Gloves
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28705, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Satin Hood
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28706, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Satin Leggings
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28707, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Satin Mantle
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28708, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Satin Robe
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28709, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Scaled Chestpiece
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28710, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Scaled Gauntlets
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28711, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Scaled Helm
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28712, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Scaled Legguards
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28713, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Scaled Shoulders
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28714, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Silk Amice
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28715, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Silk Cowl
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28716, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Silk Handguards
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28717, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Silk Raiment
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28718, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Silk Trousers
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28719, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Wyrmhide Gloves
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28720, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Wyrmhide Helm
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28721, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Wyrmhide Legguards
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28722, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Wyrmhide Spaulders
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28723, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Wyrmhide Tunic
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31589, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Kodohide Gloves
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31590, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Kodohide Helm
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31591, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Kodohide Legguards
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31592, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Kodohide Spaulders
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31593, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Kodohide Tunic
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31596, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Kodohide Belt
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31597, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Marshal's Kodohide Boots
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31599, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Marshal's Kodohide Bracers
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31620, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Mooncloth Mitts
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31622, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Mooncloth Cowl
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31623, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Mooncloth Legguards
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31624, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Mooncloth Shoulderpads
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31625, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Mooncloth Vestments
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31630, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Ornamented Chestplate
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31631, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Ornamented Gloves
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31632, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Ornamented Headguard
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31633, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Ornamented Leggings
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31634, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Ornamented Spaulders
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31640, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Ringmail Chestguard
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31641, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Ringmail Gloves
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31642, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Ringmail Headpiece
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31643, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Ringmail Legguards
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 31644, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Ringmail Shoulderpads
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28973, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Marshal's Chain Bracers
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28974, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Chain Girdle
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28975, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Marshal's Chain Sabatons
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28976, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Dragonhide Belt
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28977, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Marshal's Dragonhide Boots
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28978, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Marshal's Dragonhide Bracers
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28980, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Dreadweave Belt
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28981, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Marshal's Dreadweave Cuffs
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28982, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Marshal's Dreadweave Stalkers
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28983, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Lamellar Belt
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28984, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Marshal's Lamellar Bracers
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28985, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Lamellar Greaves
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28986, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Leather Belt
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28987, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Marshal's Leather Boots
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28988, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Marshal's Leather Bracers
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28989, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Marshal's Linked Bracers
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28990, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Linked Girdle
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28991, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Marshal's Linked Sabatons
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28992, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Marshal's Mail Bracers
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28993, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Mail Girdle
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28994, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Marshal's Mail Sabatons
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28995, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Plate Belt
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28996, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Marshal's Plate Bracers
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28997, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Marshal's Plate Greaves
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28998, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Scaled Belt
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 28999, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Marshal's Scaled Bracers
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 29000, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Marshal's Scaled Greaves
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 29001, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Silk Belt
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 29002, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Marshal's Silk Cuffs
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 29003, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Marshal's Silk Footguards
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 29004, 0, 0, @COST_17850_HP_40_AB), -- Marshal's Wyrmhide Belt
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 29005, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Marshal's Wyrmhide Boots
(@SEASON_1, @CAPTAIN_DIRGEHAMMER, 29006, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Marshal's Wyrmhide Bracers
(@SEASON_1, @CAPTAIN_ONEAL, 28950, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Bonecracker
(@SEASON_1, @CAPTAIN_ONEAL, 28942, 0, 0, @COST_30600_HP_40_AB), -- Grand Marshal's Bonegrinder
(@SEASON_1, @CAPTAIN_ONEAL, 28944, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Cleaver
(@SEASON_1, @CAPTAIN_ONEAL, 28945, 0, 0, @COST_30600_HP_40_AB), -- Grand Marshal's Decapitator
(@SEASON_1, @CAPTAIN_ONEAL, 28946, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Hacker
(@SEASON_1, @CAPTAIN_ONEAL, 28960, 0, 0, @COST_20400_HP_40_AV), -- Grand Marshal's Heavy Crossbow
(@SEASON_1, @CAPTAIN_ONEAL, 28947, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Left Ripper
(@SEASON_1, @CAPTAIN_ONEAL, 28948, 0, 0, @COST_30600_HP_40_AB), -- Grand Marshal's Maul
(@SEASON_1, @CAPTAIN_ONEAL, 28949, 0, 0, @COST_30600_HP_40_AB), -- Grand Marshal's Painsaw
(@SEASON_1, @CAPTAIN_ONEAL, 28951, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Pummeler
(@SEASON_1, @CAPTAIN_ONEAL, 28952, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Quickblade
(@SEASON_1, @CAPTAIN_ONEAL, 28953, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Right Ripper
(@SEASON_1, @CAPTAIN_ONEAL, 28954, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Shanker
(@SEASON_1, @CAPTAIN_ONEAL, 28955, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Shiv
(@SEASON_1, @CAPTAIN_ONEAL, 28956, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Slicer
(@SEASON_1, @CAPTAIN_ONEAL, 28957, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Spellblade
(@SEASON_1, @CAPTAIN_ONEAL, 28959, 0, 0, @COST_30600_HP_40_AB), -- Grand Marshal's War Staff
(@SEASON_1, @CAPTAIN_ONEAL, 28943, 0, 0, @COST_30600_HP_40_AB), -- Grand Marshal's Warblade
(@SEASON_1, @CAPTAIN_ONEAL, 28941, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Battletome
(@SEASON_1, @CAPTAIN_ONEAL, 28940, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Barricade
(@SEASON_1, @LADY_PALANSEER, 28381, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- General's Plate Bracers
(@SEASON_1, @LADY_PALANSEER, 28383, 0, 0, @COST_17850_HP_40_ES_1700_R), -- General's Plate Greaves
(@SEASON_1, @LADY_PALANSEER, 28385, 0, 0, @COST_17850_HP_40_AB), -- General's Plate Belt
(@SEASON_1, @LADY_PALANSEER, 28402, 0, 0, @COST_17850_HP_40_ES_1700_R), -- General's Dreadweave Stalkers
(@SEASON_1, @LADY_PALANSEER, 28404, 0, 0, @COST_17850_HP_40_AB), -- General's Dreadweave Belt
(@SEASON_1, @LADY_PALANSEER, 28405, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- General's Dreadweave Cuffs
(@SEASON_1, @LADY_PALANSEER, 28409, 0, 0, @COST_17850_HP_40_AB), -- General's Silk Belt
(@SEASON_1, @LADY_PALANSEER, 28410, 0, 0, @COST_17850_HP_40_ES_1700_R), -- General's Silk Footguards
(@SEASON_1, @LADY_PALANSEER, 28411, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- General's Silk Cuffs
(@SEASON_1, @LADY_PALANSEER, 28422, 0, 0, @COST_17850_HP_40_ES_1700_R), -- General's Leather Boots
(@SEASON_1, @LADY_PALANSEER, 28423, 0, 0, @COST_17850_HP_40_AB), -- General's Leather Belt
(@SEASON_1, @LADY_PALANSEER, 28424, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- General's Leather Bracers
(@SEASON_1, @LADY_PALANSEER, 28443, 0, 0, @COST_17850_HP_40_AB), -- General's Dragonhide Belt
(@SEASON_1, @LADY_PALANSEER, 28444, 0, 0, @COST_17850_HP_40_ES_1700_R), -- General's Dragonhide Boots
(@SEASON_1, @LADY_PALANSEER, 28445, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- General's Dragonhide Bracers
(@SEASON_1, @LADY_PALANSEER, 28446, 0, 0, @COST_17850_HP_40_AB), -- General's Wyrmhide Belt
(@SEASON_1, @LADY_PALANSEER, 28447, 0, 0, @COST_17850_HP_40_ES_1700_R), -- General's Wyrmhide Boots
(@SEASON_1, @LADY_PALANSEER, 28448, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- General's Wyrmhide Bracers
(@SEASON_1, @LADY_PALANSEER, 28449, 0, 0, @COST_17850_HP_40_ES_1700_R), -- General's Chain Sabatons
(@SEASON_1, @LADY_PALANSEER, 28450, 0, 0, @COST_17850_HP_40_AB), -- General's Chain Girdle
(@SEASON_1, @LADY_PALANSEER, 28451, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- General's Chain Bracers
(@SEASON_1, @LADY_PALANSEER, 28605, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- General's Linked Bracers
(@SEASON_1, @LADY_PALANSEER, 28629, 0, 0, @COST_17850_HP_40_AB), -- General's Linked Girdle
(@SEASON_1, @LADY_PALANSEER, 28630, 0, 0, @COST_17850_HP_40_ES_1700_R), -- General's Linked Sabatons
(@SEASON_1, @LADY_PALANSEER, 28638, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- General's Mail Bracers
(@SEASON_1, @LADY_PALANSEER, 28639, 0, 0, @COST_17850_HP_40_AB), -- General's Mail Girdle
(@SEASON_1, @LADY_PALANSEER, 28640, 0, 0, @COST_17850_HP_40_ES_1700_R), -- General's Mail Sabatons
(@SEASON_1, @LADY_PALANSEER, 28641, 0, 0, @COST_17850_HP_40_AB), -- General's Lamellar Belt
(@SEASON_1, @LADY_PALANSEER, 28642, 0, 0, @COST_17850_HP_40_ES_1700_R), -- General's Lamellar Greaves
(@SEASON_1, @LADY_PALANSEER, 28643, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- General's Lamellar Bracers
(@SEASON_1, @LADY_PALANSEER, 28644, 0, 0, @COST_17850_HP_40_AB), -- General's Scaled Belt
(@SEASON_1, @LADY_PALANSEER, 28645, 0, 0, @COST_17850_HP_40_ES_1700_R), -- General's Scaled Greaves
(@SEASON_1, @LADY_PALANSEER, 28646, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- General's Scaled Bracers
(@SEASON_1, @LADY_PALANSEER, 28805, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Chain Armor
(@SEASON_1, @LADY_PALANSEER, 28806, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Chain Gauntlets
(@SEASON_1, @LADY_PALANSEER, 28807, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Chain Helm
(@SEASON_1, @LADY_PALANSEER, 28808, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Chain Leggings
(@SEASON_1, @LADY_PALANSEER, 28809, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Chain Spaulders
(@SEASON_1, @LADY_PALANSEER, 28811, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Dragonhide Gloves
(@SEASON_1, @LADY_PALANSEER, 28812, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Dragonhide Helm
(@SEASON_1, @LADY_PALANSEER, 28813, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Dragonhide Legguards
(@SEASON_1, @LADY_PALANSEER, 28814, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Dragonhide Spaulders
(@SEASON_1, @LADY_PALANSEER, 28815, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Dragonhide Tunic
(@SEASON_1, @LADY_PALANSEER, 28817, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Dreadweave Gloves
(@SEASON_1, @LADY_PALANSEER, 28818, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Dreadweave Hood
(@SEASON_1, @LADY_PALANSEER, 28819, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Dreadweave Leggings
(@SEASON_1, @LADY_PALANSEER, 28820, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Dreadweave Mantle
(@SEASON_1, @LADY_PALANSEER, 28821, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Dreadweave Robe
(@SEASON_1, @LADY_PALANSEER, 28831, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Lamellar Chestpiece
(@SEASON_1, @LADY_PALANSEER, 28832, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Lamellar Gauntlets
(@SEASON_1, @LADY_PALANSEER, 28833, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Lamellar Helm
(@SEASON_1, @LADY_PALANSEER, 28834, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Lamellar Legguards
(@SEASON_1, @LADY_PALANSEER, 28835, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Lamellar Shoulders
(@SEASON_1, @LADY_PALANSEER, 28836, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Leather Gloves
(@SEASON_1, @LADY_PALANSEER, 28837, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Leather Helm
(@SEASON_1, @LADY_PALANSEER, 28838, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Leather Legguards
(@SEASON_1, @LADY_PALANSEER, 28839, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Leather Spaulders
(@SEASON_1, @LADY_PALANSEER, 28840, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Leather Tunic
(@SEASON_1, @LADY_PALANSEER, 28841, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Linked Armor
(@SEASON_1, @LADY_PALANSEER, 28842, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Linked Gauntlets
(@SEASON_1, @LADY_PALANSEER, 28843, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Linked Helm
(@SEASON_1, @LADY_PALANSEER, 28844, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Linked Leggings
(@SEASON_1, @LADY_PALANSEER, 28845, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Linked Spaulders
(@SEASON_1, @LADY_PALANSEER, 28846, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Mail Armor
(@SEASON_1, @LADY_PALANSEER, 28847, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Mail Gauntlets
(@SEASON_1, @LADY_PALANSEER, 28848, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Mail Helm
(@SEASON_1, @LADY_PALANSEER, 28849, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Mail Leggings
(@SEASON_1, @LADY_PALANSEER, 28850, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Mail Spaulders
(@SEASON_1, @LADY_PALANSEER, 28851, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Plate Chestpiece
(@SEASON_1, @LADY_PALANSEER, 28852, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Plate Gauntlets
(@SEASON_1, @LADY_PALANSEER, 28853, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Plate Helm
(@SEASON_1, @LADY_PALANSEER, 28854, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Plate Legguards
(@SEASON_1, @LADY_PALANSEER, 28855, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Plate Shoulders
(@SEASON_1, @LADY_PALANSEER, 28856, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Satin Gloves
(@SEASON_1, @LADY_PALANSEER, 28857, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Satin Hood
(@SEASON_1, @LADY_PALANSEER, 28858, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Satin Leggings
(@SEASON_1, @LADY_PALANSEER, 28859, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Satin Mantle
(@SEASON_1, @LADY_PALANSEER, 28860, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Satin Robe
(@SEASON_1, @LADY_PALANSEER, 28861, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Scaled Chestpiece
(@SEASON_1, @LADY_PALANSEER, 28862, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Scaled Gauntlets
(@SEASON_1, @LADY_PALANSEER, 28863, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Scaled Helm
(@SEASON_1, @LADY_PALANSEER, 28864, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Scaled Legguards
(@SEASON_1, @LADY_PALANSEER, 28865, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Scaled Shoulders
(@SEASON_1, @LADY_PALANSEER, 28866, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Silk Amice
(@SEASON_1, @LADY_PALANSEER, 28867, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Silk Cowl
(@SEASON_1, @LADY_PALANSEER, 28868, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Silk Handguards
(@SEASON_1, @LADY_PALANSEER, 28869, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Silk Raiment
(@SEASON_1, @LADY_PALANSEER, 28870, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Silk Trousers
(@SEASON_1, @LADY_PALANSEER, 28871, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Wyrmhide Gloves
(@SEASON_1, @LADY_PALANSEER, 28872, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Wyrmhide Helm
(@SEASON_1, @LADY_PALANSEER, 28873, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Wyrmhide Legguards
(@SEASON_1, @LADY_PALANSEER, 28874, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Wyrmhide Spaulders
(@SEASON_1, @LADY_PALANSEER, 28875, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Wyrmhide Tunic
(@SEASON_1, @LADY_PALANSEER, 31584, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Kodohide Gloves
(@SEASON_1, @LADY_PALANSEER, 31585, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Kodohide Helm
(@SEASON_1, @LADY_PALANSEER, 31586, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Kodohide Legguards
(@SEASON_1, @LADY_PALANSEER, 31587, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Kodohide Spaulders
(@SEASON_1, @LADY_PALANSEER, 31588, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Kodohide Tunic
(@SEASON_1, @LADY_PALANSEER, 31594, 0, 0, @COST_17850_HP_40_AB), -- General's Kodohide Belt
(@SEASON_1, @LADY_PALANSEER, 31595, 0, 0, @COST_17850_HP_40_ES_1700_R), -- General's Kodohide Boots
(@SEASON_1, @LADY_PALANSEER, 31598, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- General's Kodohide Bracers
(@SEASON_1, @LADY_PALANSEER, 31621, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Mooncloth Mitts
(@SEASON_1, @LADY_PALANSEER, 31626, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Mooncloth Cowl
(@SEASON_1, @LADY_PALANSEER, 31627, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Mooncloth Legguards
(@SEASON_1, @LADY_PALANSEER, 31628, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Mooncloth Shoulderpads
(@SEASON_1, @LADY_PALANSEER, 31629, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Mooncloth Vestments
(@SEASON_1, @LADY_PALANSEER, 31635, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Ornamented Chestplate
(@SEASON_1, @LADY_PALANSEER, 31636, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Ornamented Gloves
(@SEASON_1, @LADY_PALANSEER, 31637, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Ornamented Headguard
(@SEASON_1, @LADY_PALANSEER, 31638, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Ornamented Leggings
(@SEASON_1, @LADY_PALANSEER, 31639, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Ornamented Spaulders
(@SEASON_1, @LADY_PALANSEER, 31646, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Ringmail Chestguard
(@SEASON_1, @LADY_PALANSEER, 31647, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Ringmail Gloves
(@SEASON_1, @LADY_PALANSEER, 31648, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Ringmail Headpiece
(@SEASON_1, @LADY_PALANSEER, 31649, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Ringmail Legguards
(@SEASON_1, @LADY_PALANSEER, 31650, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Ringmail Shoulderpads
(@SEASON_1, @SERGEANT_THUNDERHORN, 28293, 0, 0, @COST_30600_HP_40_AB), -- High Warlord's Claymore
(@SEASON_1, @SERGEANT_THUNDERHORN, 28917, 0, 0, @COST_30600_HP_40_AB), -- High Warlord's Bonegrinder
(@SEASON_1, @SERGEANT_THUNDERHORN, 28918, 0, 0, @COST_30600_HP_40_AB), -- High Warlord's Decapitator
(@SEASON_1, @SERGEANT_THUNDERHORN, 28919, 0, 0, @COST_30600_HP_40_AB), -- High Warlord's Maul
(@SEASON_1, @SERGEANT_THUNDERHORN, 28920, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Cleaver
(@SEASON_1, @SERGEANT_THUNDERHORN, 28921, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Hacker
(@SEASON_1, @SERGEANT_THUNDERHORN, 28922, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Left Ripper
(@SEASON_1, @SERGEANT_THUNDERHORN, 28923, 0, 0, @COST_30600_HP_40_AB), -- High Warlord's Painsaw
(@SEASON_1, @SERGEANT_THUNDERHORN, 28924, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Bonecracker
(@SEASON_1, @SERGEANT_THUNDERHORN, 28925, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Pummeler
(@SEASON_1, @SERGEANT_THUNDERHORN, 28926, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Quickblade
(@SEASON_1, @SERGEANT_THUNDERHORN, 28928, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Right Ripper
(@SEASON_1, @SERGEANT_THUNDERHORN, 28929, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Shanker
(@SEASON_1, @SERGEANT_THUNDERHORN, 28930, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Shiv
(@SEASON_1, @SERGEANT_THUNDERHORN, 28931, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Spellblade
(@SEASON_1, @SERGEANT_THUNDERHORN, 28933, 0, 0, @COST_20400_HP_40_AV), -- High Warlord's Heavy Crossbow
(@SEASON_1, @SERGEANT_THUNDERHORN, 28935, 0, 0, @COST_30600_HP_40_AB), -- High Warlord's War Staff
(@SEASON_1, @SERGEANT_THUNDERHORN, 28937, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Slicer
(@SEASON_1, @SERGEANT_THUNDERHORN, 28938, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Battletome
(@SEASON_1, @SERGEANT_THUNDERHORN, 28939, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Barricade
(@SEASON_1, @VIXTON_PINCHWHISTLE, 24544, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Plate Chestpiece
(@SEASON_1, @VIXTON_PINCHWHISTLE, 24545, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Plate Helm
(@SEASON_1, @VIXTON_PINCHWHISTLE, 24546, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Plate Shoulders
(@SEASON_1, @VIXTON_PINCHWHISTLE, 24547, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Plate Legguards
(@SEASON_1, @VIXTON_PINCHWHISTLE, 24549, 0, 0, @COST_1125_AP), -- Gladiator's Plate Gauntlets
(@SEASON_1, @VIXTON_PINCHWHISTLE, 24550, 0, 0, @COST_3750_AP_2050_R), -- Gladiator's Greatsword
(@SEASON_1, @VIXTON_PINCHWHISTLE, 24552, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Dreadweave Robe
(@SEASON_1, @VIXTON_PINCHWHISTLE, 24553, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Dreadweave Hood
(@SEASON_1, @VIXTON_PINCHWHISTLE, 24554, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Dreadweave Mantle
(@SEASON_1, @VIXTON_PINCHWHISTLE, 24555, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Dreadweave Leggings
(@SEASON_1, @VIXTON_PINCHWHISTLE, 24556, 0, 0, @COST_1125_AP), -- Gladiator's Dreadweave Gloves
(@SEASON_1, @VIXTON_PINCHWHISTLE, 24557, 0, 0, @COST_3750_AP_2050_R), -- Gladiator's War Staff
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25830, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Leather Helm
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25831, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Leather Tunic
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25832, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Leather Spaulders
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25833, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Leather Legguards
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25834, 0, 0, @COST_1125_AP), -- Gladiator's Leather Gloves
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25854, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Silk Amice
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25855, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Silk Cowl
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25856, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Silk Raiment
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25857, 0, 0, @COST_1125_AP), -- Gladiator's Silk Handguards
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25858, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Silk Trousers
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25997, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Linked Armor
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25998, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Linked Helm
(@SEASON_1, @VIXTON_PINCHWHISTLE, 25999, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Linked Spaulders
(@SEASON_1, @VIXTON_PINCHWHISTLE, 26000, 0, 0, @COST_1125_AP), -- Gladiator's Linked Gauntlets
(@SEASON_1, @VIXTON_PINCHWHISTLE, 26001, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Linked Leggings
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27469, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Mail Armor
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27470, 0, 0, @COST_1125_AP), -- Gladiator's Mail Gauntlets
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27471, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Mail Helm
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27472, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Mail Leggings
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27473, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Mail Spaulders
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27702, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Lamellar Chestpiece
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27703, 0, 0, @COST_1125_AP), -- Gladiator's Lamellar Gauntlets
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27704, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Lamellar Helm
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27705, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Lamellar Legguards
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27706, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Lamellar Shoulders
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27707, 0, 0, @COST_1125_AP), -- Gladiator's Satin Gloves
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27708, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Satin Hood
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27709, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Satin Leggings
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27710, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Satin Mantle
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27711, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Satin Robe
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27879, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Scaled Chestpiece
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27880, 0, 0, @COST_1125_AP), -- Gladiator's Scaled Gauntlets
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27881, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Scaled Helm
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27882, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Scaled Legguards
(@SEASON_1, @VIXTON_PINCHWHISTLE, 27883, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Scaled Shoulders
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28126, 0, 0, @COST_1125_AP), -- Gladiator's Dragonhide Gloves
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28127, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Dragonhide Helm
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28128, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Dragonhide Legguards
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28129, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Dragonhide Spaulders
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28130, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Dragonhide Tunic
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28136, 0, 0, @COST_1125_AP), -- Gladiator's Wyrmhide Gloves
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28137, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Wyrmhide Helm
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28138, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Wyrmhide Legguards
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28139, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Wyrmhide Spaulders
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28140, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Wyrmhide Tunic
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28294, 0, 0, @COST_3750_AP_2050_R), -- Gladiator's Heavy Crossbow
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28295, 0, 0, @COST_2625_AP_2050_R), -- Gladiator's Slicer
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28297, 0, 0, @COST_3150_AP_2050_R), -- Gladiator's Spellblade
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28298, 0, 0, @COST_3750_AP_2050_R), -- Gladiator's Decapitator
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28299, 0, 0, @COST_3750_AP_2050_R), -- Gladiator's Bonegrinder
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28300, 0, 0, @COST_3750_AP_2050_R), -- Gladiator's Painsaw
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28302, 0, 0, @COST_1125_AP_2050_R), -- Gladiator's Bonecracker
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28305, 0, 0, @COST_2625_AP_2050_R), -- Gladiator's Pummeler
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28307, 0, 0, @COST_1125_AP_2050_R), -- Gladiator's Quickblade
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28308, 0, 0, @COST_2625_AP_2050_R), -- Gladiator's Cleaver
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28309, 0, 0, @COST_1125_AP_2050_R), -- Gladiator's Hacker
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28310, 0, 0, @COST_1125_AP_2050_R), -- Gladiator's Shiv
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28312, 0, 0, @COST_2625_AP_2050_R), -- Gladiator's Shanker
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28313, 0, 0, @COST_2625_AP_2050_R), -- Gladiator's Right Ripper
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28314, 0, 0, @COST_1125_AP_2050_R), -- Gladiator's Left Ripper
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28319, 0, 0, @COST_1000_AP_1750_R), -- Gladiator's War Edge
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28320, 0, 0, @COST_1000_AP_1750_R), -- Gladiator's Touch of Defeat
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28331, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Chain Helm
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28332, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Chain Leggings
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28333, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Chain Spaulders
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28334, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Chain Armor
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28335, 0, 0, @COST_1125_AP), -- Gladiator's Chain Gauntlets
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28346, 0, 0, @COST_1125_AP_2050_R), -- Gladiator's Endgame
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28355, 0, 0, @COST_1000_AP_1750_R), -- Gladiator's Idol of Tenacity
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28356, 0, 0, @COST_1000_AP_1750_R), -- Gladiator's Libram of Justice
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28357, 0, 0, @COST_1000_AP_1750_R), -- Gladiator's Totem of the Third Wind
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28358, 0, 0, @COST_1875_AP_2050_R), -- Gladiator's Shield Wall
(@SEASON_1, @VIXTON_PINCHWHISTLE, 28476, 0, 0, @COST_3750_AP_2050_R), -- Gladiator's Maul
(@SEASON_1, @VIXTON_PINCHWHISTLE, 30186, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Felweave Amice
(@SEASON_1, @VIXTON_PINCHWHISTLE, 30187, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Felweave Cowl
(@SEASON_1, @VIXTON_PINCHWHISTLE, 30188, 0, 0, @COST_1125_AP), -- Gladiator's Felweave Handguards
(@SEASON_1, @VIXTON_PINCHWHISTLE, 30200, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Felweave Raiment
(@SEASON_1, @VIXTON_PINCHWHISTLE, 30201, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Felweave Trousers
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31375, 0, 0, @COST_1125_AP), -- Gladiator's Kodohide Gloves
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31376, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Kodohide Helm
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31377, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Kodohide Legguards
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31378, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Kodohide Spaulders
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31379, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Kodohide Tunic
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31396, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Ringmail Armor
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31397, 0, 0, @COST_1125_AP), -- Gladiator's Ringmail Gauntlets
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31400, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Ringmail Helm
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31406, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Ringmail Leggings
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31407, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Ringmail Spaulders
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31409, 0, 0, @COST_1125_AP), -- Gladiator's Mooncloth Gloves
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31410, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Mooncloth Hood
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31411, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Mooncloth Leggings
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31412, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Mooncloth Mantle
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31413, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Mooncloth Robe
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31613, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Gladiator's Ornamented Chestguard
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31614, 0, 0, @COST_1125_AP), -- Gladiator's Ornamented Gloves
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31616, 0, 0, @COST_1875_AP_1700_R), -- Gladiator's Ornamented Headcover
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31618, 0, 0, @COST_1875_AP_1550_R), -- Gladiator's Ornamented Legplates
(@SEASON_1, @VIXTON_PINCHWHISTLE, 31619, 0, 0, @COST_1500_AP_2200_R), -- Gladiator's Ornamented Spaulders
(@SEASON_1, @VIXTON_PINCHWHISTLE, 32450, 0, 0, @COST_3150_AP_2050_R), -- Gladiator's Gavel
(@SEASON_1, @VIXTON_PINCHWHISTLE, 32451, 0, 0, @COST_3150_AP_2050_R), -- Gladiator's Salvation
(@SEASON_1, @VIXTON_PINCHWHISTLE, 32452, 0, 0, @COST_1125_AP_2050_R), -- Gladiator's Reprieve
(@SEASON_1, @VIXTON_PINCHWHISTLE, 33936, 0, 0, @COST_1000_AP_1750_R), -- Gladiator's Libram of Fortitude
(@SEASON_1, @VIXTON_PINCHWHISTLE, 33939, 0, 0, @COST_1000_AP_1750_R), -- Gladiator's Totem of Indomitability
(@SEASON_1, @VIXTON_PINCHWHISTLE, 33942, 0, 0, @COST_1000_AP_1750_R), -- Gladiator's Idol of Steadfastness
(@SEASON_1, @VIXTON_PINCHWHISTLE, 33945, 0, 0, @COST_1000_AP_1750_R), -- Gladiator's Idol of Resolve
(@SEASON_1, @VIXTON_PINCHWHISTLE, 33948, 0, 0, @COST_1000_AP_1750_R), -- Gladiator's Libram of Vengeance
(@SEASON_1, @VIXTON_PINCHWHISTLE, 33951, 0, 0, @COST_1000_AP_1750_R); -- Gladiator's Totem of Survival

# Season 2
DELETE FROM game_event_npc_vendor WHERE event = @SEASON_2;
INSERT INTO game_event_npc_vendor (event, guid, item, maxcount, incrtime, ExtendedCost) VALUES
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28613, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Chain Armor
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28614, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Chain Gauntlets
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28615, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Chain Helm
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28616, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Chain Leggings
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28617, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Chain Spaulders
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28618, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Dragonhide Gloves
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28619, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Dragonhide Helm
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28620, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Dragonhide Legguards
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28622, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Dragonhide Spaulders
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28623, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Dragonhide Tunic
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28624, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Dreadweave Gloves
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28625, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Dreadweave Hood
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28626, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Dreadweave Leggings
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28627, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Dreadweave Mantle
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28628, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Dreadweave Robe
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28679, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Lamellar Chestpiece
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28680, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Lamellar Gauntlets
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28681, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Lamellar Helm
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28724, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Lamellar Legguards
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28683, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Lamellar Shoulders
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28684, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Leather Gloves
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28685, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Leather Helm
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28686, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Leather Legguards
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28687, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Leather Spaulders
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28688, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Leather Tunic
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28689, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Linked Armor
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28690, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Linked Gauntlets
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28691, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Linked Helm
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28692, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Linked Leggings
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28693, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Linked Spaulders
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28694, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Mail Armor
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28695, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Mail Gauntlets
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28696, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Mail Helm
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28697, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Mail Leggings
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28698, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Mail Spaulders
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28699, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Plate Chestpiece
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28700, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Plate Gauntlets
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28701, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Plate Helm
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28702, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Plate Legguards
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28703, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Plate Shoulders
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28704, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Satin Gloves
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28705, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Satin Hood
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28706, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Satin Leggings
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28707, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Satin Mantle
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28708, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Satin Robe
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28709, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Scaled Chestpiece
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28710, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Scaled Gauntlets
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28711, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Scaled Helm
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28712, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Scaled Legguards
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28713, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Scaled Shoulders
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28714, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Silk Amice
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28715, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Silk Cowl
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28716, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Silk Handguards
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28717, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Silk Raiment
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28718, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Silk Trousers
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28719, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Wyrmhide Gloves
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28720, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Wyrmhide Helm
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28721, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Wyrmhide Legguards
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28722, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Wyrmhide Spaulders
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 28723, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Wyrmhide Tunic
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31589, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Kodohide Gloves
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31590, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Kodohide Helm
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31591, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Kodohide Legguards
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31592, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Kodohide Spaulders
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31593, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Kodohide Tunic
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31596, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Mooncloth Mitts
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31597, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Mooncloth Cowl
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31599, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Mooncloth Legguards
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31620, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Mooncloth Shoulderpads
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31622, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Mooncloth Vestments
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31623, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Ornamented Chestplate
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31624, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Ornamented Gloves
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31625, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Ornamented Headguard
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31630, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Ornamented Leggings
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31631, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Ornamented Spaulders
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31632, 0, 0, @COST_14500_HP_30_WSG), -- Grand Marshal's Ringmail Chestguard
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31633, 0, 0, @COST_5500_HP_20_AV), -- Grand Marshal's Ringmail Gloves
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31634, 0, 0, @COST_8750_HP_30_AV), -- Grand Marshal's Ringmail Headpiece
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31640, 0, 0, @COST_8750_HP_30_WSG), -- Grand Marshal's Ringmail Legguards
(@SEASON_2, @CAPTAIN_DIRGEHAMMER, 31641, 0, 0, @COST_5500_HP_20_AB), -- Grand Marshal's Ringmail Shoulderpads
(@SEASON_2, @LIEUTENANT_TRISTIA, 32785, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Chain Sabatons
(@SEASON_2, @LIEUTENANT_TRISTIA, 32786, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Dragonhide Boots
(@SEASON_2, @LIEUTENANT_TRISTIA, 32787, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Dreadweave Stalkers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32788, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Kodohide Boots
(@SEASON_2, @LIEUTENANT_TRISTIA, 32789, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Lamellar Greaves
(@SEASON_2, @LIEUTENANT_TRISTIA, 32790, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Leather Boots
(@SEASON_2, @LIEUTENANT_TRISTIA, 32791, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Linked Sabatons
(@SEASON_2, @LIEUTENANT_TRISTIA, 32792, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Mail Sabatons
(@SEASON_2, @LIEUTENANT_TRISTIA, 32793, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Plate Greaves
(@SEASON_2, @LIEUTENANT_TRISTIA, 32794, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Scaled Greaves
(@SEASON_2, @LIEUTENANT_TRISTIA, 32795, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Silk Footguards
(@SEASON_2, @LIEUTENANT_TRISTIA, 32796, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Wyrmhide Boots
(@SEASON_2, @LIEUTENANT_TRISTIA, 32797, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Chain Girdle
(@SEASON_2, @LIEUTENANT_TRISTIA, 32798, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Dragonhide Belt
(@SEASON_2, @LIEUTENANT_TRISTIA, 32799, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Dreadweave Belt
(@SEASON_2, @LIEUTENANT_TRISTIA, 32800, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Kodohide Belt
(@SEASON_2, @LIEUTENANT_TRISTIA, 32801, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Lamellar Belt
(@SEASON_2, @LIEUTENANT_TRISTIA, 32802, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Leather Belt
(@SEASON_2, @LIEUTENANT_TRISTIA, 32803, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Linked Girdle
(@SEASON_2, @LIEUTENANT_TRISTIA, 32804, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Mail Girdle
(@SEASON_2, @LIEUTENANT_TRISTIA, 32805, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Plate Belt
(@SEASON_2, @LIEUTENANT_TRISTIA, 32806, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Scaled Belt
(@SEASON_2, @LIEUTENANT_TRISTIA, 32807, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Silk Belt
(@SEASON_2, @LIEUTENANT_TRISTIA, 32808, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Wyrmhide Belt
(@SEASON_2, @LIEUTENANT_TRISTIA, 32809, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Chain Bracers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32810, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Dragonhide Bracers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32811, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Dreadweave Cuffs
(@SEASON_2, @LIEUTENANT_TRISTIA, 32812, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Kodohide Bracers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32813, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Lamellar Bracers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32814, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Leather Bracers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32816, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Linked Bracers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32817, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Mail Bracers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32818, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Plate Bracers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32819, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Scaled Bracers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32820, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Silk Cuffs
(@SEASON_2, @LIEUTENANT_TRISTIA, 32821, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Wyrmhide Bracers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32979, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Mooncloth Belt
(@SEASON_2, @LIEUTENANT_TRISTIA, 32980, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Mooncloth Cuffs
(@SEASON_2, @LIEUTENANT_TRISTIA, 32981, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Mooncloth Slippers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32988, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Ornamented Belt
(@SEASON_2, @LIEUTENANT_TRISTIA, 32989, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Ornamented Bracers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32990, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Ornamented Greaves
(@SEASON_2, @LIEUTENANT_TRISTIA, 32997, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Ringmail Bracers
(@SEASON_2, @LIEUTENANT_TRISTIA, 32998, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Ringmail Girdle
(@SEASON_2, @LIEUTENANT_TRISTIA, 32999, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Ringmail Sabatons
(@SEASON_2, @LIEUTENANT_TRISTIA, 33056, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Veteran's Band of Dominance
(@SEASON_2, @LIEUTENANT_TRISTIA, 33057, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Veteran's Band of Triumph
(@SEASON_2, @LIEUTENANT_TRISTIA, 33064, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Veteran's Band of Salvation
(@SEASON_2, @LIEUTENANT_TRISTIA, 33065, 0, 0, @COST_15300_HP_10_ES), -- Veteran's Pendant of Dominance
(@SEASON_2, @LIEUTENANT_TRISTIA, 33066, 0, 0, @COST_15300_HP_10_ES), -- Veteran's Pendant of Triumph
(@SEASON_2, @LIEUTENANT_TRISTIA, 33067, 0, 0, @COST_15300_HP_10_ES), -- Veteran's Pendant of Conquest
(@SEASON_2, @LIEUTENANT_TRISTIA, 33068, 0, 0, @COST_15300_HP_10_ES), -- Veteran's Pendant of Salvation
(@SEASON_2, @CAPTAIN_ONEAL, 28950, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Bonecracker
(@SEASON_2, @CAPTAIN_ONEAL, 28942, 0, 0, @COST_30600_HP_40_AB), -- Grand Marshal's Bonegrinder
(@SEASON_2, @CAPTAIN_ONEAL, 28944, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Cleaver
(@SEASON_2, @CAPTAIN_ONEAL, 28945, 0, 0, @COST_30600_HP_40_AB), -- Grand Marshal's Decapitator
(@SEASON_2, @CAPTAIN_ONEAL, 28946, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Hacker
(@SEASON_2, @CAPTAIN_ONEAL, 28960, 0, 0, @COST_20400_HP_40_AV), -- Grand Marshal's Heavy Crossbow
(@SEASON_2, @CAPTAIN_ONEAL, 28947, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Left Ripper
(@SEASON_2, @CAPTAIN_ONEAL, 28948, 0, 0, @COST_30600_HP_40_AB), -- Grand Marshal's Maul
(@SEASON_2, @CAPTAIN_ONEAL, 28949, 0, 0, @COST_30600_HP_40_AB), -- Grand Marshal's Painsaw
(@SEASON_2, @CAPTAIN_ONEAL, 28951, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Pummeler
(@SEASON_2, @CAPTAIN_ONEAL, 28952, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Quickblade
(@SEASON_2, @CAPTAIN_ONEAL, 28953, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Right Ripper
(@SEASON_2, @CAPTAIN_ONEAL, 28954, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Shanker
(@SEASON_2, @CAPTAIN_ONEAL, 28955, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Shiv
(@SEASON_2, @CAPTAIN_ONEAL, 28956, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Slicer
(@SEASON_2, @CAPTAIN_ONEAL, 28957, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Spellblade
(@SEASON_2, @CAPTAIN_ONEAL, 28959, 0, 0, @COST_30600_HP_40_AB), -- Grand Marshal's War Staff
(@SEASON_2, @CAPTAIN_ONEAL, 28943, 0, 0, @COST_30600_HP_40_AB), -- Grand Marshal's Warblade
(@SEASON_2, @CAPTAIN_ONEAL, 28941, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Battletome
(@SEASON_2, @CAPTAIN_ONEAL, 28940, 0, 0, @COST_15300_HP_20_ES), -- Grand Marshal's Barricade
(@SEASON_2, @LADY_PALANSEER, 28805, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Chain Armor
(@SEASON_2, @LADY_PALANSEER, 28806, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Chain Gauntlets
(@SEASON_2, @LADY_PALANSEER, 28807, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Chain Helm
(@SEASON_2, @LADY_PALANSEER, 28808, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Chain Leggings
(@SEASON_2, @LADY_PALANSEER, 28809, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Chain Spaulders
(@SEASON_2, @LADY_PALANSEER, 28811, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Dragonhide Gloves
(@SEASON_2, @LADY_PALANSEER, 28812, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Dragonhide Helm
(@SEASON_2, @LADY_PALANSEER, 28813, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Dragonhide Legguards
(@SEASON_2, @LADY_PALANSEER, 28814, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Dragonhide Spaulders
(@SEASON_2, @LADY_PALANSEER, 28815, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Dragonhide Tunic
(@SEASON_2, @LADY_PALANSEER, 28817, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Dreadweave Gloves
(@SEASON_2, @LADY_PALANSEER, 28818, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Dreadweave Hood
(@SEASON_2, @LADY_PALANSEER, 28819, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Dreadweave Leggings
(@SEASON_2, @LADY_PALANSEER, 28820, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Dreadweave Mantle
(@SEASON_2, @LADY_PALANSEER, 28821, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Dreadweave Robe
(@SEASON_2, @LADY_PALANSEER, 28831, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Lamellar Chestpiece
(@SEASON_2, @LADY_PALANSEER, 28832, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Lamellar Gauntlets
(@SEASON_2, @LADY_PALANSEER, 28833, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Lamellar Helm
(@SEASON_2, @LADY_PALANSEER, 28834, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Lamellar Legguards
(@SEASON_2, @LADY_PALANSEER, 28835, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Lamellar Shoulders
(@SEASON_2, @LADY_PALANSEER, 28836, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Leather Gloves
(@SEASON_2, @LADY_PALANSEER, 28837, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Leather Helm
(@SEASON_2, @LADY_PALANSEER, 28838, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Leather Legguards
(@SEASON_2, @LADY_PALANSEER, 28839, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Leather Spaulders
(@SEASON_2, @LADY_PALANSEER, 28840, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Leather Tunic
(@SEASON_2, @LADY_PALANSEER, 28841, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Linked Armor
(@SEASON_2, @LADY_PALANSEER, 28842, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Linked Gauntlets
(@SEASON_2, @LADY_PALANSEER, 28843, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Linked Helm
(@SEASON_2, @LADY_PALANSEER, 28844, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Linked Leggings
(@SEASON_2, @LADY_PALANSEER, 28845, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Linked Spaulders
(@SEASON_2, @LADY_PALANSEER, 28846, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Mail Armor
(@SEASON_2, @LADY_PALANSEER, 28847, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Mail Gauntlets
(@SEASON_2, @LADY_PALANSEER, 28848, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Mail Helm
(@SEASON_2, @LADY_PALANSEER, 28849, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Mail Leggings
(@SEASON_2, @LADY_PALANSEER, 28850, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Mail Spaulders
(@SEASON_2, @LADY_PALANSEER, 28851, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Plate Chestpiece
(@SEASON_2, @LADY_PALANSEER, 28852, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Plate Gauntlets
(@SEASON_2, @LADY_PALANSEER, 28853, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Plate Helm
(@SEASON_2, @LADY_PALANSEER, 28854, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Plate Legguards
(@SEASON_2, @LADY_PALANSEER, 28855, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Plate Shoulders
(@SEASON_2, @LADY_PALANSEER, 28856, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Satin Gloves
(@SEASON_2, @LADY_PALANSEER, 28857, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Satin Hood
(@SEASON_2, @LADY_PALANSEER, 28858, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Satin Leggings
(@SEASON_2, @LADY_PALANSEER, 28859, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Satin Mantle
(@SEASON_2, @LADY_PALANSEER, 28860, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Satin Robe
(@SEASON_2, @LADY_PALANSEER, 28861, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Scaled Chestpiece
(@SEASON_2, @LADY_PALANSEER, 28862, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Scaled Gauntlets
(@SEASON_2, @LADY_PALANSEER, 28863, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Scaled Helm
(@SEASON_2, @LADY_PALANSEER, 28864, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Scaled Legguards
(@SEASON_2, @LADY_PALANSEER, 28865, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Scaled Shoulders
(@SEASON_2, @LADY_PALANSEER, 28866, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Silk Amice
(@SEASON_2, @LADY_PALANSEER, 28867, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Silk Cowl
(@SEASON_2, @LADY_PALANSEER, 28868, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Silk Handguards
(@SEASON_2, @LADY_PALANSEER, 28869, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Silk Raiment
(@SEASON_2, @LADY_PALANSEER, 28870, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Silk Trousers
(@SEASON_2, @LADY_PALANSEER, 28871, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Wyrmhide Gloves
(@SEASON_2, @LADY_PALANSEER, 28872, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Wyrmhide Helm
(@SEASON_2, @LADY_PALANSEER, 28873, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Wyrmhide Legguards
(@SEASON_2, @LADY_PALANSEER, 28874, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Wyrmhide Spaulders
(@SEASON_2, @LADY_PALANSEER, 28875, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Wyrmhide Tunic
(@SEASON_2, @LADY_PALANSEER, 31584, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Kodohide Gloves
(@SEASON_2, @LADY_PALANSEER, 31585, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Kodohide Helm
(@SEASON_2, @LADY_PALANSEER, 31586, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Kodohide Legguards
(@SEASON_2, @LADY_PALANSEER, 31587, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Kodohide Spaulders
(@SEASON_2, @LADY_PALANSEER, 31588, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Kodohide Tunic
(@SEASON_2, @LADY_PALANSEER, 31621, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Mooncloth Mitts
(@SEASON_2, @LADY_PALANSEER, 31626, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Mooncloth Cowl
(@SEASON_2, @LADY_PALANSEER, 31627, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Mooncloth Legguards
(@SEASON_2, @LADY_PALANSEER, 31628, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Mooncloth Shoulderpads
(@SEASON_2, @LADY_PALANSEER, 31629, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Mooncloth Vestments
(@SEASON_2, @LADY_PALANSEER, 31635, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Ornamented Chestplate
(@SEASON_2, @LADY_PALANSEER, 31636, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Ornamented Gloves
(@SEASON_2, @LADY_PALANSEER, 31637, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Ornamented Headguard
(@SEASON_2, @LADY_PALANSEER, 31638, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Ornamented Leggings
(@SEASON_2, @LADY_PALANSEER, 31639, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Ornamented Spaulders
(@SEASON_2, @LADY_PALANSEER, 31646, 0, 0, @COST_14500_HP_30_WSG), -- High Warlord's Ringmail Chestguard
(@SEASON_2, @LADY_PALANSEER, 31647, 0, 0, @COST_5500_HP_20_AV), -- High Warlord's Ringmail Gloves
(@SEASON_2, @LADY_PALANSEER, 31648, 0, 0, @COST_8750_HP_30_AV), -- High Warlord's Ringmail Headpiece
(@SEASON_2, @LADY_PALANSEER, 31649, 0, 0, @COST_8750_HP_30_WSG), -- High Warlord's Ringmail Legguards
(@SEASON_2, @LADY_PALANSEER, 31650, 0, 0, @COST_5500_HP_20_AB), -- High Warlord's Ringmail Shoulderpads
(@SEASON_2, @SERGEANT_THUNDERHORN, 28293, 0, 0, @COST_30600_HP_40_AB), -- High Warlord's Claymore
(@SEASON_2, @SERGEANT_THUNDERHORN, 28917, 0, 0, @COST_30600_HP_40_AB), -- High Warlord's Bonegrinder
(@SEASON_2, @SERGEANT_THUNDERHORN, 28918, 0, 0, @COST_30600_HP_40_AB), -- High Warlord's Decapitator
(@SEASON_2, @SERGEANT_THUNDERHORN, 28919, 0, 0, @COST_30600_HP_40_AB), -- High Warlord's Maul
(@SEASON_2, @SERGEANT_THUNDERHORN, 28920, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Cleaver
(@SEASON_2, @SERGEANT_THUNDERHORN, 28921, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Hacker
(@SEASON_2, @SERGEANT_THUNDERHORN, 28922, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Left Ripper
(@SEASON_2, @SERGEANT_THUNDERHORN, 28923, 0, 0, @COST_30600_HP_40_AB), -- High Warlord's Painsaw
(@SEASON_2, @SERGEANT_THUNDERHORN, 28924, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Bonecracker
(@SEASON_2, @SERGEANT_THUNDERHORN, 28925, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Pummeler
(@SEASON_2, @SERGEANT_THUNDERHORN, 28926, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Quickblade
(@SEASON_2, @SERGEANT_THUNDERHORN, 28928, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Right Ripper
(@SEASON_2, @SERGEANT_THUNDERHORN, 28929, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Shanker
(@SEASON_2, @SERGEANT_THUNDERHORN, 28930, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Shiv
(@SEASON_2, @SERGEANT_THUNDERHORN, 28931, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Spellblade
(@SEASON_2, @SERGEANT_THUNDERHORN, 28933, 0, 0, @COST_20400_HP_40_AV), -- High Warlord's Heavy Crossbow
(@SEASON_2, @SERGEANT_THUNDERHORN, 28935, 0, 0, @COST_30600_HP_40_AB), -- High Warlord's War Staff
(@SEASON_2, @SERGEANT_THUNDERHORN, 28937, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Slicer
(@SEASON_2, @SERGEANT_THUNDERHORN, 28938, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Battletome
(@SEASON_2, @SERGEANT_THUNDERHORN, 28939, 0, 0, @COST_15300_HP_20_ES), -- High Warlord's Barricade
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 24544, 0, 0, @COST_1500_AP), -- Gladiator's Plate Chestpiece
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 24545, 0, 0, @COST_1500_AP), -- Gladiator's Plate Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 24546, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Plate Shoulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 24547, 0, 0, @COST_1500_AP), -- Gladiator's Plate Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 24549, 0, 0, @COST_900_AP), -- Gladiator's Plate Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 24550, 0, 0, @COST_3000_AP_1800_R), -- Gladiator's Greatsword
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 24552, 0, 0, @COST_1500_AP), -- Gladiator's Dreadweave Robe
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 24553, 0, 0, @COST_1500_AP), -- Gladiator's Dreadweave Hood
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 24554, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Dreadweave Mantle
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 24555, 0, 0, @COST_1500_AP), -- Gladiator's Dreadweave Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 24556, 0, 0, @COST_900_AP), -- Gladiator's Dreadweave Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 24557, 0, 0, @COST_3000_AP_1800_R), -- Gladiator's War Staff
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25830, 0, 0, @COST_1500_AP), -- Gladiator's Leather Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25831, 0, 0, @COST_1500_AP), -- Gladiator's Leather Tunic
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25832, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Leather Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25833, 0, 0, @COST_1500_AP), -- Gladiator's Leather Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25834, 0, 0, @COST_900_AP), -- Gladiator's Leather Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25854, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Silk Amice
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25855, 0, 0, @COST_1500_AP), -- Gladiator's Silk Cowl
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25856, 0, 0, @COST_1500_AP), -- Gladiator's Silk Raiment
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25857, 0, 0, @COST_900_AP), -- Gladiator's Silk Handguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25858, 0, 0, @COST_1500_AP), -- Gladiator's Silk Trousers
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25997, 0, 0, @COST_1500_AP), -- Gladiator's Linked Armor
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25998, 0, 0, @COST_1500_AP), -- Gladiator's Linked Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 25999, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Linked Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 26000, 0, 0, @COST_900_AP), -- Gladiator's Linked Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 26001, 0, 0, @COST_1500_AP), -- Gladiator's Linked Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27469, 0, 0, @COST_1500_AP), -- Gladiator's Mail Armor
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27470, 0, 0, @COST_900_AP), -- Gladiator's Mail Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27471, 0, 0, @COST_1500_AP), -- Gladiator's Mail Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27472, 0, 0, @COST_1500_AP), -- Gladiator's Mail Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27473, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Mail Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27702, 0, 0, @COST_1500_AP), -- Gladiator's Lamellar Chestpiece
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27703, 0, 0, @COST_900_AP), -- Gladiator's Lamellar Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27704, 0, 0, @COST_1500_AP), -- Gladiator's Lamellar Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27705, 0, 0, @COST_1500_AP), -- Gladiator's Lamellar Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27706, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Lamellar Shoulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27707, 0, 0, @COST_900_AP), -- Gladiator's Satin Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27708, 0, 0, @COST_1500_AP), -- Gladiator's Satin Hood
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27709, 0, 0, @COST_1500_AP), -- Gladiator's Satin Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27710, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Satin Mantle
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27711, 0, 0, @COST_1500_AP), -- Gladiator's Satin Robe
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27879, 0, 0, @COST_1500_AP), -- Gladiator's Scaled Chestpiece
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27880, 0, 0, @COST_900_AP), -- Gladiator's Scaled Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27881, 0, 0, @COST_1500_AP), -- Gladiator's Scaled Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27882, 0, 0, @COST_1500_AP), -- Gladiator's Scaled Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 27883, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Scaled Shoulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28126, 0, 0, @COST_900_AP), -- Gladiator's Dragonhide Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28127, 0, 0, @COST_1500_AP), -- Gladiator's Dragonhide Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28128, 0, 0, @COST_1500_AP), -- Gladiator's Dragonhide Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28129, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Dragonhide Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28130, 0, 0, @COST_1500_AP), -- Gladiator's Dragonhide Tunic
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28136, 0, 0, @COST_900_AP), -- Gladiator's Wyrmhide Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28137, 0, 0, @COST_1500_AP), -- Gladiator's Wyrmhide Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28138, 0, 0, @COST_1500_AP), -- Gladiator's Wyrmhide Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28139, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Wyrmhide Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28140, 0, 0, @COST_1500_AP), -- Gladiator's Wyrmhide Tunic
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28294, 0, 0, @COST_3000_AP_1800_R), -- Gladiator's Heavy Crossbow
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28295, 0, 0, @COST_2100_AP_1800_R), -- Gladiator's Slicer
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28297, 0, 0, @COST_2520_AP_1800_R), -- Gladiator's Spellblade
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28298, 0, 0, @COST_3000_AP_1800_R), -- Gladiator's Decapitator
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28299, 0, 0, @COST_3000_AP_1800_R), -- Gladiator's Bonegrinder
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28300, 0, 0, @COST_3000_AP_1800_R), -- Gladiator's Painsaw
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28302, 0, 0, @COST_900_AP_1800_R), -- Gladiator's Bonecracker
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28305, 0, 0, @COST_2100_AP_1800_R), -- Gladiator's Pummeler
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28307, 0, 0, @COST_900_AP_1800_R), -- Gladiator's Quickblade
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28308, 0, 0, @COST_2100_AP_1800_R), -- Gladiator's Cleaver
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28309, 0, 0, @COST_900_AP_1800_R), -- Gladiator's Hacker
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28310, 0, 0, @COST_900_AP_1800_R), -- Gladiator's Shiv
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28312, 0, 0, @COST_2100_AP_1800_R), -- Gladiator's Shanker
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28313, 0, 0, @COST_2100_AP_1800_R), -- Gladiator's Right Ripper
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28314, 0, 0, @COST_900_AP_1800_R), -- Gladiator's Left Ripper
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28319, 0, 0, @COST_800_AP), -- Gladiator's War Edge
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28320, 0, 0, @COST_800_AP), -- Gladiator's Touch of Defeat
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28331, 0, 0, @COST_1500_AP), -- Gladiator's Chain Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28332, 0, 0, @COST_1500_AP), -- Gladiator's Chain Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28333, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Chain Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28334, 0, 0, @COST_1500_AP), -- Gladiator's Chain Armor
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28335, 0, 0, @COST_900_AP), -- Gladiator's Chain Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28346, 0, 0, @COST_900_AP_1800_R), -- Gladiator's Endgame
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28355, 0, 0, @COST_800_AP), -- Gladiator's Idol of Tenacity
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28356, 0, 0, @COST_800_AP), -- Gladiator's Libram of Justice
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28357, 0, 0, @COST_800_AP), -- Gladiator's Totem of the Third Wind
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28358, 0, 0, @COST_1500_AP_1800_R), -- Gladiator's Shield Wall
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 28476, 0, 0, @COST_3000_AP_1800_R), -- Gladiator's Maul
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 30186, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Felweave Amice
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 30187, 0, 0, @COST_1500_AP), -- Gladiator's Felweave Cowl
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 30188, 0, 0, @COST_900_AP), -- Gladiator's Felweave Handguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 30200, 0, 0, @COST_1500_AP), -- Gladiator's Felweave Raiment
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 30201, 0, 0, @COST_1500_AP), -- Gladiator's Felweave Trousers
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 30486, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Plate Chestpiece
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 30487, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Plate Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 30488, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Plate Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 30489, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Plate Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 30490, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Plate Shoulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31375, 0, 0, @COST_900_AP), -- Gladiator's Kodohide Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31376, 0, 0, @COST_1500_AP), -- Gladiator's Kodohide Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31377, 0, 0, @COST_1500_AP), -- Gladiator's Kodohide Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31378, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Kodohide Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31379, 0, 0, @COST_1500_AP), -- Gladiator's Kodohide Tunic
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31396, 0, 0, @COST_1500_AP), -- Gladiator's Ringmail Armor
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31397, 0, 0, @COST_900_AP), -- Gladiator's Ringmail Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31400, 0, 0, @COST_1500_AP), -- Gladiator's Ringmail Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31406, 0, 0, @COST_1500_AP), -- Gladiator's Ringmail Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31407, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Ringmail Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31409, 0, 0, @COST_900_AP), -- Gladiator's Mooncloth Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31410, 0, 0, @COST_1500_AP), -- Gladiator's Mooncloth Hood
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31411, 0, 0, @COST_1500_AP), -- Gladiator's Mooncloth Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31412, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Mooncloth Mantle
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31413, 0, 0, @COST_1500_AP), -- Gladiator's Mooncloth Robe
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31613, 0, 0, @COST_1500_AP), -- Gladiator's Ornamented Chestguard
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31614, 0, 0, @COST_900_AP), -- Gladiator's Ornamented Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31616, 0, 0, @COST_1500_AP), -- Gladiator's Ornamented Headcover
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31618, 0, 0, @COST_1500_AP), -- Gladiator's Ornamented Legplates
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31619, 0, 0, @COST_1200_AP_1950_R), -- Gladiator's Ornamented Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31958, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Bonecracker
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31959, 0, 0, @COST_3750_AP_2050_R), -- Merciless Gladiator's Bonegrinder
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31960, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Chain Armor
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31961, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Chain Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31962, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Chain Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31963, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Chain Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31964, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Chain Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31965, 0, 0, @COST_2625_AP_2050_R), -- Merciless Gladiator's Cleaver
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31966, 0, 0, @COST_3750_AP_2050_R), -- Merciless Gladiator's Decapitator
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31967, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Dragonhide Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31968, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Dragonhide Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31969, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Dragonhide Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31971, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Dragonhide Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31972, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Dragonhide Tunic
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31973, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Dreadweave Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31974, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Dreadweave Hood
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31975, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Dreadweave Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31976, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Dreadweave Mantle
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31977, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Dreadweave Robe
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31978, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Endgame
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31979, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Felweave Amice
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31980, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Felweave Cowl
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31981, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Felweave Handguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31982, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Felweave Raiment
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31983, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Felweave Trousers
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31984, 0, 0, @COST_3750_AP_2050_R), -- Merciless Gladiator's Greatsword
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31985, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Hacker
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31986, 0, 0, @COST_3750_AP_2050_R), -- Merciless Gladiator's Crossbow of the Phoenix
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31987, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Kodohide Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31988, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Kodohide Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31989, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Kodohide Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31990, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Kodohide Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31991, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Kodohide Tunic
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31992, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Lamellar Chestpiece
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31993, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Lamellar Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31995, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Lamellar Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31996, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Lamellar Shoulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31997, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Lamellar Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31998, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Leather Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 31999, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Leather Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32000, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Leather Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32001, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Leather Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32002, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Leather Tunic
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32003, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Left Ripper
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32004, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Linked Armor
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32005, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Linked Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32006, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Linked Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32007, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Linked Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32008, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Linked Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32009, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Mail Armor
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32010, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Mail Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32011, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Mail Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32012, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Mail Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32013, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Mail Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32014, 0, 0, @COST_3750_AP_2050_R), -- Merciless Gladiator's Maul
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32015, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Mooncloth Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32016, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Mooncloth Hood
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32017, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Mooncloth Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32018, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Mooncloth Mantle
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32019, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Mooncloth Robe
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32020, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Ornamented Chestguard
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32021, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Ornamented Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32022, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Ornamented Headcover
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32023, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Ornamented Legplates
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32024, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Ornamented Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32025, 0, 0, @COST_3750_AP_2050_R), -- Merciless Gladiator's Painsaw
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32026, 0, 0, @COST_2625_AP_2050_R), -- Merciless Gladiator's Pummeler
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32027, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Quickblade
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32028, 0, 0, @COST_2625_AP_2050_R), -- Merciless Gladiator's Right Ripper
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32029, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Ringmail Armor
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32030, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Ringmail Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32031, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Ringmail Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32032, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Ringmail Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32033, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Ringmail Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32034, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Satin Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32035, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Satin Hood
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32036, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Satin Leggings
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32037, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Satin Mantle
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32038, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Satin Robe
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32039, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Scaled Chestpiece
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32040, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Scaled Gauntlets
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32041, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Scaled Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32042, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Scaled Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32043, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Scaled Shoulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32044, 0, 0, @COST_2625_AP_2050_R), -- Merciless Gladiator's Shanker
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32045, 0, 0, @COST_1875_AP_2050_R), -- Merciless Gladiator's Shield Wall
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32046, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Shiv
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32047, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Silk Amice
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32048, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Silk Cowl
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32049, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Silk Handguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32050, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Silk Raiment
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32051, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Silk Trousers
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32052, 0, 0, @COST_2625_AP_2050_R), -- Merciless Gladiator's Slicer
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32053, 0, 0, @COST_3150_AP_2050_R), -- Merciless Gladiator's Spellblade
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32054, 0, 0, @COST_1000_AP_1750_R), -- Merciless Gladiator's War Edge
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32055, 0, 0, @COST_3750_AP_2050_R), -- Merciless Gladiator's War Staff
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32056, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Wyrmhide Gloves
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32057, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Wyrmhide Helm
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32058, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Wyrmhide Legguards
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32059, 0, 0, @COST_1500_AP_2200_R), -- Merciless Gladiator's Wyrmhide Spaulders
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32060, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Merciless Gladiator's Wyrmhide Tunic
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32450, 0, 0, @COST_2520_AP_1800_R), -- Gladiator's Gavel
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32451, 0, 0, @COST_2520_AP_1800_R), -- Gladiator's Salvation
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32452, 0, 0, @COST_900_AP_1800_R), -- Gladiator's Reprieve
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32961, 0, 0, @COST_1125_AP), -- Merciless Gladiator's Reprieve
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32962, 0, 0, @COST_1000_AP_1750_R), -- Merciless Gladiator's Touch of Defeat
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32963, 0, 0, @COST_3150_AP_2050_R), -- Merciless Gladiator's Gavel
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 32964, 0, 0, @COST_3150_AP_2050_R), -- Merciless Gladiator's Salvation
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33076, 0, 0, @COST_1000_AP_1750_R), -- Merciless Gladiator's Idol of Tenacity
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33077, 0, 0, @COST_1000_AP_1750_R), -- Merciless Gladiator's Libram of Justice
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33078, 0, 0, @COST_1000_AP_1750_R), -- Merciless Gladiator's Totem of the Third Wind
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33309, 0, 0, @COST_1875_AP_2050_R), -- Merciless Gladiator's Redoubt
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33313, 0, 0, @COST_1875_AP_2050_R), -- Merciless Gladiator's Barrier
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33936, 0, 0, @COST_800_AP), -- Gladiator's Libram of Fortitude
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33937, 0, 0, @COST_1000_AP_1750_R), -- Merciless Gladiator's Libram of Fortitude
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33939, 0, 0, @COST_800_AP), -- Gladiator's Totem of Indomitability
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33940, 0, 0, @COST_1000_AP_1750_R), -- Merciless Gladiator's Totem of Indomitability
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33942, 0, 0, @COST_800_AP), -- Gladiator's Idol of Steadfastness
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33943, 0, 0, @COST_1000_AP_1750_R), -- Merciless Gladiator's Idol of Steadfastness
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33945, 0, 0, @COST_800_AP), -- Gladiator's Idol of Resolve
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33946, 0, 0, @COST_1000_AP_1750_R), -- Merciless Gladiator's Idol of Resolve
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33948, 0, 0, @COST_800_AP), -- Gladiator's Libram of Vengeance
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33949, 0, 0, @COST_1000_AP_1750_R), -- Merciless Gladiator's Libram of Vengeance
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33951, 0, 0, @COST_800_AP), -- Gladiator's Totem of Survival
(@SEASON_2, @KRIXEL_PINCHWHISTLE, 33952, 0, 0, @COST_1000_AP_1750_R), -- Merciless Gladiator's Totem of Survival
(@SEASON_2, @SERGEANT_KIEN, 32785, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Chain Sabatons
(@SEASON_2, @SERGEANT_KIEN, 32786, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Dragonhide Boots
(@SEASON_2, @SERGEANT_KIEN, 32787, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Dreadweave Stalkers
(@SEASON_2, @SERGEANT_KIEN, 32788, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Kodohide Boots
(@SEASON_2, @SERGEANT_KIEN, 32789, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Lamellar Greaves
(@SEASON_2, @SERGEANT_KIEN, 32790, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Leather Boots
(@SEASON_2, @SERGEANT_KIEN, 32791, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Linked Sabatons
(@SEASON_2, @SERGEANT_KIEN, 32792, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Mail Sabatons
(@SEASON_2, @SERGEANT_KIEN, 32793, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Plate Greaves
(@SEASON_2, @SERGEANT_KIEN, 32794, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Scaled Greaves
(@SEASON_2, @SERGEANT_KIEN, 32795, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Silk Footguards
(@SEASON_2, @SERGEANT_KIEN, 32796, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Wyrmhide Boots
(@SEASON_2, @SERGEANT_KIEN, 32797, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Chain Girdle
(@SEASON_2, @SERGEANT_KIEN, 32798, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Dragonhide Belt
(@SEASON_2, @SERGEANT_KIEN, 32799, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Dreadweave Belt
(@SEASON_2, @SERGEANT_KIEN, 32800, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Kodohide Belt
(@SEASON_2, @SERGEANT_KIEN, 32801, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Lamellar Belt
(@SEASON_2, @SERGEANT_KIEN, 32802, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Leather Belt
(@SEASON_2, @SERGEANT_KIEN, 32803, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Linked Girdle
(@SEASON_2, @SERGEANT_KIEN, 32804, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Mail Girdle
(@SEASON_2, @SERGEANT_KIEN, 32805, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Plate Belt
(@SEASON_2, @SERGEANT_KIEN, 32806, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Scaled Belt
(@SEASON_2, @SERGEANT_KIEN, 32807, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Silk Belt
(@SEASON_2, @SERGEANT_KIEN, 32808, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Wyrmhide Belt
(@SEASON_2, @SERGEANT_KIEN, 32809, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Chain Bracers
(@SEASON_2, @SERGEANT_KIEN, 32810, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Dragonhide Bracers
(@SEASON_2, @SERGEANT_KIEN, 32811, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Dreadweave Cuffs
(@SEASON_2, @SERGEANT_KIEN, 32812, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Kodohide Bracers
(@SEASON_2, @SERGEANT_KIEN, 32813, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Lamellar Bracers
(@SEASON_2, @SERGEANT_KIEN, 32814, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Leather Bracers
(@SEASON_2, @SERGEANT_KIEN, 32816, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Linked Bracers
(@SEASON_2, @SERGEANT_KIEN, 32817, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Mail Bracers
(@SEASON_2, @SERGEANT_KIEN, 32818, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Plate Bracers
(@SEASON_2, @SERGEANT_KIEN, 32819, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Scaled Bracers
(@SEASON_2, @SERGEANT_KIEN, 32820, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Silk Cuffs
(@SEASON_2, @SERGEANT_KIEN, 32821, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Wyrmhide Bracers
(@SEASON_2, @SERGEANT_KIEN, 32979, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Mooncloth Belt
(@SEASON_2, @SERGEANT_KIEN, 32980, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Mooncloth Cuffs
(@SEASON_2, @SERGEANT_KIEN, 32981, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Mooncloth Slippers
(@SEASON_2, @SERGEANT_KIEN, 32988, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Ornamented Belt
(@SEASON_2, @SERGEANT_KIEN, 32989, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Ornamented Bracers
(@SEASON_2, @SERGEANT_KIEN, 32990, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Ornamented Greaves
(@SEASON_2, @SERGEANT_KIEN, 32997, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Veteran's Ringmail Bracers
(@SEASON_2, @SERGEANT_KIEN, 32998, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Veteran's Ringmail Girdle
(@SEASON_2, @SERGEANT_KIEN, 32999, 0, 0, @COST_17850_HP_40_AB), -- Veteran's Ringmail Sabatons
(@SEASON_2, @SERGEANT_KIEN, 33056, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Veteran's Band of Dominance
(@SEASON_2, @SERGEANT_KIEN, 33057, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Veteran's Band of Triumph
(@SEASON_2, @SERGEANT_KIEN, 33064, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Veteran's Band of Salvation
(@SEASON_2, @SERGEANT_KIEN, 33065, 0, 0, @COST_15300_HP_10_ES), -- Veteran's Pendant of Dominance
(@SEASON_2, @SERGEANT_KIEN, 33066, 0, 0, @COST_15300_HP_10_ES), -- Veteran's Pendant of Triumph
(@SEASON_2, @SERGEANT_KIEN, 33067, 0, 0, @COST_15300_HP_10_ES), -- Veteran's Pendant of Conquest
(@SEASON_2, @SERGEANT_KIEN, 33068, 0, 0, @COST_15300_HP_10_ES); -- Veteran's Pendant of Salvation

# Season 3
DELETE FROM game_event_npc_vendor WHERE event = @SEASON_3;
INSERT INTO game_event_npc_vendor (event, guid, item, maxcount, incrtime, ExtendedCost) VALUES
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 24544, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Plate Chestpiece
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 24545, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Plate Helm
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 24546, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Plate Shoulders
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 24547, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Plate Legguards
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 24549, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Plate Gauntlets
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 24552, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Dreadweave Robe
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 24553, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Dreadweave Hood
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 24554, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Dreadweave Mantle
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 24555, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Dreadweave Leggings
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 24556, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Dreadweave Gloves
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25830, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Leather Helm
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25831, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Leather Tunic
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25832, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Leather Spaulders
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25833, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Leather Legguards
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25834, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Leather Gloves
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25854, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Silk Amice
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25855, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Silk Cowl
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25856, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Silk Raiment
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25857, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Silk Handguards
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25858, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Silk Trousers
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25997, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Linked Armor
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25998, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Linked Helm
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 25999, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Linked Spaulders
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 26000, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Linked Gauntlets
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 26001, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Linked Leggings
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27469, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Mail Armor
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27470, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Mail Gauntlets
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27471, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Mail Helm
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27472, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Mail Leggings
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27473, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Mail Spaulders
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27702, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Lamellar Chestpiece
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27703, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Lamellar Gauntlets
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27704, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Lamellar Helm
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27705, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Lamellar Legguards
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27706, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Lamellar Shoulders
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27707, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Satin Gloves
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27708, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Satin Hood
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27709, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Satin Leggings
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27710, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Satin Mantle
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27711, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Satin Robe
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27879, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Scaled Chestpiece
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27880, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Scaled Gauntlets
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27881, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Scaled Helm
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27882, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Scaled Legguards
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 27883, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Scaled Shoulders
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28126, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Dragonhide Gloves
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28127, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Dragonhide Helm
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28128, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Dragonhide Legguards
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28129, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Dragonhide Spaulders
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28130, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Dragonhide Tunic
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28136, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Wyrmhide Gloves
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28137, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Wyrmhide Helm
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28138, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Wyrmhide Legguards
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28139, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Wyrmhide Spaulders
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28140, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Wyrmhide Tunic
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28331, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Chain Helm
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28332, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Chain Leggings
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28333, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Chain Spaulders
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28334, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Chain Armor
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 28335, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Chain Gauntlets
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 30186, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Felweave Amice
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 30187, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Felweave Cowl
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 30188, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Felweave Handguards
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 30200, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Felweave Raiment
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 30201, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Felweave Trousers
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31375, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Kodohide Gloves
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31376, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Kodohide Helm
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31377, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Kodohide Legguards
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31378, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Kodohide Spaulders
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31379, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Kodohide Tunic
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31396, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Ringmail Armor
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31397, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Ringmail Gauntlets
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31400, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Ringmail Helm
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31406, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Ringmail Leggings
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31407, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Ringmail Spaulders
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31409, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Mooncloth Gloves
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31410, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Mooncloth Hood
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31411, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Mooncloth Leggings
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31412, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Mooncloth Mantle
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31413, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Mooncloth Robe
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31613, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Ornamented Chestguard
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31614, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Ornamented Gloves
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31616, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Ornamented Headcover
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31618, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Ornamented Legplates
(@SEASON_3, @CAPTAIN_DIRGEHAMMER, 31619, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Ornamented Spaulders
(@SEASON_3, @LIEUTENANT_TRISTIA, 33056, 0, 0, @COST_11934_HP_10_AV), -- Veteran's Band of Dominance
(@SEASON_3, @LIEUTENANT_TRISTIA, 33057, 0, 0, @COST_11934_HP_10_AV), -- Veteran's Band of Triumph
(@SEASON_3, @LIEUTENANT_TRISTIA, 33064, 0, 0, @COST_11934_HP_10_AV), -- Veteran's Band of Salvation
(@SEASON_3, @LIEUTENANT_TRISTIA, 33811, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Plate Belt
(@SEASON_3, @LIEUTENANT_TRISTIA, 33812, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Plate Greaves
(@SEASON_3, @LIEUTENANT_TRISTIA, 33813, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Plate Bracers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33853, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Vindicator's Band of Dominance
(@SEASON_3, @LIEUTENANT_TRISTIA, 33876, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Chain Bracers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33877, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Chain Girdle
(@SEASON_3, @LIEUTENANT_TRISTIA, 33878, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Chain Sabatons
(@SEASON_3, @LIEUTENANT_TRISTIA, 33879, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Dragonhide Belt
(@SEASON_3, @LIEUTENANT_TRISTIA, 33880, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Dragonhide Boots
(@SEASON_3, @LIEUTENANT_TRISTIA, 33881, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Dragonhide Bracers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33882, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Dreadweave Belt
(@SEASON_3, @LIEUTENANT_TRISTIA, 33883, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Dreadweave Cuffs
(@SEASON_3, @LIEUTENANT_TRISTIA, 33884, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Dreadweave Stalkers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33885, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Kodohide Belt
(@SEASON_3, @LIEUTENANT_TRISTIA, 33886, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Kodohide Boots
(@SEASON_3, @LIEUTENANT_TRISTIA, 33887, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Kodohide Bracers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33888, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Lamellar Belt
(@SEASON_3, @LIEUTENANT_TRISTIA, 33889, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Lamellar Bracers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33890, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Lamellar Greaves
(@SEASON_3, @LIEUTENANT_TRISTIA, 33891, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Leather Belt
(@SEASON_3, @LIEUTENANT_TRISTIA, 33892, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Leather Boots
(@SEASON_3, @LIEUTENANT_TRISTIA, 33893, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Leather Bracers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33894, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Linked Bracers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33895, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Linked Girdle
(@SEASON_3, @LIEUTENANT_TRISTIA, 33896, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Linked Sabatons
(@SEASON_3, @LIEUTENANT_TRISTIA, 33897, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Mail Bracers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33898, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Mail Girdle
(@SEASON_3, @LIEUTENANT_TRISTIA, 33899, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Mail Sabatons
(@SEASON_3, @LIEUTENANT_TRISTIA, 33900, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Mooncloth Belt
(@SEASON_3, @LIEUTENANT_TRISTIA, 33901, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Mooncloth Cuffs
(@SEASON_3, @LIEUTENANT_TRISTIA, 33902, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Mooncloth Slippers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33903, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Ornamented Belt
(@SEASON_3, @LIEUTENANT_TRISTIA, 33904, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Ornamented Bracers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33905, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Ornamented Greaves
(@SEASON_3, @LIEUTENANT_TRISTIA, 33906, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Ringmail Bracers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33907, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Ringmail Girdle
(@SEASON_3, @LIEUTENANT_TRISTIA, 33908, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Ringmail Sabatons
(@SEASON_3, @LIEUTENANT_TRISTIA, 33909, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Scaled Belt
(@SEASON_3, @LIEUTENANT_TRISTIA, 33910, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Scaled Bracers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33911, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Scaled Greaves
(@SEASON_3, @LIEUTENANT_TRISTIA, 33912, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Silk Belt
(@SEASON_3, @LIEUTENANT_TRISTIA, 33913, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Silk Cuffs
(@SEASON_3, @LIEUTENANT_TRISTIA, 33914, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Silk Footguards
(@SEASON_3, @LIEUTENANT_TRISTIA, 33915, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Wyrmhide Belt
(@SEASON_3, @LIEUTENANT_TRISTIA, 33916, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Wyrmhide Boots
(@SEASON_3, @LIEUTENANT_TRISTIA, 33917, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Wyrmhide Bracers
(@SEASON_3, @LIEUTENANT_TRISTIA, 33918, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Vindicator's Band of Salvation
(@SEASON_3, @LIEUTENANT_TRISTIA, 33919, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Vindicator's Band of Triumph
(@SEASON_3, @LIEUTENANT_TRISTIA, 33920, 0, 0, @COST_15300_HP_10_ES), -- Vindicator's Pendant of Conquest
(@SEASON_3, @LIEUTENANT_TRISTIA, 33921, 0, 0, @COST_15300_HP_10_ES), -- Vindicator's Pendant of Dominance
(@SEASON_3, @LIEUTENANT_TRISTIA, 33922, 0, 0, @COST_15300_HP_10_ES), -- Vindicator's Pendant of Salvation
(@SEASON_3, @LIEUTENANT_TRISTIA, 33923, 0, 0, @COST_15300_HP_10_ES), -- Vindicator's Pendant of Triumph
(@SEASON_3, @LIEUTENANT_TRISTIA, 35317, 0, 0, @COST_15300_HP_10_ES), -- Vindicator's Pendant of Reprieve
(@SEASON_3, @LIEUTENANT_TRISTIA, 35319, 0, 0, @COST_15300_HP_10_ES), -- Vindicator's Pendant of Subjugation
(@SEASON_3, @LIEUTENANT_TRISTIA, 35320, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Vindicator's Band of Subjugation
(@SEASON_3, @LIEUTENANT_TRISTIA, 34576, 0, 0, @COST_30000_HP_40_AV), -- Battlemaster's Cruelty
(@SEASON_3, @LIEUTENANT_TRISTIA, 34577, 0, 0, @COST_30000_HP_40_AV), -- Battlemaster's Depravity
(@SEASON_3, @LIEUTENANT_TRISTIA, 34578, 0, 0, @COST_30000_HP_40_AV), -- Battlemaster's Determination
(@SEASON_3, @LIEUTENANT_TRISTIA, 34579, 0, 0, @COST_30000_HP_40_AV), -- Battlemaster's Audacity
(@SEASON_3, @LIEUTENANT_TRISTIA, 34580, 0, 0, @COST_30000_HP_40_AV), -- Battlemaster's Perseverance
(@SEASON_3, @CAPTAIN_ONEAL, 24550, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's Greatsword
(@SEASON_3, @CAPTAIN_ONEAL, 24557, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's War Staff
(@SEASON_3, @CAPTAIN_ONEAL, 28294, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's Heavy Crossbow
(@SEASON_3, @CAPTAIN_ONEAL, 28295, 0, 0, @COST_18000_HP_20_ES), -- Gladiator's Slicer
(@SEASON_3, @CAPTAIN_ONEAL, 28297, 0, 0, @COST_25200_HP_20_ES), -- Gladiator's Spellblade
(@SEASON_3, @CAPTAIN_ONEAL, 28298, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's Decapitator
(@SEASON_3, @CAPTAIN_ONEAL, 28299, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's Bonegrinder
(@SEASON_3, @CAPTAIN_ONEAL, 28300, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's Painsaw
(@SEASON_3, @CAPTAIN_ONEAL, 28302, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Bonecracker
(@SEASON_3, @CAPTAIN_ONEAL, 28305, 0, 0, @COST_18000_HP_20_ES), -- Gladiator's Pummeler
(@SEASON_3, @CAPTAIN_ONEAL, 28307, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Quickblade
(@SEASON_3, @CAPTAIN_ONEAL, 28308, 0, 0, @COST_18000_HP_20_ES), -- Gladiator's Cleaver
(@SEASON_3, @CAPTAIN_ONEAL, 28309, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Hacker
(@SEASON_3, @CAPTAIN_ONEAL, 28310, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Shiv
(@SEASON_3, @CAPTAIN_ONEAL, 28312, 0, 0, @COST_18000_HP_20_ES), -- Gladiator's Shanker
(@SEASON_3, @CAPTAIN_ONEAL, 28313, 0, 0, @COST_18000_HP_20_ES), -- Gladiator's Right Ripper
(@SEASON_3, @CAPTAIN_ONEAL, 28314, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Left Ripper
(@SEASON_3, @CAPTAIN_ONEAL, 28319, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's War Edge
(@SEASON_3, @CAPTAIN_ONEAL, 28320, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Touch of Defeat
(@SEASON_3, @CAPTAIN_ONEAL, 28346, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Endgame
(@SEASON_3, @CAPTAIN_ONEAL, 28355, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Idol of Tenacity
(@SEASON_3, @CAPTAIN_ONEAL, 28356, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Libram of Justice
(@SEASON_3, @CAPTAIN_ONEAL, 28357, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Totem of the Third Wind
(@SEASON_3, @CAPTAIN_ONEAL, 28358, 0, 0, @COST_15000_HP_20_ES), -- Gladiator's Shield Wall
(@SEASON_3, @CAPTAIN_ONEAL, 28476, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's Maul
(@SEASON_3, @CAPTAIN_ONEAL, 32450, 0, 0, @COST_25200_HP_20_ES), -- Gladiator's Gavel
(@SEASON_3, @CAPTAIN_ONEAL, 32451, 0, 0, @COST_25200_HP_20_ES), -- Gladiator's Salvation
(@SEASON_3, @CAPTAIN_ONEAL, 32452, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Reprieve
(@SEASON_3, @CAPTAIN_ONEAL, 33936, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Libram of Fortitude
(@SEASON_3, @CAPTAIN_ONEAL, 33939, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Totem of Indomitability
(@SEASON_3, @CAPTAIN_ONEAL, 33942, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Idol of Steadfastness
(@SEASON_3, @CAPTAIN_ONEAL, 33945, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Idol of Resolve
(@SEASON_3, @CAPTAIN_ONEAL, 33948, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Libram of Vengeance
(@SEASON_3, @CAPTAIN_ONEAL, 33951, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Totem of Survival
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33006, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Heavy Crossbow
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33661, 0, 0, @COST_1875_AP_2050_R), -- Vengeful Gladiator's Barrier
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33662, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Bonecracker
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33663, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Bonegrinder
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33664, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Chain Armor
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33665, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Chain Gauntlets
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33666, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Chain Helm
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33667, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Chain Leggings
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33668, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Chain Spaulders
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33669, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Cleaver
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33670, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Decapitator
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33671, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Dragonhide Gloves
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33672, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Dragonhide Helm
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33673, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Dragonhide Legguards
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33674, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Dragonhide Spaulders
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33675, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Dragonhide Tunic
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33676, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Dreadweave Gloves
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33677, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Dreadweave Hood
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33678, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Dreadweave Leggings
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33679, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Dreadweave Mantle
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33680, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Dreadweave Robe
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33681, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Endgame
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33682, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Felweave Amice
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33683, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Felweave Cowl
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33684, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Felweave Handguards
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33685, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Felweave Raiment
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33686, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Felweave Trousers
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33687, 0, 0, @COST_3150_AP_2050_R), -- Vengeful Gladiator's Gavel
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33688, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Greatsword
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33689, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Hacker
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33690, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Kodohide Gloves
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33691, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Kodohide Helm
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33692, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Kodohide Legguards
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33693, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Kodohide Spaulders
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33694, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Kodohide Tunic
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33695, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Lamellar Chestpiece
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33696, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Lamellar Gauntlets
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33697, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Lamellar Helm
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33698, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Lamellar Legguards
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33699, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Lamellar Shoulders
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33700, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Leather Gloves
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33701, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Leather Helm
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33702, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Leather Legguards
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33703, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Leather Spaulders
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33704, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Leather Tunic
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33705, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Left Ripper
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33706, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Linked Armor
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33707, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Linked Gauntlets
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33708, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Linked Helm
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33709, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Linked Leggings
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33710, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Linked Spaulders
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33711, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Mail Armor
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33712, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Mail Gauntlets
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33713, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Mail Helm
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33714, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Mail Leggings
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33715, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Mail Spaulders
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33716, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Staff
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33717, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Mooncloth Gloves
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33718, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Mooncloth Hood
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33719, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Mooncloth Leggings
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33720, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Mooncloth Mantle
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33721, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Mooncloth Robe
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33722, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Ornamented Chestguard
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33723, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Ornamented Gloves
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33724, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Ornamented Headcover
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33725, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Ornamented Legplates
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33726, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Ornamented Spaulders
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33727, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Painsaw
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33728, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Plate Chestpiece
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33729, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Plate Gauntlets
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33730, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Plate Helm
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33731, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Plate Legguards
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33732, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Plate Shoulders
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33733, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Pummeler
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33734, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Quickblade
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33735, 0, 0, @COST_1875_AP_2050_R), -- Vengeful Gladiator's Redoubt
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33736, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Reprieve
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33737, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Right Ripper
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33738, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Ringmail Armor
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33739, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Ringmail Gauntlets
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33740, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Ringmail Helm
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33741, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Ringmail Leggings
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33742, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Ringmail Spaulders
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33743, 0, 0, @COST_3150_AP_2050_R), -- Vengeful Gladiator's Salvation
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33744, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Satin Gloves
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33745, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Satin Hood
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33746, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Satin Leggings
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33747, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Satin Mantle
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33748, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Satin Robe
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33749, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Scaled Chestpiece
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33750, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Scaled Gauntlets
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33751, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Scaled Helm
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33752, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Scaled Legguards
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33753, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Scaled Shoulders
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33754, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Shanker
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33755, 0, 0, @COST_1875_AP_2050_R), -- Vengeful Gladiator's Shield Wall
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33756, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Shiv
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33757, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Silk Amice
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33758, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Silk Cowl
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33759, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Silk Handguards
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33760, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Silk Raiment
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33761, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Silk Trousers
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33762, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Slicer
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33763, 0, 0, @COST_3150_AP_2050_R), -- Vengeful Gladiator's Spellblade
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33764, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Touch of Defeat
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33765, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's War Edge
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33766, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's War Staff
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33767, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Wyrmhide Gloves
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33768, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Wyrmhide Helm
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33769, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Wyrmhide Legguards
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33770, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Wyrmhide Spaulders
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33771, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Wyrmhide Tunic
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33801, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Mutilator
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33841, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Idol of Tenacity
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33842, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Libram of Justice
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33843, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Totem of the Third Wind
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33938, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Libram of Fortitude
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33941, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Totem of Indomitability
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33944, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Idol of Steadfastness
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33947, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Idol of Resolve
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33950, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Libram of Vengeance
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 33953, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Totem of Survival
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 34014, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Waraxe
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 34015, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Chopper
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 34016, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Left Render
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 34033, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Grimoire
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 34059, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Baton of Light
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 34066, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Piercing Touch
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 34529, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Longbow
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 34530, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Rifle
(@SEASON_3, @LEENIE_SMILEY_SMALLS, 34540, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Battle Staff
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33006, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Heavy Crossbow
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33661, 0, 0, @COST_1875_AP_2050_R), -- Vengeful Gladiator's Barrier
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33662, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Bonecracker
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33663, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Bonegrinder
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33664, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Chain Armor
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33665, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Chain Gauntlets
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33666, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Chain Helm
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33667, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Chain Leggings
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33668, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Chain Spaulders
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33669, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Cleaver
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33670, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Decapitator
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33671, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Dragonhide Gloves
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33672, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Dragonhide Helm
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33673, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Dragonhide Legguards
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33674, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Dragonhide Spaulders
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33675, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Dragonhide Tunic
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33676, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Dreadweave Gloves
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33677, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Dreadweave Hood
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33678, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Dreadweave Leggings
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33679, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Dreadweave Mantle
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33680, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Dreadweave Robe
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33681, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Endgame
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33682, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Felweave Amice
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33683, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Felweave Cowl
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33684, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Felweave Handguards
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33685, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Felweave Raiment
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33686, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Felweave Trousers
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33687, 0, 0, @COST_3150_AP_2050_R), -- Vengeful Gladiator's Gavel
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33688, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Greatsword
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33689, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Hacker
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33690, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Kodohide Gloves
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33691, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Kodohide Helm
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33692, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Kodohide Legguards
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33693, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Kodohide Spaulders
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33694, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Kodohide Tunic
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33695, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Lamellar Chestpiece
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33696, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Lamellar Gauntlets
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33697, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Lamellar Helm
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33698, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Lamellar Legguards
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33699, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Lamellar Shoulders
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33700, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Leather Gloves
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33701, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Leather Helm
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33702, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Leather Legguards
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33703, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Leather Spaulders
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33704, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Leather Tunic
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33705, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Left Ripper
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33706, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Linked Armor
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33707, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Linked Gauntlets
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33708, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Linked Helm
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33709, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Linked Leggings
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33710, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Linked Spaulders
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33711, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Mail Armor
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33712, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Mail Gauntlets
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33713, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Mail Helm
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33714, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Mail Leggings
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33715, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Mail Spaulders
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33716, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Staff
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33717, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Mooncloth Gloves
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33718, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Mooncloth Hood
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33719, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Mooncloth Leggings
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33720, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Mooncloth Mantle
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33721, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Mooncloth Robe
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33722, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Ornamented Chestguard
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33723, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Ornamented Gloves
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33724, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Ornamented Headcover
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33725, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Ornamented Legplates
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33726, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Ornamented Spaulders
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33727, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Painsaw
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33728, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Plate Chestpiece
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33729, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Plate Gauntlets
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33730, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Plate Helm
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33731, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Plate Legguards
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33732, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Plate Shoulders
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33733, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Pummeler
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33734, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Quickblade
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33735, 0, 0, @COST_1875_AP_2050_R), -- Vengeful Gladiator's Redoubt
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33736, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Reprieve
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33737, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Right Ripper
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33738, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Ringmail Armor
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33739, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Ringmail Gauntlets
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33740, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Ringmail Helm
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33741, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Ringmail Leggings
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33742, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Ringmail Spaulders
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33743, 0, 0, @COST_3150_AP_2050_R), -- Vengeful Gladiator's Salvation
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33744, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Satin Gloves
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33745, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Satin Hood
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33746, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Satin Leggings
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33747, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Satin Mantle
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33748, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Satin Robe
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33749, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Scaled Chestpiece
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33750, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Scaled Gauntlets
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33751, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Scaled Helm
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33752, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Scaled Legguards
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33753, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Scaled Shoulders
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33754, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Shanker
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33755, 0, 0, @COST_1875_AP_2050_R), -- Vengeful Gladiator's Shield Wall
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33756, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Shiv
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33757, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Silk Amice
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33758, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Silk Cowl
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33759, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Silk Handguards
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33760, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Silk Raiment
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33761, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Silk Trousers
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33762, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Slicer
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33763, 0, 0, @COST_3150_AP_2050_R), -- Vengeful Gladiator's Spellblade
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33764, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Touch of Defeat
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33765, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's War Edge
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33766, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's War Staff
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33767, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Wyrmhide Gloves
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33768, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Wyrmhide Helm
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33769, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Wyrmhide Legguards
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33770, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Wyrmhide Spaulders
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33771, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Wyrmhide Tunic
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33801, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Mutilator
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33841, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Idol of Tenacity
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33842, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Libram of Justice
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33843, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Totem of the Third Wind
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33938, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Libram of Fortitude
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33941, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Totem of Indomitability
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33944, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Idol of Steadfastness
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33947, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Idol of Resolve
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33950, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Libram of Vengeance
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 33953, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Totem of Survival
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 34014, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Waraxe
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 34015, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Chopper
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 34016, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Left Render
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 34033, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Grimoire
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 34059, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Baton of Light
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 34066, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Piercing Touch
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 34529, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Longbow
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 34530, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Rifle
(@SEASON_3, @EXPLODYNE_FIZZLESPURT, 34540, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Battle Staff
(@SEASON_3, @ECTON_BRASSTUMBLER, 33006, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Heavy Crossbow
(@SEASON_3, @ECTON_BRASSTUMBLER, 33661, 0, 0, @COST_1875_AP_2050_R), -- Vengeful Gladiator's Barrier
(@SEASON_3, @ECTON_BRASSTUMBLER, 33662, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Bonecracker
(@SEASON_3, @ECTON_BRASSTUMBLER, 33663, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Bonegrinder
(@SEASON_3, @ECTON_BRASSTUMBLER, 33664, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Chain Armor
(@SEASON_3, @ECTON_BRASSTUMBLER, 33665, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Chain Gauntlets
(@SEASON_3, @ECTON_BRASSTUMBLER, 33666, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Chain Helm
(@SEASON_3, @ECTON_BRASSTUMBLER, 33667, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Chain Leggings
(@SEASON_3, @ECTON_BRASSTUMBLER, 33668, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Chain Spaulders
(@SEASON_3, @ECTON_BRASSTUMBLER, 33669, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Cleaver
(@SEASON_3, @ECTON_BRASSTUMBLER, 33670, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Decapitator
(@SEASON_3, @ECTON_BRASSTUMBLER, 33671, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Dragonhide Gloves
(@SEASON_3, @ECTON_BRASSTUMBLER, 33672, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Dragonhide Helm
(@SEASON_3, @ECTON_BRASSTUMBLER, 33673, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Dragonhide Legguards
(@SEASON_3, @ECTON_BRASSTUMBLER, 33674, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Dragonhide Spaulders
(@SEASON_3, @ECTON_BRASSTUMBLER, 33675, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Dragonhide Tunic
(@SEASON_3, @ECTON_BRASSTUMBLER, 33676, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Dreadweave Gloves
(@SEASON_3, @ECTON_BRASSTUMBLER, 33677, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Dreadweave Hood
(@SEASON_3, @ECTON_BRASSTUMBLER, 33678, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Dreadweave Leggings
(@SEASON_3, @ECTON_BRASSTUMBLER, 33679, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Dreadweave Mantle
(@SEASON_3, @ECTON_BRASSTUMBLER, 33680, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Dreadweave Robe
(@SEASON_3, @ECTON_BRASSTUMBLER, 33681, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Endgame
(@SEASON_3, @ECTON_BRASSTUMBLER, 33682, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Felweave Amice
(@SEASON_3, @ECTON_BRASSTUMBLER, 33683, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Felweave Cowl
(@SEASON_3, @ECTON_BRASSTUMBLER, 33684, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Felweave Handguards
(@SEASON_3, @ECTON_BRASSTUMBLER, 33685, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Felweave Raiment
(@SEASON_3, @ECTON_BRASSTUMBLER, 33686, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Felweave Trousers
(@SEASON_3, @ECTON_BRASSTUMBLER, 33687, 0, 0, @COST_3150_AP_2050_R), -- Vengeful Gladiator's Gavel
(@SEASON_3, @ECTON_BRASSTUMBLER, 33688, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Greatsword
(@SEASON_3, @ECTON_BRASSTUMBLER, 33689, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Hacker
(@SEASON_3, @ECTON_BRASSTUMBLER, 33690, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Kodohide Gloves
(@SEASON_3, @ECTON_BRASSTUMBLER, 33691, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Kodohide Helm
(@SEASON_3, @ECTON_BRASSTUMBLER, 33692, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Kodohide Legguards
(@SEASON_3, @ECTON_BRASSTUMBLER, 33693, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Kodohide Spaulders
(@SEASON_3, @ECTON_BRASSTUMBLER, 33694, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Kodohide Tunic
(@SEASON_3, @ECTON_BRASSTUMBLER, 33695, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Lamellar Chestpiece
(@SEASON_3, @ECTON_BRASSTUMBLER, 33696, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Lamellar Gauntlets
(@SEASON_3, @ECTON_BRASSTUMBLER, 33697, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Lamellar Helm
(@SEASON_3, @ECTON_BRASSTUMBLER, 33698, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Lamellar Legguards
(@SEASON_3, @ECTON_BRASSTUMBLER, 33699, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Lamellar Shoulders
(@SEASON_3, @ECTON_BRASSTUMBLER, 33700, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Leather Gloves
(@SEASON_3, @ECTON_BRASSTUMBLER, 33701, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Leather Helm
(@SEASON_3, @ECTON_BRASSTUMBLER, 33702, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Leather Legguards
(@SEASON_3, @ECTON_BRASSTUMBLER, 33703, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Leather Spaulders
(@SEASON_3, @ECTON_BRASSTUMBLER, 33704, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Leather Tunic
(@SEASON_3, @ECTON_BRASSTUMBLER, 33705, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Left Ripper
(@SEASON_3, @ECTON_BRASSTUMBLER, 33706, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Linked Armor
(@SEASON_3, @ECTON_BRASSTUMBLER, 33707, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Linked Gauntlets
(@SEASON_3, @ECTON_BRASSTUMBLER, 33708, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Linked Helm
(@SEASON_3, @ECTON_BRASSTUMBLER, 33709, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Linked Leggings
(@SEASON_3, @ECTON_BRASSTUMBLER, 33710, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Linked Spaulders
(@SEASON_3, @ECTON_BRASSTUMBLER, 33711, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Mail Armor
(@SEASON_3, @ECTON_BRASSTUMBLER, 33712, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Mail Gauntlets
(@SEASON_3, @ECTON_BRASSTUMBLER, 33713, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Mail Helm
(@SEASON_3, @ECTON_BRASSTUMBLER, 33714, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Mail Leggings
(@SEASON_3, @ECTON_BRASSTUMBLER, 33715, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Mail Spaulders
(@SEASON_3, @ECTON_BRASSTUMBLER, 33716, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Staff
(@SEASON_3, @ECTON_BRASSTUMBLER, 33717, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Mooncloth Gloves
(@SEASON_3, @ECTON_BRASSTUMBLER, 33718, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Mooncloth Hood
(@SEASON_3, @ECTON_BRASSTUMBLER, 33719, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Mooncloth Leggings
(@SEASON_3, @ECTON_BRASSTUMBLER, 33720, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Mooncloth Mantle
(@SEASON_3, @ECTON_BRASSTUMBLER, 33721, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Mooncloth Robe
(@SEASON_3, @ECTON_BRASSTUMBLER, 33722, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Ornamented Chestguard
(@SEASON_3, @ECTON_BRASSTUMBLER, 33723, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Ornamented Gloves
(@SEASON_3, @ECTON_BRASSTUMBLER, 33724, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Ornamented Headcover
(@SEASON_3, @ECTON_BRASSTUMBLER, 33725, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Ornamented Legplates
(@SEASON_3, @ECTON_BRASSTUMBLER, 33726, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Ornamented Spaulders
(@SEASON_3, @ECTON_BRASSTUMBLER, 33727, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Painsaw
(@SEASON_3, @ECTON_BRASSTUMBLER, 33728, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Plate Chestpiece
(@SEASON_3, @ECTON_BRASSTUMBLER, 33729, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Plate Gauntlets
(@SEASON_3, @ECTON_BRASSTUMBLER, 33730, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Plate Helm
(@SEASON_3, @ECTON_BRASSTUMBLER, 33731, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Plate Legguards
(@SEASON_3, @ECTON_BRASSTUMBLER, 33732, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Plate Shoulders
(@SEASON_3, @ECTON_BRASSTUMBLER, 33733, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Pummeler
(@SEASON_3, @ECTON_BRASSTUMBLER, 33734, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Quickblade
(@SEASON_3, @ECTON_BRASSTUMBLER, 33735, 0, 0, @COST_1875_AP_2050_R), -- Vengeful Gladiator's Redoubt
(@SEASON_3, @ECTON_BRASSTUMBLER, 33736, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Reprieve
(@SEASON_3, @ECTON_BRASSTUMBLER, 33737, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Right Ripper
(@SEASON_3, @ECTON_BRASSTUMBLER, 33738, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Ringmail Armor
(@SEASON_3, @ECTON_BRASSTUMBLER, 33739, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Ringmail Gauntlets
(@SEASON_3, @ECTON_BRASSTUMBLER, 33740, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Ringmail Helm
(@SEASON_3, @ECTON_BRASSTUMBLER, 33741, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Ringmail Leggings
(@SEASON_3, @ECTON_BRASSTUMBLER, 33742, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Ringmail Spaulders
(@SEASON_3, @ECTON_BRASSTUMBLER, 33743, 0, 0, @COST_3150_AP_2050_R), -- Vengeful Gladiator's Salvation
(@SEASON_3, @ECTON_BRASSTUMBLER, 33744, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Satin Gloves
(@SEASON_3, @ECTON_BRASSTUMBLER, 33745, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Satin Hood
(@SEASON_3, @ECTON_BRASSTUMBLER, 33746, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Satin Leggings
(@SEASON_3, @ECTON_BRASSTUMBLER, 33747, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Satin Mantle
(@SEASON_3, @ECTON_BRASSTUMBLER, 33748, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Satin Robe
(@SEASON_3, @ECTON_BRASSTUMBLER, 33749, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Scaled Chestpiece
(@SEASON_3, @ECTON_BRASSTUMBLER, 33750, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Scaled Gauntlets
(@SEASON_3, @ECTON_BRASSTUMBLER, 33751, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Scaled Helm
(@SEASON_3, @ECTON_BRASSTUMBLER, 33752, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Scaled Legguards
(@SEASON_3, @ECTON_BRASSTUMBLER, 33753, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Scaled Shoulders
(@SEASON_3, @ECTON_BRASSTUMBLER, 33754, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Shanker
(@SEASON_3, @ECTON_BRASSTUMBLER, 33755, 0, 0, @COST_1875_AP_2050_R), -- Vengeful Gladiator's Shield Wall
(@SEASON_3, @ECTON_BRASSTUMBLER, 33756, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Shiv
(@SEASON_3, @ECTON_BRASSTUMBLER, 33757, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Silk Amice
(@SEASON_3, @ECTON_BRASSTUMBLER, 33758, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Silk Cowl
(@SEASON_3, @ECTON_BRASSTUMBLER, 33759, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Silk Handguards
(@SEASON_3, @ECTON_BRASSTUMBLER, 33760, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Silk Raiment
(@SEASON_3, @ECTON_BRASSTUMBLER, 33761, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Silk Trousers
(@SEASON_3, @ECTON_BRASSTUMBLER, 33762, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Slicer
(@SEASON_3, @ECTON_BRASSTUMBLER, 33763, 0, 0, @COST_3150_AP_2050_R), -- Vengeful Gladiator's Spellblade
(@SEASON_3, @ECTON_BRASSTUMBLER, 33764, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Touch of Defeat
(@SEASON_3, @ECTON_BRASSTUMBLER, 33765, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's War Edge
(@SEASON_3, @ECTON_BRASSTUMBLER, 33766, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's War Staff
(@SEASON_3, @ECTON_BRASSTUMBLER, 33767, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Wyrmhide Gloves
(@SEASON_3, @ECTON_BRASSTUMBLER, 33768, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Wyrmhide Helm
(@SEASON_3, @ECTON_BRASSTUMBLER, 33769, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Wyrmhide Legguards
(@SEASON_3, @ECTON_BRASSTUMBLER, 33770, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Wyrmhide Spaulders
(@SEASON_3, @ECTON_BRASSTUMBLER, 33771, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Wyrmhide Tunic
(@SEASON_3, @ECTON_BRASSTUMBLER, 33801, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Mutilator
(@SEASON_3, @ECTON_BRASSTUMBLER, 33841, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Idol of Tenacity
(@SEASON_3, @ECTON_BRASSTUMBLER, 33842, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Libram of Justice
(@SEASON_3, @ECTON_BRASSTUMBLER, 33843, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Totem of the Third Wind
(@SEASON_3, @ECTON_BRASSTUMBLER, 33938, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Libram of Fortitude
(@SEASON_3, @ECTON_BRASSTUMBLER, 33941, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Totem of Indomitability
(@SEASON_3, @ECTON_BRASSTUMBLER, 33944, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Idol of Steadfastness
(@SEASON_3, @ECTON_BRASSTUMBLER, 33947, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Idol of Resolve
(@SEASON_3, @ECTON_BRASSTUMBLER, 33950, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Libram of Vengeance
(@SEASON_3, @ECTON_BRASSTUMBLER, 33953, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Totem of Survival
(@SEASON_3, @ECTON_BRASSTUMBLER, 34014, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Waraxe
(@SEASON_3, @ECTON_BRASSTUMBLER, 34015, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Chopper
(@SEASON_3, @ECTON_BRASSTUMBLER, 34016, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Left Render
(@SEASON_3, @ECTON_BRASSTUMBLER, 34033, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Grimoire
(@SEASON_3, @ECTON_BRASSTUMBLER, 34059, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Baton of Light
(@SEASON_3, @ECTON_BRASSTUMBLER, 34066, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Piercing Touch
(@SEASON_3, @ECTON_BRASSTUMBLER, 34529, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Longbow
(@SEASON_3, @ECTON_BRASSTUMBLER, 34530, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Rifle
(@SEASON_3, @ECTON_BRASSTUMBLER, 34540, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Battle Staff
(@SEASON_3, @MEMINNIE, 33006, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Heavy Crossbow
(@SEASON_3, @MEMINNIE, 33661, 0, 0, @COST_1875_AP_2050_R), -- Vengeful Gladiator's Barrier
(@SEASON_3, @MEMINNIE, 33662, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Bonecracker
(@SEASON_3, @MEMINNIE, 33663, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Bonegrinder
(@SEASON_3, @MEMINNIE, 33664, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Chain Armor
(@SEASON_3, @MEMINNIE, 33665, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Chain Gauntlets
(@SEASON_3, @MEMINNIE, 33666, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Chain Helm
(@SEASON_3, @MEMINNIE, 33667, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Chain Leggings
(@SEASON_3, @MEMINNIE, 33668, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Chain Spaulders
(@SEASON_3, @MEMINNIE, 33669, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Cleaver
(@SEASON_3, @MEMINNIE, 33670, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Decapitator
(@SEASON_3, @MEMINNIE, 33671, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Dragonhide Gloves
(@SEASON_3, @MEMINNIE, 33672, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Dragonhide Helm
(@SEASON_3, @MEMINNIE, 33673, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Dragonhide Legguards
(@SEASON_3, @MEMINNIE, 33674, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Dragonhide Spaulders
(@SEASON_3, @MEMINNIE, 33675, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Dragonhide Tunic
(@SEASON_3, @MEMINNIE, 33676, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Dreadweave Gloves
(@SEASON_3, @MEMINNIE, 33677, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Dreadweave Hood
(@SEASON_3, @MEMINNIE, 33678, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Dreadweave Leggings
(@SEASON_3, @MEMINNIE, 33679, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Dreadweave Mantle
(@SEASON_3, @MEMINNIE, 33680, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Dreadweave Robe
(@SEASON_3, @MEMINNIE, 33681, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Endgame
(@SEASON_3, @MEMINNIE, 33682, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Felweave Amice
(@SEASON_3, @MEMINNIE, 33683, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Felweave Cowl
(@SEASON_3, @MEMINNIE, 33684, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Felweave Handguards
(@SEASON_3, @MEMINNIE, 33685, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Felweave Raiment
(@SEASON_3, @MEMINNIE, 33686, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Felweave Trousers
(@SEASON_3, @MEMINNIE, 33687, 0, 0, @COST_3150_AP_2050_R), -- Vengeful Gladiator's Gavel
(@SEASON_3, @MEMINNIE, 33688, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Greatsword
(@SEASON_3, @MEMINNIE, 33689, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Hacker
(@SEASON_3, @MEMINNIE, 33690, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Kodohide Gloves
(@SEASON_3, @MEMINNIE, 33691, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Kodohide Helm
(@SEASON_3, @MEMINNIE, 33692, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Kodohide Legguards
(@SEASON_3, @MEMINNIE, 33693, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Kodohide Spaulders
(@SEASON_3, @MEMINNIE, 33694, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Kodohide Tunic
(@SEASON_3, @MEMINNIE, 33695, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Lamellar Chestpiece
(@SEASON_3, @MEMINNIE, 33696, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Lamellar Gauntlets
(@SEASON_3, @MEMINNIE, 33697, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Lamellar Helm
(@SEASON_3, @MEMINNIE, 33698, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Lamellar Legguards
(@SEASON_3, @MEMINNIE, 33699, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Lamellar Shoulders
(@SEASON_3, @MEMINNIE, 33700, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Leather Gloves
(@SEASON_3, @MEMINNIE, 33701, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Leather Helm
(@SEASON_3, @MEMINNIE, 33702, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Leather Legguards
(@SEASON_3, @MEMINNIE, 33703, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Leather Spaulders
(@SEASON_3, @MEMINNIE, 33704, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Leather Tunic
(@SEASON_3, @MEMINNIE, 33705, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Left Ripper
(@SEASON_3, @MEMINNIE, 33706, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Linked Armor
(@SEASON_3, @MEMINNIE, 33707, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Linked Gauntlets
(@SEASON_3, @MEMINNIE, 33708, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Linked Helm
(@SEASON_3, @MEMINNIE, 33709, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Linked Leggings
(@SEASON_3, @MEMINNIE, 33710, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Linked Spaulders
(@SEASON_3, @MEMINNIE, 33711, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Mail Armor
(@SEASON_3, @MEMINNIE, 33712, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Mail Gauntlets
(@SEASON_3, @MEMINNIE, 33713, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Mail Helm
(@SEASON_3, @MEMINNIE, 33714, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Mail Leggings
(@SEASON_3, @MEMINNIE, 33715, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Mail Spaulders
(@SEASON_3, @MEMINNIE, 33716, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Staff
(@SEASON_3, @MEMINNIE, 33717, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Mooncloth Gloves
(@SEASON_3, @MEMINNIE, 33718, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Mooncloth Hood
(@SEASON_3, @MEMINNIE, 33719, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Mooncloth Leggings
(@SEASON_3, @MEMINNIE, 33720, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Mooncloth Mantle
(@SEASON_3, @MEMINNIE, 33721, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Mooncloth Robe
(@SEASON_3, @MEMINNIE, 33722, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Ornamented Chestguard
(@SEASON_3, @MEMINNIE, 33723, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Ornamented Gloves
(@SEASON_3, @MEMINNIE, 33724, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Ornamented Headcover
(@SEASON_3, @MEMINNIE, 33725, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Ornamented Legplates
(@SEASON_3, @MEMINNIE, 33726, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Ornamented Spaulders
(@SEASON_3, @MEMINNIE, 33727, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Painsaw
(@SEASON_3, @MEMINNIE, 33728, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Plate Chestpiece
(@SEASON_3, @MEMINNIE, 33729, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Plate Gauntlets
(@SEASON_3, @MEMINNIE, 33730, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Plate Helm
(@SEASON_3, @MEMINNIE, 33731, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Plate Legguards
(@SEASON_3, @MEMINNIE, 33732, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Plate Shoulders
(@SEASON_3, @MEMINNIE, 33733, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Pummeler
(@SEASON_3, @MEMINNIE, 33734, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Quickblade
(@SEASON_3, @MEMINNIE, 33735, 0, 0, @COST_1875_AP_2050_R), -- Vengeful Gladiator's Redoubt
(@SEASON_3, @MEMINNIE, 33736, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Reprieve
(@SEASON_3, @MEMINNIE, 33737, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Right Ripper
(@SEASON_3, @MEMINNIE, 33738, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Ringmail Armor
(@SEASON_3, @MEMINNIE, 33739, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Ringmail Gauntlets
(@SEASON_3, @MEMINNIE, 33740, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Ringmail Helm
(@SEASON_3, @MEMINNIE, 33741, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Ringmail Leggings
(@SEASON_3, @MEMINNIE, 33742, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Ringmail Spaulders
(@SEASON_3, @MEMINNIE, 33743, 0, 0, @COST_3150_AP_2050_R), -- Vengeful Gladiator's Salvation
(@SEASON_3, @MEMINNIE, 33744, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Satin Gloves
(@SEASON_3, @MEMINNIE, 33745, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Satin Hood
(@SEASON_3, @MEMINNIE, 33746, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Satin Leggings
(@SEASON_3, @MEMINNIE, 33747, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Satin Mantle
(@SEASON_3, @MEMINNIE, 33748, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Satin Robe
(@SEASON_3, @MEMINNIE, 33749, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Scaled Chestpiece
(@SEASON_3, @MEMINNIE, 33750, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Scaled Gauntlets
(@SEASON_3, @MEMINNIE, 33751, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Scaled Helm
(@SEASON_3, @MEMINNIE, 33752, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Scaled Legguards
(@SEASON_3, @MEMINNIE, 33753, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Scaled Shoulders
(@SEASON_3, @MEMINNIE, 33754, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Shanker
(@SEASON_3, @MEMINNIE, 33755, 0, 0, @COST_1875_AP_2050_R), -- Vengeful Gladiator's Shield Wall
(@SEASON_3, @MEMINNIE, 33756, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Shiv
(@SEASON_3, @MEMINNIE, 33757, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Silk Amice
(@SEASON_3, @MEMINNIE, 33758, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Silk Cowl
(@SEASON_3, @MEMINNIE, 33759, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Silk Handguards
(@SEASON_3, @MEMINNIE, 33760, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Silk Raiment
(@SEASON_3, @MEMINNIE, 33761, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Silk Trousers
(@SEASON_3, @MEMINNIE, 33762, 0, 0, @COST_2625_AP_2050_R), -- Vengeful Gladiator's Slicer
(@SEASON_3, @MEMINNIE, 33763, 0, 0, @COST_3150_AP_2050_R), -- Vengeful Gladiator's Spellblade
(@SEASON_3, @MEMINNIE, 33764, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Touch of Defeat
(@SEASON_3, @MEMINNIE, 33765, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's War Edge
(@SEASON_3, @MEMINNIE, 33766, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's War Staff
(@SEASON_3, @MEMINNIE, 33767, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Wyrmhide Gloves
(@SEASON_3, @MEMINNIE, 33768, 0, 0, @COST_1875_AP_1700_R), -- Vengeful Gladiator's Wyrmhide Helm
(@SEASON_3, @MEMINNIE, 33769, 0, 0, @COST_1875_AP_1550_R), -- Vengeful Gladiator's Wyrmhide Legguards
(@SEASON_3, @MEMINNIE, 33770, 0, 0, @COST_1500_AP_2200_R), -- Vengeful Gladiator's Wyrmhide Spaulders
(@SEASON_3, @MEMINNIE, 33771, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Vengeful Gladiator's Wyrmhide Tunic
(@SEASON_3, @MEMINNIE, 33801, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Mutilator
(@SEASON_3, @MEMINNIE, 33841, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Idol of Tenacity
(@SEASON_3, @MEMINNIE, 33842, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Libram of Justice
(@SEASON_3, @MEMINNIE, 33843, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Totem of the Third Wind
(@SEASON_3, @MEMINNIE, 33938, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Libram of Fortitude
(@SEASON_3, @MEMINNIE, 33941, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Totem of Indomitability
(@SEASON_3, @MEMINNIE, 33944, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Idol of Steadfastness
(@SEASON_3, @MEMINNIE, 33947, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Idol of Resolve
(@SEASON_3, @MEMINNIE, 33950, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Libram of Vengeance
(@SEASON_3, @MEMINNIE, 33953, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Totem of Survival
(@SEASON_3, @MEMINNIE, 34014, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Waraxe
(@SEASON_3, @MEMINNIE, 34015, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Chopper
(@SEASON_3, @MEMINNIE, 34016, 0, 0, @COST_1125_AP_2050_R), -- Vengeful Gladiator's Left Render
(@SEASON_3, @MEMINNIE, 34033, 0, 0, @COST_1125_AP), -- Vengeful Gladiator's Grimoire
(@SEASON_3, @MEMINNIE, 34059, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Baton of Light
(@SEASON_3, @MEMINNIE, 34066, 0, 0, @COST_1000_AP_1750_R), -- Vengeful Gladiator's Piercing Touch
(@SEASON_3, @MEMINNIE, 34529, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Longbow
(@SEASON_3, @MEMINNIE, 34530, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Rifle
(@SEASON_3, @MEMINNIE, 34540, 0, 0, @COST_3750_AP_2050_R), -- Vengeful Gladiator's Battle Staff
(@SEASON_3, @LADY_PALANSEER, 24544, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Plate Chestpiece
(@SEASON_3, @LADY_PALANSEER, 24545, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Plate Helm
(@SEASON_3, @LADY_PALANSEER, 24546, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Plate Shoulders
(@SEASON_3, @LADY_PALANSEER, 24547, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Plate Legguards
(@SEASON_3, @LADY_PALANSEER, 24549, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Plate Gauntlets
(@SEASON_3, @LADY_PALANSEER, 24552, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Dreadweave Robe
(@SEASON_3, @LADY_PALANSEER, 24553, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Dreadweave Hood
(@SEASON_3, @LADY_PALANSEER, 24554, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Dreadweave Mantle
(@SEASON_3, @LADY_PALANSEER, 24555, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Dreadweave Leggings
(@SEASON_3, @LADY_PALANSEER, 24556, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Dreadweave Gloves
(@SEASON_3, @LADY_PALANSEER, 25830, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Leather Helm
(@SEASON_3, @LADY_PALANSEER, 25831, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Leather Tunic
(@SEASON_3, @LADY_PALANSEER, 25832, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Leather Spaulders
(@SEASON_3, @LADY_PALANSEER, 25833, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Leather Legguards
(@SEASON_3, @LADY_PALANSEER, 25834, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Leather Gloves
(@SEASON_3, @LADY_PALANSEER, 25854, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Silk Amice
(@SEASON_3, @LADY_PALANSEER, 25855, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Silk Cowl
(@SEASON_3, @LADY_PALANSEER, 25856, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Silk Raiment
(@SEASON_3, @LADY_PALANSEER, 25857, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Silk Handguards
(@SEASON_3, @LADY_PALANSEER, 25858, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Silk Trousers
(@SEASON_3, @LADY_PALANSEER, 25997, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Linked Armor
(@SEASON_3, @LADY_PALANSEER, 25998, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Linked Helm
(@SEASON_3, @LADY_PALANSEER, 25999, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Linked Spaulders
(@SEASON_3, @LADY_PALANSEER, 26000, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Linked Gauntlets
(@SEASON_3, @LADY_PALANSEER, 26001, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Linked Leggings
(@SEASON_3, @LADY_PALANSEER, 27469, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Mail Armor
(@SEASON_3, @LADY_PALANSEER, 27470, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Mail Gauntlets
(@SEASON_3, @LADY_PALANSEER, 27471, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Mail Helm
(@SEASON_3, @LADY_PALANSEER, 27472, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Mail Leggings
(@SEASON_3, @LADY_PALANSEER, 27473, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Mail Spaulders
(@SEASON_3, @LADY_PALANSEER, 27702, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Lamellar Chestpiece
(@SEASON_3, @LADY_PALANSEER, 27703, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Lamellar Gauntlets
(@SEASON_3, @LADY_PALANSEER, 27704, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Lamellar Helm
(@SEASON_3, @LADY_PALANSEER, 27705, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Lamellar Legguards
(@SEASON_3, @LADY_PALANSEER, 27706, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Lamellar Shoulders
(@SEASON_3, @LADY_PALANSEER, 27707, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Satin Gloves
(@SEASON_3, @LADY_PALANSEER, 27708, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Satin Hood
(@SEASON_3, @LADY_PALANSEER, 27709, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Satin Leggings
(@SEASON_3, @LADY_PALANSEER, 27710, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Satin Mantle
(@SEASON_3, @LADY_PALANSEER, 27711, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Satin Robe
(@SEASON_3, @LADY_PALANSEER, 27879, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Scaled Chestpiece
(@SEASON_3, @LADY_PALANSEER, 27880, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Scaled Gauntlets
(@SEASON_3, @LADY_PALANSEER, 27881, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Scaled Helm
(@SEASON_3, @LADY_PALANSEER, 27882, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Scaled Legguards
(@SEASON_3, @LADY_PALANSEER, 27883, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Scaled Shoulders
(@SEASON_3, @LADY_PALANSEER, 28126, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Dragonhide Gloves
(@SEASON_3, @LADY_PALANSEER, 28127, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Dragonhide Helm
(@SEASON_3, @LADY_PALANSEER, 28128, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Dragonhide Legguards
(@SEASON_3, @LADY_PALANSEER, 28129, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Dragonhide Spaulders
(@SEASON_3, @LADY_PALANSEER, 28130, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Dragonhide Tunic
(@SEASON_3, @LADY_PALANSEER, 28136, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Wyrmhide Gloves
(@SEASON_3, @LADY_PALANSEER, 28137, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Wyrmhide Helm
(@SEASON_3, @LADY_PALANSEER, 28138, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Wyrmhide Legguards
(@SEASON_3, @LADY_PALANSEER, 28139, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Wyrmhide Spaulders
(@SEASON_3, @LADY_PALANSEER, 28140, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Wyrmhide Tunic
(@SEASON_3, @LADY_PALANSEER, 28331, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Chain Helm
(@SEASON_3, @LADY_PALANSEER, 28332, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Chain Leggings
(@SEASON_3, @LADY_PALANSEER, 28333, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Chain Spaulders
(@SEASON_3, @LADY_PALANSEER, 28334, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Chain Armor
(@SEASON_3, @LADY_PALANSEER, 28335, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Chain Gauntlets
(@SEASON_3, @LADY_PALANSEER, 30186, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Felweave Amice
(@SEASON_3, @LADY_PALANSEER, 30187, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Felweave Cowl
(@SEASON_3, @LADY_PALANSEER, 30188, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Felweave Handguards
(@SEASON_3, @LADY_PALANSEER, 30200, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Felweave Raiment
(@SEASON_3, @LADY_PALANSEER, 30201, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Felweave Trousers
(@SEASON_3, @LADY_PALANSEER, 31375, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Kodohide Gloves
(@SEASON_3, @LADY_PALANSEER, 31376, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Kodohide Helm
(@SEASON_3, @LADY_PALANSEER, 31377, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Kodohide Legguards
(@SEASON_3, @LADY_PALANSEER, 31378, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Kodohide Spaulders
(@SEASON_3, @LADY_PALANSEER, 31379, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Kodohide Tunic
(@SEASON_3, @LADY_PALANSEER, 31396, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Ringmail Armor
(@SEASON_3, @LADY_PALANSEER, 31397, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Ringmail Gauntlets
(@SEASON_3, @LADY_PALANSEER, 31400, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Ringmail Helm
(@SEASON_3, @LADY_PALANSEER, 31406, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Ringmail Leggings
(@SEASON_3, @LADY_PALANSEER, 31407, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Ringmail Spaulders
(@SEASON_3, @LADY_PALANSEER, 31409, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Mooncloth Gloves
(@SEASON_3, @LADY_PALANSEER, 31410, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Mooncloth Hood
(@SEASON_3, @LADY_PALANSEER, 31411, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Mooncloth Leggings
(@SEASON_3, @LADY_PALANSEER, 31412, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Mooncloth Mantle
(@SEASON_3, @LADY_PALANSEER, 31413, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Mooncloth Robe
(@SEASON_3, @LADY_PALANSEER, 31613, 0, 0, @COST_14500_HP_30_AB), -- Gladiator's Ornamented Chestguard
(@SEASON_3, @LADY_PALANSEER, 31614, 0, 0, @COST_10500_HP_20_AV), -- Gladiator's Ornamented Gloves
(@SEASON_3, @LADY_PALANSEER, 31616, 0, 0, @COST_14500_HP_30_AV), -- Gladiator's Ornamented Headcover
(@SEASON_3, @LADY_PALANSEER, 31618, 0, 0, @COST_14500_HP_30_WSG), -- Gladiator's Ornamented Legplates
(@SEASON_3, @LADY_PALANSEER, 31619, 0, 0, @COST_11250_HP_20_AB), -- Gladiator's Ornamented Spaulders
(@SEASON_3, @SERGEANT_THUNDERHORN, 24550, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's Greatsword
(@SEASON_3, @SERGEANT_THUNDERHORN, 24557, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's War Staff
(@SEASON_3, @SERGEANT_THUNDERHORN, 28294, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's Heavy Crossbow
(@SEASON_3, @SERGEANT_THUNDERHORN, 28295, 0, 0, @COST_18000_HP_20_ES), -- Gladiator's Slicer
(@SEASON_3, @SERGEANT_THUNDERHORN, 28297, 0, 0, @COST_25200_HP_20_ES), -- Gladiator's Spellblade
(@SEASON_3, @SERGEANT_THUNDERHORN, 28298, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's Decapitator
(@SEASON_3, @SERGEANT_THUNDERHORN, 28299, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's Bonegrinder
(@SEASON_3, @SERGEANT_THUNDERHORN, 28300, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's Painsaw
(@SEASON_3, @SERGEANT_THUNDERHORN, 28302, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Bonecracker
(@SEASON_3, @SERGEANT_THUNDERHORN, 28305, 0, 0, @COST_18000_HP_20_ES), -- Gladiator's Pummeler
(@SEASON_3, @SERGEANT_THUNDERHORN, 28307, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Quickblade
(@SEASON_3, @SERGEANT_THUNDERHORN, 28308, 0, 0, @COST_18000_HP_20_ES), -- Gladiator's Cleaver
(@SEASON_3, @SERGEANT_THUNDERHORN, 28309, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Hacker
(@SEASON_3, @SERGEANT_THUNDERHORN, 28310, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Shiv
(@SEASON_3, @SERGEANT_THUNDERHORN, 28312, 0, 0, @COST_18000_HP_20_ES), -- Gladiator's Shanker
(@SEASON_3, @SERGEANT_THUNDERHORN, 28313, 0, 0, @COST_18000_HP_20_ES), -- Gladiator's Right Ripper
(@SEASON_3, @SERGEANT_THUNDERHORN, 28314, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Left Ripper
(@SEASON_3, @SERGEANT_THUNDERHORN, 28319, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's War Edge
(@SEASON_3, @SERGEANT_THUNDERHORN, 28320, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Touch of Defeat
(@SEASON_3, @SERGEANT_THUNDERHORN, 28346, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Endgame
(@SEASON_3, @SERGEANT_THUNDERHORN, 28355, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Idol of Tenacity
(@SEASON_3, @SERGEANT_THUNDERHORN, 28356, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Libram of Justice
(@SEASON_3, @SERGEANT_THUNDERHORN, 28357, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Totem of the Third Wind
(@SEASON_3, @SERGEANT_THUNDERHORN, 28358, 0, 0, @COST_15000_HP_20_ES), -- Gladiator's Shield Wall
(@SEASON_3, @SERGEANT_THUNDERHORN, 28476, 0, 0, @COST_27000_HP_40_AV), -- Gladiator's Maul
(@SEASON_3, @SERGEANT_THUNDERHORN, 32450, 0, 0, @COST_25200_HP_20_ES), -- Gladiator's Gavel
(@SEASON_3, @SERGEANT_THUNDERHORN, 32451, 0, 0, @COST_25200_HP_20_ES), -- Gladiator's Salvation
(@SEASON_3, @SERGEANT_THUNDERHORN, 32452, 0, 0, @COST_9000_HP_20_ES), -- Gladiator's Reprieve
(@SEASON_3, @SERGEANT_THUNDERHORN, 33936, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Libram of Fortitude
(@SEASON_3, @SERGEANT_THUNDERHORN, 33939, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Totem of Indomitability
(@SEASON_3, @SERGEANT_THUNDERHORN, 33942, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Idol of Steadfastness
(@SEASON_3, @SERGEANT_THUNDERHORN, 33945, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Idol of Resolve
(@SEASON_3, @SERGEANT_THUNDERHORN, 33948, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Libram of Vengeance
(@SEASON_3, @SERGEANT_THUNDERHORN, 33951, 0, 0, @COST_8000_HP_10_ES), -- Gladiator's Totem of Survival
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 30486, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Plate Chestpiece
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 30487, 0, 0, @COST_900_AP), -- Merciless Gladiator's Plate Gauntlets
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 30488, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Plate Helm
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 30489, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Plate Legguards
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 30490, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Plate Shoulders
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31958, 0, 0, @COST_900_AP), -- Merciless Gladiator's Bonecracker
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31959, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Bonegrinder
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31960, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Chain Armor
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31961, 0, 0, @COST_900_AP), -- Merciless Gladiator's Chain Gauntlets
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31962, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Chain Helm
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31963, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Chain Leggings
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31964, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Chain Spaulders
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31965, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Cleaver
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31966, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Decapitator
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31967, 0, 0, @COST_900_AP), -- Merciless Gladiator's Dragonhide Gloves
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31968, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dragonhide Helm
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31969, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dragonhide Legguards
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31971, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Dragonhide Spaulders
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31972, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dragonhide Tunic
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31973, 0, 0, @COST_900_AP), -- Merciless Gladiator's Dreadweave Gloves
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31974, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dreadweave Hood
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31975, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dreadweave Leggings
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31976, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Dreadweave Mantle
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31977, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dreadweave Robe
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31978, 0, 0, @COST_900_AP), -- Merciless Gladiator's Endgame
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31979, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Felweave Amice
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31980, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Felweave Cowl
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31981, 0, 0, @COST_900_AP), -- Merciless Gladiator's Felweave Handguards
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31982, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Felweave Raiment
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31983, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Felweave Trousers
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31984, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Greatsword
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31985, 0, 0, @COST_900_AP), -- Merciless Gladiator's Hacker
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31986, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Crossbow of the Phoenix
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31987, 0, 0, @COST_900_AP), -- Merciless Gladiator's Kodohide Gloves
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31988, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Kodohide Helm
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31989, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Kodohide Legguards
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31990, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Kodohide Spaulders
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31991, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Kodohide Tunic
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31992, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Lamellar Chestpiece
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31993, 0, 0, @COST_900_AP), -- Merciless Gladiator's Lamellar Gauntlets
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31995, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Lamellar Legguards
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31996, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Lamellar Shoulders
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31997, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Lamellar Helm
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31998, 0, 0, @COST_900_AP), -- Merciless Gladiator's Leather Gloves
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 31999, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Leather Helm
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32000, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Leather Legguards
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32001, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Leather Spaulders
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32002, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Leather Tunic
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32003, 0, 0, @COST_900_AP), -- Merciless Gladiator's Left Ripper
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32004, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Linked Armor
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32005, 0, 0, @COST_900_AP), -- Merciless Gladiator's Linked Gauntlets
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32006, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Linked Helm
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32007, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Linked Leggings
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32008, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Linked Spaulders
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32009, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mail Armor
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32010, 0, 0, @COST_900_AP), -- Merciless Gladiator's Mail Gauntlets
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32011, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mail Helm
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32012, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mail Leggings
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32013, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Mail Spaulders
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32014, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Maul
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32015, 0, 0, @COST_900_AP), -- Merciless Gladiator's Mooncloth Gloves
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32016, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mooncloth Hood
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32017, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mooncloth Leggings
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32018, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Mooncloth Mantle
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32019, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mooncloth Robe
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32020, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ornamented Chestguard
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32021, 0, 0, @COST_900_AP), -- Merciless Gladiator's Ornamented Gloves
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32022, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ornamented Headcover
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32023, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ornamented Legplates
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32024, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Ornamented Spaulders
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32025, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Painsaw
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32026, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Pummeler
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32027, 0, 0, @COST_900_AP), -- Merciless Gladiator's Quickblade
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32028, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Right Ripper
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32029, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ringmail Armor
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32030, 0, 0, @COST_900_AP), -- Merciless Gladiator's Ringmail Gauntlets
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32031, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ringmail Helm
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32032, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ringmail Leggings
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32033, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Ringmail Spaulders
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32034, 0, 0, @COST_900_AP), -- Merciless Gladiator's Satin Gloves
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32035, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Satin Hood
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32036, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Satin Leggings
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32037, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Satin Mantle
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32038, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Satin Robe
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32039, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Scaled Chestpiece
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32040, 0, 0, @COST_900_AP), -- Merciless Gladiator's Scaled Gauntlets
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32041, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Scaled Helm
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32042, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Scaled Legguards
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32043, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Scaled Shoulders
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32044, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Shanker
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32045, 0, 0, @COST_1500_AP_1800_R), -- Merciless Gladiator's Shield Wall
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32046, 0, 0, @COST_900_AP), -- Merciless Gladiator's Shiv
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32047, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Silk Amice
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32048, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Silk Cowl
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32049, 0, 0, @COST_900_AP), -- Merciless Gladiator's Silk Handguards
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32050, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Silk Raiment
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32051, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Silk Trousers
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32052, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Slicer
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32053, 0, 0, @COST_2520_AP_1800_R), -- Merciless Gladiator's Spellblade
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32054, 0, 0, @COST_800_AP), -- Merciless Gladiator's War Edge
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32055, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's War Staff
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32056, 0, 0, @COST_900_AP), -- Merciless Gladiator's Wyrmhide Gloves
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32057, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Wyrmhide Helm
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32058, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Wyrmhide Legguards
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32059, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Wyrmhide Spaulders
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32060, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Wyrmhide Tunic
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32961, 0, 0, @COST_900_AP), -- Merciless Gladiator's Reprieve
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32962, 0, 0, @COST_800_AP), -- Merciless Gladiator's Touch of Defeat
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32963, 0, 0, @COST_2520_AP_1800_R), -- Merciless Gladiator's Gavel
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 32964, 0, 0, @COST_2520_AP_1800_R), -- Merciless Gladiator's Salvation
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 33076, 0, 0, @COST_800_AP), -- Merciless Gladiator's Idol of Tenacity
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 33077, 0, 0, @COST_800_AP), -- Merciless Gladiator's Libram of Justice
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 33078, 0, 0, @COST_800_AP), -- Merciless Gladiator's Totem of the Third Wind
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 33309, 0, 0, @COST_1500_AP_1800_R), -- Merciless Gladiator's Redoubt
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 33313, 0, 0, @COST_1500_AP_1800_R), -- Merciless Gladiator's Barrier
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 33937, 0, 0, @COST_800_AP), -- Merciless Gladiator's Libram of Fortitude
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 33940, 0, 0, @COST_800_AP), -- Merciless Gladiator's Totem of Indomitability
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 33943, 0, 0, @COST_800_AP), -- Merciless Gladiator's Idol of Steadfastness
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 33946, 0, 0, @COST_800_AP), -- Merciless Gladiator's Idol of Resolve
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 33949, 0, 0, @COST_800_AP), -- Merciless Gladiator's Libram of Vengeance
(@SEASON_3, @KRIXEL_PINCHWHISTLE, 33952, 0, 0, @COST_800_AP), -- Merciless Gladiator's Totem of Survival
(@SEASON_3, @DORIS_VOLANTHIUS, 33056, 0, 0, @COST_11934_HP_10_AV), -- Veteran's Band of Dominance
(@SEASON_3, @DORIS_VOLANTHIUS, 33057, 0, 0, @COST_11934_HP_10_AV), -- Veteran's Band of Triumph
(@SEASON_3, @DORIS_VOLANTHIUS, 33064, 0, 0, @COST_11934_HP_10_AV), -- Veteran's Band of Salvation
(@SEASON_3, @DORIS_VOLANTHIUS, 33811, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Plate Belt
(@SEASON_3, @DORIS_VOLANTHIUS, 33812, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Plate Greaves
(@SEASON_3, @DORIS_VOLANTHIUS, 33813, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Plate Bracers
(@SEASON_3, @DORIS_VOLANTHIUS, 33853, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Vindicator's Band of Dominance
(@SEASON_3, @DORIS_VOLANTHIUS, 33876, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Chain Bracers
(@SEASON_3, @DORIS_VOLANTHIUS, 33877, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Chain Girdle
(@SEASON_3, @DORIS_VOLANTHIUS, 33878, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Chain Sabatons
(@SEASON_3, @DORIS_VOLANTHIUS, 33879, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Dragonhide Belt
(@SEASON_3, @DORIS_VOLANTHIUS, 33880, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Dragonhide Boots
(@SEASON_3, @DORIS_VOLANTHIUS, 33881, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Dragonhide Bracers
(@SEASON_3, @DORIS_VOLANTHIUS, 33882, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Dreadweave Belt
(@SEASON_3, @DORIS_VOLANTHIUS, 33883, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Dreadweave Cuffs
(@SEASON_3, @DORIS_VOLANTHIUS, 33884, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Dreadweave Stalkers
(@SEASON_3, @DORIS_VOLANTHIUS, 33885, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Kodohide Belt
(@SEASON_3, @DORIS_VOLANTHIUS, 33886, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Kodohide Boots
(@SEASON_3, @DORIS_VOLANTHIUS, 33887, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Kodohide Bracers
(@SEASON_3, @DORIS_VOLANTHIUS, 33888, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Lamellar Belt
(@SEASON_3, @DORIS_VOLANTHIUS, 33889, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Lamellar Bracers
(@SEASON_3, @DORIS_VOLANTHIUS, 33890, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Lamellar Greaves
(@SEASON_3, @DORIS_VOLANTHIUS, 33891, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Leather Belt
(@SEASON_3, @DORIS_VOLANTHIUS, 33892, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Leather Boots
(@SEASON_3, @DORIS_VOLANTHIUS, 33893, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Leather Bracers
(@SEASON_3, @DORIS_VOLANTHIUS, 33894, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Linked Bracers
(@SEASON_3, @DORIS_VOLANTHIUS, 33895, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Linked Girdle
(@SEASON_3, @DORIS_VOLANTHIUS, 33896, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Linked Sabatons
(@SEASON_3, @DORIS_VOLANTHIUS, 33897, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Mail Bracers
(@SEASON_3, @DORIS_VOLANTHIUS, 33898, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Mail Girdle
(@SEASON_3, @DORIS_VOLANTHIUS, 33899, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Mail Sabatons
(@SEASON_3, @DORIS_VOLANTHIUS, 33900, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Mooncloth Belt
(@SEASON_3, @DORIS_VOLANTHIUS, 33901, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Mooncloth Cuffs
(@SEASON_3, @DORIS_VOLANTHIUS, 33902, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Mooncloth Slippers
(@SEASON_3, @DORIS_VOLANTHIUS, 33903, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Ornamented Belt
(@SEASON_3, @DORIS_VOLANTHIUS, 33904, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Ornamented Bracers
(@SEASON_3, @DORIS_VOLANTHIUS, 33905, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Ornamented Greaves
(@SEASON_3, @DORIS_VOLANTHIUS, 33906, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Ringmail Bracers
(@SEASON_3, @DORIS_VOLANTHIUS, 33907, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Ringmail Girdle
(@SEASON_3, @DORIS_VOLANTHIUS, 33908, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Ringmail Sabatons
(@SEASON_3, @DORIS_VOLANTHIUS, 33909, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Scaled Belt
(@SEASON_3, @DORIS_VOLANTHIUS, 33910, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Scaled Bracers
(@SEASON_3, @DORIS_VOLANTHIUS, 33911, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Scaled Greaves
(@SEASON_3, @DORIS_VOLANTHIUS, 33912, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Silk Belt
(@SEASON_3, @DORIS_VOLANTHIUS, 33913, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Silk Cuffs
(@SEASON_3, @DORIS_VOLANTHIUS, 33914, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Silk Footguards
(@SEASON_3, @DORIS_VOLANTHIUS, 33915, 0, 0, @COST_17850_HP_40_AB), -- Vindicator's Wyrmhide Belt
(@SEASON_3, @DORIS_VOLANTHIUS, 33916, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Vindicator's Wyrmhide Boots
(@SEASON_3, @DORIS_VOLANTHIUS, 33917, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Vindicator's Wyrmhide Bracers
(@SEASON_3, @DORIS_VOLANTHIUS, 33918, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Vindicator's Band of Salvation
(@SEASON_3, @DORIS_VOLANTHIUS, 33919, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Vindicator's Band of Triumph
(@SEASON_3, @DORIS_VOLANTHIUS, 33920, 0, 0, @COST_15300_HP_10_ES), -- Vindicator's Pendant of Conquest
(@SEASON_3, @DORIS_VOLANTHIUS, 33921, 0, 0, @COST_15300_HP_10_ES), -- Vindicator's Pendant of Dominance
(@SEASON_3, @DORIS_VOLANTHIUS, 33922, 0, 0, @COST_15300_HP_10_ES), -- Vindicator's Pendant of Salvation
(@SEASON_3, @DORIS_VOLANTHIUS, 33923, 0, 0, @COST_15300_HP_10_ES), -- Vindicator's Pendant of Triumph
(@SEASON_3, @DORIS_VOLANTHIUS, 35317, 0, 0, @COST_15300_HP_10_ES), -- Vindicator's Pendant of Reprieve
(@SEASON_3, @DORIS_VOLANTHIUS, 35319, 0, 0, @COST_15300_HP_10_ES), -- Vindicator's Pendant of Subjugation
(@SEASON_3, @DORIS_VOLANTHIUS, 35320, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Vindicator's Band of Subjugation
(@SEASON_3, @DORIS_VOLANTHIUS, 34576, 0, 0, @COST_30000_HP_40_AV), -- Battlemaster's Cruelty
(@SEASON_3, @DORIS_VOLANTHIUS, 34577, 0, 0, @COST_30000_HP_40_AV), -- Battlemaster's Depravity
(@SEASON_3, @DORIS_VOLANTHIUS, 34578, 0, 0, @COST_30000_HP_40_AV), -- Battlemaster's Determination
(@SEASON_3, @DORIS_VOLANTHIUS, 34579, 0, 0, @COST_30000_HP_40_AV), -- Battlemaster's Audacity
(@SEASON_3, @DORIS_VOLANTHIUS, 34580, 0, 0, @COST_30000_HP_40_AV); -- Battlemaster's Perseverance

# Season 4
DELETE FROM game_event_npc_vendor WHERE event = @SEASON_4;
INSERT INTO game_event_npc_vendor (event, guid, item, maxcount, incrtime, ExtendedCost) VALUES
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 30486, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Plate Chestpiece
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 30487, 0, 0, @COST_900_AP), -- Merciless Gladiator's Plate Gauntlets
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 30488, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Plate Helm
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 30489, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Plate Legguards
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 30490, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Plate Shoulders
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31960, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Chain Armor
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31961, 0, 0, @COST_900_AP), -- Merciless Gladiator's Chain Gauntlets
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31962, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Chain Helm
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31963, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Chain Leggings
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31964, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Chain Spaulders
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31967, 0, 0, @COST_900_AP), -- Merciless Gladiator's Dragonhide Gloves
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31968, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dragonhide Helm
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31969, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dragonhide Legguards
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31971, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Dragonhide Spaulders
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31972, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dragonhide Tunic
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31973, 0, 0, @COST_900_AP), -- Merciless Gladiator's Dreadweave Gloves
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31974, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dreadweave Hood
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31975, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dreadweave Leggings
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31976, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Dreadweave Mantle
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31977, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dreadweave Robe
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31979, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Felweave Amice
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31980, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Felweave Cowl
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31981, 0, 0, @COST_900_AP), -- Merciless Gladiator's Felweave Handguards
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31982, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Felweave Raiment
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31983, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Felweave Trousers
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31987, 0, 0, @COST_900_AP), -- Merciless Gladiator's Kodohide Gloves
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31988, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Kodohide Helm
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31989, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Kodohide Legguards
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31990, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Kodohide Spaulders
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31991, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Kodohide Tunic
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31992, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Lamellar Chestpiece
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31993, 0, 0, @COST_900_AP), -- Merciless Gladiator's Lamellar Gauntlets
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31995, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Lamellar Legguards
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31996, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Lamellar Shoulders
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31997, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Lamellar Helm
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31998, 0, 0, @COST_900_AP), -- Merciless Gladiator's Leather Gloves
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 31999, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Leather Helm
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32000, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Leather Legguards
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32001, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Leather Spaulders
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32002, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Leather Tunic
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32004, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Linked Armor
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32005, 0, 0, @COST_900_AP), -- Merciless Gladiator's Linked Gauntlets
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32006, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Linked Helm
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32007, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Linked Leggings
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32008, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Linked Spaulders
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32009, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mail Armor
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32010, 0, 0, @COST_900_AP), -- Merciless Gladiator's Mail Gauntlets
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32011, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mail Helm
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32012, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mail Leggings
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32013, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Mail Spaulders
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32014, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Maul
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32015, 0, 0, @COST_900_AP), -- Merciless Gladiator's Mooncloth Gloves
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32016, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mooncloth Hood
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32017, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mooncloth Leggings
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32018, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Mooncloth Mantle
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32019, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mooncloth Robe
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32020, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ornamented Chestguard
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32021, 0, 0, @COST_900_AP), -- Merciless Gladiator's Ornamented Gloves
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32022, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ornamented Headcover
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32023, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ornamented Legplates
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32024, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Ornamented Spaulders
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32029, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ringmail Armor
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32030, 0, 0, @COST_900_AP), -- Merciless Gladiator's Ringmail Gauntlets
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32031, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ringmail Helm
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32032, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ringmail Leggings
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32033, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Ringmail Spaulders
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32034, 0, 0, @COST_900_AP), -- Merciless Gladiator's Satin Gloves
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32035, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Satin Hood
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32036, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Satin Leggings
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32037, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Satin Mantle
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32038, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Satin Robe
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32039, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Scaled Chestpiece
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32040, 0, 0, @COST_900_AP), -- Merciless Gladiator's Scaled Gauntlets
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32041, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Scaled Helm
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32042, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Scaled Legguards
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32043, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Scaled Shoulders
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32047, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Silk Amice
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32048, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Silk Cowl
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32049, 0, 0, @COST_900_AP), -- Merciless Gladiator's Silk Handguards
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32050, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Silk Raiment
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32051, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Silk Trousers
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32056, 0, 0, @COST_900_AP), -- Merciless Gladiator's Wyrmhide Gloves
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32057, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Wyrmhide Helm
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32058, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Wyrmhide Legguards
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32059, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Wyrmhide Spaulders
(@SEASON_4, @CAPTAIN_DIRGEHAMMER, 32060, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Wyrmhide Tunic
(@SEASON_4, @CAPTAIN_ONEAL, 31958, 0, 0, @COST_900_AP), -- Merciless Gladiator's Bonecracker
(@SEASON_4, @CAPTAIN_ONEAL, 31959, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Bonegrinder
(@SEASON_4, @CAPTAIN_ONEAL, 31965, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Cleaver
(@SEASON_4, @CAPTAIN_ONEAL, 31966, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Decapitator
(@SEASON_4, @CAPTAIN_ONEAL, 31978, 0, 0, @COST_900_AP), -- Merciless Gladiator's Endgame
(@SEASON_4, @CAPTAIN_ONEAL, 31984, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Greatsword
(@SEASON_4, @CAPTAIN_ONEAL, 31985, 0, 0, @COST_900_AP), -- Merciless Gladiator's Hacker
(@SEASON_4, @CAPTAIN_ONEAL, 31986, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Crossbow of the Phoenix
(@SEASON_4, @CAPTAIN_ONEAL, 32003, 0, 0, @COST_900_AP), -- Merciless Gladiator's Left Ripper
(@SEASON_4, @CAPTAIN_ONEAL, 32025, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Painsaw
(@SEASON_4, @CAPTAIN_ONEAL, 32026, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Pummeler
(@SEASON_4, @CAPTAIN_ONEAL, 32027, 0, 0, @COST_900_AP), -- Merciless Gladiator's Quickblade
(@SEASON_4, @CAPTAIN_ONEAL, 32028, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Right Ripper
(@SEASON_4, @CAPTAIN_ONEAL, 32044, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Shanker
(@SEASON_4, @CAPTAIN_ONEAL, 32045, 0, 0, @COST_1500_AP_1800_R), -- Merciless Gladiator's Shield Wall
(@SEASON_4, @CAPTAIN_ONEAL, 32046, 0, 0, @COST_900_AP), -- Merciless Gladiator's Shiv
(@SEASON_4, @CAPTAIN_ONEAL, 32052, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Slicer
(@SEASON_4, @CAPTAIN_ONEAL, 32053, 0, 0, @COST_2520_AP_1800_R), -- Merciless Gladiator's Spellblade
(@SEASON_4, @CAPTAIN_ONEAL, 32054, 0, 0, @COST_800_AP), -- Merciless Gladiator's War Edge
(@SEASON_4, @CAPTAIN_ONEAL, 32055, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's War Staff
(@SEASON_4, @CAPTAIN_ONEAL, 32961, 0, 0, @COST_900_AP), -- Merciless Gladiator's Reprieve
(@SEASON_4, @CAPTAIN_ONEAL, 32962, 0, 0, @COST_800_AP), -- Merciless Gladiator's Touch of Defeat
(@SEASON_4, @CAPTAIN_ONEAL, 32963, 0, 0, @COST_2520_AP_1800_R), -- Merciless Gladiator's Gavel
(@SEASON_4, @CAPTAIN_ONEAL, 32964, 0, 0, @COST_2520_AP_1800_R), -- Merciless Gladiator's Salvation
(@SEASON_4, @CAPTAIN_ONEAL, 33076, 0, 0, @COST_800_AP), -- Merciless Gladiator's Idol of Tenacity
(@SEASON_4, @CAPTAIN_ONEAL, 33077, 0, 0, @COST_800_AP), -- Merciless Gladiator's Libram of Justice
(@SEASON_4, @CAPTAIN_ONEAL, 33078, 0, 0, @COST_800_AP), -- Merciless Gladiator's Totem of the Third Wind
(@SEASON_4, @CAPTAIN_ONEAL, 33309, 0, 0, @COST_1500_AP_1800_R), -- Merciless Gladiator's Redoubt
(@SEASON_4, @CAPTAIN_ONEAL, 33313, 0, 0, @COST_1500_AP_1800_R), -- Merciless Gladiator's Barrier
(@SEASON_4, @CAPTAIN_ONEAL, 33937, 0, 0, @COST_800_AP), -- Merciless Gladiator's Libram of Fortitude
(@SEASON_4, @CAPTAIN_ONEAL, 33940, 0, 0, @COST_800_AP), -- Merciless Gladiator's Totem of Indomitability
(@SEASON_4, @CAPTAIN_ONEAL, 33943, 0, 0, @COST_800_AP), -- Merciless Gladiator's Idol of Steadfastness
(@SEASON_4, @CAPTAIN_ONEAL, 33946, 0, 0, @COST_800_AP), -- Merciless Gladiator's Idol of Resolve
(@SEASON_4, @CAPTAIN_ONEAL, 33949, 0, 0, @COST_800_AP), -- Merciless Gladiator's Libram of Vengeance
(@SEASON_4, @CAPTAIN_ONEAL, 33952, 0, 0, @COST_800_AP), -- Merciless Gladiator's Totem of Survival
(@SEASON_4, @LADY_PALANSEER, 30486, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Plate Chestpiece
(@SEASON_4, @LADY_PALANSEER, 30487, 0, 0, @COST_900_AP), -- Merciless Gladiator's Plate Gauntlets
(@SEASON_4, @LADY_PALANSEER, 30488, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Plate Helm
(@SEASON_4, @LADY_PALANSEER, 30489, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Plate Legguards
(@SEASON_4, @LADY_PALANSEER, 30490, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Plate Shoulders
(@SEASON_4, @LADY_PALANSEER, 31960, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Chain Armor
(@SEASON_4, @LADY_PALANSEER, 31961, 0, 0, @COST_900_AP), -- Merciless Gladiator's Chain Gauntlets
(@SEASON_4, @LADY_PALANSEER, 31962, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Chain Helm
(@SEASON_4, @LADY_PALANSEER, 31963, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Chain Leggings
(@SEASON_4, @LADY_PALANSEER, 31964, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Chain Spaulders
(@SEASON_4, @LADY_PALANSEER, 31967, 0, 0, @COST_900_AP), -- Merciless Gladiator's Dragonhide Gloves
(@SEASON_4, @LADY_PALANSEER, 31968, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dragonhide Helm
(@SEASON_4, @LADY_PALANSEER, 31969, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dragonhide Legguards
(@SEASON_4, @LADY_PALANSEER, 31971, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Dragonhide Spaulders
(@SEASON_4, @LADY_PALANSEER, 31972, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dragonhide Tunic
(@SEASON_4, @LADY_PALANSEER, 31973, 0, 0, @COST_900_AP), -- Merciless Gladiator's Dreadweave Gloves
(@SEASON_4, @LADY_PALANSEER, 31974, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dreadweave Hood
(@SEASON_4, @LADY_PALANSEER, 31975, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dreadweave Leggings
(@SEASON_4, @LADY_PALANSEER, 31976, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Dreadweave Mantle
(@SEASON_4, @LADY_PALANSEER, 31977, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Dreadweave Robe
(@SEASON_4, @LADY_PALANSEER, 31979, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Felweave Amice
(@SEASON_4, @LADY_PALANSEER, 31980, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Felweave Cowl
(@SEASON_4, @LADY_PALANSEER, 31981, 0, 0, @COST_900_AP), -- Merciless Gladiator's Felweave Handguards
(@SEASON_4, @LADY_PALANSEER, 31982, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Felweave Raiment
(@SEASON_4, @LADY_PALANSEER, 31983, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Felweave Trousers
(@SEASON_4, @LADY_PALANSEER, 31987, 0, 0, @COST_900_AP), -- Merciless Gladiator's Kodohide Gloves
(@SEASON_4, @LADY_PALANSEER, 31988, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Kodohide Helm
(@SEASON_4, @LADY_PALANSEER, 31989, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Kodohide Legguards
(@SEASON_4, @LADY_PALANSEER, 31990, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Kodohide Spaulders
(@SEASON_4, @LADY_PALANSEER, 31991, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Kodohide Tunic
(@SEASON_4, @LADY_PALANSEER, 31992, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Lamellar Chestpiece
(@SEASON_4, @LADY_PALANSEER, 31993, 0, 0, @COST_900_AP), -- Merciless Gladiator's Lamellar Gauntlets
(@SEASON_4, @LADY_PALANSEER, 31995, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Lamellar Legguards
(@SEASON_4, @LADY_PALANSEER, 31996, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Lamellar Shoulders
(@SEASON_4, @LADY_PALANSEER, 31997, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Lamellar Helm
(@SEASON_4, @LADY_PALANSEER, 31998, 0, 0, @COST_900_AP), -- Merciless Gladiator's Leather Gloves
(@SEASON_4, @LADY_PALANSEER, 31999, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Leather Helm
(@SEASON_4, @LADY_PALANSEER, 32000, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Leather Legguards
(@SEASON_4, @LADY_PALANSEER, 32001, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Leather Spaulders
(@SEASON_4, @LADY_PALANSEER, 32002, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Leather Tunic
(@SEASON_4, @LADY_PALANSEER, 32004, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Linked Armor
(@SEASON_4, @LADY_PALANSEER, 32005, 0, 0, @COST_900_AP), -- Merciless Gladiator's Linked Gauntlets
(@SEASON_4, @LADY_PALANSEER, 32006, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Linked Helm
(@SEASON_4, @LADY_PALANSEER, 32007, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Linked Leggings
(@SEASON_4, @LADY_PALANSEER, 32008, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Linked Spaulders
(@SEASON_4, @LADY_PALANSEER, 32009, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mail Armor
(@SEASON_4, @LADY_PALANSEER, 32010, 0, 0, @COST_900_AP), -- Merciless Gladiator's Mail Gauntlets
(@SEASON_4, @LADY_PALANSEER, 32011, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mail Helm
(@SEASON_4, @LADY_PALANSEER, 32012, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mail Leggings
(@SEASON_4, @LADY_PALANSEER, 32013, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Mail Spaulders
(@SEASON_4, @LADY_PALANSEER, 32014, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Maul
(@SEASON_4, @LADY_PALANSEER, 32015, 0, 0, @COST_900_AP), -- Merciless Gladiator's Mooncloth Gloves
(@SEASON_4, @LADY_PALANSEER, 32016, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mooncloth Hood
(@SEASON_4, @LADY_PALANSEER, 32017, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mooncloth Leggings
(@SEASON_4, @LADY_PALANSEER, 32018, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Mooncloth Mantle
(@SEASON_4, @LADY_PALANSEER, 32019, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Mooncloth Robe
(@SEASON_4, @LADY_PALANSEER, 32020, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ornamented Chestguard
(@SEASON_4, @LADY_PALANSEER, 32021, 0, 0, @COST_900_AP), -- Merciless Gladiator's Ornamented Gloves
(@SEASON_4, @LADY_PALANSEER, 32022, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ornamented Headcover
(@SEASON_4, @LADY_PALANSEER, 32023, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ornamented Legplates
(@SEASON_4, @LADY_PALANSEER, 32024, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Ornamented Spaulders
(@SEASON_4, @LADY_PALANSEER, 32029, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ringmail Armor
(@SEASON_4, @LADY_PALANSEER, 32030, 0, 0, @COST_900_AP), -- Merciless Gladiator's Ringmail Gauntlets
(@SEASON_4, @LADY_PALANSEER, 32031, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ringmail Helm
(@SEASON_4, @LADY_PALANSEER, 32032, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Ringmail Leggings
(@SEASON_4, @LADY_PALANSEER, 32033, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Ringmail Spaulders
(@SEASON_4, @LADY_PALANSEER, 32034, 0, 0, @COST_900_AP), -- Merciless Gladiator's Satin Gloves
(@SEASON_4, @LADY_PALANSEER, 32035, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Satin Hood
(@SEASON_4, @LADY_PALANSEER, 32036, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Satin Leggings
(@SEASON_4, @LADY_PALANSEER, 32037, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Satin Mantle
(@SEASON_4, @LADY_PALANSEER, 32038, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Satin Robe
(@SEASON_4, @LADY_PALANSEER, 32039, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Scaled Chestpiece
(@SEASON_4, @LADY_PALANSEER, 32040, 0, 0, @COST_900_AP), -- Merciless Gladiator's Scaled Gauntlets
(@SEASON_4, @LADY_PALANSEER, 32041, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Scaled Helm
(@SEASON_4, @LADY_PALANSEER, 32042, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Scaled Legguards
(@SEASON_4, @LADY_PALANSEER, 32043, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Scaled Shoulders
(@SEASON_4, @LADY_PALANSEER, 32047, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Silk Amice
(@SEASON_4, @LADY_PALANSEER, 32048, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Silk Cowl
(@SEASON_4, @LADY_PALANSEER, 32049, 0, 0, @COST_900_AP), -- Merciless Gladiator's Silk Handguards
(@SEASON_4, @LADY_PALANSEER, 32050, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Silk Raiment
(@SEASON_4, @LADY_PALANSEER, 32051, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Silk Trousers
(@SEASON_4, @LADY_PALANSEER, 32056, 0, 0, @COST_900_AP), -- Merciless Gladiator's Wyrmhide Gloves
(@SEASON_4, @LADY_PALANSEER, 32057, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Wyrmhide Helm
(@SEASON_4, @LADY_PALANSEER, 32058, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Wyrmhide Legguards
(@SEASON_4, @LADY_PALANSEER, 32059, 0, 0, @COST_1200_AP_1950_R), -- Merciless Gladiator's Wyrmhide Spaulders
(@SEASON_4, @LADY_PALANSEER, 32060, 0, 0, @COST_1500_AP), -- Merciless Gladiator's Wyrmhide Tunic
(@SEASON_4, @SERGEANT_THUNDERHORN, 31958, 0, 0, @COST_900_AP), -- Merciless Gladiator's Bonecracker
(@SEASON_4, @SERGEANT_THUNDERHORN, 31959, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Bonegrinder
(@SEASON_4, @SERGEANT_THUNDERHORN, 31965, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Cleaver
(@SEASON_4, @SERGEANT_THUNDERHORN, 31966, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Decapitator
(@SEASON_4, @SERGEANT_THUNDERHORN, 31978, 0, 0, @COST_900_AP), -- Merciless Gladiator's Endgame
(@SEASON_4, @SERGEANT_THUNDERHORN, 31984, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Greatsword
(@SEASON_4, @SERGEANT_THUNDERHORN, 31985, 0, 0, @COST_900_AP), -- Merciless Gladiator's Hacker
(@SEASON_4, @SERGEANT_THUNDERHORN, 31986, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Crossbow of the Phoenix
(@SEASON_4, @SERGEANT_THUNDERHORN, 32003, 0, 0, @COST_900_AP), -- Merciless Gladiator's Left Ripper
(@SEASON_4, @SERGEANT_THUNDERHORN, 32025, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's Painsaw
(@SEASON_4, @SERGEANT_THUNDERHORN, 32026, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Pummeler
(@SEASON_4, @SERGEANT_THUNDERHORN, 32027, 0, 0, @COST_900_AP), -- Merciless Gladiator's Quickblade
(@SEASON_4, @SERGEANT_THUNDERHORN, 32028, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Right Ripper
(@SEASON_4, @SERGEANT_THUNDERHORN, 32044, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Shanker
(@SEASON_4, @SERGEANT_THUNDERHORN, 32045, 0, 0, @COST_1500_AP_1800_R), -- Merciless Gladiator's Shield Wall
(@SEASON_4, @SERGEANT_THUNDERHORN, 32046, 0, 0, @COST_900_AP), -- Merciless Gladiator's Shiv
(@SEASON_4, @SERGEANT_THUNDERHORN, 32052, 0, 0, @COST_2100_AP_1800_R), -- Merciless Gladiator's Slicer
(@SEASON_4, @SERGEANT_THUNDERHORN, 32053, 0, 0, @COST_2520_AP_1800_R), -- Merciless Gladiator's Spellblade
(@SEASON_4, @SERGEANT_THUNDERHORN, 32054, 0, 0, @COST_800_AP), -- Merciless Gladiator's War Edge
(@SEASON_4, @SERGEANT_THUNDERHORN, 32055, 0, 0, @COST_3000_AP_1800_R), -- Merciless Gladiator's War Staff
(@SEASON_4, @SERGEANT_THUNDERHORN, 32961, 0, 0, @COST_900_AP), -- Merciless Gladiator's Reprieve
(@SEASON_4, @SERGEANT_THUNDERHORN, 32962, 0, 0, @COST_800_AP), -- Merciless Gladiator's Touch of Defeat
(@SEASON_4, @SERGEANT_THUNDERHORN, 32963, 0, 0, @COST_2520_AP_1800_R), -- Merciless Gladiator's Gavel
(@SEASON_4, @SERGEANT_THUNDERHORN, 32964, 0, 0, @COST_2520_AP_1800_R), -- Merciless Gladiator's Salvation
(@SEASON_4, @SERGEANT_THUNDERHORN, 33076, 0, 0, @COST_800_AP), -- Merciless Gladiator's Idol of Tenacity
(@SEASON_4, @SERGEANT_THUNDERHORN, 33077, 0, 0, @COST_800_AP), -- Merciless Gladiator's Libram of Justice
(@SEASON_4, @SERGEANT_THUNDERHORN, 33078, 0, 0, @COST_800_AP), -- Merciless Gladiator's Totem of the Third Wind
(@SEASON_4, @SERGEANT_THUNDERHORN, 33309, 0, 0, @COST_1500_AP_1800_R), -- Merciless Gladiator's Redoubt
(@SEASON_4, @SERGEANT_THUNDERHORN, 33313, 0, 0, @COST_1500_AP_1800_R), -- Merciless Gladiator's Barrier
(@SEASON_4, @SERGEANT_THUNDERHORN, 33937, 0, 0, @COST_800_AP), -- Merciless Gladiator's Libram of Fortitude
(@SEASON_4, @SERGEANT_THUNDERHORN, 33940, 0, 0, @COST_800_AP), -- Merciless Gladiator's Totem of Indomitability
(@SEASON_4, @SERGEANT_THUNDERHORN, 33943, 0, 0, @COST_800_AP), -- Merciless Gladiator's Idol of Steadfastness
(@SEASON_4, @SERGEANT_THUNDERHORN, 33946, 0, 0, @COST_800_AP), -- Merciless Gladiator's Idol of Resolve
(@SEASON_4, @SERGEANT_THUNDERHORN, 33949, 0, 0, @COST_800_AP), -- Merciless Gladiator's Libram of Vengeance
(@SEASON_4, @SERGEANT_THUNDERHORN, 33952, 0, 0, @COST_800_AP), -- Merciless Gladiator's Totem of Survival
(@SEASON_4, @LIEUTENANT_TRISTIA, 33853, 0, 0, @COST_11934_HP_10_AV), -- Vindicator's Band of Dominance
(@SEASON_4, @LIEUTENANT_TRISTIA, 33918, 0, 0, @COST_11934_HP_10_AV), -- Vindicator's Band of Salvation
(@SEASON_4, @LIEUTENANT_TRISTIA, 33919, 0, 0, @COST_11934_HP_10_AV), -- Vindicator's Band of Triumph
(@SEASON_4, @LIEUTENANT_TRISTIA, 35129, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Guardian's Band of Dominance
(@SEASON_4, @LIEUTENANT_TRISTIA, 35130, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Guardian's Band of Salvation
(@SEASON_4, @LIEUTENANT_TRISTIA, 35131, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Guardian's Band of Triumph
(@SEASON_4, @LIEUTENANT_TRISTIA, 35132, 0, 0, @COST_15300_HP_10_ES), -- Guardian's Pendant of Conquest
(@SEASON_4, @LIEUTENANT_TRISTIA, 35133, 0, 0, @COST_15300_HP_10_ES), -- Guardian's Pendant of Dominance
(@SEASON_4, @LIEUTENANT_TRISTIA, 35134, 0, 0, @COST_15300_HP_10_ES), -- Guardian's Pendant of Salvation
(@SEASON_4, @LIEUTENANT_TRISTIA, 35135, 0, 0, @COST_15300_HP_10_ES), -- Guardian's Pendant of Triumph
(@SEASON_4, @LIEUTENANT_TRISTIA, 35136, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Chain Sabatons
(@SEASON_4, @LIEUTENANT_TRISTIA, 35137, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Dragonhide Boots
(@SEASON_4, @LIEUTENANT_TRISTIA, 35138, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Dreadweave Stalkers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35139, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Kodohide Boots
(@SEASON_4, @LIEUTENANT_TRISTIA, 35140, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Lamellar Greaves
(@SEASON_4, @LIEUTENANT_TRISTIA, 35141, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Leather Boots
(@SEASON_4, @LIEUTENANT_TRISTIA, 35142, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Linked Sabatons
(@SEASON_4, @LIEUTENANT_TRISTIA, 35143, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Mail Sabatons
(@SEASON_4, @LIEUTENANT_TRISTIA, 35144, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Mooncloth Slippers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35145, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Ornamented Greaves
(@SEASON_4, @LIEUTENANT_TRISTIA, 35146, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Plate Greaves
(@SEASON_4, @LIEUTENANT_TRISTIA, 35147, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Ringmail Sabatons
(@SEASON_4, @LIEUTENANT_TRISTIA, 35148, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Scaled Greaves
(@SEASON_4, @LIEUTENANT_TRISTIA, 35149, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Silk Footguards
(@SEASON_4, @LIEUTENANT_TRISTIA, 35150, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Wyrmhide Boots
(@SEASON_4, @LIEUTENANT_TRISTIA, 35151, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Chain Girdle
(@SEASON_4, @LIEUTENANT_TRISTIA, 35152, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Dragonhide Belt
(@SEASON_4, @LIEUTENANT_TRISTIA, 35153, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Dreadweave Belt
(@SEASON_4, @LIEUTENANT_TRISTIA, 35154, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Kodohide Belt
(@SEASON_4, @LIEUTENANT_TRISTIA, 35155, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Lamellar Belt
(@SEASON_4, @LIEUTENANT_TRISTIA, 35156, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Leather Belt
(@SEASON_4, @LIEUTENANT_TRISTIA, 35157, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Linked Girdle
(@SEASON_4, @LIEUTENANT_TRISTIA, 35158, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Mail Girdle
(@SEASON_4, @LIEUTENANT_TRISTIA, 35159, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Mooncloth Belt
(@SEASON_4, @LIEUTENANT_TRISTIA, 35160, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Ornamented Belt
(@SEASON_4, @LIEUTENANT_TRISTIA, 35161, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Plate Belt
(@SEASON_4, @LIEUTENANT_TRISTIA, 35162, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Ringmail Girdle
(@SEASON_4, @LIEUTENANT_TRISTIA, 35163, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Scaled Belt
(@SEASON_4, @LIEUTENANT_TRISTIA, 35164, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Silk Belt
(@SEASON_4, @LIEUTENANT_TRISTIA, 35165, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Wyrmhide Belt
(@SEASON_4, @LIEUTENANT_TRISTIA, 35166, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Chain Bracers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35167, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Dragonhide Bracers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35168, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Dreadweave Cuffs
(@SEASON_4, @LIEUTENANT_TRISTIA, 35169, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Kodohide Bracers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35170, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Lamellar Bracers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35171, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Leather Bracers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35172, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Linked Bracers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35173, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Mail Bracers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35174, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Mooncloth Cuffs
(@SEASON_4, @LIEUTENANT_TRISTIA, 35175, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Ornamented Bracers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35176, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Plate Bracers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35177, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Ringmail Bracers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35178, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Scaled Bracers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35179, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Silk Cuffs
(@SEASON_4, @LIEUTENANT_TRISTIA, 35180, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Wyrmhide Bracers
(@SEASON_4, @LIEUTENANT_TRISTIA, 35317, 0, 0, @COST_11934_HP_10_ES), -- Vindicator's Pendant of Reprieve
(@SEASON_4, @LIEUTENANT_TRISTIA, 35319, 0, 0, @COST_11934_HP_10_ES), -- Vindicator's Pendant of Subjugation
(@SEASON_4, @LIEUTENANT_TRISTIA, 35320, 0, 0, @COST_11934_HP_10_AV), -- Vindicator's Band of Subjugation
(@SEASON_4, @LIEUTENANT_TRISTIA, 37927, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Guardian's Band of Subjugation
(@SEASON_4, @LIEUTENANT_TRISTIA, 37928, 0, 0, @COST_15300_HP_10_ES), -- Guardian's Pendant of Subjugation
(@SEASON_4, @LIEUTENANT_TRISTIA, 37929, 0, 0, @COST_15300_HP_10_ES), -- Guardian's Pendant of Reprieve
(@SEASON_4, @DORIS_VOLANTHIUS, 33853, 0, 0, @COST_11934_HP_10_AV), -- Vindicator's Band of Dominance
(@SEASON_4, @DORIS_VOLANTHIUS, 33918, 0, 0, @COST_11934_HP_10_AV), -- Vindicator's Band of Salvation
(@SEASON_4, @DORIS_VOLANTHIUS, 33919, 0, 0, @COST_11934_HP_10_AV), -- Vindicator's Band of Triumph
(@SEASON_4, @DORIS_VOLANTHIUS, 35129, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Guardian's Band of Dominance
(@SEASON_4, @DORIS_VOLANTHIUS, 35130, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Guardian's Band of Salvation
(@SEASON_4, @DORIS_VOLANTHIUS, 35131, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Guardian's Band of Triumph
(@SEASON_4, @DORIS_VOLANTHIUS, 35132, 0, 0, @COST_15300_HP_10_ES), -- Guardian's Pendant of Conquest
(@SEASON_4, @DORIS_VOLANTHIUS, 35133, 0, 0, @COST_15300_HP_10_ES), -- Guardian's Pendant of Dominance
(@SEASON_4, @DORIS_VOLANTHIUS, 35134, 0, 0, @COST_15300_HP_10_ES), -- Guardian's Pendant of Salvation
(@SEASON_4, @DORIS_VOLANTHIUS, 35135, 0, 0, @COST_15300_HP_10_ES), -- Guardian's Pendant of Triumph
(@SEASON_4, @DORIS_VOLANTHIUS, 35136, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Chain Sabatons
(@SEASON_4, @DORIS_VOLANTHIUS, 35137, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Dragonhide Boots
(@SEASON_4, @DORIS_VOLANTHIUS, 35138, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Dreadweave Stalkers
(@SEASON_4, @DORIS_VOLANTHIUS, 35139, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Kodohide Boots
(@SEASON_4, @DORIS_VOLANTHIUS, 35140, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Lamellar Greaves
(@SEASON_4, @DORIS_VOLANTHIUS, 35141, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Leather Boots
(@SEASON_4, @DORIS_VOLANTHIUS, 35142, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Linked Sabatons
(@SEASON_4, @DORIS_VOLANTHIUS, 35143, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Mail Sabatons
(@SEASON_4, @DORIS_VOLANTHIUS, 35144, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Mooncloth Slippers
(@SEASON_4, @DORIS_VOLANTHIUS, 35145, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Ornamented Greaves
(@SEASON_4, @DORIS_VOLANTHIUS, 35146, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Plate Greaves
(@SEASON_4, @DORIS_VOLANTHIUS, 35147, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Ringmail Sabatons
(@SEASON_4, @DORIS_VOLANTHIUS, 35148, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Scaled Greaves
(@SEASON_4, @DORIS_VOLANTHIUS, 35149, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Silk Footguards
(@SEASON_4, @DORIS_VOLANTHIUS, 35150, 0, 0, @COST_17850_HP_40_ES_1700_R), -- Guardian's Wyrmhide Boots
(@SEASON_4, @DORIS_VOLANTHIUS, 35151, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Chain Girdle
(@SEASON_4, @DORIS_VOLANTHIUS, 35152, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Dragonhide Belt
(@SEASON_4, @DORIS_VOLANTHIUS, 35153, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Dreadweave Belt
(@SEASON_4, @DORIS_VOLANTHIUS, 35154, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Kodohide Belt
(@SEASON_4, @DORIS_VOLANTHIUS, 35155, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Lamellar Belt
(@SEASON_4, @DORIS_VOLANTHIUS, 35156, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Leather Belt
(@SEASON_4, @DORIS_VOLANTHIUS, 35157, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Linked Girdle
(@SEASON_4, @DORIS_VOLANTHIUS, 35158, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Mail Girdle
(@SEASON_4, @DORIS_VOLANTHIUS, 35159, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Mooncloth Belt
(@SEASON_4, @DORIS_VOLANTHIUS, 35160, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Ornamented Belt
(@SEASON_4, @DORIS_VOLANTHIUS, 35161, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Plate Belt
(@SEASON_4, @DORIS_VOLANTHIUS, 35162, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Ringmail Girdle
(@SEASON_4, @DORIS_VOLANTHIUS, 35163, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Scaled Belt
(@SEASON_4, @DORIS_VOLANTHIUS, 35164, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Silk Belt
(@SEASON_4, @DORIS_VOLANTHIUS, 35165, 0, 0, @COST_17850_HP_40_AB), -- Guardian's Wyrmhide Belt
(@SEASON_4, @DORIS_VOLANTHIUS, 35166, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Chain Bracers
(@SEASON_4, @DORIS_VOLANTHIUS, 35167, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Dragonhide Bracers
(@SEASON_4, @DORIS_VOLANTHIUS, 35168, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Dreadweave Cuffs
(@SEASON_4, @DORIS_VOLANTHIUS, 35169, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Kodohide Bracers
(@SEASON_4, @DORIS_VOLANTHIUS, 35170, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Lamellar Bracers
(@SEASON_4, @DORIS_VOLANTHIUS, 35171, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Leather Bracers
(@SEASON_4, @DORIS_VOLANTHIUS, 35172, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Linked Bracers
(@SEASON_4, @DORIS_VOLANTHIUS, 35173, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Mail Bracers
(@SEASON_4, @DORIS_VOLANTHIUS, 35174, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Mooncloth Cuffs
(@SEASON_4, @DORIS_VOLANTHIUS, 35175, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Ornamented Bracers
(@SEASON_4, @DORIS_VOLANTHIUS, 35176, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Plate Bracers
(@SEASON_4, @DORIS_VOLANTHIUS, 35177, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Ringmail Bracers
(@SEASON_4, @DORIS_VOLANTHIUS, 35178, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Scaled Bracers
(@SEASON_4, @DORIS_VOLANTHIUS, 35179, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Silk Cuffs
(@SEASON_4, @DORIS_VOLANTHIUS, 35180, 0, 0, @COST_11794_HP_20_WSG_1600_R), -- Guardian's Wyrmhide Bracers
(@SEASON_4, @DORIS_VOLANTHIUS, 35317, 0, 0, @COST_11934_HP_10_ES), -- Vindicator's Pendant of Reprieve
(@SEASON_4, @DORIS_VOLANTHIUS, 35319, 0, 0, @COST_11934_HP_10_ES), -- Vindicator's Pendant of Subjugation
(@SEASON_4, @DORIS_VOLANTHIUS, 35320, 0, 0, @COST_11934_HP_10_AV), -- Vindicator's Band of Subjugation
(@SEASON_4, @DORIS_VOLANTHIUS, 37927, 0, 0, @COST_15300_HP_10_AV_1650_R), -- Guardian's Band of Subjugation
(@SEASON_4, @DORIS_VOLANTHIUS, 37928, 0, 0, @COST_15300_HP_10_ES), -- Guardian's Pendant of Subjugation
(@SEASON_4, @DORIS_VOLANTHIUS, 37929, 0, 0, @COST_15300_HP_10_ES), -- Guardian's Pendant of Reprieve
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33006, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Heavy Crossbow
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33661, 0, 0, @COST_1500_AP_1800_R), -- Vengeful Gladiator's Barrier
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33662, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Bonecracker
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33663, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Bonegrinder
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33664, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Chain Armor
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33665, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Chain Gauntlets
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33666, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Chain Helm
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33667, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Chain Leggings
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33668, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Chain Spaulders
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33669, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Cleaver
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33670, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Decapitator
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33671, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Dragonhide Gloves
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33672, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dragonhide Helm
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33673, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dragonhide Legguards
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33674, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Dragonhide Spaulders
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33675, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dragonhide Tunic
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33676, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Dreadweave Gloves
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33677, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dreadweave Hood
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33678, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dreadweave Leggings
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33679, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Dreadweave Mantle
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33680, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dreadweave Robe
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33681, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Endgame
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33682, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Felweave Amice
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33683, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Felweave Cowl
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33684, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Felweave Handguards
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33685, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Felweave Raiment
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33686, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Felweave Trousers
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33687, 0, 0, @COST_2520_AP_1800_R), -- Vengeful Gladiator's Gavel
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33688, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Greatsword
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33689, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Hacker
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33690, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Kodohide Gloves
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33691, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Kodohide Helm
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33692, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Kodohide Legguards
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33693, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Kodohide Spaulders
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33694, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Kodohide Tunic
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33695, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Lamellar Chestpiece
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33696, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Lamellar Gauntlets
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33697, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Lamellar Helm
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33698, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Lamellar Legguards
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33699, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Lamellar Shoulders
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33700, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Leather Gloves
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33701, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Leather Helm
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33702, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Leather Legguards
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33703, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Leather Spaulders
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33704, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Leather Tunic
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33705, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Left Ripper
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33706, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Linked Armor
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33707, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Linked Gauntlets
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33708, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Linked Helm
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33709, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Linked Leggings
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33710, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Linked Spaulders
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33711, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mail Armor
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33712, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Mail Gauntlets
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33713, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mail Helm
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33714, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mail Leggings
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33715, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Mail Spaulders
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33716, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Staff
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33717, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Mooncloth Gloves
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33718, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mooncloth Hood
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33719, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mooncloth Leggings
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33720, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Mooncloth Mantle
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33721, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mooncloth Robe
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33722, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ornamented Chestguard
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33723, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Ornamented Gloves
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33724, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ornamented Headcover
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33725, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ornamented Legplates
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33726, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Ornamented Spaulders
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33727, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Painsaw
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33728, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Plate Chestpiece
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33729, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Plate Gauntlets
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33730, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Plate Helm
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33731, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Plate Legguards
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33732, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Plate Shoulders
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33733, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Pummeler
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33734, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Quickblade
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33735, 0, 0, @COST_1500_AP_1800_R), -- Vengeful Gladiator's Redoubt
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33736, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Reprieve
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33737, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Right Ripper
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33738, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ringmail Armor
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33739, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Ringmail Gauntlets
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33740, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ringmail Helm
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33741, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ringmail Leggings
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33742, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Ringmail Spaulders
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33743, 0, 0, @COST_2520_AP_1800_R), -- Vengeful Gladiator's Salvation
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33744, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Satin Gloves
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33745, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Satin Hood
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33746, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Satin Leggings
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33747, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Satin Mantle
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33748, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Satin Robe
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33749, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Scaled Chestpiece
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33750, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Scaled Gauntlets
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33751, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Scaled Helm
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33752, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Scaled Legguards
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33753, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Scaled Shoulders
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33754, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Shanker
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33755, 0, 0, @COST_1500_AP_1800_R), -- Vengeful Gladiator's Shield Wall
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33756, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Shiv
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33757, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Silk Amice
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33758, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Silk Cowl
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33759, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Silk Handguards
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33760, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Silk Raiment
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33761, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Silk Trousers
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33762, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Slicer
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33763, 0, 0, @COST_2520_AP_1800_R), -- Vengeful Gladiator's Spellblade
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33764, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Touch of Defeat
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33765, 0, 0, @COST_800_AP), -- Vengeful Gladiator's War Edge
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33766, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's War Staff
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33767, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Wyrmhide Gloves
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33768, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Wyrmhide Helm
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33769, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Wyrmhide Legguards
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33770, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Wyrmhide Spaulders
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33771, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Wyrmhide Tunic
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33801, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Mutilator
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33841, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Idol of Tenacity
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33842, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Libram of Justice
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33843, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Totem of the Third Wind
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33938, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Libram of Fortitude
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33941, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Totem of Indomitability
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33944, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Idol of Steadfastness
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33947, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Idol of Resolve
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33950, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Libram of Vengeance
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 33953, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Totem of Survival
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 34014, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Waraxe
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 34015, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Chopper
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 34016, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Left Render
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 34033, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Grimoire
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 34059, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Baton of Light
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 34066, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Piercing Touch
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 34529, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Longbow
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 34530, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Rifle
(@SEASON_4, @LEENIE_SMILEY_SMALLS, 34540, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Battle Staff
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33006, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Heavy Crossbow
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33661, 0, 0, @COST_1500_AP_1800_R), -- Vengeful Gladiator's Barrier
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33662, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Bonecracker
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33663, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Bonegrinder
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33664, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Chain Armor
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33665, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Chain Gauntlets
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33666, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Chain Helm
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33667, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Chain Leggings
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33668, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Chain Spaulders
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33669, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Cleaver
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33670, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Decapitator
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33671, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Dragonhide Gloves
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33672, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dragonhide Helm
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33673, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dragonhide Legguards
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33674, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Dragonhide Spaulders
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33675, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dragonhide Tunic
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33676, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Dreadweave Gloves
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33677, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dreadweave Hood
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33678, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dreadweave Leggings
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33679, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Dreadweave Mantle
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33680, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dreadweave Robe
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33681, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Endgame
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33682, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Felweave Amice
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33683, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Felweave Cowl
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33684, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Felweave Handguards
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33685, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Felweave Raiment
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33686, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Felweave Trousers
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33687, 0, 0, @COST_2520_AP_1800_R), -- Vengeful Gladiator's Gavel
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33688, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Greatsword
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33689, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Hacker
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33690, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Kodohide Gloves
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33691, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Kodohide Helm
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33692, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Kodohide Legguards
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33693, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Kodohide Spaulders
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33694, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Kodohide Tunic
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33695, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Lamellar Chestpiece
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33696, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Lamellar Gauntlets
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33697, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Lamellar Helm
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33698, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Lamellar Legguards
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33699, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Lamellar Shoulders
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33700, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Leather Gloves
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33701, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Leather Helm
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33702, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Leather Legguards
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33703, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Leather Spaulders
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33704, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Leather Tunic
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33705, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Left Ripper
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33706, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Linked Armor
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33707, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Linked Gauntlets
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33708, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Linked Helm
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33709, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Linked Leggings
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33710, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Linked Spaulders
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33711, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mail Armor
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33712, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Mail Gauntlets
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33713, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mail Helm
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33714, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mail Leggings
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33715, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Mail Spaulders
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33716, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Staff
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33717, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Mooncloth Gloves
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33718, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mooncloth Hood
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33719, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mooncloth Leggings
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33720, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Mooncloth Mantle
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33721, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mooncloth Robe
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33722, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ornamented Chestguard
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33723, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Ornamented Gloves
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33724, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ornamented Headcover
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33725, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ornamented Legplates
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33726, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Ornamented Spaulders
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33727, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Painsaw
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33728, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Plate Chestpiece
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33729, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Plate Gauntlets
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33730, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Plate Helm
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33731, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Plate Legguards
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33732, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Plate Shoulders
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33733, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Pummeler
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33734, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Quickblade
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33735, 0, 0, @COST_1500_AP_1800_R), -- Vengeful Gladiator's Redoubt
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33736, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Reprieve
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33737, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Right Ripper
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33738, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ringmail Armor
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33739, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Ringmail Gauntlets
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33740, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ringmail Helm
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33741, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ringmail Leggings
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33742, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Ringmail Spaulders
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33743, 0, 0, @COST_2520_AP_1800_R), -- Vengeful Gladiator's Salvation
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33744, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Satin Gloves
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33745, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Satin Hood
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33746, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Satin Leggings
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33747, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Satin Mantle
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33748, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Satin Robe
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33749, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Scaled Chestpiece
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33750, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Scaled Gauntlets
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33751, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Scaled Helm
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33752, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Scaled Legguards
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33753, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Scaled Shoulders
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33754, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Shanker
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33755, 0, 0, @COST_1500_AP_1800_R), -- Vengeful Gladiator's Shield Wall
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33756, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Shiv
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33757, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Silk Amice
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33758, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Silk Cowl
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33759, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Silk Handguards
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33760, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Silk Raiment
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33761, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Silk Trousers
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33762, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Slicer
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33763, 0, 0, @COST_2520_AP_1800_R), -- Vengeful Gladiator's Spellblade
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33764, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Touch of Defeat
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33765, 0, 0, @COST_800_AP), -- Vengeful Gladiator's War Edge
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33766, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's War Staff
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33767, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Wyrmhide Gloves
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33768, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Wyrmhide Helm
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33769, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Wyrmhide Legguards
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33770, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Wyrmhide Spaulders
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33771, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Wyrmhide Tunic
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33801, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Mutilator
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33841, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Idol of Tenacity
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33842, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Libram of Justice
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33843, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Totem of the Third Wind
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33938, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Libram of Fortitude
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33941, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Totem of Indomitability
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33944, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Idol of Steadfastness
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33947, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Idol of Resolve
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33950, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Libram of Vengeance
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 33953, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Totem of Survival
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 34014, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Waraxe
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 34015, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Chopper
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 34016, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Left Render
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 34033, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Grimoire
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 34059, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Baton of Light
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 34066, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Piercing Touch
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 34529, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Longbow
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 34530, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Rifle
(@SEASON_4, @EXPLODYNE_FIZZLESPURT, 34540, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Battle Staff
(@SEASON_4, @ECTON_BRASSTUMBLER, 33006, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Heavy Crossbow
(@SEASON_4, @ECTON_BRASSTUMBLER, 33661, 0, 0, @COST_1500_AP_1800_R), -- Vengeful Gladiator's Barrier
(@SEASON_4, @ECTON_BRASSTUMBLER, 33662, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Bonecracker
(@SEASON_4, @ECTON_BRASSTUMBLER, 33663, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Bonegrinder
(@SEASON_4, @ECTON_BRASSTUMBLER, 33664, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Chain Armor
(@SEASON_4, @ECTON_BRASSTUMBLER, 33665, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Chain Gauntlets
(@SEASON_4, @ECTON_BRASSTUMBLER, 33666, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Chain Helm
(@SEASON_4, @ECTON_BRASSTUMBLER, 33667, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Chain Leggings
(@SEASON_4, @ECTON_BRASSTUMBLER, 33668, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Chain Spaulders
(@SEASON_4, @ECTON_BRASSTUMBLER, 33669, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Cleaver
(@SEASON_4, @ECTON_BRASSTUMBLER, 33670, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Decapitator
(@SEASON_4, @ECTON_BRASSTUMBLER, 33671, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Dragonhide Gloves
(@SEASON_4, @ECTON_BRASSTUMBLER, 33672, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dragonhide Helm
(@SEASON_4, @ECTON_BRASSTUMBLER, 33673, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dragonhide Legguards
(@SEASON_4, @ECTON_BRASSTUMBLER, 33674, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Dragonhide Spaulders
(@SEASON_4, @ECTON_BRASSTUMBLER, 33675, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dragonhide Tunic
(@SEASON_4, @ECTON_BRASSTUMBLER, 33676, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Dreadweave Gloves
(@SEASON_4, @ECTON_BRASSTUMBLER, 33677, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dreadweave Hood
(@SEASON_4, @ECTON_BRASSTUMBLER, 33678, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dreadweave Leggings
(@SEASON_4, @ECTON_BRASSTUMBLER, 33679, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Dreadweave Mantle
(@SEASON_4, @ECTON_BRASSTUMBLER, 33680, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dreadweave Robe
(@SEASON_4, @ECTON_BRASSTUMBLER, 33681, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Endgame
(@SEASON_4, @ECTON_BRASSTUMBLER, 33682, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Felweave Amice
(@SEASON_4, @ECTON_BRASSTUMBLER, 33683, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Felweave Cowl
(@SEASON_4, @ECTON_BRASSTUMBLER, 33684, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Felweave Handguards
(@SEASON_4, @ECTON_BRASSTUMBLER, 33685, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Felweave Raiment
(@SEASON_4, @ECTON_BRASSTUMBLER, 33686, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Felweave Trousers
(@SEASON_4, @ECTON_BRASSTUMBLER, 33687, 0, 0, @COST_2520_AP_1800_R), -- Vengeful Gladiator's Gavel
(@SEASON_4, @ECTON_BRASSTUMBLER, 33688, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Greatsword
(@SEASON_4, @ECTON_BRASSTUMBLER, 33689, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Hacker
(@SEASON_4, @ECTON_BRASSTUMBLER, 33690, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Kodohide Gloves
(@SEASON_4, @ECTON_BRASSTUMBLER, 33691, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Kodohide Helm
(@SEASON_4, @ECTON_BRASSTUMBLER, 33692, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Kodohide Legguards
(@SEASON_4, @ECTON_BRASSTUMBLER, 33693, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Kodohide Spaulders
(@SEASON_4, @ECTON_BRASSTUMBLER, 33694, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Kodohide Tunic
(@SEASON_4, @ECTON_BRASSTUMBLER, 33695, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Lamellar Chestpiece
(@SEASON_4, @ECTON_BRASSTUMBLER, 33696, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Lamellar Gauntlets
(@SEASON_4, @ECTON_BRASSTUMBLER, 33697, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Lamellar Helm
(@SEASON_4, @ECTON_BRASSTUMBLER, 33698, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Lamellar Legguards
(@SEASON_4, @ECTON_BRASSTUMBLER, 33699, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Lamellar Shoulders
(@SEASON_4, @ECTON_BRASSTUMBLER, 33700, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Leather Gloves
(@SEASON_4, @ECTON_BRASSTUMBLER, 33701, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Leather Helm
(@SEASON_4, @ECTON_BRASSTUMBLER, 33702, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Leather Legguards
(@SEASON_4, @ECTON_BRASSTUMBLER, 33703, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Leather Spaulders
(@SEASON_4, @ECTON_BRASSTUMBLER, 33704, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Leather Tunic
(@SEASON_4, @ECTON_BRASSTUMBLER, 33705, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Left Ripper
(@SEASON_4, @ECTON_BRASSTUMBLER, 33706, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Linked Armor
(@SEASON_4, @ECTON_BRASSTUMBLER, 33707, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Linked Gauntlets
(@SEASON_4, @ECTON_BRASSTUMBLER, 33708, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Linked Helm
(@SEASON_4, @ECTON_BRASSTUMBLER, 33709, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Linked Leggings
(@SEASON_4, @ECTON_BRASSTUMBLER, 33710, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Linked Spaulders
(@SEASON_4, @ECTON_BRASSTUMBLER, 33711, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mail Armor
(@SEASON_4, @ECTON_BRASSTUMBLER, 33712, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Mail Gauntlets
(@SEASON_4, @ECTON_BRASSTUMBLER, 33713, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mail Helm
(@SEASON_4, @ECTON_BRASSTUMBLER, 33714, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mail Leggings
(@SEASON_4, @ECTON_BRASSTUMBLER, 33715, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Mail Spaulders
(@SEASON_4, @ECTON_BRASSTUMBLER, 33716, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Staff
(@SEASON_4, @ECTON_BRASSTUMBLER, 33717, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Mooncloth Gloves
(@SEASON_4, @ECTON_BRASSTUMBLER, 33718, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mooncloth Hood
(@SEASON_4, @ECTON_BRASSTUMBLER, 33719, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mooncloth Leggings
(@SEASON_4, @ECTON_BRASSTUMBLER, 33720, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Mooncloth Mantle
(@SEASON_4, @ECTON_BRASSTUMBLER, 33721, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mooncloth Robe
(@SEASON_4, @ECTON_BRASSTUMBLER, 33722, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ornamented Chestguard
(@SEASON_4, @ECTON_BRASSTUMBLER, 33723, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Ornamented Gloves
(@SEASON_4, @ECTON_BRASSTUMBLER, 33724, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ornamented Headcover
(@SEASON_4, @ECTON_BRASSTUMBLER, 33725, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ornamented Legplates
(@SEASON_4, @ECTON_BRASSTUMBLER, 33726, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Ornamented Spaulders
(@SEASON_4, @ECTON_BRASSTUMBLER, 33727, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Painsaw
(@SEASON_4, @ECTON_BRASSTUMBLER, 33728, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Plate Chestpiece
(@SEASON_4, @ECTON_BRASSTUMBLER, 33729, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Plate Gauntlets
(@SEASON_4, @ECTON_BRASSTUMBLER, 33730, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Plate Helm
(@SEASON_4, @ECTON_BRASSTUMBLER, 33731, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Plate Legguards
(@SEASON_4, @ECTON_BRASSTUMBLER, 33732, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Plate Shoulders
(@SEASON_4, @ECTON_BRASSTUMBLER, 33733, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Pummeler
(@SEASON_4, @ECTON_BRASSTUMBLER, 33734, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Quickblade
(@SEASON_4, @ECTON_BRASSTUMBLER, 33735, 0, 0, @COST_1500_AP_1800_R), -- Vengeful Gladiator's Redoubt
(@SEASON_4, @ECTON_BRASSTUMBLER, 33736, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Reprieve
(@SEASON_4, @ECTON_BRASSTUMBLER, 33737, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Right Ripper
(@SEASON_4, @ECTON_BRASSTUMBLER, 33738, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ringmail Armor
(@SEASON_4, @ECTON_BRASSTUMBLER, 33739, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Ringmail Gauntlets
(@SEASON_4, @ECTON_BRASSTUMBLER, 33740, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ringmail Helm
(@SEASON_4, @ECTON_BRASSTUMBLER, 33741, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ringmail Leggings
(@SEASON_4, @ECTON_BRASSTUMBLER, 33742, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Ringmail Spaulders
(@SEASON_4, @ECTON_BRASSTUMBLER, 33743, 0, 0, @COST_2520_AP_1800_R), -- Vengeful Gladiator's Salvation
(@SEASON_4, @ECTON_BRASSTUMBLER, 33744, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Satin Gloves
(@SEASON_4, @ECTON_BRASSTUMBLER, 33745, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Satin Hood
(@SEASON_4, @ECTON_BRASSTUMBLER, 33746, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Satin Leggings
(@SEASON_4, @ECTON_BRASSTUMBLER, 33747, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Satin Mantle
(@SEASON_4, @ECTON_BRASSTUMBLER, 33748, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Satin Robe
(@SEASON_4, @ECTON_BRASSTUMBLER, 33749, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Scaled Chestpiece
(@SEASON_4, @ECTON_BRASSTUMBLER, 33750, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Scaled Gauntlets
(@SEASON_4, @ECTON_BRASSTUMBLER, 33751, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Scaled Helm
(@SEASON_4, @ECTON_BRASSTUMBLER, 33752, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Scaled Legguards
(@SEASON_4, @ECTON_BRASSTUMBLER, 33753, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Scaled Shoulders
(@SEASON_4, @ECTON_BRASSTUMBLER, 33754, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Shanker
(@SEASON_4, @ECTON_BRASSTUMBLER, 33755, 0, 0, @COST_1500_AP_1800_R), -- Vengeful Gladiator's Shield Wall
(@SEASON_4, @ECTON_BRASSTUMBLER, 33756, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Shiv
(@SEASON_4, @ECTON_BRASSTUMBLER, 33757, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Silk Amice
(@SEASON_4, @ECTON_BRASSTUMBLER, 33758, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Silk Cowl
(@SEASON_4, @ECTON_BRASSTUMBLER, 33759, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Silk Handguards
(@SEASON_4, @ECTON_BRASSTUMBLER, 33760, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Silk Raiment
(@SEASON_4, @ECTON_BRASSTUMBLER, 33761, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Silk Trousers
(@SEASON_4, @ECTON_BRASSTUMBLER, 33762, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Slicer
(@SEASON_4, @ECTON_BRASSTUMBLER, 33763, 0, 0, @COST_2520_AP_1800_R), -- Vengeful Gladiator's Spellblade
(@SEASON_4, @ECTON_BRASSTUMBLER, 33764, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Touch of Defeat
(@SEASON_4, @ECTON_BRASSTUMBLER, 33765, 0, 0, @COST_800_AP), -- Vengeful Gladiator's War Edge
(@SEASON_4, @ECTON_BRASSTUMBLER, 33766, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's War Staff
(@SEASON_4, @ECTON_BRASSTUMBLER, 33767, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Wyrmhide Gloves
(@SEASON_4, @ECTON_BRASSTUMBLER, 33768, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Wyrmhide Helm
(@SEASON_4, @ECTON_BRASSTUMBLER, 33769, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Wyrmhide Legguards
(@SEASON_4, @ECTON_BRASSTUMBLER, 33770, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Wyrmhide Spaulders
(@SEASON_4, @ECTON_BRASSTUMBLER, 33771, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Wyrmhide Tunic
(@SEASON_4, @ECTON_BRASSTUMBLER, 33801, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Mutilator
(@SEASON_4, @ECTON_BRASSTUMBLER, 33841, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Idol of Tenacity
(@SEASON_4, @ECTON_BRASSTUMBLER, 33842, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Libram of Justice
(@SEASON_4, @ECTON_BRASSTUMBLER, 33843, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Totem of the Third Wind
(@SEASON_4, @ECTON_BRASSTUMBLER, 33938, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Libram of Fortitude
(@SEASON_4, @ECTON_BRASSTUMBLER, 33941, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Totem of Indomitability
(@SEASON_4, @ECTON_BRASSTUMBLER, 33944, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Idol of Steadfastness
(@SEASON_4, @ECTON_BRASSTUMBLER, 33947, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Idol of Resolve
(@SEASON_4, @ECTON_BRASSTUMBLER, 33950, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Libram of Vengeance
(@SEASON_4, @ECTON_BRASSTUMBLER, 33953, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Totem of Survival
(@SEASON_4, @ECTON_BRASSTUMBLER, 34014, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Waraxe
(@SEASON_4, @ECTON_BRASSTUMBLER, 34015, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Chopper
(@SEASON_4, @ECTON_BRASSTUMBLER, 34016, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Left Render
(@SEASON_4, @ECTON_BRASSTUMBLER, 34033, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Grimoire
(@SEASON_4, @ECTON_BRASSTUMBLER, 34059, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Baton of Light
(@SEASON_4, @ECTON_BRASSTUMBLER, 34066, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Piercing Touch
(@SEASON_4, @ECTON_BRASSTUMBLER, 34529, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Longbow
(@SEASON_4, @ECTON_BRASSTUMBLER, 34530, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Rifle
(@SEASON_4, @ECTON_BRASSTUMBLER, 34540, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Battle Staff
(@SEASON_4, @MEMINNIE, 33006, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Heavy Crossbow
(@SEASON_4, @MEMINNIE, 33661, 0, 0, @COST_1500_AP_1800_R), -- Vengeful Gladiator's Barrier
(@SEASON_4, @MEMINNIE, 33662, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Bonecracker
(@SEASON_4, @MEMINNIE, 33663, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Bonegrinder
(@SEASON_4, @MEMINNIE, 33664, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Chain Armor
(@SEASON_4, @MEMINNIE, 33665, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Chain Gauntlets
(@SEASON_4, @MEMINNIE, 33666, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Chain Helm
(@SEASON_4, @MEMINNIE, 33667, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Chain Leggings
(@SEASON_4, @MEMINNIE, 33668, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Chain Spaulders
(@SEASON_4, @MEMINNIE, 33669, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Cleaver
(@SEASON_4, @MEMINNIE, 33670, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Decapitator
(@SEASON_4, @MEMINNIE, 33671, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Dragonhide Gloves
(@SEASON_4, @MEMINNIE, 33672, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dragonhide Helm
(@SEASON_4, @MEMINNIE, 33673, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dragonhide Legguards
(@SEASON_4, @MEMINNIE, 33674, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Dragonhide Spaulders
(@SEASON_4, @MEMINNIE, 33675, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dragonhide Tunic
(@SEASON_4, @MEMINNIE, 33676, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Dreadweave Gloves
(@SEASON_4, @MEMINNIE, 33677, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dreadweave Hood
(@SEASON_4, @MEMINNIE, 33678, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dreadweave Leggings
(@SEASON_4, @MEMINNIE, 33679, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Dreadweave Mantle
(@SEASON_4, @MEMINNIE, 33680, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Dreadweave Robe
(@SEASON_4, @MEMINNIE, 33681, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Endgame
(@SEASON_4, @MEMINNIE, 33682, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Felweave Amice
(@SEASON_4, @MEMINNIE, 33683, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Felweave Cowl
(@SEASON_4, @MEMINNIE, 33684, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Felweave Handguards
(@SEASON_4, @MEMINNIE, 33685, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Felweave Raiment
(@SEASON_4, @MEMINNIE, 33686, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Felweave Trousers
(@SEASON_4, @MEMINNIE, 33687, 0, 0, @COST_2520_AP_1800_R), -- Vengeful Gladiator's Gavel
(@SEASON_4, @MEMINNIE, 33688, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Greatsword
(@SEASON_4, @MEMINNIE, 33689, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Hacker
(@SEASON_4, @MEMINNIE, 33690, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Kodohide Gloves
(@SEASON_4, @MEMINNIE, 33691, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Kodohide Helm
(@SEASON_4, @MEMINNIE, 33692, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Kodohide Legguards
(@SEASON_4, @MEMINNIE, 33693, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Kodohide Spaulders
(@SEASON_4, @MEMINNIE, 33694, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Kodohide Tunic
(@SEASON_4, @MEMINNIE, 33695, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Lamellar Chestpiece
(@SEASON_4, @MEMINNIE, 33696, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Lamellar Gauntlets
(@SEASON_4, @MEMINNIE, 33697, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Lamellar Helm
(@SEASON_4, @MEMINNIE, 33698, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Lamellar Legguards
(@SEASON_4, @MEMINNIE, 33699, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Lamellar Shoulders
(@SEASON_4, @MEMINNIE, 33700, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Leather Gloves
(@SEASON_4, @MEMINNIE, 33701, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Leather Helm
(@SEASON_4, @MEMINNIE, 33702, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Leather Legguards
(@SEASON_4, @MEMINNIE, 33703, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Leather Spaulders
(@SEASON_4, @MEMINNIE, 33704, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Leather Tunic
(@SEASON_4, @MEMINNIE, 33705, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Left Ripper
(@SEASON_4, @MEMINNIE, 33706, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Linked Armor
(@SEASON_4, @MEMINNIE, 33707, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Linked Gauntlets
(@SEASON_4, @MEMINNIE, 33708, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Linked Helm
(@SEASON_4, @MEMINNIE, 33709, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Linked Leggings
(@SEASON_4, @MEMINNIE, 33710, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Linked Spaulders
(@SEASON_4, @MEMINNIE, 33711, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mail Armor
(@SEASON_4, @MEMINNIE, 33712, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Mail Gauntlets
(@SEASON_4, @MEMINNIE, 33713, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mail Helm
(@SEASON_4, @MEMINNIE, 33714, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mail Leggings
(@SEASON_4, @MEMINNIE, 33715, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Mail Spaulders
(@SEASON_4, @MEMINNIE, 33716, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Staff
(@SEASON_4, @MEMINNIE, 33717, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Mooncloth Gloves
(@SEASON_4, @MEMINNIE, 33718, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mooncloth Hood
(@SEASON_4, @MEMINNIE, 33719, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mooncloth Leggings
(@SEASON_4, @MEMINNIE, 33720, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Mooncloth Mantle
(@SEASON_4, @MEMINNIE, 33721, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Mooncloth Robe
(@SEASON_4, @MEMINNIE, 33722, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ornamented Chestguard
(@SEASON_4, @MEMINNIE, 33723, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Ornamented Gloves
(@SEASON_4, @MEMINNIE, 33724, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ornamented Headcover
(@SEASON_4, @MEMINNIE, 33725, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ornamented Legplates
(@SEASON_4, @MEMINNIE, 33726, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Ornamented Spaulders
(@SEASON_4, @MEMINNIE, 33727, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Painsaw
(@SEASON_4, @MEMINNIE, 33728, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Plate Chestpiece
(@SEASON_4, @MEMINNIE, 33729, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Plate Gauntlets
(@SEASON_4, @MEMINNIE, 33730, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Plate Helm
(@SEASON_4, @MEMINNIE, 33731, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Plate Legguards
(@SEASON_4, @MEMINNIE, 33732, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Plate Shoulders
(@SEASON_4, @MEMINNIE, 33733, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Pummeler
(@SEASON_4, @MEMINNIE, 33734, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Quickblade
(@SEASON_4, @MEMINNIE, 33735, 0, 0, @COST_1500_AP_1800_R), -- Vengeful Gladiator's Redoubt
(@SEASON_4, @MEMINNIE, 33736, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Reprieve
(@SEASON_4, @MEMINNIE, 33737, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Right Ripper
(@SEASON_4, @MEMINNIE, 33738, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ringmail Armor
(@SEASON_4, @MEMINNIE, 33739, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Ringmail Gauntlets
(@SEASON_4, @MEMINNIE, 33740, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ringmail Helm
(@SEASON_4, @MEMINNIE, 33741, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Ringmail Leggings
(@SEASON_4, @MEMINNIE, 33742, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Ringmail Spaulders
(@SEASON_4, @MEMINNIE, 33743, 0, 0, @COST_2520_AP_1800_R), -- Vengeful Gladiator's Salvation
(@SEASON_4, @MEMINNIE, 33744, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Satin Gloves
(@SEASON_4, @MEMINNIE, 33745, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Satin Hood
(@SEASON_4, @MEMINNIE, 33746, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Satin Leggings
(@SEASON_4, @MEMINNIE, 33747, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Satin Mantle
(@SEASON_4, @MEMINNIE, 33748, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Satin Robe
(@SEASON_4, @MEMINNIE, 33749, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Scaled Chestpiece
(@SEASON_4, @MEMINNIE, 33750, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Scaled Gauntlets
(@SEASON_4, @MEMINNIE, 33751, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Scaled Helm
(@SEASON_4, @MEMINNIE, 33752, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Scaled Legguards
(@SEASON_4, @MEMINNIE, 33753, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Scaled Shoulders
(@SEASON_4, @MEMINNIE, 33754, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Shanker
(@SEASON_4, @MEMINNIE, 33755, 0, 0, @COST_1500_AP_1800_R), -- Vengeful Gladiator's Shield Wall
(@SEASON_4, @MEMINNIE, 33756, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Shiv
(@SEASON_4, @MEMINNIE, 33757, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Silk Amice
(@SEASON_4, @MEMINNIE, 33758, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Silk Cowl
(@SEASON_4, @MEMINNIE, 33759, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Silk Handguards
(@SEASON_4, @MEMINNIE, 33760, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Silk Raiment
(@SEASON_4, @MEMINNIE, 33761, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Silk Trousers
(@SEASON_4, @MEMINNIE, 33762, 0, 0, @COST_2100_AP_1800_R), -- Vengeful Gladiator's Slicer
(@SEASON_4, @MEMINNIE, 33763, 0, 0, @COST_2520_AP_1800_R), -- Vengeful Gladiator's Spellblade
(@SEASON_4, @MEMINNIE, 33764, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Touch of Defeat
(@SEASON_4, @MEMINNIE, 33765, 0, 0, @COST_800_AP), -- Vengeful Gladiator's War Edge
(@SEASON_4, @MEMINNIE, 33766, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's War Staff
(@SEASON_4, @MEMINNIE, 33767, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Wyrmhide Gloves
(@SEASON_4, @MEMINNIE, 33768, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Wyrmhide Helm
(@SEASON_4, @MEMINNIE, 33769, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Wyrmhide Legguards
(@SEASON_4, @MEMINNIE, 33770, 0, 0, @COST_1200_AP_1950_R), -- Vengeful Gladiator's Wyrmhide Spaulders
(@SEASON_4, @MEMINNIE, 33771, 0, 0, @COST_1500_AP), -- Vengeful Gladiator's Wyrmhide Tunic
(@SEASON_4, @MEMINNIE, 33801, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Mutilator
(@SEASON_4, @MEMINNIE, 33841, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Idol of Tenacity
(@SEASON_4, @MEMINNIE, 33842, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Libram of Justice
(@SEASON_4, @MEMINNIE, 33843, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Totem of the Third Wind
(@SEASON_4, @MEMINNIE, 33938, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Libram of Fortitude
(@SEASON_4, @MEMINNIE, 33941, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Totem of Indomitability
(@SEASON_4, @MEMINNIE, 33944, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Idol of Steadfastness
(@SEASON_4, @MEMINNIE, 33947, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Idol of Resolve
(@SEASON_4, @MEMINNIE, 33950, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Libram of Vengeance
(@SEASON_4, @MEMINNIE, 33953, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Totem of Survival
(@SEASON_4, @MEMINNIE, 34014, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Waraxe
(@SEASON_4, @MEMINNIE, 34015, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Chopper
(@SEASON_4, @MEMINNIE, 34016, 0, 0, @COST_900_AP_1800_R), -- Vengeful Gladiator's Left Render
(@SEASON_4, @MEMINNIE, 34033, 0, 0, @COST_900_AP), -- Vengeful Gladiator's Grimoire
(@SEASON_4, @MEMINNIE, 34059, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Baton of Light
(@SEASON_4, @MEMINNIE, 34066, 0, 0, @COST_800_AP), -- Vengeful Gladiator's Piercing Touch
(@SEASON_4, @MEMINNIE, 34529, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Longbow
(@SEASON_4, @MEMINNIE, 34530, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Rifle
(@SEASON_4, @MEMINNIE, 34540, 0, 0, @COST_3000_AP_1800_R), -- Vengeful Gladiator's Battle Staff
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34985, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Baton of Light
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34986, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Barrier
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34987, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Battle Staff
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34988, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Bonecracker
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34989, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Bonegrinder
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34990, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Chain Armor
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34991, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Chain Gauntlets
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34992, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Chain Helm
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34993, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Chain Leggings
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34994, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Chain Spaulders
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34995, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Chopper
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34996, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Cleaver
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34997, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Decapitator
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34998, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Dragonhide Gloves
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 34999, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Dragonhide Helm
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35000, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Dragonhide Legguards
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35001, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Dragonhide Spaulders
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35002, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Dragonhide Tunic
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35003, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Dreadweave Gloves
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35004, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Dreadweave Hood
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35005, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Dreadweave Leggings
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35006, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Dreadweave Mantle
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35007, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Dreadweave Robe
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35008, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Endgame
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35009, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Felweave Amice
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35010, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Felweave Cowl
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35011, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Felweave Handguards
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35012, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Felweave Raiment
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35013, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Felweave Trousers
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35014, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Gavel
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35015, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Greatsword
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35016, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Grimoire
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35017, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Hacker
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35018, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Heavy Crossbow
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35019, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Resolve
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35020, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Steadfastness
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35021, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Tenacity
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35022, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Kodohide Gloves
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35023, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Kodohide Helm
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35024, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Kodohide Legguards
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35025, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Kodohide Spaulders
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35026, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Kodohide Tunic
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35027, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Lamellar Chestpiece
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35028, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Lamellar Gauntlets
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35029, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Lamellar Helm
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35030, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Lamellar Legguards
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35031, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Lamellar Shoulders
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35032, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Leather Gloves
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35033, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Leather Helm
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35034, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Leather Legguards
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35035, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Leather Spaulders
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35036, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Leather Tunic
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35037, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Left Render
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35038, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Left Ripper
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35039, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Fortitude
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35040, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Justice
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35041, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Vengeance
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35042, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Linked Armor
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35043, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Linked Gauntlets
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35044, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Linked Helm
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35045, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Linked Leggings
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35046, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Linked Spaulders
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35047, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Longbow
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35048, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Mail Armor
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35049, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Mail Gauntlets
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35050, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Mail Helm
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35051, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Mail Leggings
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35052, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Mail Spaulders
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35053, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Mooncloth Gloves
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35054, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Mooncloth Hood
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35055, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Mooncloth Leggings
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35056, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Mooncloth Mantle
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35057, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Mooncloth Robe
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35058, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Mutilator
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35059, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Ornamented Chestguard
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35060, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Ornamented Gloves
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35061, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Ornamented Headcover
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35062, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Ornamented Legplates
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35063, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Ornamented Spaulders
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35064, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Painsaw
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35065, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Piercing Touch
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35066, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Plate Chestpiece
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35067, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Plate Gauntlets
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35068, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Plate Helm
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35069, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Plate Legguards
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35070, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Plate Shoulders
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35071, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Pummeler
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35072, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Quickblade
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35073, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Redoubt
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35074, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Reprieve
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35075, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Rifle
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35076, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Right Ripper
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35077, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Ringmail Armor
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35078, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Ringmail Gauntlets
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35079, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Ringmail Helm
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35080, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Ringmail Leggings
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35081, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Ringmail Spaulders
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35082, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Salvation
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35083, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Satin Gloves
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35084, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Satin Hood
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35085, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Satin Leggings
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35086, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Satin Mantle
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35087, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Satin Robe
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35088, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Scaled Chestpiece
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35089, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Scaled Gauntlets
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35090, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Scaled Helm
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35091, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Scaled Legguards
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35092, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Scaled Shoulders
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35093, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Shanker
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35094, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Shield Wall
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35095, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Shiv
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35096, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Silk Amice
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35097, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Silk Cowl
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35098, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Silk Handguards
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35099, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Silk Raiment
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35100, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Silk Trousers
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35101, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Slicer
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35102, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Spellblade
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35103, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Staff
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35104, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of Indomitability
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35105, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of Survival
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35106, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of the Third Wind
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35107, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Touch of Defeat
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35108, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's War Edge
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35109, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's War Staff
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35110, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Waraxe
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35111, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Wyrmhide Gloves
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35112, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Wyrmhide Helm
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35113, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Wyrmhide Legguards
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35114, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Wyrmhide Spaulders
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 35115, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Wyrmhide Tunic
(@SEASON_4, @BIG_ZOKK_TORQUEWRENCH, 36737, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Hatchet
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34985, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Baton of Light
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34986, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Barrier
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34987, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Battle Staff
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34988, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Bonecracker
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34989, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Bonegrinder
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34990, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Chain Armor
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34991, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Chain Gauntlets
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34992, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Chain Helm
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34993, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Chain Leggings
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34994, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Chain Spaulders
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34995, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Chopper
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34996, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Cleaver
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34997, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Decapitator
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34998, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Dragonhide Gloves
(@SEASON_4, @GRIKKIN_COPPERSPRING, 34999, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Dragonhide Helm
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35000, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Dragonhide Legguards
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35001, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Dragonhide Spaulders
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35002, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Dragonhide Tunic
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35003, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Dreadweave Gloves
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35004, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Dreadweave Hood
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35005, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Dreadweave Leggings
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35006, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Dreadweave Mantle
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35007, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Dreadweave Robe
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35008, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Endgame
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35009, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Felweave Amice
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35010, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Felweave Cowl
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35011, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Felweave Handguards
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35012, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Felweave Raiment
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35013, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Felweave Trousers
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35014, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Gavel
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35015, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Greatsword
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35016, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Grimoire
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35017, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Hacker
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35018, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Heavy Crossbow
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35019, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Resolve
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35020, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Steadfastness
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35021, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Tenacity
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35022, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Kodohide Gloves
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35023, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Kodohide Helm
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35024, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Kodohide Legguards
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35025, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Kodohide Spaulders
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35026, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Kodohide Tunic
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35027, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Lamellar Chestpiece
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35028, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Lamellar Gauntlets
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35029, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Lamellar Helm
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35030, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Lamellar Legguards
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35031, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Lamellar Shoulders
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35032, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Leather Gloves
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35033, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Leather Helm
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35034, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Leather Legguards
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35035, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Leather Spaulders
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35036, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Leather Tunic
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35037, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Left Render
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35038, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Left Ripper
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35039, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Fortitude
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35040, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Justice
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35041, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Vengeance
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35042, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Linked Armor
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35043, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Linked Gauntlets
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35044, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Linked Helm
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35045, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Linked Leggings
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35046, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Linked Spaulders
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35047, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Longbow
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35048, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Mail Armor
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35049, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Mail Gauntlets
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35050, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Mail Helm
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35051, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Mail Leggings
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35052, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Mail Spaulders
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35053, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Mooncloth Gloves
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35054, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Mooncloth Hood
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35055, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Mooncloth Leggings
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35056, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Mooncloth Mantle
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35057, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Mooncloth Robe
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35058, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Mutilator
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35059, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Ornamented Chestguard
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35060, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Ornamented Gloves
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35061, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Ornamented Headcover
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35062, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Ornamented Legplates
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35063, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Ornamented Spaulders
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35064, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Painsaw
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35065, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Piercing Touch
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35066, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Plate Chestpiece
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35067, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Plate Gauntlets
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35068, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Plate Helm
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35069, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Plate Legguards
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35070, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Plate Shoulders
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35071, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Pummeler
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35072, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Quickblade
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35073, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Redoubt
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35074, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Reprieve
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35075, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Rifle
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35076, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Right Ripper
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35077, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Ringmail Armor
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35078, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Ringmail Gauntlets
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35079, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Ringmail Helm
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35080, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Ringmail Leggings
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35081, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Ringmail Spaulders
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35082, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Salvation
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35083, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Satin Gloves
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35084, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Satin Hood
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35085, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Satin Leggings
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35086, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Satin Mantle
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35087, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Satin Robe
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35088, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Scaled Chestpiece
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35089, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Scaled Gauntlets
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35090, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Scaled Helm
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35091, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Scaled Legguards
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35092, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Scaled Shoulders
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35093, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Shanker
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35094, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Shield Wall
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35095, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Shiv
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35096, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Silk Amice
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35097, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Silk Cowl
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35098, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Silk Handguards
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35099, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Silk Raiment
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35100, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Silk Trousers
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35101, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Slicer
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35102, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Spellblade
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35103, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Staff
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35104, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of Indomitability
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35105, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of Survival
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35106, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of the Third Wind
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35107, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Touch of Defeat
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35108, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's War Edge
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35109, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's War Staff
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35110, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Waraxe
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35111, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Wyrmhide Gloves
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35112, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Wyrmhide Helm
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35113, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Wyrmhide Legguards
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35114, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Wyrmhide Spaulders
(@SEASON_4, @GRIKKIN_COPPERSPRING, 35115, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Wyrmhide Tunic
(@SEASON_4, @GRIKKIN_COPPERSPRING, 36737, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Hatchet
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34985, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Baton of Light
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34986, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Barrier
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34987, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Battle Staff
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34988, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Bonecracker
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34989, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Bonegrinder
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34990, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Chain Armor
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34991, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Chain Gauntlets
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34992, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Chain Helm
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34993, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Chain Leggings
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34994, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Chain Spaulders
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34995, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Chopper
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34996, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Cleaver
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34997, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Decapitator
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34998, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Dragonhide Gloves
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 34999, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Dragonhide Helm
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35000, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Dragonhide Legguards
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35001, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Dragonhide Spaulders
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35002, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Dragonhide Tunic
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35003, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Dreadweave Gloves
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35004, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Dreadweave Hood
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35005, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Dreadweave Leggings
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35006, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Dreadweave Mantle
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35007, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Dreadweave Robe
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35008, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Endgame
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35009, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Felweave Amice
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35010, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Felweave Cowl
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35011, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Felweave Handguards
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35012, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Felweave Raiment
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35013, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Felweave Trousers
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35014, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Gavel
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35015, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Greatsword
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35016, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Grimoire
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35017, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Hacker
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35018, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Heavy Crossbow
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35019, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Resolve
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35020, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Steadfastness
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35021, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Tenacity
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35022, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Kodohide Gloves
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35023, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Kodohide Helm
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35024, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Kodohide Legguards
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35025, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Kodohide Spaulders
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35026, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Kodohide Tunic
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35027, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Lamellar Chestpiece
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35028, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Lamellar Gauntlets
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35029, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Lamellar Helm
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35030, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Lamellar Legguards
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35031, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Lamellar Shoulders
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35032, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Leather Gloves
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35033, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Leather Helm
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35034, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Leather Legguards
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35035, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Leather Spaulders
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35036, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Leather Tunic
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35037, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Left Render
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35038, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Left Ripper
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35039, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Fortitude
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35040, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Justice
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35041, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Vengeance
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35042, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Linked Armor
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35043, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Linked Gauntlets
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35044, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Linked Helm
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35045, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Linked Leggings
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35046, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Linked Spaulders
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35047, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Longbow
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35048, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Mail Armor
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35049, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Mail Gauntlets
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35050, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Mail Helm
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35051, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Mail Leggings
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35052, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Mail Spaulders
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35053, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Mooncloth Gloves
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35054, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Mooncloth Hood
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35055, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Mooncloth Leggings
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35056, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Mooncloth Mantle
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35057, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Mooncloth Robe
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35058, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Mutilator
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35059, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Ornamented Chestguard
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35060, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Ornamented Gloves
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35061, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Ornamented Headcover
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35062, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Ornamented Legplates
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35063, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Ornamented Spaulders
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35064, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Painsaw
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35065, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Piercing Touch
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35066, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Plate Chestpiece
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35067, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Plate Gauntlets
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35068, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Plate Helm
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35069, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Plate Legguards
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35070, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Plate Shoulders
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35071, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Pummeler
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35072, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Quickblade
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35073, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Redoubt
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35074, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Reprieve
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35075, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Rifle
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35076, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Right Ripper
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35077, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Ringmail Armor
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35078, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Ringmail Gauntlets
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35079, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Ringmail Helm
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35080, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Ringmail Leggings
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35081, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Ringmail Spaulders
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35082, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Salvation
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35083, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Satin Gloves
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35084, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Satin Hood
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35085, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Satin Leggings
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35086, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Satin Mantle
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35087, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Satin Robe
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35088, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Scaled Chestpiece
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35089, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Scaled Gauntlets
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35090, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Scaled Helm
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35091, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Scaled Legguards
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35092, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Scaled Shoulders
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35093, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Shanker
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35094, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Shield Wall
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35095, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Shiv
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35096, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Silk Amice
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35097, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Silk Cowl
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35098, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Silk Handguards
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35099, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Silk Raiment
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35100, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Silk Trousers
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35101, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Slicer
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35102, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Spellblade
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35103, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Staff
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35104, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of Indomitability
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35105, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of Survival
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35106, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of the Third Wind
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35107, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Touch of Defeat
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35108, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's War Edge
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35109, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's War Staff
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35110, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Waraxe
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35111, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Wyrmhide Gloves
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35112, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Wyrmhide Helm
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35113, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Wyrmhide Legguards
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35114, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Wyrmhide Spaulders
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 35115, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Wyrmhide Tunic
(@SEASON_4, @FRIXEE_BRASSTUMBLER, 36737, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Hatchet
(@SEASON_4, @EVEE_COPPERSPRING, 34985, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Baton of Light
(@SEASON_4, @EVEE_COPPERSPRING, 34986, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Barrier
(@SEASON_4, @EVEE_COPPERSPRING, 34987, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Battle Staff
(@SEASON_4, @EVEE_COPPERSPRING, 34988, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Bonecracker
(@SEASON_4, @EVEE_COPPERSPRING, 34989, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Bonegrinder
(@SEASON_4, @EVEE_COPPERSPRING, 34990, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Chain Armor
(@SEASON_4, @EVEE_COPPERSPRING, 34991, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Chain Gauntlets
(@SEASON_4, @EVEE_COPPERSPRING, 34992, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Chain Helm
(@SEASON_4, @EVEE_COPPERSPRING, 34993, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Chain Leggings
(@SEASON_4, @EVEE_COPPERSPRING, 34994, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Chain Spaulders
(@SEASON_4, @EVEE_COPPERSPRING, 34995, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Chopper
(@SEASON_4, @EVEE_COPPERSPRING, 34996, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Cleaver
(@SEASON_4, @EVEE_COPPERSPRING, 34997, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Decapitator
(@SEASON_4, @EVEE_COPPERSPRING, 34998, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Dragonhide Gloves
(@SEASON_4, @EVEE_COPPERSPRING, 34999, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Dragonhide Helm
(@SEASON_4, @EVEE_COPPERSPRING, 35000, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Dragonhide Legguards
(@SEASON_4, @EVEE_COPPERSPRING, 35001, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Dragonhide Spaulders
(@SEASON_4, @EVEE_COPPERSPRING, 35002, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Dragonhide Tunic
(@SEASON_4, @EVEE_COPPERSPRING, 35003, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Dreadweave Gloves
(@SEASON_4, @EVEE_COPPERSPRING, 35004, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Dreadweave Hood
(@SEASON_4, @EVEE_COPPERSPRING, 35005, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Dreadweave Leggings
(@SEASON_4, @EVEE_COPPERSPRING, 35006, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Dreadweave Mantle
(@SEASON_4, @EVEE_COPPERSPRING, 35007, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Dreadweave Robe
(@SEASON_4, @EVEE_COPPERSPRING, 35008, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Endgame
(@SEASON_4, @EVEE_COPPERSPRING, 35009, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Felweave Amice
(@SEASON_4, @EVEE_COPPERSPRING, 35010, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Felweave Cowl
(@SEASON_4, @EVEE_COPPERSPRING, 35011, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Felweave Handguards
(@SEASON_4, @EVEE_COPPERSPRING, 35012, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Felweave Raiment
(@SEASON_4, @EVEE_COPPERSPRING, 35013, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Felweave Trousers
(@SEASON_4, @EVEE_COPPERSPRING, 35014, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Gavel
(@SEASON_4, @EVEE_COPPERSPRING, 35015, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Greatsword
(@SEASON_4, @EVEE_COPPERSPRING, 35016, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Grimoire
(@SEASON_4, @EVEE_COPPERSPRING, 35017, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Hacker
(@SEASON_4, @EVEE_COPPERSPRING, 35018, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Heavy Crossbow
(@SEASON_4, @EVEE_COPPERSPRING, 35019, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Resolve
(@SEASON_4, @EVEE_COPPERSPRING, 35020, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Steadfastness
(@SEASON_4, @EVEE_COPPERSPRING, 35021, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Tenacity
(@SEASON_4, @EVEE_COPPERSPRING, 35022, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Kodohide Gloves
(@SEASON_4, @EVEE_COPPERSPRING, 35023, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Kodohide Helm
(@SEASON_4, @EVEE_COPPERSPRING, 35024, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Kodohide Legguards
(@SEASON_4, @EVEE_COPPERSPRING, 35025, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Kodohide Spaulders
(@SEASON_4, @EVEE_COPPERSPRING, 35026, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Kodohide Tunic
(@SEASON_4, @EVEE_COPPERSPRING, 35027, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Lamellar Chestpiece
(@SEASON_4, @EVEE_COPPERSPRING, 35028, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Lamellar Gauntlets
(@SEASON_4, @EVEE_COPPERSPRING, 35029, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Lamellar Helm
(@SEASON_4, @EVEE_COPPERSPRING, 35030, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Lamellar Legguards
(@SEASON_4, @EVEE_COPPERSPRING, 35031, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Lamellar Shoulders
(@SEASON_4, @EVEE_COPPERSPRING, 35032, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Leather Gloves
(@SEASON_4, @EVEE_COPPERSPRING, 35033, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Leather Helm
(@SEASON_4, @EVEE_COPPERSPRING, 35034, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Leather Legguards
(@SEASON_4, @EVEE_COPPERSPRING, 35035, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Leather Spaulders
(@SEASON_4, @EVEE_COPPERSPRING, 35036, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Leather Tunic
(@SEASON_4, @EVEE_COPPERSPRING, 35037, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Left Render
(@SEASON_4, @EVEE_COPPERSPRING, 35038, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Left Ripper
(@SEASON_4, @EVEE_COPPERSPRING, 35039, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Fortitude
(@SEASON_4, @EVEE_COPPERSPRING, 35040, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Justice
(@SEASON_4, @EVEE_COPPERSPRING, 35041, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Vengeance
(@SEASON_4, @EVEE_COPPERSPRING, 35042, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Linked Armor
(@SEASON_4, @EVEE_COPPERSPRING, 35043, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Linked Gauntlets
(@SEASON_4, @EVEE_COPPERSPRING, 35044, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Linked Helm
(@SEASON_4, @EVEE_COPPERSPRING, 35045, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Linked Leggings
(@SEASON_4, @EVEE_COPPERSPRING, 35046, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Linked Spaulders
(@SEASON_4, @EVEE_COPPERSPRING, 35047, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Longbow
(@SEASON_4, @EVEE_COPPERSPRING, 35048, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Mail Armor
(@SEASON_4, @EVEE_COPPERSPRING, 35049, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Mail Gauntlets
(@SEASON_4, @EVEE_COPPERSPRING, 35050, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Mail Helm
(@SEASON_4, @EVEE_COPPERSPRING, 35051, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Mail Leggings
(@SEASON_4, @EVEE_COPPERSPRING, 35052, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Mail Spaulders
(@SEASON_4, @EVEE_COPPERSPRING, 35053, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Mooncloth Gloves
(@SEASON_4, @EVEE_COPPERSPRING, 35054, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Mooncloth Hood
(@SEASON_4, @EVEE_COPPERSPRING, 35055, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Mooncloth Leggings
(@SEASON_4, @EVEE_COPPERSPRING, 35056, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Mooncloth Mantle
(@SEASON_4, @EVEE_COPPERSPRING, 35057, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Mooncloth Robe
(@SEASON_4, @EVEE_COPPERSPRING, 35058, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Mutilator
(@SEASON_4, @EVEE_COPPERSPRING, 35059, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Ornamented Chestguard
(@SEASON_4, @EVEE_COPPERSPRING, 35060, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Ornamented Gloves
(@SEASON_4, @EVEE_COPPERSPRING, 35061, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Ornamented Headcover
(@SEASON_4, @EVEE_COPPERSPRING, 35062, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Ornamented Legplates
(@SEASON_4, @EVEE_COPPERSPRING, 35063, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Ornamented Spaulders
(@SEASON_4, @EVEE_COPPERSPRING, 35064, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Painsaw
(@SEASON_4, @EVEE_COPPERSPRING, 35065, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Piercing Touch
(@SEASON_4, @EVEE_COPPERSPRING, 35066, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Plate Chestpiece
(@SEASON_4, @EVEE_COPPERSPRING, 35067, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Plate Gauntlets
(@SEASON_4, @EVEE_COPPERSPRING, 35068, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Plate Helm
(@SEASON_4, @EVEE_COPPERSPRING, 35069, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Plate Legguards
(@SEASON_4, @EVEE_COPPERSPRING, 35070, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Plate Shoulders
(@SEASON_4, @EVEE_COPPERSPRING, 35071, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Pummeler
(@SEASON_4, @EVEE_COPPERSPRING, 35072, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Quickblade
(@SEASON_4, @EVEE_COPPERSPRING, 35073, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Redoubt
(@SEASON_4, @EVEE_COPPERSPRING, 35074, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Reprieve
(@SEASON_4, @EVEE_COPPERSPRING, 35075, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Rifle
(@SEASON_4, @EVEE_COPPERSPRING, 35076, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Right Ripper
(@SEASON_4, @EVEE_COPPERSPRING, 35077, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Ringmail Armor
(@SEASON_4, @EVEE_COPPERSPRING, 35078, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Ringmail Gauntlets
(@SEASON_4, @EVEE_COPPERSPRING, 35079, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Ringmail Helm
(@SEASON_4, @EVEE_COPPERSPRING, 35080, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Ringmail Leggings
(@SEASON_4, @EVEE_COPPERSPRING, 35081, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Ringmail Spaulders
(@SEASON_4, @EVEE_COPPERSPRING, 35082, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Salvation
(@SEASON_4, @EVEE_COPPERSPRING, 35083, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Satin Gloves
(@SEASON_4, @EVEE_COPPERSPRING, 35084, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Satin Hood
(@SEASON_4, @EVEE_COPPERSPRING, 35085, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Satin Leggings
(@SEASON_4, @EVEE_COPPERSPRING, 35086, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Satin Mantle
(@SEASON_4, @EVEE_COPPERSPRING, 35087, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Satin Robe
(@SEASON_4, @EVEE_COPPERSPRING, 35088, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Scaled Chestpiece
(@SEASON_4, @EVEE_COPPERSPRING, 35089, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Scaled Gauntlets
(@SEASON_4, @EVEE_COPPERSPRING, 35090, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Scaled Helm
(@SEASON_4, @EVEE_COPPERSPRING, 35091, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Scaled Legguards
(@SEASON_4, @EVEE_COPPERSPRING, 35092, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Scaled Shoulders
(@SEASON_4, @EVEE_COPPERSPRING, 35093, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Shanker
(@SEASON_4, @EVEE_COPPERSPRING, 35094, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Shield Wall
(@SEASON_4, @EVEE_COPPERSPRING, 35095, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Shiv
(@SEASON_4, @EVEE_COPPERSPRING, 35096, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Silk Amice
(@SEASON_4, @EVEE_COPPERSPRING, 35097, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Silk Cowl
(@SEASON_4, @EVEE_COPPERSPRING, 35098, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Silk Handguards
(@SEASON_4, @EVEE_COPPERSPRING, 35099, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Silk Raiment
(@SEASON_4, @EVEE_COPPERSPRING, 35100, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Silk Trousers
(@SEASON_4, @EVEE_COPPERSPRING, 35101, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Slicer
(@SEASON_4, @EVEE_COPPERSPRING, 35102, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Spellblade
(@SEASON_4, @EVEE_COPPERSPRING, 35103, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Staff
(@SEASON_4, @EVEE_COPPERSPRING, 35104, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of Indomitability
(@SEASON_4, @EVEE_COPPERSPRING, 35105, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of Survival
(@SEASON_4, @EVEE_COPPERSPRING, 35106, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of the Third Wind
(@SEASON_4, @EVEE_COPPERSPRING, 35107, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Touch of Defeat
(@SEASON_4, @EVEE_COPPERSPRING, 35108, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's War Edge
(@SEASON_4, @EVEE_COPPERSPRING, 35109, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's War Staff
(@SEASON_4, @EVEE_COPPERSPRING, 35110, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Waraxe
(@SEASON_4, @EVEE_COPPERSPRING, 35111, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Wyrmhide Gloves
(@SEASON_4, @EVEE_COPPERSPRING, 35112, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Wyrmhide Helm
(@SEASON_4, @EVEE_COPPERSPRING, 35113, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Wyrmhide Legguards
(@SEASON_4, @EVEE_COPPERSPRING, 35114, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Wyrmhide Spaulders
(@SEASON_4, @EVEE_COPPERSPRING, 35115, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Wyrmhide Tunic
(@SEASON_4, @EVEE_COPPERSPRING, 36737, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Hatchet
(@SEASON_4, @ONTOK_SHATTERHORN, 34985, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Baton of Light
(@SEASON_4, @ONTOK_SHATTERHORN, 34986, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Barrier
(@SEASON_4, @ONTOK_SHATTERHORN, 34987, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Battle Staff
(@SEASON_4, @ONTOK_SHATTERHORN, 34988, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Bonecracker
(@SEASON_4, @ONTOK_SHATTERHORN, 34989, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Bonegrinder
(@SEASON_4, @ONTOK_SHATTERHORN, 34990, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Chain Armor
(@SEASON_4, @ONTOK_SHATTERHORN, 34991, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Chain Gauntlets
(@SEASON_4, @ONTOK_SHATTERHORN, 34992, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Chain Helm
(@SEASON_4, @ONTOK_SHATTERHORN, 34993, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Chain Leggings
(@SEASON_4, @ONTOK_SHATTERHORN, 34994, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Chain Spaulders
(@SEASON_4, @ONTOK_SHATTERHORN, 34995, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Chopper
(@SEASON_4, @ONTOK_SHATTERHORN, 34996, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Cleaver
(@SEASON_4, @ONTOK_SHATTERHORN, 34997, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Decapitator
(@SEASON_4, @ONTOK_SHATTERHORN, 34998, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Dragonhide Gloves
(@SEASON_4, @ONTOK_SHATTERHORN, 34999, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Dragonhide Helm
(@SEASON_4, @ONTOK_SHATTERHORN, 35000, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Dragonhide Legguards
(@SEASON_4, @ONTOK_SHATTERHORN, 35001, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Dragonhide Spaulders
(@SEASON_4, @ONTOK_SHATTERHORN, 35002, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Dragonhide Tunic
(@SEASON_4, @ONTOK_SHATTERHORN, 35003, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Dreadweave Gloves
(@SEASON_4, @ONTOK_SHATTERHORN, 35004, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Dreadweave Hood
(@SEASON_4, @ONTOK_SHATTERHORN, 35005, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Dreadweave Leggings
(@SEASON_4, @ONTOK_SHATTERHORN, 35006, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Dreadweave Mantle
(@SEASON_4, @ONTOK_SHATTERHORN, 35007, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Dreadweave Robe
(@SEASON_4, @ONTOK_SHATTERHORN, 35008, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Endgame
(@SEASON_4, @ONTOK_SHATTERHORN, 35009, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Felweave Amice
(@SEASON_4, @ONTOK_SHATTERHORN, 35010, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Felweave Cowl
(@SEASON_4, @ONTOK_SHATTERHORN, 35011, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Felweave Handguards
(@SEASON_4, @ONTOK_SHATTERHORN, 35012, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Felweave Raiment
(@SEASON_4, @ONTOK_SHATTERHORN, 35013, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Felweave Trousers
(@SEASON_4, @ONTOK_SHATTERHORN, 35014, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Gavel
(@SEASON_4, @ONTOK_SHATTERHORN, 35015, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Greatsword
(@SEASON_4, @ONTOK_SHATTERHORN, 35016, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Grimoire
(@SEASON_4, @ONTOK_SHATTERHORN, 35017, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Hacker
(@SEASON_4, @ONTOK_SHATTERHORN, 35018, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Heavy Crossbow
(@SEASON_4, @ONTOK_SHATTERHORN, 35019, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Resolve
(@SEASON_4, @ONTOK_SHATTERHORN, 35020, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Steadfastness
(@SEASON_4, @ONTOK_SHATTERHORN, 35021, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Idol of Tenacity
(@SEASON_4, @ONTOK_SHATTERHORN, 35022, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Kodohide Gloves
(@SEASON_4, @ONTOK_SHATTERHORN, 35023, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Kodohide Helm
(@SEASON_4, @ONTOK_SHATTERHORN, 35024, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Kodohide Legguards
(@SEASON_4, @ONTOK_SHATTERHORN, 35025, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Kodohide Spaulders
(@SEASON_4, @ONTOK_SHATTERHORN, 35026, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Kodohide Tunic
(@SEASON_4, @ONTOK_SHATTERHORN, 35027, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Lamellar Chestpiece
(@SEASON_4, @ONTOK_SHATTERHORN, 35028, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Lamellar Gauntlets
(@SEASON_4, @ONTOK_SHATTERHORN, 35029, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Lamellar Helm
(@SEASON_4, @ONTOK_SHATTERHORN, 35030, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Lamellar Legguards
(@SEASON_4, @ONTOK_SHATTERHORN, 35031, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Lamellar Shoulders
(@SEASON_4, @ONTOK_SHATTERHORN, 35032, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Leather Gloves
(@SEASON_4, @ONTOK_SHATTERHORN, 35033, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Leather Helm
(@SEASON_4, @ONTOK_SHATTERHORN, 35034, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Leather Legguards
(@SEASON_4, @ONTOK_SHATTERHORN, 35035, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Leather Spaulders
(@SEASON_4, @ONTOK_SHATTERHORN, 35036, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Leather Tunic
(@SEASON_4, @ONTOK_SHATTERHORN, 35037, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Left Render
(@SEASON_4, @ONTOK_SHATTERHORN, 35038, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Left Ripper
(@SEASON_4, @ONTOK_SHATTERHORN, 35039, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Fortitude
(@SEASON_4, @ONTOK_SHATTERHORN, 35040, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Justice
(@SEASON_4, @ONTOK_SHATTERHORN, 35041, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Libram of Vengeance
(@SEASON_4, @ONTOK_SHATTERHORN, 35042, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Linked Armor
(@SEASON_4, @ONTOK_SHATTERHORN, 35043, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Linked Gauntlets
(@SEASON_4, @ONTOK_SHATTERHORN, 35044, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Linked Helm
(@SEASON_4, @ONTOK_SHATTERHORN, 35045, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Linked Leggings
(@SEASON_4, @ONTOK_SHATTERHORN, 35046, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Linked Spaulders
(@SEASON_4, @ONTOK_SHATTERHORN, 35047, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Longbow
(@SEASON_4, @ONTOK_SHATTERHORN, 35048, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Mail Armor
(@SEASON_4, @ONTOK_SHATTERHORN, 35049, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Mail Gauntlets
(@SEASON_4, @ONTOK_SHATTERHORN, 35050, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Mail Helm
(@SEASON_4, @ONTOK_SHATTERHORN, 35051, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Mail Leggings
(@SEASON_4, @ONTOK_SHATTERHORN, 35052, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Mail Spaulders
(@SEASON_4, @ONTOK_SHATTERHORN, 35053, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Mooncloth Gloves
(@SEASON_4, @ONTOK_SHATTERHORN, 35054, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Mooncloth Hood
(@SEASON_4, @ONTOK_SHATTERHORN, 35055, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Mooncloth Leggings
(@SEASON_4, @ONTOK_SHATTERHORN, 35056, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Mooncloth Mantle
(@SEASON_4, @ONTOK_SHATTERHORN, 35057, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Mooncloth Robe
(@SEASON_4, @ONTOK_SHATTERHORN, 35058, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Mutilator
(@SEASON_4, @ONTOK_SHATTERHORN, 35059, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Ornamented Chestguard
(@SEASON_4, @ONTOK_SHATTERHORN, 35060, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Ornamented Gloves
(@SEASON_4, @ONTOK_SHATTERHORN, 35061, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Ornamented Headcover
(@SEASON_4, @ONTOK_SHATTERHORN, 35062, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Ornamented Legplates
(@SEASON_4, @ONTOK_SHATTERHORN, 35063, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Ornamented Spaulders
(@SEASON_4, @ONTOK_SHATTERHORN, 35064, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Painsaw
(@SEASON_4, @ONTOK_SHATTERHORN, 35065, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Piercing Touch
(@SEASON_4, @ONTOK_SHATTERHORN, 35066, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Plate Chestpiece
(@SEASON_4, @ONTOK_SHATTERHORN, 35067, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Plate Gauntlets
(@SEASON_4, @ONTOK_SHATTERHORN, 35068, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Plate Helm
(@SEASON_4, @ONTOK_SHATTERHORN, 35069, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Plate Legguards
(@SEASON_4, @ONTOK_SHATTERHORN, 35070, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Plate Shoulders
(@SEASON_4, @ONTOK_SHATTERHORN, 35071, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Pummeler
(@SEASON_4, @ONTOK_SHATTERHORN, 35072, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Quickblade
(@SEASON_4, @ONTOK_SHATTERHORN, 35073, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Redoubt
(@SEASON_4, @ONTOK_SHATTERHORN, 35074, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Reprieve
(@SEASON_4, @ONTOK_SHATTERHORN, 35075, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Rifle
(@SEASON_4, @ONTOK_SHATTERHORN, 35076, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Right Ripper
(@SEASON_4, @ONTOK_SHATTERHORN, 35077, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Ringmail Armor
(@SEASON_4, @ONTOK_SHATTERHORN, 35078, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Ringmail Gauntlets
(@SEASON_4, @ONTOK_SHATTERHORN, 35079, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Ringmail Helm
(@SEASON_4, @ONTOK_SHATTERHORN, 35080, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Ringmail Leggings
(@SEASON_4, @ONTOK_SHATTERHORN, 35081, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Ringmail Spaulders
(@SEASON_4, @ONTOK_SHATTERHORN, 35082, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Salvation
(@SEASON_4, @ONTOK_SHATTERHORN, 35083, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Satin Gloves
(@SEASON_4, @ONTOK_SHATTERHORN, 35084, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Satin Hood
(@SEASON_4, @ONTOK_SHATTERHORN, 35085, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Satin Leggings
(@SEASON_4, @ONTOK_SHATTERHORN, 35086, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Satin Mantle
(@SEASON_4, @ONTOK_SHATTERHORN, 35087, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Satin Robe
(@SEASON_4, @ONTOK_SHATTERHORN, 35088, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Scaled Chestpiece
(@SEASON_4, @ONTOK_SHATTERHORN, 35089, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Scaled Gauntlets
(@SEASON_4, @ONTOK_SHATTERHORN, 35090, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Scaled Helm
(@SEASON_4, @ONTOK_SHATTERHORN, 35091, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Scaled Legguards
(@SEASON_4, @ONTOK_SHATTERHORN, 35092, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Scaled Shoulders
(@SEASON_4, @ONTOK_SHATTERHORN, 35093, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Shanker
(@SEASON_4, @ONTOK_SHATTERHORN, 35094, 0, 0, @COST_1875_AP_2050_R), -- Brutal Gladiator's Shield Wall
(@SEASON_4, @ONTOK_SHATTERHORN, 35095, 0, 0, @COST_1125_AP_2050_R), -- Brutal Gladiator's Shiv
(@SEASON_4, @ONTOK_SHATTERHORN, 35096, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Silk Amice
(@SEASON_4, @ONTOK_SHATTERHORN, 35097, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Silk Cowl
(@SEASON_4, @ONTOK_SHATTERHORN, 35098, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Silk Handguards
(@SEASON_4, @ONTOK_SHATTERHORN, 35099, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Silk Raiment
(@SEASON_4, @ONTOK_SHATTERHORN, 35100, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Silk Trousers
(@SEASON_4, @ONTOK_SHATTERHORN, 35101, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Slicer
(@SEASON_4, @ONTOK_SHATTERHORN, 35102, 0, 0, @COST_3150_AP_2050_R), -- Brutal Gladiator's Spellblade
(@SEASON_4, @ONTOK_SHATTERHORN, 35103, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's Staff
(@SEASON_4, @ONTOK_SHATTERHORN, 35104, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of Indomitability
(@SEASON_4, @ONTOK_SHATTERHORN, 35105, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of Survival
(@SEASON_4, @ONTOK_SHATTERHORN, 35106, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Totem of the Third Wind
(@SEASON_4, @ONTOK_SHATTERHORN, 35107, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's Touch of Defeat
(@SEASON_4, @ONTOK_SHATTERHORN, 35108, 0, 0, @COST_1000_AP_1750_R), -- Brutal Gladiator's War Edge
(@SEASON_4, @ONTOK_SHATTERHORN, 35109, 0, 0, @COST_3750_AP_2050_R), -- Brutal Gladiator's War Staff
(@SEASON_4, @ONTOK_SHATTERHORN, 35110, 0, 0, @COST_2625_AP_2050_R), -- Brutal Gladiator's Waraxe
(@SEASON_4, @ONTOK_SHATTERHORN, 35111, 0, 0, @COST_1125_AP), -- Brutal Gladiator's Wyrmhide Gloves
(@SEASON_4, @ONTOK_SHATTERHORN, 35112, 0, 0, @COST_1875_AP_1700_R), -- Brutal Gladiator's Wyrmhide Helm
(@SEASON_4, @ONTOK_SHATTERHORN, 35113, 0, 0, @COST_1875_AP_1550_R), -- Brutal Gladiator's Wyrmhide Legguards
(@SEASON_4, @ONTOK_SHATTERHORN, 35114, 0, 0, @COST_1500_AP_2200_R), -- Brutal Gladiator's Wyrmhide Spaulders
(@SEASON_4, @ONTOK_SHATTERHORN, 35115, 0, 0, @COST_1875_AP_20_WSG_1575_R), -- Brutal Gladiator's Wyrmhide Tunic
(@SEASON_4, @ONTOK_SHATTERHORN, 36737, 0, 0, @COST_2625_AP_2050_R); -- Brutal Gladiator's Hatchet