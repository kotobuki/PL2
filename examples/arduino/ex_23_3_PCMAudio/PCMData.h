const int SOUNDDATA_LENGTH = 8000;

const unsigned char soundData[] PROGMEM = {
  -128, -94, -63, -40, -28, -27, -39, -62, -92, -127, 94, 63, 40, 27, 26, 37, 
  59, 89, 124, -97, -66, -42, -28, -27, -38, -59, -89, -123, 98, 66, 42, 28, 
  26, 36, 57, 86, 120, -100, -69, -44, -29, -27, -36, -56, -85, -120, 101, 69, 
  44, 29, 25, 34, 54, 83, 117, -104, -71, -46, -30, -26, -35, -54, -82, -116, 
  105, 72, 46, 30, 25, 33, 52, 80, 113, -107, -74, -48, -31, -26, -33, -52, 
  -79, -113, 108, 75, 48, 31, 25, 32, 49, 77, 110, -111, -77, -50, -32, -26, 
  -32, -49, -76, -109, 111, 78, 50, 32, 25, 30, 47, 74, 106, -114, -81, -53, 
  -34, -26, -31, -47, -73, -106, 115, 81, 53, 33, 25, 29, 45, 71, 103, -118, 
  -84, -55, -35, -26, -30, -45, -70, -102, 119, 84, 55, 35, 26, 28, 43, 68, 
  100, -121, -87, -58, -37, -27, -29, -43, -67, -99, 122, 88, 58, 36, 26, 28, 
  41, 65, 96, -125, -90, -60, -38, -27, -28, -41, -64, -95, 126, 91, 61, 38, 
  26, 27, 39, 62, 93, -128, -94, -63, -40, -28, -28, -39, -62, -92, -127, 94, 
  63, 40, 27, 26, 37, 59, 90, 124, -97, -66, -42, -28, -27, -38, -59, -89, 
  -123, 98, 66, 42, 28, 26, 36, 57, 86, 121, -100, -68, -44, -29, -27, -36, 
  -57, -86, -120, 101, 69, 44, 29, 25, 34, 54, 83, 117, -104, -71, -46, -30, 
  -26, -35, -54, -82, -116, 104, 72, 46, 30, 25, 33, 52, 80, 114, -107, -74, 
  -48, -31, -26, -33, -52, -79, -113, 108, 75, 48, 31, 25, 32, 50, 77, 110, 
  -111, -77, -50, -32, -26, -32, -49, -76, -109, 111, 78, 50, 32, 25, 30, 47, 
  74, 107, -114, -80, -53, -34, -26, -31, -47, -73, -106, 115, 81, 53, 33, 25, 
  29, 45, 71, 103, -118, -84, -55, -35, -26, -30, -45, -70, -102, 118, 84, 55, 
  35, 26, 28, 43, 68, 100, -121, -87, -57, -37, -27, -29, -43, -67, -99, 122, 
  87, 58, 36, 26, 28, 41, 65, 96, -125, -90, -60, -38, -27, -28, -41, -65, 
  -96, 125, 91, 60, 38, 26, 27, 39, 62, 93, -128, -93, -63, -40, -28, -28, 
  -39, -62, -92, -127, 94, 63, 40, 27, 26, 38, 60, 90, 124, -97, -65, -42, 
  -28, -27, -38, -59, -89, -124, 97, 66, 42, 28, 26, 36, 57, 86, 121, -100, 
  -68, -44, -29, -27, -36, -57, -86, -120, 101, 69, 44, 29, 25, 34, 54, 83, 
  117, -104, -71, -46, -30, -26, -35, -54, -83, -116, 104, 72, 46, 30, 25, 33, 
  52, 80, 114, -107, -74, -48, -31, -26, -33, -52, -79, -113, 108, 75, 48, 31, 
  25, 32, 50, 77, 110, -110, -77, -50, -32, -26, -32, -49, -76, -109, 111, 78, 
  50, 32, 25, 30, 47, 74, 107, -114, -80, -52, -34, -26, -31, -47, -73, -106, 
  115, 81, 53, 33, 25, 29, 45, 71, 103, -117, -83, -55, -35, -26, -30, -45, 
  -70, -103, 118, 84, 55, 35, 26, 28, 43, 68, 100, -121, -87, -57, -37, -27, 
  -29, -43, -68, -99, 122, 87, 58, 36, 26, 28, 41, 65, 96, -124, -90, -60, 
  -38, -27, -28, -41, -65, -96, 125, 91, 60, 38, 26, 27, 39, 62, 93, -128, 
  -93, -63, -40, -28, -28, -39, -62, -92, -127, 94, 63, 40, 27, 26, 38, 60, 
  90, 124, -97, -65, -42, -28, -27, -38, -59, -89, -124, 97, 66, 42, 28, 26, 
  36, 57, 87, 121, -100, -68, -44, -29, -27, -36, -57, -86, -120, 101, 69, 44, 
  29, 25, 34, 55, 83, 117, -103, -71, -46, -30, -26, -35, -54, -83, -117, 104, 
  72, 46, 30, 25, 33, 52, 80, 114, -107, -74, -48, -31, -26, -33, -52, -80, 
  -113, 108, 75, 48, 31, 25, 32, 50, 77, 110, -110, -77, -50, -32, -26, -32, 
  -50, -77, -110, 111, 78, 50, 32, 25, 31, 47, 74, 107, -114, -80, -52, -34, 
  -26, -31, -47, -73, -106, 115, 81, 53, 33, 25, 29, 45, 71, 103, -117, -83, 
  -55, -35, -26, -30, -45, -71, -103, 118, 84, 55, 35, 26, 28, 43, 68, 100, 
  -121, -87, -57, -36, -27, -29, -43, -68, -99, 122, 87, 58, 36, 26, 28, 41, 
  65, 97, -124, -90, -60, -38, -27, -28, -41, -65, -96, 125, 90, 60, 38, 26, 
  27, 39, 62, 93, -128, -93, -62, -40, -28, -28, -40, -62, -93, -127, 94, 63, 
  40, 27, 26, 38, 60, 90, 125, -96, -65, -42, -28, -27, -38, -59, -89, -124, 
  97, 66, 42, 28, 26, 36, 57, 87, 121, -100, -68, -44, -29, -27, -36, -57, 
  -86, -120, 100, 68, 44, 29, 25, 35, 55, 83, 118, -103, -71, -46, -30, -26, 
  -35, -54, -83, -117, 104, 71, 46, 30, 25, 33, 52, 80, 114, -107, -74, -48, 
  -31, -26, -33, -52, -80, -113, 107, 74, 48, 31, 25, 32, 50, 77, 111, -110, 
  -77, -50, -32, -26, -32, -50, -77, -110, 111, 77, 50, 32, 25, 31, 48, 74, 
  107, -114, -80, -52, -34, -26, -31, -47, -74, -106, 114, 81, 52, 33, 25, 29, 
  45, 71, 104, -117, -83, -55, -35, -26, -30, -45, -71, -103, 118, 84, 55, 35, 
  25, 29, 43, 68, 100, -121, -86, -57, -36, -27, -29, -43, -68, -99, 121, 87, 
  57, 36, 26, 28, 41, 65, 97, -124, -90, -60, -38, -27, -28, -41, -65, -96, 
  125, 90, 60, 38, 26, 27, 40, 63, 93, -128, -93, -62, -40, -28, -28, -40, 
  -62, -93, -128, 94, 63, 40, 27, 26, 38, 60, 90, 125, -96, -65, -42, -28, 
  -27, -38, -60, -89, -124, 97, 65, 41, 28, 26, 36, 57, 87, 121, -100, -68, 
  -43, -29, -27, -36, -57, -86, -120, 100, 68, 43, 29, 25, 35, 55, 84, 118, 
  -103, -71, -45, -30, -26, -35, -55, -83, -117, 104, 71, 46, 30, 25, 33, 52, 
  80, 114, -106, -74, -48, -31, -26, -33, -52, -80, -113, 107, 74, 48, 31, 25, 
  32, 50, 77, 111, -110, -77, -50, -32, -26, -32, -50, -77, -110, 111, 77, 50, 
  32, 25, 31, 48, 74, 107, -113, -80, -52, -33, -26, -31, -48, -74, -106, 114, 
  80, 52, 33, 25, 30, 46, 71, 104, -117, -83, -55, -35, -26, -30, -45, -71, 
  -103, 118, 84, 55, 35, 25, 29, 43, 68, 100, -120, -86, -57, -36, -27, -29, 
  -43, -68, -100, 121, 87, 57, 36, 26, 28, 41, 66, 97, -124, -89, -60, -38, 
  -27, -28, -42, -65, -96, 125, 90, 60, 38, 26, 27, 40, 63, 94, -128, -93, 
  -62, -40, -28, -28, -40, -62, -93, -128, 93, 63, 40, 27, 26, 38, 60, 90, 
  125, -96, -65, -41, -28, -27, -38, -60, -90, -124, 97, 65, 41, 28, 26, 36, 
  57, 87, 121, -99, -68, -43, -29, -27, -36, -57, -86, -121, 100, 68, 43, 29, 
  25, 35, 55, 84, 118, -103, -71, -45, -30, -26, -35, -55, -83, -117, 104, 71, 
  45, 29, 25, 33, 52, 81, 114, -106, -74, -47, -31, -26, -34, -52, -80, -114, 
  107, 74, 48, 31, 25, 32, 50, 77, 111, -110, -77, -50, -32, -26, -32, -50, 
  -77, -110, 111, 77, 50, 32, 25, 31, 48, 74, 107, -113, -80, -52, -33, -26, 
  -31, -48, -74, -107, 114, 80, 52, 33, 25, 30, 46, 71, 104, -117, -83, -54, 
  -35, -26, -30, -46, -71, -103, 118, 83, 55, 34, 25, 29, 44, 68, 100, -120, 
  -86, -57, -36, -27, -29, -44, -68, -100, 121, 87, 57, 36, 26, 28, 42, 66, 
  97, -124, -89, -59, -38, -27, -28, -42, -65, -96, 125, 90, 60, 38, 26, 27, 
  40, 63, 94, -127, -93, -62, -40, -28, -28, -40, -62, -93, -128, 93, 62, 39, 
  27, 26, 38, 60, 90, 125, -96, -65, -41, -28, -27, -38, -60, -90, -124, 97, 
  65, 41, 28, 26, 36, 58, 87, 122, -99, -68, -43, -29, -27, -36, -57, -87, 
  -121, 100, 68, 43, 28, 26, 35, 55, 84, 118, -103, -71, -45, -30, -26, -35, 
  -55, -83, -117, 103, 71, 45, 29, 25, 33, 53, 81, 115, -106, -73, -47, -31, 
  -26, -34, -52, -80, -114, 107, 74, 47, 31, 25, 32, 50, 78, 111, -110, -77, 
  -50, -32, -26, -32, -50, -77, -110, 110, 77, 50, 32, 25, 31, 48, 75, 108, 
  -113, -80, -52, -33, -26, -31, -48, -74, -107, 114, 80, 52, 33, 25, 30, 46, 
  72, 104, -117, -83, -54, -35, -26, -30, -46, -71, -103, 117, 83, 55, 34, 25, 
  29, 44, 69, 101, -120, -86, -57, -36, -27, -29, -44, -68, -100, 121, 87, 57, 
  36, 26, 28, 42, 66, 97, -124, -89, -59, -38, -27, -28, -42, -65, -97, 124, 
  90, 60, 38, 26, 27, 40, 63, 94, -127, -92, -62, -39, -28, -28, -40, -63, 
  -93, -128, 93, 62, 39, 27, 26, 38, 60, 91, 125, -96, -65, -41, -28, -27, 
  -38, -60, -90, -124, 96, 65, 41, 28, 26, 36, 58, 87, 122, -99, -68, -43, 
  -29, -27, -37, -57, -87, -121, 100, 68, 43, 28, 26, 35, 55, 84, 118, -103, 
  -70, -45, -30, -26, -35, -55, -83, -117, 103, 71, 45, 29, 25, 33, 53, 81, 
  115, -106, -73, -47, -31, -26, -34, -52, -80, -114, 107, 74, 47, 30, 25, 32, 
  50, 78, 111, -109, -76, -49, -32, -26, -32, -50, -77, -110, 110, 77, 50, 32, 
  25, 31, 48, 75, 108, -113, -79, -52, -33, -26, -31, -48, -74, -107, 114, 80, 
  52, 33, 25, 30, 46, 72, 104, -116, -83, -54, -35, -26, -30, -46, -71, -103, 
  117, 83, 54, 34, 25, 29, 44, 69, 101, -120, -86, -57, -36, -27, -29, -44, 
  -68, -100, 121, 86, 57, 36, 26, 28, 42, 66, 97, -124, -89, -59, -38, -27, 
  -28, -42, -65, -97, 124, 90, 60, 38, 26, 27, 40, 63, 94, -127, -92, -62, 
  -39, -28, -28, -40, -63, -93, -128, 93, 62, 39, 27, 26, 38, 60, 91, 125, 
  -96, -65, -41, -28, -27, -38, -60, -90, -125, 96, 65, 41, 28, 26, 36, 58, 
  87, 122, -99, -67, -43, -29, -27, -37, -57, -87, -121, 100, 68, 43, 28, 26, 
  35, 55, 84, 118, -102, -70, -45, -30, -26, -35, -55, -84, -118, 103, 71, 45, 
  29, 25, 33, 53, 81, 115, -106, -73, -47, -31, -26, -34, -53, -80, -114, 107, 
  74, 47, 30, 25, 32, 50, 78, 111, -109, -76, -49, -32, -26, -32, -50, -77, 
  -111, 110, 77, 50, 32, 25, 31, 48, 75, 108, -113, -79, -52, -33, -26, -31, 
  -48, -74, -107, 114, 80, 52, 33, 25, 30, 46, 72, 104, -116, -82, -54, -35, 
  -26, -30, -46, -71, -104, 117, 83, 54, 34, 25, 29, 44, 69, 101, -120, -86, 
  -57, -36, -27, -29, -44, -68, -100, 121, 86, 57, 36, 26, 28, 42, 66, 98, 
  -123, -89, -59, -38, -27, -28, -42, -66, -97, 124, 90, 59, 37, 26, 27, 40, 
  63, 94, -127, -92, -62, -39, -28, -28, -40, -63, -94, -128, 93, 62, 39, 27, 
  26, 38, 60, 91, 126, -95, -64, -41, -28, -27, -38, -60, -90, -125, 96, 65, 
  41, 28, 26, 36, 58, 88, 122, -99, -67, -43, -29, -27, -37, -58, -87, -121, 
  100, 68, 43, 28, 26, 35, 55, 84, 119, -102, -70, -45, -30, -26, -35, -55, 
  -84, -118, 103, 71, 45, 29, 25, 33, 53, 81, 115, -106, -73, -47, -31, -26, 
  -34, -53, -81, -114, 106, 74, 47, 30, 25, 32, 50, 78, 111, -109, -76, -49, 
  -32, -26, -32, -50, -77, -111, 110, 77, 49, 32, 25, 31, 48, 75, 108, -113, 
  -79, -52, -33, -26, -31, -48, -74, -107, 113, 80, 52, 33, 25, 30, 46, 72, 
  105, -116, -82, -54, -35, -26, -30, -46, -71, -104, 117, 83, 54, 34, 25, 29, 
  44, 69, 101, -120, -85, -56, -36, -27, -29, -44, -69, -100, 120, 86, 57, 36, 
  26, 28, 42, 66, 98, -123, -89, -59, -38, -27, -28, -42, -66, -97, 124, 89, 
  59, 37, 26, 27, 40, 63, 94, -127, -92, -62, -39, -27, -28, -40, -63, -94, 
  -128, 93, 62, 39, 27, 26, 38, 61, 91, 126, -95, -64, -41, -28, -27, -38, 
  -60, -90, -125, 96, 65, 41, 28, 26, 37, 58, 88, 122, -99, -67, -43, -29, 
  -27, -37, -58, -87, -121, 99, 68, 43, 28, 26, 35, 55, 84, 119, -102, -70, 
  -45, -30, -26, -35, -55, -84, -118, 103, 70, 45, 29, 25, 34, 53, 81, 115, 
  -106, -73, -47, -31, -26, -34, -53, -81, -114, 106, 73, 47, 30, 25, 32, 51, 
  78, 112, -109, -76, -49, -32, -26, -33, -50, -78, -111, 110, 76, 49, 31, 25, 
  31, 48, 75, 108, -112, -79, -51, -33, -26, -31, -48, -75, -107, 113, 80, 52, 
  33, 25, 30, 46, 72, 105, -116, -82, -54, -34, -26, -30, -46, -72, -104, 117, 
  83, 54, 34, 25, 29, 44, 69, 101, -120, -85, -56, -36, -27, -29, -44, -69, 
  -101, 120, 86, 57, 36, 26, 28, 42, 66, 98, -123, -89, -59, -37, -27, -29, 
  -42, -66, -97, 124, 89, 59, 37, 26, 27, 40, 63, 94, -127, -92, -62, -39, 
  -27, -28, -40, -63, -94, 127, 93, 62, 39, 27, 27, 38, 61, 91, 126, -95, 
  -64, -41, -28, -27, -38, -60, -91, -125, 96, 65, 41, 27, 26, 37, 58, 88, 
  122, -99, -67, -43, -29, -27, -37, -58, -87, -122, 99, 67, 43, 28, 26, 35, 
  56, 85, 119, -102, -70, -45, -30, -26, -35, -55, -84, -118, 103, 70, 45, 29, 
  25, 34, 53, 81, 115, -105, -73, -47, -31, -26, -34, -53, -81, -115, 106, 73, 
  47, 30, 25, 32, 51, 78, 112, -109, -76, -49, -32, -26, -33, -51, -78, -111, 
  110, 76, 49, 31, 25, 31, 48, 75, 108, -112, -79, -51, -33, -26, -31, -48, 
  -75, -108, 113, 79, 52, 33, 25, 30, 46, 72, 105, -116, -82, -54, -34, -26, 
  -30, -46, -72, -104, 117, 83, 54, 34, 25, 29, 44, 69, 101, -119, -85, -56, 
  -36, -27, -29, -44, -69, -101, 120, 86, 56, 36, 26, 28, 42, 66, 98, -123, 
  -88, -59, -37, -27, -29, -42, -66, -97, 124, 89, 59, 37, 26, 27, 40, 64, 
  95, -126, -92, -61, -39, -27, -28, -40, -63, -94, 127, 92, 62, 39, 27, 27, 
  38, 61, 91, 126, -95, -64, -41, -28, -27, -39, -61, -91, -125, 96, 64, 41, 
  27, 26, 37, 58, 88, 123, -98, -67, -43, -29, -27, -37, -58, -87, -122, 99, 
  67, 43, 28, 26, 35, 56, 85, 119, -102, -70, -45, -30, -26, -35, -55, -84, 
  -118, 103, 70, 45, 29, 25, 34, 53, 82, 115, -105, -73, -47, -31, -26, -34, 
  -53, -81, -115, 106, 73, 47, 30, 25, 32, 51, 78, 112, -109, -76, -49, -32, 
  -26, -33, -51, -78, -111, 109, 76, 49, 31, 25, 31, 48, 75, 108, -112, -79, 
  -51, -33, -26, -31, -48, -75, -108, 113, 79, 51, 33, 25, 30, 46, 72, 105, 
  -116, -82, -54, -34, -26, -30, -46, -72, -104, 116, 82, 54, 34, 25, 29, 44, 
  69, 102, -119, -85, -56, -36, -27, -29, -44, -69, -101, 120, 86, 56, 36, 26, 
  28, 42, 67, 98, -123, -88, -59, -37, -27, -29, -42, -66, -97, 123, 89, 59, 
  37, 26, 27, 40, 64, 95, -126, -92, -61, -39, -27, -28, -40, -63, -94, 127, 
  92, 62, 39, 27, 27, 38, 61, 91, 126, -95, -64, -41, -28, -27, -39, -61, 
  -91, -125, 96, 64, 41, 27, 26, 37, 58, 88, 123, -98, -67, -43, -29, -27, 
  -37, -58, -88, -122, 99, 67, 43, 28, 26, 35, 56, 85, 119, -102, -70, -45, 
  -30, -26, -35, -56, -84, -118, 102, 70, 45, 29, 25, 34, 53, 82, 116, -105, 
  -73, -47, -31, -26, -34, -53, -81, -115, 106, 73, 47, 30, 25, 32, 51, 79, 
  112, -109, -76, -49, -32, -26, -33, -51, -78, -111, 109, 76, 49, 31, 25, 31, 
  49, 76, 109, -112, -79, -51, -33, -26, -32, -48, -75, -108, 113, 79, 51, 33, 
  25, 30, 46, 73, 105, -116, -82, -54, -34, -26, -30, -46, -72, -104, 116, 82, 
  54, 34, 25, 29, 44, 70, 102, -119, -85, -56, -36, -27, -29, -44, -69, -101, 
  120, 86, 56, 35, 26, 28, 42, 67, 98, -123, -88, -59, -37, -27, -29, -42, 
  -66, -98, 123, 89, 59, 37, 26, 27, 40, 64, 95, -126, -91, -61, -39, -27, 
  -28, -40, -63, -94, 127, 92, 61, 39, 27, 27, 39, 61, 92, 126, -95, -64, 
  -41, -28, -27, -39, -61, -91, -126, 95, 64, 41, 27, 26, 37, 58, 88, 123, 
  -98, -67, -43, -29, -27, -37, -58, -88, -122, 99, 67, 43, 28, 26, 35, 56, 
  85, 119, -101, -69, -45, -30, -26, -35, -56, -84, -119, 102, 70, 45, 29, 25, 
  34, 53, 82, 116, -105, -72, -47, -31, -26, -34, -53, -81, -115, 106, 73, 47, 
  30, 25, 32, 51, 79, 112, -108, -75, -49, -32, -26, -33, -51, -78, -112, 109, 
  76, 49, 31, 25, 31, 49, 76, 109, -112, -78, -51, -33, -26, -32, -49, -75, 
  -108, 113, 79, 51, 33, 25, 30, 46, 73, 105, -115, -82, -53, -34, -26, -30, 
  -46, -72, -105, 116, 82, 54, 34, 25, 29, 44, 70, 102, -119, -85, -56, -36, 
  -26, -30, -44, -69, -101, 120, 85, 56, 35, 26, 28, 42, 67, 98, -122, -88, 
  -58, -37, -27, -29, -42, -66, -98, 123, 89, 59, 37, 26, 27, 40, 64, 95, 
  -126, -91, -61, -39, -27, -28, -41, -64, -94, 127, 92, 61, 39, 27, 27, 39, 
  61, 92, 127, -95, -64, -41, -28, -27, -39, -61, -91, -126, 95, 64, 41, 27, 
  26, 37, 59, 88, 123, -98, -67, -42, -29, -27, -37, -58, -88, -122, 99, 67, 
  42, 28, 26, 35, 56, 85, 119, -101, -69, -44, -30, -26, -36, -56, -85, -119, 
  102, 70, 44, 29, 25, 34, 54, 82, 116, -105, -72, -47, -31, -26, -34, -53, 
  -81, -115, 105, 73, 47, 30, 25, 32, 51, 79, 112, -108, -75, -49, -32, -26, 
  -33, -51, -78, -112, 109, 76, 49, 31, 25, 31, 49, 76, 109, -112, -78, -51, 
  -33, -26, -32, -49, -75, -108, 112, 79, 51, 32, 25, 30, 47, 73, 105, -115, 
  -81, -53, -34, -26, -31, -47, -72, -105, 116, 82, 54, 34, 25, 29, 44, 70, 
  102, -119, -85, -56, -36, -26, -30, -44, -69, -101, 119, 85, 56, 35, 26, 28, 
  42, 67, 99, -122, -88, -58, -37, -27, -29, -42, -67, -98, 123, 88, 59, 37, 
  26, 27, 41, 64, 95, -126, -91, -61, -39, -27, -28, -41, -64, -95, 127, 92, 
  61, 39, 27, 27, 39, 61, 92, 127, -94, -64, -41, -28, -27, -39, -61, -91, 
  -126, 95, 64, 40, 27, 26, 37, 59, 89, 123, -98, -66, -42, -29, -27, -37, 
  -58, -88, -122, 98, 67, 42, 28, 26, 35, 56, 85, 120, -101, -69, -44, -30, 
  -27, -36, -56, -85, -119, 102, 70, 44, 29, 25, 34, 54, 82, 116, -105, -72, 
  -46, -30, -26, -34, -53, -82, -115, 105, 73, 46, 30, 25, 33, 51, 79, 113, 
  -108, -75, -49, -32, -26, -33, -51, -78, -112, 109, 76, 49, 31, 25, 31, 49, 
  76, 109, -112, -78, -51, -33, -26, -32, -49, -75, -108, 112, 79, 51, 32, 25, 
  30, 47, 73, 106, -115, -81, -53, -34, -26, -31, -47, -72, -105, 116, 82, 53, 
  34, 25, 29, 45, 70, 102, -119, -84, -56, -35, -26, -30, -45, -69, -101, 119, 
  85, 56, 35, 26, 28, 43, 67, 99, -122, -88, -58, -37, -27, -29, -43, -67, 
  -98, 123, 88, 58, 37, 26, 27, 41, 64, 95, -126, -91, -61, -39, -27, -28, 
  -41, -64, -95, 126, 92, 61, 39, 27, 27, 39, 61, 92, 127, -94, -63, -40, 
  -28, -27, -39, -61, -91, -126, 95, 64, 40, 27, 26, 37, 59, 89, 123, -98, 
  -66, -42, -29, -27, -37, -59, -88, -123, 98, 67, 42, 28, 26, 35, 56, 86, 
  120, -101, -69, -44, -29, -26, -36, -56, -85, -119, 102, 70, 44, 29, 25, 34, 
  54, 82, 116, -104, -72, -46, -30, -26, -34, -54, -82, -116, 105, 72, 46, 30, 
  25, 33, 51, 79, 113, -108, -75, -48, -32, -26, -33, -51, -79, -112, 109, 76, 
  49, 31, 25, 31, 49, 76, 109, -111, -78, -51, -33, -26, -32, -49, -76, -109, 
  112, 79, 51, 32, 25, 30, 47, 73, 106, -115, -81, -53, -34, -26, -31, -47, 
  -73, -105, 116, 82, 53, 34, 25, 29, 45, 70, 102, -118, -84, -56, -35, -26, 
  -30, -45, -70, -102, 119, 85, 56, 35, 26, 28, 43, 67, 99, -122, -88, -58, 
  -37, -27, -29, -43, -67, -98, 123, 88, 58, 37, 26, 27, 41, 64, 96, -125, 
  -91, -61, -39, -27, -28, -41, -64, -95, 126, 91, 61, 38, 27, 27, 39, 62, 
  92, 127, -94, -63, -40, -28, -27, -39, -61, -92, -126, 95, 64, 40, 27, 26, 
  37, 59, 89, 123, -97, -66, -42, -29, -27, -37, -59, -88, -123, 98, 67, 42, 
  28, 26, 36, 56, 86, 120, -101, -69, -44, -29, -27, -36, -56, -85, -119, 102, 
  69, 44, 29, 25, 34, 54, 82, 116, -104, -72, -46, -30, -26, -34, -54, -82, 
  -116, 105, 72, 46, 30, 25, 33, 51, 79, 113, -108, -75, -48, -31, -26, -33, 
  -51, -79, -112, 108, 75, 48, 31, 25, 31, 49, 76, 109, -111, -78, -51, -33, 
  -26, -32, -49, -76, -109, 112, 78, 51, 32, 25, 30, 47, 73, 106, -115, -81, 
  -53, -34, -26, -31, -47, -73, -105, 115, 82, 53, 34, 25, 29, 45, 70, 103, 
  -118, -84, -55, -35, -26, -30, -45, -70, -102, 119, 85, 56, 35, 26, 28, 43, 
  67, 99, -122, -87, -58, -37, -27, -29, -43, -67, -98, 123, 88, 58, 37, 26, 
  27, 41, 64, 96, -125, -91, -61, -39, -27, -28, -41, -64, -95, 126, 91, 61, 
  38, 27, 27, 39, 62, 92, 127, -94, -63, -40, -28, -27, -39, -61, -92, -126, 
  95, 64, 40, 27, 26, 37, 59, 89, 124, -97, -66, -42, -29, -27, -37, -59, 
  -88, -123, 98, 66, 42, 28, 26, 36, 56, 86, 120, -101, -69, -44, -29, -27, 
  -36, -56, -85, -119, 101, 69, 44, 29, 25, 34, 54, 83, 117, -104, -72, -46, 
  -30, -26, -34, -54, -82, -116, 105, 72, 46, 30, 25, 33, 52, 79, 113, -108, 
  -75, -48, -31, -26, -33, -51, -79, -112, 108, 75, 48, 31, 25, 31, 49, 76, 
  110, -111, -78, -51, -33, -26, -32, -49, -76, -109, 112, 78, 51, 32, 25, 30, 
  47, 73, 106, -115, -81, -53, -34, -26, -31, -47, -73, -105, 115, 81, 53, 34, 
  25, 29, 45, 70, 103, -118, -84, -55, -35, -26, -30, -45, -70, -102, 119, 85, 
  56, 35, 26, 28, 43, 67, 99, -122, -87, -58, -37, -27, -29, -43, -67, -99, 
  122, 88, 58, 37, 26, 27, 41, 65, 96, -125, -91, -60, -38, -27, -28, -41, 
  -64, -95, 126, 91, 61, 38, 27, 27, 39, 62, 93, 127, -94, -63, -40, -28, 
  -27, -39, -62, -92, -127, 94, 63, 40, 27, 26, 37, 59, 89, 124, -97, -66, 
  -42, -29, -27, -37, -59, -89, -123, 98, 66, 42, 28, 26, 36, 57, 86, 120, 
  -101, -69, -44, -29, -27, -36, -56, -85, -119, 101, 69, 44, 29, 25, 34, 54, 
  83, 117, -104, -72, -46, -30, -26, -34, -54, -82, -116, 105, 72, 46, 30, 25, 
  33, 52, 80, 113, -107, -75, -48, -31, -26, -33, -51, -79, -112, 108, 75, 48, 
  31, 25, 31, 49, 76, 110, -111, -78, -50, -33, -26, -32, -49, -76, -109, 112, 
  78, 51, 32, 25, 30, 47, 73, 106, -114, -81, -53, -34, -26, -31, -47, -73, 
  -106, 115, 81, 53, 34, 25, 29, 45, 70, 103, -118, -84, -55, -35, -26, -30, 
  -45, -70, -102, 119, 84, 55, 35, 26, 28, 43, 68, 99, -121, -87, -58, -37, 
  -27, -29, -43, -67, -99, 122, 88, 58, 37, 26, 27, 41, 65, 96, -125, -90, 
  -60, -38, -27, -28, -41, -64, -95, 126, 91, 61, 38, 26, 27, 39, 62, 93, 
  127, -94, -63, -40, -28, -27, -39, -62, -92, -127, 94, 63, 40, 27, 26, 37, 
  59, 89, 124, -97, -66, -42, -28, -27, -38, -59, -89, -123, 98, 66, 42, 28, 
  26, 36, 57, 86, 120, -100, -69, -44, -29, -27, -36, -56, -85, -120, 101, 69, 
  44, 29, 25, 34, 54, 83, 117, -104, -71, -46, -30, -26, -35, -54, -82, -116, 
  105, 72, 46, 30, 25, 33, 52, 80, 113, -107, -74, -48, -31, -26, -33, -52, 
  -79, -113, 108, 75, 48, 31, 25, 32, 49, 77, 110, -111, -77, -50, -32, -26, 
  -32, -49, -76, -109, 111, 78, 50, 32, 25, 30, 47, 74, 106, -114, -81, -53, 
  -34, -26, -31, -47, -73, -106, 115, 81, 53, 33, 25, 29, 45, 71, 103, -118, 
  -84, -55, -35, -26, -30, -45, -70, -102, 118, 84, 55, 35, 26, 28, 43, 68, 
  100, -121, -87, -58, -37, -27, -29, -43, -67, -99, 122, 88, 58, 36, 26, 28, 
  41, 65, 96, -125, -90, -60, -38, -27, -28, -41, -64, -95, 126, 91, 61, 38, 
  26, 27, 39, 62, 93, -128, -94, -63, -40, -28, -28, -39, -62, -92, -127, 94, 
  63, 40, 27, 26, 37, 59, 90, 124, -97, -66, -42, -28, -27, -38, -59, -89, 
  -123, 98, 66, 42, 28, 26, 36, 57, 86, 121, -100, -68, -44, -29, -27, -36, 
  -57, -86, -120, 101, 69, 44, 29, 25, 34, 54, 83, 117, -104, -71, -46, -30, 
  -26, -35, -54, -82, -116, 104, 72, 46, 30, 25, 33, 52, 80, 114, -107, -74, 
  -48, -31, -26, -33, -52, -79, -113, 108, 75, 48, 31, 25, 32, 50, 77, 110, 
  -111, -77, -50, -32, -26, -32, -49, -76, -109, 111, 78, 50, 32, 25, 30, 47, 
  74, 107, -114, -80, -53, -34, -26, -31, -47, -73, -106, 115, 81, 53, 33, 25, 
  29, 45, 71, 103, -118, -84, -55, -35, -26, -30, -45, -70, -102, 118, 84, 55, 
  35, 26, 28, 43, 68, 100, -121, -87, -57, -37, -27, -29, -43, -67, -99, 122, 
  87, 58, 36, 26, 28, 41, 65, 96, -125, -90, -60, -38, -27, -28, -41, -65, 
  -96, 125, 91, 60, 38, 26, 27, 39, 62, 93, -128, -93, -63, -40, -28, -28, 
  -39, -62, -92, -127, 94, 63, 40, 27, 26, 38, 60, 90, 124, -97, -65, -42, 
  -28, -27, -38, -59, -89, -124, 97, 66, 42, 28, 26, 36, 57, 86, 121, -100, 
  -68, -44, -29, -27, -36, -57, -86, -120, 101, 69, 44, 29, 25, 34, 54, 83, 
  117, -103, -71, -46, -30, -26, -35, -54, -83, -116, 104, 72, 46, 30, 25, 33, 
  52, 80, 114, -107, -74, -48, -31, -26, -33, -52, -79, -113, 108, 75, 48, 31, 
  25, 32, 50, 77, 110, -110, -77, -50, -32, -26, -32, -50, -76, -109, 111, 78, 
  50, 32, 25, 30, 47, 74, 107, -114, -80, -52, -34, -26, -31, -47, -73, -106, 
  115, 81, 53, 33, 25, 29, 45, 71, 103, -117, -83, -55, -35, -26, -30, -45, 
  -70, -103, 118, 84, 55, 35, 26, 28, 43, 68, 100, -121, -87, -57, -37, -27, 
  -29, -43, -68, -99, 122, 87, 58, 36, 26, 28, 41, 65, 96, -124, -90, -60, 
  -38, -27, -28, -41, -65, -96, 125, 91, 60, 38, 26, 27, 39, 62, 93, -128, 
  -93, -63, -40, -28, -28, -39, -62, -92, -127, 94, 63, 40, 27, 26, 38, 60, 
  90, 124, -97, -65, -42, -28, -27, -38, -59, -89, -124, 97, 66, 42, 28, 26, 
  36, 57, 87, 121, -100, -68, -44, -29, -27, -36, -57, -86, -120, 101, 69, 44, 
  29, 25, 34, 55, 83, 117, -103, -71, -46, -30, -26, -35, -54, -83, -117, 104, 
  72, 46, 30, 25, 33, 52, 80, 114, -107, -74, -48, -31, -26, -33, -52, -80, 
  -113, 108, 75, 48, 31, 25, 32, 50, 77, 110, -110, -77, -50, -32, -26, -32, 
  -50, -77, -110, 111, 78, 50, 32, 25, 31, 47, 74, 107, -114, -80, -52, -34, 
  -26, -31, -47, -73, -106, 115, 81, 53, 33, 25, 29, 45, 71, 103, -117, -83, 
  -55, -35, -26, -30, -45, -71, -103, 118, 84, 55, 35, 26, 28, 43, 68, 100, 
  -121, -87, -57, -36, -27, -29, -43, -68, -99, 122, 87, 58, 36, 26, 28, 41, 
  65, 97, -124, -90, -60, -38, -27, -28, -41, -65, -96, 125, 90, 60, 38, 26, 
  27, 39, 62, 93, -128, -93, -62, -40, -28, -28, -40, -62, -93, -127, 94, 63, 
  40, 27, 26, 38, 60, 90, 125, -96, -65, -42, -28, -27, -38, -59, -89, -124, 
  97, 66, 42, 28, 26, 36, 57, 87, 121, -100, -68, -44, -29, -27, -36, -57, 
  -86, -120, 100, 68, 44, 29, 25, 35, 55, 83, 118, -103, -71, -46, -30, -26, 
  -35, -54, -83, -117, 104, 71, 46, 30, 25, 33, 52, 80, 114, -107, -74, -48, 
  -31, -26, -33, -52, -80, -113, 107, 74, 48, 31, 25, 32, 50, 77, 111, -110, 
  -77, -50, -32, -26, -32, -50, -77, -110, 111, 77, 50, 32, 25, 31, 48, 74, 
  107, -114, -80, -52, -34, -26, -31, -47, -74, -106, 114, 81, 52, 33, 25, 29, 
  45, 71, 104, -117, -83, -55, -35, -26, -30, -45, -71, -103, 118, 84, 55, 35, 
  25, 29, 43, 68, 100, -121, -86, -57, -36, -27, -29, -43, -68, -99, 121, 87, 
  57, 36, 26, 28, 41, 65, 97, -124, -90, -60, -38, -27, -28, -41, -65, -96, 
  125, 90, 60, 38, 26, 27, 40, 63, 93, -128, -93, -62, -40, -28, -28, -40, 
  -62, -93, -128, 94, 63, 40, 27, 26, 38, 60, 90, 125, -96, -65, -42, -28, 
  -27, -38, -60, -89, -124, 97, 66, 41, 28, 26, 36, 57, 87, 121, -100, -68, 
  -43, -29, -27, -36, -57, -86, -120, 100, 68, 43, 29, 25, 35, 55, 84, 118, 
  -103, -71, -45, -30, -26, -35, -55, -83, -117, 104, 71, 46, 30, 25, 33, 52, 
  80, 114, -106, -74, -48, -31, -26, -33, -52, -80, -113, 107, 74, 48, 31, 25, 
  32, 50, 77, 111, -110, -77, -50, -32, -26, -32, -50, -77, -110, 111, 77, 50, 
  32, 25, 31, 48, 74, 107, -113, -80, -52, -33, -26, -31, -48, -74, -106, 114, 
  80, 52, 33, 25, 30, 46, 71, 104, -117, -83, -55, -35, -26, -30, -45, -71, 
  -103, 118, 84, 55, 35, 25, 29, 43, 68, 100, -120, -86, -57, -36, -27, -29, 
  -43, -68, -100, 121, 87, 57, 36, 26, 28, 41, 66, 97, -124, -89, -60, -38, 
  -27, -28, -42, -65, -96, 125, 90, 60, 38, 26, 27, 40, 63, 94, -128, -93, 
  -62, -40, -28, -28, -40, -62, -93, -128, 93, 63, 40, 27, 26, 38, 60, 90, 
  125, -96, -65, -41, -28, -27, -38, -60, -90, -124, 97, 65, 41, 28, 26, 36, 
  57, 87, 121, -99, -68, -43, -29, -27, -36, -57, -86, -121, 100, 68, 43, 29, 
  25, 35, 55, 84, 118, -103, -71, -45, -30, -26, -35, -55, -83, -117, 104, 71, 
  45, 29, 25, 33, 52, 81, 114, -106, -74, -47, -31, -26, -34, -52, -80, -114, 
  107, 74, 48, 31, 25, 32, 50, 77, 111, -110, -77, -50, -32, -26, -32, -50, 
  -77, -110, 111, 77, 50, 32, 25, 31, 48, 74, 107, -113, -80, -52, -33, -26, 
  -31, -48, -74, -107, 114, 80, 52, 33, 25, 30, 46, 71, 104, -117, -83, -54, 
  -35, -26, -30, -46, -71, -103, 118, 83, 55, 35, 25, 29, 44, 68, 100, -120, 
  -86, -57, -36, -27, -29, -44, -68, -100, 121, 87, 57, 36, 26, 28, 42, 66, 
  97, -124, -89, -59, -38, -27, -28, -42, -65, -96, 125, 90, 60, 38, 26, 27, 
  40, 63, 94, -127, -93, -62, -40, -28, -28, -40, -62, -93, -128, 93, 62, 39, 
  27, 26, 38, 60, 90, 125, -96, -65, -41, -28, -27, -38, -60, -90, -124, 97, 
  65, 41, 28, 26, 36, 58, 87, 122, -99, -68, -43, -29, -27, -36, -57, -87, 
  -121, 100, 68, 43, 28, 25, 35, 55, 84, 118, -103, -71, -45, -30, -26, -35, 
  -55, -83, -117, 103, 71, 45, 29, 25, 33, 53, 81, 115, -106, -73, -47, -31, 
  -26, -34, -52, -80, -114, 107, 74, 47, 31, 25, 32, 50, 78, 111, -110, -77, 
  -50, -32, -26, -32, -50, -77, -110, 110, 77, 50, 32, 25, 31, 48, 75, 108, 
  -113, -80, -52, -33, -26, -31, -48, -74, -107, 114, 80, 52, 33, 25, 30, 46, 
  72, 104, -117, -83, -54, -35, -26, -30, -46, -71, -103, 117, 83, 55, 34, 25, 
  29, 44, 69, 101, -120, -86, -57, -36, -27, -29, -44, -68, -100, 121, 87, 57, 
  36, 26, 28, 42, 66, 97, -124, -89, -59, -38, -27, -28, -42, -65, -97, 124, 
  90, 60, 38, 26, 27, 40, 63, 94, -127, -92, -62, -39, -28, -28, -40, -63, 
  -93, -128, 93, 62, 39, 27, 26, 38, 60, 91, 125, -96, -65, -41, -28, -27, 
  -38, -60, -90, -124, 96, 65, 41, 28, 26, 36, 58, 87, 122, -99, -68, -43, 
  -29, -27, -37, -57, -87, -121, 100, 68, 43, 28, 26, 35, 55, 84, 118, -103, 
  -70, -45, -30, -26, -35, -55, -83, -117, 103, 71, 45, 29, 25, 33, 53, 81, 
  115, -106, -73, -47, -31, -26, -34, -52, -80, -114, 107, 74, 47, 30, 25, 32, 
  50, 78, 111, -109, -76, -49, -32, -26, -32, -50, -77, -110, 110, 77, 50, 32, 
  25, 31, 48, 75, 108, -113, -79, -52, -33, -26, -31, -48, -74, -107, 114, 80, 
  52, 33, 25, 30, 46, 72, 104, -116, -83, -54, -35, -26, -30, -46, -71, -103, 
  117, 83, 54, 34, 25, 29, 44, 69, 101, -120, -86, -57, -36, -27, -29, -44, 
  -68, -100, 121, 86, 57, 36, 26, 28, 42, 66, 97, -124, -89, -59, -38, -27, 
  -28, -42, -65, -97, 124, 90, 60, 38, 26, 27, 40, 63, 94, -127, -92, -62, 
  -39, -28, -28, -40, -63, -93, -128, 93, 62, 39, 27, 26, 38, 60, 91, 125, 
  -96, -65, -41, -28, -27, -38, -60, -90, -125, 96, 65, 41, 28, 26, 36, 58, 
  87, 122, -99, -67, -43, -29, -27, -37, -57, -87, -121, 100, 68, 43, 28, 26, 
  35, 55, 84, 118, -102, -70, -45, -30, -26, -35, -55, -84, -118, 103, 71, 45, 
  29, 25, 33, 53, 81, 115, -106, -73, -47, -31, -26, -34, -53, -80, -114, 107, 
  74, 47, 30, 25, 32, 50, 78, 111, -109, -76, -49, -32, -26, -32, -50, -77, 
  -111, 110, 77, 50, 32, 25, 31, 48, 75, 108, -113, -79, -52, -33, -26, -31, 
  -48, -74, -107, 114, 80, 52, 33, 25, 30, 46, 72, 104, -116, -82, -54, -35, 
  -26, -30, -46, -71, -104, 117, 83, 54, 34, 25, 29, 44, 69, 101, -120, -86, 
  -57, -36, -27, -29, -44, -68, -100, 121, 86, 57, 36, 26, 28, 42, 66, 98, 
  -123, -89, -59, -38, -27, -28, -42, -66, -97, 124, 90, 59, 37, 26, 27, 40, 
  63, 94, -127, -92, -62, -39, -28, -28, -40, -63, -93, -128, 93, 62, 39, 27, 
  26, 38, 61, 91, 126, -95, -64, -41, -28, -27, -38, -60, -90, -125, 96, 65, 
  41, 28, 26, 36, 58, 88, 122, -99, -67, -43, -29, -27, -37, -58, -87, -121, 
  100, 68, 43, 28, 26, 35, 55, 84, 119, -102, -70, -45, -30, -26, -35, -55, 
  -84, -118, 103, 71, 45, 29, 25, 33, 53, 81, 115, -106, -73, -47, -31, -26, 
  -34, -53, -81, -114, 106, 74, 47, 30, 25, 32, 50, 78, 111, -109, -76, -49, 
  -32, -26, -32, -50, -77, -111, 110, 77, 49, 32, 25, 31, 48, 75, 108, -113, 
  -79, -52, -33, -26, -31, -48, -74, -107, 113, 80, 52, 33, 25, 30, 46, 72, 
  105, -116, -82, -54, -35, -26, -30, -46, -71, -104, 117, 83, 54, 34, 25, 29, 
  44, 69, 101, -120, -85, -56, -36, -27, -29, -44, -69, -100, 120, 86, 57, 36, 
  26, 28, 42, 66, 98, -123, -89, -59, -38, -27, -29, -42, -66, -97, 124, 89, 
  59, 37, 26, 27, 40, 63, 94, -127, -92, -62, -39, -27, -28, -40, -63, -94, 
  127, 93, 62, 39, 27, 26, 38, 61, 91, 126, -95, -64, -41, -28, -27, -38, 
  -60, -90, -125, 96, 65, 41, 27, 26, 37, 58, 88, 122, -99, -67, -43, -29, 
  -27, -37, -58, -87, -121, 99, 68, 43, 28, 26, 35, 55, 84, 119, -102, -70, 
  -45, -30, -26, -35, -55, -84, -118, 103, 70, 45, 29, 25, 34, 53, 81, 115, 
  -106, -73, -47, -31, -26, -34, -53, -81, -114, 106, 73, 47, 30, 25, 32, 51, 
  78, 112, -109, -76, -49, -32, -26, -33, -50, -78, -111, 110, 76, 49, 31, 25, 
  31, 48, 75, 108, -112, -79, -51, -33, -26, -31, -48, -75, -107, 113, 80, 52, 
  33, 25, 30, 46, 72, 105, -116, -82, -54, -34, -26, -30, -46, -72, -104, 117, 
  83, 54, 34, 25, 29, 44, 69, 101, -119, -85, -56, -36, -27, -29, -44, -69, 
  -101, 120, 86, 57, 36, 26, 28, 42, 66, 98, -123, -89, -59, -37, -27, -29, 
  -42, -66, -97, 124, 89, 59, 37, 26, 27, 40, 63, 94, -127, -92, -62, -39, 
  -27, -28, -40, -63, -94, 127, 93, 62, 39, 27, 27, 38, 61, 91, 126, -95, 
  -64, -41, -28, -27, -38, -60, -90, -125, 96, 65, 41, 27, 26, 37, 58, 88, 
  122, -99, -67, -43, -29, -27, -37, -58, -87, -122, 99, 67, 43, 28, 26, 35, 
  56, 85, 119, -102, -70, -45, -30, -26, -35, -55, -84, -118, 103, 70, 45, 29, 
  25, 34, 53, 81, 115, -105, -73, -47, -31, -26, -34, -53, -81, -115, 106, 73, 
  47, 30, 25, 32, 51, 78, 112, -109, -76, -49, -32, -26, -33, -51, -78, -111, 
  110, 76, 49, 31, 25, 31, 48, 75, 108, -112, -79, -51, -33, -26, -31, -48, 
  -75, -108, 113, 79, 52, 33, 25, 30, 46, 72, 105, -116, -82, -54, -34, -26, 
  -30, -46, -72, -104, 117, 83, 54, 34, 25, 29, 44, 69, 101, -119, -85, -56, 
  -36, -27, -29, -44, -69, -101, 120, 86, 56, 36, 26, 28, 42, 66, 98, -123, 
  -88, -59, -37, -27, -29, -42, -66, -97, 124, 89, 59, 37, 26, 27, 40, 64, 
  95, -126, -92, -61, -39, -27, -28, -40, -63, -94, 127, 92, 62, 39, 27, 27, 
  38, 61, 91, 126, -95, -64, -41, -28, -27, -39, -61, -91, -125, 96, 64, 41, 
  27, 26, 37, 58, 88, 123, -98, -67, -43, -29, -27, -37, -58, -87, -122, 99, 
  67, 43, 28, 26, 35, 56, 85, 119, -102, -70, -45, -30, -26, -35, -55, -84, 
  -118, 102, 70, 45, 29, 25, 34, 53, 82, 115, -105, -73, -47, -31, -26, -34, 
  -53, -81, -115, 106, 73, 47, 30, 25, 32, 51, 78, 112, -109, -76, -49, -32, 
  -26, -33, -51, -78, -111, 109, 76, 49, 31, 25, 31, 49, 75, 108, -112, -79, 
  -51, -33, -26, -31, -48, -75, -108, 113, 79, 51, 33, 25, 30, 46, 72, 105, 
  -116, -82, -54, -34, -26, -30, -46, -72, -104, 116, 82, 54, 34, 25, 29, 44, 
  69, 102, -119, -85, -56, -36, -27, -29, -44, -69, -101, 120, 86, 56, 36, 26, 
  28, 42, 67, 98, -123, -88, -59, -37, -27, -29, -42, -66, -97, 123, 89, 59, 
  37, 26, 27, 40, 64, 95, -126, -92, -61, -39, -27, -28, -40, -63, -94, 127, 
  92, 62, 39, 27, 27, 38, 61, 91, 126, -95, -64, -41, -28, -27, -39, -61, 
  -91, -125, 96, 64, 41, 27, 26, 37, 58, 88, 123, -98, -67, -43, -29, -27, 
  -37, -58, -88, -122, 99, 67, 43, 28, 26, 35, 56, 85, 119, -102, -70, -45, 
  -30, -26, -35, -56, -84, -118, 102, 70, 45, 29, 25, 34, 53, 82, 116, -105, 
  -73, -47, -31, -26, -34, -53, -81, -115, 106, 73, 47, 30, 25, 32, 51, 79, 
  112, -109, -76, -49, -32, -26, -33, -51, -78, -111, 109, 76, 49, 31, 25, 31, 
  49, 76, 109, -112, -79, -51, -33, -26, -32, -48, -75, -108, 113, 79, 51, 33, 
  25, 30, 46, 73, 105, -115, -82, -54, -34, -26, -30, -46, -72, -104, 116, 82, 
  54, 34, 25, 29, 44, 70, 102, -119, -85, -56, -36, -27, -29, -44, -69, -101, 
  120, 86, 56, 35, 26, 28, 42, 67, 98, -123, -88, -59, -37, -27, -29, -42, 
  -66, -98, 123, 89, 59, 37, 26, 27, 40, 64, 95, -126, -91, -61, -39, -27, 
  -28, -40, -63, -94, 127, 92, 61, 39, 27, 27, 39, 61, 92, 126, -95, -64, 
  -41, -28, -27, -39, -61, -91, -126, 95, 64, 41, 27, 26, 37, 58, 88, 123, 
  -98, -67, -43, -29, -27, -37, -58, -88, -122, 99, 67, 43, 28, 26, 35, 56, 
  85, 119, -101, -69, -45, -30, -26, -36, -56, -84, -119, 102, 70, 45, 29, 25, 
  34, 53, 82, 116, -105, -72, -47, -31, -26, -34, -53, -81, -115, 106, 73, 47, 
  30, 25, 32, 51, 79, 112, -108, -75, -49, -32, -26, -33, -51, -78, -112, 109, 
  76, 49, 31, 25, 31, 49, 76, 109, -112, -78, -51, -33, -26, -32, -49, -75, 
  -108, 113, 79, 51, 33, 25, 30, 46, 73, 105, -115, -82, -53, -34, -26, -30, 
  -46, -72, -105, 116, 82, 54, 34, 25, 29, 44, 70, 102, -119, -85, -56, -36, 
  -27, -30, -44, -69, -101, 120, 85, 56, 35, 26, 28, 42, 67, 98, -122, -88, 
  -58, -37, -27, -29, -42, -66, -98, 123, 89, 59, 37, 26, 27, 40, 64, 95, 
  -126, -91, -61, -39, -27, -28, -41, -64, -94, 127, 92, 61, 39, 27, 27, 39, 
  61, 92, 127, -95, -64, -41, -28, -27, -39, -61, -91, -126, 95, 64, 41, 27, 
  26, 37, 59, 88, 123, -98, -67, -42, -29, -27, -37, -58, -88, -122, 99, 67, 
  42, 28, 26, 35, 56, 85, 119, -101, -69, -44, -30, -26, -36, -56, -85, -119, 
  102, 70, 44, 29, 25, 34, 54, 82, 116, -105, -72, -47, -31, -26, -34, -53, 
  -81, -115, 105, 73, 47, 30, 25, 32, 51, 79, 112, -108, -75, -49, -32, -26, 
  -33, -51, -78, -112, 109, 76, 49, 31, 25, 31, 49, 76, 109, -112, -78, -51, 
  -33, -26, -32, -49, -75, -108, 112, 79, 51, 32, 25, 30, 47, 73, 105, -115, 
  -81, -53, -34, -26, -31, -47, -72, -105, 116, 82, 54, 34, 25, 29, 44, 70, 
  102, -119, -85, -56, -36, -26, -30, -44, -69, -101, 119, 85, 56, 35, 26, 28, 
  42, 67, 99, -122, -88, -58, -37, -27, -29, -42, -66, -98, 123, 88, 59, 37, 
  26, 27, 41, 64, 95, -126, -91, -61, -39, -27, -28, -41, -64, -95, 127, 92, 
  61, 39, 27, 27, 39, 61, 92, 127, -94, -64, -41, -28, -27, -39, -61, -91, 
  -126, 95, 64, 40, 27, 26, 37, 59, 89, 123, -98, -66, -42, -29, -27, -37, 
  -58, -88, -122, 98, 67, 42, 28, 26, 35, 56, 85, 120, -101, -69, -44, -30, 
  -26, -36, -56, -85, -119, 102, 70, 44, 29, 25, 34, 54, 82, 116, -105, -72, 
  -46, -30, -26, -34, -53, -82, -115, 105, 73, 46, 30, 25, 33, 51, 79, 113, 
  -108, -75, -49, -32, -26, -33, -51, -78, -112, 109, 76, 49, 31, 25, 31, 49, 
  76, 109, -112, -78, -51, -33, -26, -32, -49, -75, -108, 112, 79, 51, 32, 25, 
  30, 47, 73, 106, -115, -81, -53, -34, -26, -31, -47, -72, -105, 116, 82, 53, 
  34, 25, 29, 45, 70, 102, -119, -84, -56, -36, -26, -30, -45, -69, -101, 119, 
  85, 56, 35, 26, 28, 43, 67, 99, -122, -88, -58, -37, -27, -29, -43, -67, 
  -98, 123, 88, 58, 37, 26, 27, 41, 64, 95, -126, -91, -61, -39, -27, -28, 
  -41, -64, -95, 126, 92, 61, 39, 27, 27, 39, 61, 92, 127, -94, -63, -40, 
  -28, -27, -39, -61, -91, -126, 95, 64, 40, 27, 26, 37, 59, 89, 123, -98, 
  -66, -42, -29, -27, -37, -59, -88, -123, 98, 67, 42, 28, 26, 35, 56, 86, 
  120, -101, -69, -44, -29, -26, -36, -56, -85, -119, 102, 70, 44, 29, 25, 34, 
  54, 82, 116, -104, -72, -46, -30, -26, -34, -54, -82, -116, 105, 72, 46, 30, 
  25, 33, 51, 79, 113, -108, -75, -48, -32, -26, -33, -51, -79, -112, 109, 76, 
  49, 31, 25, 31, 49, 76, 109, -111, -78, -51, -33, -26, -32, -49, -76, -109, 
  112, 79, 51, 32, 25, 30, 47, 73, 106, -115, -81, -53, -34, -26, -31, -47, 
  -73, -105, 116, 82, 53, 34, 25, 29, 45, 70, 102, -118, -84, -56, -35, -26, 
  -30, -45, -70, -102, 119, 85, 56, 35, 26, 28, 43, 67, 99, -122, -88, -58, 
  -37, -27, -29, -43, -67, -98, 123, 88, 58, 37, 26, 27, 41, 64, 96, -125, 
  -91, -61, -39, -27, -28, -41, -64, -95, 126, 91, 61, 38, 27, 27, 39, 62, 
  92, 127, -94, -63, -40, -28, -27, -39, -61, -92, -126, 95, 64, 40, 27, 26, 
  37, 59, 89, 123, -97, -66, -42, -29, -27, -37, -59, -88, -123, 98, 67, 42, 
  28, 26, 36, 56, 86, 120, -101, -69, -44, -29, -27, -36, -56, -85, -119, 102, 
  69, 44, 29, 25, 34, 54, 82, 116, -104, -72, -46, -30, -26, -34, -54, -82, 
  -116, 105, 72, 46, 30, 25, 33, 51, 79, 113, -108, -75, -48, -31, -26, -33, 
  -51, -79, -112, 108, 75, 49, 31, 25, 31, 49, 76, 109, -111, -78, -51, -33, 
  -26, -32, -49, -76, -109, 112, 78, 51, 32, 25, 30, 47, 73, 106, -115, -81, 
  -53, -34, -26, -31, -47, -73, -105, 115, 82, 53, 34, 25, 29, 45, 70, 103, 
  -118, -84, -55, -35, -26, -30, -45, -70, -102, 119, 85, 56, 35, 26, 28, 43, 
  67, 99, -122, -87, -58, -37, -27, -29, -43, -67, -98, 123, 88, 58, 37, 26, 
  27, 41, 64, 96, -125, -91, -61, -39, -27, -28, -41, -64, -95, 126, 91, 61, 
  38, 27, 27, 39, 62, 92, 127, -94, -63, -40, -28, -27, -39, -61, -92, -126, 
  95, 64, 40, 27, 26, 37, 59, 89, 124, -97, -66, -42, -29, -27, -37, -59, 
  -88, -123, 98, 66, 42, 28, 26, 36, 56, 86, 120, -101, -69, -44, -29, -27, 
  -36, -56, -85, -119, 101, 69, 44, 29, 25, 34, 54, 83, 117, -104, -72, -46, 
  -30, -26, -34, -54, -82, -116, 105, 72, 46, 30, 25, 33, 52, 79, 113, -108, 
  -75, -48, -31, -26, -33, -51, -79, -112, 108, 75, 48, 31, 25, 31, 49, 76, 
  110, -111, -78, -51, -33, -26, -32, -49, -76, -109, 112, 78, 51, 32, 25, 30, 
  47, 73, 106, -115, -81, -53, -34, -26, -31, -47, -73, -105, 115, 81, 53, 34, 
  25, 29, 45, 70, 103, -118, -84, -55, -35, -26, -30, -45, -70, -102, 119, 85, 
  56, 35, 26, 28, 43, 67, 99, -122, -87, -58, -37, -27, -29, -43, -67, -99, 
  122, 88, 58, 37, 26, 27, 41, 65, 96, -125, -91, -60, -38, -27, -28, -41, 
  -64, -95, 126, 91, 61, 38, 27, 27, 39, 62, 93, 127, -94, -63, -40, -28, 
  -27, -39, -62, -92, -127, 94, 63, 40, 27, 26, 37, 59, 89, 124, -97, -66, 
  -42, -29, -27, -37, -59, -89, -123, 98, 66, 42, 28, 26, 36, 57, 86, 120, 
  -101, -69, -44, -29, -27, -36, -56, -85, -120, 101, 69, 44, 29, 25, 34, 54, 
  83, 117, -104, -72, -46, -30, -26, -34, -54, -82, -116, 105, 72, 46, 30, 25, 
  33, 52, 80, 113, -107, -75, -48, -31, -26, -33, -51, -79, -112, 108, 75, 48, 
  31, 25, 31, 49, 76, 110, -111, -78, -50, -33, -26, -32, -49, -76, -109, 112, 
  78, 51, 32, 25, 30, 47, 73, 106, -114, -81, -53, -34, -26, -31, -47, -73, 
  -106, 115, 81, 53, 34, 25, 29, 45, 70, 103, -118, -84, -55, -35, -26, -30, 
  -45, -70, -102, 119, 84, 55, 35, 26, 28, 43, 68, 99, -121, -87, -58, -37, 
  -27, -29, -43, -67, -99, 122, 88, 58, 37, 26, 28, 41, 65, 96, -125, -90, 
  -60, -38, -27, -28, -41, -64, -95, 126, 91, 61, 38, 26, 27, 39, 62, 93,   
};

