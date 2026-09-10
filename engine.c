#include<stdio.h>
#include<stdbool.h>

#include "defs.h"

#define STEP 0.1
#define g -9.8


int main(){
	float ti = 0;
	float tf = 1;
	bool h = 1;

	particle2 p1;
	particle2 p2;

	p1.mass = 82;
	p1.acc.x = 1;
	p1.acc.y = g;
	p1.pos.x = 0;
	p1.pos.y = 100;
	p1.elp_time = ti;

	//p2.mass = 82;
	//p2.acc.x = 1;
	//p2.acc.y = g;
	//p2.pos.x = 0;
	//p2.pos.y = 100;
	//p2.elp_time = ti;
	//calcforce(&p2);

	bool p1_header = true;
	bool p2_header = true;

	while(ti <= tf){
		calcforce(&p1);
		calcacc(&p1);
		calcvel(&p1);
		calcpos(&p1);

		if(p1_header == true){
			printf("====Particle P1:=======\n");
			p1_header = false;
		}

		stats(&p1,h);

		//calcforce(&p2);
		//calcacc(&p2);
		//calcvel(&p2);
		//calcpos(&p2);
		//if(p2_header == true){
			//printf("====Particle P2:=======\n");
			//p2_header = false;
		//}
		//stats(&p2,h);

		h = 0;

		ti += STEP;

		p1.elp_time = ti;
		p1.mass -= 1;

		p2.elp_time = ti;
	}
}
