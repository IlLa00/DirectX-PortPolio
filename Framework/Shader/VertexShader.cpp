#include "framework.h"

unordered_map<wstring, VertexShader*> VertexShader::shader_data;

void VertexShader::CreateInputLayout()
{
    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
        0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
        ,{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    D3D11_INPUT_ELEMENT_DESC layouts_UV[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
        0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"UV", 0, DXGI_FORMAT_R32G32_FLOAT,
        0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layoutSize;

    switch (type)
    {
    case 0: 
        layoutSize = ARRAYSIZE(layouts);
        Device::Get()->GetDevice()->CreateInputLayout(layouts, layoutSize, vertex_blob->GetBufferPointer(),
            vertex_blob->GetBufferSize(), &input_layout);
        break;
    case 1:
        layoutSize = ARRAYSIZE(layouts_UV);
        Device::Get()->GetDevice()->CreateInputLayout(layouts_UV, layoutSize, vertex_blob->GetBufferPointer(),
            vertex_blob->GetBufferSize(), &input_layout);
        break;
    }
}

void VertexShader::CreateInputLayoutByPos()
{
    D3DReflect(vertex_blob->GetBufferPointer(), vertex_blob->GetBufferSize(),
        IID_ID3D11ShaderReflection, (void**)&reflection);
    
    D3D11_SHADER_DESC shader_desc;
    reflection->GetDesc(&shader_desc);

    vector<D3D11_INPUT_ELEMENT_DESC> input_layouts;

    for (UINT i = 0; i < shader_desc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        reflection->GetInputParameterDesc(i, &paramDesc);

        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName = paramDesc.SemanticName;
        elementDesc.SemanticIndex = paramDesc.SemanticIndex;
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;

        if (paramDesc.Mask == 1)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask < 4)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask < 8)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (paramDesc.Mask < 16)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }

        string temp = paramDesc.SemanticName;
        if (temp == "POSITION")
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

        input_layouts.push_back(elementDesc);
    }

    DEVICE->CreateInputLayout(input_layouts.data(), input_layouts.size(),
        vertex_blob->GetBufferPointer(), vertex_blob->GetBufferSize(), &input_layout);
}
VertexShader::VertexShader(wstring file_loc, UINT type, DWORD flags)
    : type(type)
{
    D3DCompileFromFile(file_loc.c_str(), nullptr, nullptr, "VS",
        "vs_5_0", flags, 0, &vertex_blob, nullptr);

    DEVICE->CreateVertexShader(vertex_blob->GetBufferPointer(),
        vertex_blob->GetBufferSize(), nullptr, &VS);

    if (type == 2)
        CreateInputLayoutByPos();
    else
        CreateInputLayout();
}

VertexShader::~VertexShader()
{
    Release();
}

void VertexShader::Release()
{
    VS->Release();
    input_layout->Release();
}

void VertexShader::Set()
{
    DVC->IASetInputLayout(input_layout);
    DVC->VSSetShader(VS, nullptr, 0);
}


VertexShader* VertexShader::GetInstance(wstring file_loc, UINT type)
{
    if (shader_data.count(file_loc) > 0) 
        return shader_data[file_loc]; 

    VertexShader* instance = new VertexShader(file_loc, type);
    shader_data[file_loc] = instance; 
    return instance;
}

void VertexShader::Delete()
{
   
}
