
/*  © Copyright CERN, 2015. All rights not expressly granted are reserved.

    The stub of this file was generated by quasar (https://github.com/quasar-team/quasar/)

    Quasar is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public Licence as published by
    the Free Software Foundation, either version 3 of the Licence.
    Quasar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public Licence for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Quasar.  If not, see <http://www.gnu.org/licenses/>.


 */


#include <Configuration.hxx> // TODO; should go away, is already in Base class for ages

#include <DTimingEndpoint.h>
#include <DWIB.h>
#include <ASTimingEndpoint.h>

namespace Device
{
// 1111111111111111111111111111111111111111111111111111111111111111111111111
// 1     GENERATED CODE STARTS HERE AND FINISHES AT SECTION 2              1
// 1     Users don't modify this code!!!!                                  1
// 1     If you modify this code you may start a fire or a flood somewhere,1
// 1     and some human being may possible cease to exist. You don't want  1
// 1     to be charged with that!                                          1
// 1111111111111111111111111111111111111111111111111111111111111111111111111






// 2222222222222222222222222222222222222222222222222222222222222222222222222
// 2     SEMI CUSTOM CODE STARTS HERE AND FINISHES AT SECTION 3            2
// 2     (code for which only stubs were generated automatically)          2
// 2     You should add the implementation but dont alter the headers      2
// 2     (apart from constructor, in which you should complete initializati2
// 2     on list)                                                          2
// 2222222222222222222222222222222222222222222222222222222222222222222222222

/* sample ctr */
DTimingEndpoint::DTimingEndpoint (
    const Configuration::TimingEndpoint& config,
    Parent_DTimingEndpoint* parent
):
    Base_DTimingEndpoint( config, parent)

    /* fill up constructor initialization list here */
{
    /* fill up constructor body here */
}

/* sample dtr */
DTimingEndpoint::~DTimingEndpoint ()
{
}

/* delegates for cachevariables */



/* delegators for methods */
UaStatus DTimingEndpoint::callPoll (
    OpcUa_Boolean& success
)
{
    wib::GetTimingStatus req;
    wib::GetTimingStatus::TimingStatus rep;
    if (getParent()->wib.send_command(req,rep,1000)) {
        auto *as = getAddressSpaceLink();
        
        as->setLol_val(rep.lol_val(), OpcUa_Good);
        as->setLol_flg_val(rep.lol_flg_val(), OpcUa_Good);
        
        as->setLol_val(rep.los_val(), OpcUa_Good);
        as->setLol_flg_val(rep.los_flg_val(), OpcUa_Good);
        
        as->setEpt_status(rep.ept_status(), OpcUa_Good);
        
        success = true;
        return OpcUa_Good;
    } else {
        return OpcUa_Bad;
    }
}

// 3333333333333333333333333333333333333333333333333333333333333333333333333
// 3     FULLY CUSTOM CODE STARTS HERE                                     3
// 3     Below you put bodies for custom methods defined for this class.   3
// 3     You can do whatever you want, but please be decent.               3
// 3333333333333333333333333333333333333333333333333333333333333333333333333

void DTimingEndpoint::update()
{
    auto *as = getAddressSpaceLink();
    if (as->getPoll_period() > 0 && poll_timer.elapsed() > as->getPoll_period()) {
        poll_timer.reset();
        OpcUa_Boolean success;
        callPoll(success);
    }
}

}
