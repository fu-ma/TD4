#include "Sprite.hlsli"

float4 main(VSOutput input) : SV_TARGET
{
    return tex.Sample(smp, input.uv);
    
    ////�ȒP�Ȃڂ��������̂���
    //float w, h, levels;
    ////���̊֐��Ńe�N�X�`���̃T�C�Y��񂪎���
    //tex.GetDimensions(0, w, h, levels);
    ////�T�C�Y�����擾����ׂ̂͗̃s�N�Z���̏����擾���邽��
    ////��f���擾���āA�ڂ����̋����ipower�j�Ŋ���
    //float power = 9;
    ////��f�ړ��̃I�t�Z�b�g�l���Z�o
    //float dx = 1.0f / w;
    //float dy = 1.0f / h;
    //float4 ret = float4(0, 0, 0, 0);
    
    ////�ȉ��A��f���o�i3 * 3�j
    
    ////��̉�f
    ////ret += tex.Sample(smp, input.uv + float2(-2 * dx, -2 * dy)); //����
    //ret += tex.Sample(smp, input.uv + float2(0, -2 * dy)) * -1; //��
    ////ret += tex.Sample(smp, input.uv + float2(2 * dx, -2 * dy)); //�E��
    ////�����̉�f
    //ret += tex.Sample(smp, input.uv + float2(-2 * dx, 0)) * -1; //��
    //ret += tex.Sample(smp, input.uv) * 4; //����
    //ret += tex.Sample(smp, input.uv + float2(2 * dx, 0)) * -1; //�E
    ////���̉�f
    ////ret += tex.Sample(smp, input.uv + float2(-2 * dx, 2 * dy)); //����
    //ret += tex.Sample(smp, input.uv + float2(0, 2 * dy)) * -1; //��
    ////ret += tex.Sample(smp, input.uv + float2(2 * dx, 2 * dy)); //�E��
    
    ////�ڂ���
    ////�ڂ����̋����Ŋ����ĕԋp
    ////return ret / power;

    ////�G�b�W����
    ////��L�̉�f�̂����A�㉺���E�����̃e�[�u�����g�p
    ////�����������A�㉺���E��-1����
    
    ////���̌㔽�]
    //float Y = dot(ret.rgb, float3(0.299, 0.587, 0.114));
    ////�G�b�W���X�ɋ���
    //Y = pow(1.0f - Y, 10.0f);
    ////�]�v�ȗ֊s������
    //Y = step(0.2, Y);
    
    
    ////�M��p��
    //float2 sp = input.uv;
    //sp -= float2(0.5, 0.5);
    //float distPower = pow(length(sp), 0.06);
    //sp *= float2(distPower, distPower);
    //sp += float2(0.5, 0.5);
    //float4 Tex = tex.Sample(smp, sp);
    
    ////������
    //float Time = color.a * 40;
    
    //float sinv = sin(sp.y * 2 + Time * -0.1);
    //float steped = step(0.99, sinv * sinv);
    //Tex.rgb -= (1 - steped) * abs(sin(sp.y * 50.0f + Time * 1.0)) * 0.02;
    //Tex.rgb -= (1 - steped) * abs(sin(sp.y * 100.0f - Time * 2.0)) * 0.06;
    
    
    ////�r�l�b�g
    ////float2 samp = input.uv;
    ////float4 Tex3 = tex.Sample(smp, samp);
    ////float vignette = length(float2(0.5f, 0.5f) - input.uv);
    ////vignette = clamp(vignette - 0.2, 0, 1);
    ////Tex.rgb -= vignette;
    
    //return Tex;

}