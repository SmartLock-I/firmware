#include <mq.h>

sli_err mq_create(mq_t* mq, uint32_t* space, uint32_t size) {
  /* mq object must be null in creation process */
  if (mq != NULL) return SLI_ERR;
  /* mq size must greater than zero */
  if (size == 0) return SLI_ERR;

  if (space == NULL)
    mq->msg = malloc(size * sizeof(uint32_t));
  else
    mq->msg = space;

  mq->n = size;
  mq->head = 0;
  mq->tail = 0;

  return SLI_OK;
}

sli_err mq_send(mq_t* mq, uint32_t msg) {
  /* send msg into mq object */
  if (mq == NULL) return SLI_ERR;
  if (mq->n == 0) return SLI_ERR;
  if ((mq->tail + 1) % mq->n == mq->head) return SLI_ERR;
  mq->msg[mq->tail] = msg;
  mq->tail = (mq->tail + 1) % mq->n;
  return SLI_OK;
}

sli_err mq_receive(mq_t* mq, uint32_t* buffer) {
  if (mq == NULL) return SLI_ERR;
  if (mq->head == mq->tail) return SLI_ERR;
  *buffer = mq->msg[mq->head];
  mq->head = (mq->head + 1) % mq->n;
  return SLI_OK;
}

sli_err mq_peek(mq_t* mq, uint32_t* buffer) {
  /* peek msg from mq object */
  if (mq == NULL) return SLI_ERR;
  if (mq->head == mq->tail) return SLI_ERR;
  *buffer = mq->msg[mq->head];
  return SLI_OK;
}

sli_err mq_clear(mq_t* mq) {
  /* clear mq object */
  if (mq == NULL) return SLI_ERR;
  mq->head = 0;
  mq->tail = 0;
  mq->n = 0;
  return SLI_OK;
}
