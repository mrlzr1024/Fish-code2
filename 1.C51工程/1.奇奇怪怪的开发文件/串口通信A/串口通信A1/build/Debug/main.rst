                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.1.0 #12072 (MINGW64)
                                      4 ;--------------------------------------------------------
                                      5 	.module main
                                      6 	.optsdcc -mmcs51 --model-small
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _dio
                                     13 	.globl _CP_RL2
                                     14 	.globl _C_T2
                                     15 	.globl _TR2
                                     16 	.globl _EXEN2
                                     17 	.globl _TCLK
                                     18 	.globl _RCLK
                                     19 	.globl _EXF2
                                     20 	.globl _TF2
                                     21 	.globl _T2
                                     22 	.globl _T2EX
                                     23 	.globl _RI
                                     24 	.globl _TI
                                     25 	.globl _RB8
                                     26 	.globl _TB8
                                     27 	.globl _REN
                                     28 	.globl _SM2
                                     29 	.globl _SM1
                                     30 	.globl _SM0
                                     31 	.globl _RXD
                                     32 	.globl _TXD
                                     33 	.globl _INT0
                                     34 	.globl _INT1
                                     35 	.globl _T0
                                     36 	.globl _T1
                                     37 	.globl _WR
                                     38 	.globl _RD
                                     39 	.globl _PX0
                                     40 	.globl _PT0
                                     41 	.globl _PX1
                                     42 	.globl _PT1
                                     43 	.globl _PS
                                     44 	.globl _PT2
                                     45 	.globl _EX0
                                     46 	.globl _ET0
                                     47 	.globl _EX1
                                     48 	.globl _ET1
                                     49 	.globl _ES
                                     50 	.globl _ET2
                                     51 	.globl _EA
                                     52 	.globl _IT0
                                     53 	.globl _IE0
                                     54 	.globl _IT1
                                     55 	.globl _IE1
                                     56 	.globl _TR0
                                     57 	.globl _TF0
                                     58 	.globl _TR1
                                     59 	.globl _TF1
                                     60 	.globl _P
                                     61 	.globl _OV
                                     62 	.globl _RS0
                                     63 	.globl _RS1
                                     64 	.globl _F0
                                     65 	.globl _AC
                                     66 	.globl _CY
                                     67 	.globl _P37
                                     68 	.globl _P36
                                     69 	.globl _P35
                                     70 	.globl _P34
                                     71 	.globl _P33
                                     72 	.globl _P32
                                     73 	.globl _P31
                                     74 	.globl _P30
                                     75 	.globl _P27
                                     76 	.globl _P26
                                     77 	.globl _P25
                                     78 	.globl _P24
                                     79 	.globl _P23
                                     80 	.globl _P22
                                     81 	.globl _P21
                                     82 	.globl _P20
                                     83 	.globl _P17
                                     84 	.globl _P16
                                     85 	.globl _P15
                                     86 	.globl _P14
                                     87 	.globl _P13
                                     88 	.globl _P12
                                     89 	.globl _P11
                                     90 	.globl _P10
                                     91 	.globl _P07
                                     92 	.globl _P06
                                     93 	.globl _P05
                                     94 	.globl _P04
                                     95 	.globl _P03
                                     96 	.globl _P02
                                     97 	.globl _P01
                                     98 	.globl _P00
                                     99 	.globl _TH2
                                    100 	.globl _TL2
                                    101 	.globl _RCAP2H
                                    102 	.globl _RCAP2L
                                    103 	.globl _T2CON
                                    104 	.globl _SBUF
                                    105 	.globl _SCON
                                    106 	.globl _IP
                                    107 	.globl _IE
                                    108 	.globl _TH1
                                    109 	.globl _TH0
                                    110 	.globl _TL1
                                    111 	.globl _TL0
                                    112 	.globl _TMOD
                                    113 	.globl _TCON
                                    114 	.globl _PCON
                                    115 	.globl _DPH
                                    116 	.globl _DPL
                                    117 	.globl _SP
                                    118 	.globl _B
                                    119 	.globl _ACC
                                    120 	.globl _PSW
                                    121 	.globl _P3
                                    122 	.globl _P2
                                    123 	.globl _P1
                                    124 	.globl _P0
                                    125 ;--------------------------------------------------------
                                    126 ; special function registers
                                    127 ;--------------------------------------------------------
                                    128 	.area RSEG    (ABS,DATA)
      000000                        129 	.org 0x0000
                           000080   130 _P0	=	0x0080
                           000090   131 _P1	=	0x0090
                           0000A0   132 _P2	=	0x00a0
                           0000B0   133 _P3	=	0x00b0
                           0000D0   134 _PSW	=	0x00d0
                           0000E0   135 _ACC	=	0x00e0
                           0000F0   136 _B	=	0x00f0
                           000081   137 _SP	=	0x0081
                           000082   138 _DPL	=	0x0082
                           000083   139 _DPH	=	0x0083
                           000087   140 _PCON	=	0x0087
                           000088   141 _TCON	=	0x0088
                           000089   142 _TMOD	=	0x0089
                           00008A   143 _TL0	=	0x008a
                           00008B   144 _TL1	=	0x008b
                           00008C   145 _TH0	=	0x008c
                           00008D   146 _TH1	=	0x008d
                           0000A8   147 _IE	=	0x00a8
                           0000B8   148 _IP	=	0x00b8
                           000098   149 _SCON	=	0x0098
                           000099   150 _SBUF	=	0x0099
                           0000C8   151 _T2CON	=	0x00c8
                           0000CA   152 _RCAP2L	=	0x00ca
                           0000CB   153 _RCAP2H	=	0x00cb
                           0000CC   154 _TL2	=	0x00cc
                           0000CD   155 _TH2	=	0x00cd
                                    156 ;--------------------------------------------------------
                                    157 ; special function bits
                                    158 ;--------------------------------------------------------
                                    159 	.area RSEG    (ABS,DATA)
      000000                        160 	.org 0x0000
                           000080   161 _P00	=	0x0080
                           000081   162 _P01	=	0x0081
                           000082   163 _P02	=	0x0082
                           000083   164 _P03	=	0x0083
                           000084   165 _P04	=	0x0084
                           000085   166 _P05	=	0x0085
                           000086   167 _P06	=	0x0086
                           000087   168 _P07	=	0x0087
                           000090   169 _P10	=	0x0090
                           000091   170 _P11	=	0x0091
                           000092   171 _P12	=	0x0092
                           000093   172 _P13	=	0x0093
                           000094   173 _P14	=	0x0094
                           000095   174 _P15	=	0x0095
                           000096   175 _P16	=	0x0096
                           000097   176 _P17	=	0x0097
                           0000A0   177 _P20	=	0x00a0
                           0000A1   178 _P21	=	0x00a1
                           0000A2   179 _P22	=	0x00a2
                           0000A3   180 _P23	=	0x00a3
                           0000A4   181 _P24	=	0x00a4
                           0000A5   182 _P25	=	0x00a5
                           0000A6   183 _P26	=	0x00a6
                           0000A7   184 _P27	=	0x00a7
                           0000B0   185 _P30	=	0x00b0
                           0000B1   186 _P31	=	0x00b1
                           0000B2   187 _P32	=	0x00b2
                           0000B3   188 _P33	=	0x00b3
                           0000B4   189 _P34	=	0x00b4
                           0000B5   190 _P35	=	0x00b5
                           0000B6   191 _P36	=	0x00b6
                           0000B7   192 _P37	=	0x00b7
                           0000D7   193 _CY	=	0x00d7
                           0000D6   194 _AC	=	0x00d6
                           0000D5   195 _F0	=	0x00d5
                           0000D4   196 _RS1	=	0x00d4
                           0000D3   197 _RS0	=	0x00d3
                           0000D2   198 _OV	=	0x00d2
                           0000D0   199 _P	=	0x00d0
                           00008F   200 _TF1	=	0x008f
                           00008E   201 _TR1	=	0x008e
                           00008D   202 _TF0	=	0x008d
                           00008C   203 _TR0	=	0x008c
                           00008B   204 _IE1	=	0x008b
                           00008A   205 _IT1	=	0x008a
                           000089   206 _IE0	=	0x0089
                           000088   207 _IT0	=	0x0088
                           0000AF   208 _EA	=	0x00af
                           0000AD   209 _ET2	=	0x00ad
                           0000AC   210 _ES	=	0x00ac
                           0000AB   211 _ET1	=	0x00ab
                           0000AA   212 _EX1	=	0x00aa
                           0000A9   213 _ET0	=	0x00a9
                           0000A8   214 _EX0	=	0x00a8
                           0000BD   215 _PT2	=	0x00bd
                           0000BC   216 _PS	=	0x00bc
                           0000BB   217 _PT1	=	0x00bb
                           0000BA   218 _PX1	=	0x00ba
                           0000B9   219 _PT0	=	0x00b9
                           0000B8   220 _PX0	=	0x00b8
                           0000B7   221 _RD	=	0x00b7
                           0000B6   222 _WR	=	0x00b6
                           0000B5   223 _T1	=	0x00b5
                           0000B4   224 _T0	=	0x00b4
                           0000B3   225 _INT1	=	0x00b3
                           0000B2   226 _INT0	=	0x00b2
                           0000B1   227 _TXD	=	0x00b1
                           0000B0   228 _RXD	=	0x00b0
                           00009F   229 _SM0	=	0x009f
                           00009E   230 _SM1	=	0x009e
                           00009D   231 _SM2	=	0x009d
                           00009C   232 _REN	=	0x009c
                           00009B   233 _TB8	=	0x009b
                           00009A   234 _RB8	=	0x009a
                           000099   235 _TI	=	0x0099
                           000098   236 _RI	=	0x0098
                           000091   237 _T2EX	=	0x0091
                           000090   238 _T2	=	0x0090
                           0000CF   239 _TF2	=	0x00cf
                           0000CE   240 _EXF2	=	0x00ce
                           0000CD   241 _RCLK	=	0x00cd
                           0000CC   242 _TCLK	=	0x00cc
                           0000CB   243 _EXEN2	=	0x00cb
                           0000CA   244 _TR2	=	0x00ca
                           0000C9   245 _C_T2	=	0x00c9
                           0000C8   246 _CP_RL2	=	0x00c8
                                    247 ;--------------------------------------------------------
                                    248 ; overlayable register banks
                                    249 ;--------------------------------------------------------
                                    250 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        251 	.ds 8
                                    252 ;--------------------------------------------------------
                                    253 ; internal ram data
                                    254 ;--------------------------------------------------------
                                    255 	.area DSEG    (DATA)
                                    256 ;--------------------------------------------------------
                                    257 ; overlayable items in internal ram 
                                    258 ;--------------------------------------------------------
                                    259 	.area	OSEG    (OVR,DATA)
                                    260 ;--------------------------------------------------------
                                    261 ; Stack segment in internal ram 
                                    262 ;--------------------------------------------------------
                                    263 	.area	SSEG
      000008                        264 __start__stack:
      000008                        265 	.ds	1
                                    266 
                                    267 ;--------------------------------------------------------
                                    268 ; indirectly addressable internal ram data
                                    269 ;--------------------------------------------------------
                                    270 	.area ISEG    (DATA)
                                    271 ;--------------------------------------------------------
                                    272 ; absolute internal ram data
                                    273 ;--------------------------------------------------------
                                    274 	.area IABS    (ABS,DATA)
                                    275 	.area IABS    (ABS,DATA)
                                    276 ;--------------------------------------------------------
                                    277 ; bit data
                                    278 ;--------------------------------------------------------
                                    279 	.area BSEG    (BIT)
                                    280 ;--------------------------------------------------------
                                    281 ; paged external ram data
                                    282 ;--------------------------------------------------------
                                    283 	.area PSEG    (PAG,XDATA)
                                    284 ;--------------------------------------------------------
                                    285 ; external ram data
                                    286 ;--------------------------------------------------------
                                    287 	.area XSEG    (XDATA)
                                    288 ;--------------------------------------------------------
                                    289 ; absolute external ram data
                                    290 ;--------------------------------------------------------
                                    291 	.area XABS    (ABS,XDATA)
                                    292 ;--------------------------------------------------------
                                    293 ; external initialized ram data
                                    294 ;--------------------------------------------------------
                                    295 	.area XISEG   (XDATA)
                                    296 	.area HOME    (CODE)
                                    297 	.area GSINIT0 (CODE)
                                    298 	.area GSINIT1 (CODE)
                                    299 	.area GSINIT2 (CODE)
                                    300 	.area GSINIT3 (CODE)
                                    301 	.area GSINIT4 (CODE)
                                    302 	.area GSINIT5 (CODE)
                                    303 	.area GSINIT  (CODE)
                                    304 	.area GSFINAL (CODE)
                                    305 	.area CSEG    (CODE)
                                    306 ;--------------------------------------------------------
                                    307 ; interrupt vector 
                                    308 ;--------------------------------------------------------
                                    309 	.area HOME    (CODE)
      000000                        310 __interrupt_vect:
      000000 02 00 06         [24]  311 	ljmp	__sdcc_gsinit_startup
                                    312 ;--------------------------------------------------------
                                    313 ; global & static initialisations
                                    314 ;--------------------------------------------------------
                                    315 	.area HOME    (CODE)
                                    316 	.area GSINIT  (CODE)
                                    317 	.area GSFINAL (CODE)
                                    318 	.area GSINIT  (CODE)
                                    319 	.globl __sdcc_gsinit_startup
                                    320 	.globl __sdcc_program_startup
                                    321 	.globl __start__stack
                                    322 	.globl __mcs51_genXINIT
                                    323 	.globl __mcs51_genXRAMCLEAR
                                    324 	.globl __mcs51_genRAMCLEAR
                                    325 	.area GSFINAL (CODE)
      00005F 02 00 03         [24]  326 	ljmp	__sdcc_program_startup
                                    327 ;--------------------------------------------------------
                                    328 ; Home
                                    329 ;--------------------------------------------------------
                                    330 	.area HOME    (CODE)
                                    331 	.area HOME    (CODE)
      000003                        332 __sdcc_program_startup:
      000003 02 00 6D         [24]  333 	ljmp	_main
                                    334 ;	return from main will return to caller
                                    335 ;--------------------------------------------------------
                                    336 ; code
                                    337 ;--------------------------------------------------------
                                    338 	.area CSEG    (CODE)
                                    339 ;------------------------------------------------------------
                                    340 ;Allocation info for local variables in function 'dio'
                                    341 ;------------------------------------------------------------
                                    342 ;dat                       Allocated to registers 
                                    343 ;------------------------------------------------------------
                                    344 ;	.\src\main.c:10: unsigned char dio(void){
                                    345 ;	-----------------------------------------
                                    346 ;	 function dio
                                    347 ;	-----------------------------------------
      000062                        348 _dio:
                           000007   349 	ar7 = 0x07
                           000006   350 	ar6 = 0x06
                           000005   351 	ar5 = 0x05
                           000004   352 	ar4 = 0x04
                           000003   353 	ar3 = 0x03
                           000002   354 	ar2 = 0x02
                           000001   355 	ar1 = 0x01
                           000000   356 	ar0 = 0x00
                                    357 ;	.\src\main.c:12: while(RI=!0);
      000062                        358 00101$:
                                    359 ;	assignBit
      000062 D2 98            [12]  360 	setb	_RI
      000064 20 98 FB         [24]  361 	jb	_RI,00101$
                                    362 ;	.\src\main.c:13: RI=0;
                                    363 ;	assignBit
      000067 C2 98            [12]  364 	clr	_RI
                                    365 ;	.\src\main.c:14: dat=SBUF;
      000069 85 99 82         [24]  366 	mov	dpl,_SBUF
                                    367 ;	.\src\main.c:15: return dat;
                                    368 ;	.\src\main.c:16: }
      00006C 22               [24]  369 	ret
                                    370 ;------------------------------------------------------------
                                    371 ;Allocation info for local variables in function 'main'
                                    372 ;------------------------------------------------------------
                                    373 ;	.\src\main.c:17: void main(void){
                                    374 ;	-----------------------------------------
                                    375 ;	 function main
                                    376 ;	-----------------------------------------
      00006D                        377 _main:
                                    378 ;	.\src\main.c:18: TMOD=0x20;
      00006D 75 89 20         [24]  379 	mov	_TMOD,#0x20
                                    380 ;	.\src\main.c:19: SCON=0x50;
      000070 75 98 50         [24]  381 	mov	_SCON,#0x50
                                    382 ;	.\src\main.c:20: PCON=0x00;//波特率=9600
      000073 75 87 00         [24]  383 	mov	_PCON,#0x00
                                    384 ;	.\src\main.c:21: TH1=0xfd;
      000076 75 8D FD         [24]  385 	mov	_TH1,#0xfd
                                    386 ;	.\src\main.c:22: TL1=TH0;
      000079 85 8C 8B         [24]  387 	mov	_TL1,_TH0
                                    388 ;	.\src\main.c:23: TR1=1;
                                    389 ;	assignBit
      00007C D2 8E            [12]  390 	setb	_TR1
                                    391 ;	.\src\main.c:24: REN=1;
                                    392 ;	assignBit
      00007E D2 9C            [12]  393 	setb	_REN
                                    394 ;	.\src\main.c:25: while(1){
      000080                        395 00102$:
                                    396 ;	.\src\main.c:26: P1=dio();
      000080 12 00 62         [24]  397 	lcall	_dio
      000083 85 82 90         [24]  398 	mov	_P1,dpl
                                    399 ;	.\src\main.c:29: }
      000086 80 F8            [24]  400 	sjmp	00102$
                                    401 	.area CSEG    (CODE)
                                    402 	.area CONST   (CODE)
                                    403 	.area XINIT   (CODE)
                                    404 	.area CABS    (ABS,CODE)
