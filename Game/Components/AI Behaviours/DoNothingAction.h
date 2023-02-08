#pragma once
#include "Core/Components/AI/Behaviour.h"

class DoNothingAction :
    public Behaviour
{
public:
    void Act() override;
};