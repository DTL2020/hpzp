LoadPlugin("RawSourcePlus.dll")
LoadPlugin("ResampleMT.dll")

RawSourcePlus("out8.raw", 308,308, "Y8")

ConvertToRGB24(matrix="PC.709")

AddBorders(10,10,10,10,color=$101010)

SincLin2ResizeMT(width*2, height*2, taps=32)

