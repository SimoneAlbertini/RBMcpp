/* 
 * File:   SVM.h
 * Author: Simone Albertini
 * 
 * albertini.simone@gmail.com
 * http://www.dicom.uninsubria.it/~simone.albertini/
 * 
 */

#ifndef SVM_H
#define	SVM_H

#include <opencv2/ml/ml.hpp>

namespace artelab
{

    class SVM 
    {
    public:

        enum { NO_KFOLD = 0 };

        SVM(cv::SVMParams params=cv::SVMParams());

        void load(std::string file);
        void save(std::string file);

        bool train(const cv::Mat& trainingData, const cv::Mat& targets, const int kfold=NO_KFOLD);
        void predict(const cv::Mat& samples, cv::Mat& outPredictions);

        bool is_trained();

        cv::SVMParams get_params();
        SVM& set_params(cv::SVMParams params);
        std::string description();


    private:
        cv::SVMParams _params;
        cv::SVM _model;
        bool _trained;
    };
}
    
#endif	/* SVM_H */

