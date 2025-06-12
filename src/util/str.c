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

#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <zlib.h>

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
    str_hash_sha1_n(buffer, str, strlen(str));
}

void str_hash_sha1_n(char * restrict buffer, const char * str, size_t len){
    unsigned char hash[SHA_DIGEST_LENGTH];
    if (SHA1((const unsigned char *)str, len, hash) == NULL){
        fprintf(stderr, "Failed to hash the string using SHA1");
        exit(1);
    }
    
    // Convert binary hash to hex string
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(buffer + (i * 2), "%02x", hash[i]);
    }
}

unsigned long str_decompress(const char * src_buffer, size_t src_size, 
    char * dest_buffer, size_t dest_size, bool ignore_error){
    // decompress the content
    if (src_size == 0 || dest_size == 0 || src_buffer == NULL || dest_buffer == NULL){
        return 0;
    }
    uLongf decompressed_size = dest_size;
    int result = uncompress((Bytef *)dest_buffer, &decompressed_size, (Bytef *)src_buffer, src_size);
    if (!ignore_error && result != Z_OK){
        if (result == Z_MEM_ERROR){
            fprintf(stderr, "Out of memory\n");
        }else if (result == Z_BUF_ERROR){
            fprintf(stderr, "Buffer too small\n");
        }else{
            fprintf(stderr, "Failed to decompress the content: %d\n", result);
        }
        exit(1);
    }
    return (unsigned long)decompressed_size;
}

unsigned long str_compress(const char * src_buffer, size_t src_size, char * dest_buffer, size_t dest_size){
    // compress the content
    if (src_size == 0 || dest_size == 0 || src_buffer == NULL || dest_buffer == NULL){
        return 0;
    }
    uLongf compressed_size = dest_size;
    int result = compress((Bytef *)dest_buffer, &compressed_size, (Bytef *)src_buffer, src_size);
    if (result != Z_OK){
        if (result == Z_MEM_ERROR){
            fprintf(stderr, "Out of memory\n");
        }else if (result == Z_BUF_ERROR){
            fprintf(stderr, "Buffer too small\n");
        }else{
            fprintf(stderr, "Failed to compress the content: %d\n", result);
        }
        exit(1);
    }
    return (unsigned long)compressed_size;
}