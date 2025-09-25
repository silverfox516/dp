#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <map>

// Abstract Handler
class RequestHandler {
protected:
    std::unique_ptr<RequestHandler> nextHandler;

public:
    virtual ~RequestHandler() = default;

    void setNext(std::unique_ptr<RequestHandler> handler) {
        nextHandler = std::move(handler);
    }

    virtual void handleRequest(const std::string& request) {
        if (canHandle(request)) {
            processRequest(request);
        } else if (nextHandler) {
            std::cout << "Passing request to next handler..." << std::endl;
            nextHandler->handleRequest(request);
        } else {
            std::cout << "❌ No handler found for request: " << request << std::endl;
        }
    }

protected:
    virtual bool canHandle(const std::string& request) = 0;
    virtual void processRequest(const std::string& request) = 0;
    virtual std::string getHandlerName() const = 0;
};

// Example 1: Authentication and Authorization Chain
class AuthenticationHandler : public RequestHandler {
private:
    std::string validUser = "admin";
    std::string validPassword = "password123";

protected:
    bool canHandle(const std::string& request) override {
        return request.find("auth:") == 0;
    }

    void processRequest(const std::string& request) override {
        std::cout << "🔐 " << getHandlerName() << " processing: " << request << std::endl;

        // Extract credentials from request
        std::string credentials = request.substr(5); // Remove "auth:"
        size_t colonPos = credentials.find(':');

        if (colonPos != std::string::npos) {
            std::string user = credentials.substr(0, colonPos);
            std::string password = credentials.substr(colonPos + 1);

            if (user == validUser && password == validPassword) {
                std::cout << "✅ Authentication successful for user: " << user << std::endl;
            } else {
                std::cout << "❌ Authentication failed!" << std::endl;
            }
        } else {
            std::cout << "❌ Invalid credentials format!" << std::endl;
        }
    }

    std::string getHandlerName() const override {
        return "Authentication Handler";
    }
};

class AuthorizationHandler : public RequestHandler {
private:
    std::vector<std::string> authorizedActions = {"read", "write", "delete"};

protected:
    bool canHandle(const std::string& request) override {
        return request.find("authorize:") == 0;
    }

    void processRequest(const std::string& request) override {
        std::cout << "🛡️ " << getHandlerName() << " processing: " << request << std::endl;

        std::string action = request.substr(10); // Remove "authorize:"

        auto it = std::find(authorizedActions.begin(), authorizedActions.end(), action);
        if (it != authorizedActions.end()) {
            std::cout << "✅ Action '" << action << "' is authorized" << std::endl;
        } else {
            std::cout << "❌ Action '" << action << "' is not authorized!" << std::endl;
        }
    }

    std::string getHandlerName() const override {
        return "Authorization Handler";
    }
};

class ValidationHandler : public RequestHandler {
protected:
    bool canHandle(const std::string& request) override {
        return request.find("validate:") == 0;
    }

    void processRequest(const std::string& request) override {
        std::cout << "✔️ " << getHandlerName() << " processing: " << request << std::endl;

        std::string data = request.substr(9); // Remove "validate:"

        // Simple validation rules
        if (data.empty()) {
            std::cout << "❌ Validation failed: Empty data!" << std::endl;
        } else if (data.length() < 3) {
            std::cout << "❌ Validation failed: Data too short!" << std::endl;
        } else if (data.find_first_of("!@#$%^&*") != std::string::npos) {
            std::cout << "❌ Validation failed: Invalid characters!" << std::endl;
        } else {
            std::cout << "✅ Validation successful for: " << data << std::endl;
        }
    }

    std::string getHandlerName() const override {
        return "Validation Handler";
    }
};

// Example 2: Support Ticket System
enum class TicketPriority {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3,
    CRITICAL = 4
};

struct SupportTicket {
    int id;
    std::string description;
    TicketPriority priority;
    std::string category;

    std::string toString() const {
        std::string priorityStr;
        switch (priority) {
            case TicketPriority::LOW: priorityStr = "LOW"; break;
            case TicketPriority::MEDIUM: priorityStr = "MEDIUM"; break;
            case TicketPriority::HIGH: priorityStr = "HIGH"; break;
            case TicketPriority::CRITICAL: priorityStr = "CRITICAL"; break;
        }
        return "Ticket #" + std::to_string(id) + " [" + priorityStr + "] " +
               category + ": " + description;
    }
};

class SupportHandler {
protected:
    std::unique_ptr<SupportHandler> nextHandler;

public:
    virtual ~SupportHandler() = default;

    void setNext(std::unique_ptr<SupportHandler> handler) {
        nextHandler = std::move(handler);
    }

    virtual void handleTicket(const SupportTicket& ticket) {
        if (canHandle(ticket)) {
            processTicket(ticket);
        } else if (nextHandler) {
            std::cout << "Escalating to next level..." << std::endl;
            nextHandler->handleTicket(ticket);
        } else {
            std::cout << "❌ No handler available for ticket: " << ticket.toString() << std::endl;
        }
    }

protected:
    virtual bool canHandle(const SupportTicket& ticket) = 0;
    virtual void processTicket(const SupportTicket& ticket) = 0;
    virtual std::string getHandlerLevel() const = 0;
};

class Level1SupportHandler : public SupportHandler {
protected:
    bool canHandle(const SupportTicket& ticket) override {
        return ticket.priority <= TicketPriority::MEDIUM &&
               (ticket.category == "General" || ticket.category == "Account");
    }

    void processTicket(const SupportTicket& ticket) override {
        std::cout << "🎧 " << getHandlerLevel() << " handling: " << ticket.toString() << std::endl;
        std::cout << "   Providing basic troubleshooting steps..." << std::endl;
        std::cout << "   ✅ Ticket resolved by Level 1 Support" << std::endl;
    }

    std::string getHandlerLevel() const override {
        return "Level 1 Support";
    }
};

class Level2SupportHandler : public SupportHandler {
protected:
    bool canHandle(const SupportTicket& ticket) override {
        return ticket.priority <= TicketPriority::HIGH &&
               (ticket.category == "Technical" || ticket.category == "Software");
    }

    void processTicket(const SupportTicket& ticket) override {
        std::cout << "🔧 " << getHandlerLevel() << " handling: " << ticket.toString() << std::endl;
        std::cout << "   Performing advanced diagnostics..." << std::endl;
        std::cout << "   ✅ Ticket resolved by Level 2 Support" << std::endl;
    }

    std::string getHandlerLevel() const override {
        return "Level 2 Support";
    }
};

class Level3SupportHandler : public SupportHandler {
protected:
    bool canHandle(const SupportTicket& ticket) override {
        return ticket.priority == TicketPriority::CRITICAL ||
               ticket.category == "Security" || ticket.category == "Infrastructure";
    }

    void processTicket(const SupportTicket& ticket) override {
        std::cout << "🚨 " << getHandlerLevel() << " handling: " << ticket.toString() << std::endl;
        std::cout << "   Engaging senior engineers..." << std::endl;
        std::cout << "   ✅ Critical issue handled by Level 3 Support" << std::endl;
    }

    std::string getHandlerLevel() const override {
        return "Level 3 Support";
    }
};

// Example 3: HTTP Request Processing Chain
struct HTTPRequest {
    std::string method;
    std::string path;
    std::string userAgent;
    std::string clientIP;
    std::map<std::string, std::string> headers;

    std::string toString() const {
        return method + " " + path + " from " + clientIP;
    }
};

class HTTPHandler {
protected:
    std::unique_ptr<HTTPHandler> nextHandler;

public:
    virtual ~HTTPHandler() = default;

    void setNext(std::unique_ptr<HTTPHandler> handler) {
        nextHandler = std::move(handler);
    }

    virtual bool handle(HTTPRequest& request) {
        if (shouldHandle(request)) {
            return processRequest(request);
        } else if (nextHandler) {
            return nextHandler->handle(request);
        }
        return false;
    }

protected:
    virtual bool shouldHandle(const HTTPRequest& request) = 0;
    virtual bool processRequest(HTTPRequest& request) = 0;
    virtual std::string getHandlerName() const = 0;
};

class RateLimitHandler : public HTTPHandler {
private:
    std::map<std::string, int> requestCounts;
    int maxRequestsPerMinute = 100;

protected:
    bool shouldHandle(const HTTPRequest& request) override {
        return true; // Always check rate limiting
    }

    bool processRequest(HTTPRequest& request) override {
        std::cout << "🚦 " << getHandlerName() << " checking: " << request.toString() << std::endl;

        requestCounts[request.clientIP]++;

        if (requestCounts[request.clientIP] > maxRequestsPerMinute) {
            std::cout << "   ❌ Rate limit exceeded for IP: " << request.clientIP << std::endl;
            return false; // Block the request
        }

        std::cout << "   ✅ Rate limit OK (" << requestCounts[request.clientIP]
                  << "/" << maxRequestsPerMinute << ")" << std::endl;
        return true; // Continue to next handler
    }

    std::string getHandlerName() const override {
        return "Rate Limit Handler";
    }
};

class AuthenticationHTTPHandler : public HTTPHandler {
protected:
    bool shouldHandle(const HTTPRequest& request) override {
        return request.path.find("/api/") == 0 || request.path.find("/admin/") == 0;
    }

    bool processRequest(HTTPRequest& request) override {
        std::cout << "🔑 " << getHandlerName() << " checking: " << request.toString() << std::endl;

        auto authHeader = request.headers.find("Authorization");
        if (authHeader == request.headers.end()) {
            std::cout << "   ❌ Missing Authorization header" << std::endl;
            return false;
        }

        if (authHeader->second == "Bearer valid_token") {
            std::cout << "   ✅ Authentication successful" << std::endl;
            return true;
        } else {
            std::cout << "   ❌ Invalid authentication token" << std::endl;
            return false;
        }
    }

    std::string getHandlerName() const override {
        return "Authentication Handler";
    }
};

class CacheHandler : public HTTPHandler {
private:
    std::map<std::string, std::string> cache;

protected:
    bool shouldHandle(const HTTPRequest& request) override {
        return request.method == "GET";
    }

    bool processRequest(HTTPRequest& request) override {
        std::cout << "💾 " << getHandlerName() << " checking: " << request.toString() << std::endl;

        auto it = cache.find(request.path);
        if (it != cache.end()) {
            std::cout << "   ✅ Cache hit for: " << request.path << std::endl;
            std::cout << "   Returning cached response: " << it->second << std::endl;
            return false; // Don't continue processing, return cached response
        } else {
            std::cout << "   ❌ Cache miss for: " << request.path << std::endl;
            // Simulate adding to cache
            cache[request.path] = "Cached response for " + request.path;
            return true; // Continue processing
        }
    }

    std::string getHandlerName() const override {
        return "Cache Handler";
    }
};

class RouteHandler : public HTTPHandler {
protected:
    bool shouldHandle(const HTTPRequest& request) override {
        return true; // Always handle as the final handler
    }

    bool processRequest(HTTPRequest& request) override {
        std::cout << "🛣️ " << getHandlerName() << " processing: " << request.toString() << std::endl;

        if (request.path == "/") {
            std::cout << "   📄 Serving home page" << std::endl;
        } else if (request.path.find("/api/") == 0) {
            std::cout << "   🔌 Processing API request" << std::endl;
        } else if (request.path.find("/static/") == 0) {
            std::cout << "   📁 Serving static file" << std::endl;
        } else {
            std::cout << "   ❌ 404 - Page not found" << std::endl;
            return false;
        }

        std::cout << "   ✅ Request processed successfully" << std::endl;
        return true;
    }

    std::string getHandlerName() const override {
        return "Route Handler";
    }
};

// Functional Chain of Responsibility using std::function
template<typename Request>
class FunctionalChain {
private:
    using Handler = std::function<bool(const Request&)>;
    std::vector<Handler> handlers;

public:
    void addHandler(Handler handler) {
        handlers.push_back(handler);
    }

    bool process(const Request& request) {
        for (const auto& handler : handlers) {
            if (handler(request)) {
                return true; // Request handled
            }
        }
        return false; // No handler processed the request
    }
};

int main() {
    std::cout << "=== Chain of Responsibility Pattern Demo ===" << std::endl;

    // Example 1: Authentication Chain
    std::cout << "\n1. Authentication and Authorization Chain:" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    auto authHandler = std::make_unique<AuthenticationHandler>();
    auto authzHandler = std::make_unique<AuthorizationHandler>();
    auto validationHandler = std::make_unique<ValidationHandler>();

    // Build the chain
    authHandler->setNext(std::move(authzHandler));
    // Note: In a real implementation, you'd properly chain these
    // This is simplified for demonstration

    std::vector<std::string> requests = {
        "auth:admin:password123",
        "auth:user:wrongpassword",
        "authorize:read",
        "authorize:execute",
        "validate:ValidData123",
        "validate:x",
        "validate:",
        "unknown:request"
    };

    for (const auto& request : requests) {
        std::cout << "\nProcessing request: " << request << std::endl;
        if (request.find("auth:") == 0) {
            authHandler->handleRequest(request);
        } else {
            // Create individual handlers for this demo
            if (request.find("authorize:") == 0) {
                AuthorizationHandler authzHandler;
                authzHandler.handleRequest(request);
            } else if (request.find("validate:") == 0) {
                ValidationHandler validationHandler;
                validationHandler.handleRequest(request);
            } else {
                std::cout << "❌ No handler found for request: " << request << std::endl;
            }
        }
    }

    // Example 2: Support Ticket System
    std::cout << "\n\n2. Support Ticket System:" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    auto level1 = std::make_unique<Level1SupportHandler>();
    auto level2 = std::make_unique<Level2SupportHandler>();
    auto level3 = std::make_unique<Level3SupportHandler>();

    // Build the support chain
    level1->setNext(std::move(level2));
    level1->setNext(std::move(level3)); // This would properly chain in real implementation

    std::vector<SupportTicket> tickets = {
        {1, "Password reset request", TicketPriority::LOW, "Account"},
        {2, "Software installation issue", TicketPriority::MEDIUM, "Technical"},
        {3, "Server down", TicketPriority::CRITICAL, "Infrastructure"},
        {4, "Security breach detected", TicketPriority::CRITICAL, "Security"},
        {5, "General inquiry", TicketPriority::LOW, "General"}
    };

    // Process each ticket through the appropriate handler
    std::vector<std::unique_ptr<SupportHandler>> handlers;
    handlers.push_back(std::make_unique<Level1SupportHandler>());
    handlers.push_back(std::make_unique<Level2SupportHandler>());
    handlers.push_back(std::make_unique<Level3SupportHandler>());

    for (const auto& ticket : tickets) {
        std::cout << "\nNew ticket: " << ticket.toString() << std::endl;
        bool handled = false;
        for (auto& handler : handlers) {
            Level1SupportHandler* l1 = dynamic_cast<Level1SupportHandler*>(handler.get());
            Level2SupportHandler* l2 = dynamic_cast<Level2SupportHandler*>(handler.get());
            Level3SupportHandler* l3 = dynamic_cast<Level3SupportHandler*>(handler.get());

            if (l1 && (ticket.priority <= TicketPriority::MEDIUM &&
                      (ticket.category == "General" || ticket.category == "Account"))) {
                l1->handleTicket(ticket);
                handled = true;
                break;
            } else if (l2 && (ticket.priority <= TicketPriority::HIGH &&
                             (ticket.category == "Technical" || ticket.category == "Software"))) {
                l2->handleTicket(ticket);
                handled = true;
                break;
            } else if (l3 && (ticket.priority == TicketPriority::CRITICAL ||
                             ticket.category == "Security" || ticket.category == "Infrastructure")) {
                l3->handleTicket(ticket);
                handled = true;
                break;
            }
        }
        if (!handled) {
            std::cout << "❌ No handler available for this ticket type" << std::endl;
        }
    }

    // Example 3: HTTP Request Processing
    std::cout << "\n\n3. HTTP Request Processing Chain:" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    auto rateLimiter = std::make_unique<RateLimitHandler>();
    auto httpAuth = std::make_unique<AuthenticationHTTPHandler>();
    auto cache = std::make_unique<CacheHandler>();
    auto router = std::make_unique<RouteHandler>();

    // Build HTTP processing chain
    rateLimiter->setNext(std::move(httpAuth));
    // Simplified chaining for demo

    std::vector<HTTPRequest> httpRequests = {
        {"GET", "/", "Mozilla/5.0", "192.168.1.1", {}},
        {"GET", "/api/users", "curl/7.68.0", "192.168.1.2", {{"Authorization", "Bearer valid_token"}}},
        {"GET", "/api/data", "PostmanRuntime/7.26.8", "192.168.1.3", {}},
        {"POST", "/api/upload", "Chrome/91.0", "192.168.1.1", {{"Authorization", "Bearer invalid_token"}}},
        {"GET", "/static/style.css", "Mozilla/5.0", "192.168.1.4", {}}
    };

    for (auto& request : httpRequests) {
        std::cout << "\nProcessing HTTP request: " << request.toString() << std::endl;

        // Simulate the chain processing
        RateLimitHandler rateLimitHandler;
        if (rateLimitHandler.handle(request)) {
            AuthenticationHTTPHandler authHandler;
            if (authHandler.handle(request)) {
                CacheHandler cacheHandler;
                if (cacheHandler.handle(request)) {
                    RouteHandler routeHandler;
                    routeHandler.handle(request);
                }
            }
        }
    }

    // Example 4: Functional Chain of Responsibility
    std::cout << "\n\n4. Functional Chain of Responsibility:" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    FunctionalChain<std::string> functionalChain;

    // Add lambda handlers
    functionalChain.addHandler([](const std::string& request) -> bool {
        if (request.find("email:") == 0) {
            std::string email = request.substr(6);
            std::cout << "📧 Email handler processing: " << email << std::endl;
            if (email.find("@") != std::string::npos) {
                std::cout << "   ✅ Valid email format" << std::endl;
                return true;
            } else {
                std::cout << "   ❌ Invalid email format" << std::endl;
                return false;
            }
        }
        return false;
    });

    functionalChain.addHandler([](const std::string& request) -> bool {
        if (request.find("phone:") == 0) {
            std::string phone = request.substr(6);
            std::cout << "📞 Phone handler processing: " << phone << std::endl;
            if (phone.length() >= 10) {
                std::cout << "   ✅ Valid phone number" << std::endl;
                return true;
            } else {
                std::cout << "   ❌ Invalid phone number" << std::endl;
                return false;
            }
        }
        return false;
    });

    std::vector<std::string> functionalRequests = {
        "email:user@example.com",
        "email:invalid-email",
        "phone:1234567890",
        "phone:123",
        "unknown:request"
    };

    for (const auto& request : functionalRequests) {
        std::cout << "\nProcessing: " << request << std::endl;
        if (!functionalChain.process(request)) {
            std::cout << "❌ No handler found for: " << request << std::endl;
        }
    }

    // Benefits summary
    std::cout << "\n\n5. Chain of Responsibility Benefits:" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "✓ Decouples sender from receivers" << std::endl;
    std::cout << "✓ Simplifies object interconnections" << std::endl;
    std::cout << "✓ Adds flexibility in assigning responsibilities" << std::endl;
    std::cout << "✓ Easy to add or change handlers" << std::endl;
    std::cout << "✓ Follows single responsibility principle" << std::endl;
    std::cout << "✓ Supports dynamic handler chains" << std::endl;
    std::cout << "✓ Can be implemented functionally with lambdas" << std::endl;

    return 0;
}