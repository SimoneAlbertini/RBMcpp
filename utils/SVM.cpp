/* 
 * File:   SVM.cpp
 * Author: Simone Albertini
 * 
 * albertini.simone@gmail.com
 * http://www.dicom.uninsubria.it/~simone.albertini/
 * 
 */

#include "SVM.h"

namespace artelab
{

    SVM::SVM(cv::SVMParams params)
    {
        _params = params;
        _model = cv::SVM();
    }

    bool SVM::is_trained()
    {
        return _trained;
    }

    void SVM::load(std::string file)
    {
        _model.load(file.c_str());
        _params = _model.get_params();
        _trained = true;
    }

    void SVM::save(std::string file)
    {
        _model.save(file.c_str());
    }

    bool SVM::train(const cv::Mat& trainingData, const cv::Mat& targets, const int kfold)
    {
        if(kfold == NO_KFOLD)
        {
            _trained = _model.train(trainingData, targets, cv::Mat(), cv::Mat(), _params);
            _params = _model.get_params();
        }
        else if(kfold > 1)
        {
            _trained = _model.train_auto(trainingData, targets, cv::Mat(), cv::Mat(), _params, kfold);
            _params = _model.get_params();
        }
        else
        {
            _trained = false;
        }
        return _trained;
    }

    void SVM::predict(const cv::Mat& samples, cv::Mat& outPredictions)
    {
        outPredictions.create(samples.rows, 1, CV_32FC1);
        for(unsigned int i = 0; i < samples.rows; i++)
        {
            outPredictions.at<float>(i, 0) = _model.predict(samples.row(i));
        }
    }

    cv::SVMParams SVM::get_params()
    {
        return _params;
    }

    SVM& SVM::set_params(cv::SVMParams params)
    {
        _params = params;
        return *this;
    }

    std::string SVM::description()
    {
        std::ostringstream ss;

        ss << "SVM Type: ";
        switch(_params.svm_type)
        {
            case cv::SVM::C_SVC:
                ss << "C_SVC\n" << "C: " << _params.C;
                break;
            case cv::SVM::NU_SVC:
                ss << "NU_SVC\n" << "Nu: " << _params.nu;
                break;
            case cv::SVM::ONE_CLASS:
                ss << "ONE_CLASS\n" << "Nu: " << _params.nu;
                break;
            case cv::SVM::EPS_SVR:
                ss << "EPS_SVR\n" << "C: " << _params.C << " p: " << _params.p;
                break;
            case cv::SVM::NU_SVR:
                ss << "NU_SVR\n" << "C: " << _params.C << " Nu: " << _params.nu;
                break;
            default:
                ss << "-unknown type-";
        }
        ss << "\n";

        ss << "Kernel: ";
        switch(_params.kernel_type)
        {
            case cv::SVM::LINEAR:
                ss << "LINEAR";
                break;
            case cv::SVM::POLY:
                ss << "POLY degree" << _params.degree 
                   << " gamma: " << _params.gamma
                   << " coef0: " << _params.coef0;
                break;
            case cv::SVM::RBF:
                ss << "RBF gamma: " << _params.gamma;
                break;
            case cv::SVM::SIGMOID:
                ss << "SIGMOID gamma: " << _params.gamma 
                   << " coef0: " << _params.coef0;
                break;
            default:
                ss << "-unknown kernel-";
        }
        ss << "\n";

        ss << "TERM type: ";
        switch(_params.term_crit.type)
        {
            case CV_TERMCRIT_ITER:
                ss << "iter " << _params.term_crit.max_iter;
                break;
            case CV_TERMCRIT_EPS:
                ss << "epsilon " << _params.term_crit.epsilon;
                break;
            case CV_TERMCRIT_EPS | CV_TERMCRIT_ITER:
                ss << "iter&epsilon iter: " << _params.term_crit.max_iter
                   << " epsilon: " << _params.term_crit.epsilon;
                break;
            default:
                ss << "-no term criteria-";
        }

        return ss.str();
    }

}