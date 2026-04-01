# 1 "effects.c" 1
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/osbind.h" 2
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 1 "effects.c" 2
# 1 "./effects.h" 1
# 1 "./psg.h" 1
# 1 "C:/c68/include/stdio.h" 1
# 20 "C:/c68/include/stdio.h"
typedef unsigned long  size_t;
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 4 "./psg.h" 2
# 1 "./types.h" 1
# 11 "./types.h"
typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
# 5 "./psg.h" 2




void write_psg(int reg, UINT8 val);



void read_psg(int reg);




void set_tone(int channel, int tuning);



void set_volume(int channel, int volume);



void enable_channel(int channel, int tone_on, int noise_on);



void set_noise(int tuning);




void set_envelope(int shape, unsigned int sustain);


void stop_sound();
# 1 "./effects.h" 2
# 1 "./events.h" 1
# 1 "./model.h" 1
# 1 "./types.h" 1
# 4 "./model.h" 2
# 28 "./model.h"
extern const UINT32 Chuck_bitmap[32 ];
extern const UINT32 womenWalking_bitmap[32 ];
extern const UINT32 womenSwimming_forward_bitmap[32 ];
extern const UINT32 womenSwimming_backward_bitmap[32 ];
extern const UINT32 road_bitmap_upper[32 ];
extern const UINT32 road_bitmap_lower[32 ];
extern const UINT32 water_bitmap[32 ];

typedef struct {
    int x;
    int y;
    int oldx;
    int oldy;
    int isWalking;
    int deltaX;
    int deltaY;
    int isColliding;
    int deathCounter;
} Chuck;

typedef struct {
    int x, y;
    int oldx, oldy;
    int deltaX, deltaY;
    int isColliding;
} WomenWalking;

typedef struct {
    unsigned int x,y;
    int deltaX, deltaY;
    int isColliding;
    int isForward;
    int frameCount;
} WomenSwimming;

typedef struct {
    unsigned int x,y;
    int isLower;
    int isColliding;
} Road;

typedef struct {
    unsigned int x,y;
} Water;

typedef struct {
    int gameOver;
    int crossCount;
    int oldCrossCount;
    Chuck chuck;
    WomenWalking womenWalking[15];

    WomenSwimming womenSwimming[30];
    Water water[20];
    Road road[120];
} Model;
# 102 "./model.h"
void initChuck(Chuck* chuck, int x, int y);
# 121 "./model.h"
void startWalking(Chuck* chuck, int deltaX, int deltaY);
# 140 "./model.h"
void updateChuck(Chuck* chuck);
# 156 "./model.h"
void stopWalking(Chuck* chuck);
# 172 "./model.h"
void initWomenWalking(WomenWalking* womenWalking, unsigned int x, unsigned int y);
# 186 "./model.h"
void updateWomenWalking(WomenWalking* womenWalking);
# 200 "./model.h"
void collisionWomenWalking(WomenWalking* womenWalking, Chuck* chuck);
# 214 "./model.h"
int intGenerator(int max);
# 233 "./model.h"
void initWomenSwimming(WomenSwimming* womenSwimming, unsigned int x, unsigned int y);
# 249 "./model.h"
void updateWomenSwimming(WomenSwimming* womenSwimming);
# 265 "./model.h"
void collisionWomenSwimming(WomenSwimming* womenSwimming, Chuck* chuck);

void initRoad(Road* road, UINT16 x, UINT16 y, int z);
void isRoadCollidingWalker(Road* road, WomenWalking* womenWalking);
void isRoadCollidingChuck(Road* road, Chuck* chuck);
# 286 "./model.h"
void initWater(Water* water, unsigned int x, unsigned int y);
# 297 "./model.h"
void Model_init(Model *model);
# 308 "./model.h"
void init_land(Model *model);
# 319 "./model.h"
void init_women(Model *model);
# 4 "./events.h" 2
# 1 "./asynch.h" 1
# 1 "./model.h" 1
# 4 "./asynch.h" 2
# 25 "./asynch.h"
void asynch_button_W(Model *model);
# 39 "./asynch.h"
void asynch_button_A(Model *model);
# 53 "./asynch.h"
void asynch_button_S(Model *model);
# 67 "./asynch.h"
void asynch_button_D(Model *model);
# 80 "./asynch.h"
void asynch_button_X(Model *model);
# 92 "./asynch.h"
void asynch_button_P(Model *model);
# 5 "./events.h" 2
# 1 "./synch.h" 1
# 1 "./model.h" 1
# 4 "./synch.h" 2


void synch_update(Model *model);
# 6 "./events.h" 2
# 1 "./cond.h" 1
# 1 "./model.h" 1
# 4 "./cond.h" 2
# 30 "./cond.h"
void cond_update(Model *model);
# 7 "./events.h" 2
# 31 "./events.h"
void event_handler(Model *model);
# 2 "./effects.h" 2
# 1 "./model.h" 1
# 3 "./effects.h" 2
# 1 "./sound.h" 1
# 1 "./types.h" 1
# 3 "./sound.h" 2
# 1 "C:/c68/include/osbind.h" 1
# 4 "./sound.h" 2
# 1 "./psg.h" 1
# 6 "./sound.h" 2
# 16 "./sound.h"
void start_music();
# 24 "./sound.h"
void update_music(UINT32 time_elapsed);


UINT32 get_clock();


void delay(int count);
# 4 "./effects.h" 2
# 22 "./effects.h"
void play_chuck_walking();



void play_chuck_win();




void play_touch_edge();




void play_women_collide();
# 2 "effects.c" 2
# 1 "./psg.h" 1
# 3 "effects.c" 2




void play_chuck_walking() {
    enable_channel(2, 1, 0);
    set_envelope(0x0A, 0x2000);
    set_volume(2, 8);

    set_tone(2, 0x1ac);
    delay(10);

    set_tone(2, 0x0d6);
    delay(20);

    set_volume(2, 0);
}


void play_chuck_win() {
    enable_channel(2, 1, 0);
    set_envelope(0x0A, 0x2000);
    set_volume(2, 8);

    set_tone(2, 0x0be);
    delay(20);

    set_tone(2, 0x17d);
    delay(30);

    set_volume(2, 0);
}


void play_touch_edge() {
    enable_channel(2, 1, 0);
    set_envelope(0x0A, 0x2000);
    set_volume(2, 8);

    set_tone(2, 0x6ae);
    set_noise(0x01);
    delay(20);

    set_volume(2, 0);
}



void play_women_collide() {
    enable_channel(2, 1, 1);
    set_envelope(0x0A, 0x2000);
    set_volume(2, 11);

    set_tone(2, 0x54d);
    delay(20);

    set_tone(2, 0x6ae);
    set_noise(0x03);
    delay(30);

    set_volume(2, 0);
}
