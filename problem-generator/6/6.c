#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
static int sDidOverflow = 0;
typedef unsigned long my_uint;
#define MAX_CACHED_POWER 130
struct PrimePower_t {
unsigned short powers[MAX_CACHED_POWER - 2];
unsigned char overflows[MAX_CACHED_POWER - 2];
} sPowers[126];
#define MAX_FACTOR_COUNT 6
struct PrimeFactorization_t {
unsigned char productOfOnePlusMultiplicities;
unsigned char isPrime;
unsigned char powerIndexesPlusOne[MAX_FACTOR_COUNT];
unsigned char multiplicities[MAX_FACTOR_COUNT];
char padding[2];
};
static const unsigned short sPrimesTable[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701};
static const my_uint sPerfectSquares[] = {0,1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256,289,324,361,400,441,484,529,576,625,676,729,784,841,900,961,1024,1089,1156,1225,1296,1369,1444,1521,1600,1681,1764,1849,1936,2025,2116,2209,2304,2401,2500,2601,2704,2809,2916,3025,3136,3249,3364,3481,3600,3721,3844,3969,4096,4225,4356,4489,4624,4761,4900,5041,5184,5329,5476,5625,5776,5929,6084,6241,6400,6561,6724,6889,7056,7225,7396,7569,7744,7921,8100,8281,8464,8649,8836,9025,9216,9409,9604,9801,10000,10201,10404,10609,10816,11025,11236,11449,11664,11881,12100,12321,12544,12769,12996,13225,13456,13689,13924,14161,14400,14641,14884,15129,15376,15625,15876,16129,16384,16641,16900,17161,17424,17689,17956,18225,18496,18769,19044,19321,19600,19881,20164,20449,20736,21025,21316,21609,21904,22201,22500,22801,23104,23409,23716,24025,24336,24649,24964,25281,25600,25921,26244,26569,26896,27225,27556,27889,28224,28561,28900,29241,29584,29929,30276,30625,30976,31329,31684,32041,32400,32761,33124,33489,33856,34225,34596,34969,35344,35721,36100,36481,36864,37249,37636,38025,38416,38809,39204,39601,40000,40401,40804,41209,41616,42025,42436,42849,43264,43681,44100,44521,44944,45369,45796,46225,46656,47089,47524,47961,48400,48841,49284,49729,50176,50625,51076,51529,51984,52441,52900,53361,53824,54289,54756,55225,55696,56169,56644,57121,57600,58081,58564,59049,59536,60025,60516,61009,61504,62001,62500,63001,63504,64009,64516,65025,65536,66049,66564,67081,67600,68121,68644,69169,69696,70225,70756,71289,71824,72361,72900,73441,73984,74529,75076,75625,76176,76729,77284,77841,78400,78961,79524,80089,80656,81225,81796,82369,82944,83521,84100,84681,85264,85849,86436,87025,87616,88209,88804,89401,90000,90601,91204,91809,92416,93025,93636,94249,94864,95481,96100,96721,97344,97969,98596,99225,99856,100489,101124,101761,102400,103041,103684,104329,104976,105625,106276,106929,107584,108241,108900,109561,110224,110889,111556,112225,112896,113569,114244,114921,115600,116281,116964,117649,118336,119025,119716,120409,121104,121801,122500,123201,123904,124609,125316,126025,126736,127449,128164,128881,129600,130321,131044,131769,132496,133225,133956,134689,135424,136161,136900,137641,138384,139129,139876,140625,141376,142129,142884,143641,144400,145161,145924,146689,147456,148225,148996,149769,150544,151321,152100,152881,153664,154449,155236,156025,156816,157609,158404,159201,160000,160801,161604,162409,163216,164025,164836,165649,166464,167281,168100,168921,169744,170569,171396,172225,173056,173889,174724,175561,176400,177241,178084,178929,179776,180625,181476,182329,183184,184041,184900,185761,186624,187489,188356,189225,190096,190969,191844,192721,193600,194481,195364,196249,197136,198025,198916,199809,200704,201601,202500,203401,204304,205209,206116,207025,207936,208849,209764,210681,211600,212521,213444,214369,215296,216225,217156,218089,219024,219961,220900,221841,222784,223729,224676,225625,226576,227529,228484,229441,230400,231361,232324,233289,234256,235225,236196,237169,238144,239121,240100,241081,242064,243049,244036,245025,246016,247009,248004,249001,250000,251001,252004,253009,254016,255025,256036,257049,258064,259081,260100,261121,262144,263169,264196,265225,266256,267289,268324,269361,270400,271441,272484,273529,274576,275625,276676,277729,278784,279841,280900,281961,283024,284089,285156,286225,287296,288369,289444,290521,291600,292681,293764,294849,295936,297025,298116,299209,300304,301401,302500,303601,304704,305809,306916,308025,309136,310249,311364,312481,313600,314721,315844,316969,318096,319225,320356,321489,322624,323761,324900,326041,327184,328329,329476,330625,331776,332929,334084,335241,336400,337561,338724,339889,341056,342225,343396,344569,345744,346921,348100,349281,350464,351649,352836,354025,355216,356409,357604,358801,360000,361201,362404,363609,364816,366025,367236,368449,369664,370881,372100,373321,374544,375769,376996,378225,379456,380689,381924,383161,384400,385641,386884,388129,389376,390625,391876,393129,394384,395641,396900,398161,399424,400689,401956,403225,404496,405769,407044,408321,409600,410881,412164,413449,414736,416025,417316,418609,419904,421201,422500,423801,425104,426409,427716,429025,430336,431649,432964,434281,435600,436921,438244,439569,440896,442225,443556,444889,446224,447561,448900,450241,451584,452929,454276,455625,456976,458329,459684,461041,462400,463761,465124,466489,467856,469225,470596,471969,473344,474721,476100,477481,478864,480249,481636,483025,484416,485809,487204,488601,490000,491401,492804,494209,495616,497025,498436,499849,501264};
static struct PrimeFactorization_t *sPrimeFactorizations;
static my_uint usqrt(my_uint val) {
my_uint left = 0, right = sizeof sPerfectSquares / sizeof *sPerfectSquares;
while (left + 1 < right) {
my_uint midIndex = (left + right) / 2;
my_uint midValue = sPerfectSquares[midIndex];
if (midValue > val) {
right = midIndex;
}
else if (midValue < val) {
left = midIndex;
}
else {
return midIndex;
}
}
return left;
}
static inline my_uint mod10000(my_uint num) {
if (num >= 10000) {
sDidOverflow = 1;
return num % 10000;
}
return num;
}
static inline my_uint sm(my_uint a, my_uint b) {
return mod10000(a * b);
}
static inline my_uint ipower_loop_mod10000(my_uint num, my_uint power) {
my_uint base = num;
my_uint result = 1;
while (power > 0) {
if (power & 1) result = sm(result, base);
base = sm(base, base);
power >>= 1;
}
return result;
}
static my_uint ipower_compute_mod10000(my_uint num, my_uint power) {
if (power == 1 || num == 1) return num;
switch (power) {
case 2:
{
my_uint t2 = sm(num, num);
return t2;
}
case 3:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
return t3;
}
case 4:
{
my_uint t2 = sm(num, num);
my_uint t4 = sm(t2, t2);
return t4;
}
case 5:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
return t5;
}
case 6:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
return t6;
}
case 7:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
return t7;
}
case 8:
{
my_uint t2 = sm(num, num);
my_uint t4 = sm(t2, t2);
my_uint t8 = sm(t4, t4);
return t8;
}
case 9:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t9 = sm(t3, t6);
return t9;
}
case 10:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
return t10;
}
case 11:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t11 = sm(num, t10);
return t11;
}
case 12:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t12 = sm(t6, t6);
return t12;
}
case 13:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t13 = sm(t3, t10);
return t13;
}
case 14:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
return t14;
}
case 15:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t15 = sm(t5, t10);
return t15;
}
case 16:
{
my_uint t2 = sm(num, num);
my_uint t4 = sm(t2, t2);
my_uint t8 = sm(t4, t4);
my_uint t16 = sm(t8, t8);
return t16;
}
case 17:
{
my_uint t2 = sm(num, num);
my_uint t4 = sm(t2, t2);
my_uint t8 = sm(t4, t4);
my_uint t16 = sm(t8, t8);
my_uint t17 = sm(num, t16);
return t17;
}
case 18:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t9 = sm(t3, t6);
my_uint t18 = sm(t9, t9);
return t18;
}
case 19:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t19 = sm(t5, t14);
return t19;
}
case 20:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t20 = sm(t10, t10);
return t20;
}
case 21:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t21 = sm(t7, t14);
return t21;
}
case 22:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t11 = sm(num, t10);
my_uint t22 = sm(t11, t11);
return t22;
}
case 23:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t13 = sm(t3, t10);
my_uint t23 = sm(t10, t13);
return t23;
}
case 24:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t12 = sm(t6, t6);
my_uint t24 = sm(t12, t12);
return t24;
}
case 25:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t15 = sm(t5, t10);
my_uint t25 = sm(t10, t15);
return t25;
}
case 26:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t13 = sm(t3, t10);
my_uint t26 = sm(t13, t13);
return t26;
}
case 27:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t9 = sm(t3, t6);
my_uint t18 = sm(t9, t9);
my_uint t27 = sm(t9, t18);
return t27;
}
case 28:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t28 = sm(t14, t14);
return t28;
}
case 29:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t28 = sm(t14, t14);
my_uint t29 = sm(num, t28);
return t29;
}
case 30:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t15 = sm(t5, t10);
my_uint t30 = sm(t15, t15);
return t30;
}
case 31:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t28 = sm(t14, t14);
my_uint t31 = sm(t3, t28);
return t31;
}
case 32:
{
my_uint t2 = sm(num, num);
my_uint t4 = sm(t2, t2);
my_uint t8 = sm(t4, t4);
my_uint t16 = sm(t8, t8);
my_uint t32 = sm(t16, t16);
return t32;
}
case 33:
{
my_uint t2 = sm(num, num);
my_uint t4 = sm(t2, t2);
my_uint t8 = sm(t4, t4);
my_uint t16 = sm(t8, t8);
my_uint t17 = sm(num, t16);
my_uint t33 = sm(t16, t17);
return t33;
}
case 34:
{
my_uint t2 = sm(num, num);
my_uint t4 = sm(t2, t2);
my_uint t8 = sm(t4, t4);
my_uint t16 = sm(t8, t8);
my_uint t17 = sm(num, t16);
my_uint t34 = sm(t17, t17);
return t34;
}
case 35:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t21 = sm(t7, t14);
my_uint t35 = sm(t14, t21);
return t35;
}
case 36:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t9 = sm(t3, t6);
my_uint t18 = sm(t9, t9);
my_uint t36 = sm(t18, t18);
return t36;
}
case 37:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t9 = sm(t3, t6);
my_uint t18 = sm(t9, t9);
my_uint t36 = sm(t18, t18);
my_uint t37 = sm(num, t36);
return t37;
}
case 38:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t19 = sm(t5, t14);
my_uint t38 = sm(t19, t19);
return t38;
}
case 39:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t13 = sm(t3, t10);
my_uint t26 = sm(t13, t13);
my_uint t39 = sm(t13, t26);
return t39;
}
case 40:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t20 = sm(t10, t10);
my_uint t40 = sm(t20, t20);
return t40;
}
case 41:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t20 = sm(t10, t10);
my_uint t40 = sm(t20, t20);
my_uint t41 = sm(num, t40);
return t41;
}
case 42:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t21 = sm(t7, t14);
my_uint t42 = sm(t21, t21);
return t42;
}
case 43:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t20 = sm(t10, t10);
my_uint t40 = sm(t20, t20);
my_uint t43 = sm(t3, t40);
return t43;
}
case 44:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t11 = sm(num, t10);
my_uint t22 = sm(t11, t11);
my_uint t44 = sm(t22, t22);
return t44;
}
case 45:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t15 = sm(t5, t10);
my_uint t30 = sm(t15, t15);
my_uint t45 = sm(t15, t30);
return t45;
}
case 46:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t13 = sm(t3, t10);
my_uint t23 = sm(t10, t13);
my_uint t46 = sm(t23, t23);
return t46;
}
case 47:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t21 = sm(t7, t14);
my_uint t42 = sm(t21, t21);
my_uint t47 = sm(t5, t42);
return t47;
}
case 48:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t12 = sm(t6, t6);
my_uint t24 = sm(t12, t12);
my_uint t48 = sm(t24, t24);
return t48;
}
case 49:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t12 = sm(t6, t6);
my_uint t24 = sm(t12, t12);
my_uint t48 = sm(t24, t24);
my_uint t49 = sm(num, t48);
return t49;
}
case 50:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t15 = sm(t5, t10);
my_uint t25 = sm(t10, t15);
my_uint t50 = sm(t25, t25);
return t50;
}
case 51:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t12 = sm(t6, t6);
my_uint t24 = sm(t12, t12);
my_uint t48 = sm(t24, t24);
my_uint t51 = sm(t3, t48);
return t51;
}
case 52:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t13 = sm(t3, t10);
my_uint t26 = sm(t13, t13);
my_uint t52 = sm(t26, t26);
return t52;
}
case 53:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t13 = sm(t3, t10);
my_uint t26 = sm(t13, t13);
my_uint t52 = sm(t26, t26);
my_uint t53 = sm(num, t52);
return t53;
}
case 54:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t9 = sm(t3, t6);
my_uint t18 = sm(t9, t9);
my_uint t27 = sm(t9, t18);
my_uint t54 = sm(t27, t27);
return t54;
}
case 55:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t11 = sm(num, t10);
my_uint t22 = sm(t11, t11);
my_uint t44 = sm(t22, t22);
my_uint t55 = sm(t11, t44);
return t55;
}
case 56:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t28 = sm(t14, t14);
my_uint t56 = sm(t28, t28);
return t56;
}
case 57:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t19 = sm(t5, t14);
my_uint t38 = sm(t19, t19);
my_uint t57 = sm(t19, t38);
return t57;
}
case 58:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t28 = sm(t14, t14);
my_uint t29 = sm(num, t28);
my_uint t58 = sm(t29, t29);
return t58;
}
case 59:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t28 = sm(t14, t14);
my_uint t31 = sm(t3, t28);
my_uint t59 = sm(t28, t31);
return t59;
}
case 60:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t15 = sm(t5, t10);
my_uint t30 = sm(t15, t15);
my_uint t60 = sm(t30, t30);
return t60;
}
case 61:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t28 = sm(t14, t14);
my_uint t56 = sm(t28, t28);
my_uint t61 = sm(t5, t56);
return t61;
}
case 62:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t28 = sm(t14, t14);
my_uint t31 = sm(t3, t28);
my_uint t62 = sm(t31, t31);
return t62;
}
case 63:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t21 = sm(t7, t14);
my_uint t42 = sm(t21, t21);
my_uint t63 = sm(t21, t42);
return t63;
}
case 64:
{
my_uint t2 = sm(num, num);
my_uint t4 = sm(t2, t2);
my_uint t8 = sm(t4, t4);
my_uint t16 = sm(t8, t8);
my_uint t32 = sm(t16, t16);
my_uint t64 = sm(t32, t32);
return t64;
}
case 65:
{
my_uint t2 = sm(num, num);
my_uint t4 = sm(t2, t2);
my_uint t8 = sm(t4, t4);
my_uint t16 = sm(t8, t8);
my_uint t32 = sm(t16, t16);
my_uint t64 = sm(t32, t32);
my_uint t65 = sm(num, t64);
return t65;
}
case 66:
{
my_uint t2 = sm(num, num);
my_uint t4 = sm(t2, t2);
my_uint t8 = sm(t4, t4);
my_uint t16 = sm(t8, t8);
my_uint t17 = sm(num, t16);
my_uint t33 = sm(t16, t17);
my_uint t66 = sm(t33, t33);
return t66;
}
case 67:
{
my_uint t2 = sm(num, num);
my_uint t4 = sm(t2, t2);
my_uint t8 = sm(t4, t4);
my_uint t16 = sm(t8, t8);
my_uint t17 = sm(num, t16);
my_uint t33 = sm(t16, t17);
my_uint t66 = sm(t33, t33);
my_uint t67 = sm(num, t66);
return t67;
}
case 68:
{
my_uint t2 = sm(num, num);
my_uint t4 = sm(t2, t2);
my_uint t8 = sm(t4, t4);
my_uint t16 = sm(t8, t8);
my_uint t17 = sm(num, t16);
my_uint t34 = sm(t17, t17);
my_uint t68 = sm(t34, t34);
return t68;
}
case 69:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t13 = sm(t3, t10);
my_uint t23 = sm(t10, t13);
my_uint t46 = sm(t23, t23);
my_uint t69 = sm(t23, t46);
return t69;
}
case 70:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t21 = sm(t7, t14);
my_uint t35 = sm(t14, t21);
my_uint t70 = sm(t35, t35);
return t70;
}
case 71:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t19 = sm(t5, t14);
my_uint t38 = sm(t19, t19);
my_uint t57 = sm(t19, t38);
my_uint t71 = sm(t14, t57);
return t71;
}
case 72:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t9 = sm(t3, t6);
my_uint t18 = sm(t9, t9);
my_uint t36 = sm(t18, t18);
my_uint t72 = sm(t36, t36);
return t72;
}
case 73:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t9 = sm(t3, t6);
my_uint t18 = sm(t9, t9);
my_uint t36 = sm(t18, t18);
my_uint t37 = sm(num, t36);
my_uint t73 = sm(t36, t37);
return t73;
}
case 74:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t9 = sm(t3, t6);
my_uint t18 = sm(t9, t9);
my_uint t36 = sm(t18, t18);
my_uint t37 = sm(num, t36);
my_uint t74 = sm(t37, t37);
return t74;
}
case 75:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t15 = sm(t5, t10);
my_uint t25 = sm(t10, t15);
my_uint t50 = sm(t25, t25);
my_uint t75 = sm(t25, t50);
return t75;
}
case 76:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t19 = sm(t5, t14);
my_uint t38 = sm(t19, t19);
my_uint t76 = sm(t38, t38);
return t76;
}
case 77:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t19 = sm(t5, t14);
my_uint t38 = sm(t19, t19);
my_uint t76 = sm(t38, t38);
my_uint t77 = sm(num, t76);
return t77;
}
case 78:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t13 = sm(t3, t10);
my_uint t26 = sm(t13, t13);
my_uint t39 = sm(t13, t26);
my_uint t78 = sm(t39, t39);
return t78;
}
case 79:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t19 = sm(t5, t14);
my_uint t38 = sm(t19, t19);
my_uint t76 = sm(t38, t38);
my_uint t79 = sm(t3, t76);
return t79;
}
case 80:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t20 = sm(t10, t10);
my_uint t40 = sm(t20, t20);
my_uint t80 = sm(t40, t40);
return t80;
}
case 81:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t20 = sm(t10, t10);
my_uint t40 = sm(t20, t20);
my_uint t41 = sm(num, t40);
my_uint t81 = sm(t40, t41);
return t81;
}
case 82:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t20 = sm(t10, t10);
my_uint t40 = sm(t20, t20);
my_uint t41 = sm(num, t40);
my_uint t82 = sm(t41, t41);
return t82;
}
case 83:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t20 = sm(t10, t10);
my_uint t40 = sm(t20, t20);
my_uint t43 = sm(t3, t40);
my_uint t83 = sm(t40, t43);
return t83;
}
case 84:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t21 = sm(t7, t14);
my_uint t42 = sm(t21, t21);
my_uint t84 = sm(t42, t42);
return t84;
}
case 85:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t20 = sm(t10, t10);
my_uint t40 = sm(t20, t20);
my_uint t80 = sm(t40, t40);
my_uint t85 = sm(t5, t80);
return t85;
}
case 86:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t20 = sm(t10, t10);
my_uint t40 = sm(t20, t20);
my_uint t43 = sm(t3, t40);
my_uint t86 = sm(t43, t43);
return t86;
}
case 87:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t21 = sm(t7, t14);
my_uint t42 = sm(t21, t21);
my_uint t84 = sm(t42, t42);
my_uint t87 = sm(t3, t84);
return t87;
}
case 88:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t11 = sm(num, t10);
my_uint t22 = sm(t11, t11);
my_uint t44 = sm(t22, t22);
my_uint t88 = sm(t44, t44);
return t88;
}
case 89:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t21 = sm(t7, t14);
my_uint t42 = sm(t21, t21);
my_uint t47 = sm(t5, t42);
my_uint t89 = sm(t42, t47);
return t89;
}
case 90:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t15 = sm(t5, t10);
my_uint t30 = sm(t15, t15);
my_uint t45 = sm(t15, t30);
my_uint t90 = sm(t45, t45);
return t90;
}
case 91:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t21 = sm(t7, t14);
my_uint t35 = sm(t14, t21);
my_uint t70 = sm(t35, t35);
my_uint t91 = sm(t21, t70);
return t91;
}
case 92:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t13 = sm(t3, t10);
my_uint t23 = sm(t10, t13);
my_uint t46 = sm(t23, t23);
my_uint t92 = sm(t46, t46);
return t92;
}
case 93:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t28 = sm(t14, t14);
my_uint t31 = sm(t3, t28);
my_uint t62 = sm(t31, t31);
my_uint t93 = sm(t31, t62);
return t93;
}
case 94:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t21 = sm(t7, t14);
my_uint t42 = sm(t21, t21);
my_uint t47 = sm(t5, t42);
my_uint t94 = sm(t47, t47);
return t94;
}
case 95:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t7 = sm(t2, t5);
my_uint t14 = sm(t7, t7);
my_uint t19 = sm(t5, t14);
my_uint t38 = sm(t19, t19);
my_uint t57 = sm(t19, t38);
my_uint t95 = sm(t38, t57);
return t95;
}
case 96:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t12 = sm(t6, t6);
my_uint t24 = sm(t12, t12);
my_uint t48 = sm(t24, t24);
my_uint t96 = sm(t48, t48);
return t96;
}
case 97:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t12 = sm(t6, t6);
my_uint t24 = sm(t12, t12);
my_uint t48 = sm(t24, t24);
my_uint t49 = sm(num, t48);
my_uint t97 = sm(t48, t49);
return t97;
}
case 98:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t12 = sm(t6, t6);
my_uint t24 = sm(t12, t12);
my_uint t48 = sm(t24, t24);
my_uint t49 = sm(num, t48);
my_uint t98 = sm(t49, t49);
return t98;
}
case 99:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t6 = sm(t3, t3);
my_uint t12 = sm(t6, t6);
my_uint t24 = sm(t12, t12);
my_uint t48 = sm(t24, t24);
my_uint t51 = sm(t3, t48);
my_uint t99 = sm(t48, t51);
return t99;
}
case 100:
{
my_uint t2 = sm(num, num);
my_uint t3 = sm(num, t2);
my_uint t5 = sm(t2, t3);
my_uint t10 = sm(t5, t5);
my_uint t15 = sm(t5, t10);
my_uint t25 = sm(t10, t15);
my_uint t50 = sm(t25, t25);
my_uint t100 = sm(t50, t50);
return t100;
}
default: return ipower_loop_mod10000(num, power);
}
}
static my_uint ipower_mod10000(my_uint num, my_uint power, int powerIndex) {
if (power == 0) return 1;
if (power == 1 || num == 1) return num;
if (powerIndex == -1 || power >= MAX_CACHED_POWER) return ipower_compute_mod10000(num, power);
my_uint result = sPowers[powerIndex].powers[power - 2];
if (result == 0) {
int savedDidOverflow = sDidOverflow;
sDidOverflow = 0;
result = ipower_compute_mod10000(num, power);
sPowers[powerIndex].powers[power - 2] = result;
sPowers[powerIndex].overflows[power - 2] = sDidOverflow;
sDidOverflow = sDidOverflow || savedDidOverflow;
}
else {
sDidOverflow = sDidOverflow || sPowers[powerIndex].overflows[power - 2];
}
return result;
}
static void copy_factorization_with_additional_factor(my_uint srcIndex, my_uint targetIndex, unsigned char primeIndexPlusOne) {
int foundIt = 0;
my_uint i;
my_uint productOfOnePlusMultiplicities = sPrimeFactorizations[srcIndex].productOfOnePlusMultiplicities;
for (i=0; i < MAX_FACTOR_COUNT; i++) {
unsigned char existingPrimeIndexPlusOne = sPrimeFactorizations[srcIndex].powerIndexesPlusOne[i];
if (! existingPrimeIndexPlusOne) break;
unsigned char existingMultiplicity = sPrimeFactorizations[srcIndex].multiplicities[i];
if (existingPrimeIndexPlusOne == primeIndexPlusOne) {
existingMultiplicity++;
productOfOnePlusMultiplicities = (productOfOnePlusMultiplicities / existingMultiplicity) * (existingMultiplicity + 1);
foundIt = 1;
}
sPrimeFactorizations[targetIndex].multiplicities[i] = existingMultiplicity;
sPrimeFactorizations[targetIndex].powerIndexesPlusOne[i] = existingPrimeIndexPlusOne;
}
if (! foundIt) {
sPrimeFactorizations[targetIndex].powerIndexesPlusOne[i] = primeIndexPlusOne;
sPrimeFactorizations[targetIndex].multiplicities[i] = 1;
productOfOnePlusMultiplicities *= 2;
}
sPrimeFactorizations[targetIndex].productOfOnePlusMultiplicities = productOfOnePlusMultiplicities;
}
#define TEST(prime, primeIndex) do { \
if ((prime) * (prime) > remainingNum) goto noRemainingFactors;\
while (remainingNum % (prime) == 0) {\
subfactorizations[subfactorIndex] = remainingNum;\
subfactors[subfactorIndex] = (prime);\
primeIndexes[subfactorIndex] = 1 + (primeIndex);\
remainingNum /= (prime);\
subfactorIndex++;\
if (remainingNum == 1 || PrimeFactorizations[remainingNum].productOfOnePlusMultiplicities) goto foundSubfactorization;\
}\
} while (0)
static void compute_prime_factors(my_uint num) {
my_uint subfactorizations[20];
my_uint subfactors[20];
signed char primeIndexes[20];
my_uint subfactorIndex = 0;
struct PrimeFactorization_t * const PrimeFactorizations = sPrimeFactorizations;
my_uint remainingNum = num;
int trailingBits = __builtin_ctzl(remainingNum);
while (trailingBits--) {
subfactorizations[subfactorIndex] = remainingNum;
subfactors[subfactorIndex] = 2;
primeIndexes[subfactorIndex] = 1 + 0;
subfactorIndex++;
remainingNum >>= 1;
if (PrimeFactorizations[remainingNum].productOfOnePlusMultiplicities) goto foundSubfactorization;
}
TEST(3, 1); TEST(5, 2); TEST(7, 3); TEST(11, 4); TEST(13, 5); TEST(17, 6); TEST(19, 7);
TEST(23, 8); TEST(29, 9); TEST(31, 10); TEST(37, 11); TEST(41, 12); TEST(43, 13); TEST(47, 14);
TEST(53, 15); TEST(59, 16); TEST(61, 17); TEST(67, 18); TEST(71, 19); TEST(73, 20); TEST(79, 21);
TEST(83, 22); TEST(89, 23); TEST(97, 24); TEST(101, 25); TEST(103, 26); TEST(107, 27); TEST(109, 28);
TEST(113, 29); TEST(127, 30); TEST(131, 31); TEST(137, 32); TEST(139, 33); TEST(149, 34); TEST(151, 35);
TEST(157, 36); TEST(163, 37); TEST(167, 38); TEST(173, 39); TEST(179, 40); TEST(181, 41); TEST(191, 42);
TEST(193, 43); TEST(197, 44); TEST(199, 45); TEST(211, 46); TEST(223, 47); TEST(227, 48); TEST(229, 49);
TEST(233, 50); TEST(239, 51); TEST(241, 52); TEST(251, 53); TEST(257, 54); TEST(263, 55); TEST(269, 56);
TEST(271, 57); TEST(277, 58); TEST(281, 59); TEST(283, 60); TEST(293, 61); TEST(307, 62); TEST(311, 63);
TEST(313, 64); TEST(317, 65); TEST(331, 66); TEST(337, 67); TEST(347, 68); TEST(349, 69); TEST(353, 70);
TEST(359, 71); TEST(367, 72); TEST(373, 73); TEST(379, 74); TEST(383, 75); TEST(389, 76); TEST(397, 77);
TEST(401, 78); TEST(409, 79); TEST(419, 80); TEST(421, 81); TEST(431, 82); TEST(433, 83); TEST(439, 84);
TEST(443, 85); TEST(449, 86); TEST(457, 87); TEST(461, 88); TEST(463, 89); TEST(467, 90); TEST(479, 91);
TEST(487, 92); TEST(491, 93); TEST(499, 94); TEST(503, 95); TEST(509, 96); TEST(521, 97); TEST(523, 98);
TEST(541, 99); TEST(547, 100); TEST(557, 101); TEST(563, 102); TEST(569, 103); TEST(571, 104); TEST(577, 105);
TEST(587, 106); TEST(593, 107); TEST(599, 108); TEST(601, 109); TEST(607, 110); TEST(613, 111); TEST(617, 112);
TEST(619, 113); TEST(631, 114); TEST(641, 115); TEST(643, 116); TEST(647, 117); TEST(653, 118); TEST(659, 119);
TEST(661, 120); TEST(673, 121); TEST(677, 122); TEST(683, 123); TEST(691, 124); TEST(701, 125);
noRemainingFactors:
/* If we get here, remainingNum is prime or 1 */
PrimeFactorizations[remainingNum].isPrime = 1; //yes, we consider 1 to be prime
if (remainingNum == 1) {
PrimeFactorizations[remainingNum].productOfOnePlusMultiplicities = 1;
}
else {
PrimeFactorizations[remainingNum].productOfOnePlusMultiplicities = 2;
}
foundSubfactorization:
while (subfactorIndex--) {
copy_factorization_with_additional_factor(remainingNum, subfactorizations[subfactorIndex], primeIndexes[subfactorIndex]);
remainingNum = subfactorizations[subfactorIndex];
}
}
#undef TEST
static my_uint calcResult6(my_uint num) {
const struct PrimeFactorization_t *factors = & sPrimeFactorizations[num];
if (! factors->productOfOnePlusMultiplicities) {
compute_prime_factors(num);
}
if (factors->isPrime) return 1;
my_uint i;
my_uint productOfMultiplicities = factors->productOfOnePlusMultiplicities;
my_uint result = 1;
if ((productOfMultiplicities & 1) == 0) {
result = ipower_compute_mod10000(mod10000(num), (productOfMultiplicities - 2) >> 1);
}
else {
result = ipower_compute_mod10000(usqrt(num), productOfMultiplicities - 2);
}
return result;
}
#define OUTBUFF_SIZE (64 * 1024)
#define INBUFF_SIZE (64 * 1024)
static void flush_output(const char *outbufferPtr, const char *outcursorPtr) {
fwrite(outbufferPtr, 1, outcursorPtr - outbufferPtr, stdout);
}
static char *output_value(my_uint value, char * outbufferPtr, char *outcursorPtr) {
const char * const endPtr = outbufferPtr + OUTBUFF_SIZE;
#define PUSH_CHAR(c) do { \
*outcursorPtr++ = (c); \
if (outcursorPtr == endPtr) {\
flush_output(outbufferPtr, outcursorPtr);\
outcursorPtr = outbufferPtr;\
}\
} while (0)
unsigned char digits[4] = {0};
digits[3] = value % 10; value /= 10;
digits[2] = value % 10; value /= 10;
digits[1] = value % 10; value /= 10;
digits[0] = value;
int digitCount = 4;
while (! sDidOverflow) {
if (! digits[0]) digitCount--; else break;
if (! digits[1]) digitCount--; else break;
if (! digits[2]) digitCount--;
break;
}
switch (digitCount) {
case 4: PUSH_CHAR(digits[0] + '0');
case 3: PUSH_CHAR(digits[1] + '0');
case 2: PUSH_CHAR(digits[2] + '0');
case 1: PUSH_CHAR(digits[3] + '0');
}
PUSH_CHAR('\n');
return outcursorPtr;
}
int main(void)
{
my_uint testsRemaining;
char * const inbufferPtr = (char *)malloc(INBUFF_SIZE + 1);
const char *incursorPtr = inbufferPtr + INBUFF_SIZE;
inbufferPtr[INBUFF_SIZE] = 0;
char * const outbufferPtr = (char *)malloc(OUTBUFF_SIZE);
char *outcursorPtr = outbufferPtr;
fscanf(stdin,"%lu ",&testsRemaining);
sPrimeFactorizations = malloc(500001 * sizeof *sPrimeFactorizations);
bzero(sPrimeFactorizations, 500001 * sizeof *sPrimeFactorizations);
/* Prime the pump, as it were */
my_uint q;
for (q=0; q < sizeof sPrimesTable / sizeof *sPrimesTable; q++) {
my_uint prime = sPrimesTable[q];
struct PrimeFactorization_t *f = sPrimeFactorizations + prime;
f->isPrime = 1;
f->powerIndexesPlusOne[0] = q + 1;
f->multiplicities[0] = 1;
f->productOfOnePlusMultiplicities = 2;
}
my_uint numberToProcess = 0;
while (1) {
if (! *incursorPtr) {
incursorPtr = inbufferPtr;
size_t amountRead = fread(inbufferPtr, 1, INBUFF_SIZE, stdin);
inbufferPtr[amountRead] = 0;
if (amountRead == 0) {
flush_output(outbufferPtr, outcursorPtr);
return 0;
}
}
char c;
while ((c = *incursorPtr++)) {
if (c == '\n') {
testsRemaining--;
sDidOverflow = 0;
my_uint result = calcResult6(numberToProcess);
outcursorPtr = output_value(result, outbufferPtr, outcursorPtr);
if (testsRemaining == 0){
flush_output(outbufferPtr, outcursorPtr);
return 0;
}
numberToProcess = 0;
}
else {
if (c >= '0' && c <= '9') numberToProcess = numberToProcess * 10 + (c - '0');
}
}
}
return 0;
}
