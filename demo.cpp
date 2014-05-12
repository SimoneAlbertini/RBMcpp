/* 
 * File:   demo.cpp
 * Author: Simone Albertini
 * 
 * albertini.simone@gmail.com
 * http://www.dicom.uninsubria.it/~simone.albertini/
 * 
 */

#include <fstream>
#include <iomanip>
#include <opencv2/highgui/highgui.hpp>

#include "utils/ConfusionMatrix.h"
#include "utils/SVM.h"
#include "RBMcpp/rbmUtils.h"
#include "RBMcpp/RBMglu.h"

using namespace artelab;
using std::string;
using std::cout;
using std::endl;
using std::flush;
using std::setw;
using std::left;
using std::right;
using std::vector;

void show_weights_histogram(RBM* rbm, string filename="weight_hist.png")
{
    float min=0, max=0;
    cv::Mat hist = artelab::weight_distribution(rbm, 20, min, max);
    cv::Mat image = artelab::save_and_load_histogram_image(hist, filename);
    cv::imshow("Weight distribution", image);
}

void print_header()
{
    cout << setw(5) << left << "Epoch" << setw(3) << " | "
         << setw(10) << left << "Train mse" <<  setw(3) << " | "
         << setw(10) << left << "Val mse" << setw(3) <<  " | "
         << setw(10) << left << "Train F" << setw(3) <<  " | "
         << setw(10) << left << "Val F" << setw(3) <<  " | "
         << setw(10) << left << "diff " << endl;
}

void print_info(RBM* rbm, const int epoch, cv::Mat& train, cv::Mat& val)
{
    float mset = artelab::average_mse(rbm, train);
    float msev = artelab::average_mse(rbm, val);
    float ft = rbm->avg_free_energy(train);
    float fv = rbm->avg_free_energy(val);
    float diff = ft-fv;
    cout << setw(5) << right << epoch << setw(3) << " | " 
         << setw(10) << left << mset << setw(3) << " | " 
         << setw(10) << left << msev << setw(3) << " | " 
         << setw(10) << left << ft << setw(3) << " | " 
         << setw(10) << left << fv << setw(3) << " | " 
         << setw(10) << left << (diff>0? diff : -diff) << setw(3) << endl;
}

void load_data(string filename, cv::Mat& patterns, cv::Mat& labels)
{
    cv::FileStorage fs;
    fs.open(filename, cv::FileStorage::READ);
    fs["data"] >> patterns;
    fs["labels"] >> labels;
    fs.release();
}

int main(int argc, char** argv) 
{
    // load data
    cv::Mat train, train_lab, val, val_lab, test, test_lab;
    load_data("traindata.mat", train, train_lab);
    load_data("validationdata.mat", val, val_lab);
    load_data("testdata.mat", test, test_lab);
    
    cout << "Data split" << endl;
    cout << "Train data: " << train.rows << "x" << train.cols << endl;
    cout << "Validation data: " << val.rows << "x" << val.cols << endl;
    cout << "Test data: " << test.rows << "x" << test.cols << endl << endl;
    
    // Train RBM
    cout << "Training RBM" << endl << endl;
    const int num_hid = 200;
    const int epochs = 10;
    RBMglu::TrainParams params;
    params.learning_rate = 0.02;
    params.batch_size = 10;
    params.momentum = 0.5;
    params.iterations = train.rows / params.batch_size * epochs;
    params.weight_decay = RBMglu::TrainParams::L2_WEIGHT_DECAY;
    params.wd_delta = 0.0002;
    
    RBMglu rbm(train.cols, num_hid);
    rbm.set_seed(345)
       .set_datasets(train, val)
       .set_step_type(RBM::EPOCHS)
       .set_train_params(params);
    
    cout << rbm.description() << endl << endl;
    
    int epoch = 0;
    print_header();
    while(++epoch && rbm.step())
    {
        print_info(&rbm, epoch, train, val);
        
        artelab::show_bases(&rbm, cv::Size(16,16));
        show_weights_histogram(&rbm);
        cv::waitKey(epoch==1? 10000 : 1000);
        
        if(epoch == 5)
        {
            params.learning_rate = 0.001;
            params.momentum = 0.9;
            rbm.set_train_params(params);
        }
    }
    print_info(&rbm, epoch, train, val);
    artelab::show_bases(&rbm, cv::Size(16,16));
    cout << "RBM succesfully trained; press any key to continue... " << flush;
    cv::waitKey();
    cout << endl;
    
    // Classification
    cout << "Classification using the RBM features" << endl;
    cv::Mat train_feat, test_feat;
    
    // Train classifier
    artelab::feature_patterns(&rbm, train, train_feat);
    
    cv::SVMParams svm_params;
    svm_params.kernel_type = cv::SVM::LINEAR;
    svm_params.svm_type = cv::SVM::C_SVC;
    const int kfold = 5;
    
    SVM svm(svm_params);
    cout << "Training linear SVM... " << flush;
    svm.train(train_feat, train_lab, kfold);
    cout << "Done!" << endl;
    
    // Check train
    cv::Mat predictions;
    ConfusionMatrix conf(10);
    
    svm.predict(train_feat, predictions);
    conf.add(predictions, train_lab);
    cout << "Train OA: " << conf.overall_accuracy() << endl;
    
    // Check Test
    artelab::feature_patterns(&rbm, test, test_feat);
    conf.reset();
    
    svm.predict(test_feat, predictions);
    conf.add(predictions, test_lab);
    cout << "Test OA: " << conf.overall_accuracy() << endl;
    
    return EXIT_SUCCESS;
}

