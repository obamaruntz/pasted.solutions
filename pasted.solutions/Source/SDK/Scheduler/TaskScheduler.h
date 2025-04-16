#pragma once

#include <vector>
#include <string>

#include <Framework.h>
#include <SDK/Instance.h>
#include <SDK/DataModel/DataModel.h>
#include <SDK/VisualEngine/VisualEngine.h>

//#include "sdk/datamodel/datamodel_t.h"
//#include "sdk/visualengine/visualengine_t.h"

namespace RBX {
    class TaskScheduler {
    public:
        u64 Address;
        TaskScheduler();
        ~TaskScheduler() = default;

        u64 GetScheduler();
        bool IsLoaded();

        u64 GetJobAddress(const std::string& Name);
        std::string GetJobName(u64 Job);
        std::vector<u64> GetActiveJobs();
        std::vector<u64> GetJobs(const std::string& Name);

        void PrintJobs();

        u64 GetRenderView();
        RBX::DataModel GetDataModel();
        RBX::VisualEngine GetVisualEngine();
    };
}