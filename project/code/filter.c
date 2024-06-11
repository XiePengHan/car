#include "zf_common_headfile.h"

#define Filter_N 5

#define window_size 5            //�������ڳ���
float buffer[window_size] = {0}; //������������buf

float sliding_average_filter(float value)
{
    static int data_num = 0;
    float output = 0;

    if (data_num < window_size) //�������ڣ������
    {
      buffer[data_num++] = value;
      output = value; //������ͬ��ֵ
    }
    else
    {
      int i = 0;
      float sum = 0;

      memcpy(&buffer[0], &buffer[1], (window_size - 1) * 4); //��1֮��������Ƶ�0֮�󣬼��Ƴ�ͷ��
      buffer[window_size - 1] = value;                       //�����β��

      for (i = 0; i < window_size; i++) //ÿһ�ζ����㣬���Ա����ۼƸ���������
        sum += buffer[i];

      output = sum / window_size;
    }

  return output;
}
