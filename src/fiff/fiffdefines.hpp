#ifndef NEUROMAG2MNE_FIFFDEFINES_HPP
#define NEUROMAG2MNE_FIFFDEFINES_HPP


// Tags
#define FIFF_NCHAN            200        /**< Number of channels. */
#define FIFF_SFREQ            201        /**< Sampling frequency (Hz). */
#define FIFF_CH_INFO          203        /**< Channel descriptor. */
#define FIFF_DATA_BUFFER      300        /**< Buffer containing measurement data. */

// Block Tags
#define FIFF_BLOCK_START      104
#define FIFF_BLOCK_END        105

// Block Types
#define FIFFB_RAW_DATA        102

#endif //NEUROMAG2MNE_FIFFDEFINES_HPP
