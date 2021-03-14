#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, const char* argv[])
{
	// args: (uint)Size , (uint)SizeTrans, (float)Scale
	if (argc < 4)
	{
		printf("Error: not enough arguments. Using: hpzp.exe (uint)Size (uint)SizeTrans (float)Scale\r\n");
		printf("Example. hpzp.exe 288 20 0.02\r\n");
		return 1;
	}

	int iWidth = atoi(argv[1]); // 288
	int iHeight = iWidth;

	int iSizeTrans = atoi(argv[2]); // 20

	float fK_all = (float)atof(argv[3]); // 0.02f

    //int iWidth = 288, iHeight = 288;
	int iWidthFull = iWidth + iSizeTrans;
	int iHeightFull = iHeight + iSizeTrans;
    float fPi = 3.14159265f;

    FILE* f8 = fopen("out8.raw", "wb");

	if (f8 == 0)
	{
		printf("Error: can not open out8.raw for writing.");
		return 1;
	}

	FILE* f16 = fopen("out16.raw", "wb");

	if (f16 == 0)
	{
		printf("Error: can not open out16.raw for writing.");
			return 1;
	}

	FILE* ff = fopen("outf.raw", "wb");

	if (ff == 0)
	{
		printf("Error: can not open outf.raw for writing.");
			return 1;
	}

    unsigned char* pucArr = (unsigned char*)malloc(iWidthFull);
	unsigned short* pusArr = (unsigned short*)malloc(iWidthFull * sizeof(unsigned short));
	float* pfArr = (float*)malloc(iWidthFull * sizeof(float));

	for (int y = 0; y < iWidthFull; y++)
	{
		for (int x = 0; x < iHeightFull; x++)
		{
			float fOut;
			float fDist_x = (float)(x - iWidthFull / 2);
			float fDist_y = (float)(y - iHeightFull / 2);

			float fK0 = fPi / 2;

			float fKx = fK_all;
			float fKy = fK_all;

			float fKxy = fK_all;

			fOut = 110.0f * sinf(fK0 + fKx * fDist_x + fKy * fDist_y + fKxy * fDist_y * fDist_x);

			if (fabs(fDist_x) > iWidth / 2) // left and right proc
			{
				float frDist_x = (float)(iWidthFull / 2 - x);
				float frDist_y = (float)(iHeightFull / 2 - y);
				fOut = 110.0f * sinf(fK0 + fKx * frDist_x + fKy * frDist_y + fKxy * fDist_y * frDist_x);
				float fArg = fabs(fDist_x) - iWidth / 2;
				float fArgSin = fArg * fPi / ((iWidthFull - iWidth) / 2);
				float fWeight = 0.5f * cosf(fArgSin) + 0.5f;
				fOut *= fWeight;
			}

			if (fabs(fDist_y) > iHeight / 2) // upper and lower proc
			{
				float frDist_x = iWidthFull / 2 - x;
				float frDist_y = iHeightFull / 2 - y;
				fOut = 110.0f * sinf(fK0 + fKx * frDist_x + fKy * frDist_y + fKxy * frDist_y * fDist_x);
				float fArg = fabs(fDist_y) - iHeight / 2;
				float fArgSin = fArg * fPi / ((iHeightFull - iHeight) / 2);
				float fWeight = 0.5f * cosf(fArgSin) + 0.5f;
				fOut *= fWeight;
			}
			
			if (y < (iHeightFull - iHeight) / 2 && x > iWidthFull - (iWidthFull - iWidth) / 2 ) // upper right corner proc
			{
				float frDist_x = iWidthFull / 2 - x;
				float frDist_y = iHeightFull / 2 - y;
				fOut = 110.0f * sinf(fK0 + fKx * frDist_x + fKy * frDist_y + fKxy * frDist_y * frDist_x);
				float fArg_x = fabs(fDist_x) - iWidth / 2;
				float fArg_y = fabs(fDist_y) - iHeight / 2;
				float fArg = sqrtf(fArg_x * fArg_x + fArg_y * fArg_y);
				float fArgSin = fArg * fPi / ((iHeightFull - iHeight) / 2);
				float fWeight = 0.5f * cosf(fArgSin) + 0.5f;
				fOut *= fWeight;
			}

			if (y < (iHeightFull - iHeight) / 2 && x < (iWidthFull - iWidth) / 2) // upper left corner proc
			{
				fOut = 110.0f * sinf(fK0 + fKx * fDist_x + fKy * fDist_y + fKxy * fDist_y * fDist_x);
				float fArg_x = fabs(fDist_x) - iWidth / 2;
				float fArg_y = fabs(fDist_y) - iHeight / 2;
				float fArg = sqrtf(fArg_x * fArg_x + fArg_y * fArg_y);
				float fArgSin = fArg * fPi / ((iHeightFull - iHeight) / 2);
				float fWeight = 0.5f * cosf(fArgSin) + 0.5f;
				fOut *= fWeight;
			}

			if (y > iHeightFull - (iHeightFull - iHeight) / 2 && x < (iWidthFull - iWidth) / 2) // lower left corner proc
			{
				fOut = 110.0f * sinf(fK0 + fKx * fDist_x + fKy * fDist_y + fKxy * fDist_y * fDist_x);
				float fArg_x = fabs(fDist_x) - iWidth / 2;
				float fArg_y = fabs(fDist_y) - iHeight / 2;
				float fArg = sqrtf(fArg_x * fArg_x + fArg_y * fArg_y);
				float fArgSin = fArg * fPi / ((iHeightFull - iHeight) / 2);
				float fWeight = 0.5f * cosf(fArgSin) + 0.5f;
				fOut *= fWeight;
			}

			if (y > iHeightFull - (iHeightFull - iHeight) / 2 && x > iWidthFull - (iWidthFull - iWidth) / 2) // lower right corner proc
			{
				fOut = 110.0f * sinf(fK0 + fKx * fDist_x + fKy * fDist_y + fKxy * fDist_y * fDist_x);
				float fArg_x = fabs(fDist_x) - iWidth / 2;
				float fArg_y = fabs(fDist_y) - iHeight / 2;
				float fArg = sqrtf(fArg_x * fArg_x + fArg_y * fArg_y);
				float fArgSin = fArg * fPi / ((iHeightFull - iHeight) / 2);
				float fWeight = 0.5f * cosf(fArgSin) + 0.5f;
				fOut *= fWeight;
			}
			pucArr[x] = (unsigned char)(110.0f + 16.0f + fOut);
			pusArr[x] = (unsigned short)(110.0f * 256.0f + 16.0f * 256.0f + fOut * 256.0f);
			pfArr[x] = 110.0f + 16.0f + fOut;

			// transition to code level 16 (8bit) - immediate 110, 50

			// top and bottom
			if ((y == 0) || (y == iHeightFull - 1))
				for (int idx = 0; idx < iWidthFull; idx++)
				{
					pucArr[idx] = 50;
					pusArr[idx] = 50 * 256;
					pfArr[idx] = 50.0f;
				}
			if ((y == 1) || (y == iHeightFull - 2))
				for (int idx = 0; idx < iWidthFull; idx++)
				{
					pucArr[idx] = 110;
					pusArr[idx] = 110 * 256;
					pfArr[idx] = 110.0f;
				}

			// left and right

			pucArr[0] = 50;
			pucArr[iWidthFull - 1] = 50;

			pusArr[0] = 50 * 256;
			pusArr[iWidthFull - 1] = 50 * 256;

			pfArr[0] = 50.0f;
			pfArr[iWidthFull - 1] = 50.0f;
	

        } // x
        fwrite(pucArr, 1, iWidthFull, f8);
		fwrite(pusArr, sizeof(unsigned short), iWidthFull, f16);
		fwrite(pfArr, sizeof(float), iWidthFull, ff);

    } // y

    fclose(f8);
	fclose(f16);
	fclose(ff);

    free(pucArr);
	free(pusArr);
	free(pfArr);

    return 0;
}


