#include "gz.h"
#include "z64.h"

static uint16_t angle_tbl[] = {
	0x00AD, 0x00AD, 0x00B7, 0x00B7, 0x00B7, 0x00C2, 0x00C2, 0x00C2, 0x00CC, 0x00CC, 0x00CC, 0x00D6, 0x00D6, 0x00E0, 0x00E0, 0x00EA, 0x00EA, 
	0x00F4, 0x00F4, 0x00FF, 0x0109, 0x0109, 0x0113, 0x011D, 0x011D, 0x0127, 0x0131, 0x013C, 0x0146, 0x0150, 0x015A, 0x015A, 0x0164, 0x0164, 
	0x0164, 0x016F, 0x0179, 0x0179, 0x0179, 0x0183, 0x0183, 0x018D, 0x018D, 0x018D, 0x0197, 0x01A1, 0x01A1, 0x01AC, 0x01B6, 0x01B6, 0x01C0, 
	0x01CA, 0x01CA, 0x01D4, 0x01DE, 0x01DE, 0x01E9, 0x01F3, 0x01F3, 0x01FD, 0x0207, 0x0207, 0x0207, 0x0211, 0x021B, 0x021B, 0x0226, 0x0226, 
	0x0226, 0x0230, 0x0230, 0x023A, 0x0244, 0x0244, 0x0244, 0x024E, 0x0258, 0x0258, 0x0262, 0x0262, 0x0262, 0x026D, 0x0277, 0x0281, 0x028B, 
	0x028B, 0x028B, 0x0295, 0x029F, 0x02A9, 0x02B4, 0x02B4, 0x02B4, 0x02B4, 0x02BE, 0x02C8, 0x02D2, 0x02D2, 0x02D2, 0x02DC, 0x02E6, 0x02E6, 
	0x02E6, 0x02E6, 0x02F0, 0x02FB, 0x0305, 0x0305, 0x030F, 0x030F, 0x0323, 0x0323, 0x0323, 0x0323, 0x032D, 0x0337, 0x0341, 0x0341, 0x034C, 
	0x0356, 0x0360, 0x0360, 0x0360, 0x0360, 0x0360, 0x0374, 0x0374, 0x037E, 0x037E, 0x0388, 0x0388, 0x0392, 0x0392, 0x039C, 0x039C, 0x03B1, 
	0x03B1, 0x03B1, 0x03B1, 0x03B1, 0x03C5, 0x03C5, 0x03CF, 0x03D9, 0x03E3, 0x03E3, 0x03E3, 0x03ED, 0x03F7, 0x03F7, 0x040C, 0x040C, 0x040C, 
	0x040C, 0x040C, 0x040C, 0x0420, 0x0420, 0x042A, 0x0434, 0x0434, 0x043E, 0x0448, 0x0448, 0x0448, 0x0452, 0x045C, 0x045C, 0x0466, 0x0466, 
	0x0470, 0x0484, 0x0484, 0x0484, 0x0484, 0x0484, 0x0484, 0x0499, 0x0499, 0x04A3, 0x04AD, 0x04AD, 0x04B7, 0x04B7, 0x04C1, 0x04C1, 0x04C1, 
	0x04CB, 0x04D5, 0x04DF, 0x04DF, 0x04E9, 0x04E9, 0x04F3, 0x04F3, 0x04FD, 0x0511, 0x0511, 0x0511, 0x0511, 0x0511, 0x0511, 0x0511, 0x0525, 
	0x052F, 0x052F, 0x0539, 0x0543, 0x054D, 0x054D, 0x0557, 0x0557, 0x056B, 0x056B, 0x056B, 0x056B, 0x0575, 0x0575, 0x057F, 0x0589, 0x0589, 
	0x0593, 0x0593, 0x0593, 0x059D, 0x05A7, 0x05A7, 0x05B1, 0x05C5, 0x05C5, 0x05C5, 0x05C5, 0x05C5, 0x05C5, 0x05C5, 0x05C5, 0x05E3, 0x05E3, 
	0x05ED, 0x05F7, 0x0601, 0x0601, 0x060B, 0x0615, 0x0615, 0x0615, 0x061F, 0x061F, 0x0629, 0x0629, 0x063D, 0x063D, 0x063D, 0x063D, 0x0647, 
	0x0647, 0x0651, 0x065B, 0x0665, 0x0665, 0x0665, 0x066E, 0x0678, 0x0678, 0x0682, 0x0682, 0x068C, 0x0696, 0x0696, 0x06A0, 0x06BE, 0x06BE, 
	0x06BE, 0x06BE, 0x06BE, 0x06BE, 0x06BE, 0x06BE, 0x06BE, 0x06BE, 0x06DC, 0x06DC, 0x06DC, 0x06E5, 0x06EF, 0x06F9, 0x06F9, 0x06F9, 0x0703, 
	0x0703, 0x070D, 0x0717, 0x0721, 0x0721, 0x0721, 0x072B, 0x0735, 0x0735, 0x073E, 0x073E, 0x0752, 0x0752, 0x0752, 0x0752, 0x0752, 0x0766, 
	0x0766, 0x0770, 0x077A, 0x077A, 0x0783, 0x0783, 0x078D, 0x078D, 0x078D, 0x0797, 0x07A1, 0x07A1, 0x07AB, 0x07AB, 0x07B5, 0x07BE, 0x07BE, 
	0x07C8, 0x07C8, 0x07D2, 0x07DC, 0x07DC, 0x07E6, 0x07E6, 0x080D, 0x080D, 0x080D, 0x080D, 0x080D, 0x080D, 0x080D, 0x080D, 0x080D, 0x080D, 
	0x080D, 0x080D, 0x082A, 0x0834, 0x0834, 0x0834, 0x083E, 0x0848, 0x0851, 0x0851, 0x085B, 0x085B, 0x085B, 0x0865, 0x0878, 0x0878, 0x0878, 
	0x0882, 0x0882, 0x088C, 0x0896, 0x0896, 0x0896, 0x0896, 0x08A9, 0x08A9, 0x08B3, 0x08BD, 0x08BD, 0x08BD, 0x08C6, 0x08D0, 0x08D0, 0x08DA, 
	0x08ED, 0x08ED, 0x08ED, 0x08ED, 0x08ED, 0x08ED, 0x0901, 0x0901, 0x0901, 0x090A, 0x0914, 0x091E, 0x091E, 0x0927, 0x0927, 0x0931, 0x093B, 
	0x093B, 0x093B, 0x093B, 0x094E, 0x094E, 0x0958, 0x0958, 0x0961, 0x096B, 0x096B, 0x096B, 0x0975, 0x097E, 0x097E, 0x0988, 0x0988, 0x0992, 
	0x099B, 0x099B, 0x09A5, 0x09A5, 0x09A5, 0x09AE, 0x09B8, 0x09C2, 0x09C2, 0x09CB, 0x09CB, 0x09D5, 0x09FB, 0x09FB, 0x09FB, 0x09FB, 0x09FB, 
	0x09FB, 0x09FB, 0x09FB, 0x09FB, 0x09FB, 0x09FB, 0x09FB, 0x09FB, 0x09FB, 0x09FB, 0x0A22, 0x0A2B, 0x0A2B, 0x0A2B, 0x0A35, 0x0A3E, 0x0A3E, 
	0x0A48, 0x0A51, 0x0A51, 0x0A51, 0x0A5B, 0x0A64, 0x0A64, 0x0A6E, 0x0A77, 0x0A77, 0x0A77, 0x0A81, 0x0A8B, 0x0A94, 0x0A9E, 0x0A9E, 0x0A9E, 
	0x0A9E, 0x0AA7, 0x0AB1, 0x0ABA, 0x0ABA, 0x0AC4, 0x0AC4, 0x0ACD, 0x0AD7, 0x0AD7, 0x0AD7, 0x0AD7, 0x0AD7, 0x0AE9, 0x0AF3, 0x0AF3, 0x0AF3, 
	0x0AFC, 0x0B06, 0x0B06, 0x0B06, 0x0B19, 0x0B22, 0x0B22, 0x0B22, 0x0B2C, 0x0B35, 0x0B35, 0x0B3F, 0x0B3F, 0x0B5B, 0x0B5B, 0x0B5B, 0x0B5B, 
	0x0B5B, 0x0B5B, 0x0B5B, 0x0B5B, 0x0B6E, 0x0B6E, 0x0B77, 0x0B77, 0x0B80, 0x0B8A, 0x0B93, 0x0B93, 0x0B9D, 0x0B9D, 0x0BA6, 0x0BA6, 0x0BA6, 
	0x0BB9, 0x0BB9, 0x0BB9, 0x0BC2, 0x0BCB, 0x0BCB, 0x0BDE, 0x0BDE, 0x0BDE, 0x0BDE, 0x0BDE, 0x0BDE, 0x0BF1, 0x0BFA, 0x0BFA, 0x0C03, 0x0C0D, 
	0x0C0D, 0x0C0D, 0x0C16, 0x0C16, 0x0C29, 0x0C29, 0x0C29, 0x0C29, 0x0C3B, 0x0C3B, 0x0C45, 0x0C45, 0x0C4E, 0x0C57, 0x0C57, 0x0C57, 0x0C60, 
	0x0C6A, 0x0C6A, 0x0C73, 0x0C73, 0x0C73, 0x0C7C, 0x0C86, 0x0C8F, 0x0C8F, 0x0C98, 0x0CA1, 0x0CA1, 0x0CA1, 0x0CAB, 0x0CAB, 0x0CB4, 0x0CB4, 
	0x0CBD, 0x0CC6, 0x0CCF, 0x0CCF, 0x0CD9, 0x0CD9, 0x0CE2, 0x0CE2, 0x0CE2, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 
	0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D19, 0x0D50, 0x0D50, 0x0D59, 0x0D59, 0x0D62, 
	0x0D62, 0x0D6B, 0x0D6B, 0x0D74, 0x0D7D, 0x0D87, 0x0D87, 0x0D90, 0x0D90, 0x0D90, 0x0D99, 0x0DA2, 0x0DA2, 0x0DAB, 0x0DB4, 0x0DB4, 0x0DB4, 
	0x0DBD, 0x0DC6, 0x0DC6, 0x0DCF, 0x0DCF, 0x0DCF, 0x0DE1, 0x0DE1, 0x0DEA, 0x0DEA, 0x0DFC, 0x0DFC, 0x0DFC, 0x0DFC, 0x0E05, 0x0E0F, 0x0E18, 
	0x0E18, 0x0E21, 0x0E21, 0x0E2A, 0x0E33, 0x0E33, 0x0E33, 0x0E33, 0x0E33, 0x0E45, 0x0E4E, 0x0E4E, 0x0E4E, 0x0E56, 0x0E5F, 0x0E5F, 0x0E5F, 
	0x0E68, 0x0E71, 0x0E71, 0x0E7A, 0x0E83, 0x0E83, 0x0E8C, 0x0E9E, 0x0E9E, 0x0E9E, 0x0E9E, 0x0E9E, 0x0E9E, 0x0E9E, 0x0EB0, 0x0EB9, 0x0EB9, 
	0x0EC2, 0x0EC2, 0x0ECB, 0x0ED4, 0x0ED4, 0x0EDC, 0x0EE5, 0x0EE5, 0x0EEE, 0x0EF7, 0x0EF7, 0x0EF7, 0x0EF7, 0x0F00, 0x0F09, 0x0F09, 0x0F12, 
	0x0F1B, 0x0F1B, 0x0F1B, 0x0F23, 0x0F2C, 0x0F35, 0x0F35, 0x0F3E, 0x0F3E, 0x0F3E, 0x0F47, 0x0F50, 0x0F58, 0x0F58, 0x0F61, 0x0F61, 0x0F84, 
	0x0F84, 0x0F84, 0x0F84, 0x0F84, 0x0F84, 0x0F84, 0x0F84, 0x0F84, 0x0F84, 0x0F84, 0x0F84, 0x0F9F, 0x0FA7, 0x0FA7, 0x0FA7, 0x0FB0, 0x0FB9, 
	0x0FC2, 0x0FC2, 0x0FC2, 0x0FCA, 0x0FD3, 0x0FD3, 0x0FDC, 0x0FE5, 0x0FED, 0x0FED, 0x0FED, 0x0FF6, 0x0FFF, 0x0FFF, 0x1007, 0x1007, 0x1019, 
	0x1019, 0x1019, 0x1019, 0x1019, 0x1021, 0x102A, 0x102A, 0x1033, 0x103B, 0x103B, 0x103B, 0x1044, 0x104D, 0x104D, 0x1055, 0x1055, 0x105E, 
	0x1067, 0x1067, 0x1080, 0x1080, 0x1080, 0x1080, 0x1080, 0x1080, 0x1080, 0x1080, 0x1092, 0x109A, 0x109A, 0x10A3, 0x10AB, 0x10AB, 0x10AB, 
	0x10B4, 0x10B4, 0x10BC, 0x10C5, 0x10CE, 0x10CE, 0x10CE, 0x10D6, 0x10DF, 0x10E7, 0x10E7, 0x10E7, 0x10F0, 0x10F0, 0x10F8, 0x1109, 0x1109, 
	0x1109, 0x1109, 0x1109, 0x1109, 0x111A, 0x1123, 0x1123, 0x112B, 0x112B, 0x1134, 0x113C, 0x113C, 0x113C, 0x1145, 0x1145, 0x114D, 0x1156, 
	0x115E, 0x115E, 0x115E, 0x115E, 0x115E, 0x116F, 0x116F, 0x1177, 0x1180, 0x1180, 0x1180, 0x1188, 0x1191, 0x11A1, 0x11A1, 0x11A1, 0x11A1, 
	0x11AA, 0x11B2, 0x11B2, 0x11B2, 0x11BB, 0x11C3, 0x11CB, 0x11CB, 0x11CB, 0x11CB, 0x11D4, 0x11DC, 0x11E4, 0x11ED, 0x11ED, 0x11ED, 0x11F5, 
	0x11FD, 0x11FD, 0x1206, 0x1206, 0x1206, 0x120E, 0x120E, 0x121F, 0x121F, 0x1227, 0x122F, 0x122F, 0x1237, 0x1240, 0x1240, 0x1240, 0x1248, 
	0x1248, 0x1250, 0x1250, 0x1250, 0x1259, 0x1259, 0x1261, 0x1269, 0x1271, 0x127A, 0x1282, 0x1282, 0x128A, 0x128A, 0x1292, 0x1292, 0x1292, 
	0x129A, 0x129A, 0x129A, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 
	0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x12E4, 0x132D, 
	0x132D, 0x132D, 0x1335, 0x1335, 0x1335, 0x133D, 0x133D, 0x1345, 0x1345, 0x134D, 0x1355, 0x135E, 0x1366, 0x136E, 0x136E, 0x1376, 0x1376, 
	0x1376, 0x137E, 0x137E, 0x1386, 0x1386, 0x1386, 0x138E, 0x1396, 0x1396, 0x139E, 0x13A6, 0x13A6, 0x13B6, 0x13B6, 0x13BE, 0x13BE, 0x13BE, 
	0x13C6, 0x13C6, 0x13CE, 0x13D6, 0x13D6, 0x13D6, 0x13DE, 0x13E6, 0x13ED, 0x13F5, 0x13F5, 0x13F5, 0x13F5, 0x13FD, 0x1405, 0x140D, 0x140D, 
	0x140D, 0x1415, 0x141D, 0x141D, 0x141D, 0x141D, 0x142D, 0x1435, 0x143D, 0x143D, 0x143D, 0x1444, 0x144C, 0x144C, 0x145C, 0x145C, 0x145C, 
	0x145C, 0x145C, 0x1464, 0x146C, 0x1473, 0x1473, 0x147B, 0x147B, 0x147B, 0x1483, 0x148B, 0x148B, 0x1493, 0x1493, 0x149B, 0x14AA, 0x14AA, 
	0x14AA, 0x14AA, 0x14AA, 0x14AA, 0x14BA, 0x14C1, 0x14C1, 0x14C9, 0x14C9, 0x14C9, 0x14D1, 0x14D9, 0x14E0, 0x14E0, 0x14E0, 0x14E8, 0x14F0, 
	0x14F8, 0x14F8, 0x14FF, 0x14FF, 0x14FF, 0x1507, 0x150F, 0x150F, 0x1516, 0x1526, 0x1526, 0x1526, 0x1526, 0x1526, 0x1526, 0x1526, 0x1526, 
	0x153D, 0x153D, 0x1544, 0x154C, 0x154C, 0x1554, 0x1554, 0x155B, 0x1563, 0x1563, 0x1563, 0x156B, 0x1572, 0x1572, 0x157A, 0x1581, 0x1581, 
	0x1581, 0x1581, 0x1581, 0x1591, 0x1591, 0x1598, 0x1598, 0x15A0, 0x15A7, 0x15A7, 0x15A7, 0x15AF, 0x15B7, 0x15BE, 0x15BE, 0x15C6, 0x15CD, 
	0x15CD, 0x15CD, 0x15D5, 0x15DC, 0x15E4, 0x15E4, 0x15E4, 0x15EB, 0x1602, 0x1602, 0x1602, 0x1602, 0x1602, 0x1602, 0x1602, 0x1602, 0x1602, 
	0x1602, 0x1602, 0x1602, 0x1620, 0x1620, 0x1627, 0x1627, 0x162F, 0x1636, 0x163E, 0x163E, 0x163E, 0x1645, 0x1645, 0x164C, 0x1654, 0x165B, 
	0x165B, 0x165B, 0x1663, 0x166A, 0x166A, 0x1671, 0x1679, 0x1679, 0x1679, 0x1679, 0x1680, 0x1688, 0x1688, 0x168F, 0x1696, 0x1696, 0x169E, 
	0x16A5, 0x16A5, 0x16AC, 0x16AC, 0x16B4, 0x16C2, 0x16C2, 0x16C2, 0x16C2, 0x16C2, 0x16C2, 0x16C2, 0x16D1, 0x16D8, 0x16D8, 0x16E0, 0x16E7, 
	0x16E7, 0x16EE, 0x16F6, 0x16F6, 0x16F6, 0x16FD, 0x1704, 0x1704, 0x1704, 0x170B, 0x171A, 0x171A, 0x171A, 0x171A, 0x171A, 0x1721, 0x1728, 
	0x1728, 0x1730, 0x1730, 0x1737, 0x173E, 0x1745, 0x1745, 0x1745, 0x1745, 0x1754, 0x1754, 0x175B, 0x175B, 0x1769, 0x1769, 0x1769, 0x1770, 
	0x1770, 0x1778, 0x177F, 0x177F, 0x177F, 0x1786, 0x178D, 0x178D, 0x1794, 0x179B, 0x179B, 0x179B, 0x17A2, 0x17A2, 0x17AA, 0x17B1, 0x17B8, 
	0x17B8, 0x17BF, 0x17BF, 0x17C6, 0x17C6, 0x17CD, 0x17CD, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 
	0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x17F7, 0x1822, 0x1822, 0x1822, 0x1829, 0x1829, 0x1830, 0x1830, 
	0x1837, 0x183E, 0x1845, 0x1845, 0x184C, 0x184C, 0x1853, 0x1853, 0x1853, 0x185A, 0x1860, 0x1860, 0x1867, 0x186E, 0x1875, 0x1875, 0x1875, 
	0x187C, 0x187C, 0x1883, 0x188A, 0x188A, 0x188A, 0x1891, 0x1898, 0x1898, 0x189F, 0x189F, 0x18AD, 0x18AD, 0x18AD, 0x18AD, 0x18BA, 0x18BA, 
	0x18C1, 0x18C1, 0x18C1, 0x18C8, 0x18CF, 0x18CF, 0x18D6, 0x18E3, 0x18E3, 0x18E3, 0x18E3, 0x18E3, 0x18E3, 0x18F1, 0x18F1, 0x18F8, 0x18FF, 
	0x18FF, 0x18FF, 0x190C, 0x190C, 0x190C, 0x1913, 0x1913, 0x191A, 0x191A, 0x1921, 0x1928, 0x192E, 0x192E, 0x1935, 0x1935, 0x1943, 0x1943, 
	0x1943, 0x1943, 0x1943, 0x1943, 0x1943, 0x1943, 0x1957, 0x1957, 0x195D, 0x195D, 0x1964, 0x196B, 0x196B, 0x196B, 0x1972, 0x197F, 0x197F, 
	0x197F, 0x1986, 0x198C, 0x198C, 0x198C, 0x1993, 0x19A0, 0x19A0, 0x19A0, 0x19A0, 0x19A0, 0x19A7, 0x19AE, 0x19AE, 0x19B4, 0x19B4, 0x19BB, 
	0x19C2, 0x19C8, 0x19C8, 0x19C8, 0x19C8, 0x19CF, 0x19D5, 0x19DC, 0x19E3, 0x19E3, 0x19E3, 0x19E9, 0x19F0, 0x19F0, 0x19F6, 0x19FD, 0x19FD, 
	0x19FD, 0x1A04, 0x1A0A, 0x1A0A, 0x1A11, 0x1A17, 0x1A17, 0x1A17, 0x1A1E, 0x1A38, 0x1A38, 0x1A38, 0x1A38, 0x1A38, 0x1A38, 0x1A38, 0x1A38, 
	0x1A38, 0x1A38, 0x1A38, 0x1A38, 0x1A38, 0x1A38, 0x1A38, 0x1A52, 0x1A58, 0x1A58, 0x1A5F, 0x1A5F, 0x1A65, 0x1A6C, 0x1A72, 0x1A72, 0x1A72, 
	0x1A79, 0x1A79, 0x1A7F, 0x1A86, 0x1A86, 0x1A8C, 0x1A8C, 0x1A93, 0x1A99, 0x1A99, 0x1A99, 0x1A9F, 0x1AA6, 0x1AA6, 0x1AAC, 0x1AAC, 0x1AB9, 
	0x1AB9, 0x1AB9, 0x1AB9, 0x1AC0, 0x1AC6, 0x1AC6, 0x1ACC, 0x1ACC, 0x1AD3, 0x1AD9, 0x1ADF, 0x1ADF, 0x1ADF, 0x1AEC, 0x1AEC, 0x1AEC, 0x1AEC, 
	0x1AEC, 0x1AEC, 0x1AF9, 0x1AFF, 0x1AFF, 0x1B05, 0x1B0C, 0x1B0C, 0x1B0C, 0x1B12, 0x1B18, 0x1B18, 0x1B25, 0x1B25, 0x1B25, 0x1B25, 0x1B2B, 
	0x1B32, 0x1B32, 0x1B38, 0x1B38, 0x1B38, 0x1B44, 0x1B4B, 0x1B4B, 0x1B4B, 0x1B51, 0x1B51, 0x1B57, 0x1B5D, 0x1B64, 0x1B64, 0x1B64, 0x1B6A, 
	0x1B7D, 0x1B7D, 0x1B7D, 0x1B7D, 0x1B7D, 0x1B7D, 0x1B7D, 0x1B7D, 0x1B7D, 0x1B7D, 0x1B7D, 0x1B7D, 0x1B95, 0x1B95, 0x1B9C, 0x1B9C, 0x1BA2, 
	0x1BA8, 0x1BA8, 0x1BAE, 0x1BAE, 0x1BB4, 0x1BBA, 0x1BBA, 0x1BC1, 0x1BC1, 0x1BC7, 0x1BCD, 0x1BCD, 0x1BCD, 0x1BD3, 0x1BD3, 0x1BD9, 0x1BD9, 
	0x1BDF, 0x1BE5, 0x1BE5, 0x1BF2, 0x1BF2, 0x1BF2, 0x1BF2, 0x1BF2, 0x1BFE, 0x1BFE, 0x1C04, 0x1C04, 0x1C0A, 0x1C10, 0x1C10, 0x1C10, 0x1C16, 
	0x1C1C, 0x1C22, 0x1C22, 0x1C28, 0x1C28, 0x1C28, 0x1C2E, 0x1C34, 0x1C3A, 0x1C3A, 0x1C3A, 0x1C4C, 0x1C4C, 0x1C4C, 0x1C4C, 0x1C4C, 0x1C4C, 
	0x1C4C, 0x1C4C, 0x1C4C, 0x1C4C, 0x1C5E, 0x1C64, 0x1C64, 0x1C6A, 0x1C70, 0x1C70, 0x1C76, 0x1C76, 0x1C7C, 0x1C82, 0x1C82, 0x1C82, 0x1C88, 
	0x1C8E, 0x1C94, 0x1C94, 0x1C9A, 0x1C9A, 0x1C9A, 0x1C9A, 0x1CA6, 0x1CA6, 0x1CAC, 0x1CAC, 0x1CB2, 0x1CB2, 0x1CB2, 0x1CB8, 0x1CBE, 0x1CBE, 
	0x1CC3, 0x1CC9, 0x1CCF, 0x1CCF, 0x1CE1, 0x1CE1, 0x1CE1, 0x1CE1, 0x1CE1, 0x1CE1, 0x1CE1, 0x1CE1, 0x1CED, 0x1CF3, 0x1CF3, 0x1CF8, 0x1CFE, 
	0x1CFE, 0x1CFE, 0x1D04, 0x1D04, 0x1D0A, 0x1D10, 0x1D10, 0x1D16, 0x1D16, 0x1D16, 0x1D16, 0x1D21, 0x1D21, 0x1D27, 0x1D27, 0x1D2D, 0x1D33, 
	0x1D38, 0x1D38, 0x1D3E, 0x1D4A, 0x1D4A, 0x1D4A, 0x1D4A, 0x1D4A, 0x1D4A, 0x1D4A, 0x1D55, 0x1D5B, 0x1D5B, 0x1D61, 0x1D61, 0x1D66, 0x1D66, 
	0x1D6C, 0x1D72, 0x1D78, 0x1D78, 0x1D78, 0x1D7D, 0x1D7D, 0x1D83, 0x1D83, 0x1D89, 0x1D8E, 0x1D8E, 0x1D9A, 0x1D9A, 0x1D9A, 0x1D9A, 0x1D9A, 
	0x1D9A, 0x1DA5, 0x1DAB, 0x1DAB, 0x1DB1, 0x1DB1, 0x1DB6, 0x1DBC, 0x1DBC, 0x1DBC, 0x1DC2, 0x1DC7, 0x1DC7, 0x1DCD, 0x1DD3, 0x1DD3, 0x1DDE, 
	0x1DDE, 0x1DDE, 0x1DDE, 0x1DDE, 0x1DDE, 0x1DE9, 0x1DE9, 0x1DEF, 0x1DF4, 0x1DF4, 0x1DF4, 0x1DFA, 0x1DFF, 0x1E05, 0x1E05, 0x1E10, 0x1E10, 
	0x1E10, 0x1E10, 0x1E10, 0x1E1B, 0x1E1B, 0x1E21, 0x1E21, 0x1E26, 0x1E26, 0x1E2C, 0x1E2C, 0x1E32, 0x1E32, 0x1E3D, 0x1E3D, 0x1E3D, 0x1E3D, 
	0x1E3D, 0x1E42, 0x1E48, 0x1E4D, 0x1E4D, 0x1E53, 0x1E58, 0x1E5E, 0x1E5E, 0x1E5E, 0x1E5E, 0x1E69, 0x1E69, 0x1E6E, 0x1E6E, 0x1E74, 0x1E79, 
	0x1E7F, 0x1E7F, 0x1E7F, 0x1E7F, 0x1E84, 0x1E8A, 0x1E8A, 0x1E8A, 0x1E8F, 0x1E94, 0x1E9A, 0x1E9A, 0x1E9A, 0x1E9A, 0x1E9F, 0x1EA5, 0x1EAA, 
	0x1EB0, 0x1EB0, 0x1EB0, 0x1EB5, 0x1EBA, 0x1EC0, 0x1EC5, 0x1EC5, 0x1EC5, 0x1ECB, 0x1ECB, 0x1ED0, 0x1ED5, 0x1ED5, 0x1ED5, 0x1EDB, 0x1EE0, 
	0x1EE0, 0x1EE6, 0x1EE6, 0x1EE6, 0x1EEB, 0x1EEB, 0x1EF0, 0x1EF6, 0x1EF6, 0x1EF6, 0x1EFB, 0x1F00, 0x1F00, 0x1F06, 0x1F0B, 0x1F0B, 0x1F10, 
	0x1F16, 0x1F16, 0x1F1B, 0x1F20, 0x1F20, 0x1F26, 0x1F2B, 0x1F2B, 0x1F30, 0x1F36, 0x1F36, 0x1F36, 0x1F3B, 0x1F3B, 0x1F40, 0x1F40, 0x1F40, 
	0x1F45, 0x1F4B, 0x1F4B, 0x1F4B, 0x1F50, 0x1F50, 0x1F55, 0x1F5A, 0x1F60, 0x1F65, 0x1F6A, 0x1F6F, 0x1F6F, 0x1F75, 0x1F7A, 0x1F7A, 0x1F7F, 
	0x1F84, 0x1F84, 0x1F8A, 0x1F8A, 0x1F8F, 0x1F8F, 0x1F94, 0x1F94, 0x1F99, 0x1F99, 0x1F99, 0x1F9E, 0x1F9E, 0x1F9E, 0x1FA4, 0x1FA4, 0x1FA4, 
	0x1FA9, 0x1FA9,
};
static uint16_t analog_tbl[] = {
    0x1109, 0x110D, 0x10FC, 0x1100, 0x1105, 0x10F0, 0x10F4, 0x10F8, 0x10E4, 0x10E8, 0x10EC, 0x10DC, 0x10E0, 0x10D4, 0x10D8, 0x10CC, 0x10D0, 
    0x10C4, 0x10C8, 0x10C0, 0x10B8, 0x10BC, 0x10B4, 0x10AC, 0x10B0, 0x10A8, 0x10A4, 0x10A0, 0x109C, 0x1098, 0x1094, 0x130F, 0x1090, 0x1307, 
    0x1309, 0x1300, 0x108C, 0x12F8, 0x12FE, 0x1088, 0x12F4, 0x1084, 0x12EC, 0x12F2, 0x12EA, 0x1080, 0x12E4, 0x12E2, 0x107C, 0x12DC, 0x12DA, 
    0x1078, 0x12D4, 0x12D2, 0x1074, 0x12CC, 0x12CA, 0x1070, 0x12C4, 0x12C2, 0x106C, 0x12BE, 0x150F, 0x1509, 0x12B8, 0x1507, 0x1068, 0x12B4, 
    0x1500, 0x12B2, 0x14FE, 0x14F8, 0x1064, 0x12AE, 0x14F4, 0x14F2, 0x12A8, 0x14EC, 0x1060, 0x12A6, 0x14EA, 0x14E4, 0x12A2, 0x14E2, 0x105C, 
    0x129C, 0x14DC, 0x14DA, 0x129A, 0x14D4, 0x1058, 0x1294, 0x14D2, 0x170F, 0x1709, 0x14CC, 0x1292, 0x14CA, 0x1707, 0x1700, 0x1054, 0x128E, 
    0x14C4, 0x16FE, 0x16F8, 0x14C2, 0x1288, 0x16F4, 0x14BE, 0x16F2, 0x1050, 0x1286, 0x14B8, 0x16EC, 0x16EA, 0x14B4, 0x1282, 0x16E4, 0x14B2, 
    0x16E2, 0x104C, 0x127C, 0x14AE, 0x16DC, 0x190F, 0x16DA, 0x1909, 0x14A8, 0x1907, 0x127A, 0x16D4, 0x14A6, 0x1901, 0x16D2, 0x18FE, 0x1048, 
    0x1276, 0x14A2, 0x16CC, 0x18F8, 0x16CA, 0x18F4, 0x149C, 0x18F2, 0x1270, 0x16C4, 0x18EC, 0x149A, 0x16C2, 0x18EA, 0x1044, 0x126E, 0x1494, 
    0x16BE, 0x18E4, 0x1B0D, 0x18E2, 0x1B09, 0x16B8, 0x1492, 0x1B05, 0x18DC, 0x126A, 0x16B4, 0x1B01, 0x18DA, 0x148E, 0x1AFC, 0x16B2, 0x18D4, 
    0x1AF8, 0x1040, 0x1264, 0x1488, 0x16AE, 0x18D2, 0x1AF4, 0x18CC, 0x1AF0, 0x16A8, 0x1486, 0x1AEC, 0x18CA, 0x1D0F, 0x1262, 0x16A6, 0x1AE8, 
    0x1D09, 0x18C4, 0x1482, 0x1AE4, 0x16A2, 0x1D07, 0x18C2, 0x1AE0, 0x1D01, 0x103C, 0x125E, 0x147C, 0x169C, 0x18BE, 0x1ADC, 0x1CFE, 0x1CF8, 
    0x18B8, 0x1AD8, 0x169A, 0x1CF4, 0x147A, 0x1AD4, 0x18B4, 0x1CF2, 0x1258, 0x1694, 0x1AD0, 0x1F0F, 0x18B2, 0x1CEC, 0x1F09, 0x1476, 0x1ACC, 
    0x1692, 0x1CEA, 0x1F07, 0x18AE, 0x1AC8, 0x1CE4, 0x1F01, 0x1038, 0x1256, 0x1470, 0x168E, 0x18A8, 0x1AC4, 0x1CE2, 0x1EFE, 0x1CDC, 0x1EF8, 
    0x1AC0, 0x18A6, 0x1688, 0x1EF4, 0x1CDA, 0x146E, 0x1ABC, 0x210F, 0x18A2, 0x1EF2, 0x1CD4, 0x2109, 0x1252, 0x1686, 0x1AB8, 0x1EEC, 0x1CD2, 
    0x2107, 0x189C, 0x1EEA, 0x146A, 0x1AB4, 0x2101, 0x1CCC, 0x1682, 0x1EE4, 0x189A, 0x20FF, 0x1AB0, 0x1CCA, 0x1EE2, 0x20F8, 0x1034, 0x124E, 
    0x1464, 0x167C, 0x1894, 0x1AAC, 0x1CC4, 0x1EDC, 0x20F4, 0x230D, 0x1EDA, 0x20F2, 0x2309, 0x1CC2, 0x1AA8, 0x1892, 0x20EC, 0x2305, 0x167A, 
    0x1ED4, 0x1CBE, 0x2301, 0x1462, 0x1AA4, 0x20EA, 0x1ED2, 0x188E, 0x22FD, 0x1CB8, 0x20E4, 0x124A, 0x1676, 0x1AA0, 0x1ECC, 0x22F8, 0x20E2, 
    0x250F, 0x1CB4, 0x1888, 0x22F4, 0x1ECA, 0x2509, 0x145E, 0x1A9C, 0x20DC, 0x22F0, 0x1CB2, 0x2507, 0x1670, 0x1EC4, 0x20DA, 0x1886, 0x22EC, 
    0x1A98, 0x2501, 0x1CAE, 0x1EC2, 0x20D4, 0x22E8, 0x24FF, 0x1030, 0x1244, 0x1458, 0x166E, 0x1882, 0x1A94, 0x1CA8, 0x1EBE, 0x20D2, 0x22E4, 
    0x24F8, 0x270F, 0x2709, 0x20CC, 0x22E0, 0x24F4, 0x1EB8, 0x1CA6, 0x1A90, 0x2707, 0x187C, 0x22DC, 0x24F2, 0x20CA, 0x166A, 0x1EB4, 0x2701, 
    0x1CA2, 0x24EC, 0x22D8, 0x1456, 0x1A8C, 0x20C4, 0x26FF, 0x1EB2, 0x24EA, 0x290F, 0x187A, 0x22D4, 0x26F8, 0x1C9C, 0x20C2, 0x24E4, 0x2909, 
    0x1242, 0x1664, 0x1A88, 0x1EAE, 0x22D0, 0x26F4, 0x20BE, 0x24E2, 0x2907, 0x1C9A, 0x26F2, 0x1876, 0x22CC, 0x1EA8, 0x2901, 0x24DC, 0x1452, 
    0x1A84, 0x20B8, 0x26EC, 0x22C8, 0x28FF, 0x1C94, 0x2B0F, 0x24DA, 0x1662, 0x1EA6, 0x26EA, 0x28F9, 0x20B4, 0x2B09, 0x1870, 0x22C4, 0x24D4, 
    0x1A80, 0x26E4, 0x1C92, 0x28F4, 0x2B07, 0x1EA2, 0x20B2, 0x22C0, 0x24D2, 0x26E2, 0x28F2, 0x2B01, 0x102C, 0x123E, 0x144E, 0x165E, 0x186E, 
    0x1A7C, 0x1C8E, 0x1E9C, 0x20AE, 0x22BC, 0x24CC, 0x26DC, 0x28EC, 0x2AFF, 0x2D0D, 0x2D09, 0x26DA, 0x28EA, 0x2AF9, 0x24CA, 0x20A8, 0x22B8, 
    0x1E9A, 0x1C88, 0x2AF4, 0x2D05, 0x28E4, 0x1A78, 0x26D4, 0x24C4, 0x186A, 0x22B4, 0x2D01, 0x2AF2, 0x20A6, 0x28E2, 0x1658, 0x1E94, 0x26D2, 
    0x2F0F, 0x2CFD, 0x24C2, 0x1C86, 0x2AEC, 0x22B0, 0x28DC, 0x2F09, 0x144A, 0x1A74, 0x20A2, 0x26CC, 0x2CF9, 0x2AEA, 0x1E92, 0x24BE, 0x2F07, 
    0x28DA, 0x1864, 0x22AC, 0x2CF4, 0x26CA, 0x1C82, 0x2AE4, 0x2F01, 0x209C, 0x24B8, 0x28D4, 0x2CF0, 0x310F, 0x123A, 0x1656, 0x1A70, 0x1E8E, 
    0x22A8, 0x26C4, 0x2AE2, 0x2EFF, 0x2CEC, 0x3109, 0x24B4, 0x28D2, 0x209A, 0x2EF9, 0x1C7C, 0x2ADC, 0x26C2, 0x3107, 0x1862, 0x22A4, 0x2CE8, 
    0x1E88, 0x28CC, 0x2EF5, 0x24B2, 0x2ADA, 0x3101, 0x1444, 0x1A6C, 0x2094, 0x26BE, 0x2CE4, 0x330D, 0x2EF2, 0x22A0, 0x28CA, 0x30FF, 0x1C7A, 
    0x2AD4, 0x3309, 0x24AE, 0x2CE0, 0x1652, 0x1E86, 0x26B8, 0x2EEC, 0x28C4, 0x30F9, 0x2092, 0x3305, 0x2AD2, 0x185E, 0x229C, 0x2CDC, 0x2EEA, 
    0x24A8, 0x30F5, 0x1A68, 0x26B4, 0x3301, 0x350F, 0x28C2, 0x1C76, 0x2ACC, 0x2CD8, 0x1E82, 0x2EE4, 0x30F2, 0x208E, 0x32FD, 0x2298, 0x3509, 
    0x24A6, 0x26B2, 0x28BE, 0x2ACA, 0x2CD4, 0x2EE2, 0x30EC, 0x32F9, 0x3507, 0x1028, 0x1234, 0x1442, 0x164E, 0x1858, 0x1A64, 0x1C70, 0x1E7C, 
    0x2088, 0x2294, 0x24A2, 0x26AE, 0x28B8, 0x2AC4, 0x2CD0, 0x2EDC, 0x30EA, 0x32F5, 0x3501, 0x370F, 0x34FF, 0x3709, 0x30E4, 0x32F1, 0x2CCC, 
    0x2EDA, 0x28B4, 0x2AC2, 0x26A8, 0x249C, 0x2290, 0x3707, 0x2086, 0x32EC, 0x34F9, 0x30E2, 0x1E7A, 0x2ED4, 0x2CC8, 0x1C6E, 0x2ABE, 0x390D, 
    0x3701, 0x28B2, 0x34F5, 0x1A60, 0x26A6, 0x32E8, 0x249A, 0x30DC, 0x2ED2, 0x3909, 0x1856, 0x228C, 0x2CC4, 0x36FF, 0x34F3, 0x2AB8, 0x2082, 
    0x32E4, 0x28AE, 0x30DA, 0x3905, 0x164A, 0x1E76, 0x26A2, 0x2ECC, 0x36F9, 0x34EC, 0x2494, 0x2CC0, 0x3B0F, 0x32E0, 0x1C6A, 0x2AB4, 0x3901, 
    0x30D4, 0x2288, 0x36F5, 0x28A8, 0x2ECA, 0x34EA, 0x3B09, 0x143E, 0x1A5C, 0x207C, 0x269C, 0x2CBC, 0x32DC, 0x38FD, 0x36F3, 0x2AB2, 0x30D2, 
    0x2492, 0x3B07, 0x34E4, 0x1E70, 0x2EC4, 0x38F9, 0x28A6, 0x32D8, 0x3D0F, 0x1852, 0x2284, 0x2CB8, 0x36EC, 0x3B01, 0x269A, 0x30CC, 0x34E2, 
    0x1C64, 0x2AAE, 0x38F5, 0x3D09, 0x2EC2, 0x207A, 0x32D4, 0x248E, 0x36EA, 0x3AFF, 0x28A2, 0x2CB4, 0x30CA, 0x34DC, 0x38F1, 0x3D07, 0x1232, 
    0x1644, 0x1A58, 0x1E6E, 0x2280, 0x2694, 0x2AA8, 0x2EBE, 0x32D0, 0x36E4, 0x3AF9, 0x3F0D, 0x3D01, 0x30C4, 0x34DA, 0x38ED, 0x2CB0, 0x289C, 
    0x2488, 0x3AF5, 0x3F09, 0x36E2, 0x2076, 0x32CC, 0x2EB8, 0x3CFF, 0x1C62, 0x2AA6, 0x38E8, 0x34D4, 0x2692, 0x3F05, 0x30C2, 0x3AF3, 0x184E, 
    0x227C, 0x2CAC, 0x36DC, 0x410F, 0x3CF9, 0x289A, 0x32C8, 0x38E4, 0x1E6A, 0x2EB4, 0x3F01, 0x34D2, 0x2486, 0x3AED, 0x2AA2, 0x4109, 0x30BE, 
    0x36DA, 0x3CF5, 0x143A, 0x1A54, 0x2070, 0x268E, 0x2CA8, 0x32C4, 0x38E0, 0x3EFD, 0x4107, 0x34CC, 0x3AEA, 0x2EB2, 0x2894, 0x3CF3, 0x430F, 
    0x2278, 0x36D4, 0x30B8, 0x3EF9, 0x1C5E, 0x2A9C, 0x38DC, 0x4101, 0x32C0, 0x2482, 0x3AE4, 0x4309, 0x2CA4, 0x34CA, 0x3CED, 0x1642, 0x1E64, 
    0x2688, 0x2EAE, 0x36D2, 0x3EF5, 0x40FF, 0x30B4, 0x38D8, 0x2892, 0x4307, 0x3AE2, 0x206E, 0x32BC, 0x450D, 0x2A9A, 0x3CEB, 0x34C4, 0x3EF1, 
    0x184A, 0x2274, 0x2CA0, 0x36CC, 0x40F9, 0x38D4, 0x4301, 0x2EA8, 0x247C, 0x3ADC, 0x4509, 0x30B2, 0x3CE4, 0x1A50, 0x2686, 0x32B8, 0x3EED, 
    0x40F5, 0x288E, 0x34C2, 0x42FF, 0x36CA, 0x4505, 0x1C58, 0x2A94, 0x38D0, 0x470F, 0x3ADA, 0x2C9C, 0x3CE2, 0x1E62, 0x2EA6, 0x3EE9, 0x40F3, 
    0x30AE, 0x42F9, 0x206A, 0x32B4, 0x4501, 0x34BE, 0x4709, 0x2270, 0x36C4, 0x38CC, 0x247A, 0x3AD4, 0x3CDC, 0x2682, 0x3EE4, 0x40ED, 0x2888, 
    0x42F5, 0x2A92, 0x44FD, 0x4707, 0x2C98, 0x490F, 0x2EA2, 0x30A8, 0x32B0, 0x34B8, 0x36C2, 0x38C8, 0x3AD2, 0x3CDA, 0x3EE0, 0x40EB, 0x42F3, 
    0x44F9, 0x4701, 0x4909, 0x1024, 0x122E, 0x1434, 0x163E, 0x1844, 0x1A4C, 0x1C56, 0x1E5E, 0x2064, 0x226C, 0x2476, 0x267C, 0x2886, 0x2A8E, 
    0x2C94, 0x2E9C, 0x30A6, 0x32AC, 0x34B4, 0x36BE, 0x38C4, 0x3ACC, 0x3CD4, 0x3EDC, 0x40E5, 0x42ED, 0x44F5, 0x46FF, 0x4907, 0x4B0D, 0x46F9, 
    0x4901, 0x4B09, 0x40E2, 0x42EB, 0x44F1, 0x3CD2, 0x3ED8, 0x38C0, 0x3ACA, 0x36B8, 0x34B2, 0x32A8, 0x30A2, 0x2E9A, 0x4D0F, 0x2C90, 0x48FF, 
    0x4B05, 0x2A88, 0x46F5, 0x2882, 0x42E5, 0x44ED, 0x40DC, 0x267A, 0x3ED4, 0x3CCC, 0x2470, 0x3AC4, 0x38BC, 0x4D09, 0x2268, 0x36B4, 0x4B01, 
    0x34AE, 0x48F9, 0x46F3, 0x2062, 0x32A4, 0x44E9, 0x42E3, 0x309C, 0x40DA, 0x1E58, 0x2E94, 0x3ED0, 0x4F0D, 0x4D07, 0x3CCA, 0x2C8C, 0x3AC2, 
    0x4AFD, 0x48F5, 0x1C52, 0x2A86, 0x38B8, 0x46ED, 0x44E5, 0x36B2, 0x287C, 0x42DC, 0x4F09, 0x34A8, 0x40D4, 0x4D01, 0x1A48, 0x2676, 0x32A0, 
    0x3ECC, 0x4AF9, 0x48F3, 0x3CC4, 0x309A, 0x46EB, 0x246E, 0x3ABE, 0x510F, 0x44E1, 0x2E92, 0x4F05, 0x38B4, 0x42DA, 0x4CFF, 0x1842, 0x2264, 
    0x2C88, 0x36AE, 0x40D2, 0x4AF5, 0x48ED, 0x34A6, 0x3EC8, 0x2A82, 0x46E5, 0x5109, 0x3CC2, 0x4F01, 0x205E, 0x329C, 0x44DC, 0x4CF9, 0x3AB8, 
    0x287A, 0x42D4, 0x3094, 0x4AF1, 0x530F, 0x38B0, 0x40CC, 0x48EB, 0x5107, 0x163A, 0x1E56, 0x2670, 0x2E8E, 0x36A8, 0x3EC4, 0x46E3, 0x4EFD, 
    0x44D8, 0x4CF5, 0x3CBE, 0x34A2, 0x5309, 0x2C84, 0x4AED, 0x42D2, 0x246A, 0x3AB4, 0x5101, 0x48E5, 0x3298, 0x40CA, 0x4EF9, 0x1C4E, 0x2A7C, 
    0x38AC, 0x46DD, 0x550D, 0x3EC0, 0x4CF3, 0x3092, 0x5307, 0x44D4, 0x2260, 0x36A6, 0x4AE9, 0x50FF, 0x3CB8, 0x2876, 0x42CC, 0x48E3, 0x2E88, 
    0x4EF5, 0x5509, 0x349C, 0x3AB2, 0x40C4, 0x46DA, 0x4CED, 0x5301, 0x1432, 0x1A44, 0x2058, 0x266E, 0x2C80, 0x3294, 0x38A8, 0x3EBC, 0x44D0, 
    0x4AE5, 0x50F9, 0x570F, 0x4EF1, 0x5505, 0x42CA, 0x48DD, 0x3CB4, 0x36A2, 0x308E, 0x4CEB, 0x52FF, 0x2A7A, 0x46D4, 0x40C2, 0x5709, 0x2464, 
    0x3AAE, 0x50F5, 0x4AE1, 0x349A, 0x44CC, 0x5501, 0x1E52, 0x2E86, 0x3EB8, 0x4EED, 0x590F, 0x38A4, 0x48DA, 0x52F9, 0x2870, 0x42C4, 0x4CE5, 
    0x3290, 0x5707, 0x3CB2, 0x46D2, 0x50F3, 0x183E, 0x225C, 0x2C7C, 0x369C, 0x40BE, 0x4ADD, 0x54FD, 0x5909, 0x44C8, 0x4EE9, 0x3AA8, 0x3088, 
    0x52F5, 0x48D4, 0x266A, 0x3EB4, 0x5701, 0x4CE3, 0x3494, 0x42C2, 0x5B0D, 0x50ED, 0x1C4A, 0x2A76, 0x38A0, 0x46CC, 0x54F9, 0x5907, 0x3CAE, 
    0x4AD9, 0x2E82, 0x4EE5, 0x40B8, 0x52F3, 0x2056, 0x328C, 0x44C4, 0x56FF, 0x48D2, 0x5B09, 0x369A, 0x4CDD, 0x2462, 0x3AA6, 0x50EB, 0x3EB0, 
    0x54F5, 0x5901, 0x286E, 0x42BE, 0x5D0D, 0x46CA, 0x2C78, 0x4AD4, 0x4EE1, 0x3086, 0x52ED, 0x56F9, 0x3492, 0x5B05, 0x389C, 0x3CA8, 0x40B4, 
    0x44C0, 0x48CC, 0x4CDB, 0x50E5, 0x54F1, 0x58FF, 0x5D09, 0x122A, 0x1634, 0x1A40, 0x1E4E, 0x2258, 0x2664, 0x2A70, 0x2E7C, 0x3288, 0x3694, 
    0x3AA2, 0x3EAC, 0x42B8, 0x46C4, 0x4AD0, 0x4EDD, 0x52EB, 0x56F5, 0x5B01, 0x5F0F, 0x54ED, 0x58F9, 0x5D05, 0x4CD5, 0x50E3, 0x44BC, 0x48CA, 
    0x40B2, 0x3CA6, 0x3898, 0x5F09, 0x348E, 0x5AFD, 0x3082, 0x52E5, 0x56F3, 0x4ED9, 0x2C74, 0x4ACC, 0x46C2, 0x610F, 0x286A, 0x42B4, 0x5D01, 
    0x3EA8, 0x58F5, 0x54E9, 0x245E, 0x3A9C, 0x50DD, 0x4CD2, 0x3692, 0x5F07, 0x48C4, 0x5AF9, 0x2052, 0x3284, 0x44B8, 0x56ED, 0x40AE, 0x52E3, 
    0x2E7A, 0x4ED5, 0x6109, 0x5CFD, 0x3CA2, 0x4AC8, 0x58F3, 0x1C44, 0x2A6E, 0x3894, 0x46BE, 0x54E5, 0x630D, 0x50DB, 0x5F01, 0x42B2, 0x3488, 
    0x4CCC, 0x5AF5, 0x2662, 0x3EA4, 0x56EB, 0x48C2, 0x6107, 0x307C, 0x52DD, 0x5CF9, 0x3A9A, 0x44B4, 0x4ED1, 0x58ED, 0x6309, 0x183A, 0x2254, 
    0x2C70, 0x368E, 0x40A8, 0x4AC4, 0x54E1, 0x5EFF, 0x5AF1, 0x650F, 0x46B8, 0x50D5, 0x3C9C, 0x3280, 0x56E5, 0x6101, 0x4CCA, 0x2864, 0x42AE, 
    0x5CF5, 0x52DB, 0x3890, 0x48BE, 0x6305, 0x58EB, 0x1E4A, 0x2E76, 0x3EA0, 0x4ECC, 0x5EF9, 0x6509, 0x44B0, 0x54DD, 0x3486, 0x5AED, 0x4AC0, 
    0x60FF, 0x2458, 0x3A94, 0x50D3, 0x670D, 0x56E3, 0x40A6, 0x5CF1, 0x2A6A, 0x46B4, 0x6301, 0x4CC4, 0x307A, 0x52D5, 0x58E5, 0x3688, 0x5EF5, 
    0x6507, 0x3C9A, 0x42A8, 0x48B8, 0x4EC8, 0x54D9, 0x5AE9, 0x60F9, 0x6709, 0x142E, 0x1A3C, 0x204E, 0x265E, 0x2C6C, 0x327C, 0x388C, 0x3E9C, 
    0x44AC, 0x4ABC, 0x50CC, 0x56DD, 0x5CED, 0x62FD, 0x690F, 0x6501, 0x58E3, 0x5EF3, 0x4CC2, 0x52D3, 0x46B2, 0x40A2, 0x3A92, 0x60F5, 0x6705, 
    0x3482, 0x5AE5, 0x54D5, 0x2E70, 0x4EC4, 0x48B4, 0x6909, 0x62F9, 0x2862, 0x42A6, 0x5CE9, 0x56DB, 0x3C94, 0x6B0D, 0x50CA, 0x64FF, 0x2250, 
    0x3686, 0x4AB8, 0x5EED, 0x58DD, 0x44A8, 0x6701, 0x3076, 0x52CD, 0x60F3, 0x3E98, 0x4CBE, 0x5AE1, 0x6907, 0x1C42, 0x2A64, 0x3888, 0x46AE, 
    0x54D1, 0x62F5, 0x6B09, 0x4EC0, 0x5CE5, 0x409C, 0x3278, 0x56D5, 0x64F9, 0x6D0F, 0x48B2, 0x5EEB, 0x2456, 0x3A8E, 0x50C4, 0x66FD, 0x58DB, 
    0x42A2, 0x60ED, 0x2C68, 0x4AB4, 0x6901, 0x52CA, 0x347C, 0x5ADD, 0x62F1, 0x3C92, 0x6B05, 0x44A4, 0x4CB8, 0x54CD, 0x5CE1, 0x64F5, 0x6D09, 
    0x1632, 0x1E44, 0x2658, 0x2E6E, 0x3682, 0x3E94, 0x46A8, 0x4EBC, 0x56D3, 0x5EE5, 0x66F9, 0x6F0D, 0x60EB, 0x68FF, 0x50C2, 0x58D5, 0x48AE, 
    0x409A, 0x6B01, 0x3884, 0x62ED, 0x5AD9, 0x3070, 0x52C4, 0x4AB0, 0x6D07, 0x64F3, 0x285E, 0x429C, 0x5CDD, 0x54C9, 0x6F09, 0x3A88, 0x66F5, 
    0x4CB4, 0x5EE3, 0x710F, 0x204A, 0x3274, 0x44A0, 0x56CD, 0x68F9, 0x4EB8, 0x60E5, 0x3C8E, 0x6AFD, 0x58D3, 0x2A62, 0x46A6, 0x62E9, 0x6D01, 
    0x50BE, 0x347A, 0x5AD5, 0x3E90, 0x64ED, 0x6F05, 0x48A8, 0x52C2, 0x5CD9, 0x66F1, 0x7109, 0x1834, 0x224C, 0x2C64, 0x367C, 0x4094, 0x4AAC, 
    0x54C4, 0x5EDD, 0x68F5, 0x730D, 0x6AF9, 0x56CB, 0x60E3, 0x4CB2, 0x429A, 0x6CFF, 0x3880, 0x62E5, 0x58CD, 0x2E6A, 0x4EB4, 0x6F01, 0x64EB, 
    0x449C, 0x5AD1, 0x7107, 0x2452, 0x3A86, 0x50B8, 0x66ED, 0x5CD5, 0x7309, 0x46A2, 0x68F3, 0x306E, 0x52BE, 0x750F, 0x5EDB, 0x3C88, 0x6AF5, 
    0x48A6, 0x54C0, 0x60DD, 0x6CF9, 0x1A38, 0x2656, 0x3270, 0x3E8C, 0x4AA8, 0x56C5, 0x62E1, 0x6EFD, 0x7101, 0x58CB, 0x64E5, 0x4CAE, 0x4092, 
    0x66E9, 0x7305, 0x3476, 0x5ACD, 0x7509, 0x4EB0, 0x68ED, 0x2858, 0x4294, 0x5CD1, 0x770D, 0x50B4, 0x6AF1, 0x367A, 0x5ED5, 0x6CF5, 0x4498, 
    0x52B8, 0x60DB, 0x6EF9, 0x1C3E, 0x2A5E, 0x387C, 0x469C, 0x54BC, 0x62DD, 0x70FF, 0x7301, 0x56C2, 0x64E3, 0x48A2, 0x7507, 0x3A82, 0x66E5, 
    0x58C5, 0x7709, 0x2C60, 0x4AA4, 0x68EB, 0x5AC9, 0x790F, 0x3C86, 0x6AED, 0x4CA8, 0x5CCD, 0x6CF3, 0x1E42, 0x2E64, 0x3E88, 0x4EAC, 0x5ED3, 
    0x6EF5, 0x70F9, 0x50B2, 0x60D5, 0x408E, 0x72FD, 0x62D9, 0x306A, 0x52B4, 0x7501, 0x64DD, 0x4292, 0x7705, 0x54B8, 0x66E1, 0x7909, 0x2044, 
    0x326C, 0x4494, 0x56BE, 0x68E5, 0x7B0D, 0x58C3, 0x6AE9, 0x469A, 0x3470, 0x5AC5, 0x6CED, 0x6EF1, 0x489C, 0x5CC9, 0x70F5, 0x2248, 0x3676, 
    0x4AA0, 0x5ECD, 0x72F9, 0x60D3, 0x74FF, 0x4CA6, 0x7701, 0x3878, 0x62D5, 0x4EA8, 0x7907, 0x64DB, 0x7B09, 0x244E, 0x3A7C, 0x50AE, 0x66DD, 
    0x7D0D, 0x68E3, 0x52B2, 0x3C82, 0x6AE5, 0x54B4, 0x6CEB, 0x2652, 0x3E84, 0x56B8, 0x6EED, 0x58BE, 0x70F3, 0x4088, 0x72F5, 0x5AC1, 0x74F9, 
    0x2856, 0x428E, 0x5CC5, 0x76FD, 0x7901, 0x4490, 0x5ECB, 0x7B05, 0x60CD, 0x7D09, 0x2A58, 0x4694, 0x62D1, 0x7F0F, 0x64D5, 0x489A, 0x66D9, 
    0x2C5C, 0x4A9C, 0x68DD, 0x6AE1, 0x4CA2, 0x6CE5, 0x2E62, 0x4EA4, 0x6EE9, 0x50A8, 0x70ED, 0x72F1, 0x3064, 0x52AE, 0x74F5, 0x76F9, 0x54B0, 
    0x78FF, 0x3268, 0x56B4, 0x7B01, 0x58B8, 0x7D05, 0x7F09, 0x346E, 0x5ABD, 0x810D, 0x5CC1, 0x3670, 0x5EC5, 0x60CB, 0x3874, 0x62CD, 0x64D3, 
    0x3A7A, 0x66D5, 0x68DB, 0x3C7C, 0x6ADD, 0x6CE3, 0x3E80, 0x6EE5, 0x70EB, 0x4086, 0x72ED, 0x74F3, 0x4288, 0x76F5, 0x448C, 0x78F9, 0x7AFD, 
    0x7D01, 0x4692, 0x7F07, 0x8109, 0x4894, 0x830F, 0x4A98, 0x4C9C, 0x4EA0, 0x50A6, 0x52A8, 0x54AC, 0x56B2, 0x58B4, 0x5AB8, 0x5CBD, 0x5EC3, 
    0x60C5, 0x62C9, 0x64CD, 0x66D1, 0x68D5, 0x6AD9, 0x6CDD, 0x6EE1, 0x70E5, 0x72E9, 0x74ED, 0x76F1, 0x78F5, 0x7AF9, 0x7CFD, 0x7F01, 0x8105, 
    0x8309, 0x850D, 
};


// converts the values in the lookup table to x and y analog values, and two flags.
static void unpack_analog(uint16_t analog, int16_t* x, int16_t* y, uint16_t* is_accessible_vc, uint16_t* is_fullspeed){
	*x = -(int16_t)((analog & 0xFE00) >> 9);
	*y =  (int16_t)((analog & 0x01FC) >> 2);
	*is_accessible_vc = ((analog & 0x0002) >> 1);
	*is_fullspeed = (analog & 0x0001);
}

static uint16_t lookup(uint16_t* found_angle, uint16_t angle, uint16_t fullspeed){
    uint16_t is_accessible_vc;
    uint16_t is_fullspeed;
    uint16_t lower_val;
    uint16_t lower_idx;
    uint16_t upper_val;
    uint16_t upper_idx;
    uint16_t i;

	if (angle < angle_tbl[0]/2){
        *found_angle = 0x0;
		return 0x010F; // encoded result for cardinal up (0,67)
	}
	else if (angle <= angle_tbl[0]){
        *found_angle = angle_tbl[0];
		return analog_tbl[0];
    }

	lower_val = angle_tbl[0];
	lower_idx = 0;

	// Finding the best candidate:
	for (i = 1; i < sizeof(angle_tbl)/sizeof(angle_tbl[0]); i++){
        is_accessible_vc = (analog_tbl[i] & 0x0002 >> 1);
        is_fullspeed = (analog_tbl[i] & 0x0001);

		if (settings->bits.wiivc_cam && !is_accessible_vc){}
        else if (fullspeed && !is_fullspeed){}
        else{
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
	return 0x870F; // encoded result for diagonal (67,67)
}

static void find_best_analog(int16_t* x, int16_t* y, uint16_t* found_angle, uint16_t full_angle, uint16_t fullspeed){
	int16_t x_temp;
	int16_t y_temp;
	uint16_t is_accessible_vc;
	uint16_t is_fullspeed;
    uint16_t angle;
    uint16_t analog;
	uint16_t lookup_angle;
	
    angle = full_angle - z64_camera_angle;
	if (angle < 0x2000)
	{
		lookup_angle = angle;
		analog = lookup(found_angle, lookup_angle, fullspeed);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc, &is_fullspeed);
		
        *found_angle = *found_angle;
		*x = x_temp;
		*y = y_temp;		
	}
	else if (angle < 0x4000)
	{
		lookup_angle = 0x4000 - angle;
		analog = lookup(found_angle, lookup_angle, fullspeed);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc, &is_fullspeed);
		
        *found_angle = 0x4000 - *found_angle;
		*x = -y_temp;
		*y = -x_temp;	
	}
	else if (angle < 0x6000)
	{
		lookup_angle = angle - 0x4000;
		analog = lookup(found_angle, lookup_angle, fullspeed);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc, &is_fullspeed);
		
        *found_angle = *found_angle + 0x4000;
		*x = -y_temp;
		*y = x_temp;	
	}
	else if (angle < 0x8000)
	{
		lookup_angle = 0x8000 - angle;
		analog = lookup(found_angle, lookup_angle, fullspeed);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc, &is_fullspeed);
		
        *found_angle = 0x8000 - *found_angle;
		*x = x_temp;
		*y = -y_temp;	
	}
	else if (angle < 0xA000)
	{
		lookup_angle = angle - 0x8000;
		analog = lookup(found_angle, lookup_angle, fullspeed);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc, &is_fullspeed);
		
        *found_angle = *found_angle + 0x8000;
		*x = -x_temp;
		*y = -y_temp;	
	}
	else if (angle < 0xC000)
	{
		lookup_angle = 0xC000 - angle;
		analog = lookup(found_angle, lookup_angle, fullspeed);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc, &is_fullspeed);
		
        *found_angle = 0xC000 - *found_angle;
		*x = y_temp;
		*y = x_temp;	
	}
	else if (angle < 0xE000)
	{
		lookup_angle = angle - 0xC000;
		analog = lookup(found_angle, lookup_angle, fullspeed);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc, &is_fullspeed);
		
        *found_angle = *found_angle + 0xC000;
		*x = y_temp;
		*y = -x_temp;	
	}
	else
	{
		lookup_angle = -angle;
		analog = lookup(found_angle, lookup_angle, fullspeed);
		unpack_analog(analog, &x_temp, &y_temp, &is_accessible_vc, &is_fullspeed);
		
        *found_angle = -*found_angle;
		*x = -x_temp;
		*y = y_temp;	
	}
    *found_angle = *found_angle + z64_camera_angle;
}

void gz_angle_finder(){
    if (gz.angle_enable)
        find_best_analog(&gz.angle_x, &gz.angle_y, &gz.angle_best_matching, gz.angle_desired, gz.angle_full_speed);
}