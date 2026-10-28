#include "Misc.h"
#include <cctype>
namespace unc::misc_api {
std::string trim(std::string_view value) { std::size_t a=0,b=value.size(); while(a<b && std::isspace(static_cast<unsigned char>(value[a]))) ++a; while(b>a && std::isspace(static_cast<unsigned char>(value[b-1]))) --b; return std::string(value.substr(a,b-a)); }
std::vector<std::string> split(std::string_view value,char delimiter,bool keep_empty) { std::vector<std::string> out; std::size_t start=0; for(std::size_t i=0;i<=value.size();++i) if(i==value.size() || value[i]==delimiter) { if(keep_empty || i>start) out.emplace_back(value.substr(start,i-start)); start=i+1; } return out; }
bool starts_with(std::string_view value,std::string_view prefix) noexcept { return value.size()>=prefix.size() && value.substr(0,prefix.size())==prefix; }
bool ends_with(std::string_view value,std::string_view suffix) noexcept { return value.size()>=suffix.size() && value.substr(value.size()-suffix.size())==suffix; }
std::string replace_all(std::string_view value,std::string_view needle,std::string_view replacement) { std::string out(value); if(needle.empty()) return out; std::size_t pos=0; while((pos=out.find(needle,pos))!=std::string::npos) { out.replace(pos,needle.size(),replacement); pos+=replacement.size(); } return out; }
} // namespace unc::misc_api
