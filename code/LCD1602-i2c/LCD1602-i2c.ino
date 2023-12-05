#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 设置LCD地址，可以通过I2C扫描工具查找
#define LCD_ADDRESS 0x27

// 设置LCD列数和行数
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// 创建LiquidCrystal_I2C对象
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  // 初始化LCD
  lcd.begin();

  // 打印"Hello World"到LCD
  lcd.print("Hello");
}

void loop() {
  // 在loop中可以添加其他代码
}
