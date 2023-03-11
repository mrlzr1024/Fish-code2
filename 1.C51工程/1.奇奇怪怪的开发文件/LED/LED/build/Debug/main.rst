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
                                     12 	.globl _CP_RL2
                                     13 	.globl _C_T2
                                     14 	.globl _TR2
                                     15 	.globl _EXEN2
                                     16 	.globl _TCLK
                                     17 	.globl _RCLK
                                     18 	.globl _EXF2
                                     19 	.globl _TF2
                                     20 	.globl _T2
                                     21 	.globl _T2EX
                                     22 	.globl _RI
                                     23 	.globl _TI
                                     24 	.globl _RB8
                                     25 	.globl _TB8
                                     26 	.globl _REN
                                     27 	.globl _SM2
                                     28 	.globl _SM1
                                     29 	.globl _SM0
                                     30 	.globl _RXD
                                     31 	.globl _TXD
                                     32 	.globl _INT0
                                     33 	.globl _INT1
                                     34 	.globl _T0
                                     35 	.globl _T1
                                     36 	.globl _WR
                                     37 	.globl _RD
                                     38 	.globl _PX0
                                     39 	.globl _PT0
                                     40 	.globl _PX1
                                     41 	.globl _PT1
                                     42 	.globl _PS
                                     43 	.globl _PT2
                                     44 	.globl _EX0
                                     45 	.globl _ET0
                                     46 	.globl _EX1
                                     47 	.globl _ET1
                                     48 	.globl _ES
                                     49 	.globl _ET2
                                     50 	.globl _EA
                                     51 	.globl _IT0
                                     52 	.globl _IE0
                                     53 	.globl _IT1
                                     54 	.globl _IE1
                                     55 	.globl _TR0
                                     56 	.globl _TF0
                                     57 	.globl _TR1
                                     58 	.globl _TF1
                                     59 	.globl _P
                                     60 	.globl _OV
                                     61 	.globl _RS0
                                     62 	.globl _RS1
                                     63 	.globl _F0
                                     64 	.globl _AC
                                     65 	.globl _CY
                                     66 	.globl _P37
                                     67 	.globl _P36
                                     68 	.globl _P35
                                     69 	.globl _P34
                                     70 	.globl _P33
                                     71 	.globl _P32
                                     72 	.globl _P31
                                     73 	.globl _P30
                                     74 	.globl _P27
                                     75 	.globl _P26
                                     76 	.globl _P25
                                     77 	.globl _P24
                                     78 	.globl _P23
                                     79 	.globl _P22
                                     80 	.globl _P21
                                     81 	.globl _P20
                                     82 	.globl _P17
                                     83 	.globl _P16
                                     84 	.globl _P15
                                     85 	.globl _P14
                                     86 	.globl _P13
                                     87 	.globl _P12
                                     88 	.globl _P11
                                     89 	.globl _P10
                                     90 	.globl _P07
                                     91 	.globl _P06
                                     92 	.globl _P05
                                     93 	.globl _P04
                                     94 	.globl _P03
                                     95 	.globl _P02
                                     96 	.globl _P01
                                     97 	.globl _P00
                                     98 	.globl _TH2
                                     99 	.globl _TL2
                                    100 	.globl _RCAP2H
                                    101 	.globl _RCAP2L
                                    102 	.globl _T2CON
                                    103 	.globl _SBUF
                                    104 	.globl _SCON
                                    105 	.globl _IP
                                    106 	.globl _IE
                                    107 	.globl _TH1
                                    108 	.globl _TH0
                                    109 	.globl _TL1
                                    110 	.globl _TL0
                                    111 	.globl _TMOD
                                    112 	.globl _TCON
                                    113 	.globl _PCON
                                    114 	.globl _DPH
                                    115 	.globl _DPL
                                    116 	.globl _SP
                                    117 	.globl _B
                                    118 	.globl _ACC
                                    119 	.globl _PSW
                                    120 	.globl _P3
                                    121 	.globl _P2
                                    122 	.globl _P1
                                    123 	.globl _P0
                                    124 	.globl _delay_100ms
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
      000003 02 00 62         [24]  333 	ljmp	_main
                                    334 ;	return from main will return to caller
                                    335 ;--------------------------------------------------------
                                    336 ; code
                                    337 ;--------------------------------------------------------
                                    338 	.area CSEG    (CODE)
                                    339 ;------------------------------------------------------------
                                    340 ;Allocation info for local variables in function 'main'
                                    341 ;------------------------------------------------------------
                                    342 ;	.\src\main.c:17: void main()
                                    343 ;	-----------------------------------------
                                    344 ;	 function main
                                    345 ;	-----------------------------------------
      000062                        346 _main:
                           000007   347 	ar7 = 0x07
                           000006   348 	ar6 = 0x06
                           000005   349 	ar5 = 0x05
                           000004   350 	ar4 = 0x04
                           000003   351 	ar3 = 0x03
                           000002   352 	ar2 = 0x02
                           000001   353 	ar1 = 0x01
                           000000   354 	ar0 = 0x00
                                    355 ;	.\src\main.c:19: while (1)
      000062                        356 00102$:
                                    357 ;	.\src\main.c:21: P00 = !P00;
      000062 B2 80            [12]  358 	cpl	_P00
                                    359 ;	.\src\main.c:22: delay_100ms();
      000064 12 00 69         [24]  360 	lcall	_delay_100ms
                                    361 ;	.\src\main.c:24: }
      000067 80 F9            [24]  362 	sjmp	00102$
                                    363 ;------------------------------------------------------------
                                    364 ;Allocation info for local variables in function 'delay_100ms'
                                    365 ;------------------------------------------------------------
                                    366 ;i                         Allocated to registers r6 
                                    367 ;j                         Allocated to registers r7 
                                    368 ;------------------------------------------------------------
                                    369 ;	.\src\main.c:26: void delay_100ms()
                                    370 ;	-----------------------------------------
                                    371 ;	 function delay_100ms
                                    372 ;	-----------------------------------------
      000069                        373 _delay_100ms:
                                    374 ;	.\src\main.c:35: while (--j)
      000069 7F 8A            [12]  375 	mov	r7,#0x8a
      00006B 7E C3            [12]  376 	mov	r6,#0xc3
      00006D                        377 00101$:
      00006D DF FE            [24]  378 	djnz	r7,00101$
                                    379 ;	.\src\main.c:37: } while (--i);
      00006F DE FC            [24]  380 	djnz	r6,00101$
                                    381 ;	.\src\main.c:38: }
      000071 22               [24]  382 	ret
                                    383 	.area CSEG    (CODE)
                                    384 	.area CONST   (CODE)
                                    385 	.area XINIT   (CODE)
                                    386 	.area CABS    (ABS,CODE)
