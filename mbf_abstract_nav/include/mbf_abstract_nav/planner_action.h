/*
 *  Copyright 2018, Magazino GmbH, Sebastian Pütz, Jorge Santos Simón
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 *  3. Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *  planner_action.h
 *
 *  authors:
 *    Sebastian Pütz <spuetz@uni-osnabrueck.de>
 *    Jorge Santos Simón <santos@magazino.eu>
 *
 */

#ifndef MBF_ABSTRACT_NAV__PLANNER_ACTION_H_
#define MBF_ABSTRACT_NAV__PLANNER_ACTION_H_

#include "mbf_abstract_nav/abstract_action.h"
#include "mbf_abstract_nav/abstract_planner_execution.h"
#include "mbf_abstract_nav/robot_information.h"
#include <actionlib/server/action_server.h>
#include <mbf_msgs/GetPathAction.h>

namespace mbf_abstract_nav{


class PlannerAction : public AbstractAction<mbf_msgs::GetPathAction, AbstractPlannerExecution>
{
 public:

  typedef boost::shared_ptr<PlannerAction> Ptr;

  PlannerAction(
      const ros::NodeHandle& nh, const ros::NodeHandle& nhp,
      const std::string& name,
      const RobotInformation &robot_info
  );

  void run(GoalHandle &goal_handle, AbstractPlannerExecution &execution);

 protected:

  /**
   * @brief Publishes the given path / plan
   * @param plan The plan, a list of stamped poses, to be published
   */
  void publishPath(std::vector<geometry_msgs::PoseStamped> &plan);

  /**
   * @brief Transforms a pose to the global frame (global_frame_) coord system.
   * @param pose Input pose to be transformed.
   * @param global_pose Output pose, which is then transformed to the global frame.
   * @return true, if the transformation succeeded, false otherwise
   */
  bool transformPoseToGlobalFrame(
      const geometry_msgs::PoseStamped &pose, geometry_msgs::PoseStamped &global_pose);

  /**
   * @brief Transforms a plan to the global frame (global_frame_) coord system.
   * @param plan Input plan to be transformed.
   * @param global_plan Output plan, which is then transformed to the global frame.
   * @return true, if the transformation succeeded, false otherwise
   */
  bool transformPlanToGlobalFrame(std::vector<geometry_msgs::PoseStamped> &plan,
                                  std::vector<geometry_msgs::PoseStamped> &global_plan);


 private:

  //! Publisher to publish the current goal pose, which is used for path planning
  ros::Publisher current_goal_pub_;

  //! Publisher to publish the current computed path
  ros::Publisher path_pub_;

  //! Path sequence counter
  unsigned int path_seq_count_;
};


}


#endif //MBF_ABSTRACT_NAV__PLANNER_ACTION_H_
