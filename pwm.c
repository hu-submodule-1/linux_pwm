/**
 * @file      : pwm.c
 * @brief     : Linux平台PWM驱动源文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-01-18 13:48:41
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-01-18 huenrong        创建文件
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "./pwm.h"

// pwm路径
#define SYS_PWM_DIR "/sys/class/pwm"

// 命令buf最大长度
#define CMD_BUF_MAX_LEN 60

/**
 * @brief  导出PWM到用户空间
 * @param  pwm_chip: 输入参数, 待导出的pwm组
 * @return true : 成功
 * @return false: 失败
 */
bool pwm_export(const uint16_t pwm_chip)
{
    int ret = -1;
    int fd = -1;
    int len = 0;
    char cmd_buf[CMD_BUF_MAX_LEN] = {0};

    // pwm已经导出, 直接返回成功
    memset(cmd_buf, 0, sizeof(cmd_buf));
    snprintf(cmd_buf, sizeof(cmd_buf), "%s/pwmchip%d/pwm0", SYS_PWM_DIR, pwm_chip);
    ret = access(cmd_buf, F_OK);
    if (0 == ret)
    {
        return true;
    }

    // 打开文件: /sys/class/pwm/pwmchipx/export
    memset(cmd_buf, 0, sizeof(cmd_buf));
    snprintf(cmd_buf, sizeof(cmd_buf), "%s/pwmchip%d/export", SYS_PWM_DIR, pwm_chip);
    fd = open(cmd_buf, O_WRONLY);
    if (fd < 0)
    {
        return false;
    }

    // export文件写入信息(固定写0)
    memset(cmd_buf, 0, sizeof(cmd_buf));
    len = snprintf(cmd_buf, sizeof(cmd_buf), "%d", 0);
    ret = write(fd, cmd_buf, len);
    if (-1 == ret)
    {
        close(fd);

        return false;
    }

    // 关闭文件
    ret = close(fd);
    if (-1 == ret)
    {
        return false;
    }

    return true;
}

/**
 * @brief  取消导出PWM到用户空间
 * @param  pwm_chip: 输入参数, 待取消导出的pwm组
 * @return true : 成功
 * @return false: 失败
 */
bool pwm_unexport(const uint16_t pwm_chip)
{
    int ret = -1;
    int fd = -1;
    int len = 0;
    char cmd_buf[CMD_BUF_MAX_LEN] = {0};

    // pwm未导出, 直接返回成功
    memset(cmd_buf, 0, sizeof(cmd_buf));
    snprintf(cmd_buf, sizeof(cmd_buf), "%s/pwmchip%d/pwm0", SYS_PWM_DIR, pwm_chip);
    ret = access(cmd_buf, F_OK);
    if (0 != ret)
    {
        return true;
    }

    // 打开文件: /sys/class/pwm/pwmchipx/unexport
    memset(cmd_buf, 0, sizeof(cmd_buf));
    snprintf(cmd_buf, sizeof(cmd_buf), "%s/pwmchip%d/unexport", SYS_PWM_DIR, pwm_chip);
    fd = open(cmd_buf, O_WRONLY);
    if (fd < 0)
    {
        return false;
    }

    // unexport文件写入信息(固定写0)
    memset(cmd_buf, 0, sizeof(cmd_buf));
    len = snprintf(cmd_buf, sizeof(cmd_buf), "%d", 0);
    ret = write(fd, cmd_buf, len);
    if (-1 == ret)
    {
        close(fd);

        return false;
    }

    // 关闭文件
    ret = close(fd);
    if (-1 == ret)
    {
        return false;
    }

    return true;
}

/**
 * @brief  使能PWM
 * @param  pwm_chip: 输入参数, 待使能的pwm组
 * @return true : 成功
 * @return false: 失败
 */
bool pwm_enable(const uint16_t pwm_chip)
{
    int ret = -1;
    int fd = -1;
    int len = 0;
    char cmd_buf[CMD_BUF_MAX_LEN] = {0};

    // pwm未导出, 直接返回失败
    memset(cmd_buf, 0, sizeof(cmd_buf));
    snprintf(cmd_buf, sizeof(cmd_buf), "%s/pwmchip%d/pwm0", SYS_PWM_DIR, pwm_chip);
    ret = access(cmd_buf, F_OK);
    if (0 != ret)
    {
        return false;
    }

    // 打开文件: /sys/class/pwm/pwmchipx/pwm0/enable
    memset(cmd_buf, 0, sizeof(cmd_buf));
    snprintf(cmd_buf, sizeof(cmd_buf), "%s/pwmchip%d/pwm0/enable", SYS_PWM_DIR, pwm_chip);
    fd = open(cmd_buf, O_WRONLY);
    if (fd < 0)
    {
        return false;
    }

    // 使能pwm
    memset(cmd_buf, 0, sizeof(cmd_buf));
    len = snprintf(cmd_buf, sizeof(cmd_buf), "%d", 1);
    ret = write(fd, cmd_buf, len);
    if (-1 == ret)
    {
        close(fd);

        return false;
    }

    // 关闭文件
    ret = close(fd);
    if (-1 == ret)
    {
        return false;
    }

    return true;
}

/**
 * @brief  设置PWM周期
 * @param  pwm_chip: 输入参数, 待设置的pwm组
 * @param  period  : 输入参数, 待设置的PWM周期值(单位: ns)
 * @return true : 成功
 * @return false: 失败
 */
bool pwm_set_period(const uint16_t pwm_chip, const uint32_t period)
{
    int ret = -1;
    int fd = -1;
    int len = 0;
    char cmd_buf[CMD_BUF_MAX_LEN] = {0};

    // pwm未导出, 直接返回失败
    memset(cmd_buf, 0, sizeof(cmd_buf));
    snprintf(cmd_buf, sizeof(cmd_buf), "%s/pwmchip%d/pwm0", SYS_PWM_DIR, pwm_chip);
    ret = access(cmd_buf, F_OK);
    if (0 != ret)
    {
        return false;
    }

    // 打开文件: /sys/class/pwm/pwmchipx/pwm0/period
    memset(cmd_buf, 0, sizeof(cmd_buf));
    snprintf(cmd_buf, sizeof(cmd_buf), "%s/pwmchip%d/pwm0/period", SYS_PWM_DIR, pwm_chip);
    fd = open(cmd_buf, O_WRONLY);
    if (fd < 0)
    {
        return false;
    }

    // 设置周期
    memset(cmd_buf, 0, sizeof(cmd_buf));
    len = snprintf(cmd_buf, sizeof(cmd_buf), "%d", period);
    ret = write(fd, cmd_buf, len);
    if (-1 == ret)
    {
        close(fd);

        return false;
    }

    // 关闭文件
    ret = close(fd);
    if (-1 == ret)
    {
        return false;
    }

    return true;
}

/**
 * @brief  设置PWM占空比
 * @param  pwm_chip  : 输入参数, 待设置的pwm组
 * @param  duty_cycle: 输入参数, 待设置的PWM占空比(设置高电平的时间, 单位: ns)
 * @return true : 成功
 * @return false: 失败
 */
bool pwm_set_duty_cycle(const uint16_t pwm_chip, const uint32_t duty_cycle)
{
    int ret = -1;
    int fd = -1;
    int len = 0;
    char cmd_buf[CMD_BUF_MAX_LEN] = {0};

    // pwm未导出, 直接返回失败
    memset(cmd_buf, 0, sizeof(cmd_buf));
    snprintf(cmd_buf, sizeof(cmd_buf), "%s/pwmchip%d/pwm0", SYS_PWM_DIR, pwm_chip);
    ret = access(cmd_buf, F_OK);
    if (0 != ret)
    {
        return false;
    }

    // 打开文件: /sys/class/pwm/pwmchipx/pwm0/duty_cycle
    memset(cmd_buf, 0, sizeof(cmd_buf));
    snprintf(cmd_buf, sizeof(cmd_buf), "%s/pwmchip%d/pwm0/duty_cycle", SYS_PWM_DIR, pwm_chip);
    fd = open(cmd_buf, O_WRONLY);
    if (fd < 0)
    {
        return false;
    }

    // 设置占空比
    memset(cmd_buf, 0, sizeof(cmd_buf));
    len = snprintf(cmd_buf, sizeof(cmd_buf), "%d", duty_cycle);
    ret = write(fd, cmd_buf, len);
    if (-1 == ret)
    {
        close(fd);

        return false;
    }

    // 关闭文件
    ret = close(fd);
    if (-1 == ret)
    {
        return false;
    }

    return true;
}
