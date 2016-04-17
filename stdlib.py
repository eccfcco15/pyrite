import llvmlite.binding
from llvmlite import ir
from llvmlite.ir import Constant, IntType, DoubleType, ArrayType

list_node_t   = ir.IdentifiedStructType(None, 'struct.list_node')
list_struct_t = ir.IdentifiedStructType(None, 'struct.list')

class StdLib:
    def __init__(self, lib_file, module):
        self.std_mod = None
        self.func_dict = {
                'list_init':
                ir.Function(module,
                    ir.FunctionType(ir.PointerType(list_struct_t), tuple()),
                    'list_init')
                }
        '''
        with open(lib_file, 'r') as std_lib_ir:
            llvm_ir = std_lib_ir.read()
            self.std_mod = llvmlite.binding.parse_assembly(llvm_ir)
            for func in self.std_mod.functions:
                self.func_dict[func.name] = self.std_mod.get_function(func.name)
                print llvmlite.binding.address_of_symbol(func.name)#self.func_dict[func.name]
        '''
    def get_funcs(self):
        return self.func_dict



#stdLibModule = StdLib('stdlib/stdlib.ll')


