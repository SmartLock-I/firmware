#ifndef __MQ__
#define __MQ__

#include <bsp.h>
#include <stdint.h>

typedef struct {
  uint32_t n, head, tail;
  uint32_t* msg;
} mq_t;

sli_err mq_create(mq_t* mq, uint32_t* space, uint32_t size);
sli_err mq_send(mq_t* mq, uint32_t msg);
sli_err mq_receive(mq_t* mq, uint32_t* buffer);
sli_err mq_peek(mq_t* mq, uint32_t* buffer);
sli_err mq_clear(mq_t* mq);

#endif
