
Filter_table_datatype = {
    [1] = 0,
    [2] = 1,
    [3] = 0,
    [4] = 0,
    [5] = 1,
    [6] = 1,
    [7] = 1,
    [8] = 0,
    [9] = 1,
    [10] = 0,
    [11] = 1,    
}

Filter_res = {}

function Datatype_filter(datatype)
    local length = #datatype
    local sum = 0
    local index = 1
    Filter_res = {}
    for i=1,length do
        if(Filter_table_datatype[i] == 1)
        then
            print(Filter_table_datatype[i], "is fitered")
        else
            print("append res, index: ", index, "datatype: ", i)
            table.insert(Filter_res, i)
            index = index + 1
        end
        sum = sum + datatype[i]
    end
    -- return {1, 2, 3}

    -- lua 回调c++接口
    -- FilterResProc(Filter_res)
    --返回结果数组的长度, c++代码依据长度获取结果
    -- return Filter_res
end


-- local datatype = {1, 2, 3}
-- local res = Datatype_filter(datatype)
-- print(res)
-- print(#res, res[1], res[2])