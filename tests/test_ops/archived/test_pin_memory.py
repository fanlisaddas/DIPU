import torch
import torch_dipu

a = torch.tensor([1,2,3])
assert not a.is_pinned()

b = a.pin_memory()
assert b.is_pinned()
assert torch.allclose(a, b)
assert a.data_ptr() != b.data_ptr()

c = b.pin_memory()
assert c.is_pinned()
assert torch.allclose(a, c)
assert b.data_ptr() == c.data_ptr()