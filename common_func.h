#ifndef COMMOM_FUNC_H
#define COMMOM_FUNC_H

#include <QString>
#include <QtGlobal>
#include <iostream>

#define EXCEED_PULSE 6553500
#define MAX_PULSE 4294967296

using namespace std;

qint64 pulse_sub_ret(unsigned int first_c, unsigned int second_c);

bool pulse_first_bigger_than_second(unsigned int first_c, unsigned int second_c);

qint64 pulse_move(qint64 first_c, qint64 second_c);

QString get_bmp_filename(int _id);

void setFlawDrawParam(float max_mm, float min_mm, int max_pixel, int min_pixel);

int calcDrawWidth(float width_mm);

typedef struct _ipv4 {
    unsigned char ipaddr_v4[4];
} ipv4_addr;

typedef struct my_mac_addr {
    unsigned char addr[6];
} mac_addr;

bool convert_ip_string_to_struct(string _ip_str, ipv4_addr& _ip_struct);

void convert_mac_string_to_struct(QString _mac_str, mac_addr& _mac_struct);

QString convert_mac_struct_to_string(mac_addr _addr);

QString convert_ip_struct_to_string(ipv4_addr _addr);

#endif // COMMOM_FUNC_H
