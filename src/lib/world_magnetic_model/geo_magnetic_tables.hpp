/****************************************************************************
 *
 *   Copyright (c) 2020-2023 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <stdint.h>

static constexpr float SAMPLING_RES = 10;
static constexpr float SAMPLING_MIN_LAT = -90;
static constexpr float SAMPLING_MAX_LAT = 90;
static constexpr float SAMPLING_MIN_LON = -180;
static constexpr float SAMPLING_MAX_LON = 180;

static constexpr int LAT_DIM = 19;
static constexpr int LON_DIM = 37;


// *INDENT-OFF*
// Magnetic declination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2024.3743,
static constexpr const int16_t declination_table[19][37] {
	//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
	/* LAT: -90 */ {  25941, 24196, 22451, 20705, 18960, 17215, 15469, 13724, 11979, 10233,  8488,  6743,  4997,  3252,  1507,  -239, -1984, -3729, -5475, -7220, -8965,-10711,-12456,-14201,-15947,-17692,-19437,-21183,-22928,-24673,-26419,-28164,-29909, 31177, 29432, 27687, 25941, },
	/* LAT: -80 */ {  22503, 20377, 18442, 16671, 15033, 13496, 12034, 10624,  9249,  7900,  6569,  5251,  3942,  2638,  1329,     9, -1334, -2709, -4122, -5577, -7075, -8616,-10196,-11819,-13486,-15207,-16995,-18871,-20856,-22978,-25255,-27690,-30258, 29938, 27326, 24827, 22503, },
	/* LAT: -70 */ {  14990, 13589, 12458, 11491, 10618,  9782,  8937,  8047,  7092,  6072,  5002,  3910,  2827,  1775,   756,  -254, -1293, -2404, -3612, -4921, -6309, -7745, -9198,-10644,-12073,-13491,-14923,-16414,-18047,-19976,-22523,-26359, 30554, 24076, 19616, 16859, 14990, }, // WARNING! black out zone
	/* LAT: -60 */ {   8469,  8214,  7923,  7640,  7378,  7118,  6803,  6365,  5745,  4921,  3917,  2805,  1689,   670,  -201,  -950, -1678, -2507, -3525, -4739, -6085, -7464, -8790,-10002,-11065,-11960,-12673,-13166,-13338,-12890,-10772, -3356,  5089,  7768,  8507,  8616,  8469, }, // WARNING! black out zone
	/* LAT: -50 */ {   5523,  5555,  5493,  5396,  5315,  5272,  5232,  5099,  4749,  4079,  3061,  1785,   448,  -718, -1567, -2111, -2496, -2942, -3649, -4694, -5964, -7256, -8400, -9296, -9883,-10106, -9895, -9122, -7599, -5226, -2313,   437,  2548,  3974,  4849,  5322,  5523, },
	/* LAT: -40 */ {   3982,  4073,  4076,  4024,  3957,  3918,  3919,  3904,  3725,  3180,  2144,   693,  -867, -2162, -2998, -3423, -3585, -3635, -3822, -4439, -5460, -6555, -7436, -7958, -8042, -7639, -6726, -5332, -3626, -1936,  -484,   734,  1781,  2654,  3316,  3750,  3982, },
	/* LAT: -30 */ {   3007,  3092,  3116,  3093,  3028,  2944,  2879,  2843,  2713,  2224,  1170,  -364, -1968, -3200, -3911, -4231, -4285, -4047, -3608, -3434, -3861, -4636, -5324, -5649, -5496, -4884, -3910, -2707, -1517,  -589,    79,   676,  1305,  1918,  2436,  2804,  3007, },
	/* LAT: -20 */ {   2364,  2409,  2418,  2411,  2361,  2260,  2146,  2067,  1920,  1414,   337, -1167, -2640, -3676, -4177, -4264, -4035, -3449, -2577, -1811, -1588, -1980, -2633, -3083, -3096, -2718, -2074, -1264,  -506,   -33,   218,   516,   964,  1455,  1889,  2205,  2364, },
	/* LAT: -10 */ {   1971,  1963,  1933,  1920,  1884,  1792,  1673,  1577,  1391,   832,  -247, -1635, -2897, -3698, -3928, -3669, -3074, -2282, -1438,  -699,  -261,  -325,  -812, -1312, -1509, -1407, -1088,  -594,  -110,   116,   152,   306,   685,  1139,  1546,  1845,  1971, },
	/* LAT:   0 */ {   1757,  1721,  1657,  1639,  1620,  1543,  1427,  1306,  1049,   423,  -627, -1856, -2895, -3452, -3416, -2889, -2112, -1334,  -690,  -162,   241,   333,    36,  -381,  -627,  -677,  -578,  -322,   -41,    35,   -39,    43,   393,   853,  1288,  1620,  1757, },
	/* LAT:  10 */ {   1616,  1622,  1573,  1581,  1600,  1542,  1409,  1214,   836,   117,  -907, -1978, -2787, -3098, -2866, -2242, -1463,  -759,  -253,   122,   443,   580,   404,    81,  -148,  -255,  -284,  -211,  -115,  -167,  -318,  -296,    14,   485,   980,  1399,  1616, },
	/* LAT:  20 */ {   1421,  1569,  1625,  1712,  1793,  1765,  1600,  1290,   744,  -110, -1149, -2090, -2667, -2753, -2406, -1794, -1083,  -439,    12,   315,   571,   709,   609,   364,   169,    48,   -53,  -128,  -217,  -415,  -660,  -721,  -479,   -18,   533,  1060,  1421, },
	/* LAT:  30 */ {   1104,  1470,  1728,  1950,  2108,  2114,  1920,  1492,   763,  -261, -1367, -2227, -2622, -2544, -2135, -1551,  -895,  -281,   174,   474,   701,   841,   813,   662,   515,   388,   219,    -7,  -301,  -682, -1054, -1212, -1045,  -611,   -29,   583,  1104, },
	/* LAT:  40 */ {    728,  1313,  1808,  2202,  2452,  2495,  2278,  1743,   834,  -383, -1603, -2449, -2753, -2591, -2140, -1546,  -892,  -265,   239,   598,   863,  1055,  1141,  1126,  1050,   898,   615,   186,  -367,  -980, -1499, -1737, -1613, -1192,  -594,    74,   728, },
	/* LAT:  50 */ {    417,  1160,  1843,  2406,  2778,  2889,  2664,  2014,   884,  -593, -1990, -2884, -3167, -2971, -2479, -1833, -1124,  -429,   182,   683,  1096,  1444,  1716,  1880,  1894,  1697,  1234,   502,  -408, -1313, -1983, -2257, -2126, -1685, -1058,  -337,   417, },
	/* LAT:  60 */ {    190,  1036,  1843,  2546,  3061,  3286,  3086,  2295,   814, -1102, -2786, -3752, -4004, -3747, -3179, -2437, -1615,  -779,    24,   771,  1458,  2083,  2619,  3006,  3153,  2948,  2281,  1133,  -300, -1616, -2467, -2761, -2592, -2106, -1428,  -645,   190, },
	/* LAT:  70 */ {   -102,   824,  1719,  2522,  3148,  3460,  3241,  2174,    53, -2552, -4477, -5322, -5357, -4896, -4143, -3221, -2207, -1149,   -81,   974,  1994,  2956,  3817,  4516,  4950,  4960,  4313,  2786,   549, -1562, -2841, -3273, -3115, -2596, -1864, -1014,  -102, }, // WARNING! black out zone
	/* LAT:  80 */ {   -996,   -79,   768,  1460,  1858,  1729,   698, -1557, -4438, -6521, -7366, -7332, -6775, -5909, -4854, -3681, -2434, -1143,   172,  1492,  2801,  4081,  5307,  6447,  7445,  8208,  8548,  8072,  6007,  1935, -1808, -3489, -3807, -3452, -2766, -1915,  -996, }, // WARNING! black out zone
	/* LAT:  90 */ { -29136,-27391,-25645,-23900,-22155,-20409,-18664,-16919,-15173,-13428,-11683, -9937, -8192, -6447, -4701, -2956, -1211,   535,  2280,  4025,  5771,  7516,  9261, 11007, 12752, 14497, 16243, 17988, 19733, 21479, 23224, 24969, 26714, 28460, 30205,-30881,-29136, }, // WARNING! black out zone
};
static constexpr float WMM_DECLINATION_MIN_RAD = -3.088; // latitude: 90, longitude: 170
static constexpr float WMM_DECLINATION_MAX_RAD = 3.118; // latitude: -90, longitude: 150


// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2024.3743,
static constexpr const int16_t inclination_table[19][37] {
	//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
	/* LAT: -90 */ { -12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560,-12560, },
	/* LAT: -80 */ { -13642,-13508,-13347,-13167,-12973,-12772,-12569,-12369,-12179,-12003,-11847,-11714,-11604,-11517,-11454,-11412,-11392,-11394,-11421,-11475,-11559,-11674,-11820,-11994,-12193,-12410,-12640,-12873,-13101,-13313,-13499,-13648,-13750,-13800,-13796,-13741,-13642, },
	/* LAT: -70 */ { -14088,-13769,-13450,-13127,-12796,-12453,-12099,-11744,-11402,-11096,-10845,-10664,-10553,-10501,-10486,-10487,-10491,-10498,-10519,-10574,-10683,-10860,-11109,-11426,-11801,-12221,-12670,-13135,-13601,-14053,-14469,-14811,-14993,-14935,-14702,-14404,-14088, }, // WARNING! black out zone
	/* LAT: -60 */ { -13508,-13153,-12814,-12481,-12138,-11766,-11351,-10898,-10432,-10005, -9680, -9511, -9513, -9652, -9855,-10041,-10158,-10192,-10171,-10153,-10202,-10366,-10663,-11078,-11582,-12141,-12729,-13326,-13914,-14476,-14973,-15261,-15076,-14687,-14278,-13883,-13508, }, // WARNING! black out zone
	/* LAT: -50 */ { -12491,-12147,-11815,-11492,-11168,-10822,-10423, -9953, -9426, -8909, -8527, -8413, -8626, -9093, -9655,-10157,-10502,-10647,-10600,-10438,-10296,-10311,-10546,-10974,-11524,-12120,-12706,-13242,-13685,-13980,-14086,-14012,-13808,-13523,-13193,-12843,-12491, },
	/* LAT: -40 */ { -11239,-10887,-10536,-10190, -9850, -9513, -9154, -8731, -8213, -7652, -7238, -7216, -7696, -8529, -9449,-10268,-10912,-11327,-11442,-11251,-10899,-10636,-10648,-10947,-11419,-11925,-12365,-12679,-12833,-12836,-12747,-12613,-12436,-12205,-11918,-11588,-11239, },
	/* LAT: -30 */ {  -9603, -9217, -8832, -8440, -8048, -7675, -7322, -6936, -6425, -5818, -5381, -5494, -6296, -7514, -8762, -9845,-10744,-11435,-11805,-11763,-11370,-10862,-10545,-10564,-10826,-11148,-11397,-11500,-11432,-11257,-11087,-10959,-10819,-10615,-10334, -9986, -9603, },
	/* LAT: -20 */ {  -7374, -6922, -6496, -6064, -5620, -5193, -4808, -4403, -3842, -3161, -2733, -3036, -4192, -5825, -7447, -8795, -9837,-10588,-10997,-11002,-10613, -9988, -9437, -9210, -9269, -9433, -9569, -9577, -9400, -9129, -8943, -8869, -8777, -8576, -8259, -7843, -7374, },
	/* LAT: -10 */ {  -4421, -3867, -3401, -2958, -2500, -2052, -1645, -1203,  -588,   105,   441,   -34, -1413, -3356, -5322, -6896, -7955, -8558, -8797, -8710, -8276, -7574, -6912, -6581, -6550, -6644, -6756, -6773, -6581, -6288, -6145, -6175, -6155, -5948, -5564, -5029, -4421, },
	/* LAT:   0 */ {   -914,  -270,   210,   619,  1039,  1455,  1837,  2264,  2832,  3394,  3570,  3032,  1691,  -248, -2284, -3895, -4858, -5253, -5289, -5100, -4637, -3901, -3196, -2838, -2781, -2847, -2968, -3037, -2906, -2675, -2635, -2805, -2894, -2720, -2294, -1655,  -914, },
	/* LAT:  10 */ {   2554,  3199,  3646,  3993,  4350,  4716,  5060,  5432,  5866,  6221,  6235,  5716,  4599,  3010,  1324,   -19,  -784,  -999,  -887,  -638,  -210,   445,  1078,  1407,  1471,  1435,  1339,  1248,  1289,  1386,  1295,  1002,   785,   845,  1199,  1811,  2554, },
	/* LAT:  20 */ {   5411,  5952,  6341,  6640,  6955,  7297,  7633,  7969,  8288,  8475,  8372,  7889,  7032,  5924,  4804,  3915,  3414,  3320,  3486,  3739,  4080,  4555,  5017,  5269,  5329,  5320,  5277,  5218,  5202,  5177,  4990,  4639,  4323,  4225,  4398,  4828,  5411, },
	/* LAT:  30 */ {   7567,  7946,  8268,  8553,  8862,  9207,  9560,  9893, 10159, 10262, 10106,  9673,  9035,  8321,  7666,  7167,  6891,  6865,  7019,  7237,  7490,  7796,  8086,  8259,  8319,  8339,  8346,  8336,  8308,  8219,  7988,  7624,  7259,  7034,  7018,  7217,  7567, },
	/* LAT:  40 */ {   9266,  9488,  9745, 10031, 10356, 10715, 11079, 11412, 11657, 11731, 11574, 11209, 10735, 10264,  9873,  9597,  9457,  9463,  9581,  9748,  9928, 10116, 10290, 10415, 10495, 10560, 10619, 10652, 10632, 10515, 10266,  9910,  9537,  9251,  9108,  9121,  9266, },
	/* LAT:  50 */ {  10803, 10922, 11123, 11391, 11712, 12063, 12414, 12726, 12944, 12998, 12856, 12558, 12195, 11853, 11582, 11400, 11313, 11316, 11388, 11495, 11613, 11732, 11850, 11966, 12086, 12211, 12327, 12399, 12386, 12255, 12004, 11673, 11332, 11047, 10857, 10777, 10803, },
	/* LAT:  60 */ {  12320, 12390, 12537, 12752, 13019, 13317, 13616, 13880, 14053, 14080, 13946, 13699, 13413, 13144, 12927, 12774, 12687, 12659, 12678, 12729, 12800, 12887, 12995, 13129, 13291, 13468, 13633, 13740, 13741, 13615, 13387, 13108, 12830, 12594, 12424, 12332, 12320, },
	/* LAT:  70 */ {  13757, 13796, 13887, 14025, 14201, 14401, 14607, 14786, 14891, 14876, 14745, 14548, 14333, 14131, 13959, 13826, 13734, 13681, 13663, 13678, 13722, 13796, 13901, 14039, 14208, 14396, 14580, 14718, 14760, 14684, 14521, 14322, 14128, 13963, 13842, 13772, 13757, }, // WARNING! black out zone
	/* LAT:  80 */ {  14989, 14999, 15033, 15090, 15163, 15245, 15321, 15367, 15356, 15285, 15179, 15059, 14938, 14826, 14727, 14646, 14585, 14545, 14527, 14532, 14559, 14609, 14682, 14776, 14888, 15016, 15152, 15285, 15393, 15435, 15390, 15299, 15201, 15115, 15048, 15006, 14989, }, // WARNING! black out zone
	/* LAT:  90 */ {  15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, 15401, }, // WARNING! black out zone
};
static constexpr float WMM_INCLINATION_MIN_RAD = -1.526; // latitude: -60, longitude: 130
static constexpr float WMM_INCLINATION_MAX_RAD = 1.543; // latitude: 80, longitude: 110


// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2024.3743,
static constexpr const int16_t strength_table[19][37] {
	//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
	/* LAT: -90 */ {  5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, 5440, },
	/* LAT: -80 */ {  6047, 5983, 5903, 5810, 5706, 5594, 5476, 5354, 5231, 5111, 4997, 4892, 4799, 4720, 4657, 4613, 4589, 4588, 4610, 4657, 4729, 4823, 4939, 5071, 5216, 5366, 5516, 5659, 5790, 5904, 5996, 6064, 6108, 6127, 6121, 6094, 6047, },
	/* LAT: -70 */ {  6292, 6157, 6005, 5838, 5658, 5465, 5260, 5045, 4826, 4612, 4410, 4228, 4071, 3941, 3838, 3762, 3715, 3704, 3734, 3811, 3941, 4123, 4354, 4623, 4919, 5227, 5531, 5815, 6064, 6268, 6418, 6512, 6552, 6543, 6492, 6406, 6292, },
	/* LAT: -60 */ {  6178, 5983, 5780, 5569, 5349, 5113, 4857, 4578, 4286, 3997, 3732, 3506, 3328, 3194, 3096, 3023, 2972, 2953, 2980, 3072, 3244, 3499, 3829, 4217, 4641, 5076, 5497, 5881, 6205, 6452, 6614, 6690, 6690, 6626, 6510, 6357, 6178, },
	/* LAT: -50 */ {  5837, 5605, 5371, 5138, 4904, 4658, 4387, 4084, 3755, 3424, 3124, 2886, 2727, 2637, 2589, 2553, 2518, 2490, 2496, 2571, 2749, 3045, 3447, 3921, 4430, 4936, 5410, 5827, 6165, 6405, 6541, 6580, 6535, 6423, 6259, 6059, 5837, },
	/* LAT: -40 */ {  5388, 5140, 4894, 4652, 4417, 4178, 3923, 3639, 3325, 2999, 2702, 2482, 2367, 2343, 2362, 2381, 2383, 2368, 2355, 2385, 2522, 2806, 3232, 3751, 4299, 4821, 5285, 5671, 5961, 6147, 6234, 6235, 6164, 6031, 5848, 5629, 5388, },
	/* LAT: -30 */ {  4875, 4632, 4391, 4155, 3928, 3709, 3489, 3258, 3002, 2726, 2469, 2289, 2223, 2250, 2317, 2387, 2450, 2496, 2514, 2525, 2598, 2807, 3180, 3675, 4208, 4703, 5116, 5428, 5629, 5727, 5753, 5725, 5645, 5511, 5330, 5113, 4875, },
	/* LAT: -20 */ {  4319, 4104, 3894, 3688, 3491, 3308, 3139, 2975, 2796, 2597, 2406, 2275, 2238, 2286, 2377, 2487, 2614, 2739, 2822, 2853, 2880, 2985, 3235, 3627, 4080, 4506, 4849, 5078, 5180, 5187, 5156, 5109, 5027, 4899, 4732, 4534, 4319, },
	/* LAT: -10 */ {  3789, 3626, 3472, 3324, 3188, 3068, 2964, 2871, 2771, 2655, 2533, 2435, 2395, 2424, 2514, 2645, 2800, 2955, 3074, 3132, 3146, 3176, 3308, 3567, 3897, 4219, 4480, 4638, 4669, 4616, 4548, 4485, 4398, 4273, 4124, 3959, 3789, },
	/* LAT:   0 */ {  3412, 3317, 3232, 3158, 3102, 3064, 3036, 3015, 2988, 2938, 2859, 2766, 2689, 2663, 2710, 2816, 2948, 3082, 3195, 3267, 3296, 3319, 3399, 3561, 3774, 3988, 4167, 4269, 4272, 4204, 4115, 4023, 3913, 3781, 3646, 3521, 3412, },
	/* LAT:  10 */ {  3282, 3250, 3228, 3223, 3247, 3293, 3347, 3397, 3430, 3418, 3349, 3235, 3111, 3021, 3000, 3044, 3127, 3226, 3325, 3410, 3473, 3536, 3627, 3748, 3886, 4026, 4145, 4214, 4213, 4150, 4039, 3895, 3733, 3574, 3437, 3340, 3282, },
	/* LAT:  20 */ {  3399, 3400, 3424, 3476, 3566, 3686, 3813, 3927, 4006, 4017, 3943, 3802, 3638, 3502, 3431, 3423, 3461, 3535, 3633, 3731, 3822, 3922, 4034, 4147, 4258, 4372, 4475, 4540, 4548, 4487, 4348, 4144, 3916, 3706, 3542, 3439, 3399, },
	/* LAT:  30 */ {  3722, 3725, 3777, 3874, 4015, 4184, 4358, 4512, 4619, 4645, 4572, 4418, 4232, 4072, 3971, 3928, 3935, 3989, 4078, 4177, 4276, 4384, 4501, 4619, 4740, 4868, 4991, 5077, 5100, 5040, 4881, 4640, 4364, 4110, 3909, 3779, 3722, },
	/* LAT:  40 */ {  4222, 4216, 4277, 4397, 4562, 4747, 4929, 5085, 5189, 5215, 5148, 5001, 4817, 4647, 4523, 4450, 4428, 4453, 4516, 4597, 4685, 4784, 4899, 5033, 5184, 5348, 5500, 5609, 5645, 5588, 5430, 5191, 4917, 4658, 4447, 4299, 4222, },
	/* LAT:  50 */ {  4832, 4819, 4870, 4976, 5120, 5278, 5428, 5549, 5624, 5634, 5573, 5448, 5288, 5127, 4993, 4898, 4846, 4837, 4863, 4915, 4986, 5078, 5198, 5349, 5525, 5709, 5875, 5991, 6032, 5984, 5852, 5656, 5433, 5219, 5039, 4907, 4832, },
	/* LAT:  60 */ {  5393, 5375, 5398, 5457, 5540, 5634, 5721, 5789, 5824, 5818, 5766, 5674, 5556, 5429, 5313, 5218, 5153, 5121, 5120, 5149, 5207, 5295, 5414, 5561, 5728, 5896, 6042, 6143, 6184, 6160, 6077, 5952, 5808, 5667, 5544, 5451, 5393, },
	/* LAT:  70 */ {  5726, 5702, 5696, 5705, 5725, 5751, 5776, 5792, 5793, 5776, 5739, 5684, 5616, 5541, 5469, 5406, 5359, 5332, 5328, 5349, 5395, 5465, 5557, 5666, 5783, 5896, 5994, 6066, 6104, 6106, 6078, 6025, 5958, 5888, 5822, 5767, 5726, },
	/* LAT:  80 */ {  5790, 5772, 5756, 5743, 5732, 5722, 5713, 5701, 5687, 5670, 5649, 5625, 5599, 5573, 5549, 5530, 5517, 5513, 5518, 5534, 5560, 5595, 5638, 5686, 5735, 5783, 5825, 5859, 5883, 5896, 5898, 5890, 5875, 5856, 5834, 5811, 5790, },
	/* LAT:  90 */ {  5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, 5686, },
};
static constexpr float WMM_STRENGTH_MIN_GS = 22.2; // latitude: -30, longitude: -60
static constexpr float WMM_STRENGTH_MAX_GS = 66.9; // latitude: -60, longitude: 130
static constexpr float WMM_STRENGTH_MEAN_GS = 46.4;
static constexpr float WMM_STRENGTH_MEDIAN_GS = 48.8;


