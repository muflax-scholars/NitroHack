/*	SCCS Id: @(#)artifact.c	3.0	88/07/27
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"

#ifdef NAMED_ITEMS

#include "artifact.h"

/* the artifacts (currently weapons only) */
static const struct artifact artilist[] = {

#define	    NO_ATTK	{ 0, 0, 0, 0 }

{ LONG_SWORD,	 "Excalibur",	(SPFX_NOGEN | SPFX_SEEK | SPFX_DEFN |
								SPFX_SEARCH), 0,
  { 0, AD_PHYS, 5, 10 }, { 0, AD_DRLI, 0, 0}, A_LAW, 'K' },

{ KATANA,	 "Snickersnee",	SPFX_RESTR, 0,
  { 0, AD_PHYS, 0, 8 }, NO_ATTK, A_LAW, 'S' },

/*	Ah, never shall I forget the cry, 
 *		or the shriek that shrieked he,
 *	As I gnashed my teeth, and from my sheath
 *		I drew my Snickersnee!
 *
 *		--Koko, Lord high executioner of Titipu
 *		  (From Sir W.S. Gilbert's "The Mikado")
 */

{ AXE,		 "Cleaver",	SPFX_RESTR, 0,
  { 0, AD_PHYS, 3, 12 }, NO_ATTK, A_CHAOS, 0 },

#ifdef TOLKIEN
{ ORCISH_DAGGER, "Grimtooth",	SPFX_RESTR, 0,
  { 0, AD_PHYS, 2, 6 }, NO_ATTK, A_CHAOS, 0 },
#else
{ DAGGER,	 "Grimtooth",	SPFX_RESTR, 0,
  { 0, AD_PHYS, 2, 6 }, NO_ATTK, A_CHAOS, 0 },
#endif

/*  Special purpose swords - various types */

{ TWO_HANDED_SWORD, "Orcrist",	SPFX_DFLAG2, M2_ORC,
  { 0, AD_PHYS, 5, 0 }, NO_ATTK, A_LAW, 'E' },

#ifdef TOLKIEN
{ ELVEN_DAGGER,	 "Sting",	(SPFX_WARN | SPFX_DFLAG2), M2_ORC,
  { 0, AD_PHYS, 5, 0 }, NO_ATTK, A_LAW, 0 },
#else
{ DAGGER,	 "Sting",	(SPFX_WARN | SPFX_DFLAG2), M2_ORC,
  { 0, AD_PHYS, 5, 0 }, NO_ATTK, A_LAW, 0 },
#endif

{ LONG_SWORD,	 "Frost Brand", (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN), 0,
  { 0, AD_COLD, 5, 0 }, { 0, AD_COLD, 0, 0 }, A_NEUTRAL, 0 },

{ LONG_SWORD,	 "Fire Brand",	(SPFX_RESTR | SPFX_ATTK | SPFX_DEFN), 0,
  { 0, AD_FIRE, 5, 0 }, { 0, AD_FIRE, 0, 0 }, A_NEUTRAL, 0 },

/* Stormbringer only has a 2 because it can drain a level, providing 8 more */
{ BROADSWORD,	 "Stormbringer", (SPFX_RESTR | SPFX_ATTK | SPFX_DEFN |
								SPFX_DRLI), 0,
  { 0, AD_DRLI, 5, 2 }, { 0, AD_DRLI, 0, 0 }, A_CHAOS, 0 },

{ LONG_SWORD,	 "Sunsword",	(SPFX_RESTR | SPFX_DFLAG1), M1_UNDEAD,
  { 0, AD_PHYS, 5, 0 }, NO_ATTK, A_LAW, 0 },

{ BROADSWORD,	 "Dragonbane",	(SPFX_RESTR | SPFX_DCLAS), S_DRAGON,
  { 0, AD_PHYS, 5, 0 }, NO_ATTK, A_NEUTRAL, 0 },

{ LONG_SWORD,	 "Demonbane",	(SPFX_RESTR | SPFX_DFLAG2), M2_DEMON,
  { 0, AD_PHYS, 5, 0 }, NO_ATTK, A_LAW, 0 },

/* A silver weapon would be appropriate, if we had one. */
{ LONG_SWORD,	 "Werebane",	(SPFX_RESTR | SPFX_DFLAG1), M1_WERE,
  { 0, AD_PHYS, 5, 0 }, NO_ATTK, A_LAW, 0 },

{ LONG_SWORD,	 "Giantslayer", (SPFX_RESTR | SPFX_DFLAG2), M2_GIANT,
  { 0, AD_PHYS, 5, 0 }, NO_ATTK, A_NEUTRAL, 0 },

/* Another interesting weapon would be the dwarven hammer or axe with the
 * boomerang-like power of returning to the wielder's hand, if the code
 * were written to add such an ability.
 */
{ WAR_HAMMER, "Ogresmasher",	(SPFX_RESTR | SPFX_DCLAS), S_OGRE,
  { 0, AD_PHYS, 5, 0 }, NO_ATTK, A_LAW, 0 },

{ WAR_HAMMER, "Mjollnir",	(SPFX_RESTR | SPFX_ATTK),  0,
  { 0, AD_ELEC, 5, 24 }, NO_ATTK, A_LAW, 'V' }, /* Mjo:llnir */

{ MORNING_STAR,	 "Trollsbane", (SPFX_RESTR | SPFX_DCLAS), S_TROLL,
  { 0, AD_PHYS, 5, 0 }, NO_ATTK, A_LAW, 0 },

/*	ARRAY TERMINATOR	*/
{ 0,  "", 0, 0, NO_ATTK, NO_ATTK, 0, 0 }
};

void
mkartifact(otmp1)
struct obj **otmp1;
{
	register const struct artifact *artif;
	register struct obj *otmp = *otmp1;
	register int n = 0;

	for(artif = artilist; artif->otyp; artif++)
	    if(otmp->otyp == artif->otyp && !(artif->spfx & SPFX_NOGEN)) n++;

	if (n) {
		n = rnd(n);
		for(artif = artilist; artif->otyp && n > 0; ) {
		    if(otmp->otyp == artif->otyp && !(artif->spfx & SPFX_NOGEN)) n--;
		    if (n>0) artif++;
		}

		if(artif->otyp) *otmp1 = oname(otmp, artif->name, 0);
	}
}

static struct artifact *
get_artifact(otmp)
struct obj *otmp;
{
	register const struct artifact *artif;

	if(otmp)
	    if(strlen(ONAME(otmp)))
		for(artif = artilist; artif->otyp; artif++)
		    if(artif->otyp == otmp->otyp &&
		       !strcmp(ONAME(otmp), artif->name))
			    return((struct artifact *)artif);
	return((struct artifact *)0);
}

boolean
is_artifact(otmp)
struct obj *otmp;
{
	return(get_artifact(otmp) != (struct artifact *)0);
}

boolean
spec_ability(otmp, abil)
struct obj *otmp;
unsigned abil;
{
	struct artifact *arti = get_artifact(otmp);
	
	return(arti && (arti->spfx & abil));
}

int
restr_name(otmp, name)	/* returns 1 if name is restricted for otmp->otyp */
register struct obj *otmp;
register char	*name;
{
	register const struct artifact *artif;

	if(!strlen(name)) return(0);

	for(artif = artilist; artif->otyp; artif++)
	    if(artif->otyp == otmp->otyp)
		if(artif->spfx & (SPFX_NOGEN | SPFX_RESTR))
		    if(!strcmp(artif->name, name)) return(1);

	return(0);
}

# if defined(THEOLOGY) && defined(ALTARS)
struct obj *
mk_aligned_artifact(align)
unsigned align;
{
	register const struct artifact *artif;
	register struct obj *otmp;
	register int n = 0;

	for(artif = artilist; artif->otyp; artif++)
	    if(align == artif->align && !(artif->spfx & SPFX_NOGEN))
		if (pl_character[0] == artif->class) {
		    n=0; break;
		} else n++;
	if (n) {
		n = rnd(n);
		for(artif = artilist; artif->otyp && n > 0; ) {
		    if(align == artif->align && !(artif->spfx & SPFX_NOGEN))
			n--;
		    if (n > 0) artif++;
		}
	}
	if(artif->otyp) {
		otmp = mksobj((int)artif->otyp, FALSE);
		otmp = oname(otmp, artif->name, 0);
		return (otmp);
	}
	return ((struct obj *) 0);
}
# endif

int
defends(adtyp, otmp)
register int adtyp;
register struct obj *otmp;
{
	register struct artifact *weap;

	if(weap = get_artifact(otmp))
		return(weap->defn.adtyp == adtyp);
	return(0);
}

static int
spec_applies(weap, ptr)
register struct artifact *weap;
struct permonst *ptr;
{
	if(!(weap->spfx & (SPFX_DBONUS | SPFX_ATTK)))
	    return(1);

	if(weap->spfx & SPFX_DMONS)
	    return((ptr == &mons[(int)weap->mtype]));
	else if(weap->spfx & SPFX_DCLAS)
	    return((weap->mtype == ptr->mlet));
	else if(weap->spfx & SPFX_DFLAG1)
	    return((ptr->mflags1 & weap->mtype) != 0L);
	else if(weap->spfx & SPFX_DFLAG2)
	    return((ptr->mflags2 & weap->mtype) != 0L);
	else if(weap->spfx & SPFX_ATTK) {
	    switch(weap->attk.adtyp) {
		case AD_FIRE:	return(!resists_fire(ptr));
		case AD_COLD:	return(!resists_cold(ptr));
		case AD_ELEC:	return(!resists_elec(ptr));
		case AD_DRLI:	return(!resists_drli(ptr));
		case AD_STON:	return(!resists_ston(ptr));
		default:	impossible("Weird special attack for '%s'",
					   weap->name);
	    }
	}
	return(0);
}

int
spec_abon(otmp, ptr)
struct obj *otmp;
struct permonst *ptr;
{
	register struct artifact *weap;

	if((weap = get_artifact(otmp)))
		if(spec_applies(weap, ptr))
		    return((weap->attk.damn) ? rnd((int)weap->attk.damn) : 0);
	return(0);
}

int
spec_dbon(otmp, ptr, tmp)
register struct obj *otmp;
register struct permonst *ptr;
register int	tmp;
{
	register struct artifact *weap;

	if((weap = get_artifact(otmp)))
		if(spec_applies(weap, ptr))
		    return((weap->attk.damd) ? rnd((int)weap->attk.damd) : tmp);
	return(0);
}
#endif /* NAMED_ITEMS */
