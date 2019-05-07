/**
 *@author: Zane Jakobs
 *@brief: base class for bidding agents
 */
#include <vector>
#include <utility>
#include <string_view>

namespace Econ
{
    template<class Currency = double>
    class Bidder
    {
        /**
         did the bidder win? How much did they pay and what was the item worth?
         If the bidder lost (first argument false), the second argument is the winning price
         */
        using outcome = std::tuple<bool, Currency, Currency>;
    protected:
        //outcomes of previous auctions
        std::vector<outcome> history;
        //string containing "name" or other identification
        std::string_view ID;
        //current bid value
        Currency currBid;
        
    public:
        //returns the bidder's bid as a function of the auction state
        template<typename AuctionState>
        virtual Currency bid(AuctionState currState) = 0;
        
        /**
         *@brief: updates the player history and other parameters after an auction
         *@param winner: id of the auction winner
         *@param winningPayment: how much does the winner pay?
         */
        virtual void update(std::string_view winner, Currency winningPayment) = 0;
        
    };
}
