#pragma once

#include <armadillo>

#include <hop>

class ParallelKinematicMachine_3PRRR_IntersectionBased : public hop::ParallelKinematicMachine {
  public:
    explicit ParallelKinematicMachine_3PRRR_IntersectionBased();
    explicit ParallelKinematicMachine_3PRRR_IntersectionBased(const arma::Mat<double>::fixed<2, 3>& relativeEndEffectorJoints, const arma::Mat<double>::fixed<2, 3>& linkLengths, const arma::Mat<double>::fixed<2, 3>& redundantJointStarts, const arma::Mat<double>::fixed<2, 3>& redundantJointEnds);

    arma::Mat<double> getJacobian(const arma::Col<double>& endEffectorPose, const arma::Col<double>& redundantActuationParameters) const override;

  protected:
    arma::Mat<double>::fixed<2, 3> endEffectorJointsRelative_;
    arma::Mat<double>::fixed<2, 3> linkLengths_;

    arma::Mat<double>::fixed<2, 3> redundantJointStarts_;
    arma::Mat<double>::fixed<2, 3> redundantJointEnds_;
    arma::Mat<double>::fixed<2, 3> redundantJointsStartToEnd_;
    arma::Col<arma::uword> redundantJointIndicies_;
    arma::Col<double> redundantJointAnglesSine_;
    arma::Col<double> redundantJointAnglesCosine_;
};
