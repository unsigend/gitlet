/**
 * MIT License
 *
 * Copyright (c) 2025 Qiu Yixiang
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <util/str.h>
#include <util/error.h>

#include <string.h>
#include <openssl/sha.h>
#include <stdio.h>

bool str_start_with(const char *str, const char *prefix){
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

bool str_end_with(const char *str, const char *suffix){
    return strncmp(str + strlen(str) - strlen(suffix), suffix, strlen(suffix)) == 0;
}

bool str_contains(const char *str, const char *substr){
    return strstr(str, substr) != NULL;
}

bool str_equals(const char *str1, const char *str2){
    return strcmp(str1, str2) == 0;
}

void str_hash_sha1(char * restrict buffer, const char * str){
    unsigned char hash[SHA_DIGEST_LENGTH];
    if (SHA1((const unsigned char *)str, strlen(str), hash) == NULL){
        gitlet_panic("Failed to hash the string using SHA1");
    }
    
    // Convert binary hash to hex string
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(buffer + (i * 2), "%02x", hash[i]);
    }
}