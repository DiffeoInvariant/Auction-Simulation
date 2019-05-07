/**
 *@author: Zane Jakobs
 *@brief: class to represent order books
 * for various auction formats
 */
#include <set>
#include <string_view>
#include <utility>
#include <algorithm>
#include <iterator>
#include <deque>

namespace Econ
{
    
    //compares bids
    struct bid_less
    {
        //a bid is a pair of a name (a string_view) and a bid amount
        template<class Currency = double>
        using bid = std::pair<std::string_view, Currency>;
        
        constexpr bool operator()(const bid &lhs, const bid &rhs) const
        {
            return lhs.second < rhs.second;
        }
    }
    
    /**
     *@author: Zane Jakobs
     *@param Currency: arithmetic type representing the currency.
     Use double as default
     */
    template<class Currency = double>
    class Book
    {
        //a bid is a pair of a name (a string_view) and a bid amount
        using bid = std::pair<std::string_view, Currency>;
        
    protected:
        std::multiset<bid, bid_less> bids;
        
    public:
        
        constexpr Book() {};
        /**
         constructor if given some std container that's not a multiset,
         e.g. a vector or a deque or an array, that contains bids
         */
        template<class BidContainer = std::deque<bid>>
        Book(BidContainer cont)
        {
            bids = std::multiset<bid, bid_less>(cont.begin(), cont.end());
        }
        
        constexpr Book(std::multiset<bid, bid_less> _bids) : bids(_bids) {};
        
        //adds a bid to the order book
        constexpr void insert(bid newBid)
        {
            bids.insert(newBid);
        }
        
        //returns largest bid
        constexpr auto largest()
        {
            return *(std::prev(bids.end()));
        }
        //gets N-th highest bid
        constexpr auto NthPrice(std::size_t N)
        {
            auto numBids = bids.size();
            if(numBids < N)
            {
                throw "Error: not enough bids in the book.";
            }
            else
            {   //N is a size_t so it can't be negative, but it could (incorrectly) be zero
                if( N == 0)
                {
                    throw "Error: N must be greater than 0";
                }
                else
                {
                    auto elem = std::prev(bids.end(), N);
                    return *elem;
                }//end else
            }//end else
        }
        
        
    };
    
}
