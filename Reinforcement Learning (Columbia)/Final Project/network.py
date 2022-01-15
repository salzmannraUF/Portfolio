import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F


class Network(nn.Module):
    def __init__(self, env):
        super(Network, self).__init__()
        self.layer1 = nn.Linear(4, 256)
        self.layer2 = nn.Linear(256, 256)   # try 3 layers?
        self.layer3 = nn.Linear(256, 3)

    def forward(self, x, device):
        x = torch.from_numpy(x).float()
        x = F.relu(self.layer1(x))          # try relu
        x = F.relu(self.layer2(x))
        x = self.layer3(x)

        return x
