"""
Named constants, or objects with values that are constant, used by other
modules.
"""

# Universal gas constant [J mol^-1 K^-1]
GAS_CONST = 8.314
# The cooling rate in *C/min to use if a cool down period is specified
COOL_RATE = -13
# Tolerances for ODE solver
ABSOLUTE_TOLERANCE = 1E-11
RELATIVE_TOLERANCE = 1E-9

# MW Dictionary values are:
# [0] MW
# [1] phase (g,s,lt,t,char,H20,CO,CO2)
# The rest of the columns are information that is only needed for tar
# components, so it may be blank in species of other phases
# [2] phenolic family (phenol/syringol)
# [3] number of [C,H,O] in the molecule
# [4] number of each type of C-bond/functional group in each molecule
# [carbonyl, aromatic C-O, aromatic C-C, aromatic C-H, aliphatic C-O,
# Methoxyl-aromatic, aliphatic C-C]
# .
# You can make changes to this dictionary to adjust which fraction each species
# is attributed to when lumping (commonly changed might be methanol, ETOH,
# ALD3, so those are located at the top).
# .
# The phenolic family entry indicates whether a tar species belongs to the
# phenol family or the syringol family (has methoxyl groups).
MW = {'CH3OH'    : [32 , 'lt'  , ' ', [1 , 4 , 1 ], [0, 0, 0, 0, 1, 0, 0]],
      'ETOH'     : [46 , 'lt'  , ' ', [2 , 6 , 1 ], [0, 0, 0, 0, 1, 0, 1]],
      'ALD3'     : [58 , 'lt'  , ' ', [3 , 6 , 1 ], [1, 0, 0, 0, 0, 0, 2]],
      'PLIGH'    : [436, 's'   , ' ', [22, 28, 9 ], [0, 7, 1, 4, 5, 4, 1]],
      'LIGH'     : [437, 's'   , ' '],
      'PLIGO'    : [422, 's'   , ' ', [20, 22, 10], [1, 7, 1, 4, 3, 4, 0]],
      'LIGO'     : [423, 's'   , ' '],
      'PLIGC'    : [300, 's'   , ' ', [17, 16, 5 ], [1, 3, 1, 8, 3, 0, 1]],
      'LIGC'     : [301, 's'   , ' '],
      'PLIGM2'   : [378, 's'   , ' '],
      'LIGM2'    : [379, 's'   , ' '],
      'PLIG'     : [258, 's'   , ' '],
      'LIG'      : [259, 's'   , ' '],
      'PADIOM2'  : [227, 's'   , ' '],
      'ADIOM2'   : [228, 's'   , ' '],
      'PADIO'    : [167, 's'   , ' '],
      'ADIO'     : [168, 's'   , ' '],
      'PFET3'    : [165, 's'   , ' '],
      'PFET3M2'  : [225, 's'   , ' '],
      'SYNAPYL'  : [210, 's'   , ' '],
      'COUMARYL' : [150, 's'   , ' '],
      'PKETM2'   : [225, 's'   , ' '],
      'KETM2'    : [226, 's'   , ' '],
      'KET'      : [166, 's'   , ' '],
      'KETDM2'   : [208, 's'   , ' '],
      'KETD'     : [148, 's'   , ' '],
      'MGUAI'    : [154, 's'   , ' '],
      'PHENOL'   : [94 , 's'   , ' '],
      'C10H2M4'  : [244, 's'   , ' '],
      'C10H2M2'  : [182, 's'   , ' '],
      'C10H2'    : [122, 's'   , ' '],
      'CHAR'     : [120, 'char', ' '],
      'PC2H2'    : [26 , 's'   , ' '],
      'PCH2P'    : [14 , 's'   , ' '],
      'PCOS'     : [28 , 's'   , ' '],
      'PCOH'     : [28 , 's'   , ' '],
      'PCH2OH'   : [31 , 's'   , ' '],
      'PCHO'     : [29 , 's'   , ' '],
      'PCHOHP'   : [30 , 's'   , ' '],
      'PRLIGM2A' : [377, 's'   , ' '],
      'RLIGM2A'  : [378, 's'   , ' '],
      'RLIGM2B'  : [378, 's'   , ' '],
      'RLIGA'    : [258, 's'   , ' '],
      'RLIGB'    : [258, 's'   , ' '],
      'PRADIOM2' : [226, 's'   , ' '],
      'RADIOM2'  : [227, 's'   , ' '],
      'PRADIO'   : [166, 's'   , ' '],
      'RADIO'    : [167, 's'   , ' '],
      'PRKETM2'  : [224, 's'   , ' '],
      'RKETM2'   : [225, 's'   , ' '],
      'RKET'     : [165, 's'   , ' '],
      'PRFET3M2' : [224, 's'   , ' '],
      'PRFET3'   : [164, 's'   , ' '],
      'RPHENOL'  : [91 , 's'   , ' '],
      'RPHENOXM2': [152, 's'   , ' '],
      'RPHENOX'  : [90 , 's'   , ' '],
      'RCH3O'    : [31 , 'g'   , ' ', [1 , 3 , 1 ]],
      'CO'       : [28 , 'CO'  , ' ', [1 , 0 , 1 ]],
      'H2'       : [2  , 'g'   , ' ', [0 , 2 , 0 ]],
      'PCHP2'    : [13 , 's'   , ' '],
      'RCH3'     : [15 , 'g'   , ' ', [1 , 3 , 0 ]],
      'PH2'      : [2  , 's'   , ' '],
      'H2O'      : [18 , 'H2O' , ' ', [0 , 2 , 1 ], [0, 0, 0, 0, 0, 0, 0]],
      'C2H6'     : [30 , 'g'   , ' ', [2 , 6 , 0 ]],
      'PCH3'     : [15 , 's'   , ' '],
      'CH3CHO'   : [44 , 'g'   , ' ', [2 , 4 , 1 ]],
      'CO2'      : [44 , 'CO2' , ' ', [1 , 0 , 2 ]],
      'CH2CO'    : [42 , 'g'   , ' ', [2 , 2 , 1 ]],
      'OH'       : [17 , 'g'   , ' ', [0 , 1 , 1 ]],
      'C3H6'     : [42 , 'g'   , ' ', [3 , 6 , 0 ]],
      'C3H6O2'   : [74 , 'lt'  , ' ', [3 , 6 , 2 ], [0, 1, 0, 1, 1, 0, 0]],
      'C3H4O2'   : [72 , 'lt'  , ' ', [3 , 4 , 2 ], [1, 1, 0, 1, 0, 0, 0]],
      'RC3H7O2'  : [75 , 'lt'  , ' ', [3 , 7 , 2 ], [0, 0, 0, 0, 2, 0, 1]],
      'RC3H5O2'  : [73 , 'lt'  , ' ', [3 , 5 , 2 ], [0, 1, 0, 1, 1, 0, 0]],
      'RC3H3O'   : [55 , 'lt'  , ' ', [3 , 3 , 1 ], [1, 0, 0, 2, 0, 0, 0]],
      'PRLIGH'   : [435, 's'   , ' '],
      'PRLIGH2'  : [435, 's'   , ' '],
      'RMGUAI'   : [153, 's'   , ' '],
      'RLIGH'    : [436, 's'   , ' '],
      'PCOHP2'   : [29 , 's'   , ' '],
      'VADIOM2'  : [228, 't'   , 's', [11, 16, 5 ], [0, 3, 1, 2, 2, 2, 1]],
      'VKETM2'   : [226, 't'   , 's', [11, 14, 5 ], [1, 3, 1, 2, 1, 2, 1]],
      'VKETDM2'  : [208, 't'   , 's', [11, 12, 4 ], [1, 3, 3, 2, 0, 2, 0]],
      'VSYNAPYL' : [210, 't'   , 's', [11, 14, 4 ], [0, 3, 3, 2, 1, 2, 0]],
      'VMGUAI'   : [154, 't'   , 's', [8 , 10, 3 ], [0, 3, 0, 3, 0, 2, 0]],
      'VCOUMARYL': [150, 't'   , 'p', [9 , 10, 2 ], [0, 1, 3, 4, 1, 0, 0]],
      'VADIO'    : [168, 't'   , 'p', [9 , 12, 3 ], [0, 1, 1, 4, 2, 0, 1]],
      'VKET'     : [166, 't'   , 'p', [9 , 10, 3 ], [1, 1, 1, 4, 1, 0, 1]],
      'VKETD'    : [148, 't'   , 'p', [9 , 8 , 2 ], [1, 1, 3, 4, 0, 0, 0]],
      'VPHENOL'  : [94 , 't'   , 'p', [6 , 6 , 1 ], [0, 1, 0, 5, 0, 0, 0]],
      'C3H4O'    : [56 , 'lt'  , ' ', [3 , 4 , 1 ], [1, 0, 0, 2, 0, 0, 0]],
      'C3H8O2'   : [76 , 'lt'  , ' ', [3 , 8 , 2 ], [0, 0, 0, 0, 2, 0, 1]],
      'CH4'      : [16 , 'g'   , ' ', [1 , 4 , 0 ]]}
