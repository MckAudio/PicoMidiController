clear:
	cmake --build ./build --target clear
	openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program build/clear.elf verify reset exit"

oled:
	cmake --build ./build --target oled
	openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program build/oled.elf verify reset exit"

control:
	cmake --build ./build --target oled_ctrl
	openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program build/oled_ctrl.elf verify reset exit"