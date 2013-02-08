// Copyright Andrew Little 2005

// See QUAN_ROOT/quan_matters/index.html for documentation.
#define BOOST_PQS_USE_BOOST_TYPEOF_BINARY_OPERATION

#include <quan_matters/test/simple_test.hpp>
#include <quan/out/pressure.hpp>
#include <quan/meta/eval_rational.hpp>
#include <quan_matters/test/utility/eval_exponent.hpp>
#include <utility>
/*
    check values are correct when assigning
    a t1_quantity with another of different units, both coherent and incoherent
    and optionally value_type

    Also checks t1_quantity::numeric_value();
    exceptions on out of range double to int value_type

    postcondition of a conversion: 

According to t1_quantity spec docs,
after conversions (where rhs is the source and 'this' is the target):

this->numeric_value() += ( rhs.numeric_value() 
* quan::meta::eval_exponent< 
    binary_op<
        typeof(rhs)::unit::exponent,
        minus,
        typeof(*this)::unit::exponent
    >::type
>() * rhs.units.multiplier / this->units.multiplier ).

*/


//add
    //incoherent, floating-pt --> coarser-grained units coherent, floating-pt
    //incoherent, floating-pt --> coarser-grained units coherent, int
    //incoherent, floating-pt --> coarser-grained units coherent, floating-pt
    //incoherent, floating-pt --> coarser-grained units coherent, floating-pt

namespace {

#define QUAN_TEST_FUN(fun) void fun ();

    QUAN_TEST_FUN(conv_coh_gt_coh)
    QUAN_TEST_FUN(conv_coh_gt_coh_int)
    QUAN_TEST_FUN(conv_coh_less_coh)
    QUAN_TEST_FUN(conv_coh_less_coh_int)
    QUAN_TEST_FUN(conv_coh_to_gt_inco)
    QUAN_TEST_FUN(conv_coh_to_gt_inco_int)
    QUAN_TEST_FUN(coh_to_less_inco)
    QUAN_TEST_FUN(coh_to_less_inco_int)
    QUAN_TEST_FUN(incoh_gt_inco)
    QUAN_TEST_FUN(incoh_gt_inco_int)
    QUAN_TEST_FUN(incoh_less_inco)
    QUAN_TEST_FUN(incoh_less_inco_int)

#undef QUAN_TEST_FUN
}

void minus_assignment_test()
{
#define QUAN_TEST_FUN(fun) fun();
    QUAN_TEST_FUN(conv_coh_gt_coh)
    QUAN_TEST_FUN(conv_coh_gt_coh_int)
    QUAN_TEST_FUN(conv_coh_less_coh)
    QUAN_TEST_FUN(conv_coh_less_coh_int)
    QUAN_TEST_FUN(conv_coh_to_gt_inco)
    QUAN_TEST_FUN(conv_coh_to_gt_inco_int)
    QUAN_TEST_FUN(coh_to_less_inco)
    QUAN_TEST_FUN(coh_to_less_inco_int)
    QUAN_TEST_FUN(incoh_gt_inco)
    QUAN_TEST_FUN(incoh_gt_inco_int)
    QUAN_TEST_FUN(incoh_less_inco)
    QUAN_TEST_FUN(incoh_less_inco_int)
#undef QUAN_TEST_FUN
}
namespace {

   template < typename To, typename From>
   std::pair<bool,To> conv_impl(From const & rhs, QUAN_FLOAT_TYPE eps = QUAN_FLOAT_TYPE(0))
   {

       typedef  typename quan::meta::get_conversion_factor<typename From::unit>::type from_conv_factor;
       typedef  typename quan::meta::get_exponent<from_conv_factor>::type from_exp;
       typedef  typename quan::meta::get_multiplier<from_conv_factor>::type from_multiplier;
       
       typedef typename quan::meta::get_conversion_factor<typename To::unit>::type to_conv_factor;
       typedef typename quan::meta::get_exponent<to_conv_factor>::type to_exp;
       typedef typename quan::meta::get_multiplier<to_conv_factor>::type to_multiplier;
       
      //  sort  exponent functor
       typedef typename quan::meta::binary_op<
           from_exp,
           quan::meta::minus,
           to_exp
       >::type exponent;

       typedef quan::meta::eval_exponent<exponent> exp_eval;

       // sort multiplier functors
       typedef quan::meta::eval_rational<
          from_multiplier
       > from_mux_rat;
       typedef quan::meta::eval_rational<
           to_multiplier
       > to_mux_rat;

       // get promoted value_type for calculation
       typedef typename quan::meta::arithmetic_promote<
           typename from_mux_rat::result_type,
           typename to_mux_rat::result_type
       >::type prom1;

       typedef typename quan::meta::if_<
           quan::meta::eq_one<from_multiplier>,
           QUAN_INT32,
           QUAN_FLOAT_TYPE
       >::type min_rational;

       typedef typename quan::meta::arithmetic_promote<
            min_rational,prom1
       >::type rat_eval_type;

       from_mux_rat from_mux_;
       to_mux_rat to_mux_;

       typename exp_eval::eval  exp;
       typename exp_eval::result_type exp_result = exp();
       rat_eval_type from_mux = from_mux_();
       rat_eval_type to_mux = to_mux_();
       
   // comparisons provide automatic promotions
   // that will give erroneous results,
   // so convert From.numeric_value() from source value_type to target value_type 
   // before comparison. conversion must usenumeric converter 
   // using round-nearest algorithm.
       typename quan::quantity_traits::value_type_converter<
           typename To::value_type,
           typename From::value_type
       > convert;
       typename To::value_type cmp_val;
           cmp_val = convert( (rhs.numeric_value() * exp_result ) * from_mux  / to_mux );
       cmp_val -= cmp_val;
       To to = rhs;
       to -= rhs; 
        
       QUAN_CHECK_EQUAL(cmp_val, typename To::value_type(0));
       To to1(rhs);
       to1 -=rhs;
       QUAN_CHECK_EQUAL(to.numeric_value(),to1.numeric_value());
       bool result1 = (to.numeric_value() == cmp_val);
       
       if( !result1){
           typename To::value_type abs_to = (to.numeric_value() >=0) ? to.numeric_value() : -to.numeric_value();
           typename To::value_type abs_from = (cmp_val >=0) ? cmp_val :-cmp_val;
           typename To::value_type dif = abs_to - abs_from;
           typename To::value_type abs_diff = (dif >=0) ? dif : -dif;
           QUAN_FLOAT_TYPE abs_eps = (eps>=0) ? eps : -eps;
          
           result1 = ( abs_diff < abs_eps);
           if (!result1){
               std::cout.precision(35);
               std::cout << "not equal detected:\n"; 
               std::cout << "lhs.value == " << abs_to <<'\n';
               std::cout << "rhs.value == " << abs_from <<'\n';
               std::cout << "abs error = " << abs_diff << '\n';
               std::cout << "eps = " << abs_eps << '\n';
           }
       }
       std::pair<bool,To> result(result1,to);
       return result;
   }
   template <typename Exp, typename To, typename From>
   std::pair<bool,To> conv_impl(From const & rhs)
   {
       typename quan::meta::eval_exponent<Exp>::eval ev;
       return conv_impl<To>(rhs,ev());
   }

   // asignment_test
   //{
   //    /*
   //    coherent --> finer-grained units coherent
   //    coherent --> coarser-grained units coherent
   //    coherent --> coarser-grained units incoherent
   //
   //    incoherent --> coarser-grained units incoherent
   //    incoherent --> finer-grained units incoherent
   //    incoherent --> coarser-grained units coherent
   //    */

   // coherent , floating-pt --> coarser-grained units coherent , floating-pt
   void conv_coh_gt_coh()
   {
       bool r1 
       = conv_impl<quan::pressure::MPa>( quan::pressure::Pa(5000000),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r1);

       bool r2
       = conv_impl<quan::pressure::MPa>( quan::pressure::mPa(1.1e9),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r2);

       bool r3 
       = conv_impl<quan::pressure::cPa>( quan::pressure::fPa(10234.8976),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r3);

       bool r4 
       = conv_impl<quan::pressure::MPa>( quan::pressure::kPa(9e20),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r4); 

       bool r5
       = conv_impl<quan::pressure::MPa>( quan::pressure::Pa(10),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r5);
   }

   //coherent, floating-pt --> coarser-grained units coherent, int value_type
   void conv_coh_gt_coh_int()
   {
       bool r1 
       = conv_impl<quan::pressure_<QUAN_INT32>::kPa>( quan::pressure::Pa(10),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r1);

       bool r2
       = conv_impl<quan::pressure_<QUAN_INT32>::MPa>( quan::pressure::mPa(10),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r2);

       bool r3 
       = conv_impl<quan::pressure_<QUAN_INT32>::cPa>( quan::pressure::fPa(10),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r3);

       bool r4 
       = conv_impl<quan::pressure_<QUAN_INT32>::MPa>( quan::pressure::kPa(10),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r4); 
   }

   // coherent, floating-pt --> finer-grained units coherent, floating-pt
   void conv_coh_less_coh()
   {
       bool r1 
       = conv_impl<quan::pressure::Pa>( quan::pressure::MPa(1e7),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r1);

       bool r2
       = conv_impl<quan::pressure::mPa>( quan::pressure::MPa(232),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r2);

       bool r3 
       = conv_impl<quan::pressure::fPa>( quan::pressure::cPa(-34),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r3);

       bool r4 
       = conv_impl<quan::pressure::kPa>( quan::pressure::MPa(6789),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r4); 
   }

   //coherent, floating-pt --> finer-grained units coherent with int value_type
   void conv_coh_less_coh_int()
   {
       bool r1 
       = conv_impl<quan::pressure_<QUAN_INT32>::Pa>( quan::pressure::kPa(123),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r1);

       bool r2 = false;
       try{
            conv_impl<quan::pressure_<QUAN_INT32>::Pa>( quan::pressure::MPa(9876),FP_MAX_DIFFERENCE).first;
       }
       catch(std::exception &){
           r2 = true;
       }
       QUAN_CHECK(r2);
       
       bool r3 
       = conv_impl<quan::pressure_<QUAN_INT32>::mPa>( quan::pressure::cPa(-34),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r3);

       bool r4 
       = conv_impl<quan::pressure_<QUAN_INT32>::kPa>( quan::pressure::MPa(67),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r4); 
   }

   // coherent, floating-pt --> coarser-grained units incoherent, floating-pt
   void conv_coh_to_gt_inco()
   {
       bool r1 
       = conv_impl<quan::pressure::cmHg>( quan::pressure::mPa(1.676),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r1);

       bool r2
       = conv_impl<quan::pressure::mbar>( quan::pressure::pPa(25e3),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r2);

       bool r3
       = conv_impl<quan::pressure::dyn_per_cm2>( quan::pressure::mPa(.0008),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r3);
   }

   // coherent, floating-pt --> coarser-grained units incoherent , int value_type
   void conv_coh_to_gt_inco_int()
   {
       bool r1 
       = conv_impl<quan::pressure_<QUAN_INT32>::cmHg>( quan::pressure::mPa(1.676),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r1);

       bool r2
       = conv_impl<quan::pressure_<QUAN_INT32>::mbar>( quan::pressure::mPa(25.034),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r2);

       bool r3
       = conv_impl<quan::pressure_<QUAN_INT32>::dyn_per_cm2>( quan::pressure::mPa(.0008),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r3);

       bool r4
       = conv_impl<quan::pressure_<QUAN_INT32>::atm>( quan::pressure::Pa(.08),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r4);
   }

       //coherent, floating-pt --> finer-grained units incoherent, floating-pt
   void coh_to_less_inco()
   {
       bool r1 
       = conv_impl<quan::pressure::dyn_per_cm2>( quan::pressure::Pa(1.676),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r1);
       
       bool r2
       = conv_impl<quan::pressure::kgf_per_m2>( quan::pressure::kPa(201.7867),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r2);
        
       bool r3
       = conv_impl<quan::pressure::in_water39_2F>( 
           quan::pressure::MPa(1.676),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r3);

        bool r4
       = conv_impl<quan::pressure::atm>( 
           quan::pressure::MPa(-45.3333),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r4);
   }

   //coherent, floating-pt --> finer-grained units incoherent, int
      
   void coh_to_less_inco_int()
   {
       bool r1 
       = conv_impl<quan::pressure_<QUAN_INT32>::dyn_per_cm2>( 
           quan::pressure::Pa(1.676),FP_MAX_DIFFERENCE
       ).first;
       QUAN_CHECK(r1);
       
       bool r2
       = conv_impl<quan::pressure_<QUAN_INT32>::kgf_per_m2>( 
           quan::pressure::kPa(201.7867),FP_MAX_DIFFERENCE
       ).first;
       QUAN_CHECK(r2);
        
       bool r3
       = conv_impl<quan::pressure_<QUAN_INT32>::in_water39_2F>( 
           quan::pressure::MPa(1.676),FP_MAX_DIFFERENCE
       ).first;
       QUAN_CHECK(r3);

        bool r4
       = conv_impl<quan::pressure_<QUAN_INT32>::atm>( 
           quan::pressure::MPa(1.676),FP_MAX_DIFFERENCE
       ).first;
       QUAN_CHECK(r4);
   }

    //incoherent, floating-pt --> coarser-grained units incoherent, floating-pt
   void incoh_gt_inco()
   {
       bool r1 
       = conv_impl<quan::pressure::dyn_per_cm2>( quan::pressure::atm(1999.),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r1);
       
       bool r2
       = conv_impl<quan::pressure::kgf_per_cm2>( quan::pressure::kgf_per_m2(201.7867),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r2);
        
       bool r3
       = conv_impl<quan::pressure::ksi>( 
           quan::pressure::lbf_per_ft2(1.676),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r3);

        bool r4
       = conv_impl<quan::pressure::atm>( 
           quan::pressure::ftHg(-45.3333),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r4);
   }
       //incoherent, floating-pt --> coarser-grained units incoherent, int
   void incoh_gt_inco_int()
   {
       bool r1 
       = conv_impl<quan::pressure_<QUAN_INT32>::dyn_per_cm2>( quan::pressure::atm(1999.),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r1);
       
       bool r2
       = conv_impl<quan::pressure_<QUAN_INT32>::kgf_per_cm2>( quan::pressure::kgf_per_m2(201.7867),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r2);
        
       bool r3
       = conv_impl<quan::pressure_<QUAN_INT32>::ksi>( 
           quan::pressure::lbf_per_ft2(1.676),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r3);

        bool r4
       = conv_impl<quan::pressure_<QUAN_INT32>::atm>( 
           quan::pressure::ftHg(-45.3333),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r4);
   }

   //incoherent, floating-pt --> finer-grained units incoherent, floating-pt
      
   void incoh_less_inco()
   {
       bool r1 
       = conv_impl<quan::pressure::atm>(  quan::pressure::dyn_per_cm2(1999.),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r1);
       
       bool r2
       = conv_impl<quan::pressure::kgf_per_m2 >( quan::pressure::kgf_per_cm2(2.7867),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r2);
        
       bool r3
       = conv_impl<
           quan::meta::rational<-10>,
           quan::pressure::lbf_per_ft2
       >( quan::pressure::ksi(.0676)).first;
       QUAN_CHECK(r3);

       bool r4
       = conv_impl<
           quan::meta::rational<-12>,
           quan::pressure::ftHg>( quan::pressure::atm(-45.3333)).first;
       QUAN_CHECK(r4);
   }

   //incoherent, floating-pt --> finer-grained units incoherent, int
   void incoh_less_inco_int()
   {
       bool r1 
       = conv_impl<quan::pressure_<QUAN_INT32>::atm>(  quan::pressure::dyn_per_cm2(1999.),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r1);
       
       bool r2
       = conv_impl<quan::pressure_<QUAN_INT32>::kgf_per_m2 >( quan::pressure::kgf_per_cm2(2.7867),FP_MAX_DIFFERENCE).first;
       QUAN_CHECK(r2);
        
       bool r3
       = conv_impl<
           quan::meta::rational<-10>,
           quan::pressure_<QUAN_INT32>::lbf_per_ft2
       >( quan::pressure::ksi(.0676)).first;
       QUAN_CHECK(r3);

       bool r4
       = conv_impl<
           quan::meta::rational<-12>,
           quan::pressure_<QUAN_INT32>::ftHg>( quan::pressure::atm(-45.3333)).first;
       QUAN_CHECK(r4);
   }

}

