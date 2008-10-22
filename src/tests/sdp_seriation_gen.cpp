#define BOOST_TEST_MODULE sdp_ser_gen_test

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <sdp_wrapper.hpp>
#include <sdp_prob.hpp>
#include <sdp_seriation_gen.hpp>
#include <sdp_seriation_prob_gen.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <memory>
#include <factory/factory.h>
#include <configuration.hpp>
using namespace std;

struct Fixture{
	const int n;
	auto_ptr<SDPSeriationGen> sdpsergen;
	auto_ptr<SDPSeriationProbGen::AdjMatT> am;
	
	Fixture()
		:  n(6)
		 , am(new SDPSeriationProbGen::AdjMatT(n,n))
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			{
				(*am)(i,j) = ((i+j)%2>0)?1.0:1.0;
			}
		sdpsergen.reset(new SDPSeriationGen());
	}
	~Fixture(){
	}
};

void testSerGen(const char* sdpwrapper, SDPSeriationGen* sdpsergen, SDPSeriationProbGen::AdjMatT* adj){
	auto_ptr<SDPWrapper> wrap = genericFactory<SDPWrapper>::instance().create(sdpwrapper);
	wrap->configure();
	sdpsergen->setSDPWrapper(wrap);
	SeriationGen::SeriationT ser = (*sdpsergen)(*adj);
}

BOOST_FIXTURE_TEST_SUITE( suite, Fixture )

#ifdef HAVE_SDPA
BOOST_AUTO_TEST_CASE( testSDPA )
{
	gCfg().parsecfg(0,NULL);
	testSerGen("SDPAWrapper",sdpsergen.get(),am.get());
}
#endif
#ifdef HAVE_DSDP
BOOST_AUTO_TEST_CASE( testDSDP )
{
	gCfg().parsecfg(0,NULL);
	testSerGen("DSDPWrapper",sdpsergen.get(),am.get());
}
#endif
#ifdef HAVE_SDPLR
BOOST_AUTO_TEST_CASE( testSDPLR )
{
	gCfg().parsecfg(0,NULL);
	testSerGen("SDPLRWrapper",sdpsergen.get(),am.get());
}
#endif


BOOST_AUTO_TEST_SUITE_END()
