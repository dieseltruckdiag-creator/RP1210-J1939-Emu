// Standalone CAT-extended flash simulator wire helpers; no real ECU programming.
#pragma once
#include <cstdint>
#include <vector>
#include <cstddef>
namespace catj {
constexpr uint32_t PGN_DM13=0xDF00;
constexpr uint8_t CMD_READ=0x82,CMD_WRITE_RESP=0x83;
constexpr uint8_t PID_FLASH_STATUS=0x88,PID_FLASH_INFO=0x03,PID_FLASH_CONTROL=0x01,PID_FLASH_DATA=0x02,SUB_SOFTWARE_PART=0x01;
constexpr uint8_t M_NOTFLASH=0,M_INFLASH=1,M_FILE=2,M_FILEPROC=3,M_FILEDONE=4;
constexpr uint8_t FC_OK=0,FC_BUSY=1,FC_CHECKSUM=2,FC_BADCHECKSUM=3,FC_INAPPROPRIATE=4,FC_ERASEFAIL=5,FC_TERMINATE=6,FC_ABORT=7,FC_BADFILEINFO=8,FC_INVALIDOFFSET=9,FC_PROCEED=10,FC_BADFILEDATA=11,FC_COMPLETE=12;
inline void putBe16(std::vector<uint8_t>&v,uint16_t x){v.push_back(uint8_t(x>>8));v.push_back(uint8_t(x));}
inline void putBe32(std::vector<uint8_t>&v,uint32_t x){v.push_back(uint8_t(x>>24));v.push_back(uint8_t(x>>16));v.push_back(uint8_t(x>>8));v.push_back(uint8_t(x));}
inline uint16_t getBe16(const uint8_t*p){return uint16_t((uint16_t(p[0])<<8)|p[1]);}
inline uint32_t getBe32(const uint8_t*p){return (uint32_t(p[0])<<24)|(uint32_t(p[1])<<16)|(uint32_t(p[2])<<8)|p[3];}
inline uint16_t packStatus(uint8_t cmd,uint8_t mode){return uint16_t((uint16_t(cmd)<<8)|mode);}
inline uint8_t statusCmd(uint8_t a,uint8_t){return a;}
inline uint8_t statusMode(uint8_t b){return b;}
inline std::vector<uint8_t> buildMsg(uint8_t cmd,uint8_t pid,const std::vector<uint8_t>&body){std::vector<uint8_t>v={cmd,pid};v.insert(v.end(),body.begin(),body.end());return v;}
inline size_t parseHeader(const std::vector<uint8_t>&v,uint8_t&cmd,uint16_t&pid){if(v.size()<2)return 0;cmd=v[0];pid=v[1];return 2;}
}
