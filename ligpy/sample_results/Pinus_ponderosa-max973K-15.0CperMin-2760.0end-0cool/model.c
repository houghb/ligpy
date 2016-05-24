#include <parest.h>

/* universal gas constant */
const double Renergy = 8.314;
const double Rgas = 8.314e1; /* cm^3*bar/mol*K */
double Temperature, T0, coeffa, coeffb, coeffc, coeffd;
extern InputStructure *gInputPtr;

/* names for species */
   enum {PLIGC, PLIGH, PLIGO, PRLIGH, LIGH, C3H6, OH, RLIGM2A, LIGM2,
      RPHENOXM2, RADIOM2, PLIGM2, PRADIOM2, LIG, RPHENOX, RADIO, PLIG, PRADIO,
      PADIOM2, PADIO, PKETM2, PRKETM2, KETDM2, CO, C10H2M4, H2, C10H2, RLIGH,
      ALD3, PRLIGH2, PRLIGM2A, RMGUAI, C3H6O2, KETM2, RLIGM2B, PFET3M2,
      PRFET3M2, C3H4O2, RPHENOL, RLIGA, KET, RLIGB, PFET3, PRFET3, SYNAPYL,
      RKETM2, COUMARYL, RKET, KETD, RC3H7O2, RCH3O, CH3CHO, C10H2M2, CH2CO,
      CO2, ADIOM2, PH2, PCOH, RC3H5O2, RC3H3O, PCOS, ADIO, RCH3, PCH3, ETOH,
      H2O, PCH2OH, PCHP2, PCHOHP, CHAR, PCOHP2, PC2H2, PCHO, CH3OH, C2H6,
      PCH2P, VADIOM2, VKETM2, VKETDM2, VSYNAPYL, MGUAI, VMGUAI, VCOUMARYL,
      VADIO, VKET, VKETD, PHENOL, VPHENOL, LIGC, LIGO, C3H8O2, CH4, C3H4O};

int netRates(double *rate, double *netRate)
{
   netRate[0] = 1.0 * rate[0] - 0.0;
   netRate[1] = 1.0 * rate[1] - 0.0;
   netRate[2] = 1.0 * rate[2] - 0.0;
   netRate[3] = 1.0 * rate[3] - 0.0;
   netRate[4] = 1.0 * rate[4] - 0.0;
   netRate[5] = 1.0 * rate[5] - 0.0;
   netRate[6] = 1.0 * rate[6] - 0.0;
   netRate[7] = 1.0 * rate[7] - 0.0;
   netRate[8] = 1.0 * rate[8] - 0.0;
   netRate[9] = 1.0 * rate[9] - 0.0;
   netRate[10] = 1.0 * rate[10] - 0.0;
   netRate[11] = 1.0 * rate[11] - 0.0;
   netRate[12] = 1.0 * rate[12] - 0.0;
   netRate[13] = 1.0 * rate[13] - 0.0;
   netRate[14] = 1.0 * rate[14] - 0.0;
   netRate[15] = 1.0 * rate[15] - 0.0;
   netRate[16] = 1.0 * rate[16] - 0.0;
   netRate[17] = 1.0 * rate[17] - 0.0;
   netRate[18] = 1.0 * rate[18] - 0.0;
   netRate[19] = 1.0 * rate[19] - 0.0;
   netRate[20] = 1.0 * rate[20] - 0.0;
   netRate[21] = 1.0 * rate[21] - 0.0;
   netRate[22] = 1.0 * rate[22] - 0.0;
   netRate[23] = 1.0 * rate[23] - 0.0;
   netRate[24] = 1.0 * rate[24] - 0.0;
   netRate[25] = 1.0 * rate[25] - 0.0;
   netRate[26] = 1.0 * rate[26] - 0.0;
   netRate[27] = 1.0 * rate[27] - 0.0;
   netRate[28] = 1.0 * rate[28] - 0.0;
   netRate[29] = 1.0 * rate[29] - 0.0;
   netRate[30] = 1.0 * rate[30] - 0.0;
   netRate[31] = 1.0 * rate[31] - 0.0;
   netRate[32] = 1.0 * rate[32] - 0.0;
   netRate[33] = 1.0 * rate[33] - 0.0;
   netRate[34] = 1.0 * rate[34] - 0.0;
   netRate[35] = 1.0 * rate[35] - 0.0;
   netRate[36] = 1.0 * rate[36] - 0.0;
   netRate[37] = 1.0 * rate[37] - 0.0;
   netRate[38] = 1.0 * rate[38] - 0.0;
   netRate[39] = 1.0 * rate[39] - 0.0;
   netRate[40] = 1.0 * rate[40] - 0.0;
   netRate[41] = 1.0 * rate[41] - 0.0;
   netRate[42] = 1.0 * rate[42] - 0.0;
   netRate[43] = 1.0 * rate[43] - 0.0;
   netRate[44] = 1.0 * rate[44] - 0.0;
   netRate[45] = 1.0 * rate[45] - 0.0;
   netRate[46] = 1.0 * rate[46] - 0.0;
   netRate[47] = 1.0 * rate[47] - 0.0;
   netRate[48] = 1.0 * rate[48] - 0.0;
   netRate[49] = 1.0 * rate[49] - 0.0;
   netRate[50] = 1.0 * rate[50] - 0.0;
   netRate[51] = 1.0 * rate[51] - 0.0;
   netRate[52] = 1.0 * rate[52] - 0.0;
   netRate[53] = 1.0 * rate[53] - 0.0;
   netRate[54] = 1.0 * rate[54] - 0.0;
   netRate[55] = 1.0 * rate[55] - 0.0;
   netRate[56] = 1.0 * rate[56] - 0.0;
   netRate[57] = 1.0 * rate[57] - 0.0;
   netRate[58] = 1.0 * rate[58] - 0.0;
   netRate[59] = 1.0 * rate[59] - 0.0;
   netRate[60] = 1.0 * rate[60] - 0.0;
   netRate[61] = 1.0 * rate[61] - 0.0;
   netRate[62] = 1.0 * rate[62] - 0.0;
   netRate[63] = 1.0 * rate[63] - 0.0;
   netRate[64] = 1.0 * rate[64] - 0.0;
   netRate[65] = 1.0 * rate[65] - 0.0;
   netRate[66] = 1.0 * rate[66] - 0.0;
   netRate[67] = 1.0 * rate[67] - 0.0;
   netRate[68] = 1.0 * rate[68] - 0.0;
   netRate[69] = 1.0 * rate[69] - 0.0;
   netRate[70] = 1.0 * rate[70] - 0.0;
   netRate[71] = 1.0 * rate[71] - 0.0;
   netRate[72] = 1.0 * rate[72] - 0.0;
   netRate[73] = 1.0 * rate[73] - 0.0;
   netRate[74] = 1.0 * rate[74] - 0.0;
   netRate[75] = 1.0 * rate[75] - 0.0;
   netRate[76] = 1.0 * rate[76] - 0.0;
   netRate[77] = 1.0 * rate[77] - 0.0;
   netRate[78] = 1.0 * rate[78] - 0.0;
   netRate[79] = 1.0 * rate[79] - 0.0;
   netRate[80] = 1.0 * rate[80] - 0.0;
   netRate[81] = 1.0 * rate[81] - 0.0;
   netRate[82] = 1.0 * rate[82] - 0.0;
   netRate[83] = 1.0 * rate[83] - 0.0;
   netRate[84] = 1.0 * rate[84] - 0.0;
   netRate[85] = 1.0 * rate[85] - 0.0;
   netRate[86] = 1.0 * rate[86] - 0.0;
   netRate[87] = 1.0 * rate[87] - 0.0;
   netRate[88] = 1.0 * rate[88] - 0.0;
   netRate[89] = 1.0 * rate[89] - 0.0;
   netRate[90] = 1.0 * rate[90] - 0.0;
   netRate[91] = 1.0 * rate[91] - 0.0;
   netRate[92] = 1.0 * rate[92] - 0.0;
   netRate[93] = 1.0 * rate[93] - 0.0;
   netRate[94] = 1.0 * rate[94] - 0.0;
   netRate[95] = 1.0 * rate[95] - 0.0;
   netRate[96] = 1.0 * rate[96] - 0.0;
   netRate[97] = 1.0 * rate[97] - 0.0;
   netRate[98] = 1.0 * rate[98] - 0.0;
   netRate[99] = 1.0 * rate[99] - 0.0;
   netRate[100] = 1.0 * rate[100] - 0.0;
   netRate[101] = 1.0 * rate[101] - 0.0;
   netRate[102] = 1.0 * rate[102] - 0.0;
   netRate[103] = 1.0 * rate[103] - 0.0;
   netRate[104] = 1.0 * rate[104] - 0.0;
   netRate[105] = 1.0 * rate[105] - 0.0;
   netRate[106] = 1.0 * rate[106] - 0.0;
   netRate[107] = 1.0 * rate[107] - 0.0;
   netRate[108] = 1.0 * rate[108] - 0.0;
   netRate[109] = 1.0 * rate[109] - 0.0;
   netRate[110] = 1.0 * rate[110] - 0.0;
   netRate[111] = 1.0 * rate[111] - 0.0;
   netRate[112] = 1.0 * rate[112] - 0.0;
   netRate[113] = 1.0 * rate[113] - 0.0;
   netRate[114] = 1.0 * rate[114] - 0.0;
   netRate[115] = 1.0 * rate[115] - 0.0;
   netRate[116] = 1.0 * rate[116] - 0.0;
   netRate[117] = 1.0 * rate[117] - 0.0;
   netRate[118] = 1.0 * rate[118] - 0.0;
   netRate[119] = 1.0 * rate[119] - 0.0;
   netRate[120] = 1.0 * rate[120] - 0.0;
   netRate[121] = 1.0 * rate[121] - 0.0;
   netRate[122] = 1.0 * rate[122] - 0.0;
   netRate[123] = 1.0 * rate[123] - 0.0;
   netRate[124] = 1.0 * rate[124] - 0.0;
   netRate[125] = 1.0 * rate[125] - 0.0;
   netRate[126] = 1.0 * rate[126] - 0.0;
   netRate[127] = 1.0 * rate[127] - 0.0;
   netRate[128] = 1.0 * rate[128] - 0.0;
   netRate[129] = 1.0 * rate[129] - 0.0;
   netRate[130] = 1.0 * rate[130] - 0.0;
   netRate[131] = 1.0 * rate[131] - 0.0;
   netRate[132] = 1.0 * rate[132] - 0.0;
   netRate[133] = 1.0 * rate[133] - 0.0;
   netRate[134] = 1.0 * rate[134] - 0.0;
   netRate[135] = 1.0 * rate[135] - 0.0;
   netRate[136] = 1.0 * rate[136] - 0.0;
   netRate[137] = 1.0 * rate[137] - 0.0;
   netRate[138] = 1.0 * rate[138] - 0.0;
   netRate[139] = 1.0 * rate[139] - 0.0;
   netRate[140] = 1.0 * rate[140] - 0.0;
   netRate[141] = 1.0 * rate[141] - 0.0;
   netRate[142] = 1.0 * rate[142] - 0.0;
   netRate[143] = 1.0 * rate[143] - 0.0;
   netRate[144] = 1.0 * rate[144] - 0.0;
   netRate[145] = 1.0 * rate[145] - 0.0;
   netRate[146] = 1.0 * rate[146] - 0.0;
   netRate[147] = 1.0 * rate[147] - 0.0;
   netRate[148] = 1.0 * rate[148] - 0.0;
   netRate[149] = 1.0 * rate[149] - 0.0;
   netRate[150] = 1.0 * rate[150] - 0.0;
   netRate[151] = 1.0 * rate[151] - 0.0;
   netRate[152] = 1.0 * rate[152] - 0.0;
   netRate[153] = 1.0 * rate[153] - 0.0;
   netRate[154] = 1.0 * rate[154] - 0.0;
   netRate[155] = 1.0 * rate[155] - 0.0;
   netRate[156] = 1.0 * rate[156] - 0.0;
   netRate[157] = 1.0 * rate[157] - 0.0;
   netRate[158] = 1.0 * rate[158] - 0.0;
   netRate[159] = 1.0 * rate[159] - 0.0;
   netRate[160] = 1.0 * rate[160] - 0.0;
   netRate[161] = 1.0 * rate[161] - 0.0;
   netRate[162] = 1.0 * rate[162] - 0.0;
   netRate[163] = 1.0 * rate[163] - 0.0;
   netRate[164] = 1.0 * rate[164] - 0.0;
   netRate[165] = 1.0 * rate[165] - 0.0;
   netRate[166] = 1.0 * rate[166] - 0.0;
   netRate[167] = 1.0 * rate[167] - 0.0;
   netRate[168] = 1.0 * rate[168] - 0.0;
   netRate[169] = 1.0 * rate[169] - 0.0;
   netRate[170] = 1.0 * rate[170] - 0.0;
   netRate[171] = 1.0 * rate[171] - 0.0;
   netRate[172] = 1.0 * rate[172] - 0.0;
   netRate[173] = 1.0 * rate[173] - 0.0;
   netRate[174] = 1.0 * rate[174] - 0.0;
   netRate[175] = 1.0 * rate[175] - 0.0;
   netRate[176] = 1.0 * rate[176] - 1.0 * rate[350];
   netRate[177] = 1.0 * rate[177] - 0.0;
   netRate[178] = 1.0 * rate[178] - 1.0 * rate[245];
   netRate[179] = 1.0 * rate[179] - 1.0 * rate[224];
   netRate[180] = 1.0 * rate[180] - 0.0;
   netRate[181] = 1.0 * rate[181] - 1.0 * rate[203];
   netRate[182] = 1.0 * rate[182] - 1.0 * rate[182];
   netRate[183] = 1.0 * rate[183] - 0.0;
   netRate[184] = 1.0 * rate[184] - 0.0;
   netRate[185] = 1.0 * rate[185] - 1.0 * rate[392];
   netRate[186] = 1.0 * rate[186] - 0.0;
   netRate[187] = 1.0 * rate[187] - 0.0;
   netRate[188] = 1.0 * rate[188] - 1.0 * rate[329];
   netRate[189] = 1.0 * rate[189] - 1.0 * rate[308];
   netRate[190] = 1.0 * rate[190] - 0.0;
   netRate[191] = 1.0 * rate[191] - 0.0;
   netRate[192] = 1.0 * rate[192] - 0.0;
   netRate[193] = 1.0 * rate[193] - 0.0;
   netRate[194] = 1.0 * rate[194] - 0.0;
   netRate[195] = 1.0 * rate[195] - 1.0 * rate[371];
   netRate[196] = 1.0 * rate[196] - 0.0;
   netRate[197] = 1.0 * rate[197] - 1.0 * rate[349];
   netRate[198] = 1.0 * rate[198] - 0.0;
   netRate[199] = 1.0 * rate[199] - 1.0 * rate[244];
   netRate[200] = 1.0 * rate[200] - 1.0 * rate[223];
   netRate[201] = 1.0 * rate[201] - 0.0;
   netRate[202] = 1.0 * rate[202] - 1.0 * rate[202];
   netRate[203] = 1.0 * rate[204] - 0.0;
   netRate[204] = 1.0 * rate[205] - 0.0;
   netRate[205] = 1.0 * rate[206] - 1.0 * rate[391];
   netRate[206] = 1.0 * rate[207] - 0.0;
   netRate[207] = 1.0 * rate[208] - 0.0;
   netRate[208] = 1.0 * rate[209] - 1.0 * rate[328];
   netRate[209] = 1.0 * rate[210] - 1.0 * rate[307];
   netRate[210] = 1.0 * rate[211] - 0.0;
   netRate[211] = 1.0 * rate[212] - 0.0;
   netRate[212] = 1.0 * rate[213] - 0.0;
   netRate[213] = 1.0 * rate[214] - 0.0;
   netRate[214] = 1.0 * rate[215] - 0.0;
   netRate[215] = 1.0 * rate[216] - 1.0 * rate[370];
   netRate[216] = 1.0 * rate[217] - 0.0;
   netRate[217] = 1.0 * rate[218] - 1.0 * rate[347];
   netRate[218] = 1.0 * rate[219] - 0.0;
   netRate[219] = 1.0 * rate[220] - 1.0 * rate[242];
   netRate[220] = 1.0 * rate[221] - 1.0 * rate[221];
   netRate[221] = 1.0 * rate[222] - 0.0;
   netRate[222] = 1.0 * rate[225] - 0.0;
   netRate[223] = 1.0 * rate[226] - 0.0;
   netRate[224] = 1.0 * rate[227] - 1.0 * rate[389];
   netRate[225] = 1.0 * rate[228] - 0.0;
   netRate[226] = 1.0 * rate[229] - 0.0;
   netRate[227] = 1.0 * rate[230] - 1.0 * rate[326];
   netRate[228] = 1.0 * rate[231] - 1.0 * rate[305];
   netRate[229] = 1.0 * rate[232] - 0.0;
   netRate[230] = 1.0 * rate[233] - 0.0;
   netRate[231] = 1.0 * rate[234] - 0.0;
   netRate[232] = 1.0 * rate[235] - 0.0;
   netRate[233] = 1.0 * rate[236] - 0.0;
   netRate[234] = 1.0 * rate[237] - 1.0 * rate[368];
   netRate[235] = 1.0 * rate[238] - 0.0;
   netRate[236] = 1.0 * rate[239] - 1.0 * rate[346];
   netRate[237] = 1.0 * rate[240] - 0.0;
   netRate[238] = 1.0 * rate[241] - 1.0 * rate[241];
   netRate[239] = 1.0 * rate[243] - 0.0;
   netRate[240] = 1.0 * rate[246] - 0.0;
   netRate[241] = 1.0 * rate[247] - 0.0;
   netRate[242] = 1.0 * rate[248] - 1.0 * rate[388];
   netRate[243] = 1.0 * rate[249] - 0.0;
   netRate[244] = 1.0 * rate[250] - 0.0;
   netRate[245] = 1.0 * rate[251] - 1.0 * rate[325];
   netRate[246] = 1.0 * rate[252] - 1.0 * rate[304];
   netRate[247] = 1.0 * rate[253] - 0.0;
   netRate[248] = 1.0 * rate[254] - 0.0;
   netRate[249] = 1.0 * rate[255] - 0.0;
   netRate[250] = 1.0 * rate[256] - 0.0;
   netRate[251] = 1.0 * rate[257] - 0.0;
   netRate[252] = 1.0 * rate[258] - 1.0 * rate[367];
   netRate[253] = 1.0 * rate[259] - 0.0;
   netRate[254] = 1.0 * rate[260] - 0.0;
   netRate[255] = 1.0 * rate[261] - 0.0;
   netRate[256] = 1.0 * rate[262] - 0.0;
   netRate[257] = 1.0 * rate[263] - 0.0;
   netRate[258] = 1.0 * rate[264] - 0.0;
   netRate[259] = 1.0 * rate[265] - 0.0;
   netRate[260] = 1.0 * rate[266] - 0.0;
   netRate[261] = 1.0 * rate[267] - 0.0;
   netRate[262] = 1.0 * rate[268] - 0.0;
   netRate[263] = 1.0 * rate[269] - 0.0;
   netRate[264] = 1.0 * rate[270] - 0.0;
   netRate[265] = 1.0 * rate[271] - 0.0;
   netRate[266] = 1.0 * rate[272] - 0.0;
   netRate[267] = 1.0 * rate[273] - 0.0;
   netRate[268] = 1.0 * rate[274] - 0.0;
   netRate[269] = 1.0 * rate[275] - 0.0;
   netRate[270] = 1.0 * rate[276] - 0.0;
   netRate[271] = 1.0 * rate[277] - 0.0;
   netRate[272] = 1.0 * rate[278] - 0.0;
   netRate[273] = 1.0 * rate[279] - 0.0;
   netRate[274] = 1.0 * rate[280] - 0.0;
   netRate[275] = 1.0 * rate[281] - 0.0;
   netRate[276] = 1.0 * rate[282] - 0.0;
   netRate[277] = 1.0 * rate[283] - 0.0;
   netRate[278] = 1.0 * rate[284] - 0.0;
   netRate[279] = 1.0 * rate[285] - 0.0;
   netRate[280] = 1.0 * rate[286] - 0.0;
   netRate[281] = 1.0 * rate[287] - 0.0;
   netRate[282] = 1.0 * rate[288] - 0.0;
   netRate[283] = 1.0 * rate[289] - 0.0;
   netRate[284] = 1.0 * rate[290] - 0.0;
   netRate[285] = 1.0 * rate[291] - 0.0;
   netRate[286] = 1.0 * rate[292] - 0.0;
   netRate[287] = 1.0 * rate[293] - 0.0;
   netRate[288] = 1.0 * rate[294] - 0.0;
   netRate[289] = 1.0 * rate[295] - 0.0;
   netRate[290] = 1.0 * rate[296] - 0.0;
   netRate[291] = 1.0 * rate[297] - 0.0;
   netRate[292] = 1.0 * rate[298] - 0.0;
   netRate[293] = 1.0 * rate[299] - 0.0;
   netRate[294] = 1.0 * rate[300] - 0.0;
   netRate[295] = 1.0 * rate[301] - 0.0;
   netRate[296] = 1.0 * rate[302] - 1.0 * rate[357];
   netRate[297] = 1.0 * rate[303] - 0.0;
   netRate[298] = 1.0 * rate[306] - 0.0;
   netRate[299] = 1.0 * rate[309] - 0.0;
   netRate[300] = 1.0 * rate[310] - 0.0;
   netRate[301] = 1.0 * rate[311] - 1.0 * rate[399];
   netRate[302] = 1.0 * rate[312] - 0.0;
   netRate[303] = 1.0 * rate[313] - 0.0;
   netRate[304] = 1.0 * rate[314] - 1.0 * rate[336];
   netRate[305] = 1.0 * rate[315] - 1.0 * rate[315];
   netRate[306] = 1.0 * rate[316] - 0.0;
   netRate[307] = 1.0 * rate[317] - 0.0;
   netRate[308] = 1.0 * rate[318] - 0.0;
   netRate[309] = 1.0 * rate[319] - 0.0;
   netRate[310] = 1.0 * rate[320] - 0.0;
   netRate[311] = 1.0 * rate[321] - 1.0 * rate[378];
   netRate[312] = 1.0 * rate[322] - 0.0;
   netRate[313] = 1.0 * rate[323] - 1.0 * rate[356];
   netRate[314] = 1.0 * rate[324] - 0.0;
   netRate[315] = 1.0 * rate[327] - 0.0;
   netRate[316] = 1.0 * rate[330] - 0.0;
   netRate[317] = 1.0 * rate[331] - 0.0;
   netRate[318] = 1.0 * rate[332] - 1.0 * rate[398];
   netRate[319] = 1.0 * rate[333] - 0.0;
   netRate[320] = 1.0 * rate[334] - 0.0;
   netRate[321] = 1.0 * rate[335] - 1.0 * rate[335];
   netRate[322] = 1.0 * rate[337] - 0.0;
   netRate[323] = 1.0 * rate[338] - 0.0;
   netRate[324] = 1.0 * rate[339] - 0.0;
   netRate[325] = 1.0 * rate[340] - 0.0;
   netRate[326] = 1.0 * rate[341] - 0.0;
   netRate[327] = 1.0 * rate[342] - 1.0 * rate[377];
   netRate[328] = 1.0 * rate[343] - 0.0;
   netRate[329] = 1.0 * rate[344] - 1.0 * rate[344];
   netRate[330] = 1.0 * rate[345] - 0.0;
   netRate[331] = 1.0 * rate[348] - 0.0;
   netRate[332] = 1.0 * rate[351] - 0.0;
   netRate[333] = 1.0 * rate[352] - 0.0;
   netRate[334] = 1.0 * rate[353] - 1.0 * rate[386];
   netRate[335] = 1.0 * rate[354] - 0.0;
   netRate[336] = 1.0 * rate[355] - 0.0;
   netRate[337] = 1.0 * rate[358] - 0.0;
   netRate[338] = 1.0 * rate[359] - 0.0;
   netRate[339] = 1.0 * rate[360] - 0.0;
   netRate[340] = 1.0 * rate[361] - 0.0;
   netRate[341] = 1.0 * rate[362] - 0.0;
   netRate[342] = 1.0 * rate[363] - 1.0 * rate[365];
   netRate[343] = 1.0 * rate[364] - 0.0;
   netRate[344] = 1.0 * rate[366] - 0.0;
   netRate[345] = 1.0 * rate[369] - 0.0;
   netRate[346] = 1.0 * rate[372] - 0.0;
   netRate[347] = 1.0 * rate[373] - 0.0;
   netRate[348] = 1.0 * rate[374] - 1.0 * rate[405];
   netRate[349] = 1.0 * rate[375] - 0.0;
   netRate[350] = 1.0 * rate[376] - 0.0;
   netRate[351] = 1.0 * rate[379] - 0.0;
   netRate[352] = 1.0 * rate[380] - 0.0;
   netRate[353] = 1.0 * rate[381] - 0.0;
   netRate[354] = 1.0 * rate[382] - 0.0;
   netRate[355] = 1.0 * rate[383] - 0.0;
   netRate[356] = 1.0 * rate[384] - 1.0 * rate[384];
   netRate[357] = 1.0 * rate[385] - 0.0;
   netRate[358] = 1.0 * rate[387] - 0.0;
   netRate[359] = 1.0 * rate[390] - 0.0;
   netRate[360] = 1.0 * rate[393] - 0.0;
   netRate[361] = 1.0 * rate[394] - 0.0;
   netRate[362] = 1.0 * rate[395] - 1.0 * rate[395];
   netRate[363] = 1.0 * rate[396] - 0.0;
   netRate[364] = 1.0 * rate[397] - 0.0;
   netRate[365] = 1.0 * rate[400] - 0.0;
   netRate[366] = 1.0 * rate[401] - 0.0;
   netRate[367] = 1.0 * rate[402] - 0.0;
   netRate[368] = 1.0 * rate[403] - 0.0;
   netRate[369] = 1.0 * rate[404] - 0.0;

   return 0;
}

int Rates(double *y, double *rate, double *k, int *ipar, InputStructure *Input)
{
   double Tref;

   Tref = k[ipar[0]];

   rate[0] = k_jim(1e+13, 163254, 0) * y[PLIGH];
   rate[1] = k_jim(1e+13, 163254, 0) * y[LIGH];
   rate[2] = k_jim(1e+13, 163254, 0) * y[LIGM2];
   rate[3] = k_jim(1e+13, 163254, 0) * y[PLIGM2];
   rate[4] = k_jim(1e+13, 184184, 0) * y[LIG];
   rate[5] = k_jim(1e+13, 188370, 0) * y[PLIG];
   rate[6] = k_jim(1e+13, 171626, 0) * y[PADIOM2];
   rate[7] = k_jim(1e+13, 179998, 0) * y[PADIO];
   rate[8] = k_jim(1e+13, 167440, 0) * y[PKETM2];
   rate[9] = k_jim(1e+13, 121394, 0) * y[PRKETM2];
   rate[10] = k_jim(40000000000.0, 209300, 0) * y[RPHENOXM2];
   rate[11] = k_jim(40000000000.0, 209300, 0) * y[RPHENOX];
   rate[12] = k_jim(1e+13, 133952, 0) * y[RLIGH];
   rate[13] = k_jim(1e+13, 133952, 0) * y[PRLIGH2];
   rate[14] = k_jim(1e+13, 133952, 0) * y[RADIOM2];
   rate[15] = k_jim(5e+12, 133952, 0) * y[RLIGM2A];
   rate[16] = k_jim(5e+12, 133952, 0) * y[PRLIGM2A];
   rate[17] = k_jim(1e+13, 163254, 0) * y[RLIGM2B];
   rate[18] = k_jim(1e+13, 133952, 0) * y[PRFET3M2];
   rate[19] = k_jim(1e+13, 163254, 0) * y[RADIO];
   rate[20] = k_jim(1e+13, 138138, 0) * y[RLIGA];
   rate[21] = k_jim(1e+13, 163254, 0) * y[RLIGB];
   rate[22] = k_jim(1e+13, 138138, 0) * y[PRFET3];
   rate[23] = k_jim(3e+11, 104650, 0) * y[RADIOM2];
   rate[24] = k_jim(3e+11, 104650, 0) * y[RKETM2];
   rate[25] = k_jim(3e+11, 104650, 0) * y[RADIO];
   rate[26] = k_jim(3e+11, 113022, 0) * y[RKET];
   rate[27] = k_jim(1e+13, 129766, 0) * y[RC3H7O2];
   rate[28] = k_jim(1e+13, 196742, 0) * y[C10H2M4];
   rate[29] = k_jim(1e+13, 196742, 0) * y[C10H2M2];
   rate[30] = k_jim(100000000.0, 121394, 0) * y[PLIGC];
   rate[31] = k_jim(1000000000.0, 108836, 0) * y[PLIGO];
   rate[32] = k_jim(1000000000.0, 121394, 0) * y[ADIOM2] * y[RPHENOXM2];
   rate[33] = k_jim(1000000000.0, 121394, 0) * y[KETM2] * y[RPHENOXM2];
   rate[34] = k_jim(1000000000.0, 121394, 0) * y[RPHENOXM2] * y[KETDM2];
   rate[35] = k_jim(1000000000.0, 121394, 0) * y[SYNAPYL] * y[RPHENOXM2];
   rate[36] = k_jim(1000000000.0, 121394, 0) * y[ADIOM2] * y[RPHENOX];
   rate[37] = k_jim(1000000000.0, 121394, 0) * y[KETM2] * y[RPHENOX];
   rate[38] = k_jim(1000000000.0, 121394, 0) * y[RPHENOX] * y[KETDM2];
   rate[39] = k_jim(1000000000.0, 121394, 0) * y[SYNAPYL] * y[RPHENOX];
   rate[40] = k_jim(1000000000.0, 121394, 0) * y[ADIO] * y[RPHENOX];
   rate[41] = k_jim(1000000000.0, 121394, 0) * y[KET] * y[RPHENOX];
   rate[42] = k_jim(1000000000.0, 121394, 0) * y[KETD] * y[RPHENOX];
   rate[43] = k_jim(1000000000.0, 121394, 0) * y[COUMARYL] * y[RPHENOX];
   rate[44] = k_jim(1000000000.0, 121394, 0) * y[ADIO] * y[RPHENOXM2];
   rate[45] = k_jim(1000000000.0, 121394, 0) * y[KET] * y[RPHENOXM2];
   rate[46] = k_jim(1000000000.0, 121394, 0) * y[KETD] * y[RPHENOXM2];
   rate[47] = k_jim(1000000000.0, 121394, 0) * y[COUMARYL] * y[RPHENOXM2];
   rate[48] = k_jim(1000000000.0, 115115, 0) * y[C10H2M4] * y[RPHENOXM2];
   rate[49] = k_jim(1000000000.0, 115115, 0) * y[C10H2M2] * y[RPHENOXM2];
   rate[50] = k_jim(1000000000.0, 117208, 0) * y[C10H2M4] * y[RPHENOX];
   rate[51] = k_jim(1000000000.0, 117208, 0) * y[C10H2M2] * y[RPHENOX];
   rate[52] = k_jim(100000000.0, 54418, 0) * y[RCH3O] * y[RPHENOX];
   rate[53] = k_jim(100000000.0, 54418, 0) * y[RCH3O] * y[RPHENOXM2];
   rate[54] = k_jim(100000000.0, 48139, 0) * y[RCH3] * y[RPHENOXM2];
   rate[55] = k_jim(100000000.0, 48139, 0) * y[RCH3] * y[RPHENOX];
   rate[56] = k_jim(100000000.0, 12558, 0) * y[RCH3] * y[RCH3O];
   rate[57] = k_jim(100000000.0, 12558, 0) * y[RCH3O] * y[RCH3O];
   rate[58] = k_jim(100000000.0, 52325, 0) * y[PRADIOM2] * y[RCH3O];
   rate[59] = k_jim(100000000.0, 52325, 0) * y[PRKETM2] * y[RCH3O];
   rate[60] = k_jim(31600000.0, 83720, 0) * y[RADIOM2] * y[RADIOM2];
   rate[61] = k_jim(31600000.0, 83720, 0) * y[RLIGM2B] * y[RLIGM2B];
   rate[62] = k_jim(31600000.0, 83720, 0) * y[RLIGM2A] * y[RLIGM2A];
   rate[63] = k_jim(31600000.0, 83720, 0) * y[RMGUAI] * y[RMGUAI];
   rate[64] = k_jim(31600000.0, 83720, 0) * y[RKETM2] * y[RKETM2];
   rate[65] = k_jim(31600000.0, 83720, 0) * y[PRFET3M2] * y[PRFET3M2];
   rate[66] = k_jim(100000000.0, 12558, 0) * y[RC3H7O2] * y[RC3H7O2];
   rate[67] = k_jim(100000000.0, 12558, 0) * y[RC3H5O2] * y[RC3H5O2];
   rate[68] = k_jim(100000000.0, 12558, 0) * y[RC3H3O] * y[RC3H3O];
   rate[69] = k_jim(100000000.0, 12558, 0) * y[RCH3] * y[OH];
   rate[70] = k_jim(100000000.0, 12558, 0) * y[RCH3] * y[RCH3];
   rate[71] = k_jim(100000000.0, 48139, 0) * y[PRADIOM2] * y[RCH3];
   rate[72] = k_jim(100000000.0, 48139, 0) * y[PRKETM2] * y[RCH3];
   rate[73] = k_jim(31600000.0, 83720, 0) * y[RLIGB] * y[RPHENOX];
   rate[74] = k_jim(31600000.0, 92092, 0) * y[RADIO] * y[RADIO];
   rate[75] = k_jim(31600000.0, 83720, 0) * y[RLIGB] * y[RLIGB];
   rate[76] = k_jim(31600000.0, 83720, 0) * y[RLIGA] * y[RLIGA];
   rate[77] = k_jim(31600000.0, 83720, 0) * y[RKET] * y[RKET];
   rate[78] = k_jim(31600000.0, 83720, 0) * y[PRFET3] * y[PRFET3];
   rate[79] = k_jim(31600000.0, 83720, 0) * y[RLIGH] * y[RLIGH];
   rate[80] = k_jim(50000000.0, 83720, 0) * y[RPHENOX] * y[RPHENOL];
   rate[81] = k_jim(100000000.0, 48139, 0) * y[RC3H3O] * y[RPHENOX];
   rate[82] = k_jim(30000000.0, 104650, 0) * y[CHAR] * y[RPHENOX];
   rate[83] = k_jim(30000000.0, 104650, 0) * y[CHAR] * y[RPHENOXM2];
   rate[84] = k_jim(1, 62790, 1) * y[ADIOM2];
   rate[85] = k_jim(1, 62790, 1) * y[KETM2];
   rate[86] = k_jim(1, 58604, 1) * y[KETDM2];
   rate[87] = k_jim(1, 62790, 1) * y[SYNAPYL];
   rate[88] = k_jim(1, 66976, 1) * y[MGUAI];
   rate[89] = k_jim(1, 83720, 1) * y[COUMARYL];
   rate[90] = k_jim(1, 66976, 1) * y[ADIO];
   rate[91] = k_jim(1, 66976, 1) * y[KET];
   rate[92] = k_jim(1, 83720, 1) * y[KETD];
   rate[93] = k_jim(1, 58604, 1) * y[PHENOL];
   rate[94] = k_jim(200000000.0, 209300, 0) * y[PCOS];
   rate[95] = k_jim(10000000.0, 138138, 0) * y[PCOH];
   rate[96] = k_jim(10000000000.0, 209300, 0) * y[PH2];
   rate[97] = k_jim(500000000.0, 205114, 0) * y[PC2H2];
   rate[98] = k_jim(500000000.0, 0, 0) * y[PCH2OH];
   rate[99] = k_jim(500000000.0, 0, 0) * y[PCHOHP];
   rate[100] = k_jim(500000000.0, 0, 0) * y[PCOHP2];
   rate[101] = k_jim(1e+13, 125580, 0) * y[PCH3];
   rate[102] = k_jim(500000000.0, 209300, 0) * y[PCH2P];
   rate[103] = k_jim(500000000.0, 209300, 0) * y[PCHP2];
   rate[104] = k_jim(1e+13, 154812, 0) * y[PLIGH];
   rate[105] = k_jim(1e+13, 168458, 0) * y[PLIGC];
   rate[106] = k_jim(1e+13, 154812, 0) * y[PLIGO];
   rate[107] = k_jim(1000000000.0, 108836, 0) * y[LIGO];
   rate[108] = k_jim(100000000.0, 121394, 0) * y[LIGC];
   rate[109] = k_jim(31600000.0, 92092, 0) * y[PRADIO] * y[PRADIO];
   rate[110] = k_jim(31600000.0, 83720, 0) * y[PRADIOM2] * y[PRADIOM2];
   rate[111] = k_jim(10000000.0, 138138, 0) * y[PCHO];
   rate[112] = k_jim(200000000, 66976, 0) * y[LIGH] * y[RC3H5O2];
   rate[113] = k_jim(200000000, 50232, 0) * y[LIGH] * y[PRFET3];
   rate[114] = k_jim(200000000, 58604, 0) * y[RC3H7O2] * y[LIGH];
   rate[115] = k_jim(200000000, 50232, 0) * y[LIGH] * y[RADIOM2];
   rate[116] = k_jim(200000000, 50232, 0) * y[PRFET3M2] * y[LIGH];
   rate[117] = k_jim(632455532.034, 37674, 0) * y[PRLIGH] * y[LIGH];
   rate[118] = k_jim(200000000, 50232, 0) * y[RLIGM2B] * y[LIGH];
   rate[119] = k_jim(200000000, 50232, 0) * y[RLIGM2A] * y[LIGH];
   rate[120] = k_jim(632455532.034, 43953, 0) * y[RCH3] * y[LIGH];
   rate[121] = k_jim(200000000, 50232, 0) * y[PRKETM2] * y[LIGH];
   rate[122] = k_jim(632455532.034, 50232, 0) * y[LIGH] * y[RKET];
   rate[123] = k_jim(200000000, 41860, 0) * y[LIGH] * y[PRADIO];
   rate[124] = k_jim(200000000, 79534, 0) * y[RC3H3O] * y[LIGH];
   rate[125] = k_jim(200000000, 52325, 0) * y[RLIGB] * y[LIGH];
   rate[126] = k_jim(200000000, 52325, 0) * y[LIGH] * y[RLIGA];
   rate[127] = k_jim(632455532.034, 37674, 0) * y[PRADIOM2] * y[LIGH];
   rate[128] = k_jim(200000000, 50232, 0) * y[RMGUAI] * y[LIGH];
   rate[129] = k_jim(6324555320.34, 10465, 0) * y[LIGH] * y[OH];
   rate[130] = k_jim(632455532.034, 28883, 0) * y[RCH3O] * y[LIGH];
   rate[131] = k_jim(632455532.034, 50232, 0) * y[LIGH] * y[RPHENOL];
   rate[132] = k_jim(200000000, 50232, 0) * y[RADIO] * y[LIGH];
   rate[133] = k_jim(200000000, 66976, 0) * y[PLIGH] * y[RC3H5O2];
   rate[134] = k_jim(200000000, 50232, 0) * y[PLIGH] * y[PRFET3];
   rate[135] = k_jim(200000000, 58604, 0) * y[RC3H7O2] * y[PLIGH];
   rate[136] = k_jim(200000000, 50232, 0) * y[PLIGH] * y[RADIOM2];
   rate[137] = k_jim(200000000, 50232, 0) * y[PLIGH] * y[PRFET3M2];
   rate[138] = k_jim(632455532.034, 37674, 0) * y[PLIGH] * y[PRLIGH];
   rate[139] = k_jim(200000000, 50232, 0) * y[RLIGM2B] * y[PLIGH];
   rate[140] = k_jim(200000000, 50232, 0) * y[RLIGM2A] * y[PLIGH];
   rate[141] = k_jim(632455532.034, 43953, 0) * y[PLIGH] * y[RCH3];
   rate[142] = k_jim(200000000, 50232, 0) * y[PRKETM2] * y[PLIGH];
   rate[143] = k_jim(632455532.034, 50232, 0) * y[PLIGH] * y[RKET];
   rate[144] = k_jim(200000000, 41860, 0) * y[PLIGH] * y[PRADIO];
   rate[145] = k_jim(200000000, 79534, 0) * y[RC3H3O] * y[PLIGH];
   rate[146] = k_jim(200000000, 52325, 0) * y[PLIGH] * y[RLIGB];
   rate[147] = k_jim(200000000, 52325, 0) * y[PLIGH] * y[RLIGA];
   rate[148] = k_jim(632455532.034, 37674, 0) * y[PRADIOM2] * y[PLIGH];
   rate[149] = k_jim(200000000, 50232, 0) * y[RMGUAI] * y[PLIGH];
   rate[150] = k_jim(6324555320.34, 10465, 0) * y[PLIGH] * y[OH];
   rate[151] = k_jim(632455532.034, 28883, 0) * y[PLIGH] * y[RCH3O];
   rate[152] = k_jim(632455532.034, 50232, 0) * y[PLIGH] * y[RPHENOL];
   rate[153] = k_jim(200000000, 50232, 0) * y[RADIO] * y[PLIGH];
   rate[154] = k_jim(200000000, 66976, 0) * y[PLIGM2] * y[RC3H5O2];
   rate[155] = k_jim(200000000, 50232, 0) * y[PLIGM2] * y[PRFET3];
   rate[156] = k_jim(200000000, 58604, 0) * y[PLIGM2] * y[RC3H7O2];
   rate[157] = k_jim(200000000, 50232, 0) * y[PLIGM2] * y[RADIOM2];
   rate[158] = k_jim(200000000, 50232, 0) * y[PLIGM2] * y[PRFET3M2];
   rate[159] = k_jim(632455532.034, 37674, 0) * y[PLIGM2] * y[PRLIGH];
   rate[160] = k_jim(200000000, 50232, 0) * y[RLIGM2B] * y[PLIGM2];
   rate[161] = k_jim(200000000, 50232, 0) * y[PLIGM2] * y[RLIGM2A];
   rate[162] = k_jim(632455532.034, 43953, 0) * y[PLIGM2] * y[RCH3];
   rate[163] = k_jim(200000000, 50232, 0) * y[PLIGM2] * y[PRKETM2];
   rate[164] = k_jim(632455532.034, 50232, 0) * y[PLIGM2] * y[RKET];
   rate[165] = k_jim(200000000, 41860, 0) * y[PLIGM2] * y[PRADIO];
   rate[166] = k_jim(200000000, 79534, 0) * y[PLIGM2] * y[RC3H3O];
   rate[167] = k_jim(200000000, 52325, 0) * y[PLIGM2] * y[RLIGB];
   rate[168] = k_jim(200000000, 52325, 0) * y[PLIGM2] * y[RLIGA];
   rate[169] = k_jim(632455532.034, 37674, 0) * y[PLIGM2] * y[PRADIOM2];
   rate[170] = k_jim(200000000, 50232, 0) * y[PLIGM2] * y[RMGUAI];
   rate[171] = k_jim(6324555320.34, 10465, 0) * y[PLIGM2] * y[OH];
   rate[172] = k_jim(632455532.034, 28883, 0) * y[PLIGM2] * y[RCH3O];
   rate[173] = k_jim(632455532.034, 50232, 0) * y[PLIGM2] * y[RPHENOL];
   rate[174] = k_jim(200000000, 50232, 0) * y[RADIO] * y[PLIGM2];
   rate[175] = k_jim(100000000, 66976, 0) * y[RC3H5O2] * y[LIGM2];
   rate[176] = k_jim(100000000, 50232, 0) * y[PRFET3] * y[LIGM2];
   rate[177] = k_jim(100000000, 58604, 0) * y[RC3H7O2] * y[LIGM2];
   rate[178] = k_jim(100000000, 50232, 0) * y[LIGM2] * y[RADIOM2];
   rate[179] = k_jim(100000000, 50232, 0) * y[PRFET3M2] * y[LIGM2];
   rate[180] = k_jim(316227766.017, 37674, 0) * y[PRLIGH] * y[LIGM2];
   rate[181] = k_jim(100000000, 50232, 0) * y[RLIGM2B] * y[LIGM2];
   rate[182] = k_jim(100000000, 50232, 0) * y[RLIGM2A] * y[LIGM2];
   rate[183] = k_jim(316227766.017, 43953, 0) * y[RCH3] * y[LIGM2];
   rate[184] = k_jim(100000000, 50232, 0) * y[PRKETM2] * y[LIGM2];
   rate[185] = k_jim(316227766.017, 50232, 0) * y[RKET] * y[LIGM2];
   rate[186] = k_jim(100000000, 41860, 0) * y[PRADIO] * y[LIGM2];
   rate[187] = k_jim(100000000, 79534, 0) * y[RC3H3O] * y[LIGM2];
   rate[188] = k_jim(100000000, 52325, 0) * y[RLIGB] * y[LIGM2];
   rate[189] = k_jim(100000000, 52325, 0) * y[RLIGA] * y[LIGM2];
   rate[190] = k_jim(316227766.017, 37674, 0) * y[PRADIOM2] * y[LIGM2];
   rate[191] = k_jim(100000000, 50232, 0) * y[RMGUAI] * y[LIGM2];
   rate[192] = k_jim(3162277660.17, 10465, 0) * y[LIGM2] * y[OH];
   rate[193] = k_jim(316227766.017, 28883, 0) * y[RCH3O] * y[LIGM2];
   rate[194] = k_jim(316227766.017, 50232, 0) * y[LIGM2] * y[RPHENOL];
   rate[195] = k_jim(100000000, 50232, 0) * y[RADIO] * y[LIGM2];
   rate[196] = k_jim(100000000, 66976, 0) * y[RC3H5O2] * y[LIGM2];
   rate[197] = k_jim(100000000, 50232, 0) * y[PRFET3] * y[LIGM2];
   rate[198] = k_jim(100000000, 58604, 0) * y[RC3H7O2] * y[LIGM2];
   rate[199] = k_jim(100000000, 50232, 0) * y[LIGM2] * y[RADIOM2];
   rate[200] = k_jim(100000000, 50232, 0) * y[PRFET3M2] * y[LIGM2];
   rate[201] = k_jim(316227766.017, 37674, 0) * y[PRLIGH] * y[LIGM2];
   rate[202] = k_jim(100000000, 50232, 0) * y[RLIGM2B] * y[LIGM2];
   rate[203] = k_jim(100000000, 50232, 0) * y[RLIGM2A] * y[LIGM2];
   rate[204] = k_jim(316227766.017, 43953, 0) * y[RCH3] * y[LIGM2];
   rate[205] = k_jim(100000000, 50232, 0) * y[PRKETM2] * y[LIGM2];
   rate[206] = k_jim(316227766.017, 50232, 0) * y[RKET] * y[LIGM2];
   rate[207] = k_jim(100000000, 41860, 0) * y[PRADIO] * y[LIGM2];
   rate[208] = k_jim(100000000, 79534, 0) * y[RC3H3O] * y[LIGM2];
   rate[209] = k_jim(100000000, 52325, 0) * y[RLIGB] * y[LIGM2];
   rate[210] = k_jim(100000000, 52325, 0) * y[RLIGA] * y[LIGM2];
   rate[211] = k_jim(316227766.017, 37674, 0) * y[PRADIOM2] * y[LIGM2];
   rate[212] = k_jim(100000000, 50232, 0) * y[RMGUAI] * y[LIGM2];
   rate[213] = k_jim(3162277660.17, 10465, 0) * y[LIGM2] * y[OH];
   rate[214] = k_jim(316227766.017, 28883, 0) * y[RCH3O] * y[LIGM2];
   rate[215] = k_jim(316227766.017, 50232, 0) * y[LIGM2] * y[RPHENOL];
   rate[216] = k_jim(100000000, 50232, 0) * y[RADIO] * y[LIGM2];
   rate[217] = k_jim(200000000, 66976, 0) * y[RC3H5O2] * y[PFET3M2];
   rate[218] = k_jim(200000000, 50232, 0) * y[PRFET3] * y[PFET3M2];
   rate[219] = k_jim(200000000, 58604, 0) * y[RC3H7O2] * y[PFET3M2];
   rate[220] = k_jim(200000000, 50232, 0) * y[PFET3M2] * y[RADIOM2];
   rate[221] = k_jim(200000000, 50232, 0) * y[PRFET3M2] * y[PFET3M2];
   rate[222] = k_jim(632455532.034, 37674, 0) * y[PRLIGH] * y[PFET3M2];
   rate[223] = k_jim(200000000, 50232, 0) * y[RLIGM2B] * y[PFET3M2];
   rate[224] = k_jim(200000000, 50232, 0) * y[RLIGM2A] * y[PFET3M2];
   rate[225] = k_jim(632455532.034, 43953, 0) * y[RCH3] * y[PFET3M2];
   rate[226] = k_jim(200000000, 50232, 0) * y[PRKETM2] * y[PFET3M2];
   rate[227] = k_jim(632455532.034, 50232, 0) * y[RKET] * y[PFET3M2];
   rate[228] = k_jim(200000000, 41860, 0) * y[PRADIO] * y[PFET3M2];
   rate[229] = k_jim(200000000, 79534, 0) * y[RC3H3O] * y[PFET3M2];
   rate[230] = k_jim(200000000, 52325, 0) * y[RLIGB] * y[PFET3M2];
   rate[231] = k_jim(200000000, 52325, 0) * y[RLIGA] * y[PFET3M2];
   rate[232] = k_jim(632455532.034, 37674, 0) * y[PRADIOM2] * y[PFET3M2];
   rate[233] = k_jim(200000000, 50232, 0) * y[RMGUAI] * y[PFET3M2];
   rate[234] = k_jim(6324555320.34, 10465, 0) * y[OH] * y[PFET3M2];
   rate[235] = k_jim(632455532.034, 28883, 0) * y[RCH3O] * y[PFET3M2];
   rate[236] = k_jim(632455532.034, 50232, 0) * y[PFET3M2] * y[RPHENOL];
   rate[237] = k_jim(200000000, 50232, 0) * y[RADIO] * y[PFET3M2];
   rate[238] = k_jim(100000000, 66976, 0) * y[RC3H5O2] * y[ADIOM2];
   rate[239] = k_jim(100000000, 50232, 0) * y[PRFET3] * y[ADIOM2];
   rate[240] = k_jim(100000000, 58604, 0) * y[RC3H7O2] * y[ADIOM2];
   rate[241] = k_jim(100000000, 50232, 0) * y[ADIOM2] * y[RADIOM2];
   rate[242] = k_jim(100000000, 50232, 0) * y[PRFET3M2] * y[ADIOM2];
   rate[243] = k_jim(316227766.017, 37674, 0) * y[PRLIGH] * y[ADIOM2];
   rate[244] = k_jim(100000000, 50232, 0) * y[RLIGM2B] * y[ADIOM2];
   rate[245] = k_jim(100000000, 50232, 0) * y[RLIGM2A] * y[ADIOM2];
   rate[246] = k_jim(316227766.017, 43953, 0) * y[RCH3] * y[ADIOM2];
   rate[247] = k_jim(100000000, 50232, 0) * y[PRKETM2] * y[ADIOM2];
   rate[248] = k_jim(316227766.017, 50232, 0) * y[RKET] * y[ADIOM2];
   rate[249] = k_jim(100000000, 41860, 0) * y[PRADIO] * y[ADIOM2];
   rate[250] = k_jim(100000000, 79534, 0) * y[RC3H3O] * y[ADIOM2];
   rate[251] = k_jim(100000000, 52325, 0) * y[RLIGB] * y[ADIOM2];
   rate[252] = k_jim(100000000, 52325, 0) * y[RLIGA] * y[ADIOM2];
   rate[253] = k_jim(316227766.017, 37674, 0) * y[PRADIOM2] * y[ADIOM2];
   rate[254] = k_jim(100000000, 50232, 0) * y[RMGUAI] * y[ADIOM2];
   rate[255] = k_jim(3162277660.17, 10465, 0) * y[OH] * y[ADIOM2];
   rate[256] = k_jim(316227766.017, 28883, 0) * y[RCH3O] * y[ADIOM2];
   rate[257] = k_jim(316227766.017, 50232, 0) * y[ADIOM2] * y[RPHENOL];
   rate[258] = k_jim(100000000, 50232, 0) * y[RADIO] * y[ADIOM2];
   rate[259] = k_jim(100000000, 66976, 0) * y[KETM2] * y[RC3H5O2];
   rate[260] = k_jim(100000000, 50232, 0) * y[KETM2] * y[PRFET3];
   rate[261] = k_jim(100000000, 58604, 0) * y[KETM2] * y[RC3H7O2];
   rate[262] = k_jim(100000000, 50232, 0) * y[KETM2] * y[RADIOM2];
   rate[263] = k_jim(100000000, 50232, 0) * y[KETM2] * y[PRFET3M2];
   rate[264] = k_jim(316227766.017, 37674, 0) * y[KETM2] * y[PRLIGH];
   rate[265] = k_jim(100000000, 50232, 0) * y[RLIGM2B] * y[KETM2];
   rate[266] = k_jim(100000000, 50232, 0) * y[KETM2] * y[RLIGM2A];
   rate[267] = k_jim(316227766.017, 43953, 0) * y[KETM2] * y[RCH3];
   rate[268] = k_jim(100000000, 50232, 0) * y[KETM2] * y[PRKETM2];
   rate[269] = k_jim(316227766.017, 50232, 0) * y[KETM2] * y[RKET];
   rate[270] = k_jim(100000000, 41860, 0) * y[KETM2] * y[PRADIO];
   rate[271] = k_jim(100000000, 79534, 0) * y[KETM2] * y[RC3H3O];
   rate[272] = k_jim(100000000, 52325, 0) * y[KETM2] * y[RLIGB];
   rate[273] = k_jim(100000000, 52325, 0) * y[KETM2] * y[RLIGA];
   rate[274] = k_jim(316227766.017, 37674, 0) * y[KETM2] * y[PRADIOM2];
   rate[275] = k_jim(100000000, 50232, 0) * y[KETM2] * y[RMGUAI];
   rate[276] = k_jim(3162277660.17, 10465, 0) * y[KETM2] * y[OH];
   rate[277] = k_jim(316227766.017, 28883, 0) * y[KETM2] * y[RCH3O];
   rate[278] = k_jim(316227766.017, 50232, 0) * y[KETM2] * y[RPHENOL];
   rate[279] = k_jim(100000000, 50232, 0) * y[RADIO] * y[KETM2];
   rate[280] = k_jim(100000000, 92092, 0) * y[C10H2] * y[RC3H5O2];
   rate[281] = k_jim(100000000, 75348, 0) * y[C10H2] * y[PRFET3];
   rate[282] = k_jim(100000000, 83720, 0) * y[RC3H7O2] * y[C10H2];
   rate[283] = k_jim(100000000, 75348, 0) * y[C10H2] * y[RADIOM2];
   rate[284] = k_jim(100000000, 75348, 0) * y[PRFET3M2] * y[C10H2];
   rate[285] = k_jim(316227766.017, 62790, 0) * y[PRLIGH] * y[C10H2];
   rate[286] = k_jim(100000000, 75348, 0) * y[RLIGM2B] * y[C10H2];
   rate[287] = k_jim(100000000, 75348, 0) * y[RLIGM2A] * y[C10H2];
   rate[288] = k_jim(316227766.017, 69069, 0) * y[RCH3] * y[C10H2];
   rate[289] = k_jim(100000000, 75348, 0) * y[PRKETM2] * y[C10H2];
   rate[290] = k_jim(316227766.017, 75348, 0) * y[RKET] * y[C10H2];
   rate[291] = k_jim(100000000, 66976, 0) * y[C10H2] * y[PRADIO];
   rate[292] = k_jim(100000000, 104650, 0) * y[RC3H3O] * y[C10H2];
   rate[293] = k_jim(100000000, 77441, 0) * y[RLIGB] * y[C10H2];
   rate[294] = k_jim(100000000, 77441, 0) * y[RLIGA] * y[C10H2];
   rate[295] = k_jim(316227766.017, 62790, 0) * y[PRADIOM2] * y[C10H2];
   rate[296] = k_jim(100000000, 75348, 0) * y[RMGUAI] * y[C10H2];
   rate[297] = k_jim(3162277660.17, 35581, 0) * y[C10H2] * y[OH];
   rate[298] = k_jim(316227766.017, 53999, 0) * y[RCH3O] * y[C10H2];
   rate[299] = k_jim(316227766.017, 75348, 0) * y[C10H2] * y[RPHENOL];
   rate[300] = k_jim(100000000, 75348, 0) * y[RADIO] * y[C10H2];
   rate[301] = k_jim(100000000, 66976, 0) * y[LIG] * y[RC3H5O2];
   rate[302] = k_jim(100000000, 50232, 0) * y[LIG] * y[PRFET3];
   rate[303] = k_jim(100000000, 58604, 0) * y[LIG] * y[RC3H7O2];
   rate[304] = k_jim(100000000, 50232, 0) * y[LIG] * y[RADIOM2];
   rate[305] = k_jim(100000000, 50232, 0) * y[LIG] * y[PRFET3M2];
   rate[306] = k_jim(316227766.017, 37674, 0) * y[LIG] * y[PRLIGH];
   rate[307] = k_jim(100000000, 50232, 0) * y[RLIGM2B] * y[LIG];
   rate[308] = k_jim(100000000, 50232, 0) * y[LIG] * y[RLIGM2A];
   rate[309] = k_jim(316227766.017, 43953, 0) * y[LIG] * y[RCH3];
   rate[310] = k_jim(100000000, 50232, 0) * y[LIG] * y[PRKETM2];
   rate[311] = k_jim(316227766.017, 50232, 0) * y[LIG] * y[RKET];
   rate[312] = k_jim(100000000, 41860, 0) * y[LIG] * y[PRADIO];
   rate[313] = k_jim(100000000, 79534, 0) * y[LIG] * y[RC3H3O];
   rate[314] = k_jim(100000000, 52325, 0) * y[LIG] * y[RLIGB];
   rate[315] = k_jim(100000000, 52325, 0) * y[LIG] * y[RLIGA];
   rate[316] = k_jim(316227766.017, 37674, 0) * y[LIG] * y[PRADIOM2];
   rate[317] = k_jim(100000000, 50232, 0) * y[LIG] * y[RMGUAI];
   rate[318] = k_jim(3162277660.17, 10465, 0) * y[LIG] * y[OH];
   rate[319] = k_jim(316227766.017, 28883, 0) * y[LIG] * y[RCH3O];
   rate[320] = k_jim(316227766.017, 50232, 0) * y[LIG] * y[RPHENOL];
   rate[321] = k_jim(100000000, 50232, 0) * y[RADIO] * y[LIG];
   rate[322] = k_jim(100000000, 66976, 0) * y[LIG] * y[RC3H5O2];
   rate[323] = k_jim(100000000, 50232, 0) * y[LIG] * y[PRFET3];
   rate[324] = k_jim(100000000, 58604, 0) * y[LIG] * y[RC3H7O2];
   rate[325] = k_jim(100000000, 50232, 0) * y[LIG] * y[RADIOM2];
   rate[326] = k_jim(100000000, 50232, 0) * y[LIG] * y[PRFET3M2];
   rate[327] = k_jim(316227766.017, 37674, 0) * y[LIG] * y[PRLIGH];
   rate[328] = k_jim(100000000, 50232, 0) * y[RLIGM2B] * y[LIG];
   rate[329] = k_jim(100000000, 50232, 0) * y[LIG] * y[RLIGM2A];
   rate[330] = k_jim(316227766.017, 43953, 0) * y[LIG] * y[RCH3];
   rate[331] = k_jim(100000000, 50232, 0) * y[LIG] * y[PRKETM2];
   rate[332] = k_jim(316227766.017, 50232, 0) * y[LIG] * y[RKET];
   rate[333] = k_jim(100000000, 41860, 0) * y[LIG] * y[PRADIO];
   rate[334] = k_jim(100000000, 79534, 0) * y[LIG] * y[RC3H3O];
   rate[335] = k_jim(100000000, 52325, 0) * y[LIG] * y[RLIGB];
   rate[336] = k_jim(100000000, 52325, 0) * y[LIG] * y[RLIGA];
   rate[337] = k_jim(316227766.017, 37674, 0) * y[LIG] * y[PRADIOM2];
   rate[338] = k_jim(100000000, 50232, 0) * y[LIG] * y[RMGUAI];
   rate[339] = k_jim(3162277660.17, 10465, 0) * y[LIG] * y[OH];
   rate[340] = k_jim(316227766.017, 28883, 0) * y[LIG] * y[RCH3O];
   rate[341] = k_jim(316227766.017, 50232, 0) * y[LIG] * y[RPHENOL];
   rate[342] = k_jim(100000000, 50232, 0) * y[RADIO] * y[LIG];
   rate[343] = k_jim(200000000, 66976, 0) * y[PFET3] * y[RC3H5O2];
   rate[344] = k_jim(200000000, 50232, 0) * y[PFET3] * y[PRFET3];
   rate[345] = k_jim(200000000, 58604, 0) * y[RC3H7O2] * y[PFET3];
   rate[346] = k_jim(200000000, 50232, 0) * y[PFET3] * y[RADIOM2];
   rate[347] = k_jim(200000000, 50232, 0) * y[PFET3] * y[PRFET3M2];
   rate[348] = k_jim(632455532.034, 37674, 0) * y[PFET3] * y[PRLIGH];
   rate[349] = k_jim(200000000, 50232, 0) * y[RLIGM2B] * y[PFET3];
   rate[350] = k_jim(200000000, 50232, 0) * y[RLIGM2A] * y[PFET3];
   rate[351] = k_jim(632455532.034, 43953, 0) * y[PFET3] * y[RCH3];
   rate[352] = k_jim(200000000, 50232, 0) * y[PRKETM2] * y[PFET3];
   rate[353] = k_jim(632455532.034, 50232, 0) * y[PFET3] * y[RKET];
   rate[354] = k_jim(200000000, 41860, 0) * y[PFET3] * y[PRADIO];
   rate[355] = k_jim(200000000, 79534, 0) * y[RC3H3O] * y[PFET3];
   rate[356] = k_jim(200000000, 52325, 0) * y[PFET3] * y[RLIGB];
   rate[357] = k_jim(200000000, 52325, 0) * y[PFET3] * y[RLIGA];
   rate[358] = k_jim(632455532.034, 37674, 0) * y[PRADIOM2] * y[PFET3];
   rate[359] = k_jim(200000000, 50232, 0) * y[PFET3] * y[RMGUAI];
   rate[360] = k_jim(6324555320.34, 10465, 0) * y[PFET3] * y[OH];
   rate[361] = k_jim(632455532.034, 28883, 0) * y[PFET3] * y[RCH3O];
   rate[362] = k_jim(632455532.034, 50232, 0) * y[PFET3] * y[RPHENOL];
   rate[363] = k_jim(200000000, 50232, 0) * y[RADIO] * y[PFET3];
   rate[364] = k_jim(100000000, 66976, 0) * y[ADIO] * y[RC3H5O2];
   rate[365] = k_jim(100000000, 50232, 0) * y[ADIO] * y[PRFET3];
   rate[366] = k_jim(100000000, 58604, 0) * y[RC3H7O2] * y[ADIO];
   rate[367] = k_jim(100000000, 50232, 0) * y[ADIO] * y[RADIOM2];
   rate[368] = k_jim(100000000, 50232, 0) * y[PRFET3M2] * y[ADIO];
   rate[369] = k_jim(316227766.017, 37674, 0) * y[PRLIGH] * y[ADIO];
   rate[370] = k_jim(100000000, 50232, 0) * y[RLIGM2B] * y[ADIO];
   rate[371] = k_jim(100000000, 50232, 0) * y[RLIGM2A] * y[ADIO];
   rate[372] = k_jim(316227766.017, 43953, 0) * y[RCH3] * y[ADIO];
   rate[373] = k_jim(100000000, 50232, 0) * y[PRKETM2] * y[ADIO];
   rate[374] = k_jim(316227766.017, 50232, 0) * y[ADIO] * y[RKET];
   rate[375] = k_jim(100000000, 41860, 0) * y[ADIO] * y[PRADIO];
   rate[376] = k_jim(100000000, 79534, 0) * y[RC3H3O] * y[ADIO];
   rate[377] = k_jim(100000000, 52325, 0) * y[RLIGB] * y[ADIO];
   rate[378] = k_jim(100000000, 52325, 0) * y[ADIO] * y[RLIGA];
   rate[379] = k_jim(316227766.017, 37674, 0) * y[PRADIOM2] * y[ADIO];
   rate[380] = k_jim(100000000, 50232, 0) * y[RMGUAI] * y[ADIO];
   rate[381] = k_jim(3162277660.17, 10465, 0) * y[ADIO] * y[OH];
   rate[382] = k_jim(316227766.017, 28883, 0) * y[RCH3O] * y[ADIO];
   rate[383] = k_jim(316227766.017, 50232, 0) * y[ADIO] * y[RPHENOL];
   rate[384] = k_jim(100000000, 50232, 0) * y[RADIO] * y[ADIO];
   rate[385] = k_jim(100000000, 66976, 0) * y[KET] * y[RC3H5O2];
   rate[386] = k_jim(100000000, 50232, 0) * y[KET] * y[PRFET3];
   rate[387] = k_jim(100000000, 58604, 0) * y[RC3H7O2] * y[KET];
   rate[388] = k_jim(100000000, 50232, 0) * y[KET] * y[RADIOM2];
   rate[389] = k_jim(100000000, 50232, 0) * y[PRFET3M2] * y[KET];
   rate[390] = k_jim(316227766.017, 37674, 0) * y[PRLIGH] * y[KET];
   rate[391] = k_jim(100000000, 50232, 0) * y[RLIGM2B] * y[KET];
   rate[392] = k_jim(100000000, 50232, 0) * y[RLIGM2A] * y[KET];
   rate[393] = k_jim(316227766.017, 43953, 0) * y[RCH3] * y[KET];
   rate[394] = k_jim(100000000, 50232, 0) * y[PRKETM2] * y[KET];
   rate[395] = k_jim(316227766.017, 50232, 0) * y[KET] * y[RKET];
   rate[396] = k_jim(100000000, 41860, 0) * y[KET] * y[PRADIO];
   rate[397] = k_jim(100000000, 79534, 0) * y[RC3H3O] * y[KET];
   rate[398] = k_jim(100000000, 52325, 0) * y[RLIGB] * y[KET];
   rate[399] = k_jim(100000000, 52325, 0) * y[KET] * y[RLIGA];
   rate[400] = k_jim(316227766.017, 37674, 0) * y[PRADIOM2] * y[KET];
   rate[401] = k_jim(100000000, 50232, 0) * y[RMGUAI] * y[KET];
   rate[402] = k_jim(3162277660.17, 10465, 0) * y[KET] * y[OH];
   rate[403] = k_jim(316227766.017, 28883, 0) * y[RCH3O] * y[KET];
   rate[404] = k_jim(316227766.017, 50232, 0) * y[KET] * y[RPHENOL];
   rate[405] = k_jim(100000000, 50232, 0) * y[RADIO] * y[KET];

   return 0;
}

int ModelODEs(double *y, double *dydt, double *k, int *ipar,
              InputStructure *Input)
{
   double *rate;

   /* Setup parameter and rate arrays */
   rate = (double *) New(sizeof(double) * (406));
   Rates(y, rate, k, ipar, Input);

   /* ODE for PLIGC => PLIGC = 0 */
   dydt[PLIGC] = - rate[30] - rate[105];
   /* ODE for PLIGH => PLIGH = 1 */
   dydt[PLIGH] = - rate[153] - rate[137] + rate[201] - rate[133] - rate[142] -
      rate[135] + rate[306] + rate[327] - rate[104] - rate[141] - rate[139] +
      rate[243] + rate[180] + rate[285] - rate[145] - rate[143] - rate[147] +
      rate[159] - rate[152] - rate[151] - rate[144] - rate[150] - rate[148] -
      rate[146] - rate[136] + rate[348] - rate[140] - rate[0] - rate[134] +
      rate[222] + rate[264] + rate[390] + rate[117] - rate[149] + rate[369];
   /* ODE for PLIGO => PLIGO = 2 */
   dydt[PLIGO] = - rate[31] - rate[106];
   /* ODE for PRLIGH => PRLIGH = 3 */
   dydt[PRLIGH] = - rate[243] - rate[390] - rate[180] - rate[285] - rate[201] -
      rate[348] - rate[306] - rate[327] + rate[0] - rate[159] - rate[117] -
      rate[138] - rate[222] - rate[264] - rate[369];
   /* ODE for LIGH => LIGH = 4 */
   dydt[LIGH] = - rate[123] - rate[132] - rate[129] - rate[115] - rate[122] -
      rate[127] + rate[104] - rate[120] - rate[114] - rate[126] - rate[116] -
      rate[118] - rate[121] - rate[124] - rate[112] - rate[125] - rate[113] -
      rate[119] - rate[128] - rate[1] - rate[131] - rate[117] - rate[130];
   /* ODE for C3H6 => C3H6 = 5 */
   dydt[C3H6] = + rate[1];
   /* ODE for OH => OH = 6 */
   dydt[OH] = + rate[99] + rate[98] + rate[26] - rate[234] - rate[339] -
      rate[129] - rate[192] - rate[297] + rate[100] - rate[318] - rate[276] +
      rate[9] - rate[171] - rate[213] - rate[69] + rate[25] + rate[23] -
      rate[381] + rate[24] + rate[1] - rate[360] - rate[402] - rate[255] -
      rate[150];
   /* ODE for RLIGM2A => RLIGM2A = 7 */
   dydt[RLIGM2A] = + rate[191] - rate[308] - rate[287] + rate[194] + rate[189]
      - rate[392] + rate[180] - rate[350] + rate[185] - rate[119] - rate[371] +
      rate[1] - 2.000000e+00 * rate[62] - rate[15] - rate[266] - rate[245] +
      rate[176] + rate[195] + rate[178] - rate[140] + rate[193] - rate[161] +
      rate[187] + rate[192] + rate[186] - rate[224] + rate[184] + rate[12] +
      rate[188] + rate[175] + rate[183] - rate[203] - rate[329] + rate[181] +
      rate[179] + rate[177] + rate[190];
   /* ODE for LIGM2 => LIGM2 = 8 */
   dydt[LIGM2] = - rate[191] + rate[308] - rate[210] - rate[194] + rate[392] -
      rate[212] + rate[139] - rate[199] + rate[350] + rate[307] - rate[2] -
      rate[196] + rate[107] + rate[371] + rate[328] + rate[265] + rate[161] -
      rate[192] + rate[224] - rate[213] - rate[208] - rate[175] - rate[183] -
      rate[200] + rate[329] - rate[179] - rate[209] - rate[207] - rate[205] -
      rate[198] - rate[177] - rate[214] - rate[190] - rate[216] - rate[201] +
      rate[287] - rate[211] - rate[189] + rate[286] - rate[204] - rate[180] -
      rate[215] - rate[185] + rate[119] + rate[244] - rate[206] + rate[266] +
      rate[223] + rate[245] - rate[195] - rate[176] - rate[178] - rate[193] +
      rate[140] - rate[187] - rate[186] - rate[184] - rate[188] + rate[370] -
      rate[197] + rate[118] + rate[349] + rate[391] + rate[160];
   /* ODE for RPHENOXM2 => RPHENOXM2 = 9 */
   dydt[RPHENOXM2] = - rate[10] - rate[49] + rate[16] - rate[48] - rate[45] -
      rate[32] - rate[83] - rate[46] - rate[44] - rate[33] + rate[3] - rate[35]
      - rate[34] + rate[2] - rate[47] - rate[54] - rate[53] + rate[15] +
      rate[18];
   /* ODE for RADIOM2 => RADIOM2 = 10 */
   dydt[RADIOM2] = - rate[367] - 2.000000e+00 * rate[60] - rate[283] +
      rate[256] - rate[115] + rate[249] - rate[199] + rate[243] - rate[304] -
      rate[23] + rate[244] + rate[2] + rate[257] - rate[262] - rate[220] +
      rate[242] + rate[238] + rate[255] + rate[247] - rate[346] - rate[14] +
      rate[245] - rate[178] + rate[246] - rate[136] + rate[253] - rate[388] -
      rate[325] + rate[240] - rate[157] + rate[239] + rate[252] + rate[254] +
      rate[250] + rate[248] + rate[258] + rate[251];
   /* ODE for PLIGM2 => PLIGM2 = 11 */
   dydt[PLIGM2] = - rate[167] - rate[173] - rate[161] - rate[168] - rate[172] -
      rate[169] - rate[158] - rate[171] - rate[157] - rate[170] - rate[3] +
      rate[31] - rate[155] - rate[156] - rate[165] - rate[174] - rate[164] -
      rate[154] - rate[162] - rate[160] - rate[159] - rate[166] - rate[163];
   /* ODE for PRADIOM2 => PRADIOM2 = 12 */
   dydt[PRADIOM2] = - rate[148] - rate[379] - rate[316] - rate[253] - rate[211]
      - rate[127] - rate[295] - rate[232] - rate[71] - rate[169] + rate[3] -
      rate[274] + rate[6] - rate[58] - 2.000000e+00 * rate[110] - rate[400] -
      rate[337] - rate[358] - rate[190];
   /* ODE for LIG => LIG = 13 */
   dydt[LIG] = + rate[230] + rate[356] - rate[339] - rate[308] - rate[316] -
      rate[306] - rate[327] + rate[210] - rate[318] - rate[310] - rate[319] -
      rate[304] - rate[307] - rate[317] - rate[305] + rate[273] - rate[312] +
      rate[147] - rate[342] - rate[328] - rate[321] - rate[330] - rate[331] -
      rate[332] - rate[324] + rate[252] + rate[108] + rate[126] + rate[125] -
      rate[329] - rate[341] + rate[209] - rate[313] + rate[272] + rate[231] +
      rate[293] - rate[337] + rate[251] + rate[189] + rate[377] + rate[357] +
      rate[398] - rate[326] - rate[311] - rate[334] - rate[303] - rate[309] -
      rate[301] + rate[146] - rate[323] + rate[167] - rate[4] + rate[168] -
      rate[333] - rate[320] + rate[378] + rate[294] - rate[325] + rate[188] -
      rate[338] - rate[322] - rate[302] - rate[340] + rate[399];
   /* ODE for RPHENOX => RPHENOX = 14 */
   dydt[RPHENOX] = - rate[39] + rate[4] - rate[42] - rate[52] - rate[81] -
      rate[36] - rate[41] - rate[50] - rate[40] - rate[80] - rate[37] +
      rate[22] + rate[28] + rate[5] - rate[43] - rate[11] - rate[51] - rate[38]
      - rate[82] - rate[73] - rate[55] + rate[29] + rate[20];
   /* ODE for RADIO => RADIO = 15 */
   dydt[RADIO] = + rate[367] - 2.000000e+00 * rate[74] - rate[216] - rate[153]
      - rate[132] - rate[279] + rate[372] + rate[364] + rate[377] + rate[373] -
      rate[405] + rate[381] - rate[174] + rate[371] + rate[380] - rate[321] -
      rate[342] - rate[19] + rate[379] - rate[195] + rate[365] + rate[366] +
      rate[4] + rate[383] + rate[382] + rate[378] + rate[370] - rate[25] -
      rate[237] + rate[375] + rate[368] + rate[376] - rate[258] - rate[363] -
      rate[300] + rate[369] + rate[374];
   /* ODE for PLIG => PLIG = 16 */
   dydt[PLIG] = + rate[30] - rate[5];
   /* ODE for PRADIO => PRADIO = 17 */
   dydt[PRADIO] = - rate[123] - rate[270] - rate[333] - rate[186] - rate[396] -
      rate[249] + rate[5] - 2.000000e+00 * rate[109] - rate[165] - rate[354] -
      rate[207] - rate[312] - rate[375] + rate[7] - rate[228] - rate[291] -
      rate[144];
   /* ODE for PADIOM2 => PADIOM2 = 18 */
   dydt[PADIOM2] = + rate[148] + rate[379] + rate[316] + rate[253] + rate[211]
      + rate[127] + rate[295] + rate[232] + rate[71] + rate[169] + rate[274] -
      rate[6] + rate[58] + rate[400] + rate[337] + rate[358] + rate[190];
   /* ODE for PADIO => PADIO = 19 */
   dydt[PADIO] = + rate[123] + rate[165] + rate[354] + rate[375] + rate[312] +
      rate[270] + rate[207] - rate[7] + rate[333] + rate[228] + rate[186] +
      rate[396] + rate[291] + rate[249] + rate[144];
   /* ODE for PKETM2 => PKETM2 = 20 */
   dydt[PKETM2] = + rate[16] + rate[394] + rate[142] + rate[289] + rate[310] +
      rate[184] + rate[373] + rate[331] + rate[59] + rate[268] + rate[352] +
      rate[121] + rate[72] + rate[226] - rate[8] + rate[205] + rate[163] +
      rate[247];
   /* ODE for PRKETM2 => PRKETM2 = 21 */
   dydt[PRKETM2] = - rate[394] - rate[142] - rate[289] - rate[310] - rate[184]
      - rate[373] - rate[331] - rate[9] - rate[59] - rate[268] - rate[352] -
      rate[121] - rate[72] - rate[226] + rate[8] - rate[205] - rate[163] -
      rate[247];
   /* ODE for KETDM2 => KETDM2 = 22 */
   dydt[KETDM2] = - rate[34] - rate[86] - rate[38] + rate[24] + rate[9];
   /* ODE for CO => CO = 23 */
   dydt[CO] = + rate[11] + rate[10] + rate[95] + rate[111] + rate[94];
   /* ODE for C10H2M4 => C10H2M4 = 24 */
   dydt[C10H2M4] = + rate[60] + 5.000000e-01 * rate[10] + 5.000000e-01 *
      rate[49] + 5.000000e-01 * rate[39] + rate[63] + 5.000000e-01 * rate[45] +
      rate[32] + 5.000000e-01 * rate[83] + 5.000000e-01 * rate[36] -
      5.000000e-01 * rate[50] + 5.000000e-01 * rate[37] + 5.000000e-01 *
      rate[46] - 5.000000e-01 * rate[28] + 5.000000e-01 * rate[44] + rate[33] +
      rate[35] + rate[65] + rate[34] + rate[64] + 2.000000e+00 * rate[61] +
      5.000000e-01 * rate[47] + 2.000000e+00 * rate[79] + 5.000000e-01 *
      rate[54] + rate[110] + 5.000000e-01 * rate[53] + 2.000000e+00 * rate[62]
      + 5.000000e-01 * rate[38];
   /* ODE for H2 => H2 = 25 */
   dydt[H2] = + rate[78] + rate[74] + 5.000000e-01 * rate[49] + rate[97] +
      1.500000e+00 * rate[52] + 5.000000e-01 * rate[48] + 1.500000e+00 *
      rate[45] + 5.000000e-01 * rate[32] + rate[96] + 5.000000e-01 * rate[83] +
      1.500000e+00 * rate[41] + 1.500000e+00 * rate[40] + 1.500000e+00 *
      rate[80] + 2.000000e+00 * rate[75] + 1.500000e+00 * rate[44] +
      2.500000e+00 * rate[43] + 5.000000e-01 * rate[33] + 1.500000e+00 *
      rate[47] + 5.000000e-01 * rate[102] + 5.000000e-01 * rate[53] +
      5.000000e-01 * rate[38] + 2.000000e+00 * rate[73] + 5.000000e-01 *
      rate[10] + 5.000000e-01 * rate[103] + 1.500000e+00 * rate[39] +
      2.000000e+00 * rate[77] + 1.500000e+00 * rate[42] + rate[81] +
      1.500000e+00 * rate[50] + 5.000000e-01 * rate[37] + 1.500000e+00 *
      rate[46] + rate[35] + 1.500000e+00 * rate[11] + rate[109] + 5.000000e-01
      * rate[34] + 1.500000e+00 * rate[51] + rate[79] + 2.000000e+00 * rate[76]
      + 1.500000e+00 * rate[82];
   /* ODE for C10H2 => C10H2 = 26 */
   dydt[C10H2] = + rate[78] + rate[74] - 5.000000e-01 * rate[284] +
      5.000000e-01 * rate[49] - 5.000000e-01 * rate[292] - 5.000000e-01 *
      rate[283] - 5.000000e-01 * rate[282] + 5.000000e-01 * rate[52] +
      5.000000e-01 * rate[45] - 5.000000e-01 * rate[287] + rate[41] -
      5.000000e-01 * rate[286] + rate[40] - 5.000000e-01 * rate[299] + rate[80]
      + 2.000000e+00 * rate[75] + 5.000000e-01 * rate[44] + rate[43] -
      5.000000e-01 * rate[285] + 5.000000e-01 * rate[47] - 5.000000e-01 *
      rate[288] + 5.000000e-01 * rate[38] + 1.500000e+00 * rate[73] +
      5.000000e-01 * rate[29] - 5.000000e-01 * rate[290] + 5.000000e-01 *
      rate[39] + rate[77] + rate[42] - 5.000000e-01 * rate[297] + 5.000000e-01
      * rate[36] + 5.000000e-01 * rate[81] - 5.000000e-01 * rate[289] +
      5.000000e-01 * rate[50] - 5.000000e-01 * rate[280] - 5.000000e-01 *
      rate[295] + 5.000000e-01 * rate[37] - 5.000000e-01 * rate[294] +
      5.000000e-01 * rate[46] - 5.000000e-01 * rate[296] + 5.000000e-01 *
      rate[11] + rate[109] - 5.000000e-01 * rate[298] - 5.000000e-01 *
      rate[281] + rate[51] - 5.000000e-01 * rate[293] + 2.000000e+00 * rate[76]
      - 5.000000e-01 * rate[291] + 5.000000e-01 * rate[55] + 5.000000e-01 *
      rate[82] - 5.000000e-01 * rate[300];
   /* ODE for RLIGH => RLIGH = 27 */
   dydt[RLIGH] = + rate[123] + rate[132] + rate[129] + rate[115] + rate[122] +
      rate[127] + rate[120] - rate[12] + rate[114] + rate[126] + rate[116] +
      rate[118] + rate[121] + rate[124] + rate[112] + rate[125] + rate[113] +
      rate[119] - 2.000000e+00 * rate[79] + rate[128] + rate[131] + rate[117] +
      rate[130];
   /* ODE for ALD3 => ALD3 = 28 */
   dydt[ALD3] = + rate[13] + rate[12];
   /* ODE for PRLIGH2 => PRLIGH2 = 29 */
   dydt[PRLIGH2] = + rate[148] + rate[146] + rate[153] - rate[13] + rate[137] +
      rate[133] + rate[136] + rate[142] + rate[140] + rate[135] + rate[141] +
      rate[134] + rate[138] + rate[139] + rate[145] + rate[143] + rate[147] +
      rate[152] + rate[151] + rate[149] + rate[144] + rate[150];
   /* ODE for PRLIGM2A => PRLIGM2A = 30 */
   dydt[PRLIGM2A] = + rate[167] - rate[16] + rate[13] + rate[173] + rate[161] +
      rate[168] + rate[172] + rate[169] + rate[158] + rate[171] + rate[157] +
      rate[170] + rate[155] + rate[156] + rate[165] + rate[174] + rate[164] +
      rate[154] + rate[162] + rate[160] + rate[159] + rate[166] + rate[163];
   /* ODE for RMGUAI => RMGUAI = 31 */
   dydt[RMGUAI] = - rate[191] + rate[14] - rate[401] - 2.000000e+00 * rate[63]
      - rate[233] - rate[212] - rate[338] - rate[170] - rate[296] - rate[254] -
      rate[317] - rate[128] + rate[17] - rate[359] - rate[380] - rate[275] -
      rate[149];
   /* ODE for C3H6O2 => C3H6O2 = 32 */
   dydt[C3H6O2] = + rate[301] + rate[19] + rate[14] + rate[133] + rate[364] +
      rate[343] + rate[280] + rate[217] + rate[259] + rate[175] + rate[112] +
      rate[385] + rate[196] + rate[322] + rate[154] + rate[238];
   /* ODE for KETM2 => KETM2 = 33 */
   dydt[KETM2] = - rate[260] - rate[278] - rate[269] - rate[279] - rate[265] -
      rate[270] - rate[85] - rate[37] - rate[264] - rate[276] - rate[277] -
      rate[33] - rate[259] - rate[268] - rate[274] - rate[263] - rate[273] -
      rate[272] - rate[262] - rate[267] + rate[15] - rate[271] - rate[275] -
      rate[261] - rate[266];
   /* ODE for RLIGM2B => RLIGM2B = 34 */
   dydt[RLIGM2B] = + rate[216] + rate[201] + rate[211] + rate[210] - rate[286]
      + rate[204] + rate[212] - rate[139] + rate[199] + rate[215] - rate[307] -
      rate[244] - 2.000000e+00 * rate[61] + rate[196] + rate[206] - rate[328] -
      rate[223] - rate[265] - rate[370] + rate[213] + rate[197] + rate[208] +
      rate[203] + rate[200] - rate[118] - rate[181] - rate[349] + rate[207] +
      rate[209] - rate[391] + rate[205] - rate[17] + rate[198] - rate[160] +
      rate[214];
   /* ODE for PFET3M2 => PFET3M2 = 35 */
   dydt[PFET3M2] = - rate[229] - rate[219] + rate[284] - rate[230] + rate[137]
      + rate[347] - rate[236] - rate[232] - rate[235] - rate[233] + rate[158] +
      rate[326] - rate[217] + rate[263] + rate[305] - rate[226] - rate[220] -
      rate[225] + rate[242] - rate[227] - rate[223] + rate[389] - rate[234] -
      rate[218] - rate[224] - rate[222] + rate[200] + rate[116] - rate[237] +
      rate[179] + rate[368] + rate[17] - rate[228] - rate[231];
   /* ODE for PRFET3M2 => PRFET3M2 = 36 */
   dydt[PRFET3M2] = + rate[229] + rate[219] - rate[284] + rate[230] - rate[137]
      - rate[347] + rate[236] + rate[232] + rate[235] + rate[233] - rate[158] -
      rate[326] + rate[217] - rate[263] - 2.000000e+00 * rate[65] - rate[305] +
      rate[226] + rate[220] + rate[225] - rate[18] - rate[242] + rate[227] +
      rate[223] - rate[389] + rate[234] + rate[218] + rate[224] + rate[222] -
      rate[200] - rate[116] + rate[237] - rate[179] - rate[368] + rate[228] +
      rate[231];
   /* ODE for C3H4O2 => C3H4O2 = 37 */
   dydt[C3H4O2] = + rate[18] + rate[22];
   /* ODE for RPHENOL => RPHENOL = 38 */
   dydt[RPHENOL] = + rate[19] - rate[278] - rate[173] - rate[383] - rate[320] -
      rate[236] - rate[194] - rate[299] - rate[80] - rate[362] - rate[215] -
      rate[341] - rate[257] - rate[131] + rate[21] - rate[404] - rate[152];
   /* ODE for RLIGA => RLIGA = 39 */
   dydt[RLIGA] = + rate[308] + rate[316] + rate[306] - rate[189] - rate[210] +
      rate[318] + rate[310] - rate[357] + rate[319] + rate[304] + rate[307] +
      rate[317] + rate[311] - rate[273] + rate[305] + rate[312] - rate[147] +
      rate[303] - rate[336] + rate[321] - rate[20] + rate[301] + rate[309] -
      rate[168] + rate[320] - rate[378] - rate[294] - rate[252] - rate[126] +
      rate[313] - rate[231] + rate[302] - 2.000000e+00 * rate[76] + rate[314] -
      rate[399];
   /* ODE for KET => KET = 40 */
   dydt[KET] = - rate[91] - rate[394] - rate[45] - rate[41] - rate[392] -
      rate[398] - rate[405] + rate[185] + rate[143] + rate[311] + rate[164] -
      rate[400] + rate[206] + rate[227] - rate[402] - rate[387] + rate[20] +
      rate[269] - rate[389] + rate[290] - rate[401] - rate[397] + rate[122] -
      rate[388] - rate[396] + rate[332] - rate[393] - rate[390] - rate[385] -
      rate[386] + rate[353] + rate[248] - rate[391] - rate[404] - rate[403] +
      rate[374] - rate[399];
   /* ODE for RLIGB => RLIGB = 41 */
   dydt[RLIGB] = - rate[230] - rate[356] + rate[339] + rate[327] - rate[377] -
      2.000000e+00 * rate[75] - rate[398] + rate[326] + rate[334] + rate[336] -
      rate[73] + rate[342] + rate[328] - rate[146] + rate[323] - rate[167] +
      rate[330] + rate[333] + rate[325] + rate[331] - rate[188] + rate[324] +
      rate[332] + rate[338] - rate[125] + rate[329] + rate[341] + rate[322] -
      rate[209] - rate[272] - rate[21] - rate[293] + rate[337] + rate[340] -
      rate[314] - rate[251];
   /* ODE for PFET3 => PFET3 = 42 */
   dydt[PFET3] = + rate[260] - rate[361] - rate[356] - rate[347] - rate[343] -
      rate[357] - rate[362] + rate[155] - rate[350] - rate[354] - rate[345] -
      rate[359] - rate[358] - rate[355] - rate[346] + rate[323] + rate[176] +
      rate[365] - rate[348] + rate[218] + rate[134] + rate[239] + rate[197] -
      rate[352] + rate[386] + rate[281] + rate[113] - rate[353] - rate[349] -
      rate[351] + rate[21] - rate[360] + rate[302] - rate[363];
   /* ODE for PRFET3 => PRFET3 = 43 */
   dydt[PRFET3] = - 2.000000e+00 * rate[78] - rate[260] + rate[361] + rate[356]
      + rate[347] + rate[343] - rate[22] + rate[357] + rate[362] - rate[155] +
      rate[350] + rate[354] + rate[345] + rate[359] + rate[358] + rate[355] +
      rate[346] - rate[323] - rate[176] - rate[365] + rate[348] - rate[218] -
      rate[134] - rate[239] - rate[197] + rate[352] - rate[386] - rate[281] -
      rate[113] + rate[353] + rate[349] + rate[351] + rate[360] - rate[302] +
      rate[363];
   /* ODE for SYNAPYL => SYNAPYL = 44 */
   dydt[SYNAPYL] = - rate[87] - rate[35] - rate[39] + rate[23];
   /* ODE for RKETM2 => RKETM2 = 45 */
   dydt[RKETM2] = + rate[260] + rate[278] + rate[269] + rate[279] + rate[265] +
      rate[270] + rate[264] + rate[276] + rate[277] + rate[259] + rate[268] +
      rate[274] + rate[263] - rate[24] - 2.000000e+00 * rate[64] + rate[273] +
      rate[262] + rate[267] + rate[272] + rate[271] + rate[275] + rate[261] +
      rate[266];
   /* ODE for COUMARYL => COUMARYL = 46 */
   dydt[COUMARYL] = - rate[89] + rate[25] - rate[47] - rate[43];
   /* ODE for RKET => RKET = 47 */
   dydt[RKET] = + rate[394] + rate[392] + rate[398] + rate[405] - rate[185] -
      rate[143] - rate[311] - rate[164] + rate[400] - rate[206] - rate[227] +
      rate[402] + rate[387] - rate[269] + rate[389] - rate[26] - 2.000000e+00 *
      rate[77] - rate[290] + rate[397] + rate[401] - rate[122] + rate[388] +
      rate[396] - rate[332] + rate[393] + rate[390] + rate[385] + rate[386] -
      rate[353] - rate[248] + rate[391] + rate[404] + rate[403] - rate[374] +
      rate[399];
   /* ODE for KETD => KETD = 48 */
   dydt[KETD] = + rate[26] - rate[46] - rate[42] - rate[92];
   /* ODE for RC3H7O2 => RC3H7O2 = 49 */
   dydt[RC3H7O2] = - rate[27] - rate[219] - rate[366] - 2.000000e+00 * rate[66]
      - rate[282] - rate[135] + rate[32] + rate[36] + rate[40] - rate[240] -
      rate[324] + rate[44] - rate[114] - rate[156] - rate[345] - rate[198] -
      rate[303] - rate[177] - rate[261] - rate[387];
   /* ODE for RCH3O => RCH3O = 50 */
   dydt[RCH3O] = + rate[27] + rate[49] - rate[56] - rate[361] - rate[256] -
      rate[193] - rate[52] + rate[48] - rate[382] - rate[172] + rate[50] -
      2.000000e+00 * rate[57] - rate[235] + rate[28] - rate[277] - rate[59] -
      rate[319] - rate[298] - rate[58] + rate[51] - rate[53] - rate[340] -
      rate[151] - rate[214] - rate[130] - rate[403] + rate[29];
   /* ODE for CH3CHO => CH3CHO = 51 */
   dydt[CH3CHO] = + rate[27] + rate[57];
   /* ODE for C10H2M2 => C10H2M2 = 52 */
   dydt[C10H2M2] = - 5.000000e-01 * rate[49] + 5.000000e-01 * rate[50] -
      5.000000e-01 * rate[51] + 5.000000e-01 * rate[48] - rate[29];
   /* ODE for CH2CO => CH2CO = 53 */
   dydt[CH2CO] = + rate[108] + rate[30];
   /* ODE for CO2 => CO2 = 54 */
   dydt[CO2] = + rate[107] + rate[53] + rate[31] + rate[52];
   /* ODE for ADIOM2 => ADIOM2 = 55 */
   dydt[ADIOM2] = + rate[367] + rate[283] - rate[256] - rate[84] - rate[32] +
      rate[115] - rate[249] + rate[199] - rate[243] + rate[304] - rate[244] -
      rate[257] + rate[262] + rate[220] - rate[242] - rate[238] - rate[255] -
      rate[247] + rate[346] - rate[245] + rate[178] - rate[246] + rate[136] -
      rate[36] - rate[253] + rate[388] + rate[325] - rate[240] + rate[157] -
      rate[239] - rate[252] - rate[254] - rate[250] - rate[248] - rate[258] -
      rate[251];
   /* ODE for PH2 => PH2 = 56 */
   dydt[PH2] = + 2.000000e+00 * rate[78] + 3.000000e+00 * rate[74] +
      2.000000e+00 * rate[60] + rate[68] + 2.000000e+00 * rate[63] + rate[45] +
      rate[32] - rate[96] + 2.000000e+00 * rate[41] + 2.000000e+00 * rate[40] +
      2.000000e+00 * rate[80] + 5.000000e+00 * rate[75] + rate[44] +
      2.000000e+00 * rate[43] + rate[33] + rate[65] + 2.000000e+00 * rate[64] +
      3.000000e+00 * rate[61] + 2.000000e+00 * rate[47] + 5.000000e-01 *
      rate[54] + rate[110] + 3.000000e+00 * rate[62] + 2.000000e+00 * rate[38]
      + 3.000000e+00 * rate[73] + 2.000000e+00 * rate[39] + 2.000000e+00 *
      rate[77] + rate[66] + 2.000000e+00 * rate[42] + rate[81] + rate[36] +
      2.000000e+00 * rate[37] + rate[46] + 1.500000e+00 * rate[35] +
      2.000000e+00 * rate[109] + rate[34] + 5.000000e+00 * rate[76] +
      1.500000e+00 * rate[55] + rate[67];
   /* ODE for PCOH => PCOH = 57 */
   dydt[PCOH] = + rate[74] + 2.000000e+00 * rate[60] + rate[49] + 3.000000e+00
      * rate[77] + rate[39] + 2.000000e+00 * rate[68] + 2.000000e+00 * rate[63]
      + rate[48] + rate[45] + 2.000000e+00 * rate[32] + rate[81] + rate[36] -
      rate[95] + rate[46] + 2.000000e+00 * rate[33] + rate[44] + 2.000000e+00 *
      rate[35] + rate[109] + 2.000000e+00 * rate[65] + 2.000000e+00 * rate[34]
      + 4.000000e+00 * rate[64] + 4.000000e+00 * rate[61] + rate[47] +
      4.000000e+00 * rate[79] + rate[54] + 2.000000e+00 * rate[110] +
      4.000000e+00 * rate[62] + rate[38] + rate[55] + 2.000000e+00 * rate[67];
   /* ODE for RC3H5O2 => RC3H5O2 = 58 */
   dydt[RC3H5O2] = - rate[301] - rate[133] - rate[364] + rate[45] - rate[343] +
      rate[41] - rate[280] + rate[37] + rate[33] - rate[217] - rate[259] -
      rate[175] - rate[385] - rate[112] - rate[196] - rate[322] - rate[154] -
      rate[238] - 2.000000e+00 * rate[67];
   /* ODE for RC3H3O => RC3H3O = 59 */
   dydt[RC3H3O] = - rate[229] - rate[292] + rate[39] - 2.000000e+00 * rate[68]
      - rate[397] + rate[42] - rate[187] - rate[81] + rate[46] + rate[43] +
      rate[35] - rate[208] - rate[124] + rate[34] - rate[145] + rate[47] -
      rate[250] - rate[334] - rate[313] - rate[376] - rate[271] - rate[166] +
      rate[38] - rate[355];
   /* ODE for PCOS => PCOS = 60 */
   dydt[PCOS] = + 2.000000e+00 * rate[78] + rate[74] + rate[77] + rate[39] +
      2.000000e+00 * rate[42] + rate[45] + rate[83] + rate[81] + rate[36] +
      2.000000e+00 * rate[41] + rate[50] + 2.000000e+00 * rate[40] +
      2.000000e+00 * rate[80] + 2.000000e+00 * rate[37] - rate[94] + rate[46] +
      4.000000e+00 * rate[75] + 2.000000e+00 * rate[43] + rate[44] + rate[109]
      + rate[47] + rate[51] + 4.000000e+00 * rate[76] + rate[38] + rate[82] +
      3.000000e+00 * rate[73];
   /* ODE for ADIO => ADIO = 61 */
   dydt[ADIO] = - rate[367] + rate[216] + rate[153] + rate[132] + rate[279] -
      rate[372] - rate[364] - rate[377] - rate[40] - rate[373] - rate[44] +
      rate[405] - rate[381] + rate[174] - rate[371] - rate[380] - rate[90] +
      rate[321] + rate[342] - rate[379] + rate[195] - rate[365] - rate[366] -
      rate[383] - rate[382] - rate[378] - rate[370] + rate[237] - rate[375] -
      rate[368] - rate[376] + rate[258] + rate[363] + rate[300] - rate[369] -
      rate[374];
   /* ODE for RCH3 => RCH3 = 62 */
   dydt[RCH3] = - rate[309] - rate[56] - rate[246] - 2.000000e+00 * rate[70] -
      rate[372] - rate[330] + rate[52] - rate[204] - rate[120] - rate[141] -
      rate[71] - rate[393] - rate[69] - rate[183] - rate[72] - rate[54] -
      rate[351] + rate[53] - rate[267] - rate[162] - rate[225] - rate[288] -
      rate[55] + rate[101];
   /* ODE for PCH3 => PCH3 = 63 */
   dydt[PCH3] = + rate[72] + rate[71] + rate[55] - rate[101] + 2.000000e+00 *
      rate[79] + rate[54];
   /* ODE for ETOH => ETOH = 64 */
   dydt[ETOH] = + rate[56];
   /* ODE for H2O => H2O = 65 */
   dydt[H2O] = + rate[234] + 2.000000e+00 * rate[66] + rate[339] + rate[129] +
      rate[192] + rate[297] + rate[318] + rate[57] + rate[276] + rate[171] +
      rate[213] + rate[381] + 4.000000e+00 * rate[79] + 2.000000e+00 * rate[62]
      + rate[360] + 2.000000e+00 * rate[76] + rate[402] + rate[73] + rate[255]
      + 2.000000e+00 * rate[67] + rate[150];
   /* ODE for PCH2OH => PCH2OH = 66 */
   dydt[PCH2OH] = + 2.000000e+00 * rate[74] + 2.000000e+00 * rate[60] -
      rate[98] + 2.000000e+00 * rate[109] + 2.000000e+00 * rate[77] + rate[58]
      + 2.000000e+00 * rate[64] + 2.000000e+00 * rate[61] + 2.000000e+00 *
      rate[110] + rate[59] + 2.000000e+00 * rate[75];
   /* ODE for PCHP2 => PCHP2 = 67 */
   dydt[PCHP2] = + 2.000000e+00 * rate[78] + 2.000000e+00 * rate[74] +
      2.000000e+00 * rate[60] + 2.000000e+00 * rate[109] - rate[103] +
      2.000000e+00 * rate[65] + 2.000000e+00 * rate[77] + 2.000000e+00 *
      rate[64] + rate[102] + 2.000000e+00 * rate[79] + 2.000000e+00 *
      rate[110];
   /* ODE for PCHOHP => PCHOHP = 68 */
   dydt[PCHOHP] = - rate[99] + 2.000000e+00 * rate[78] + 2.000000e+00 *
      rate[74] + 2.000000e+00 * rate[60] + 2.000000e+00 * rate[109] +
      2.000000e+00 * rate[65] + 2.000000e+00 * rate[66] + 2.000000e+00 *
      rate[61] + 2.000000e+00 * rate[110] + 2.000000e+00 * rate[75];
   /* ODE for CHAR => CHAR = 69 */
   dydt[CHAR] = + 5.000000e-01 * rate[284] + 5.000000e-01 * rate[292] +
      1.000000e-01 * rate[103] + 2.000000e-01 * rate[97] + 5.000000e-01 *
      rate[290] + 5.000000e-01 * rate[283] + 5.000000e-01 * rate[282] +
      5.000000e-01 * rate[287] + 5.000000e-01 * rate[297] + 1.000000e-01 *
      rate[100] + 5.000000e-01 * rate[289] + 5.000000e-01 * rate[286] +
      5.000000e-01 * rate[280] + 5.000000e-01 * rate[299] + 5.000000e-01 *
      rate[295] + 5.000000e-01 * rate[294] + 2.000000e-01 * rate[75] +
      5.000000e-01 * rate[296] + 5.000000e-01 * rate[298] + 5.000000e-01 *
      rate[285] + 5.000000e-01 * rate[281] + 2.000000e-01 * rate[61] +
      5.000000e-01 * rate[293] + 5.000000e-01 * rate[288] + 5.000000e-01 *
      rate[291] + 5.000000e-01 * rate[300];
   /* ODE for PCOHP2 => PCOHP2 = 70 */
   dydt[PCOHP2] = - rate[100] + 2.000000e+00 * rate[62] + 2.000000e+00 *
      rate[76] + rate[73] + 2.000000e+00 * rate[79];
   /* ODE for PC2H2 => PC2H2 = 71 */
   dydt[PC2H2] = + 5.000000e-01 * rate[99] + rate[81] + 2.000000e+00 * rate[62]
      - rate[97] + 2.000000e+00 * rate[76] + 2.000000e+00 * rate[68] +
      2.000000e+00 * rate[66] + rate[73] + 2.000000e+00 * rate[79] +
      2.000000e+00 * rate[67];
   /* ODE for PCHO => PCHO = 72 */
   dydt[PCHO] = + 2.000000e+00 * rate[78] + 2.000000e+00 * rate[65] -
      rate[111];
   /* ODE for CH3OH => CH3OH = 73 */
   dydt[CH3OH] = + rate[319] + rate[69] + rate[298] + rate[361] + rate[256] +
      rate[193] + rate[382] + rate[172] + rate[340] + rate[151] + rate[235] +
      rate[130] + rate[214] + rate[403] + rate[277];
   /* ODE for C2H6 => C2H6 = 74 */
   dydt[C2H6] = + rate[70];
   /* ODE for PCH2P => PCH2P = 75 */
   dydt[PCH2P] = + rate[98] - rate[102] + 2.000000e+00 * rate[79];
   /* ODE for VADIOM2 => VADIOM2 = 76 */
   dydt[VADIOM2] = + rate[84];
   /* ODE for VKETM2 => VKETM2 = 77 */
   dydt[VKETM2] = + rate[85];
   /* ODE for VKETDM2 => VKETDM2 = 78 */
   dydt[VKETDM2] = + rate[86];
   /* ODE for VSYNAPYL => VSYNAPYL = 79 */
   dydt[VSYNAPYL] = + rate[87];
   /* ODE for MGUAI => MGUAI = 80 */
   dydt[MGUAI] = + rate[191] + rate[170] + rate[296] + rate[401] + rate[317] +
      rate[254] - rate[88] + rate[128] + rate[359] + rate[380] + rate[275] +
      rate[233] + rate[149] + rate[212] + rate[338];
   /* ODE for VMGUAI => VMGUAI = 81 */
   dydt[VMGUAI] = + rate[88];
   /* ODE for VCOUMARYL => VCOUMARYL = 82 */
   dydt[VCOUMARYL] = + rate[89];
   /* ODE for VADIO => VADIO = 83 */
   dydt[VADIO] = + rate[90];
   /* ODE for VKET => VKET = 84 */
   dydt[VKET] = + rate[91];
   /* ODE for VKETD => VKETD = 85 */
   dydt[VKETD] = + rate[92];
   /* ODE for PHENOL => PHENOL = 86 */
   dydt[PHENOL] = + rate[362] + rate[215] + rate[278] + rate[173] + rate[341] +
      rate[383] + rate[257] + rate[320] - rate[93] + rate[131] + rate[194] +
      rate[236] + rate[404] + rate[152] + rate[299];
   /* ODE for VPHENOL => VPHENOL = 87 */
   dydt[VPHENOL] = + rate[93];
   /* ODE for LIGC => LIGC = 88 */
   dydt[LIGC] = - rate[108] + rate[105];
   /* ODE for LIGO => LIGO = 89 */
   dydt[LIGO] = - rate[107] + rate[106];
   /* ODE for C3H8O2 => C3H8O2 = 90 */
   dydt[C3H8O2] = + rate[114] + rate[219] + rate[156] + rate[366] + rate[345] +
      rate[282] + rate[135] + rate[303] + rate[198] + rate[177] + rate[261] +
      rate[387] + rate[240] + rate[324];
   /* ODE for CH4 => CH4 = 91 */
   dydt[CH4] = + rate[393] + rate[309] + rate[183] + rate[246] + rate[372] +
      rate[330] + rate[351] + rate[162] + rate[267] + rate[225] + rate[288] +
      rate[120] + rate[204] + rate[141];
   /* ODE for C3H4O => C3H4O = 92 */
   dydt[C3H4O] = + rate[229] + rate[208] + rate[292] + rate[124] + rate[145] +
      rate[397] + rate[250] + rate[334] + rate[313] + rate[187] + rate[376] +
      rate[271] + rate[166] + rate[355];

   Delete(rate);
   return 0;
}

int AlgebraicEqns(double *y, double *f, double *k, int *ipar,
                  InputStructure *Input, int check)
{
   return 0;
}

int EqnType(double *ework, int nSpecies, int nSurfaceSpecies,
            InputStructure *Input)
{
   return 0;
}

void TimeFcn(double t, double *y, double *yprime, double *flowin, int nSpecies,
	     int nSurfaceSpecies, double *k, int *ipar, InputStructure *Input,
	     double *density, double *molwt)
{
   return;
}

void dump2f(FILE *ffile, double t, int nstvar, double *y, double *f, double *wt,
            int nspar, double *deriv, int lenfc, int nSpecies, int nSurfaceSpecies,
            InputStructure *Input, int iout, double *density, double *molwt, double *yprime,
	    double *k)
{
   int i, j, findex;
   int yfirst=0, ylast=0;
   double modify=1.0e0;

   /* calculate starting index of f array */
   findex = iout * (ylast - yfirst + 1);

   if (Input->reactor == ePFR) {
      /* convert to pressures 
       * (assumes only gaseous species will be put in f and deriv) */
      double Fs=0.0e0;
      for (i = nSurfaceSpecies; i < nSpecies; i++) {
	 Fs += y[i];
      }
      modify *= Input->ptot / Fs;
   }
   fprintf(ffile, "%le\t", t);
   for (j = 0; j <= ylast - yfirst; j++) {
      fprintf(ffile, "%le\t", y[yfirst + j] * modify);
      if (f != NULL) {
         f[findex + j] = y[yfirst + j] * modify * wt[findex + j];
         for (i = 0; i < nspar; i++) {
            deriv[findex + j + lenfc * i] = y[yfirst + j + nstvar * (i + 1)]
               * modify * wt[findex + j];
         }
      }
   }
   fprintf(ffile, "\n");
   return;
}
