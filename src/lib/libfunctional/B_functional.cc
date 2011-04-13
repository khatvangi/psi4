/**********************************************************
* B_functional.cc: definitions for B_functional for KS-DFT
* boost::boost::shared_ptr Parrish, robparrish@gmail.com
* Autogenerated by MATLAB Script on 15-Sep-2010
*
***********************************************************/
#include <libmints/properties.h>
#include <libciomr/libciomr.h>
#include "B_functional.h"
#include <stdlib.h>
#include <cmath>
#include <string>
#include <string>
#include <vector>

using namespace psi;
using namespace boost;
using namespace std;

namespace psi { namespace functional {

B_Functional::B_Functional(int npoints, int deriv) : Functional(npoints, deriv)
{
    
    name_ = "B";
    description_ = "Becke Exchange (S+B88)";
    citation_ = "A.D. Becke, Phys. Rev. A, 38(6):3098-3100, 1988";
    
    double c = 9.3052573634909974E-01;
    params_.push_back(make_pair("c",c));
    double d = 4.1999999999999997E-03;
    params_.push_back(make_pair("d",d));

    is_gga_ = true;
    is_meta_ = false;

    //Required allocateion
    allocate();
}
B_Functional::~B_Functional()
{
}
void B_Functional::computeRKSFunctional(boost::shared_ptr<Properties> prop)
{
    int ntrue = prop->getTrueSize();

    const double* rho_a;
    const double* gamma_aa;
    const double* tau_a;

    rho_a = prop->getRhoA();
    if (is_gga_) {
        gamma_aa = prop->getGammaAA();
    }
    if (is_meta_) {
        tau_a = prop->getTauA();
    }

    double c = params_[0].second;
    double d = params_[1].second;

    //Functional
    for (int index = 0; index < ntrue; index++) {

        //Functional Value
        if (rho_a[index] > cutoff_) {
            double t2982 = pow(rho_a[index],4.0/3.0);
            double t2983 = sqrt(gamma_aa[index]);
            functional_[index] = c*t2982*-2.0-(d*gamma_aa[index]*t2982*2.0)/(d*t2983*log(t2983+sqrt(t2983*t2983+ \
               1.0))*6.0+1.0);
        } else {
            functional_[index] = 0.0;
        } 

    }
    //First Partials
    for (int index = 0; index < ntrue && deriv_ >= 1; index++) {
        
        //V_rho_a
        if (rho_a[index] > cutoff_) {
            double t2985 = pow(rho_a[index],1.0/3.0);
            double t2986 = sqrt(gamma_aa[index]);
            v_rho_a_[index] = c*t2985*(-8.0/3.0)-(d*gamma_aa[index]*t2985*(8.0/3.0))/(d*t2986*log(t2986+sqrt(t2986* \
               t2986+1.0))*6.0+1.0);
        } else {
            v_rho_a_[index] = 0.0;
        } 
        
        if (is_gga_) {
            
            if (rho_a[index] > cutoff_) {
                double t2988 = sqrt(gamma_aa[index]);
                double t2989 = pow(rho_a[index],4.0/3.0);
                double t2990 = log(t2988+sqrt(t2988*t2988+1.0));
                double t2991 = d*t2990*t2988*6.0;
                double t2992 = t2991+1.0;
                v_gamma_aa_[index] = (d*t2989*-2.0)/t2992+d*gamma_aa[index]*1/(t2992*t2992)*t2989*(d*1/sqrt(gamma_aa[index]+ \
                   1.0)*3.0+d*1/sqrt(gamma_aa[index])*t2990*3.0)*2.0;
            } else {
                v_gamma_aa_[index] = 0.0;
            } 
        
        }
        if (is_meta_) {
        
            //V_tau_a
            if (rho_a[index] > cutoff_) {
                v_tau_a_[index] = 0.0;
            } else {
                v_tau_a_[index] = 0.0;
            } 
        
        }
    }
    //Second Partials
    for (int index = 0; index < ntrue && deriv_ >= 2; index++) {
        
        //V_rho_a_rho_a
        if (rho_a[index] > cutoff_) {
            double t2995 = 1/pow(rho_a[index],2.0/3.0);
            double t2996 = sqrt(gamma_aa[index]);
            v_rho_a_rho_a_[index] = c*t2995*(-8.0/9.0)-(d*gamma_aa[index]*t2995*(8.0/9.0))/(d*t2996*log(t2996+ \
               sqrt(t2996*t2996+1.0))*6.0+1.0);
        } else {
            v_rho_a_rho_a_[index] = 0.0;
        } 
        
        if (is_gga_) {
        
            //V_rho_a_gamma_aa
            if (rho_a[index] > cutoff_) {
                double t2998 = sqrt(gamma_aa[index]);
                double t2999 = pow(rho_a[index],1.0/3.0);
                double t3000 = log(t2998+sqrt(t2998*t2998+1.0));
                double t3001 = d*t2998*t3000*6.0;
                double t3002 = t3001+1.0;
                v_rho_a_gamma_aa_[index] = (d*t2999*(-8.0/3.0))/t3002+d*gamma_aa[index]*t2999*1/(t3002*t3002)*(d* \
                   1/sqrt(gamma_aa[index]+1.0)*3.0+d*1/sqrt(gamma_aa[index])*t3000*3.0)*(8.0/3.0);
            } else {
                v_rho_a_gamma_aa_[index] = 0.0;
            } 
        
            //V_gamma_aa_gamma_aa
            if (rho_a[index] > cutoff_) {
                double t3004 = sqrt(gamma_aa[index]);
                double t3005 = log(t3004+sqrt(t3004*t3004+1.0));
                double t3006 = pow(rho_a[index],4.0/3.0);
                double t3007 = d*t3004*t3005*6.0;
                double t3008 = t3007+1.0;
                double t3009 = 1/(t3008*t3008);
                double t3010 = gamma_aa[index]+1.0;
                double t3011 = 1/sqrt(t3010);
                double t3012 = d*t3011*3.0;
                double t3013 = 1/sqrt(gamma_aa[index]);
                double t3014 = d*t3013*t3005*3.0;
                double t3015 = t3012+t3014;
                v_gamma_aa_gamma_aa_[index] = d*t3006*t3015*t3009*4.0-d*gamma_aa[index]*t3006*t3009*(d*1/pow(t3010,3.0/ \
                   2.0)*(3.0/2.0)-(d*t3011*(3.0/2.0))/gamma_aa[index]+d*1/pow(gamma_aa[index],3.0/2.0)*t3005*(3.0/2.0) \
                   )*2.0-d*gamma_aa[index]*t3006*(t3015*t3015)*1/(t3008*t3008*t3008)*4.0;
            } else {
                v_gamma_aa_gamma_aa_[index] = 0.0;
            } 
        
        }
        if (is_meta_) {
        
            //V_rho_a_tau_a
            if (rho_a[index] > cutoff_) {
                v_rho_a_tau_a_[index] = 0.0;
            } else {
                v_rho_a_tau_a_[index] = 0.0;
            } 
        
            //V_tau_a_tau_a
            if (rho_a[index] > cutoff_) {
                v_tau_a_tau_a_[index] = 0.0;
            } else {
                v_tau_a_tau_a_[index] = 0.0;
            } 
       
            if (is_gga_) {
        
                //V_gamma_aa_tau_a
                if (rho_a[index] > cutoff_) {
                    v_gamma_aa_tau_a_[index] = 0.0;
                } else {
                    v_gamma_aa_tau_a_[index] = 0.0;
                } 
       
            }
        }
    }
}
void B_Functional::computeUKSFunctional(boost::shared_ptr<Properties> prop)
{
    int ntrue = prop->getTrueSize();

    const double* rho_a;
    const double* rho_b;
    const double* gamma_aa;
    const double* gamma_ab;
    const double* gamma_bb;
    const double* tau_a;
    const double* tau_b;

    rho_a = prop->getRhoA();
    rho_b = prop->getRhoB();
    if (is_gga_) {
        gamma_aa = prop->getGammaAA();
        gamma_ab = prop->getGammaAB();
        gamma_bb = prop->getGammaBB();
    }
    if (is_meta_) {
        tau_a = prop->getTauA();
        tau_b = prop->getTauB();
    }

    double c = params_[0].second;
    double d = params_[1].second;
    
    //Functional
    for (int index = 0; index < ntrue; index++) {

        //Functional Value
        if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
            double t2726 = pow(rho_a[index],4.0/3.0);
            double t2727 = sqrt(gamma_aa[index]);
            double t2728 = pow(rho_b[index],4.0/3.0);
            double t2729 = sqrt(gamma_bb[index]);
            functional_[index] = -c*(t2726+t2728)-(d*gamma_aa[index]*t2726)/(d*t2727*log(t2727+sqrt(t2727*t2727+ \
               1.0))*6.0+1.0)-(d*gamma_bb[index]*t2728)/(d*t2729*log(t2729+sqrt(t2729*t2729+1.0))*6.0+1.0);
        } else if (rho_a[index] > cutoff_) {
            double t2882 = pow(rho_a[index],4.0/3.0);
            double t2883 = sqrt(gamma_aa[index]);
            functional_[index] = -c*t2882-(d*gamma_aa[index]*t2882)/(d*t2883*log(t2883+sqrt(t2883*t2883+1.0)) \
               *6.0+1.0);
        } else if (rho_b[index] > cutoff_) {
            double t2818 = pow(rho_b[index],4.0/3.0);
            double t2819 = sqrt(gamma_bb[index]);
            functional_[index] = -c*t2818-(d*gamma_bb[index]*t2818)/(d*t2819*log(t2819+sqrt(t2819*t2819+1.0)) \
               *6.0+1.0);
        } else {
            functional_[index] = 0.0;
        } 
   
    }
    //First Partials
    for (int index = 0; index < ntrue && deriv_ >= 1; index++) {

        //V_rho_a
        if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
            double t2731 = pow(rho_a[index],1.0/3.0);
            double t2732 = sqrt(gamma_aa[index]);
            v_rho_a_[index] = c*t2731*(-4.0/3.0)-(d*gamma_aa[index]*t2731*(4.0/3.0))/(d*t2732*log(t2732+sqrt(t2732* \
               t2732+1.0))*6.0+1.0);
        } else if (rho_a[index] > cutoff_) {
            double t2885 = pow(rho_a[index],1.0/3.0);
            double t2886 = sqrt(gamma_aa[index]);
            v_rho_a_[index] = c*t2885*(-4.0/3.0)-(d*gamma_aa[index]*t2885*(4.0/3.0))/(d*t2886*log(t2886+sqrt(t2886* \
               t2886+1.0))*6.0+1.0);
        } else if (rho_b[index] > cutoff_) {
            v_rho_a_[index] = 0.0;
        } else {
            v_rho_a_[index] = 0.0;
        } 

        //V_rho_b
        if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
            double t2734 = pow(rho_b[index],1.0/3.0);
            double t2735 = sqrt(gamma_bb[index]);
            v_rho_b_[index] = c*t2734*(-4.0/3.0)-(d*gamma_bb[index]*t2734*(4.0/3.0))/(d*t2735*log(t2735+sqrt(t2735* \
               t2735+1.0))*6.0+1.0);
        } else if (rho_a[index] > cutoff_) {
            v_rho_b_[index] = 0.0;
        } else if (rho_b[index] > cutoff_) {
            double t2822 = pow(rho_b[index],1.0/3.0);
            double t2823 = sqrt(gamma_bb[index]);
            v_rho_b_[index] = c*t2822*(-4.0/3.0)-(d*gamma_bb[index]*t2822*(4.0/3.0))/(d*t2823*log(t2823+sqrt(t2823* \
               t2823+1.0))*6.0+1.0);
        } else {
            v_rho_b_[index] = 0.0;
        } 

        if (is_gga_) {

            //V_gamma_aa
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                double t2737 = sqrt(gamma_aa[index]);
                double t2738 = pow(rho_a[index],4.0/3.0);
                double t2739 = log(t2737+sqrt(t2737*t2737+1.0));
                double t2740 = d*t2737*t2739*6.0;
                double t2741 = t2740+1.0;
                v_gamma_aa_[index] = -(d*t2738)/t2741+d*gamma_aa[index]*1/(t2741*t2741)*t2738*(d*1/sqrt(gamma_aa[index]+ \
                   1.0)*3.0+d*1/sqrt(gamma_aa[index])*t2739*3.0);
            } else if (rho_a[index] > cutoff_) {
                double t2889 = sqrt(gamma_aa[index]);
                double t2890 = pow(rho_a[index],4.0/3.0);
                double t2891 = log(t2889+sqrt(t2889*t2889+1.0));
                double t2892 = d*t2891*t2889*6.0;
                double t2893 = t2892+1.0;
                v_gamma_aa_[index] = -(d*t2890)/t2893+d*gamma_aa[index]*t2890*1/(t2893*t2893)*(d*1/sqrt(gamma_aa[index]+ \
                   1.0)*3.0+d*1/sqrt(gamma_aa[index])*t2891*3.0);
            } else if (rho_b[index] > cutoff_) {
                v_gamma_aa_[index] = 0.0;
            } else {
                v_gamma_aa_[index] = 0.0;
            } 

            //V_gamma_ab
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_gamma_ab_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_gamma_ab_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_gamma_ab_[index] = 0.0;
            } else {
                v_gamma_ab_[index] = 0.0;
            } 

            //V_gamma_bb
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                double t2744 = sqrt(gamma_bb[index]);
                double t2745 = pow(rho_b[index],4.0/3.0);
                double t2746 = log(t2744+sqrt(t2744*t2744+1.0));
                double t2747 = d*t2744*t2746*6.0;
                double t2748 = t2747+1.0;
                v_gamma_bb_[index] = -(d*t2745)/t2748+d*gamma_bb[index]*t2745*1/(t2748*t2748)*(d*1/sqrt(gamma_bb[index]+ \
                   1.0)*3.0+d*1/sqrt(gamma_bb[index])*t2746*3.0);
            } else if (rho_a[index] > cutoff_) {
                v_gamma_bb_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                double t2827 = sqrt(gamma_bb[index]);
                double t2828 = pow(rho_b[index],4.0/3.0);
                double t2829 = log(t2827+sqrt(t2827*t2827+1.0));
                double t2830 = d*t2827*t2829*6.0;
                double t2831 = t2830+1.0;
                v_gamma_bb_[index] = -(d*t2828)/t2831+d*gamma_bb[index]*1/(t2831*t2831)*t2828*(d*1/sqrt(gamma_bb[index]+ \
                   1.0)*3.0+d*1/sqrt(gamma_bb[index])*t2829*3.0);
            } else {
                v_gamma_bb_[index] = 0.0;
            } 
        }
        if (is_meta_) {

            //V_tau_a
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_tau_a_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_tau_a_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_tau_a_[index] = 0.0;
            } else {
                v_tau_a_[index] = 0.0;
            } 

            //V_tau_a
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_tau_b_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_tau_b_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_tau_b_[index] = 0.0;
            } else {
                v_tau_b_[index] = 0.0;
            } 
        }
    }
    //Second Partials
    for (int index = 0; index < ntrue && deriv_ >= 2; index++) {

        //V_rho_a_rho_a
        if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
            double t2752 = 1/pow(rho_a[index],2.0/3.0);
            double t2753 = sqrt(gamma_aa[index]);
            v_rho_a_rho_a_[index] = c*t2752*(-4.0/9.0)-(d*gamma_aa[index]*t2752*(4.0/9.0))/(d*t2753*log(t2753+ \
               sqrt(t2753*t2753+1.0))*6.0+1.0);
        } else if (rho_a[index] > cutoff_) {
            double t2899 = 1/pow(rho_a[index],2.0/3.0);
            double t2900 = sqrt(gamma_aa[index]);
            v_rho_a_rho_a_[index] = c*t2899*(-4.0/9.0)-(d*gamma_aa[index]*t2899*(4.0/9.0))/(d*t2900*log(t2900+ \
               sqrt(t2900*t2900+1.0))*6.0+1.0);
        } else if (rho_b[index] > cutoff_) {
            v_rho_a_rho_a_[index] = 0.0;
        } else {
            v_rho_a_rho_a_[index] = 0.0;
        } 

        //V_rho_a_rho_b
        if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
            v_rho_a_rho_b_[index] = 0.0;
        } else if (rho_a[index] > cutoff_) {
            v_rho_a_rho_b_[index] = 0.0;
        } else if (rho_b[index] > cutoff_) {
            v_rho_a_rho_b_[index] = 0.0;
        } else {
            v_rho_a_rho_b_[index] = 0.0;
        } 

        //V_rho_b_rho_b
        if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
            double t2756 = 1/pow(rho_b[index],2.0/3.0);
            double t2757 = sqrt(gamma_bb[index]);
            v_rho_b_rho_b_[index] = c*t2756*(-4.0/9.0)-(d*gamma_bb[index]*t2756*(4.0/9.0))/(d*t2757*log(t2757+ \
               sqrt(t2757*t2757+1.0))*6.0+1.0);
        } else if (rho_a[index] > cutoff_) {
            v_rho_b_rho_b_[index] = 0.0;
        } else if (rho_b[index] > cutoff_) {
            double t2837 = 1/pow(rho_b[index],2.0/3.0);
            double t2838 = sqrt(gamma_bb[index]);
            v_rho_b_rho_b_[index] = c*t2837*(-4.0/9.0)-(d*gamma_bb[index]*t2837*(4.0/9.0))/(d*t2838*log(t2838+ \
               sqrt(t2838*t2838+1.0))*6.0+1.0);
        } else {
            v_rho_b_rho_b_[index] = 0.0;
        } 

        if (is_gga_) {

            //V_rho_a_gamma_aa
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                double t2759 = sqrt(gamma_aa[index]);
                double t2760 = pow(rho_a[index],1.0/3.0);
                double t2761 = log(t2759+sqrt(t2759*t2759+1.0));
                double t2762 = d*t2761*t2759*6.0;
                double t2763 = t2762+1.0;
                v_rho_a_gamma_aa_[index] = (d*t2760*(-4.0/3.0))/t2763+d*gamma_aa[index]*t2760*1/(t2763*t2763)*(d* \
                   1/sqrt(gamma_aa[index]+1.0)*3.0+d*1/sqrt(gamma_aa[index])*t2761*3.0)*(4.0/3.0);
            } else if (rho_a[index] > cutoff_) {
                double t2904 = sqrt(gamma_aa[index]);
                double t2905 = pow(rho_a[index],1.0/3.0);
                double t2906 = log(t2904+sqrt(t2904*t2904+1.0));
                double t2907 = d*t2904*t2906*6.0;
                double t2908 = t2907+1.0;
                v_rho_a_gamma_aa_[index] = (d*t2905*(-4.0/3.0))/t2908+d*gamma_aa[index]*t2905*1/(t2908*t2908)*(d* \
                   1/sqrt(gamma_aa[index]+1.0)*3.0+d*1/sqrt(gamma_aa[index])*t2906*3.0)*(4.0/3.0);
            } else if (rho_b[index] > cutoff_) {
                v_rho_a_gamma_aa_[index] = 0.0;
            } else {
                v_rho_a_gamma_aa_[index] = 0.0;
            } 

            //V_rho_a_gamma_ab
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_rho_a_gamma_ab_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_rho_a_gamma_ab_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_rho_a_gamma_ab_[index] = 0.0;
            } else {
                v_rho_a_gamma_ab_[index] = 0.0;
            } 

            //V_rho_a_gamma_bb
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_rho_a_gamma_bb_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_rho_a_gamma_bb_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_rho_a_gamma_bb_[index] = 0.0;
            } else {
                v_rho_a_gamma_bb_[index] = 0.0;
            } 

            //V_rho_b_gamma_aa
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_rho_b_gamma_aa_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_rho_b_gamma_aa_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_rho_b_gamma_aa_[index] = 0.0;
            } else {
                v_rho_b_gamma_aa_[index] = 0.0;
            } 

            //V_rho_b_gamma_ab
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_rho_b_gamma_ab_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_rho_b_gamma_ab_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_rho_b_gamma_ab_[index] = 0.0;
            } else {
                v_rho_b_gamma_ab_[index] = 0.0;
            } 

            //V_rho_b_gamma_bb
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                double t2769 = sqrt(gamma_bb[index]);
                double t2770 = pow(rho_b[index],1.0/3.0);
                double t2771 = log(t2769+sqrt(t2769*t2769+1.0));
                double t2772 = d*t2771*t2769*6.0;
                double t2773 = t2772+1.0;
                v_rho_b_gamma_bb_[index] = (d*t2770*(-4.0/3.0))/t2773+d*gamma_bb[index]*t2770*1/(t2773*t2773)*(d* \
                   1/sqrt(gamma_bb[index]+1.0)*3.0+d*1/sqrt(gamma_bb[index])*t2771*3.0)*(4.0/3.0);
            } else if (rho_a[index] > cutoff_) {
                v_rho_b_gamma_bb_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                double t2845 = sqrt(gamma_bb[index]);
                double t2846 = pow(rho_b[index],1.0/3.0);
                double t2847 = log(t2845+sqrt(t2845*t2845+1.0));
                double t2848 = d*t2845*t2847*6.0;
                double t2849 = t2848+1.0;
                v_rho_b_gamma_bb_[index] = (d*t2846*(-4.0/3.0))/t2849+d*gamma_bb[index]*t2846*1/(t2849*t2849)*(d* \
                   1/sqrt(gamma_bb[index]+1.0)*3.0+d*1/sqrt(gamma_bb[index])*t2847*3.0)*(4.0/3.0);
            } else {
                v_rho_b_gamma_bb_[index] = 0.0;
            } 

            //V_gamma_aa_gamma_aa
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                double t2775 = sqrt(gamma_aa[index]);
                double t2776 = log(t2775+sqrt(t2775*t2775+1.0));
                double t2777 = pow(rho_a[index],4.0/3.0);
                double t2778 = d*t2775*t2776*6.0;
                double t2779 = t2778+1.0;
                double t2780 = 1/(t2779*t2779);
                double t2781 = gamma_aa[index]+1.0;
                double t2782 = 1/sqrt(t2781);
                double t2783 = d*t2782*3.0;
                double t2784 = 1/sqrt(gamma_aa[index]);
                double t2785 = d*t2784*t2776*3.0;
                double t2786 = t2783+t2785;
                v_gamma_aa_gamma_aa_[index] = d*t2780*t2777*t2786*2.0-d*gamma_aa[index]*t2780*t2777*(d*1/pow(t2781,3.0/ \
                   2.0)*(3.0/2.0)-(d*t2782*(3.0/2.0))/gamma_aa[index]+d*1/pow(gamma_aa[index],3.0/2.0)*t2776*(3.0/2.0) \
                   )-d*gamma_aa[index]*t2777*(t2786*t2786)*1/(t2779*t2779*t2779)*2.0;
            } else if (rho_a[index] > cutoff_) {
                double t2915 = sqrt(gamma_aa[index]);
                double t2916 = log(t2915+sqrt(t2915*t2915+1.0));
                double t2917 = pow(rho_a[index],4.0/3.0);
                double t2918 = d*t2915*t2916*6.0;
                double t2919 = t2918+1.0;
                double t2920 = 1/(t2919*t2919);
                double t2921 = gamma_aa[index]+1.0;
                double t2922 = 1/sqrt(t2921);
                double t2923 = d*t2922*3.0;
                double t2924 = 1/sqrt(gamma_aa[index]);
                double t2925 = d*t2924*t2916*3.0;
                double t2926 = t2923+t2925;
                v_gamma_aa_gamma_aa_[index] = d*t2920*t2917*t2926*2.0-d*gamma_aa[index]*t2920*t2917*(d*1/pow(t2921,3.0/ \
                   2.0)*(3.0/2.0)-(d*t2922*(3.0/2.0))/gamma_aa[index]+d*1/pow(gamma_aa[index],3.0/2.0)*t2916*(3.0/2.0) \
                   )-d*gamma_aa[index]*t2917*(t2926*t2926)*1/(t2919*t2919*t2919)*2.0;
            } else if (rho_b[index] > cutoff_) {
                v_gamma_aa_gamma_aa_[index] = 0.0;
            } else {
                v_gamma_aa_gamma_aa_[index] = 0.0;
            } 

            //V_gamma_aa_gamma_ab
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_gamma_aa_gamma_ab_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_gamma_aa_gamma_ab_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_gamma_aa_gamma_ab_[index] = 0.0;
            } else {
                v_gamma_aa_gamma_ab_[index] = 0.0;
            } 

            //V_gamma_aa_gamma_bb
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_gamma_aa_gamma_bb_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_gamma_aa_gamma_bb_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_gamma_aa_gamma_bb_[index] = 0.0;
            } else {
                v_gamma_aa_gamma_bb_[index] = 0.0;
            } 

            //V_gamma_ab_gamma_ab
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_gamma_ab_gamma_ab_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_gamma_ab_gamma_ab_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_gamma_ab_gamma_ab_[index] = 0.0;
            } else {
                v_gamma_ab_gamma_ab_[index] = 0.0;
            } 

            //V_gamma_ab_gamma_bb
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_gamma_ab_gamma_bb_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_gamma_ab_gamma_bb_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_gamma_ab_gamma_bb_[index] = 0.0;
            } else {
                v_gamma_ab_gamma_bb_[index] = 0.0;
            } 

            //V_gamma_bb_gamma_bb
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                double t2792 = sqrt(gamma_bb[index]);
                double t2793 = log(t2792+sqrt(t2792*t2792+1.0));
                double t2794 = pow(rho_b[index],4.0/3.0);
                double t2795 = d*t2792*t2793*6.0;
                double t2796 = t2795+1.0;
                double t2797 = 1/(t2796*t2796);
                double t2798 = gamma_bb[index]+1.0;
                double t2799 = 1/sqrt(t2798);
                double t2800 = d*t2799*3.0;
                double t2801 = 1/sqrt(gamma_bb[index]);
                double t2802 = d*t2793*t2801*3.0;
                double t2803 = t2800+t2802;
                v_gamma_bb_gamma_bb_[index] = d*t2794*t2797*t2803*2.0-d*gamma_bb[index]*t2794*t2797*(d*1/pow(t2798,3.0/ \
                   2.0)*(3.0/2.0)+d*1/pow(gamma_bb[index],3.0/2.0)*t2793*(3.0/2.0)-(d*t2799*(3.0/2.0))/gamma_bb[index]) \
                   -d*gamma_bb[index]*t2794*1/(t2796*t2796*t2796)*(t2803*t2803)*2.0;
            } else if (rho_a[index] > cutoff_) {
                v_gamma_bb_gamma_bb_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                double t2856 = sqrt(gamma_bb[index]);
                double t2857 = log(t2856+sqrt(t2856*t2856+1.0));
                double t2858 = pow(rho_b[index],4.0/3.0);
                double t2859 = d*t2856*t2857*6.0;
                double t2860 = t2859+1.0;
                double t2861 = 1/(t2860*t2860);
                double t2862 = gamma_bb[index]+1.0;
                double t2863 = 1/sqrt(t2862);
                double t2864 = d*t2863*3.0;
                double t2865 = 1/sqrt(gamma_bb[index]);
                double t2866 = d*t2865*t2857*3.0;
                double t2867 = t2864+t2866;
                v_gamma_bb_gamma_bb_[index] = d*t2861*t2858*t2867*2.0-d*gamma_bb[index]*t2861*t2858*(d*1/pow(t2862,3.0/ \
                   2.0)*(3.0/2.0)-(d*t2863*(3.0/2.0))/gamma_bb[index]+d*1/pow(gamma_bb[index],3.0/2.0)*t2857*(3.0/2.0) \
                   )-d*gamma_bb[index]*1/(t2860*t2860*t2860)*t2858*(t2867*t2867)*2.0;
            } else {
                v_gamma_bb_gamma_bb_[index] = 0.0;
            } 

        }                       
        if (is_meta_) {

            //V_rho_a_tau_a
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_rho_a_tau_a_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_rho_a_tau_a_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_rho_a_tau_a_[index] = 0.0;
            } else {
                v_rho_a_tau_a_[index] = 0.0;
            } 

            //V_rho_a_tau_b
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_rho_a_tau_b_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_rho_a_tau_b_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_rho_a_tau_b_[index] = 0.0;
            } else {
                v_rho_a_tau_b_[index] = 0.0;
            } 

            //V_rho_b_tau_a
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_rho_b_tau_a_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_rho_b_tau_a_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_rho_b_tau_a_[index] = 0.0;
            } else {
                v_rho_b_tau_a_[index] = 0.0;
            } 

            //V_rho_b_tau_b
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_rho_b_tau_b_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_rho_b_tau_b_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_rho_b_tau_b_[index] = 0.0;
            } else {
                v_rho_b_tau_b_[index] = 0.0;
            } 

            //V_tau_a_tau_a
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_tau_a_tau_a_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_tau_a_tau_a_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_tau_a_tau_a_[index] = 0.0;
            } else {
                v_tau_a_tau_a_[index] = 0.0;
            } 

            //V_tau_a_tau_b
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_tau_a_tau_b_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_tau_a_tau_b_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_tau_a_tau_b_[index] = 0.0;
            } else {
                v_tau_a_tau_b_[index] = 0.0;
            } 

            //V_tau_b_tau_b
            if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                v_tau_b_tau_b_[index] = 0.0;
            } else if (rho_a[index] > cutoff_) {
                v_tau_b_tau_b_[index] = 0.0;
            } else if (rho_b[index] > cutoff_) {
                v_tau_b_tau_b_[index] = 0.0;
            } else {
                v_tau_b_tau_b_[index] = 0.0;
            } 

            if (is_gga_) {
            	
                //V_gamma_aa_tau_a
                if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                    v_gamma_aa_tau_a_[index] = 0.0;
                } else if (rho_a[index] > cutoff_) {
                    v_gamma_aa_tau_a_[index] = 0.0;
                } else if (rho_b[index] > cutoff_) {
                    v_gamma_aa_tau_a_[index] = 0.0;
                } else {
                    v_gamma_aa_tau_a_[index] = 0.0;
                } 
            	
                //V_gamma_aa_tau_b
                if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                    v_gamma_aa_tau_b_[index] = 0.0;
                } else if (rho_a[index] > cutoff_) {
                    v_gamma_aa_tau_b_[index] = 0.0;
                } else if (rho_b[index] > cutoff_) {
                    v_gamma_aa_tau_b_[index] = 0.0;
                } else {
                    v_gamma_aa_tau_b_[index] = 0.0;
                } 
            	
                //V_gamma_ab_tau_a
                if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                    v_gamma_ab_tau_a_[index] = 0.0;
                } else if (rho_a[index] > cutoff_) {
                    v_gamma_ab_tau_a_[index] = 0.0;
                } else if (rho_b[index] > cutoff_) {
                    v_gamma_ab_tau_a_[index] = 0.0;
                } else {
                    v_gamma_ab_tau_a_[index] = 0.0;
                } 
            	
                //V_gamma_ab_tau_b
                if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                    v_gamma_ab_tau_b_[index] = 0.0;
                } else if (rho_a[index] > cutoff_) {
                    v_gamma_ab_tau_b_[index] = 0.0;
                } else if (rho_b[index] > cutoff_) {
                    v_gamma_ab_tau_b_[index] = 0.0;
                } else {
                    v_gamma_ab_tau_b_[index] = 0.0;
                } 
            	
                //V_gamma_bb_tau_a
                if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                    v_gamma_bb_tau_a_[index] = 0.0;
                } else if (rho_a[index] > cutoff_) {
                    v_gamma_bb_tau_a_[index] = 0.0;
                } else if (rho_b[index] > cutoff_) {
                    v_gamma_bb_tau_a_[index] = 0.0;
                } else {
                    v_gamma_bb_tau_a_[index] = 0.0;
                } 
            	
                //V_gamma_bb_tau_b
                if (rho_a[index] > cutoff_ && rho_b[index] > cutoff_) {
                    v_gamma_bb_tau_b_[index] = 0.0;
                } else if (rho_a[index] > cutoff_) {
                    v_gamma_bb_tau_b_[index] = 0.0;
                } else if (rho_b[index] > cutoff_) {
                    v_gamma_bb_tau_b_[index] = 0.0;
                } else {
                    v_gamma_bb_tau_b_[index] = 0.0;
                } 
          
            }  
        }
    }
}

}}

