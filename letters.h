#ifndef LETTERS_H
#define LETTERS_H

#include "types.h"

//ALL ZEROS
#define BLANK_SPACE 62
#define LETTER_WIDTH 7
#define LETTER_HEIGHT 10
#define LETTER_VECTOR_SIZE 70 //letterw * letterh
#define ALPHABET_SIZE 26
#define MAPPED_CHARS 63 //caracteres mapeados ate o momento



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
BLANK_SPACE,    //  LF     0x0a     10
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
BLANK_SPACE,    //  !      0x21     33
BLANK_SPACE,    //  "      0x22     34
BLANK_SPACE,    //  #      0x23     35
BLANK_SPACE,    //  $      0x24     36
BLANK_SPACE,    //  %      0x25     37
BLANK_SPACE,    //  &      0x26     38
BLANK_SPACE,    //  '      0x27     39
BLANK_SPACE,    //  (      0x28     40
BLANK_SPACE,    //  )      0x29     41
BLANK_SPACE,    //  *      0x2a     42
BLANK_SPACE,    //  +      0x2b     43
BLANK_SPACE,    //  ´      0x2c     44
BLANK_SPACE,    //  -      0x2d     45
BLANK_SPACE,    //  .      0x2e     46
BLANK_SPACE,    //  /      0x2f     47
52,             //  0      0x30     48
53,             //  1      0x31     49
54,             //  2      0x32     50
55,             //  3      0x33     51
56,             //  4      0x34     52
57,             //  5      0x35     53
58,             //  6      0x36     54
59,             //  7      0x37     55
60,             //  8      0x38     56
61,             //  9      0x39     57
BLANK_SPACE,    //  :      0x3a     58
BLANK_SPACE,    //  ;      0x3b     59
BLANK_SPACE,    //  <      0x3c     60
BLANK_SPACE,    //  =      0x3d     61
BLANK_SPACE,    //  >      0x3e     62
BLANK_SPACE,    //  ?      0x3f     63
BLANK_SPACE,    //  @      0x40     64
0,              //  A      0x41     65
1,              //  B      0x42     66
2,              //  C      0x43     67
3,              //  D      0x44     68
4,              //  E      0x45     69
5,              //  F      0x46     70
6,              //  G      0x47     71
7,              //  H      0x48     72
8,              //  I      0x49     73
9,              //  J      0x4a     74
10,             //  K      0x4b     75
11,             //  L      0x4c     76
12,             //  M      0x4d     77
13,             //  N      0x4e     78
14,             //  O      0x4f     79
15,             //  P      0x50     80
16,             //  Q      0x51     81
17,             //  R      0x52     82
18,             //  S      0x53     83
19,             //  T      0x54     84
20,             //  U      0x55     85
21,             //  V      0x56     86
22,             //  W      0x57     87
23,             //  X      0x58     88
24,             //  Y      0x59     89
25,             //  Z      0x5a     90
BLANK_SPACE,    //  [      0x5b     91
BLANK_SPACE,    //  '\'    0x5c     92
BLANK_SPACE,    //  ]      0x5d     93
BLANK_SPACE,    //  ^      0x5e     94
BLANK_SPACE,    //  _      0x5f     95
BLANK_SPACE,    //  `      0x60     96
26,             //  a      0x61     97
27,             //  b      0x62     98
28,             //  c      0x63     99
29,             //  d      0x64     100
30,             //  e      0x65     101
31,             //  f      0x66     102
32,             //  g      0x67     103
33,             //  h      0x68     104
34,             //  i      0x69     105
35,             //  j      0x6a     106
36,             //  k      0x6b     107
37,             //  l      0x6c     108
38,             //  m      0x6d     109
39,             //  n      0x6e     110
40,             //  o      0x6f     111
41,             //  p      0x70     112
42,             //  q      0x71     113
43,             //  r      0x72     114
44,             //  s      0x73     115
45,             //  t      0x74     116
46,             //  u      0x75     117
47,             //  v      0x76     118
48,             //  w      0x77     119
49,             //  x      0x78     120
50,             //  y      0x79     121
51,             //  z      0x7a     122
BLANK_SPACE,    //  {      0x7b     123
BLANK_SPACE,    //  |      0x7c     124
BLANK_SPACE,    //  }      0x7d     125
BLANK_SPACE,    //  ~      0x7e     126
BLANK_SPACE     //  DEL    0x7f     127
};

uint8 characters[MAPPED_CHARS][70] = {
	{
		0,0,0,0,0,0,0,
		0,0,0,1,1,1,0,
		0,0,1,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,0,0,0,
		0,1,0,0,1,0,0,
		0,1,0,0,1,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,1,1,1,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,0,0,
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
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,1,1,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,1,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,1,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,
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
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,1,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,1,0,0,
		0,1,0,0,1,0,0,
		0,1,0,1,0,0,0,
		0,1,1,0,0,0,0,
		0,1,0,1,0,0,0,
		0,1,0,0,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,0,1,1,0,
		0,1,0,1,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
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
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,1,0,0,
		0,1,0,0,0,1,0,
		0,0,1,1,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,1,0,1,0,0,0,
		0,1,0,0,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,0,0,
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
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,1,0,1,0,
		0,1,1,0,1,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,0,1,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,1,0,0,
		0,1,0,0,1,0,0,
		0,1,0,0,1,0,0,
		0,1,0,0,1,0,0,
		0,0,1,1,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,1,1,0,
		0,0,1,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,0,1,1,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,1,1,1,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,1,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
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
		0,0,1,0,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,1,0,
		0,0,0,0,0,1,0,
		0,0,0,1,1,0,0,
		0,0,0,0,0,0,0,
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
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,1,0,0,
		0,0,0,0,1,0,0,
		0,1,0,0,1,0,0,
		0,0,1,1,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,1,0,0,
		0,1,1,1,0,0,0,
		0,1,1,0,0,0,0,
		0,1,0,1,0,0,0,
		0,1,0,0,1,0,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,1,0,
		0,0,0,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,1,0,1,0,
		0,1,0,1,0,1,0,
		0,1,0,1,0,1,0,
		0,1,0,1,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,0,0,0,
		0,1,0,0,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,1,1,1,0,
		0,1,1,0,0,1,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,1,1,1,0,
		0,0,1,0,0,0,0,
		0,0,0,1,1,0,0,
		0,0,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,1,1,1,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,1,0,
		0,0,0,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,1,0,1,0,
		0,0,1,1,1,0,0,
		0,0,1,0,1,0,0,
		0,0,0,0,0,0,0,
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
		0,1,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,1,1,1,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,1,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,1,0,0,0,
		0,1,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,1,0,0,0,0,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,1,0,
		0,1,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,0,0,
		0,1,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,1,0,
		0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,1,0,0,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
	{
		0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,1,0,
		0,0,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,1,1,0,0,
		0,0,0,0,0,0,0,
	},
    {
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,   
    }
};


#endif