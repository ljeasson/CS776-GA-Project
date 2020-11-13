/*
 * Individual.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include <Individual.h>
#include <Utils.h>

Individual::Individual(int len) {
	// TODO Auto-generated constructor stub
	chromLength = len;
	fitness = -1;
}

Individual::~Individual() {
	// TODO Auto-generated destructor stub
}

void Individual::Init(){
	//for(int i = 0; i < chromLength; i++){
	//	chromosome[i] = Flip(0.5f);
	//}

	/*
	dalponte2016(
 		chm,
  		treetops,
  		th_tree = 2,
  		th_seed = 0.45,
  		th_cr = 0.55,
  		max_cr = 10,
  		ID = "treeID"
	)
	
	watershed(
		chm,
		th_tree = 2, 
		tol = 1, 
		ext = 1
	)
	mcwatershed(
		chm, 
		treetops, 
		th_tree = 2, 
		ID = "treeID"
	)

	li2012(
		dt1 = 1.5, 
		dt2 = 2, 
		R = 2, 
		Zu = 15, 
		hmin = 2, 
		speed_up = 10
	)

	silva2016(
		chm, 
		treetops, 
		max_cr_factor = 0.6, 
		exclusion = 0.3, 
		ID = "treeID"
	)
	
	CHROMOSOME: 
	[alg, chm, treetops, th_tree, th_seed, th_cr, max_cr, tol, ext, 
	 dt1, dt2, R, Zu, hmin, speed_up, max_cr_factor, exclusion]
	*/
	
	chromosome[0] = IntInRange(0,3); // alg
	
	chromosome[1] = IntInRange(1,5); // th_tree
	chromosome[2] = DoubleInRange(0.0,1.0); // th_seed
	chromosome[3] = DoubleInRange(0.0,1.0); // th_cr
	chromosome[4] = IntInRange(1,20); // max_cr

	chromosome[5] = IntInRange(1,10); // tol
	chromosome[6] = IntInRange(1,10); // ext

	chromosome[7] = DoubleInRange(1,10); // dt1
	chromosome[8] = DoubleInRange(1,10); // dt2
	chromosome[9] = DoubleInRange(0,20); // R (search radius)
	chromosome[10] = DoubleInRange(10,30); // Zu
	chromosome[11] = DoubleInRange(1,100); // hmin
	chromosome[12] = DoubleInRange(1,100); // speed_up

	chromosome[13] = DoubleInRange(0,1); // max_cr_factor
	chromosome[14] = DoubleInRange(0,1); // exclusion

}

void Individual::Mutate(double pm){
	//for(int i = 0; i < chromLength; i++){
	//	if(Flip(pm))
	//		chromosome[i] = 1 - chromosome[i];
	//}
		
	// Mutate parameters
	for(int i = 0; i < chromLength; i++){
		if(Flip(pm)){
			switch (i){
				case 0:
					chromosome[0] = IntInRange(0,4); // alg
					break;
				case 1:
					chromosome[1] = IntInRange(1,5); // th_tree
					break;
				case 2:
					chromosome[2] = DoubleInRange(0.0,1.0); // th_seed
					break;
				case 3:
					chromosome[3] = DoubleInRange(0.0,1.0); // th_cr
					break;
				case 4:
					chromosome[4] = IntInRange(1,20); // max_cr
					break;
				case 5:
					chromosome[5] = IntInRange(1,10); // tol
					break;
				case 6:
					chromosome[6] = IntInRange(1,10); // ext
					break;
				case 7:
					chromosome[7] = DoubleInRange(1,10); // dt1
					break;
				case 8:
					chromosome[8] = DoubleInRange(1,10); // dt2
					break;
				case 9:
					chromosome[9] = DoubleInRange(0,20); // R (search radius)
					break;
				case 10:
					chromosome[10] = DoubleInRange(10,30); // Zu
					break;
				case 11:
					chromosome[11] = DoubleInRange(1,100); // hmin
					break;
				case 12:
					chromosome[12] = DoubleInRange(1,100); // speed_up
					break;
				case 13:
					chromosome[13] = DoubleInRange(0,1); // max_cr_factor
					break;
				case 14:
					chromosome[14] = DoubleInRange(0,1); // exclusion
					break;
			}
		}
	}
}
