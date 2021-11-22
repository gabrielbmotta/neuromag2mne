#ifndef NEUROMAG2MNE_FIFFDEFINES_HPP
#define NEUROMAG2MNE_FIFFDEFINES_HPP

// Acquisition Tags

#define FIFF_NEW_FILE             1
#define FIFF_CLOSE_FILE           2
#define FIFF_DISCARD_FILE         3
#define FIFF_ERROR_MESSAGE        4
#define FIFF_SUSPEND_READING      5
#define FIFF_FATAL_ERROR_MESSAGE  6
#define FIFF_CONNECTION_CHECK     7
#define FIFF_SUSPEND_FILING       8
#define FIFF_RESUME_FILING        9
#define FIFF_RAW_PREBASE          10
#define FIFF_RAW_PICK_LIST        11
#define FIFF_ECHO                 12
#define FIFF_RESUME_READING       13
#define FIFF_DACQ_SYSTEM_TYPE     14
#define FIFF_SELECT_RAW_CH        15
#define FIFF_PLAYBACK_MODE        16
#define FIFF_CONTINUE_FILE        17
#define FIFF_JITTER_MAX           18
#define FIFF_STREAM_SEGMENT       19
// File Tags
#define FIFF_FILE_ID              100
#define FIFF_DIR_POINTER          101
#define FIFF_DIR                  102
#define FIFF_BLOCK_ID             103
#define FIFF_BLOCK_START          104
#define FIFF_BLOCK_END            105

// Common Tags
#define FIFF_NCHAN                200
#define FIFF_SFREQ                201
#define FIFF_DATA_PACK            202
#define FIFF_CH_INFO              203
#define FIFF_MEAS_DATE            204
#define FIFF_SUBJECT              205
#define FIFF_COMMENT              206
#define FIFF_NAVE                 207
#define FIFF_FIRST_SAMPLE         208
#define FIFF_LAST_SAMPLE          209
#define FIFF_ASPECT_KIND          210
#define FIFF_REF_EVENT            211
#define FIFF_EXPERIMENTER         212
#define FIFF_DIG_POINT            213
#define FIFF_CH_POS_VEC           214
#define FIFF_HPI_SLOPES           215
#define FIFF_HPI_NCOIL            216
#define FIFF_REQ_EVENT            217
#define FIFF_REQ_LIMIT            218
#define FIFF_LOWPASS              219
#define FIFF_BAD_CHS              220
#define FIFF_ARTEF_REMOVAL        221
#define FIFF_COORD_TRANS          222
#define FIFF_HIGHPASS             223
#define FIFF_CH_CALS_VEC          224
#define FIFF_HPI_BAD_CHS          225
#define FIFF_HPI_CORR_COEFF       226
#define FIFF_EVENT_COMMENT        227
#define FIFF_NO_SAMPLES           228
#define FIFF_FIRST_TIME           229
#define FIFF_SUBAVE_SIZE          230
#define FIFF_SUBAVE_FIRST         231
#define FIFF_NAME                 233
#define FIFF_DESCRIPTION          206
#define FIFF_DIG_STRING           234

#define FIFF_LINE_FREQ            235
#define FIFF_HPI_COIL_FREQ        236
#define FIFF_SIGNAL_CHANNEL       237

#define FIFFC_HPI_MAX_NCOIL       1000

// Block Types
#define FIFFB_ROOT                999
#define FIFFB_MEAS                100
#define FIFFB_MEAS_INFO           101
#define FIFFB_RAW_DATA            102
#define FIFFB_PROCESSED_DATA      103
#define FIFFB_EVOKED              104

#endif //NEUROMAG2MNE_FIFFDEFINES_HPP
