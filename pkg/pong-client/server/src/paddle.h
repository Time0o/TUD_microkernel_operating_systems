#pragma once

#include <l4/keyboard-drv/keyboard_drv.h>

#include <l4/sys/capability>
#include <l4/sys/irq>
#include <l4/sys/types.h>

#include <mutex>
#include <ostream>
#include <string>
#include <thread>

class Paddle
{
enum {
  Paddle_start_pos = 0,
  Paddle_min_pos = 0,
  Paddle_max_pos = 1023,
  Paddle_speed = 10,
  Paddle_initial_lifes = 5,
  Paddle_move_timeout = 10
};

public:
  enum direction {
    Direction_none,
    Direction_up,
    Direction_down
  };

  Paddle(l4_cap_idx_t paddle_cap_idx) : _paddle_cap_idx(paddle_cap_idx) {}

  void move(direction dir);

private:
  void _move();

  l4_cap_idx_t _paddle_cap_idx;

  direction _dir = Direction_none;
  std::mutex _dir_mutex;

  std::thread _move_thread;
  int _current_pos = Paddle_start_pos;
  bool _moving = false;
};
