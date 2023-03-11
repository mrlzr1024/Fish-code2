/* 
 * SimpleKalmanFilter - a Kalman Filter implementation for single variable models.
 * Created by Denys Sene, January, 1, 2017.
 * Released under MIT License - see LICENSE file for details.
 */

#include "Arduino.h"
#include "SimpleKalmanFilter.h"
#include <math.h>

SimpleKalmanFilter::SimpleKalmanFilter(float 观测值_误差, float 初始_误差_估计值, float 过程方差)
{
  仪器误差=观测值_误差;
  _误差_估计值=初始_误差_估计值;
  _过程方差 = 过程方差;
}

float SimpleKalmanFilter::update估计值(float 观测值)
{
  _卡尔曼增益 = _误差_估计值/(_误差_估计值 + 仪器误差);
  _现在的_估计值 = _上一次_估计值 + _卡尔曼增益 * (观测值 - _上一次_估计值);
  _误差_估计值 =  (1.0 - _卡尔曼增益)*_误差_估计值 + fabs(_上一次_估计值-_现在的_估计值)*_过程方差;
  _上一次_估计值=_现在的_估计值;

  return _现在的_估计值;
}

void SimpleKalmanFilter::设置测量值ment误差or(float 观测值_误差)
{
  仪器误差=观测值_误差;
}

void SimpleKalmanFilter::设置估计值误差or(float 初始_误差_估计值)
{
  _误差_估计值=初始_误差_估计值;
}

void SimpleKalmanFilter::设置过程噪声(float 过程方差)
{
  _过程方差=过程方差;
}

float SimpleKalmanFilter::get卡尔曼增益() {
  return _卡尔曼增益;
}

