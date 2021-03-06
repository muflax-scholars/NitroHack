# dat/CMakeLists.txt: generate game data files

set (LEVEL_DESCRIPTIONS
    ${LNH_DAT}/Arch.des
    ${LNH_DAT}/Barb.des
    ${LNH_DAT}/bigroom.des
    ${LNH_DAT}/castle.des
    ${LNH_DAT}/Caveman.des
    ${LNH_DAT}/endgame.des
    ${LNH_DAT}/gehennom.des
    ${LNH_DAT}/Healer.des
    ${LNH_DAT}/Knight.des
    ${LNH_DAT}/knox.des
    ${LNH_DAT}/medusa.des
    ${LNH_DAT}/mines.des
    ${LNH_DAT}/Monk.des
    ${LNH_DAT}/oracle.des
    ${LNH_DAT}/Priest.des
    ${LNH_DAT}/Ranger.des
    ${LNH_DAT}/Rogue.des
    ${LNH_DAT}/Samurai.des
    ${LNH_DAT}/sokoban.des
    ${LNH_DAT}/Tourist.des
    ${LNH_DAT}/tower.des
    ${LNH_DAT}/Valkyrie.des
    ${LNH_DAT}/Wizard.des
    ${LNH_DAT}/yendor.des 
    )

# the compiled levels that will be added to nhdat
set (COMPILED_LEVELS
    air.lev      Arc-fila.lev Arc-filb.lev Arc-goal.lev
    Arc-loca.lev Arc-strt.lev asmodeus.lev astral.lev
    baalz.lev    Bar-fila.lev Bar-filb.lev Bar-goal.lev
    Bar-loca.lev Bar-strt.lev bigrm-1.lev  bigrm-2.lev
    bigrm-3.lev  bigrm-4.lev  bigrm-5.lev  castle.lev
    Cav-fila.lev Cav-filb.lev Cav-goal.lev Cav-loca.lev
    Cav-strt.lev earth.lev    fakewiz1.lev fakewiz2.lev
    fire.lev     Hea-fila.lev Hea-filb.lev Hea-goal.lev
    Hea-loca.lev Hea-strt.lev juiblex.lev  Kni-fila.lev
    Kni-filb.lev Kni-goal.lev Kni-loca.lev Kni-strt.lev
    knox.lev     medusa-1.lev medusa-2.lev minefill.lev
    minend-1.lev minend-2.lev minend-3.lev minetn-1.lev
    minetn-2.lev minetn-3.lev minetn-4.lev minetn-5.lev
    minetn-6.lev minetn-7.lev Mon-fila.lev Mon-filb.lev
    Mon-goal.lev Mon-loca.lev Mon-strt.lev oracle.lev
    orcus.lev    Pri-fila.lev Pri-filb.lev Pri-goal.lev
    Pri-loca.lev Pri-strt.lev Ran-fila.lev Ran-filb.lev
    Ran-goal.lev Ran-loca.lev Ran-strt.lev Rog-fila.lev
    Rog-filb.lev Rog-goal.lev Rog-loca.lev Rog-strt.lev
    Sam-fila.lev Sam-filb.lev Sam-goal.lev Sam-loca.lev
    Sam-strt.lev sanctum.lev  soko1-1.lev  soko1-2.lev
    soko2-1.lev  soko2-2.lev  soko3-1.lev  soko3-2.lev
    soko4-1.lev  soko4-2.lev  Tou-fila.lev Tou-filb.lev
    Tou-goal.lev Tou-loca.lev Tou-strt.lev tower1.lev
    tower2.lev   tower3.lev   Val-fila.lev Val-filb.lev
    Val-goal.lev valley.lev   Val-loca.lev Val-strt.lev
    water.lev    wizard1.lev  wizard2.lev  wizard3.lev
    Wiz-fila.lev Wiz-filb.lev Wiz-goal.lev Wiz-loca.lev
    Wiz-strt.lev
    )

set (NHDAT_SRC dungeon quest.dat rumors oracles ${COMPILED_LEVELS} history data)

configure_file(${LNH_DAT}/history history COPYONLY)

get_property(MAKEDEFS_BIN TARGET makedefs PROPERTY LOCATION)
get_property(DGN_COMP_BIN TARGET dgn_comp PROPERTY LOCATION)
get_property(LEV_COMP_BIN TARGET lev_comp PROPERTY LOCATION)
get_property(DLB_BIN TARGET dlb PROPERTY LOCATION)


# makedefs -d
add_custom_command (OUTPUT data
                    COMMAND ${MAKEDEFS_BIN}
                    ARGS -d ${LNH_DAT}/data.base data
                    DEPENDS makedefs)
# makedefs -e 
add_custom_command (OUTPUT dungeon.pdf
                    COMMAND ${MAKEDEFS_BIN}
                    ARGS -e ${LNH_DAT}/dungeon.def dungeon.pdf
                    DEPENDS makedefs)
# makedefs -q
add_custom_command (OUTPUT quest.dat
                    COMMAND ${MAKEDEFS_BIN}
                    ARGS -q ${LNH_DAT}/quest.txt quest.dat
                    DEPENDS makedefs)
# makedefs -r
add_custom_command (OUTPUT rumors
                    COMMAND ${MAKEDEFS_BIN}
                    ARGS -r ${LNH_DAT}/rumors.tru
                            ${LNH_DAT}/rumors.fal rumors
                    DEPENDS makedefs)
# makedefs -h
add_custom_command (OUTPUT oracles
                    COMMAND ${MAKEDEFS_BIN}
                    ARGS -h ${LNH_DAT}/oracles.txt oracles
                    DEPENDS makedefs)

add_custom_command (OUTPUT dungeon
                    COMMAND ${DGN_COMP_BIN}
                    ARGS ${LNH_DAT_GEN}/dungeon.pdf
                    DEPENDS dungeon.pdf)

add_custom_command (OUTPUT nhdat
                    COMMAND ${LEV_COMP_BIN} ${LEVEL_DESCRIPTIONS}
                    COMMAND ${DLB_BIN}
                    ARGS cf nhdat ${NHDAT_SRC}
                    DEPENDS lev_comp dungeon quest.dat rumors oracles data ${LEVEL_DESCRIPTIONS})

# pseudo-target: depend on all other generated data
add_custom_target (nitrohack_data_files ALL
                   DEPENDS nhdat)

install(FILES ${LNH_DAT_GEN}/nhdat
        DESTINATION ${DATADIR})
install(FILES license
        DESTINATION ${DATADIR})
