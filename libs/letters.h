#ifndef LETTERS_H
#define LETTERS_H

#include "../types.h"

//ALL ZEROS
#define BLANK_SPACE 0
#define LETTER_WIDTH 7
#define LETTER_HEIGHT 9
#define LETTER_VECTOR_SIZE LETTER_HEIGHT*LETTER_WIDTH //letterw * letterh
#define ALPHABET_SIZE 26
#define MAPPED_CHARS 87 //caracteres mapeados ate o momento



char map_ascii[128] = {
BLANK_SPACE,    //  NULL   0x00     0
BLANK_SPACE,    //  SOH    0x01     1
BLANK_SPACE,    //  SOT    0x02     2
BLANK_SPACE,    //  ETX    0x03     3
BLANK_SPACE,    //  EOT    0x04     4
BLANK_SPACE,    //  ENQ    0x05     5
BLANK_SPACE,    //  ACK    0x06     6
BLANK_SPACE,    //  BEL    0x07     7
BLANK_SPACE,    //  BS     0x08     8
BLANK_SPACE,    //  TAB    0x09     9
BLANK_SPACE,    //  LF     0x0a     10  line feed nao esta mapeado mas pode ser usado para quebra de linhas
BLANK_SPACE,    //  VT     0x0b     11
BLANK_SPACE,    //  FF     0x0c     12
BLANK_SPACE,    //  CR     0x0d     13
BLANK_SPACE,    //  SO     0x0e     14
BLANK_SPACE,    //  SI     0x0f     15
BLANK_SPACE,    //  DLE    0x10     16
BLANK_SPACE,    //  DC1    0x11     17
BLANK_SPACE,    //  DC2    0x12     18
BLANK_SPACE,    //  DC3    0x13     19
BLANK_SPACE,    //  DC4    0x14     20
BLANK_SPACE,    //  NAK    0x15     21
BLANK_SPACE,    //  SYN    0x16     22
BLANK_SPACE,    //  ETB    0x17     23
BLANK_SPACE,    //  CAN    0x18     24
BLANK_SPACE,    //  EM     0x19     25
BLANK_SPACE,    //  SUB    0x1a     26
BLANK_SPACE,    //  ESC    0x1b     27
BLANK_SPACE,    //  FS     0x1c     28
BLANK_SPACE,    //  GS     0x1d     29
BLANK_SPACE,    //  RS     0x1e     30
BLANK_SPACE,    //  US     0x1f     31
BLANK_SPACE,    //  SPACE  0x20     32
63,    			//  !      0x21     33
77,    			//  "      0x22     34
64,    			//  #      0x23     35
65,    			//  $      0x24     36
66,    			//  %      0x25     37
BLANK_SPACE,    //  &      0x26     38
67,    			//  '      0x27     39
68,    			//  (      0x28     40
69,    			//  )      0x29     41
78,    			//  *      0x2a     42
70,    			//  +      0x2b     43
71,    			//  ,      0x2c     44
72,    			//  -      0x2d     45
73,    			//  .      0x2e     46
79,    			//  /      0x2f     47
53,             //  0      0x30     48
54,             //  1      0x31     49
55,             //  2      0x32     50
56,             //  3      0x33     51
57,             //  4      0x34     52
58,             //  5      0x35     53
59,             //  6      0x36     54
60,             //  7      0x37     55
61,             //  8      0x38     56
62,             //  9      0x39     57
81,    			//  :      0x3a     58
74,    			//  ;      0x3b     59
BLANK_SPACE,    //  <      0x3c     60
75,    			//  =      0x3d     61
BLANK_SPACE,    //  >      0x3e     62
82,    			//  ?      0x3f     63
76,    			//  @      0x40     64
1,              //  A      0x41     65
2,              //  B      0x42     66
3,              //  C      0x43     67
4,              //  D      0x44     68
5,              //  E      0x45     69
6,              //  F      0x46     70
7,              //  G      0x47     71
8,              //  H      0x48     72
9,              //  I      0x49     73
10,             //  J      0x4a     74
11,             //  K      0x4b     75
12,             //  L      0x4c     76
13,             //  M      0x4d     77
14,             //  N      0x4e     78
15,             //  O      0x4f     79
16,             //  P      0x50     80
17,             //  Q      0x51     81
18,             //  R      0x52     82
19,             //  S      0x53     83
20,             //  T      0x54     84
21,             //  U      0x55     85
22,             //  V      0x56     86
23,             //  W      0x57     87
24,             //  X      0x58     88
25,             //  Y      0x59     89
26,             //  Z      0x5a     90
83,    			//  [      0x5b     91
80,    			//  '\'    0x5c     92
84,    			//  ]      0x5d     93
BLANK_SPACE,    //  ^      0x5e     94
BLANK_SPACE,    //  _      0x5f     95
BLANK_SPACE,    //  `      0x60     96
27,             //  a      0x61     97
28,             //  b      0x62     98
29,             //  c      0x63     99
30,             //  d      0x64     100
31,             //  e      0x65     101
32,             //  f      0x66     102
33,             //  g      0x67     103
34,             //  h      0x68     104
35,             //  i      0x69     105
36,             //  j      0x6a     106
37,             //  k      0x6b     107
38,             //  l      0x6c     108
39,             //  m      0x6d     109
40,             //  n      0x6e     110
41,             //  o      0x6f     111
42,             //  p      0x70     112
43,             //  q      0x71     113
44,             //  r      0x72     114
45,             //  s      0x73     115
46,             //  t      0x74     116
47,             //  u      0x75     117
48,             //  v      0x76     118
49,             //  w      0x77     119
50,             //  x      0x78     120
51,             //  y      0x79     121
52,             //  z      0x7a     122
85,    			//  {      0x7b     123
BLANK_SPACE,    //  |      0x7c     124
86,    			//  }      0x7d     125
BLANK_SPACE,    //  ~      0x7e     126
BLANK_SPACE     //  DEL    0x7f     127
};


uint8 characters[MAPPED_CHARS][LETTER_WIDTH*LETTER_HEIGHT] = {
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,1,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,1,0,0,
		0,1,0,0,1,0,0,
		0,0,1,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,1,0,0,
		0,1,1,1,0,0,0,
		0,1,0,0,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,1,0,1,1,0,
		0,1,0,1,0,1,0,
		0,1,0,1,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,0,0,1,0,
		0,1,0,1,0,1,0,
		0,1,0,0,1,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,1,0,0,
		0,0,1,1,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,1,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,1,0,1,0,
		0,1,1,0,1,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,1,0,
		0,0,1,1,1,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,1,1,1,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,1,0,0,0,0,0,
		0,0,1,1,1,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,1,0,0,
		0,0,1,0,0,1,0,
		0,0,1,0,0,0,0,
		0,1,1,1,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,1,0,
		0,0,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,1,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,1,0,0,
		0,1,0,0,1,0,0,
		0,0,1,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,1,0,0,
		0,1,1,1,0,0,0,
		0,1,0,0,1,0,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,1,0,1,0,
		0,1,0,1,0,1,0,
		0,1,0,1,0,1,0,
		0,1,0,1,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,0,1,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,1,0,0,
		0,0,1,1,1,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,1,1,0,0,
		0,1,1,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,1,0,
		0,1,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,1,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,1,1,0,
		0,0,1,1,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,1,0,1,0,
		0,1,1,1,1,1,0,
		0,1,0,1,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,0,1,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,1,0,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,1,0,
		0,0,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,1,1,0,
		0,1,0,1,0,1,0,
		0,1,1,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,1,0,0,0,
		0,1,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,1,1,0,0,
		0,0,1,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,1,1,0,0,
		0,0,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,1,0,0,
		0,0,0,1,1,0,0,
		0,0,1,0,1,0,0,
		0,1,0,0,1,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,1,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,1,0,
		0,0,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,0,1,0,0,
		0,0,1,0,1,0,0,
		0,1,1,1,1,1,0,
		0,0,1,0,1,0,0,
		0,1,1,1,1,1,0,
		0,0,1,0,1,0,0,
		0,0,1,0,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,1,1,1,0,
		0,1,0,1,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,1,0,1,0,
		0,1,1,1,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,
		0,1,1,0,0,1,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,1,0,0,1,1,0,
		0,0,0,0,1,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,1,1,1,0,
		0,1,0,1,0,1,0,
		0,1,0,1,1,0,0,
		0,1,0,0,0,0,0,
		0,0,1,1,1,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,0,1,0,0,
		0,0,1,0,1,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,1,0,1,0,
		0,0,1,1,1,0,0,
		0,1,1,1,1,1,0,
		0,0,1,1,1,0,0,
		0,1,0,1,0,1,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,1,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,1,0,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,0,0,0,0,0,0
	}
};


#endif