# hpzp
Hyperbolic zone plate calculator

Outputs RAW line scanned files: uint8, uint16 and float32. Out file names: out8.raw, out16.raw, outf.raw.
Output size (width=height) is size+size_of_transition.

The calculated zone plate is scaled to 110.0f amplitude and added 16.0f offset for 16..235 levels 8bit (16 bit is 256.0 multiplied, float is just float in 16..235).
Edges are conditioned to transition to 16 code level (with hard coded 50 and 110 of 8bit values).

Using: hpzp size size_of_transition scale. All 3 parameters must present.
size - size of zone plate in samples. Integer number.
size_of_transition scale - size of transition to mid-level, transition is shaped with cosine curve. Integer number, even value recommended.
scale - the most magic param, determite the highest frequency in zone plate. Determined with hand picked. Typical values for start - 1/size. Float number.
Float number digit may depends on OS regional options like 0.02 or 0,02.

Example: hpzp 272 16 0.02

Outputs 288x288 raw files.

Example of loading out8.raw into avisynth with Rawsource plugin:
LoadPlugin("RawSourcePlus.dll")
RawSourcePlus("out8.raw", 288,288, "Y8")
ConvertToRGB24(matrix="PC.709")
AddBorders(10,10,10,10,color=$101010)

