'''
@ author: Antonio1111111111
@ date:   Mar, 27, 2025
@ 代码说明： 本代码是我们的K210的正式代码，包含YOLO识别部分以及串口通信。
@ 修改日志：参照新标准修改原来握手逻辑与通信逻辑
'''

import sensor, image, time, lcd, gc, cmath
from maix import KPU
from hiwonder import hw_uart
from hiwonder import hw_led , fill_light
import time

lcd.init()                          # Init lcd display
lcd.clear(lcd.BLUE)                  # Clear lcd screen.

# sensor.reset(dual_buff=True)      # improve fps
sensor.reset()                      # Reset and initialize the sensor.
sensor.set_pixformat(sensor.RGB565) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
#sensor.set_vflip(True)              # 翻转摄像头
#sensor.set_hmirror(True)            # 镜像摄像头
sensor.skip_frames(time = 1000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.

print("ready load model")

kpu = KPU()
# 从sd或flash加载模型
kpu.load_kmodel('/sd/cls.kmodel')
#kpu.load_kmodel(0x300000, MODEL_SIZE)
# 创建hiwonder的串口对象
serial = hw_uart()
f_led = fill_light()
bt = serial.rec_bytes()
labels = ["ELE_V_L", "ELE_V_R", "ELE_V_O", "ELE_V_F", "ELE_V_B"] #类名称，按照label.txt顺序填写


img256256 = image.Image(size=(256,256))

while(True):
    gc.collect()

    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.

    img256240 = img.copy((32, 0, 256, 240))
    a = img256256.draw_image(img256240,0,8)
    del img256240

    img128128 = img256256.resize(128,128)
    img128128.pix_to_ai()

    result = kpu.run_with_output(img128128, getlist=True)
    del img128128
    print('1')

    fps = clock.fps()

    result = kpu.softmax(result)

    print(result)
    _max_val = max(result)
    print('3')
    _max_idx = result.index(_max_val)

    print(labels[_max_idx], _max_val)
    print(labels[_max_idx])
    if bt == 'ELE_V_START':
        try:
            # 串口发送数据
            serial.send_bytearray(bytearray("ELE_V_STARTED"))
            serial.send_bytearray(bytearray(labels[_max_idx], 'utf-8'))

        except Exception as e:
            print("Serial communication error:", e)


    elif bt == 'ELE_V_END':
        try:
            # 串口发送数据
            serial.send_bytearray(bytearray("ELE_V_ENDED"))


        except Exception as e:
            print("Serial communication error:", e)

    img.draw_string(32, 0, labels[_max_idx] + " %.3f"%_max_val,0xFFFF,2.0)
    img.draw_rectangle(32,0,256,240)
    a = img.draw_string(0, 240 - 32, "%2.1ffps" %(fps),color=(0,60,255),scale=2.0)
    lcd.display(img)
