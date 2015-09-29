/*
 * Copyright (C) 2005-2008 MaNGOS <http://www.mangosproject.org/>
 *
 * Copyright (C) 2008 Trinity <http://www.trinitycore.org/>
 *
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

#ifndef _THREATMANAGER
#define _THREATMANAGER

#include "Common.h"
#include "SharedDefines.h"
#include "Reference.h"
#include "UnitEvents.h"

#include <list>

//==============================================================

class Unit;
class Creature;
class ThreatManager;
class SpellInfo;

//==============================================================
// Class to calculate the real threat based

class ThreatCalcHelper
{
    public:
        static float calcThreat(Unit* pHatedUnit, Unit* pHatingUnit, float threat, SpellSchoolMask schoolMask = SPELL_SCHOOL_MASK_NORMAL, SpellInfo const *threatSpell = NULL);
};

//==============================================================

class HostileReference : public Reference<Unit, ThreatManager>
{
    private:
        float iThreat;
        float iTempThreatModifyer;                          // used for taunt
        uint64 iUnitGuid;
        bool iOnline;
        bool iAccessible;
    private:
        // Inform the source, that the status of that reference was changed
        void fireStatusChanged(const ThreatRefStatusChangeEvent& pThreatRefStatusChangeEvent);

    public:
        Unit* getSourceUnit();
        HostileReference(Unit* pUnit, ThreatManager *pThreatManager, float pThreat);

        //=================================================
        void addThreat(float pMod);

        void setThreat(float pThreat) { addThreat(pThreat - getThreat()); }

        void addThreatPercent(int32 pPercent) { float tmpThreat = iThreat; tmpThreat = tmpThreat * (pPercent+100) / 100; addThreat(tmpThreat-iThreat); }

        float getThreat() const { return iThreat; }

        bool isOnline() const { return iOnline; }

        // The Unit might be in water and the creature can not enter the water, but has range attack
        // in this case online = true, but accessible = false
        bool isAccessible() const { return iAccessible; }

        // used for temporary setting a threat and reducting it later again.
        // the threat modification is stored
        void setTempThreat(float pThreat) { iTempThreatModifyer = pThreat - getThreat(); if(iTempThreatModifyer != 0.0f) addThreat(iTempThreatModifyer);  }

        void resetTempThreat()
        {
            if(iTempThreatModifyer != 0.0f)
            {
                addThreat(-iTempThreatModifyer);  iTempThreatModifyer = 0.0f;
            }
        }

        float getTempThreatModifyer() { return iTempThreatModifyer; }

        //=================================================
        // check, if source can reach target and set the status
        void updateOnlineStatus();

        void setOnlineOfflineState(bool pIsOnline);

        void setAccessibleState(bool pIsAccessible);
        //=================================================

        bool operator ==(const HostileReference& pHostileReference) const { return pHostileReference.getUnitGuid() == getUnitGuid(); }

        //=================================================

        uint64 getUnitGuid() const { return iUnitGuid; }

        //=================================================
        // reference is not needed anymore. realy delete it !

        void removeReference();

        //=================================================

        HostileReference* next() { return ((HostileReference* ) Reference<Unit, ThreatManager>::next()); }

        //=================================================

        // Tell our refTo (target) object that we have a link
        void targetObjectBuildLink();

        // Tell our refTo (taget) object, that the link is cut
        void targetObjectDestroyLink();

        // Tell our refFrom (source) object, that the link is cut (Target destroyed)
        void sourceObjectDestroyLink();
};

//==============================================================
class ThreatManager;

class ThreatContainer
{
    private:
        std::list<HostileReference*> iThreatList;
        bool iDirty;
    protected:
        friend class ThreatManager;

        void remove(HostileReference* pRef) { iThreatList.remove(pRef); }
        void addReference(HostileReference* pHostileReference) { iThreatList.push_back(pHostileReference); }
        void clearReferences();
        // Sort the list if necessary
        void update();
    public:
        ThreatContainer() { iDirty = false; }
        ~ThreatContainer() { clearReferences(); }

        HostileReference* addThreat(Unit* pVictim, float pThreat);
        
        //modify threat for victim. Do not remove from threat list in any case
        void modifyThreatPercent(Unit *pVictim, int32 percent);

        HostileReference* selectNextVictim(Creature* pAttacker, HostileReference* pCurrentVictim);

        void setDirty(bool pDirty) { iDirty = pDirty; }

        bool isDirty() { return iDirty; }

        bool empty() { return(iThreatList.empty()); }

        HostileReference* getMostHated() { return iThreatList.empty() ? NULL : iThreatList.front(); }

        HostileReference* getReferenceByTarget(Unit* pVictim);

        std::list<HostileReference*>& getThreatList() { return iThreatList; }
};

//=================================================

class ThreatManager
{
    private:
        HostileReference* iCurrentVictim;
        Unit* iOwner;
        ThreatContainer iThreatContainer;
        ThreatContainer iThreatOfflineContainer;

        void _addThreat(Unit* target, float threat);
    public:
        explicit ThreatManager(Unit *pOwner);

        ~ThreatManager() { clearReferences(); }

        void clearReferences();
        void clearCurrentVictim() { iCurrentVictim = nullptr; }

        void addThreat(Unit* pVictim, float threat, SpellSchoolMask schoolMask = SPELL_SCHOOL_MASK_NORMAL, SpellInfo const *threatSpell = NULL);
        //modify threat for victim. Do not remove from threat list in any case
        void modifyThreatPercent(Unit *pVictim, int32 pPercent);

        float getThreat(Unit *pVictim, bool pAlsoSearchOfflineList = false);

        bool isThreatListEmpty() { return iThreatContainer.empty();}

        bool processThreatEvent(const UnitBaseEvent* pUnitBaseEvent);

        HostileReference* getCurrentVictim() { return iCurrentVictim; }

        Unit*  GetOwner() { return iOwner; }

        Unit* getHostilTarget();

        void tauntApply(Unit* pTaunter);
        void tauntFadeOut(Unit *pTaunter);
        
        void detauntApply(Unit* pDetaunter);
        void detauntFadeOut(Unit* pDetaunter);

        void setCurrentVictim(HostileReference* pHostileReference);

        void setDirty(bool pDirty) { iThreatContainer.setDirty(pDirty); }

        // methods to access the lists from the outside to do sume dirty manipulation (scriping and such)
        // I hope they are used as little as possible.
        inline std::list<HostileReference*>& getThreatList() { return iThreatContainer.getThreatList(); }
        inline std::list<HostileReference*>& getOfflieThreatList() { return iThreatOfflineContainer.getThreatList(); }
        inline ThreatContainer& getOnlineContainer() { return iThreatContainer; }
        inline ThreatContainer& getOfflineContainer() { return iThreatOfflineContainer; }
};

//=================================================
#endif

