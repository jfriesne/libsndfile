/*
** Copyright (C) 1999-2016 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation; either version 2.1 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/*
** sndfile.h -- system-wide definitions
**
** API documentation is in the doc/ directory of the source code tarball
** and at http://libsndfile.github.io/libsndfile/api.html.
*/

#ifndef SNDFILE_H
#define SNDFILE_H

/* This is the version 1.0.X header file. */
#define	SNDFILE_1

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* The following file types can be read and written.
** A file type would consist of a major type (ie SF_FORMAT_WAV) bitwise
** ORed with a minor type (ie SF_FORMAT_PCM). SF_FORMAT_TYPEMASK and
** SF_FORMAT_SUBMASK can be used to separate the major and minor file
** types.
*/

enum
{	/* Major formats. */
	SF_FORMAT_WAV			= 0x010000,		/* Microsoft WAV format (little endian default). */
	SF_FORMAT_AIFF			= 0x020000,		/* Apple/SGI AIFF format (big endian). */
	SF_FORMAT_AU			= 0x030000,		/* Sun/NeXT AU format (big endian). */
	SF_FORMAT_RAW			= 0x040000,		/* RAW PCM data. */
	SF_FORMAT_PAF			= 0x050000,		/* Ensoniq PARIS file format. */
	SF_FORMAT_SVX			= 0x060000,		/* Amiga IFF / SVX8 / SV16 format. */
	SF_FORMAT_NIST			= 0x070000,		/* Sphere NIST format. */
	SF_FORMAT_VOC			= 0x080000,		/* VOC files. */
	SF_FORMAT_IRCAM			= 0x0A0000,		/* Berkeley/IRCAM/CARL */
	SF_FORMAT_W64			= 0x0B0000,		/* Sonic Foundry's 64 bit RIFF/WAV */
	SF_FORMAT_MAT4			= 0x0C0000,		/* Matlab (tm) V4.2 / GNU Octave 2.0 */
	SF_FORMAT_MAT5			= 0x0D0000,		/* Matlab (tm) V5.0 / GNU Octave 2.1 */
	SF_FORMAT_PVF			= 0x0E0000,		/* Portable Voice Format */
	SF_FORMAT_XI			= 0x0F0000,		/* Fasttracker 2 Extended Instrument */
	SF_FORMAT_HTK			= 0x100000,		/* HMM Tool Kit format */
	SF_FORMAT_SDS			= 0x110000,		/* Midi Sample Dump Standard */
	SF_FORMAT_AVR			= 0x120000,		/* Audio Visual Research */
	SF_FORMAT_WAVEX			= 0x130000,		/* MS WAVE with WAVEFORMATEX */
	SF_FORMAT_SD2			= 0x160000,		/* Sound Designer 2 */
	SF_FORMAT_FLAC			= 0x170000,		/* FLAC lossless file format */
	SF_FORMAT_CAF			= 0x180000,		/* Core Audio File format */
	SF_FORMAT_WVE			= 0x190000,		/* Psion WVE format */
	SF_FORMAT_OGG			= 0x200000,		/* Xiph OGG container */
	SF_FORMAT_MPC2K			= 0x210000,		/* Akai MPC 2000 sampler */
	SF_FORMAT_RF64			= 0x220000,		/* RF64 WAV file */
	SF_FORMAT_MPEG			= 0x230000,		/* MPEG-1/2 audio stream */

	/* Subtypes from here on. */

	SF_FORMAT_PCM_S8		= 0x0001,		/* Signed 8 bit data */
	SF_FORMAT_PCM_16		= 0x0002,		/* Signed 16 bit data */
	SF_FORMAT_PCM_24		= 0x0003,		/* Signed 24 bit data */
	SF_FORMAT_PCM_32		= 0x0004,		/* Signed 32 bit data */

	SF_FORMAT_PCM_U8		= 0x0005,		/* Unsigned 8 bit data (WAV and RAW only) */

	SF_FORMAT_FLOAT			= 0x0006,		/* 32 bit float data */
	SF_FORMAT_DOUBLE		= 0x0007,		/* 64 bit float data */

	SF_FORMAT_ULAW			= 0x0010,		/* U-Law encoded. */
	SF_FORMAT_ALAW			= 0x0011,		/* A-Law encoded. */
	SF_FORMAT_IMA_ADPCM		= 0x0012,		/* IMA ADPCM. */
	SF_FORMAT_MS_ADPCM		= 0x0013,		/* Microsoft ADPCM. */

	SF_FORMAT_GSM610		= 0x0020,		/* GSM 6.10 encoding. */
	SF_FORMAT_VOX_ADPCM		= 0x0021,		/* OKI / Dialogix ADPCM */

	SF_FORMAT_NMS_ADPCM_16	= 0x0022,		/* 16kbs NMS G721-variant encoding. */
	SF_FORMAT_NMS_ADPCM_24	= 0x0023,		/* 24kbs NMS G721-variant encoding. */
	SF_FORMAT_NMS_ADPCM_32	= 0x0024,		/* 32kbs NMS G721-variant encoding. */

	SF_FORMAT_G721_32		= 0x0030,		/* 32kbs G721 ADPCM encoding. */
	SF_FORMAT_G723_24		= 0x0031,		/* 24kbs G723 ADPCM encoding. */
	SF_FORMAT_G723_40		= 0x0032,		/* 40kbs G723 ADPCM encoding. */

	SF_FORMAT_DWVW_12		= 0x0040, 		/* 12 bit Delta Width Variable Word encoding. */
	SF_FORMAT_DWVW_16		= 0x0041, 		/* 16 bit Delta Width Variable Word encoding. */
	SF_FORMAT_DWVW_24		= 0x0042, 		/* 24 bit Delta Width Variable Word encoding. */
	SF_FORMAT_DWVW_N		= 0x0043, 		/* N bit Delta Width Variable Word encoding. */

	SF_FORMAT_DPCM_8		= 0x0050,		/* 8 bit differential PCM (XI only) */
	SF_FORMAT_DPCM_16		= 0x0051,		/* 16 bit differential PCM (XI only) */

	SF_FORMAT_VORBIS		= 0x0060,		/* Xiph Vorbis encoding. */
	SF_FORMAT_OPUS			= 0x0064,		/* Xiph/Skype Opus encoding. */

	SF_FORMAT_ALAC_16		= 0x0070,		/* Apple Lossless Audio Codec (16 bit). */
	SF_FORMAT_ALAC_20		= 0x0071,		/* Apple Lossless Audio Codec (20 bit). */
	SF_FORMAT_ALAC_24		= 0x0072,		/* Apple Lossless Audio Codec (24 bit). */
	SF_FORMAT_ALAC_32		= 0x0073,		/* Apple Lossless Audio Codec (32 bit). */

	SF_FORMAT_MPEG_LAYER_I	= 0x0080,		/* MPEG-1 Audio Layer I */
	SF_FORMAT_MPEG_LAYER_II	= 0x0081,		/* MPEG-1 Audio Layer II */
	SF_FORMAT_MPEG_LAYER_III = 0x0082,		/* MPEG-2 Audio Layer III */

	/* Endian-ness options. */

	SF_ENDIAN_FILE			= 0x00000000,	/* Default file endian-ness. */
	SF_ENDIAN_LITTLE		= 0x10000000,	/* Force little endian-ness. */
	SF_ENDIAN_BIG			= 0x20000000,	/* Force big endian-ness. */
	SF_ENDIAN_CPU			= 0x30000000,	/* Force CPU endian-ness. */

	SF_FORMAT_SUBMASK		= 0x0000FFFF,
	SF_FORMAT_TYPEMASK		= 0x0FFF0000,
	SF_FORMAT_ENDMASK		= 0x30000000
} ;

/*
** The following are the valid command numbers for the sf_command()
** interface.  The use of these commands is documented in the file
** command.html in the doc directory of the source code distribution.
*/

enum
{	SFC_GET_LIB_VERSION				= 0x1000,
	SFC_GET_LOG_INFO				= 0x1001,
	SFC_GET_CURRENT_SF_INFO			= 0x1002,


	SFC_GET_NORM_DOUBLE				= 0x1010,
	SFC_GET_NORM_FLOAT				= 0x1011,
	SFC_SET_NORM_DOUBLE				= 0x1012,
	SFC_SET_NORM_FLOAT				= 0x1013,
	SFC_SET_SCALE_FLOAT_INT_READ	= 0x1014,
	SFC_SET_SCALE_INT_FLOAT_WRITE	= 0x1015,

	SFC_GET_SIMPLE_FORMAT_COUNT		= 0x1020,
	SFC_GET_SIMPLE_FORMAT			= 0x1021,

	SFC_GET_FORMAT_INFO				= 0x1028,

	SFC_GET_FORMAT_MAJOR_COUNT		= 0x1030,
	SFC_GET_FORMAT_MAJOR			= 0x1031,
	SFC_GET_FORMAT_SUBTYPE_COUNT	= 0x1032,
	SFC_GET_FORMAT_SUBTYPE			= 0x1033,

	SFC_CALC_SIGNAL_MAX				= 0x1040,
	SFC_CALC_NORM_SIGNAL_MAX		= 0x1041,
	SFC_CALC_MAX_ALL_CHANNELS		= 0x1042,
	SFC_CALC_NORM_MAX_ALL_CHANNELS	= 0x1043,
	SFC_GET_SIGNAL_MAX				= 0x1044,
	SFC_GET_MAX_ALL_CHANNELS		= 0x1045,

	SFC_SET_ADD_PEAK_CHUNK			= 0x1050,

	SFC_UPDATE_HEADER_NOW			= 0x1060,
	SFC_SET_UPDATE_HEADER_AUTO		= 0x1061,

	SFC_FILE_TRUNCATE				= 0x1080,

	SFC_SET_RAW_START_OFFSET		= 0x1090,

	/* Commands reserved for dithering, which is not implemented. */
	SFC_SET_DITHER_ON_WRITE			= 0x10A0,
	SFC_SET_DITHER_ON_READ			= 0x10A1,

	SFC_GET_DITHER_INFO_COUNT		= 0x10A2,
	SFC_GET_DITHER_INFO				= 0x10A3,

	SFC_GET_EMBED_FILE_INFO			= 0x10B0,

	SFC_SET_CLIPPING				= 0x10C0,
	SFC_GET_CLIPPING				= 0x10C1,

	SFC_GET_CUE_COUNT				= 0x10CD,
	SFC_GET_CUE						= 0x10CE,
	SFC_SET_CUE						= 0x10CF,

	SFC_GET_INSTRUMENT				= 0x10D0,
	SFC_SET_INSTRUMENT				= 0x10D1,

	SFC_GET_LOOP_INFO				= 0x10E0,

	SFC_GET_BROADCAST_INFO			= 0x10F0,
	SFC_SET_BROADCAST_INFO			= 0x10F1,

	SFC_GET_CHANNEL_MAP_INFO		= 0x1100,
	SFC_SET_CHANNEL_MAP_INFO		= 0x1101,

	SFC_RAW_DATA_NEEDS_ENDSWAP		= 0x1110,

	/* Support for Wavex Ambisonics Format */
	SFC_WAVEX_SET_AMBISONIC			= 0x1200,
	SFC_WAVEX_GET_AMBISONIC			= 0x1201,

	/*
	** RF64 files can be set so that on-close, writable files that have less
	** than 4GB of data in them are converted to RIFF/WAV, as per EBU
	** recommendations.
	*/
	SFC_RF64_AUTO_DOWNGRADE			= 0x1210,

	SFC_SET_VBR_ENCODING_QUALITY	= 0x1300,
	SFC_SET_COMPRESSION_LEVEL		= 0x1301,

	/* Ogg format commands */
	SFC_SET_OGG_PAGE_LATENCY_MS		= 0x1302,
	SFC_SET_OGG_PAGE_LATENCY		= 0x1303,
	SFC_GET_OGG_STREAM_SERIALNO		= 0x1306,

	SFC_GET_BITRATE_MODE			= 0x1304,
	SFC_SET_BITRATE_MODE			= 0x1305,

	/* Cart Chunk support */
	SFC_SET_CART_INFO				= 0x1400,
	SFC_GET_CART_INFO				= 0x1401,

	/* Opus files original samplerate metadata */
	SFC_SET_ORIGINAL_SAMPLERATE		= 0x1500,
	SFC_GET_ORIGINAL_SAMPLERATE		= 0x1501,

	/* Following commands for testing only. */
	SFC_TEST_IEEE_FLOAT_REPLACE		= 0x6001,

	/*
	** These SFC_SET_ADD_* values are deprecated and will disappear at some
	** time in the future. They are guaranteed to be here up to and
	** including version 1.0.8 to avoid breakage of existing software.
	** They currently do nothing and will continue to do nothing.
	*/
	SFC_SET_ADD_HEADER_PAD_CHUNK	= 0x1051,

	SFC_SET_ADD_DITHER_ON_WRITE		= 0x1070,
	SFC_SET_ADD_DITHER_ON_READ		= 0x1071
} ;


/*
** String types that can be set and read from files. Not all file types
** support this and even the file types which support one, may not support
** all string types.
*/

enum
{	SF_STR_TITLE					= 0x01,
	SF_STR_COPYRIGHT				= 0x02,
	SF_STR_SOFTWARE					= 0x03,
	SF_STR_ARTIST					= 0x04,
	SF_STR_COMMENT					= 0x05,
	SF_STR_DATE						= 0x06,
	SF_STR_ALBUM					= 0x07,
	SF_STR_LICENSE					= 0x08,
	SF_STR_TRACKNUMBER				= 0x09,
	SF_STR_GENRE					= 0x10
} ;

/*
** Use the following as the start and end index when doing metadata
** transcoding.
*/

#define	SF_STR_FIRST	SF_STR_TITLE
#define	SF_STR_LAST		SF_STR_GENRE

enum
{	/* True and false */
	SF_FALSE	= 0,
	SF_TRUE		= 1,

	/* Modes for opening files. */
	SFM_READ	= 0x10,
	SFM_WRITE	= 0x20,
	SFM_RDWR	= 0x30,

	SF_AMBISONIC_NONE		= 0x40,
	SF_AMBISONIC_B_FORMAT	= 0x41
} ;

/* Public error values. These are guaranteed to remain unchanged for the duration
** of the library major version number.
** There are also a large number of private error numbers which are internal to
** the library which can change at any time.
*/

enum
{	SF_ERR_NO_ERROR				= 0,
	SF_ERR_UNRECOGNISED_FORMAT	= 1,
	SF_ERR_SYSTEM				= 2,
	SF_ERR_MALFORMED_FILE		= 3,
	SF_ERR_UNSUPPORTED_ENCODING	= 4
} ;


/* Channel map values (used with SFC_SET/GET_CHANNEL_MAP).
*/

enum
{	SF_CHANNEL_MAP_INVALID = 0,
	SF_CHANNEL_MAP_MONO = 1,
	SF_CHANNEL_MAP_LEFT,					/* Apple calls this 'Left' */
	SF_CHANNEL_MAP_RIGHT,					/* Apple calls this 'Right' */
	SF_CHANNEL_MAP_CENTER,					/* Apple calls this 'Center' */
	SF_CHANNEL_MAP_FRONT_LEFT,
	SF_CHANNEL_MAP_FRONT_RIGHT,
	SF_CHANNEL_MAP_FRONT_CENTER,
	SF_CHANNEL_MAP_REAR_CENTER,				/* Apple calls this 'Center Surround', Msft calls this 'Back Center' */
	SF_CHANNEL_MAP_REAR_LEFT,				/* Apple calls this 'Left Surround', Msft calls this 'Back Left' */
	SF_CHANNEL_MAP_REAR_RIGHT,				/* Apple calls this 'Right Surround', Msft calls this 'Back Right' */
	SF_CHANNEL_MAP_LFE,						/* Apple calls this 'LFEScreen', Msft calls this 'Low Frequency'  */
	SF_CHANNEL_MAP_FRONT_LEFT_OF_CENTER,	/* Apple calls this 'Left Center' */
	SF_CHANNEL_MAP_FRONT_RIGHT_OF_CENTER,	/* Apple calls this 'Right Center */
	SF_CHANNEL_MAP_SIDE_LEFT,				/* Apple calls this 'Left Surround Direct' */
	SF_CHANNEL_MAP_SIDE_RIGHT,				/* Apple calls this 'Right Surround Direct' */
	SF_CHANNEL_MAP_TOP_CENTER,				/* Apple calls this 'Top Center Surround' */
	SF_CHANNEL_MAP_TOP_FRONT_LEFT,			/* Apple calls this 'Vertical Height Left' */
	SF_CHANNEL_MAP_TOP_FRONT_RIGHT,			/* Apple calls this 'Vertical Height Right' */
	SF_CHANNEL_MAP_TOP_FRONT_CENTER,		/* Apple calls this 'Vertical Height Center' */
	SF_CHANNEL_MAP_TOP_REAR_LEFT,			/* Apple and MS call this 'Top Back Left' */
	SF_CHANNEL_MAP_TOP_REAR_RIGHT,			/* Apple and MS call this 'Top Back Right' */
	SF_CHANNEL_MAP_TOP_REAR_CENTER,			/* Apple and MS call this 'Top Back Center' */

	SF_CHANNEL_MAP_AMBISONIC_B_W,
	SF_CHANNEL_MAP_AMBISONIC_B_X,
	SF_CHANNEL_MAP_AMBISONIC_B_Y,
	SF_CHANNEL_MAP_AMBISONIC_B_Z,

	SF_CHANNEL_MAP_MAX
} ;

/* Bitrate mode values (for use with SFC_GET/SET_BITRATE_MODE)
*/
enum
{	SF_BITRATE_MODE_CONSTANT = 0,
	SF_BITRATE_MODE_AVERAGE,
	SF_BITRATE_MODE_VARIABLE
} ;


/* A SNDFILE* pointer can be passed around much like stdio.h's FILE* pointer. */

typedef	struct sf_private_tag	SNDFILE ;

/* The following typedef is system specific and is defined when libsndfile is
** compiled. sf_count_t will be a 64 bit value when the underlying OS allows
** 64 bit file offsets.
** On windows, we need to allow the same header file to be compiler by both GCC
** and the Microsoft compiler.
*/

typedef int64_t			sf_count_t ;
#ifndef SF_COUNT_MAX
#define SF_COUNT_MAX	INT64_MAX
#endif


/* A pointer to a SF_INFO structure is passed to sf_open () and filled in.
** On write, the SF_INFO structure is filled in by the user and passed into
** sf_open ().
*/

struct SF_INFO
{	sf_count_t	frames ;		/* Used to be called samples.  Changed to avoid confusion. */
	int			samplerate ;
	int			channels ;
	int			format ;
	int			sections ;
	int			seekable ;
} ;

typedef	struct SF_INFO SF_INFO ;

/* The SF_FORMAT_INFO struct is used to retrieve information about the sound
** file formats libsndfile supports using the sf_command () interface.
**
** Using this interface will allow applications to support new file formats
** and encoding types when libsndfile is upgraded, without requiring
** re-compilation of the application.
**
** Please consult the libsndfile documentation (particularly the information
** on the sf_command () interface) for examples of its use.
*/

typedef struct
{	int			format ;
	const char	*name ;
	const char	*extension ;
} SF_FORMAT_INFO ;

/*
** Enums and typedefs for adding dither on read and write.
** Reserved for future implementation.
*/

enum
{	SFD_DEFAULT_LEVEL	= 0,
	SFD_CUSTOM_LEVEL	= 0x40000000,

	SFD_NO_DITHER		= 500,
	SFD_WHITE			= 501,
	SFD_TRIANGULAR_PDF	= 502
} ;

typedef struct
{	int			type ;
	double		level ;
	const char	*name ;
} SF_DITHER_INFO ;

/* Struct used to retrieve information about a file embedded within a
** larger file. See SFC_GET_EMBED_FILE_INFO.
*/

typedef struct
{	sf_count_t	offset ;
	sf_count_t	length ;
} SF_EMBED_FILE_INFO ;

/*
**	Struct used to retrieve cue marker information from a file
*/

typedef struct
{	int32_t 	indx ;
	uint32_t 	position ;
	int32_t 	fcc_chunk ;
	int32_t 	chunk_start ;
	int32_t		block_start ;
	uint32_t 	sample_offset ;
	char name [256] ;
} SF_CUE_POINT ;

#define	SF_CUES_VAR(count) \
	struct \
	{	uint32_t cue_count ; \
		SF_CUE_POINT cue_points [count] ; \
	}

typedef SF_CUES_VAR (100) SF_CUES ;

/*
**	Structs used to retrieve music sample information from a file.
*/

enum
{	/*
	**	The loop mode field in SF_INSTRUMENT will be one of the following.
	*/
	SF_LOOP_NONE = 800,
	SF_LOOP_FORWARD,
	SF_LOOP_BACKWARD,
	SF_LOOP_ALTERNATING
} ;

typedef struct
{	int gain ;
	char basenote, detune ;
	char velocity_lo, velocity_hi ;
	char key_lo, key_hi ;
	int loop_count ;

	struct
	{	int mode ;
		uint32_t start ;
		uint32_t end ;
		uint32_t count ;
	} loops [16] ; /* make variable in a sensible way */
} SF_INSTRUMENT ;



/* Struct used to retrieve loop information from a file.*/
typedef struct
{
	short	time_sig_num ;	/* any positive integer    > 0  */
	short	time_sig_den ;	/* any positive power of 2 > 0  */
	int		loop_mode ;		/* see SF_LOOP enum             */

	int		num_beats ;		/* this is NOT the amount of quarter notes !!!*/
							/* a full bar of 4/4 is 4 beats */
							/* a full bar of 7/8 is 7 beats */

	float	bpm ;			/* suggestion, as it can be calculated using other fields:*/
							/* file's length, file's sampleRate and our time_sig_den*/
							/* -> bpms are always the amount of _quarter notes_ per minute */

	int	root_key ;			/* MIDI note, or -1 for None */
	int future [6] ;
} SF_LOOP_INFO ;


/*	Struct used to retrieve broadcast (EBU) information from a file.
**	Strongly (!) based on EBU "bext" chunk format used in Broadcast WAVE.
*/
#define	SF_BROADCAST_INFO_VAR(coding_hist_size) \
			struct \
			{	char		description [256] ; \
				char		originator [32] ; \
				char		originator_reference [32] ; \
				char		origination_date [10] ; \
				char		origination_time [8] ; \
				uint32_t	time_reference_low ; \
				uint32_t	time_reference_high ; \
				short		version ; \
				char		umid [64] ; \
				int16_t	loudness_value ; \
				int16_t	loudness_range ; \
				int16_t	max_true_peak_level ; \
				int16_t	max_momentary_loudness ; \
				int16_t	max_shortterm_loudness ; \
				char		reserved [180] ; \
				uint32_t	coding_history_size ; \
				char		coding_history [coding_hist_size] ; \
			}

/* SF_BROADCAST_INFO is the above struct with coding_history field of 256 bytes. */
typedef SF_BROADCAST_INFO_VAR (256) SF_BROADCAST_INFO ;

struct SF_CART_TIMER
{	char	usage [4] ;
	int32_t	value ;
} ;

typedef struct SF_CART_TIMER SF_CART_TIMER ;

#define	SF_CART_INFO_VAR(p_tag_text_size) \
			struct \
			{	char		version [4] ; \
				char		title [64] ; \
				char		artist [64] ; \
				char		cut_id [64] ; \
				char		client_id [64] ; \
				char		category [64] ; \
				char		classification [64] ; \
				char		out_cue [64] ; \
				char		start_date [10] ; \
				char		start_time [8] ; \
				char		end_date [10] ; \
				char		end_time [8] ; \
				char		producer_app_id [64] ; \
				char		producer_app_version [64] ; \
				char		user_def [64] ; \
				int32_t		level_reference ; \
				SF_CART_TIMER	post_timers [8] ; \
				char		reserved [276] ; \
				char		url [1024] ; \
				uint32_t	tag_text_size ; \
				char		tag_text [p_tag_text_size] ; \
			}

typedef SF_CART_INFO_VAR (256) SF_CART_INFO ;

/*	Virtual I/O functionality. */

typedef sf_count_t		(*sf_vio_get_filelen)	(void *user_data) ;
typedef sf_count_t		(*sf_vio_seek)		(sf_count_t offset, int whence, void *user_data) ;
typedef sf_count_t		(*sf_vio_read)		(void *ptr, sf_count_t count, void *user_data) ;
typedef sf_count_t		(*sf_vio_write)		(const void *ptr, sf_count_t count, void *user_data) ;
typedef sf_count_t		(*sf_vio_tell)		(void *user_data) ;

struct SF_VIRTUAL_IO
{	sf_vio_get_filelen	get_filelen ;
	sf_vio_seek			seek ;
	sf_vio_read			read ;
	sf_vio_write		write ;
	sf_vio_tell			tell ;
} ;

typedef	struct SF_VIRTUAL_IO SF_VIRTUAL_IO ;


/* Open the specified file for read, write or both. On error, this will
** return a NULL pointer. To find the error number, pass a NULL SNDFILE
** to sf_strerror ().
** All calls to sf_open() should be matched with a call to sf_close().
*/

SNDFILE* 	sf_open		(const char *path, int mode, SF_INFO *sfinfo) ;


/* Use the existing file descriptor to create a SNDFILE object. If close_desc
** is TRUE, the file descriptor will be closed when sf_close() is called. If
** it is FALSE, the descriptor will not be closed.
** When passed a descriptor like this, the library will assume that the start
** of file header is at the current file offset. This allows sound files within
** larger container files to be read and/or written.
** On error, this will return a NULL pointer. To find the error number, pass a
** NULL SNDFILE to sf_strerror ().
** All calls to sf_open_fd() should be matched with a call to sf_close().

*/

SNDFILE* 	sf_open_fd	(int fd, int mode, SF_INFO *sfinfo, int close_desc) ;

SNDFILE* 	sf_open_virtual	(SF_VIRTUAL_IO *sfvirtual, int mode, SF_INFO *sfinfo, void *user_data) ;


/* sf_error () returns a error number which can be translated to a text
** string using sf_error_number().
*/

int		sf_error		(SNDFILE *sndfile) ;


/* sf_strerror () returns to the caller a pointer to the current error message for
** the given SNDFILE.
*/

const char* sf_strerror (SNDFILE *sndfile) ;


/* sf_error_number () allows the retrieval of the error string for each internal
** error number.
**
*/

const char*	sf_error_number	(int errnum) ;


/* The following two error functions are deprecated but they will remain in the
** library for the foreseeable future. The function sf_strerror() should be used
** in their place.
*/

int		sf_perror		(SNDFILE *sndfile) ;
int		sf_error_str	(SNDFILE *sndfile, char* str, size_t len) ;


/* Allow the caller to retrieve information from or change aspects of the
** library behaviour.
*/

int		sf_command	(SNDFILE *sndfile, int command, void *data, int datasize) ;


/* Return SF_TRUE if fields of the SF_INFO struct are a valid combination of values,
 * of SF_FALSE if they cannot be used.
** Note this function is logically equivalent to:
**    return (sf_get_format_check_failure_reason(info) == NULL) ? SF_TRUE : SF_FALSE;
*/

int		sf_format_check	(const SF_INFO *info) ;


/* Return NULL if fields of the SF_INFO struct are a valid combination of values,
** or a human-readable explanation-string describing the problem otherwise.
** Note that this function is logically equivalent to sf_format_check(), just with
** a different return-type.
*/

const char *		sf_get_format_check_failure_reason (const SF_INFO *info) ;


/* Seek within the waveform data chunk of the SNDFILE. sf_seek () uses
** the same values for whence (SEEK_SET, SEEK_CUR and SEEK_END) as
** stdio.h function fseek ().
** An offset of zero with whence set to SEEK_SET will position the
** read / write pointer to the first data sample.
** On success sf_seek returns the current position in (multi-channel)
** samples from the start of the file.
** Please see the libsndfile documentation for moving the read pointer
** separately from the write pointer on files open in mode SFM_RDWR.
** On error all of these functions return -1.
*/

enum
{	SF_SEEK_SET = SEEK_SET,
	SF_SEEK_CUR = SEEK_CUR,
	SF_SEEK_END = SEEK_END
} ;

sf_count_t	sf_seek 		(SNDFILE *sndfile, sf_count_t frames, int whence) ;


/* Functions for retrieving and setting string data within sound files.
** Not all file types support this features; AIFF and WAV do. For both
** functions, the str_type parameter must be one of the SF_STR_* values
** defined above.
** On error, sf_set_string() returns non-zero while sf_get_string()
** returns NULL.
*/

int sf_set_string (SNDFILE *sndfile, int str_type, const char* str) ;

const char* sf_get_string (SNDFILE *sndfile, int str_type) ;


/* Return the library version string. */

const char * sf_version_string (void) ;

/* Return the current byterate at this point in the file. The byte rate in this
** case is the number of bytes per second of audio data. For instance, for a
** stereo, 18 bit PCM encoded file with an 16kHz sample rate, the byte rate
** would be 2 (stereo) * 2 (two bytes per sample) * 16000 => 64000 bytes/sec.
** For some file formats the returned value will be accurate and exact, for some
** it will be a close approximation, for some it will be the average bitrate for
** the whole file and for some it will be a time varying value that was accurate
** when the file was most recently read or written.
** To get the bitrate, multiple this value by 8.
** Returns -1 for unknown.
*/
int sf_current_byterate (SNDFILE *sndfile) ;

/* Functions for reading/writing the waveform data of a sound file.
*/

sf_count_t	sf_read_raw		(SNDFILE *sndfile, void *ptr, sf_count_t bytes) ;
sf_count_t	sf_write_raw 	(SNDFILE *sndfile, const void *ptr, sf_count_t bytes) ;


/* Functions for reading and writing the data chunk in terms of frames.
** The number of items actually read/written = frames * number of channels.
**     sf_xxxx_raw		read/writes the raw data bytes from/to the file
**     sf_xxxx_short	passes data in the native short format
**     sf_xxxx_int		passes data in the native int format
**     sf_xxxx_float	passes data in the native float format
**     sf_xxxx_double	passes data in the native double format
** All of these read/write function return number of frames read/written.
*/

sf_count_t	sf_readf_short	(SNDFILE *sndfile, short *ptr, sf_count_t frames) ;
sf_count_t	sf_writef_short	(SNDFILE *sndfile, const short *ptr, sf_count_t frames) ;

sf_count_t	sf_readf_int	(SNDFILE *sndfile, int *ptr, sf_count_t frames) ;
sf_count_t	sf_writef_int 	(SNDFILE *sndfile, const int *ptr, sf_count_t frames) ;

sf_count_t	sf_readf_float	(SNDFILE *sndfile, float *ptr, sf_count_t frames) ;
sf_count_t	sf_writef_float	(SNDFILE *sndfile, const float *ptr, sf_count_t frames) ;

sf_count_t	sf_readf_double		(SNDFILE *sndfile, double *ptr, sf_count_t frames) ;
sf_count_t	sf_writef_double	(SNDFILE *sndfile, const double *ptr, sf_count_t frames) ;


/* Functions for reading and writing the data chunk in terms of items.
** Otherwise similar to above.
** All of these read/write function return number of items read/written.
*/

sf_count_t	sf_read_short	(SNDFILE *sndfile, short *ptr, sf_count_t items) ;
sf_count_t	sf_write_short	(SNDFILE *sndfile, const short *ptr, sf_count_t items) ;

sf_count_t	sf_read_int		(SNDFILE *sndfile, int *ptr, sf_count_t items) ;
sf_count_t	sf_write_int 	(SNDFILE *sndfile, const int *ptr, sf_count_t items) ;

sf_count_t	sf_read_float	(SNDFILE *sndfile, float *ptr, sf_count_t items) ;
sf_count_t	sf_write_float	(SNDFILE *sndfile, const float *ptr, sf_count_t items) ;

sf_count_t	sf_read_double	(SNDFILE *sndfile, double *ptr, sf_count_t items) ;
sf_count_t	sf_write_double	(SNDFILE *sndfile, const double *ptr, sf_count_t items) ;


/* Close the SNDFILE and clean up all memory allocations associated with this
** file.
** Returns 0 on success, or an error number.
*/

int		sf_close		(SNDFILE *sndfile) ;


/* If the file is opened SFM_WRITE or SFM_RDWR, call fsync() on the file
** to force the writing of data to disk. If the file is opened SFM_READ
** no action is taken.
*/

void	sf_write_sync	(SNDFILE *sndfile) ;



/* The function sf_wchar_open() is Windows Only!
** Open a file passing in a Windows Unicode filename. Otherwise, this is
** the same as sf_open().
*/

#ifdef _WIN32
SNDFILE* sf_wchar_open (const wchar_t *wpath, int mode, SF_INFO *sfinfo) ;
#endif




/* Getting and setting of chunks from within a sound file.
**
** These functions allow the getting and setting of chunks within a sound file
** (for those formats which allow it).
**
** These functions fail safely. Specifically, they will not allow you to overwrite
** existing chunks or add extra versions of format specific reserved chunks but
** should allow you to retrieve any and all chunks (may not be implemented for
** all chunks or all file formats).
*/

struct SF_CHUNK_INFO
{	char		id [64] ;	/* The chunk identifier. */
	unsigned	id_size ;	/* The size of the chunk identifier. */
	unsigned	datalen ;	/* The size of that data. */
	void		*data ;		/* Pointer to the data. */
} ;

typedef struct SF_CHUNK_INFO SF_CHUNK_INFO ;

/* Set the specified chunk info (must be done before any audio data is written
** to the file). This will fail for format specific reserved chunks.
** The chunk_info->data pointer must be valid until the file is closed.
** Returns SF_ERR_NO_ERROR on success or non-zero on failure.
*/
int sf_set_chunk (SNDFILE * sndfile, const SF_CHUNK_INFO * chunk_info) ;

/*
** An opaque structure to an iterator over the all chunks of a given id
*/
typedef	struct SF_CHUNK_ITERATOR SF_CHUNK_ITERATOR ;

/* Get an iterator for all chunks matching chunk_info.
** The iterator will point to the first chunk matching chunk_info.
** Chunks are matching, if (chunk_info->id) matches the first
**     (chunk_info->id_size) bytes of a chunk found in the SNDFILE* handle.
** If chunk_info is NULL, an iterator to all chunks in the SNDFILE* handle
**     is returned.
** The values of chunk_info->datalen and chunk_info->data are ignored.
** If no matching chunks are found in the sndfile, NULL is returned.
** The returned iterator will stay valid until one of the following occurs:
**     a) The sndfile is closed.
**     b) A new chunk is added using sf_set_chunk().
**     c) Another chunk iterator function is called on the same SNDFILE* handle
**        that causes the iterator to be modified.
** The memory for the iterator belongs to the SNDFILE* handle and is freed when
** sf_close() is called.
*/
SF_CHUNK_ITERATOR *
sf_get_chunk_iterator (SNDFILE * sndfile, const SF_CHUNK_INFO * chunk_info) ;

/* Iterate through chunks by incrementing the iterator.
** Increments the iterator and returns a handle to the new one.
** After this call, iterator will no longer be valid, and you must use the
**      newly returned handle from now on.
** The returned handle can be used to access the next chunk matching
**      the criteria as defined in sf_get_chunk_iterator().
** If iterator points to the last chunk, this will free all resources
**      associated with iterator and return NULL.
** The returned iterator will stay valid until sf_get_chunk_iterator_next
**      is called again, the sndfile is closed or a new chunk us added.
*/
SF_CHUNK_ITERATOR *
sf_next_chunk_iterator (SF_CHUNK_ITERATOR * iterator) ;


/* Get the size of the specified chunk.
** If the specified chunk exists, the size will be returned in the
**      datalen field of the SF_CHUNK_INFO struct.
**      Additionally, the id of the chunk will be copied to the id
**      field of the SF_CHUNK_INFO struct and it's id_size field will
**      be updated accordingly.
** If the chunk doesn't exist chunk_info->datalen will be zero, and the
**      id and id_size fields will be undefined.
** The function will return SF_ERR_NO_ERROR on success or non-zero on
** failure.
*/
int
sf_get_chunk_size (const SF_CHUNK_ITERATOR * it, SF_CHUNK_INFO * chunk_info) ;

/* Get the specified chunk data.
** If the specified chunk exists, up to chunk_info->datalen bytes of
**      the chunk data will be copied into the chunk_info->data buffer
**      (allocated by the caller) and the chunk_info->datalen field
**      updated to reflect the size of the data. The id and id_size
**      field will be updated according to the retrieved chunk
** If the chunk doesn't exist chunk_info->datalen will be zero, and the
**      id and id_size fields will be undefined.
** The function will return SF_ERR_NO_ERROR on success or non-zero on
** failure.
*/
int
sf_get_chunk_data (const SF_CHUNK_ITERATOR * it, SF_CHUNK_INFO * chunk_info) ;


#ifdef __cplusplus
}		/* extern "C" */
#endif	/* __cplusplus */

#endif	/* SNDFILE_H */
