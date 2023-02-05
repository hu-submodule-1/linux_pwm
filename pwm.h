/**
 * @file      : pwm.h
 * @brief     : Linux平台PWM驱动头文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-01-18 13:49:21
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-01-18 huenrong        创建文件
 *
 */

#ifndef __PWM_H
#define __PWM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief  导出PWM到用户空间
 * @param  pwm_chip: 输入参数, 待导出的pwm组
 * @return true : 成功
 * @return false: 失败
 */
bool pwm_export(const uint16_t pwm_chip);

/**
 * @brief  取消导出PWM到用户空间
 * @param  pwm_chip: 输入参数, 待取消导出的pwm组
 * @return true : 成功
 * @return false: 失败
 */
bool pwm_unexport(const uint16_t pwm_chip);

/**
 * @brief  使能PWM
 * @param  pwm_chip: 输入参数, 待使能的pwm组
 * @return true : 成功
 * @return false: 失败
 */
bool pwm_enable(const uint16_t pwm_chip);

/**
 * @brief  设置PWM周期
 * @param  pwm_chip: 输入参数, 待设置的pwm组
 * @param  period  : 输入参数, 待设置的PWM周期值(单位: ns)
 * @return true : 成功
 * @return false: 失败
 */
bool pwm_set_period(const uint16_t pwm_chip, const uint32_t period);

/**
 * @brief  设置PWM占空比
 * @param  pwm_chip  : 输入参数, 待设置的pwm组
 * @param  duty_cycle: 输入参数, 待设置的PWM占空比(设置高电平的时间, 单位: ns)
 * @return true : 成功
 * @return false: 失败
 */
bool pwm_set_duty_cycle(const uint16_t pwm_chip, const uint32_t duty_cycle);

#ifdef __cplusplus
}
#endif

#endif // __PWM_H
