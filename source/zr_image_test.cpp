#include "zr_image_test.hpp"

unsigned char image_test_png[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x01, 0xb1, 0x00, 0x00, 0x01, 0x23,
  0x08, 0x02, 0x00, 0x00, 0x00, 0x33, 0x1c, 0xa8, 0xae, 0x00, 0x00, 0x00,
  0x01, 0x73, 0x52, 0x47, 0x42, 0x00, 0xae, 0xce, 0x1c, 0xe9, 0x00, 0x00,
  0x00, 0x04, 0x67, 0x41, 0x4d, 0x41, 0x00, 0x00, 0xb1, 0x8f, 0x0b, 0xfc,
  0x61, 0x05, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00,
  0x0e, 0xc3, 0x00, 0x00, 0x0e, 0xc3, 0x01, 0xc7, 0x6f, 0xa8, 0x64, 0x00,
  0x00, 0x0b, 0x5b, 0x49, 0x44, 0x41, 0x54, 0x78, 0x5e, 0xed, 0xda, 0xe9,
  0x75, 0xe4, 0xb8, 0x19, 0x86, 0x51, 0xc7, 0xd5, 0x01, 0x75, 0x3c, 0x8e,
  0x66, 0x92, 0x71, 0x30, 0x63, 0xd5, 0x22, 0xbd, 0xc5, 0xe2, 0x07, 0x92,
  0xe0, 0x52, 0x8b, 0xea, 0xde, 0x5f, 0x3e, 0xdd, 0x04, 0x08, 0x82, 0xe0,
  0xd3, 0xd2, 0x1c, 0xff, 0xe7, 0x5f, 0x00, 0xbe, 0x69, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68, 0x22, 0x40, 0x68,
  0x22, 0x40, 0xbc, 0x65, 0x13, 0xff, 0xf9, 0xfb, 0x9f, 0x8d, 0xfe, 0xfc,
  0xf7, 0x7f, 0xd7, 0xb9, 0xf8, 0x4c, 0xff, 0xfb, 0xef, 0x9f, 0xeb, 0x59,
  0x78, 0x90, 0xbf, 0xff, 0x5c, 0xef, 0xcc, 0x8b, 0xd3, 0x44, 0x3e, 0x92,
  0x26, 0xd2, 0xf0, 0x7b, 0x7e, 0x77, 0x6e, 0x1d, 0x72, 0x67, 0x91, 0x42,
  0xf3, 0xdf, 0xd5, 0xea, 0xbc, 0x34, 0x2e, 0xae, 0xfe, 0x65, 0x6d, 0xb6,
  0xd6, 0x3f, 0xc3, 0xef, 0x42, 0x13, 0xf9, 0x48, 0x45, 0xe6, 0xda, 0x27,
  0xa5, 0xa3, 0x89, 0x17, 0xc5, 0x61, 0xd4, 0xc4, 0x77, 0xa1, 0x89, 0x7c,
  0xa4, 0xbb, 0xcc, 0x4d, 0x17, 0xab, 0xbb, 0x89, 0x27, 0x5d, 0x77, 0xe0,
  0x75, 0x68, 0x22, 0x9f, 0x68, 0x78, 0x5a, 0xe6, 0xce, 0xc8, 0xaa, 0x26,
  0xf6, 0xde, 0x84, 0x17, 0xa1, 0x89, 0x7c, 0xa2, 0xdb, 0xd3, 0x32, 0x7f,
  0x42, 0x56, 0x36, 0xb1, 0xf7, 0x36, 0xbc, 0x04, 0x4d, 0xe4, 0x13, 0xa5,
  0x72, 0x4b, 0x7e, 0xa7, 0x5d, 0xdd, 0xc4, 0xde, 0x1b, 0xf1, 0x02, 0x34,
  0x91, 0x4f, 0xf4, 0x93, 0xaa, 0x45, 0xc7, 0x63, 0x43, 0x13, 0x73, 0x2e,
  0x35, 0xf1, 0x4d, 0x68, 0x22, 0x1f, 0xe8, 0xe7, 0xb0, 0x2c, 0x3b, 0x1d,
  0x5b, 0x9a, 0xd8, 0x7b, 0x2f, 0x9e, 0x4d, 0x13, 0xf9, 0x40, 0xdf, 0x87,
  0x65, 0xe1, 0xe1, 0xd8, 0xd4, 0xc4, 0xde, 0x9b, 0xf1, 0x64, 0x9a, 0xc8,
  0x07, 0xba, 0x46, 0x6e, 0xe9, 0xd9, 0xd8, 0xd6, 0xc4, 0xef, 0xa3, 0xf9,
  0xf6, 0xbf, 0x3c, 0xdf, 0x7f, 0x62, 0xbf, 0xf4, 0xbf, 0x06, 0x68, 0x22,
  0x1f, 0xe8, 0x12, 0xb9, 0xc5, 0x47, 0x63, 0x63, 0x13, 0xaf, 0x67, 0xf3,
  0xbd, 0x13, 0x52, 0xec, 0x81, 0x26, 0xbe, 0x38, 0x4d, 0x64, 0xa9, 0xde,
  0x46, 0x6d, 0x6d, 0xe2, 0x65, 0x02, 0x4d, 0x7c, 0x0f, 0x9a, 0xc8, 0xe7,
  0xb9, 0x9c, 0x95, 0xe5, 0x27, 0x63, 0x73, 0x13, 0x7b, 0x6f, 0xf8, 0x82,
  0x34, 0xf1, 0xfd, 0x68, 0x22, 0x47, 0xd9, 0xdc, 0xc4, 0x5f, 0x40, 0x13,
  0xdf, 0x8f, 0x26, 0x72, 0x14, 0x4d, 0xd4, 0xc4, 0x77, 0x74, 0x5c, 0x13,
  0x2f, 0xa7, 0x61, 0x3c, 0x4f, 0xf5, 0xa5, 0xcc, 0xdd, 0xad, 0x58, 0xe5,
  0x1e, 0xd1, 0x6e, 0x7c, 0xb4, 0x57, 0xfb, 0x9c, 0xdd, 0x72, 0x83, 0x1b,
  0x53, 0xdf, 0x5e, 0xdb, 0xf1, 0x7c, 0xd5, 0x63, 0xbc, 0xc2, 0x87, 0xd7,
  0xd8, 0xde, 0xc3, 0x96, 0xb6, 0xeb, 0x3e, 0x8c, 0x26, 0x5b, 0x37, 0x53,
  0xb1, 0xa6, 0x57, 0x78, 0x35, 0x07, 0xd0, 0xc4, 0xab, 0xc6, 0xb1, 0x8f,
  0x9b, 0x79, 0x5a, 0xb7, 0xfa, 0x56, 0x9e, 0x95, 0x99, 0x41, 0xab, 0xca,
  0x38, 0xb7, 0x90, 0xa1, 0xb5, 0x47, 0x78, 0xc1, 0x5d, 0x6e, 0xa7, 0x1e,
  0xef, 0xe4, 0xfc, 0x8d, 0x67, 0x77, 0x7f, 0x97, 0x7f, 0x39, 0x56, 0x6b,
  0x2c, 0x6f, 0xff, 0x26, 0xec, 0xbb, 0x0f, 0x93, 0xb3, 0x7d, 0x4f, 0x74,
  0xba, 0x68, 0x3c, 0x69, 0xdf, 0xc9, 0x1a, 0xda, 0x7f, 0x5b, 0x1e, 0x4b,
  0x13, 0xaf, 0x66, 0x4f, 0xe3, 0xed, 0x19, 0x3a, 0x19, 0xbc, 0xf9, 0xd1,
  0xe8, 0xe1, 0xb9, 0xf8, 0x59, 0xdb, 0xed, 0x1f, 0x8f, 0x16, 0xdc, 0x73,
  0xdc, 0x87, 0xa3, 0xcb, 0x53, 0x58, 0x6d, 0x48, 0xf7, 0x71, 0x1d, 0x3c,
  0xd8, 0x68, 0xf4, 0xf8, 0x6f, 0xeb, 0x6d, 0x9c, 0x7a, 0xb2, 0xc1, 0x32,
  0xef, 0x2f, 0x1c, 0x4e, 0xd7, 0xbd, 0xfa, 0xbd, 0xd4, 0x4f, 0xb5, 0xef,
  0x7a, 0x76, 0xde, 0x87, 0x4c, 0x37, 0xbe, 0xfa, 0x7b, 0xb6, 0xaf, 0xbf,
  0xb9, 0xfc, 0xcf, 0xf1, 0xfb, 0xa9, 0x0e, 0xcf, 0x52, 0x4f, 0x7b, 0x4d,
  0x3b, 0xd1, 0xc4, 0x4a, 0x35, 0xd7, 0x79, 0x9e, 0xeb, 0x5f, 0x14, 0x73,
  0x8e, 0x3e, 0x9b, 0x9c, 0x8c, 0xeb, 0x5f, 0x8d, 0x07, 0x4d, 0x8c, 0x99,
  0x36, 0x58, 0xdf, 0xc4, 0x03, 0x8e, 0x6e, 0xd0, 0x77, 0x60, 0x07, 0xc3,
  0x1b, 0xb7, 0x19, 0x6f, 0xd5, 0xed, 0x46, 0x5d, 0x35, 0x97, 0x78, 0x7b,
  0x87, 0xd6, 0x45, 0x83, 0x55, 0x3c, 0xe7, 0x7b, 0x2b, 0xf6, 0xf1, 0x64,
  0xbf, 0xc5, 0xec, 0xbd, 0x0f, 0xd7, 0x6b, 0xa7, 0xae, 0x5a, 0x72, 0xcb,
  0x5b, 0xc5, 0x1e, 0x3c, 0xe7, 0x65, 0x1c, 0x4e, 0x13, 0x2b, 0xd5, 0x5c,
  0x5f, 0xf3, 0x5c, 0xfe, 0xb8, 0x31, 0xe1, 0xf8, 0xcc, 0x5c, 0x2e, 0x3c,
  0xff, 0x79, 0xe3, 0xf4, 0x8c, 0xc6, 0x2c, 0x3a, 0x65, 0x77, 0xab, 0x9b,
  0x7a, 0xc0, 0xe2, 0x20, 0x2f, 0xdd, 0x8f, 0xc5, 0x77, 0x19, 0xde, 0x23,
  0x4f, 0xf0, 0xfd, 0xe7, 0xcd, 0x67, 0x1a, 0x0c, 0x5c, 0xfe, 0x14, 0x4b,
  0x1f, 0x60, 0x47, 0xc5, 0x36, 0x9e, 0xec, 0xd4, 0x84, 0xdd, 0xf7, 0xe1,
  0x7a, 0xdd, 0xec, 0x46, 0xfd, 0xcc, 0xb7, 0x64, 0x4b, 0x8b, 0x3d, 0xd8,
  0xe9, 0xf9, 0x5f, 0x8d, 0x26, 0x56, 0xea, 0x26, 0x9e, 0x4e, 0x45, 0xfb,
  0x18, 0x8c, 0xcf, 0xcc, 0xe9, 0xda, 0xf3, 0x9f, 0x36, 0x97, 0x50, 0x8f,
  0x99, 0x33, 0x1a, 0xd5, 0x7e, 0xc4, 0xe2, 0x41, 0x96, 0x1d, 0xe4, 0xfb,
  0x81, 0x53, 0xa3, 0xee, 0xd6, 0xb3, 0xea, 0x06, 0x93, 0x6f, 0xe9, 0x7e,
  0x31, 0x6b, 0x5e, 0xe9, 0x26, 0xe3, 0xf7, 0x74, 0xb6, 0xec, 0x49, 0xa7,
  0x1d, 0xb0, 0x0f, 0xd7, 0xd5, 0x2e, 0xd9, 0xa5, 0xfe, 0x4b, 0x6f, 0xed,
  0xf1, 0xfc, 0x2f, 0x48, 0x13, 0x2b, 0xd5, 0x5c, 0x7f, 0xfe, 0xfc, 0x99,
  0x3c, 0x04, 0xc5, 0x98, 0x3f, 0x7f, 0xff, 0x7e, 0xfd, 0xd9, 0xc4, 0x02,
  0x8a, 0x31, 0x0b, 0x96, 0x3b, 0x3a, 0x9d, 0x13, 0xcb, 0x2a, 0x4e, 0xf2,
  0xaa, 0x0f, 0x60, 0x6a, 0x50, 0xd7, 0xc5, 0x57, 0xf7, 0x63, 0xa6, 0x87,
  0xdc, 0x5f, 0xfd, 0xe8, 0x8f, 0xb1, 0xd8, 0xc5, 0x93, 0x1d, 0x96, 0x71,
  0xc0, 0x3e, 0x5c, 0x2f, 0x5a, 0xb6, 0xb8, 0xcb, 0x09, 0x5c, 0x75, 0x24,
  0x1e, 0xff, 0x1a, 0x1e, 0x44, 0x13, 0x2b, 0x8d, 0xb9, 0x26, 0xa7, 0x6a,
  0x8c, 0x99, 0x3c, 0x37, 0xeb, 0x9a, 0xd8, 0xf3, 0x21, 0x15, 0x27, 0x79,
  0xc1, 0x1d, 0xc6, 0xa3, 0xa6, 0x06, 0x8d, 0x9f, 0x62, 0xee, 0x16, 0x7d,
  0xf3, 0xf7, 0x5f, 0xbf, 0xb7, 0x62, 0x17, 0x4f, 0x36, 0x37, 0xe1, 0x90,
  0x7d, 0xf8, 0xbe, 0xa8, 0x23, 0x8a, 0x4b, 0x76, 0xb3, 0xd8, 0x03, 0x4d,
  0x7c, 0x71, 0x8d, 0x26, 0xad, 0xfa, 0x7a, 0xea, 0xb9, 0xa6, 0x67, 0xaa,
  0xc7, 0x4c, 0x1f, 0x9b, 0x62, 0x4c, 0xc7, 0x49, 0xbe, 0xe8, 0xfd, 0x8a,
  0x16, 0x6c, 0x48, 0xb1, 0xac, 0xa9, 0x41, 0xe3, 0xcb, 0x67, 0x1e, 0xa2,
  0x77, 0x51, 0xd5, 0xd6, 0xce, 0x3f, 0xc5, 0x8e, 0x8a, 0x05, 0x9f, 0x6c,
  0x6d, 0xc2, 0x21, 0xfb, 0x30, 0xb8, 0x68, 0xc7, 0x5d, 0xd2, 0xc4, 0xf7,
  0x53, 0x1d, 0x98, 0x93, 0x35, 0xc7, 0xa2, 0x9c, 0x6b, 0x66, 0xa2, 0xfa,
  0xfe, 0xd3, 0x83, 0x8a, 0x31, 0x3b, 0x9f, 0xb3, 0x47, 0x34, 0xb1, 0xf7,
  0x1e, 0x55, 0x61, 0x26, 0x07, 0x54, 0x5b, 0xfb, 0xd0, 0xef, 0xb1, 0x5a,
  0xf1, 0x97, 0x8d, 0x6b, 0x38, 0x68, 0x1f, 0x1a, 0x8b, 0x9d, 0x7f, 0xed,
  0xd3, 0x8a, 0x69, 0x35, 0xf1, 0xc5, 0xd5, 0x4d, 0x5a, 0x77, 0x16, 0xd6,
  0x7c, 0x84, 0xe5, 0xfd, 0x67, 0x6e, 0x5e, 0x8c, 0xd9, 0xf9, 0x9c, 0x15,
  0x27, 0x79, 0xc1, 0x86, 0x8c, 0x47, 0x4d, 0x0d, 0x1a, 0x5f, 0x3d, 0xf9,
  0x10, 0x8d, 0x6f, 0xb6, 0xd7, 0xd6, 0x6f, 0xbc, 0x47, 0x63, 0xc9, 0xdb,
  0xde, 0xd5, 0x51, 0xfb, 0xd0, 0xfa, 0x10, 0x86, 0xba, 0xd7, 0x5e, 0x2c,
  0x77, 0xe7, 0xb3, 0xfa, 0x2a, 0x34, 0xb1, 0xb2, 0x57, 0x13, 0x57, 0x8c,
  0xd9, 0xf9, 0x9c, 0x15, 0x27, 0x79, 0xc1, 0x86, 0x8c, 0xd7, 0xb5, 0x5f,
  0x13, 0x5b, 0xef, 0xa9, 0xd7, 0x23, 0x3f, 0xc8, 0x23, 0x9a, 0x78, 0xe0,
  0x3e, 0x74, 0xd4, 0x76, 0xf9, 0xd7, 0xa1, 0x89, 0xef, 0xa7, 0x75, 0xc6,
  0xf6, 0x6a, 0xe2, 0xdc, 0x3c, 0xd5, 0x98, 0xb9, 0x43, 0x53, 0x8c, 0xd9,
  0x78, 0xce, 0x16, 0x7c, 0x69, 0x4b, 0x36, 0x64, 0x34, 0x4d, 0x57, 0x13,
  0x27, 0x9f, 0xa1, 0xfe, 0x60, 0xd7, 0xbc, 0xa5, 0xc7, 0x39, 0xa2, 0x89,
  0x47, 0xee, 0xc3, 0x82, 0x53, 0x70, 0x63, 0xd9, 0x63, 0x68, 0xe2, 0xfb,
  0x69, 0x9d, 0x83, 0x35, 0xa7, 0xac, 0x9a, 0x6b, 0x6e, 0x9e, 0x9d, 0xc6,
  0xf4, 0x9f, 0xb3, 0xbe, 0x0f, 0x60, 0xe9, 0x86, 0xdc, 0x7d, 0x02, 0x13,
  0xcb, 0x1a, 0xdd, 0x7f, 0xfa, 0x11, 0x34, 0xf1, 0xe2, 0xe0, 0x7d, 0x68,
  0x2c, 0xb9, 0x61, 0xc1, 0x6d, 0x8b, 0x09, 0x35, 0xf1, 0xc5, 0xb5, 0xd2,
  0xb0, 0xe6, 0x94, 0xed, 0xd4, 0xb7, 0x35, 0x63, 0x3a, 0xce, 0xd9, 0x92,
  0xaf, 0xaa, 0xb8, 0x66, 0xe9, 0x86, 0x0c, 0x87, 0xb6, 0x47, 0xdd, 0xdd,
  0x62, 0xee, 0x01, 0x96, 0xac, 0xfa, 0xd5, 0xd4, 0x6b, 0x7e, 0xe9, 0x26,
  0x9e, 0x34, 0x96, 0x5d, 0x9a, 0xbd, 0x71, 0x31, 0x99, 0x26, 0xbe, 0xb8,
  0x8f, 0x6a, 0xe2, 0x78, 0x60, 0xe3, 0x56, 0xc5, 0x49, 0xee, 0xd8, 0x90,
  0xdb, 0xdb, 0xb4, 0x86, 0x0d, 0xef, 0x30, 0x3f, 0xf9, 0x03, 0x5a, 0xb0,
  0xbb, 0x46, 0x5c, 0x5e, 0xbd, 0x89, 0x17, 0xd5, 0xc1, 0x2c, 0xac, 0xf8,
  0xb7, 0x4c, 0x13, 0x5f, 0x5c, 0xeb, 0xd5, 0xaf, 0x39, 0x65, 0xd5, 0x5c,
  0x73, 0xf3, 0xec, 0x34, 0x66, 0xc1, 0x39, 0x1b, 0x9d, 0xce, 0x89, 0x31,
  0xc5, 0x49, 0xee, 0xdd, 0x90, 0x4c, 0x31, 0x1e, 0x39, 0x98, 0x7e, 0xd9,
  0xc4, 0xf5, 0x7b, 0xea, 0x5d, 0xd4, 0x63, 0x15, 0xbb, 0x78, 0xb2, 0xa9,
  0x09, 0x4f, 0xda, 0x87, 0xc6, 0xa3, 0x7c, 0x99, 0x79, 0x9a, 0x62, 0xa0,
  0x26, 0xbe, 0xb8, 0xfa, 0x8c, 0xad, 0x3b, 0x65, 0x3b, 0xf5, 0x6d, 0xcd,
  0x98, 0xb9, 0x73, 0x36, 0x1e, 0x32, 0x39, 0xa2, 0x38, 0xc9, 0x1d, 0x1b,
  0xd2, 0xda, 0xd3, 0x91, 0x9e, 0xaf, 0xa3, 0xfc, 0x2a, 0x0f, 0x6f, 0xc1,
  0x26, 0x47, 0x34, 0xf1, 0xa8, 0x7d, 0x38, 0x4d, 0xbb, 0x74, 0x96, 0xe1,
  0xfb, 0x9d, 0x1e, 0x55, 0x2c, 0x57, 0x13, 0x5f, 0x5c, 0xeb, 0xfb, 0x5d,
  0x73, 0xca, 0xaa, 0xb9, 0xe6, 0xe6, 0xd9, 0x69, 0xcc, 0xcc, 0x39, 0x1b,
  0x9f, 0xcc, 0xe9, 0x01, 0xc5, 0x49, 0x5e, 0xb6, 0x21, 0xe5, 0x17, 0x3b,
  0xb6, 0xe6, 0xb3, 0xa8, 0xa6, 0xee, 0x7a, 0x4b, 0xe7, 0x6d, 0x5b, 0xf3,
  0x5e, 0xd7, 0x6a, 0x6c, 0xc6, 0xc6, 0x26, 0x1c, 0xb3, 0x0f, 0xe7, 0x59,
  0x7b, 0xa6, 0xf9, 0x39, 0x84, 0xd3, 0x83, 0x8a, 0xd5, 0x6a, 0xe2, 0x8b,
  0xab, 0x9a, 0x74, 0xb2, 0xe6, 0xdb, 0xa9, 0xe6, 0x9a, 0x9b, 0x67, 0xa7,
  0x31, 0xfb, 0x26, 0x6e, 0xcd, 0xa2, 0x06, 0xa3, 0xd6, 0xec, 0xde, 0xac,
  0x8d, 0x9f, 0xd7, 0x79, 0x79, 0x87, 0x2c, 0xac, 0xa5, 0xaa, 0xd7, 0x97,
  0xad, 0x4d, 0x38, 0x64, 0x1f, 0x2e, 0x93, 0x76, 0x2d, 0xed, 0xba, 0x8e,
  0xe9, 0x2d, 0xdd, 0xb8, 0xd8, 0x37, 0xa2, 0x89, 0x95, 0x35, 0x29, 0xd9,
  0x69, 0xcc, 0xe4, 0x39, 0xeb, 0xbe, 0x47, 0xf5, 0x31, 0x2f, 0x5d, 0xd4,
  0x81, 0x27, 0x7e, 0xbc, 0xac, 0x8e, 0x9b, 0x9d, 0x07, 0xaf, 0x79, 0xab,
  0xeb, 0x55, 0xdb, 0xf8, 0x65, 0xf3, 0x0e, 0x1d, 0xb1, 0x0f, 0xd7, 0x39,
  0x7b, 0xd6, 0x76, 0x7d, 0xe3, 0xd3, 0x7b, 0x5a, 0xec, 0xc1, 0x81, 0x27,
  0xe4, 0x99, 0x34, 0xb1, 0xd2, 0xdd, 0x9e, 0x2f, 0x3b, 0x8d, 0x99, 0x3c,
  0x67, 0xbd, 0xf7, 0x28, 0xbf, 0xe5, 0x99, 0x45, 0x5d, 0xc6, 0x1c, 0x7d,
  0xdc, 0x47, 0x2b, 0x5b, 0xfa, 0x9a, 0x2e, 0x5b, 0xb0, 0xf4, 0xea, 0x9d,
  0x94, 0xfb, 0xb8, 0xcb, 0x26, 0xed, 0xbf, 0x0f, 0x3f, 0x33, 0x2e, 0x5f,
  0xdd, 0xa2, 0x3d, 0xed, 0x3d, 0xab, 0xef, 0x4b, 0x13, 0x2b, 0xd5, 0x5c,
  0x73, 0xf3, 0xec, 0x34, 0xa6, 0xbb, 0x89, 0xed, 0x9b, 0x34, 0xbe, 0xe4,
  0xe9, 0x45, 0x5d, 0x6e, 0xf1, 0x80, 0xd3, 0x7e, 0xb7, 0xba, 0x65, 0x77,
  0x7c, 0xd8, 0xea, 0x86, 0x8e, 0x6b, 0xe2, 0xfe, 0xfb, 0x70, 0x33, 0xdf,
  0xc2, 0xf5, 0x5d, 0x26, 0xdb, 0xf1, 0xac, 0x9e, 0x2f, 0x9d, 0x9b, 0xef,
  0x75, 0x69, 0x62, 0xa5, 0x9a, 0x6b, 0xc5, 0x99, 0xd9, 0xf3, 0x9c, 0x5d,
  0x94, 0x0f, 0xd9, 0xfe, 0x34, 0xfe, 0xfe, 0x33, 0x79, 0x87, 0xaf, 0xbf,
  0x1c, 0x8d, 0xbd, 0x7e, 0x52, 0x8f, 0x38, 0xd1, 0xc3, 0xb5, 0x4d, 0x3f,
  0xf8, 0xd9, 0x65, 0x6d, 0x0b, 0x2e, 0xdc, 0xdb, 0x5d, 0xb7, 0xbe, 0xed,
  0xb4, 0x92, 0x7d, 0xf7, 0x61, 0xb8, 0xd6, 0xf9, 0xf7, 0x78, 0xbd, 0xfb,
  0xfc, 0x85, 0xc5, 0x26, 0x94, 0x83, 0xce, 0x13, 0x3e, 0xe1, 0x25, 0xed,
  0x46, 0x13, 0x2b, 0xd5, 0x5c, 0x73, 0xf3, 0xec, 0x34, 0x66, 0xe6, 0x30,
  0x2d, 0x79, 0xca, 0xeb, 0x35, 0x97, 0x99, 0xda, 0xb7, 0x38, 0x9f, 0xf1,
  0xd1, 0x0a, 0x73, 0xf2, 0xd7, 0x6c, 0x5c, 0xaf, 0xe1, 0xea, 0xa6, 0xee,
  0xf8, 0xbd, 0xae, 0xa7, 0x7c, 0x6c, 0x45, 0x0e, 0x4e, 0xf6, 0x5b, 0xcb,
  0x8e, 0xfb, 0x30, 0x5a, 0xeb, 0xd4, 0x2a, 0xbf, 0x2f, 0x5e, 0xf2, 0xae,
  0xdb, 0x27, 0xe9, 0xd6, 0x65, 0xc6, 0x47, 0x9c, 0x9d, 0xc3, 0xbc, 0x65,
  0x13, 0x1b, 0x47, 0xb4, 0xc3, 0xf8, 0x65, 0x76, 0xcd, 0xf9, 0x3d, 0xbc,
  0x67, 0xd0, 0x9a, 0x31, 0xd5, 0xa1, 0x2b, 0x8e, 0x66, 0x21, 0x03, 0xa7,
  0xae, 0x2f, 0xa6, 0xdf, 0xbc, 0xb7, 0xc5, 0x9c, 0xd3, 0x86, 0x77, 0x1c,
  0x7f, 0x4d, 0x37, 0x7f, 0x7f, 0xf4, 0xa7, 0xb6, 0x6c, 0x6f, 0x67, 0xad,
  0x5b, 0xe6, 0x4e, 0xfb, 0xf0, 0x73, 0xd9, 0xd7, 0x45, 0x53, 0x43, 0xf2,
  0x77, 0x8b, 0x97, 0x3b, 0x5c, 0xe1, 0xd9, 0xe0, 0x6d, 0x5f, 0xff, 0xbe,
  0xfb, 0x04, 0xbc, 0x18, 0x4d, 0xbc, 0xea, 0x9a, 0xf3, 0x7b, 0x78, 0xcf,
  0xa0, 0x35, 0x63, 0x5a, 0xc7, 0x6b, 0x7a, 0x8e, 0xd1, 0xa0, 0xc6, 0xe5,
  0xe5, 0xe4, 0xcf, 0xc9, 0xc2, 0x82, 0xbb, 0x76, 0xce, 0xb8, 0xca, 0x53,
  0x9b, 0x78, 0xb2, 0xc3, 0x3e, 0x9c, 0x5f, 0xf6, 0xcd, 0xab, 0x9d, 0x9e,
  0xb2, 0x71, 0xc0, 0x5a, 0xe6, 0xd7, 0xf7, 0x88, 0xd7, 0x74, 0xb0, 0xdf,
  0xf3, 0xbb, 0xf3, 0xc7, 0x29, 0xce, 0xe7, 0xc4, 0x81, 0xbc, 0xeb, 0x62,
  0xfb, 0xca, 0x9d, 0xba, 0xd0, 0xfd, 0xb9, 0x9d, 0x55, 0xf5, 0x5e, 0x33,
  0xcf, 0xbb, 0xdb, 0x7f, 0x1f, 0xc6, 0x33, 0xae, 0xae, 0x57, 0x7d, 0x42,
  0x7e, 0xcf, 0x6b, 0xd2, 0x44, 0xee, 0x3d, 0xb5, 0x8a, 0xf0, 0x64, 0x9a,
  0x48, 0x61, 0xaf, 0x2c, 0xfe, 0x82, 0xdf, 0xa4, 0xf8, 0x34, 0x9a, 0x48,
  0x53, 0xf5, 0x1b, 0x5c, 0x27, 0x51, 0xe4, 0xdd, 0x68, 0x22, 0x6d, 0xd7,
  0x1f, 0x17, 0xfb, 0xc2, 0x36, 0x28, 0xa9, 0x5f, 0x9f, 0x79, 0x37, 0x9a,
  0x48, 0xe9, 0xe7, 0xb7, 0xe7, 0x75, 0x3f, 0xe9, 0x6d, 0x1c, 0x0e, 0x4f,
  0xa3, 0x89, 0x8c, 0xe4, 0xbf, 0x26, 0x6e, 0xf8, 0x31, 0x6f, 0xd5, 0xcf,
  0x98, 0xf0, 0x74, 0x9a, 0xc8, 0x50, 0x82, 0xb8, 0xf1, 0x37, 0xdf, 0xcb,
  0x44, 0x9a, 0xc8, 0x9b, 0xd1, 0x44, 0x06, 0x06, 0xff, 0x35, 0x70, 0x53,
  0xd0, 0xce, 0x33, 0x49, 0x22, 0xef, 0x46, 0x13, 0xb9, 0x75, 0xfb, 0x53,
  0xe2, 0x0e, 0x3f, 0x26, 0x4a, 0x22, 0x6f, 0x47, 0x13, 0xb9, 0x35, 0x68,
  0xe2, 0x86, 0xa4, 0xf9, 0xc5, 0x99, 0x77, 0xa5, 0x89, 0x0c, 0xec, 0xf2,
  0xff, 0xa4, 0xb9, 0x4c, 0xa2, 0x88, 0xbc, 0x23, 0x4d, 0x64, 0x68, 0xf8,
  0x93, 0x62, 0x7f, 0x15, 0xaf, 0xe3, 0x37, 0xfd, 0xde, 0x0d, 0xcf, 0xa3,
  0x89, 0x8c, 0x0c, 0x7e, 0x56, 0xec, 0xa8, 0xdb, 0xcf, 0x38, 0x41, 0xe4,
  0x7d, 0x69, 0x22, 0x95, 0xe1, 0x4f, 0x8b, 0x27, 0xed, 0xdf, 0x84, 0xb7,
  0xfe, 0x64, 0x09, 0xaf, 0x44, 0x13, 0x69, 0x1a, 0xfe, 0xbc, 0x38, 0xcf,
  0x7f, 0x40, 0xe4, 0x17, 0xd0, 0x44, 0x66, 0x8d, 0x7f, 0x68, 0xbc, 0xe5,
  0x07, 0x43, 0x7e, 0x15, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04, 0x08, 0x4d, 0x04,
  0xf8, 0xf6, 0xef, 0xbf, 0xff, 0x07, 0xf2, 0x9a, 0xcb, 0x64, 0xd9, 0x7f,
  0x71, 0x72, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42,
  0x60, 0x82
};
unsigned int image_test_png_len = 3014;
