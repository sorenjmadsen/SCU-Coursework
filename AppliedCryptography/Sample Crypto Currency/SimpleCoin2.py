
""" Used to store coin information """
class CoinID:
    def __init__(value, ID, num):
        self.value = value
        self.ID = ID
        self.num = num
    def getValue():
        return self.value
    def getID():
        return self.ID
    def getNum():
        return self.num

""" Used to store the Hash pointers """
class H_ptr:
    def __init__(data: Transaction):
        """ Take in a Transaction and output the Hash pointer """
        self.hash = Hash(data)  """Hash of data"""
        self.data = data        """Pointer to data of Transaction"""

""" Used to define the detailed information of the Transaction """
class Transaction:
    prev_H_ptr = None
    type = "PayCoin"
    transID = 0
    consumed = []   """Array of CoinIDs"""
    created = []    """Array of tuples containing {num, value, recipient}"""
    signatures = [] """Array of signatures of owners of consumed coins"""
    """ Initialize the data structure """
    def __init__ (ID, consumed_coins, created_coins, signatures):
        self.transID = ID
        self.consumed = consumed_coins
        self.created = created_coins
        self.signatures = signatures

    """ Verify the Transaction before adding, uses the blockchain """
    def verifyTransaction(chain: H_ptr):
        ledger = chain
        consumed_val = 0
        """ Search through entire ledger """
        """ Check if coins: have been previously consumed, have been created, are signed correctly """
        to_verify = self.consumed
        while (ledger != None):
            data = ledger.data
            for coin in to_verify:
                """ Check coin is not already consumed """
                for consumed_prev in data.consumed:
                    if (coin.getID() == consumed_prev.getID() && coin.getNum() == consumed_prev.getNum()):
                        return False """ Coin has alread been consumed """

                """ Check coin has been created """
                for created_prev in data.created:
                    """ Check to see if coin has been created in this Transaction """
                    if(coin.getID() == created_prev.getID() && coin.getNum() == created_prev.getNum()):
                        """ If coin HAS been created here, verify the signature """
                        verified = 0
                        for sig in self.signatures:
                            """ Check all signatures to see if there is a match """
                            """ PK = recipient, msg = data, sig = signature referenced in transaction"""
                            if (verifySignature(created_prev.recipient, data, sig)):
                                verified = 1
                        """ Coin has NOT been verified correctly """
                        if (verified == 0):
                            return False
                        """ If verified, then remove coin from to_verify """
                        to_verify.remove(coin)

            """ Move to next block in the chain """
            ledger = data.prev_H_ptr
        """ If coins still need to be verified for creation, then they don't exist in the chain"""
        if len(to_verify_creation > 0):
            return False

        """ Add up the values of consumed and created """
        total_val = 0
        for coin in self.consumed:
            total_val += coin.getValue()
        for coin in self.created:
            total_val -= coin.getValue()

        """ Consumption/Creation of coins values don't match """
        if (total_val != 0):
            return False

        return True


    """ Add the block to the chain """
    def addBlock (chain: H_ptr) -> H_ptr:
        self.prev_H_ptr = chain     """ Assigns the chain to prev_H_ptr """
        return H_ptr(self)          """ Create a new H_ptr and return to the ledger variable """


""" Create the blockchain """
""" Assume an initialized chain exists so coins exist in the system """
S = some_initialized_chain
to_be_consumed = list_of_coins_to_consume

""" Create new transaction """
new_trans = Transaction(initialized.data.transID + 1, to_be_consumed, created_coins, signatures)

""" Verify and add to blockchain """
if (new_trans.verifyTransaction(S)):
    S = new_trans.addBlock(S)
