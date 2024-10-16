###############################################
#
#  file: uart.py
#  update: 2024-08-27
#  usage: 
#      sudo python uart.py
#
###############################################

from periphery import Serial

uart_dev = "/dev/ttyS3"

def main():

    try:
        
        # 申请串口资源/dev/ttyS3，设置串口波特率为115200，数据位为8，无校验位，停止位为1，不使用流控制
        serial = Serial(
            uart_dev,
            baudrate=115200,
            databits=8,
            parity="none",
            stopbits=1,
            xonxoff=False,
            rtscts=False,
        )
        # 使用申请的串口发送字节流数据 "python-periphery!\n"
        serial.write(b"python-periphery!\n")

        # 读取串口接收的数据，该函数返回条件二者满足其一，一、读取到128个字节，二、读取时间超过5秒
        buf = serial.read(128, 5)

        # 注：Python读取出来的数据类型为：bytes
        # 打印原始数据
        print("接收到的原始数据:\n", buf)

        # 转码为gbk字符串，可以显示中文
        data_strings = buf.decode("gbk")

        # 打印读取的数据量及数据内容
        print("接收到 {:d} 个字节，以字符串形式打印:\n {:s}".format(len(buf), data_strings))

    except Exception as e:
        
        print("exit...：", e)
    
    finally:

        # 释放申请的串口资源
        serial.close()
        
if __name__ == "__main__":  
    main()