
/*
 * SI_main.c
 *
 *  Created on: 16.06.2015.
 *      Authors: Standzi, Marko, Dva geja (Urosko i Milan GAY)
 */

#include "SI_logic.h"
#include "SI_interrupt.h"
#include <stdlib.h>



Xuint8 max_asteroids_on_level;
	struct asteroids_info asteroid_field[100];
	int current_asteroid_on_field;
	int max_asteroids_on_field;
	int destroyed_asteroids[100];
	struct bullet projectile;
	int score = 0;


Xuint32 border_upper_left[26][3]=
{{0x22222222, 0x22222222, 0x22222222},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000} };


Xuint32 border_horizontal[26][3]=
{{0x22222222, 0x22222222, 0x22222222},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000} };

Xuint32 bullet_right[26][3]=
{{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00111111},
{0x00000000, 0x00000000, 0x00111111},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000} };

Xuint32 bullet_left[26][3]=
{{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x11111100, 0x00000000, 0x00000000},
{0x11111100, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000} };


Xuint32 border_horizontal_lower[26][3]=
{{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x00000000, 0x00000000, 0x00000000},
{0x22222222, 0x22222222, 0x22222222},
{0x00000000, 0x00000000, 0x00000000} };


Xuint32 home_base[26][3]=
{{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000},
{0x00000000, 0x00444400, 0x00000000} };


Xuint32 border_upper_right[26][3]=
{{0x22222222, 0x22222222, 0x22222222},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002} };

Xuint32 border_vertical_right[26][3]=
{{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002} };

Xuint32 border_vertical_left[26][3]=
{{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000} };


Xuint32 border_lover_left[26][3]=
{{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x20000000, 0x00000000, 0x00000000},
{0x22222222, 0x22222222, 0x22222222},
{0x20000000, 0x00000000, 0x00000000}
 };

Xuint32 border_lover_right[26][3]=
{{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x00000000, 0x00000000, 0x00000002},
{0x22222222, 0x22222222, 0x22222222},
{0x00000000, 0x00000000, 0x00000002}
};




Xuint32 asteroid_t1[26][3]=
{{0x00000000, 0x00022000, 0x00000000},
{0x00000000, 0x00200200, 0x00000000},
{0x00000000, 0x02002000, 0x00000000},
{0x00000000, 0x20000200, 0x00000000},
{0x00000002, 0x00002000, 0x00000000},
{0x00000020, 0x00020000, 0x00000000},
{0x00000200, 0x00002000, 0x00000000},
{0x00000200, 0x00000200, 0x00000000},
{0x00000200, 0x00000020, 0x00000000},
{0x00000200, 0x00000002, 0x00000000},
{0x00000020, 0x00000000, 0x20000000},
{0x00000002, 0x00000000, 0x02000000},
{0x00000002, 0x00000000, 0x02000000},
{0x00000002, 0x00000000, 0x02000000},
{0x00000020, 0x00000000, 0x02000000},
{0x00000020, 0x00000000, 0x02000000},
{0x00000002, 0x00000000, 0x20000000},
{0x00000020, 0x00000000, 0x20000000},
{0x00000200, 0x00000002, 0x00000000},
{0x00002000, 0x00000002, 0x00000000},
{0x00002000, 0x00000020, 0x00000000},
{0x00002000, 0x00000200, 0x00000000},
{0x00000200, 0x00002000, 0x00000000},
{0x00000020, 0x00020000, 0x00000000},
{0x00000002, 0x00200000, 0x00000000},
{0x00000000, 0x22000000, 0x00000000} };
Xuint32 asteroid_t2[26][3]=
{{0x00000000, 0x00220000, 0x00000000},
{ 0x00000000, 0x02002000, 0x00000000},
{ 0x00000000, 0x20000200, 0x00000000},
{ 0x00000002, 0x00000020, 0x00000000},
{ 0x00000002, 0x00000020, 0x00000000},
{ 0x00000020, 0x00000020, 0x00000000},
{ 0x00000200, 0x00000020, 0x00000000},
{ 0x00000200, 0x00000002, 0x00000000},
{ 0x00000020, 0x00000002, 0x00000000},
{ 0x00000200, 0x00000002, 0x00000000},
{ 0x00000020, 0x00000002, 0x00000000},
{ 0x00000020, 0x00000002, 0x00000000},
{ 0x00000020, 0x00000000, 0x20000000},
{ 0x00000002, 0x00000000, 0x20000000},
{ 0x00000002, 0x00000000, 0x20000000},
{ 0x00000000, 0x20000000, 0x02000000},
{ 0x00000000, 0x20000000, 0x02000000},
{ 0x00000000, 0x02000000, 0x00200000},
{ 0x00000000, 0x02000000, 0x00200000},
{ 0x00000000, 0x02000000, 0x02000000},
{ 0x00000000, 0x00200000, 0x20000000},
{ 0x00000000, 0x00020002, 0x00000000},
{ 0x00000000, 0x00020020, 0x00000000},
{ 0x00000000, 0x00020020, 0x00000000},
{ 0x00000000, 0x0000220,  0x00000000},
{ 0x00000000, 0x00002200, 0x00000000}
};
Xuint32 asteroid_t3[26][3]=
{
 {0x00000000, 0x00000022, 0x00000000},
 {0x00000000, 0x00000200, 0x20000000},
 {0x00000000, 0x00002000, 0x20000000},
 {0x00000000, 0x00002000, 0x02000000},
 {0x00000000, 0x00020000, 0x02000000},
 {0x00000000, 0x00020000, 0x00200000},
 {0x00000000, 0x00200000, 0x00020000},
 {0x00000000, 0x00200000, 0x00020000},
 {0x00000000, 0x02000000, 0x00002000},
 {0x00000000, 0x02000000, 0x00002000},
 {0x00000000, 0x20000000, 0x00000200},
 {0x00000000, 0x20000000, 0x00000200},
 {0x00000000, 0x02000000, 0x00002000},
 {0x00000000, 0x00200000, 0x00002000},
 {0x00000000, 0x00020000, 0x00020000},
 {0x00000000, 0x00002000, 0x00020000},
 {0x00000000, 0x00002000, 0x00020000},
 {0x00000000, 0x00000200, 0x00200000},
 {0x00000000, 0x00000200, 0x00200000},
 {0x00000000, 0x00000020, 0x02000000},
 {0x00000000, 0x00000002, 0x02000000},
 {0x00000000, 0x00000002, 0x20000000},
 {0x00000000, 0x00000000, 0x00000000},
 {0x00000000, 0x00000000, 0x00000000},
 {0x00000000, 0x00000000, 0x00000000},
 {0x00000000, 0x00000000, 0x00000000}
};
unsigned player_state1[26][3]=
{
{0x00000000,0x00022000,0x00000000},
{0x00000000,0x00022000,0x00000000},
{0x00000000,0x00022000,0x00000000},
{0x00000000,0x00222200,0x00000000},
{0x00000000,0x00222200,0x00000000},
{0x00000000,0x02222220,0x00000000},
{0x00000000,0x02222220,0x00000000},
{0x00000000,0x22222222,0x00000000},
{0x00000000,0x22222222,0x00000000},
{0x00000002,0x22222222,0x20000000},
{0x00000002,0x22222222,0x20000000},
{0x00000022,0x22222222,0x22000000},
{0x00000022,0x22222222,0x22000000},
{0x00000222,0x22222222,0x22200000},
{0x00000222,0x22200222,0x22200000},
{0x00002222,0x22000022,0x22220000},
{0x00002222,0x20000002,0x22220000},
{0x00002222,0x00000000,0x22220000},
{0x00022220,0x00000000,0x02222000},
{0x00022200,0x00000000,0x00222000},
{0x00222000,0x00000000,0x00022200},
{0x02220000,0x00000000,0x00002220},
{0x02200000,0x00000000,0x00000220},
{0x22000000,0x00000000,0x00000022},
{0x20000000,0x00000000,0x00000002}
};

unsigned player_state5[26][3]=
{
{0x20000000,0x00000000,0x00000002},
{0x22000000,0x00000000,0x00000022},
{0x02200000,0x00000000,0x00000220},
{0x02220000,0x00000000,0x00002220},
{0x00222000,0x00000000,0x00022200},
{0x00022200,0x00000000,0x00222000},
{0x00022220,0x00000000,0x02222000},
{0x00002222,0x00000000,0x22220000},
{0x00002222,0x20000002,0x22220000},
{0x00002222,0x22000022,0x22220000},
{0x00000222,0x22200222,0x22200000},
{0x00000222,0x22222222,0x22200000},
{0x00000022,0x22222222,0x22000000},
{0x00000022,0x22222222,0x22000000},
{0x00000002,0x22222222,0x20000000},
{0x00000002,0x22222222,0x20000000},
{0x00000000,0x22222222,0x00000000},
{0x00000000,0x22222222,0x00000000},
{0x00000000,0x02222220,0x00000000},
{0x00000000,0x02222220,0x00000000},
{0x00000000,0x02222220,0x00000000},
{0x00000000,0x00222200,0x00000000},
{0x00000000,0x00222200,0x00000000},
{0x00000000,0x00022000,0x00000000},
{0x00000000,0x00022000,0x00000000},
{0x00000000,0x00022000,0x00000000}
};

unsigned player_state2[26][3]=
{
{0x00000000,0x00000000,0x00000002},
{0x00000000,0x00000000,0x00000022},
{0x00000000,0x00000000,0x00002220},
{0x00000000,0x00000000,0x00022200},
{0x00000000,0x00000000,0x00222200},
{0x00000000,0x00000000,0x22222000},
{0x00000000,0x00000002,0x22220000},
{0x00000000,0x00000022,0x22220000},
{0x00000000,0x00002222,0x22200000},
{0x00000000,0x00222222,0x20000000},
{0x00000000,0x02222222,0x20000000},
{0x00000002,0x22222222,0x00000000},
{0x00000022,0x22222220,0x00000000},
{0x00000222,0x22222200,0x00000000},
{0x00022222,0x22222200,0x00000000},
{0x00222220,0x02222000,0x00000000},
{0x02222000,0x00222000,0x00000000},
{0x22200000,0x00222000,0x00000000},
{0x22000000,0x02220000,0x00000000},
{0x20000000,0x02220000,0x00000000},
{0x00000000,0x02200000,0x00000000},
{0x00000000,0x02200000,0x00000000},
{0x00000000,0x22000000,0x00000000},
{0x00000000,0x22000000,0x00000000},
{0x00000000,0x20000000,0x00000000},
{0x00000000,0x20000000,0x00000000}
};

unsigned player_state6[26][3]=
{
{0x00000000,0x00000002,0x00000000},
{0x00000000,0x00000002,0x00000000},
{0x00000000,0x00000022,0x00000000},
{0x00000000,0x00000022,0x00000000},
{0x00000000,0x00000220,0x00000000},
{0x00000000,0x00002220,0x00000000},
{0x00000000,0x00002220,0x00000000},
{0x00000000,0x00022200,0x00000000},
{0x00000000,0x00222200,0x00000222},
{0x00000000,0x00222200,0x00222200},
{0x00000000,0x02222002,0x22222000},
{0x00000000,0x02222222,0x22200000},
{0x00000000,0x22222222,0x22000000},
{0x00000002,0x22222222,0x20000000},
{0x00000002,0x22222220,0x00000000},
{0x00000022,0x22222200,0x00000000},
{0x00000222,0x22222000,0x00000000},
{0x00000222,0x22220000,0x00000000},
{0x00002222,0x22000000,0x00000000},
{0x00002222,0x20000000,0x00000000},
{0x00022220,0x00000000,0x00000000},
{0x00022200,0x00000000,0x00000000},
{0x00220000,0x00000000,0x00000000},
{0x02200000,0x00000000,0x00000000},
{0x22000000,0x00000000,0x00000000},
{0x20000000,0x00000000,0x00000000}
};
unsigned player_state3[26][3]=
{
{0x22000000,0x00000000,0x00000000},
{0x02200000,0x00000000,0x00000000},
{0x00222000,0x00000000,0x00000000},
{0x00222220,0x00000000,0x00000000},
{0x00022222,0x00000000,0x00000000},
{0x00002222,0x22000000,0x00000000},
{0x00000222,0x22220000,0x00000000},
{0x00000022,0x22222200,0x00000000},
{0x00000002,0x22222222,0x00000000},
{0x00000000,0x22222222,0x22000000},
{0x00000000,0x02222222,0x22220000},
{0x00000000,0x02222222,0x22222200},
{0x00000000,0x00222222,0x22222222},
{0x00000000,0x00222222,0x22222222},
{0x00000000,0x02222222,0x22222200},
{0x00000000,0x02222222,0x22220000},
{0x00000000,0x22222222,0x22000000},
{0x00000002,0x22222222,0x00000000},
{0x00000022,0x22222200,0x00000000},
{0x00000222,0x22220000,0x00000000},
{0x00002222,0x22000000,0x00000000},
{0x00022222,0x00000000,0x00000000},
{0x00222220,0x00000000,0x00000000},
{0x00222000,0x00000000,0x00000000},
{0x02200000,0x00000000,0x00000000},
{0x22000000,0x00000000,0x00000000}
};
unsigned player_state7[26][3]=
{
{0x00000000,0x00000000,0x00000022},
{0x00000000,0x00000000,0x00000220},
{0x00000000,0x00000000,0x00022200},
{0x00000000,0x00000000,0x00222200},
{0x00000000,0x00000000,0x22222000},
{0x00000000,0x00000022,0x22220000},
{0x00000000,0x00002222,0x22200000},
{0x00000000,0x00022222,0x22000000},
{0x00000000,0x02222222,0x22000000},
{0x00000002,0x22222222,0x20000000},
{0x00000222,0x22222222,0x00000000},
{0x00222222,0x22222220,0x00000000},
{0x22222222,0x22222200,0x00000000},
{0x22222222,0x22222200,0x00000000},
{0x00222222,0x22222220,0x00000000},
{0x00000222,0x22222222,0x00000000},
{0x00000002,0x22222222,0x20000000},
{0x00000000,0x02222222,0x22000000},
{0x00000000,0x00022222,0x22000000},
{0x00000000,0x00002222,0x22200000},
{0x00000000,0x00000022,0x22220000},
{0x00000000,0x00000000,0x22222000},
{0x00000000,0x00000000,0x00222200},
{0x00000000,0x00000000,0x00022200},
{0x00000000,0x00000000,0x00000220},
{0x00000000,0x00000000,0x00000022}
};
unsigned player_state4[26][3]=
{
{0x00000000,0x20000000,0x00000000},
{0x00000000,0x20000000,0x00000000},
{0x00000000,0x22000000,0x00000000},
{0x00000000,0x22000000,0x00000000},
{0x00000000,0x02200000,0x00000000},
{0x00000000,0x02220000,0x00000000},
{0x00000000,0x02220000,0x00000000},
{0x00000000,0x02222000,0x00000000},
{0x22000000,0x02222000,0x00000000},
{0x02222200,0x00222200,0x00000000},
{0x00022222,0x00222220,0x00000000},
{0x00002222,0x22222220,0x00000000},
{0x00000022,0x22222222,0x00000000},
{0x00000002,0x22222222,0x20000000},
{0x00000000,0x22222222,0x20000000},
{0x00000000,0x00222222,0x22000000},
{0x00000000,0x00022222,0x22000000},
{0x00000000,0x00000222,0x22200000},
{0x00000000,0x00000022,0x22220000},
{0x00000000,0x00000002,0x22220000},
{0x00000000,0x00000000,0x02222000},
{0x00000000,0x00000000,0x00222000},
{0x00000000,0x00000000,0x00022200},
{0x00000000,0x00000000,0x00002220},
{0x00000000,0x00000000,0x00000022},
{0x00000000,0x00000000,0x00000002}
};
unsigned player_state8[26][3]=
{
{0x20000000,0x00000000,0x00000000},
{0x02200000,0x00000000,0x00000000},
{0x02220000,0x00000000,0x00000000},
{0x00222000,0x00000000,0x00000000},
{0x00022200,0x00000000,0x00000000},
{0x00022222,0x00000000,0x00000000},
{0x00002222,0x20000000,0x00000000},
{0x00000222,0x22000000,0x00000000},
{0x00000222,0x22200000,0x00000000},
{0x00000022,0x22222000,0x00000000},
{0x00000002,0x22222200,0x00000000},
{0x00000002,0x22222220,0x00000000},
{0x00000000,0x22222222,0x20000000},
{0x00000000,0x22222222,0x22000000},
{0x00000000,0x02222222,0x22200000},
{0x00000000,0x00222200,0x02222000},
{0x00000000,0x00222200,0x00022200},
{0x00000000,0x00022200,0x00000220},
{0x00000000,0x00022200,0x00000022},
{0x00000000,0x00002200,0x00000002},
{0x00000000,0x00000220,0x00000000},
{0x00000000,0x00000220,0x00000000},
{0x00000000,0x00000220,0x00000000},
{0x00000000,0x00000022,0x00000000},
{0x00000000,0x00000002,0x00000000},
{0x00000000,0x00000002,0x00000000}
};


void init_colors()
{
	/* Define colors */
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0x000000);	//color 0
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14, 0x808080);	//color 1
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0xffffff);	//color 2
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x1C, 0xa0a0a0);	//color 3 siva
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x20, 0x00ffff);	//color 4
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x24, 0xff00ff);	//color 5
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x28, 0xffff00);	//color 6
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x2C, 0x000000);	//color 7
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x30, 0xffffff);	//color 8
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x34, 0xff1493);	//color 9
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x38, 0xff6666);	//color 10 A
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x3C, 0x556b2f);	//color 11 B
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x40, 0x191970);	//color 12 C
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x44, 0xb8860b);	//color 13 D
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x48, 0xffe4c4);	//color 14 E
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x4C, 0xd2691e);	//color 15 F
}

void create_asteroids(){
	int i,x;
	max_asteroids_on_level = 90;
	current_asteroid_on_field = 0;
	max_asteroids_on_field = level * ASTEROID_INIT_COUNT;
	for(i = 0; i< 100; i++){
		if(i<max_asteroids_on_field){
			destroyed_asteroids[i] = 0;
		}else{
			destroyed_asteroids[i] = 1;
		}
	}

	for(i=0; i<max_asteroids_on_level; i++){
		x=rand()%2;
	if(x)
		{
			asteroid_field[i].X_coordinate= 4 + rand()%5;
		}
	else
	{
		asteroid_field[i].X_coordinate= 74 - rand()%5;
	}
	asteroid_field[i].Y_coordinate=rand()% (12-3) + 3;

	if(asteroid_field[i].X_coordinate>39){
		asteroid_field[i].asteroid_direction = 0;
	}
	else{
		asteroid_field[i].asteroid_direction = 1;
	}
	asteroid_field[i].asteroid_speed = 2;
	asteroid_field[i].type = rand()%(3-0);
	asteroid_field[i].id = i;
}
}

void move_asteroids()
{
	int i;
	for(i=0; i<current_asteroid_on_field; i++){
		//current_asteroid_on_field++;
		if(!destroyed_asteroids[asteroid_field[i].id]){
			erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, asteroid_field[i].X_coordinate, asteroid_field[i].Y_coordinate);
				if(asteroid_field[i].asteroid_direction == 0)
				{
						asteroid_field[i].X_coordinate--;
						if(asteroid_field[i].X_coordinate == 40){
							 destroyed_asteroids[asteroid_field[i].id] = 1;
							 if(current_asteroid_on_field +1 != max_asteroids_on_level){
								 current_asteroid_on_field++;
							 }

							 destroyed_asteroids[asteroid_field[current_asteroid_on_field].id] = 0;
							 erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, asteroid_field[i].X_coordinate-1, asteroid_field[i].Y_coordinate);
							 lives--;
							 break;
						}
				}
				else
				{
					asteroid_field[i].X_coordinate++;
					if(asteroid_field[i].X_coordinate == 39){
						destroyed_asteroids[asteroid_field[i].id] = 1;
						if(current_asteroid_on_field +1 != max_asteroids_on_level){
							current_asteroid_on_field++;
													 }

						 destroyed_asteroids[asteroid_field[current_asteroid_on_field].id] = 0;
						erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, asteroid_field[i].X_coordinate-1, asteroid_field[i].Y_coordinate);
						lives--;
						break;
						}
				}

				if(projectile.is_Bullet == 1){
					if(projectile.bullet_dir == 1){
						if(projectile.bullet_X < 76){
						projectile.bullet_X++;
						erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, projectile.bullet_X-1, projectile.bullet_Y);
						} else{
							projectile.is_Bullet = 0;
						}
					} else if(projectile.bullet_dir == 2){
						if(projectile.bullet_X > 4){
							projectile.bullet_X--;
							erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, projectile.bullet_X+1, projectile.bullet_Y);
						}
						 else{
									projectile.is_Bullet = 0;
								}
					}
				}


				if( asteroid_field[i].X_coordinate == projectile.bullet_X && asteroid_field[i].Y_coordinate == projectile.bullet_Y){
					score+=10;
					destroyed_asteroids[asteroid_field[i].id] = 1;
					projectile.is_Bullet = 0;
					if(current_asteroid_on_field +1 != max_asteroids_on_level){
						current_asteroid_on_field++;
					}
					destroyed_asteroids[asteroid_field[current_asteroid_on_field].id] = 0;
					erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, asteroid_field[i].X_coordinate-1, asteroid_field[i].Y_coordinate);
					break;

			}

				switch(projectile.bullet_dir){

				case 1:
					draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, projectile.bullet_X,projectile.bullet_Y, bullet_right);
					break;
				case 2:
					draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, projectile.bullet_X,projectile.bullet_Y, bullet_left);
					break;
				default:
					break;
				}

				switch (asteroid_field[i].type) {
				case 0:
					draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, asteroid_field[i].X_coordinate,asteroid_field[i].Y_coordinate, asteroid_t1);
					break;
				case 1:
					draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, asteroid_field[i].X_coordinate,asteroid_field[i].Y_coordinate, asteroid_t2);
					break;
				default:
					draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, asteroid_field[i].X_coordinate,asteroid_field[i].Y_coordinate, asteroid_t3);
					break;
			}
					}
		}
	}



void init_variables(Xuint8* spaceship_dir, Xuint8* invader_dir, Xuint8* invader_dir_chng, Xuint8* row)
{
	int i, j;

	/* Init all arrays and variables */
	for(i = 0; i < INIT_ROWS + level - 1; i++)
	{
		invader_dir[i] = RIGHT;
		invader_dir_chng[i] = 1;
		row[i] = i + INVADER_INIT_ROW;
		flag_row[i] = 0;
	}

	spaceship_speed_cnt = 0;
	projectil_speed = 0;
	spaceship_flag = 0;
	projectil_flag = 0;
	invader_speed = 0;
	shoot_flag = 0;
	invader_shoot_flag = 0;
	counter = 0;
	invaders_num = INIT_NUM + INIT_COLS*(level-1);
	game_over = 0;
	move_faster = 0,
	seed = 0;
	input = 0;

	if(level - 1 == 0)
	{
		*spaceship_dir = 0;
		spaceship_x = 7;
		lives = INIT_LIVES;
	}

	for(i = 0; i < MAX_PROJECTILES_X; i++)
	{
		projectiles_of_ship_num[i] = 0;
		projectiles_of_invaders_num[i] = 0;

		for(j = 0; j < MAX_PROJECTILES_Y; j++)
		{
			projectiles_map[i][j] = 0;
			invaders_map[i][j] = 0;
		}
	}
}

void init_draw()
{
	int i, j;

	//if(level - 1 == 0)
	for(i = 0; i < SHIP_Y+1; i++)
	{
		for(j = 1; j < MAX_SHIP_X; j++)
		{
			if(j == 2 && i == 1 )
			{
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, j, i, border_upper_left);
			}
			if(j > 2 && j<76 && i == 1)
			{
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, j, i, border_horizontal);
			}
			if(j == 77 && i == 1)
			{
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, j, i, border_upper_right);
			}
			if(j == 2 && i > 1 && i<14)
			{
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, j, i, border_vertical_left);
			}
			if(j == 2 && i == 14)
			{
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, j, i, border_lover_left);
			}
			if(j > 2 && j < 77 && i == 14)
			{
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, j, i, border_horizontal_lower);
			}
			if(j == 77  && i == 14)
			{
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, j, i, border_lover_right);
			}

			if(j == 77 && i >1 && i < 14)
						{
							draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, j, i, border_vertical_right);
						}
			if(j == 39 && i >1 && i < 14)
					{
						draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, j, i, home_base);
					}

		}

				}
	}


void clear_text_screen(Xuint32 BaseAddress)
{
   	int i;

    for (i = 0; i < 4800; i++)
    {
        VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + i*4, 0x20);
    }
}

void print_string(Xuint32 BaseAddress, char string_s[], int lenght)
{
    int i;

    for (i = 0; i < lenght; i++)
    {
        VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + cursor_position + i*4, (string_s[i]-0x40));
    }
}

void set_cursor(Xuint32 new_value)
{
    cursor_position = new_value;
}

int num_len(int num)
{
	int len = 0;

	if(num == 0)
	{
		len++;
	}
	else
	{
		while(num > 0)
		{
			num /= 10;
			len++;
		}
	}

	return len;
}

void num_to_str(char *s, unsigned long bin, unsigned char n)
{
    s += n;
    *s = '\0';

    while (n--)
    {
        --s;
    	*s = (bin % 10) + '0';
        bin /= 10;
    }
}



int main()
{
	/*************************/
	/* VARIABLES DECLARATION */
	/*************************/

	/*Xuint8 i, j, k1, k2, k3;
	Xuint8 spaceship_dir;
	Xuint8 invader_x;

	Xuint8* row;
	Xuint8* invader_dir;
	Xuint8* invader_dir_chng;


	int old_lives = 0, old_invaders_num = 0, old_level = -1;
	int score = 0, old_score = 0;
	char* str = NULL;



	init_platform();
	init_interrupt_controller();
	init_colors();

	clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);

	while(1)
	{
		clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);


		VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0b01);    //text mode

		set_cursor(8115);
		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "PRESS KEY DOWN TO START", strlen("PRESS KEY DOWN TO START"));

		while(input != 30)	//wait for input from user
		{
			input = VGA_PERIPH_MEM_mReadMemory(XPAR_MY_PERIPHERAL_0_BASEADDR);
			seed++;
		}
		srand(seed);


		VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0b11);	//display and text mode
		set_cursor(666);
		clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "SCORE", strlen("SCORE"));

		set_cursor(688);
		num_to_str(str, 0, num_len(0));
		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));

		set_cursor(710);
		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "LIVES", strlen("LIVES"));

		set_cursor(732);
		num_to_str(str, lives, num_len(lives));
		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));

		set_cursor(751);
		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "LEVEL", strlen("LEVEL"));

		game_over = 0;
		level = 0;
		print_level = 0;
		old_level = -1;
		score = 0;
		old_score = 0;
		j = 1;

		while(!game_over)
		{
			print_level++;

			if(level < 4)
			{
				level++;
			}

			old_score += score;

			row = (Xuint8*) malloc((INIT_ROWS+level-1)*sizeof(Xuint8));
			invader_dir = (Xuint8*) malloc((INIT_ROWS+level-1)*sizeof(Xuint8));
			invader_dir_chng = (Xuint8*) malloc((INIT_ROWS+level-1)*sizeof(Xuint8));

			init_variables(&spaceship_dir, invader_dir, invader_dir_chng, row);
			generate_init_invaders_positions();

			clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);

			if(level > 1)
			{
				for(k1 = 0; k1 < 230; k1++)
					for(k2 = 0; k2 < 230; k2++)
						for(k3 = 0; k3 < 20; k3++)
						{
							set_cursor(6543);
							print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "NEXT LEVEL", 10);
						}
				clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
				set_cursor(666);
				clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
				print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "SCORE", strlen("SCORE"));

				set_cursor(688);
				num_to_str(str, 0, num_len(0));
				print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));

				set_cursor(710);
				print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "LIVES", strlen("LIVES"));

				set_cursor(732);
				num_to_str(str, lives, num_len(lives));
				print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));

				set_cursor(751);
				print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "LEVEL", strlen("LEVEL"));

			}

			init_draw(row);

			while(!((invaders_num == 0) || (game_over == 1)))
			{
				switch(input)
				{
					case LEFT_JOY:
							spaceship_dir = LEFT;
							spaceship_speed = 4;
							break;

					case RIGHT_JOY:
							spaceship_dir = RIGHT;
							spaceship_speed = 4;
							break;

					case MIDDLE_JOY:
							if(shoot_flag == 0)
							{
								shoot_projectile_from_ship(spaceship_x);
								shoot_flag = SHOOT_SPEED;
							}
							break;
				}

				if(input != LEFT_JOY && input != RIGHT_JOY) //STISNUT NEKI JOY
				{
					spaceship_speed = 8;
				}


				if(spaceship_flag)	//time to move spaceship
				{
					move_spaceship(&spaceship_dir);
					spaceship_flag = 0;
				}

				if(projectil_flag)	//time to move projectiles
				{
					move_projectile_from_ship();
					move_projectile_from_invader();
					projectil_flag = 0;
				}

				if(invader_shoot_flag)
				{
					invader_x = rand()%80;
					shoot_projectile_from_invader(invader_x, row);
					invader_shoot_flag = 0;
				}

				for(i = 0; i < INIT_ROWS + level - 1; i++)
				{
					if(flag_row[i])	//time to move this row of invaders?
					{
						if(invader_dir_chng[i] == DOWN)	//time to move rows down?
						{
							invader_dir_chng[i]++;
							move_invaders_down(row, i);
						}
						else							//if not, move rows left/right
							move_invaders_row(row, invader_dir, invader_dir_chng, i);

						flag_row[i] = 0;
					}
				}

				if(old_invaders_num != invaders_num)
				{
					set_cursor(688);
					score = (INIT_NUM + INIT_COLS*(level-1) - invaders_num)*10;
					num_to_str(str, score + old_score, num_len(score + old_score));
					print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));
					old_invaders_num = invaders_num;

					if(score + old_score > 500*j)
					{
						j++;
						lives++;
					}
				}

				if(old_lives != lives)
				{
					set_cursor(732);
					num_to_str(str, lives, num_len(lives));
					print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));
					old_lives = lives;
				}

				if(old_level != print_level)
				{
					set_cursor(751 + 24);
					num_to_str(str, print_level, num_len(print_level));
					print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));
					old_level = print_level;
				}
			}

			free(row);
			free(invader_dir);
			free(invader_dir_chng);
		}

		VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0b01);    //text mode
		clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);

		set_cursor(3660);
		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "GAME OVER", 9);

		set_cursor(6543);
		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "SCORE", 5);

		set_cursor(6543 + 24);
		num_to_str(str, score + old_score, num_len(score + old_score));
		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, num_len(score + old_score));

	}*/

	Xuint8 i, j;
	char* str = NULL;
	Xuint8 x_crdnt = 0, y_crdnt = 0;
	Xuint8 k = x_crdnt;
	Xuint8 game_over = 0;
	Xuint8 spaceship_dir,current_spaceship_state , spaceship_height = 7;
	int current_state=0;
	int x=1;
	int print_level = 1;
	int lives_flag = 0;

	init_platform();
	init_interrupt_controller();
	init_colors();

	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0b11); //display and text mode
	clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
	clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
	set_cursor(3660);
	print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "PRESS DOWN", 10);


	while(input != 30)	//wait for input from user
			{
				input = VGA_PERIPH_MEM_mReadMemory(XPAR_MY_PERIPHERAL_0_BASEADDR);
				seed++;
			}
	srand(seed);



	clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);



	set_cursor(666);
	clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
	print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "SCORE", strlen("SCORE"));

	set_cursor(688);
	num_to_str(str, 0, num_len(0));
	print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));

	set_cursor(710);
	print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "LIVES", strlen("LIVES"));

	set_cursor(732);
	num_to_str(str, lives, num_len(lives));
	print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));

	set_cursor(751);
	print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "LEVEL", strlen("LEVEL"));

	set_cursor(773);
	num_to_str(str, level, num_len(level));
	print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));

	clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);

	init_draw();
	draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x+119, SHIP_Y-7, player_state1);

	create_asteroids();
	current_asteroid_on_field = max_asteroids_on_field;
	spaceship_flag = 0;
	projectil_flag = 0;
	shoot_flag = 0;
	lives = 50;
	while(1){



		/*
*/

		while(!game_over) {
			switch(input)
									{
										case LEFT_JOY:
											if(current_state == 0){
												spaceship_dir = 3;
												//spaceship_speed = 4;
												current_state = 1;
											}
												break;

										case RIGHT_JOY:
											if(current_state == 0){
												spaceship_dir = 7;
												//spaceship_speed = 4;
												current_state = 2;
											}
												break;

										case DOWN_JOY:
											if(current_state == 0){
												spaceship_height++;
												spaceship_dir = 5;
												current_state=3;
												if(spaceship_height > 13){
													spaceship_height = 2;
													erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x+119,SHIP_Y - 1);
													draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x+119, SHIP_Y - 1, home_base);
												}else{
													erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x+119, spaceship_height -1);
													draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x+119, spaceship_height - 1, home_base);
												}



											}
												break;

										case MIDDLE_JOY:
											if(projectile.is_Bullet == 0){
												if(spaceship_dir == 3){
													projectile.bullet_X = 40;
													projectile.bullet_Y = spaceship_height;
													projectile.bullet_dir = 1;
													projectile.is_Bullet = 1;
												} else if(spaceship_dir == 7){
													projectile.bullet_X = 38;
													projectile.bullet_Y = spaceship_height;
													projectile.bullet_dir = 2;
													projectile.is_Bullet = 1;
												} else{
													projectile.bullet_X = 39;
													projectile.bullet_Y = spaceship_height;
													projectile.bullet_dir = 0;
													//projectile.is_Bullet = 0;
												}
											}
											break;
										case UP_JOY:
											if(current_state == 0){
												spaceship_height--;
												spaceship_dir = 1;
												current_state=4;
												if(spaceship_height  < 2){
													spaceship_height = 13;
													erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x+119, 2);
													draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x+119, 2, home_base);
												}else{
													erase_square(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x+119, spaceship_height +1);
													draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x+119, spaceship_height + 1, home_base);
												}

											}
											break;

										default:
												current_state = 0;
												break;
									}


			if(spaceship_flag){
				move_asteroids();
				spaceship_flag = 0;
			}

			if(current_asteroid_on_field == 10 * x){
				print_level++;
				x++;
				if(spaceship_speed >= 2)
					spaceship_speed -=2;
			}
			current_spaceship_state = spaceship_dir-1;
			switch(current_spaceship_state) {
			case 0:
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, 39, spaceship_height, player_state1);
				break;
			case 1:
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, 39, spaceship_height, player_state2);
				break;
			case 2:
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, 39, spaceship_height, player_state3);
				break;
			case 3:
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, 39, spaceship_height, player_state4);
				break;
			case 4:
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, 39, spaceship_height, player_state5);
				break;
			case 5:
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x+119, spaceship_height, player_state6);
				break;
			case 6:
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x+119, spaceship_height, player_state7);
				break;
			case 7:
				draw_bitmap(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, spaceship_x+119, spaceship_height, player_state8);
				break;
			}

			if(lives < 10 && lives_flag == 0){
				set_cursor(732);
				print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "  ", 2);
				lives_flag++;
			}

			set_cursor(732);
			num_to_str(str, lives, num_len(lives));
			print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));

			set_cursor(688);
			num_to_str(str, score, num_len(score));
			print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));


			set_cursor(751 + 24);
			num_to_str(str, print_level, num_len(print_level));
			print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, str, strlen(str));


			if(lives == 0){
				game_over=1;
			}
		}
		clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
		set_cursor(3660);
		print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, "GAME OVER", 9);

	}

    return 0;
}

