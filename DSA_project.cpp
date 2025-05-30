#include <iostream>
#include <list>
#include <queue>
#include <string>
using namespace std;

// Structure to represent a Shop
struct Shop {
    int shopID;
    string name;
    string category;
};

// Structure to represent a Customer
struct Customer {
    int customerID;
    string name;
    int shopID;
};

// Linked List to manage Shops dynamically
class ShopList {
private:
    list<Shop> shops;

public:
    void addShop(int id, const string& name, const string& category) {
        shops.push_back({id, name, category});
        cout << "Shop " << name << " added \n";
    }

    void removeShop(int id) {
        for (auto it = shops.begin(); it != shops.end(); ++it) {
            if (it->shopID == id) {
                shops.erase(it);
                cout << "Shop with ID " << id << " removed \n";
                return;
            }
        }
        cout << "Shop with ID " << id << " not found \n";
    }

    void displayShops() {
        if (shops.empty()) {
            cout << "No shops available \n";
            return;
        }
        for (const auto& shop : shops) {
            cout << "Shop ID: " << shop.shopID << ", Name: " << shop.name
                 << ", Category: " << shop.category << "\n";
        }
    }
};

// Simple structure to represent a path between two shops
struct Path {
    int fromShopID;
    int toShopID;
    int distance;
};

// Class to manage Paths (between shops)
class Mall {
private:
    list<Path> paths;
    int adjMatrix[100][100];  // Adjacency matrix to represent the graph
    int numShops;

public:
    Mall() {
        numShops = 0;
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                adjMatrix[i][j] = 999999; // Use a large number to represent "infinity"
            }
        }
    }

    void addPath(int fromShopID, int toShopID, int distance) {
        adjMatrix[fromShopID][toShopID] = distance;
        adjMatrix[toShopID][fromShopID] = distance;  // Assuming bidirectional path
        paths.push_back({fromShopID, toShopID, distance});
        paths.push_back({toShopID, fromShopID, distance});
        cout << "Path added between Shop " << fromShopID << " and Shop " << toShopID
             << " with distance " << distance << "\n";
    }

    void displayPaths() {
        if (paths.empty()) {
            cout << "No paths available \n";
            return;
        }
        for (const auto& path : paths) {
            cout << "Path from Shop " << path.fromShopID << " to Shop " << path.toShopID
                 << " with distance " << path.distance << "\n";
        }
    }

    // Dijkstra's algorithm to find the shortest path between two shops
    void shortestPath(int startShopID, int endShopID) {
        int dist[100];
        int prev[100];
        bool visited[100];

        for (int i = 0; i < 100; i++) {
            dist[i] = 999999; // Use a large number to represent "infinity"
            prev[i] = -1;
            visited[i] = false;
        }

        dist[startShopID] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, startShopID});

        while (!pq.empty()) {
            int currentShop = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            if (visited[currentShop]) continue;
            visited[currentShop] = true;

            for (int i = 0; i < 100; i++) {
                if (adjMatrix[currentShop][i] != 999999 && !visited[i]) {
                    int newDist = currentDist + adjMatrix[currentShop][i];
                    if (newDist < dist[i]) {
                        dist[i] = newDist;
                        prev[i] = currentShop;
                        pq.push({newDist, i});
                    }
                }
            }
        }

        // Reconstruct the shortest path
        if (dist[endShopID] == 999999) {
            cout << "No path found between Shop " << startShopID << " and Shop " << endShopID << "\n";
            return;
        }

        // Display the shortest path
        cout << "Shortest path from Shop " << startShopID << " to Shop " << endShopID << ":\n";
        int currentShop = endShopID;
        while (currentShop != startShopID) {
            cout << currentShop << " <- ";
            currentShop = prev[currentShop];
        }
        cout << startShopID << "\n";
        cout << "Total distance: " << dist[endShopID] << "\n";
    }
};

// Class to manage Customers in a queue
class CustomerQueue {
private:
    queue<Customer> customerQueue;

public:
    void addCustomer(int customerID, const string& name, int shopID) {
        customerQueue.push({customerID, name, shopID});
        cout << "Customer " << name << " added to the queue at Shop " << shopID << "\n";
    }

    void processCustomer() {
        if (!customerQueue.empty()) {
            Customer frontCustomer = customerQueue.front();
            cout << "Customer " << frontCustomer.name << " with ID: " << frontCustomer.customerID
                 << " processed and left the queue" << frontCustomer.shopID << "\n";
            customerQueue.pop();
        } else {
            cout << "Queue is empty \n";
        }
    }

    void displayQueue() {
        if (!customerQueue.empty()) {
            cout << "Current Queue: \n";
            queue<Customer> tempQueue = customerQueue;
            while (!tempQueue.empty()) {
                Customer frontCustomer = tempQueue.front();
                cout << "Customer " << frontCustomer.name << " (ID: " << frontCustomer.customerID
                     << ") at Shop " << frontCustomer.shopID << "\n";
                tempQueue.pop();
            }
        } else {
            cout << "Queue is empty.\n";
        }
    }
};

// Main function
int main() {
    int choice;
    ShopList shopList;
    Mall mall;
    CustomerQueue customerQueue;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Shop\n";
        cout << "2. Remove Shop\n";
        cout << "3. Display Shops\n";
        cout << "4. Add Path\n";
        cout << "5. Display Paths\n";
        cout << "6. Add Customer to Queue\n";
        cout << "7. Process Customer (Dequeue)\n";
        cout << "8. Display Queue\n";
        cout << "9. Find Shortest Path between Shops\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                int id;
                string name, category;
                cout << "Enter Shop ID: ";
                cin >> id;
                cin.ignore(); // to clear newline character
                cout << "Enter Shop Name: ";
                getline(cin, name);
                cout << "Enter Shop Category: ";
                getline(cin, category);
                shopList.addShop(id, name, category);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Shop ID to remove: ";
                cin >> id;
                shopList.removeShop(id);
                break;
            }
            case 3:
                shopList.displayShops();
                break;
            case 4: {
                int fromShopID, toShopID, distance;
                cout << "Enter From Shop ID: ";
                cin >> fromShopID;
                cout << "Enter To Shop ID: ";
                cin >> toShopID;
                cout << "Enter Path Distance: ";
                cin >> distance;
                mall.addPath(fromShopID, toShopID, distance);
                break;
            }
            case 5:
                mall.displayPaths();
                break;
            case 6: {
                int customerID, shopID;
                string name;
                cout << "Enter Customer ID: ";
                cin >> customerID;
                cout << "Enter Customer Name: ";
                cin.ignore();  // Ignore leftover newline character
                getline(cin, name);
                cout << "Enter Shop ID (where customer is located): ";
                cin >> shopID;
                customerQueue.addCustomer(customerID, name, shopID);
                break;
            }
            case 7:
                customerQueue.processCustomer();
                break;
            case 8:
                customerQueue.displayQueue();
                break;
            case 9: {
                int startShopID, endShopID;
                cout << "Enter Starting Shop ID: ";
                cin >> startShopID;
                cout << "Enter Ending Shop ID: ";
                cin >> endShopID;
                mall.shortestPath(startShopID, endShopID);
                break;
            }
            case 10:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 10);

    return 0;
}
