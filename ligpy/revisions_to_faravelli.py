"""
This module contains the code to implement most of the changes we made to
the Faravelli et al. scheme.  The current version of `ligpy.py` makes use
of our updated kinetic scheme, so there should not be any need to run this
module again unless you want to modify the changes we made.  See our
publication for details on the following changes.

**************************************************************

Notes & changes to the Faravelli scheme:
 - The following species show up in the Faravelli reaction mechanism as
   reactants, but they are never produced as products so the reactions they
   are involved in will never proceed: LIGB, RFET3, RFET3M2, RLINH
 - The density of the condensed phase is assumed constant in the range of
   700-800 kg/m^3 (stated in Faravelli paper).  I have used 750 here.
   -- From correspondence with the authors they now use a value of 850 kg/m^3,
      but I have not adopted this value as it is not published.
 - typo: I changed "LIGB" in the recombination reactions to RLIGB.
 - typo: I changed "RLINH" in the recombination reactions to RLIGH.
 - typo: I changed "RFET3M2" in the recominbation reactions to PRFET3M2.
 - typo: I changed "RFET3" in the recombination reactions to PRFET3.
 - typo: I corrected the spelling from "RFHENOX" to "RPHENOX" in one of
   the initiation reactions.

 - Mass is not entirely conserved because the loss of hydrogen radicals in the
   initiation reactions is not accounted for (in both Faravelli and my model).

 - I am removing the reactions PLIG -> PRLINES and PLIGM2 -> PRLIN because
   once they form they don't react all the way and are still present at the
   end of the scheme, and I don't know what they become after H-abstraction.
 - Add species (C3H8O2, C3H4O, CH4) that are created during H-abstraction.

 New reactions added to the Faravelli scheme:
 - Add reactions to create LIG* from PLIG* species.  These reactions do not
   exist in the model but they are necessary in order for some species to
   ever be created (LIG,LIGM2,LIGH,RLIGH,RLIGM2B,RLIGA,RLIGB,LIGB).
 - The kinetic rate parameters for these reactions are determined by DFT
   calculations for the initial fission reaction, which is assumed to be the
   rate limiting step.  Addition of an H atom is assumed to happen
   spontaneously.  See the Read_enthalpies notebook for those calculations.
 - Add reactions for LIGO and LIGC
 - Add radical recombinations (PRADIO, PRADIOM2).
   Their kinetic parameters are the same as the non-P reactions.
 - Add a char devolatilization reaction (PCHO).  It's kinetic parameters are
   the same as PCOH -> CO
"""

# paths to the files referenced in this module
file_reactionlist = 'data/faravelli_reactionlist.dat'
file_rateconstantlist = 'data/faravelli_rateconstantlist.dat'
file_completereactionlist = 'data/complete_reaction_list.dat'
file_completerateconstantlist = 'data/complete_rateconstant_list.dat'

# New reactions to write to the complete_reactions_list.dat file
addrxns = ['-1_PLIGH,1_LIGH',
           '-1_PLIGC,1_LIGC',
           '-1_PLIGO,1_LIGO',
           '-1_LIGO,1_LIGM2,1_CO2',
           '-1_LIGC,1_LIG,1_CH2CO',
           '-2_PRADIO,1_PCOH,1_PCOS,2_PCH2OH,2_PCHP2,2_PCHOHP,1_C10H2,2_PH2,1_H2',
           '-2_PRADIOM2,2_PCOH,2_PCH2OH,2_PCHP2,2_PCHOHP,1_PH2,1_C10H2M4',
           '-1_PCHO,1_CO'
           ]
# Rate constant parameters to add to the complete_rateconstant_list.dat file
addparams = ['1E13 0 154812',
             '1E13 0 168458',
             '1E13 0 154812',
             '1E9 0 108836',
             '1E8 0 121394',
             '3.16E7 0 92092',
             '3.16E7 0 83720',
             '1E7 0 138138'
             ]
# Write the new reactions & parameters
open(file_completereactionlist, 'w').write(open(file_reactionlist, 'r').read())
for line in addrxns:
    open(file_completereactionlist, 'a').write(line+'\n')

open(file_completerateconstantlist, 'w').write(open(file_rateconstantlist, 'r')
                                               .read())
for line in addparams:
    open(file_completerateconstantlist, 'a').write(line+'\n')


# Create a dictionary to assign an index to each species in the kinetic scheme.
# file_completereactionlist lists all of the reactions in the scheme.
# Each line in the file is one reaction.  The stoichiometric coefficient is
# listed first, followed by an underscore and then the species name.
# A comma follows the species name and then the next
# stoichiometric cofficient_species name, etc.
specieslist = []
for line in open(file_completereactionlist, 'r').readlines():
    for spec in line.split(','):
        # If the species has already been added to the list then move on.
        if spec.split('_')[1].split()[0] in specieslist:
            continue
        else:
            specieslist.append(spec.split('_')[1].split()[0])

# Add these species because I assume they are what R* becomes after
# H-abstraction but they are not in the Faravelli list.
specieslist.append('C3H8O2')
specieslist.append('C3H4O')
specieslist.append('CH4')
specieslist.sort()

# Generate the H-abstraction reactions...
# This block identifies which species are H-abstracting radicals and builds a
# dictionary with these as keys. The values of the dictionary are the species
# that these radicals become after H-abstraction.
radicallist = {}
for species in specieslist:
    if 'R'in species[0:2]:
        # Names post-abstraction species the same as parent-R
        radicallist[species] = species[0:2].replace('R', '')+species[2:]
# These need to be manually corrected because they are written for the
# radical at specific positions so the A/B needs to be removed.
radicallist['RLIGM2A'] = 'LIGM2'
radicallist['RLIGM2B'] = 'LIGM2'
radicallist['RLIGA'] = 'LIG'
radicallist['RLIGB'] = 'LIG'
radicallist['PRLIGM2A'] = 'PLIGM2'
# These C* species need to be specified because they don't follow the same
# naming convention as the other species.
radicallist['RCH3'] = 'CH4'
radicallist['RCH3O'] = 'CH3OH'
radicallist['RC3H7O2'] = 'C3H8O2'
radicallist['RC3H5O2'] = 'C3H6O2'
radicallist['RC3H3O'] = 'C3H4O'
# Manually specify OH because it is not named as a radical in the paper.
radicallist['OH'] = 'H2O'
# The following species are radicals but they are not H-abstracting radicals,
# so must be removed from the list.
del radicallist["RLIGH"]
del radicallist["RPHENOX"]
del radicallist["RPHENOXM2"]
del radicallist["PRLIGM2A"]
del radicallist["RKETM2"]
del radicallist["PRLIGH2"]

# These are the published H-abstraction reactions, every H-abstracting radical
# undergoes all of these reactions.
Habstrxns = ['-1_Radical,-1_LIGH,1_RadH,1_RLIGH',
             '-1_Radical,-1_PLIGH,1_RadH,1_PRLIGH2',
             '-1_Radical,-1_PLIGM2,1_RadH,1_PRLIGM2A',
             '-1_Radical,-1_LIGM2,1_RadH,1_RLIGM2A',
             '-1_Radical,-1_LIGM2,1_RadH,1_RLIGM2B',
             '-1_Radical,-1_PFET3M2,1_RadH,1_PRFET3M2',
             '-1_Radical,-1_ADIOM2,1_RadH,1_RADIOM2',
             '-1_Radical,-1_KETM2,1_RadH,1_RKETM2',
             '-1_Radical,-1_C10H2,1_RadH,0.5_C10H2,0.5_CHAR',
             '-1_Radical,-1_LIG,1_RadH,1_RLIGA',
             '-1_Radical,-1_LIG,1_RadH,1_RLIGB',
             '-1_Radical,-1_PFET3,1_RadH,1_PRFET3',
             '-1_Radical,-1_ADIO,1_RadH,1_RADIO',
             '-1_Radical,-1_KET,1_RadH,1_RKET'
             ]
# This is the "H type" column from the H-abstraction reactions.
# These are factors to be multiplied by A from the reference
# kinetic parameters for each radical.  The entries here are ['A E',...].
Htype = ['2 4186',
         '2 4186',
         '2 4186',
         '1 4186',
         '1 4186',
         '2 4186',
         '1 4186',
         '1 4186',
         '1 -20930',
         '1 4186',
         '1 4186',
         '2 4186',
         '1 4186',
         '1 4186'
         ]
# This is a dictionary of the reference kinetic parameters of H-abstracting
# radicals.  The values are 'A n E'.
ref = {}
for radical in radicallist:
    ref[radical] = None
ref['OH'] = '10**9.5 0 14651'
ref['RCH3'] = '10**8.5 0 48139'
ref['RCH3O'] = '10**8.5 0 33069'
ref['RKET'] = ref['RPHENOL'] = '10**8.5 0 54418'
ref['RLIGA'] = ref['RLIGB'] = '10**8 0 56511'
ref['RC3H7O2'] = '10**8 0 62790'
ref['RC3H5O2'] = '10**8 0 71162'
ref['RC3H3O'] = '10**8 0 83720'
ref['PRADIO'] = '10**8 0 46046'
ref['PRLIGH'] = ref['PRADIOM2'] = '10**8.5 0 41860'
# Populate the last line of Faravelli's Appendix B
for radical in radicallist:
    if ref[radical] is None:
        ref[radical] = '10**8 0 54418'

Habstractionlist = []      # to write the H-abstraction rxns to a file later
Habstractionratelist = []  # rate parameters corresponding to the H-abs rxns
for i, rxn in enumerate(Habstrxns):
    for radicalspecies in radicallist:
        Habstractionlist.append(rxn.replace('Radical', str(radicalspecies))
                                .replace('RadH',
                                         str(radicallist[radicalspecies]))
                                )
        Habstractionratelist.append(Htype[i].split(' ')[0] + '*' +
                                    ref[radicalspecies].split(' ')[0] + ' ' +
                                    ref[radicalspecies].split(' ')[1] + ' ' +
                                    ref[radicalspecies].split(' ')[2] + '-' +
                                    Htype[i].split(' ')[1]
                                    )
# The (-) sign in the above line is correct because E in ref is positive
# (compared to neg in the published appendix).

# Write all of the H-abstraction rxns to the completereactionlist
for reaction in Habstractionlist:
    open(file_completereactionlist, 'a').write(reaction+'\n')
# Write the H-abstraction rxn rate parameters to the completerateconstantlist
for parameters in Habstractionratelist:
    open(file_completerateconstantlist, 'a').write(parameters+'\n')
