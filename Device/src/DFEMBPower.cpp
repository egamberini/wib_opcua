
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

#include <DFEMBPower.h>
#include <DWIB.h>
#include <ASFEMBPower.h>

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
DFEMBPower::DFEMBPower (
    const Configuration::FEMBPower& config,
    Parent_DFEMBPower* parent
):
    Base_DFEMBPower( config, parent)

    /* fill up constructor initialization list here */
{
    /* fill up constructor body here */
}

/* sample dtr */
DFEMBPower::~DFEMBPower ()
{
}

/* delegates for cachevariables */



/* delegators for methods */
UaStatus DFEMBPower::callSet (
    OpcUa_Boolean femb0_on,
    OpcUa_Boolean femb1_on,
    OpcUa_Boolean femb2_on,
    OpcUa_Boolean femb3_on,
    OpcUa_Boolean cold,
    OpcUa_UInt32 stage,
    OpcUa_Boolean& success
)
{
    auto *as = getAddressSpaceLink();
    wib::ConfigurePower conf_req;
    conf_req.set_dc2dc_o1(as->getDc2dc_o1_setpoint());
    conf_req.set_dc2dc_o2(as->getDc2dc_o2_setpoint());
    conf_req.set_dc2dc_o3(as->getDc2dc_o3_setpoint());
    conf_req.set_dc2dc_o4(as->getDc2dc_o4_setpoint());
    conf_req.set_ldo_a0(as->getLdo_a0_setpoint());
    conf_req.set_ldo_a1(as->getLdo_a1_setpoint());
    wib::Status conf_rep;
    if (getParent()->wib.send_command(conf_req,conf_rep,10000)) {
        if (!conf_rep.success()) return OpcUa_Bad;
    } else {
        return OpcUa_Bad;
    }
    
    wib::PowerWIB req;
    req.set_femb0(femb0_on);
    req.set_femb1(femb1_on);
    req.set_femb2(femb2_on);
    req.set_femb3(femb3_on);
    req.set_cold(cold);
    req.set_stage(stage);
    wib::Status rep;
    if (getParent()->wib.send_command(req,rep,10000)) {
        success = rep.success();
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

void DFEMBPower::update()
{
	auto *as = getAddressSpaceLink();
	if (as->getConfigure() == OpcUa_True) {
		LOG(Log::INF) << "do configuration";
		sleep(1);
		as->setConfigure(OpcUa_False, OpcUa_Good);
	}
}

}
