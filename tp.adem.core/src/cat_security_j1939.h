// Standalone training simulator security memory-tunnel helpers.
// Passwords here are artificial test fixtures, never credentials for real ECMs.
#pragma once
#include <cstdint>
#include <vector>
namespace catsec {
constexpr uint32_t PGN_DM14=0xD900,PGN_DM15=0xD800,PGN_DM16=0xD700,PTR_MASK=0xFFFFFF;
constexpr uint32_t MAP_LEVEL_READ=0xFFFF00,MAP_PASSWORD_1=0xFFFF01,MAP_PASSWORD_2=0xFFFF02,MAP_CUST_PW_1=0xFFFF03,MAP_CUST_PW_2=0xFFFF04;
constexpr uint8_t CMD_READ=1,CMD_WRITE=2,ST_PROCEED=0,ST_OP_DONE=1,ST_OP_FAILED=2;
constexpr uint16_t SEED_UNSECURED=0xFFFF;
constexpr int LVL_NORMAL=0,LVL_CUSTOMER=1,LVL_SERVICE_TOOL=2,LVL_FACTORY=3,PW_WIDTH=8;
static constexpr uint8_t SERVICE_TOOL_PW1[PW_WIDTH]={'S','I','M','-','S','V','C','1'};
static constexpr uint8_t SERVICE_TOOL_PW2[PW_WIDTH]={'S','I','M','-','S','V','C','2'};
static constexpr uint8_t TRAINER_FACTORY_PW1[PW_WIDTH]={'S','I','M','-','F','A','C','1'};
static constexpr uint8_t TRAINER_FACTORY_PW2[PW_WIDTH]={'S','I','M','-','F','A','C','2'};
inline bool pointerMatches(uint32_t a,uint32_t b){return (a&PTR_MASK)==(b&PTR_MASK);}
inline std::vector<uint8_t> padPassword(const uint8_t*p,int n){std::vector<uint8_t>v(PW_WIDTH,0);for(int i=0;i<n&&i<PW_WIDTH;++i)v[i]=p[i];return v;}
inline bool parseDm14(const std::vector<uint8_t>&v,uint16_t&length,uint8_t&command,uint32_t&pointer,uint16_t&key){
 if(v.size()<8)return false;length=uint16_t(v[0])|(uint16_t(v[1]&1)<<8);command=uint8_t((v[1]>>1)&7);pointer=uint32_t(v[2])|(uint32_t(v[3])<<8)|(uint32_t(v[4])<<16);key=uint16_t(v[6])|(uint16_t(v[7])<<8);return true;
}
inline std::vector<uint8_t> buildDm15(uint16_t length,uint8_t status,uint16_t seed){return {uint8_t(length),uint8_t(((length>>8)&1)|(status<<1)),0xFF,0xFF,0xFF,0xFF,uint8_t(seed),uint8_t(seed>>8)};}
inline std::vector<uint8_t> buildDm16(const std::vector<uint8_t>&v){std::vector<uint8_t>out={uint8_t(v.size()>255?255:v.size())};out.insert(out.end(),v.begin(),v.begin()+(v.size()>255?255:v.size()));return out;}
}
