#ifndef NEUROMAG2MNE_FIELDTRIPTYPES_HPP
#define NEUROMAG2MNE_FIELDTRIPTYPES_HPP

#include <stdint.h>
#include <string>

#define VERSION    static_cast<int32_t>(0x0001)

#define PUT_HDR    static_cast<int32_t>(0x0101) /* decimal 257 */
#define PUT_DAT    static_cast<int32_t>(0x0102) /* decimal 258 */
#define PUT_EVT    static_cast<int32_t>(0x0103) /* decimal 259 */
#define PUT_OK     static_cast<int32_t>(0x0104) /* decimal 260 */
#define PUT_ERR    static_cast<int32_t>(0x0105) /* decimal 261 */

#define GET_HDR    static_cast<int32_t>(0x0201) /* decimal 513 */
#define GET_DAT    static_cast<int32_t>(0x0202) /* decimal 514 */
#define GET_EVT    static_cast<int32_t>(0x0203) /* decimal 515 */
#define GET_OK     static_cast<int32_t>(0x0204) /* decimal 516 */
#define GET_ERR    static_cast<int32_t>(0x0205) /* decimal 517 */

#define WAIT_DAT   static_cast<int32_t>(0x0402) /* decimal 1026 */
#define WAIT_OK    static_cast<int32_t>(0x0404) /* decimal 1027 */
#define WAIT_ERR   static_cast<int32_t>(0x0405) /* decimal 1028 */

#define PUT_HDR_NORESPONSE static_cast<int32_t>(0x0501) /* decimal 1281 */
#define PUT_DAT_NORESPONSE static_cast<int32_t>(0x0502) /* decimal 1282 */
#define PUT_EVT_NORESPONSE static_cast<int32_t>(0x0503) /* decimal 1283 */

//----------------------------------------------------
// Fieldtrip protocol types
//----------------------------------------------------
struct datadef_t{
  int32_t nchans;
  int32_t nsamples;
  int32_t data_type;
  int32_t bufsize;     /* size of the buffer in bytes */
};

struct headerdef_t{
  int32_t  nchans;
  int32_t  nsamples;
  int32_t  nevents;
  float   fsample;
  int32_t  data_type;
  int32_t  bufsize;     /* size of the buffer in bytes */
};

struct header_t{
  headerdef_t *def;
  void        *buf;
};

struct messagedef_t{
  int16_t version;   /* see VERSION */
  int16_t command;   /* see PUT_xxx, GET_xxx and FLUSH_xxx */
  int32_t bufsize;   /* size of the buffer in bytes */
};

struct message_t{
  messagedef_t *def;
  void         *buf;
};

struct datasel_t{
  int32_t begsample; /* indexing starts with 0, should be >=0 */
  int32_t endsample; /* indexing starts with 0, should be <header.nsamples */
};

struct samples_events_t{
  int32_t nsamples;
  int32_t nevents;
};

//----------------------------------------------------
// Convenient types
//----------------------------------------------------

namespace fieldtrip {
struct HeaderChunk {
  std::string filePath;
};

struct BufferParameters {

  BufferParameters(int channels, float frequency, int type)
  : nChannels(channels)
  , sampleFrequency(frequency)
  , dataType(type) {};

  int nChannels;
  float sampleFrequency;
  int dataType;
};
}

#endif //NEUROMAG2MNE_FIELDTRIPTYPES_HPP
