#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <cstdint>

/* Congestion controller interface */

class Controller {
   private:
    bool debug_;                   /* Enables debugging output */
    int64_t window_size_ = 1;      /* Window size */
    uint64_t acked_in_window_ = 0; /* Number of packets ack'ed in this window */
    uint64_t timeout_loss_ms_ = 1000; /* Timeout */
    uint64_t avg_rtt_ = 0;            /* Average measured RTT */
    uint64_t alpha_ = 0.9;            /* Weighting parameter */
    uint64_t rtt_thresh_ms_ = 80;     /* Threshold delay of 300ms */
    int64_t last_error_ = 0; /* Used to calculate the D part in the PID */
    int64_t integral_ = 0;

   public:
    /* Public interface for the congestion controller */

    /* Default constructor */
    Controller(const bool debug);

    /* Get current window size, in datagrams */
    unsigned int window_size(void);

    /* To be called when a timeout occurs. */
    void timeout_callback();

    /* A datagram was sent */
    void datagram_was_sent(const uint64_t sequence_number,
                           const uint64_t send_timestamp);

    /* An ack was received */
    void ack_received(const uint64_t sequence_number_acked,
                      const uint64_t send_timestamp_acked,
                      const uint64_t recv_timestamp_acked,
                      const uint64_t timestamp_ack_received);

    /* How long to wait (in milliseconds) if there are no acks
       before sending one more datagram */
    unsigned int timeout_ms(void);
};

#endif
