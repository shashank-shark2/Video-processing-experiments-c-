#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    auto pipe = popen(cmd, "r");
    
    if (!pipe) throw std::runtime_error("popen() failed!");
    
    while (!feof(pipe))
    {
        if (fgets(buffer.data(), 128, pipe) != nullptr)
            result += buffer.data();
    }
    
    auto rc = pclose(pipe);
    
    if (rc == EXIT_SUCCESS)
    {
        std::cout << "SUCCESS\n";
    }
    else
    {
        std::cout << "FAILED\n";
    }
    
    return result;
}

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Start\n";
    std::string res;
    
    res = exec("ffprobe ../drop.avi > drop.txt 2>&1");

    res = exec("ffmpeg -i ../drop.avi -fs 900K outputMyMin.mp4");
    res = exec("ffprobe outputMyMin.mp4 > outputMyMin.txt 2>&1");

    res = exec("ffmpeg -i ../drop.avi -fs 10MB outputMyMax.mp4");
    res = exec("ffprobe outputMyMax.mp4 > outputMyMax.txt 2>&1");

    std::cout << "OUTPUT" << res << std::endl;
    cout<<"End\n";
    return 0;
}