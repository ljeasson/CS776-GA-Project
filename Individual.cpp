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
	[alg, chm, treetops, th_tree, th_seed, th_cr, max_cr, tol, ext, dt1, dt2, R, Zu, hmin, speed_up, max_cr_factor, exclusion]
	*/
	
	chromosome[0] = IntInRange(0,4); // alg
	chromosome[1] = 0; // chm (CHANGE)
	chromosome[2] = 0; // treetops (CHANGE)
	
	chromosome[3] = IntInRange(1,5); // th_tree
	chromosome[4] = DoubleInRange(0.0,1.0); // th_seed
	chromosome[5] = DoubleInRange(0.0,1.0); // th_cr
	chromosome[6] = InInRange(1,20); // max_cr

	chromosome[7] = InInRange(1,10); // tol
	chromosome[8] = InInRange(1,10); // ext

	chromosome[9] = DoubleInRange(1,10); // dt1
	chromosome[10] = DoubleInRange(1,10); // dt2
	chromosome[11] = DoubleInRange(0,20); // R (search radius)
	chromosome[12] = DoubleInRange(10,30); // Zu
	chromosome[13] = DoubleInRange(1,100); // hmin
	chromosome[14] = DoubleInRange(1,100); // speed_up

	chromosome[15] = DoubleInRange(0,1); // max_cr_factor
	chromosome[16] = DoubleInRange(0,1); // exclusion

}

void Individual::Mutate(double pm){
	//for(int i = 0; i < chromLength; i++){
	//	if(Flip(pm))
	//		chromosome[i] = 1 - chromosome[i];
	//}
	
	// Mutate algorithm (0-4)
	if (Flip(pm))
		chromosome[0] = IntInRange(0,4); // alg
	
	// Mutate parameters
	for(int i = 3; i < chromLength; i++){
		if(Flip(pm)){
			switch (i){
				case 3:
					chromosome[3] = IntInRange(1,5); // th_tree
					break;
				case 4:
					chromosome[4] = DoubleInRange(0.0,1.0); // th_seed
					break;
				case 5:
					chromosome[5] = DoubleInRange(0.0,1.0); // th_cr
					break;
				case 6:
					chromosome[6] = InInRange(1,20); // max_cr
					break;
				case 7:
					chromosome[7] = InInRange(1,10); // tol
					break;
				case 8:
					chromosome[8] = InInRange(1,10); // ext
					break;
				case 9:
					chromosome[9] = DoubleInRange(1,10); // dt1
					break;
				case 10:
					chromosome[10] = DoubleInRange(1,10); // dt2
					break;
				case 11:
					chromosome[11] = DoubleInRange(0,20); // R (search radius)
					break;
				case 12:
					chromosome[12] = DoubleInRange(10,30); // Zu
					break;
				case 13:
					chromosome[13] = DoubleInRange(1,100); // hmin
					break;
				case 14:
					chromosome[14] = DoubleInRange(1,100); // speed_up
					break;
				case 15:
					chromosome[15] = DoubleInRange(0,1); // max_cr_factor
					break;
				case 16:
					chromosome[16] = DoubleInRange(0,1); // exclusion
					break;
			}
		}
	}
}
