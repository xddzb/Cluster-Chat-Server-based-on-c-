#定义一个 包含该目录下所有源文件的变量
aux_source_directory(. SRC_LIST)
#指定生成可执行文件
add_executable(ChatServer ${SRC_LIST})
#指定可执行文件链接时需要依赖的库文件
target_link_libraries(ChatServer muduo_net muduo_base pthread) 