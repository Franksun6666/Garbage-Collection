class Person {
    let name: String
    var creditCard: CreditCard?
    
    init(name: String) {
        self.name = name
    }
    
    deinit {
        print("\(name) is being deinitialized")
    }
}

class CreditCard {
    let number: UInt64
    unowned let owner: Person
    
    init(number: UInt64, owner: Person) {
        self.number = number
        self.owner = owner
    }
    
    deinit {
        print("Card \(number) is being deinitialized")
    }
}

// Example usage:
var john: Person? = Person(name: "John Doe")
if let person = john {
    john?.creditCard = CreditCard(number: 1234567890123456, owner: person)
}

// Break the strong reference to see deinitialization in action
john = nil  // This should trigger deinitialization of both `Person` and `CreditCard` instances.
