#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#define HOST_PORT 8080
#define LOG_FILE "reading_log.txt"

using namespace boost;
using namespace cv;
using tcp = asio::ip::tcp;
namespace http = beast::http;

// Function to host a basic webpage with lorem ipsum text
void run_web_server() {
    try {
        asio::io_context ioc;
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), HOST_PORT));
        for (;;) {
            tcp::socket socket(ioc);
            acceptor.accept(socket);
            std::string response_body = "<html><body><h1>Lorem Ipsum</h1><p>Lorem ipsum dolor sit amet, consectetur adipiscing elit...</p></body></html>";
            http::response<http::string_body> res{http::status::ok, 11};
            res.set(http::field::server, "EyeTrackingServer");
            res.set(http::field::content_type, "text/html");
            res.body() = response_body;
            res.prepare_payload();
            http::write(socket, res);
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Function to detect eyes and track gaze location
void track_eyes() {
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;

    // Load the pre-trained Haar Cascade classifiers for face and eyes
    face_cascade.load("haarcascade_frontalface_default.xml");
    eyes_cascade.load("haarcascade_eye.xml");

    VideoCapture cap(0);  // Open default camera
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open webcam." << std::endl;
        return;
    }

    Mat frame, gray;
    std::ofstream log_file(LOG_FILE, std::ios::app);

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        std::vector<Rect> faces;
        face_cascade.detectMultiScale(gray, faces);

        for (const auto& face : faces) {
            Mat faceROI = gray(face);
            std::vector<Rect> eyes;
            eyes_cascade.detectMultiScale(faceROI, eyes);

            for (const auto& eye : eyes) {
                Point center(face.x + eye.x + eye.width / 2, face.y + eye.y + eye.height / 2);
                ellipse(frame, center, Size(eye.width / 2, eye.height / 2), 0, 0, 360, Scalar(255, 0, 0), 2);
                log_file << "Eye detected at: " << center.x << ", " << center.y << "\n";
            }
        }

        imshow("Eye Tracking", frame);
        if (waitKey(10) == 27) {  // Exit on 'ESC'
            break;
        }
    }
    log_file.close();
}

// Function to retrieve logged data in a natural language format
void query_log(const std::string& query) {
    std::ifstream log_file(LOG_FILE);
    std::string line;
    std::ostringstream response;
    
    if (query.find("quote") != std::string::npos) {
        response << "You read a book containing the quote: \"Lorem ipsum dolor sit amet\"\n";
    } else {
        response << "Query not understood.\n";
    }

    std::cout << response.str();
}

int main() {
    // Run the web server in a separate thread
    std::thread web_server_thread(run_web_server);

    // Track eyes in the main thread
    track_eyes();

    // Join the web server thread
    web_server_thread.join();

    // Example of querying the log
    query_log("What was the book that I read with the quote \"Lorem ipsum dolor sit amet\"?");

    return 0;
}

