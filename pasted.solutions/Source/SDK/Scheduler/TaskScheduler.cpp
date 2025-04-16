#include <thread>
#include <chrono>
#include <iostream>

#include <Global.h>
#include <Logging/Logger.h>
#include <SDK/Data/Offsets.h>
#include <SDK/Scheduler/TaskScheduler.h>
#include <SDK/DataModel/DataModel.h>
#include <SDK/VisualEngine/VisualEngine.h>

RBX::TaskScheduler::TaskScheduler() {
    Address = GetScheduler();
}

u64 RBX::TaskScheduler::GetScheduler() {
    return Driver->PRead<u64>(Driver->ImageAddress + Offsets::TaskScheduler::JobsPointer);
}

std::string RBX::TaskScheduler::GetJobName(u64 Job) {
    return Driver->ReadStr(Job + Offsets::TaskScheduler::JobName);
}

std::vector<u64> RBX::TaskScheduler::GetActiveJobs() {
    std::vector<u64> Jobs;

    u64 JobCount = Driver->PRead<u64>(Address - sizeof(u64));
    for (u64 i = 0; i <= JobCount; i += sizeof(std::shared_ptr<void*>)) {
        u64 Job = Driver->PRead<u64>(Address + i);

        if (Job == 0) {
            break;
        }

        if (GetJobName(Job).empty()) {
            continue;
        }

        Jobs.push_back(Job);
    }

    return Jobs;
}

std::vector<u64> RBX::TaskScheduler::GetJobs(const std::string& Name) {
    std::vector<u64> result;

    for (const u64& Job : GetActiveJobs()) {
        if (GetJobName(Job) == Name) {
            result.push_back(Job);
        }
    }

    return result;
}

u64 RBX::TaskScheduler::GetJobAddress(const std::string& Name) {
    for (u64& Job : GetActiveJobs()) {
        if (GetJobName(Job) == Name) {
            return Job;
        }
    }

    return 0;
}

void RBX::TaskScheduler::PrintJobs() {
    for (u64& job : GetActiveJobs()) {
        Logger::Log(Type::DEBUG, "Task Scheduler - Found job @ [0x%llx - %s]\n", job, GetJobName(job).c_str());
    }
}

u64 RBX::TaskScheduler::GetRenderView() {
    u64 RenderJob = GetJobAddress("RenderJob");

    return Driver->PRead<u64>(RenderJob + Offsets::TaskScheduler::RenderViewPointer);
}

RBX::DataModel RBX::TaskScheduler::GetDataModel() {
    u64 RenderJob = GetJobAddress("RenderJob");

    return RBX::DataModel(Driver->PRead<u64>(RenderJob + Offsets::TaskScheduler::DataModelPointer) + Offsets::TaskScheduler::DataModelOffset);
}

RBX::VisualEngine RBX::TaskScheduler::GetVisualEngine() {
    u64 RenderJob = GetJobAddress("RenderJob");

    u64 RenderView = Driver->PRead<u64>(RenderJob + Offsets::TaskScheduler::RenderViewPointer);
    return RBX::VisualEngine(Driver->PRead<u64>(RenderView + Offsets::TaskScheduler::VisualEnginePointer));
}

bool RBX::TaskScheduler::IsLoaded() {
    return GetActiveJobs().size() != 0;
}