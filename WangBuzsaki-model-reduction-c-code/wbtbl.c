#include <stdio.h>
#include <math.h>

#define I	7
#define gna	35.
#define gk	9.
#define gl	0.1
#define ena	55.
#define ek	(-90.)
#define el	(-65.)
#define dt	0.01
/*
inline double Minf(double v);
inline double na(double v);
inline double nb(double v);
inline double ha(double v);
inline double hb(double v);


double Minf(double v){
	double a = 0.1*(v+35.)/(1.0-exp(-(v+35.)/10.)) ;
	double b = 4.0*exp(-(v+60.)/18.);
	return a/(a+b);
};

double ha(double v) { return 0.07*exp(-(v+58.)/20.);               };
double hb(double v) { return 1.0/(1.0+exp(-(v+28.)/10.));          };

double na(double v) { return 0.01*(v+34.)/(1.0-exp(-(v+34.)/10.)); };
double nb(double v) { return 0.125*exp(-(v+44.)/80.);              };
*/

static double tbl[201][6]={
    {-90.,0.00106457,0.994192,0.573497,0.00926988,0.891982},
    {-89.275,0.00117619,0.993531,0.594272,0.00992365,0.899508},
    {-88.55,0.00129929,0.992794,0.615753,0.0106214,0.907057},
    {-87.825,0.00143503,0.991974,0.637956,0.011366,0.914626},
    {-87.1,0.00158467,0.991062,0.660898,0.0121603,0.922211},
    {-86.375,0.0017496,0.990047,0.684593,0.0130072,0.929809},
    {-85.65,0.00193134,0.988919,0.709056,0.0139101,0.937415},
    {-84.925,0.00213156,0.987664,0.734298,0.0148722,0.945026},
    {-84.2,0.00235207,0.98627,0.76033,0.0158972,0.952637},
    {-83.475,0.00259487,0.984721,0.787159,0.0169887,0.960243},
    {-82.75,0.00286215,0.983,0.814791,0.0181506,0.96784},
    {-82.025,0.00315629,0.98109,0.843227,0.019387,0.975421},
    {-81.3,0.00347989,0.97897,0.872466,0.0207021,0.982981},
    {-80.575,0.00383581,0.976619,0.9025,0.0221003,0.990513},
    {-79.85,0.00422714,0.974013,0.933319,0.0235863,0.998012},
    {-79.125,0.00465729,0.971125,0.964903,0.0251648,1.00547},
    {-78.4,0.00512993,0.967929,0.997229,0.0268408,1.01288},
    {-77.675,0.0056491,0.964392,1.03026,0.0286196,1.02023},
    {-76.95,0.00621916,0.960483,1.06397,0.0305064,1.02752},
    {-76.225,0.00684487,0.956165,1.09828,0.0325068,1.03473},
    {-75.5,0.00753141,0.951402,1.13315,0.0346265,1.04187},
    {-74.775,0.00828438,0.946153,1.1685,0.0368714,1.04891},
    {-74.05,0.00910987,0.940374,1.20424,0.0392474,1.05584},
    {-73.325,0.0100144,0.934022,1.24026,0.0417607,1.06267},
    {-72.6,0.0110053,0.92705,1.27644,0.0444177,1.06937},
    {-71.875,0.01209,0.919409,1.31265,0.0472247,1.07593},
    {-71.15,0.0132769,0.91105,1.34873,0.0501882,1.08235},
    {-70.425,0.0145751,0.901921,1.38451,0.0533149,1.08861},
    {-69.7,0.015994,0.891975,1.41978,0.0566114,1.0947},
    {-68.975,0.0175441,0.881161,1.45435,0.0600843,1.1006},
    {-68.25,0.0192365,0.869432,1.48796,0.0637403,1.10629},
    {-67.525,0.021083,0.856745,1.52038,0.067586,1.11178},
    {-66.8,0.0230963,0.843061,1.55132,0.0716281,1.11704},
    {-66.075,0.02529,0.828346,1.58051,0.0758729,1.12205},
    {-65.35,0.0276783,0.812575,1.60765,0.0803268,1.12681},
    {-64.625,0.0302767,0.795733,1.63245,0.084996,1.1313},
    {-63.9,0.0331012,0.777813,1.65459,0.0898863,1.13549},
    {-63.175,0.0361688,0.758822,1.67378,0.0950034,1.13939},
    {-62.45,0.0394975,0.738782,1.68973,0.100353,1.14297},
    {-61.725,0.0431059,0.717728,1.70218,0.105939,1.14621},
    {-61,0.0470137,0.695712,1.71087,0.111767,1.1491},
    {-60.275,0.0512411,0.672801,1.71561,0.11784,1.15164},
    {-59.55,0.055809,0.649079,1.71622,0.124162,1.15379},
    {-58.825,0.0607392,0.624646,1.71258,0.130737,1.15556},
    {-58.1,0.0660537,0.599614,1.70464,0.137565,1.15692},
    {-57.375,0.0717748,0.574108,1.69238,0.14465,1.15786},
    {-56.65,0.0779251,0.548264,1.67586,0.151991,1.15837},
    {-55.925,0.0845273,0.522224,1.65519,0.159589,1.15844},
    {-55.2,0.0916035,0.496134,1.63054,0.167443,1.15806},
    {-54.475,0.0991757,0.470141,1.60216,0.175551,1.15723},
    {-53.75,0.107265,0.444389,1.5703,0.183912,1.15592},
    {-53.025,0.115891,0.419017,1.5353,0.192521,1.15414},
    {-52.3,0.125072,0.394154,1.49752,0.201374,1.15188},
    {-51.575,0.134826,0.369918,1.45732,0.210465,1.14913},
    {-50.85,0.145166,0.346414,1.4151,0.21979,1.1459},
    {-50.125,0.156105,0.323733,1.37127,0.22934,1.14217},
    {-49.4,0.167652,0.30195,1.32622,0.239108,1.13796},
    {-48.675,0.179813,0.281124,1.28032,0.249084,1.13327},
    {-47.95,0.192589,0.261298,1.23396,0.259258,1.12809},
    {-47.225,0.205979,0.2425,1.18746,0.269621,1.12243},
    {-46.5,0.219976,0.224745,1.14115,0.28016,1.11631},
    {-45.775,0.23457,0.208035,1.0953,0.290862,1.10972},
    {-45.05,0.249745,0.19236,1.05016,0.301717,1.10269},
    {-44.325,0.265479,0.177702,1.00594,0.312709,1.09521},
    {-43.6,0.281747,0.164032,0.962838,0.323824,1.0873},
    {-42.875,0.298518,0.151318,0.920993,0.335049,1.07899},
    {-42.15,0.315757,0.139519,0.880528,0.346368,1.07028},
    {-41.425,0.333424,0.128593,0.841535,0.357766,1.06119},
    {-40.7,0.351472,0.118496,0.804082,0.369228,1.05174},
    {-39.975,0.369856,0.10918,0.768213,0.380739,1.04194},
    {-39.25,0.388521,0.100597,0.733952,0.392283,1.03183},
    {-38.525,0.407415,0.0927005,0.701307,0.403844,1.02141},
    {-37.8,0.42648,0.0854438,0.67027,0.415408,1.01072},
    {-37.075,0.445659,0.0787816,0.640822,0.426959,0.999768},
    {-36.35,0.464892,0.0726701,0.612931,0.438484,0.98858},
    {-35.625,0.48412,0.0670676,0.586559,0.449966,0.977179},
    {-34.9,0.503286,0.0619344,0.56166,0.461394,0.965588},
    {-34.175,0.522334,0.057233,0.538185,0.472754,0.953829},
    {-33.45,0.541208,0.0529284,0.51608,0.484032,0.941923},
    {-32.725,0.559856,0.0489875,0.495287,0.495217,0.929894},
    {-32,0.578231,0.0453799,0.475749,0.506297,0.917761},
    {-31.275,0.596286,0.042077,0.457407,0.517262,0.905547},
    {-30.55,0.613981,0.0390527,0.440203,0.528102,0.893272},
    {-29.825,0.63128,0.0362828,0.424077,0.538807,0.880956},
    {-29.1,0.648148,0.0337448,0.408973,0.549369,0.868617},
    {-28.375,0.664559,0.0314185,0.394835,0.55978,0.856274},
    {-27.65,0.680489,0.0292849,0.381609,0.570033,0.843944},
    {-26.925,0.695918,0.0273271,0.369242,0.580122,0.831645},
    {-26.2,0.710831,0.0255293,0.357683,0.590041,0.819391},
    {-25.475,0.725217,0.0238772,0.346886,0.599785,0.807198},
    {-24.75,0.73907,0.0223578,0.336803,0.60935,0.795078},
    {-24.025,0.752385,0.0209593,0.327391,0.618733,0.783046},
    {-23.3,0.765162,0.0196708,0.318607,0.627931,0.771112},
    {-22.575,0.777405,0.0184827,0.310413,0.636941,0.759289},
    {-21.85,0.789117,0.0173858,0.302771,0.645762,0.747585},
    {-21.125,0.800307,0.0163723,0.295645,0.654393,0.73601},
    {-20.4,0.810984,0.0154346,0.289003,0.662833,0.724573},
    {-19.675,0.82116,0.0145663,0.282812,0.671082,0.71328},
    {-18.95,0.830847,0.0137612,0.277043,0.679141,0.702139},
    {-18.225,0.84006,0.0130138,0.271668,0.687009,0.691155},
    {-17.5,0.848813,0.0123192,0.266662,0.69469,0.680333},
    {-16.775,0.857122,0.0116729,0.261999,0.702183,0.669677},
    {-16.05,0.865003,0.0110707,0.257656,0.709491,0.659192},
    {-15.325,0.872474,0.0105091,0.253613,0.716615,0.64888},
    {-14.6,0.87955,0.00998452,0.249849,0.723559,0.638743},
    {-13.875,0.886248,0.00949403,0.246346,0.730324,0.628783},
    {-13.15,0.892585,0.00903482,0.243084,0.736914,0.619003},
    {-12.425,0.898577,0.00860438,0.240049,0.743331,0.609402},
    {-11.7,0.904242,0.00820042,0.237224,0.749579,0.59998},
    {-10.975,0.909593,0.00782086,0.234596,0.755661,0.590739},
    {-10.25,0.914648,0.00746381,0.232151,0.761579,0.581677},
    {-9.525,0.91942,0.00712755,0.229876,0.767339,0.572794},
    {-8.8,0.923925,0.00681052,0.22776,0.772942,0.564088},
    {-8.075,0.928177,0.00651129,0.225791,0.778392,0.555559},
    {-7.35,0.932188,0.00622856,0.22396,0.783694,0.547204},
    {-6.625,0.935972,0.00596114,0.222257,0.788851,0.539022},
    {-5.9,0.939541,0.00570796,0.220673,0.793865,0.531011},
    {-5.175,0.942908,0.00546801,0.219201,0.798742,0.523169},
    {-4.45,0.946082,0.0052404,0.217831,0.803484,0.515492},
    {-3.725,0.949076,0.0050243,0.216558,0.808095,0.507979},
    {-3,0.951898,0.00481894,0.215374,0.812579,0.500628},
    {-2.275,0.95456,0.00462364,0.214274,0.816938,0.493434},
    {-1.55,0.957069,0.00443774,0.213251,0.821177,0.486396},
    {-0.825,0.959436,0.00426067,0.2123,0.825299,0.47951},
    {-0.1,0.961667,0.00409188,0.211416,0.829307,0.472774},
    {0.625,0.963771,0.00393087,0.210594,0.833205,0.466185},
    {1.35,0.965756,0.00377718,0.209831,0.836995,0.459739},
    {2.075,0.967627,0.00363039,0.209121,0.840681,0.453434},
    {2.8,0.969392,0.00349011,0.208462,0.844266,0.447267},
    {3.525,0.971057,0.00335597,0.207849,0.847752,0.441234},
    {4.25,0.972627,0.00322763,0.20728,0.851144,0.435332},
    {4.975,0.974109,0.00310478,0.206751,0.854443,0.429559},
    {5.7,0.975507,0.00298714,0.20626,0.857652,0.423912},
    {6.425,0.976826,0.00287442,0.205804,0.860775,0.418387},
    {7.15,0.978071,0.00276638,0.20538,0.863813,0.412982},
    {7.875,0.979247,0.00266278,0.204986,0.86677,0.407694},
    {8.6,0.980356,0.0025634,0.204621,0.869648,0.402519},
    {9.325,0.981404,0.00246804,0.204281,0.872449,0.397456},
    {10.05,0.982393,0.00237651,0.203966,0.875175,0.392501},
    {10.775,0.983327,0.00228861,0.203673,0.87783,0.387652},
    {11.5,0.984209,0.00220419,0.203402,0.880414,0.382906},
    {12.225,0.985043,0.00212308,0.203149,0.882931,0.37826},
    {12.95,0.98583,0.00204514,0.202915,0.885382,0.373712},
    {13.675,0.986574,0.00197022,0.202698,0.887769,0.369259},
    {14.4,0.987278,0.00189819,0.202496,0.890095,0.364899},
    {15.125,0.987942,0.00182892,0.202309,0.892361,0.36063},
    {15.85,0.988571,0.0017623,0.202136,0.894568,0.356449},
    {16.575,0.989165,0.0016982,0.201975,0.89672,0.352354},
    {17.3,0.989727,0.00163653,0.201825,0.898817,0.348343},
    {18.025,0.990259,0.00157719,0.201687,0.900861,0.344413},
    {18.75,0.990762,0.00152007,0.201558,0.902854,0.340562},
    {19.475,0.991237,0.00146509,0.201439,0.904797,0.336789},
    {20.2,0.991688,0.00141215,0.201329,0.906691,0.333091},
    {20.925,0.992114,0.00136119,0.201226,0.908539,0.329467},
    {21.65,0.992517,0.00131211,0.201131,0.910342,0.325914},
    {22.375,0.992899,0.00126484,0.201043,0.9121,0.322431},
    {23.1,0.99326,0.00121932,0.200962,0.913816,0.319015},
    {23.825,0.993602,0.00117547,0.200886,0.91549,0.315666},
    {24.55,0.993927,0.00113323,0.200816,0.917124,0.312381},
    {25.275,0.994234,0.00109253,0.200752,0.918719,0.309159},
    {26,0.994525,0.00105332,0.200692,0.920276,0.305998},
    {26.725,0.9948,0.00101554,0.200636,0.921796,0.302897},
    {27.45,0.995062,0.000979136,0.200585,0.92328,0.299854},
    {28.175,0.995309,0.000944054,0.200537,0.924729,0.296867},
    {28.9,0.995544,0.000910245,0.200493,0.926145,0.293935},
    {29.625,0.995766,0.000877661,0.200453,0.927528,0.291058},
    {30.35,0.995977,0.000846257,0.200415,0.928879,0.288233},
    {31.075,0.996177,0.000815988,0.20038,0.930199,0.285458},
    {31.8,0.996367,0.000786812,0.200348,0.931488,0.282734},
    {32.525,0.996547,0.000758688,0.200318,0.932749,0.280059},
    {33.25,0.996718,0.000731578,0.200291,0.933981,0.27743},
    {33.975,0.99688,0.000705444,0.200266,0.935186,0.274848},
    {34.7,0.997033,0.00068025,0.200242,0.936363,0.272312},
    {35.425,0.997179,0.000655962,0.200221,0.937514,0.269819},
    {36.15,0.997318,0.000632546,0.200201,0.93864,0.267369},
    {36.875,0.997449,0.000609971,0.200182,0.939742,0.264961},
    {37.6,0.997574,0.000588206,0.200165,0.940819,0.262594},
    {38.325,0.997692,0.000567221,0.20015,0.941872,0.260267},
    {39.05,0.997805,0.000546988,0.200135,0.942903,0.257979},
    {39.775,0.997912,0.00052748,0.200122,0.943912,0.255729},
    {40.5,0.998013,0.000508671,0.20011,0.944899,0.253517},
    {41.225,0.998109,0.000490534,0.200099,0.945864,0.25134},
    {41.95,0.998201,0.000473046,0.200089,0.94681,0.249199},
    {42.675,0.998288,0.000456184,0.200079,0.947735,0.247093},
    {43.4,0.99837,0.000439924,0.20007,0.948641,0.24502},
    {44.125,0.998449,0.000424246,0.200063,0.949528,0.242981},
    {44.85,0.998524,0.000409127,0.200055,0.950397,0.240974},
    {45.575,0.998594,0.000394549,0.200049,0.951247,0.238998},
    {46.3,0.998662,0.000380491,0.200042,0.95208,0.237054},
    {47.025,0.998726,0.000366935,0.200037,0.952896,0.235139},
    {47.75,0.998787,0.000353863,0.200032,0.953695,0.233254},
    {48.475,0.998845,0.000341257,0.200027,0.954478,0.231398},
    {49.2,0.9989,0.000329101,0.200023,0.955245,0.22957},
    {49.925,0.998952,0.000317379,0.200019,0.955996,0.22777},
    {50.65,0.999002,0.000306074,0.200016,0.956733,0.225997},
    {51.375,0.999049,0.000295173,0.200012,0.957455,0.22425},
    {52.1,0.999095,0.000284661,0.200009,0.958162,0.222529},
    {52.825,0.999137,0.000274523,0.200007,0.958855,0.220833},
    {53.55,0.999178,0.000264747,0.200004,0.959535,0.219162},
    {54.275,0.999217,0.000255319,0.200002,0.960201,0.217516},
    {55.,0.999254,0.000246227,0.2,0.960855,0.215893}
};

int main(int argc, char** argv){
	int t = 0,vx;
	double dv = (ena-ek)/201.;
	double n=0, h=0, minf, ninf, hinf, ntau, htau, a, b, v=-63., ras;
	v=-63.;
	for(t=0; t<60000000; ++t){
		vx = (int)floor((v-ek)/dv);
		ras   = (v - tbl[vx][0])/dv;
		minf = tbl[vx][1] + (tbl[vx+1][1] - tbl[vx][1])*ras;
		hinf = tbl[vx][2] + (tbl[vx+1][2] - tbl[vx][2])*ras;
		htau = tbl[vx][3] + (tbl[vx+1][3] - tbl[vx][3])*ras;
		ninf = tbl[vx][4] + (tbl[vx+1][4] - tbl[vx][4])*ras;
		ntau = tbl[vx][5] + (tbl[vx+1][5] - tbl[vx][5])*ras;
		
		n += dt*(ninf - n)/ntau;
		h += dt*(hinf - h)/htau;
		v += dt*(-gna*minf*minf*minf*h*(v-ena)-gk*n*n*n*n*(v-ek)-gl*(v-el)+I);
	}
	return 0;
}
