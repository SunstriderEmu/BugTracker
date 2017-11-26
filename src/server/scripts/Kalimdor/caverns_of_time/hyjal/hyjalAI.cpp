/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: HyjalAI
SD%Complete: 90
SDComment:
SDCategory: Caverns of Time, Mount Hyjal
EndScriptData */


#include "hyjalAI.h"
#include "hyjal_trash.h"
#include "MapManager.h"
#include "Language.h"
#include "Chat.h"
#include "Object.h"

#define SPAWN_GARG_GATE 0
#define SPAWN_WYRM_GATE 1
#define SPAWN_NEAR_TOWER 2

#define TEXT_ARCHIMONDE_AT_HORDE_RETREAT -1543998
#define EMOTE_MASS_TELEPORT -1543997

// Locations for summoning gargoyls and frost wyrms in special cases
float SpawnPointSpecial[3][3]=
{
    {5497.08f,   -2493.23f,   1535.72f}, //spawn point for the gargoyles near the horde gate
    {5624.53f,   -2548.12f,   1551.54f}, //spawn point for the frost wyrm near the horde gate
    {5604.41f,   -2811.98f,   1547.77f}  //spawn point for the gargoyles and wyrms near the horde tower
};

// Locations for summoning waves in Alliance base
float AllianceBase[4][3]=
{
    {4928.48f,    -1526.38f,    1326.83f},
    {4923.54f,    -1514.29f,    1327.98f},
    {4928.41f,    -1510.35f,    1327.99f},
    {4938.35f,    -1521.00f,    1326.69f}
};

float JainaDummySpawn[2][4]=
{
    {5497.01f, -2719.03f, 1483.08f, 2.90426f},
    {5484.98f, -2721.69f, 1483.39f, 6.00656f}
};


// Locations for summoning waves in Horde base
float HordeBase[4][3]=
{
    {5458.01f,    -2340.27f,    1459.60f},
    {5466.01f,    -2334.69f,    1460.06f},
    {5468.45f,    -2355.13f,    1459.99f},
    {5479.06f,    -2344.16f,    1461.74f}
};

// Lady Jaina's waypoints when retreathing
float JainaWPs[2][3]=
{
    {5078.56f,    -1789.79f,    1320.73f},//next to the small stairs
    {5037.38f,    -1778.39f,    1322.61f},//center of alliance base
};

float InfernalPos[8][3]=//spawn points for the infernals in the horde base
{
    {5453.59f,    -2764.52f,    1493.50f},
    {5478.40f,    -2781.77f,    1497.52f},
    {5506.09f,    -2780.53f,    1496.32f},
    {5532.10f,    -2763.42f,    1492.37f},
    {5544.16f,    -2733.99f,    1487.14f},
    {5536.19f,    -2708.18f,    1480.01f},
    {5510.16f,    -2691.75f,    1479.66f},
    {5482.39f,    -2689.19f,    1481.09f}
};

float InfernalSPWP[26][4]=//spawn points for the infernals in the horde base used in the cleaning wave
{
    {5490.96f, -2718.72f, 1482.96f, 0.49773f},
    {5449.51f, -2723.32f, 1485.69f, 2.69685f},
    {5520.83f, -2624.68f, 1483.82f, 1.20459f},
    {5558.28f, -2629.26f, 1485.76f, 0.37992f},
    {5567.97f, -2758.69f, 1494.10f, 5.04125f},
    {5384.90f, -2793.47f, 1503.90f, 5.55412f},
    {5495.33f, -2814.06f, 1501.56f, 1.12055f},
    {5472.63f, -2929.39f, 1538.31f, 1.95777f},
    {5334.72f, -2952.29f, 1534.34f, 0.50869f},
    {5398.36f, -2872.46f, 1512.38f, 0.76787f},
    {5514.39f, -2768.63f, 1492.30f, 1.55721f},
    {5598.91f, -2703.75f, 1495.64f, 2.56644f},
    {5467.80f, -2655.93f, 1482.27f, 0.85819f},
    {5399.83f, -2985.24f, 1545.04f, 5.92559f},
    {5232.13f, -2967.05f, 1553.09f, 5.41351f},
    {5272.02f, -3082.52f, 1567.09f, 3.40681f},
    {5343.26f, -3120.71f, 1582.92f, 3.16727f},
    {5371.26f, -3175.24f, 1587.41f, 6.10466f},
    {5434.67f, -3177.91f, 1579.25f, 2.77850f},
    {5237.39f, -3149.25f, 1593.59f, 0.83855f},
    {5202.15f, -3016.64f, 1566.28f, 3.31256f},
    {5302.54f, -2914.37f, 1528.53f, 3.37146f},
    {5439.04f, -2834.81f, 1508.80f, 2.14231f},
    {5421.33f, -2771.04f, 1494.28f, 6.06223f},
    {5549.76f, -2692.93f, 1482.68f, 2.19414f},
    {5459.78f, -2755.71f, 1490.68f, 1.05139f}
};

float VeinPos[14][8]=//spawn points of the ancient gem veins
{
    {5184.84f,    -1982.59f,    1382.66f,    2.5807900f,    0.0f,    0.0f,    0.96094400f,    0.2767420f},  //alliance
    {5107.66f,    -2071.16f,    1368.37f,    2.6514800f,    0.0f,    0.0f,    0.97012400f,    0.2426110f},    //alliance
    {5040.53f,    -2227.65f,    1403.17f,    3.3504900f,    0.0f,    0.0f,    0.99455000f,   -0.1042570f},    //alliance
    {5187.59f,    -2453.12f,    1455.51f,    5.8794300f,    0.0f,    0.0f,    0.20051000f,   -0.9796920f},    //alliance
    {5429.43f,    -2340.65f,    1465.38f,    4.7681000f,    0.0f,    0.0f,    0.68713800f,   -0.7265270f},    //alliance
    {5463.99f,    -2315.95f,    1470.29f,    1.5204500f,    0.0f,    0.0f,    0.68908400f,    0.7246820f},    //alliance
    {5624.65f,    -2495.09f,    1510.11f,    0.0124869f,    0.0f,    0.0f,    0.00624342f,    0.9999810f},    //alliance
    {5285.41f,    -3348.32f,    1663.01f,    1.5715200f,    0.0f,    0.0f,    0.70736200f,    0.7068520f},    //horde
    {5417.69f,    -3372.52f,    1656.31f,    0.3619930f,    0.0f,    0.0f,    0.18001000f,    0.9836650f},    //horde
    {5315.34f,    -3238.32f,    1622.88f,    3.0362700f,    0.0f,    0.0f,    0.99861400f,    0.0526347f},    //horde
    {5303.40f,    -3096.44f,    1596.41f,    1.7207300f,    0.0f,    0.0f,    0.75808100f,    0.6521600f},    //horde
    {5265.13f,    -3177.27f,    1616.22f,    0.8136040f,    0.0f,    0.0f,    0.39567400f,    0.9183910f},    //horde
    {5374.30f,    -3420.59f,    1653.43f,    1.4576200f,    0.0f,    0.0f,    0.66598100f,    0.7459690f},    //horde
    {5441.54f,    -3321.59f,    1651.55f,    0.2583060f,    0.0f,    0.0f,    0.12879400f,    0.9916710f}   //horde
};

float AllianceOverrunGargPos[5][4]=//gargoyle spawn points in the alliance overrun
{
    {5279.94f, -2049.68f, 1311.38f, 0.0f},//garg1
    {5289.15f, -2219.06f, 1291.12f, 0.0f},//garg2
    {5202.07f, -2136.10f, 1305.07f, 2.8f},//garg3
    {5071.52f, -2425.63f, 1454.48f, 5.54f},//garg4
    {5120.65f, -2467.92f, 1463.93f, 2.54f}//garg5
};

float AllianceFirePos[92][8]=//spawn points for the fire visuals (GO) in the alliance base
{
    {5039.90f,    -1796.84f,    1323.88f,    2.5922200f,    0.0f,    0.0f,    0.96251100f,     0.2712430f},
    {5087.20f,    -1795.20f,    1320.68f,    1.0394600f,    0.0f,    0.0f,    0.49664400f,     0.8679540f},
    {5112.68f,    -1806.66f,    1359.93f,    1.3779900f,    0.0f,    0.0f,    0.63576000f,     0.7718870f},
    {5095.61f,    -1793.27f,    1359.78f,    0.5808060f,    0.0f,    0.0f,    0.28633800f,     0.9581290f},
    {5090.43f,    -1784.45f,    1360.44f,    0.7967840f,    0.0f,    0.0f,    0.38793700f,     0.9216860f},
    {5139.25f,    -1783.11f,    1359.39f,    3.3084900f,    0.0f,    0.0f,    0.99652000f,    -0.0833509f},
    {5112.16f,    -1763.72f,    1361.35f,    5.1031200f,    0.0f,    0.0f,    0.55638800f,    -0.8309220f},
    {4981.18f,    -1793.98f,    1335.70f,    3.2307200f,    0.0f,    0.0f,    0.99900700f,    -0.0445498f},
    {4996.57f,    -1766.75f,    1341.62f,    3.5331000f,    0.0f,    0.0f,    0.98090200f,    -0.1945050f},
    {4983.74f,    -1769.25f,    1345.75f,    3.7922800f,    0.0f,    0.0f,    0.94754100f,    -0.3196350f},
    {4996.01f,    -1774.43f,    1330.71f,    3.0736400f,    0.0f,    0.0f,    0.99942300f,     0.0339693f},
    {5094.20f,    -1726.13f,    1330.55f,    1.5617500f,    0.0f,    0.0f,    0.70390100f,     0.7102980f},
    {5079.82f,    -1721.24f,    1336.26f,    1.1886800f,    0.0f,    0.0f,    0.55996400f,     0.8285170f},
    {5077.68f,    -1717.15f,    1327.78f,    0.0145145f,    0.0f,    0.0f,    0.00725717f,     0.9999740f},
    {5122.27f,    -1738.22f,    1341.67f,    0.8352560f,    0.0f,    0.0f,    0.40559300f,     0.9140540f},
    {5131.88f,    -1741.15f,    1335.25f,    2.1547200f,    0.0f,    0.0f,    0.88071200f,     0.4736530f},
    {5196.93f,    -1772.99f,    1345.20f,    0.1283970f,    0.0f,    0.0f,    0.06415440f,     0.9979400f},
    {5225.33f,    -1756.06f,    1344.17f,    3.0422300f,    0.0f,    0.0f,    0.99876600f,     0.0496599f},
    {5224.84f,    -1767.05f,    1360.06f,    3.1953800f,    0.0f,    0.0f,    0.99963800f,    -0.0268922f},
    {5202.05f,    -1763.47f,    1361.68f,    2.5945500f,    0.0f,    0.0f,    0.96282600f,     0.2701220f},
    {5194.74f,    -1766.66f,    1356.94f,    0.0734191f,    0.0f,    0.0f,    0.03670130f,     0.9993260f},
    {5159.67f,    -1832.97f,    1344.50f,    5.1745700f,    0.0f,    0.0f,    0.52635600f,    -0.8502640f},
    {5096.17f,    -1858.73f,    1332.46f,    5.3002100f,    0.0f,    0.0f,    0.47193900f,    -0.8816310f},
    {5110.70f,    -1856.59f,    1342.84f,    5.9756400f,    0.0f,    0.0f,    0.15316700f,    -0.9882000f},
    {5109.76f,    -1855.30f,    1332.38f,    4.8957200f,    0.0f,    0.0f,    0.63941100f,    -0.7688650f},
    {5068.95f,    -1837.37f,    1328.81f,    2.6156900f,    0.0f,    0.0f,    0.96562800f,     0.2599300f},
    {5064.40f,    -1824.77f,    1329.02f,    2.1640900f,    0.0f,    0.0f,    0.88292000f,     0.4695240f},
    {5059.89f,    -1848.79f,    1329.59f,    0.0709955f,    0.0f,    0.0f,    0.03549030f,     0.9993700f},
    {5014.37f,    -1851.39f,    1322.56f,    4.6694900f,    0.0f,    0.0f,    0.72211100f,    -0.6917770f},
    {5025.10f,    -1848.27f,    1323.39f,    4.4456500f,    0.0f,    0.0f,    0.79485400f,    -0.6068010f},
    {4942.63f,    -1890.13f,    1326.59f,    3.2871900f,    0.0f,    0.0f,    0.99735100f,    -0.0727343f},
    {4937.95f,    -1888.71f,    1352.41f,    3.4167800f,    0.0f,    0.0f,    0.99054900f,    -0.1371600f},
    {4922.48f,    -1881.92f,    1352.41f,    5.0307700f,    0.0f,    0.0f,    0.58607500f,    -0.8102570f},
    {4915.35f,    -1894.32f,    1351.24f,    6.2245700f,    0.0f,    0.0f,    0.02930480f,    -0.9995710f},
    {4922.71f,    -1904.84f,    1352.56f,    1.3786600f,    0.0f,    0.0f,    0.63602000f,     0.7716720f},
    {4932.89f,    -1905.49f,    1352.56f,    1.8970200f,    0.0f,    0.0f,    0.81254900f,     0.5828930f},
    {5011.83f,    -1861.05f,    1345.86f,    4.4377700f,    0.0f,    0.0f,    0.79723900f,    -0.6036640f},
    {5011.83f,    -1861.05f,    1363.26f,    4.7480000f,    0.0f,    0.0f,    0.69440600f,    -0.7195830f},
    {5021.46f,    -1858.35f,    1342.17f,    4.8618800f,    0.0f,    0.0f,    0.65232900f,    -0.7579360f},
    {4995.02f,    -1698.30f,    1370.38f,    6.1577900f,    0.0f,    0.0f,    0.06265790f,    -0.9980350f},
    {5119.85f,    -1728.90f,    1336.04f,    5.8711200f,    0.0f,    0.0f,    0.20457900f,    -0.9788500f},
    {5214.75f,    -1751.02f,    1342.50f,    5.0896500f,    0.0f,    0.0f,    0.56197200f,    -0.8271560f},
    {5075.04f,    -1822.43f,    1328.87f,    3.9995100f,    0.0f,    0.0f,    0.90940000f,    -0.4159240f},
    {5057.09f,    -1823.32f,    1350.35f,    3.8816900f,    0.0f,    0.0f,    0.93231000f,    -0.3616590f},
    {4984.60f,    -1816.99f,    1329.21f,    3.0530800f,    0.0f,    0.0f,    0.99902100f,     0.0442417f},
    {4983.35f,    -1811.55f,    1356.82f,    3.3397500f,    0.0f,    0.0f,    0.99509600f,    -0.0989170f},
    {4984.11f,    -1825.73f,    1350.76f,    2.2637500f,    0.0f,    0.0f,    0.90521100f,     0.4249620f},
    {4968.47f,    -1786.46f,    1354.09f,    3.0766300f,    0.0f,    0.0f,    0.99947300f,     0.0324733f},
    {5061.82f,    -1751.16f,    1339.07f,    5.9472700f,    0.0f,    0.0f,    0.16717100f,    -0.9859280f},
    {5063.75f,    -1763.00f,    1351.91f,    0.7597070f,    0.0f,    0.0f,    0.37078400f,     0.9287190f},
    {5078.65f,    -1708.26f,    1353.90f,    1.2702200f,    0.0f,    0.0f,    0.59326400f,     0.8050080f},
    {4983.19f,    -1755.96f,    1331.13f,    4.2822100f,    0.0f,    0.0f,    0.84173300f,    -0.5398940f},
    {4972.76f,    -1755.30f,    1332.50f,    4.2193800f,    0.0f,    0.0f,    0.85827600f,    -0.5131880f},
    {4961.65f,    -1760.82f,    1351.69f,    3.5651500f,    0.0f,    0.0f,    0.97765900f,    -0.2101980f},
    {5086.45f,    -1779.83f,    1321.62f,    6.2315700f,    0.0f,    0.0f,    0.02580510f,    -0.9996670f},
    {5063.15f,    -1756.74f,    1328.56f,    0.8869260f,    0.0f,    0.0f,    0.42907000f,     0.9032710f},
    {5042.45f,    -1800.61f,    1323.88f,    2.5009300f,    0.0f,    0.0f,    0.94913100f,     0.3148800f},
    {5084.74f,    -1725.35f,    1327.89f,    1.6503400f,    0.0f,    0.0f,    0.73466300f,     0.6784320f},
    {4993.25f,    -1758.10f,    1331.07f,    3.4999500f,    0.0f,    0.0f,    0.98399000f,    -0.1782230f},
    {5078.53f,    -1867.85f,    1348.91f,    5.8561200f,    0.0f,    0.0f,    0.21191300f,    -0.9772880f},
    {5080.74f,    -1869.73f,    1333.18f,    6.1820600f,    0.0f,    0.0f,    0.05054240f,    -0.9987220f},
    {5089.55f,    -1894.13f,    1356.08f,    1.5207200f,    0.0f,    0.0f,    0.68918100f,     0.7245890f},
    {5113.24f,    -1899.49f,    1363.77f,    1.5010800f,    0.0f,    0.0f,    0.68203400f,     0.7313210f},
    {4984.18f,    -1907.69f,    1325.62f,    3.8219300f,    0.0f,    0.0f,    0.94269800f,    -0.3336460f},
    {5094.14f,    -2432.08f,    1429.38f,    4.7008300f,    0.0f,    0.0f,    0.71118200f,    -0.7030070f},
    {5329.89f,    -2113.30f,    1281.06f,    5.6056000f,    0.0f,    0.0f,    0.33234700f,    -0.9431570f},
    {5170.87f,    -2148.13f,    1278.32f,    1.6354000f,    0.0f,    0.0f,    0.72957300f,     0.6839030f},
    {5132.94f,    -1960.25f,    1367.80f,    3.6978700f,    0.0f,    0.0f,    0.96156800f,    -0.2745660f},
    {5280.82f,    -2351.55f,    1431.57f,    4.4691300f,    0.0f,    0.0f,    0.78767700f,    -0.6160880f},
    {5176.78f,    -2121.43f,    1295.27f,    3.2415300f,    0.0f,    0.0f,    0.99875200f,    -0.0499500f},
    {5332.75f,    -2101.41f,    1296.37f,    5.5035000f,    0.0f,    0.0f,    0.38004300f,    -0.9249690f},
    {5265.70f,    -2050.27f,    1287.57f,    0.5005100f,    0.0f,    0.0f,    0.24765500f,     0.9688480f},
    {5194.21f,    -2129.89f,    1274.04f,    3.0805300f,    0.0f,    0.0f,    0.99953400f,     0.0305272f},
    {5225.81f,    -1985.50f,    1364.15f,    0.3724700f,    0.0f,    0.0f,    0.18516300f,     0.9827080f},
    {5339.46f,    -2204.47f,    1280.45f,    0.9992100f,    0.0f,    0.0f,    0.47908100f,     0.8777710f},
    {5269.63f,    -2020.57f,    1299.62f,    3.0020100f,    0.0f,    0.0f,    0.99756600f,     0.0697332f},
    {5111.54f,    -2445.70f,    1435.31f,    2.7098300f,    0.0f,    0.0f,    0.97678800f,     0.2142070f},
    {5111.24f,    -1901.14f,    1355.33f,    1.6102800f,    0.0f,    0.0f,    0.72092900f,     0.6930090f},
    {5310.42f,    -2207.82f,    1277.46f,    0.5044100f,    0.0f,    0.0f,    0.24954400f,     0.9683630f},
    {5150.81f,    -2042.13f,    1394.30f,    2.2103100f,    0.0f,    0.0f,    0.89353400f,     0.4489950f},
    {5224.84f,    -2376.61f,    1366.33f,    5.0621000f,    0.0f,    0.0f,    0.57331100f,    -0.8193380f},
    {5105.41f,    -2454.86f,    1446.16f,    4.6458400f,    0.0f,    0.0f,    0.73023900f,    -0.6831910f},
    {5309.65f,    -2188.28f,    1266.84f,    5.5663100f,    0.0f,    0.0f,    0.35081100f,    -0.9364460f},
    {5281.46f,    -2047.82f,    1287.67f,    2.4490900f,    0.0f,    0.0f,    0.94065200f,     0.3393730f},
    {5325.45f,    -2189.41f,    1309.60f,    6.2378300f,    0.0f,    0.0f,    0.02267710f,    -0.9997430f},
    {5190.96f,    -2142.54f,    1293.03f,    6.2566800f,    0.0f,    0.0f,    0.01325440f,    -0.9999120f},
    {5089.99f,    -2467.49f,    1441.80f,    0.7738100f,    0.0f,    0.0f,    0.37732600f,     0.9260800f},
    {5195.08f,    -2129.01f,    1285.36f,    3.5572700f,    0.0f,    0.0f,    0.97848000f,    -0.2063440f},
    {5353.76f,    -2116.28f,    1299.27f,    6.1789400f,    0.0f,    0.0f,    0.05210060f,    -0.9986420f},
    {5271.14f,    -2037.38f,    1299.24f,    4.0787900f,    0.0f,    0.0f,    0.89220100f,    -0.4516380f},
    {5332.50f,    -2181.28f,    1279.95f,    4.6906000f,    0.0f,    0.0f,    0.71476800f,    -0.6993620f},
    {5108.20f,    -2429.84f,    1427.73f,    4.5194000f,    0.0f,    0.0f,    0.77194300f,    -0.6356910f}
};

float HordeFirePos[65][8]=//spawn points for the fire visuals (GO) in the horde base
{
    {5524.11f,    -2612.73f,    1483.38f,    1.9619800f,    0.0f,    0.0f,    0.8310470f,    0.55620200f},
    {5514.42f,    -2617.19f,    1505.77f,    1.8245300f,    0.0f,    0.0f,    0.7908920f,    0.61195600f},
    {5510.21f,    -2624.77f,    1485.34f,    1.7106500f,    0.0f,    0.0f,    0.7547830f,    0.65597400f},
    {5570.72f,    -2619.04f,    1487.62f,    0.7288980f,    0.0f,    0.0f,    0.3564350f,    0.93432000f},
    {5570.29f,    -2639.37f,    1487.31f,    1.4930800f,    0.0f,    0.0f,    0.6791040f,    0.73404200f},
    {5583.56f,    -2637.20f,    1503.78f,    1.4655900f,    0.0f,    0.0f,    0.6689510f,    0.74330700f},
    {5571.53f,    -2626.81f,    1510.99f,    0.3621070f,    0.0f,    0.0f,    0.1800660f,    0.98365400f},
    {5545.97f,    -2659.62f,    1489.64f,    5.0705500f,    0.0f,    0.0f,    0.5698450f,    -0.8217520f},
    {5557.44f,    -2675.91f,    1482.58f,    1.7011800f,    0.0f,    0.0f,    0.7516710f,    0.65953900f},
    {5594.98f,    -2742.31f,    1495.51f,    4.5993000f,    0.0f,    0.0f,    0.7459400f,    -0.6660130f},
    {5599.65f,    -2755.60f,    1505.05f,    1.6689600f,    0.0f,    0.0f,    0.7409470f,    0.67156400f},
    {5565.95f,    -2774.75f,    1499.48f,    6.2242500f,    0.0f,    0.0f,    0.0294611f,    -0.9995660f},
    {5567.10f,    -2769.70f,    1511.17f,    5.9925700f,    0.0f,    0.0f,    0.1447990f,    -0.9894610f},
    {5572.84f,    -2774.16f,    1527.06f,    0.8364280f,    0.0f,    0.0f,    0.4061290f,    0.91381600f},
    {5538.32f,    -2805.94f,    1498.87f,    4.3008200f,    0.0f,    0.0f,    0.8366740f,    -0.5477010f},
    {5515.66f,    -2801.74f,    1503.53f,    5.5731600f,    0.0f,    0.0f,    0.3476020f,    -0.9376420f},
    {5516.76f,    -2827.14f,    1501.15f,    0.3502600f,    0.0f,    0.0f,    0.1742360f,    0.98470400f},
    {5536.13f,    -2813.51f,    1537.21f,    4.5168100f,    0.0f,    0.0f,    0.7727650f,    -0.6346920f},
    {5525.05f,    -2825.16f,    1538.53f,    0.4892750f,    0.0f,    0.0f,    0.2422050f,    0.97022500f},
    {5534.42f,    -2815.45f,    1562.84f,    4.6283400f,    0.0f,    0.0f,    0.7361910f,    -0.6767740f},
    {5519.64f,    -2831.12f,    1526.46f,    0.6110080f,    0.0f,    0.0f,    0.3007740f,    0.95369600f},
    {5551.04f,    -2827.55f,    1523.50f,    3.3520600f,    0.0f,    0.0f,    0.9944680f,    -0.1050400f},
    {5469.22f,    -2802.87f,    1503.50f,    4.9950900f,    0.0f,    0.0f,    0.6004360f,    -0.7996730f},
    {5427.80f,    -2737.26f,    1487.12f,    1.7867300f,    0.0f,    0.0f,    0.7791860f,    0.62679300f},
    {5454.10f,    -2709.10f,    1485.92f,    3.0355200f,    0.0f,    0.0f,    0.9985940f,    0.05301370f},
    {5436.30f,    -2718.20f,    1506.02f,    2.7567000f,    0.0f,    0.0f,    0.9815390f,    0.19126100f},
    {5412.60f,    -2740.55f,    1510.79f,    2.9844600f,    0.0f,    0.0f,    0.9969150f,    0.07848320f},
    {5406.12f,    -2752.48f,    1521.01f,    2.0576900f,    0.0f,    0.0f,    0.8567050f,    0.51580700f},
    {5445.24f,    -2676.35f,    1521.89f,    2.9137800f,    0.0f,    0.0f,    0.9935200f,    0.11366100f},
    {5481.40f,    -2665.08f,    1482.23f,    4.3000100f,    0.0f,    0.0f,    0.8368950f,    -0.5473630f},
    {5443.51f,    -2675.44f,    1487.12f,    2.9098600f,    0.0f,    0.0f,    0.9932950f,    0.11560600f},
    {5391.72f,    -2647.30f,    1528.90f,    3.7698700f,    0.0f,    0.0f,    0.9510630f,    -0.3089970f},
    {5421.09f,    -2734.12f,    1521.01f,    2.7056700f,    0.0f,    0.0f,    0.9763400f,    0.21624200f},
    {5405.39f,    -2710.33f,    1533.77f,    2.5132400f,    0.0f,    0.0f,    0.9510520f,    0.30903200f},
    {5423.96f,    -2703.76f,    1516.34f,    2.7920600f,    0.0f,    0.0f,    0.9847670f,    0.17387900f},
    {5444.75f,    -2735.23f,    1486.37f,    2.2265700f,    0.0f,    0.0f,    0.8971550f,    0.44171500f},
    {5570.98f,    -2747.91f,    1495.70f,    5.1443300f,    0.0f,    0.0f,    0.5391500f,    -0.8422100f},
    {5567.79f,    -2673.90f,    1484.66f,    2.7252900f,    0.0f,    0.0f,    0.9784150f,    0.20665000f},
    {5600.71f,    -2696.80f,    1500.42f,    0.4437040f,    0.0f,    0.0f,    0.2200360f,    0.97549200f},
    {5600.70f,    -2693.04f,    1515.20f,    5.1600300f,    0.0f,    0.0f,    0.5325220f,    -0.8464160f},
    {5627.56f,    -2839.66f,    1510.53f,    5.4152700f,    0.0f,    0.0f,    0.4204630f,    -0.9073090f},
    {5622.02f,    -2868.71f,    1516.22f,    2.2548200f,    0.0f,    0.0f,    0.9033030f,    0.42900200f},
    {5586.61f,    -2878.97f,    1510.34f,    4.5560400f,    0.0f,    0.0f,    0.7601700f,    -0.6497240f},
    {5583.78f,    -2843.71f,    1509.54f,    5.3571500f,    0.0f,    0.0f,    0.4466500f,    -0.8947090f},
    {5580.95f,    -2811.30f,    1513.30f,    3.5758700f,    0.0f,    0.0f,    0.9765180f,    -0.2154340f},
    {5542.52f,    -2869.31f,    1523.13f,    5.2330400f,    0.0f,    0.0f,    0.5012750f,    -0.8652880f},
    {5557.35f,    -2866.36f,    1518.76f,    4.4829900f,    0.0f,    0.0f,    0.7833880f,    -0.6215330f},
    {5380.91f,    -2849.36f,    1512.81f,    3.9096200f,    0.0f,    0.0f,    0.9271680f,    -0.3746460f},
    {5395.76f,    -2881.41f,    1521.11f,    4.2842600f,    0.0f,    0.0f,    0.8411800f,    -0.5407550f},
    {5374.87f,    -2859.63f,    1528.98f,    3.3025200f,    0.0f,    0.0f,    0.9967650f,    -0.0803745f},
    {5356.07f,    -2854.66f,    1520.34f,    5.8393300f,    0.0f,    0.0f,    0.2201080f,    -0.9754750f},
    {5363.01f,    -2975.72f,    1539.02f,    4.1373800f,    0.0f,    0.0f,    0.8785900f,    -0.4775760f},
    {5336.85f,    -2980.74f,    1561.24f,    5.1112600f,    0.0f,    0.0f,    0.5530010f,    -0.8331800f},
    {5335.23f,    -2974.62f,    1540.05f,    5.0445100f,    0.0f,    0.0f,    0.5804960f,    -0.8142630f},
    {5422.37f,    -2998.87f,    1549.98f,    4.5183100f,    0.0f,    0.0f,    0.7722880f,    -0.6352720f},
    {5405.54f,    -3014.60f,    1562.16f,    5.8676100f,    0.0f,    0.0f,    0.2062980f,    -0.9784890f},
    {5427.96f,    -3019.40f,    1561.58f,    3.5349800f,    0.0f,    0.0f,    0.9807180f,    -0.1954300f},
    {5348.12f,    -2977.84f,    1582.47f,    3.9402500f,    0.0f,    0.0f,    0.9213230f,    -0.3887990f},
    {5331.12f,    -2993.71f,    1576.14f,    0.0642734f,    0.0f,    0.0f,    0.0321311f,    0.99948400f},
    {5321.63f,    -2986.55f,    1552.20f,    5.2950300f,    0.0f,    0.0f,    0.4742190f,    -0.8804070f},
    {5292.10f,    -2914.36f,    1529.52f,    2.9742000f,    0.0f,    0.0f,    0.9964990f,    0.08360100f},
    {5281.77f,    -2926.50f,    1530.62f,    1.6782900f,    0.0f,    0.0f,    0.7440710f,    0.66810000f},
    {5287.19f,    -2909.94f,    1543.49f,    3.3119200f,    0.0f,    0.0f,    0.9963760f,    -0.0850591f},
    {5534.15f,    -2679.35f,    1483.61f,    0.4286850f,    0.0f,    0.0f,    0.2127050f,    0.97711600f},
    {5545.43f,    -2647.82f,    1483.05f,    5.3884800f,    0.0f,    0.0f,    0.4325780f,    -0.9015960f}
};

hyjalAI::hyjalAI(Creature *c) : npc_escortAI(c), Summons(me)
{
    pInstance = ((InstanceScript*)c->GetInstanceScript());
    VeinsSpawned[0] = false;
    VeinsSpawned[1] = false;
    for(uint64 & i : VeinGUID)
        i = 0;
    InfernalCount = 0;
    TeleportTimer = 1000;
    Overrun = false;
    Teleported = false;
    WaitForTeleport = false;
    OverrunCounter = 0;
    OverrunCounter2 = 0;
    InfernalPoint = 0;
    RespawnTimer = 10000;
    DoHide = false;
    MassTeleportTimer = 0;
    DoMassTeleport = false;
    Wipe = false;
    
     //Initialize spells
    memset(Spell, 0, sizeof(Spell));
}

void hyjalAI::JustSummoned(Creature *summoned)
{
    Summons.Summon(summoned);
}

void hyjalAI::SummonedCreatureDespawn(Creature* summoned)
{
    Summons.Despawn(summoned);
}

void hyjalAI::Reset()
{
    IsDummy = false;
    me->SetKeepActive(true);
    // GUIDs
    PlayerGUID = 0;
    BossGUID[0] = 0;
    BossGUID[1] = 0;

    // Timers
    NextWaveTimer = 10000;
    CheckTimer = 0;
    RetreatTimer = 1000;

    // Misc
    if (Wipe)
        WaveCount = 0;
    else if (pInstance)
        WaveCount = pInstance->GetData(DATA_CURRENT_WAVE);

    if (pInstance)
        pInstance->SetData(DATA_CURRENT_WAVE, WaveCount);

    // Set faction properly based on creature entry
    switch(me->GetEntry())
    {
        case JAINA:
            Faction = 0;
            DoCast(me, SPELL_BRILLIANCE_AURA, true);
            break;

        case THRALL:
            Faction = 1;
            break;

        case TYRANDE:
            Faction = 2;
            break;
    }

    //Bools
    EventBegun = false;
    FirstBossDead = false;
    SecondBossDead = false;
    Summon = false;
    bRetreat = false;
    Debug = false;


    //Flags
    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

    //Reset Instance Data for trash count
    if(pInstance)
    {
        if((!pInstance->GetData(DATA_ALLIANCE_RETREAT) && me->GetEntry() == JAINA) || (pInstance->GetData(DATA_ALLIANCE_RETREAT) && me->GetEntry() == THRALL))
        {
            //Reset World States
            UpdateWorldState(WORLD_STATE_WAVES, 0);
            UpdateWorldState(WORLD_STATE_ENEMY, 0);
            UpdateWorldState(WORLD_STATE_ENEMYCOUNT, 0);
            pInstance->SetData(DATA_RESET_TRASH_COUNT, 0);
        }
    }else error_log(ERROR_INST_DATA);

    //Visibility
    DoHide = true;
}

void hyjalAI::EnterEvadeMode(EvadeReason /* why */)
{
    me->InterruptNonMeleeSpells(true);
    if(me->GetEntry() != JAINA)
        me->RemoveAllAuras();
    me->GetThreatManager().ClearAllThreat();
    me->CombatStop();
    me->InitCreatureAddon(true);

    if(me->IsAlive())
        me->GetMotionMaster()->MoveTargetedHome();

    me->SetLootRecipient(nullptr);
}

void hyjalAI::EnterCombat(Unit *who)
{
    if(IsDummy)return;
    for(uint8 i = 0; i < 2; ++i)
        if(Spell[i].Cooldown)
            SpellTimer[i] = Spell[i].Cooldown / 2;

    Talk(ATTACKED);

    if(me->GetEntry() == CREATURE_JAINA)
        if(pInstance)
            pInstance->SetData(DATA_JAINAINCOMBAT,1); //Call for help
}

void hyjalAI::MoveInLineOfSight(Unit *who)
{
    if(IsDummy)
        return;

    if(HasEscortState(STATE_ESCORT_ESCORTING) && !GetAttack())
        return;

    if(me->GetVictim() || me->CanAggro(who) != CAN_ATTACK_RESULT_OK)
        return;

    AttackStart(who);
}

void hyjalAI::SummonCreature(uint32 entry, float Base[4][3])
{
    uint32 random = rand()%4;
    float SpawnLoc[3];

    for(uint8 i = 0; i < 3; ++i)
    {
        SpawnLoc[i] = Base[random][i];
    }
    Creature* pCreature = nullptr;
    switch(entry)
    {
            case 17906:    //GARGOYLE

                if(!FirstBossDead && (WaveCount == 1 || WaveCount == 3))
                {//summon at tower
                    pCreature = me->SummonCreature(entry, SpawnPointSpecial[SPAWN_NEAR_TOWER][0]+irand(-20,20), SpawnPointSpecial[SPAWN_NEAR_TOWER][1]+irand(-20,20), SpawnPointSpecial[SPAWN_NEAR_TOWER][2]+irand(-10,10), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 2*MINUTE*IN_MILLISECONDS);
                    if(pCreature)
                        ((hyjal_trashAI*)pCreature->AI())->useFlyPath = true;
                }else{//summon at gate
                    pCreature = me->SummonCreature(entry, SpawnPointSpecial[SPAWN_GARG_GATE][0]+irand(-10,10), SpawnPointSpecial[SPAWN_GARG_GATE][1]+irand(-10,10), SpawnPointSpecial[SPAWN_GARG_GATE][2]+irand(-10,10), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 2*MINUTE*IN_MILLISECONDS);
                }
                break;
            case 17907:    //FROST_WYRM ,
                if(FirstBossDead && WaveCount == 1)
                {//summon at gate
                    pCreature = me->SummonCreature(entry, SpawnPointSpecial[SPAWN_WYRM_GATE][0],SpawnPointSpecial[SPAWN_WYRM_GATE][1],SpawnPointSpecial[SPAWN_WYRM_GATE][2], 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 2*MINUTE*IN_MILLISECONDS);
                }else{
                    pCreature = me->SummonCreature(entry, SpawnPointSpecial[SPAWN_NEAR_TOWER][0], SpawnPointSpecial[SPAWN_NEAR_TOWER][1],SpawnPointSpecial[SPAWN_NEAR_TOWER][2], 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 2*MINUTE*IN_MILLISECONDS);
                    if(pCreature)
                        ((hyjal_trashAI*)pCreature->AI())->useFlyPath = true;
                }
                break;
            case 17908:    //GIANT_INFERNAL
                InfernalCount++;
                if(InfernalCount > 7)InfernalCount = 0;
                pCreature = me->SummonCreature(entry, InfernalPos[InfernalCount][0], InfernalPos[InfernalCount][1], InfernalPos[InfernalCount][2], 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 2*MINUTE*IN_MILLISECONDS);
                break;
            case RAGE_WINTERCHILL:
            case ANETHERON:
            case KAZROGAL:
            case AZGALOR:
                pCreature = me->SummonCreature(entry, SpawnLoc[0], SpawnLoc[1], SpawnLoc[2], 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20*MINUTE*IN_MILLISECONDS);
                break;
            default:
                pCreature = me->SummonCreature(entry, SpawnLoc[0], SpawnLoc[1], SpawnLoc[2], 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 2*MINUTE*IN_MILLISECONDS);
                break;

    }

    if(pCreature)
    {
        // Increment Enemy Count to be used in World States and instance script
        ++EnemyCount;

        pCreature->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
        pCreature->SetKeepActive(true);
        switch(entry)
        {
            case NECROMANCER:
            case ABOMINATION:
            case GHOUL:
            case BANSHEE:
            case CRYPT_FIEND:
            case GARGOYLE:
            case FROST_WYRM:
            case GIANT_INFERNAL:
            case FEL_STALKER:
            case RAGE_WINTERCHILL:
            case ANETHERON:
            case KAZROGAL:
            case AZGALOR:
                ((hyjal_trashAI*)pCreature->AI())->IsEvent = true;
                break;
        }
        if(pInstance)
        {
            if(pInstance->GetData(DATA_RAIDDAMAGE) < MINRAIDDAMAGE)
                pCreature->SetDisableReputationGain(true);//no repu for solo farming
        }
        // Check if creature is a boss.
        if (pCreature->IsWorldBoss())
        {
            if(!FirstBossDead)  BossGUID[0] = pCreature->GetGUID();
            else                BossGUID[1] = pCreature->GetGUID();
            CheckTimer = 5000;
        }
    }
}

void hyjalAI::SummonNextWave(Wave wave[18], uint32 Count, float Base[4][3])
{
    if (pInstance)
        pInstance->SetData(DATA_CURRENT_WAVE, WaveCount);

    // 1 in 4 chance we give a rally yell. Not sure if the chance is offilike.
    if (rand()%4 == 0)
        Talk(RALLY);

    if(!pInstance)
    {
        error_log(ERROR_INST_DATA);
        return;
    }
    InfernalCount = 0;//reset infernal count every new wave

    EnemyCount = pInstance->GetData(DATA_TRASH);
    for(uint32 i : wave[Count].Mob)
    {
        if(i)
            SummonCreature(i, Base);
    }

    if(!wave[Count].IsBoss)
    {
        uint32 stateValue = Count+1;
        if(FirstBossDead)
            stateValue -= 9;                                // Subtract 9 from it to give the proper wave number if we are greater than 8
        UpdateWorldState(WORLD_STATE_WAVES, stateValue);    // Set world state to our current wave number
        UpdateWorldState(WORLD_STATE_ENEMY, 1);             // Enable world state

        if(pInstance) pInstance->SetData(DATA_TRASH, EnemyCount);         // Send data for instance script to update count

        if(!Debug)
            NextWaveTimer = wave[Count].WaveTimer;
        else
        {
            NextWaveTimer = 15000;
        }
    }
    else
    {
        UpdateWorldState(WORLD_STATE_WAVES, 0);             // Set world state for waves to 0 to disable it.
        UpdateWorldState(WORLD_STATE_ENEMY, 1);
        UpdateWorldState(WORLD_STATE_ENEMYCOUNT, 1);        // Set World State for enemies invading to 1.
        Summon = false;
    }
    CheckTimer = 5000;
}

void hyjalAI::StartEvent(Player* player)
{
    if(!player || IsDummy)
        return;
        
    Wipe = true;

    Talk(BEGIN);

    EventBegun = true;
    Summon = true;

    NextWaveTimer = 15000;
    CheckTimer = 5000;
    PlayerGUID = player->GetGUID();

    UpdateWorldState(WORLD_STATE_WAVES, 0);
    UpdateWorldState(WORLD_STATE_ENEMY, 0);
    UpdateWorldState(WORLD_STATE_ENEMYCOUNT, 0);

    DeSpawnVeins();
}

uint32 hyjalAI::GetInstanceScript(uint32 Event)
{
    if(pInstance)
        return pInstance->GetData(Event);
    else error_log(ERROR_INST_DATA);

    return 0;
}

void hyjalAI::Talk(uint32 id)
{
    std::list<uint8> index;
    for(uint8 i = 0; i < 10; i++)
    {
        if(Faction == 0)                                    // Alliance
        {
            if(JainaQuotes[i].id == id)
                index.push_back(i);
        }
        else if(Faction == 1)                               // Horde
        {
            if(ThrallQuotes[i].id == id)
                index.push_back(i);
        }
    }

    if(index.empty())
        return;                                             // No quotes found, no use to continue

    uint8 ind = *(index.begin()) + rand()%index.size();

    int32 YellId = 0;
    if(Faction == 0)                                        // Alliance
    {
        YellId = JainaQuotes[ind].textid;
    }
    else if(Faction == 1)                                   // Horde
    {
        YellId = ThrallQuotes[ind].textid;
    }

    if (YellId)
        DoScriptText(YellId, me);
}

void hyjalAI::UpdateWorldState(uint32 id, uint32 state)
{
    Map * map = me->GetMap();

    if(!map->IsDungeon())
        return;

    Map::PlayerList const& players = map->GetPlayers();

    if (!players.isEmpty())
    {
            for(const auto & itr : players)
            {
                if (Player* player = itr.GetSource())
                    player->SendUpdateWorldState(id,state);
            }
    }else TC_LOG_ERROR("scripts","HyjalAI: UpdateWorldState, but PlayerList is empty");
}

void hyjalAI::Retreat()
{
    if(pInstance)
    {
        if(Faction == 0)
        {
            pInstance->SetData(DATA_ALLIANCE_RETREAT, 1);
            AddWaypoint(0,JainaWPs[0][0],JainaWPs[0][1],JainaWPs[0][2]);
            AddWaypoint(1,JainaWPs[1][0],JainaWPs[1][1],JainaWPs[1][2]);
            Start(false, false, false);
            SetDespawnAtEnd(false);//move to center of alliance base
            Talk(SUCCESS);
        }
        if(Faction == 1)
        {
            pInstance->SetData(DATA_HORDE_RETREAT, 1);
            Creature* JainaDummy = me->SummonCreature(JAINA,JainaDummySpawn[0][0],JainaDummySpawn[0][1],JainaDummySpawn[0][2],JainaDummySpawn[0][3],TEMPSUMMON_TIMED_DESPAWN,60000);
            if(JainaDummy)
            {
                JainaDummy->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                ((hyjalAI*)JainaDummy->AI())->IsDummy = true;
                DummyGuid = JainaDummy->GetGUID();
            }
            AddWaypoint(0,JainaDummySpawn[1][0],JainaDummySpawn[1][1],JainaDummySpawn[1][2]);
            Start(false, false, false);
            SetDespawnAtEnd(false);//move to center of horde base
            if(Creature* archimonde = me->GetMap()->GetCreature(pInstance->GetData64(DATA_ARCHIMONDE)))
                DoScriptText(TEXT_ARCHIMONDE_AT_HORDE_RETREAT, archimonde); //Not ok, not enough range
        }
    }
    SpawnVeins();
    Overrun = true;
    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);//cant talk after overrun event started
}

void hyjalAI::SpawnVeins()
{
    if(Faction == 0)
    {
        if (VeinsSpawned[0])//prevent any buggers
            return;
        for (uint8 i = 0; i<7; i++)
        {
            GameObject* gem = me->SummonGameObject(ANCIENT_VEIN, Position(VeinPos[i][0],VeinPos[i][1],VeinPos[i][2],VeinPos[i][3]), G3D::Quat(VeinPos[i][4],VeinPos[i][5],VeinPos[i][6],VeinPos[i][7]),0);
            if(gem)
                VeinGUID[i]=gem->GetGUID();
        }
        VeinsSpawned[0] = true;
    }else{
        if (VeinsSpawned[1])
            return;
        for (uint8 i = 7; i<14; i++)
        {
            GameObject* gem = me->SummonGameObject(ANCIENT_VEIN,Position(VeinPos[i][0],VeinPos[i][1],VeinPos[i][2],VeinPos[i][3]), G3D::Quat(VeinPos[i][4],VeinPos[i][5],VeinPos[i][6],VeinPos[i][7]),0);
            if(gem)
                VeinGUID[i]=gem->GetGUID();
        }
        VeinsSpawned[1] = true;
    }
}

void hyjalAI::DeSpawnVeins()
{
    if(!pInstance)return;
    if(Faction == 1)
    {
        Creature* pUnit=ObjectAccessor::GetCreature((*me),pInstance->GetData64(DATA_JAINAPROUDMOORE));
        if (!pUnit)return;
        hyjalAI* ai = ((hyjalAI*)pUnit->AI());
        if(!ai)return;
        for (uint8 i = 0; i<7; i++)
        {
            GameObject* gem = GameObject::GetGameObject((*me), ai->VeinGUID[i]);
            if(gem)
                gem->RemoveFromWorld();
        }
    }else if (Faction)
    {
        Creature* pUnit=ObjectAccessor::GetCreature((*me),pInstance->GetData64(DATA_THRALL));
        if (!pUnit)return;
        hyjalAI* ai = ((hyjalAI*)pUnit->AI());
        if(!ai)return;
        for (uint8 i = 7; i<14; i++)
        {
            GameObject* gem = GameObject::GetGameObject((*me), ai->VeinGUID[i]);
            if(gem)
                gem->RemoveFromWorld();
        }
    }
}

void hyjalAI::UpdateAI(const uint32 diff)
{
    if(IsDummy)
    {
        if(MassTeleportTimer < diff && DoMassTeleport)
        {
            me->CastSpell(me,SPELL_MASS_TELEPORT,false);
            DoMassTeleport = false;
        }else MassTeleportTimer -= diff;
        return;
    }
    if(DoHide)
    {
        DoHide = false;
        switch(me->GetEntry())
        {
            case JAINA:
                if(pInstance && pInstance->GetData(DATA_ALLIANCE_RETREAT))
                {
                    me->SetVisible(false);
                    HideNearPos(me->GetPositionX(), me->GetPositionY());
                    HideNearPos(5037.76, -1889.71);
                    for(auto & AllianceFirePo : AllianceFirePos)//summon fires
                        me->SummonGameObject(FLAMEOBJECT,Position(AllianceFirePo[0],AllianceFirePo[1],AllianceFirePo[2],AllianceFirePo[3]), G3D::Quat(AllianceFirePo[4],AllianceFirePo[5],AllianceFirePo[6],AllianceFirePo[7]),0);

                }
                else me->SetVisible(true);
                break;
            case THRALL: //thrall
                if(pInstance && pInstance->GetData(DATA_HORDE_RETREAT))
                {
                    me->SetVisible(false);
                    HideNearPos(me->GetPositionX(), me->GetPositionY());
                    HideNearPos(5563, -2763.19);
                    HideNearPos(5542.2, -2629.36);
                    for(auto & HordeFirePo : HordeFirePos)//summon fires
                        me->SummonGameObject(FLAMEOBJECT,Position(HordeFirePo[0],HordeFirePo[1],HordeFirePo[2],HordeFirePo[3]), G3D::Quat(HordeFirePo[4],HordeFirePo[5],HordeFirePo[6],HordeFirePo[7]),0);

                }
                else me->SetVisible(true);
                break;
        }
    }
    if(RespawnTimer)
    {
        if(RespawnTimer <= diff)
        {
            RespawnTimer = 0;
            //respawn creatures nearby
            RespawnNearPos(me->GetPositionX(), me->GetPositionY());
            if(Faction == 0)
            {
                RespawnNearPos(5037.76, -1889.71);
            }else if (Faction == 1)
            {
                RespawnNearPos(5563, -2763.19);
                RespawnNearPos(5542.2, -2629.36);
            }
            me->SetVisible(true);
        }else{
            RespawnTimer -= diff;
            me->SetVisible(false);
        }
        return;
    }
    if(Overrun)
        DoOverrun(Faction, diff);
    if(bRetreat)
    {
        if(RetreatTimer < diff)
        {
            IsDummy = true;
            bRetreat = false;
            HideNearPos(me->GetPositionX(), me->GetPositionY());
            switch(me->GetEntry())
            {
                case JAINA://jaina
                    HideNearPos(5037.76, -1889.71);
                    break;
                case THRALL://thrall
                    HideNearPos(5563, -2763.19);
                    HideNearPos(5542.2, -2629.36);
                    HideNearPos(5603.75, -2853.12);
                    break;
            }
            me->SetVisible(false);
        }else RetreatTimer -= diff;
    }

    if(!EventBegun)
        return;

    if(Summon)
    {
        if(pInstance && EnemyCount)
        {
            EnemyCount = pInstance->GetData(DATA_TRASH);
            if(!EnemyCount)
                NextWaveTimer = 5000;
        }

        if(NextWaveTimer < diff)
        {
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            if(Faction == 0)
                SummonNextWave(AllianceWaves, WaveCount, AllianceBase);
            else if(Faction == 1)
                SummonNextWave(HordeWaves, WaveCount, HordeBase);
            ++WaveCount;
        }else NextWaveTimer -= diff;
    }
         
    if(CheckTimer < diff)
    {
        for(uint64 & i : BossGUID)
        {
            if(i)
            {
                Unit* pUnit = ObjectAccessor::GetUnit((*me), i);
                if(pUnit && (!pUnit->IsAlive()))
                {
                    if(i == BossGUID[0])
                    {
                        Talk(INCOMING);
                        FirstBossDead = true;
                    }
                    else if(i == BossGUID[1])
                    {
                        SecondBossDead = true;
                    }
                    EventBegun = false;
                    CheckTimer = 0;
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP); 
                    i = 0;
                    UpdateWorldState(WORLD_STATE_ENEMY, 0); // Reset world state for enemies to disable it
                }
            }
        }
        CheckTimer = 5000;
    }else CheckTimer -= diff;

    if(!UpdateVictim())
        return;
    
    for(uint8 i = 0; i < 3; ++i)
    {
        if(Spell[i].SpellId)
        {
            if(SpellTimer[i] < diff)
            {
                Unit* target = nullptr;

                switch(Spell[i].TargetType)
                {
                    case TARGETTYPE_SELF: target = me; break;
                    case TARGETTYPE_RANDOM: target = SelectTarget(SELECT_TARGET_RANDOM, 0); break;
                    case TARGETTYPE_VICTIM: target = me->GetVictim(); break;
                }

                if(target && target->IsAlive())
                {
                    if(DoCast(target, Spell[i].SpellId))
                        SpellTimer[i] = Spell[i].Cooldown;
                }
            }else SpellTimer[i] -= diff;
        }
    }

    DoMeleeAttackIfReady();
}

void hyjalAI::SetData(uint32 type, uint32 data, Unit* setter)
{
    Wipe = true;
}

void hyjalAI::JustDied(Unit* killer)
{
    if(IsDummy)return;
    me->Respawn();
    me->SetVisible(false);
    RespawnTimer = 120000;
    Talk(DEATH);
    Summons.DespawnAll();//despawn all wave's summons
    if(pInstance)
    {//reset encounter if boss is despawned (ex: thrall is killed, boss despawns, event stucks at inprogress)
        if(pInstance->GetData(DATA_RAGEWINTERCHILLEVENT) == IN_PROGRESS)
            pInstance->SetData(DATA_RAGEWINTERCHILLEVENT, NOT_STARTED);
        if(pInstance->GetData(DATA_ANETHERONEVENT) == IN_PROGRESS)
            pInstance->SetData(DATA_ANETHERONEVENT, NOT_STARTED);
        if(pInstance->GetData(DATA_KAZROGALEVENT) == IN_PROGRESS)
            pInstance->SetData(DATA_KAZROGALEVENT, NOT_STARTED);
        if(pInstance->GetData(DATA_AZGALOREVENT) == IN_PROGRESS)
            pInstance->SetData(DATA_AZGALOREVENT, NOT_STARTED);

        pInstance->SetData(DATA_RESET_RAIDDAMAGE, 0);//reset damage on die
    }
}
void hyjalAI::HideNearPos(float x, float y)
{
    // First get all creatures.
    std::list<Creature*> creatures;
    Trinity::AllFriendlyCreaturesInGrid creature_check(me);
    Trinity::CreatureListSearcher<Trinity::AllFriendlyCreaturesInGrid> creature_searcher(me, creatures, creature_check);
    Cell::VisitGridObjects(me, creature_searcher, 250.0f);

    if(!creatures.empty())
    {
        for(auto & creature : creatures)
        {
            creature->SetVisible(false);
            creature->SetFaction(FACTION_FRIENDLY);//make them friendly so mobs won't attack them
        }
    }
}
void hyjalAI::RespawnNearPos(float x, float y)
{
    Trinity::RespawnDo u_do;
    Trinity::WorldObjectWorker<Trinity::RespawnDo> worker(me, u_do);
    Cell::VisitGridObjects(me, worker, 250.0f);
}

void hyjalAI::WaypointReached(uint32 i, uint32 pathID)
{
    if(i == 1 || (i == 0 && me->GetEntry() == THRALL))
    {
        WaitForTeleport = true;
        TeleportTimer = 20000;
        if(me->GetEntry() == JAINA)
        {
            DoScriptText(EMOTE_MASS_TELEPORT,me);
            me->CastSpell(me,SPELL_MASS_TELEPORT,false);
        }
        if(me->GetEntry() == THRALL && DummyGuid)
        {
            Unit* Dummy = ObjectAccessor::GetUnit((*me),DummyGuid);
            if(Dummy)
            {
                ((hyjalAI*)(Dummy->ToCreature())->AI())->DoMassTeleport = true;
                ((hyjalAI*)(Dummy->ToCreature())->AI())->MassTeleportTimer = 20000;
                Dummy->CastSpell(me,SPELL_MASS_TELEPORT,false);
                DoScriptText(EMOTE_MASS_TELEPORT,Dummy);
            }
        }
        //do some talking
        //all alive guards walk near here
        CellCoord pair(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
        Cell cell(pair);
        cell.SetNoCreate();

        // First get all creatures.
        std::list<Creature*> creatures;
        Trinity::AllFriendlyCreaturesInGrid creature_check(me);
        Trinity::CreatureListSearcher<Trinity::AllFriendlyCreaturesInGrid> creature_searcher(me, creatures, creature_check);
        Cell::VisitGridObjects(me, creature_searcher, MAX_SEARCHER_DISTANCE);

        if(!creatures.empty())
        {
            for(auto & creature : creatures)
            {
                if(creature && creature->IsAlive() && creature != me && creature->GetEntry() != JAINA)
                {
                    if(creature->GetDistance(me) >= 60)
                        creature->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    float x, y, z;
                    creature->SetDefaultMovementType(IDLE_MOTION_TYPE);
                    creature->GetMotionMaster()->Initialize();
                    float range = 10;
                    if(me->GetEntry() == THRALL)range = 20;
                    me->GetNearPoint(me, x, y, z, range, 0, me->GetAngle(creature));
                    creature->GetMotionMaster()->MovePoint(0, x+irand(-5,5), y+irand(-5,5), me->GetPositionZ());
                }
            }
        }
    }
}
void hyjalAI::DoOverrun(uint32 faction, const uint32 diff)
{
    npc_escortAI::UpdateAI(diff);
    if(WaitForTeleport)
    {
        if(TeleportTimer < diff)
        {
            std::list<Creature*> creatures;
            Trinity::AllFriendlyCreaturesInGrid creature_check(me);
            Trinity::CreatureListSearcher<Trinity::AllFriendlyCreaturesInGrid> creature_searcher(me, creatures, creature_check);
            Cell::VisitGridObjects(me, creature_searcher, MAX_SEARCHER_DISTANCE);

            if(!creatures.empty())
            {
                for(auto & creature : creatures)
                {
                    if(creature && creature->IsAlive())
                    {
                        creature->CastSpell(creature, SPELL_TELEPORT_VISUAL, true);
                        creature->SetFaction(FACTION_FRIENDLY);//make them friendly so mobs won't attack them
                        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    }
                }
                DoCast(me, SPELL_TELEPORT_VISUAL);
                bRetreat = true;
                RetreatTimer = 1000;
            }

            WaitForTeleport = false;
            Teleported = true;
        }TeleportTimer -= diff;
    }
    if(!Teleported)
        return;
    Overrun = false;//execute once
    switch(faction)
    {
        case 0://alliance
            for(auto & AllianceFirePo : AllianceFirePos)//summon fires
                me->SummonGameObject(FLAMEOBJECT,Position(AllianceFirePo[0],AllianceFirePo[1],AllianceFirePo[2],AllianceFirePo[3]), G3D::Quat(AllianceFirePo[4],AllianceFirePo[5],AllianceFirePo[6],AllianceFirePo[7]),0);

            for(uint8 i = 0; i < 25; i++)//summon 25 ghouls
            {
                uint8 r = rand()%4;
                Creature* pUnit = me->SummonCreature(GHOUL, AllianceBase[r][0]+irand(-15,15), AllianceBase[r][1]+irand(-15,15), AllianceBase[r][2], 0, TEMPSUMMON_MANUAL_DESPAWN, 2*60*IN_MILLISECONDS);
                if(pUnit)
                {
                    ((hyjal_trashAI*)pUnit->AI())->faction = Faction;
                    ((hyjal_trashAI*)pUnit->AI())->IsOverrun = true;
                    ((hyjal_trashAI*)pUnit->AI())->OverrunType = i;
                    pUnit->SetKeepActive(true);
                }
            }
            for(uint8 i = 0; i < 3; i++)//summon 3 abominations
            {
                uint8 r = rand()%4;
                Creature* pUnit = me->SummonCreature(ABOMINATION, AllianceBase[r][0]+irand(-15,15), AllianceBase[r][1]+irand(-15,15), AllianceBase[r][2], 0, TEMPSUMMON_MANUAL_DESPAWN, 2*60*IN_MILLISECONDS);
                if(pUnit)
                {
                    ((hyjal_trashAI*)pUnit->AI())->faction = Faction;
                    ((hyjal_trashAI*)pUnit->AI())->IsOverrun = true;
                    ((hyjal_trashAI*)pUnit->AI())->OverrunType = i;
                    pUnit->SetKeepActive(true);
                }
            }
            for(uint8 i = 0; i < 5; i++)//summon 5 gargoyles
            {
                Creature* pUnit = me->SummonCreature(GARGOYLE, AllianceOverrunGargPos[i][0], AllianceOverrunGargPos[i][1], AllianceOverrunGargPos[i][2], AllianceOverrunGargPos[i][3], TEMPSUMMON_MANUAL_DESPAWN, 2*60*IN_MILLISECONDS);
                if(pUnit)
                {
                    pUnit->SetHomePosition(AllianceOverrunGargPos[i][0], AllianceOverrunGargPos[i][1], AllianceOverrunGargPos[i][2], AllianceOverrunGargPos[i][3]);
                    ((hyjal_trashAI*)pUnit->AI())->faction = Faction;
                    ((hyjal_trashAI*)pUnit->AI())->IsOverrun = true;
                    ((hyjal_trashAI*)pUnit->AI())->OverrunType = i;
                    pUnit->SetKeepActive(true);
                }
            }
            break;
        case 1://horde
            for(auto & HordeFirePo : HordeFirePos)//summon fires
                me->SummonGameObject(FLAMEOBJECT,Position(HordeFirePo[0],HordeFirePo[1],HordeFirePo[2],HordeFirePo[3]), G3D::Quat(HordeFirePo[4],HordeFirePo[5],HordeFirePo[6],HordeFirePo[7]),0);

            for(uint8 i = 0; i < 26; i++)//summon infernals
            {
                Creature* pUnit = me->SummonCreature(GIANT_INFERNAL, InfernalSPWP[i][0], InfernalSPWP[i][1], InfernalSPWP[i][2], InfernalSPWP[i][3], TEMPSUMMON_MANUAL_DESPAWN, 2*60*IN_MILLISECONDS);
                if(pUnit)
                {
                    pUnit->SetHomePosition(InfernalSPWP[i][0], InfernalSPWP[i][1], InfernalSPWP[i][2], InfernalSPWP[i][3]);
                    ((hyjal_trashAI*)pUnit->AI())->faction = Faction;
                    ((hyjal_trashAI*)pUnit->AI())->IsOverrun = true;
                    ((hyjal_trashAI*)pUnit->AI())->OverrunType = i;
                    pUnit->SetKeepActive(true);
                }
            }
            for(uint8 i = 0; i < 25; i++)//summon 25 ghouls
            {
                uint8 r = rand()%4;
                Creature* pUnit = me->SummonCreature(GHOUL, HordeBase[r][0]+irand(-15,15), HordeBase[r][1]+irand(-15,15), HordeBase[r][2], 0, TEMPSUMMON_MANUAL_DESPAWN, 2*60*IN_MILLISECONDS);
                if(pUnit)
                {
                    ((hyjal_trashAI*)pUnit->AI())->faction = Faction;
                    ((hyjal_trashAI*)pUnit->AI())->IsOverrun = true;
                    ((hyjal_trashAI*)pUnit->AI())->OverrunType = i;
                    pUnit->SetKeepActive(true);
                }
            }
            for(uint8 i = 0; i < 5; i++)//summon 5 abominations
            {
                uint8 r = rand()%4;
                Creature* pUnit = me->SummonCreature(ABOMINATION, HordeBase[r][0]+irand(-15,15), HordeBase[r][1]+irand(-15,15), HordeBase[r][2], 0, TEMPSUMMON_MANUAL_DESPAWN, 2*60*IN_MILLISECONDS);
                if(pUnit)
                {
                    ((hyjal_trashAI*)pUnit->AI())->faction = Faction;
                    ((hyjal_trashAI*)pUnit->AI())->IsOverrun = true;
                    ((hyjal_trashAI*)pUnit->AI())->OverrunType = i;
                    pUnit->SetKeepActive(true);
                }
            }
            break;
    }
}
