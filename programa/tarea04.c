/*
 * Copyright (C) 2010
 * Pablo Alvarado
 *
 * This file is part of the EL-5805 Digital Signal Processing Lecture at
 * the Costa Rica Institute of Technology
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the authors nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file   tarea04.c
 *         Contains the processing function
 * \author Pablo Alvarado
 * \author Student
 * \date   August 9th, 2010
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* For alpha = 0.4 */
#define DEFAULT_ALPHA 0.4
/* For k = Fs * 0.25 */
#define DEFAULT_DECIMATION 0.25

/**
 * You may need some global values
 */
static int k;
static float alpha;
static float *out_samples;
static int idx;


static float get_k_sample(int i) {
  /* modulus makes the array circular */
  return out_samples[(idx + i) % k];
}


static void set_k_sample(int i, float value) {
  /* modulus makes the array circular */
  out_samples[(idx + i) % k] = value;
}

/**
 * This method is called before the real processing starts.
 * You may use it to initialize whatever you need to.
 */
void init(const unsigned int Fs) {
#ifndef DECIMATION
  k = (int)((float)Fs * DEFAULT_DECIMATION);
#else
  k = (float)Fs * DECIMATION;
#endif

#ifndef ALPHA
  alpha = (float) DEFAULT_ALPHA;
#else
  alpha = (float) ALPHA;
#endif

  /* Calloc sets everything to zero, making the sys in steady state */
  out_samples = calloc(k, sizeof(float));
  idx = 0;
}

/**
 * Process a buffer of data.
 *
 * @param Fs sampling rate
 * @param channels number of channels per frame
 * @param frames   number of frames per buffer
 * @param buffer   input and output buffer
 *
 * @return zero if error, or 1 otherwise.
 */
int process(const unsigned int Fs, const int nframes, const float *in,
            float *out) {

  /* Apply filter */
  for(int i = 0; i < nframes; ++i){
    /* (1-a)x[n] + alpha y[n-k] */
    out[i] = (1.f - alpha) * in[i] + alpha * get_k_sample(i);
    set_k_sample(i, out[i]);
  }

  idx += nframes;

  return 0; // everything is ok
}
