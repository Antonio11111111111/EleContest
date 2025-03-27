'''
@ author: Antonio1111111111
@ date:   Mar, 27, 2025
@ 代码说明： 本代码是我们的K210的正式代码，包含YOLO识别部分以及串口通信。
@ 调试说明： 由于本套板子资料不是很全，我们就从115200的波特率开始试验吧😂
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
sensor.set_vflip(True)              # 翻转摄像头
sensor.set_hmirror(True)            # 镜像摄像头
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

labels = ["r","l","o","f","b"] #类名称，按照label.txt顺序填写

img256256 = image.Image(size=(256,256))
bt = 'n'
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
    #print(result)

    fps = clock.fps()

    result = kpu.softmax(result)
    #print(result)

    _max_val = max(result)
    _max_idx = result.index(_max_val)

    print(labels[_max_idx], _max_val)

    # 识别后串口发送程序
    sbuf = [labels[_max_idx]]
    serial.send_bytearray(sbuf)
    bt = serial.rec_bytes()
    # uart的各种状态显示
    if bt == 's': # succeed for uart of K210
        f_led.fill_onoff(0) #补光灯关
        time.sleep(0.5)  #延时0.5s
        f_led.fill_onoff(1) #补光灯开
        time.sleep(0.5)  #延时0.5s
    if bt == 'n':  # not succeed for uart of K210
        f_led.fill_onoff(1) #补光灯开
    if bt == 'h': # hands 握手成功
        f_led.fill_onoff(0) #补光灯关
        
    img.draw_string(32, 0, labels[_max_idx] + " %.3f"%_max_val,0xFFFF,2.0)
    img.draw_rectangle(32,0,256,240)
    a = img.draw_string(0, 240 - 32, "%2.1ffps" %(fps),color=(0,60,255),scale=2.0)
    lcd.display(img)

