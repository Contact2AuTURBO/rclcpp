// Copyright 2018 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RCLCPP__WAITABLE_HPP_
#define RCLCPP__WAITABLE_HPP_

#include "rclcpp/macros.hpp"
#include "rclcpp/visibility_control.hpp"

#include "rcl/wait.h"

namespace rclcpp
{

class Waitable
{
public:
  RCLCPP_SMART_PTR_DEFINITIONS_NOT_COPYABLE(Waitable)

  /// Get the number of ready subscriptions
  RCLCPP_PUBLIC
  virtual
  size_t
  get_number_of_ready_subscriptions() = 0;

  /// Get the number of ready timers
  RCLCPP_PUBLIC
  virtual
  size_t
  get_number_of_ready_timers() = 0;

  /// Get the number of ready clients
  RCLCPP_PUBLIC
  virtual
  size_t
  get_number_of_ready_clients() = 0;

  /// Get the number of ready services
  RCLCPP_PUBLIC
  virtual
  size_t
  get_number_of_ready_services() = 0;

  /// Get the number of ready guard_conditions
  RCLCPP_PUBLIC
  virtual
  size_t
  get_number_of_ready_guard_conditions() = 0;

  // TODO(jacobperron): smart pointer?
  /// Add the Waitable to a wait set.
  /**
   * \param[in] wait_set A handle to the wait set to add the Waitable to.
   * \return `true` if the Waitable is added successfully, `false` otherwise.
   */
  RCLCPP_PUBLIC
  virtual
  bool
  add_to_wait_set(rcl_wait_set_t * wait_set) = 0;

  /// Update the entities in the Waitable based on a wait set.
  /**
   * The input wait set should be the same that was used in a previously call to
   * `add_to_wait_set()`.
   * The wait set should also have been previously waited on with `rcl_wait()`.
   *
   * \param[in] wait_set A handle to the wait set the Waitable was previously added to
   *   and that has been waited on.
   */
  RCLCPP_PUBLIC
  virtual
  void
  update(rcl_wait_set_t *) = 0;

  /// Execute any entities of the Waitable that are ready.
  /**
   * Before calling this method, the Waitable should be added to a wait set,
   * waited on, and then updated.
   *
   * Example usage:
   *
   * ```
   * // ... create a wait set and a Waitable
   * // Add the Waitable to the wait set
   * bool add_ret = waitable.add_to_wait_set(wait_set);
   * // ... error handling
   * // Wait
   * rcl_ret_t wait_ret = rcl_wait(wait_set);
   * // ... error handling
   * // Update the Waitable
   * waitable.update(wait_set);
   * // Execute any entities of the Waitable that may be ready
   * waitable.execute();
   * ```
   */
  RCLCPP_PUBLIC
  virtual
  void
  execute() = 0;
};  // class Waitable

}  // namespace rclcpp

#endif  // RCLCPP__WAITABLE_HPP_
