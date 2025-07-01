#include <iostream>
#include <string>
#include <memory>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <Eigen/Dense>

#include "utils.h"
#include "scancontext.h"

using std::cout;
using std::endl;
using std::string;
using namespace Eigen;
using namespace utils;
using SC = scancontext::Scancontext;

auto main(void) -> int 
{
    // Initialize random seed for reproducibility
    std::srand((unsigned int) time(0));

    // Descriptor dimensions
    int num_rings{40}; 
    int num_sectors{120};
    double loop_threshold = 0.15;

    // Display config
    cout << "Descriptor Config: " << endl;
    disp(num_rings);
    disp(num_sectors);
    lc;

    // Base constant to avoid negative values in descriptors
    MatrixXd sc_const = MatrixXd::Constant(num_rings, num_sectors, 2.0);

    // Create a reference descriptor (e.g., current scan)
    MatrixXd sc_ref_eig = MatrixXd::Random(num_rings, num_sectors) + sc_const;
    scancontext::Descriptor sc_ref = eigen2desc(sc_ref_eig);

    // Simulate multiple test descriptors
    for (int i = 0; i < 5; ++i) {
        MatrixXd sc_test_eig = MatrixXd::Random(num_rings, num_sectors) + sc_const;
        scancontext::Descriptor sc_test = eigen2desc(sc_test_eig);

        // Calculate descriptor distance
        float dist = scancontext::distance(sc_ref, sc_test);

        // Output result
        cout << "Test scan " << i 
             << " → distance: " << dist 
             << " → ";

        if (dist < loop_threshold) {
            cout << "🔁 Loop closure detected!" << endl;
        } else {
            cout << "No loop closure." << endl;
        }
    }

    return 0;
}
