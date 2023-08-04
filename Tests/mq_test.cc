#include "mq.h"

#include <gtest/gtest.h>

#include <string>

#include "sli.h"

TEST(MQ, INIT_DYNAMIC_1) {
  // Test with none null.
  mq_t mq;
  EXPECT_EQ(SLI_ERR, mq_create(&mq, NULL, 0));
}

TEST(MQ, INIT_DYNAMIC_2) {
  // Test with null object.
  mq_t *mq = NULL;
  EXPECT_EQ(SLI_ERR, mq_create(mq, NULL, 0));
  EXPECT_EQ(SLI_ERR, mq_create(mq, NULL, 1));

  EXPECT_EQ(SLI_ERR, mq_create(NULL, NULL, 0));
  EXPECT_EQ(SLI_ERR, mq_create(NULL, NULL, 1));
}

TEST(MQ, INIT_DYNAMIC_3) {
  // Test with valid space.
  mq_t mq;
  const uint32_t space = 9876;
  EXPECT_EQ(SLI_OK, mq_create(&mq, NULL, space));
  EXPECT_EQ(space, mq.n);
  EXPECT_EQ(0, mq.head);
  EXPECT_EQ(0, mq.tail);

  ASSERT_NO_FATAL_FAILURE(free(mq.msg));
}

TEST(MQ, INIT_STATIC_1) {
  // Test with invalid size.
  mq_t mq;
  uint32_t msg[1];
  EXPECT_EQ(SLI_ERR, mq_create(&mq, msg, 0));
}

TEST(MQ, INIT_STATIC_2) {
  // Test with size but invalid mq object.
  uint32_t msg[1];
  EXPECT_EQ(SLI_ERR, mq_create(NULL, msg, 1));
}

TEST(MQ, INIT_STATIC_3) {
  // Test with valid space.
  mq_t mq;
  const uint32_t space = 9876;
  uint32_t msg[space];
  EXPECT_EQ(SLI_OK, mq_create(&mq, msg, space));
  EXPECT_EQ(space, mq.n);
  EXPECT_EQ(0, mq.head);
  EXPECT_EQ(0, mq.tail);
  EXPECT_EQ(msg, mq.msg);
}

TEST(MQ, SEND_1) {
  // Test with null mq object.
  EXPECT_EQ(SLI_ERR, mq_send(NULL, 1234));
}

TEST(MQ, SEND_2) {
  // Test with valid mq object and send message normally.
  mq_t mq;
  const uint32_t space = 1;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;
  err = mq_send(&mq, 1234);
  EXPECT_EQ(SLI_OK, err);
  EXPECT_EQ(1234, msg[0]);
  EXPECT_EQ(0, mq.head);
  EXPECT_EQ(0, mq.tail);
}

TEST(MQ, SEND_3) {
  // Test with valid mq object and send message normally.
  mq_t mq;
  const uint32_t space = 2;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;
  err = mq_send(&mq, 1234);
  EXPECT_EQ(SLI_OK, err);
  EXPECT_EQ(1234, msg[0]);
  EXPECT_EQ(0, mq.head);
  EXPECT_EQ(1, mq.tail);
}

TEST(MQ, SEND_4) {
  // Test with valid mq object and send message normally.
  mq_t mq;
  const uint32_t space = 9876;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;
  for (uint32_t i = 0; i < space; ++i) {
    err = mq_send(&mq, 1234);
    EXPECT_EQ(SLI_OK, err);
  }
  EXPECT_EQ(0, mq.head);
  EXPECT_EQ(0, mq.tail);
}

TEST(MQ, SEND_5) {
  // Test with valid mq object and send message normally.
  mq_t mq;
  const uint32_t space = 10000;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;
  for (uint32_t i = 0; i < space; ++i) {
    err = mq_send(&mq, i);
    EXPECT_EQ(SLI_OK, err);
  }
  EXPECT_EQ(0, mq.head);
  EXPECT_EQ(0, mq.tail);
}

TEST(MQ, SEND_6) {
  // Test with valid mq object but messages are more than size.
  mq_t mq;
  const uint32_t space = 1;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  err = mq_send(&mq, 0);
  EXPECT_EQ(SLI_OK, err);
  err = mq_send(&mq, 0);
  EXPECT_EQ(SLI_ERR, err);
}

TEST(MQ, SEND_7) {
  // Test with valid mq object but messages are more than size.
  mq_t mq;
  const uint32_t space = 3;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  err = mq_send(&mq, 0);
  EXPECT_EQ(SLI_OK, err);
  err = mq_send(&mq, 0);
  EXPECT_EQ(SLI_OK, err);
  err = mq_send(&mq, 0);
  EXPECT_EQ(SLI_OK, err);
  err = mq_send(&mq, 0);
  EXPECT_EQ(SLI_ERR, err);
}

TEST(MQ, RECV_1) {
  // Test with null mq object.
  uint32_t msg;
  ASSERT_NO_FATAL_FAILURE(mq_receive(NULL, &msg));
  EXPECT_EQ(SLI_ERR, mq_receive(NULL, &msg));
}

TEST(MQ, RECV_2) {
  // Test with null message.
  mq_t mq;
  EXPECT_EQ(SLI_ERR, mq_receive(&mq, NULL));
}

TEST(MQ, RECV_3) {
  // Test with both null message and mq.
  EXPECT_EQ(SLI_ERR, mq_receive(NULL, NULL));
}

TEST(MQ, RECV_4) {
  mq_t mq;
  const uint32_t space = 3;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  err = mq_send(&mq, 0);
  EXPECT_EQ(SLI_OK, err);

  uint32_t recv = 1;
  err = mq_receive(&mq, &recv);
  EXPECT_EQ(SLI_OK, err);
  EXPECT_EQ(0, recv);
}

TEST(MQ, RECV_5) {
  mq_t mq;
  const uint32_t space = 100;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  for (uint32_t i = 0; i < space; ++i) {
    err = mq_send(&mq, i);
    EXPECT_EQ(SLI_OK, err);
  }

  for (uint32_t i = 0; i < space; ++i) {
    uint32_t recv = 0;
    err = mq_receive(&mq, &recv);
    EXPECT_EQ(SLI_OK, err);
    EXPECT_EQ(i, recv);
  }
}

TEST(MQ, SEND_RECV_1) {
  mq_t mq;
  const uint32_t space = 100;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  for (uint32_t _ = 0; _ < 5; ++_) {
    for (uint32_t i = 0; i < 30; ++i) {
      err = mq_send(&mq, i);
      EXPECT_EQ(SLI_OK, err);
    }

    for (uint32_t i = 0; i < 30; ++i) {
      uint32_t recv = 0;
      err = mq_receive(&mq, &recv);
      EXPECT_EQ(SLI_OK, err);
      EXPECT_EQ(i, recv);
    }
  }
}

TEST(MQ, SEND_RECV_2) {
  mq_t mq;
  const uint32_t space = 100;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  for (uint32_t i = 0; i < space * 5; ++i) {
    err = mq_send(&mq, i);
    EXPECT_EQ(SLI_OK, err);

    uint32_t recv = 0;
    err = mq_receive(&mq, &recv);
    EXPECT_EQ(SLI_OK, err);
    EXPECT_EQ(i, recv);
  }
}

TEST(MQ, SEND_RECV_3) {
  mq_t mq;
  const uint32_t space = 1;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  for (uint32_t i = 0; i < 100; ++i) {
    err = mq_send(&mq, i);
    EXPECT_EQ(SLI_OK, err);

    uint32_t recv = 0;
    err = mq_receive(&mq, &recv);
    EXPECT_EQ(SLI_OK, err);
    EXPECT_EQ(i, recv);
  }
}

TEST(MQ, CLEAR_1) {
  mq_t mq;
  const uint32_t space = 10;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  uint32_t recv = 0;
  err = mq_receive(&mq, &recv);
  EXPECT_EQ(SLI_ERR, err);

  err = mq_clear(&mq);
  EXPECT_EQ(SLI_OK, err);
  err = mq_receive(&mq, &recv);
  EXPECT_EQ(SLI_ERR, err);
}

TEST(MQ, CLEAR_2) {
  mq_t mq;
  const uint32_t space = 10;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  err = mq_send(&mq, 10);
  EXPECT_EQ(SLI_OK, err);

  uint32_t recv = 0;
  err = mq_receive(&mq, &recv);
  EXPECT_EQ(SLI_OK, err);
  EXPECT_EQ(10, recv);

  err = mq_send(&mq, 10);
  EXPECT_EQ(SLI_OK, err);
  err = mq_clear(&mq);
  EXPECT_EQ(SLI_OK, err);
  err = mq_receive(&mq, &recv);
  EXPECT_EQ(SLI_ERR, err);
}

TEST(MQ, PEEK_1) {
  mq_t mq;
  const uint32_t space = 10;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  uint32_t recv = 0;
  err = mq_peek(&mq, &recv);
  EXPECT_EQ(SLI_ERR, err);
}

TEST(MQ, PEEK_2) {
  mq_t mq;
  const uint32_t space = 10;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  err = mq_send(&mq, 10);
  EXPECT_EQ(SLI_OK, err);

  uint32_t recv = 0;
  err = mq_peek(&mq, &recv);
  EXPECT_EQ(SLI_OK, err);
  EXPECT_EQ(10, recv);
}

TEST(MQ, PEEK_3) {
  mq_t mq;
  const uint32_t space = 10;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  err = mq_send(&mq, 10);
  EXPECT_EQ(SLI_OK, err);

  for (uint32_t i = 0; i < space; ++i) {
    uint32_t recv = 0;
    err = mq_peek(&mq, &recv);
    EXPECT_EQ(SLI_OK, err);
    EXPECT_EQ(10, recv);
  }
}

TEST(MQ, PEEK_4) {
  mq_t mq;
  const uint32_t space = 10;
  uint32_t msg[space];
  mq_create(&mq, msg, space);
  sli_err err;

  for (uint32_t i = 0; i < space; ++i) {
    err = mq_send(&mq, i);
    EXPECT_EQ(SLI_OK, err);
  }

  for (uint32_t i = 0; i < space; ++i) {
    uint32_t recv = 0;
    err = mq_peek(&mq, &recv);
    EXPECT_EQ(SLI_OK, err);
    EXPECT_EQ(0, recv);
  }
}
