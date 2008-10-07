/*       Created   :  10/03/2008 08:22:01 PM
 *       Last Change: Tue Oct 07 09:00 PM 2008 CEST
 */

#include <string>
#include <iostream>
#include <nana.h>
#include <factory/factory.h>
#include "configuration.hpp"

#include <sdp_seriation_gen.hpp>

#include <boost/numeric/ublas/matrix.hpp>
using namespace boost::numeric::ublas;
using namespace std;

int main(int argc, char* argv[]){
	gCfg().parsecfg(argc,argv);

	typedef matrix<double,column_major> AdjMatCT;
	AdjMatCT adjmat(6,6);

	SDPSeriationGen walkgen;
	string sdp_wrapper_name          = gCfg().getString("sdp-wrapper");
	auto_ptr<SDPWrapper> sdp_wrapper = genericFactory<SDPWrapper>::instance().create(sdp_wrapper_name);
	walkgen.setSDPWrapper( sdp_wrapper );

	SeriationGen::SeriationT randwalk  = walkgen(adjmat);
}
