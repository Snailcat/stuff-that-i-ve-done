#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
void funcout(std::vector<std::string> function) {
    int quarter, half, threefourths;
    quarter = function.size() / 4;
    half = function.size() / 2;
    threefourths = function.size() * 3 / 4;
    std::cout << "====================DDNF===============" << std::endl;
    for (int i = 0; i < function.size()/4; i++)
    {
        std::cout << function[i] << function[i + quarter] << function[i + half] << function[i + threefourths] << std::endl;
    }
}

void funcout(const std::vector<bool> function)
{
    int quarter, half, threefourths;
    quarter = function.size() / 4;
    half = function.size() / 2;
    threefourths = function.size() * 3 / 4;
    std::cout << "=============DDNF=BINARY==========" << std::endl;
    for (int i = 0; i < function.size() / 4; i++)
    {
        /*
        if (i % 4 == 0)
            std::cout << function[i-1+threefourths] << " ";
        else
            std::cout << function[i-1] << function[i-1+quarter] <<function[i-1+half];
        */
        std::cout << function[i] << function[i + quarter] << function[i + half] << function[i + threefourths] << " ";
    }
    std::cout<<std::endl;
}

void funcshuffle(std::vector<bool> function,std::vector<bool> &outfunc)
{
    int quarter, half, threefourths;
    quarter = function.size() / 4;
    half = function.size() / 2;
    threefourths = function.size() * 3 / 4;
    std::cout << "=============DDNF=BINARY==========" << std::endl;
    for (int i = 0; i < function.size()/4; i++)
    {
        outfunc[i] = function[i];
        outfunc[i + 1] = function[i + quarter];
        outfunc[i + 2] = function[i + half];
        outfunc[i + 3] = function[i + threefourths];
    }
}

int main()
{
    const unsigned n = 4;
    std::vector<bool> input{1,1,1,1,1,1,1,0,0,1,1,1,0,0,1,1}, DDNFbinary, DDNFbinaryout(16);
    std::vector<std::vector<int> > output(n, std::vector<int>(1 << n));
    std::vector<std::string> DDNF;
    //std::vector<std::vector<std::string>> DDNFoutput(n), DKNFoutput(n);
    unsigned num_to_fill = 1U << (n - 1);
    for (unsigned col = 0; col < n; ++col, num_to_fill >>= 1U)
    {
        for (unsigned row = num_to_fill; row < (1U << n); row += (num_to_fill * 2))
        {
            std::fill_n(&output[col][row], num_to_fill, 1);
        }
    }
    
    for (auto i = 0; i < n; i++)
    {
        for (auto j = 0; j < output[i].size(); j++)
        {
            if (input[j] == 1)
            {
                if (output[i][j] == 1)
                {
                    switch (i)
                    {
                    case 0:
                        DDNF.emplace_back("(x ^ ");
                        DDNFbinary.emplace_back(1);
                        break;
                    case 1:
                        DDNF.emplace_back("y ^ ");
                        DDNFbinary.emplace_back(1);
                        break;
                    case 2:
                        DDNF.emplace_back("z ^ ");
                        DDNFbinary.emplace_back(1);
                        break;
                    case 3:
                        DDNF.emplace_back("w) V ");
                        DDNFbinary.emplace_back(1);
                        break;
                    default:
                        break;
                    }
                }
                if (output[i][j] == 0)
                {
                    switch (i)
                    {
                    case 0:
                        DDNF.emplace_back("(!x ^ ");
                        DDNFbinary.emplace_back(0);
                        break;
                    case 1:
                        DDNF.emplace_back("!y ^ ");
                        DDNFbinary.emplace_back(0);
                        break;
                    case 2:
                        DDNF.emplace_back("!z ^ ");
                        DDNFbinary.emplace_back(0);
                        break;
                    case 3:
                        DDNF.emplace_back("!w) V ");
                        DDNFbinary.emplace_back(0);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }

    // These loops just print out the results, nothing more.
    std::cout << "x y z w f" << std::endl;
    for (unsigned x = 0; x < output[1].size(); ++x)
    {
        for (unsigned y = 0; y < n; ++y)
        {
            std::cout << output[y][x] << " ";
        }
        std::cout << input[x];
        std::cout << std::endl;
    }
    funcout(DDNF);
    funcout(DDNFbinary);
    //funcshuffle(DDNFbinary,DDNFbinaryout);
    //for (int i = 1; i < DDNFbinaryout.size() + 1; i++)
    //{
    //    if (i % 4 == 0)
    //        std::cout << DDNFbinaryout[i - 1] << " ";
    //    else
    //        std::cout << DDNFbinaryout[i - 1];
    //}
    return 0;
}