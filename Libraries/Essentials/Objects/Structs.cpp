#pragma once

namespace gm {

    struct ob_data {
        int id;
        int ob_type;
    };
    
    struct Connection {
        int ob_id;
        std::string signal;
    };
}