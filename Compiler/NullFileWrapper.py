
class  NullFileWrapper:
    def __init__(self, file_handle):
        self.file_handle = file_handle

    def write(self, data):
        if self.file_handle is not None:
            self.file_handle.write(data)