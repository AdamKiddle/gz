#include "gz.h"
#include "z64.h"

static uint16_t angle_tbl[] = {
	0x0000, 0x00AD, 0x00B7, 0x00C2, 0x00CC, 0x00D6, 0x00E0, 0x00EA, 0x00F4, 0x00FF, 0x0109, 0x0113, 0x011D, 
	0x0127, 0x0131, 0x013C, 0x0146, 0x0150, 0x015A, 0x015A, 0x0164, 0x0164, 0x016F, 0x0179, 0x0179, 0x0183, 
	0x018D, 0x018D, 0x0197, 0x01A1, 0x01AC, 0x01B6, 0x01C0, 0x01CA, 0x01D4, 0x01DE, 0x01E9, 0x01F3, 0x01FD, 
	0x0207, 0x0207, 0x0211, 0x021B, 0x021B, 0x0226, 0x0230, 0x023A, 0x0244, 0x0244, 0x024E, 0x0258, 0x0262, 
	0x0262, 0x026D, 0x0277, 0x0281, 0x028B, 0x0295, 0x029F, 0x02A9, 0x02B4, 0x02B4, 0x02BE, 0x02C8, 0x02D2, 
	0x02DC, 0x02E6, 0x02E6, 0x02F0, 0x02FB, 0x0305, 0x030F, 0x0323, 0x0323, 0x032D, 0x0337, 0x0341, 0x034C, 
	0x0356, 0x0360, 0x0360, 0x0374, 0x037E, 0x037E, 0x0388, 0x0392, 0x039C, 0x03B1, 0x03B1, 0x03C5, 0x03CF, 
	0x03D9, 0x03E3, 0x03ED, 0x03F7, 0x040C, 0x040C, 0x0420, 0x042A, 0x0434, 0x043E, 0x0448, 0x0452, 0x045C, 
	0x0466, 0x0470, 0x0484, 0x0484, 0x0499, 0x04A3, 0x04AD, 0x04B7, 0x04C1, 0x04CB, 0x04D5, 0x04DF, 0x04E9, 
	0x04F3, 0x04FD, 0x0511, 0x0511, 0x0525, 0x052F, 0x0539, 0x0543, 0x054D, 0x0557, 0x0557, 0x056B, 0x056B, 
	0x0575, 0x057F, 0x0589, 0x0593, 0x059D, 0x05A7, 0x05B1, 0x05C5, 0x05C5, 0x05E3, 0x05ED, 0x05F7, 0x0601, 
	0x060B, 0x0615, 0x061F, 0x0629, 0x063D, 0x0647, 0x0651, 0x065B, 0x0665, 0x066E, 0x0678, 0x0682, 0x068C, 
	0x0696, 0x06A0, 0x06BE, 0x06BE, 0x06DC, 0x06E5, 0x06EF, 0x06F9, 0x0703, 0x070D, 0x0717, 0x0721, 0x072B, 
	0x0735, 0x073E, 0x0752, 0x0766, 0x0770, 0x077A, 0x0783, 0x078D, 0x0797, 0x07A1, 0x07AB, 0x07B5, 0x07BE, 
	0x07C8, 0x07D2, 0x07DC, 0x07E6, 0x07E6, 0x080D, 0x080D, 0x082A, 0x0834, 0x083E, 0x0848, 0x0851, 0x0851, 
	0x085B, 0x085B, 0x0865, 0x0878, 0x0882, 0x088C, 0x0896, 0x08A9, 0x08B3, 0x08BD, 0x08C6, 0x08D0, 0x08DA, 
	0x08ED, 0x0901, 0x090A, 0x0914, 0x091E, 0x0927, 0x0931, 0x093B, 0x094E, 0x094E, 0x0958, 0x0958, 0x0961, 
	0x096B, 0x0975, 0x097E, 0x0988, 0x0992, 0x099B, 0x09A5, 0x09AE, 0x09B8, 0x09C2, 0x09C2, 0x09CB, 0x09D5, 
	0x09FB, 0x09FB, 0x0A22, 0x0A2B, 0x0A35, 0x0A3E, 0x0A48, 0x0A51, 0x0A5B, 0x0A64, 0x0A6E, 0x0A77, 0x0A81, 
	0x0A8B, 0x0A94, 0x0A9E, 0x0A9E, 0x0AA7, 0x0AB1, 0x0ABA, 0x0AC4, 0x0ACD, 0x0AD7, 0x0AE9, 0x0AF3, 0x0AFC, 
	0x0B06, 0x0B19, 0x0B22, 0x0B2C, 0x0B35, 0x0B3F, 0x0B3F, 0x0B5B, 0x0B6E, 0x0B77, 0x0B77, 0x0B80, 0x0B8A, 
	0x0B93, 0x0B9D, 0x0BA6, 0x0BB9, 0x0BC2, 0x0BCB, 0x0BDE, 0x0BDE, 0x0BF1, 0x0BFA, 0x0BFA, 0x0C03, 0x0C0D, 
	0x0C16, 0x0C29, 0x0C3B, 0x0C45, 0x0C4E, 0x0C57, 0x0C60, 0x0C6A, 0x0C73, 0x0C7C, 0x0C86, 0x0C8F, 0x0C98, 
	0x0CA1, 0x0CAB, 0x0CB4, 0x0CBD, 0x0CC6, 0x0CCF, 0x0CD9, 0x0CD9, 0x0CE2, 0x0CE2, 0x0D19, 0x0D19, 0x0D50, 
	0x0D59, 0x0D62, 0x0D62, 0x0D6B, 0x0D6B, 0x0D74, 0x0D7D, 0x0D87, 0x0D87, 0x0D90, 0x0D99, 0x0DA2, 0x0DAB, 
	0x0DB4, 0x0DBD, 0x0DC6, 0x0DCF, 0x0DCF, 0x0DE1, 0x0DEA, 0x0DFC, 0x0E05, 0x0E0F, 0x0E18, 0x0E21, 0x0E2A, 
	0x0E33, 0x0E45, 0x0E4E, 0x0E4E, 0x0E56, 0x0E5F, 0x0E68, 0x0E71, 0x0E7A, 0x0E83, 0x0E8C, 0x0E9E, 0x0EB0, 
	0x0EB9, 0x0EC2, 0x0ECB, 0x0ED4, 0x0EDC, 0x0EE5, 0x0EEE, 0x0EF7, 0x0F00, 0x0F09, 0x0F12, 0x0F1B, 0x0F1B, 
	0x0F23, 0x0F2C, 0x0F35, 0x0F3E, 0x0F47, 0x0F50, 0x0F58, 0x0F61, 0x0F61, 0x0F84, 0x0F9F, 0x0FA7, 0x0FA7, 
	0x0FB0, 0x0FB9, 0x0FC2, 0x0FCA, 0x0FD3, 0x0FDC, 0x0FE5, 0x0FED, 0x0FF6, 0x0FFF, 0x1007, 0x1019, 0x1021, 
	0x102A, 0x1033, 0x103B, 0x1044, 0x104D, 0x1055, 0x105E, 0x1067, 0x1080, 0x1092, 0x109A, 0x109A, 0x10A3, 
	0x10AB, 0x10AB, 0x10B4, 0x10BC, 0x10C5, 0x10CE, 0x10D6, 0x10DF, 0x10E7, 0x10F0, 0x10F0, 0x10F8, 0x1109, 
	0x111A, 0x1123, 0x112B, 0x1134, 0x113C, 0x1145, 0x114D, 0x1156, 0x115E, 0x116F, 0x1177, 0x1180, 0x1188, 
	0x1191, 0x11A1, 0x11A1, 0x11AA, 0x11B2, 0x11BB, 0x11C3, 0x11CB, 0x11CB, 0x11D4, 0x11DC, 0x11E4, 0x11ED, 
	0x11F5, 0x11FD, 0x1206, 0x120E, 0x121F, 0x1227, 0x122F, 0x1237, 0x1240, 0x1248, 0x1250, 0x1259, 0x1259, 
	0x1261, 0x1269, 0x1271, 0x127A, 0x1282, 0x128A, 0x1292, 0x1292, 0x129A, 0x12E4, 0x12E4, 0x132D, 0x1335, 
	0x133D, 0x1345, 0x1345, 0x134D, 0x1355, 0x135E, 0x1366, 0x136E, 0x1376, 0x1376, 0x137E, 0x1386, 0x138E, 
	0x1396, 0x139E, 0x13A6, 0x13B6, 0x13BE, 0x13C6, 0x13CE, 0x13D6, 0x13DE, 0x13E6, 0x13ED, 0x13F5, 0x13FD, 
	0x1405, 0x140D, 0x140D, 0x1415, 0x141D, 0x142D, 0x1435, 0x143D, 0x1444, 0x144C, 0x145C, 0x145C, 0x1464, 
	0x146C, 0x1473, 0x147B, 0x1483, 0x148B, 0x1493, 0x1493, 0x149B, 0x14AA, 0x14BA, 0x14C1, 0x14C9, 0x14D1, 
	0x14D9, 0x14E0, 0x14E8, 0x14F0, 0x14F8, 0x14FF, 0x14FF, 0x1507, 0x150F, 0x150F, 0x1516, 0x1526, 0x153D, 
	0x1544, 0x154C, 0x1554, 0x155B, 0x1563, 0x156B, 0x1572, 0x1572, 0x157A, 0x1581, 0x1591, 0x1591, 0x1598, 
	0x15A0, 0x15A7, 0x15A7, 0x15AF, 0x15B7, 0x15BE, 0x15C6, 0x15CD, 0x15D5, 0x15DC, 0x15E4, 0x15E4, 0x15EB, 
	0x1602, 0x1620, 0x1627, 0x162F, 0x1636, 0x163E, 0x1645, 0x164C, 0x1654, 0x165B, 0x165B, 0x1663, 0x166A, 
	0x1671, 0x1679, 0x1680, 0x1688, 0x1688, 0x168F, 0x1696, 0x169E, 0x16A5, 0x16A5, 0x16AC, 0x16B4, 0x16C2, 
	0x16D1, 0x16D8, 0x16E0, 0x16E7, 0x16EE, 0x16F6, 0x16FD, 0x1704, 0x1704, 0x170B, 0x171A, 0x1721, 0x1728, 
	0x1730, 0x1737, 0x173E, 0x1745, 0x1754, 0x175B, 0x1769, 0x1770, 0x1778, 0x177F, 0x1786, 0x178D, 0x1794, 
	0x179B, 0x17A2, 0x17AA, 0x17B1, 0x17B8, 0x17BF, 0x17BF, 0x17C6, 0x17CD, 0x17F7, 0x1822, 0x1829, 0x1829, 
	0x1830, 0x1830, 0x1837, 0x183E, 0x1845, 0x184C, 0x1853, 0x185A, 0x1860, 0x1867, 0x186E, 0x1875, 0x187C, 
	0x1883, 0x188A, 0x1891, 0x1898, 0x189F, 0x18AD, 0x18BA, 0x18C1, 0x18C8, 0x18CF, 0x18D6, 0x18E3, 0x18E3, 
	0x18F1, 0x18F8, 0x18FF, 0x190C, 0x1913, 0x191A, 0x1921, 0x1928, 0x192E, 0x1935, 0x1943, 0x1957, 0x1957, 
	0x195D, 0x1964, 0x196B, 0x1972, 0x197F, 0x197F, 0x1986, 0x198C, 0x198C, 0x1993, 0x19A0, 0x19A7, 0x19AE, 
	0x19B4, 0x19BB, 0x19C2, 0x19C8, 0x19C8, 0x19CF, 0x19D5, 0x19DC, 0x19E3, 0x19E9, 0x19F0, 0x19F6, 0x19FD, 
	0x19FD, 0x1A04, 0x1A0A, 0x1A11, 0x1A17, 0x1A1E, 0x1A38, 0x1A52, 0x1A58, 0x1A5F, 0x1A65, 0x1A6C, 0x1A72, 
	0x1A79, 0x1A7F, 0x1A86, 0x1A8C, 0x1A93, 0x1A99, 0x1A9F, 0x1AA6, 0x1AAC, 0x1AB9, 0x1AB9, 0x1AC0, 0x1AC6, 
	0x1ACC, 0x1AD3, 0x1AD9, 0x1ADF, 0x1AEC, 0x1AF9, 0x1AFF, 0x1B05, 0x1B0C, 0x1B12, 0x1B18, 0x1B25, 0x1B2B, 
	0x1B32, 0x1B38, 0x1B44, 0x1B4B, 0x1B51, 0x1B57, 0x1B5D, 0x1B64, 0x1B6A, 0x1B7D, 0x1B95, 0x1B9C, 0x1BA2, 
	0x1BA8, 0x1BAE, 0x1BB4, 0x1BBA, 0x1BC1, 0x1BC1, 0x1BC7, 0x1BCD, 0x1BD3, 0x1BD9, 0x1BDF, 0x1BE5, 0x1BF2, 
	0x1BFE, 0x1C04, 0x1C0A, 0x1C10, 0x1C16, 0x1C1C, 0x1C22, 0x1C28, 0x1C2E, 0x1C34, 0x1C3A, 0x1C4C, 0x1C5E, 
	0x1C64, 0x1C6A, 0x1C70, 0x1C76, 0x1C7C, 0x1C82, 0x1C88, 0x1C8E, 0x1C94, 0x1C94, 0x1C9A, 0x1CA6, 0x1CAC, 
	0x1CB2, 0x1CB8, 0x1CBE, 0x1CC3, 0x1CC9, 0x1CCF, 0x1CE1, 0x1CE1, 0x1CED, 0x1CF3, 0x1CF8, 0x1CFE, 0x1D04, 
	0x1D0A, 0x1D10, 0x1D16, 0x1D21, 0x1D27, 0x1D2D, 0x1D33, 0x1D38, 0x1D38, 0x1D3E, 0x1D4A, 0x1D55, 0x1D5B, 
	0x1D61, 0x1D66, 0x1D6C, 0x1D72, 0x1D78, 0x1D78, 0x1D7D, 0x1D7D, 0x1D83, 0x1D89, 0x1D8E, 0x1D8E, 0x1D9A, 
	0x1DA5, 0x1DAB, 0x1DB1, 0x1DB6, 0x1DBC, 0x1DC2, 0x1DC7, 0x1DCD, 0x1DD3, 0x1DDE, 0x1DDE, 0x1DE9, 0x1DEF, 
	0x1DF4, 0x1DFA, 0x1DFF, 0x1E05, 0x1E10, 0x1E10, 0x1E1B, 0x1E21, 0x1E26, 0x1E2C, 0x1E2C, 0x1E32, 0x1E3D, 
	0x1E42, 0x1E48, 0x1E4D, 0x1E53, 0x1E58, 0x1E5E, 0x1E69, 0x1E6E, 0x1E74, 0x1E79, 0x1E7F, 0x1E84, 0x1E8A, 
	0x1E8A, 0x1E8F, 0x1E94, 0x1E9A, 0x1E9A, 0x1E9F, 0x1EA5, 0x1EAA, 0x1EB0, 0x1EB5, 0x1EBA, 0x1EC0, 0x1EC5, 
	0x1ECB, 0x1ED0, 0x1ED5, 0x1ED5, 0x1EDB, 0x1EE0, 0x1EE0, 0x1EE6, 0x1EEB, 0x1EF0, 0x1EF6, 0x1EFB, 0x1F00, 
	0x1F06, 0x1F0B, 0x1F10, 0x1F16, 0x1F1B, 0x1F20, 0x1F26, 0x1F2B, 0x1F30, 0x1F36, 0x1F3B, 0x1F40, 0x1F45, 
	0x1F4B, 0x1F50, 0x1F50, 0x1F55, 0x1F5A, 0x1F60, 0x1F65, 0x1F6A, 0x1F6F, 0x1F6F, 0x1F75, 0x1F7A, 0x1F7F, 
	0x1F84, 0x1F8A, 0x1F8F, 0x1F94, 0x1F99, 0x1F9E, 0x1FA4, 0x1FA9, 
};
static uint16_t analog_tbl[] = {
	0x0087, 0x1084, 0x107E, 0x1078, 0x1072, 0x106E, 0x106A, 0x1066, 0x1062, 0x1060, 0x105C, 0x105A, 0x1056, 
	0x1054, 0x1052, 0x1050, 0x104E, 0x104C, 0x104A, 0x1287, 0x1048, 0x1283, 0x1280, 0x1046, 0x127F, 0x1044, 
	0x1042, 0x1279, 0x1275, 0x1040, 0x1271, 0x103E, 0x126D, 0x103C, 0x1269, 0x103A, 0x1265, 0x1038, 0x1261, 
	0x1036, 0x125F, 0x1484, 0x125C, 0x1483, 0x1034, 0x1259, 0x147C, 0x1032, 0x1257, 0x1479, 0x1254, 0x1030, 
	0x1253, 0x1472, 0x1251, 0x1471, 0x102E, 0x146D, 0x124D, 0x146A, 0x102C, 0x1469, 0x1684, 0x1466, 0x1249, 
	0x1680, 0x102A, 0x1247, 0x167C, 0x1461, 0x1244, 0x145F, 0x1028, 0x1243, 0x1675, 0x145A, 0x1241, 0x1459, 
	0x1671, 0x1026, 0x1457, 0x166D, 0x1454, 0x1883, 0x123D, 0x1453, 0x1669, 0x1024, 0x123B, 0x1665, 0x144E, 
	0x1879, 0x1238, 0x144D, 0x1661, 0x1022, 0x1237, 0x1871, 0x165C, 0x1449, 0x186E, 0x1235, 0x186D, 0x1447, 
	0x1659, 0x1A7C, 0x1020, 0x1657, 0x1866, 0x1654, 0x1443, 0x1865, 0x1231, 0x1C84, 0x1862, 0x1441, 0x1651, 
	0x1861, 0x1C80, 0x101E, 0x122F, 0x1C7C, 0x185C, 0x164D, 0x1C7A, 0x143D, 0x185A, 0x1C79, 0x122C, 0x1E87, 
	0x1859, 0x1E84, 0x143B, 0x1649, 0x1857, 0x1A64, 0x1E80, 0x101C, 0x122B, 0x1C6E, 0x1A60, 0x1853, 0x1644, 
	0x1C6D, 0x1437, 0x1851, 0x1C6A, 0x1229, 0x1C69, 0x184E, 0x1E75, 0x1435, 0x1C66, 0x1641, 0x184D, 0x1A58, 
	0x1C65, 0x207C, 0x101A, 0x1227, 0x1E6D, 0x1C61, 0x1A54, 0x1849, 0x163D, 0x1C5F, 0x2280, 0x1431, 0x1E69, 
	0x1847, 0x1C5C, 0x1225, 0x2071, 0x1C5A, 0x1844, 0x1E65, 0x142F, 0x2278, 0x1C59, 0x1638, 0x206D, 0x1843, 
	0x1A4C, 0x1C57, 0x1E61, 0x2274, 0x247F, 0x1018, 0x1637, 0x2684, 0x2066, 0x1E5C, 0x1C53, 0x1A48, 0x2683, 
	0x183E, 0x2479, 0x2065, 0x1635, 0x1C51, 0x226C, 0x142B, 0x1E59, 0x2887, 0x183D, 0x1C4E, 0x2061, 0x2884, 
	0x1221, 0x205F, 0x1C4D, 0x2679, 0x183B, 0x1E54, 0x246E, 0x1429, 0x2264, 0x287F, 0x1C4A, 0x2A87, 0x246D, 
	0x1631, 0x287C, 0x205A, 0x1838, 0x246A, 0x1A40, 0x1C49, 0x1E51, 0x2059, 0x2260, 0x2469, 0x2671, 0x2A80, 
	0x1016, 0x121F, 0x2C84, 0x266D, 0x2465, 0x2054, 0x1E4D, 0x1C44, 0x2872, 0x1A3C, 0x2462, 0x1835, 0x2A79, 
	0x2053, 0x2871, 0x162C, 0x2669, 0x2C7E, 0x2461, 0x1C43, 0x2258, 0x2E84, 0x1425, 0x2A75, 0x1E49, 0x286D, 
	0x1832, 0x2665, 0x1C41, 0x204E, 0x245C, 0x2C78, 0x3087, 0x121D, 0x2C76, 0x245A, 0x2869, 0x204D, 0x2E7C, 
	0x1C3E, 0x2661, 0x1831, 0x1E44, 0x2459, 0x2A6D, 0x1422, 0x265F, 0x2E79, 0x2250, 0x2865, 0x307F, 0x1C3D, 
	0x2457, 0x1629, 0x2862, 0x2049, 0x2A69, 0x182F, 0x2E75, 0x2454, 0x1A34, 0x3487, 0x2861, 0x1C3B, 0x2C6C, 
	0x1E41, 0x2047, 0x224C, 0x2453, 0x2659, 0x285F, 0x2C6A, 0x2E71, 0x3076, 0x3483, 0x1014, 0x1421, 0x347F, 
	0x3072, 0x2C66, 0x2E6D, 0x285A, 0x2A61, 0x2654, 0x244E, 0x2248, 0x3683, 0x2043, 0x3071, 0x1E3D, 0x2C64, 
	0x1C37, 0x3680, 0x2859, 0x1A30, 0x2653, 0x244D, 0x2E69, 0x182B, 0x3479, 0x2A5C, 0x2041, 0x2857, 0x3882, 
	0x1625, 0x3476, 0x244A, 0x3A87, 0x3270, 0x1C35, 0x306A, 0x2244, 0x2854, 0x2E65, 0x3A84, 0x141F, 0x3679, 
	0x2A59, 0x2449, 0x3472, 0x1E38, 0x387C, 0x2853, 0x3C87, 0x1829, 0x3A80, 0x264D, 0x3471, 0x1C32, 0x2A57, 
	0x3C84, 0x2E61, 0x203D, 0x2447, 0x2851, 0x2C5A, 0x3065, 0x3878, 0x3C83, 0x1219, 0x3C80, 0x3062, 0x346D, 
	0x2C58, 0x284E, 0x2444, 0x3671, 0x203B, 0x2E5C, 0x3C7F, 0x1C31, 0x346A, 0x2649, 0x3061, 0x1827, 0x3C7C, 
	0x284D, 0x3872, 0x1E35, 0x3469, 0x2443, 0x2A51, 0x305F, 0x366D, 0x141D, 0x4083, 0x3466, 0x3A75, 0x2E59, 
	0x284A, 0x3C79, 0x223C, 0x305C, 0x3E7C, 0x1C2F, 0x4080, 0x3260, 0x2441, 0x2C52, 0x3465, 0x3C76, 0x1621, 
	0x407F, 0x305A, 0x2849, 0x3A71, 0x2037, 0x2A4D, 0x3462, 0x3E78, 0x1825, 0x386A, 0x2E54, 0x243E, 0x3059, 
	0x3C72, 0x1A28, 0x2643, 0x407A, 0x2847, 0x3665, 0x4482, 0x1C2C, 0x4687, 0x3A6D, 0x2C4E, 0x3C71, 0x1E31, 
	0x4079, 0x3057, 0x2035, 0x345F, 0x2238, 0x3866, 0x243D, 0x3C6E, 0x2641, 0x2844, 0x2A49, 0x2C4C, 0x4887, 
	0x2E51, 0x3054, 0x3258, 0x345C, 0x3661, 0x3A69, 0x3E70, 0x4075, 0x447C, 0x1012, 0x1217, 0x467C, 0x4071, 
	0x3C69, 0x3860, 0x3A65, 0x365C, 0x3459, 0x3254, 0x3051, 0x2E4D, 0x2C48, 0x487F, 0x2A44, 0x2841, 0x406E, 
	0x263D, 0x3C66, 0x2438, 0x385E, 0x2234, 0x3457, 0x4679, 0x2031, 0x4271, 0x304E, 0x406D, 0x1E2C, 0x4C83, 
	0x3C65, 0x2C46, 0x3A61, 0x487A, 0x1C29, 0x4472, 0x3659, 0x283E, 0x3454, 0x406A, 0x1A24, 0x263B, 0x4879, 
	0x3C62, 0x304D, 0x2437, 0x4470, 0x2E49, 0x385A, 0x426D, 0x4C7F, 0x1821, 0x4876, 0x3453, 0x2A41, 0x3C61, 
	0x4E80, 0x202F, 0x4C7C, 0x3A5C, 0x283D, 0x304A, 0x5287, 0x3858, 0x4066, 0x4875, 0x5083, 0x161D, 0x446C, 
	0x3C5F, 0x3451, 0x2C42, 0x4269, 0x2435, 0x4872, 0x324C, 0x4065, 0x4E7C, 0x1C27, 0x3E60, 0x4C79, 0x3049, 
	0x446A, 0x2230, 0x3653, 0x507F, 0x3C5C, 0x283B, 0x4871, 0x2E44, 0x344E, 0x3A59, 0x4062, 0x466D, 0x5280, 
	0x1419, 0x4E78, 0x4265, 0x3C5A, 0x3651, 0x3047, 0x2A3D, 0x4061, 0x5684, 0x2432, 0x3A57, 0x4A70, 0x344D, 
	0x5480, 0x1E29, 0x5887, 0x3852, 0x486D, 0x527C, 0x2838, 0x4C72, 0x3248, 0x5683, 0x3C59, 0x5079, 0x181F, 
	0x5884, 0x4464, 0x3A54, 0x3044, 0x486A, 0x2635, 0x4C71, 0x344A, 0x4261, 0x5076, 0x1C25, 0x5883, 0x3C57, 
	0x2E41, 0x405C, 0x5279, 0x202B, 0x4869, 0x364D, 0x2431, 0x3E58, 0x5880, 0x2837, 0x4665, 0x2C3C, 0x4E70, 
	0x3043, 0x3449, 0x384E, 0x3C54, 0x405A, 0x4866, 0x4C6D, 0x5072, 0x587F, 0x1215, 0x5476, 0x4C6A, 0x5071, 
	0x445E, 0x4865, 0x4059, 0x3C53, 0x384C, 0x3447, 0x3041, 0x4E6C, 0x2C3A, 0x4661, 0x6087, 0x2835, 0x3E54, 
	0x5474, 0x242F, 0x4C69, 0x3649, 0x4862, 0x2029, 0x4057, 0x2E3D, 0x5C7E, 0x3C51, 0x5879, 0x1C22, 0x2A37, 
	0x506D, 0x4259, 0x3444, 0x2631, 0x4861, 0x303E, 0x5C7C, 0x3A4D, 0x445A, 0x5876, 0x181D, 0x5A78, 0x6487, 
	0x465C, 0x3C4E, 0x3240, 0x4C65, 0x2832, 0x4257, 0x526D, 0x3848, 0x485F, 0x5875, 0x1E25, 0x6484, 0x4458, 
	0x3443, 0x4A60, 0x607F, 0x242C, 0x5069, 0x5671, 0x4053, 0x5C78, 0x2A35, 0x4C62, 0x303D, 0x5872, 0x3644, 
	0x6483, 0x3C4D, 0x4254, 0x4E64, 0x546C, 0x6684, 0x1417, 0x6480, 0x5871, 0x4C61, 0x4659, 0x4051, 0x3A49, 
	0x3441, 0x546A, 0x2E38, 0x485A, 0x627C, 0x2831, 0x566D, 0x3C4A, 0x5065, 0x2228, 0x3643, 0x586E, 0x4454, 
	0x303B, 0x6079, 0x3E4C, 0x4C5F, 0x1C21, 0x6A84, 0x4E60, 0x404E, 0x323C, 0x6C87, 0x4859, 0x242B, 0x586D, 
	0x4251, 0x2C34, 0x5265, 0x343E, 0x3C49, 0x4452, 0x4C5C, 0x5466, 0x6C84, 0x1619, 0x6075, 0x5061, 0x4857, 
	0x404D, 0x3842, 0x5A6C, 0x3038, 0x4A58, 0x6C83, 0x6479, 0x282F, 0x5464, 0x3A44, 0x4C5A, 0x5E71, 0x2025, 
	0x4E5C, 0x3C47, 0x5869, 0x2A31, 0x6C80, 0x505F, 0x343D, 0x3E48, 0x4854, 0x5261, 0x5C6C, 0x181A, 0x6A7C, 
	0x5665, 0x4C59, 0x424D, 0x3840, 0x5866, 0x2E35, 0x6475, 0x444E, 0x5A68, 0x7083, 0x2429, 0x5C6A, 0x4651, 
	0x3037, 0x5E6D, 0x3C44, 0x4853, 0x5460, 0x606E, 0x1A1C, 0x262B, 0x7080, 0x5865, 0x4C57, 0x4049, 0x343B, 
	0x7484, 0x4E58, 0x282C, 0x505A, 0x363D, 0x6C7A, 0x444C, 0x525C, 0x606D, 0x6E7C, 0x1C1F, 0x7280, 0x5661, 
	0x4851, 0x3A41, 0x5862, 0x7684, 0x2C30, 0x6875, 0x5A64, 0x7887, 0x3C43, 0x4C54, 0x5C66, 0x6C79, 0x1E21, 
	0x707C, 0x5059, 0x4047, 0x626C, 0x3035, 0x646E, 0x4249, 0x545C, 0x6670, 0x2022, 0x565F, 0x5861, 0x464D, 
	0x3438, 0x6E78, 0x484E, 0x5C64, 0x2224, 0x363B, 0x6069, 0x4C53, 0x383C, 0x4E54, 0x7883, 0x646D, 0x2427, 
	0x6871, 0x5259, 0x3C41, 0x545A, 0x6C75, 0x2629, 0x585F, 0x4044, 0x5A60, 0x747C, 0x282B, 0x7880, 0x4448, 
	0x5E65, 0x6066, 0x7C84, 0x2A2C, 0x7E87, 0x646A, 0x484D, 0x666C, 0x2C2E, 0x6A70, 0x4C51, 0x6C72, 0x2E31, 
	0x5054, 0x7278, 0x3032, 0x5257, 0x767C, 0x5458, 0x787F, 0x3234, 0x585C, 0x7E84, 0x3437, 0x5C60, 0x3638, 
	0x6065, 0x383A, 0x6469, 0x3A3D, 0x686D, 0x3C3E, 0x6C71, 0x3E40, 0x7075, 0x4043, 0x4244, 0x4446, 0x7C80, 
	0x4649, 0x484A, 0x8287, 0x4A4C, 0x4C4E, 0x4E50, 0x5053, 0x5254, 0x5456, 0x5659, 0x585A, 0x5A5C, 0x5E61, 
	0x6062, 0x6466, 0x686A, 0x6C6E, 0x7072, 0x7678, 0x7C7E, 0x8284, 
};

// converts the values in the lookup table to x and y analog values, and a flag.
static void unpack_analog(uint16_t analog, int16_t* x, int16_t* y, uint16_t* is_accessible_vc){
  *x = -(int16_t)((analog & 0xFE00) >> 9);
  *y =  (int16_t)((analog & 0x01FE) >> 1);
  *is_accessible_vc = (analog & 0x0001);
}

static int16_t adjust_analog(int16_t x){
  if (8 > x && x > -8)
    return 0;
  else if (x > 67)
    return 60;
  else if (x < -67)
    return -60;
  else if (x < 0)
    return x + 7;
  else
    return x - 7;
}

static uint16_t lookup(uint16_t* found_angle, uint16_t angle, uint16_t r_min){
    uint16_t is_accessible_vc;
    uint16_t lower_val = 0;
    uint16_t lower_idx = 0;
    uint16_t upper_val;
    uint16_t upper_idx;
    uint16_t i;
    int16_t x;
    int16_t y;

    // Finding the first eligible lower boundary
    for (i = 0; i < sizeof(angle_tbl)/sizeof(angle_tbl[0]); i++){
        unpack_analog(analog_tbl[i], &x, &y, &is_accessible_vc);
        x = adjust_analog(x);
        y = adjust_analog(y);
        if ((!settings->bits.wiivc_cam || is_accessible_vc) && (x*x + y*y >= r_min*r_min)){
		    if (angle_tbl[i] >= angle){
				*found_angle = angle_tbl[i];
				return analog_tbl[i];
			}
			else{
				lower_val = angle_tbl[i];
				lower_idx = i;
				break;
			}
		}
	}

	// Finding the best candidate:
	for (i = lower_idx+1; i < sizeof(angle_tbl)/sizeof(angle_tbl[0]); i++){
		unpack_analog(analog_tbl[i], &x, &y, &is_accessible_vc);
		x = adjust_analog(x);
		y = adjust_analog(y);
		if ((!settings->bits.wiivc_cam || is_accessible_vc) && (x*x + y*y >= r_min*r_min)){
			upper_val = angle_tbl[i];
			upper_idx = i;
			if (upper_val == angle){
                *found_angle = upper_val;
				return analog_tbl[i];
			}
			else if (upper_val > angle){
				if (upper_val - angle <= angle - lower_val){
                    *found_angle = upper_val;
					return analog_tbl[upper_idx];
				}
				else{
                    *found_angle = lower_val;
					return analog_tbl[lower_idx];
				}
			}
			lower_val = upper_val;
			lower_idx = upper_idx;
		}
	}
    *found_angle = 0x2000;
	return 0x8687; // encoded result for diagonal (67,67)
}

static void find_best_analog(int16_t* x, int16_t* y, uint16_t* found_angle, uint16_t full_angle, uint16_t r_min){
	int16_t x_temp;
	int16_t y_temp;
	uint16_t is_accessible_vc;
    uint16_t angle;
    uint16_t analog;
	uint16_t lookup_angle;
	
    angle = full_angle - z64_game.camera_angle;
	if (angle < 0x2000)
	{
		lookup_angle = angle;
		analog = lookup(found_angle, lookup_angle, r_min);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc);
		
        *found_angle = *found_angle;
		*x = x_temp;
		*y = y_temp;		
	}
	else if (angle < 0x4000)
	{
		lookup_angle = 0x4000 - angle;
		analog = lookup(found_angle, lookup_angle, r_min);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc);
		
        *found_angle = 0x4000 - *found_angle;
		*x = -y_temp;
		*y = -x_temp;	
	}
	else if (angle < 0x6000)
	{
		lookup_angle = angle - 0x4000;
		analog = lookup(found_angle, lookup_angle, r_min);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc);
		
        *found_angle = *found_angle + 0x4000;
		*x = -y_temp;
		*y = x_temp;	
	}
	else if (angle < 0x8000)
	{
		lookup_angle = 0x8000 - angle;
		analog = lookup(found_angle, lookup_angle, r_min);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc);
		
        *found_angle = 0x8000 - *found_angle;
		*x = x_temp;
		*y = -y_temp;	
	}
	else if (angle < 0xA000)
	{
		lookup_angle = angle - 0x8000;
		analog = lookup(found_angle, lookup_angle, r_min);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc);
		
        *found_angle = *found_angle + 0x8000;
		*x = -x_temp;
		*y = -y_temp;	
	}
	else if (angle < 0xC000)
	{
		lookup_angle = 0xC000 - angle;
		analog = lookup(found_angle, lookup_angle, r_min);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc);
		
        *found_angle = 0xC000 - *found_angle;
		*x = y_temp;
		*y = x_temp;	
	}
	else if (angle < 0xE000)
	{
		lookup_angle = angle - 0xC000;
		analog = lookup(found_angle, lookup_angle, r_min);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc);
		
        *found_angle = *found_angle + 0xC000;
		*x = y_temp;
		*y = -x_temp;	
	}
	else
	{
		lookup_angle = -angle;
		analog = lookup(found_angle, lookup_angle, r_min);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc);
		
        *found_angle = -*found_angle;
		*x = -x_temp;
		*y = y_temp;	
	}
    *found_angle = *found_angle + z64_game.camera_angle;
}

void gz_angle_finder(){
    if (gz.angle_enable){
		if (gz.angle_use_min)
			find_best_analog(&gz.angle_x, &gz.angle_y, &gz.angle_best_matching, gz.angle_desired, gz.angle_r_min);
		else
			find_best_analog(&gz.angle_x, &gz.angle_y, &gz.angle_best_matching, gz.angle_desired, 0);
	}        
}
