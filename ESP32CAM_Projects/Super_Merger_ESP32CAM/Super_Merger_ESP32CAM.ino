/*********
  Rui Santos + Custom Merge by Varun
  Webserver + SD card photo saving
*********/

#include "WiFi.h"
#include "esp_camera.h"
#include "Arduino.h"
#include "soc/soc.h"           // Disable brownout detector
#include "soc/rtc_cntl_reg.h"
#include "driver/rtc_io.h"
#include <ESPAsyncWebServer.h>
#include "SD_MMC.h"
#include <EEPROM.h>

#define EEPROM_SIZE 1

// WiFi Credentials
const char* ssid = "Varun S's S23 FE";
const char* password = "vsp@5311";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
boolean takeNewPhoto = false;

// OV2640 camera module pins (AI THINKER)
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// Webpage HTML
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { text-align:center; font-family: Arial; }
    .vert { margin-bottom: 10%; }
    .hori{ margin-bottom: 0%; }
    button { margin: 10px; padding: 10px 20px; }
  </style>
</head>
<body>
  <div id="container">
    <h2>ESP32-CAM Last SD Photo</h2>
    <p><button onclick="rotatePhoto();">ROTATE</button>
    <button onclick="capturePhoto()">CAPTURE PHOTO</button>
    <button onclick="location.reload();">REFRESH PAGE</button></p>
  </div>
  <div><img src="latest-photo" id="photo" width="70%"></div>
</body>
<script>
  var deg = 0;
  function capturePhoto() {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', "/capture", true);
    xhr.send();
  }
  function rotatePhoto() {
    var img = document.getElementById("photo");
    deg += 90;
    if(isOdd(deg/90)){ document.getElementById("container").className = "vert"; }
    else{ document.getElementById("container").className = "hori"; }
    img.style.transform = "rotate(" + deg + "deg)";
  }
  function isOdd(n) { return Math.abs(n % 2) == 1; }
</script>
</html>)rawliteral";

// Latest photo path
String latestPhotoPath = "/picture0.jpg";

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Disable brownout

  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP Address: http://");
  Serial.println(WiFi.localIP());

  // Init SD Card
  if (!SD_MMC.begin()) {
    Serial.println("SD Card Mount Failed");
    return;
  }
  if (SD_MMC.cardType() == CARD_NONE) {
    Serial.println("No SD Card attached");
    return;
  }
  Serial.println("SD Card ready");

  // Init camera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("Camera init failed");
    return;
  }

  // Web routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", index_html);
  });

  server.on("/capture", HTTP_GET, [](AsyncWebServerRequest *request){
    takeNewPhoto = true;
    request->send(200, "text/plain", "Taking photo...");
  });

  server.on("/latest-photo", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD_MMC, latestPhotoPath.c_str(), "image/jpg", false);
  });

  server.begin();
}

void loop() {
  if (takeNewPhoto) {
    capturePhotoToSD();
    takeNewPhoto = false;
  }
}

// Take photo and save to SD with incremented filename
void capturePhotoToSD() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  int picNum = EEPROM.read(0);
  latestPhotoPath = "/picture" + String(picNum) + ".jpg";

  File file = SD_MMC.open(latestPhotoPath.c_str(), FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    esp_camera_fb_return(fb);
    return;
  }

  file.write(fb->buf, fb->len);
  file.close();
  Serial.println("Photo saved to SD: " + latestPhotoPath);

  // Update EEPROM
  EEPROM.write(0, (picNum + 1) % 256); // Wrap after 255
  EEPROM.commit();

  esp_camera_fb_return(fb);
}
