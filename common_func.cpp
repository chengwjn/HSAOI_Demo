#include "common_func.h"
#include <QObject>
#include <QString>
#include <QtCore>

static float flaw_max_mm = 0;
static float flaw_min_mm = 0;
static float mm_per_pixel = 0;
static int flaw_max_pixel = 0;
static int flaw_min_pixel = 0;

void setFlawDrawParam(float max_mm, float min_mm, int max_pixel,
    int min_pixel)
{
    flaw_max_mm = max_mm;
    flaw_min_mm = min_mm;
    flaw_max_pixel = max_pixel;
    flaw_min_pixel = min_pixel;
    mm_per_pixel = (flaw_max_mm - flaw_min_mm) / (flaw_max_pixel - flaw_min_pixel);
}

int calcDrawWidth(float width_mm)
{
    if (width_mm < flaw_min_mm)
        return flaw_min_pixel;
    else if (width_mm >= flaw_min_mm && width_mm <= flaw_max_mm) {
        int out_pixel = 0;
        out_pixel = (width_mm - flaw_min_mm) / mm_per_pixel + flaw_min_pixel;
        return out_pixel;
    } else
        return flaw_max_pixel;
}

qint64 pulse_sub_ret(unsigned int first_c, unsigned int second_c)
{
    qint64 ret = (qint64(first_c) - qint64(second_c));
    if ((ret) < -EXCEED_PULSE)
        ret = (ret + MAX_PULSE) % MAX_PULSE;
    else if (ret > EXCEED_PULSE)
        ret = ret - MAX_PULSE;
    return ret;
}

unsigned int pulse_sub_move(unsigned int first_c, unsigned int second_c)
{
    qint64 ret = qint64(first_c) - qint64(second_c);
    if (ret < 0)
        ret = (ret + MAX_PULSE) % MAX_PULSE;
    return ret;
}

bool pulse_first_bigger_than_second(unsigned int first_c,
    unsigned int second_c)
{
    bool ret = false;
    if (first_c == second_c)
        return true;

    if (first_c > second_c) {
        if ((first_c - second_c) > EXCEED_PULSE) {
            ret = false;
        } else {
            ret = true;
        }
    } else {
        if ((second_c - first_c) > EXCEED_PULSE) {
            ret = true;
        } else {
            ret = false;
        }
    }
    return ret;
}

qint64 pulse_move(qint64 first_c, qint64 second_c)
{
    qint64 ret = (first_c) + (second_c);
    if (ret >= MAX_PULSE)
        ret = ret % MAX_PULSE;
    else if (ret < 0)
        ret = (ret + MAX_PULSE) % MAX_PULSE;
    return ret;
}

QString get_bmp_filename(int _id)
{
    QString filepath;
    filepath.sprintf("flaw_temp\\%05d_flaw", _id);
    return filepath;
}

bool convert_ip_string_to_struct(string _ip_str, ipv4_addr& _ip_struct)
{
    int _position = 0;
    int _position_start = 0;

    unsigned int t_count = 0;
    _position = _ip_str.find(".", _position_start);
    while (_position != std::string::npos) {
        if (t_count < 3) {
            string str = _ip_str.substr(_position_start, _position - _position_start);
            QString qstr(str.c_str());
            _ip_struct.ipaddr_v4[t_count] = qstr.toInt();
            //_ip_struct.ipaddr_v4[t_count] = atoi(const_cast<char*>(str.c_str()));
            if (t_count == 2) {
                string t_str = _ip_str.substr(_position + 1, _ip_str.size());
                QString qstr(t_str.c_str());
                _ip_struct.ipaddr_v4[t_count] = qstr.toInt();
                //_ip_struct.ipaddr_v4[t_count+1] =
                //atoi(const_cast<char*>(str.c_str()));
            }
        }
        _position_start = _position + 1;
        _position = _ip_str.find(".", _position_start);
        t_count++;
    }
    if (t_count == 3)
        return true;
    else
        return false;
}

void convert_mac_string_to_struct(QString _mac_str, mac_addr& _mac_struct)
{
    int _count = 0;
    int position = 0;
    bool is_ok;
    while (_count < 6) {
        if (_count < 5) {
            position = _mac_str.indexOf("-", 0);
            QString tmp = _mac_str.left(position);
            _mac_struct.addr[_count] = tmp.toInt(&is_ok, 16);
            _mac_str = _mac_str.right(_mac_str.length() - position - 1);
        } else {

            QString tmp = _mac_str.right(_mac_str.length() - position - 1);
            _mac_struct.addr[_count] = tmp.toInt(&is_ok, 16);
        }
        _count++;
    }
}

QString convert_ip_struct_to_string(ipv4_addr ip_addr)
{
    QString str = QString("%1.%2.%3.%4")
                      .arg(ip_addr.ipaddr_v4[0])
                      .arg(ip_addr.ipaddr_v4[1])
                      .arg(ip_addr.ipaddr_v4[2])
                      .arg(ip_addr.ipaddr_v4[3]);
    return str;
}

QString convert_mac_struct_to_string(mac_addr _addr)
{
    QString str = QString("%1-%2-%3-%4-%5-%6")
                      .arg(_addr.addr[0], 2, 16, QLatin1Char('0'))
                      .arg(_addr.addr[1], 2, 16, QLatin1Char(QLatin1Char('0')))
                      .arg(_addr.addr[2], 2, 16, QLatin1Char('0'))
                      .arg(_addr.addr[3], 2, 16, QLatin1Char('0'))
                      .arg(_addr.addr[4], 2, 16, QLatin1Char('0'))
                      .arg(_addr.addr[5], 2, 16, QLatin1Char('0'));
    return str;
}
