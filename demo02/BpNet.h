//
// Created by 钟昌明 on 2017/12/4.
//

#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define innode 2          //输入结点数
#define hidenode 4        //隐含结点数
#define hidelayer 1       //隐含层数
#define outnode 1         //输出结点数
#define learningRate 0.9  //学习速率，alpha

// -1~1 随机数产生器 ---
inline double get_11Random() {
    return ((2.0*(double)rand()/RAND_MAX) - 1);
}

// sigmoid 函数
inline double sigmoid(double x) {
    double ans = 1 / (1+exp(-x));
    return ans;
}

// 输入层节点
typedef struct tag_inputNode {
    double value;             //固定输入值
    vector<double> weight;    //面对第一层隐含层每个节点都有权值
    vector<double> wDeltaSum; //面对第一层隐含层每个节点权值的delta值累积
}inputNode;

// 输出层节点
typedef struct tag_outputNode {
    double value;     //节点当前值
    double delta;     //与正确输出值之间的delta值 (调整量)
    double rightout;  //正确输出值
    double bias;      //偏移量
    double bDeltaSum; //bias的delta值的累积，每个节点一个
} outputNode;

// 隐含层节点
typedef struct tag_hiddenNode {
    double value;             //节点当前值
    double delta;             //BP推导出的delta值 (调整量)
    double bias;              //偏移量
    double bDeltaSum;         //bias的delta值的累积，每个节点一个
    vector<double> weight;    //面对下一层（隐含层/输出层）每个节点都有权值
    vector<double> wDeltaSum; //weight的delta值的累积，面对下一层（隐含层/输出层）每个节点各自积累
} hiddenNode;

// 单个样本
typedef struct tag_sample {
    vector<double> in;  //样本输入
    vector<double> out; //样本输出
} sample;

// BP神经网络
class BpNet
{
public:
    BpNet();    //构造函数
    void forwardPropagationEpoc();  // 单个样本前向传播
    void backPropagationEpoc();     // 单个样本后向传播

    void training ( vector<sample> sampleGroup, double threshold);// 更新 weight, bias
    void predict  (vector<sample>& testGroup);                    // 神经网络预测
    void update   (int sampleNum);                                // 更新参数
    void initDeltaSum();

    void setInput ( vector<double> sampleIn);  // 设置学习样本输入
    void setOutput( vector<double> sampleOut); // 设置学习样本输出

public:
    double error;
    inputNode* inputLayer[innode];                // 输入层（仅一层）
    outputNode* outputLayer[outnode];             // 输出层（仅一层）
    hiddenNode* hiddenLayer[hidelayer][hidenode]; // 隐含层（可能有多层）
};

