#ifndef NEUROMAG2MNE_FIFFDEFINES_HPP
#define NEUROMAG2MNE_FIFFDEFINES_HPP

#include <stdint.h>

// Acquisition Tags
#define FIFF_NEW_FILE                   1
#define FIFF_CLOSE_FILE                 2
#define FIFF_DISCARD_FILE               3
#define FIFF_ERROR_MESSAGE              4
#define FIFF_SUSPEND_READING            5
#define FIFF_FATAL_ERROR_MESSAGE        6
#define FIFF_CONNECTION_CHECK           7
#define FIFF_SUSPEND_FILING             8
#define FIFF_RESUME_FILING              9
#define FIFF_RAW_PREBASE                10
#define FIFF_RAW_PICK_LIST              11
#define FIFF_ECHO                       12
#define FIFF_RESUME_READING             13
#define FIFF_DACQ_SYSTEM_TYPE           14
#define FIFF_SELECT_RAW_CH              15
#define FIFF_PLAYBACK_MODE              16
#define FIFF_CONTINUE_FILE              17
#define FIFF_JITTER_MAX                 18
#define FIFF_STREAM_SEGMENT             19

// File Tags
#define FIFF_FILE_ID                    100
#define FIFF_DIR_POINTER                101
#define FIFF_DIR                        102
#define FIFF_BLOCK_ID                   103
#define FIFF_BLOCK_START                104
#define FIFF_BLOCK_END                  105

// Common Tags
#define FIFF_NCHAN                      200
#define FIFF_SFREQ                      201
#define FIFF_DATA_PACK                  202
#define FIFF_CH_INFO                    203
#define FIFF_MEAS_DATE                  204
#define FIFF_SUBJECT                    205
#define FIFF_COMMENT                    206
#define FIFF_NAVE                       207
#define FIFF_FIRST_SAMPLE               208
#define FIFF_LAST_SAMPLE                209
#define FIFF_ASPECT_KIND                210
#define FIFF_REF_EVENT                  211
#define FIFF_EXPERIMENTER               212
#define FIFF_DIG_POINT                  213
#define FIFF_CH_POS_VEC                 214
#define FIFF_HPI_SLOPES                 215
#define FIFF_HPI_NCOIL                  216
#define FIFF_REQ_EVENT                  217
#define FIFF_REQ_LIMIT                  218
#define FIFF_LOWPASS                    219
#define FIFF_BAD_CHS                    220
#define FIFF_ARTEF_REMOVAL              221
#define FIFF_COORD_TRANS                222
#define FIFF_HIGHPASS                   223
#define FIFF_CH_CALS_VEC                224
#define FIFF_HPI_BAD_CHS                225
#define FIFF_HPI_CORR_COEFF             226
#define FIFF_EVENT_COMMENT              227
#define FIFF_NO_SAMPLES                 228
#define FIFF_FIRST_TIME                 229
#define FIFF_SUBAVE_SIZE                230
#define FIFF_SUBAVE_FIRST               231
#define FIFF_NAME                       233
#define FIFF_DESCRIPTION                206
#define FIFF_DIG_STRING                 234

#define FIFF_LINE_FREQ                  235
#define FIFF_HPI_COIL_FREQ              236
#define FIFF_SIGNAL_CHANNEL             237

#define FIFFC_HPI_MAX_NCOIL             1000

#define FIFF_MNE_PROJ_ITEM_ACTIVE       3560       /**< Is this projection item active?*/

// Block Types
#define FIFFB_ROOT                      999
#define FIFFB_MEAS                      100
#define FIFFB_MEAS_INFO                 101
#define FIFFB_RAW_DATA                  102
#define FIFFB_PROCESSED_DATA            103
#define FIFFB_EVOKED                    104

// Data Types
#define FIFFT_VOID                      0
#define FIFFT_BYTE                      1
#define FIFFT_SHORT                     2
#define FIFFT_INT                       3
#define FIFFT_FLOAT                     4
#define FIFFT_DOUBLE                    5
#define FIFFT_JULIAN                    6
#define FIFFT_USHORT                    7
#define FIFFT_UINT                      8
#define FIFFT_ULONG                     9
#define FIFFT_STRING                    10
#define FIFFT_ASCII                     10
#define FIFFT_LONG                      11
#define FIFFT_DAU_PACK13                13
#define FIFFT_DAU_PACK14                14
#define FIFFT_DAU_PACK16                16
#define FIFFT_COMPLEX_FLOAT             20
#define FIFFT_COMPLEX_DOUBLE            21
#define FIFFT_OLD_PACK                  23
#define FIFFT_CH_INFO_STRUCT            30
#define FIFFT_ID_STRUCT                 31
#define FIFFT_DIR_ENTRY_STRUCT          32
#define FIFFT_DIG_POINT_STRUCT          33
#define FIFFT_CH_POS_STRUCT             34
#define FIFFT_COORD_TRANS_STRUCT        35
#define FIFFT_DIG_STRING_STRUCT         36
#define FIFFT_STREAM_SEGMENT_STRUCT     37
#define FIFFT_DATA_REF_STRUCT           38

// Channel kinds

#define FIFFV_MAGN_CH                   1
#define FIFFV_EL_CH                     2
#define FIFFV_MEG_CH                    FIFFV_MAGN_CH
#define FIFFV_MCG_CH                    201
#define FIFFV_REF_MEG_CH                301    /**< CTF coil and channel type. */
#define FIFFV_EEG_CH                    FIFFV_EL_CH
#define FIFFV_STIM_CH                   3

#define FIFFV_EOG_CH                    202
#define FIFFV_EMG_CH                    302
#define FIFFV_ECG_CH                    402
#define FIFFV_MISC_CH                   502
#define FIFFV_RESP_CH                   602

// Units

#define FIFF_UNIT_HZ                    101
#define FIFF_UNIT_N                     102
#define FIFF_UNIT_PA                    103
#define FIFF_UNIT_J                     104
#define FIFF_UNIT_W                     105
#define FIFF_UNIT_C                     106
#define FIFF_UNIT_V                     107
#define FIFF_UNIT_F                     108
#define FIFF_UNIT_OHM                   109
#define FIFF_UNIT_MHO                   110
#define FIFF_UNIT_WB                    111
#define FIFF_UNIT_T                     112
#define FIFF_UNIT_H                     113
#define FIFF_UNIT_CEL                   114
#define FIFF_UNIT_LM                    115
#define FIFF_UNIT_LX                    116

#define FIFF_UNIT_T_M                   201   /* T/m */
#define FIFF_UNIT_AM                    202   /* Am  */
#define FIFF_UNIT_AM_M2                 203   /* Am/m^2  */
#define FIFF_UNIT_AM_M3                 204   /* Am/m^3  */

// Multipliers
#define FIFF_UNITM_E                    18
#define FIFF_UNITM_PET                  15
#define FIFF_UNITM_T                    12
#define FIFF_UNITM_MEG                  6
#define FIFF_UNITM_K                    3
#define FIFF_UNITM_H                    2
#define FIFF_UNITM_DA                   1
#define FIFF_UNITM_NONE                 0
#define FIFF_UNITM_D                    -1
#define FIFF_UNITM_C                    -2
#define FIFF_UNITM_M                    -3
#define FIFF_UNITM_MU                   -6
#define FIFF_UNITM_N                    -9
#define FIFF_UNITM_P                    -12
#define FIFF_UNITM_F                    -15
#define FIFF_UNITM_A                    -18

// Type Structs
struct ch_info_t{
  int32_t scanNo;       // Position of this channel in scanning order.
  int32_t logNo;        // Logical channel number. These must be unique within channels of the same kind.
  int32_t kind;         // Kind of the channel described (MEG, EEG, EOG, etc.)
  float range;          // The raw data values must be multiplied by this to get into volts at the electronics output.
  float cal;            // Calibration of the channel. If the raw data values are multiplied by range*cal, the result is in units given by unit and unit_mul.
  int32_t coil_type;    // Kind of MEG coil or kind of EEG channel.
  float r0[3];          // Coil coordinate system origin. For EEG electrodes, this is the location of the electrode.
  float ex[3];          // Coil coordinate system unit vector ex. For EEG electrodes, this specifies the location of a reference electrode. Set to (0,0,0) for no reference.
  float ey[3];          // Coil coordinate system unit vector ey. This is ignored for EEG electrodes.
  float ez[3];          // Coil coordinate system unit vector ez . This is ignored for EEG electrodes.
  int32_t unit;         // The real-world unit-of measure.
  int32_t unit_mul;     // The unit multiplier. The result given by range*cal*data is in units unit*10^unit_mul.
}; //size is 80 bytes


#endif //NEUROMAG2MNE_FIFFDEFINES_HPP
